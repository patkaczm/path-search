#include "Algorithm/PathFinding/Dijkstra.hpp"

#include <cstdint>
#include <limits>
#include <queue>
#include <set>

namespace algorithm
{

Algorithm::Path Dijkstra::findPath(const graph::Graph& graph, const graph::Vertex &start, const graph::Vertex &end) const
{
    auto prev = solve(graph, start);
    return reconstructPath(start, end, prev);
}

std::map<graph::Vertex, graph::Vertex> Dijkstra::solve(const graph::Graph& graph, const graph::Vertex& start) const {
    using distance = std::int32_t;
    auto vertexes = graph.getVertexes();
    std::map<graph::Vertex, distance> Q;
    std::map<graph::Vertex, graph::Vertex> prev;

    std::for_each(vertexes.begin(), vertexes.end(), [&Q](const decltype (vertexes)::value_type& v){
        Q[v] = std::numeric_limits<distance>::max();
    });

    Q[start] = 0;
    while(!Q.empty()) {
        auto u = *std::min_element(Q.begin(), Q.end(), [](const decltype (Q)::value_type& lhs, const decltype (Q)::value_type& rhs){
            return lhs.second < rhs.second;
        });
        for (const auto& neighbour : graph.getNeighbours(u.first)) {
            if (!Q.contains(neighbour)) {
                continue;
            }

            auto alt = Q[u.first] + /*length(u, v)*/ 1;
            if (alt < Q[neighbour]) {
                Q[neighbour] = alt;
                prev[neighbour] = u.first;
            }
            emit vertexVisited(neighbour);
        }
        Q.erase(u.first);
    }
    return prev;
}

Algorithm::Path Dijkstra::reconstructPath(const graph::Vertex &start, const graph::Vertex &end, const std::map<graph::Vertex, graph::Vertex> &prev) const
{
    //@todo add tests to this
    if (prev.empty() || start == end) {
        return {};
    }
    Path p;

    for (auto u = end; prev.contains(u); u=prev.at(u)) {
        p.emplace_back(u);
    }

    return p;
}

}
