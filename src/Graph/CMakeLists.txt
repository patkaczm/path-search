cmake_minimum_required(VERSION 3.14)

add_library(GraphLib Graph.cpp)
target_include_directories(GraphLib PRIVATE ${INCLUDE_DIR})
