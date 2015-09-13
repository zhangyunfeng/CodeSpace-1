
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

    template<typename T>
    static int String2Int(const T& number);
    
    static short GetR(const std::string& rgb);
    static short GetG(const std::string& rgb);
    static short GetB(const std::string& rgb);
};


#endif /* MISCUTILS_H */
