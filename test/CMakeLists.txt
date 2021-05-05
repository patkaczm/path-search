cmake_minimum_required(VERSION 3.14)
project(path-search-tests LANGUAGES CXX)

set(TEST_MAIN ${CMAKE_CURRENT_LIST_DIR}/main_test.cpp)

add_subdirectory(Graph)
add_subdirectory(Algorithm)
add_subdirectory(Backend)
