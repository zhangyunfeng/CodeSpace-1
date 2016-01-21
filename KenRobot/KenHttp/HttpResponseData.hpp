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




class HttpResponseData
{
  public:
    HttpResponseData() = delete;
    HttpResponseData(const std::string& responseData);
    ~HttpResponseData();

    const std::string ToString() const;

    const std::string GetHttpProtocol() { return m_responseData.protocol; } 
    int GetHttpCode() const { return m_responseData.code; }
    const std::string GetHttpServer() const { return m_responseData.server; }
    const std::string GetHttpDate() const { return m_responseData.date; }
    const std::string GetHttpContentType() const { return m_responseData.content_type; }
    int GetHttpContentLength() const { return m_responseData.content_length; }
    const std::string GetHttpCharset() const { return m_responseData.charset; }
    const std::string GetHttpConnection() const { return m_responseData.connection; }

    const std::string GetResponseBody() const { return m_responseData.body; }
    
  private:
    struct stResponse {
        std::string protocol; // HTTP/1.1
        int code; // 200, 400, ...
        std::string server;
        std::string date;
        std::string content_type;
        int content_length;
        std::string charset;
        std::string connection;
        std::string body;

        stResponse() :
                protocol(""),
                code(-1),
                server(""),
                date(""),
                content_type(""),
                content_length(-1),
                charset(""),
                connection(""),
                body("") { }
    };

  private:
    void parseHeader(const std::string& data) ;
    void parseBody(const std::string& data) ;
    
  private:
    stResponse m_responseData;
};


#endif /* HTTPRESPONSEDATA_H */

