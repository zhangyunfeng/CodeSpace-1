/**
 * @file   PdfXmlLoader.cpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Thu Sep 10 23:59:59 2015
 * 
 * @brief  
 * 
 * 
 */


#include "PdfXmlLoader.hpp"
#include "GlobalInclude.hpp"
#include "MiscUtils.hpp"

PdfXmlLoader::PdfXmlLoader() {
    
}

PdfXmlLoader::PdfXmlLoader(const std::string& xmlfile) : XmlLoader(xmlfile){
    
}

PdfXmlLoader::~PdfXmlLoader() {
    
}


void PdfXmlLoader::ParseXml(TiXmlElement* m_rootElement) {
    if (m_rootElement) {
        HandlePdfElement(m_rootElement);
        TiXmlElement* page_element = m_rootElement->FirstChildElement(PageProperties::TAG.c_str());
        int page_id = 0;
        while (page_element) { // handle page element
            page_id++;
            HandlePageElement(page_element, page_id);

            // Line
            TiXmlElement* line_element = page_element->FirstChildElement(LineProperties::TAG.c_str());
            while (line_element) {
                HandleLineElement(line_element);
                line_element = line_element->NextSiblingElement(LineProperties::TAG.c_str());
            }

            // Text
            TiXmlElement* text_element = page_element->FirstChildElement(TextProperties::TAG.c_str());
            while (text_element) {
                HandleTextElement(text_element);
                text_element = text_element->NextSiblingElement(TextProperties::TAG.c_str());
            }

            // Rect
            TiXmlElement* rect_element = page_element->FirstChildElement(RectProperties::TAG.c_str());
            while (rect_element) {
                HandleRectElement(rect_element);
                rect_element = rect_element->NextSiblingElement(RectProperties::TAG.c_str());
            }

            // Image
            TiXmlElement* image_element = page_element->FirstChildElement(ImageProperties::TAG.c_str());
            while (image_element) {
                HandleImageElement(image_element);
                image_element = image_element->NextSiblingElement(ImageProperties::TAG.c_str());
            }
                    
            page_element = page_element->NextSiblingElement(PageProperties::TAG.c_str());
        }
        
    }
}


void PdfXmlLoader::HandlePdfElement(TiXmlElement* element) {
    if (element == nullptr) {
        return;
    }
    
     const std::string* strptr = nullptr;
    strptr = element->Attribute(PdfProperties::ATTR_PAGELAYOUT);
    if (strptr != nullptr) {
        m_pdfProperties.page_layout = *strptr;
        strptr = nullptr;
    }

    strptr = element->Attribute(PdfProperties::ATTR_FONT);
    if (strptr != nullptr) {
        m_pdfProperties.fontname = *strptr;
        strptr = nullptr;
    }

    strptr = element->Attribute(PdfProperties::ATTR_COMPRESSMODE);
    if (strptr != nullptr) {
        m_pdfProperties.compress_mode = *strptr;
        strptr = nullptr;
    }

    strptr = element->Attribute(PdfProperties::ATTR_PAGEMODE);
    if (strptr != nullptr) {
        m_pdfProperties.page_mode = *strptr;
        strptr = nullptr;
    }

    strptr = element->Attribute(PdfProperties::ATTR_OWNER);
    if (strptr != nullptr) {
        m_pdfProperties.owner = *strptr;
        strptr = nullptr;
    }

    strptr = element->Attribute(PdfProperties::ATTR_PASSWD);
    if (strptr != nullptr) {
        m_pdfProperties.password = *strptr;
        strptr = nullptr;
    }

    strptr = element->Attribute(PdfProperties::ATTR_DOCNAME);
    if (strptr != nullptr) {
        m_pdfProperties.docname = *strptr;
        strptr = nullptr;
    }
    
}

