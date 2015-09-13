# AutoPager  cmake file

PROJECT (AutoPager)

ADD_SUBDIRECTORY(tinyxml)

SET(SRC_LIST main.cpp)

MESSAGE(STATUS "This is BINARY dir " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "This is SOURCE dir " ${PROJECT_SOURCE_DIR})


ADD_EXECUTABLE(autopager ${SRC_LIST})
