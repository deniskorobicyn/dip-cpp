cmake_minimum_required (VERSION 2.6)
project (ride)
set(YAML_INCLUDE_PATH "PLEASE SET" CACHE FILEPATH "yaml-cpp include directory path")
set(YAML_LIB_PATH "PLEASE SET" CACHE FILEPATH "yaml-cpp static library path")

include_directories(${YAML_INCLUDE_PATH})
add_executable(ride main.cpp)
target_link_libraries(ride ${YAML_LIB_PATH})