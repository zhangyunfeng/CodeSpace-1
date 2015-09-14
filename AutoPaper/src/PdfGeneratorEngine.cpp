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
        std::cerr << "Error: Can not create PdfDoc obbject" << std::endl;
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



