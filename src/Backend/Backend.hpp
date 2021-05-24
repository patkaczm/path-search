#pragma once

#include <QObject>
#include <QString>
#include <QQmlApplicationEngine>

#include "Graph/Graph.hpp"
#include "Algorithm/PathFinding/Algorithm.hpp"
#include "Algorithm/PathFinding/AlgorithmList.hpp"
#include "Backend/Cell.hpp"
#include "Backend/Grid.hpp"

class Cell;

class Backend : public QObject
{
    Q_OBJECT

public:
    explicit Backend(QQmlApplicationEngine& engine, QObject *parent = nullptr);

signals:
    void pathFindingDone(QVariant path);
    void vertexVisited(QVariant v);
    void mazeCellGenerated(QVariant v);
    void availableAlgorithmsSet(QVariant v);
    void mazeGenerationDone(QVariant v);

public slots:
    void onStartPathFinding(QVariant gc, int width);
    void onVertexVisited(const graph::Vertex& v);
    void onAlgorithmSelected(QVariant v);
    void onGenerateMaze(int width, int heigth);
    void onMazeCellGenerated(const grid::Cell& c);

public:
    void loadAlgorithms();

private:
    QVariant toQVatiantVS(const std::vector<std::string>& val) const;
    QVariant toQVariant(const algorithm::Algorithm::Path& path) const;

    QQmlApplicationEngine& mEngine;
    algorithm::AlgorithmList algorithmList;
};

