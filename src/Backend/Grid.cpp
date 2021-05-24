#include "Backend/Grid.hpp"

#include <QDebug>

namespace grid {

Grid::Grid(std::size_t heigth, std::size_t width)
{
    for (std::size_t i = 0 ; i < heigth; i++) {
        mGrid.push_back({});
        for (std::size_t j = 0 ; j < width; j++) {
            mGrid[i].push_back(Cell(i * width + j, static_cast<std::uint8_t>(Cell::Type::EmptyField)));
        }
    }
}

grid::Grid::Grid(QVariant gc, std::size_t width)
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

Grid::Grid_t &Grid::getRows()
{
    return mGrid;
}

const Grid::Grid_t &Grid::getRows() const
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
