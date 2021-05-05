#pragma once

#include <QObject>
#include <QString>
#include <QQmlApplicationEngine>
#include <QTimer>

#include "Graph/Graph.hpp"
#include "Algorithm/BreadthFirstSearch.hpp"
#include "Cell.hpp"

class Backend : public QObject
{
    Q_OBJECT

public:
    explicit Backend(QQmlApplicationEngine& engine, QObject *parent = nullptr);

signals:
    void pathFindingDone(QVariant path);

public slots:
    void onStartPathFinding(QVariant gc, int width);

private:
    using Plane = QVector<QVector<Grid::Cell>>;
    QVariant toQVariant(const algorithm::Path& path) const;

    int getStart(const Plane& plane) const;
    int getEnd(const Plane& plane) const;
    Plane make_plane(QVariant data,int width) const;
    graph::Graph make_graph(const Plane& plane) const;

    QQmlApplicationEngine& mEngine;
};

