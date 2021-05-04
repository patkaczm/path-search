#pragma once

#include <QObject>
#include <QString>
#include <QQmlApplicationEngine>
#include <QTimer>

#include "Graph/Graph.hpp"

class Backend : public QObject
{
    Q_OBJECT

public:
    explicit Backend(QQmlApplicationEngine& engine, QObject *parent = nullptr);

signals:
    void userNameChanged();

public slots:
    void onStartPathFinding(QVariant gc, int width);

private:
    using Plane = QVector<QVector<int>>;
    Plane make_plane(QVariant data,int width) const;
    graph::Graph make_graph(const Plane& plane) const;

    QQmlApplicationEngine& mEngine;
};

