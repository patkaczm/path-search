#include "Algorithm/PathFinding/AlgorithmList.hpp"

namespace algorithm {

const Algorithm* AlgorithmList::getSelected() const
{
    if (nameAlgorithmMap.contains(selected)) {
        return nameAlgorithmMap.at(selected).get();
    }
    return nullptr;
}

std::vector<std::string> AlgorithmList::getAlgorithmList() const
{
    std::vector<std::string> r;
    for(const auto& [key, _] : nameAlgorithmMap)
    {
        r.emplace_back(key);
    }

    return r;
}

void AlgorithmList::selectAlgorithm(const std::string & name)
{
    if (not nameAlgorithmMap.contains(name)) {
        throw std::logic_error("Algorithm has not been registered");
    }
    selected = name;
}

}
