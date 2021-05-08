cmake_minimum_required(VERSION 3.14)

add_executable(BreadthFirstSearchTest BreadthFirstSearchTest.cpp
                         ${TEST_MAIN})
target_link_libraries(BreadthFirstSearchTest PRIVATE
    gtest
    gmock
    GraphLib
    AlgorithmLib)
target_include_directories(BreadthFirstSearchTest PRIVATE ${INCLUDE_DIR})
add_test(NAME BreadthFirstSearchTest COMMAND BreadthFirstSearchTest)
