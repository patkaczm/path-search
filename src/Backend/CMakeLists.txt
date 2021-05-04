cmake_minimum_required(VERSION 3.14)

add_library(BackendLib Backend.cpp)
target_include_directories(BackendLib PRIVATE ${INCLUDE_DIR})
target_link_libraries(BackendLib PRIVATE ${QtLib} GraphLib AlgorithmLib)
