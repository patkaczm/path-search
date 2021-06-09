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
    // This one does not work.
    const std::set<Direction> directions{Direction::Down, Direction::Up, Direction::Right, Direction::Left};
    for (std::uint32_t j = 0 ; j < mHeight; j++) {
        for (std::uint32_t i = 0 ; i < mWidth; i++) {
            std::cout << j << " " << i <<std::endl;
            for (const auto& direction : directions) {
                if (shouldCreateConnectionWithCell(direction, j, i)) {
                    createConnectionWithCell(direction, j, i);
                }
            }
        }
    }
}

bool RectangleGrid::shouldCreateConnectionWithCell(const RectangleGrid::Direction &d, std::uint32_t j, std::uint32_t i) const
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
        //@todo EmptyField seems to be superflavous here.
        ret.emplace(Cell(v.id, Cell::Type::EmptyField));
    }
    return ret;
}

std::vector<int> RectangleGrid::flat() const
{
    return {};
}

std::optional<Cell> RectangleGrid::getCell(std::uint32_t id) const
{
    auto vertexes = mGraph.getVertexes();
    auto found = std::find(vertexes.begin(), vertexes.end(), graph::Vertex{id});
    if (found != vertexes.end()) {
        //@todo EmptyField seems to be superflavous here.
        return Cell(id, Cell::Type::EmptyField);
    }
    return std::nullopt;
}

}
