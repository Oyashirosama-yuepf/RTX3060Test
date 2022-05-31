#include <gtest/gtest.h>
#include <holo/sensors/smart_camera/me8/me8_holocan.h>

TEST(Me8LaneBoundary, construtor_a)
{
    holo::sensors::me8::Me8LaneBoundaryAdjacent lb_a;

    ASSERT_FLOAT_EQ(lb_a.GetLHConfidence(), 0.0f);
    ASSERT_EQ(lb_a.GetLHLanemarkType(), 0u);
    ASSERT_EQ(lb_a.GetLHSide(), 0u);
    ASSERT_FLOAT_EQ(lb_a.GetLHVrStart(), 0.0f);
    ASSERT_FLOAT_EQ(lb_a.GetLHVrEnd(), 0.0f);
    ASSERT_FLOAT_EQ(lb_a.GetLHC0(), 0.0f);
    ASSERT_FLOAT_EQ(lb_a.GetLHC1(), 0.0f);
    ASSERT_FLOAT_EQ(lb_a.GetLHC2(), 0.0f);
    ASSERT_FLOAT_EQ(lb_a.GetLHC3(), 0.0f);
    ASSERT_FALSE(lb_a.GetValid());
}

TEST(Me8LaneBoundary, construtor_h)
{
    holo::sensors::me8::Me8LaneBoundaryHost lb_h;

    ASSERT_EQ(lb_h.GetAdjacentType(), 0u);
    ASSERT_FLOAT_EQ(lb_h.GetAdjacentConfidence(), 0.0f);
    ASSERT_FLOAT_EQ(lb_h.GetAdjacentViewRangeStart(), 0.0f);
    ASSERT_FLOAT_EQ(lb_h.GetAdjacentViewRangeEnd(), 0.0f);
    ASSERT_FLOAT_EQ(lb_h.SetAdjacentC0(), 0.0f);
    ASSERT_FLOAT_EQ(lb_h.SetAdjacentC1(), 0.0f);
    ASSERT_FLOAT_EQ(lb_h.SetAdjacentC2(), 0.0f);
    ASSERT_FLOAT_EQ(lb_h.SetAdjacentC3(), 0.0f);
    ASSERT_FALSE(lb_h.GetValid());
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
