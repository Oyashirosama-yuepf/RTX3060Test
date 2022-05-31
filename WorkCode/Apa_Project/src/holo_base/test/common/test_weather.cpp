/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_weather.cpp
 * @brief Unit test for Weather object.
 * @author lanshayun(lanshayun@holomaitc.com)
 * @date "2020-03-30"
 */

#include <gtest/gtest.h>
#include <holo/common/weather.h>

using Weather   = holo::common::Weather;

TEST(Weather, ConstructDefault)
{
    Weather weather;
    ASSERT_FALSE(weather.IsCloudy());
    ASSERT_FALSE(weather.IsRainy());
    ASSERT_FALSE(weather.IsSnowy());
    ASSERT_FALSE(weather.IsSandy());
    ASSERT_FALSE(weather.IsFoggy());
}

TEST(Weather, ConstructFromUint32)
{
    Weather weather(0u);
    ASSERT_FALSE(weather.IsCloudy());
    ASSERT_FALSE(weather.IsRainy());
    ASSERT_FALSE(weather.IsSnowy());
    ASSERT_TRUE(weather.IsFoggy());
    ASSERT_TRUE(weather.IsSandy());

    Weather weather1(0x1cf8f1);
    ASSERT_TRUE(weather1.IsCloudy());
    ASSERT_TRUE(weather1.IsRainy());
    ASSERT_EQ(weather1.GetRainFall(), 216);
    ASSERT_TRUE(weather1.IsSnowy());
    ASSERT_EQ(weather1.GetSnowFall(), 3);
    ASSERT_FALSE(weather1.IsFoggy());
    ASSERT_EQ(weather1.GetFoggyVisibility(), 1085);
    ASSERT_TRUE(weather1.IsSandy());
    ASSERT_EQ(weather1.GetSandyVisibility(), 980);
}

TEST(Weather, AssignUint32)
{
    Weather weather;
    weather = 0x111111;
    ASSERT_EQ(0x111111, weather);
}

TEST(Weather, CastUint32)
{
    Weather  weather(0x123456u);
    uint32_t value = weather;
    ASSERT_EQ(value, 0x123456u);
}

TEST(Weather, SetGetCloudy)
{
    Weather weather;
    ASSERT_FALSE(weather.IsCloudy());
    weather.SetCloudy(1u);
    ASSERT_TRUE(weather.IsCloudy());
    ASSERT_NO_THROW(weather.SetCloudy(2u));
}

TEST(Weather, SetGetRainy)
{
    Weather weather;
    ASSERT_FALSE(weather.IsRainy());
    weather.SetRainFall(30u);
    ASSERT_TRUE(weather.IsRainy());
    ASSERT_NEAR(weather.GetRainFall(), 30u, Weather::RAINY_MAPPED_PARAM);
    ASSERT_NO_THROW(weather.SetRainFall(300u));
    ASSERT_EQ(weather.GetRainFall(), 279u);
}

TEST(Weather, SetGetSnowy)
{
    Weather weather;
    ASSERT_FALSE(weather.IsSnowy());
    weather.SetSnowFall(3u);
    ASSERT_TRUE(weather.IsSnowy());
    ASSERT_EQ(weather.GetSnowFall(), 3u);
    ASSERT_NO_THROW(weather.SetSnowFall(40u));
    ASSERT_EQ(weather.GetSnowFall(), 31u);
}

TEST(Weather, SetGetFoggy)
{
    Weather weather;
    ASSERT_FALSE(weather.IsFoggy());
    weather.SetFoggyVisibility(4u);
    ASSERT_TRUE(weather.IsFoggy());
    ASSERT_NEAR(weather.GetFoggyVisibility(), 4u, Weather::VIS_MAPPED_PARAM);
    ASSERT_NO_THROW(weather.SetFoggyVisibility(1500u));
    ASSERT_EQ(weather.GetFoggyVisibility(), 1085u);
}

TEST(Weather, SetGetSandy)
{
    Weather weather;
    ASSERT_FALSE(weather.IsSandy());
    weather.SetSandyVisibility(500u);
    ASSERT_NEAR(weather.GetSandyVisibility(), 500u, Weather::VIS_MAPPED_PARAM);
    ASSERT_TRUE(weather.IsSandy());
    ASSERT_NO_THROW(weather.SetSandyVisibility(1200u));
    ASSERT_EQ(weather.GetSandyVisibility(), 1085u);
}

TEST(Weather, SetGetTimeStamp)
{
    const holo::common::Timestamp timestamp(1589895651u, 10000u);
    Weather               weather;
    weather.SetTimestamp(timestamp);
    ASSERT_EQ(weather.GetTimestamp(), timestamp);
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
