/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_chassis_state_io.cpp
 * @brief unit test io utils for chassis_state objects
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 2021-04-12
 */
#include <yaml-cpp/yaml.h>

#include <gtest/gtest.h>
#include <holo/common/chassis_state.h>
#include <holo/io/common/chassis_state.h>
#include <string>

using ChassisState = holo::common::ChassisState;

TEST(ChassisStateIO, EncodeAndDecodeChassisState)
{
    ChassisState chassis_state, chassis_state_expected;

    chassis_state.SetTimestamp(holo::Timestamp(3, 500));
    chassis_state.SetVehicleSpeed(1.0f);
    chassis_state.SetFrontLeftWheelSpeed(2.0f);
    chassis_state.SetFrontRightWheelSpeed(3.0f);
    chassis_state.SetRearLeftWheelSpeed(4.0f);
    chassis_state.SetRearRightWheelSpeed(5.0f);
    chassis_state.SetFrontLeftWheelPulse(6.0f);
    chassis_state.SetFrontRightWheelPulse(7.0f);
    chassis_state.SetRearLeftWheelPulse(8.0f);
    chassis_state.SetRearRightWheelPulse(9.0f);
    chassis_state.SetLongitudinalAcceleration(10.0f);
    chassis_state.SetLateralAcceleration(11.0f);
    chassis_state.SetYawRate(12.0f);
    chassis_state.SetFrontWheelAngle(13.0f);
    chassis_state.SetLongitudinalControlValue(14.0f);
    chassis_state.SetEnergySourceLevel(30U);
    chassis_state.SetGearPosition(holo::common::ChassisState::GearPosition::D);
    chassis_state.SetGearLevel(4U);
    chassis_state.SetStateValue(16383);
    chassis_state.SetInvalidFlagValue(16383);

    YAML::Node node;
    node["test"] = chassis_state;
    std::cout << node["test"] << std::endl;
    chassis_state_expected = node["test"].as<ChassisState>();

    ASSERT_EQ(chassis_state.GetTimestamp(), chassis_state_expected.GetTimestamp());
    ASSERT_EQ(chassis_state.GetVehicleSpeed(), chassis_state_expected.GetVehicleSpeed());
    ASSERT_EQ(chassis_state.GetFrontLeftWheelSpeed(), chassis_state_expected.GetFrontLeftWheelSpeed());
    ASSERT_EQ(chassis_state.GetFrontRightWheelSpeed(), chassis_state_expected.GetFrontRightWheelSpeed());
    ASSERT_EQ(chassis_state.GetRearLeftWheelSpeed(), chassis_state_expected.GetRearLeftWheelSpeed());
    ASSERT_EQ(chassis_state.GetRearRightWheelSpeed(), chassis_state_expected.GetRearRightWheelSpeed());
    ASSERT_EQ(chassis_state.GetLongitudinalAcceleration(), chassis_state_expected.GetLongitudinalAcceleration());
    ASSERT_EQ(chassis_state.GetLateralAcceleration(), chassis_state_expected.GetLateralAcceleration());
    ASSERT_EQ(chassis_state.GetYawRate(), chassis_state_expected.GetYawRate());
    ASSERT_EQ(chassis_state.GetFrontWheelAngle(), chassis_state_expected.GetFrontWheelAngle());
    ASSERT_EQ(chassis_state.GetLongitudinalControlValue(), chassis_state_expected.GetLongitudinalControlValue());
    ASSERT_EQ(chassis_state.GetEnergySourceLevel(), chassis_state_expected.GetEnergySourceLevel());
    ASSERT_EQ(chassis_state.GetGearPosition(), chassis_state_expected.GetGearPosition());
    ASSERT_EQ(chassis_state.GetGearLevel(), chassis_state_expected.GetGearLevel());
    ASSERT_EQ(chassis_state.GetStateValue(), chassis_state_expected.GetStateValue());
    ASSERT_EQ(chassis_state.GetInvalidFlagValue(), chassis_state_expected.GetInvalidFlagValue());
}

