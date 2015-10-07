/**
 * @file   Constants.hpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Tue Sep 15 23:40:16 2015
 * 
 * @brief  xml中属性的特定值
 * 
 * 
 */

#include <string>

// PDF

namespace Constants {

class CompressMode
{
  public:
    static const std::string NONE;
    static const std::string TEXT;
    static const std::string IMAGE;
    static const std::string METADATA;
    static const std::string ALL ;
};



class PageMode
{
  public:
    static const std::string NONE;
    static const std::string OUTLINE;
    static const std::string THUMBS;
    static const std::string FULL_SCREEN;
};

};
