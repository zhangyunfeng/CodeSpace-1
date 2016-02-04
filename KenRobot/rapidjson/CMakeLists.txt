project(rapidjson)

#Add the source in project root directory
aux_source_directory(. rapidjson_SRC)

# add header file include directories
include_directories(./ ./error ./internal ./msinttypes)

# add sub block directories
add_subdirectory(error)
add_subdirectory(internal)

add_library(rapidjson ${rapidjson_SRC})
