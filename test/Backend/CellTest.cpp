#include "Backend/Cell.hpp"

#include <gtest/gtest.h>

namespace grid {
namespace test {

TEST(CellTest, CellTypeStart)
{
    Cell cell{1, 1};
    EXPECT_EQ(Cell::Type::Start, cell.type);
}

TEST(CellTest, CellTypeEnd)
{
    Cell cell{1, 2};
    EXPECT_EQ(Cell::Type::End, cell.type);
}

TEST(CellTest, CellTypeObstacle)
{
    Cell cell{1, 3};
    EXPECT_EQ(Cell::Type::Obstacle, cell.type);
}

TEST(CellTest, CellTypeEmptyField)
{
    Cell cell{1, 0};
    EXPECT_EQ(Cell::Type::EmptyField, cell.type);
}

TEST(CellTest, throwOnUnknownType)
{
    EXPECT_THROW(Cell(1, 4), std::out_of_range);
}

TEST(CellTest, canUseEqualOperator)
{
    Cell a (1, 2);
    Cell b (2, 3);
    EXPECT_TRUE(a == a);
    EXPECT_FALSE(a == b);
}

}
}
