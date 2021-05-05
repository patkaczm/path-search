cmake_minimum_required(VERSION 3.14)

add_executable(CellTest CellTest.cpp
                         ${TEST_MAIN})
target_link_libraries(CellTest PRIVATE
    gtest
    gmock
    CellLib)
target_include_directories(CellTest PRIVATE ${INCLUDE_DIR})
