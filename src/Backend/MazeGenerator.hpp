#pragma once

#include <memory>
#include <QObject>

#include "Graph/Graph.hpp"
#include "Graph/Vertex.hpp"

#include "Algorithm/MazeGeneration/MazeGenerationAlgorithm.hpp"

#include "Backend/Grid.hpp"
#include "Backend/Cell.hpp"

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

private slots:
    void onWallRemoved(const graph::Edge &e);

private:
    std::unique_ptr<algorithm::MazeGenerationAlgorithm> mAlgorithm;
    std::size_t mWidth;
    std::size_t mHeight;
    std::vector<grid::Cell> mGenerationHistory;
};
