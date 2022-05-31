#include <gtest/gtest.h>
#include <holo/sensors/smart_camera/me3/structure/me3_obstacle.h>

TEST(MobileyeObstacle, Construtor)
{
    holo::sensors::mobileye::MobileyeObstacle obs;

    ASSERT_EQ(obs.GetTimestamp().GetSec(), 0u);
    ASSERT_EQ(obs.GetTimestamp().GetNsec(), 0u);
}

TEST(MobileyeObstacle, Copy)
{
    holo::sensors::mobileye::MobileyeObstacle input;

    holo::common::Timestamp input_timestamp(222, 333);
    input.SetTimestamp(input_timestamp);
    input.SetLongitudinalDist(1.2);
    input.SetLateralDist(2.3);
    input.SetLongitudinalVelocity(3.4);
    input.SetLateralVelocity(4.5);
    input.SetAcceleration(5.6);
    input.SetWidth(6.7);
    input.SetAngleLeft(0.1);
    input.SetAngleRight(0.2);
    input.SetAngleRateMean(0.3);
    input.SetObjectAge(1000);
    input.SetId(10);
    input.SetObjectClass(1);
    input.SetMotionStatus(2);
    input.SetCutInOut(3);
    input.SetReplaced(false);
    input.SetCipvFlag(true);
    input.SetPart0Valid(true);
    input.SetPart1Valid(true);
    input.SetPart2Valid(true);
    input.SetPart3Valid(true);

    holo::sensors::mobileye::MobileyeObstacle obs(input);
    ASSERT_EQ(obs.GetTimestamp().GetSec(), 222u);
    ASSERT_EQ(obs.GetTimestamp().GetNsec(), 333u);
    ASSERT_FLOAT_EQ(obs.GetLongitudinalDist(), 1.2);
    ASSERT_FLOAT_EQ(obs.GetLateralDist(), 2.3);
    ASSERT_FLOAT_EQ(obs.GetLongitudinalVelocity(), 3.4);
    ASSERT_FLOAT_EQ(obs.GetLateralVelocity(), 4.5);
    ASSERT_FLOAT_EQ(obs.GetAcceleration(), 5.6);
    ASSERT_FLOAT_EQ(obs.GetWidth(), 6.7);
    ASSERT_FLOAT_EQ(obs.GetAngleLeft(), 0.1);
    ASSERT_FLOAT_EQ(obs.GetAngleRight(), 0.2);
    ASSERT_FLOAT_EQ(obs.GetAngleRateMean(), 0.3);
    ASSERT_EQ(obs.GetObjectAge(), 1000);
    ASSERT_EQ(obs.GetId(), 10);
    ASSERT_EQ(obs.GetObjectClass(), 1);
    ASSERT_EQ(obs.GetMotionStatus(), 2);
    ASSERT_EQ(obs.GetCutInOut(), 3);
    ASSERT_FALSE(obs.GetReplaced());
    ASSERT_TRUE(obs.GetCipvFlag());
    ASSERT_TRUE(obs.GetPart0Valid());
    ASSERT_TRUE(obs.GetPart1Valid());
    ASSERT_TRUE(obs.GetPart2Valid());
    ASSERT_TRUE(obs.GetPart3Valid());
    ASSERT_TRUE(obs.IsAllPartsValid());
}

TEST(MobileyeObstacle, OpreatorEquale)
{
    holo::sensors::mobileye::MobileyeObstacle input;

    holo::common::Timestamp input_timestamp(222, 333);
    input.SetTimestamp(input_timestamp);

    holo::sensors::mobileye::MobileyeObstacle obs;

    obs = input;
    ASSERT_EQ(obs.GetTimestamp().GetSec(), 222u);
    ASSERT_EQ(obs.GetTimestamp().GetNsec(), 333u);

    obs = obs;
    ASSERT_EQ(obs.GetTimestamp().GetSec(), 222u);
    ASSERT_EQ(obs.GetTimestamp().GetNsec(), 333u);
}

TEST(MobileyeObstacle, ConvertToHoloObstacle)
{
    holo::sensors::mobileye::MobileyeObstacle input;
    holo::common::Timestamp                   timestamp(1, 2);
    input.SetTimestamp(timestamp);

    holo::obstacle::ObstacleVisionT<holo::float32_t> output;
    input.ConvertToHoloObstacle(output);
    ASSERT_EQ(output.GetTimestamp().GetSec(), 1);
    ASSERT_EQ(output.GetTimestamp().GetNsec(), 2);
}

TEST(MobileyeObstacle, ConvertToHoloObstacleWithTransform)
{
    holo::sensors::mobileye::MobileyeObstacle input;
    holo::common::Timestamp                   timestamp(1, 2);
    input.SetTimestamp(timestamp);

    holo::common::Extrinsicf                         extrinsic;
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
