#include <gtest/gtest.h>
#include <holo/sensors/smart_camera/mpc2/mpc2_holocan.h>
#include <holo_c/sensors/dbc/mpc_recv_dbc.h>

using namespace holo;
using namespace holo::sensors::bosch_mpc;

/* obstacle alias */
using ObjectType   = holo::sensors::bosch_mpc::BoschMpcObstacle;
using ObstacleType = holo::obstacle::ObstacleVisionT<float32_t>;
using ObstaclePtrListType =
    holo::obstacle::ObstaclePtrListT<ObstacleType, holo::obstacle::VISION_OBSTACLE_LIST_COMMON_CAPACITY>;
using ObstacleListCallback = std::function<void(const ObstaclePtrListType&)>;
/* lane boundary alias */
using MpcBoundaryType   = holo::sensors::bosch_mpc::BoschMpcLaneBoundary;
using LaneboundaryType  = holo::common::LaneBoundary<holo::numerics::Polynomial<float32_t, 3>>;
using RoadFrameType     = holo::common::RoadFrame<holo::numerics::Polynomial<float32_t, 3>, 8>;
using RoadFrameCallback = std::function<void(const RoadFrameType&)>;

TEST(BoschMpcDriverHoloCan, ConstructLaneBoundaryPartA)
{
    Extrinsicf                     extrinsic;
    BoschMpcDriverT<HoloCanPacket> driver(extrinsic);

    uint8_t raw_data[28];
    (void)std::memcpy(&raw_data[0], "##@!", 4);
    raw_data[4] = 1;
    raw_data[5] = 2;
    raw_data[6] = 8;
    raw_data[7] = 0;

    raw_data[8]  = (0 >> 24) & 0xFF;
    raw_data[9]  = (0 >> 16) & 0xFF;
    raw_data[10] = (0 >> 8) & 0xFF;
    raw_data[11] = (0 >> 0) & 0xFF;

    raw_data[12] = 0;
    raw_data[13] = 0;
    raw_data[14] = 0;
    raw_data[15] = 0;
    raw_data[16] = 0;
    raw_data[17] = 0;
    raw_data[18] = 0;
    raw_data[19] = 0;

    raw_data[20] = (123456789 >> 24) & 0xFF;
    raw_data[21] = (123456789 >> 16) & 0xFF;
    raw_data[22] = (123456789 >> 8) & 0xFF;
    raw_data[23] = (123456789 >> 0) & 0xFF;

    raw_data[24] = (987654321 >> 24) & 0xFF;
    raw_data[25] = (987654321 >> 16) & 0xFF;
    raw_data[26] = (987654321 >> 8) & 0xFF;
    raw_data[27] = (987654321 >> 0) & 0xFF;

    HoloCanPacket packet;
    packet.Deserialize(raw_data, sizeof(raw_data));
    MpcBoundaryType lane_boundary;
    driver.ConstructLaneBoundaryPartA(packet, lane_boundary);
    ASSERT_FLOAT_EQ(lane_boundary.GetDxBegin(), 0.0f);
    ASSERT_FLOAT_EQ(lane_boundary.GetDxEnd(), 0.0f);
    ASSERT_FLOAT_EQ(lane_boundary.GetDy(), -8.0f);
    ASSERT_FLOAT_EQ(lane_boundary.GetConfidence(), 0.0f);
    ASSERT_FLOAT_EQ(lane_boundary.GetAngleDiff(), -1.0f);
    ASSERT_TRUE(lane_boundary.GetPartAValid());
}

