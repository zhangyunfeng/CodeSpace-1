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
    }
}


void PdfGeneratorEngine::DrawLine(const LineProperties& lineProperties, HPDF_Page& page) {
    HPDF_Page_MoveTo(page, MiscUtils::String2Int(lineProperties.startX), MiscUtils::String2Int(lineProperties.startY));
    HPDF_Page_LineTo(page, MiscUtils::String2Int(lineProperties.endX), MiscUtils::String2Int(lineProperties.endY));
    HPDF_Page_Stroke(page);
}

/** 
 * draw rect
 * 
 * @param rectProperties 
 * @param page 
 */
void PdfGeneratorEngine::DrawRect(RectProperties& rectProperties, HPDF_Page& page) {
    HPDF_Page_Retangle(page, MiscUtils::String2Int(rectProperties.x), MiscUtils::String2Int(rectProperties.y),
                       MiscUtils::String2Int(rectProperties.width), MiscUtils::String2Int(rectProperties.height));
    
}



void PdfGeneratorEngine::DrawPage(PageProperties& pageProperties) {
    HPDF_Page page = HPDF_AddPage(m_hpdf_doc);
    const int page_width = MiscUtils::String2Int(pageProperties.width);
    const int page_height = MiscUtils::String2Int(pageProperties.height);
    
    HPDF_Page_SetWidth(page, page_width);
    HPDF_Page_SetHeight(page, page_height);

    std::vector<LineProperties>::iterator linesVecNext = pageProperties.linesVec.begin();  // lines
    std::vector<LineProperties>::iterator linesVecEnd = pageProperties.linesVec.end();
    for (linesVecNext; lineVecNext != linesVecEnd; linesVecNext++) {
        DrawLine(*linesVecNext, page);
    }

    std::vector<TextProperties>::iterator textVecNext = pageProperties.textVec.begin();   // text
    std::vector<TextProperties>::iterator textVecEnd = pageProperties.textVec.end();
    for (textVecNext; textVecNext != textVecEnd; textVecNext++) {
        DrawText(*textVecNext, page);
    }
        
    std::vector<RectProperties>::iterator rectVecNext = pageProperties.rectVec.begin();
    std::vector<RectProperties>::iterator rectVecEnd = pageProperties.rectVec.end();
    for (rectVecNext; rectVecNext != rectVecEnd; rectVecNext++) {
        DrawRect(*rectVecNext, page);
    }
    
    std::vector<ImageProperties> imagesVec;  // images
    std::vector<ImageProperties> imagesVecNext = pageProperties.imagesVec.begin();
    std::vector<ImageProperties> imagesVecEnd = pageProperties.imageVec.end();
    for (imagesVecNext; imagesVecNext != imagesVecEnd; imagesVecNext++) {
        DrawImage(*imageVecNext, page);
    }
 }

/** 
 * draw text
 * 
 * @param textProperties 
 * @param page 
 */
void PdfGeneratorEngine::DrawText(TextProperties& textProperties, HPDF_Page& page) {
    HPDF_REAL text_width = HPDF_Page_TextWidth(page, textProperties.text.c_str());
    HPDF_Page_BeginText(page);
    int x = MiscUtils::String2Int(textProperties.textX);
    int y = MiscUtils::String2Int(textProperties.textY);
    HPDF_Page_MoveTextPos(page, x, y);
    HPDF_Page_SetFontAndSize(page, textProperties.font.c_str(), MiscUtils::String2Int(textProperties.size));
    HPDF_Page_ShowText(page, textProperties.text.c_str());
    HPDF_Page_EndText(page);
}


/** 
 * draw iamges  (png  )
 * 
 * @param imageProperties 
 * @param page 
 */
void PdfGeneratorEngine::DrawImage(ImageProperties& imageProperties, HPDF_Page& page) {
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
    
}


void PdfGeneratorEngine::SaveDoc(void) {
    
}
