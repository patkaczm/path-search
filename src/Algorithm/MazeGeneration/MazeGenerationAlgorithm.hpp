#pragma once

#include <QtPlugin>

#include "Graph/Vertex.hpp"
#include "Graph/Graph.hpp"

namespace algorithm {

class MazeGenerationAlgorithm {
public:
    virtual ~MazeGenerationAlgorithm() = default;
    virtual graph::Graph generateMaze(const graph::Graph& g, const graph::Vertex& start) = 0;
signals:
    virtual void wallRemoved(const graph::Vertex& a, const graph::Vertex& b, const graph::Edge& e) = 0;
};

}

Q_DECLARE_INTERFACE(algorithm::MazeGenerationAlgorithm, "MazeGenerationAlgorithm")