TEST(BoschMpcDriverHoloCan, ConstructLaneBoundaryPartB)
{
    Extrinsicf                     extrinsic;
    BoschMpcDriverT<HoloCanPacket> driver(extrinsic);

    uint8_t raw_data[28];
    (void)std::memcpy(&raw_data[0], "##@!", 4);
    raw_data[4] = 1;
    raw_data[5] = 2;
    raw_data[6] = 8;
    raw_data[7] = 0;

    raw_data[8]  = (0 >> 24) & 0xFF;
    raw_data[9]  = (0 >> 16) & 0xFF;
    raw_data[10] = (0 >> 8) & 0xFF;
    raw_data[11] = (0 >> 0) & 0xFF;

    raw_data[12] = 0;
    raw_data[13] = 0;
    raw_data[14] = 0;
    raw_data[15] = 0;
    raw_data[16] = 0;
    raw_data[17] = 0;
    raw_data[18] = 0;
    raw_data[19] = 0;

    raw_data[20] = (123456789 >> 24) & 0xFF;
    raw_data[21] = (123456789 >> 16) & 0xFF;
    raw_data[22] = (123456789 >> 8) & 0xFF;
    raw_data[23] = (123456789 >> 0) & 0xFF;

    raw_data[24] = (987654321 >> 24) & 0xFF;
    raw_data[25] = (987654321 >> 16) & 0xFF;
    raw_data[26] = (987654321 >> 8) & 0xFF;
    raw_data[27] = (987654321 >> 0) & 0xFF;

    HoloCanPacket packet;
    packet.Deserialize(raw_data, sizeof(raw_data));
    MpcBoundaryType lane_boundary;
    driver.ConstructLaneBoundaryPartB(packet, lane_boundary);
    ASSERT_FLOAT_EQ(lane_boundary.GetHorizonCurvature(), -2047);
    ASSERT_FLOAT_EQ(lane_boundary.GetLineWidth(), -0.5);
    ASSERT_FLOAT_EQ(lane_boundary.GetLineNumber(), 0);
    ASSERT_FLOAT_EQ(lane_boundary.GetLineType(), 0);
    ASSERT_FLOAT_EQ(lane_boundary.GetLineColor(), 0);
    ASSERT_TRUE(lane_boundary.GetPartBValid());
    ASSERT_EQ(lane_boundary.GetTimestamp().GetSec(), 123456789);
    ASSERT_EQ(lane_boundary.GetTimestamp().GetNsec(), 987654321);
}

