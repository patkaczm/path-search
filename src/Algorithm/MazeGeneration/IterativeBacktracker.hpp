#pragma once

#include <QObject>

#include "Graph/Graph.hpp"

namespace algorithm {

class IterativeBacktracker : public QObject {
    Q_OBJECT

public:
    graph::Graph generateMaze(const graph::Graph& g, const graph::Vertex& start);

signals:
    void wallRemoved(const graph::Vertex& a, const graph::Vertex& b, const graph::Edge& e);
};

}
