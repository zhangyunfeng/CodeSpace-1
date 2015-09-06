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
    HttpResponseData();
    HttpResponseData(const std::string& responseData);
    ~HttpResponseData();

    void SetResponseData(const std::string& responseData);
    const std::string GetResponseHeader();
    const std::string GetResponseBody();

  private:
    const std::string parseHeader() const;
    const std::string parseBody() const;
    
  private:
    std::string m_responseData;
    std::string m_responseHeader;
    std::string m_responseBody;
};


#endif /* HTTPRESPONSEDATA_H */

