/**
 * @file   CommonUtils.h
 * @author Ken <ken@ken-Ubuntu>
 * @date   Mon Dec  7 22:44:31 2015
 * 
 * @brief  
 * 
 * 
 */


#ifndef COMMONUTILS_H
#define COMMONUTILS_H

#include "GoBangBoard.hpp"

#include <string>

class CommonUtils {
public:
    static void SaveBoard(const GoBangBoard& board, const std::string& path);

    static GoBangBoard LoadBoard(const std::string& boardFile);
};


#endif /* COMMONUTILS_H */

