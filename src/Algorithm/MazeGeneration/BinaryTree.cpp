#include "Algorithm/MazeGeneration/BinaryTree.hpp"

#include <stack>
#include <set>

#include "Algorithm/MazeGeneration/Utils.hpp"

#include "QDebug"

namespace algorithm {

//assume that this is only possible for rectangleGrid
void BinaryTree::generateMaze(grid::RectangleGrid &r, const std::optional<grid::Cell> &) const
{
    std::stack<grid::Cell> unvisited;

    auto gridSize = r.size();
    //consider adding getCells method to Grid
    for (std::size_t i = 0; i < gridSize.height * gridSize.width; i++) {
        unvisited.push(grid::Cell(i));
    }

    while(!unvisited.empty())
    {
        auto cell = unvisited.top();
        //choose which one wall needs to be erased
        std::set<grid::Cell> wallsToRemove;
        for(const auto& c : r.adjacent(cell))
        {
            if (c.id == cell.id - gridSize.width // upper | north
                || c.id == cell.id + 1 // right
                ) {
                wallsToRemove.insert(c);
            }
        }
        if (wallsToRemove.size() > 0) {
            auto ra = utils::getRandom(wallsToRemove);
            r.removeWall(cell, ra);
            qDebug() << "Remove: " << cell.id << " : " << ra.id;
        }
        qDebug() << "Pop: " << cell.id;
        unvisited.pop();
    }
    qDebug() << "Done";
}

}

