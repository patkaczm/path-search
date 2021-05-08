cmake_minimum_required(VERSION 3.14)

add_library(BreadthFirstSearchLib BreadthFirstSearch.cpp)
target_include_directories(BreadthFirstSearchLib PRIVATE ${INCLUDE_DIR})
target_link_libraries(BreadthFirstSearchLib PRIVATE GraphLib)

add_library(AlgorithmLib)
target_link_libraries(AlgorithmLib PUBLIC BreadthFirstSearchLib)
