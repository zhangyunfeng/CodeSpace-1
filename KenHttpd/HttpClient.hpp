

#ifndef HTTP_CLIENT_HPP_
#define HTTP_CLIENT_HPP_

#include <iostream>
#include <memory>
#include <string>
#include <map>
#include "Url.hpp"

enum class HttpMethod {
    GET, POST,
};

extern const std::string ConvertHttpMethodToStr(HttpMethod method) ;

class HttpClient {
  public:
    HttpClient() = delete;
    explicit HttpClient(const std::string& url);
    HttpClient(const std::string& url, const std::string& postbody);

    const std::string BlockingRequestHttp() const;

    // for chaining call
    HttpClient& SetHttpMethod(HttpMethod method);
    HttpClient& SetUrl(const std::string& url);
    HttpClient& SetHttpBody(const std::string& body);
    HttpClient& SetHeadMap(const std::map<std::string, std::string> headers);
    HttpClient& AddHeaderPair(const std::string& key, const std::string& value);
    
    std::string MakeHttpHead() const;
    const std::string& GetBody() const;
    const std::string GetSendData() const;

  private:
    void defaultMapHead();

  private:
    Url m_url;
    std::string m_postbody;
    HttpMethod m_method;
    std::map<std::string, std::string> m_mapHead;
};

#endif

