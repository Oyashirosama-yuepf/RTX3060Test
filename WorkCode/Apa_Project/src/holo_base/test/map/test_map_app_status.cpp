/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_map_app_status.cpp
 * @brief Testing for MapAppStatus
 * @author wanghaiyang(wanghaiyang@holomaitc.com)
 * @date "2019-12-18"
 */

#include <gtest/gtest.h>

#include <holo/map/map_app_status.h>

TEST(TestMapAppStatus, TestConstructor)
{
    const holo::map::MapCodeType code = static_cast<holo::map::MapCodeType>(holo::map::MapStatusCode::K_COMMON_IO_ERROR);
    
    holo::map::MapAppStatus status;
    status.SetStatusCode(code);

    EXPECT_EQ(status.GetStatusCode(), code);
}

TEST(TestMapAppStatus, TestCopyConstructor)
{
    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);

    const holo::common::Timestamp ts(holo::uint32_t(time.tv_sec), holo::uint32_t(time.tv_nsec));
    const holo::map::MapCodeType code = static_cast<holo::map::MapCodeType>(holo::map::MapStatusCode::K_COMMON_IO_ERROR);

    holo::map::MapAppStatus raw_status;
    raw_status.SetTimestamp(ts);
    raw_status.SetStatusCode(code);

    const holo::map::MapAppStatus copy_status(raw_status);

    EXPECT_EQ(copy_status.GetTimestamp(), ts);
    EXPECT_EQ(copy_status.GetStatusCode(), code);
}

TEST(TestMapAppStatus, TestMoveConstructor)
{
    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);

    const holo::common::Timestamp ts(holo::uint32_t(time.tv_sec), holo::uint32_t(time.tv_nsec));
    const holo::map::MapCodeType code = static_cast<holo::map::MapCodeType>(holo::map::MapStatusCode::K_COMMON_IO_ERROR);

    holo::map::MapAppStatus raw_status;
    raw_status.SetTimestamp(ts);
    raw_status.SetStatusCode(code);

    const holo::map::MapAppStatus move_status(std::move(raw_status));

    EXPECT_EQ(move_status.GetTimestamp(), ts);
    EXPECT_EQ(move_status.GetStatusCode(), code);
}

TEST(TestMapAppStatus, TestCopyAssignment)
{
    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);

    const holo::common::Timestamp ts(holo::uint32_t(time.tv_sec), holo::uint32_t(time.tv_nsec));
    const holo::map::MapCodeType code = static_cast<holo::map::MapCodeType>(holo::map::MapStatusCode::K_COMMON_IO_ERROR);

    holo::map::MapAppStatus raw_status;
    raw_status.SetTimestamp(ts);
    raw_status.SetStatusCode(code);

    const holo::map::MapAppStatus copy_status = raw_status;

    EXPECT_EQ(copy_status.GetTimestamp(), ts);
    EXPECT_EQ(copy_status.GetStatusCode(), code);
}

TEST(TestMapAppStatus, TestMoveAssignment)
{
    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);

    const holo::common::Timestamp ts(holo::uint32_t(time.tv_sec), holo::uint32_t(time.tv_nsec));
    const holo::map::MapCodeType code = static_cast<holo::map::MapCodeType>(holo::map::MapStatusCode::K_COMMON_IO_ERROR);

    holo::map::MapAppStatus raw_status;
    raw_status.SetTimestamp(ts);
    raw_status.SetStatusCode(code);

    const holo::map::MapAppStatus move_status = std::move(raw_status);

    EXPECT_EQ(move_status.GetTimestamp(), ts);
    EXPECT_EQ(move_status.GetStatusCode(), code);
}

