/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_vehicle_body_state_io.cpp
 * @brief unit test io utils for vehicle_body_state objects
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 2021-04-12
 */
#include <gtest/gtest.h>
#include <holo/common/vehicle_body_state.h>
#include <holo/io/common/vehicle_body_state.h>

using VehicleBodyState = holo::common::VehicleBodyState;

TEST(VehicleBodyStateIO, EncodeAndDecodeVehicleBodyState)
{
    VehicleBodyState vehicle_body_state, vehicle_body_expected;

    vehicle_body_state.SetTimestamp(holo::common::Timestamp(10, 20));
    vehicle_body_state.SetFrontLeftTirePressure(101.0);
    vehicle_body_state.SetFrontRightTirePressure(102.0);
    vehicle_body_state.SetRearLeftTirePressure(103.0);
    vehicle_body_state.SetRearRightTirePressure(104.0);
    vehicle_body_state.SetStateValue(536870911);
    vehicle_body_state.SetInvalidFlagValue(1073741817);

    YAML::Node node;
    node["test"]          = vehicle_body_state;
    vehicle_body_expected = node["test"].as<VehicleBodyState>();

    EXPECT_EQ(vehicle_body_state.GetTimestamp(), vehicle_body_expected.GetTimestamp());
    EXPECT_EQ(vehicle_body_state.GetFrontLeftTirePressure(), vehicle_body_expected.GetFrontLeftTirePressure());
    EXPECT_EQ(vehicle_body_state.GetFrontRightTirePressure(), vehicle_body_expected.GetFrontRightTirePressure());
    EXPECT_EQ(vehicle_body_state.GetRearLeftTirePressure(), vehicle_body_expected.GetRearLeftTirePressure());
    EXPECT_EQ(vehicle_body_state.GetRearRightTirePressure(), vehicle_body_expected.GetRearRightTirePressure());
    EXPECT_EQ(vehicle_body_state.GetStateValue(), vehicle_body_expected.GetStateValue());
    EXPECT_EQ(vehicle_body_state.GetInvalidFlagValue(), vehicle_body_expected.GetInvalidFlagValue());
}

TEST(VehicleBodyStateIO, DecodeVehicleBodyState_1)
{
    VehicleBodyState vehicle_body_state, vehicle_body_expected;

    vehicle_body_state.SetTimestamp(holo::common::Timestamp(10, 20));
    vehicle_body_state.SetFrontLeftTirePressure(101.0);
    vehicle_body_state.SetFrontRightTirePressure(102.0);
    vehicle_body_state.SetRearLeftTirePressure(103.0);
    vehicle_body_state.SetRearRightTirePressure(104.0);
    vehicle_body_state.SetStateValue(536870911);
    vehicle_body_state.SetInvalidFlagValue(1073741823);

    YAML::Node node = YAML::Load(
        "{'timestamp':{'sec':10,'nsec':20},'front_left_tire_pressure':101.0,'front_right_tire_pressure':102.0,'rear_"
        "left_tire_pressure':103.0,'rear_right_tire_pressure':104,'states':536870911,'invalid_flags':1073741823}");
    vehicle_body_expected = node.as<VehicleBodyState>();

    EXPECT_EQ(vehicle_body_state.GetTimestamp(), vehicle_body_expected.GetTimestamp());
    EXPECT_EQ(vehicle_body_state.GetFrontLeftTirePressure(), vehicle_body_expected.GetFrontLeftTirePressure());
    EXPECT_EQ(vehicle_body_state.GetFrontRightTirePressure(), vehicle_body_expected.GetFrontRightTirePressure());
    EXPECT_EQ(vehicle_body_state.GetRearLeftTirePressure(), vehicle_body_expected.GetRearLeftTirePressure());
    EXPECT_EQ(vehicle_body_state.GetRearRightTirePressure(), vehicle_body_expected.GetRearRightTirePressure());
    EXPECT_EQ(vehicle_body_state.GetStateValue(), vehicle_body_expected.GetStateValue());
    EXPECT_EQ(vehicle_body_state.GetInvalidFlagValue(), vehicle_body_expected.GetInvalidFlagValue());
}

