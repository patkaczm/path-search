// Adjacency list graph
#pragma once

#include <map>
#include <set>

#include "Graph/Vertex.hpp"

namespace graph {

struct VertexDoesNotExist : public std::exception
{};

struct Edge {
    Vertex a;
    Vertex b;
};

class Graph {
public:
    using AdjacencyList = std::map<Vertex, std::set<Vertex>>;

    bool add(const Vertex& v);
    bool add(const Edge& e);

    bool isAdjacent(const Vertex& lhs, const Vertex& rhs);

private:
    AdjacencyList adjList;

};

}
