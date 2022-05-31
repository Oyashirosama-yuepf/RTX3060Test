#include <holo/log/hololog.h>
#include <gtest/gtest.h>
#include <holo/sensors/format/pandar.h>

using namespace holo::sensors::format;

TEST(PandarBlockTest, Construct)
{
    PandarBlock b;
    ASSERT_EQ(b.Valid(), false);
    ASSERT_EQ(b.Azimuth(), 0.0f);
    ASSERT_EQ(b.Depth(0), 0.0f);
    ASSERT_EQ(b.Intensity(0), 0.0f);
}

TEST(PandarPacketTest, Construct)
{
    PandarPacket p;
    ASSERT_EQ(p.Block(0).Valid(), false);
}

TEST(PandarGpsPacketTest, Construct)
{
    PandarGpsPacket g;
    ASSERT_EQ(g.Valid(), false);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