TEST(VehicleBodyStateIO, DecodeVehicleBodyState_2)
{
    VehicleBodyState vehicle_body_state, vehicle_body_expected;

    vehicle_body_state.SetTimestamp(holo::common::Timestamp(10, 20));
    vehicle_body_state.SetFrontLeftTirePressure(101.0);
    vehicle_body_state.SetFrontRightTirePressure(102.0);
    vehicle_body_state.SetRearLeftTirePressure(103.0);
    vehicle_body_state.SetRearRightTirePressure(104.0);
    vehicle_body_state.SetStateValue(7);
    vehicle_body_state.SetInvalidFlagValue(7);

    YAML::Node node = YAML::Load(
        "{'timestamp':{'sec':10,'nsec':20},'front_left_tire_pressure':101.0,'front_right_tire_pressure':102.0,'rear_"
        "left_tire_pressure':103.0,'rear_right_tire_pressure':104,'states':['LEFT_TURN_SIGNAL_ON','RIGHT_TURN_SIGNAL_"
        "ON','HARZARD_FLASHER_ON'],'invalid_flags':['LEFT_TURN_SIGNAL_INVALID','RIGHT_TURN_SIGNAL_INVALID','HARZARD_"
        "FLASHER_INVALID']}");
    vehicle_body_expected = node.as<VehicleBodyState>();

    EXPECT_EQ(vehicle_body_state.GetTimestamp(), vehicle_body_expected.GetTimestamp());
    EXPECT_EQ(vehicle_body_state.GetFrontLeftTirePressure(), vehicle_body_expected.GetFrontLeftTirePressure());
    EXPECT_EQ(vehicle_body_state.GetFrontRightTirePressure(), vehicle_body_expected.GetFrontRightTirePressure());
    EXPECT_EQ(vehicle_body_state.GetRearLeftTirePressure(), vehicle_body_expected.GetRearLeftTirePressure());
    EXPECT_EQ(vehicle_body_state.GetRearRightTirePressure(), vehicle_body_expected.GetRearRightTirePressure());
    EXPECT_EQ(vehicle_body_state.GetStateValue(), vehicle_body_expected.GetStateValue());
    EXPECT_EQ(vehicle_body_state.GetInvalidFlagValue(), vehicle_body_expected.GetInvalidFlagValue());
}

TEST(VehicleBodyStateIO, DecodeVehicleBodyState_3)
{
    VehicleBodyState vehicle_body_state, vehicle_body_expected;

    vehicle_body_state.SetTimestamp(holo::common::Timestamp(10, 20));
    vehicle_body_state.SetFrontLeftTirePressure(101.0);
    vehicle_body_state.SetFrontRightTirePressure(102.0);
    vehicle_body_state.SetRearLeftTirePressure(103.0);
    vehicle_body_state.SetRearRightTirePressure(104.0);
    vehicle_body_state.SetStateValue(7);
    vehicle_body_state.SetInvalidFlagValue(7);

    YAML::Node node = YAML::Load(
        "{'timestamp':{'sec':10,'nsec':20},'front_left_tire_pressure':101.0,'front_right_tire_pressure':102.0,'rear_"
        "left_tire_pressure':103.0,'rear_right_tire_pressure':104,'states':[0x01,'RIGHT_TURN_SIGNAL_ON',0x04],'invalid_"
        "flags':['LEFT_TURN_SIGNAL_INVALID',0x02,'HARZARD_FLASHER_INVALID']}");
    vehicle_body_expected = node.as<VehicleBodyState>();

    EXPECT_EQ(vehicle_body_state.GetTimestamp(), vehicle_body_expected.GetTimestamp());
    EXPECT_EQ(vehicle_body_state.GetFrontLeftTirePressure(), vehicle_body_expected.GetFrontLeftTirePressure());
    EXPECT_EQ(vehicle_body_state.GetFrontRightTirePressure(), vehicle_body_expected.GetFrontRightTirePressure());
    EXPECT_EQ(vehicle_body_state.GetRearLeftTirePressure(), vehicle_body_expected.GetRearLeftTirePressure());
    EXPECT_EQ(vehicle_body_state.GetRearRightTirePressure(), vehicle_body_expected.GetRearRightTirePressure());
    EXPECT_EQ(vehicle_body_state.GetStateValue(), vehicle_body_expected.GetStateValue());
    EXPECT_EQ(vehicle_body_state.GetInvalidFlagValue(), vehicle_body_expected.GetInvalidFlagValue());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
