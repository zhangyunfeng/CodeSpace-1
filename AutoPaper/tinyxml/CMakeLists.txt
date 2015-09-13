SET(LIBTINYXML_SRC tinystr.cpp tinyxmlparser.cpp tinyxmlerror.cpp tinyxml.cpp)

# tinyxml.so
ADD_LIBRARY(tinyxml SHARED ${LIBTINYXML_SRC})

# tinyxml_static.a
ADD_LIBRARY(tinyxml_static STATIC ${LIBTINYXML_SRC})

# convert tinyxml_static to tinyxml.a
SET_TARGET_PROPERTIES(tinyxml_static PROPERTIES OUTPUT_NAME tinyxml)


# do not clean
SET_TARGET_PROPERTIES(tinyxml PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(tinyxml_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

# version and api-version
# NOTE: dynamic lib can has a version
#static lib need not
SET_TARGET_PROPERTIES(tinyxml PROPERTIES VERSION 1.0 SOVERSION 1)
#SET_TARGET_PROPERTIES(tinyxml_static PROPERTIES VERSION 1.0 SOVERSION 1)

INSTALL(TARGETS tinyxml tinyxml_static
  LIBRARY DESTINATION tinyxml
  ARCHIVE DESTINATION tinyxml)
