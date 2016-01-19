/**
 * @file   MiscUtils.hpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Thu Sep  3 21:13:00 2015
 * 
 * @brief   Misc Utils 
 *  Copyright
 * 
 */



#ifndef MISCUTILS_H
#define MISCUTILS_H

#include <string>



class MiscUtils {
  public:
    // some misc utils here
    static inline std::string Base64_encode(unsigned char* const bytes_to_encode, unsigned int in_len);

    static inline std::string Base64_decode(std::string const& encoded_string);
};


#endif /* MISCUTILS_H */
