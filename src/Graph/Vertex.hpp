#pragma once

#include <cstdint>

namespace graph {

// Adjacency list graph
struct Vertex {
    //@todo in that phase assume that id is unique
    std::uint32_t id;
    bool operator<(const Vertex& rhs) const;
    bool operator==(const Vertex& rhs) const;
};

}
