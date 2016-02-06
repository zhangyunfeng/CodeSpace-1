/**
 * @file   KenRobot.hpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Mon Jan 25 22:49:38 2016
 * 
 * @brief  
 * 
 * 
 */


#ifndef KENROBOT_H
#define KENROBOT_H

#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "OnRequestListener.hpp"
#include "HttpManager.hpp"
#include "ResponseParser.hpp"
#include "VoiceManager.hpp"


// 用于保证用户输入和机器回复是一问一答的方式
extern volatile bool gFlag;

class MyOnRequestListener : public OnRequestListener
{
  public:
    MyOnRequestListener() {
        
    }
    
    virtual ~MyOnRequestListener() {
        
    }

    void OnReceived(int id, const std::string& data) override {
        // 解析 data 用json,
        // std::cout << ResponseParser::GetInstance().GetTulingCode(data) << std::endl;
        std::string text(ResponseParser::GetInstance().GetText(data) + ResponseParser::GetInstance().GetUrl(data));
        std::cout << "\n" << text << std::endl;
        VoiceManager::GetInstance().ConvertText2Speech(text.c_str(), "voice");
        system("play voice");
        
        gFlag = true;
    }
    
    void OnFailed(int id, int err_code, const std::string& err_msg) override {
        // 请求失败
        std::cerr << "Tuling Failed: " << "id: " << id << " err_code: " << err_code
                  <<  " err_msg: " << err_msg << std::endl;
    }
};


/// Main controller
class KenRobot
{
  public:
    KenRobot();
    virtual ~KenRobot();

    /** 
     * send data to 
     * request-reply方式 一问一答
     * @param words 
     */
    void Say(const std::string& words) const;
    void Run();
  private:
    std::unique_ptr<MyOnRequestListener> m_listener;
};


#endif /* KENROBOT_H */
