CMAKE_MINIMUM_REQUIRED(VERSION 3.2)

PROJECT(TEST)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
INCLUDE_DIRECTORIES("../tinyxml")
LINK_DIRECTORIES("/home/ken/KenHttpd/AutoPaper/tinyxml")

INCLUDE_DIRECTORIES("../libharu/include")
LINK_DIRECTORIES("/home/ken/KenHttpd/AutoPager/libharu/lib")
# find_library(hpdf libhpdf.a)
# ADD_LIBRARY(hpdf STATICIMPORTED)
# SET_TARGET_PROPERTIES(hpdf PROPERTIES IMPORTED_LOCATION /home/ken/KenHttpd/AutoPager/libharu/lib/libhpdf.a)


SET(SRC_LIST Test.cpp
  GlobalInclude.hpp
  MiscUtils.cpp
  PdfCommonData.cpp
  PdfXmlLoader.cpp
  XmlLoader.cpp
  PdfGeneratorEngineHelper.cpp
  PdfGeneratorEngine.cpp
  Constants.cpp
  )

ADD_EXECUTABLE(Test ${SRC_LIST})
TARGET_LINK_LIBRARIES(Test tinyxml hpdf)


