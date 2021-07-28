#include "Algorithm/MazeGeneration/Sidewinder.hpp"

#include <vector>
#include <set>

#include "Algorithm/MazeGeneration/Utils.hpp"

#include "QDebug"

namespace algorithm {

//assume that this is only possible for rectangleGrid
void Sidewinder::generateMaze(grid::RectangleGrid &r, const std::optional<grid::Cell> &) const
{

    std::set<grid::Cell> currentChunk{};

    auto gridSize = r.size();

    auto isNorthCell = [width =  gridSize.width](const auto& from, const auto& to){return from.id == to.id + width;};
    auto isRightCell = [](const auto& lhs, const auto& rhs){return lhs.id == rhs.id + 1;};

    auto getRightNeighbour = [isRightCell](const auto& neighbours, const auto& cell) {
        return *std::find_if(begin(neighbours), end(neighbours), [&](const auto& c){
            return isRightCell(c, cell);
        });
    };

    auto getNorthNeighbour = [isNorthCell](const auto& neighbours, const auto& cell) {
        return *std::find_if(begin(neighbours), end(neighbours), [&](const auto& c){
            return isNorthCell(cell, c);
        });
    };

    auto a1 = [&r, getRightNeighbour](const auto& currentCell){
        r.removeWall(currentCell, getRightNeighbour(r.adjacent(currentCell), currentCell));
    };

    auto a2 = [&currentChunk, &r, getNorthNeighbour](const auto& currentCell){
        auto randCell = utils::getRandom(currentChunk);
        auto northCell = getNorthNeighbour(r.adjacent(randCell), randCell);
        r.removeWall(randCell, northCell);
        currentChunk.clear();
    };

    for (std::size_t row = gridSize.height; row > 0; row --)
    {
        for (std::size_t col = 0; col < gridSize.width; col++)
        {
            std::vector<std::function<void(const grid::Cell& currentCell)>> possibleActions;
            currentChunk.insert(r.at(row - 1, col));
            if (col != gridSize.width - 1)
            {
                possibleActions.push_back(a1);
            }
            if (row - 1 > 0)
            {
                possibleActions.push_back(a2);
            }
            if (!possibleActions.empty()) {
                utils::getRandom(possibleActions)(r.at(row - 1, col));
            }
        }
    }

}

}

