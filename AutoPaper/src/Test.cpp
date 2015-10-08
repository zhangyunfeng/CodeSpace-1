/**
 * @file   Test.cpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Sun Sep 13 21:18:01 2015
 * 
 * @brief  
 * 
 * 
 */

#include <iostream>
#include <string>

#include "PdfXmlLoader.hpp"
#include "PdfCommonData.hpp"
#include "PdfGeneratorEngine.hpp"


int main(int argc, char *argv[])
{
    PdfXmlLoader* p = new PdfXmlLoader();

    std::cout << "LoadXml..." << std::endl;
    p->LoadXml("./pdf.xml");

    std::cout << "GetPdfProperties " << std::endl;
    PdfProperties pf = p->GetPdfProperties();
    std::cout << "Printing: " << std::endl;
    std::cout << pf.fontname << " " << pf.owner << " " << pf.password << " " << pf.page_layout << " " << pf.compress_mode << std::endl;

    PdfGeneratorEngine* engine = new PdfGeneratorEngine();
    // engine->SetXml("./pdf.xml");
    
    engine->SetPdfXmlLoader(p);
    engine->OnDrawPdf();
    engine->SaveDoc();
    
    return 0;
}




