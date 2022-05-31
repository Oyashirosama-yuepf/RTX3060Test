/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_chassis_state_meta_struct.cpp
 * @brief unit test for chassis state meta struct
 * @author zhangjiannan@holomatic.com
 * @date 2021-01-11
 */

#include <gtest/gtest.h>
#include <holo/common/chassis_state.h>
#include <holo/metadata/common/chassis_state_type_description.h>
#include <holo/metadata/meta_struct.h>
#include <holo/utils/buffer.h>

TEST(ChassisStateMetaStruct, Decode)
{
    holo::common::ChassisState state;
    state.SetVehicleSpeed(10.0f);
    state.SetFrontLeftWheelSpeed(10.1f);
    state.SetFrontRightWheelSpeed(10.2f);
    state.SetRearLeftWheelSpeed(10.3f);
    state.SetRearRightWheelSpeed(10.4f);
    state.SetFrontLeftWheelPulse(1000);
    state.SetFrontRightWheelPulse(2000);
    state.SetRearLeftWheelPulse(3000);
    state.SetRearRightWheelPulse(4000);
    state.SetLongitudinalAcceleration(1.0f);
    state.SetLateralAcceleration(0.5f);
    state.SetYawRate(0.1f);
    state.SetFrontWheelAngle(0.3f);
    state.SetLongitudinalControlValue(-2.0f);
    state.SetEnergySourceLevel(30);
    state.SetGearPosition(holo::common::ChassisState::GearPosition::D);
    state.SetGearLevel(0);
    state.SetState(holo::common::ChassisState::State::LATERAL_TAKEOVER,
                   holo::common::ChassisState::State::LONGITUDINAL_TAKEOVER);
    state.SetInvalidFlag(holo::common::ChassisState::InvalidFlag::BRAKE_INVALID,
                         holo::common::ChassisState::InvalidFlag::FRONT_WHEEL_ANGLE_INVALID);

    holo::utils::FixedSizeBuffer<1024> buf;
    holo::utils::Serializer<>          ser(buf);
    ser << state;

    std::shared_ptr<holo::metadata::MetaStruct> pmeta =
        holo::metadata::CreateMetaStruct(holo::metadata::TypeDescriptionResolver<holo::common::ChassisState>::Get());
    pmeta->Decode(buf.GetData(), buf.GetSize(), 0U);
    std::cout << pmeta->PrintToString() << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

