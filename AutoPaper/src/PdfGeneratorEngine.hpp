/**
 * @file   PdfGeneratorEngine.hpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Mon Sep 14 21:39:17 2015
 * 
 * @brief  
 * 
 * 
 */


#ifndef PDFGENERATORENGINE_H
#define PDFGENERATORENGINE_H

#include <memory>
#include <vector>
#include <string>

#ifdef __CPLUSPLUS
extern "C" {
#endif

#include <setjmp.h>

#ifdef __CPLUSPLUS
}
#endif

#include "PdfXmlLoader.hpp"
#include "../libharu/include/hpdf.h"
#include "PdfCommonData.hpp"

class PdfGeneratorEngine
{
  public:
    PdfGeneratorEngine();
    PdfGeneratorEngine(const std::string& xmlfile);
    virtual ~PdfGeneratorEngine(); // HPDF_Free(m_hpdf_doc);

    void SetPdfXmlLoader(PdfXmlLoader* pdfXmlLoader);
    void SetPdfTitle(const std::string& title);
    void LoadXml(void);
    void SetXml(const std::string& xmlfile);
    
    void ConfigPdfProperties(const PdfProperties& pdfProperties);
    void DrawPage(const PageProperties& pageProperties);

    void DrawLine(const LineProperties& lineProperties, HPDF_Page& page);
    void DrawRect(const RectProperties& rectProperties, HPDF_Page& page);
    void DrawText(const TextProperties& textProperties, HPDF_Page& page);
    void DrawImage(const ImageProperties& iamgeProperties, HPDF_Page& page);

    void OnDrawPdf(void);

    void SaveDoc(void);
    
    static void ErrorHandler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void* user_data);
  private:
    void init(void);
    
  private:
    std::string m_xmlfile;
    PdfXmlLoader* m_pdfXmlLoader;
    std::string m_pdfTitle;
    HPDF_Doc m_hpdf_doc;
    std::vector<HPDF_Page> m_pages;

    static jmp_buf env;
};


#endif /* PDFGENERATORENGINE_H */
