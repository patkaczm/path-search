#include <gtest/gtest.h>

#include "Graph/Graph.hpp"

namespace graph {
namespace test {

class GraphTest : public ::testing::Test
{
public:
    Graph g;
};

TEST_F(GraphTest, creates)
{
    Graph();
}

TEST_F(GraphTest, canAddVertex)
{
    Vertex v{1};
    Graph g;
    EXPECT_TRUE(g.add(v));
}

TEST_F(GraphTest, canAddEdge)
{
    Vertex v1{1};
    Vertex v2{2};
    Edge e {v1, v2};
    EXPECT_TRUE(g.add(e));
}

}
}
