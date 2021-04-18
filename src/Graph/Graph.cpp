#include "Graph/Graph.hpp"

namespace graph {

bool Graph::add(const Vertex& v)
{
    if(adjList.contains(v)) {
        return false;
    }
    adjList[v] = {};
    return true;
}

bool Graph::add(const Edge &e)
{
    if(!adjList.contains(e.a) || !adjList.contains(e.b))
    {
        throw VertexDoesNotExist{};
    }

    if(adjList.at(e.a).contains(e.b) && adjList.at(e.b).contains(e.a))
    {
        return false;
    } else if ((adjList.at(e.a).contains(e.b) && !adjList.at(e.b).contains(e.a)) ||
               (adjList.at(e.b).contains(e.a) && !adjList.at(e.a).contains(e.b))) {
        throw(std::logic_error{"This is bidirectional graph. This cannot happen"});
    }

    adjList.at(e.a).insert(e.b);
    adjList.at(e.b).insert(e.a);
    return true;
}


}
