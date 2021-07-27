#include "Algorithm/MazeGeneration/BinaryTree.hpp"

#include <stack>
#include <set>

#include "Algorithm/MazeGeneration/Utils.hpp"

#include "QDebug"

namespace algorithm {

//assume that this is only possible for rectangleGrid
void BinaryTree::generateMaze(grid::RectangleGrid &r, const std::optional<grid::Cell> &) const
{

    std::stack<grid::Cell> unvisited{};

    auto gridSize = r.size();

    const auto isNorthCell = [width =  gridSize.width](const auto& lhs, const auto& rhs){return lhs.id == rhs.id - width;};
    const auto isRightCell = [](const auto& lhs, const auto& rhs){return lhs.id == rhs.id + 1;};

    //consider adding getCells method to Grid
    for (std::size_t row = 0; row < gridSize.height; row++) {
        for (std::size_t col = 0; col < gridSize.width; col++) {
            unvisited.push(r.at(row, col));
        }
    }

    while(!unvisited.empty())
    {
        auto visited = unvisited.top();
        //choose which one wall needs to be erased
        std::set<grid::Cell> wallsToRemove;
        for(const auto& cell : r.adjacent(visited))
        {
            if (isNorthCell(cell, visited)
                || isRightCell(cell, visited)
                ) {
                wallsToRemove.insert(cell);
            }
        }
        if (!wallsToRemove.empty()) {
            auto ra = utils::getRandom(wallsToRemove);
            r.removeWall(visited, ra);
        }
        unvisited.pop();
    }
}

}

