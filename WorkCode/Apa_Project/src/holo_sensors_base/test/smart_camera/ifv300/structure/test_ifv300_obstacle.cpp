#include <gtest/gtest.h>
#include <holo/sensors/smart_camera/ifv300/structure/ifv300_obstacle.h>

static const holo::float32_t EPSILON = 10e-6;
TEST(Ifv300Obstacle, Construtor)
{
    holo::sensors::ifv300::Ifv300Obstacle obs;

    ASSERT_EQ(obs.GetTimestamp().GetSec(), 0u);
    ASSERT_EQ(obs.GetTimestamp().GetNsec(), 0u);
    ASSERT_FLOAT_EQ(obs.GetLongPos(), 0.0f);
    ASSERT_FLOAT_EQ(obs.GetLatPos(), 0.0f);
    ASSERT_FLOAT_EQ(obs.GetLongVel(), 0.0f);
    ASSERT_FLOAT_EQ(obs.GetLatVel(), 0.0f);
    ASSERT_FLOAT_EQ(obs.GetLongAccel(), 0.0f);
    ASSERT_FLOAT_EQ(obs.GetWidth(), 0.0f);
    ASSERT_FLOAT_EQ(obs.GetHeight(), 0.0f);
    ASSERT_FLOAT_EQ(obs.GetTtc(), 0.0f);
    ASSERT_EQ(obs.GetObjectId(), 0);
    ASSERT_EQ(obs.GetClassification(), 0);
    ASSERT_EQ(obs.GetBrakeLightInd(), 0);
    ASSERT_EQ(obs.GetTurnInd(), 0);
    ASSERT_EQ(obs.GetCutInOut(), 0);
    ASSERT_EQ(obs.GetRollingCounter(), 0);
    ASSERT_FALSE(obs.GetPedWaistUp());
    ASSERT_FALSE(obs.GetPartAValid());
    ASSERT_FALSE(obs.GetPartBValid());
    ASSERT_FALSE(obs.GetPartCValid());
    ASSERT_FALSE(obs.IsValid());
}

TEST(Ifv300Obstacle, Copy)
{
    holo::sensors::ifv300::Ifv300Obstacle input;

    holo::common::Timestamp input_timestamp(222, 333);
    input.SetTimestamp(input_timestamp);
    input.SetLongPos(12.34f);
    input.SetLatPos(5.67f);
    input.SetLongVel(8.9f);
    input.SetLatVel(9.10f);
    input.SetLongAccel(1.23f);
    input.SetWidth(3.33f);
    input.SetHeight(4.44f);
    input.SetTtc(5.55f);
    input.SetObjectId(11);
    input.SetClassification(5);
    input.SetBrakeLightInd(1);
    input.SetTurnInd(2);
    input.SetCutInOut(5);
    input.SetRollingCounter(1);
    input.SetPedWaistUp(true);
    input.SetPartAValid(true);
    input.SetPartBValid(false);
    input.SetPartCValid(true);

    holo::sensors::ifv300::Ifv300Obstacle obs(input);
    ASSERT_EQ(obs.GetTimestamp().GetSec(), 222u);
    ASSERT_EQ(obs.GetTimestamp().GetNsec(), 333u);
    ASSERT_FLOAT_EQ(obs.GetLongPos(), 12.34f);
    ASSERT_FLOAT_EQ(obs.GetLatPos(), 5.67f);
    ASSERT_FLOAT_EQ(obs.GetLongVel(), 8.9f);
    ASSERT_FLOAT_EQ(obs.GetLatVel(), 9.10f);
    ASSERT_FLOAT_EQ(obs.GetLongAccel(), 1.23f);
    ASSERT_FLOAT_EQ(obs.GetWidth(), 3.33f);
    ASSERT_FLOAT_EQ(obs.GetHeight(), 4.44f);
    ASSERT_FLOAT_EQ(obs.GetTtc(), 5.55f);
    ASSERT_EQ(obs.GetObjectId(), 11);
    ASSERT_EQ(obs.GetClassification(), 5);
    ASSERT_EQ(obs.GetBrakeLightInd(), 1);
    ASSERT_EQ(obs.GetTurnInd(), 2);
    ASSERT_EQ(obs.GetCutInOut(), 5);
    ASSERT_EQ(obs.GetRollingCounter(), 1);
    ASSERT_TRUE(obs.GetPedWaistUp());
    ASSERT_TRUE(obs.GetPartAValid());
    ASSERT_FALSE(obs.GetPartBValid());
    ASSERT_TRUE(obs.GetPartCValid());
    ASSERT_FALSE(obs.IsValid());
}

