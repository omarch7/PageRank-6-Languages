cmake_minimum_required(VERSION 3.5)
project(PageRank)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

set(SOURCE_FILES main.cpp BasicGraph.h BasicGraph.cpp)
add_executable(PageRank ${SOURCE_FILES})