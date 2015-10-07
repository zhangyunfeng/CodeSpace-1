/**
 * @file   PdfGeneratorEngineHelper.cpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Tue Sep 15 00:30:28 2015
 * 
 * @brief  
 * 
 * 
 */

#include "../libharu/include/hpdf.h"
#include "../libharu/include/hpdf_types.h"
#include "Constants.hpp"
#include "./PdfGeneratorEngineHelper.hpp"


/** 
 * hpdf_consts.h  HPDF_COMP_XXX
 * 
 * @param compress_mode 
 * 
 * @return 
 */

HPDF_UINT PdfGeneratorEngineHelper::GetCompressMode(const std::string& compress_mode) {
    if (Constants::CompressMode::ALL.compare(compress_mode) == 0) {
        return HPDF_COMP_ALL;
    }
    if (Constants::CompressMode::NONE.compare(compress_mode) == 0) {
        return HPDF_COMP_NONE;
    }
    if (Constants::CompressMode::TEXT.compare(compress_mode) == 0) {
        return HPDF_COMP_TEXT;
    }
    if (Constants::CompressMode::IMAGE.compare(compress_mode) == 0) {
        return HPDF_COMP_IMAGE;
    }
    if (Constants::CompressMode::METADATA.compare(compress_mode) == 0) {
        return HPDF_COMP_METADATA;
    }
    return HPDF_COMP_NONE;
}

HPDF_PageMode PdfGeneratorEngineHelper::GetPageMode(const std::string& page_mode) {
    if (Constants::PageMode::NONE.compare(page_mode) == 0) {
        return HPDF_PAGE_MODE_USE_NONE;
    }
    if (Constants::PageMode::THUMBS.compare(page_mode) == 0) {
        return HPDF_PAGE_MODE_USE_THUMBS;
    }
    if (Constants::PageMode::OUTLINE.compare(page_mode) == 0) {
        return HPDF_PAGE_MODE_USE_OUTLINE;
    }
    if (Constants::PageMode::FULL_SCREEN.compare(page_mode) == 0) {
        return HPDF_PAGE_MODE_FULL_SCREEN;
    }
    return HPDF_PAGE_MODE_USE_NONE;
}




