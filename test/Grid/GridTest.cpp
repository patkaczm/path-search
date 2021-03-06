#include "Grid/Grid.hpp"

#include <gtest/gtest.h>

#include <QVariant>
#include <QList>

#include <QCoreApplication>
#include <QJSValue>
#include <QJSEngine>

#include "Grid/Make.hpp"

namespace grid {
namespace test {

class GridTest : public ::testing::Test {
protected:
    GridTest() {
        // this seems to be hacky
        a = new QCoreApplication(argc, nullptr);
        e = new QJSEngine(a);
        v = e->newArray(width*height);
    }
    ~GridTest() {
        delete a;
    }

    const int width {10};
    const int height {5};
    const int start {12};
    const int end {39};
    QList<int> rawData;
    QVariant varData;

    int argc { 0 };

    QCoreApplication* a;
    QJSEngine* e;
    QJSValue v;
};

TEST_F(GridTest, makesGridWithoutStartPointAndEndPoint)
{
    varData.setValue(rawData);
    Grid grid(varData, width);
    EXPECT_FALSE(grid.getStart());
    EXPECT_FALSE(grid.getEnd());
}

TEST_F(GridTest, makesGridWithoutEndPoint)
{
    v.setProperty(start, 1);
    varData = v.toVariant();

    Grid grid(varData, width);

    auto s = grid.getStart();
    ASSERT_TRUE(s);
    EXPECT_EQ(start, s->id);
    EXPECT_FALSE(grid.getEnd());
}

TEST_F(GridTest, makesGridWithoutStartPoint)
{
    v.setProperty(end, 2);
    varData = v.toVariant();
    Grid grid(varData, width);

    auto e = grid.getEnd();
    ASSERT_TRUE(e);
    EXPECT_EQ(end, e->id);
    EXPECT_FALSE(grid.getStart());
}


TEST_F(GridTest, makesGrid)
{
    v.setProperty(start, 1);
    v.setProperty(end, 2);
    varData = v.toVariant();
    Grid grid(varData, width);

    auto e = grid.getEnd();
    ASSERT_TRUE(e);
    EXPECT_EQ(end, e->id);
    auto s = grid.getStart();
    ASSERT_TRUE(s);
    EXPECT_EQ(start, s->id);
}

TEST_F(GridTest, canCreateGridFromDimentions)
{
    Grid grid(height, width);
    EXPECT_FALSE(grid.getStart());
    EXPECT_FALSE(grid.getEnd());
    EXPECT_EQ(height, grid.getRows().size());
    EXPECT_EQ(width, grid.getRows()[0].size());
}

TEST(MakeGrid, test1) {
    auto grid = grid::make<grid::GridType::Rectangle>(10, 14);
}

}
}
