include_directories("." "../../rapidjson")
link_directories("../../rapidjson")

aux_source_directory(. server_SRC)

add_executable(kenChatServer ${server_SRC})

target_link_libraries(kenChatServer zmq rapidjson)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Wno-unused-variable -pthread")
