cmake_minimum_required (VERSION 3.1)

project (dip-tests)

##################################
# Download and install GoogleTest

include(ExternalProject)
set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)
ExternalProject_Add(googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG "release-1.8.0"
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION} -Dgtest_force_shared_crt=ON
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/googletest/
)

ExternalProject_Get_Property(googletest source_dir binary_dir)

include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

add_executable(run_test ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
add_dependencies(run_test googletest)
target_link_libraries(run_test gtest gtest_main)

enable_testing()
add_test(NAME    run_test
         COMMAND run_test)