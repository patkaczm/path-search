#pragma once

#include <QObject>
#include <QString>
#include <QQmlApplicationEngine>
#include <QTimer>

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
    enum class Direction {
        Top,
        Right,
        Bottom,
        Left
    };

    struct Cell {
        std::size_t i;
        std::size_t j;
        std::size_t id;

        bool operator<(const Cell& rhs) const {
            return i < rhs.i || i == rhs.i && j < rhs.j;
        }
    };
signals:
    void pathFindingDone(QVariant path);
    void vertexVisited(QVariant v);
    void availableAlgorithmsSet(QVariant v);
    void mazeGenerationDone(QVariant v);

public slots:
    void onStartPathFinding(QVariant gc, int width);
    void onVertexVisited(const graph::Vertex& v);
    void onAlgorithmSelected(QVariant v);
    void onGenerateMaze(int width, int heigth);

public:
    void loadAlgorithms();

    void removeTheWall(std::map<Cell, std::map<Direction, bool>>& walls, Cell& current, Cell& randomNeighbour);

private:
    QVariant toQVatiantVS(const std::vector<std::string>& val) const;
    QVariant toQVariant(const algorithm::Algorithm::Path& path) const;

    graph::Graph make_graph(const grid::Grid::Grid_t& plane) const;
    std::vector<Cell> getUnvisited(const std::vector<Cell>& neighbours, const std::map<Cell, bool>& visited);
    std::vector<Cell> getNeighbours(const std::vector<Cell>& grid, const std::size_t width, const std::size_t height, const Cell& cell);

    QQmlApplicationEngine& mEngine;
    algorithm::AlgorithmList algorithmList;
};

