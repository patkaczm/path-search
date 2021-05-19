#include "Algorithm/MazeGeneration/IterativeBacktracker.hpp"

#include <algorithm>
#include <stack>
#include <random>
#include <set>

#include "Graph/Vertex.hpp"
#include "Graph/Graph.hpp"

namespace algorithm {

namespace {
graph::Vertex getRandomNeighbour(const graph::Graph::Neighbours& neighbours) {
    std::random_device seeder;
    std::mt19937 engine(seeder());
    std::uniform_int_distribution<std::size_t> dist(0, neighbours.size() - 1);
    auto it = neighbours.begin();
    std::advance(it, dist(engine));
    return *it;
}

std::set<graph::Vertex> getUnvisited(const graph::Graph::Neighbours& neighbours, const std::map<graph::Vertex, bool>& visited)
{
    std::set<graph::Vertex> unvisited;
    std::for_each(neighbours.begin(), neighbours.end(), [&visited, &unvisited](const graph::Vertex& v){
        if (not visited.at(v)) {
            unvisited.emplace(v);
        }
    });
    return unvisited;
}
}

graph::Graph algorithm::IterativeBacktracker::generateMaze(const graph::Graph &g, const graph::Vertex& start)
{
    graph::Graph maze;
    auto mazeVertexes = g.getVertexes();
    std::map<graph::Vertex, bool> visited;
    std::for_each(mazeVertexes.begin(), mazeVertexes.end(), [&maze, &visited](auto& v){
        maze.add(v);
        visited.emplace(v, false);
    });

    std::stack<graph::Vertex> s;
    auto& current = start;
    visited[graph::Vertex{static_cast<std::uint32_t>(current.id)}] = true;
    s.push(graph::Vertex{static_cast<std::uint32_t>(current.id)});

    while(!s.empty()) {
        auto current = s.top();
        s.pop();
        auto unvisited = getUnvisited(g.getNeighbours(graph::Vertex{current.id}), visited);
        if (unvisited.size() > 0) {
            s.push(current);
            auto randomNeighbour = getRandomNeighbour(unvisited);
            //remove wall
            maze.add(graph::Edge{current, randomNeighbour});
            visited[randomNeighbour] = true;
            s.push(randomNeighbour);
        }
    }
    return maze;
}

}

