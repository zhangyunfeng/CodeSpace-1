/**
 * @file   HttpManager.cpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Sun Jan 17 19:45:06 2016
 * 
 * @brief  
 * 
 * 
 */

#include "HttpManager.hpp"

HttpManager::HttpManager() : m_threadPool(COUNT_THREADS) {
    
}


HttpManager& HttpManager::GetInstance() {
    static HttpManager instance;
    return instance;
}

HttpManager::~HttpManager() {
    // release resources
}


void HttpManager::Request(int id, const std::string& url, OnRequestListener* listener) {
    m_threadPool.Enqueue([=, &url, &listener] {
            this->request(id, url, listener);
        });
}

void HttpManager::request(int id, const std::string& url, OnRequestListener* listener) {
    HttpClient hc(url);
    const std::string result = hc.blockingRequestHttp(url);
    if (listener != nullptr) {
        listener->OnReceived(id, result);
    }
}

