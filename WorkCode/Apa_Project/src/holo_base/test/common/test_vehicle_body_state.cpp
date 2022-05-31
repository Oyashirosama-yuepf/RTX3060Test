/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
/**
 * @file  test_vehicle_body_state.cpp
 * @brief Unit test for VehicleBodyState object
 * @author houyujian@holomatic.com
 * @author zhouhuishuang@holomatic.com
 * @date 2020-12-17
 */

#include <gtest/gtest.h>
#include <holo/common/vehicle_body_state.h>

TEST(VehicleBodyState, Construct)
{
    holo::common::VehicleBodyState state;
    EXPECT_EQ(0.0f, state.GetFrontLeftTirePressure());
    EXPECT_EQ(0.0f, state.GetFrontRightTirePressure());
    EXPECT_EQ(0.0f, state.GetRearLeftTirePressure());
    EXPECT_EQ(0.0f, state.GetRearRightTirePressure());

    EXPECT_FALSE(state.IsLeftTurnSignalOn());
    EXPECT_FALSE(state.IsRightTurnSignalOn());
    EXPECT_FALSE(state.IsHazardFlasherOn());
    EXPECT_FALSE(state.IsLowBeamOn());
    EXPECT_FALSE(state.IsHighBeamOn());
    EXPECT_FALSE(state.IsBrakeLightOn());
    EXPECT_FALSE(state.IsFrontFogLightOn());
    EXPECT_FALSE(state.IsRearFogLightOn());

    EXPECT_FALSE(state.DoDriverSeatbeltNeedFastening());
    EXPECT_FALSE(state.DoPassengerSeatbeltNeedFastening());

    EXPECT_FALSE(state.IsDoorOpen());
    EXPECT_FALSE(state.IsFrontLeftDoorOpen());
    EXPECT_FALSE(state.IsFrontRightDoorOpen());
    EXPECT_FALSE(state.IsRearLeftDoorOpen());
    EXPECT_FALSE(state.IsRearRightDoorOpen());
    EXPECT_FALSE(state.IsTrunkDoorOpen());
    EXPECT_FALSE(state.IsCarHoodOpen());

    EXPECT_FALSE(state.IsWindowOpen());
    EXPECT_FALSE(state.IsFrontLeftWindowOpen());
    EXPECT_FALSE(state.IsFrontRightWindowOpen());
    EXPECT_FALSE(state.IsRearLeftWindowOpen());
    EXPECT_FALSE(state.IsRearRightWindowOpen());
    EXPECT_FALSE(state.IsAutoSunroofOpen());

    EXPECT_FALSE(state.IsFrontWiperOpen());
    EXPECT_FALSE(state.IsRearWiperOpen());
}

TEST(VehicleBodyState, TirePressure)
{
    auto state = holo::common::VehicleBodyState();
    state.SetFrontLeftTirePressure(1.1f);
    EXPECT_EQ(1.1f, state.GetFrontLeftTirePressure());
    state.SetFrontRightTirePressure(2.2f);
    EXPECT_EQ(2.2f, state.GetFrontRightTirePressure());
    state.SetRearLeftTirePressure(3.3f);
    EXPECT_EQ(3.3f, state.GetRearLeftTirePressure());
    state.SetRearRightTirePressure(4.4f);
    EXPECT_EQ(4.4f, state.GetRearRightTirePressure());
}

