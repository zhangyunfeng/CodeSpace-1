
#include <exception>
#include <stdexcept>
#include <string>
#include <iostream>

#include "server_manager.hpp"
#include "../utils.hpp"

#include "../../rapidjson/rapidjson.h"
#include "../../rapidjson/document.h"
#include "../../rapidjson/stringbuffer.h"

ServerManager::ServerManager() {
  //init();
}

ServerManager::~ServerManager() {
  
}

ServerManager& ServerManager::Instance() {
  static ServerManager instance;
  return instance;
}

std::vector<ServerConfig>& ServerManager::GetServerConfigs() {
  return m_configs;
}

/**
 *初始化
 */
void ServerManager::init() {
  std::string content = Utils::ReadFile("/home/ken/Github/KenChat/src/config.json");
  parseServerConfig(content);
}

void ServerManager::parseServerConfig(const std::string& config) {
  rapidjson::Document document;
  if ((document.Parse<0>(config.c_str())).HasParseError()) {
    std::cerr << "RapidJson parses failed: json " + config << std::endl;
    throw std::runtime_error("parse server config failed\n");
    return;
  }

  // 根据server这个关键字取出所有的server的配置
  rapidjson::Value& serverArray = document["server"];
  if (serverArray.IsArray()) {
    for (unsigned int i = 0; i < serverArray.Capacity(); i++) {
      rapidjson::Value& v = serverArray[i];

      std::string ip("Unknown");
      unsigned int port = 0;

      if (v.HasMember("ip")) {
        ip = v["ip"].GetString();
      }

      if (v.HasMember("port")) {
        port = v["port"].GetInt();
      }

      m_configs.push_back(ServerConfig(ip, port));
    }
  }
}


void ServerManager::InsertMessage( const std::string &uuid_src, const std::string &uuid_dst, const std::string &data ) {
  m_map.emplace(uuid_dst, From_Message(uuid_src, data));
}


void ServerManager::ClearMessage() {
  m_map.clear();
}


From_Message ServerManager::GetMessage( const std::string &uuid_src ) {
  auto it = m_map.find(uuid_src);
  From_Message ret("", "");

  if (it != m_map.end()) {
    ret = it->second;
    m_map.erase(it);
  }
  return ret;
}