TEST(BoschMpcDriverHoloCan, ConvertToRoadFrameWithTransform)
{
    Extrinsicf                     extrinsic;
    BoschMpcDriverT<HoloCanPacket> driver(extrinsic);

    std::array<MpcBoundaryType, 4> input;
    input[0].SetTimestamp(holo::common::Timestamp(1, 2));
    input[0].SetLineNumber(9);
    input[0].SetLineType(2);
    input[0].SetLineColor(1);
    input[0].SetHorizonCurvature(1);
    input[0].SetDxBegin(1);
    input[0].SetDxEnd(50);
    input[0].SetDy(6);
    input[0].SetAngleDiff(0);
    input[0].SetLineWidth(0.15);
    input[0].SetConfidence(0.1);
    input[0].SetPartAValid(true);
    input[0].SetPartBValid(true);
    input[1].SetTimestamp(holo::common::Timestamp(1, 2));
    input[1].SetLineNumber(10);
    input[1].SetLineType(2);
    input[1].SetLineColor(1);
    input[1].SetHorizonCurvature(1);
    input[1].SetDxBegin(1);
    input[1].SetDxEnd(50);
    input[1].SetDy(2);
    input[1].SetAngleDiff(0);
    input[1].SetLineWidth(0.15);
    input[1].SetConfidence(0.1);
    input[1].SetPartAValid(true);
    input[1].SetPartBValid(true);
    input[2].SetTimestamp(holo::common::Timestamp(1, 2));
    input[2].SetLineNumber(11);
    input[2].SetLineType(2);
    input[2].SetLineColor(1);
    input[2].SetHorizonCurvature(1);
    input[2].SetDxBegin(1);
    input[2].SetDxEnd(50);
    input[2].SetDy(-2);
    input[2].SetAngleDiff(0);
    input[2].SetLineWidth(0.15);
    input[2].SetConfidence(0.1);
    input[2].SetPartAValid(true);
    input[2].SetPartBValid(true);
    input[3].SetTimestamp(holo::common::Timestamp(1, 2));
    input[3].SetLineNumber(12);
    input[3].SetLineType(2);
    input[3].SetLineColor(1);
    input[3].SetHorizonCurvature(1);
    input[3].SetDxBegin(1);
    input[3].SetDxEnd(50);
    input[3].SetDy(-6);
    input[3].SetAngleDiff(0);
    input[3].SetLineWidth(0.15);
    input[3].SetConfidence(0.1);
    input[3].SetPartAValid(true);
    input[3].SetPartBValid(true);
    RoadFrameType output;
    driver.ConvertToRoadFrameWithTransform(input, output);
    ASSERT_FLOAT_EQ(output.GetTimestamp().GetSec(), 1);
    ASSERT_FLOAT_EQ(output.GetTimestamp().GetNsec(), 2);
    ASSERT_EQ(output.at(0).GetStyle(), holo::common::BoundaryStyle::DASHED);
    ASSERT_EQ(output.at(0).GetColor(), holo::common::BoundaryColor::WHITE);
    ASSERT_FLOAT_EQ(output.at(0).GetConfidence(), 10);
    std::pair<float32_t, float32_t> range = output.at(0).GetCoordinateRange();
    ASSERT_FLOAT_EQ(range.first, 1);
    ASSERT_FLOAT_EQ(range.second, 50);
    ASSERT_EQ(output.at(0).GetWidth(), 15);
    holo::geometry::Point2f p0 = output.at(0).GetSampleByCoordinate(0.0f);
    ASSERT_FLOAT_EQ(p0.GetX(), 0.0f);
    ASSERT_FLOAT_EQ(p0.GetY(), 6.0f);
    p0 = output.at(1).GetSampleByCoordinate(0.0f);
    ASSERT_FLOAT_EQ(p0.GetX(), 0.0f);
    ASSERT_FLOAT_EQ(p0.GetY(), 2.0f);
    p0 = output.at(2).GetSampleByCoordinate(0.0f);
    ASSERT_FLOAT_EQ(p0.GetX(), 0.0f);
    ASSERT_FLOAT_EQ(p0.GetY(), -2.0f);
    p0 = output.at(3).GetSampleByCoordinate(0.0f);
    ASSERT_FLOAT_EQ(p0.GetX(), 0.0f);
    ASSERT_FLOAT_EQ(p0.GetY(), -6.0f);
}

