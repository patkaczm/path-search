#include "Algorithm/MazeGeneration/Utils.hpp"

#include <random>
#include <algorithm>

namespace algorithm {
namespace utils {

graph::Vertex getRandom(const graph::Graph::Neighbours& neighbours) {
    std::random_device seeder;
    std::mt19937 engine(seeder());
    std::uniform_int_distribution<std::size_t> dist(0, neighbours.size() - 1);
    auto it = neighbours.begin();
    std::advance(it, dist(engine));
    return *it;
}

std::set<graph::Vertex> getUnvisited(const graph::Graph::Neighbours& neighbours, const std::set<graph::Vertex>& visited)
{
    std::set<graph::Vertex> unvisited;
    std::set_difference(neighbours.begin(), neighbours.end(),
                        visited.begin(), visited.end(), std::inserter(unvisited, unvisited.begin()));

    return unvisited;
}

}
}
