

/**
 * @file   gethostbyname.cpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Mon Aug 31 22:42:02 2015
 * 
 * @brief  Dns util
 *
 * @build  g++ gethostbyname.cpp -o dnstest -std=c++11
 * 
 */

#include <string>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <sys/socket.h>


class DNSUtil
{
  public:
    static std::string GetIpByHostname(const std::string& hostname)
    {
        std::string ip("");
        if (hostname.empty()) {
            return ip;
        }

        struct in_addr addr;
        struct hostent *host = NULL;
        host = gethostbyname(hostname.c_str());
        memcpy(&addr.s_un.s_addr, host->h_addr_list[0], host->h_length);
        ip = inet_ntoa(addr);

        return ip;
    }
};


/** For Test **/
int main(int argc, char *argv[])
{
    std::std::cout << DNSUtil.GetIpByHostname("www.baidu.com") << std::endl;
    return 0;
}


