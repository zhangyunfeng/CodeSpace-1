//Note: 不要过度包含头文件， 系统文件在前，自定义头文件在后
//尽量以Google的code style
#include <sstream>
#include <iostream>
#include "StringUtils.h"

char* Ken_i2a(unsigned i, char* a, unsigned r)
{
  if (i/r > 0) a = Ken_i2a(i/r, a, r);
  *a = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[i%r];
  return a + 1;
}

//FIXME: first version, not good ; please make it better later.
//@strSrc  the input string to split
//@chSep  the sep char
TStringVec Ken_SplitString(std::string& strSrc, const char chSep)
{
	TStringVec result;
	std::size_t len = strSrc.length();

	int pre_position = 0;
	while (pre_position < len) {
		if (strSrc.at(pre_position) == chSep) {
			pre_position++;
		} else {
			break;
		} // if .. else ..
	}	  // while ..

	if (pre_position >= len) return result;
	int last_position = pre_position;
	while (last_position < len) {
		if (strSrc.at(last_position) != chSep && last_position != len-1) {
			last_position++;
		} else {
			int last_position_tmp = \
				(last_position == len-1 && strSrc.at(last_position) != chSep) ? last_position + 1 : last_position;
			result.push_back(strSrc.substr(pre_position, last_position_tmp - pre_position));
			if (last_position >= len - 1) break; // it's time to exit'
			while (last_position < len) {
				if (strSrc.at(last_position) == chSep) {
					last_position++;
				} else {
					break;
				} // if .. else.. 
			}	  // while ..
			pre_position = last_position;
			
		}		  // if .. else ..
	}			  // while ..	
}


std::wstring A2W(std::string& astr_)
{
	std::wstring ws(astr_.begin(), astr_.end());
	return ws;
}

std::string W2A(std::wstring& wstr_)
{
	std::string as(wstr_.begin(), wstr_.end());
	return as;
	
}


std::string Ken_Int2String(const int num)
{
	std::string str;
	std::stringstream ss;
	ss.clear();
	ss << num;
	ss >> str;
	return str;
}

std::string Ken_FormatInt2Thousands(const int num)
{
	std::string rst("");
	rst = Ken_Int2String(num);
	std::cout << rst << std::endl;
	int pos = rst.length() - 1 - 2;
	while (pos > 0)	{
		if (rst[pos - 1] != '-' && rst[pos - 1] != '+')	{
			rst.insert(pos, ",");
		}
		pos -= 3;
	}
	//if (num < 0 && rst[0] != '-') rst.insert(0, "-");
	
	return rst;
}

std::string Ken_SplitFileName(const std::string& src)
{
	if (src.empty()) return "";
	unsigned pos = src.find_last_of("/\\"); 
	std::string filename = src.substr(pos+1);
	return filename;
}