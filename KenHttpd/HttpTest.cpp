
/**
 * @file   HttpTest.cpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Wed Aug 19 22:46:40 2015
 * 
 * @brief  Http client test
 * 
 * 
 */

#include <iostream>
#include <string>

#include "HttpClient.hpp"





int main(int argc, char *argv[])
{

    std::string url = "http://128.199.103.33/data/2.5/weather?lat=35&lon=139";
    
    HttpClient hc(url);
    Url u(url);
    
    std::string head = hc.MakeHttpHead(u);

    std::cout << head << std::endl;

    std::string data = hc.blockingRequestHttp(url);
    std::cout << data << std::endl;
    
    return 0;
}

