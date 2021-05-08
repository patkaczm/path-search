#pragma once

#include <map>
#include <memory>
#include "Algorithm/Algorithm.hpp"

namespace algorithm {

class AlgorithmList {
public:
    static std::unique_ptr<Algorithm> getSelected();
    static void selectAlgorithm(const std::string&);
    static void registerAlgorithm(std::unique_ptr<Algorithm> a);

private:
    static std::map<std::string, std::unique_ptr<Algorithm>> registeredAlgorithmList;
    static std::unique_ptr<Algorithm> selected;
};

}
