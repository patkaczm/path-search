#pragma once

#include <QObject>
#include <QString>
#include <QQmlApplicationEngine>
#include <QTimer>

#include "Graph/Graph.hpp"
#include "Algorithm/BreadthFirstSearch.hpp"

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
    enum class CellType {
        EmptyField,
        Obstacle,
        Start,
        End
    };
    struct Cell {
        int id;
        CellType cellType;
    };
    using Plane = QVector<QVector<Cell>>;
    CellType toCellType(int) const;
    QVariant toQVariant(const algorithm::Path& path) const;

    int getStart(const Plane& plane) const;
    int getEnd(const Plane& plane) const;
    Plane make_plane(QVariant data,int width) const;
    graph::Graph make_graph(const Plane& plane) const;

    QQmlApplicationEngine& mEngine;
};

