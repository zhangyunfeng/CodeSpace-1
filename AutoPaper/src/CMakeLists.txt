CMAKE_MINIMUM_REQUIRED(VERSION 3.2)

PROJECT(TEST)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
INCLUDE_DIRECTORIES("../tinyxml")
LINK_DIRECTORIES("/home/ken/KenHttpd/AutoPaper/tinyxml")
SET(SRC_LIST Test.cpp
  GlobalInclude.hpp
  MiscUtils.cpp
  PdfCommonData.cpp
  PdfXmlLoader.cpp
  XmlLoader.cpp
  Test.cpp
  )

ADD_EXECUTABLE(Test ${SRC_LIST})
TARGET_LINK_LIBRARIES(Test tinyxml)


