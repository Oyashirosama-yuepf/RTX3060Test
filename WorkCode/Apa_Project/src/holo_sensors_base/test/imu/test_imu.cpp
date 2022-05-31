#include <gtest/gtest.h>
#include <holo/sensors/imu/imu.h>

using namespace holo;
using namespace holo::sensors;

class ImuDriverTest : public ImuDriverT<int>
{
public:
    ImuDriverTest(const Extrinsicf& extrinsic) : ImuDriverT(extrinsic)
    {
    }
    void ParseData(const int&)
    {
    }
};

static void Callback0(const holo::common::Imud& input, holo::common::Imud& output, bool& called)
{
    output = input;
    called = true;
}

TEST(ImuDriverBase, Constructor)
{
    Extrinsicf                                     extrinsic;
    ImuDriverTest                                  base1(extrinsic);
    holo::common::Imud                             data;
    bool                                           called = false;
    std::function<void(const holo::common::Imud&)> handler =
        std::bind(&Callback0, std::placeholders::_1, std::ref(data), std::ref(called));
    base1.InstallCallback(handler);
    int idata = 0;
    ASSERT_NO_THROW(base1.ParseData(idata));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
