cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(ray-tracer CXX)

file(GLOB_RECURSE SOURCE_FILES ./Source/*.cpp)

add_executable(ray-tracer ${SOURCE_FILES})
target_include_directories(ray-tracer PUBLIC ./Source)

add_custom_command(
	TARGET ray-tracer 
	POST_BUILD 
	COMMAND ray-tracer > image.ppm && code image.ppm
)