TEST(Ifv300Obstacle, OpreatorEquale)
{
    holo::sensors::ifv300::Ifv300Obstacle input;

    holo::common::Timestamp input_timestamp(222, 333);
    input.SetTimestamp(input_timestamp);
    input.SetLongPos(12.34f);
    input.SetLatPos(5.67f);
    input.SetLongVel(8.9f);
    input.SetLatVel(9.10f);
    input.SetLongAccel(1.23f);
    input.SetWidth(3.33f);
    input.SetHeight(4.44f);
    input.SetTtc(5.55f);
    input.SetObjectId(11);
    input.SetClassification(5);
    input.SetBrakeLightInd(1);
    input.SetTurnInd(2);
    input.SetCutInOut(5);
    input.SetRollingCounter(1);
    input.SetPedWaistUp(true);
    input.SetPartAValid(true);
    input.SetPartBValid(false);
    input.SetPartCValid(true);

    holo::sensors::ifv300::Ifv300Obstacle obs;

    obs = input;
    ASSERT_EQ(obs.GetTimestamp().GetSec(), 222u);
    ASSERT_EQ(obs.GetTimestamp().GetNsec(), 333u);
    ASSERT_FLOAT_EQ(obs.GetLongPos(), 12.34f);
    ASSERT_FLOAT_EQ(obs.GetLatPos(), 5.67f);
    ASSERT_FLOAT_EQ(obs.GetLongVel(), 8.9f);
    ASSERT_FLOAT_EQ(obs.GetLatVel(), 9.10f);
    ASSERT_FLOAT_EQ(obs.GetLongAccel(), 1.23f);
    ASSERT_FLOAT_EQ(obs.GetWidth(), 3.33f);
    ASSERT_FLOAT_EQ(obs.GetHeight(), 4.44f);
    ASSERT_FLOAT_EQ(obs.GetTtc(), 5.55f);
    ASSERT_EQ(obs.GetObjectId(), 11);
    ASSERT_EQ(obs.GetClassification(), 5);
    ASSERT_EQ(obs.GetBrakeLightInd(), 1);
    ASSERT_EQ(obs.GetTurnInd(), 2);
    ASSERT_EQ(obs.GetCutInOut(), 5);
    ASSERT_EQ(obs.GetRollingCounter(), 1);
    ASSERT_TRUE(obs.GetPedWaistUp());
    ASSERT_TRUE(obs.GetPartAValid());
    ASSERT_FALSE(obs.GetPartBValid());
    ASSERT_TRUE(obs.GetPartCValid());
    ASSERT_FALSE(obs.IsValid());

    obs = obs;
    ASSERT_TRUE(obs.GetPedWaistUp());
    ASSERT_TRUE(obs.GetPartAValid());
    ASSERT_FALSE(obs.GetPartBValid());
    ASSERT_TRUE(obs.GetPartCValid());
    ASSERT_FALSE(obs.IsValid());
}

