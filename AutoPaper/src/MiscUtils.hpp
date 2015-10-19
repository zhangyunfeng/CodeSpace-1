
#ifndef MISCUTILS_H
#define MISCUTILS_H


/** 
 * MiscUtils is a util class contained many common tools
 * 
 * static methods
 */

#include <string>

class MiscUtils
{
  public:
    MiscUtils();
    ~MiscUtils();

    static int String2Int(const std::string& number);

    static short GetR(const std::string& rgb);
    static short GetG(const std::string& rgb);
    static short GetB(const std::string& rgb);

    static const std::string GetFileText(const std::string& filename);
};


#endif /* MISCUTILS_H */
