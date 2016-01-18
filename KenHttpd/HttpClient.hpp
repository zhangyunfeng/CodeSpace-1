

#ifndef HTTP_CLIENT_HPP_
#define HTTP_CLIENT_HPP_

#include <iostream>
#include <memory>
#include <string>
#include "Url.hpp"


class HttpClient {
  public:
    HttpClient() = delete;
    explicit HttpClient(const std::string& url);

    const std::string blockingRequestHttp();

    static std::string MakeHttpHead(const Url& url);

  private:
    Url m_url;
};

#endif