TEST(BoschMpcDriverHoloCan, ConvertToRoadFrameWithTransform2)
{
    Extrinsicf                     extrinsic;
    BoschMpcDriverT<HoloCanPacket> driver(extrinsic);

    /* CHANGE TO LEFT */
    std::array<MpcBoundaryType, 4> input;
    input[0].SetTimestamp(holo::common::Timestamp(1, 2));
    input[0].SetLineNumber(9);
    input[0].SetLineType(2);
    input[0].SetLineColor(1);
    input[0].SetHorizonCurvature(1);
    input[0].SetDxBegin(1);
    input[0].SetDxEnd(50);
    input[0].SetDy(6);
    input[0].SetAngleDiff(0);
    input[0].SetLineWidth(0.15);
    input[0].SetConfidence(0.1);
    input[0].SetPartAValid(true);
    input[0].SetPartBValid(true);
    input[1].SetTimestamp(holo::common::Timestamp(1, 2));
    input[1].SetLineNumber(10);
    input[1].SetLineType(2);
    input[1].SetLineColor(1);
    input[1].SetHorizonCurvature(1);
    input[1].SetDxBegin(1);
    input[1].SetDxEnd(50);
    input[1].SetDy(0.25);
    input[1].SetAngleDiff(0);
    input[1].SetLineWidth(0.15);
    input[1].SetConfidence(0.1);
    input[1].SetPartAValid(true);
    input[1].SetPartBValid(true);
    input[2].SetTimestamp(holo::common::Timestamp(1, 2));
    input[2].SetLineNumber(11);
    input[2].SetLineType(2);
    input[2].SetLineColor(1);
    input[2].SetHorizonCurvature(1);
    input[2].SetDxBegin(1);
    input[2].SetDxEnd(50);
    input[2].SetDy(-2);
    input[2].SetAngleDiff(0);
    input[2].SetLineWidth(0.15);
    input[2].SetConfidence(0.1);
    input[2].SetPartAValid(true);
    input[2].SetPartBValid(true);
    input[3].SetTimestamp(holo::common::Timestamp(1, 2));
    input[3].SetLineNumber(12);
    input[3].SetLineType(2);
    input[3].SetLineColor(1);
    input[3].SetHorizonCurvature(1);
    input[3].SetDxBegin(1);
    input[3].SetDxEnd(50);
    input[3].SetDy(-6);
    input[3].SetAngleDiff(0);
    input[3].SetLineWidth(0.15);
    input[3].SetConfidence(0.1);
    input[3].SetPartAValid(true);
    input[3].SetPartBValid(true);
    RoadFrameType output;
    driver.ConvertToRoadFrameWithTransform(input, output);
    ASSERT_FLOAT_EQ(output.GetTimestamp().GetSec(), 1);
    ASSERT_FLOAT_EQ(output.GetTimestamp().GetNsec(), 2);
    auto lbd = output.at(1);
    ASSERT_EQ(lbd.GetStyle(), holo::common::BoundaryStyle::DASHED);
    ASSERT_EQ(lbd.GetColor(), holo::common::BoundaryColor::WHITE);
    ASSERT_FLOAT_EQ(lbd.GetConfidence(), 10);
    std::pair<float32_t, float32_t> range = lbd.GetCoordinateRange();
    ASSERT_FLOAT_EQ(range.first, 1);
    ASSERT_FLOAT_EQ(range.second, 50);
    ASSERT_EQ(lbd.GetWidth(), 15);
    holo::geometry::Point2f p0 = lbd.GetSampleByCoordinate(0.0f);
    ASSERT_FLOAT_EQ(p0.GetX(), 0.0f);
    ASSERT_FLOAT_EQ(p0.GetY(), 0.25f);
    /* KEEP */
    input[0].SetTimestamp(holo::common::Timestamp(1, 2));
    input[0].SetLineNumber(9);
    input[0].SetLineType(2);
    input[0].SetLineColor(1);
    input[0].SetHorizonCurvature(1);
    input[0].SetDxBegin(1);
    input[0].SetDxEnd(50);
    input[0].SetDy(6);
    input[0].SetAngleDiff(0);
    input[0].SetLineWidth(0.15);
    input[0].SetConfidence(0.1);
    input[0].SetPartAValid(true);
    input[0].SetPartBValid(true);
    input[1].SetTimestamp(holo::common::Timestamp(1, 2));
    input[1].SetLineNumber(10);
    input[1].SetLineType(2);
    input[1].SetLineColor(1);
    input[1].SetHorizonCurvature(1);
    input[1].SetDxBegin(1);
    input[1].SetDxEnd(50);
    input[1].SetDy(4);
    input[1].SetAngleDiff(0);
    input[1].SetLineWidth(0.15);
    input[1].SetConfidence(0.1);
    input[1].SetPartAValid(true);
    input[1].SetPartBValid(true);
    input[2].SetTimestamp(holo::common::Timestamp(1, 2));
    input[2].SetLineNumber(11);
    input[2].SetLineType(2);
    input[2].SetLineColor(1);
    input[2].SetHorizonCurvature(1);
    input[2].SetDxBegin(1);
    input[2].SetDxEnd(50);
    input[2].SetDy(-0.46875);
    input[2].SetAngleDiff(0);
    input[2].SetLineWidth(0.15);
    input[2].SetConfidence(0.1);
    input[2].SetPartAValid(true);
    input[2].SetPartBValid(true);
    input[3].SetTimestamp(holo::common::Timestamp(1, 2));
    input[3].SetLineNumber(12);
    input[3].SetLineType(2);
    input[3].SetLineColor(1);
    input[3].SetHorizonCurvature(1);
    input[3].SetDxBegin(1);
    input[3].SetDxEnd(50);
    input[3].SetDy(-6);
    input[3].SetAngleDiff(0);
    input[3].SetLineWidth(0.15);
    input[3].SetConfidence(0.1);
    input[3].SetPartAValid(true);
    input[3].SetPartBValid(true);
    RoadFrameType output2;
    driver.ConvertToRoadFrameWithTransform(input, output2);
    ASSERT_FLOAT_EQ(output2.GetTimestamp().GetSec(), 1);
    ASSERT_FLOAT_EQ(output2.GetTimestamp().GetNsec(), 2);
    auto lbd2 = output2.at(1);
    ASSERT_EQ(lbd2.GetStyle(), holo::common::BoundaryStyle::DASHED);
    ASSERT_EQ(lbd2.GetColor(), holo::common::BoundaryColor::WHITE);
    ASSERT_FLOAT_EQ(lbd2.GetConfidence(), 10);
    std::pair<float32_t, float32_t> range2 = lbd2.GetCoordinateRange();
    ASSERT_FLOAT_EQ(range2.first, 1);
    ASSERT_FLOAT_EQ(range2.second, 50);
    ASSERT_EQ(lbd2.GetWidth(), 15);
    p0 = lbd2.GetSampleByCoordinate(0.0f);
    ASSERT_FLOAT_EQ(p0.GetX(), 0.0f);
    ASSERT_FLOAT_EQ(p0.GetY(), -0.46875f);
    /* CHANGE TO RIGHT */
    input[0].SetTimestamp(holo::common::Timestamp(1, 2));
    input[0].SetLineNumber(9);
    input[0].SetLineType(2);
    input[0].SetLineColor(1);
    input[0].SetHorizonCurvature(1);
    input[0].SetDxBegin(1);
    input[0].SetDxEnd(50);
    input[0].SetDy(6);
    input[0].SetAngleDiff(0);
    input[0].SetLineWidth(0.15);
    input[0].SetConfidence(0.1);
    input[0].SetPartAValid(true);
    input[0].SetPartBValid(true);
    input[1].SetTimestamp(holo::common::Timestamp(1, 2));
    input[1].SetLineNumber(10);
    input[1].SetLineType(2);
    input[1].SetLineColor(1);
    input[1].SetHorizonCurvature(1);
    input[1].SetDxBegin(1);
    input[1].SetDxEnd(50);
    input[1].SetDy(2);
    input[1].SetAngleDiff(0);
    input[1].SetLineWidth(0.15);
    input[1].SetConfidence(0.1);
    input[1].SetPartAValid(true);
    input[1].SetPartBValid(true);
    input[2].SetTimestamp(holo::common::Timestamp(1, 2));
    input[2].SetLineNumber(11);
    input[2].SetLineType(2);
    input[2].SetLineColor(1);
    input[2].SetHorizonCurvature(1);
    input[2].SetDxBegin(1);
    input[2].SetDxEnd(50);
    input[2].SetDy(-0.25);
    input[2].SetAngleDiff(0);
    input[2].SetLineWidth(0.15);
    input[2].SetConfidence(0.1);
    input[2].SetPartAValid(true);
    input[2].SetPartBValid(true);
    input[3].SetTimestamp(holo::common::Timestamp(1, 2));
    input[3].SetLineNumber(12);
    input[3].SetLineType(2);
    input[3].SetLineColor(1);
    input[3].SetHorizonCurvature(1);
    input[3].SetDxBegin(1);
    input[3].SetDxEnd(50);
    input[3].SetDy(-6);
    input[3].SetAngleDiff(0);
    input[3].SetLineWidth(0.15);
    input[3].SetConfidence(0.1);
    input[3].SetPartAValid(true);
    input[3].SetPartBValid(true);
    RoadFrameType output3;
    driver.ConvertToRoadFrameWithTransform(input, output3);
    ASSERT_FLOAT_EQ(output3.GetTimestamp().GetSec(), 1);
    ASSERT_FLOAT_EQ(output3.GetTimestamp().GetNsec(), 2);
    auto lbd3 = output3.at(2);
    ASSERT_EQ(lbd3.GetStyle(), holo::common::BoundaryStyle::DASHED);
    ASSERT_EQ(lbd3.GetColor(), holo::common::BoundaryColor::WHITE);
    ASSERT_FLOAT_EQ(lbd3.GetConfidence(), 10);
    std::pair<float32_t, float32_t> range3 = lbd3.GetCoordinateRange();
    ASSERT_FLOAT_EQ(range3.first, 1);
    ASSERT_FLOAT_EQ(range3.second, 50);
    ASSERT_EQ(lbd3.GetWidth(), 15);
    p0 = lbd3.GetSampleByCoordinate(0.0f);
    ASSERT_FLOAT_EQ(p0.GetX(), 0.0f);
    ASSERT_FLOAT_EQ(p0.GetY(), -0.25f);
    /*  */
    input[0].SetTimestamp(holo::common::Timestamp(1, 2));
    input[0].SetLineNumber(9);
    input[0].SetLineType(2);
    input[0].SetLineColor(1);
    input[0].SetHorizonCurvature(1);
    input[0].SetDxBegin(1);
    input[0].SetDxEnd(50);
    input[0].SetDy(4);
    input[0].SetAngleDiff(0);
    input[0].SetLineWidth(0.15);
    input[0].SetConfidence(0);
    input[0].SetPartAValid(true);
    input[0].SetPartBValid(true);
    input[1].SetTimestamp(holo::common::Timestamp(1, 2));
    input[1].SetLineNumber(10);
    input[1].SetLineType(2);
    input[1].SetLineColor(1);
    input[1].SetHorizonCurvature(1);
    input[1].SetDxBegin(1);
    input[1].SetDxEnd(50);
    input[1].SetDy(-0.46875);
    input[1].SetAngleDiff(0);
    input[1].SetLineWidth(0.15);
    input[1].SetConfidence(0.1);
    input[1].SetPartAValid(true);
    input[1].SetPartBValid(true);
    input[2].SetTimestamp(holo::common::Timestamp(1, 2));
    input[2].SetLineNumber(11);
    input[2].SetLineType(2);
    input[2].SetLineColor(1);
    input[2].SetHorizonCurvature(1);
    input[2].SetDxBegin(1);
    input[2].SetDxEnd(50);
    input[2].SetDy(-2);
    input[2].SetAngleDiff(0);
    input[2].SetLineWidth(0.15);
    input[2].SetConfidence(0.1);
    input[2].SetPartAValid(true);
    input[2].SetPartBValid(true);
    input[3].SetTimestamp(holo::common::Timestamp(1, 2));
    input[3].SetLineNumber(12);
    input[3].SetLineType(2);
    input[3].SetLineColor(1);
    input[3].SetHorizonCurvature(1);
    input[3].SetDxBegin(1);
    input[3].SetDxEnd(50);
    input[3].SetDy(-6);
    input[3].SetAngleDiff(0);
    input[3].SetLineWidth(0.15);
    input[3].SetConfidence(0.1);
    input[3].SetPartAValid(true);
    input[3].SetPartBValid(true);
    RoadFrameType output4;
    driver.ConvertToRoadFrameWithTransform(input, output4);
    ASSERT_FLOAT_EQ(output4.GetTimestamp().GetSec(), 1);
    ASSERT_FLOAT_EQ(output4.GetTimestamp().GetNsec(), 2);
    auto lbd4 = output4.at(2);
    ASSERT_EQ(lbd4.GetStyle(), holo::common::BoundaryStyle::DASHED);
    ASSERT_EQ(lbd4.GetColor(), holo::common::BoundaryColor::WHITE);
    ASSERT_FLOAT_EQ(lbd4.GetConfidence(), 10);
    std::pair<float32_t, float32_t> range4 = lbd4.GetCoordinateRange();
    ASSERT_FLOAT_EQ(range4.first, 1);
    ASSERT_FLOAT_EQ(range4.second, 50);
    ASSERT_EQ(lbd4.GetWidth(), 15);
    p0 = lbd4.GetSampleByCoordinate(0.0f);
    ASSERT_FLOAT_EQ(p0.GetX(), 0.0f);
    ASSERT_FLOAT_EQ(p0.GetY(), -0.46875f);
}

