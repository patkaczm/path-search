#include "Algorithm/PathFinding/BreadthFirstSearch.hpp"

#include <queue>
#include <algorithm>

namespace algorithm
{

Algorithm::Path BreadthFirstSearch::operator()(const graph::Graph& graph, const graph::Vertex &start, const graph::Vertex &end) const
{
    auto prev = solve(graph, start);
    return reconstructPath(start, end, prev);
}

std::map<graph::Vertex, graph::Vertex> BreadthFirstSearch::solve(const graph::Graph& graph, const graph::Vertex &start) const
{
    using graph::Vertex;
    std::queue<Vertex> q;
    q.push(start);

    std::set<Vertex> visited;
    visited.insert(start);

    std::map<Vertex, Vertex> prev;

    while (!q.empty()) {
        auto node = q.front();
        q.pop();
        auto neighbours = graph.getNeighbours(node);

        for (const auto neighbour : neighbours) {
            if (!visited.contains(neighbour)) {
                q.push(neighbour);
                visited.insert(neighbour);
                prev[neighbour] = node;
                emit vertexVisited(neighbour);
            }
        }
    }
    return prev;
}

Algorithm::Path BreadthFirstSearch::reconstructPath(const graph::Vertex& start, const graph::Vertex& end, const std::map<graph::Vertex, graph::Vertex> &prev) const
{
    Path p{};
    for (auto at = end; prev.contains(at) || at == start; at = prev.at(at)){
        p.push_back(at);
        if (at == start) {
            break;
        }
    }
    std::reverse(p.begin(), p.end());
    if (p.begin()!= p.end() && *p.begin() == start) {
        return p;
    }
    return {};
}

}
