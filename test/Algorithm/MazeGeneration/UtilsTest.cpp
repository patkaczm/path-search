#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Algorithm/MazeGeneration/Utils.hpp"

#include <set>
#include "Graph/Vertex.hpp"

namespace algorithm {
namespace utils {
namespace test {

TEST(GetUnvisitedTest, getSetDifference)
{
    std::set<graph::Vertex> a {graph::Vertex{1},
                               graph::Vertex{2},
                              graph::Vertex{3}};
    std::set<graph::Vertex> b {graph::Vertex{1}};
    std::set<graph::Vertex> res {graph::Vertex{2},
            graph::Vertex{3}};

    EXPECT_THAT(getUnvisited(a, b), ::testing::ContainerEq(res));
}

}
}
}
