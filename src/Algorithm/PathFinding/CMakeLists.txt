add_library(BreadthFirstSearchLib BreadthFirstSearch.cpp)
target_include_directories(BreadthFirstSearchLib PRIVATE ${INCLUDE_DIR})
target_link_libraries(BreadthFirstSearchLib PRIVATE GraphLib Qt5::Core)

add_library(DepthFirstSearchLib DepthFirstSearch.cpp)
target_include_directories(DepthFirstSearchLib PRIVATE ${INCLUDE_DIR})
target_link_libraries(DepthFirstSearchLib PRIVATE GraphLib Qt5::Core)

add_library(DijkstraLib Dijkstra.cpp)
target_include_directories(DijkstraLib PRIVATE ${INCLUDE_DIR})
target_link_libraries(DijkstraLib PRIVATE GraphLib Qt5::Core)
