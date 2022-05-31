#include <gtest/gtest.h>
#include <holo/sensors/common/device.h>

TEST(Device, ConstructorDefault)
{
    holo::sensors::common::Device dev;
    ASSERT_EQ(static_cast<uint32_t>(dev.GetSensorId()), 0);
}

TEST(Device, ConstructorSensorId)
{
    holo::sensors::common::Device dev(holo::sensors::common::Device::SensorId(1234));
    ASSERT_EQ(static_cast<uint32_t>(dev.GetSensorId()), 1234);
}

TEST(Device, GetSetSensorId)
{
    holo::sensors::common::Device dev;
    dev.SetSensorId(holo::sensors::common::Device::SensorId(1234));
    ASSERT_EQ(static_cast<uint32_t>(dev.GetSensorId()), 1234);
    dev.SetSensorId(5678);
    ASSERT_EQ(static_cast<uint32_t>(dev.GetSensorId()), 5678);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
