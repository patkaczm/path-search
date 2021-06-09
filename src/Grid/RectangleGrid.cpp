#include "Grid/RectangleGrid.hpp"
#include <iostream>
namespace grid {

RectangleGrid::RectangleGrid(std::uint32_t height, std::uint32_t width)
    : mHeight(height), mWidth(width)
{
    for (std::uint32_t j = 0 ; j < mHeight; j++) {
        for (std::uint32_t i = 0 ; i < mWidth; i++) {
            mGraph.add(graph::Vertex{j * mWidth + i});
        }
    }
    const std::set<Direction> directions{Direction::Down, Direction::Up, Direction::Right, Direction::Left};
    for (std::uint32_t j = 0 ; j < mHeight; j++) {
        for (std::uint32_t i = 0 ; i < mWidth; i++) {
            for (const auto& direction : directions) {
                if (canCreateConnectionWithCell(direction, j, i)) {
                    createConnectionWithCell(direction, j, i);
                }
            }
        }
    }
}

bool RectangleGrid::canCreateConnectionWithCell(const RectangleGrid::Direction &d, std::uint32_t j, std::uint32_t i) const
{
    switch (d) {
    case Direction::Right: {
        return i + 1 < mWidth - 1;
    }
    case Direction::Left: {
        return i > 0;
    }
    case Direction::Up: {
        return j > 0;
    }
    case Direction::Down: {
        return j + 1 < mHeight - 1;
    }
    }
    return false;
}

void RectangleGrid::createConnectionWithCell(const RectangleGrid::Direction &d, uint32_t j, uint32_t i)
{
    switch (d) {
    case Direction::Right: {
        mGraph.add(graph::Edge{graph::Vertex{j * mWidth + i}, graph::Vertex{j * mWidth + i + 1}});
        break;
    }
    case Direction::Left: {
        mGraph.add(graph::Edge{graph::Vertex{j * mWidth + i}, graph::Vertex{j * mWidth + i - 1}});
        break;
    }
    case Direction::Up: {
        mGraph.add(graph::Edge{graph::Vertex{j * mWidth + i}, graph::Vertex{(j - 1) * mWidth + i}});
        break;
    }
    case Direction::Down: {
        mGraph.add(graph::Edge{graph::Vertex{j * mWidth + i}, graph::Vertex{(j + 1) * mWidth + i}});
        break;
    }
    }
}

bool RectangleGrid::isAdjacent(const Cell &c1, const Cell &c2) const
{
        return (c2.id == c1.id + 1 || // right
                c2.id == c1.id - 1 || // left
                c2.id == c1.id - mWidth || // up
                c2.id == c1.id + mWidth // down
            );
}

std::uint32_t RectangleGrid::getCellWalls(const Cell &c) const
{
    std::uint32_t r{};
    for(const auto& neighbour : neighbours(c)) {
        if (neighbour.id == c.id + 1) { // right
            r |= 0b1;
        }
        else if (neighbour.id == c.id + mWidth) { // down
            r |= 0b10;
        } else if (neighbour.id == c.id - 1) {// left
            r |= 0b100;
        } else if (neighbour.id == c.id - mWidth) { // up
            r |= 0b1000;
        }
    }
    return r;
    // bit 0 means that there is no passage aka there is wall
}

Cell RectangleGrid::at(std::size_t j, std::size_t i) const
{
    auto cell = getCell(j * mWidth + i);
    if (cell) {
        return cell.value();
    }
    throw std::out_of_range{"RectangleGrid at out of the bounds at: [j: ." + std::to_string(j) + " i: " + std::to_string(i) + "]"};
}

std::pair<std::size_t, std::size_t> RectangleGrid::size() const
{
    return {mHeight, mWidth};
}

std::set<Cell> RectangleGrid::neighbours(const Cell &c) const
{
    auto neighbours = mGraph.getNeighbours(graph::Vertex{c.id});
    std::set<Cell> ret;
    for(const auto& v : neighbours) {
        ret.emplace(Cell(v.id));
    }
    return ret;
}

void RectangleGrid::addWall(const Cell &c1, const Cell &c2)
{
    if(isAdjacent(c1, c2)) {
        mGraph.remove(graph::Edge{graph::Vertex{c1.id}, graph::Vertex{c2.id}});
    }
}

void RectangleGrid::removeWall(const Cell &c1, const Cell &c2)
{
    if (isAdjacent(c1, c2)) {
        mGraph.add(graph::Edge{graph::Vertex{c1.id}, graph::Vertex{c2.id}});
    }
}

std::vector<int> RectangleGrid::flat() const
{
    std::vector<int> r(mHeight * mWidth, 0);

    for(std::uint32_t j = 0; j < mHeight; j++) {
        for(std::uint32_t i = 0; i < mWidth; i++) {
            auto id = j * mWidth + i;
            r.at(id) = getCellWalls(Cell(id));
        }
    }
    return r;
}


std::optional<Cell> RectangleGrid::getCell(std::uint32_t id) const
{
    auto vertexes = mGraph.getVertexes();
    auto found = std::find(vertexes.begin(), vertexes.end(), graph::Vertex{id});
    if (found != vertexes.end()) {
        return Cell(id);
    }
    return std::nullopt;
}

}
