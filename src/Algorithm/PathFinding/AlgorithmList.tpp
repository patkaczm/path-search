namespace algorithm {

template<class T>
void AlgorithmList::registerAlgorithm(const std::string& name, std::unique_ptr<T>&& a)
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
