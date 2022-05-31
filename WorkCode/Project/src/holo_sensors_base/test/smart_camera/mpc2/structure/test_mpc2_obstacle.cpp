#include <gtest/gtest.h>
#include <holo/sensors/smart_camera/mpc2/structure/mpc2_obstacle.h>

static const holo::float32_t EPSILON = 10e-6;

TEST(BoschMpcObstacle, Construtor)
{
    holo::sensors::bosch_mpc::BoschMpcObstacle obs;

    ASSERT_EQ(obs.GetTimestamp().GetSec(), 0u);
    ASSERT_EQ(obs.GetTimestamp().GetNsec(), 0u);
    ASSERT_FLOAT_EQ(obs.GetLongDist(), 0.0f);
    ASSERT_FLOAT_EQ(obs.GetAngleCenter(), 0.0f);
    ASSERT_EQ(obs.GetClassification(), 0u);
    ASSERT_FLOAT_EQ(obs.GetAngleWidth(), 0.0f);
    ASSERT_FLOAT_EQ(obs.GetConfidence(), 0.0f);
    ASSERT_FLOAT_EQ(obs.GetAngleSpeed(), 0.0f);

    ASSERT_FLOAT_EQ(obs.GetAngleOverlapEgolaneLeft(), 0.0f);
    ASSERT_FLOAT_EQ(obs.GetAngleOverlapEgolaneRight(), 0.0f);
    ASSERT_FLOAT_EQ(obs.GetInvTTC(), 0.0f);
    ASSERT_EQ(obs.GetAge(), 0);
    ASSERT_FLOAT_EQ(obs.GetAngleEdgeLeft(), 0.0f);
    ASSERT_FLOAT_EQ(obs.GetAngleEdgeRight(), 0.0f);
    ASSERT_EQ(obs.GetId(), 0u);
    ASSERT_FLOAT_EQ(obs.GetLongVelocity(), 0.0f);

    ASSERT_FALSE(obs.GetPartAValid());
    ASSERT_FALSE(obs.GetPartBValid());
    ASSERT_FALSE(obs.GetPartCValid());
    ASSERT_FALSE(obs.GetPartDValid());
    ASSERT_FALSE(obs.GetPartEValid());
}

TEST(BoschMpcObstacle, Copy)
{
    holo::sensors::bosch_mpc::BoschMpcObstacle input;

    holo::common::Timestamp input_timestamp(222, 333);
    input.SetTimestamp(input_timestamp);
    input.SetLongDist(2.3f);
    input.SetAngleCenter(112.3f);
    input.SetClassification(2u);
    input.SetAngleWidth(89.1f);
    input.SetConfidence(234.0f);
    input.SetAngleSpeed(55.213f);
    input.SetAngleOverlapEgolaneLeft(78.4f);
    input.SetAngleOverlapEgolaneRight(230.9f);
    input.SetInvTTC(223.4f);
    input.SetAge(9999);
    input.SetAngleEdgeLeft(2113.4f);
    input.SetAngleEdgeRight(1123.89f);
    input.SetId(225u);
    input.SetLongVelocity(244598.2f);
    input.SetPartAValid(true);
    input.SetPartBValid(false);
    input.SetPartCValid(false);
    input.SetPartDValid(true);
    input.SetPartEValid(true);

    holo::sensors::bosch_mpc::BoschMpcObstacle obs(input);

    ASSERT_EQ(obs.GetTimestamp().GetSec(), 222);
    ASSERT_EQ(obs.GetTimestamp().GetNsec(), 333);
    ASSERT_FLOAT_EQ(obs.GetLongDist(), 2.3f);
    ASSERT_FLOAT_EQ(obs.GetAngleCenter(), 112.3f);
    ASSERT_EQ(obs.GetClassification(), 2u);
    ASSERT_FLOAT_EQ(obs.GetAngleWidth(), 89.1f);
    ASSERT_FLOAT_EQ(obs.GetConfidence(), 234.0f);
    ASSERT_FLOAT_EQ(obs.GetAngleSpeed(), 55.213f);

    ASSERT_FLOAT_EQ(obs.GetAngleOverlapEgolaneLeft(), 78.4f);
    ASSERT_FLOAT_EQ(obs.GetAngleOverlapEgolaneRight(), 230.9f);
    ASSERT_FLOAT_EQ(obs.GetInvTTC(), 223.4f);
    ASSERT_EQ(obs.GetAge(), 9999);
    ASSERT_FLOAT_EQ(obs.GetAngleEdgeLeft(), 2113.4f);
    ASSERT_FLOAT_EQ(obs.GetAngleEdgeRight(), 1123.89f);
    ASSERT_EQ(obs.GetId(), 225u);
    ASSERT_FLOAT_EQ(obs.GetLongVelocity(), 244598.2f);

    ASSERT_TRUE(obs.GetPartAValid());
    ASSERT_FALSE(obs.GetPartBValid());
    ASSERT_FALSE(obs.GetPartCValid());
    ASSERT_TRUE(obs.GetPartDValid());
    ASSERT_TRUE(obs.GetPartEValid());
}

