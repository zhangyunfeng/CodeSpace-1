INCLUDE_DIRECTORIES("../../KenHttpd" "../rapidjson" "../Linux_voice/include")
				 
LINK_DIRECTORIES("../../KenHttpd/lib" "../rapidjson" "../Linux_voice/libs/x64")

AUX_SOURCE_DIRECTORY(. robot_SRC)

ADD_EXECUTABLE(KenRobot ${robot_SRC})

TARGET_LINK_LIBRARIES(KenRobot KenHttp rapidjson msc)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Wno-unused-variable -pthread")
