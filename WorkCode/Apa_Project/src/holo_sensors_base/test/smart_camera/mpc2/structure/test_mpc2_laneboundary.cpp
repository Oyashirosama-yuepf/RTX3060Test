#include <gtest/gtest.h>
#include <holo/sensors/smart_camera/mpc2/structure/mpc2_laneboundary.h>

TEST(BoschMpcLaneBoundary, Construtor)
{
    holo::sensors::bosch_mpc::BoschMpcLaneBoundary b;

    ASSERT_EQ(b.GetTimestamp().GetSec(), 0u);
    ASSERT_EQ(b.GetTimestamp().GetNsec(), 0u);
    ASSERT_EQ(b.GetLineNumber(), 0u);
    ASSERT_EQ(b.GetLineType(), 0u);
    ASSERT_EQ(b.GetLineColor(), 0u);
    ASSERT_EQ(b.GetHorizonCurvature(), 0);
    ASSERT_FLOAT_EQ(b.GetDxBegin(), 0.0f);
    ASSERT_FLOAT_EQ(b.GetDxEnd(), 0.0f);
    ASSERT_FLOAT_EQ(b.GetDy(), 0.0f);
    ASSERT_FLOAT_EQ(b.GetAngleDiff(), 0.0f);
    ASSERT_FLOAT_EQ(b.GetLineWidth(), 0.0f);
    ASSERT_FLOAT_EQ(b.GetConfidence(), 0.0f);
    ASSERT_FALSE(b.GetPartAValid());
    ASSERT_FALSE(b.GetPartBValid());
}

TEST(BoschMpcLaneBoundary, Copy)
{
    holo::sensors::bosch_mpc::BoschMpcLaneBoundary b1;
    holo::common::Timestamp                        input_timestamp(222, 333);
    b1.SetTimestamp(input_timestamp);
    b1.SetLineNumber(1234u);
    b1.SetLineType(5678u);
    b1.SetLineColor(9999u);
    b1.SetHorizonCurvature(-1234);
    b1.SetDxBegin(0.0f);
    b1.SetDxEnd(100.0f);
    b1.SetDy(2.5f);
    b1.SetAngleDiff(0.1f);
    b1.SetLineWidth(0.2f);
    b1.SetConfidence(0.9876f);
    b1.SetPartAValid(true);
    b1.SetPartBValid(true);

    holo::sensors::bosch_mpc::BoschMpcLaneBoundary b2(b1);

    ASSERT_EQ(b2.GetTimestamp().GetSec(), 222);
    ASSERT_EQ(b2.GetTimestamp().GetNsec(), 333);
    ASSERT_EQ(b2.GetLineNumber(), 1234u);
    ASSERT_EQ(b2.GetLineType(), 5678u);
    ASSERT_EQ(b2.GetLineColor(), 9999u);
    ASSERT_EQ(b2.GetHorizonCurvature(), -1234);
    ASSERT_FLOAT_EQ(b2.GetDxBegin(), 0.0f);
    ASSERT_FLOAT_EQ(b2.GetDxEnd(), 100.0f);
    ASSERT_FLOAT_EQ(b2.GetDy(), 2.5f);
    ASSERT_FLOAT_EQ(b2.GetAngleDiff(), 0.1f);
    ASSERT_FLOAT_EQ(b2.GetLineWidth(), 0.2f);
    ASSERT_FLOAT_EQ(b2.GetConfidence(), 0.9876f);
    ASSERT_TRUE(b2.GetPartAValid());
    ASSERT_TRUE(b2.GetPartBValid());
}

