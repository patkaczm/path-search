#include "Backend/Grid.hpp"

#include <QDebug>

namespace grid {

grid::Grid::Grid(QVariant gc, int width)
{
    QList l (gc.toList());
    QVector<grid::Cell> tmp;
    for (std::size_t i = 0 ; i < static_cast<std::size_t>(l.length()); i++ ) {
        tmp.push_back({static_cast<std::uint32_t>(i), static_cast<std::uint8_t>(l[i].toUInt())});
        if (tmp.back().type == grid::Cell::Type::Start) {
            mStart = tmp.back();
        } else if (tmp.back().type == grid::Cell::Type::End) {
            mEnd = tmp.back();
        }

        if ((i + 1) % width == 0) {
            mGrid.push_back(tmp);
            tmp = QVector<grid::Cell>();
        }
    }
}

const Grid::Grid_t &Grid::getGrid() const
{
    return mGrid;
}

std::optional<Cell> Grid::getStart() const
{
    return mStart;
}

std::optional<Cell> Grid::getEnd() const
{
    return mEnd;
}

}
