 /**
 * @file   KenRobot.cpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Mon Jan 25 22:40:46 2016
 * 
 * @brief  
 * 
 * 
 */

#include <chrono>
#include "KenRobot.hpp"
#include "Constants.hpp"
#include "MiscUtils.hpp"

volatile bool gFlag = true;

KenRobot::KenRobot() : m_listener(new MyOnRequestListener())
{

}

KenRobot::~KenRobot() {
    
}


void KenRobot::Say(const std::string& words) const {
    const std::string wordsUriEncoded = MiscUtils::UriEncode(words);
    const std::string url(Turling_URL_HOST + Turling_PATH + "key=" + Turling_KEY +
                          "&info=" + wordsUriEncoded);
    HttpClient hc(url);
    HttpManager::GetInstance().Request(1, hc, m_listener.get());
}


void KenRobot::Run() {
    while (true) {
        if (gFlag) {
            std::cout << "\n>>";
            std::string words;
            std::cin >> words;
            gFlag = false;
            this->Say(words);
        } else {
            std::chrono::duration<double, std::milli> d(0.1);
            std::this_thread::sleep_for(d);
        }
    }
}

