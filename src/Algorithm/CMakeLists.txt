cmake_minimum_required(VERSION 3.14)

add_library(AlgorithmLib BreadthFirstSearch.cpp)
target_include_directories(AlgorithmLib PRIVATE ${INCLUDE_DIR})
target_link_libraries(AlgorithmLib PRIVATE GraphLib)