TEST(ChassisStateIO, DecodeChassisState_1)
{
    ChassisState chassis_state, chassis_state_expected;

    chassis_state.SetTimestamp(holo::Timestamp(10, 20));
    chassis_state.SetVehicleSpeed(1.0f);
    chassis_state.SetFrontLeftWheelSpeed(2.0f);
    chassis_state.SetFrontRightWheelSpeed(3.0f);
    chassis_state.SetRearLeftWheelSpeed(4.0f);
    chassis_state.SetRearRightWheelSpeed(5.0f);
    chassis_state.SetFrontLeftWheelPulse(6.0f);
    chassis_state.SetFrontRightWheelPulse(7.0f);
    chassis_state.SetRearLeftWheelPulse(8.0f);
    chassis_state.SetRearRightWheelPulse(9.0f);
    chassis_state.SetLongitudinalAcceleration(10.0f);
    chassis_state.SetLateralAcceleration(11.0f);
    chassis_state.SetYawRate(12.0f);
    chassis_state.SetFrontWheelAngle(13.0f);
    chassis_state.SetLongitudinalControlValue(14.0f);
    chassis_state.SetEnergySourceLevel(30U);
    chassis_state.SetGearPosition(holo::common::ChassisState::GearPosition::D);
    chassis_state.SetGearLevel(4U);
    chassis_state.SetStateValue(7);
    chassis_state.SetInvalidFlagValue(7);

    YAML::Node node =
        YAML::Load("{'timestamp':{'sec':10,'nsec':20},'vehicle_speed': 1,'front_left_wheel_speed': "
                   "2,'front_right_wheel_speed': 3,'rear_left_wheel_speed': 4,'rear_right_wheel_speed': "
                   "5,'front_left_wheel_pulse': 6,'front_right_wheel_pulse': 7,'rear_left_wheel_pulse': "
                   "8,'rear_right_wheel_pulse': 9,'longitudinal_acceleration': 10,'lateral_acceleration': "
                   "11,'yaw_rate': 12,'front_wheel_angle': 13,'longitudinal_control_value': 14,'energy_source_level': "
                   "30,'gear_level': 4,'gear_position': 'D','states': "
                   "['HAND_BRAKE_HOLD','LATERAL_TAKEOVER','LATERAL_INACTIVE'],'invalid_flags': "
                   "['VEHICLE_SPEED_INVALID','FL_WHEEL_SPEED_INVALID','FR_WHEEL_SPEED_INVALID']}");

    chassis_state_expected = node.as<ChassisState>();

    ASSERT_EQ(chassis_state.GetTimestamp(), chassis_state_expected.GetTimestamp());
    ASSERT_EQ(chassis_state.GetVehicleSpeed(), chassis_state_expected.GetVehicleSpeed());
    ASSERT_EQ(chassis_state.GetFrontLeftWheelSpeed(), chassis_state_expected.GetFrontLeftWheelSpeed());
    ASSERT_EQ(chassis_state.GetFrontRightWheelSpeed(), chassis_state_expected.GetFrontRightWheelSpeed());
    ASSERT_EQ(chassis_state.GetRearLeftWheelSpeed(), chassis_state_expected.GetRearLeftWheelSpeed());
    ASSERT_EQ(chassis_state.GetRearRightWheelSpeed(), chassis_state_expected.GetRearRightWheelSpeed());
    ASSERT_EQ(chassis_state.GetLongitudinalAcceleration(), chassis_state_expected.GetLongitudinalAcceleration());
    ASSERT_EQ(chassis_state.GetLateralAcceleration(), chassis_state_expected.GetLateralAcceleration());
    ASSERT_EQ(chassis_state.GetYawRate(), chassis_state_expected.GetYawRate());
    ASSERT_EQ(chassis_state.GetFrontWheelAngle(), chassis_state_expected.GetFrontWheelAngle());
    ASSERT_EQ(chassis_state.GetLongitudinalControlValue(), chassis_state_expected.GetLongitudinalControlValue());
    ASSERT_EQ(chassis_state.GetEnergySourceLevel(), chassis_state_expected.GetEnergySourceLevel());
    ASSERT_EQ(chassis_state.GetGearPosition(), chassis_state_expected.GetGearPosition());
    ASSERT_EQ(chassis_state.GetGearLevel(), chassis_state_expected.GetGearLevel());
    ASSERT_EQ(chassis_state.GetStateValue(), chassis_state_expected.GetStateValue());
    ASSERT_EQ(chassis_state.GetInvalidFlagValue(), chassis_state_expected.GetInvalidFlagValue());
}

