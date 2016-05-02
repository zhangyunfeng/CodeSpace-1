#ifndef SERVER_MANAGER_H
#define SERVER_MANAGER_H

#include "server_config.hpp"
#include <vector>
#include <map>
#include <utility>

struct From_Message {
  std::string uuid_dst;
  std::string data;

  From_Message(const std::string& uuid_dst_, const std::string& data_) {
    uuid_dst = uuid_dst_;
    data = data_;
  }
};

class ServerManager
{
public:
  static ServerManager& Instance();
  std::vector<ServerConfig>& GetServerConfigs();
  void InsertMessage(const std::string& uuid_src, const std::string& uuid_dst, const std::string& data);
  void ClearMessage();
  From_Message GetMessage(const std::string& uuid_src);

private:
  ServerManager();
  virtual ~ServerManager();
  void init();
  void parseServerConfig(const std::string& config);
  
private:
  std::vector<ServerConfig> m_configs;
  std::multimap<std::string, From_Message> m_map;
};


#endif /* SERVER_MANAGER_H */
