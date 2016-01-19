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

class MyOnRequestListener : public OnRequestListener {
  public:

    void OnReceived(int id, const std::string& data) override {
        std::cout << "id: " << id << " data: " << data << std::endl;
    }

    void OnFailed(int id, int err_code, const std::string& err_msg) override {
        std::cout << "onfailed : " << id << " " << err_code << " " << err_msg << std::endl;
    }
};

int main(int argc, char *argv[]) {
    std::string url2 = "http://128.199.103.33/data/2.5/weather?lat=35&lon=139";
    //    std::string url2 = "http://api.openweathermap.org/data/2.5/weather?lat=22.33&lon=114.06";
    std::string url = "http://www.tuling123.com/openapi/api?key=1ca80891c02111111736b8ce41591426&info=%E6%98%8E%E5%A4%A9%E5%8C%97%E4%BA%AC%E9%A3%9E%E6%8B%89%E8%90%A8%E7%9A%84%E9%A3%9E%E6%9C%BA";
    std::string url3 = "http://www.baidu.com";
    // Url u(url);
    // HttpClient hc(url);  // or HttpClient hc;
    
    // SampleDataReceiver sd;
    // hc.RegistHttpReceiver(&sd);
    // hc.ansyRequestHttp(1, url);
    // hc.ansyRequestHttp(2, url);

    // // std::cout << "ENDNDNDNDDN" << std::endl;
    int temp;
    // std::cin >> temp;

    MyOnRequestListener* listener = new MyOnRequestListener();
    
    HttpManager::GetInstance().Request(1, url, listener);

    HttpManager::GetInstance().Request(2, url2, listener);

    HttpManager::GetInstance().Request(3, url3, listener);

    std::cin >> temp;
    return 0;
}

