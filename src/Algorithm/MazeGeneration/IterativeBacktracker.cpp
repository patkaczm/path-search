#include "Algorithm/MazeGeneration/IterativeBacktracker.hpp"

#include <stack>
#include <set>

#include "Graph/Vertex.hpp"
#include "Graph/Graph.hpp"

#include "Algorithm/MazeGeneration/Utils.hpp"

namespace algorithm {

graph::Graph algorithm::IterativeBacktracker::generateMaze(const graph::Graph &g, const graph::Vertex& start)
{
    graph::Graph maze;
    for(const auto& v : g.getVertexes())
    {
        maze.add(v);
    }

    std::set<graph::Vertex> visited;
    std::stack<graph::Vertex> s;
    auto& current = start;
    visited.emplace(current);
    s.push(current);

    while(!s.empty()) {
        auto current = s.top();
        s.pop();
        auto unvisited = utils::getUnvisited(g.getNeighbours(current), visited);
        if (unvisited.size() > 0) {
            s.push(current);
            auto randomNeighbour = utils::getRandom(unvisited);
            //remove wall
            auto edge = graph::Edge{current, randomNeighbour};
            maze.add(edge);
            emit wallRemoved(edge);
            visited.emplace(randomNeighbour);
            s.push(randomNeighbour);
        }
    }
    return maze;
}

void IterativeBacktracker::generateMaze(grid::RectangleGrid &r, const std::optional<grid::Cell> &start) const
{
    auto startCell = start ? start.value() : r.at(0, 0);
    std::set<grid::Cell> visited;
    std::stack<grid::Cell> s;

    visited.emplace(startCell);
    s.push(startCell);

    while(!s.empty()) {
        auto current = s.top();
        s.pop();
        auto unvisited = utils::getUnvisited(r.adjacent(current), visited);
        if (unvisited.size() > 0) {
            s.push(current);
            auto randomNeighbour = utils::getRandom(unvisited);
            r.removeWall(current, randomNeighbour);
            //emit wallRemoved
            visited.emplace(randomNeighbour);
            s.push(randomNeighbour);
        }
    }
}

}

