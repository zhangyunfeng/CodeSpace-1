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


HPDF_PageSizes PdfGeneratorEngineHelper::GetPageSize(const std::string& page_size) {
    if ("letter" == page_size) {
        return HPDF_PAGE_SIZE_LETTER;
    } else if ("legal" == page_size) {
        return HPDF_PAGE_SIZE_LEGAL;
    } else if ("a3" == page_size) {
        return HPDF_PAGE_SIZE_A3;
    } else if ("a4" == page_size) {
        return HPDF_PAGE_SIZE_A4; 
    } else if ("a5" == page_size) {
        return HPDF_PAGE_SIZE_A5;
    } else if ("b4" == page_size) {
        return HPDF_PAGE_SIZE_B4;
    } else if ("b5" == page_size) {
        return HPDF_PAGE_SIZE_B5;
    } else if ("executive" == page_size) {
        return HPDF_PAGE_SIZE_EXECUTIVE;
    } else if ("us4x6" == page_size) {
        return HPDF_PAGE_SIZE_US4x6;
    } else if ("us4x8" == page_size) {
        return HPDF_PAGE_SIZE_US4x8;
    } else if ("us5x7" == page_size) {
        return HPDF_PAGE_SIZE_US5x7;
    } else if ("comm10" == page_size) {
        return HPDF_PAGE_SIZE_COMM10;
    }
    return HPDF_PAGE_SIZE_EOF;
}


