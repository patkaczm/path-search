#include <gtest/gtest.h>
#include <gmock/gmock.h>

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
    g.addVertexes(v1, v2);
    EXPECT_TRUE(g.add(e));
    EXPECT_FALSE(g.add(e));
}

TEST_F(GraphTest, neighboursListForNotConnectedVertexIsEmpty)
{
    g.addVertexes(Vertex{1}, Vertex{2});
    auto neighbours = g.getNeighbours(Vertex{1});
    EXPECT_TRUE(neighbours.empty());
}

TEST_F(GraphTest, throwWhenGettingNeighbourListForNonExistingVertes)
{
    EXPECT_THROW(g.getNeighbours(Vertex{1}), VertexDoesNotExist);
}

TEST_F(GraphTest, canCreateConnectedGraph)
{
    using ::testing::UnorderedElementsAre;
    g.addVertexes(Vertex{1}, Vertex{2}, Vertex{3}, Vertex{4});
    g.addEdges(Edge{{1}, {2}},
               Edge{{1}, {3}},
               Edge{{2}, {3}},
               Edge{{3}, {4}});
    EXPECT_THAT(g.getNeighbours({1}), UnorderedElementsAre(Vertex{2}, Vertex{3}));
    EXPECT_THAT(g.getNeighbours({2}), UnorderedElementsAre(Vertex{1}, Vertex{3}));
    EXPECT_THAT(g.getNeighbours({3}), UnorderedElementsAre(Vertex{1}, Vertex{2}, Vertex{4}));
    EXPECT_THAT(g.getNeighbours({4}), UnorderedElementsAre(Vertex{3}));
}


}
}
