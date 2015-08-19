/**
 * @file   Url.hpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Sun Aug 16 00:10:28 2015
 * 
 * @brief  Url parser
 * 
 * 
 */
#ifndef URL_HPP__
#define URL_HPP__

#include <string>


class Url
{
public:
    Url() = delete;
    Url(const std::string& url);
    virtual ~Url();

    std::string getProtocol() const;
    std::string getHost() const;
    std::string getPath() const ;
    std::string getPort() const;
    void setUrl(const std::string& url);
private:
    std::string m_protocol;
    std::string m_host;
    std::string m_path; //Get url, server path
    std::string m_port;
    std::string m_url;
};

#endif  // URL_HPP__


