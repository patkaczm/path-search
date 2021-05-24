add_ut(NAME Cell
       SOURCES CellTest.cpp)

add_ut(NAME Grid
      SOURCES GridTest.cpp
      DEPENDS ${QtLib})

  add_ut(NAME MazeGenerator
        SOURCES MazeGeneratorTest.cpp
        DEPENDS ${QtLib} MazeGenerationAlgorithmStubLib)

    add_ut(NAME BackendUtils
            SOURCES UtilsTest.cpp
            DEPENDS GraphLib GridLib ${QtLib})
