/**
 * Copyright
 * @file   DNSUtil.hpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Wed Sep  2 00:08:28 2015
 * 
 * @brief  
 * 
 * 
 */


#ifndef DNSUTIL_H
#define DNSUTIL_H

#include <iostream>
#include <string>
#include <vector>

#define IP_VECTOR std::vector<std::string>

class DNSUtil
{
  public:
    static IP_VECTOR GetIPByHostName(const std::string& hostname);
};


#endif /* DNSUTIL_H */
