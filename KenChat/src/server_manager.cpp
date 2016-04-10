
#include <exception>
#include <stdexcept>
#include <string>
#include <iostream>

#include "../include/server_manager.hpp"
#include "../include/utils.hpp"

#include "../rapidjson/rapidjson.h"
#include "../rapidjson/document.h"
#include "../rapidjson/stringbuffer.h"

ServerManager::ServerManager() {
  init();
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
  std::cout << "ServerManager::init()" << std::endl;
  std::string content = Utils::ReadFile("/home/ken/Github/KenChat/src/config.json");
  std::cout << "content: " + content << std::endl;
  parseServerConfig(content);
}

void ServerManager::parseServerConfig(const std::string& config) {
  std::cout << "parseServerConfig: " + config << std::endl;
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

