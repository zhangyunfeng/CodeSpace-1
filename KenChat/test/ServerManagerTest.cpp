#include <iostream>
#include "../include/server_manager.hpp"

int main(int argc, char *argv[])
{
  std::cout << "ServerManager: test: " << std::endl;

  std::vector<ServerConfig>& configs = ServerManager::Instance().GetServerConfigs();
  std::cout << "Configs: " << configs.size() << std::endl;

  for (int i = 0; i < configs.size(); i++) {
    std::cout << configs.at(i).GetServerIp() << " " << configs.at(i).GetServerPort() << std::endl;
  }
  return 0;
}


