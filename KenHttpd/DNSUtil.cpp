/**
 * CopyRight  Ken
 * @file   DNSUtil.cpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Wed Sep  2 00:07:47 2015
 * 
 * @brief  get ip by host name
 *
 * 
 */

#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include "DNSUtil.hpp"

IP_VECTOR DNSUtil::GetIPByHostName(const std::string& hostname) {
    std::vector<std::string> ips;
    std::string ip("");
#ifdef __CPLUSPLUS
    extern "C" {
#endif
        struct hostent* host_ptr = NULL;
        if ((host_ptr = gethostbyname(hostname.c_str())) == NULL) {
            return ips;
        }
        char** pptr = NULL;
        char ipbuffer[32] = {0};
        // get ip
        pptr = host_ptr->h_addr_list;
        for (; *pptr != NULL; pptr++) {
            inet_ntop(host_ptr->h_addrtype, *pptr, ipbuffer, 32);
            ip.assign(ipbuffer);
            ips.push_back(ip);
            memset(ipbuffer, 0, 32);
            // break; //TODO: here only get first ip from addr_list
        }
#ifdef __CPLUSPLUS
    }
#endif
    return ips;
}
