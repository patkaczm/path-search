add_ut(NAME Cell
       SOURCES CellTest.cpp)

add_ut(NAME Grid
      SOURCES GridTest.cpp
      DEPENDS ${QtLib})

add_ut(NAME RectangleGrid
    SOURCES RectangleGridTest.cpp
)
