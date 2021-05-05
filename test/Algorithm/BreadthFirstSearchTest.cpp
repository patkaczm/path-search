#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Graph/Graph.hpp"
#include "Graph/Vertex.hpp"

#include "Algorithm/BreadthFirstSearch.hpp"

namespace algorithm {
namespace test {

using graph::Vertex;
using graph::Edge;

struct BreadthFirstSearchTestParams
{
    std::vector<Vertex> vertexes{};
    std::vector<Edge> edges{};
    std::pair<Vertex, Vertex> searchedPath{};
    std::vector<Vertex> path{};
};

class BreadthFirstSearchTest : public ::testing::TestWithParam<BreadthFirstSearchTestParams>{
protected:
    graph::Graph g;
};

TEST_P(BreadthFirstSearchTest, pathSearchingTest)
{
    auto params = GetParam();
    for(const auto& v : params.vertexes) {
        g.add(v);
    }
    for(const auto& e: params.edges) {
        g.add(e);
    }
    BreadthFirstSearch bfs;
    EXPECT_THAT(bfs(g, params.searchedPath.first, params.searchedPath.second),
                ::testing::ContainerEq(params.path));
}

const std::vector<BreadthFirstSearchTestParams> params {
    {
        {Vertex{1}, Vertex{2}, Vertex{3}, Vertex{4}},
        {Edge{{1}, {2}}, Edge{{1}, {3}}, Edge{{2}, {3}}, Edge{{3}, {4}}},
        {Vertex{1}, Vertex{4}},
        {Vertex{1}, Vertex{3}, Vertex{4}}
    },
    {
        {Vertex{1}, Vertex{2}, Vertex{3}, Vertex{4}, Vertex{5}},
        {Edge{{1}, {2}},Edge{{2}, {3}},Edge{{3}, {4}},Edge{{4}, {5}},Edge{{3}, {5}}},
        {Vertex{1}, Vertex{5}},
        {Vertex{1}, Vertex{2}, Vertex{3}, Vertex{5}}
    }
};

INSTANTIATE_TEST_SUITE_P(,
                         BreadthFirstSearchTest,
                         testing::ValuesIn(params));

}
}
