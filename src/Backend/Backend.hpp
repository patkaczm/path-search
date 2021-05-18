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
    struct Cell {
        std::size_t i;
        std::size_t j;
        std::size_t id;

        enum class Direction {
            Top,
            Right,
            Bottom,
            Left
        };

        std::map<Direction, bool> walls {
            {Direction::Top, true},
            {Direction::Right, true},
            {Direction::Bottom, true},
            {Direction::Left, true}
        };
        bool visited = false;
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

    void removeTheWall(std::vector<Cell>& grid, Cell& current, Cell& randomNeighbour, std::size_t tmpHeigth, std::size_t tmpWidth);

private:
    QVariant toQVatiantVS(const std::vector<std::string>& val) const;
    QVariant toQVariant(const algorithm::Algorithm::Path& path) const;

    graph::Graph make_graph(const grid::Grid::Grid_t& plane) const;
    std::vector<Cell> getUnvisitedNeighbours(const std::vector<Cell>& grid, const std::size_t width, const std::size_t height, const Cell& cell);

    QQmlApplicationEngine& mEngine;
    algorithm::AlgorithmList algorithmList;
};

