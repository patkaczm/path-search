#include "Backend.hpp"

#include <QObject>
#include <QVariant>
#include <QDebug>

#include "Algorithm/PathFinding/BreadthFirstSearch.hpp"
#include "Algorithm/PathFinding/DepthFirstSearch.hpp"
#include "Algorithm/PathFinding/Dijkstra.hpp"
#include "Algorithm/MazeGeneration/IterativeBacktracker.hpp"
#include "Algorithm/MazeGeneration/BinaryTree.hpp"

#include "Backend/Utils.hpp"

Backend::Backend(QQmlApplicationEngine& engine, QObject *parent)
    : QObject(parent)
    , mEngine(engine)
{
}

void Backend::onStartPathFinding(QVariant gc, int width) {
    qDebug() << "Start pathFinding";

    auto grid = grid::Grid(gc, width);
    auto graph = utils::makeGraph(grid);

    auto* alg = pathFindingAlgorithmList.getSelected();
    if (alg) {
        QObject::connect(dynamic_cast<const QObject*>(alg), SIGNAL(vertexVisited(const graph::Vertex&)),
                         this, SLOT(onVertexVisited(const graph::Vertex&)));

        auto path = alg->findPath(graph, graph::Vertex{grid.getStart()->id}, graph::Vertex{grid.getEnd()->id});

        QObject::disconnect(dynamic_cast<const QObject*>(alg), SIGNAL(vertexVisited(const graph::Vertex&)),
                            this, SLOT(onVertexVisited(const graph::Vertex&)));

        auto variant_path = toQVariant(path);
        emit pathFindingDone(variant_path);
    }
}

void Backend::onVertexVisited(const graph::Vertex &v)
{
    emit vertexVisited(v.id);
}

void Backend::onPathFindingAlgorithmSelect(QVariant v)
{
    pathFindingAlgorithmList.selectAlgorithm(v.toString().toStdString());
}

void Backend::onGenerateMaze(int width, int height)
{
    qDebug() << "Generate maze: " << width<< ":" <<height;

    grid::RectangleGrid r(height, width);
    mazeGenerationAlgorithmList.getSelected()->generateMaze(r);

    QVariant v;
    v.setValue(r.flat());
    qDebug() << r.flat();
    emit mazeGenerationDone(v);
}

void Backend::onMazeCellGenerated(const grid::Cell &c)
{
    emit mazeCellGenerated(c.id);
}

void Backend::onMazeGenerationAlgorithmSelect(QVariant v)
{
    mazeGenerationAlgorithmList.selectAlgorithm(v.toString().toStdString());
}

void Backend::loadAlgorithms()
{
    loadPathFindingAlgorithms();
    loadMazeGenerationAlgorithms();
}

void Backend::loadPathFindingAlgorithms()
{
    pathFindingAlgorithmList.registerAlgorithm("BreadthFirstSearch", std::make_unique<algorithm::BreadthFirstSearch>());
    pathFindingAlgorithmList.registerAlgorithm("DepthFirstSearch", std::make_unique<algorithm::DepthFirstSearch>());
    pathFindingAlgorithmList.registerAlgorithm("Dijkstra", std::make_unique<algorithm::Dijkstra>());
    emit availablePathFindingAlgorithmsSet(toQVatiantVS(pathFindingAlgorithmList.getAlgorithmList()));
}

void Backend::loadMazeGenerationAlgorithms()
{
    mazeGenerationAlgorithmList.registerAlgorithm("IterativeBacktracker", std::make_unique<algorithm::IterativeBacktracker>());
    mazeGenerationAlgorithmList.registerAlgorithm("BinaryTree", std::make_unique<algorithm::BinaryTree>());
    emit availableMazeGenerationAlgorithmsSet(toQVatiantVS(mazeGenerationAlgorithmList.getAlgorithmList()));
}

QVariant Backend::toQVariant(const algorithm::PathFinding::Path &path) const
{
    std::vector<int> tmp;
    for(const auto& step : path) {
        tmp.push_back(step.id);
    }
    QVariant v;
    v.setValue(tmp);
    return v;
}

QVariant Backend::toQVatiantVS(const std::vector<std::string> &val) const
{
    std::vector<QString> tmp;
    for (const auto& x : val) {
        tmp.push_back(QString::fromStdString(x));
    }
    QVariant v;
    v.setValue(tmp);
    return v;
}
