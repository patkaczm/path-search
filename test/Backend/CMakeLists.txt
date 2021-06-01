  add_ut(NAME MazeGenerator
        SOURCES MazeGeneratorTest.cpp
        DEPENDS ${QtLib} MazeGenerationAlgorithmStubLib)

    add_ut(NAME BackendUtils
            SOURCES UtilsTest.cpp
            DEPENDS GraphLib GridLib ${QtLib})
