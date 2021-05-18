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

int index(const int i,const int j, const std::size_t width, const std::size_t height) {
    if (i < 0 || j < 0 || i > height -1 || j > width -1) {
        return -1;
    }
    return i * width + j;
}

Backend::Cell getRandomNeighbour(const std::vector<Backend::Cell>& neighbours) {
    std::random_device seeder;
    std::mt19937 engine(seeder());
    std::uniform_int_distribution<std::size_t> dist(0, neighbours.size() - 1);
    return neighbours.at(dist(engine));
}

}

std::vector<Backend::Cell> Backend::getUnvisitedNeighbours(const std::vector<Cell>& grid, const std::size_t width, const std::size_t height, const Cell& cell)
{
    std::vector<Cell> unvisited;
    //todo refactor
    if (cell.i > 0 && not grid[index(cell.i-1, cell.j, width, height)].visited){
        unvisited.push_back(grid[index(cell.i-1,cell.j, width, height)]);
    }
    if (cell.j < width - 1 && not grid[index(cell.i, cell.j + 1, width, height)].visited) {
        unvisited.push_back(grid[index(cell.i, cell.j + 1, width, height)]);
    }
    if (cell.i < height - 1 && not grid[index(cell.i + 1, cell.j, width, height)].visited) {
        unvisited.push_back(grid[index(cell.i + 1, cell.j, width, height)]);
    }
    if (cell.j > 0 && not grid[index(cell.i, cell.j - 1, width, height)].visited) {
        unvisited.push_back(grid[index(cell.i, cell.j - 1, width, height)]);
    }
    return unvisited;
}

void Backend::removeTheWall(std::map<Cell, std::map<Direction, bool>>& walls, Cell& current, Cell& randomNeighbour)
{
    if (current.i < randomNeighbour.i) {
        walls[current][Direction::Bottom] = false;
        walls[randomNeighbour][Direction::Top] = false;
    } else if (current.i > randomNeighbour.i) {
        walls[current][Direction::Top] = false;
        walls[randomNeighbour][Direction::Bottom] = false;
    } else if (current.j < randomNeighbour.j) {
        walls[current][Direction::Right] = false;
        walls[randomNeighbour][Direction::Left] = false;
    } else if (current.j > randomNeighbour.j) {
        walls[current][Direction::Left] = false;
        walls[randomNeighbour][Direction::Right] = false;
    }
}

void Backend::onGenerateMaze(int width, int heigth)
{
    qDebug() << "Generate maze: " << width<< ":" <<heigth;
    std::size_t tmpHeigth = (heigth - 1) / 2;
    std::size_t tmpWidth = (width - 1) / 2;
    qDebug() << "Tmp size: "<< tmpWidth << ":" << tmpHeigth;

    std::vector<Cell> grid{};
    std::map<Cell, std::map<Direction, bool>> walls;
    // make a grid of cells
    for(std::size_t i = 0; i < tmpHeigth * tmpWidth; i++ ) {
        Cell c;
        c.i = i / tmpWidth;
        c.j = i % tmpWidth;
        c.id = i;
        grid.emplace_back(c);
        walls.emplace(c, std::map<Direction, bool> {
                             {Direction::Top, true},
                             {Direction::Right, true},
                             {Direction::Bottom, true},
                             {Direction::Left, true}
                         });
//        qDebug() << "Cell: " << c.i << ":" << c.j << ":" << c.id;
    }

    std::stack<Cell> s;
    auto& current = grid[0];
    current.visited = true;
    s.push(current);

    while(!s.empty()) {
        auto current = s.top();
        s.pop();
        auto unvisited = getUnvisitedNeighbours(grid, tmpWidth, tmpHeigth, current);
        if (unvisited.size() > 0) {
            s.push(current);
            auto randomNeighbour = getRandomNeighbour(unvisited);

            removeTheWall(walls, current, randomNeighbour);

            grid[index(randomNeighbour.i, randomNeighbour.j, tmpWidth, tmpHeigth)].visited = true;
            randomNeighbour.visited = true;

//            int id = randomNeighbour.id;
//            emit vertexVisited(id);

            s.push(randomNeighbour);
        }
    }

    std::vector<int> ret(width * heigth, static_cast<int>(grid::Cell::Type::Obstacle));
    qDebug() << "ret size: " << ret.size();

    for (const auto& cell : grid) {
        ret.at(index((2*cell.i) + 1, (2*cell.j) + 1, width, heigth)) = static_cast<int>(grid::Cell::Type::EmptyField);
        if (not walls.at(cell).at(Direction::Bottom)) {
            ret.at(index(2*(cell.i + 1), 2*cell.j + 1, width, heigth)) = static_cast<int>(grid::Cell::Type::EmptyField);
        }
        if (not walls.at(cell).at(Direction::Right)) {
            ret.at(index(2*cell.i + 1, 2*(cell.j + 1), width, heigth)) = static_cast<int>(grid::Cell::Type::EmptyField);
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
