cmake_minimum_required(VERSION 3.14)

add_executable(CellTest CellTest.cpp
                         ${TEST_MAIN})
target_link_libraries(CellTest PRIVATE
    gtest
    gmock
    CellLib)
target_include_directories(CellTest PRIVATE ${INCLUDE_DIR})
add_test(NAME CellTest COMMAND CellTest)

add_executable(GridTest GridTest.cpp
                         ${TEST_MAIN})
target_link_libraries(GridTest PRIVATE
    gtest
    gmock
    GridLib
    ${QtLib})
target_include_directories(GridTest PRIVATE ${INCLUDE_DIR})
add_test(NAME GridTest COMMAND GridTest)
