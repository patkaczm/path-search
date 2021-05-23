add_ut(NAME MazeGenerationUtils
       SOURCES UtilsTest.cpp
       DEPENDS GraphLib)


add_library(MazeGenerationAlgorithmStubLib MazeGenerationAlgorithmStub.cpp)
target_link_libraries(MazeGenerationAlgorithmStubLib PRIVATE ${QtLib} gtest gmock)
target_include_directories(MazeGenerationAlgorithmStubLib PRIVATE ${INCLUDE_DIR} ${TEST_INCLUDE_DIR})

add_ut(NAME IterativeBacktracker
       SOURCES IterativeBacktrackerTest.cpp
       DEPENDS ${QtLib})

