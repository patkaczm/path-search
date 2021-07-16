#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Algorithm/PathFinding/PathFinding.hpp"
#include "Algorithm/AlgorithmList/AlgorithmList.hpp"

namespace algorithm {
namespace test {

class DummyAlgorithm : public PathFinding
{
public:
    Path findPath(const graph::Graph& , const graph::Vertex& , const graph::Vertex& ) const override {
        return {};
    }
    void vertexVisited(const graph::Vertex&) const override {}
};

class DummyAlgorithm2 : public DummyAlgorithm
{
};

class AlgorithmListTest : public ::testing::Test {
protected:
    AlgorithmList<PathFinding> algorithmList;
};

TEST_F(AlgorithmListTest, getSelectedIsEmptyAtTheBegining)
{
    EXPECT_EQ(nullptr, algorithmList.getSelected());
}

TEST_F(AlgorithmListTest, getAlgorithmListIsEmptyAtTheBegining)
{
    EXPECT_TRUE(algorithmList.getAlgorithmList().empty());
}

TEST_F(AlgorithmListTest, canRegisterAlgorithm) {
    const std::string algorithmName {"Dummy"};
    algorithmList.registerAlgorithm(algorithmName, std::make_unique<DummyAlgorithm>());
    EXPECT_THAT(algorithmList.getAlgorithmList(), ::testing::Contains(algorithmName));
}

TEST_F(AlgorithmListTest, cannotRegisterSameAlgorithmTwice)
{
    const std::string algorithmName {"Dummy"};
    algorithmList.registerAlgorithm(algorithmName, std::make_unique<DummyAlgorithm>());
    EXPECT_THROW(algorithmList.registerAlgorithm(algorithmName, std::make_unique<DummyAlgorithm>()), std::logic_error);
}

TEST_F(AlgorithmListTest, cannotRegisterAlgorithmWithSameNameTwice)
{
    const std::string algorithmName {"Dummy"};
    algorithmList.registerAlgorithm(algorithmName, std::make_unique<DummyAlgorithm>());
    EXPECT_THROW(algorithmList.registerAlgorithm(algorithmName, std::make_unique<DummyAlgorithm2>()), std::logic_error);
}

TEST_F(AlgorithmListTest, registerMultipleAlgorithms)
{
    const std::string algorithmName {"Dummy"};
    const std::string algorithmName2 {"Dummy2"};
    EXPECT_NO_THROW(algorithmList.registerAlgorithm(algorithmName, std::make_unique<DummyAlgorithm>()));
    EXPECT_NO_THROW(algorithmList.registerAlgorithm(algorithmName2, std::make_unique<DummyAlgorithm2>()));
}

TEST_F(AlgorithmListTest, throwWhenSelectAlgorithmWhichDontExist)
{
    const std::string algorithmName {"Dummy"};
    EXPECT_THROW(algorithmList.selectAlgorithm(algorithmName), std::logic_error);
}

TEST_F(AlgorithmListTest, canSelectRegisteredAlgorithm)
{
    const std::string algorithmName {"Dummy"};
    EXPECT_NO_THROW(algorithmList.registerAlgorithm(algorithmName, std::make_unique<DummyAlgorithm>()));
    EXPECT_NO_THROW(algorithmList.selectAlgorithm(algorithmName));
}

TEST_F(AlgorithmListTest, canGetSelectedAlgorithm)
{
    auto ptr = std::make_unique<DummyAlgorithm>();
    auto* obj_addr = ptr.get();
    const std::string algorithmName {"Dummy"};
    EXPECT_NO_THROW(algorithmList.registerAlgorithm(algorithmName, std::move(ptr)));
    ASSERT_EQ(nullptr, ptr);
    ASSERT_NE(nullptr, obj_addr);
    EXPECT_NO_THROW(algorithmList.selectAlgorithm(algorithmName));
    EXPECT_EQ(algorithmList.getSelected(), obj_addr);
}

}
}