TEST(BoschMpcDriverHoloCan, ConvertToRoadFrameWithTransform3)
{
    Extrinsicf                     extrinsic;
    BoschMpcDriverT<HoloCanPacket> driver(extrinsic);
    std::array<MpcBoundaryType, 4> input;
    input[0].SetTimestamp(holo::common::Timestamp(1, 2));
    input[0].SetLineNumber(9);
    input[0].SetLineType(2);
    input[0].SetLineColor(1);
    input[0].SetHorizonCurvature(1);
    input[0].SetDxBegin(1);
    input[0].SetDxEnd(50);
    input[0].SetDy(6);
    input[0].SetAngleDiff(0);
    input[0].SetLineWidth(0.15);
    input[0].SetConfidence(0.10);
    input[0].SetPartAValid(true);
    input[0].SetPartBValid(true);
    input[1].SetTimestamp(holo::common::Timestamp(1, 2));
    input[1].SetLineNumber(10);
    input[1].SetLineType(2);
    input[1].SetLineColor(1);
    input[1].SetHorizonCurvature(1);
    input[1].SetDxBegin(1);
    input[1].SetDxEnd(50);
    input[1].SetDy(2);
    input[1].SetAngleDiff(0);
    input[1].SetLineWidth(0.15);
    input[1].SetConfidence(0);
    input[1].SetPartAValid(true);
    input[1].SetPartBValid(true);
    input[2].SetTimestamp(holo::common::Timestamp(1, 2));
    input[2].SetLineNumber(11);
    input[2].SetLineType(2);
    input[2].SetLineColor(1);
    input[2].SetHorizonCurvature(1);
    input[2].SetDxBegin(1);
    input[2].SetDxEnd(50);
    input[2].SetDy(-2);
    input[2].SetAngleDiff(0);
    input[2].SetLineWidth(0.15);
    input[2].SetConfidence(0);
    input[2].SetPartAValid(true);
    input[2].SetPartBValid(true);
    input[3].SetTimestamp(holo::common::Timestamp(1, 2));
    input[3].SetLineNumber(12);
    input[3].SetLineType(2);
    input[3].SetLineColor(1);
    input[3].SetHorizonCurvature(1);
    input[3].SetDxBegin(1);
    input[3].SetDxEnd(50);
    input[3].SetDy(-6);
    input[3].SetAngleDiff(0);
    input[3].SetLineWidth(0.15);
    input[3].SetConfidence(0.1);
    input[3].SetPartAValid(true);
    input[3].SetPartBValid(true);
    RoadFrameType output;
    driver.ConvertToRoadFrameWithTransform(input, output);
    ASSERT_FLOAT_EQ(output.GetTimestamp().GetSec(), 1);
    ASSERT_FLOAT_EQ(output.GetTimestamp().GetNsec(), 2);
    auto lbd = output.at(0);
    ASSERT_FLOAT_EQ(lbd.GetConfidence(), 10);
    holo::geometry::Point2f p0 = lbd.GetSampleByCoordinate(0.0f);
    ASSERT_FLOAT_EQ(p0.GetX(), 0.0f);
    ASSERT_FLOAT_EQ(p0.GetY(), 6.0f);
    auto lbd2 = output.at(3);
    ASSERT_FLOAT_EQ(lbd2.GetConfidence(), 10);
    holo::geometry::Point2f p1 = lbd2.GetSampleByCoordinate(0.0f);
    ASSERT_FLOAT_EQ(p1.GetX(), 0.0f);
    ASSERT_FLOAT_EQ(p1.GetY(), -6.0f);
}

