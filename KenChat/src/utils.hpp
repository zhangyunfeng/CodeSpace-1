#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdio>

#include "../rapidjson/document.h"
#include "../rapidjson/prettywriter.h"
#include "../rapidjson/filereadstream.h"
#include "../rapidjson/stringbuffer.h"

class Utils {
public:

  // read file content
  static const std::string ReadFile(const std::string& file) {
    std::cout << "ReadFile: " + file << std::endl;
    std::string content("");
    if (file.empty()) {
      return content;
    }

    if (!IsFileExisted(file)) { // file not existed
      return "";
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

  // to check file existed
  static bool IsFileExisted(const std::string& filepath) {
    std::fstream fs;
    fs.open(filepath);
    if (!fs.is_open()) {
      return false;
    }
    fs.close();
    return true;
  }

  /**
   ** 构建传输的json字符串
   **/
  static std::string BuildTranserJson(const std::string& uuid_src_, const std::string& uuid_dst_, const std::string& data_) {
    static rapidjson::Document sDocument(nullptr);
    // define the document as an object rather than an array
    sDocument.SetObject();

    static rapidjson::Document::AllocatorType& sAllocator = sDocument.GetAllocator();
    rapidjson::Value root(rapidjson::kObjectType);

    rapidjson::Value uuid_src(rapidjson::kStringType);
    uuid_src.SetString(uuid_src_.c_str(), uuid_src_.size(), sAllocator);

    rapidjson::Value uuid_dst(rapidjson::kStringType);
    uuid_dst.SetString(uuid_dst_.c_str(), uuid_dst_.size(), sAllocator);

    rapidjson::Value data (rapidjson::kStringType);
    data.SetString(data_.c_str(), data_.size(), sAllocator);

    root.AddMember("uuid_src", uuid_src, sAllocator);
    root.AddMember("uuid_dst", uuid_dst, sAllocator);
    root.AddMember("data", data, sAllocator);

    rapidjson::StringBuffer sb;
    rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
    root.Accept(writer);
    return sb.GetString();
  }

  /**
   **解析json字符串， 获取字符串内容
   **/
  static void ParseTranserJson(const std::string& in_json, std::string& uuid_src, std::string& uuid_dst, std::string& data) {
    static rapidjson::Document sDocument(nullptr);
    sDocument.Parse<0>(in_json.c_str());
    uuid_src = sDocument["uuid_src"].GetString();
    uuid_dst = sDocument["uuid_dst"].GetString();
    data = sDocument["data"].GetString();
  }

};

#endif /* UTILS_H */




