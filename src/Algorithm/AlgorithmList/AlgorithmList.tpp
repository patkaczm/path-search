namespace algorithm {

template <class Algorithm>
Algorithm* const AlgorithmList<Algorithm>::getSelected() const
{
    if (nameAlgorithmMap.contains(selected)) {
        return nameAlgorithmMap.at(selected).get();
    }
    return nullptr;
}

template <class Algorithm>
std::vector<std::string> AlgorithmList<Algorithm>::getAlgorithmList() const
{
    std::vector<std::string> r;
    for(const auto& [key, _] : nameAlgorithmMap)
    {
        r.emplace_back(key);
    }

    return r;
}

template <class Algorithm>
void AlgorithmList<Algorithm>::selectAlgorithm(const std::string & name)
{
    if (not nameAlgorithmMap.contains(name)) {
        throw std::logic_error("Algorithm has not been registered");
    }
    selected = name;
}

template <class Algorithm>
template<class T>
void AlgorithmList<Algorithm>::registerAlgorithm(const std::string& name, std::unique_ptr<T>&& a)
{
    if(typeInfoNameMap.contains(typeid(a).name())) {
        throw std::logic_error("Element with given type already exists.");
    }
    if (nameAlgorithmMap.contains(name)) {
        throw std::logic_error("Element with given name already exists.");
    }
    nameAlgorithmMap.emplace(name, std::move(a));
    typeInfoNameMap.emplace(typeid(a).name(), name);

}
}
