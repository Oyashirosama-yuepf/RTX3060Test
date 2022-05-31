/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_light_signal_request_io.cpp
 * @brief unit test io utils for light_signal_request objects
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 2021-04-12
 */

#include <gtest/gtest.h>
#include <holo/common/light_signal_request.h>
#include <holo/io/common/light_signal_request.h>

using LightSignalRequest = holo::LightSignalRequest;

TEST(LightSignalRequestIO, EncodeAndDecodeLightSignalRequest)
{
    LightSignalRequest light_signal_request, light_signal_request_expected;

    holo::common::Timestamp timestamp(1234, 5678);
    light_signal_request.SetTimestamp(timestamp);
    light_signal_request.SetBrakeLight(true);
    light_signal_request.SetHazardFlasher(true);
    light_signal_request.SetRightTurnSignal(true);
    light_signal_request.SetLeftTurnSignal(true);

    YAML::Node node;
    node["test"]                  = light_signal_request;
    light_signal_request_expected = node["test"].as<LightSignalRequest>();

    ASSERT_EQ(light_signal_request.GetTimestamp(), light_signal_request_expected.GetTimestamp());
    ASSERT_EQ(light_signal_request.GetLightCommand(), light_signal_request_expected.GetLightCommand());
}

TEST(LightSignalRequestIO, DecodeLightSignalRequest_1)
{
    LightSignalRequest light_signal_request, light_signal_request_expected;

    light_signal_request.SetTimestamp(holo::common::Timestamp(10, 20));
    light_signal_request.SetLightCommand(0x0040);

    YAML::Node node               = YAML::Load("{'timestamp':{'sec':10,'nsec':20},'light_command':0x0040}");
    light_signal_request_expected = node.as<LightSignalRequest>();

    ASSERT_EQ(light_signal_request.GetTimestamp(), light_signal_request_expected.GetTimestamp());
    ASSERT_EQ(light_signal_request.GetLightCommand(), light_signal_request_expected.GetLightCommand());
}

TEST(LightSignalRequestIO, DecodeLightSignalRequest_2)
{
    LightSignalRequest light_signal_request, light_signal_request_expected;

    light_signal_request.SetTimestamp(holo::common::Timestamp(10, 20));
    light_signal_request.SetLightCommand(100);

    YAML::Node node = YAML::Load(
        "{'timestamp':{'sec':10,'nsec':20},'light_command':['right_turn_signal','hazard_flasher','brake_light']}");
    light_signal_request_expected = node.as<LightSignalRequest>();

    ASSERT_EQ(light_signal_request.GetTimestamp(), light_signal_request_expected.GetTimestamp());
    ASSERT_EQ(light_signal_request.GetLightCommand(), light_signal_request_expected.GetLightCommand());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
