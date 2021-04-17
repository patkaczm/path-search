#include <gtest/gtest.h>

#include "Graph/Graph.hpp"

namespace graph {
namespace test {

class GraphTest : public ::testing::Test
{

};

TEST_F(GraphTest, creates)
{
    Graph();
}

}
}
