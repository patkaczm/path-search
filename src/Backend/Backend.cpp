#include "Backend.hpp"

#include <iostream>

#include <QObject>
#include <QVariant>
#include <QDebug>
#include <QQuickItem>
#include <QQuickAsyncImageProvider>

Backend::Backend(QQmlApplicationEngine& engine, QObject *parent)
    : QObject(parent)
    , mEngine(engine)
{
}

void Backend::onStartPathFinding(QVariant gc, int width) {
    // 0 for empty field
    // 1 for start
    // 2 for end
    // 3 for obstacle


    qDebug() << "Start pathFinding";

    auto plane = make_plane(gc, width);
    auto graph = make_graph(plane);
    auto alg = algorithm::BreadthFirstSearch(graph);
    auto path = alg(graph::Vertex{getStart(plane)}, graph::Vertex{getEnd(plane)});
    auto variant_path = toQVariant(path);
    emit pathFindingDone(variant_path);
}

int Backend::getStart(const Plane &plane) const
{
    for (const auto& row : plane) {
        for (const auto& cell : row) {
            if (cell.type == Grid::Cell::Type::Start) {
                return cell.id;
            }
        }
    }
    // this should never happen
    return 0;
}

int Backend::getEnd(const Plane &plane) const
{
    for (const auto& row : plane) {
        for (const auto& cell : row) {
            if (cell.type == Grid::Cell::Type::End) {
                return cell.id;
            }
        }
    }
    // this should never happen
    return 0;
}

QVariant Backend::toQVariant(const algorithm::Path &path) const
{
    std::vector<int> tmp;
    for(const auto& step : path) {
        tmp.push_back(step.id);
    }
    QVariant v;
    v.setValue(tmp);
    return v;
}

Backend::Plane Backend::make_plane(QVariant data, int width) const
{
    // for now there is assumption made that cells are numbered from left to right, from top to bottom, ascending, starting from 0
    QList l (data.toList());
    Plane plane{};

    QVector<Grid::Cell> tmp;
    for (int i = 0 ; i < l.length(); i++ ) {
        tmp.push_back({i, l[i].toInt()});
        if ((i + 1) % width == 0) {
            plane.push_back(tmp);
            tmp = QVector<Grid::Cell>();
        }
    }
    return plane;
}

graph::Graph Backend::make_graph(const Plane &plane) const
{
    graph::Graph graph;
    //add vertexes
    for (const auto& row : plane) {
        for (const auto& cell : row) {
            qDebug() << "Add: " << cell.id;
            graph.add(graph::Vertex{cell.id});
        }
    }
    //add edges
    for (int i = 0 ; i < plane.size(); i++) {
        for (int j = 0 ; j < plane[i].size(); j++) {
            if (plane[i][j].type == Grid::Cell::Type::Obstacle) {
                continue;
            }
            if (i > 0) {
                if (plane[i-1][j].type != Grid::Cell::Type::Obstacle) {
                    graph.add(graph::Edge{{plane[i][j].id}, {plane[i-1][j].id}});
                }
            }
            if (j < plane[i].size() - 1) {
                if (plane[i][j + 1].type != Grid::Cell::Type::Obstacle) {
                    graph.add(graph::Edge{{plane[i][j].id}, {plane[i][j + 1].id}});
                }
            }
            if (i < plane.size() - 1) {
                if (plane[i + 1][j].type != Grid::Cell::Type::Obstacle) {
                    graph.add(graph::Edge{{plane[i][j].id}, {plane[i + 1][j].id}});
                }
            }
            if (j > 0 ) {
                if (plane[i][j - 1].type != Grid::Cell::Type::Obstacle) {
                    graph.add(graph::Edge{{plane[i][j].id}, {plane[i][j - 1].id}});
                }
            }
        }
    }
    return graph;
}