TEST(VehicleBodyState, LightState)
{
    auto state = holo::common::VehicleBodyState();
    EXPECT_FALSE(state.IsLeftTurnSignalOn());
    EXPECT_FALSE(state.IsRightTurnSignalOn());
    EXPECT_FALSE(state.IsHazardFlasherOn());
    EXPECT_FALSE(state.IsLowBeamOn());
    EXPECT_FALSE(state.IsHighBeamOn());
    EXPECT_FALSE(state.IsBrakeLightOn());
    EXPECT_FALSE(state.IsFrontFogLightOn());
    EXPECT_FALSE(state.IsRearFogLightOn());

    state.SetLeftTurnSignal(true);
    EXPECT_TRUE(state.IsLeftTurnSignalOn());
    EXPECT_FALSE(state.IsRightTurnSignalOn());
    EXPECT_FALSE(state.IsHazardFlasherOn());
    EXPECT_FALSE(state.IsBrakeLightOn());
    EXPECT_TRUE(state.IsLeftTurnSignalOn());
    EXPECT_FALSE(state.IsRightTurnSignalOn());
    EXPECT_FALSE(state.IsHazardFlasherOn());
    EXPECT_FALSE(state.IsBrakeLightOn());

    state.SetLeftTurnSignal(false);
    state.SetRightTurnSignal(true);
    EXPECT_FALSE(state.IsLeftTurnSignalOn());
    EXPECT_TRUE(state.IsRightTurnSignalOn());
    EXPECT_FALSE(state.IsHazardFlasherOn());
    EXPECT_FALSE(state.IsBrakeLightOn());
    EXPECT_FALSE(state.IsLeftTurnSignalOn());
    EXPECT_TRUE(state.IsRightTurnSignalOn());
    EXPECT_FALSE(state.IsHazardFlasherOn());
    EXPECT_FALSE(state.IsBrakeLightOn());

    state.SetRightTurnSignal(false);
    state.SetHazardFlasher(true);
    EXPECT_FALSE(state.IsLeftTurnSignalOn());
    EXPECT_FALSE(state.IsRightTurnSignalOn());
    EXPECT_TRUE(state.IsHazardFlasherOn());
    EXPECT_FALSE(state.IsBrakeLightOn());
    EXPECT_FALSE(state.IsLeftTurnSignalOn());
    EXPECT_FALSE(state.IsRightTurnSignalOn());
    EXPECT_TRUE(state.IsHazardFlasherOn());
    EXPECT_FALSE(state.IsBrakeLightOn());

    state.SetHazardFlasher(false);
    state.SetBrakeLight(true);
    EXPECT_FALSE(state.IsLeftTurnSignalOn());
    EXPECT_FALSE(state.IsRightTurnSignalOn());
    EXPECT_FALSE(state.IsHazardFlasherOn());
    EXPECT_TRUE(state.IsBrakeLightOn());
    EXPECT_FALSE(state.IsLeftTurnSignalOn());
    EXPECT_FALSE(state.IsRightTurnSignalOn());
    EXPECT_FALSE(state.IsHazardFlasherOn());
    EXPECT_TRUE(state.IsBrakeLightOn());

    state.SetBrakeLight(false);
    EXPECT_FALSE(state.IsLeftTurnSignalOn());
    EXPECT_FALSE(state.IsRightTurnSignalOn());
    EXPECT_FALSE(state.IsHazardFlasherOn());
    EXPECT_FALSE(state.IsBrakeLightOn());

    state.SetLowBeam(true);
    EXPECT_TRUE(state.IsLowBeamOn());
    EXPECT_FALSE(state.IsHighBeamOn());
    EXPECT_TRUE(state.IsLowBeamOn());
    EXPECT_FALSE(state.IsHighBeamOn());

    state.SetLowBeam(false);
    state.SetHighBeam(true);
    EXPECT_FALSE(state.IsLowBeamOn());
    EXPECT_TRUE(state.IsHighBeamOn());
    EXPECT_FALSE(state.IsLowBeamOn());
    EXPECT_TRUE(state.IsHighBeamOn());

    state.SetHighBeam(false);
    EXPECT_FALSE(state.IsLowBeamOn());
    EXPECT_FALSE(state.IsHighBeamOn());

    state.SetFrontFogLight(true);
    EXPECT_TRUE(state.IsFrontFogLightOn());
    EXPECT_FALSE(state.IsRearFogLightOn());
    EXPECT_TRUE(state.IsFrontFogLightOn());
    EXPECT_FALSE(state.IsRearFogLightOn());

    state.SetFrontFogLight(false);
    state.SetRearFogLight(true);
    EXPECT_FALSE(state.IsFrontFogLightOn());
    EXPECT_TRUE(state.IsRearFogLightOn());
    EXPECT_FALSE(state.IsFrontFogLightOn());
    EXPECT_TRUE(state.IsRearFogLightOn());

    state.SetRearFogLight(false);
    EXPECT_FALSE(state.IsFrontFogLightOn());
    EXPECT_FALSE(state.IsRearFogLightOn());
}