TEST(ChassisStateIO, DecodeChassisState_2)
{
    ChassisState chassis_state, chassis_state_expected;

    chassis_state.SetTimestamp(holo::Timestamp(10, 20));
    chassis_state.SetVehicleSpeed(1.0f);
    chassis_state.SetFrontLeftWheelSpeed(2.0f);
    chassis_state.SetFrontRightWheelSpeed(3.0f);
    chassis_state.SetRearLeftWheelSpeed(4.0f);
    chassis_state.SetRearRightWheelSpeed(5.0f);
    chassis_state.SetFrontLeftWheelPulse(6.0f);
    chassis_state.SetFrontRightWheelPulse(7.0f);
    chassis_state.SetRearLeftWheelPulse(8.0f);
    chassis_state.SetRearRightWheelPulse(9.0f);
    chassis_state.SetLongitudinalAcceleration(10.0f);
    chassis_state.SetLateralAcceleration(11.0f);
    chassis_state.SetYawRate(12.0f);
    chassis_state.SetFrontWheelAngle(13.0f);
    chassis_state.SetLongitudinalControlValue(14.0f);
    chassis_state.SetEnergySourceLevel(30U);
    chassis_state.SetGearPosition(holo::common::ChassisState::GearPosition::D);
    chassis_state.SetGearLevel(4U);
    chassis_state.SetStateValue(7);
    chassis_state.SetInvalidFlagValue(7);

    YAML::Node node = YAML::Load(
        "{'timestamp':{'sec':10,'nsec':20},'vehicle_speed': 1,'front_left_wheel_speed': "
        "2,'front_right_wheel_speed': 3,'rear_left_wheel_speed': 4,'rear_right_wheel_speed': "
        "5,'front_left_wheel_pulse': 6,'front_right_wheel_pulse': 7,'rear_left_wheel_pulse': "
        "8,'rear_right_wheel_pulse': 9,'longitudinal_acceleration': 10,'lateral_acceleration': "
        "11,'yaw_rate': 12,'front_wheel_angle': 13,'longitudinal_control_value': 14,'energy_source_level': "
        "30,'gear_level': 4,'gear_position': 'D','states': [0x01,0x02,0x04],'invalid_flags': [0x01,0x02,0x04]}");

    chassis_state_expected = node.as<ChassisState>();

    ASSERT_EQ(chassis_state.GetTimestamp(), chassis_state_expected.GetTimestamp());
    ASSERT_EQ(chassis_state.GetVehicleSpeed(), chassis_state_expected.GetVehicleSpeed());
    ASSERT_EQ(chassis_state.GetFrontLeftWheelSpeed(), chassis_state_expected.GetFrontLeftWheelSpeed());
    ASSERT_EQ(chassis_state.GetFrontRightWheelSpeed(), chassis_state_expected.GetFrontRightWheelSpeed());
    ASSERT_EQ(chassis_state.GetRearLeftWheelSpeed(), chassis_state_expected.GetRearLeftWheelSpeed());
    ASSERT_EQ(chassis_state.GetRearRightWheelSpeed(), chassis_state_expected.GetRearRightWheelSpeed());
    ASSERT_EQ(chassis_state.GetLongitudinalAcceleration(), chassis_state_expected.GetLongitudinalAcceleration());
    ASSERT_EQ(chassis_state.GetLateralAcceleration(), chassis_state_expected.GetLateralAcceleration());
    ASSERT_EQ(chassis_state.GetYawRate(), chassis_state_expected.GetYawRate());
    ASSERT_EQ(chassis_state.GetFrontWheelAngle(), chassis_state_expected.GetFrontWheelAngle());
    ASSERT_EQ(chassis_state.GetLongitudinalControlValue(), chassis_state_expected.GetLongitudinalControlValue());
    ASSERT_EQ(chassis_state.GetEnergySourceLevel(), chassis_state_expected.GetEnergySourceLevel());
    ASSERT_EQ(chassis_state.GetGearPosition(), chassis_state_expected.GetGearPosition());
    ASSERT_EQ(chassis_state.GetGearLevel(), chassis_state_expected.GetGearLevel());
    ASSERT_EQ(chassis_state.GetStateValue(), chassis_state_expected.GetStateValue());
    ASSERT_EQ(chassis_state.GetInvalidFlagValue(), chassis_state_expected.GetInvalidFlagValue());
}

