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
    LOG_DOWNLOAD 1
    LOG_UPDATE 1
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

# From http://www.cmake.org/pipermail/cmake/2010-March/035992.html:
# function to collect all the sources from sub-directories
# into a single list
function(add_sources)
  get_property(is_defined GLOBAL PROPERTY SRCS_LIST DEFINED)
  if(NOT is_defined)
    define_property(GLOBAL PROPERTY SRCS_LIST
      BRIEF_DOCS "List of source files"
      FULL_DOCS "List of all source files in the entire project")
  endif()
  # make absolute paths
  set(SRCS)
  foreach(s IN LISTS ARGN)
    if(NOT IS_ABSOLUTE "${s}")
      get_filename_component(s "${s}" ABSOLUTE)
    endif()
    list(APPEND SRCS "${s}")
  endforeach()
  # append to global list
  set_property(GLOBAL APPEND PROPERTY SRCS_LIST "${SRCS}")
endfunction(add_sources)

SET(YAML_CPP_HEADERS ${SOURCE_DIR}/include)

include_directories(${YAML_CPP_HEADERS} include)

file(GLOB_RECURSE sources "src/[a-zA-Z_]*.cpp")

set(dip_sources ${sources})

add_executable(dip  ${dip_sources})
target_link_libraries(dip libyaml-cpp)

enable_testing()

add_subdirectory(tests)