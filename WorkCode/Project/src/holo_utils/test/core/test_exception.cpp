/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_deserializer_host_4.cpp
 * @brief Unit test for 4 byte aligned host byte order deserializer.
 * @author zhangjiannan(zhangjiannan@holomatic.com)
 * @date 2022-2-21
 */

#include <gtest/gtest.h>

#include <holo/core/exception.h>
#include <holo/core/types.h>
#include <iostream>

TEST(HoloException, OutOfRangeException)
{
    try
    {
        throw holo::exception::OutOfRangeException("Test Out Of Range");
    }
    catch (holo::exception::OutOfRangeException const& e)
    {
        EXPECT_EQ(0, std::strcmp(e.what(), "Test Out Of Range"));
    }
}

TEST(HoloException, OutOfRangeExceptionStringOverflow)
{
    try
    {
        throw holo::exception::OutOfRangeException(
            "tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt"
            "tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt"
            "tttttttttttttttttttttttttttttttttttttttttttt");  // 256 't'
    }
    catch (holo::exception::OutOfRangeException const& e)
    {
        EXPECT_EQ(
            0,
            std::strcmp(e.what(),
                        "tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt"
                        "tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt"
                        "ttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt"));  // 255 't'
    }
}

TEST(HoloException, RuntimeErrorException)
{
    try
    {
        throw holo::exception::RuntimeErrorException("Test RuntimeError");
    }
    catch (holo::exception::RuntimeErrorException const& e)
    {
        EXPECT_EQ(0, std::strcmp(e.what(), "Test RuntimeError"));
    }
}

TEST(HoloException, RuntimeErrorExceptionStringOverflow)
{
    try
    {
        throw holo::exception::RuntimeErrorException(
            "tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt"
            "tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt"
            "tttttttttttttttttttttttttttttttttttttttttttt");  // 256 't'
    }
    catch (holo::exception::RuntimeErrorException const& e)
    {
        EXPECT_EQ(
            0,
            std::strcmp(e.what(),
                        "tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt"
                        "tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt"
                        "ttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt"));  // 255 't'
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
