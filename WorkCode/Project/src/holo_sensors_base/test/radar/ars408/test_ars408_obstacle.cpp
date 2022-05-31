#include <gtest/gtest.h>
#include <holo/sensors/radar/ars408/structure/ars408_obstacle.h>

TEST(ContiRadarObstacle, Construtor)
{
    holo::sensors::conti_radar::ContiRadarObstacle obs;

    ASSERT_EQ(obs.GetTimestamp().GetSec(), 0u);
    ASSERT_EQ(obs.GetTimestamp().GetNsec(), 0u);
    ASSERT_EQ(obs.GetId(), 0);
    ASSERT_EQ(obs.GetClassification(), 0);
    ASSERT_FLOAT_EQ(obs.GetDistLong(), 0.0f);
    ASSERT_FLOAT_EQ(obs.GetDistLat(), 0.0f);
    ASSERT_FLOAT_EQ(obs.GetVrelLong(), 0.0f);
    ASSERT_FLOAT_EQ(obs.GetVrelLat(), 0.0f);
    ASSERT_FLOAT_EQ(obs.GetArelLong(), 0.0f);
    ASSERT_FLOAT_EQ(obs.GetArelLat(), 0.0f);
    ASSERT_FLOAT_EQ(obs.GetLength(), 0.0f);
    ASSERT_FLOAT_EQ(obs.GetWidth(), 0.0f);
    ASSERT_FLOAT_EQ(obs.GetAngle(), 0.0f);
    ASSERT_FLOAT_EQ(obs.GetRcs(), 0.0f);
    ASSERT_EQ(obs.GetDynprop(), 0.0f);
    ASSERT_EQ(obs.GetProbOfExist(), 0.0f);
    ASSERT_EQ(obs.GetMeasState(), 0.0f);
    ASSERT_EQ(obs.GetDistLongRms(), 0.0f);
    ASSERT_EQ(obs.GetDistLatRms(), 0.0f);
    ASSERT_EQ(obs.GetVrelLongRms(), 0.0f);
    ASSERT_EQ(obs.GetVrelLatRms(), 0.0f);
    ASSERT_EQ(obs.GetArelLongRms(), 0.0f);
    ASSERT_EQ(obs.GetArelLatRms(), 0.0f);
    ASSERT_EQ(obs.GetAngleRms(), 0.0f);
    ASSERT_FALSE(obs.GetPart1Valid());
    ASSERT_FALSE(obs.GetPart2Valid());
    ASSERT_FALSE(obs.GetPart3Valid());
}
TEST(ContiRadarObstacle, Copy)
{
    holo::sensors::conti_radar::ContiRadarObstacle input;

    holo::common::Timestamp input_timestamp(1, 2);
    input.SetTimestamp(input_timestamp);
    input.SetId(1);
    input.SetClassification(2);
    input.SetDistLong(1.2f);
    input.SetDistLat(2.3f);
    input.SetVrelLong(3.4f);
    input.SetVrelLat(4.5f);
    input.SetArelLong(5.6f);
    input.SetArelLat(6.7f);
    input.SetLength(7.8f);
    input.SetWidth(8.9f);
    input.SetAngle(9.0f);
    input.SetRcs(10.0f);
    input.SetDynprop(1);
    input.SetProbOfExist(2);
    input.SetMeasState(3);
    input.SetDistLongRms(4);
    input.SetDistLatRms(5);
    input.SetVrelLongRms(6);
    input.SetVrelLatRms(7);
    input.SetArelLongRms(8);
    input.SetArelLatRms(9);
    input.SetAngleRms(10);
    input.SetPart1Valid(true);
    input.SetPart2Valid(false);
    input.SetPart3Valid(false);

    holo::sensors::conti_radar::ContiRadarObstacle obs(input);

    ASSERT_EQ(obs.GetTimestamp().GetSec(), 1);
    ASSERT_EQ(obs.GetTimestamp().GetNsec(), 2);
    ASSERT_EQ(obs.GetId(), 1);
    ASSERT_EQ(obs.GetClassification(), 2);
    ASSERT_FLOAT_EQ(obs.GetDistLong(), 1.2f);
    ASSERT_FLOAT_EQ(obs.GetDistLat(), 2.3f);
    ASSERT_FLOAT_EQ(obs.GetVrelLong(), 3.4f);
    ASSERT_FLOAT_EQ(obs.GetVrelLat(), 4.5f);
    ASSERT_FLOAT_EQ(obs.GetArelLong(), 5.6f);
    ASSERT_FLOAT_EQ(obs.GetArelLat(), 6.7f);
    ASSERT_FLOAT_EQ(obs.GetLength(), 7.8f);
    ASSERT_FLOAT_EQ(obs.GetWidth(), 8.9f);
    ASSERT_FLOAT_EQ(obs.GetAngle(), 9.0f);
    ASSERT_FLOAT_EQ(obs.GetRcs(), 10.0f);
    ASSERT_EQ(obs.GetDynprop(), 1);
    ASSERT_EQ(obs.GetProbOfExist(), 2);
    ASSERT_EQ(obs.GetMeasState(), 3);
    ASSERT_EQ(obs.GetDistLongRms(), 4);
    ASSERT_EQ(obs.GetDistLatRms(), 5);
    ASSERT_EQ(obs.GetVrelLongRms(), 6);
    ASSERT_EQ(obs.GetVrelLatRms(), 7);
    ASSERT_EQ(obs.GetArelLongRms(), 8);
    ASSERT_EQ(obs.GetArelLatRms(), 9);
    ASSERT_EQ(obs.GetAngleRms(), 10);
    ASSERT_TRUE(obs.GetPart1Valid());
    ASSERT_FALSE(obs.GetPart2Valid());
    ASSERT_FALSE(obs.GetPart3Valid());
}