TEST(Ifv300Obstacle, ConvertToHoloObstacle1)
{
    holo::sensors::ifv300::Ifv300Obstacle input;
    holo::common::Timestamp               timestamp(1, 2);
    input.SetTimestamp(timestamp);
    input.SetLongPos(12.34f);
    input.SetLatPos(5.67f);
    input.SetLongVel(8.9f);
    input.SetLatVel(9.10f);
    input.SetLongAccel(1.23f);
    input.SetWidth(3.33f);
    input.SetHeight(4.44f);
    input.SetTtc(5.55f);
    input.SetObjectId(11);
    input.SetClassification(4);
    input.SetBrakeLightInd(1);
    input.SetTurnInd(2);
    input.SetCutInOut(5);
    input.SetRollingCounter(1);
    input.SetPedWaistUp(true);
    input.SetPartAValid(true);
    input.SetPartBValid(true);
    input.SetPartCValid(true);

    holo::obstacle::ObstacleVisionT<holo::float32_t> output;
    input.ConvertToHoloObstacle(output);
    ASSERT_EQ(output.GetTimestamp().GetSec(), 1);
    ASSERT_EQ(output.GetTimestamp().GetNsec(), 2);
    ASSERT_FLOAT_EQ(output.GetPosition().GetX(), 12.34f);
    ASSERT_FLOAT_EQ(output.GetPosition().GetY(), -5.67f);
    ASSERT_FLOAT_EQ(output.GetPosition().GetZ(), 0.0f);
    ASSERT_NEAR(output.GetObstacleBBox3D().GetWidth(), 3.33f, EPSILON);
    ASSERT_NEAR(output.GetObstacleBBox3D().GetHeight(), 4.44f, EPSILON);
    ASSERT_NEAR(output.GetObstacleBBox3D().GetDepth(), 0.1f, EPSILON);
    ASSERT_NEAR(output.GetObstacleBBox3D().GetCenter().GetX(), output.GetPosition().GetX(), EPSILON);
    ASSERT_NEAR(output.GetObstacleBBox3D().GetCenter().GetY(), output.GetPosition().GetY(), EPSILON);
    ASSERT_NEAR(output.GetObstacleBBox3D().GetCenter().GetZ(), output.GetPosition().GetZ(), EPSILON);
    ASSERT_EQ(output.GetCoordinate(), holo::common::Coordinate(holo::common::Coordinate::UNKNOWN));
    ASSERT_EQ(output.GetObstacleId(), 11);
    ASSERT_EQ(uint32_t(output.GetSensorId()), 0);
    ASSERT_EQ(output.GetClassification(),
              holo::common::Classification(holo::common::Classification::MainType::PEDESTRIAN,
                                           holo::common::Classification::SubType::PEDESTRIAN));
    ASSERT_FLOAT_EQ(output.GetObstacleExistScore(), 1.0f);
    ASSERT_FLOAT_EQ(output.GetRelativeVelocity()[0], 8.9f);
    ASSERT_FLOAT_EQ(output.GetRelativeVelocity()[1], -9.10f);
    ASSERT_FLOAT_EQ(output.GetRelativeVelocity()[2], 0.0f);
    ASSERT_FLOAT_EQ(output.GetAcceleration()[0], 1.23f);
    ASSERT_FLOAT_EQ(output.GetAcceleration()[1], 0.0f);
    ASSERT_FLOAT_EQ(output.GetAcceleration()[2], 0.0f);
    ASSERT_FLOAT_EQ(output.GetPositionSigma().GetX(), 0.0f);
    ASSERT_FLOAT_EQ(output.GetPositionSigma().GetY(), 0.0f);
    ASSERT_FLOAT_EQ(output.GetPositionSigma().GetZ(), 0.0f);
    ASSERT_FLOAT_EQ(output.GetRelativeVelocitySigma()[0], 0.0f);
    ASSERT_FLOAT_EQ(output.GetRelativeVelocitySigma()[1], 0.0f);
    ASSERT_FLOAT_EQ(output.GetRelativeVelocitySigma()[2], 0.0f);
    ASSERT_FLOAT_EQ(output.GetAccelerationSigma()[0], 0.0f);
    ASSERT_FLOAT_EQ(output.GetAccelerationSigma()[1], 0.0f);
    ASSERT_FLOAT_EQ(output.GetAccelerationSigma()[2], 0.0f);
    ASSERT_EQ(output.GetMotionStatus(), holo::obstacle::MotionStatus::UNKNOWN);
    ASSERT_EQ(output.GetCutInCutOut(), holo::obstacle::CutInCutOut::UNKNOWN);
}

