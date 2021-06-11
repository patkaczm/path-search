#pragma once

#include <QtPlugin>

#include <optional>

#include "Graph/Vertex.hpp"
#include "Graph/Graph.hpp"
#include "Grid/RectangleGrid.hpp"

namespace algorithm {

class MazeGenerationAlgorithm {
public:
    virtual ~MazeGenerationAlgorithm() = default;
    virtual graph::Graph generateMaze(const graph::Graph& g, const graph::Vertex& start) = 0;
    virtual void generateMaze(grid::RectangleGrid& r, const std::optional<grid::Cell>& start = std::nullopt) const = 0;
signals:
    virtual void wallRemoved(const graph::Edge& e) = 0;
};

}

Q_DECLARE_INTERFACE(algorithm::MazeGenerationAlgorithm, "MazeGenerationAlgorithm")