TEST(BoschMpcLaneBoundary, OpreatorEquale)
{
    holo::sensors::bosch_mpc::BoschMpcLaneBoundary b1;
    holo::common::Timestamp                        input_timestamp(222, 333);
    b1.SetTimestamp(input_timestamp);
    b1.SetLineNumber(1234u);
    b1.SetLineType(5678u);
    b1.SetLineColor(9999u);
    b1.SetHorizonCurvature(-1234);
    b1.SetDxBegin(0.0f);
    b1.SetDxEnd(100.0f);
    b1.SetDy(2.5f);
    b1.SetAngleDiff(0.1f);
    b1.SetLineWidth(0.2f);
    b1.SetConfidence(0.9876f);
    b1.SetPartAValid(true);
    b1.SetPartBValid(true);

    holo::sensors::bosch_mpc::BoschMpcLaneBoundary b2;

    b2 = b1;

    ASSERT_EQ(b2.GetTimestamp().GetSec(), 222);
    ASSERT_EQ(b2.GetTimestamp().GetNsec(), 333);
    ASSERT_EQ(b2.GetLineNumber(), 1234u);
    ASSERT_EQ(b2.GetLineType(), 5678u);
    ASSERT_EQ(b2.GetLineColor(), 9999u);
    ASSERT_EQ(b2.GetHorizonCurvature(), -1234);
    ASSERT_FLOAT_EQ(b2.GetDxBegin(), 0.0f);
    ASSERT_FLOAT_EQ(b2.GetDxEnd(), 100.0f);
    ASSERT_FLOAT_EQ(b2.GetDy(), 2.5f);
    ASSERT_FLOAT_EQ(b2.GetAngleDiff(), 0.1f);
    ASSERT_FLOAT_EQ(b2.GetLineWidth(), 0.2f);
    ASSERT_FLOAT_EQ(b2.GetConfidence(), 0.9876f);
    ASSERT_TRUE(b2.GetPartAValid());
    ASSERT_TRUE(b2.GetPartBValid());

    ASSERT_NO_THROW(b2 = b2);
    ASSERT_TRUE(b2.GetPartAValid());
    ASSERT_TRUE(b2.GetPartBValid());
}

TEST(BoschMpcLaneBoundary, ConvertToHoloLaneBoundary)
{
    auto extrinsic =
        holo::common::Extrinsicf(holo::common::Coordinate(holo::common::Coordinate::BODY),
                                 holo::common::Coordinate(holo::common::Coordinate::UNKNOWN), holo::geometry::Pose3f());
    holo::sensors::bosch_mpc::BoschMpcLaneBoundary                                              input;
    std::shared_ptr<holo::common::LaneBoundary<holo::numerics::Polynomial<holo::float32_t, 3>>> output = nullptr;
    input.ConvertToHoloLaneBoundary(output, extrinsic);
    ASSERT_EQ(output->GetStyle(), holo::common::BoundaryStyle::UNKNOWN);
    ASSERT_EQ(output->GetColor(), holo::common::BoundaryColor::UNKNOWN);
    ASSERT_FLOAT_EQ(output->GetWidth(), 0.0f);
    ASSERT_FLOAT_EQ(output->GetConfidence(), 0.0f);
}

TEST(BoschMpcLaneBoundary, ConvertToHoloLaneBoundaryWithTransform)
{
    auto extrinsic =
        holo::common::Extrinsicf(holo::common::Coordinate(holo::common::Coordinate::BODY),
                                 holo::common::Coordinate(holo::common::Coordinate::UNKNOWN), holo::geometry::Pose3f());
    holo::sensors::bosch_mpc::BoschMpcLaneBoundary                                              input;
    std::shared_ptr<holo::common::LaneBoundary<holo::numerics::Polynomial<holo::float32_t, 3>>> output = nullptr;
    input.ConvertToHoloLaneBoundary(output, extrinsic);
    ASSERT_EQ(output->GetStyle(), holo::common::BoundaryStyle::UNKNOWN);
    ASSERT_EQ(output->GetColor(), holo::common::BoundaryColor::UNKNOWN);
    ASSERT_FLOAT_EQ(output->GetWidth(), 0.0f);
    ASSERT_FLOAT_EQ(output->GetConfidence(), 0.0f);
}

TEST(BoschMpcLaneBoundary, Serialize4)
{
    holo::sensors::bosch_mpc::BoschMpcLaneBoundary b1;
    (void)b1;
}

TEST(BoschMpcLaneBoundary, Serialize8)
{
    holo::sensors::bosch_mpc::BoschMpcLaneBoundary b1;
    (void)b1;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