TEST(VehicleBodyState, DoorSeatbeltState)
{
    auto state = holo::common::VehicleBodyState();
    EXPECT_FALSE(state.DoDriverSeatbeltNeedFastening());
    EXPECT_FALSE(state.DoPassengerSeatbeltNeedFastening());
    EXPECT_FALSE(state.IsFrontLeftDoorOpen());
    EXPECT_FALSE(state.IsFrontRightDoorOpen());
    EXPECT_FALSE(state.IsRearLeftDoorOpen());
    EXPECT_FALSE(state.IsRearRightDoorOpen());
    EXPECT_FALSE(state.IsTrunkDoorOpen());
    EXPECT_FALSE(state.IsCarHoodOpen());

    state.SetNeedFasteningSeatbelt(true, true);
    EXPECT_TRUE(state.DoDriverSeatbeltNeedFastening());
    EXPECT_TRUE(state.DoPassengerSeatbeltNeedFastening());

    state.SetNeedFasteningSeatbelt(true, false);
    EXPECT_TRUE(state.DoDriverSeatbeltNeedFastening());
    EXPECT_FALSE(state.DoPassengerSeatbeltNeedFastening());

    state.SetNeedFasteningSeatbelt(false, false);
    EXPECT_FALSE(state.DoDriverSeatbeltNeedFastening());
    EXPECT_FALSE(state.DoPassengerSeatbeltNeedFastening());

    state.SetDoorState(true, true, true, true, true, true);
    EXPECT_TRUE(state.IsDoorOpen());
    EXPECT_TRUE(state.IsFrontLeftDoorOpen());
    EXPECT_TRUE(state.IsFrontRightDoorOpen());
    EXPECT_TRUE(state.IsRearLeftDoorOpen());
    EXPECT_TRUE(state.IsRearRightDoorOpen());
    EXPECT_TRUE(state.IsTrunkDoorOpen());
    EXPECT_TRUE(state.IsCarHoodOpen());

    state.SetDoorState(false, false, false, false, false, false);
    EXPECT_FALSE(state.IsDoorOpen());
    EXPECT_FALSE(state.IsFrontLeftDoorOpen());
    EXPECT_FALSE(state.IsFrontRightDoorOpen());
    EXPECT_FALSE(state.IsRearLeftDoorOpen());
    EXPECT_FALSE(state.IsRearRightDoorOpen());
    EXPECT_FALSE(state.IsTrunkDoorOpen());
    EXPECT_FALSE(state.IsCarHoodOpen());
}

TEST(VehicleBodyState, WindowState)
{
    auto state = holo::common::VehicleBodyState();
    EXPECT_FALSE(state.IsWindowOpen());
    EXPECT_FALSE(state.IsFrontLeftWindowOpen());
    EXPECT_FALSE(state.IsFrontRightWindowOpen());
    EXPECT_FALSE(state.IsRearLeftWindowOpen());
    EXPECT_FALSE(state.IsRearRightWindowOpen());
    EXPECT_FALSE(state.IsAutoSunroofOpen());

    state.SetWindowState(true, true, true, true, true);
    EXPECT_TRUE(state.IsWindowOpen());
    EXPECT_TRUE(state.IsFrontLeftWindowOpen());
    EXPECT_TRUE(state.IsFrontRightWindowOpen());
    EXPECT_TRUE(state.IsRearLeftWindowOpen());
    EXPECT_TRUE(state.IsRearRightWindowOpen());
    EXPECT_TRUE(state.IsAutoSunroofOpen());

    state.SetWindowState(false, false, false, true, true);
    EXPECT_FALSE(state.IsRearLeftWindowOpen());
    EXPECT_FALSE(state.IsFrontLeftWindowOpen());
    EXPECT_FALSE(state.IsFrontRightWindowOpen());
}

TEST(VehicleBodyState, WiperState)
{
    auto state = holo::common::VehicleBodyState();
    EXPECT_FALSE(state.IsFrontWiperOpen());
    EXPECT_FALSE(state.IsRearWiperOpen());

    state.SetWiperState(true, true);
    EXPECT_TRUE(state.IsFrontWiperOpen());
    EXPECT_TRUE(state.IsRearWiperOpen());
}

TEST(VehicleBodyState, GetSerializedSize)
{
    auto state = holo::common::VehicleBodyState();
    ASSERT_EQ(32, state.GetSerializedSize<4U>());
    ASSERT_EQ(32, state.GetSerializedSize<8U>());
}

