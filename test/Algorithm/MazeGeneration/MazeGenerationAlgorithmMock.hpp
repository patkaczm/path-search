#include <gmock/gmock.h>

#include "Utils/MockInstance.hpp"
#include "Graph/Graph.hpp"
#include "Graph/Vertex.hpp"

namespace algorithm {
namespace mock {

class MazeGenerationAlgorithmMock : public utils::mocks::MockInstance<MazeGenerationAlgorithmMock>
{
public:
    MOCK_METHOD(graph::Graph, generateMaze, (const graph::Graph& g, const graph::Vertex& start));
};

}
}
