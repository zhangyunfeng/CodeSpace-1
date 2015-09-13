/**
 ** Ken
 ** MiscUtils.cpp
 **/

#include <sstream>
#include "MiscUtils.hpp"

MiscUtils::MiscUtils() {
    
}

MiscUtils::~MiscUtils() {

}

template<typename T>
int MiscUtils::String2Int(const T& number) {
    std::stringstream ss;
    ss << number;
    int int_number = 0;
    ss >> int_number;
    return int_number;
}

short MiscUtils::GetR(const std::string& rgb) {
    std::string r(rgb.begin(), rgb.begin()+2);
    return String2Int(r);
}

short MiscUtils::GetG(const std::string& rgb) {
    std::string r(rgb.begin()+2, rgb.begin()+4);
    return String2Int(r);
}

short MiscUtils::GetB(const std::string& rgb) {
    std::string b(rgb.begin()+4, rgb.end());
    return String2Int(b);
}
