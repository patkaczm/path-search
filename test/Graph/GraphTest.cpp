#include <gtest/gtest.h>

#include "Graph/Graph.hpp"
#include "Graph/Vertex.hpp"

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
    g.add(v1);
    g.add(v2);
    Edge e {v1, v2};
    EXPECT_TRUE(g.add(e));
}

TEST_F(GraphTest, cannotAddSameVertexTwice)
{
    Vertex v1{1};

    EXPECT_TRUE(g.add(v1));
    EXPECT_FALSE(g.add(v1));
}

TEST_F(GraphTest, cannotInsertEdgeBetweenInexistentVertexes)
{
    Vertex v1{1};
    Vertex v2{2};
    Edge e {v1, v2};
    EXPECT_THROW(g.add(e), VertexDoesNotExist);
}

TEST_F(GraphTest, cannotAddSameEdgeTwice)
{
    Vertex v1{1};
    Vertex v2{2};
    Edge e {v1, v2};
    g.add(v1);
    g.add(v2);
    EXPECT_TRUE(g.add(e));
    EXPECT_FALSE(g.add(e));
}

}
}
