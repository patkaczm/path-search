#pragma once

#include <QObject>

#include "Grid/RectangleGrid.hpp"

#include "Algorithm/MazeGeneration/MazeGeneration.hpp"

namespace algorithm {

class BinaryTree : public QObject , public MazeGeneration {
    Q_OBJECT
    Q_INTERFACES(algorithm::MazeGeneration)
public:
    void generateMaze(grid::RectangleGrid& r, const std::optional<grid::Cell>& start = std::nullopt) const override;

signals:
    void wallRemoved(const graph::Edge& e);
};

}
