#pragma once

#include <QtPlugin>

#include <optional>

#include "Graph/Vertex.hpp"
#include "Graph/Graph.hpp"
#include "Grid/RectangleGrid.hpp"

namespace algorithm {

class MazeGeneration {
public:
    virtual ~MazeGeneration() = default;
    virtual void generateMaze(grid::RectangleGrid& r, const std::optional<grid::Cell>& start = std::nullopt) const = 0;
signals:
    virtual void wallRemoved(const graph::Edge& e) = 0;
};

}

Q_DECLARE_INTERFACE(algorithm::MazeGeneration, "MazeGeneration")
