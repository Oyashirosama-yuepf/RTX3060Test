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

#include <holo/common/apa_control_command.h>

using namespace holo::common;

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

TEST(ApaControlCommand, GetSerializedSize)
{
    ApaControlCommand command;
    ASSERT_EQ(28, command.GetSerializedSize<4U>());
    ASSERT_EQ(32, command.GetSerializedSize<8U>());
}

TEST(ApaControlCommand, SerializeAndDeserialize)
{
    srand(time(0));
    ApaControlCommand input_control_command, output_control_command;
    input_control_command.SetTimestamp(holo::common::Timestamp(3, 500));
    input_control_command.SetLonAutoMode(true);
    input_control_command.SetTargetGearRequest(holo::uint8_t(3));
    input_control_command.SetStopDistRequest(holo::float32_t(5.0));
    input_control_command.SetSpeedLimitRequest(holo::float32_t(1.1));
    input_control_command.SetApafailBrkmodeRequest(holo::uint8_t(0));
    input_control_command.SetSteerAutoMode(true);
    input_control_command.SetSteeringAngle(holo::float32_t(100.0));

    uint8_t                           buffer[1024];
    holo::serialization::Serializer<> serializer(buffer, 1024);
    serializer << input_control_command;
    ASSERT_EQ(input_control_command.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> output_control_command;

    ASSERT_EQ(input_control_command.GetTimestamp(), output_control_command.GetTimestamp());
    ASSERT_EQ(input_control_command.GetLonAutoMode(), output_control_command.GetLonAutoMode());
    ASSERT_EQ(input_control_command.GetTargetGearRequest(), output_control_command.GetTargetGearRequest());
    ASSERT_EQ(input_control_command.GetStopDistRequest(), output_control_command.GetStopDistRequest());
    ASSERT_EQ(input_control_command.GetSpeedLimitRequest(), output_control_command.GetSpeedLimitRequest());
    ASSERT_EQ(input_control_command.GetApafailBrkmodeRequest(), output_control_command.GetApafailBrkmodeRequest());
    ASSERT_EQ(input_control_command.GetSteerAutoMode(), output_control_command.GetSteerAutoMode());
    ASSERT_EQ(input_control_command.GetSteeringAngle(), output_control_command.GetSteeringAngle());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
