add_library(CellLib Cell.cpp)
target_include_directories(CellLib PRIVATE ${INCLUDE_DIR})

add_library(GridLib Grid.cpp)
target_include_directories(GridLib PRIVATE ${INCLUDE_DIR})
target_link_libraries(GridLib PRIVATE ${QtLib} CellLib)
