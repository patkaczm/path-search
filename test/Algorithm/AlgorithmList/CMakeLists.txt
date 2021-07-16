#this is empty lib for test
#temporary solution because add_ut needs <NAME>Lib
add_library(AlgorithmListLib)

add_ut(NAME AlgorithmList
       SOURCES AlgorithmListTest.cpp
       DEPENDS Qt5::Core
       )
