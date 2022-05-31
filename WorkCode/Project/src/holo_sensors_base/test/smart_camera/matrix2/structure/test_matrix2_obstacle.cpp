#include <gtest/gtest.h>
#include <holo/sensors/smart_camera/matrix2/structure/matrix2_obstacle.h>

static const holo::float32_t EPSILON = 10e-6;
TEST(HorizonMatrix2Obstacle, Construtor)
{
    holo::sensors::horizon_matrix2::HorizonMatrix2Obstacle obs;

    ASSERT_EQ(obs.GetTimestamp().GetSec(), 0u);
    ASSERT_EQ(obs.GetTimestamp().GetNsec(), 0u);
}

TEST(HorizonMatrix2Obstacle, Copy)
{
    holo::sensors::horizon_matrix2::HorizonMatrix2Obstacle input;
    holo::common::Timestamp                                input_timestamp(222, 333);
    input.SetTimestamp(input_timestamp);
    input.SetId(10);
    input.SetType(1);
    input.SetPedSubtype(2);
    input.SetVehicleSubtype(3);
    input.SetStatus(4);
    input.SetMoveInOut(3);
    input.SetPosX(1.2);
    input.SetPosY(2.3);
    input.SetVelX(-3.4);
    input.SetVelY(-4.5);
    input.SetAccelX(5.6);
    input.SetLength(6.7);
    input.SetWidth(7.8);
    input.SetAngleRate(8.9);
    input.SetVehicleAngle(9.0);
    input.SetValid(true);
    input.SetPartAValid(true);
    input.SetPartBValid(true);
    input.SetPartCValid(true);

    holo::sensors::horizon_matrix2::HorizonMatrix2Obstacle obs(input);
    ASSERT_EQ(obs.GetTimestamp().GetSec(), 222u);
    ASSERT_EQ(obs.GetTimestamp().GetNsec(), 333u);
    ASSERT_EQ(obs.GetId(), 10);
    ASSERT_EQ(obs.GetType(), 1);
    ASSERT_EQ(obs.GetPedSubtype(), 2);
    ASSERT_EQ(obs.GetVehicleSubtype(), 3);
    ASSERT_EQ(obs.GetStatus(), 4);
    ASSERT_EQ(obs.GetMoveInOut(), 3);
    ASSERT_FLOAT_EQ(obs.GetPosX(), 1.2);
    ASSERT_FLOAT_EQ(obs.GetPosY(), 2.3);
    ASSERT_FLOAT_EQ(obs.GetVelX(), -3.4);
    ASSERT_FLOAT_EQ(obs.GetVelY(), -4.5);
    ASSERT_FLOAT_EQ(obs.GetAccelX(), 5.6);
    ASSERT_FLOAT_EQ(obs.GetLength(), 6.7);
    ASSERT_FLOAT_EQ(obs.GetWidth(), 7.8);
    ASSERT_FLOAT_EQ(obs.GetAngleRate(), 8.9);
    ASSERT_FLOAT_EQ(obs.GetVehicleAngle(), 9.0);
    ASSERT_TRUE(obs.GetValid());
    ASSERT_TRUE(obs.GetPartAValid());
    ASSERT_TRUE(obs.GetPartBValid());
    ASSERT_TRUE(obs.GetPartCValid());
    ASSERT_TRUE(obs.IsAllPartsValid());
}

TEST(HorizonMatrix2Obstacle, OpreatorEquale)
{
    holo::sensors::horizon_matrix2::HorizonMatrix2Obstacle input;

    holo::common::Timestamp input_timestamp(222, 333);
    input.SetTimestamp(input_timestamp);

    holo::sensors::horizon_matrix2::HorizonMatrix2Obstacle obs;
    obs = input;
    ASSERT_EQ(obs.GetTimestamp().GetSec(), 222u);
    ASSERT_EQ(obs.GetTimestamp().GetNsec(), 333u);
    obs = obs;
    ASSERT_EQ(obs.GetTimestamp().GetSec(), 222u);
    ASSERT_EQ(obs.GetTimestamp().GetNsec(), 333u);
}

