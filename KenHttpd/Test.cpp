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

    return 0;
}

