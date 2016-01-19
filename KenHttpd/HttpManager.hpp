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

constexpr int const COUNT_THREADS = 50;

class HttpManager {
  public:
    ~HttpManager();
    static HttpManager& GetInstance();
    void Request(int id, const std::string& url, OnRequestListener* listener);
    void CancelRequest(int id);
    void StopAllRequests();
  private:
    HttpManager();
    void request(int id, const std::string& url, OnRequestListener* listener);
  private:
    ThreadPool m_threadPool;
};

#endif /* HTTPMANAGER_H */
