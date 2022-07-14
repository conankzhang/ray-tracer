cmake_minimum_required(VERSION 3.17)
project(ray-tracer CXX)
set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)

add_executable(ray-tracer ${SOURCE_FILES})

