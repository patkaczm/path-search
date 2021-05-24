#include "Backend/MazeGenerator.hpp"
#include "Backend/Utils.hpp"

#include <cstdint>

namespace {

std::uint32_t index(const std::size_t i,const std::size_t j, const std::size_t width, const std::size_t height) {
    if (i < 0 || j < 0 || i > height -1 || j > width -1) {
        qDebug() << "i: "<< i << " j: " << j << " width: " << width << " height: " << height;
        throw std::logic_error("Wrong parameters in index()");
    }
    return i * width + j;
}

}

MazeGenerator::MazeGenerator(std::unique_ptr<algorithm::MazeGenerationAlgorithm> &&algorithm, const std::size_t width, const std::size_t heigth)
    : mAlgorithm(std::move(algorithm)), mWidth(width), mHeight(heigth)
{
}

MazeGenerator::Maze MazeGenerator::generate()
{
    mGenerationHistory.clear();
    //todo check whether heigth and width is in 2x+1 format
    std::size_t tmpHeight = (mHeight - 1) / 2;
    std::size_t tmpWidth = (mWidth - 1) / 2;

    grid::Grid grid(tmpHeight, tmpWidth);
    auto graph = utils::makeGraph(grid);


    QObject::connect(dynamic_cast<QObject*>(mAlgorithm.get()), SIGNAL(wallRemoved(const graph::Edge&)),
                     this, SLOT(onWallRemoved(const graph::Edge &)));
    auto maze = mAlgorithm->generateMaze(graph, *graph.getVertexes().begin());
    QObject::disconnect(dynamic_cast<QObject*>(mAlgorithm.get()), SIGNAL(wallRemoved(const graph::Edge&)),
                     this, SLOT(onWallRemoved(const graph::Edge &)));

    grid::Grid retMaze(mHeight, mWidth);

    for(auto& row : retMaze.getRows()) {
        for(auto& cell : row) {
            cell.type = grid::Cell::Type::Obstacle;
        }
    }

    for(const auto& v : maze.getVertexes()) {
        auto i = v.id / tmpWidth;
        auto j = v.id % tmpWidth;
        retMaze.getRows()[(2*i) + 1][(2*j)+1].type = grid::Cell::Type::EmptyField;
        for (const auto& neighbour : maze.getNeighbours(v)) {
            if (neighbour.id == v.id + 1) { // right
                retMaze.getRows()[2*i + 1][2*(j + 1)].type = grid::Cell::Type::EmptyField;
            } else if (neighbour.id == v.id + tmpWidth) { // bottom
                retMaze.getRows()[2*(i + 1)][2*j + 1].type = grid::Cell::Type::EmptyField;
            }
        }
    }

    return {retMaze, mGenerationHistory};
}

void MazeGenerator::onWallRemoved(const graph::Edge &e)
{
    std::size_t tmpWidth = (mWidth - 1) / 2;
    auto ai = e.a.id / tmpWidth;
    auto aj = e.a.id % tmpWidth;
    auto bi = e.b.id / tmpWidth;
    auto bj = e.b.id % tmpWidth;
    updateGenerationHistory((2*ai) + 1, (2*aj) + 1);
    updateGenerationHistory((2*bi) + 1, (2*bj) + 1);
    if (e.b.id == e.a.id + 1) {
        updateGenerationHistory(2*ai + 1, 2*(aj + 1));
    } else if (e.b.id == e.a.id + tmpWidth) {
        updateGenerationHistory(2*(ai + 1), 2*aj + 1);
    } else if (e.a.id == e.b.id + 1) {
        updateGenerationHistory(2*bi + 1, 2*(bj + 1));
    } else if (e.a.id == e.b.id + tmpWidth) {
        updateGenerationHistory(2*(bi + 1), 2*bj + 1);
    }
}

void MazeGenerator::updateGenerationHistory(const std::size_t i, const std::size_t j)
{
    grid::Cell c{index(i, j, mWidth, mHeight), grid::Cell::Type::EmptyField};
    mGenerationHistory.emplace_back(c);
    emit cellGenerated(c);
}