TEST(Ifv300Obstacle, ConvertToHoloObstacle2)
{
    holo::sensors::ifv300::Ifv300Obstacle input;
    holo::common::Timestamp               timestamp(1, 2);
    input.SetTimestamp(timestamp);
    input.SetLatPos(5.67f);
    input.SetCutInOut(3);
    input.SetPedWaistUp(true);
    input.SetPartAValid(true);
    input.SetPartBValid(true);
    input.SetPartCValid(true);

    holo::obstacle::ObstacleVisionT<holo::float32_t> output;
    input.ConvertToHoloObstacle(output);
    ASSERT_EQ(output.GetCutInCutOut(), holo::obstacle::CutInCutOut::NEXT_CUT_IN_RIGHT);
}

TEST(Ifv300Obstacle, ConvertToHoloObstacle3)
{
    holo::sensors::ifv300::Ifv300Obstacle input;
    holo::common::Timestamp               timestamp(1, 2);
    input.SetTimestamp(timestamp);
    input.SetLatPos(-5.67f);
    input.SetCutInOut(3);
    input.SetPedWaistUp(true);
    input.SetPartAValid(true);
    input.SetPartBValid(true);
    input.SetPartCValid(true);

    holo::obstacle::ObstacleVisionT<holo::float32_t> output;
    input.ConvertToHoloObstacle(output);
    ASSERT_EQ(output.GetCutInCutOut(), holo::obstacle::CutInCutOut::NEXT_CUT_IN_LEFT);
}

TEST(Ifv300Obstacle, ConvertToHoloObstacle4)
{
    holo::sensors::ifv300::Ifv300Obstacle input;
    holo::common::Timestamp               timestamp(1, 2);
    input.SetTimestamp(timestamp);
    input.SetLatPos(5.67f);
    input.SetCutInOut(4);
    input.SetPedWaistUp(true);
    input.SetPartAValid(true);
    input.SetPartBValid(true);
    input.SetPartCValid(true);

    holo::obstacle::ObstacleVisionT<holo::float32_t> output;
    input.ConvertToHoloObstacle(output);
    ASSERT_EQ(output.GetCutInCutOut(), holo::obstacle::CutInCutOut::NEXT_CUT_OUT_RIGHT);
}

TEST(Ifv300Obstacle, ConvertToHoloObstacle5)
{
    holo::sensors::ifv300::Ifv300Obstacle input;
    holo::common::Timestamp               timestamp(1, 2);
    input.SetTimestamp(timestamp);
    input.SetLatPos(-5.67f);
    input.SetCutInOut(4);
    input.SetPedWaistUp(true);
    input.SetPartAValid(true);
    input.SetPartBValid(true);
    input.SetPartCValid(true);

    holo::obstacle::ObstacleVisionT<holo::float32_t> output;
    input.ConvertToHoloObstacle(output);
    ASSERT_EQ(output.GetCutInCutOut(), holo::obstacle::CutInCutOut::NEXT_CUT_OUT_LEFT);
}