TEST(ContiRadarObstacle, OpreatorEquale)
{
    holo::sensors::conti_radar::ContiRadarObstacle input;

    holo::common::Timestamp input_timestamp(1, 2);
    input.SetTimestamp(input_timestamp);
    input.SetId(1);
    input.SetClassification(2);
    input.SetDistLong(1.2f);
    input.SetDistLat(2.3f);
    input.SetVrelLong(3.4f);
    input.SetVrelLat(4.5f);
    input.SetArelLong(5.6f);
    input.SetArelLat(6.7f);
    input.SetLength(7.8f);
    input.SetWidth(8.9f);
    input.SetAngle(9.0f);
    input.SetRcs(10.0f);
    input.SetDynprop(1);
    input.SetProbOfExist(2);
    input.SetMeasState(3);
    input.SetDistLongRms(4);
    input.SetDistLatRms(5);
    input.SetVrelLongRms(6);
    input.SetVrelLatRms(7);
    input.SetArelLongRms(8);
    input.SetArelLatRms(9);
    input.SetAngleRms(10);
    input.SetPart1Valid(true);
    input.SetPart2Valid(false);
    input.SetPart3Valid(false);

    holo::sensors::conti_radar::ContiRadarObstacle obs;
    obs = input;

    ASSERT_EQ(obs.GetTimestamp().GetSec(), 1);
    ASSERT_EQ(obs.GetTimestamp().GetNsec(), 2);
    ASSERT_EQ(obs.GetId(), 1);
    ASSERT_EQ(obs.GetClassification(), 2);
    ASSERT_FLOAT_EQ(obs.GetDistLong(), 1.2f);
    ASSERT_FLOAT_EQ(obs.GetDistLat(), 2.3f);
    ASSERT_FLOAT_EQ(obs.GetVrelLong(), 3.4f);
    ASSERT_FLOAT_EQ(obs.GetVrelLat(), 4.5f);
    ASSERT_FLOAT_EQ(obs.GetArelLong(), 5.6f);
    ASSERT_FLOAT_EQ(obs.GetArelLat(), 6.7f);
    ASSERT_FLOAT_EQ(obs.GetLength(), 7.8f);
    ASSERT_FLOAT_EQ(obs.GetWidth(), 8.9f);
    ASSERT_FLOAT_EQ(obs.GetAngle(), 9.0f);
    ASSERT_FLOAT_EQ(obs.GetRcs(), 10.0f);
    ASSERT_EQ(obs.GetDynprop(), 1);
    ASSERT_EQ(obs.GetProbOfExist(), 2);
    ASSERT_EQ(obs.GetMeasState(), 3);
    ASSERT_EQ(obs.GetDistLongRms(), 4);
    ASSERT_EQ(obs.GetDistLatRms(), 5);
    ASSERT_EQ(obs.GetVrelLongRms(), 6);
    ASSERT_EQ(obs.GetVrelLatRms(), 7);
    ASSERT_EQ(obs.GetArelLongRms(), 8);
    ASSERT_EQ(obs.GetArelLatRms(), 9);
    ASSERT_EQ(obs.GetAngleRms(), 10);
    ASSERT_TRUE(obs.GetPart1Valid());
    ASSERT_FALSE(obs.GetPart2Valid());
    ASSERT_FALSE(obs.GetPart3Valid());

    ASSERT_NO_THROW(obs = obs);
    ASSERT_FALSE(obs.IsValid());
}

