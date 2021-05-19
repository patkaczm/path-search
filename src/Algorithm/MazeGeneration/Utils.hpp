#pragma once

#include <set>
#include "Graph/Vertex.hpp"
#include "Graph/Graph.hpp"

namespace algorithm {
namespace utils {

graph::Vertex getRandom(const graph::Graph::Neighbours& neighbours);
std::set<graph::Vertex> getUnvisited(const graph::Graph::Neighbours& neighbours, const std::set<graph::Vertex>& visited);

}
}