TEST(VehicleBodyState, SerializeDeserialize)
{
    uint8_t buffer[1024];
    holo::serialization::Serializer<>           ser(buffer, 1024);
    holo::common::VehicleBodyState    vbs_serialize;
    holo::common::VehicleBodyState    vbs_deserialize;
    vbs_serialize.SetFrontLeftTirePressure(101.0);
    vbs_serialize.SetFrontRightTirePressure(102.0);
    vbs_serialize.SetRearLeftTirePressure(103.0);
    vbs_serialize.SetRearRightTirePressure(104.0);
    vbs_serialize.SetDoorState(true, true, true, true, true, true);
    ser << vbs_serialize;
    EXPECT_EQ(vbs_serialize.GetSerializedSize(), ser.GetSize());

    holo::serialization::Deserializer<> des(buffer, ser.GetSize());
    des >> vbs_deserialize;
    EXPECT_EQ(vbs_serialize.GetFrontLeftTirePressure(), vbs_deserialize.GetFrontLeftTirePressure());
    EXPECT_EQ(vbs_serialize.GetFrontRightTirePressure(), vbs_deserialize.GetFrontRightTirePressure());
    EXPECT_EQ(vbs_serialize.GetRearLeftTirePressure(), vbs_deserialize.GetRearLeftTirePressure());
    EXPECT_EQ(vbs_serialize.GetRearRightTirePressure(), vbs_deserialize.GetRearRightTirePressure());
    EXPECT_TRUE(vbs_deserialize.IsDoorOpen());
    EXPECT_TRUE(vbs_deserialize.IsFrontLeftDoorOpen());
    EXPECT_TRUE(vbs_deserialize.IsFrontRightDoorOpen());
    EXPECT_TRUE(vbs_deserialize.IsRearLeftDoorOpen());
    EXPECT_TRUE(vbs_deserialize.IsRearRightDoorOpen());
    EXPECT_TRUE(vbs_deserialize.IsTrunkDoorOpen());
    EXPECT_TRUE(vbs_deserialize.IsCarHoodOpen());
}

// TEST(VehicleBodyState, SerializeDeserialize)
// {
//     holo::utils::FixedSizeBuffer<32U> buffer;
//     holo::serialization::Serializer<true, 4>  ser(buffer);
//     holo::common::VehicleBodyState    vbs_serialize;
//     holo::common::VehicleBodyState    vbs_deserialize;
//     vbs_serialize.SetFrontLeftTirePressure(101.0);
//     vbs_serialize.SetFrontRightTirePressure(102.0);
//     vbs_serialize.SetRearLeftTirePressure(103.0);
//     vbs_serialize.SetRearRightTirePressure(104.0);
//     vbs_serialize.SetDoorState(true, true, true, true, true, true);
//     ser << vbs_serialize;
//     EXPECT_EQ(vbs_serialize.GetSerializedSize(), ser.GetSize());

//     holo::serialization::Deserializer<true, 4> des(buffer);
//     des >> vbs_deserialize;
//     EXPECT_EQ(vbs_serialize.GetFrontLeftTirePressure(), vbs_deserialize.GetFrontLeftTirePressure());
//     EXPECT_EQ(vbs_serialize.GetFrontRightTirePressure(), vbs_deserialize.GetFrontRightTirePressure());
//     EXPECT_EQ(vbs_serialize.GetRearLeftTirePressure(), vbs_deserialize.GetRearLeftTirePressure());
//     EXPECT_EQ(vbs_serialize.GetRearRightTirePressure(), vbs_deserialize.GetRearRightTirePressure());
//     EXPECT_TRUE(vbs_deserialize.IsDoorOpen());
//     EXPECT_TRUE(vbs_deserialize.IsFrontLeftDoorOpen());
//     EXPECT_TRUE(vbs_deserialize.IsFrontRightDoorOpen());
//     EXPECT_TRUE(vbs_deserialize.IsRearLeftDoorOpen());
//     EXPECT_TRUE(vbs_deserialize.IsRearRightDoorOpen());
//     EXPECT_TRUE(vbs_deserialize.IsTrunkDoorOpen());
//     EXPECT_TRUE(vbs_deserialize.IsCarHoodOpen());
// }
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
