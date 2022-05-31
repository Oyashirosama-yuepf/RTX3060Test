/**
 * @file test_serialization.cpp
 * @brief Unit test for serialization serialization
 * @author zhangjiannan(zhangjiannan@holomatic.com)
 * @date 2019-10-25
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <gtest/gtest.h>

#include <holo/core/types.h>
#include <holo/serialization/utility.h>

TEST(SerializationUtil, AlignedSize)
{
    ASSERT_EQ(0, holo::serialization::AlignedSize<4>(0));
    ASSERT_EQ(4, holo::serialization::AlignedSize<4>(1));
    ASSERT_EQ(4, holo::serialization::AlignedSize<4>(2));
    ASSERT_EQ(4, holo::serialization::AlignedSize<4>(3));
    ASSERT_EQ(4, holo::serialization::AlignedSize<4>(4));
    ASSERT_EQ(8, holo::serialization::AlignedSize<4>(5));
    ASSERT_EQ(8, holo::serialization::AlignedSize<4>(6));
    ASSERT_EQ(8, holo::serialization::AlignedSize<4>(7));
    ASSERT_EQ(8, holo::serialization::AlignedSize<4>(8));
    ASSERT_EQ(12, holo::serialization::AlignedSize<4>(9));

    ASSERT_EQ(0, holo::serialization::AlignedSize<8>(0));
    ASSERT_EQ(8, holo::serialization::AlignedSize<8>(1));
    ASSERT_EQ(8, holo::serialization::AlignedSize<8>(2));
    ASSERT_EQ(8, holo::serialization::AlignedSize<8>(3));
    ASSERT_EQ(8, holo::serialization::AlignedSize<8>(4));
    ASSERT_EQ(8, holo::serialization::AlignedSize<8>(5));
    ASSERT_EQ(8, holo::serialization::AlignedSize<8>(6));
    ASSERT_EQ(8, holo::serialization::AlignedSize<8>(7));
    ASSERT_EQ(8, holo::serialization::AlignedSize<8>(8));
    ASSERT_EQ(16, holo::serialization::AlignedSize<8>(9));
}

TEST(SerializationUtil, SerializedSize)
{
    uint8_t  a = 0;
    uint16_t b = 0;
    uint32_t c = 0;
    uint64_t d = 0;

    ASSERT_EQ(4U, holo::serialization::SerializedSize<4U>(a));
    ASSERT_EQ(4U, holo::serialization::SerializedSize<4U>(a, a));
    ASSERT_EQ(4U, holo::serialization::SerializedSize<4U>(a, b));
    ASSERT_EQ(4U, holo::serialization::SerializedSize<4U>(a, a, b));
    ASSERT_EQ(8U, holo::serialization::SerializedSize<4U>(a, a, b, a));
    ASSERT_EQ(8U, holo::serialization::SerializedSize<4U>(a, c));
    ASSERT_EQ(12U, holo::serialization::SerializedSize<4U>(a, d));

    ASSERT_EQ(8U, holo::serialization::SerializedSize<8U>(a));
    ASSERT_EQ(8U, holo::serialization::SerializedSize<8U>(a, a));
    ASSERT_EQ(8U, holo::serialization::SerializedSize<8U>(a, b));
    ASSERT_EQ(8U, holo::serialization::SerializedSize<8U>(a, a, b));
    ASSERT_EQ(8U, holo::serialization::SerializedSize<8U>(a, a, b, a));
    ASSERT_EQ(8U, holo::serialization::SerializedSize<8U>(a, c));
    ASSERT_EQ(16U, holo::serialization::SerializedSize<8U>(a, d));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

