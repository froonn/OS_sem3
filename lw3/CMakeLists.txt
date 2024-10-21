cmake_minimum_required(VERSION 3.20)
project(lw3)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)


add_executable(lw3_OS main.c)
target_link_libraries(lw3_OS m)
