#include "Backend/Grid.hpp"

#include <QDebug>

namespace grid {

grid::Grid::Grid(QVariant gc, int width)
{
    QList l (gc.toList());
    QVector<grid::Cell> tmp;
    for (int i = 0 ; i < l.length(); i++ ) {
        tmp.push_back({i, l[i].toInt()});
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
