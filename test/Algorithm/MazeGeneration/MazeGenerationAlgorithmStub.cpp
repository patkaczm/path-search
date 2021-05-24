#include "Algorithm/MazeGeneration/MazeGenerationAlgorithmStub.hpp"

#include "Algorithm/MazeGeneration/MazeGenerationAlgorithmMock.hpp"

namespace algorithm {

graph::Graph algorithm::MazeGenerationAlgorithmStub::generateMaze(const graph::Graph &g, const graph::Vertex &start)
{
    return algorithm::mock::MazeGenerationAlgorithmMock::instance().generateMaze(g, start);
}

void MazeGenerationAlgorithmStub::emitWallRemoved(const graph::Edge &e)
{
    emit wallRemoved(e);
}

}
