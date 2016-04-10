#ifndef SERVER_MANAGER_H
#define SERVER_MANAGER_H

#include "server_config.hpp"
#include <vector>

class ServerManager
{
public:
  static ServerManager& Instance();
  std::vector<ServerConfig>& GetServerConfigs();
private:
  ServerManager();
  virtual ~ServerManager();
  void init();
  void parseServerConfig(const std::string& config);

private:
  std::vector<ServerConfig> m_configs;
};


#endif /* SERVER_MANAGER_H */
