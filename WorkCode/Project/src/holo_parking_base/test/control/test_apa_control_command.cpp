/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_apa_control_command.h
 * @brief Unit test for class ApaControlCommand
 * @author zhangchun(zhangchun@holomaitc.com)
 * @date 2021-01-11
 */

#include <gtest/gtest.h>

#include <holo/parking/control/apa_control_command.h>

using namespace holo::parking::control;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ApaControlCommand, DefaultConstructor)
{
    ApaControlCommand command;

    ASSERT_EQ(command.GetLonAutoMode(), false);
    ASSERT_EQ(command.GetTargetGearRequest(), uint8_t(0));
    ASSERT_FLOAT_EQ(command.GetStopDistRequest(), 0.0f);
    ASSERT_FLOAT_EQ(command.GetSpeedLimitRequest(), 0.0f);
    ASSERT_EQ(command.GetApafailBrkmodeRequest(), uint8_t(0));
    ASSERT_EQ(command.GetSteerAutoMode(), false);
    ASSERT_FLOAT_EQ(command.GetSteeringAngle(), 0.0f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ApaControlCommand, GetterAndSetter)
{
    ApaControlCommand command;

    command.SetLonAutoMode(true);
    command.SetTargetGearRequest(uint8_t(1));
    command.SetStopDistRequest(5.0f);
    command.SetSpeedLimitRequest(1.1f);
    command.SetApafailBrkmodeRequest(uint8_t(1));
    command.SetSteerAutoMode(true);
    command.SetSteeringAngle(0.5f);

    // check results
    ASSERT_EQ(command.GetLonAutoMode(), true);
    ASSERT_EQ(command.GetTargetGearRequest(), uint8_t(1));
    ASSERT_FLOAT_EQ(command.GetStopDistRequest(), 5.0f);
    ASSERT_FLOAT_EQ(command.GetSpeedLimitRequest(), 1.1f);
    ASSERT_EQ(command.GetApafailBrkmodeRequest(), uint8_t(1));
    ASSERT_EQ(command.GetSteerAutoMode(), true);
    ASSERT_FLOAT_EQ(command.GetSteeringAngle(), 0.5f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