TEST(TestMapAppStatus, TestOperation)
{
    holo::map::MapAppStatus status;
    status.SetStatusCode(static_cast<holo::map::MapCodeType>(holo::map::MapModuleCode::K_COMMON) |
                         static_cast<holo::map::MapCodeType>(holo::map::MapStatusCode::K_OK));
    bool ok = false;
    if (status)
    {
        ok = true;
    }
    EXPECT_TRUE(ok);

    status.SetStatusCode(static_cast<holo::map::MapCodeType>(holo::map::MapModuleCode::K_NAVIGATOR) |
                         static_cast<holo::map::MapCodeType>(holo::map::MapStatusCode::K_COMMON_MAP_ROUTING_ERROR));
    ok = true;
    if (!status)
    {
        ok = false;
    }
    EXPECT_FALSE(ok);

    status.SetStatusCode(static_cast<holo::map::MapCodeType>(holo::map::MapModuleCode::K_NAVIGATOR) |
                         static_cast<holo::map::MapCodeType>(holo::map::MapStatusCode::K_OK));
    ok = false;
    if (status)
    {
        ok = true;
    }
    EXPECT_TRUE(ok);

    status.SetStatusCode(static_cast<holo::map::MapCodeType>(holo::map::MapModuleCode::K_NAVIGATOR) |
                         static_cast<holo::map::MapCodeType>(holo::map::MapStatusCode::K_COMMON_MAP_ROUTING_ERROR));
    ok = true;
    if (!status)
    {
        ok = false;
    }
    EXPECT_FALSE(ok);
}

TEST(TestMapAppStatus, TestIsWorking)
{
    holo::map::MapAppStatus status;
    status.SetStatusCode(static_cast<holo::map::MapCodeType>(holo::map::MapModuleCode::K_COMMON) |
                         static_cast<holo::map::MapCodeType>(holo::map::MapStatusCode::K_OK));
    bool ok = false;
    if (status.IsWorking())
    {
        ok = true;
    }
    EXPECT_TRUE(ok);

    status.SetStatusCode(static_cast<holo::map::MapCodeType>(holo::map::MapModuleCode::K_NAVIGATOR) |
                         static_cast<holo::map::MapCodeType>(holo::map::MapStatusCode::K_COMMON_MAP_ROUTING_ERROR));
    ok = true;
    if (!status.IsWorking())
    {
        ok = false;
    }
    EXPECT_FALSE(ok);

    status.SetStatusCode(static_cast<holo::map::MapCodeType>(holo::map::MapModuleCode::K_NAVIGATOR) |
                         static_cast<holo::map::MapCodeType>(holo::map::MapStatusCode::K_OK));
    ok = false;
    if (status.IsWorking())
    {
        ok = true;
    }
    EXPECT_TRUE(ok);

    status.SetStatusCode(static_cast<holo::map::MapCodeType>(holo::map::MapModuleCode::K_NAVIGATOR) |
                         static_cast<holo::map::MapCodeType>(holo::map::MapStatusCode::K_COMMON_MAP_ROUTING_ERROR));
    ok = true;
    if (!status.IsWorking())
    {
        ok = false;
    }
    EXPECT_FALSE(ok);
}

TEST(TestMapAppStatus, TestGetSetTimestamp)
{
    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);

    const holo::common::Timestamp ts(holo::uint32_t(time.tv_sec), holo::uint32_t(time.tv_nsec));

    holo::map::MapAppStatus status;
    status.SetTimestamp(ts);

    EXPECT_EQ(status.GetTimestamp(), ts);
}

TEST(TestMapAppStatus, TestGetSetStatusCode)
{
    holo::map::MapAppStatus status;

    const holo::map::MapCodeType code1 = static_cast<holo::map::MapCodeType>(holo::map::MapModuleCode::K_COMMON) |
                                         static_cast<holo::map::MapCodeType>(holo::map::MapStatusCode::K_OK);
    status.SetStatusCode(code1);
    EXPECT_EQ(status.GetStatusCode(), code1);
    
    const holo::map::MapCodeType code2 = static_cast<holo::map::MapCodeType>(holo::map::MapModuleCode::K_NAVIGATOR) |
                         static_cast<holo::map::MapCodeType>(holo::map::MapStatusCode::K_COMMON_MAP_ROUTING_ERROR);
    status.SetStatusCode(code2);
    EXPECT_EQ(status.GetStatusCode(), code2);
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
