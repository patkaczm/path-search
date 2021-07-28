add_library(MazeGenerationUtilsLib Utils.cpp)
target_include_directories(MazeGenerationUtilsLib PRIVATE ${INCLUDE_DIR})
target_link_libraries(MazeGenerationUtilsLib PRIVATE GraphLib)

add_library(IterativeBacktrackerLib IterativeBacktracker.cpp)
target_include_directories(IterativeBacktrackerLib PRIVATE ${INCLUDE_DIR})
target_link_libraries(IterativeBacktrackerLib PRIVATE GraphLib MazeGenerationUtilsLib Qt5::Core)

add_library(BinaryTreeLib BinaryTree.cpp)
target_include_directories(BinaryTreeLib PRIVATE ${INCLUDE_DIR})
target_link_libraries(BinaryTreeLib PRIVATE GraphLib MazeGenerationUtilsLib Qt5::Core)

add_library(SidewinderLib Sidewinder.cpp)
target_include_directories(SidewinderLib PRIVATE ${INCLUDE_DIR})
target_link_libraries(SidewinderLib PRIVATE GraphLib MazeGenerationUtilsLib Qt5::Core)
