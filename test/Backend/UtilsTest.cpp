#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <set>

#include "Backend/Utils.hpp"
#include "Graph/Graph.hpp"
#include "Backend/Grid.hpp"

namespace utils::test
{

TEST(makeGraph, producesGraph)
{
    grid::Grid grid(2, 2);
    auto graph = makeGraph(grid);

    EXPECT_THAT(graph.getNeighbours(graph::Vertex{0}),
                ::testing::ContainerEq(std::set<graph::Vertex>{graph::Vertex{1}, graph::Vertex{2}}));

    EXPECT_THAT(graph.getNeighbours(graph::Vertex{1}),
                ::testing::ContainerEq(std::set<graph::Vertex>{graph::Vertex{0}, graph::Vertex{3}}));

    EXPECT_THAT(graph.getNeighbours(graph::Vertex{2}),
                ::testing::ContainerEq(std::set<graph::Vertex>{graph::Vertex{0}, graph::Vertex{3}}));

    EXPECT_THAT(graph.getNeighbours(graph::Vertex{3}),
                ::testing::ContainerEq(std::set<graph::Vertex>{graph::Vertex{1}, graph::Vertex{2}}));

}

}
