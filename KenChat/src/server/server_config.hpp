#ifndef SERVER_CONFIG_HPP
#define SERVER_CONFIG_HPP

#include <string>

struct ServerConfig  
{
private:
  std::string server_ip;
  unsigned int server_port;

public:
  ServerConfig() = delete;

  ServerConfig(const std::string& ip, unsigned int port) {
    this->server_ip = ip;
    this->server_port = port;
  }
  
  std::string GetServerIp() {
    return server_ip;
  }

  unsigned int GetServerPort() {
    return server_port;
  }
};

#endif
