#include "Backend.hpp"

#include <QObject>
#include <QVariant>
#include <QDebug>

#include "Algorithm/PathFinding/BreadthFirstSearch.hpp"
#include "Algorithm/PathFinding/DepthFirstSearch.hpp"
#include "Algorithm/PathFinding/Dijkstra.hpp"
#include "Algorithm/MazeGeneration/IterativeBacktracker.hpp"

#include "Backend/Utils.hpp"
#include "Backend/MazeGenerator.hpp"

Backend::Backend(QQmlApplicationEngine& engine, QObject *parent)
    : QObject(parent)
    , mEngine(engine)
{
}

void Backend::onStartPathFinding(QVariant gc, int width) {
    qDebug() << "Start pathFinding";

    auto grid = grid::Grid(gc, width);
    auto graph = utils::makeGraph(grid);

    auto* alg = algorithmList.getSelected();
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

void Backend::onAlgorithmSelected(QVariant v)
{
    algorithmList.selectAlgorithm(v.toString().toStdString());
}

void Backend::onGenerateMaze(int width, int height)
{
    qDebug() << "Generate maze: " << width<< ":" <<height;
    MazeGenerator mg(std::make_unique<algorithm::IterativeBacktracker>(), width, height);

    QObject::connect(&mg, &MazeGenerator::cellGenerated, this, &Backend::onMazeCellGenerated);
    auto mazeData = mg.generateRectangle();
    QObject::disconnect(&mg, &MazeGenerator::cellGenerated, this, &Backend::onMazeCellGenerated);

//    std::vector<int> ret(width * height, static_cast<int>(grid::Cell::Type::Obstacle));
//    qDebug() << "ret size: " << ret.size();
//    for (const auto& row : mazeData.maze.getRows()) {
//        for (const auto& cell : row) {
//            ret.at(cell.id) = static_cast<int>(cell.type);
//        }
//    }

    QVariant v;
    v.setValue(mazeData.flat());
    qDebug() << mazeData.flat();
    emit mazeGenerationDone(v);
}

void Backend::onMazeCellGenerated(const grid::Cell &c)
{
    emit mazeCellGenerated(c.id);
}

void Backend::loadAlgorithms()
{
    algorithmList.registerAlgorithm("BreadthFirstSearch", std::make_unique<algorithm::BreadthFirstSearch>());
    algorithmList.registerAlgorithm("DepthFirstSearch", std::make_unique<algorithm::DepthFirstSearch>());
    algorithmList.registerAlgorithm("Dijkstra", std::make_unique<algorithm::Dijkstra>());
    emit availableAlgorithmsSet(toQVatiantVS(algorithmList.getAlgorithmList()));
}

QVariant Backend::toQVariant(const algorithm::Algorithm::Path &path) const
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
