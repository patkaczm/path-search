add_library(CellLib Cell.cpp)
target_include_directories(CellLib PRIVATE ${INCLUDE_DIR})

add_library(GridLib Grid.cpp)
target_include_directories(GridLib PRIVATE ${INCLUDE_DIR})
target_link_libraries(GridLib PRIVATE ${QtLib} CellLib)

add_library(BackendUtilsLib Utils.cpp)
target_include_directories(BackendUtilsLib PRIVATE ${INCLUDE_DIR})
target_link_libraries(BackendUtilsLib PRIVATE GridLib GraphLib ${QtLib})

add_library(MazeGeneratorLib MazeGenerator.cpp)
target_include_directories(MazeGeneratorLib PRIVATE ${INCLUDE_DIR})
target_link_libraries(MazeGeneratorLib PRIVATE ${QtLib} BackendUtilsLib GraphLib GridLib)

add_library(BackendLib Backend.cpp)
target_include_directories(BackendLib PRIVATE ${INCLUDE_DIR})
target_link_libraries(BackendLib PRIVATE ${QtLib}
                                         GraphLib
                                         BreadthFirstSearchLib
                                         DepthFirstSearchLib
                                         DijkstraLib
                                         CellLib
                                         GridLib
                                         AlgorithmListLib
                                         MazeGeneratorLib
                                         BackendUtilsLib
                                         IterativeBacktrackerLib)
