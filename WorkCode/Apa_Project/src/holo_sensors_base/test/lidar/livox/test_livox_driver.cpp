#include <gtest/gtest.h>
#include <holo/sensors/lidar/livox/livox_driver.h>

using namespace holo;
using namespace holo::sensors::livox;
using namespace holo::sensors::format;

TEST(LivoxDriverTest, Constructor)
{
    LivoxDriver<LivoxPacket<96>> driver(1234, 240000 / 96, 10);
    LivoxPacket<96>              packet;
    EXPECT_NO_THROW(driver.PushPacket(packet));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
