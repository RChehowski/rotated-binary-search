cmake_minimum_required(VERSION 3.10)
project(rot_binary_search)

add_definitions(-DENABLE_LOGGING=1)

set(CMAKE_CXX_STANDARD 11)

add_executable(rot_binary_search main.cpp)