void PdfXmlLoader::HandlePageElement(TiXmlElement* element, int page_id) {
    if (element == nullptr) {
        return;
    }

    PageProperties pageProperties;
    pageProperties.SetPageId(page_id);

    const std::string* strptr = nullptr;
    strptr = element->Attribute(PageProperties::ATTR_WIDTH);
    if (strptr != nullptr) {
        pageProperties.width = *strptr;
        strptr = nullptr;
    }

    strptr = element->Attribute(PageProperties::ATTR_HEIGHT);
    if (strptr != nullptr) {
        pageProperties.height = *strptr;
        strptr = nullptr;
    }

    strptr = element->Attribute(PageProperties::ATTR_PAGESIZE);
    if (strptr != nullptr) {
        pageProperties.page_size = *strptr;
        strptr = nullptr;
    }

    strptr = element->Attribute(PageProperties::ATTR_PAGEROTATE);
    if (strptr != nullptr) {
        pageProperties.page_rotate = *strptr;
        strptr = nullptr;
    }

    strptr = element->Attribute(PageProperties::ATTR_ANNOT);
    if (strptr != nullptr) {
        pageProperties.annot = *strptr;
        strptr = nullptr;
    }

    strptr = element->Attribute(PageProperties::ATTR_SLIDESHOWTYPE);
    if (strptr != nullptr) {
        pageProperties.pageSlideShowType = *strptr;
        strptr = nullptr;
    }
    m_pageProperties.push_back(pageProperties);

    strptr = element->Attribute(PageProperties::ATTR_FONT);
    if (strptr != nullptr) {
        pageProperties.fontname = *strptr;
        strptr = nullptr;
    }
    
    
    
}

void PdfXmlLoader::HandleLineElement(TiXmlElement* lineElement) {
    if (!lineElement) {
        return;
    }
    LineProperties lineProperties;
    const std::string* strptr = nullptr;
    strptr = lineElement->Attribute(LineProperties::ATTR_LABLE);
    if (strptr != nullptr) {
        lineProperties.lable = *strptr;
        strptr = nullptr;
    }
    
    strptr = lineElement->Attribute(LineProperties::ATTR_X0);
    if (strptr != nullptr) {
        lineProperties.startX = *strptr;
        strptr = nullptr;
    }

    strptr = lineElement->Attribute(LineProperties::ATTR_Y0);
    if (strptr != nullptr) {
        lineProperties.startY = *strptr;
        strptr = nullptr;
    }

    strptr = lineElement->Attribute(LineProperties::ATTR_X1);
    if (strptr != nullptr) {
        lineProperties.endX = *strptr;
        strptr = nullptr;
    }

    strptr = lineElement->Attribute(LineProperties::ATTR_Y1);
    if (strptr != nullptr) {
        lineProperties.endY = *strptr;
        strptr = nullptr;
    }

    strptr = lineElement->Attribute(LineProperties::ATTR_LINEWIDTH);
    if (strptr != nullptr) {
        lineProperties.lineWidth = *strptr;
        strptr = nullptr;
    }

    strptr = lineElement->Attribute(LineProperties::ATTR_RGB);
    if (strptr != nullptr) {
        lineProperties.rgb = *strptr;
        strptr = nullptr;
    }

    strptr = lineElement->Attribute(LineProperties::ATTR_LINETYPE);
    if (strptr != nullptr) {
        lineProperties.lineType = *strptr;
        strptr = nullptr;
    }

    PageProperties& pageProperties = m_pageProperties.back();
    pageProperties.linesVec.push_back(lineProperties);
}

