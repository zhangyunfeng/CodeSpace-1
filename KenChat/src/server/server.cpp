/**
 *Server 
 *
 **/

#include "server.hpp"


Server::Server() : m_ip("*"), m_port(0), m_context(1), m_socket(m_context, ZMQ_REP), m_workFunc(nullptr) {
  bind();
}
                 

Server::Server(const std::string& ip, unsigned int port) : m_ip(ip), m_port(port), m_context(1), m_socket(m_context, ZMQ_REP), m_workFunc(nullptr) {
  bind();
} 


void Server::SetWorkFunction(WorkFunc_T workFunc) {
  m_workFunc = workFunc;
}


void Server::Start() {
  while (true) {
    zmq::message_t request;

    // wait for next request from client
    m_socket.recv(&request);

    // TODO: do some work here
    zmq::message_t reply;
    if (m_workFunc != nullptr) {
      m_workFunc(reply, std::string((char*)request.data()));
    }
    
    // send reply back to client
    m_socket.send(reply);
  }
}

void Server::Restart() {
  std::string uri = "tcp://" + m_ip + ":" + std::to_string(m_port);
  m_socket.unbind(uri);
  m_socket.bind(uri);
}

void Server::Stop() {
  std::string uri = "tcp://" + m_ip + ":" + std::to_string(m_port);
  m_socket.unbind(uri);
}

void Server::bind() {
  m_socket.bind("tcp://" + m_ip + ":" + std::to_string(m_port));
}

void Server::init() {
  m_context = zmq::context_t(1);
  m_socket = zmq::socket_t(m_context, ZMQ_REP);
}
