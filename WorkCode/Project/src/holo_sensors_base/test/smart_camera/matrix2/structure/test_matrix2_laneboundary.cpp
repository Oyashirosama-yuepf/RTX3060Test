#include <gtest/gtest.h>
#include <holo/sensors/smart_camera/matrix2/structure/matrix2_laneboundary.h>

TEST(HorizonMatrix2LaneBoundary, Construtor)
{
    holo::sensors::horizon_matrix2::HorizonMatrix2LaneBoundary b;
    ASSERT_EQ(b.GetTimestamp().GetSec(), 0u);
    ASSERT_EQ(b.GetTimestamp().GetNsec(), 0u);
}

TEST(HorizonMatrix2LaneBoundary, Copy)
{
    holo::sensors::horizon_matrix2::HorizonMatrix2LaneBoundary b1;
    holo::common::Timestamp                                    input_timestamp(222, 333);
    b1.SetTimestamp(input_timestamp);
    b1.SetConfidence(0.5);
    b1.SetTypeClass(1);
    b1.SetMarkColor(2);
    b1.SetQuality(1);
    b1.SetCrossing(false);
    b1.SetC0(0.1);
    b1.SetC1(0.2);
    b1.SetC2(0.3);
    b1.SetC3(0.4);
    b1.SetTlc(3.0);
    b1.SetWidthMarking(0.15);
    b1.SetViewRangeStart(0);
    b1.SetViewRangeEnd(100);
    b1.SetPartAValid(true);
    b1.SetPartBValid(true);

    holo::sensors::horizon_matrix2::HorizonMatrix2LaneBoundary b2(b1);
    ASSERT_EQ(b2.GetTimestamp().GetSec(), 222);
    ASSERT_EQ(b2.GetTimestamp().GetNsec(), 333);
    ASSERT_EQ(b2.GetConfidence(), 0.5);
    ASSERT_EQ(b2.GetTypeClass(), 1);
    ASSERT_EQ(b2.GetMarkColor(), 2);
    ASSERT_EQ(b2.GetQuality(), 1);
    ASSERT_EQ(b2.GetCrossing(), false);
    ASSERT_FLOAT_EQ(b2.GetC0(), 0.1);
    ASSERT_FLOAT_EQ(b2.GetC1(), 0.2);
    ASSERT_FLOAT_EQ(b2.GetC2(), 0.3);
    ASSERT_FLOAT_EQ(b2.GetC3(), 0.4);
    ASSERT_FLOAT_EQ(b2.GetTlc(), 3.0);
    ASSERT_FLOAT_EQ(b2.GetWidthMarking(), 0.15);
    ASSERT_FLOAT_EQ(b2.GetViewRangeStart(), 0);
    ASSERT_FLOAT_EQ(b2.GetViewRangeEnd(), 100);
    ASSERT_EQ(b2.GetPartAValid(), true);
    ASSERT_EQ(b2.GetPartBValid(), true);
    ASSERT_TRUE(b2.IsAllPartsValid());
}

TEST(HorizonMatrix2LaneBoundary, OpreatorEquale)
{
    holo::sensors::horizon_matrix2::HorizonMatrix2LaneBoundary b1;
    holo::common::Timestamp                                    input_timestamp(222, 333);
    b1.SetTimestamp(input_timestamp);

    holo::sensors::horizon_matrix2::HorizonMatrix2LaneBoundary b2;
    b2 = b1;
    ASSERT_EQ(b2.GetTimestamp().GetSec(), 222);
    ASSERT_EQ(b2.GetTimestamp().GetNsec(), 333);

    b2 = b2;
    ASSERT_EQ(b2.GetTimestamp().GetSec(), 222);
    ASSERT_EQ(b2.GetTimestamp().GetNsec(), 333);
}

TEST(HorizonMatrix2LaneBoundary, ConvertToHoloLaneBoundary1)
{
    auto extrinsic =
        holo::common::Extrinsicf(holo::common::Coordinate(holo::common::Coordinate::BODY),
                                 holo::common::Coordinate(holo::common::Coordinate::UNKNOWN), holo::geometry::Pose3f());
    std::shared_ptr<holo::common::LaneBoundary<holo::numerics::Polynomial<holo::float32_t, 3>>> output = nullptr;
    holo::sensors::horizon_matrix2::HorizonMatrix2LaneBoundary                                  input;
    input.SetViewRangeStart(0);
    input.SetViewRangeEnd(0);
    input.ConvertToHoloLaneBoundary(output, extrinsic);
    ASSERT_TRUE(output != nullptr);
    ASSERT_EQ(output->GetStyle(), holo::common::BoundaryStyle::UNKNOWN);
    ASSERT_EQ(output->GetColor(), holo::common::BoundaryColor::UNKNOWN);
    ASSERT_FLOAT_EQ(output->GetWidth(), 0);
    ASSERT_FLOAT_EQ(output->GetConfidence(), 0);
    auto range = output->GetCoordinateRange();
    ASSERT_EQ(0.0, range.first);
    ASSERT_EQ(0.0, range.second);
}

TEST(HorizonMatrix2LaneBoundary, ConvertToHoloLaneBoundary2)
{
    auto extrinsic =
        holo::common::Extrinsicf(holo::common::Coordinate(holo::common::Coordinate::BODY),
                                 holo::common::Coordinate(holo::common::Coordinate::UNKNOWN), holo::geometry::Pose3f());
    std::shared_ptr<holo::common::LaneBoundary<holo::numerics::Polynomial<holo::float32_t, 3>>> output = nullptr;
    holo::sensors::horizon_matrix2::HorizonMatrix2LaneBoundary                                  input;
    input.SetViewRangeStart(0);
    input.SetViewRangeEnd(25);
    input.ConvertToHoloLaneBoundary(output, extrinsic);
    ASSERT_TRUE(output != nullptr);
    ASSERT_EQ(output->GetStyle(), holo::common::BoundaryStyle::UNKNOWN);
    ASSERT_EQ(output->GetColor(), holo::common::BoundaryColor::WHITE);
    ASSERT_FLOAT_EQ(output->GetWidth(), 0);
    ASSERT_FLOAT_EQ(output->GetConfidence(), 0);
    auto range = output->GetCoordinateRange();
    ASSERT_EQ(0.0, range.first);
    ASSERT_EQ(25.0, range.second);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
