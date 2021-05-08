cmake_minimum_required(VERSION 3.14)

add_ut(NAME BreadthFirstSearch
       SOURCES BreadthFirstSearchTest.cpp
       DEPENDS GraphLib Qt5::Core)
