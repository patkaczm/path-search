#pragma once

#include <QVariant>
#include <QVector>

#include <optional>

#include "Graph/Graph.hpp"
#include "Backend/Cell.hpp"

namespace grid {

class Grid {
public:
    using Grid_t = QVector<QVector<Cell>>;
    Grid(QVariant gc, int width);

    const Grid_t& getGrid() const;
    std::optional<Cell> getStart() const;
    std::optional<Cell> getEnd() const;

private:
    Grid_t mGrid;
    std::optional<Cell> mStart;
    std::optional<Cell> mEnd;
};

}
