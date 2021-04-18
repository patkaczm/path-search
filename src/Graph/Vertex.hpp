#pragma once

namespace graph {

// Adjacency list graph
struct Vertex {
    //@todo in that phase assume that id is unique
    int id;
    bool operator<(const Vertex& rhs) const;
    bool operator==(const Vertex& rhs) const;
};

}