TEST(ChassisStateIO, DecodeChassisState_3)
{
    ChassisState chassis_state, chassis_state_expected;

    chassis_state.SetTimestamp(holo::Timestamp(10, 20));
    chassis_state.SetVehicleSpeed(1.0f);
    chassis_state.SetFrontLeftWheelSpeed(2.0f);
    chassis_state.SetFrontRightWheelSpeed(3.0f);
    chassis_state.SetRearLeftWheelSpeed(4.0f);
    chassis_state.SetRearRightWheelSpeed(5.0f);
    chassis_state.SetFrontLeftWheelPulse(6.0f);
    chassis_state.SetFrontRightWheelPulse(7.0f);
    chassis_state.SetRearLeftWheelPulse(8.0f);
    chassis_state.SetRearRightWheelPulse(9.0f);
    chassis_state.SetLongitudinalAcceleration(10.0f);
    chassis_state.SetLateralAcceleration(11.0f);
    chassis_state.SetYawRate(12.0f);
    chassis_state.SetFrontWheelAngle(13.0f);
    chassis_state.SetLongitudinalControlValue(14.0f);
    chassis_state.SetEnergySourceLevel(30U);
    chassis_state.SetGearPosition(holo::common::ChassisState::GearPosition::D);
    chassis_state.SetGearLevel(4U);
    chassis_state.SetStateValue(7);
    chassis_state.SetInvalidFlagValue(7);

    YAML::Node node =
        YAML::Load("{'timestamp':{'sec':10,'nsec':20},'vehicle_speed': 1,'front_left_wheel_speed': "
                   "2,'front_right_wheel_speed': 3,'rear_left_wheel_speed': 4,'rear_right_wheel_speed': "
                   "5,'front_left_wheel_pulse': 6,'front_right_wheel_pulse': 7,'rear_left_wheel_pulse': "
                   "8,'rear_right_wheel_pulse': 9,'longitudinal_acceleration': 10,'lateral_acceleration': "
                   "11,'yaw_rate': 12,'front_wheel_angle': 13,'longitudinal_control_value': 14,'energy_source_level': "
                   "30,'gear_level': 4,'gear_position': 'D','states': [0x01,'LATERAL_TAKEOVER',0x04],'invalid_flags': "
                   "[0x01,'FL_WHEEL_SPEED_INVALID',0x04]}");

    chassis_state_expected = node.as<ChassisState>();

    ASSERT_EQ(chassis_state.GetTimestamp(), chassis_state_expected.GetTimestamp());
    ASSERT_EQ(chassis_state.GetVehicleSpeed(), chassis_state_expected.GetVehicleSpeed());
    ASSERT_EQ(chassis_state.GetFrontLeftWheelSpeed(), chassis_state_expected.GetFrontLeftWheelSpeed());
    ASSERT_EQ(chassis_state.GetFrontRightWheelSpeed(), chassis_state_expected.GetFrontRightWheelSpeed());
    ASSERT_EQ(chassis_state.GetRearLeftWheelSpeed(), chassis_state_expected.GetRearLeftWheelSpeed());
    ASSERT_EQ(chassis_state.GetRearRightWheelSpeed(), chassis_state_expected.GetRearRightWheelSpeed());
    ASSERT_EQ(chassis_state.GetLongitudinalAcceleration(), chassis_state_expected.GetLongitudinalAcceleration());
    ASSERT_EQ(chassis_state.GetLateralAcceleration(), chassis_state_expected.GetLateralAcceleration());
    ASSERT_EQ(chassis_state.GetYawRate(), chassis_state_expected.GetYawRate());
    ASSERT_EQ(chassis_state.GetFrontWheelAngle(), chassis_state_expected.GetFrontWheelAngle());
    ASSERT_EQ(chassis_state.GetLongitudinalControlValue(), chassis_state_expected.GetLongitudinalControlValue());
    ASSERT_EQ(chassis_state.GetEnergySourceLevel(), chassis_state_expected.GetEnergySourceLevel());
    ASSERT_EQ(chassis_state.GetGearPosition(), chassis_state_expected.GetGearPosition());
    ASSERT_EQ(chassis_state.GetGearLevel(), chassis_state_expected.GetGearLevel());
    ASSERT_EQ(chassis_state.GetStateValue(), chassis_state_expected.GetStateValue());
    ASSERT_EQ(chassis_state.GetInvalidFlagValue(), chassis_state_expected.GetInvalidFlagValue());
}

