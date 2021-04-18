// Adjacency list graph
#pragma once

#include <map>
#include <set>
#include <type_traits>

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
    using Neighbours = std::set<Vertex>;
    using AdjacencyList = std::map<Vertex, Neighbours>;

    template<typename... Args>
    bool addVertexes(Args&&... args);

    template<typename... Args>
    bool addEdges(Args&&... args);

    bool add(const Vertex& v);
    bool add(const Edge& e);

    Neighbours getNeighbours(const Vertex& v) const;

private:
    AdjacencyList adjList;

};

}

#include "Graph/Graph.tpp"
