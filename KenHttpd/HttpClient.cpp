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
#include <exception>
#include <stdexcept>
#include <thread>
#include "HttpClient.hpp"
#include "ClientSocket.hpp"
#include "ThreadPool.hpp"
#include "DNSUtil.hpp"

const std::string ConvertHttpMethodToStr(HttpMethod method) {
    if (method == HttpMethod::GET) {
        return "GET";
    }
    if (method == HttpMethod::POST) {
        return "POST";
    }
    throw std::invalid_argument("Unknow http method or unimplemented http method");
}

HttpClient::HttpClient(const std::string& url):
        m_url(url), m_postbody(""), m_method(HttpMethod::GET) {
    defaultMapHead();
}

HttpClient::HttpClient(const std::string& url, const std::string& postbody) :
        m_url(url), m_postbody(postbody), m_method(HttpMethod::GET) {
    defaultMapHead();
}

void HttpClient::defaultMapHead() {
    m_mapHead.emplace("Host", m_url.getHost());
    m_mapHead.emplace("Connection", "keep-alive");
    m_mapHead.emplace("Accept", "*/*");
    m_mapHead.emplace("User-Agent", "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2272.118 Safari/537.36");
}

HttpClient& HttpClient::SetHttpMethod(HttpMethod method) {
    this->m_method = method;
    return *this;
}

HttpClient& HttpClient::SetHttpBody(const std::string& body) {
    this->m_postbody = body;
    return *this;
}

HttpClient& HttpClient::SetUrl(const std::string& url) {
    this->m_url.setUrl(url);
    m_mapHead.clear();
    defaultMapHead(); // 重新构造map
    return *this;
}

HttpClient& HttpClient::SetHeadMap(const std::map<std::string, std::string> headers) {
    for (const auto & m : headers) {
        auto search = m_mapHead.find(m.first);
        if (search != m_mapHead.end()) {
            search->second = m.second;
        } else {
            m_mapHead.emplace(m.first, m.second);
        }
    }
    // a simpler way:
    // for (const auto& m : headers) {
    //    m_mapHead[m.first] = m.second;
    // }
    return *this;
}

HttpClient& HttpClient::AddHeaderPair(const std::string& key, const std::string& value) {
    auto it = m_mapHead.find(key);
    if (it != m_mapHead.end()) {
        it->second = value;
    } else {
        m_mapHead.emplace(key, value);
    }
    return *this;
}

const std::string HttpClient::BlockingRequestHttp() const {
    std::string ip(DNSUtil::GetIPByHostName(m_url.getHost()).front());
    std::unique_ptr<SocketParam> sp(new SocketParam(ip,
                                                    std::stoi(m_url.getPort()),
                                                    Domain::INET,
                                                    Type::STREAM,
                                                    Protocol::DEFAULT));
    ClientSocket cs(sp);
    cs.Connect();
    std::string head = MakeHttpHead();
    cs.Send(head);
    std::string data = cs.Receive();

    return data;
}

const std::string HttpClient::GetSendData() const {
    if (m_method == HttpMethod::GET) {
        return MakeHttpHead();
    }
    if (m_method == HttpMethod::POST) {
        return MakeHttpHead() + GetBody();
    }
    return "";
}

std::string HttpClient::MakeHttpHead() const {
    std::string head("");
    // GET /bmgeorg/http/blob/master/server.c HTTP/1.1
    head += ConvertHttpMethodToStr(m_method);
    head += " ";
    head += m_url.getPath();
    head += " HTTP/1.1";
    head += "\r\n";

    for (const auto& m : m_mapHead) {
        head += m.first;
        head += ": ";
        head += m.second;
        head += "\r\n";
    }

    head += "\r\n";
    std::cout << "[[" << head << "]]" << std::endl;
    return head;
}

const std::string& HttpClient::GetBody() const {
    return m_postbody;
}


