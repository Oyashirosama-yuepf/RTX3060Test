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
#include <holo/common/app_status.h>
#include <holo/io/common/app_status.h>

using AppStatus = holo::common::AppStatus;

TEST(AppStatusIO, EncodeAndDecodeAppStatus)
{
    AppStatus status = {0x01, 0x02, 0x03, 0x04}, status_expected;
    status.SetTimestamp({100, 200});
    status.SetNodeId(10);

    YAML::Node node;
    node["test"]    = status;
    status_expected = node["test"].as<AppStatus>();

    EXPECT_EQ(status.GetTimestamp(), status_expected.GetTimestamp());
    EXPECT_EQ(status.GetNodeId(), status_expected.GetNodeId());
    ASSERT_EQ(status.size(), status_expected.size());
    for (size_t i = 0U; i < status.size(); ++i)
    {
        EXPECT_EQ(status[i], status_expected[i]);
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
