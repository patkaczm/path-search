#include <vector>
#include "Graph/Vertex.hpp"
#include "Graph/Graph.hpp"

namespace algorithm
{

using Path = std::vector<graph::Vertex>;

class BreadthFirstSearch
{
public:
    Path operator()(const graph::Graph& graph, const graph::Vertex& start, const graph::Vertex& end);
private:
    std::map<graph::Vertex, graph::Vertex> solve(const graph::Graph& graph, const graph::Vertex& start);
    Path reconstructPath(const graph::Vertex& start, const graph::Vertex& end, const std::map<graph::Vertex, graph::Vertex>& prev);
};

}
