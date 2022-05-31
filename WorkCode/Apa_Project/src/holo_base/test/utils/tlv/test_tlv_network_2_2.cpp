/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_tlv.cpp
 * @brief Unit test for tlv object.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-06-21
 */

#include <gtest/gtest.h>
#include <holo/core/types.h>
#include <holo/utils/tlv.h>

using TlvType         = holo::utils::TlvT<uint16_t, uint16_t, true>;
using TlvSequenceType = holo::utils::TlvSequence<TlvType>;

static_assert(TlvType::LENGTH_OFFSET == 2U, "");
static_assert(TlvType::VALUE_OFFSET == 4U, "");

namespace holo
{
TEST(Tlv, ConstructorWithRawBuffer)
{
    uint8_t buffer[1024U] = {};
    TlvType tlv(buffer, 1024U);
}

TEST(Tlv, SetGetType)
{
    uint8_t buffer[1024U] = {};
    TlvType tlv(buffer, 1024U);

    tlv.SetType(0x01);
    ASSERT_EQ(0x01, tlv.GetType());
}

TEST(Tlv, GetLength)
{
    uint8_t buffer[1024U] = {};
    TlvType tlv(buffer, 1024U);

    tlv.SetType(0x01);
    ASSERT_EQ(0x00, tlv.GetLength());
}

TEST(Tlv, GetSetValue)
{
    uint8_t buffer[1024U] = {};
    TlvType tlv(buffer, 1024U);

    tlv.SetType(0x01);

    char char_value = 'c';
    tlv.SetValue(char_value);
    ASSERT_EQ(0x04, tlv.GetLength());
    ASSERT_EQ(char_value, tlv.GetValue<char>());

    uint16_t u16_value = 0x1234U;
    tlv.SetValue(u16_value);
    ASSERT_EQ(0x04, tlv.GetLength());
    ASSERT_EQ(0x1234U, tlv.GetValue<uint16_t>());

    uint32_t u32_value = 0x12345678U;
    tlv.SetValue(u32_value);
    ASSERT_EQ(0x04, tlv.GetLength());
    ASSERT_EQ(0x12345678U, tlv.GetValue<uint32_t>());

    uint64_t u64_value = 0x123456789abcdef0U;
    tlv.SetValue(u64_value);
    ASSERT_EQ(0x08, tlv.GetLength());
    ASSERT_EQ(0x123456789abcdef0U, tlv.GetValue<uint64_t>());

    float32_t f32_value = 1.0f;
    tlv.SetValue(f32_value);
    ASSERT_EQ(0x04, tlv.GetLength());
    ASSERT_EQ(1.0f, tlv.GetValue<float32_t>());

    float64_t f64_value = 1.0;
    tlv.SetValue(f64_value);
    ASSERT_EQ(0x08, tlv.GetLength());
    ASSERT_EQ(1.0, tlv.GetValue<float64_t>());
}

TEST(Tlv, GetSetValuesMixedScalarType)
{
    uint8_t buffer[1024U] = {};
    TlvType tlv(buffer, 1024U);

    tlv.SetType(0x01);

    tlv.SetValues('c', 1.0, 2.0f);

    char      c;
    float64_t f64;
    float32_t f32;

    ASSERT_EQ(16U, tlv.GetLength());
    tlv.GetValues(c, f64, f32);
    ASSERT_EQ('c', c);
    ASSERT_EQ(1.0, f64);
    ASSERT_EQ(2.0f, f32);

    c   = '0';
    f32 = 0.0f;

    tlv.GetValues(c, static_cast<float64_t>(0), f32);
    ASSERT_EQ('c', c);
    ASSERT_EQ(2.0f, f32);
}

TEST(Tlv, GetSetValuesScalarArray)
{
    uint8_t buffer[1024U] = {};
    TlvType tlv(buffer, 1024U);

    tlv.SetType(0x01);

    uint32_t values[]    = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    uint32_t values2[16] = {};
    size_t   size;

    tlv.SetValues(&values[0], 10);
    tlv.GetValues(&values2[0], size);
    ASSERT_EQ(44U, tlv.GetLength());
    ASSERT_EQ(10U, size);

    char c = 'a';
    tlv.SetValues(c, values, 10);
    tlv.GetValues(c, values2, size);
    ASSERT_EQ(44U, tlv.GetLength());
    ASSERT_EQ(10U, size);
}

TEST(Tlv, GetSetValuesStringType)
{
    uint8_t buffer[1024U] = {};
    TlvType tlv(buffer, 1024U);

    tlv.SetType(0x01);

    std::string s1("Hello World!");
    std::string s2;
    tlv.SetValues(s1);
    tlv.GetValues(s2);
    ASSERT_EQ(s1, s2);
    ASSERT_EQ(16U, tlv.GetLength());

    char c = 'a';

    tlv.SetValues(c, s1);
    tlv.GetValues(c, s2);
    ASSERT_EQ(20U, tlv.GetLength());
    ASSERT_EQ(s1, s2);
}

TEST(Tlv, GetSetValuesRawStringType)
{
    uint8_t buffer[1024U] = {};
    TlvType tlv(buffer, 1024U);

    tlv.SetType(0x01);

    char const* s1      = "Hello World!";
    char        s2[32U] = {};
    tlv.SetValues(s1);
    tlv.GetValues(s2);
    ASSERT_EQ(0, std::strcmp(s1, s2));
    ASSERT_EQ(16U, tlv.GetLength());

    char c = 'a';

    tlv.SetValues(c, s1);
    tlv.GetValues(c, s2);
    ASSERT_EQ(20U, tlv.GetLength());
    ASSERT_EQ(0, std::strcmp(s1, s2));
}

TEST(Tlv, Set)
{
    uint8_t buffer[1024U] = {};
    TlvType tlv(buffer, 1024U);

    tlv.Set(0x01, 'c', 1.0, 2.0f);

    char      c;
    float64_t f64;
    float32_t f32;

    ASSERT_EQ(16U, tlv.GetLength());
    tlv.GetValues(c, f64, f32);
    ASSERT_EQ('c', c);
    ASSERT_EQ(1.0, f64);
    ASSERT_EQ(2.0f, f32);
}

TEST(TlvSequance, SetGetValues)
{
    uint8_t         buffer[1024U] = {};
    TlvSequenceType sequence(buffer, 1024U);

    auto iter = sequence.begin();
    iter->Set(0x01, 1);
    ASSERT_EQ(4U, iter->GetLength());
    ++iter;
    iter->Set(0x02, 1.0);
    ASSERT_EQ(8U, iter->GetLength());
    ++iter;
    iter->Set(0x03, "abcdefg", 2.0);
    ASSERT_EQ(16U, iter->GetLength());
    ++iter;
    iter->Set(0x00);
    ASSERT_EQ(0U, iter->GetLength());

    auto citer = sequence.cbegin();
    ASSERT_EQ(0x01, citer->GetType());
    ASSERT_EQ(1, citer->GetValue<int32_t>());
    ++citer;
    ASSERT_EQ(0x02, citer->GetType());
    ASSERT_EQ(1.0, citer->GetValue<float64_t>());
    ++citer;
    std::string s;
    float64_t   f;
    citer->GetValues(s, f);
    ASSERT_EQ("abcdefg", s);
    ASSERT_EQ(2.0, f);
}

TEST(TlvSequance, GetLength)
{
    uint8_t         buffer[1024U] = {};
    TlvSequenceType sequence(buffer, 1024U);

    auto iter = sequence.begin();
    iter->Set(0x01, 1);
    ASSERT_EQ(4U, iter->GetLength());
    ++iter;
    iter->Set(0x02, 1.0);
    ASSERT_EQ(8U, iter->GetLength());
    ++iter;
    iter->Set(0x03, "abcdefg", 2.0);
    ASSERT_EQ(16U, iter->GetLength());
    ++iter;
    iter->Set(0x00);
    ASSERT_EQ(0U, iter->GetLength());

    ASSERT_EQ(44U, sequence.GetLength());
}

}  // namespace holo

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

