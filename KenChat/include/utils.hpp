#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>

class Utils {
public:

  static const std::string ReadFile(const std::string& file) {
    std::cout << "ReadFile: " + file << std::endl;
    std::string content("");
    if (file.empty()) {
      return content;
    }
    
    std::ifstream in(file.c_str());
    if (!in) { // file not existed
      return content;
    }
    while (!in.eof()) {
      std::string tmp("");
      in >> tmp;
      std::cout << tmp << std::endl;
      content += tmp;
    }
    if (in.bad()) {
      // read file failed
      throw std::runtime_error("read file " + file + " failed\n");
    }
    in.close();
    return content;
  }


};

#endif /* UTILS_H */
