/**
 * @brief unit test for ChassisState class
 * @author zhangjiannan@holomatic.com
 * @date 2019.10.9
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <gtest/gtest.h>
#include <holo/common/chassis_state.h>

TEST(ChassisState, Construct)
{
    holo::common::ChassisState state;
    ASSERT_EQ(0.0f, state.GetVehicleSpeed());
    ASSERT_EQ(0.0f, state.GetFrontLeftWheelSpeed());
    ASSERT_EQ(0.0f, state.GetFrontRightWheelSpeed());
    ASSERT_EQ(0.0f, state.GetRearLeftWheelSpeed());
    ASSERT_EQ(0.0f, state.GetRearRightWheelSpeed());
    ASSERT_EQ(0.0f, state.GetLongitudinalAcceleration());
    ASSERT_EQ(0.0f, state.GetLateralAcceleration());
    ASSERT_EQ(0.0f, state.GetYawRate());
    ASSERT_EQ(0.0f, state.GetFrontWheelAngle());

    ASSERT_EQ(0u, state.GetEnergySourceLevel());

    ASSERT_EQ(holo::common::ChassisState::GearPosition::UNKNOWN, state.GetGearPosition());
    ASSERT_EQ(0u, state.GetGearLevel());
}

TEST(ChassisState, MotionState)
{
    holo::common::ChassisState state;
    ASSERT_EQ(0.0f, state.GetVehicleSpeed());
    ASSERT_EQ(0.0f, state.GetFrontLeftWheelSpeed());
    ASSERT_EQ(0.0f, state.GetFrontRightWheelSpeed());
    ASSERT_EQ(0.0f, state.GetRearLeftWheelSpeed());
    ASSERT_EQ(0.0f, state.GetRearRightWheelSpeed());
    ASSERT_EQ(0.0f, state.GetLongitudinalAcceleration());
    ASSERT_EQ(0.0f, state.GetLateralAcceleration());
    ASSERT_EQ(0.0f, state.GetYawRate());
    ASSERT_EQ(0.0f, state.GetFrontWheelAngle());

    state.SetVehicleSpeed(1.0f);
    state.SetFrontLeftWheelSpeed(1.0f);
    state.SetFrontRightWheelSpeed(1.0f);
    state.SetRearLeftWheelSpeed(1.0f);
    state.SetRearRightWheelSpeed(1.0f);
    state.SetLongitudinalAcceleration(1.0f);
    state.SetLateralAcceleration(1.0f);
    state.SetYawRate(1.0f);
    state.SetFrontWheelAngle(1.0f);
    state.SetLongitudinalControlValue(1.0f);

    ASSERT_EQ(1.0f, state.GetVehicleSpeed());
    ASSERT_EQ(1.0f, state.GetFrontLeftWheelSpeed());
    ASSERT_EQ(1.0f, state.GetFrontRightWheelSpeed());
    ASSERT_EQ(1.0f, state.GetRearLeftWheelSpeed());
    ASSERT_EQ(1.0f, state.GetRearRightWheelSpeed());
    ASSERT_EQ(1.0f, state.GetLongitudinalAcceleration());
    ASSERT_EQ(1.0f, state.GetLateralAcceleration());
    ASSERT_EQ(1.0f, state.GetYawRate());
    ASSERT_EQ(1.0f, state.GetFrontWheelAngle());
    ASSERT_EQ(1.0f, state.GetLongitudinalControlValue());
}

TEST(ChassisState, EnergySourceLevel)
{
    auto state = holo::common::ChassisState();
    ASSERT_EQ(0u, state.GetEnergySourceLevel());

    state.SetEnergySourceLevel(10u);
    ASSERT_EQ(10u, state.GetEnergySourceLevel());

    state.SetEnergySourceLevel(100u);
    ASSERT_EQ(100u, state.GetEnergySourceLevel());

    state.SetEnergySourceLevel(101u);
    ASSERT_EQ(100u, state.GetEnergySourceLevel());

    state.SetEnergySourceLevel(255u);
    ASSERT_EQ(100u, state.GetEnergySourceLevel());
}

TEST(ChassisState, BasicSerializeDeserialize)
{
    holo::common::ChassisState  input_chassis_state, output_chassis_state;
    input_chassis_state.SetTimestamp(holo::Timestamp(3, 500));
    input_chassis_state.SetVehicleSpeed(1.0f);
    input_chassis_state.SetFrontLeftWheelSpeed(2.0f);
    input_chassis_state.SetFrontRightWheelSpeed(3.0f);
    input_chassis_state.SetRearLeftWheelSpeed(4.0f);
    input_chassis_state.SetRearRightWheelSpeed(5.0f);
    input_chassis_state.SetLongitudinalAcceleration(6.0f);
    input_chassis_state.SetLateralAcceleration(7.0f);
    input_chassis_state.SetYawRate(8.0f);
    input_chassis_state.SetFrontWheelAngle(9.0f);
    input_chassis_state.SetLongitudinalControlValue(9.0f);
    input_chassis_state.SetEnergySourceLevel(30U);
    input_chassis_state.SetGearPosition(holo::common::ChassisState::GearPosition::D);
    input_chassis_state.SetGearLevel(4U);
    input_chassis_state.SetStateValue(123);
    input_chassis_state.SetInvalidFlagValue(456);

    uint8_t serialize_buf[1024];
    holo::serialization::Serializer<>          serializer(serialize_buf, 1024);
    serializer << input_chassis_state;
    EXPECT_EQ(input_chassis_state.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> Deserializer(serialize_buf, serializer.GetSize());
    Deserializer >> output_chassis_state;

    ASSERT_EQ(input_chassis_state.GetTimestamp(), output_chassis_state.GetTimestamp());
    ASSERT_EQ(input_chassis_state.GetVehicleSpeed(), output_chassis_state.GetVehicleSpeed());
    ASSERT_EQ(input_chassis_state.GetFrontLeftWheelSpeed(), output_chassis_state.GetFrontLeftWheelSpeed());
    ASSERT_EQ(input_chassis_state.GetFrontRightWheelSpeed(), output_chassis_state.GetFrontRightWheelSpeed());
    ASSERT_EQ(input_chassis_state.GetRearLeftWheelSpeed(), output_chassis_state.GetRearLeftWheelSpeed());
    ASSERT_EQ(input_chassis_state.GetRearRightWheelSpeed(), output_chassis_state.GetRearRightWheelSpeed());
    ASSERT_EQ(input_chassis_state.GetLongitudinalAcceleration(), output_chassis_state.GetLongitudinalAcceleration());
    ASSERT_EQ(input_chassis_state.GetLateralAcceleration(), output_chassis_state.GetLateralAcceleration());
    ASSERT_EQ(input_chassis_state.GetYawRate(), output_chassis_state.GetYawRate());
    ASSERT_EQ(input_chassis_state.GetFrontWheelAngle(), output_chassis_state.GetFrontWheelAngle());
    ASSERT_EQ(input_chassis_state.GetLongitudinalControlValue(), output_chassis_state.GetLongitudinalControlValue());
    ASSERT_EQ(input_chassis_state.GetEnergySourceLevel(), output_chassis_state.GetEnergySourceLevel());
    ASSERT_EQ(input_chassis_state.GetGearPosition(), output_chassis_state.GetGearPosition());
    ASSERT_EQ(input_chassis_state.GetGearLevel(), output_chassis_state.GetGearLevel());
    ASSERT_EQ(input_chassis_state.GetStateValue(), output_chassis_state.GetStateValue());
    ASSERT_EQ(input_chassis_state.GetInvalidFlagValue(), output_chassis_state.GetInvalidFlagValue());
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

