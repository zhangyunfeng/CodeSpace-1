/**
 * @file   PdfGeneratorEngine.cpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Mon Sep 14 21:39:25 2015
 * 
 * @brief  
 * 
 * 
 */


#include "PdfGeneratorEngine.hpp"
#include "PdfGeneratorEngineHelper.hpp"
#include "MiscUtils.hpp"

jmp_buf PdfGeneratorEngine::env;

PdfGeneratorEngine::PdfGeneratorEngine() {
    init();
}

PdfGeneratorEngine::PdfGeneratorEngine(const std::string& xmlfile) : m_xmlfile(xmlfile){
    init();
}

/** 
 * release resources
 * 
 */
PdfGeneratorEngine::~PdfGeneratorEngine() {
    if (m_hpdf_doc) {
        HPDF_Free(m_hpdf_doc);
    }

    if (m_pdfXmlLoader) {
        delete m_pdfXmlLoader;
        m_pdfXmlLoader = nullptr;
    }
}


void PdfGeneratorEngine::init() {
    m_pdfXmlLoader = new PdfXmlLoader();
    m_hpdf_doc = HPDF_New(&PdfGeneratorEngine::ErrorHandler, nullptr);
    if (!m_hpdf_doc) {
        std::cerr << "Error: Can not create PdfDoc object" << std::endl;
        return ;
    }

    if (setjmp(env)) {
        HPDF_Free(m_hpdf_doc);
        abort();
    }
    m_pdfTitle = "untitled.pdf";
}

void PdfGeneratorEngine::LoadXml(void) {
    if (! m_xmlfile.empty() && m_pdfXmlLoader) {
        m_pdfXmlLoader->LoadXml(m_xmlfile);
    }
}