TEST(BoschMpcDriverHoloCan, ConvertToRoadFrameWithTransform4)
{
    Extrinsicf                     extrinsic;
    BoschMpcDriverT<HoloCanPacket> driver(extrinsic);
    std::array<MpcBoundaryType, 4> input;
    input[0].SetTimestamp(holo::common::Timestamp(1, 2));
    input[0].SetLineNumber(9);
    input[0].SetLineType(2);
    input[0].SetLineColor(1);
    input[0].SetHorizonCurvature(1);
    input[0].SetDxBegin(1);
    input[0].SetDxEnd(50);
    input[0].SetDy(6);
    input[0].SetAngleDiff(0);
    input[0].SetLineWidth(0.15);
    input[0].SetConfidence(0);
    input[0].SetPartAValid(true);
    input[0].SetPartBValid(true);
    input[1].SetTimestamp(holo::common::Timestamp(1, 2));
    input[1].SetLineNumber(10);
    input[1].SetLineType(2);
    input[1].SetLineColor(1);
    input[1].SetHorizonCurvature(1);
    input[1].SetDxBegin(1);
    input[1].SetDxEnd(50);
    input[1].SetDy(2);
    input[1].SetAngleDiff(0);
    input[1].SetLineWidth(0.15);
    input[1].SetConfidence(0.1);
    input[1].SetPartAValid(true);
    input[1].SetPartBValid(true);
    input[2].SetTimestamp(holo::common::Timestamp(1, 2));
    input[2].SetLineNumber(11);
    input[2].SetLineType(2);
    input[2].SetLineColor(1);
    input[2].SetHorizonCurvature(1);
    input[2].SetDxBegin(1);
    input[2].SetDxEnd(50);
    input[2].SetDy(-2);
    input[2].SetAngleDiff(0);
    input[2].SetLineWidth(0.15);
    input[2].SetConfidence(0);
    input[2].SetPartAValid(true);
    input[2].SetPartBValid(true);
    input[3].SetTimestamp(holo::common::Timestamp(1, 2));
    input[3].SetLineNumber(12);
    input[3].SetLineType(2);
    input[3].SetLineColor(1);
    input[3].SetHorizonCurvature(1);
    input[3].SetDxBegin(1);
    input[3].SetDxEnd(50);
    input[3].SetDy(-6);
    input[3].SetAngleDiff(0);
    input[3].SetLineWidth(0.15);
    input[3].SetConfidence(0);
    input[3].SetPartAValid(true);
    input[3].SetPartBValid(true);
    RoadFrameType output;
    driver.ConvertToRoadFrameWithTransform(input, output);
    ASSERT_FLOAT_EQ(output.GetTimestamp().GetSec(), 1);
    ASSERT_FLOAT_EQ(output.GetTimestamp().GetNsec(), 2);
    auto lbd = output.at(1);
    ASSERT_FLOAT_EQ(lbd.GetConfidence(), 10);
    holo::geometry::Point2f p0 = lbd.GetSampleByCoordinate(0.0f);
    ASSERT_FLOAT_EQ(p0.GetX(), 0.0f);
    ASSERT_FLOAT_EQ(p0.GetY(), 2.0f);
}

