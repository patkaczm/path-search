#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Grid/RectangleGrid.hpp"

namespace grid::test {

class RectangleGridTest : public ::testing::Test {
protected:

    const std::uint32_t mXSize {3};
    const std::uint32_t mYSize {2};

    RectangleGrid mGrid{mYSize, mXSize};

};

TEST_F(RectangleGridTest, creates)
{
    auto size = mGrid.size();

    EXPECT_EQ(mYSize, size.first);
    EXPECT_EQ(mXSize, size.second);
}

TEST_F(RectangleGridTest, throwWhenAtParamsOutOfTheBounds)
{
    EXPECT_THROW(mGrid.at(mYSize + 1, mXSize), std::out_of_range);
    EXPECT_THROW(mGrid.at(mYSize, mXSize + 1), std::out_of_range);
}

TEST_F(RectangleGridTest, returnCellWhenAtParamsAreInRange)
{
    EXPECT_NO_THROW(mGrid.at(mYSize - 1, mXSize - 1));
}

TEST_F(RectangleGridTest, getNeighboursReturnRightNeighbours)
{
    std::set<grid::Cell> r1 {Cell(1, Cell::Type::EmptyField), Cell(3, Cell::Type::EmptyField)};
    EXPECT_THAT(mGrid.neighbours(Cell(0, Cell::Type::EmptyField)), ::testing::ContainerEq(r1));
    std::set<grid::Cell> r2 {Cell(0, Cell::Type::EmptyField), Cell(2, Cell::Type::EmptyField), Cell(4, Cell::Type::EmptyField)};
    EXPECT_THAT(mGrid.neighbours(Cell(1, Cell::Type::EmptyField)), ::testing::ContainerEq(r2));

}

}
