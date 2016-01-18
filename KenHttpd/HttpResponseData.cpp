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

static std::string int2string(const int num) {
    std::stringstream ss;
    ss.clear();
    ss << num;
    return ss.str();
}

static std::string getPhase(const std::string& src, size_t position, char endchar) {
    std::string ret("");
    while (position < src.length() && src.at(position) != endchar) {
        ret += src.at(position++);
    }
    return ret;
}


HttpResponseData::HttpResponseData(const std::string& responseData) {
    parseHeader(responseData);
    parseBody(responseData);
}

HttpResponseData::~HttpResponseData() {
    
}


const std::string HttpResponseData::ToString() const {
    std::string str = "PROTOCOL: " + m_responseData.protocol + "\n"
            + "CODE: " + int2string(m_responseData.code) + "\n"
              + "SERVER: " + m_responseData.server + "\n"
              + "CONTENT_TYPE: " + m_responseData.content_type + "\n"
              + "CHARSET: " + m_responseData.charset + "\n"
            + "CONTENT_LENGTH: " + int2string(m_responseData.content_length) + "\n"
              + "CONNECTION: " + m_responseData.connection + "\n"
              + "BODY: " + m_responseData.body + "\n";
    return str;
}

void HttpResponseData::parseHeader(const std::string& data) {
    std::string header("");
    size_t position = data.find("\r\n\r\n");
    header = data.substr(0, position);
    
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

    // server: 
    position = header.find("Server: ");
    if (position != std::string::npos) {
        size_t index = position + 8;
        m_responseData.server = getPhase(header, index, '\r');
    }

    // Date: 
    position = header.find("Date: "); // 6
    if (position != std::string::npos) {
        size_t index = position + 6;
        m_responseData.date = getPhase(header, index, '\r');
    }

    // Content-Type: 
    position = header.find("Content-Type: "); // 14
    if (position != std::string::npos) {
        size_t index = position + 14;
        m_responseData.content_type = getPhase(header, index, ';');
    }
    
    // charset
    position = header.find("charset=");
    if (position != std::string::npos) {
        size_t index = position + 8;
        m_responseData.charset = getPhase(header, index, '\r');
    }
    
    // Content-Length: 
    position = header.find("Content-Length: "); // 16
    if (position != std::string::npos) {
        size_t index = position + 16;
        m_responseData.content_length = std::stoi(getPhase(header, index, '\r'));
    }
    
    //Connection: 
    position = header.find("Connection: "); // 12
    if (position != std::string::npos) {
        size_t index = position + 12;
        m_responseData.connection = getPhase(header, index, '\r');
    }
}

void HttpResponseData::parseBody(const std::string& data) {
    size_t first_position = data.find("\r\n\r\n");
    if (first_position != std::string::npos) {
        m_responseData.body = data.substr(first_position + 4);  // length of "\r\n\r\n" is 4        
    }
}

