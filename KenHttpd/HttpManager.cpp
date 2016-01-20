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
    HttpClient hc(url);
    m_threadPool.Enqueue([=] {
            this->request(id, hc, listener);
        });
}

void HttpManager::Request(int id, HttpMethod method, const std::string& url, OnRequestListener* listener, const std::string& body) {
    HttpClient hc(url);
    hc.SetHttpBody(body).SetHttpMethod(method);
    request(id, hc, listener);
}

void HttpManager::Request(int id, HttpMethod method, const std::string& url, OnRequestListener* listener, HEADER_MAP_T headermap, const std::string& body) {
    HttpClient hc(url);
    hc.SetHttpBody(body).SetHttpMethod(method).SetHeadMap(headermap);
    request(id, hc, listener);
}

void HttpManager::Request(int id, HttpClient& hc, OnRequestListener* listener) {
    request(id, hc,listener);
}

void HttpManager::request(const int id, const HttpClient& hc, OnRequestListener* listener) {
    // HttpClient hc(url);
    // hc.SetHttpMethod(method).SetHeadMap(headermap).SetHttpBody(body);
    const std::string result = hc.BlockingRequestHttp();
    if (listener != nullptr) {
        HttpResponseData hrd(result);
        if (hrd.GetHttpCode() == 200) {
            listener->OnReceived(id, hrd.GetResponseBody());            
        } else {
            listener->OnFailed(id, hrd.GetHttpCode(), HttpError::GetErrMsgByErrCode(hrd.GetHttpCode()) + "  " + hrd.GetResponseBody());
        }
    }
}




