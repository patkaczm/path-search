#pragma once

#include <set>
#include <random>
#include <algorithm>

namespace algorithm {
namespace utils {

template <class T>
T getRandom(const std::set<T>& s)
{
    std::random_device seeder;
    std::mt19937 engine(seeder());
    std::uniform_int_distribution<std::size_t> dist(0, s.size() - 1);
    auto it = s.begin();
    std::advance(it, dist(engine));
    return *it;
}

template <class T>
std::set<T> getUnvisited(const std::set<T>& neighbours, const std::set<T>& visited)
{
    std::set<T> unvisited;
    std::set_difference(neighbours.begin(), neighbours.end(),
                        visited.begin(), visited.end(), std::inserter(unvisited, unvisited.begin()));
    return unvisited;
}

}
}
