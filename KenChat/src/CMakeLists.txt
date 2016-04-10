INCLUDE_DIRECTORIES("../include" "../rapidjson" )
				 
LINK_DIRECTORIES("../rapidjson" )

AUX_SOURCE_DIRECTORY(. kenchat_SRC)

ADD_EXECUTABLE(kenchat ${kenchat_SRC})

TARGET_LINK_LIBRARIES(kenchat zmq rapidjson)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Wno-unused-variable -pthread")
