/**
 * @file   PdfGeneratorEngineHelper.hpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Tue Sep 15 00:30:47 2015
 * 
 * @brief  
 * 
 * 
 */


#ifndef PDFGENERATORENGINEHELPER_H
#define PDFGENERATORENGINEHELPER_H

#include <string>
#include "../libharu/include/hpdf.h"

class PdfGeneratorEngineHelper
{
  private:
    PdfGeneratorEngineHelper(){}
    virtual ~PdfGeneratorEngineHelper(){}
  public:
    static HPDF_UINT GetCompressMode(const std::string& compress_mode);
    static HPDF_PageMode GetPageMode(const std::string& page_mode);
    static HPDF_PageSizes GetPageSize(const std::string& page_size); // a3, a4, a5...
};



#endif /* PDFGENERATORENGINEHELPER_H */

