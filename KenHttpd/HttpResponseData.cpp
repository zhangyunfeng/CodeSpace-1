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
#include "HttpResponseData.hpp"


HttpResponseData::HttpResponseData() {
    
}

HttpResponseData::HttpResponseData(const std::string& responseData) {
    this->m_responseData = responseData;
}

HttpResponseData::~HttpResponseData() {
    
}


void HttpResponseData::SetResponseData(const std::string& responseData) {
    this->m_responseData = responseData;
    this->m_responseBody = "";
    this->m_responseHeader = "";
}

const std::string HttpResponseData::GetResponseHeader() {
    if (m_responseHeader.empty()) {
        m_responseHeader = parseHeader();
    }
    return m_responseHeader;
}


const std::string HttpResponseData::GetResponseBody() {
    if (m_responseBody.empty()) {
        m_responseBody = parseBody();
    }
    return m_responseBody;
}

const std::string HttpResponseData::parseHeader() const{
    std::string header("");
    if (m_responseData.empty()) {
        return header;
    }
    int postion = m_responseData.find("\r\n\r\n");
    header = m_responseData.substr(0, postion);
    return header;
}

const std::string HttpResponseData::parseBody() const {
    std::string body("");
    if (m_responseData.empty()) {
        return body;
    }

    int first_position = m_responseData.find("\r\n\r\n");
    std::string bodypart = m_responseData.substr(first_position + 4);  // length of "\r\n\r\n" is 4
    // std::cout << "bodypart: \n" << bodypart << std::endl;              
    // int last_position = bodypart.find("\r\n");
    // int len = last_position;

    // body = bodypart.substr(0, len);
    body = bodypart;
    
    return body;
}

