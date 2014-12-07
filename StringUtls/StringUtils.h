#ifndef STRINGUTILS_HPP
#define STRINGUTILS_HPP


#include <string>
#include <vector>

//将i转换成r进制，并以字符串的形式存储在a中
// example 见 MainTest.cpp
//@i :输入数字（要转换的数字）
//@a :结果
//@r :要转的进制
extern char* Ken_i2a(unsigned i, char* a, unsigned r);

typedef std::vector<std::string> TStringVec;
extern TStringVec Ken_SplitString(std::string& strSrc, const char chSep);

//convert ansi string to wide string
extern std::wstring A2W(std::string& astr_);
//convert wide string to ansi string
extern std::string W2A(std::wstring wstr_);


#endif /* end of include guard: STRINGUTILS_HPP */
