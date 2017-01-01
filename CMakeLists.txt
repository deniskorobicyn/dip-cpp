cmake_minimum_required (VERSION 2.6)
project (ride)
include(ExternalProject)
ExternalProject_Add(
    yaml-cpp
    URL https://github.com/jbeder/yaml-cpp/archive/master.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/yaml-cpp/
    # Disable install step
    INSTALL_COMMAND ""
    UPDATE_COMMAND ""
    LOG_DOWNLOAD 1
    LOG_UPDATE 1
)

ExternalProject_Get_Property(yaml-cpp SOURCE_DIR BINARY_DIR)

add_library(libyaml-cpp STATIC IMPORTED)
set_property(TARGET libyaml-cpp PROPERTY IMPORTED_LOCATION ${BINARY_DIR}/${CMAKE_CFG_INTDIR}/libyaml-cppmd.lib)
add_dependencies(libyaml-cpp yaml-cpp)

include_directories(${SOURCE_DIR}/include)

enable_testing()

add_subdirectory(tests)

add_executable(ride main.cpp)
target_link_libraries(ride libyaml-cpp)