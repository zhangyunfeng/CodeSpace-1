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



class SampleDataReceiver : public HttpReceiver
{
  public:
    SampleDataReceiver() {
        
    }
    virtual ~SampleDataReceiver() {
        
    }

    static SampleDataReceiver GetInstance() {
        static SampleDataReceiver sd;
        return sd;
    }

    // OnReceive(int id, const std::string& data);
    void OnReceive(int id, const std::string& data) {
        std::cout << "id: " << id << " ;data: " << data << std::endl;
    }

};



int main(int argc, char *argv[]) {
    // std::string url = "http://128.199.103.33/data/2.5/weather?lat=35&lon=139";
    std::string url = "http://api.openweathermap.org/data/2.5/weather?lat=22.33&lon=114.06";

    Url u(url);
    HttpClient hc(url);  // or HttpClient hc;
    
    SampleDataReceiver sd;
    hc.RegistHttpReceiver(&sd);
    hc.ansyRequestHttp(1, url);
    hc.ansyRequestHttp(2, url);

    std::cout << "ENDNDNDNDDN" << std::endl;
    int temp;
    std::cin >> temp;
    return 0;
}

