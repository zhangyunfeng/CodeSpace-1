// Copyright Ken

/**
 * @file   ResponseParser.cpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Thu Feb  4 17:02:55 2016
 * 
 * @brief  
 * 
 * 
 */
#include <iostream>
#include <exception>
#include "ResponseParser.hpp"


/** 
 * 
 * 
 * @param data 
 * 
 * @return 
 */
const std::string ResponseParser::toJsonStr(const std::string& data) {
    std::string json("") ;
    size_t startPosition = 0;
    while (data.at(startPosition) != '{') {
        startPosition++;
    }
    // now startPosition point to '{'
    size_t endPosition = data.length() - 1;
    while (data.at(endPosition) != '}' && endPosition > startPosition) {
        endPosition--;
    }
    json = data.substr(startPosition, endPosition-startPosition+1);
    return json;
} 

/** 
 * 
 * 
 * @param data 
 * 
 * @return 
 */
const std::string ResponseParser::GetText(const std::string& data) {
    std::string body = toJsonStr(data);
    if (not body.empty()) {
        if (m_document.Parse<0>(body.c_str()).HasParseError()) {
            std::cerr << "Rapidjson parses body failed: => " << body << std::endl;
        }
        if (m_document.HasMember("text")) {
            body = m_document["text"].GetString();
        }
    }

    return body;
}

/** 
 * 
 * 
 * @param data 
 * 
 * @return 
 */
const std::string ResponseParser::GetUrl(const std::string& data) {
    std::string json = toJsonStr(data);
    std::string url("");
    if (not json.empty()) {
        if (m_document.Parse<0>(json.c_str()).HasParseError()) {
            std::cerr << "RapidJson parses json failed: => " << json << std::endl;
        }
        if (m_document.HasMember("url")) {
            url = m_document["url"].GetString();
        }
    }
    return url;
}

/** 
 * 
 * 
 * @param data 
 * 
 * @return 
 */
const int ResponseParser::GetTulingCode(const std::string& data) {
    std::string json = toJsonStr(data);
    int code = -1;
    if (not json.empty()) {
        if (m_document.Parse<0>(json.c_str()).HasParseError()) {
            std::cerr << "Rapidjson parses body failed." << std::endl;
        }
        if (m_document.HasMember("code")) {
            code = m_document["code"].GetInt();
        }
    }

    return code;
}




