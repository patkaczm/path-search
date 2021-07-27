#include <gmock/gmock.h>

#include <optional>
#include "Utils/MockInstance.hpp"
#include "Grid/RectangleGrid.hpp"

namespace algorithm {
namespace mock {

class MazeGenerationAlgorithmMock : public utils::mocks::MockInstance<MazeGenerationAlgorithmMock>
{
public:
    MOCK_METHOD(graph::Graph, generateMaze, (grid::RectangleGrid& r, const std::optional<grid::Cell>& start));
};

}
}
