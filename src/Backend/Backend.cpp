#include "Backend.hpp"

#include <iostream>

#include <QObject>
#include <QVariant>
#include <QDebug>
#include <QQuickItem>
#include <QQuickAsyncImageProvider>

#include "Backend/Grid.hpp"

Backend::Backend(QQmlApplicationEngine& engine, QObject *parent)
    : QObject(parent)
    , mEngine(engine)
{
}

void Backend::onStartPathFinding(QVariant gc, int width) {
    qDebug() << "Start pathFinding";

    auto grid = grid::Grid(gc, width);
    auto graph = make_graph(grid.getGrid());
    auto alg = algorithm::BreadthFirstSearch();

    QObject::connect(dynamic_cast<QObject*>(&alg), SIGNAL(vertexVisited(const graph::Vertex&)),
                     this, SLOT(onVertexVisited(const graph::Vertex&)));

    auto path = alg(graph, graph::Vertex{grid.getStart()->id}, graph::Vertex{grid.getEnd()->id});

    QObject::disconnect(dynamic_cast<QObject*>(&alg), SIGNAL(vertexVisited(const graph::Vertex&)),
                     this, SLOT(onVertexVisited(const graph::Vertex&)));

    auto variant_path = toQVariant(path);
    emit pathFindingDone(variant_path);
}

void Backend::onVertexVisited(const graph::Vertex &v)
{
    emit vertexVisited(v.id);
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
