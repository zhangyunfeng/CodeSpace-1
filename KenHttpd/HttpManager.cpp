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
#include "HttpResponseData.hpp"
#include "HttpError.hpp"

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
    m_threadPool.Enqueue([=] {
            this->request(id, url, listener);
        });
}

void HttpManager::request(int id, const std::string& url, OnRequestListener* listener) {
    HttpClient hc(url);
    const std::string result = hc.blockingRequestHttp();
    
    if (listener != nullptr) {
        HttpResponseData hrd(result);
        if (hrd.GetHttpCode() == 200) {
            listener->OnReceived(id, hrd.GetResponseBody());            
        } else {
            listener->OnFailed(id, hrd.GetHttpCode(), HttpError::GetErrMsgByErrCode(hrd.GetHttpCode()) + "  " + hrd.GetResponseBody());
        }

    }
}

