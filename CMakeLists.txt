cmake_minimum_required (VERSION 3.1)

set (CMAKE_CXX_STANDARD 11)

project (dip)
include(ExternalProject)

set(dip_sources ${CMAKE_CURRENT_SOURCE_DIR}/src/arguments.cpp 
            ${CMAKE_CURRENT_SOURCE_DIR}/src/dip.cpp 
			${CMAKE_CURRENT_SOURCE_DIR}/src/environment.cpp 
			${CMAKE_CURRENT_SOURCE_DIR}/src/commands/compose.cpp 
			${CMAKE_CURRENT_SOURCE_DIR}/src/commands/dnsdock.cpp 
			${CMAKE_CURRENT_SOURCE_DIR}/src/commands/service.cpp 
			${CMAKE_CURRENT_SOURCE_DIR}/src/commands/ssh.cpp)

set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)

ExternalProject_Add(
    yaml-cpp
    GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}/yaml-cpp
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/yaml-cpp/
)

include_directories(${EXTERNAL_INSTALL_LOCATION}/yaml-cpp/include include)
link_directories(${EXTERNAL_INSTALL_LOCATION}/yaml-cpp/lib)

add_executable(dip  ${dip_sources} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
add_dependencies(dip yaml-cpp)

if(WIN32)                            
  set(yaml_library_suffix "md")      
else()                               
  set(yaml_library_suffix "")        
endif()                       

target_link_libraries(dip libyaml-cpp${yaml_library_suffix})

add_subdirectory(test)