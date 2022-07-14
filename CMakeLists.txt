cmake_minimum_required(VERSION 3.17)
project(ray-tracer CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_FILES main.cpp)

add_executable(ray-tracer ${SOURCE_FILES})

add_custom_command(
	TARGET ray-tracer 
	POST_BUILD 
	COMMAND ray-tracer > image.ppm 
)