void PdfGeneratorEngine::ErrorHandler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void* user_data) {
    printf("ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no, (HPDF_UINT)detail_no);
    longjmp(env, 1);
}

void PdfGeneratorEngine::SetXml(const std::string& xmlfile) {
    m_xmlfile = xmlfile;
    HPDF_Free(m_hpdf_doc);
    if (m_pdfXmlLoader) {
        delete m_pdfXmlLoader;
        m_pdfXmlLoader = nullptr;
    }
    m_pdfXmlLoader = new PdfXmlLoader();
    if (m_pdfXmlLoader) {
        m_pdfXmlLoader->LoadXml(m_xmlfile);
    }
}

void PdfGeneratorEngine::ConfigPdfProperties(const PdfProperties& pdfProperties) {
    if (m_hpdf_doc) {
        // 使用中文自体
        HPDF_UseCNSFonts(m_hpdf_doc);

        // 压缩模式
        std::string compress_mode = pdfProperties.compress_mode;
        HPDF_SetCompressionMode(m_hpdf_doc, PdfGeneratorEngineHelper::GetCompressMode(compress_mode));
        HPDF_SetPageMode(m_hpdf_doc, PdfGeneratorEngineHelper::GetPageMode(pdfProperties.page_mode));
        if (!pdfProperties.owner.empty() && !pdfProperties.password.empty()) {
            HPDF_SetPassword(m_hpdf_doc, pdfProperties.owner.c_str(), pdfProperties.password.c_str());
        }
        //        SetPdfTitle(pdfProperties.docname);
    }
}


void PdfGeneratorEngine::DrawLine(const LineProperties& lineProperties, HPDF_Page& page) {
    HPDF_Page_SetLineWidth(page, MiscUtils::String2Int(lineProperties.lineWidth));

    int r = MiscUtils::GetR(lineProperties.rgb);
    int g = MiscUtils::GetG(lineProperties.rgb);
    int b = MiscUtils::GetB(lineProperties.rgb);
    HPDF_Page_SetRGBStroke (page, r / 255.0f, g / 255.0f, b / 255.0f);

    HPDF_Page_SetLineJoin(page, HPDF_MITER_JOIN);

    int startx = MiscUtils::String2Int(lineProperties.startX);
    int starty =  HPDF_Page_GetHeight(page) -  MiscUtils::String2Int(lineProperties.startY);
    HPDF_Page_MoveTo(page, startx, starty);
    int endx = MiscUtils::String2Int(lineProperties.endX);
    int endy =  HPDF_Page_GetHeight(page) - MiscUtils::String2Int(lineProperties.endY);

    HPDF_Page_LineTo(page, endx, endy);
    HPDF_Page_Stroke(page);
}

/** 
 * draw rect
 * 
 * @param rectProperties 
 * @param page 
 */
void PdfGeneratorEngine::DrawRect(const RectProperties& rectProperties, HPDF_Page& page) {
    HPDF_Page_Rectangle(page, MiscUtils::String2Int(rectProperties.x), MiscUtils::String2Int(rectProperties.y),
                       MiscUtils::String2Int(rectProperties.width), MiscUtils::String2Int(rectProperties.height));
    
}



void PdfGeneratorEngine::DrawPage(const PageProperties& pageProperties) {
    HPDF_Page page = HPDF_AddPage(m_hpdf_doc);
    const int page_width = MiscUtils::String2Int(pageProperties.width);
    const int page_height = MiscUtils::String2Int(pageProperties.height);

    HPDF_PageSizes page_size = PdfGeneratorEngineHelper::GetPageSize(pageProperties.page_size);  
    if (HPDF_PAGE_SIZE_EOF == page_size) {
        HPDF_Page_SetWidth(page, page_width);
        HPDF_Page_SetHeight(page, page_height);
    } else {
        HPDF_Page_SetSize(page, page_size, HPDF_PAGE_PORTRAIT);
    }

    std::vector<LineProperties>::const_iterator linesVecNext = pageProperties.linesVec.begin();  // lines
    std::vector<LineProperties>::const_iterator linesVecEnd = pageProperties.linesVec.end();
    for (; linesVecNext != linesVecEnd; linesVecNext++) {
        std::cout << "draw line" << std::endl;
        DrawLine(*linesVecNext, page);
    }

    std::vector<TextProperties>::const_iterator textVecNext = pageProperties.textVec.begin();   // text
    std::vector<TextProperties>::const_iterator textVecEnd = pageProperties.textVec.end();
    for (; textVecNext != textVecEnd; textVecNext++) {
        std::cout << "draw text start..." << std::endl;
        DrawText(*textVecNext, page);
        std::cout << "draw text end!" << std::endl << std::endl;
        
    }
        
    std::vector<RectProperties>::const_iterator rectVecNext = pageProperties.rectVec.begin();
    std::vector<RectProperties>::const_iterator rectVecEnd = pageProperties.rectVec.end();
    for (; rectVecNext != rectVecEnd; rectVecNext++) {
        std::cout << "draw rect" << std::endl;
        DrawRect(*rectVecNext, page);
    }
    
    std::vector<ImageProperties>::const_iterator imagesVecNext = pageProperties.imagesVec.begin();
    std::vector<ImageProperties>::const_iterator imagesVecEnd = pageProperties.imagesVec.end();
    for (; imagesVecNext != imagesVecEnd; imagesVecNext++) {
        std::cout << "draw image" << std::endl;
        DrawImage(*imagesVecNext, page);
    }
 }

/** 
 * draw text
 * 坐标 原点转换到左上角
 * @param textProperties 
 * @param page 
 */
void PdfGeneratorEngine::DrawText(const TextProperties& textProperties, HPDF_Page& page) {
    HPDF_Page_BeginText(page);
    int x = MiscUtils::String2Int(textProperties.textX);
    int y = MiscUtils::String2Int(textProperties.textY);
    int text_rectWidth = MiscUtils::String2Int(textProperties.textWidth);
    int text_rectHeight = MiscUtils::String2Int(textProperties.textHeight);
    if (0 == text_rectWidth) {
        text_rectWidth = HPDF_Page_GetWidth(page) - x;
    }
    if (0 == text_rectHeight) {
        text_rectHeight = HPDF_Page_GetHeight(page) - y;
    }
    int page_height = HPDF_Page_GetHeight(page);

    HPDF_Font font = HPDF_GetFont(m_hpdf_doc, textProperties.font.c_str(), nullptr);
    int r = MiscUtils::GetR(textProperties.rgb);
    int g = MiscUtils::GetG(textProperties.rgb);
    int b = MiscUtils::GetB(textProperties.rgb);
    HPDF_Page_SetRGBFill (page, r / 255.0f, g / 255.0f, b / 255.0f);
    HPDF_Page_SetFontAndSize(page, font, MiscUtils::String2Int(textProperties.size));
    HPDF_Page_TextRect(page, x, page_height - y, x + text_rectWidth, page_height - y - text_rectHeight,
                       textProperties.text.c_str(), HPDF_TALIGN_LEFT, nullptr);

    HPDF_Page_EndText(page);
}


/** 
 * draw iamges  (png  )
 * 
 * @param imageProperties 
 * @param page 
 */
void PdfGeneratorEngine::DrawImage(const ImageProperties& imageProperties, HPDF_Page& page) {
    HPDF_Image image;

    // image png format
    // TODO: need add HPDF_LoadJpegImageFromFile 
    image = HPDF_LoadPngImageFromFile(m_hpdf_doc, imageProperties.src.c_str());
    const int image_width = HPDF_Image_GetWidth(image);
    const int image_height = HPDF_Image_GetHeight(image);
    // draw image(png) to the canvas
    HPDF_Page_DrawImage(page, image, MiscUtils::String2Int(imageProperties.x), MiscUtils::String2Int(imageProperties.y), image_width, image_height);
}


/** 
 * 
 * 
 */
void PdfGeneratorEngine::OnDrawPdf(void) {
    if (m_pdfXmlLoader != nullptr) {
        PdfProperties pdfProperties = m_pdfXmlLoader->GetPdfProperties();
        ConfigPdfProperties(pdfProperties);
        std::vector<PageProperties> pagesPropertiesVec = m_pdfXmlLoader->GetPagesProperties();
        std::vector<PageProperties>::iterator itNext = pagesPropertiesVec.begin();
        std::vector<PageProperties>::iterator itEnd = pagesPropertiesVec.end();
        for (; itNext != itEnd; itNext++) {
            std::cout <<"draw page start..." <<std::endl;
            DrawPage(*itNext);
            std::cout <<"draw page end!" << std::endl << std::endl;
        }
    }
}


void PdfGeneratorEngine::SaveDoc(void) {
    if (m_hpdf_doc != nullptr) {
        HPDF_SaveToFile(m_hpdf_doc, m_pdfTitle.c_str());
        
    }

}


void PdfGeneratorEngine::SetPdfTitle(const std::string& title) {
    m_pdfTitle = title;
}

void PdfGeneratorEngine::SetPdfXmlLoader(PdfXmlLoader* pdfXmlLoader) {
    if (m_pdfXmlLoader) {
        delete m_pdfXmlLoader;
        m_pdfXmlLoader = nullptr;
    }

    m_pdfXmlLoader = pdfXmlLoader;
}
