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
    std::set<grid::Cell> r1 {Cell(1), Cell(3)};
    EXPECT_THAT(mGrid.neighbours(Cell(0)), ::testing::ContainerEq(r1));
    std::set<grid::Cell> r2 {Cell(0), Cell(2), Cell(4)};
    EXPECT_THAT(mGrid.neighbours(Cell(1)), ::testing::ContainerEq(r2));
}

TEST_F(RectangleGridTest, addWall) {
    mGrid.addWall(Cell(0), Cell(1));

    std::set<grid::Cell> neighbours {Cell(3)};
    EXPECT_THAT(mGrid.neighbours(Cell(0)), ::testing::ContainerEq(neighbours));
}

TEST_F(RectangleGridTest, cannotAddWallBetweenCellsWhichAreNotAdjacend) {
    mGrid.addWall(Cell(0), Cell(2));

    std::set<grid::Cell> neighbours {Cell(3), Cell(1)};
    EXPECT_THAT(mGrid.neighbours(Cell(0)), ::testing::ContainerEq(neighbours));
}

TEST_F(RectangleGridTest, removeWall) {
    mGrid.addWall(Cell(0), Cell(1));

    std::set<grid::Cell> neighbours {Cell(3)};
    EXPECT_THAT(mGrid.neighbours(Cell(0)), ::testing::ContainerEq(neighbours));

    mGrid.removeWall(Cell(0), Cell(1));
    neighbours.emplace(Cell(1));
    EXPECT_THAT(mGrid.neighbours(Cell(0)), ::testing::ContainerEq(neighbours));
}

TEST_F(RectangleGridTest, cannotRemoveWallBetweenCellsWhichAreNotAdjacend) {
    mGrid.removeWall(Cell(0), Cell(2));

    std::set<grid::Cell> neighbours {Cell(3), Cell(1)};
    EXPECT_THAT(mGrid.neighbours(Cell(0)), ::testing::ContainerEq(neighbours));
}

TEST_F(RectangleGridTest, getFlattenRepresentationOfGridWithWalls)
{
    std::vector<int> flatten {
        0b11,
        0b111,
        0b110,
        0b1001,
        0b1101,
        0b1100
    };
    EXPECT_THAT(mGrid.flat(), ::testing::ContainerEq(flatten));

    mGrid.addWall(Cell(0), Cell(1));
    flatten.at(0) = 0b10;
    flatten.at(1) = 0b011;
    EXPECT_THAT(mGrid.flat(), ::testing::ContainerEq(flatten));
}

}