void PdfXmlLoader::HandleTextElement(TiXmlElement* textElement) {
    if (!textElement) {
        return;
    }

    TextProperties textProperties;
    const std::string* strptr = nullptr;
    strptr = textElement->Attribute(TextProperties::ATTR_FONT);
    if (strptr) {
        textProperties.font = *strptr;
        strptr = nullptr;
    }

    strptr = textElement->Attribute(TextProperties::ATTR_SIZE);
    if (strptr) {
        textProperties.size = *strptr;
        strptr = nullptr;
    }

    strptr = textElement->Attribute(TextProperties::ATTR_RGB);
    if (strptr) {
        textProperties.rgb = *strptr;
        strptr = nullptr;
    }

    strptr = textElement->Attribute(TextProperties::ATTR_INCLUDE);
    if (strptr) {
        textProperties.includeDoc = *strptr;
        textProperties.text += MiscUtils::GetFileText(textProperties.includeDoc);
        std::cout << "include text: " << textProperties.text << std::endl;
        strptr = nullptr;
    }

    strptr = textElement->Attribute(TextProperties::ATTR_TEXTX);
    if (strptr) {
        textProperties.textX = *strptr;
        strptr = nullptr;
    }

    strptr = textElement->Attribute(TextProperties::ATTR_TEXTY);
    if (strptr) {
        textProperties.textY = *strptr;
        strptr = nullptr;
    }

    strptr = textElement->Attribute(TextProperties::ATTR_TEXTW);
    if (strptr) {
        textProperties.textWidth = *strptr;
        strptr = nullptr;
    }

    strptr = textElement->Attribute(TextProperties::ATTR_TEXTH);
    if (strptr) {
        textProperties.textHeight = *strptr;
        strptr = nullptr;
    }

    if (textElement->GetText() != nullptr) {
        std::string content(textElement->GetText());
        textProperties.text += content;
    }

    PageProperties& pageProperties = m_pageProperties.back();
    pageProperties.textVec.push_back(textProperties);
}


void PdfXmlLoader::HandleRectElement(TiXmlElement* rectElement) {
    if (!rectElement) {
        return;
    }
   RectProperties rectProperties;
   const std::string* strptr = nullptr;
 
   strptr = rectElement->Attribute(RectProperties::ATTR_LINEWIDTH);
   if (strptr != nullptr) {
       rectProperties.lineWidth = *strptr;
       strptr = nullptr;
   }

   strptr = rectElement->Attribute(RectProperties::ATTR_WIDTH);
   if (strptr != nullptr) {
       rectProperties.width = *strptr;
       strptr = nullptr;
   }


      strptr = rectElement->Attribute(RectProperties::ATTR_HEIGHT);
   if (strptr != nullptr) {
       rectProperties.height = *strptr;
       strptr = nullptr;
   }


      strptr = rectElement->Attribute(RectProperties::ATTR_RGB);
   if (strptr != nullptr) {
       rectProperties.rgb = *strptr;
       strptr = nullptr;
   }


      strptr = rectElement->Attribute(RectProperties::ATTR_STYLE);
   if (strptr != nullptr) {
       rectProperties.rectStyle = *strptr;
       strptr = nullptr;
   }

   strptr = rectElement->Attribute(RectProperties::ATTR_X);
   if (strptr != nullptr) {
       rectProperties.x = *strptr;
       strptr = nullptr;
   }

   strptr = rectElement->Attribute(RectProperties::ATTR_Y);
   if (strptr != nullptr) {
       rectProperties.y = *strptr;
       strptr = nullptr;
   }

   PageProperties& pageProperties = m_pageProperties.back();
   pageProperties.rectVec.push_back(rectProperties);
}

void PdfXmlLoader::HandleImageElement(TiXmlElement* imageElement) {
    if (!imageElement) {
        return;
    }
    ImageProperties imageProperties;
    const std::string* strptr = nullptr;
    
    strptr = imageElement->Attribute(ImageProperties::ATTR_SRC);
    if (strptr) {
        imageProperties.src = *strptr;
        strptr = nullptr;
    }

    strptr = imageElement->Attribute(ImageProperties::ATTR_X);
    if (strptr) {
        imageProperties.x = *strptr;
        strptr = nullptr;
    }

    strptr = imageElement->Attribute(ImageProperties::ATTR_Y);
    if (strptr) {
        imageProperties.y = *strptr;
        strptr = nullptr;
    }

    strptr = imageElement->Attribute(ImageProperties::ATTR_WIDTH);
    if (strptr) {
        imageProperties.width = *strptr;
        strptr = nullptr;
    }

    strptr = imageElement->Attribute(ImageProperties::ATTR_HEIGHT);
    if (strptr) {
        imageProperties.height = *strptr;
        strptr = nullptr;
    }

   PageProperties& pageProperties = m_pageProperties.back();
   pageProperties.imagesVec.push_back(imageProperties);           
}


const PdfProperties& PdfXmlLoader::GetPdfProperties(void) {
    return m_pdfProperties;
}

const std::vector<PageProperties>& PdfXmlLoader::GetPagesProperties(void) {
    return m_pageProperties;
}

