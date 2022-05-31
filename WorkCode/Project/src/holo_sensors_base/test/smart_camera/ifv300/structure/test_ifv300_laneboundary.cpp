#include <gtest/gtest.h>
#include <holo/sensors/smart_camera/ifv300/structure/ifv300_laneboundary.h>

TEST(Ifv300LaneBoundary, Construtor)
{
    holo::sensors::ifv300::Ifv300LaneBoundary b;

    ASSERT_EQ(b.GetTimestamp().GetSec(), 0u);
    ASSERT_EQ(b.GetTimestamp().GetNsec(), 0u);
    ASSERT_FLOAT_EQ(b.GetA0(), 0.0f);
    ASSERT_FLOAT_EQ(b.GetA1(), 0.0f);
    ASSERT_FLOAT_EQ(b.GetA2(), 0.0f);
    ASSERT_FLOAT_EQ(b.GetA3(), 0.0f);
    ASSERT_FLOAT_EQ(b.GetRange(), 0.0f);
    ASSERT_EQ(b.GetType(), 0);
    ASSERT_EQ(b.GetColor(), 0);
    ASSERT_EQ(b.GetQuality(), 0);
    ASSERT_FALSE(b.GetValid());
}

TEST(Ifv300LaneBoundary, Copy)
{
    holo::sensors::ifv300::Ifv300LaneBoundary b1;
    holo::common::Timestamp                   input_timestamp(222, 333);
    b1.SetTimestamp(input_timestamp);
    b1.SetA0(0.01);
    b1.SetA1(0.02);
    b1.SetA2(0.03);
    b1.SetA3(0.04);
    b1.SetRange(87.6);
    b1.SetType(1);
    b1.SetColor(2);
    b1.SetQuality(3);
    b1.SetValid(true);

    holo::sensors::ifv300::Ifv300LaneBoundary b2(b1);

    ASSERT_EQ(b2.GetTimestamp().GetSec(), 222);
    ASSERT_EQ(b2.GetTimestamp().GetNsec(), 333);
    ASSERT_FLOAT_EQ(b1.GetA0(), 0.01);
    ASSERT_FLOAT_EQ(b1.GetA1(), 0.02);
    ASSERT_FLOAT_EQ(b1.GetA2(), 0.03);
    ASSERT_FLOAT_EQ(b1.GetA3(), 0.04);
    ASSERT_FLOAT_EQ(b1.GetRange(), 87.6);
    ASSERT_EQ(b1.GetType(), 1);
    ASSERT_EQ(b1.GetColor(), 2);
    ASSERT_EQ(b1.GetQuality(), 3);
    ASSERT_TRUE(b1.GetValid());
}

TEST(Ifv300LaneBoundary, OpreatorEquale)
{
    holo::sensors::ifv300::Ifv300LaneBoundary b1;
    holo::common::Timestamp                   input_timestamp(222, 333);
    b1.SetTimestamp(input_timestamp);

    holo::sensors::ifv300::Ifv300LaneBoundary b2;
    b2 = b1;
    ASSERT_EQ(b2.GetTimestamp().GetSec(), 222);
    ASSERT_EQ(b2.GetTimestamp().GetNsec(), 333);
    b2 = b2;
    ASSERT_EQ(b2.GetTimestamp().GetSec(), 222);
    ASSERT_EQ(b2.GetTimestamp().GetNsec(), 333);
}

TEST(Ifv300LaneBoundary, ConvertToHoloLaneBoundary1)
{
    auto extrinsic =
        holo::common::Extrinsicf(holo::common::Coordinate(holo::common::Coordinate::BODY),
                                 holo::common::Coordinate(holo::common::Coordinate::UNKNOWN), holo::geometry::Pose3f());
    holo::sensors::ifv300::Ifv300LaneBoundary                                                   input;
    std::shared_ptr<holo::common::LaneBoundary<holo::numerics::Polynomial<holo::float32_t, 3>>> output = nullptr;
    input.ConvertToHoloLaneBoundary(output, extrinsic);
    ASSERT_EQ(output->GetStyle(), holo::common::BoundaryStyle::UNKNOWN);
    ASSERT_EQ(output->GetColor(), holo::common::BoundaryColor::UNKNOWN);
    ASSERT_FLOAT_EQ(output->GetWidth(), 0);
    ASSERT_FLOAT_EQ(output->GetConfidence(), 0);
}

TEST(Ifv300LaneBoundary, ConvertToHoloLaneBoundary2)
{
    auto extrinsic =
        holo::common::Extrinsicf(holo::common::Coordinate(holo::common::Coordinate::BODY),
                                 holo::common::Coordinate(holo::common::Coordinate::UNKNOWN), holo::geometry::Pose3f());
    holo::sensors::ifv300::Ifv300LaneBoundary input;
    input.SetA0(0.01);
    input.SetA1(0.02);
    input.SetA2(0.03);
    input.SetA3(0.04);
    input.SetRange(87.6);
    input.SetType(1);
    input.SetColor(2);
    input.SetQuality(3);
    input.SetValid(true);
    std::shared_ptr<holo::common::LaneBoundary<holo::numerics::Polynomial<holo::float32_t, 3>>> output = nullptr;
    input.ConvertToHoloLaneBoundary(output, extrinsic);
    ASSERT_EQ(output->GetStyle(), holo::common::BoundaryStyle::SOLID);
    ASSERT_EQ(output->GetColor(), holo::common::BoundaryColor::WHITE);
    ASSERT_EQ(output->GetWidth(), 15);
    ASSERT_EQ(output->GetConfidence(), 100);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
