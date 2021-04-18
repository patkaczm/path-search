cmake_minimum_required(VERSION 3.14)

add_executable(GraphTest GraphTest.cpp
                         ${TEST_MAIN})
target_link_libraries(GraphTest PRIVATE
    gtest
    gmock
    GraphLib)
target_include_directories(GraphTest PRIVATE ${INCLUDE_DIR})
