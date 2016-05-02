#include <string>
#include <iostream>
#include <thread>
#include <chrono>

#include "client.hpp"
#include "../utils.hpp"


int main(int argc, char *argv[])
{
  if (argc < 2) {
    std::cerr << "请指定自己身份" << std::endl;
    return -1;
  }

  std::string uuid_src = argv[1];
  
  Client client(uuid_src);
  client.Connect("127.0.0.1", 5555);
  client.StartSendThread();
  std::cout << "Start Send Thread Finish." << std::endl;
  client.StartReceiveThread();
  std::cout << "Start Receive Thread Finish." << std::endl;

  while (true) {
    std::cout << "TO:" ;
    char uuid_dst[50] = {0};
    std::flush(std::cout);
    std::cin.getline(uuid_dst, 50);
    //std::cin >> uuid_dst;
    std::cout << ">>:";
    char str[512] = {0};
    std::flush(std::cout);
    std::cin.getline(str, 512);
    client.EnQueueMsg(uuid_dst, str);
  }
  
  return 0;
}
