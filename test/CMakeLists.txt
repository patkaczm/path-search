cmake_minimum_required(VERSION 3.14)
project(path-search-tests LANGUAGES CXX)

set(TEST_MAIN ${CMAKE_CURRENT_LIST_DIR}/main_test.cpp)

add_executable(Test main_test.cpp)

target_link_libraries(Test PRIVATE gtest)

add_subdirectory(Graph)
