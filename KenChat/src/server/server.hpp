
#ifndef SERVER_HPP
#define SERVER_HPP

#include <zmq.hpp>
#include <algorithm>
#include <functional>

typedef void (*WorkFunc_T)(zmq::message_t&, std::string);

class Server {
public:
  Server();
  Server(const std::string& ip, unsigned int port);
  void Start();
  void Restart();
  void Stop() ;                 //
  void SetWorkFunction(WorkFunc_T workFunc);

private:
  void bind();
  void init();

private:
  std::string m_ip;
  unsigned int m_port;
  zmq::context_t m_context;
  zmq::socket_t m_socket;
  WorkFunc_T m_workFunc;
};

#endif //SERVER_HPP











