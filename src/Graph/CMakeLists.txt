cmake_minimum_required(VERSION 3.14)

add_library(VertexLib Vertex.cpp)
target_include_directories(VertexLib PRIVATE ${INCLUDE_DIR})

add_library(GraphLib Graph.cpp)
target_include_directories(GraphLib PRIVATE ${INCLUDE_DIR})
target_link_libraries(GraphLib PRIVATE VertexLib)
