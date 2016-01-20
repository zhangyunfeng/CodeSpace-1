#include <iostream>
#include <cassert>
#include <algorithm>
#include "Url.hpp"


Url::Url(const std::string& url) : m_url(url), m_host(""), m_path(""), m_protocol(""), m_port("80")
{
    setUrl(url);
}


Url::~Url()
{
    //deconstructor
}

void Url::setUrl(const std::string& url)
{
    //url: http://google.com/index
    if (url.empty()) {
	return;
    }
    m_url = url;
    
    // http    protocol
    std::string::size_type position = m_url.find("://"); // http://
    if (position != std::string::npos) {
        m_protocol = m_url.substr(0, position);
    } else {
        assert("protocol error");
    }

    // port :80
    std::string::size_type port_position = m_url.find_last_of(":");
    if (port_position != std::string::npos && port_position != position) {
        m_port = m_url.substr(port_position+1);
    }
    
    //www.google.com.cn/    host
    position += 3;
    std::string strtemp = m_url.substr(position);
    std::string::size_type host_position = strtemp.find("/");
    std::string::size_type path_last_position = strtemp.find_last_of(":");
    m_host = strtemp.substr(0, host_position);
    
    //path
    if (host_position != std::string::npos) {
        m_path = strtemp.substr(host_position, path_last_position-host_position-1);
    }
    
}

std::string Url::getProtocol() const
{
    return m_protocol;
}


std::string Url::getHost() const
{
    return m_host;
}

std::string Url::getPath() const
{
  return m_path;
}


std::string Url::getPort() const
{
    return m_port;

}

