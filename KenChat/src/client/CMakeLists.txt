cmake_minimum_required(VERSION 3.2)
include_directories("." "../../rapidjson")
link_directories("../../rapidjson")

aux_source_directory(. client_SRC)

add_executable(kenChatClient ${client_SRC})

target_link_libraries(kenChatClient zmq rapidjson)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Wno-unused-variable -pthread")
