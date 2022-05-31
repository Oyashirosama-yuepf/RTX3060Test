/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_weather_io.cpp
 * @brief unit test io utils for weather objects
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 2021-04-12
 */
#include <gtest/gtest.h>
#include <holo/common/weather.h>
#include <holo/io/common/weather.h>
#include <yaml-cpp/yaml.h>

using Weather = holo::common::Weather;

TEST(weatherIO, EncodeAndDecodeWeather)
{
    Weather weather(0x1cf8f1), weather_expected;

    YAML::Node node;
    node["test"]     = weather;
    weather_expected = node["test"].as<Weather>();

    ASSERT_EQ(weather.IsCloudy(), weather_expected.IsCloudy());
    ASSERT_EQ(weather.IsRainy(), weather_expected.IsRainy());
    ASSERT_EQ(weather.GetRainFall(), weather_expected.GetRainFall());
    ASSERT_EQ(weather.IsSnowy(), weather_expected.IsSnowy());
    ASSERT_EQ(weather.GetSnowFall(), weather_expected.GetSnowFall());
    ASSERT_EQ(weather.IsFoggy(), weather_expected.IsFoggy());
    ASSERT_EQ(weather.GetFoggyVisibility(), weather_expected.GetFoggyVisibility());
    ASSERT_EQ(weather.IsSandy(), weather_expected.IsSandy());
    ASSERT_EQ(weather.GetSandyVisibility(), weather_expected.GetSandyVisibility());
}

TEST(weatherIO, DecodeWeather_1)
{
    Weather weather, weather_expected;
    weather.SetTimestamp(holo::common::Timestamp(10, 20));
    weather.SetAllWeather(0x1cf8f1);

    YAML::Node node  = YAML::Load("{'timestamp':{'sec':10, 'nsec':20},'weather_category':0x1cf8f1}");
    weather_expected = node.as<Weather>();

    ASSERT_EQ(weather.IsCloudy(), weather_expected.IsCloudy());
    ASSERT_EQ(weather.IsRainy(), weather_expected.IsRainy());
    ASSERT_EQ(weather.GetRainFall(), weather_expected.GetRainFall());
    ASSERT_EQ(weather.IsSnowy(), weather_expected.IsSnowy());
    ASSERT_EQ(weather.GetSnowFall(), weather_expected.GetSnowFall());
    ASSERT_EQ(weather.IsFoggy(), weather_expected.IsFoggy());
    ASSERT_EQ(weather.GetFoggyVisibility(), weather_expected.GetFoggyVisibility());
    ASSERT_EQ(weather.IsSandy(), weather_expected.IsSandy());
    ASSERT_EQ(weather.GetSandyVisibility(), weather_expected.GetSandyVisibility());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
