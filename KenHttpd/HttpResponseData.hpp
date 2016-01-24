/**
 * @file   HttpResponseData.hpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Sun Sep  6 23:59:50 2015
 * 
 * @brief  
 * 
 * 
 */


#ifndef HTTPRESPONSEDATA_H
#define HTTPRESPONSEDATA_H

#include <string>
#include <map>
#include "MiscUtils.hpp"

class HttpResponseData
{
  public:
    HttpResponseData() = delete;
    HttpResponseData(const std::string& responseData);
    ~HttpResponseData();

    const std::string ToString() const;

    const std::string GetHttpProtocol() { return m_responseData.protocol; } 
    int GetHttpCode() const { return m_responseData.code; }
    const std::string GetHttpServer() const {
        std::string server("");
        int code = getHeaderValue("Server", server);
        if (code == 0) {
            return server;
        }
        return "";
    }
     
    const std::string GetHttpDate() const {
        std::string date("");
        int code = getHeaderValue("Date", date);
        if (code == 0) {
            return date;
        }
        return "";
    }
    
    const std::string GetHttpContentType() const {
        std::string content_type("");
        int code = getHeaderValue("Content-Type", content_type);
        if (code == 0) {
            return content_type;
        }
        return "";
    }
    
    int GetHttpContentLength() const {
        std::string content_length("");
        int code = getHeaderValue("Content-Length", content_length);
        if (code == 0) {
            return std::stoi(content_length);
        }
        return -1;
    }
    
    const std::string GetHttpConnection() const {
        std::string connection("");
        int code = getHeaderValue("Connection", connection);
        if (code == 0) {
            return connection;
        }
        return "";
    }

    const std::string GetResponseBody() const { return m_responseData.body; }
    
  private:
    int getHeaderValue(const std::string& key, std::string& value) const {
        for (auto& m : m_responseData.mapHeader) {
            if (MiscUtils::IEquals(m.first, key)) {
                value = m.second;
                return 0;
            }
        }
        return -1;
    }
    
    struct stResponse {
        std::string protocol; // HTTP/1.1
        int code; // 200, 400, ...
        std::map<std::string, std::string> mapHeader;        
        std::string body;

        stResponse() :
                protocol(""),
                code(-1),
                body("") { }
    };

  private:
    void parseHeader(const std::string& data) ;
    void parseBody(const std::string& data) ;
    
  private:
    stResponse m_responseData;
};


#endif /* HTTPRESPONSEDATA_H */

