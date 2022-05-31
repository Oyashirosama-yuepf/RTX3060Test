#include <holo/log/hololog.h>
#include <gtest/gtest.h>
#include <holo/sensors/format/livox.h>

using namespace holo::sensors::format;

TEST(LivoxPointTest, Construct)
{
    LivoxPoint p;
    ASSERT_EQ(p.GetX(), 0);
    ASSERT_EQ(p.GetY(), 0);
    ASSERT_EQ(p.GetZ(), 0);
    ASSERT_EQ(p.GetIntensity(), 0u);
    ASSERT_EQ(p.GetTag(), 0);
    ASSERT_EQ(p.GetReturnNum(), 0);
}

TEST(LivoxPacketTest, Construct)
{
    LivoxPacket<100> p;
    uint32_t         size = 18 + 100 * 14;
    ASSERT_EQ(p.GetSerializedSize(), size);
    ASSERT_EQ(p.Point(0)->GetX(), 0);
    ASSERT_EQ(p.Point(0)->GetY(), 0);
    ASSERT_EQ(p.Point(0)->GetZ(), 0);
    ASSERT_EQ(p.Point(0)->GetIntensity(), 0u);
}

TEST(LivoxHapPacketTest, Construct)
{
    LivoxHapPacket<100> p;
    uint32_t            size = 24 + 100 * 14;
    ASSERT_EQ(p.GetSerializedSize(), size);
    ASSERT_EQ(p.Point(0)->GetX(), 0);
    ASSERT_EQ(p.Point(0)->GetY(), 0);
    ASSERT_EQ(p.Point(0)->GetZ(), 0);
    ASSERT_EQ(p.Point(0)->GetIntensity(), 0u);
}

TEST(LidarLogInfoTest, Construct)
{
    const uint8_t   LOG_HEAD = 9u;
    uint8_t         data[20] = {1, 2, 3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    LivoxHapLogInfo info;
    info.Deserialize(data, 20);

    ASSERT_EQ(info.LogType(), 1);
    ASSERT_EQ(info.FileIndex(), 2);
    ASSERT_EQ(info.Rsvd(), 3);
    ASSERT_EQ(info.TransIndex(), 0xFFFFFFFF);
    ASSERT_EQ(info.LogDataLength(), 0xFFFF);
    for (int i = 0; i < 20 - LOG_HEAD; i++)
    {
        ASSERT_EQ(info.LogData()[i], 0);
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
