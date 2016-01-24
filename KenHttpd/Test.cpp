/**
   Copyright
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
#include "HttpResponseData.hpp"
#include "OnRequestListener.hpp"
#include "HttpManager.hpp"
#include "MiscUtils.hpp"
#include "HttpClient.hpp"

bool gTalkFlag = true;

class MyOnRequestListener : public OnRequestListener {
  public:

    void OnReceived(int id, const std::string& data) override {
        // std::cout << "id: " << id << " data: " << data << std::endl;
        std::cout << "图灵机器人>>\n " << data << std::endl;
        std::cout << "===========================================================" << std::endl;
        gTalkFlag = true;
    }

    void OnFailed(int id, int err_code, const std::string& err_msg) override {
        std::cout << "onfailed : " << id << " " << err_code << " " << err_msg << std::endl << std::endl;
        gTalkFlag = true;
    }
};

int main(int argc, char *argv[]) {
    std::string tuling_url_base = "http://tuling123.com/openapi/api?key=2bfa93ae9046da2a47bc780c1a151acd&info=";

    MyOnRequestListener* listener = new MyOnRequestListener();

    while (true) {
        if (gTalkFlag) {
            std::string question("");
            std::cout << ">>";
            std::cin >> question;
            std::cout << "\n";
            std::string url = tuling_url_base + MiscUtils::UriEncode(question);
            //HttpManager::GetInstance().Request(1, url, listener);
            HttpClient hc(url);
            hc.SetHttpMethod(HttpMethod::POST);
            HttpManager::GetInstance().Request(1, hc, listener);
            gTalkFlag = false;
        }
    }

    // const std::string mapHeader = "GET HTTP\1.1\r\nAccept-Ranges: none\r\nConnection: close\r\nContent-Encoding: gzip\r\nContent-Type: text/html;charset=utf-8\r\nDate: Sun, 24 Jan 2016 14:39:53 GMT\r\nLast-Modified: Sun, 24 Jan 2016 14:39:53 GMT\r\nServer: Apache\r\nSet-Cookie: JSESSIONID=AEC0D89A5970AB6D6DED33AA5824C549; Path=/UserCookie=kHeonl3IbVDnla0LqQtfqdjGTAShGVza; Expires=Wed, 18-Jan-2017 14:39:53 GMT; Path=/\r\nTransfer-Encoding: chunked\r\nVary: Accept-Encoding,User-Agent\r\naccess-control-allow-credentials: true\r\n";
    
    // std::map<std::string, std::string> map = MiscUtils::ParseHttpHeader(mapHeader);
    // for (auto& m : map) {
    //     std::cout << m.first << "  " << m.second << std::endl;
    // }
    
    return 0;
}
