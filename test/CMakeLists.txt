cmake_minimum_required(VERSION 3.14)
project(path-search-tests LANGUAGES CXX)

set(TEST_MAIN ${CMAKE_CURRENT_LIST_DIR}/main_test.cpp)

set(ALL_SOURCES "")
include(${CMAKE_BASE_LIST_DIR}/cmake/add_ut.cmake)

add_subdirectory(Graph)
add_subdirectory(Algorithm)
add_subdirectory(Backend)

list(APPEND ALL_SOURCES "S")
message(INFO ${ALL_SOURCES})
