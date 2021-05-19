#include "Backend.hpp"

#include <iostream>
#include <stack>
#include <thread>
#include <chrono>

#include <QObject>
#include <QVariant>
#include <QDebug>
#include <QQuickItem>
#include <QQuickAsyncImageProvider>

#include "Algorithm/PathFinding/BreadthFirstSearch.hpp"
#include "Algorithm/PathFinding/DepthFirstSearch.hpp"
#include "Algorithm/PathFinding/Dijkstra.hpp"

#include "Backend/Grid.hpp"
#include <random>

Backend::Backend(QQmlApplicationEngine& engine, QObject *parent)
    : QObject(parent)
    , mEngine(engine)
{
}

void Backend::onStartPathFinding(QVariant gc, int width) {
    qDebug() << "Start pathFinding";

    auto grid = grid::Grid(gc, width);
    auto graph = make_graph(grid.getGrid());
    //@todo operator() is not pretty anymore

    auto* alg = algorithmList.getSelected();
    if (alg) {
        QObject::connect(dynamic_cast<const QObject*>(alg), SIGNAL(vertexVisited(const graph::Vertex&)),
                         this, SLOT(onVertexVisited(const graph::Vertex&)));

        auto path = alg->operator()(graph, graph::Vertex{grid.getStart()->id}, graph::Vertex{grid.getEnd()->id});

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

namespace {

int index(const std::size_t i,const std::size_t j, const std::size_t width, const std::size_t height) {
    if (i < 0 || j < 0 || i > height -1 || j > width -1) {
        return -1;
    }
    return i * width + j;
}

graph::Vertex getRandomNeighbour(const graph::Graph::Neighbours& neighbours) {
    std::random_device seeder;
    std::mt19937 engine(seeder());
    std::uniform_int_distribution<std::size_t> dist(0, neighbours.size() - 1);
    auto it = neighbours.begin();
    std::advance(it, dist(engine));
    return *it;
}

std::set<graph::Vertex> getUnvisited(const graph::Graph::Neighbours& neighbours, const std::map<graph::Vertex, bool>& visited)
{
    std::set<graph::Vertex> unvisited;
    std::for_each(neighbours.begin(), neighbours.end(), [&visited, &unvisited](const graph::Vertex& v){
        if (not visited.at(v)) {
            unvisited.emplace(v);
        }
    });
    return unvisited;
}
}

void Backend::onGenerateMaze(int width, int heigth)
{
    qDebug() << "Generate maze: " << width<< ":" <<heigth;
    std::size_t tmpHeigth = (heigth - 1) / 2;
    std::size_t tmpWidth = (width - 1) / 2;
    qDebug() << "Tmp size: "<< tmpWidth << ":" << tmpHeigth;

    grid::Grid gridd(tmpHeigth, tmpWidth);
    auto graph = make_graph(gridd.getGrid());

    graph::Graph maze;
    auto mazeVertexes = graph.getVertexes();
    std::for_each(mazeVertexes.begin(), mazeVertexes.end(), [&maze](auto& v){
        maze.add(v);
    });

    std::map<graph::Vertex, bool> visited;
    // make a grid of cells
    for(std::size_t i = 0; i < tmpHeigth * tmpWidth; i++ ) {
        visited.emplace(graph::Vertex{static_cast<std::uint32_t>(i)}, false);
    }

    std::stack<graph::Vertex> s;
    auto& current = gridd.getGrid()[0][0];
    visited[graph::Vertex{static_cast<std::uint32_t>(current.id)}] = true;
    s.push(graph::Vertex{static_cast<std::uint32_t>(current.id)});

    while(!s.empty()) {
        auto current = s.top();
        s.pop();
        auto unvisited = getUnvisited(graph.getNeighbours(graph::Vertex{current.id}), visited);
        if (unvisited.size() > 0) {
            s.push(current);
            auto randomNeighbour = getRandomNeighbour(unvisited);
            //remove wall
            maze.add(graph::Edge{current, randomNeighbour});
            visited[randomNeighbour] = true;
            s.push(randomNeighbour);
        }
    }

    std::vector<int> ret(width * heigth, static_cast<int>(grid::Cell::Type::Obstacle));
    qDebug() << "ret size: " << ret.size();

    for (const auto& v : maze.getVertexes()) {
        auto i = v.id / tmpWidth;
        auto j = v.id % tmpWidth;
        ret.at(index((2*i) + 1, (2*j) + 1, width, heigth)) = static_cast<int>(grid::Cell::Type::EmptyField);
        for (const auto& neighbour : maze.getNeighbours(v)) {
            if (neighbour.id == v.id + 1) { // right
                ret.at(index(2*i + 1, 2*(j + 1), width, heigth)) = static_cast<int>(grid::Cell::Type::EmptyField);
            } else if (neighbour.id == v.id + tmpWidth) { // bottom
                ret.at(index(2*(i + 1), 2*j + 1, width, heigth)) = static_cast<int>(grid::Cell::Type::EmptyField);
            }
        }
    }

    QVariant v;
    v.setValue(ret);
    emit mazeGenerationDone(v);

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

graph::Graph Backend::make_graph(const grid::Grid::Grid_t &plane) const
{
    graph::Graph graph;
    //add vertexes
    for (const auto& row : plane) {
        for (const auto& cell : row) {
            graph.add(graph::Vertex{cell.id});
        }
    }
    //add edges
    for (int i = 0 ; i < plane.size(); i++) {
        for (int j = 0 ; j < plane[i].size(); j++) {
            if (plane[i][j].type == grid::Cell::Type::Obstacle) {
                continue;
            }
            if (i > 0) {
                if (plane[i-1][j].type != grid::Cell::Type::Obstacle) {
                    graph.add(graph::Edge{{plane[i][j].id}, {plane[i-1][j].id}});
                }
            }
            if (j < plane[i].size() - 1) {
                if (plane[i][j + 1].type != grid::Cell::Type::Obstacle) {
                    graph.add(graph::Edge{{plane[i][j].id}, {plane[i][j + 1].id}});
                }
            }
            if (i < plane.size() - 1) {
                if (plane[i + 1][j].type != grid::Cell::Type::Obstacle) {
                    graph.add(graph::Edge{{plane[i][j].id}, {plane[i + 1][j].id}});
                }
            }
            if (j > 0 ) {
                if (plane[i][j - 1].type != grid::Cell::Type::Obstacle) {
                    graph.add(graph::Edge{{plane[i][j].id}, {plane[i][j - 1].id}});
                }
            }
        }
    }
    return graph;
}
