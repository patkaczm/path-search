#include "Algorithm/Algorithm.hpp"

#include <QObject>

#include <vector>
#include "Graph/Vertex.hpp"
#include "Graph/Graph.hpp"

namespace algorithm
{

class Dijkstra : public QObject, public Algorithm
{
    Q_OBJECT
    Q_INTERFACES(algorithm::Algorithm)
public:
    Path operator()(const graph::Graph& graph, const graph::Vertex& start, const graph::Vertex& end) const override;

signals:
    void vertexVisited(const graph::Vertex&) const;

private:
    std::map<graph::Vertex, graph::Vertex> solve(const graph::Graph& graph, const graph::Vertex& start) const;
    Path reconstructPath(const graph::Vertex& start, const graph::Vertex& end, const std::map<graph::Vertex, graph::Vertex>& prev) const;

};

}
