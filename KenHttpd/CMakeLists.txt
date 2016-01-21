# CMake 最低版本要求
cmake_minimum_required (VERSION 3.1)

#项目信息
project (KenHttpTest)

# 查找当前目录下的所有的源文件，并将名称保存到 DIR_SRCS变量
aux_source_directory (. DIR_SRCS)

# 设置文件生成目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

#指定生成目标
add_executable(KenHttpTest ${DIR_SRCS})
add_library(KenHttp ${DIR_SRCS})
# support c++11
#add_definitions( -std=c++11 -lpthread)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Wno-unused-variable -pthread")