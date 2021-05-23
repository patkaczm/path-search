#include <memory>
#include <gmock/gmock.h>

namespace utils {
namespace mocks {

template <class TMock>
class MockTestListener : public ::testing::EmptyTestEventListener
{
public:
    MockTestListener(std::unique_ptr<TMock>& mockRef)
        : mock(mockRef)
    {}
    void OnTestStart(const ::testing::TestInfo&) final override
    {
        mock = std::make_unique<TMock>();
    }
    void OnTestPartResult(const ::testing::TestPartResult&) final override
    {
    }
    void OnTestEnd(const ::testing::TestInfo&) final override
    {
        delete mock.release();
    }
private:
    std::unique_ptr<TMock>& mock;
};

template <class TMock, template <class> class MockKindness = ::testing::StrictMock>
class MockInstance
{
public:
    using MockType = MockKindness<TMock>;
    typedef MockTestListener<MockType> MockListener;

    static MockType& instance()
    {
        static auto mock = std::make_unique<MockType>();
        static MockListener* listener = nullptr;
        if (!listener) {
            ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();
            listener = new MockListener(mock);
            listeners.Append(listener);
        }
        return *(mock.get());
    }

};

}
}
