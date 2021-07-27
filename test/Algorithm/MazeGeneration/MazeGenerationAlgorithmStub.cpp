#include "Algorithm/MazeGeneration/MazeGenerationAlgorithmStub.hpp"

#include "Algorithm/MazeGeneration/MazeGenerationAlgorithmMock.hpp"

namespace algorithm {

void MazeGenerationAlgorithmStub::generateMaze(grid::RectangleGrid &r, const std::optional<grid::Cell> &start) const
{
    algorithm::mock::MazeGenerationAlgorithmMock::instance().generateMaze(r, start);
}

void MazeGenerationAlgorithmStub::emitWallRemoved(const graph::Edge &e)
{
    emit wallRemoved(e);
}

}