TEST(BoschMpcObstacle, OpreatorEquale)
{
    holo::sensors::bosch_mpc::BoschMpcObstacle input;

    holo::common::Timestamp input_timestamp(222, 333);
    input.SetTimestamp(input_timestamp);
    input.SetLongDist(2.3f);
    input.SetAngleCenter(112.3f);
    input.SetClassification(2u);
    input.SetAngleWidth(89.1f);
    input.SetConfidence(234.0f);
    input.SetAngleSpeed(55.213f);
    input.SetAngleOverlapEgolaneLeft(78.4f);
    input.SetAngleOverlapEgolaneRight(230.9f);
    input.SetInvTTC(223.4f);
    input.SetAge(9999);
    input.SetAngleEdgeLeft(2113.4f);
    input.SetAngleEdgeRight(1123.89f);
    input.SetId(225u);
    input.SetLongVelocity(244598.2f);
    input.SetPartAValid(true);
    input.SetPartBValid(false);
    input.SetPartCValid(false);
    input.SetPartDValid(true);
    input.SetPartEValid(true);

    holo::sensors::bosch_mpc::BoschMpcObstacle obs;
    obs = input;

    ASSERT_EQ(obs.GetTimestamp().GetSec(), 222);
    ASSERT_EQ(obs.GetTimestamp().GetNsec(), 333);
    ASSERT_FLOAT_EQ(obs.GetLongDist(), 2.3f);
    ASSERT_FLOAT_EQ(obs.GetAngleCenter(), 112.3f);
    ASSERT_EQ(obs.GetClassification(), 2u);
    ASSERT_FLOAT_EQ(obs.GetAngleWidth(), 89.1f);
    ASSERT_FLOAT_EQ(obs.GetConfidence(), 234.0f);
    ASSERT_FLOAT_EQ(obs.GetAngleSpeed(), 55.213f);

    ASSERT_FLOAT_EQ(obs.GetAngleOverlapEgolaneLeft(), 78.4f);
    ASSERT_FLOAT_EQ(obs.GetAngleOverlapEgolaneRight(), 230.9f);
    ASSERT_FLOAT_EQ(obs.GetInvTTC(), 223.4f);
    ASSERT_EQ(obs.GetAge(), 9999);
    ASSERT_FLOAT_EQ(obs.GetAngleEdgeLeft(), 2113.4f);
    ASSERT_FLOAT_EQ(obs.GetAngleEdgeRight(), 1123.89f);
    ASSERT_EQ(obs.GetId(), 225u);
    ASSERT_FLOAT_EQ(obs.GetLongVelocity(), 244598.2f);

    ASSERT_TRUE(obs.GetPartAValid());
    ASSERT_FALSE(obs.GetPartBValid());
    ASSERT_FALSE(obs.GetPartCValid());
    ASSERT_TRUE(obs.GetPartDValid());
    ASSERT_TRUE(obs.GetPartEValid());

    obs = obs;
    ASSERT_TRUE(obs.GetPartAValid());
    ASSERT_FALSE(obs.GetPartBValid());
    ASSERT_FALSE(obs.GetPartCValid());
    ASSERT_TRUE(obs.GetPartDValid());
    ASSERT_TRUE(obs.GetPartEValid());
}

