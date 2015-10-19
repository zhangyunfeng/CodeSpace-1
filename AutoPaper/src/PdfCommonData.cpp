/**
 * @file   PdfCommonData.cpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Wed Sep  9 23:53:28 2015
 *
 * @brief  Implement of PdfCommonData.hpp
 *
 *
 */

#include "PdfCommonData.hpp"




const std::string PdfProperties::TAG = "PDF";
const std::string PdfProperties::ATTR_PAGELAYOUT = "page_layout";
const std::string PdfProperties::ATTR_FONT = "font";
const std::string PdfProperties::ATTR_COMPRESSMODE = "compress_mode";
const std::string PdfProperties::ATTR_PAGEMODE = "page_mode";
const std::string PdfProperties::ATTR_OWNER = "owner";
const std::string PdfProperties::ATTR_PASSWD = "password";
const std::string PdfProperties::ATTR_DOCNAME = "docname";





const std::string LineProperties::TAG = "line";
const std::string LineProperties::ATTR_LABLE = "lable";
const std::string LineProperties::ATTR_X0 = "x0";
const std::string LineProperties::ATTR_Y0 = "y0";
const std::string LineProperties::ATTR_X1 = "x1";
const std::string LineProperties::ATTR_Y1 = "y1";
const std::string LineProperties::ATTR_LINEWIDTH = "line_width";
const std::string LineProperties::ATTR_RGB = "rgb";
const std::string LineProperties::ATTR_LINETYPE = "line_type";



const std::string TextProperties::TAG = "text";
const std::string TextProperties::ATTR_FONT = "font";
const std::string TextProperties::ATTR_SIZE = "size";
const std::string TextProperties::ATTR_RGB = "rgb";
const std::string TextProperties::ATTR_INCLUDE = "include";
const std::string TextProperties::ATTR_TEXTX = "x";
const std::string TextProperties::ATTR_TEXTY = "y";
const std::string TextProperties::ATTR_TEXTW = "width";
const std::string TextProperties::ATTR_TEXTH = "height";
const std::string TextProperties::BODY_TEXT = "content";



const std::string RectProperties::TAG = "rect";
const std::string RectProperties::ATTR_LINEWIDTH = "line_width";
const std::string RectProperties::ATTR_RGB = "rgb";
const std::string RectProperties::ATTR_STYLE = "style";
const std::string RectProperties::ATTR_X = "x";
const std::string RectProperties::ATTR_Y = "y";
const std::string RectProperties::ATTR_WIDTH = "width";
const std::string RectProperties::ATTR_HEIGHT = "height";




const std::string ImageProperties::TAG = "image";
const std::string ImageProperties::ATTR_SRC = "src";
const std::string ImageProperties::ATTR_X = "x";
const std::string ImageProperties::ATTR_Y = "y";
const std::string ImageProperties::ATTR_WIDTH = "width";
const std::string ImageProperties::ATTR_HEIGHT = "height";




const std::string PageProperties::TAG = "page";
const std::string PageProperties::ATTR_WIDTH = "width";
const std::string PageProperties::ATTR_HEIGHT = "height";
const std::string PageProperties::ATTR_PAGESIZE = "size";
const std::string PageProperties::ATTR_PAGEROTATE = "rotate";
const std::string PageProperties::ATTR_ANNOT = "annot";
const std::string PageProperties::ATTR_SLIDESHOWTYPE = "slide_show_type";
const std::string PageProperties::ATTR_FONT = "font";
