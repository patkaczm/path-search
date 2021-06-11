#pragma once

#include <QObject>

#include "Graph/Graph.hpp"
#include "Grid/RectangleGrid.hpp"

#include "Algorithm/MazeGeneration/MazeGenerationAlgorithm.hpp"

namespace algorithm {

class IterativeBacktracker : public QObject , public MazeGenerationAlgorithm {
    Q_OBJECT
    Q_INTERFACES(algorithm::MazeGenerationAlgorithm)
public:
    graph::Graph generateMaze(const graph::Graph& g, const graph::Vertex& start) override;
    void generateMaze(grid::RectangleGrid& r, const std::optional<grid::Cell>& start = std::nullopt) const override;

signals:
    void wallRemoved(const graph::Edge& e);
};

}
