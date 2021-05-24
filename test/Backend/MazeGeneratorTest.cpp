#include <gmock/gmock.h>
#include <memory>
#include "Backend/MazeGenerator.hpp"
#include "Algorithm/MazeGeneration/MazeGenerationAlgorithmStub.hpp"
#include "Algorithm/MazeGeneration/MazeGenerationAlgorithmMock.hpp"

using namespace ::testing;
namespace test {

TEST(MazeGenerator, generatesMaze)
{
    MazeGenerator mg(std::make_unique<algorithm::MazeGenerationAlgorithmStub>(), 7, 7);

    graph::Graph g;
    g.addVertexes(graph::Vertex{0}, graph::Vertex{1}, graph::Vertex{2},
                  graph::Vertex{3}, graph::Vertex{4}, graph::Vertex{5},
                  graph::Vertex{6}, graph::Vertex{7}, graph::Vertex{8});
    g.addEdges(graph::Edge{graph::Vertex{0}, graph::Vertex{1}},
               graph::Edge{graph::Vertex{0}, graph::Vertex{3}},
               graph::Edge{graph::Vertex{3}, graph::Vertex{4}},
               graph::Edge{graph::Vertex{4}, graph::Vertex{7}},
               graph::Edge{graph::Vertex{6}, graph::Vertex{7}},
               graph::Edge{graph::Vertex{7}, graph::Vertex{8}},
               graph::Edge{graph::Vertex{8}, graph::Vertex{5}},
               graph::Edge{graph::Vertex{5}, graph::Vertex{2}});
    EXPECT_CALL(algorithm::mock::MazeGenerationAlgorithmMock::instance(), generateMaze(_, _)).WillOnce(Return(g));

    auto maze = mg.generate();
    grid::Grid expectedMaze(7, 7);
    for(auto& row : expectedMaze.getRows()) {
        for(auto& cell : row) {
            cell.type = grid::Cell::Type::Obstacle;
        }
    }
    std::vector<std::pair<std::size_t, std::size_t>> coords {{1, 1}, {1, 2}, {1, 3}, {1, 5},
                                                            {2, 1}, {2, 5},
                                                            {3, 1}, {3, 2}, {3, 3}, {3, 5},
                                                            {4, 3}, {4, 5},
                                                            {5, 1}, {5, 2}, {5,3}, {5,4}, {5,5}};
    for (const auto&[i, j] : coords) {
        expectedMaze.getRows()[i][j].type = grid::Cell::Type::EmptyField;
    }
    for (int i = 0 ; i < expectedMaze.getRows().size(); i++) {
        for (int j = 0; j < expectedMaze.getRows()[i].size(); j++) {
            EXPECT_EQ(expectedMaze.getRows()[i][j].id, maze.maze.getRows()[i][j].id);
            EXPECT_EQ(expectedMaze.getRows()[i][j].type, maze.maze.getRows()[i][j].type);
        }
    }
}

TEST(MazeGenerator, collectsRemovedWallHistory)
{
    auto stub_up = std::make_unique<algorithm::MazeGenerationAlgorithmStub>();
    auto stub = (stub_up.get());
    MazeGenerator mg(std::move(stub_up), 7, 7);
    graph::Graph g;

    EXPECT_CALL(algorithm::mock::MazeGenerationAlgorithmMock::instance(), generateMaze(_, _)).WillOnce(Invoke([&](Unused, Unused){
        stub->emitWallRemoved(graph::Edge{graph::Vertex{0}, graph::Vertex{1}});
        return g;
    }));

    auto mazeData = mg.generate();
    EXPECT_THAT(mazeData.generationHistory, Contains(grid::Cell{8, grid::Cell::Type::EmptyField}));
    EXPECT_THAT(mazeData.generationHistory, Contains(grid::Cell{9, grid::Cell::Type::EmptyField}));
    EXPECT_THAT(mazeData.generationHistory, Contains(grid::Cell{10, grid::Cell::Type::EmptyField}));
}


}
