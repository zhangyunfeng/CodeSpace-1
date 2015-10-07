/**
 * @file   PdfCommonData.hpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Wed Sep  9 23:52:17 2015
 * 
 * @brief  pdf properties
 * 
 * 
 */


#ifndef PDFCOMMONDATA_H
#define PDFCOMMONDATA_H

#include <string>
#include <vector>

#define STR_SETTER(proper, member) \
    void Set#proper (const std::string& newVal) {       \
        member = newVal; \
    }

#define STR_GETTER(proper, member)               \
    std::string Get#proper (void) {\
        return member;             \
    }


/*
 *Pdf document properties
 */ 

struct PdfProperties {
    std::string docname;       // pdf 文档名字
    std::string page_layout;  // 页面的布局类型
    std::string fontname;  // 文档字体（可以在单个page中设置）
    std::string compress_mode; // 文档压缩模式
    std::string page_mode; // 页面的模式
    std::string owner; // 文档所有者， 设置密码使用
    std::string password; // 文档密码

    // Note: 因为参数较多，所以索性不提供所有参数的构造函数
    PdfProperties() : page_layout(""), fontname(""), compress_mode(""),
                      page_mode(""), owner(""), password(""), docname("untitle") {
        
    }

    static const std::string TAG;
    static const std::string ATTR_DOCNAME;
    static const std::string ATTR_PAGELAYOUT;
    static const std::string ATTR_FONT;
    static const std::string ATTR_COMPRESSMODE;
    static const std::string ATTR_PAGEMODE;
    static const std::string ATTR_OWNER;
    static const std::string ATTR_PASSWD;
};




/**
 *Draw line properties
 *
 */
struct LineProperties {
    std::string lable;
    std::string startX;
    std::string startY;
    std::string endX;
    std::string endY;
    std::string lineWidth;
    std::string rgb;
    std::string lineType;  // 圆角  方角直线
    
    LineProperties() : lable(""), startX(""), startY(""), endX(""), endY(""),
                       lineWidth("1"), rgb("000000"), lineType("FILL") {
        
    }

    static const std::string TAG;
    static const std::string ATTR_LABLE;
    static const std::string ATTR_X0;
    static const std::string ATTR_Y0;
    static const std::string ATTR_X1;
    static const std::string ATTR_Y1;
    static const std::string ATTR_LINEWIDTH;
    static const std::string ATTR_RGB;
    static const std::string ATTR_LINETYPE;
};


/**
 *
 *text properties
 */
struct TextProperties {
    std::string font;
    std::string size;
    std::string rgb;
    std::string text;
    std::string textX;
    std::string textY;
    std::string includeDoc;
    
    TextProperties() : font(""), size("12"), rgb("000000"),
                       text(""), textX(""), textY(""), includeDoc("") {
        
    }

    static const std::string TAG;
    static const std::string ATTR_FONT;
    static const std::string ATTR_SIZE;
    static const std::string ATTR_RGB;
    static const std::string ATTR_INCLUDE;
    static const std::string ATTR_TEXTX;
    static const std::string ATTR_TEXTY;
    static const std::string BODY_TEXT;
};
        

struct RectProperties {
    std::string lineWidth;
    std::string rgb;
    std::string rectStyle;  // stroke  or fill
    std::string x;          // 矩形的左上点x坐标
    std::string y;          // 矩形的左上点y坐标
    std::string width;      // 矩形的宽
    std::string height;     // 矩形的高

    static const std::string TAG;
    static const std::string ATTR_LINEWIDTH;
    static const std::string ATTR_RGB;
    static const std::string ATTR_STYLE;
    static const std::string ATTR_X;
    static const std::string ATTR_Y;
    static const std::string ATTR_WIDTH;
    static const std::string ATTR_HEIGHT;
};


struct ImageProperties {
    std::string src;
    std::string x;
    std::string y;
    std::string width;  // 图像绘制时的宽
    std::string height; // 图像绘制时的高

    static const std::string TAG;
    static const std::string ATTR_SRC;
    static const std::string ATTR_X;
    static const std::string ATTR_Y;
    static const std::string ATTR_WIDTH;
    static const std::string ATTR_HEIGHT;
};


/**
 *
 *page properties
 *
 */
struct PageProperties {  //
    int page_id = 0;     // page id
    std::string width;           // page width 自定义page宽
    std::string height;          // page height 自定义page高
    std::string page_size;       // B5 B4 A3 等等
    std::string page_rotate;     // 页面旋转角度
    std::string annot;           // 注释
    std::string pageSlideShowType;  // 幻灯片播放模式
    std::string fontname;   // 字体

    std::vector<LineProperties> linesVec;  // lines
    std::vector<TextProperties> textVec;   // text
    std::vector<RectProperties> rectVec;   // rects
    std::vector<ImageProperties> imagesVec;  // images

    PageProperties() : width(""), height(""), page_rotate(""), annot(""),
                       pageSlideShowType(""), fontname("") {
    }

    void SetPageId(int id) {
        this->page_id = id;
    }

    int GetPageId(void) {
        return page_id;
    }

    static const std::string TAG;
    static const std::string ATTR_WIDTH;
    static const std::string ATTR_HEIGHT;
    static const std::string ATTR_PAGESIZE;
    static const std::string ATTR_PAGEROTATE;
    static const std::string ATTR_ANNOT;
    static const std::string ATTR_SLIDESHOWTYPE;
    static const std::string ATTR_FONT;
};




#endif /* PDFCOMMONDATA_H */
