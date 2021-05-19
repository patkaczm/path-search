#pragma once

#include "Graph/Graph.hpp"

namespace algorithm {

class IterativeBacktracker {
public:
    graph::Graph generateMaze(const graph::Graph& g, const graph::Vertex& start);

};

}
