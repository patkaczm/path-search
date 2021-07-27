#pragma once

#include <QObject>

#include "Graph/Graph.hpp"
#include "Algorithm/MazeGeneration/MazeGeneration.hpp"

namespace algorithm {

class MazeGenerationAlgorithmStub : public QObject , public MazeGeneration {
    Q_OBJECT
    Q_INTERFACES(algorithm::MazeGeneration)
public:
    void generateMaze(grid::RectangleGrid& r, const std::optional<grid::Cell>& start = std::nullopt) const override;
    void emitWallRemoved(const graph::Edge& e);
signals:
    void wallRemoved(const graph::Edge& e);
};

}