TEST(ChassisStateIO, DecodeChassisState_4)
{
    ChassisState chassis_state, chassis_state_expected;

    chassis_state.SetTimestamp(holo::Timestamp(10, 20));
    chassis_state.SetVehicleSpeed(1.0f);
    chassis_state.SetFrontLeftWheelSpeed(2.0f);
    chassis_state.SetFrontRightWheelSpeed(3.0f);
    chassis_state.SetRearLeftWheelSpeed(4.0f);
    chassis_state.SetRearRightWheelSpeed(5.0f);
    chassis_state.SetFrontLeftWheelPulse(6.0f);
    chassis_state.SetFrontRightWheelPulse(7.0f);
    chassis_state.SetRearLeftWheelPulse(8.0f);
    chassis_state.SetRearRightWheelPulse(9.0f);
    chassis_state.SetLongitudinalAcceleration(10.0f);
    chassis_state.SetLateralAcceleration(11.0f);
    chassis_state.SetYawRate(12.0f);
    chassis_state.SetFrontWheelAngle(13.0f);
    chassis_state.SetLongitudinalControlValue(14.0f);
    chassis_state.SetEnergySourceLevel(30U);
    chassis_state.SetGearPosition(holo::common::ChassisState::GearPosition::D);
    chassis_state.SetGearLevel(4U);
    chassis_state.SetStateValue(7);
    chassis_state.SetInvalidFlagValue(10);

    YAML::Node node =
        YAML::Load("{'timestamp':{'sec':10,'nsec':20},'vehicle_speed': 1,'front_left_wheel_speed': "
                   "2,'front_right_wheel_speed': 3,'rear_left_wheel_speed': 4,'rear_right_wheel_speed': "
                   "5,'front_left_wheel_pulse': 6,'front_right_wheel_pulse': 7,'rear_left_wheel_pulse': "
                   "8,'rear_right_wheel_pulse': 9,'longitudinal_acceleration': 10,'lateral_acceleration': "
                   "11,'yaw_rate': 12,'front_wheel_angle': 13,'longitudinal_control_value': 14,'energy_source_level': "
                   "30,'gear_level': 4,'gear_position': 'D','states': 7,'invalid_flags': 10}");

    chassis_state_expected = node.as<ChassisState>();

    ASSERT_EQ(chassis_state.GetTimestamp(), chassis_state_expected.GetTimestamp());
    ASSERT_EQ(chassis_state.GetVehicleSpeed(), chassis_state_expected.GetVehicleSpeed());
    ASSERT_EQ(chassis_state.GetFrontLeftWheelSpeed(), chassis_state_expected.GetFrontLeftWheelSpeed());
    ASSERT_EQ(chassis_state.GetFrontRightWheelSpeed(), chassis_state_expected.GetFrontRightWheelSpeed());
    ASSERT_EQ(chassis_state.GetRearLeftWheelSpeed(), chassis_state_expected.GetRearLeftWheelSpeed());
    ASSERT_EQ(chassis_state.GetRearRightWheelSpeed(), chassis_state_expected.GetRearRightWheelSpeed());
    ASSERT_EQ(chassis_state.GetLongitudinalAcceleration(), chassis_state_expected.GetLongitudinalAcceleration());
    ASSERT_EQ(chassis_state.GetLateralAcceleration(), chassis_state_expected.GetLateralAcceleration());
    ASSERT_EQ(chassis_state.GetYawRate(), chassis_state_expected.GetYawRate());
    ASSERT_EQ(chassis_state.GetFrontWheelAngle(), chassis_state_expected.GetFrontWheelAngle());
    ASSERT_EQ(chassis_state.GetLongitudinalControlValue(), chassis_state_expected.GetLongitudinalControlValue());
    ASSERT_EQ(chassis_state.GetEnergySourceLevel(), chassis_state_expected.GetEnergySourceLevel());
    ASSERT_EQ(chassis_state.GetGearPosition(), chassis_state_expected.GetGearPosition());
    ASSERT_EQ(chassis_state.GetGearLevel(), chassis_state_expected.GetGearLevel());
    ASSERT_EQ(chassis_state.GetStateValue(), chassis_state_expected.GetStateValue());
    ASSERT_EQ(chassis_state.GetInvalidFlagValue(), chassis_state_expected.GetInvalidFlagValue());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
