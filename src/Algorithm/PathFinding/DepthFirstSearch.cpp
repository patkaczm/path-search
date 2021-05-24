#include "Algorithm/PathFinding/DepthFirstSearch.hpp"

namespace algorithm
{

namespace {

}

Algorithm::Path DepthFirstSearch::findPath(const graph::Graph& graph, const graph::Vertex &start, const graph::Vertex &end) const
{
    auto vertexes = graph.getVertexes();
    std::map<graph::Vertex, bool> visited;
    std::for_each(vertexes.begin(), vertexes.end(), [&](const graph::Vertex& v){
        visited.emplace(v, false);
    });

    algorithm::Algorithm::Path path;
    bool found = false;
    DFS(start, end, graph, visited, path, found);

    if (found) {
        return path;
    }
    return {};
}

void DepthFirstSearch::DFS(const graph::Vertex& v, const graph::Vertex& end, const graph::Graph& g, std::map<graph::Vertex, bool>& visited,
                           algorithm::Algorithm::Path& p, bool& found) const {
    visited[v]=true;
    emit vertexVisited(v);
    if (!found) {
        p.push_back(v);
    }
    if (v == end) {
        found = true;
    }
    for (const auto& ve : g.getNeighbours(v)) {
        if (!visited[ve]) {
            DFS(ve, end, g, visited, p, found);
        }
    }
}


}
