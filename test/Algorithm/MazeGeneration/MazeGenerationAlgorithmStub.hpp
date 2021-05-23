#pragma once

#include <QObject>

#include "Graph/Graph.hpp"
#include "Algorithm/MazeGeneration/MazeGenerationAlgorithm.hpp"

namespace algorithm {

class MazeGenerationAlgorithmStub : public QObject , public MazeGenerationAlgorithm {
    Q_OBJECT
    Q_INTERFACES(algorithm::MazeGenerationAlgorithm)
public:
    graph::Graph generateMaze(const graph::Graph& g, const graph::Vertex& start) override;

signals:
    void wallRemoved(const graph::Vertex& a, const graph::Vertex& b, const graph::Edge& e);
};

}