TEST(Ifv300Obstacle, ConvertToHoloObstacleWithTransform)
{
    holo::sensors::ifv300::Ifv300Obstacle input;
    holo::common::Timestamp               timestamp(1, 2);
    input.SetTimestamp(timestamp);
    input.SetLongPos(12.34f);
    input.SetLatPos(5.67f);
    input.SetLongVel(8.9f);
    input.SetLatVel(9.10f);
    input.SetLongAccel(1.23f);
    input.SetWidth(3.33f);
    input.SetHeight(4.44f);
    input.SetTtc(5.55f);
    input.SetObjectId(11);
    input.SetClassification(4);
    input.SetBrakeLightInd(1);
    input.SetTurnInd(2);
    input.SetCutInOut(5);
    input.SetRollingCounter(1);
    input.SetPedWaistUp(true);
    input.SetPartAValid(true);
    input.SetPartBValid(true);
    input.SetPartCValid(true);

    holo::common::Extrinsicf extrinsic(
        holo::common::Coordinate(holo::common::Coordinate::BODY),
        holo::common::Coordinate(holo::common::Coordinate::UNKNOWN),
        holo::geometry::Pose3f(holo::geometry::Rot3f::Rz(holo::geometry::Radian<float>(-90.0f)),
                               holo::geometry::Point3f()));
    holo::obstacle::ObstacleVisionT<holo::float32_t> output;
    input.ConvertToHoloObstacleWithTransform(output, extrinsic);
    ASSERT_EQ(output.GetTimestamp().GetSec(), 1);
    ASSERT_EQ(output.GetTimestamp().GetNsec(), 2);
    ASSERT_FLOAT_EQ(output.GetPosition().GetX(), -5.67f);
    ASSERT_FLOAT_EQ(output.GetPosition().GetY(), -12.34f);
    ASSERT_FLOAT_EQ(output.GetPosition().GetZ(), 0.0f);
    ASSERT_NEAR(output.GetObstacleBBox3D().GetWidth(), 3.33f, EPSILON);
    ASSERT_NEAR(output.GetObstacleBBox3D().GetHeight(), 4.44f, EPSILON);
    ASSERT_NEAR(output.GetObstacleBBox3D().GetDepth(), 0.1f, EPSILON);
    ASSERT_NEAR(output.GetObstacleBBox3D().GetCenter().GetX(), output.GetPosition().GetX(), EPSILON);
    ASSERT_NEAR(output.GetObstacleBBox3D().GetCenter().GetY(), output.GetPosition().GetY(), EPSILON);
    ASSERT_NEAR(output.GetObstacleBBox3D().GetCenter().GetZ(), output.GetPosition().GetZ(), EPSILON);
    ASSERT_EQ(output.GetCoordinate(), holo::common::Coordinate(holo::common::Coordinate::BODY));
    ASSERT_EQ(output.GetObstacleId(), 11);
    ASSERT_EQ(uint32_t(output.GetSensorId()), 0);
    ASSERT_EQ(output.GetClassification(),
              holo::common::Classification(holo::common::Classification::MainType::PEDESTRIAN,
                                           holo::common::Classification::SubType::PEDESTRIAN));
    ASSERT_FLOAT_EQ(output.GetObstacleExistScore(), 1.0f);
    ASSERT_NEAR(output.GetRelativeVelocity()[0], -9.10f, EPSILON);
    ASSERT_NEAR(output.GetRelativeVelocity()[1], -8.9f, EPSILON);
    ASSERT_NEAR(output.GetRelativeVelocity()[2], 0.0f, EPSILON);
    ASSERT_FLOAT_EQ(output.GetAcceleration()[0], 1.23f);
    ASSERT_FLOAT_EQ(output.GetAcceleration()[1], 0.0f);
    ASSERT_FLOAT_EQ(output.GetAcceleration()[2], 0.0f);
    ASSERT_FLOAT_EQ(output.GetPositionSigma().GetX(), 0.0f);
    ASSERT_FLOAT_EQ(output.GetPositionSigma().GetY(), 0.0f);
    ASSERT_FLOAT_EQ(output.GetPositionSigma().GetZ(), 0.0f);
    ASSERT_FLOAT_EQ(output.GetRelativeVelocitySigma()[0], 0.0f);
    ASSERT_FLOAT_EQ(output.GetRelativeVelocitySigma()[1], 0.0f);
    ASSERT_FLOAT_EQ(output.GetRelativeVelocitySigma()[2], 0.0f);
    ASSERT_FLOAT_EQ(output.GetAccelerationSigma()[0], 0.0f);
    ASSERT_FLOAT_EQ(output.GetAccelerationSigma()[1], 0.0f);
    ASSERT_FLOAT_EQ(output.GetAccelerationSigma()[2], 0.0f);
    ASSERT_EQ(output.GetMotionStatus(), holo::obstacle::MotionStatus::UNKNOWN);
    ASSERT_EQ(output.GetCutInCutOut(), holo::obstacle::CutInCutOut::UNKNOWN);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
