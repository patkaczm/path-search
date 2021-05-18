#pragma once

#include <QtPlugin>

#include <vector>

#include "Graph/Vertex.hpp"
#include "Graph/Graph.hpp"

namespace algorithm {

class Algorithm {
public:
    using Path = std::vector<graph::Vertex>;
    virtual Path operator()(const graph::Graph& graph, const graph::Vertex& start, const graph::Vertex& end) const = 0;
    virtual ~Algorithm() = default;
signals:
    virtual void vertexVisited(const graph::Vertex&) const = 0;
};

}

Q_DECLARE_INTERFACE(algorithm::Algorithm, "Algorithm")