static void RfCallback(const RoadFrameType& roadframe, RoadFrameType& copy, bool& called)
{
    copy   = roadframe;
    called = true;
}

TEST(BoschMpcDriverHoloCan, ParseData)
{
    Extrinsicf                     extrinsic;
    BoschMpcDriverT<HoloCanPacket> driver(extrinsic);
    RoadFrameType                  roadframe;
    bool                           called = false;
    auto h = std::bind(&RfCallback, std::placeholders::_1, std::ref(roadframe), std::ref(called));
    driver.InstallCallback(h);

    const uint32_t id_list[9] = {0x240, 0x241, 0x243, 0x244, 0x246, 0x247, 0x249, 0x24A, 0x000};

    uint8_t raw_data[28];
    (void)std::memcpy(&raw_data[0], "##@!", 4);
    for (int i = 0; i < 9; ++i)
    {
        raw_data[8]  = (id_list[i] >> 24) & 0xFF;
        raw_data[9]  = (id_list[i] >> 16) & 0xFF;
        raw_data[10] = (id_list[i] >> 8) & 0xFF;
        raw_data[11] = (id_list[i] >> 0) & 0xFF;
        HoloCanPacket packet;
        packet.Deserialize(raw_data, sizeof(raw_data));
        ASSERT_NO_THROW(driver.ParseData(packet));
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
