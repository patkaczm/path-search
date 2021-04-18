#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Graph/Graph.hpp"
#include "Graph/Vertex.hpp"

#include "Algorithm/BreadthFirstSearch.hpp"

#include <iostream>

namespace algorithm {
namespace test {

using graph::Vertex;
using graph::Edge;

class BreadthFirstSearchTest : public ::testing::Test{
protected:
    graph::Graph g;
};

TEST_F(BreadthFirstSearchTest, test1)
{
    g.addVertexes(Vertex{1}, Vertex{2}, Vertex{3}, Vertex{4});
    g.addEdges(Edge{{1}, {2}},
               Edge{{1}, {3}},
               Edge{{2}, {3}},
               Edge{{3}, {4}});

    BreadthFirstSearch bfs(g);
    auto path = bfs(Vertex{1}, Vertex{4});
    EXPECT_THAT(path, ::testing::ElementsAre(Vertex{1}, Vertex{3}, Vertex{4}));
}

TEST_F(BreadthFirstSearchTest, test2) {
    g.addVertexes(Vertex{1}, Vertex{2}, Vertex{3}, Vertex{4}, Vertex{5});
    g.addEdges(Edge{{1}, {2}},Edge{{2}, {3}},Edge{{3}, {4}},Edge{{4}, {5}},Edge{{3}, {5}});

    BreadthFirstSearch bfs(g);
    auto path = bfs(Vertex{1}, Vertex{5});
    EXPECT_THAT(path, ::testing::ElementsAre(Vertex{1}, Vertex{2}, Vertex{3}, Vertex{5}));
}

}
}
