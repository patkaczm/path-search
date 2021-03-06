namespace graph {

template<typename... Args>
bool Graph::addVertexes(Args&&... args)
{
    static_assert ((std::is_constructible_v<Vertex, Args&&>&&...));
    return (add(std::forward<Args>(args)), ...);
}

template<typename... Args>
bool Graph::addEdges(Args&&... args)
{
    static_assert ((std::is_constructible_v<Edge, Args&&>&&...));
    return (add(std::forward<Args>(args)), ...);
}

}
