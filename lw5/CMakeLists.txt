cmake_minimum_required(VERSION 3.30)
project(lw5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O3 -Wall -Wextra -Wpedantic")

include_directories(include)

add_library(FileSystem SHARED
        src/memory_manager.cc
        src/file_system.cc)

enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include(GoogleTest)

add_executable(memory_manager_tests tests/memory_manager_tests.cc)
target_link_libraries(memory_manager_tests FileSystem GTest::GTest GTest::Main)
gtest_discover_tests(memory_manager_tests)

add_executable(file_system_tests tests/file_system_tests.cc)
target_link_libraries(file_system_tests FileSystem GTest::GTest GTest::Main)
gtest_discover_tests(file_system_tests)