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
}

Backend::Plane Backend::make_plane(QVariant data, int width) const
{
    QList l (data.toList());
    QVector<QVector<int>> plane{};

    QVector<int> tmp;
    for (int i = 0 ; i < l.length(); i++ ) {
        tmp.push_back(l[i].toInt());
        if ((i + 1) % width == 0) {
            plane.push_back(tmp);
            tmp = QVector<int>();
        }
    }
}

graph::Graph Backend::make_graph(const Plane &plane) const
{
    graph::Graph graph;

}
