/**
 * @file   HttpClient.cpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Mon Aug 17 22:25:56 2015
 * 
 * @brief  
 * 
 * 
 */
#include <iostream>
#include <string>
#include <thread>

#include "HttpClient.hpp"
#include "ClientSocket.hpp"
#include "ThreadPool.hpp"

HttpClient::HttpClient(const std::string& url): m_url(url), m_receiver(nullptr)
{
    
}

void HttpClient::requestHttp(const Url& url, const std::string& httpContent)
{
    std::unique_ptr<SocketParam> sp(new SocketParam(url.getHost(), std::stoi(url.getPort()),
                                                    Domain::INET, Type::STREAM, Protocol::DEFAULT ));

    ClientSocket cs(sp);
    cs.Connect();
    cs.Send(httpContent);
    while (true) {
        std::string data = cs.Receive();
        if (m_receiver != nullptr) {
            m_receiver->OnReceive(data);
            return;
        }
    }        

}

void HttpClient::RequestHttp(const std::string& url)
{
    m_url.setUrl(url);
    std::string httpHead("");
    httpHead = this->MakeHttpHead(m_url);
    std::thread t(&HttpClient::requestHttp, this, m_url, httpHead);
    t.detach();

}


const std::string HttpClient::blockingRequestHttp(const std::string& url)
{
    Url url_(url);
    std::unique_ptr<SocketParam> sp(new SocketParam(url_.getHost(), std::stoi(url_.getPort()),
                                                    Domain::INET, Type::STREAM, Protocol::DEFAULT));
    ClientSocket cs(sp);
    cs.Connect();
    std::string head = this->MakeHttpHead(url_);
    cs.Send(head);
    std::string data = cs.Receive();
    return data;
}

std::string HttpClient::MakeHttpHead(const Url& url)
{
    std::string head("");
    if (true) {
        // GET /bmgeorg/http/blob/master/server.c HTTP/1.1
        head += "GET ";
        head += url.getPath();
        head += " HTTP/1.1";
        head += "\r\n";

        //Host: github.com
        head += "Host: ";
        head += url.getHost();
        head += "\r\n";

        //Connection: keep-alive
        head += "Connection: keep-alive";
        head += "\r\n";
        
        //Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
        head += "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8";
        head += "\r\n";
        
        //User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2272.118 Safari/537.36
        head += "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2272.118 Safari/537.36";
        head += "\r\n";
    }

    return head;
}
