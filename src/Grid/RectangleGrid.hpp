#pragma once

#include "Grid/IGrid.hpp"

#include <set>
#include <vector>
#include <cstdint>
#include <optional>
#include "Graph/Graph.hpp"

namespace grid {

class RectangleGrid : public IGrid {
public:
    RectangleGrid(std::uint32_t height, std::uint32_t width);
    //explicit RectangleGrid(const graph::Graph& g);

    Cell at(std::size_t j, std::size_t i) const override;
    std::pair<std::size_t, std::size_t> size() const override;
    std::set<Cell> adjacent(const Cell& c) const override;

    void addWall(const Cell& c1, const Cell& c2) /*override*/;
    void removeWall(const Cell& c1, const Cell& c2) /*override*/;
    bool areConnected(const Cell& c1, const Cell& c2) /*override*/;

    //graph::Graph graph() const override;
    std::vector<int> flat() const override;

private:
    enum class Direction {
        Right,
        Left,
        Up,
        Down
    };
    bool canCreateConnectionWithCell(const Direction& d, std::uint32_t j, std::uint32_t i) const;
    void createConnectionWithCell(const Direction&d, std::uint32_t j, std::uint32_t  i);
    bool isAdjacent(const Cell& c1, const Cell& c2) const;
    std::uint32_t  getCellWalls(const Cell& c) const;
    std::optional<Cell> getCell(std::uint32_t id) const;

    graph::Graph mGraph;
    std::uint32_t mHeight;
    std::uint32_t mWidth;
    //graph or/and what?
};

}