TEST(ContiRadarObstacle, ConvertToHoloObstacle)
{
    holo::sensors::conti_radar::ContiRadarObstacle input;
    holo::common::Timestamp                        input_timestamp(1, 2);
    input.SetTimestamp(input_timestamp);
    input.SetId(1);
    input.SetClassification(2);
    input.SetDistLong(1.2f);
    input.SetDistLat(2.3f);
    input.SetVrelLong(3.4f);
    input.SetVrelLat(4.5f);
    input.SetArelLong(5.6f);
    input.SetArelLat(6.7f);
    input.SetLength(7.8f);
    input.SetWidth(8.9f);
    input.SetAngle(9.0f);
    input.SetRcs(10.0f);
    input.SetDynprop(1);
    input.SetProbOfExist(2);
    input.SetMeasState(3);
    input.SetDistLongRms(4);
    input.SetDistLatRms(5);
    input.SetVrelLongRms(6);
    input.SetVrelLatRms(7);
    input.SetArelLongRms(8);
    input.SetArelLatRms(9);
    input.SetAngleRms(10);
    input.SetPart1Valid(true);
    input.SetPart2Valid(false);
    input.SetPart3Valid(false);

    holo::obstacle::ObstacleRadarT<holo::float32_t> output;
    input.ConvertToHoloObstacle(output);
    ASSERT_EQ(output.GetTimestamp().GetSec(), 1);
    ASSERT_EQ(output.GetTimestamp().GetNsec(), 2);
    ASSERT_FLOAT_EQ(output.GetPosition().GetX(), 1.2f);
    ASSERT_FLOAT_EQ(output.GetPosition().GetY(), 2.3f);
    ASSERT_FLOAT_EQ(output.GetPosition().GetZ(), 0.0f);
    ASSERT_EQ(output.GetCoordinate(), holo::common::Coordinate(holo::common::Coordinate::UNKNOWN));
    ASSERT_EQ(output.GetObstacleId(), 1);
    ASSERT_EQ(uint32_t(output.GetSensorId()), 0);
    ASSERT_EQ(output.GetClassification(), holo::common::Classification(holo::common::Classification::MainType::VEHICLE,
                                                                       holo::common::Classification::SubType::TRUCK));
    ASSERT_FLOAT_EQ(output.GetObstacleExistScore(), 0.50f);
    ASSERT_FLOAT_EQ(output.GetRelativeVelocity()[0], 3.4f);
    ASSERT_FLOAT_EQ(output.GetRelativeVelocity()[1], 4.5f);
    ASSERT_FLOAT_EQ(output.GetRelativeVelocity()[2], 0.0f);
    ASSERT_FLOAT_EQ(output.GetAcceleration()[0], 5.6f);
    ASSERT_FLOAT_EQ(output.GetAcceleration()[1], 6.7f);
    ASSERT_FLOAT_EQ(output.GetAcceleration()[2], 0.0f);
    ASSERT_FLOAT_EQ(output.GetPositionSigma().GetX(), 0.014f);
    ASSERT_FLOAT_EQ(output.GetPositionSigma().GetY(), 0.018f);
    ASSERT_FLOAT_EQ(output.GetPositionSigma().GetZ(), 0.0f);
    ASSERT_FLOAT_EQ(output.GetRelativeVelocitySigma()[0], 0.023f);
    ASSERT_FLOAT_EQ(output.GetRelativeVelocitySigma()[1], 0.029f);
    ASSERT_FLOAT_EQ(output.GetRelativeVelocitySigma()[2], 0.0f);
    ASSERT_FLOAT_EQ(output.GetAccelerationSigma()[0], 0.038f);
    ASSERT_FLOAT_EQ(output.GetAccelerationSigma()[1], 0.049f);
    ASSERT_FLOAT_EQ(output.GetAccelerationSigma()[2], 0.0f);
    ASSERT_FLOAT_EQ(output.GetObstacleLength(), 7.8f);
    ASSERT_FLOAT_EQ(output.GetObstacleWidth(), 8.9f);
    ASSERT_EQ(output.GetMotionStatus(), holo::obstacle::MotionStatus::STATIONARY);
    ASSERT_FLOAT_EQ(output.GetObstacleRCS(), 10.0f);
}

