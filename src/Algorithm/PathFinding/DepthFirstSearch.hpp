#include "Algorithm/PathFinding/Algorithm.hpp"

#include <QObject>

#include <vector>
#include "Graph/Vertex.hpp"
#include "Graph/Graph.hpp"

namespace algorithm
{

class DepthFirstSearch : public QObject, public Algorithm
{
    Q_OBJECT
    Q_INTERFACES(algorithm::Algorithm)
public:
    Path findPath(const graph::Graph& graph, const graph::Vertex& start, const graph::Vertex& end) const override;

signals:
    void vertexVisited(const graph::Vertex&) const;

private:
    void DFS(const graph::Vertex& v, const graph::Vertex& end, const graph::Graph& g, std::map<graph::Vertex, bool>& visited,
                                                                                          algorithm::Algorithm::Path& p, bool& found) const;
};

}