TEST(BoschMpcObstacle, ConvertToHoloObstacle)
{
    holo::sensors::bosch_mpc::BoschMpcObstacle input;
    holo::common::Timestamp                    timestamp(1, 2);
    input.SetTimestamp(timestamp);
    input.SetLongDist(12.3f);
    input.SetAngleCenter(0.0f);
    input.SetClassification(1);
    input.SetAngleWidth(0.1f);
    input.SetConfidence(0.55f);
    input.SetAngleSpeed(0.66f);
    input.SetAngleOverlapEgolaneLeft(0.11f);
    input.SetAngleOverlapEgolaneRight(0.22f);
    input.SetInvTTC(4.4f);
    input.SetAge(999);
    input.SetAngleEdgeLeft(0.3f);
    input.SetAngleEdgeRight(0.2f);
    input.SetLongVelocity(6.6f);
    input.SetId(10);
    input.SetPartAValid(true);
    input.SetPartBValid(true);
    input.SetPartCValid(true);
    input.SetPartDValid(true);
    input.SetPartEValid(true);

    holo::obstacle::ObstacleVisionT<holo::float32_t> output;
    input.ConvertToHoloObstacle(output);
    ASSERT_EQ(output.GetTimestamp().GetSec(), 1);
    ASSERT_EQ(output.GetTimestamp().GetNsec(), 2);
    ASSERT_NEAR(output.GetPosition().GetX(), 12.3f, EPSILON);
    ASSERT_NEAR(output.GetPosition().GetY(), 3.140705687f, EPSILON);
    ASSERT_NEAR(output.GetPosition().GetZ(), 0.0f, EPSILON);
    ASSERT_NEAR(output.GetObstacleBBox3D().GetWidth(), 1.311502459f, EPSILON);
    ASSERT_NEAR(output.GetObstacleBBox3D().GetHeight(), 0.1f, EPSILON);
    ASSERT_NEAR(output.GetObstacleBBox3D().GetDepth(), 0.1f, EPSILON);
    ASSERT_NEAR(output.GetObstacleBBox3D().GetCenter().GetX(), output.GetPosition().GetX(), EPSILON);
    ASSERT_NEAR(output.GetObstacleBBox3D().GetCenter().GetY(), output.GetPosition().GetY(), EPSILON);
    ASSERT_NEAR(output.GetObstacleBBox3D().GetCenter().GetZ(), output.GetPosition().GetZ(), EPSILON);
    ASSERT_EQ(output.GetCoordinate(), holo::common::Coordinate(holo::common::Coordinate::UNKNOWN));
    ASSERT_EQ(output.GetObstacleId(), 10);
    ASSERT_EQ(uint32_t(output.GetSensorId()), 0);
    ASSERT_EQ(output.GetClassification(),
              holo::common::Classification(holo::common::Classification::MainType::UNKNOWN,
                                           holo::common::Classification::SubType::UNKNOWN_MOVABLE));
    ASSERT_FLOAT_EQ(output.GetObstacleExistScore(), 0.55f);
    ASSERT_FLOAT_EQ(output.GetRelativeVelocity()[0], 6.6f);
    ASSERT_FLOAT_EQ(output.GetRelativeVelocity()[1], 0.0f);
    ASSERT_FLOAT_EQ(output.GetRelativeVelocity()[2], 0.0f);
    ASSERT_FLOAT_EQ(output.GetAcceleration()[0], 0.0f);
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

TEST(BoschMpcObstacle, ConvertToHoloObstacleWithTransform)
{
    holo::sensors::bosch_mpc::BoschMpcObstacle input;
    holo::common::Timestamp                    timestamp(1, 2);
    input.SetTimestamp(timestamp);
    input.SetLongDist(12.3f);
    input.SetAngleCenter(0.0f);
    input.SetClassification(1);
    input.SetAngleWidth(0.1f);
    input.SetConfidence(0.55f);
    input.SetAngleSpeed(0.66f);
    input.SetAngleOverlapEgolaneLeft(0.11f);
    input.SetAngleOverlapEgolaneRight(0.22f);
    input.SetInvTTC(4.4f);
    input.SetAge(999);
    input.SetAngleEdgeLeft(0.3f);
    input.SetAngleEdgeRight(0.2f);
    input.SetLongVelocity(6.6f);
    input.SetId(10);
    input.SetPartAValid(true);
    input.SetPartBValid(true);
    input.SetPartCValid(true);
    input.SetPartDValid(true);
    input.SetPartEValid(true);

    holo::common::Extrinsicf extrinsic(
        holo::common::Coordinate(holo::common::Coordinate::BODY),
        holo::common::Coordinate(holo::common::Coordinate::UNKNOWN),
        holo::geometry::Pose3f(holo::geometry::Rot3f::Rz(holo::geometry::Radian<holo::float32_t>(-90.0f)),
                               holo::geometry::Point3f(0, 0, 0)));
    holo::obstacle::ObstacleVisionT<holo::float32_t> output;
    input.ConvertToHoloObstacleWithTransform(output, extrinsic);
    ASSERT_EQ(output.GetTimestamp().GetSec(), 1);
    ASSERT_EQ(output.GetTimestamp().GetNsec(), 2);
    ASSERT_NEAR(output.GetPosition().GetX(), 3.140705687f, EPSILON);
    ASSERT_NEAR(output.GetPosition().GetY(), -12.3f, EPSILON);
    ASSERT_NEAR(output.GetPosition().GetZ(), 0.0f, EPSILON);
    ASSERT_NEAR(output.GetObstacleBBox3D().GetWidth(), 1.311502459f, EPSILON);
    ASSERT_NEAR(output.GetObstacleBBox3D().GetHeight(), 0.1f, EPSILON);
    ASSERT_NEAR(output.GetObstacleBBox3D().GetDepth(), 0.1f, EPSILON);
    ASSERT_NEAR(output.GetObstacleBBox3D().GetCenter().GetX(), output.GetPosition().GetX(), EPSILON);
    ASSERT_NEAR(output.GetObstacleBBox3D().GetCenter().GetY(), output.GetPosition().GetY(), EPSILON);
    ASSERT_NEAR(output.GetObstacleBBox3D().GetCenter().GetZ(), output.GetPosition().GetZ(), EPSILON);
    ASSERT_EQ(output.GetCoordinate(), holo::common::Coordinate(holo::common::Coordinate::BODY));
    ASSERT_EQ(output.GetObstacleId(), 10);
    ASSERT_EQ(uint32_t(output.GetSensorId()), 0);
    ASSERT_EQ(output.GetClassification(),
              holo::common::Classification(holo::common::Classification::MainType::UNKNOWN,
                                           holo::common::Classification::SubType::UNKNOWN_MOVABLE));
    ASSERT_FLOAT_EQ(output.GetObstacleExistScore(), 0.55f);
    ASSERT_NEAR(output.GetRelativeVelocity()[0], 0.0f, EPSILON);
    ASSERT_NEAR(output.GetRelativeVelocity()[1], -6.6f, EPSILON);
    ASSERT_NEAR(output.GetRelativeVelocity()[2], 0.0f, EPSILON);
    ASSERT_FLOAT_EQ(output.GetAcceleration()[0], 0.0f);
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
