/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_alarm_io.cpp
 * @brief unit test io utils for alarm objects
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 2021-04-12
 */

#include <gtest/gtest.h>
#include <holo/common/alarm.h>
#include <holo/io/common/alarm.h>

using Alarm = holo::common::Alarm;

TEST(alarmIO, EncodeAndDecodeAlarm)
{
    uint16_t value = static_cast<uint16_t>(Alarm::Level::FATAL_1) << 13;
    value += 12U;
    Alarm alarm(value);
    Alarm alarm_expected;

    YAML::Node node;
    node["test"]   = alarm;
    alarm_expected = node["test"].as<Alarm>();

    ASSERT_EQ(alarm, alarm_expected);
}

TEST(alarmIO, DecodeAlarm_1)
{
    uint16_t value = static_cast<uint16_t>(Alarm::Level::FATAL_1) << 13;
    value += 12U;
    Alarm alarm(value);
    Alarm alarm_expected;

    YAML::Node node = YAML::Load("{'level':'FATAL_1','code':12}");
    alarm_expected = node.as<Alarm>();

    ASSERT_EQ(alarm, alarm_expected);
}

TEST(alarmIO, DecodeAlarm_2)
{
    uint16_t value = static_cast<uint16_t>(Alarm::Level::FATAL_1) << 13;
    value += 12U;
    Alarm alarm(value);
    Alarm alarm_expected;

    YAML::Node node = YAML::Load("{'level':3,'code':12}");
    alarm_expected = node.as<Alarm>();

    ASSERT_EQ(alarm, alarm_expected);
}


TEST(alarmIO, DecodeAlarm_3)
{
    uint16_t value = static_cast<uint16_t>(Alarm::Level::FATAL_1) << 13;
    value += 12U;
    Alarm alarm(value);
    Alarm alarm_expected;

    YAML::Node node = YAML::Load("24588");
    alarm_expected = node.as<Alarm>();

    ASSERT_EQ(alarm, alarm_expected);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
