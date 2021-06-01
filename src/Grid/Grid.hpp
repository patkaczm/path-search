#pragma once

#include <QVariant>
#include <QVector>

#include <optional>

#include "Graph/Graph.hpp"
#include "Grid/Cell.hpp"

namespace grid {

class Grid {
public:
    using Grid_t = QVector<QVector<Cell>>;
    Grid(std::size_t heigth, std::size_t width);
    Grid(QVariant gc, std::size_t width);

    Grid_t& getRows();
    const Grid_t& getRows() const;
    std::optional<Cell> getStart() const;
    std::optional<Cell> getEnd() const;

private:
    Grid_t mGrid;
    std::optional<Cell> mStart;
    std::optional<Cell> mEnd;
};

}
