cmake_minimum_required(VERSION 3.14)

add_library(BreadthFirstSearchLib BreadthFirstSearch.cpp)
target_include_directories(BreadthFirstSearchLib PRIVATE ${INCLUDE_DIR})
target_link_libraries(BreadthFirstSearchLib PRIVATE GraphLib Qt5::Core)

add_library(DepthFirstSearchLib DepthFirstSearch.cpp)
target_include_directories(DepthFirstSearchLib PRIVATE ${INCLUDE_DIR})
target_link_libraries(DepthFirstSearchLib PRIVATE GraphLib Qt5::Core)

add_library(DijkstraLib Dijkstra.cpp)
target_include_directories(DijkstraLib PRIVATE ${INCLUDE_DIR})
target_link_libraries(DijkstraLib PRIVATE GraphLib Qt5::Core)

add_library(AlgorithmListLib AlgorithmList.cpp)
target_include_directories(AlgorithmListLib PRIVATE ${INCLUDE_DIR})
target_link_libraries(AlgorithmListLib PRIVATE Qt5::Core)

#add_library(AlgorithmLib)
#target_link_libraries(AlgorithmLib INTERFACE BreadthFirstSearchLib Qt5::Core)
