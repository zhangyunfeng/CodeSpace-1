

#ifndef HTTP_CLIENT_HPP_
#define HTTP_CLIENT_HPP_

#include <iostream>
#include <memory>
#include <string>
#include "Url.hpp"


class HttpReceiver
{
  public:
    HttpReceiver()
    {
        
    }
    virtual ~HttpReceiver()
    {
        
    }
    
    virtual void OnReceive(const std::string& data)
    {
        std::cout << "please implement " << std::endl;
    }
};

class HttpClient
{
  public:
    HttpClient() = delete;
    HttpClient(const std::string& url);
    void RequestHttp(const std::string& url);

    const std::string blockingRequestHttp(const std::string& url);

    void RegistHttpReceiver(const std::unique_ptr<HttpReceiver> httpReceiver);


    std::string MakeHttpHead(const Url& url);

  private:
    void requestHttp(const Url& url, const std::string& httpContent);
    
  private:
    Url m_url;
    std::unique_ptr<HttpReceiver> m_receiver;
};

#endif 
