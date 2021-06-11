#include "Algorithm/MazeGeneration/MazeGenerationAlgorithmStub.hpp"

#include "Algorithm/MazeGeneration/MazeGenerationAlgorithmMock.hpp"

namespace algorithm {

graph::Graph algorithm::MazeGenerationAlgorithmStub::generateMaze(const graph::Graph &g, const graph::Vertex &start)
{
    return algorithm::mock::MazeGenerationAlgorithmMock::instance().generateMaze(g, start);
}

void MazeGenerationAlgorithmStub::generateMaze(grid::RectangleGrid &r, const std::optional<grid::Cell> &start) const
{

}

void MazeGenerationAlgorithmStub::emitWallRemoved(const graph::Edge &e)
{
    emit wallRemoved(e);
}

}
