#pragma once

#include<map>
#include<vector>

namespace graph {

// Adjacency list graph
struct Vertex {
    //@todo in that phase assume that id is unique
    int id;
};

struct Edge {
    Vertex a;
    Vertex b;
};

class Graph {
public:
    using AdjacencyList = std::map<Vertex, std::vector<Vertex>>;

    bool add(const Vertex& v);
    bool add(const Edge& e);

    bool isAdjacent(const Vertex& lhs, const Vertex& rhs);

private:
    AdjacencyList adjList;

};

}
