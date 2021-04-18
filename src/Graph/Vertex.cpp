#include "Graph/Vertex.hpp"

namespace graph {

bool Vertex::operator<(const Vertex &rhs) const
{
    return id < rhs.id;
}

bool Vertex::operator==(const Vertex &rhs) const
{
    return id == rhs.id;
}

}
