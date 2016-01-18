/**
 * Copyright
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
#include "DNSUtil.hpp"

HttpClient::HttpClient(const std::string& url):
    m_url(url) {
}


// void HttpClient::requestHttp(int id, const Url& url) {
//     std::string ip(DNSUtil::GetIPByHostName(url.getHost()).front());
//     std::unique_ptr<SocketParam> sp(new SocketParam(ip,
//                                                     std::stoi(url.getPort()),
//                                                     Domain::INET,
//                                                     Type::STREAM,
//                                                     Protocol::DEFAULT));

//     ClientSocket cs(sp);
//     cs.Connect();
//     std::string httpHead("");
//     httpHead = HttpClient::MakeHttpHead(url);
//     cs.Send(httpHead);
//     while (true) {
//         std::string data = cs.Receive();
//     }
// }

// void HttpClient::ansyRequestHttp(int id, const std::string& url) {
//     m_url.setUrl(url);
//     std::thread t(&HttpClient::requestHttp, this, id,  m_url);
//     t.detach();
// }


const std::string HttpClient::blockingRequestHttp() {
    std::string ip(DNSUtil::GetIPByHostName(m_url.getHost()).front());
    std::unique_ptr<SocketParam> sp(new SocketParam(ip,
                                                    std::stoi(m_url.getPort()),
                                                    Domain::INET,
                                                    Type::STREAM,
                                                    Protocol::DEFAULT));
    ClientSocket cs(sp);
    cs.Connect();
    std::string head = HttpClient::MakeHttpHead(m_url);
    cs.Send(head);
    std::string data = cs.Receive();

    return data;
}

std::string HttpClient::MakeHttpHead(const Url& url) {
    std::string head("");
    if (true) {
        // GET /bmgeorg/http/blob/master/server.c HTTP/1.1
        head += "GET ";
        head += url.getPath();
        head += " HTTP/1.1";
        head += "\r\n";

        // Host: github.com
        head += "Host: ";
        std::string ip = DNSUtil::GetIPByHostName(url.getHost()).front();
        head += ip;
        head += "\r\n";

        // Connection: keep-alive
        head += "Connection: keep-alive";
        head += "\r\n";

        head += "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8";
        head += "\r\n";

        head += "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2272.118 Safari/537.36";
        head += "\r\n";

        head += "\r\n";
    }

    return head;
}

