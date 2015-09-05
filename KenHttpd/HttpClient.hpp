

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
    
    virtual void OnReceive(int id, const std::string& data)
    {
        std::cout << "please implement " << std::endl;
    }
};


class HttpClient {
  public:
    HttpClient() = delete;
    explicit HttpClient(const std::string& url);
    void ansyRequestHttp(int id, const std::string& url);

    const std::string blockingRequestHttp(const std::string& url);

    void RegistHttpReceiver(HttpReceiver* httpReceiver);


    static std::string MakeHttpHead(const Url& url);

  private:
    void requestHttp(int id, const Url& url);

  private:
    Url m_url;
    HttpReceiver* m_receiver;
};

#endif

