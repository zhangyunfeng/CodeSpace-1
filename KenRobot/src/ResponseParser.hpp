#ifndef RESPONSEPARSER_H
#define RESPONSEPARSER_H

#include <string>
#include "../rapidjson/document.h"
#include "../rapidjson/stringbuffer.h"

class ResponseParser
{
  public:
    const std::string GetText(const std::string& data);
    const int GetTulingCode(const std::string& data);
    const std::string GetUrl(const std::string& data);
    
    static ResponseParser& GetInstance() {
        static ResponseParser instance;
        return instance;
    }

  private:
    ResponseParser() { }
    const std::string toJsonStr(const std::string& data);
  private:
    rapidjson::Document m_document;
};

#endif /* RESPONSEPARSER_H */
