/**
 * @file   HttpManager.hpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Sun Jan 17 18:55:22 2016
 * 
 * @brief  HttpMananger.hpp
 * 
 * 
 */
#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

#include <string>
#include <thread>
#include <vector>
#include "ThreadPool.hpp"
#include "OnRequestListener.hpp"
#include "HttpClient.hpp"

typedef std::map<std::string, std::string> HEADER_MAP_T;
constexpr int const COUNT_THREADS = 50;

class HttpManager {
  public:
    ~HttpManager();
    static HttpManager& GetInstance();

    /** 
     * default GET method http request
     * 
     * @param id 
     * @param url 
     * @param listener 
     */
    void Request(int id, const std::string& url, OnRequestListener* listener);

    /** 
     * use default header map
     * 
     * @param id request id
     * @param method GET or POST
     * @param url 
     * @param listener 
     * @param body 
     */
    void Request(int id, HttpMethod method, const std::string& url, OnRequestListener* listener, const std::string& body = "");

    void Request(int id, HttpMethod method, const std::string& url, OnRequestListener* listener, HEADER_MAP_T headermap, const std::string& body = "");

    void Request(int id, HttpClient& hc, OnRequestListener* listener);

    void CancelRequest(int id);

    void StopAllRequests();
  private:
    HttpManager();
    void request(const int id, const HttpClient& hc, OnRequestListener* listener);
  private:
    ThreadPool m_threadPool;
};

#endif /* HTTPMANAGER_H */
