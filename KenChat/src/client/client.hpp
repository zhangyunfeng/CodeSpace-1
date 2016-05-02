#ifndef CLIENT_H
#define CLIENT_H

#include <zmq.hpp>
#include <string>
#include <thread>
#include <memory>
#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>

class Client
{
public:
  Client(const std::string& uuid_self);
  virtual ~Client();

  void Connect(std::string server_ip, int server_port);
  void Disconnect();

  void Close();

  void SendMessage(std::string msg);
  void ReceiveMessage();

  void StartSendThread();
  void StartReceiveThread();

  void EnQueueMsg(const std::string& uuid_dst, const std::string& msg);

  void SetUuidSrc(const std::string& uuid_self); // 自己的身份, uuid_src

public:
  class ReceivedMessageCallback {
  public:
    void OnCallback(zmq::message_t& msg) {
      if (msg.size() == 39) { // empty formated string， e.g.: {"uuid_src":"","uuid_dst":"","data":""}
        return;
      }
      std::string data((char*)msg.data(), msg.size());
      
      std::cout << std::endl << data << std::endl;
    }
  };
  
private:
  std::string m_serverIp;
  int m_serverPort;
  zmq::context_t m_context;
  zmq::socket_t m_socket;
  std::shared_ptr<std::thread> m_receiverThread;
  std::shared_ptr<ReceivedMessageCallback> m_receivedMsgCallback;

  std::queue<std::string> m_queueReceived;
  std::queue<std::string> m_queueToSend;

  std::mutex m_mutex;
  std::condition_variable m_cond;
  bool m_sendFlag;

  std::string m_uuid_src;
};



#endif /* CLIENT_H */
