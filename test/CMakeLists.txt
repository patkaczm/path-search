cmake_minimum_required(VERSION 3.14)
project(path-search-tests LANGUAGES CXX)

set(TEST_MAIN ${CMAKE_CURRENT_LIST_DIR}/main_test.cpp)

include(${CMAKE_BASE_LIST_DIR}/cmake/add_ut.cmake)

set_property(GLOBAL PROPERTY ALL_TESTS_LIST)

add_subdirectory(Graph)
add_subdirectory(Grid)
add_subdirectory(Algorithm)
add_subdirectory(Backend)

get_property(ALL_TESTS_LIST GLOBAL PROPERTY ALL_TESTS_LIST)

add_custom_target(all_tests
    DEPENDS
    ${ALL_TESTS_LIST}
    COMMAND ctest)
