#pragma once

#include <memory>
#include <QObject>

#include "Graph/Graph.hpp"
#include "Graph/Vertex.hpp"

#include "Algorithm/MazeGeneration/MazeGenerationAlgorithm.hpp"

#include "Grid/Grid.hpp"
#include "Grid/Cell.hpp"

class MazeGenerator : public QObject
{
    Q_OBJECT
public:
    struct Maze {
        grid::Grid maze;
        std::vector<grid::Cell> generationHistory;
    };

    MazeGenerator(std::unique_ptr<algorithm::MazeGenerationAlgorithm>&& algorithm, const std::size_t width, const std::size_t heigth);
    Maze generate();
    //@todo tmp
    grid::RectangleGrid generateRectangle();

signals:
    void cellGenerated(const grid::Cell& c);

private slots:
    void onWallRemoved(const graph::Edge &e);

private:
    void updateGenerationHistory(const std::size_t i, const std::size_t j);
    std::unique_ptr<algorithm::MazeGenerationAlgorithm> mAlgorithm;
    std::size_t mWidth;
    std::size_t mHeight;
    std::vector<grid::Cell> mGenerationHistory;
};
