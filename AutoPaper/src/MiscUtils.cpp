/**
 ** Ken
 ** MiscUtils.cpp
 **/

#include <sstream>
#include <fstream>
#include <iostream>
#include "MiscUtils.hpp"

MiscUtils::MiscUtils() {
    
}

MiscUtils::~MiscUtils() {

}

int MiscUtils::String2Int(const std::string& number) {
    std::stringstream ss;
    ss << number;
    int int_number = 0;
    ss >> int_number;
    return int_number;
}

short MiscUtils::GetR(const std::string& rgb) {
    std::string r(rgb.begin(), rgb.begin()+2);
    int intR = 0;
    sscanf(r.c_str(), "%x", &intR);
    std::cout << "GetR: " << intR << std::endl;
    return intR;
}

short MiscUtils::GetG(const std::string& rgb) {
    std::string g(rgb.begin()+2, rgb.begin()+4);
    int intG = 0;
    sscanf(g.c_str(), "%x", &intG);
    std::cout << "GetG: " << intG << std::endl;
    return intG;
}

short MiscUtils::GetB(const std::string& rgb) {
    std::string b(rgb.begin()+4, rgb.end());
    int intB = 0;
    sscanf(b.c_str(), "%x", &intB);
    std::cout << "GetB: " << intB << std::endl;
    return intB;
}


const std::string MiscUtils::GetFileText(const std::string& filename) {
    if (filename.empty()) {
        return "";
    }

    std::ifstream t(filename);
    std::stringstream ss;
    ss << t.rdbuf();
    return ss.str();
}