TEST(ContiRadarObstacle, ConvertToHoloObstacleWithTransform)
{
    holo::sensors::conti_radar::ContiRadarObstacle input;
    holo::common::Timestamp                        input_timestamp(1, 2);
    input.SetTimestamp(input_timestamp);
    input.SetId(1);
    input.SetClassification(2);
    input.SetDistLong(1.2f);
    input.SetDistLat(2.3f);
    input.SetVrelLong(3.4f);
    input.SetVrelLat(4.5f);
    input.SetArelLong(5.6f);
    input.SetArelLat(6.7f);
    input.SetLength(7.8f);
    input.SetWidth(8.9f);
    input.SetAngle(9.0f);
    input.SetRcs(10.0f);
    input.SetDynprop(1);
    input.SetProbOfExist(2);
    input.SetMeasState(3);
    input.SetDistLongRms(4);
    input.SetDistLatRms(5);
    input.SetVrelLongRms(6);
    input.SetVrelLatRms(7);
    input.SetArelLongRms(8);
    input.SetArelLatRms(9);
    input.SetAngleRms(10);
    input.SetPart1Valid(true);
    input.SetPart2Valid(false);
    input.SetPart3Valid(false);

    holo::common::Extrinsicf                        extrinsic(holo::common::Coordinate(holo::common::Coordinate::BODY),
                                       holo::common::Coordinate(holo::common::Coordinate::UNKNOWN),
                                       holo::geometry::Pose3f());
    holo::obstacle::ObstacleRadarT<holo::float32_t> output;
    input.ConvertToHoloObstacleWithTransform(extrinsic, output);
    ASSERT_EQ(output.GetTimestamp().GetSec(), 1);
    ASSERT_EQ(output.GetTimestamp().GetNsec(), 2);
    ASSERT_FLOAT_EQ(output.GetPosition().GetX(), 1.2f);
    ASSERT_FLOAT_EQ(output.GetPosition().GetY(), 2.3f);
    ASSERT_FLOAT_EQ(output.GetPosition().GetZ(), 0.0f);
    ASSERT_EQ(output.GetCoordinate(), holo::common::Coordinate(holo::common::Coordinate::BODY));
    ASSERT_EQ(output.GetObstacleId(), 1);
    ASSERT_EQ(uint32_t(output.GetSensorId()), 0);
    ASSERT_EQ(output.GetClassification(), holo::common::Classification(holo::common::Classification::MainType::VEHICLE,
                                                                       holo::common::Classification::SubType::TRUCK));
    ASSERT_FLOAT_EQ(output.GetObstacleExistScore(), 0.50f);
    ASSERT_FLOAT_EQ(output.GetRelativeVelocity()[0], 3.4f);
    ASSERT_FLOAT_EQ(output.GetRelativeVelocity()[1], 4.5f);
    ASSERT_FLOAT_EQ(output.GetRelativeVelocity()[2], 0.0f);
    ASSERT_FLOAT_EQ(output.GetAcceleration()[0], 5.6f);
    ASSERT_FLOAT_EQ(output.GetAcceleration()[1], 6.7f);
    ASSERT_FLOAT_EQ(output.GetAcceleration()[2], 0.0f);
    // ASSERT_FLOAT_EQ(output.GetPositionSigma().GetX(), 0.014f);
    // ASSERT_FLOAT_EQ(output.GetPositionSigma().GetY(), 0.018f);
    // ASSERT_FLOAT_EQ(output.GetPositionSigma().GetZ(), 0.0f);
    ASSERT_FLOAT_EQ(output.GetRelativeVelocitySigma()[0], 0.023f);
    ASSERT_FLOAT_EQ(output.GetRelativeVelocitySigma()[1], 0.029f);
    ASSERT_FLOAT_EQ(output.GetRelativeVelocitySigma()[2], 0.0f);
    ASSERT_FLOAT_EQ(output.GetAccelerationSigma()[0], 0.038f);
    ASSERT_FLOAT_EQ(output.GetAccelerationSigma()[1], 0.049f);
    ASSERT_FLOAT_EQ(output.GetAccelerationSigma()[2], 0.0f);
    ASSERT_FLOAT_EQ(output.GetObstacleLength(), 7.8f);
    ASSERT_FLOAT_EQ(output.GetObstacleWidth(), 8.9f);
    ASSERT_EQ(output.GetMotionStatus(), holo::obstacle::MotionStatus::STATIONARY);
    ASSERT_FLOAT_EQ(output.GetObstacleRCS(), 10.0f);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
