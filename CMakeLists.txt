cmake_minimum_required (VERSION 3.1)

set (CMAKE_CXX_STANDARD 11)

project (dip)
include(ExternalProject)

ExternalProject_Add(
    yaml-cpp
    URL https://github.com/jbeder/yaml-cpp/archive/master.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/yaml-cpp/
    # Disable install step
    INSTALL_COMMAND ""
    UPDATE_COMMAND ""
)

ExternalProject_Get_Property(yaml-cpp SOURCE_DIR BINARY_DIR)
if(WIN32)
  set(yaml_library_suffix "md")
  set(yaml_library_extension ".lib")
else()
  set(yaml_library_suffix "")
  set(yaml_library_extension ".a")
endif()

add_library(libyaml-cpp STATIC IMPORTED)
# TODO: use suffic variable if not WIN32
set_property(TARGET libyaml-cpp PROPERTY IMPORTED_LOCATION ${BINARY_DIR}/${CMAKE_CFG_INTDIR}/libyaml-cpp${yaml_library_suffix}${yaml_library_extension}) 
add_dependencies(libyaml-cpp yaml-cpp)

SET(YAML_CPP_HEADERS ${SOURCE_DIR}/include)

include_directories(${YAML_CPP_HEADERS} include)

set(dip_sources ${CMAKE_CURRENT_SOURCE_DIR}/src/arguments.cpp 
            ${CMAKE_CURRENT_SOURCE_DIR}/src/dip.cpp 
			${CMAKE_CURRENT_SOURCE_DIR}/src/environment.cpp 
			${CMAKE_CURRENT_SOURCE_DIR}/src/commands/compose.cpp 
			${CMAKE_CURRENT_SOURCE_DIR}/src/commands/dnsdock.cpp 
			${CMAKE_CURRENT_SOURCE_DIR}/src/commands/service.cpp 
			${CMAKE_CURRENT_SOURCE_DIR}/src/commands/ssh.cpp)

add_executable(dip  ${dip_sources} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(dip libyaml-cpp)

add_subdirectory(tests)