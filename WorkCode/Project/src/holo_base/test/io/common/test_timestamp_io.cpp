/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_timestamp_io.cpp
 * @brief unit test io utils for timestamp objects
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 2021-04-12
 */

#include <gtest/gtest.h>
#include <holo/common/timestamp.h>
#include <holo/io/common/timestamp.h>

using Duration  = holo::common::Duration;
using Timestamp = holo::common::Timestamp;

TEST(durationIO, DurationSaveYaml)
{
    Duration duration = Duration(10U, 20U);
    Duration duration_expected;

    YAML::Node node;
    node["test"]      = duration;
    duration_expected = node["test"].as<Duration>();

    ASSERT_EQ(duration.GetSec(), duration_expected.GetSec());
    ASSERT_EQ(duration.GetNsec(), duration_expected.GetNsec());
}

TEST(durationIO, DecodeDurationException)
{
    Duration duration_expected;
    YAML::Node node = YAML::Load("'sec':4");

    try
    {
        duration_expected = node.as<Duration>();
    }
    catch(...)
    {
    }
}

TEST(timestampIO, TimestampSaveYaml)
{
    Timestamp timestamp = Timestamp(40U, 80U);
    Timestamp timestamp_expected;

    YAML::Node node;
    node["test"]       = timestamp;
    timestamp_expected = node["test"].as<Timestamp>();

    ASSERT_EQ(timestamp.GetSec(), timestamp_expected.GetSec());
    ASSERT_EQ(timestamp.GetNsec(), timestamp_expected.GetNsec());
}

TEST(timestampIO, DecodeTimestampException_2)
{
    Timestamp timestamp_expected;
    YAML::Node node = YAML::Load("'sec':4");

    try
    {
        timestamp_expected = node.as<Timestamp>();
    }
    catch(...)
    {
    }
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
