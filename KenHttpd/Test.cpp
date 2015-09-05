/**Copyright  Ken
 * @file   Test.cpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Sun Aug 16 19:43:18 2015
 *
 * @brief
 *
 *
 */
// #include <iostream>
// #include <string>
// #include "Url.hpp"



// void print(Url u)
// {
//     std::cout <<"protocol: " << u.getProtocol() << std::endl;
//     std::cout << "host: " << u.getHost() << std::endl;
//     std::cout << "path: " << u.getPath() << std::endl;
//     std::cout << "port: " << u.getPort() << std::endl;

//     std::cout << std::endl << std::endl;
// }

// int main(void)
// {
//     Url url(std::string("http://www.google.com/helloworld/abcdef:8080"));

//     print(url);

//     Url url2(std::string("https://www.tencent.com:8080"));
//     print(url2);

//     Url url3(std::string("ftp://102.3.3.44/hahah/jjj:89"));
//     print(url3);
//     return 0;
// }

#include <vector>
#include <string>
#include "DNSUtil.hpp"

void PrintVector(std::vector<std::string> vec) {
    for (std::vector<std::string>::iterator it = vec.begin();
         it != vec.end(); it++) {
        std::cout << *it << std::endl;
}
}

int main(void) {
    std::vector<std::string> ip = DNSUtil::GetIPByHostName("www.baidu.com");
    std::cout << "baidu.com: ";
    PrintVector(ip);

    ip = DNSUtil::GetIPByHostName("www.shuame.com");
    std::cout << "www.shuame.com: ";
    PrintVector(ip);

    ip = DNSUtil::GetIPByHostName("qq.com");
    std::cout << "www.qq.com: ";
    PrintVector(ip);

    ip = DNSUtil::GetIPByHostName("127.0.0.1");
    PrintVector(ip);
    return 0;
}


