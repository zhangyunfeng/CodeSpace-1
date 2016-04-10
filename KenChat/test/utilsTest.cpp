#include "../include/utils.hpp"

int main(int argc, char *argv[])
{
  std::string filePath("../src/config.json");
  std::string content = Utils::ReadFile(filePath);
  std::cout << content << std::endl;
  return 0;
}

