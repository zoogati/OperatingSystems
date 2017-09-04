cmake_minimum_required(VERSION 3.6)
project(ShortestPath)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES check_file_permissions.c)
add_executable(check_file_permissions.c ${SOURCE_FILES})