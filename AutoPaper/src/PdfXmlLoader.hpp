/**
 * @file   PdfXmlLoader.hpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Fri Sep 11 00:00:27 2015
 * 
 * @brief  加载生成pdf的xml文档， 解析出其中所有的文档和属性
 * 
 * 
 */

#include <string>
#include <vector>
#include "XmlLoader.hpp"

#include "PdfCommonData.hpp"
#include "GlobalInclude.hpp"


class PdfXmlLoader : public XmlLoader
{
  public:
    PdfXmlLoader();
    PdfXmlLoader(const std::string& xmlfile);

    virtual ~PdfXmlLoader();
    void HandlePdfElement(TiXmlElement* element);
    void HandlePageElement(TiXmlElement* element, int page_id);

    void HandleDrawElements(TiXmlElement* element);

    void HandleTextElement(TiXmlElement* textElement);
    void HandleLineElement(TiXmlElement* lineElement);
    void HandleRectElement(TiXmlElement* rectElement);
    void HandleImageElement(TiXmlElement* imageElement);

    const PdfProperties& GetPdfProperties(void) ;
    const std::vector<PageProperties>& GetPagesProperties(void);

  protected:
    virtual void ParseXml(TiXmlElement* m_rootElement);
  private:
    PdfProperties m_pdfProperties;
    std::vector<PageProperties> m_pageProperties;

};

