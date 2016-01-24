/**
 * @file   HttpResponseData.cpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Mon Sep  7 00:05:54 2015
 * 
 * @brief  
 * 
 * 
 */
#include <iostream>
#include <string>
#include <sstream>
#include "HttpResponseData.hpp"
#include "MiscUtils.hpp"


// Warning: defined but not used
// static std::string int2string(const int num) {
//     std::stringstream ss;
//     ss.clear();
//     ss << num;
//     return ss.str();
// }

// Warning: defined but not used
// static std::string getPhase(const std::string& src, size_t position, char endchar) {
//     std::string ret("");
//     while (position < src.length() && src.at(position) != endchar) {
//         ret += src.at(position++);
//     }
//     return ret;
// }


HttpResponseData::HttpResponseData(const std::string& responseData) {
    parseHeader(responseData);
    parseBody(responseData);
}

HttpResponseData::~HttpResponseData() {
    
}


const std::string HttpResponseData::ToString() const {
    std::string str("");
    for (auto& m : m_responseData.mapHeader) {
        str += m.first;
        str += "  <===>  ";
        str += m.second;
        str += "\n";
    }
    return str;
}

void HttpResponseData::parseHeader(const std::string& data) {

    size_t position = data.find("\r\n\r\n");
    std::string header = data.substr(0, position);
    
    // get protocol
    position = header.find(" ");
    if (position != std::string::npos) {
        std::string protocol = header.substr(0, position);
        m_responseData.protocol = protocol;
    }
    
    // code
    std::string tmp = header.substr(position+1);
    position = tmp.find(" ");
    if (position != std::string::npos) {
        m_responseData.code = std::stoi(tmp.substr(0, position));
    }
    
    m_responseData.mapHeader = MiscUtils::ParseHttpHeader(header);
}

void HttpResponseData::parseBody(const std::string& data) {
    size_t first_position = data.find("\r\n\r\n");
    if (first_position != std::string::npos) {
        m_responseData.body = data.substr(first_position + 4);  // length of "\r\n\r\n" is 4        
    }
}