TEST(HorizonMatrix2Obstacle, ConvertToHoloObstacle0)
{
    holo::sensors::horizon_matrix2::HorizonMatrix2Obstacle input;
    holo::common::Timestamp                                timestamp(1, 2);
    input.SetTimestamp(timestamp);
    input.SetLength(4.5f);
    input.SetWidth(2.5f);
    holo::obstacle::ObstacleVisionT<holo::float32_t> output;
    input.ConvertToHoloObstacle(output);
    ASSERT_EQ(output.GetTimestamp().GetSec(), 1);
    ASSERT_EQ(output.GetTimestamp().GetNsec(), 2);
}

TEST(HorizonMatrix2Obstacle, ConvertToHoloObstacle1)
{
    holo::sensors::horizon_matrix2::HorizonMatrix2Obstacle input;
    holo::common::Timestamp                                timestamp(1, 2);
    input.SetTimestamp(timestamp);
    input.SetType(0);
    input.SetVehicleSubtype(3);
    holo::obstacle::ObstacleVisionT<holo::float32_t> output;
    input.ConvertToHoloObstacle(output);
    ASSERT_EQ(output.GetTimestamp().GetSec(), 1);
    ASSERT_EQ(output.GetTimestamp().GetNsec(), 2);
    ASSERT_EQ(output.GetClassification().GetMainType(), holo::common::Classification::MainType::BIKE);
    ASSERT_EQ(output.GetClassification().GetSubType(), holo::common::Classification::SubType::MOTOBIKE);
}

TEST(HorizonMatrix2Obstacle, ConvertToHoloObstacle2)
{
    holo::sensors::horizon_matrix2::HorizonMatrix2Obstacle input;
    input.SetMoveInOut(3);
    input.SetPosY(1.0);
    holo::obstacle::ObstacleVisionT<holo::float32_t> output;
    input.ConvertToHoloObstacle(output);
    ASSERT_EQ(output.GetCutInCutOut(), holo::obstacle::CutInCutOut::HOST_CUT_IN_LEFT);

    input.SetMoveInOut(3);
    input.SetPosY(-1.0);
    input.ConvertToHoloObstacle(output);
    ASSERT_EQ(output.GetCutInCutOut(), holo::obstacle::CutInCutOut::HOST_CUT_IN_RIGHT);

    input.SetMoveInOut(4);
    input.SetPosY(1.0);
    input.ConvertToHoloObstacle(output);
    ASSERT_EQ(output.GetCutInCutOut(), holo::obstacle::CutInCutOut::HOST_CUT_OUT_LEFT);

    input.SetMoveInOut(4);
    input.SetPosY(-1.0);
    input.ConvertToHoloObstacle(output);
    ASSERT_EQ(output.GetCutInCutOut(), holo::obstacle::CutInCutOut::HOST_CUT_OUT_RIGHT);
}

TEST(HorizonMatrix2Obstacle, ConvertToHoloObstacleWithTransform)
{
    holo::sensors::horizon_matrix2::HorizonMatrix2Obstacle input;
    holo::common::Timestamp                                timestamp(1, 2);
    input.SetTimestamp(timestamp);
    input.SetLength(4.5f);
    input.SetWidth(2.5f);
    holo::common::Extrinsicf extrinsic(
        holo::common::Coordinate(holo::common::Coordinate::BODY),
        holo::common::Coordinate(holo::common::Coordinate::UNKNOWN),
        holo::geometry::Pose3f(holo::geometry::Rot3f::Rz(holo::geometry::Radian<float>(-90.0f)),
                               holo::geometry::Point3f()));
    holo::obstacle::ObstacleVisionT<holo::float32_t> output;
    input.ConvertToHoloObstacleWithTransform(output, extrinsic);
    ASSERT_EQ(output.GetTimestamp().GetSec(), 1);
    ASSERT_EQ(output.GetTimestamp().GetNsec(), 2);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
