cmake_minimum_required(VERSION 3.14)

add_library(BreadthFirstSearchLib BreadthFirstSearch.cpp)
target_include_directories(BreadthFirstSearchLib PRIVATE ${INCLUDE_DIR})
target_link_libraries(BreadthFirstSearchLib PRIVATE GraphLib Qt5::Core)

#add_library(AlgorithmLib)
#target_link_libraries(AlgorithmLib INTERFACE BreadthFirstSearchLib Qt5::Core)
