#include <iostream>
#include <string>
#include <functional>

#include "./server.hpp"
#include "../utils.hpp"
#include "server_manager.hpp"

void server_worker(zmq::message_t& msg, std::string str) {
  // std::cout << "Received: " << str << std::endl;
  std::string uuid_src("");
  std::string uuid_dst("");
  std::string data("");

  if (!str.empty()) {
    Utils::ParseTranserJson(str, uuid_src, uuid_dst, data);
    if (!uuid_dst.empty() && !data.empty()) {
      ServerManager::Instance().InsertMessage(uuid_src, uuid_dst, data);  
    }
  }
  From_Message fm = ServerManager::Instance().GetMessage(uuid_src);
  std::string content = Utils::BuildTranserJson(fm.uuid_dst, "", fm.data);
  std::cout << "received: " << str << "  will send: " << content << std::endl;
  //memcpy(msg.data(), content.c_str(), content.length()+1); // segment error
  msg.rebuild(content.c_str(), content.length());
  
}

int main(void) {
  // std::string uuid_src("12345");
  // std::string uuid_dst("234588");
  // std::string data("hell world");

  // std::string json = Utils::BuildTranserJson(uuid_src, uuid_dst, data);

  // std::cout << "json: " << json << std::endl;

  // std::string uuid_src2("");
  // std::string uuid_dst2("");
  // std::string data2("");
  // Utils::ParseTranserJson(json, uuid_src2, uuid_dst2, data2);

  // std::cout << "uuid_src2: " << uuid_src2 << " uuid_dst2: " << uuid_dst2 << " data2:" << data2 << std::endl;

  // Server s("localhost", 5555); // Error: will cause terminater exception: No such device; need replace "localhost" with "127.0.0.1"

  Server s("127.0.0.1", 5555);
  zmq::message_t msg;
  std::string str("");
  s.SetWorkFunction(server_worker);
  s.Start();

  return 0;
}
