#include "client.hpp"
#include "../utils.hpp"

Client::Client(const std::string& uuid_self) : m_context(1), m_socket(m_context, ZMQ_REQ), m_receivedMsgCallback(new ReceivedMessageCallback()), m_uuid_src(uuid_self) {
  m_serverIp = "";
  m_serverPort = 0;
  m_sendFlag = false;
}

Client::~Client() {
  
}

void Client::Connect( std::string server_ip, int server_port ) {
  m_serverIp = server_ip;
  m_serverPort = server_port;
  std::string uri = "tcp://" + server_ip + ":" + std::to_string(server_port);
  m_socket.connect(uri);
}

void Client::Disconnect() {
  m_socket.disconnect(m_serverIp);
}

void Client::Close() {
  m_socket.close();
}

void Client::SendMessage( std::string msg ) {
  size_t len = msg.length() + 1;
  zmq::message_t request(len);
  memcpy(request.data(), msg.c_str(), len);
  m_socket.send(request);
  
}

void Client::ReceiveMessage() {
  zmq::message_t reply;
  m_socket.recv(&reply);
  this->m_receivedMsgCallback->OnCallback(reply);
}

/**
 ** 发送消息线程
 **/
void Client::StartSendThread() {
  std::thread t([this]() {
      while (true) {
        if (!m_queueToSend.empty()) {
          {
            if (m_sendFlag) {
              continue; // 已经发送过了
            }
            std::lock_guard<std::mutex> lock(m_mutex);
            std::string msg = m_queueToSend.front();
            SendMessage(msg);
            m_sendFlag = true;
            m_queueToSend.pop();
          }
          m_cond.notify_one();
        } else {
          if (m_sendFlag) { // 已经发送过了
            continue;
          }
          {
            std::lock_guard<std::mutex> lock(m_mutex);
            std::string msg("");
            SendMessage(Utils::BuildTranserJson(this->m_uuid_src, "", ""));
            m_sendFlag = true;
          }
          m_cond.notify_one();
          std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        
      }});
    t.detach();
}


/**
 **接受消息线程
 **/
void Client::StartReceiveThread() {
  std::thread t([this]() {
      while (true) {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cond.wait(lock, [this]() {
            return m_sendFlag;
          });
        m_sendFlag = false;
        ReceiveMessage();
        lock.unlock();
      }
    });
  t.detach();
}


void Client::EnQueueMsg(const std::string& uuid_dst, const std::string& msg ) {
  if (msg.empty() or uuid_dst.empty()) {
    std::cerr << "message empty or uuid_dst empty" << std::endl;
    return;
  }
  m_queueToSend.push(Utils::BuildTranserJson(this->m_uuid_src, uuid_dst, msg));
}


void Client::SetUuidSrc( const std::string &uuid_self ) {
  this->m_uuid_src = uuid_self;
}
