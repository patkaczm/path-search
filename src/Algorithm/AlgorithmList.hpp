#pragma once

#include <map>
#include <memory>
#include <vector>
#include <typeinfo>
#include "Algorithm/Algorithm.hpp"

namespace algorithm {

class AlgorithmList {
public:
    const Algorithm* getSelected() const;
    std::vector<std::string> getAlgorithmList() const;
    void selectAlgorithm(const std::string&);

    template<class T>
    void registerAlgorithm(const std::string& name, std::unique_ptr<T>&& a);

private:
    std::map<std::string, std::unique_ptr<Algorithm>> nameAlgorithmMap;
    std::map<std::string, std::string > typeInfoNameMap;

    std::string selected;
};

}
#include "Algorithm/AlgorithmList.tpp"
