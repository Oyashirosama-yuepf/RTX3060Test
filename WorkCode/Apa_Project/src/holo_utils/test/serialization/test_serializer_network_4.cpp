/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_serializer_network_4.cpp
 * @brief Unit test for 4byte aligned network byte order serializer.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-1-7
 */

#include <gtest/gtest.h>

#include <holo/core/types.h>
#include <holo/serialization/serializer.h>

using Serializer = holo::serialization::Serializer<true, 4>;

struct TestPoint
{
    uint32_t x;
    uint32_t y;

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return 8U;
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << x << y << holo::serialization::align;
    }
};

struct TestObject
{
    uint8_t         a;
    uint16_t        b;
    uint32_t        c;
    uint64_t        d;
    holo::float32_t e;
    holo::float64_t f;
    uint16_t        g;
    uint64_t        h;
    uint8_t         i;
    holo::float32_t j;
    uint8_t         k;
    std::string     l;

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return holo::serialization::SerializedSize<ALIGN>(a,b,c,d,e,f,g,h,i,j,k,l);
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << a << b << c << d << e << f << g << h << i << j << k << l << holo::serialization::align;
    }
};

TEST(Serializer, constructor)
{
    uint8_t    buffer[1024] = {0};
    Serializer ser(buffer, 1024);
    ASSERT_EQ(0, ser.GetSize());
    ASSERT_EQ(1024, ser.GetCapacity());
    ASSERT_EQ(buffer, ser.GetData());
}

TEST(Serializer, serialize_i8)
{
    uint8_t    buffer[1024] = {0};
    Serializer ser(buffer, 1024);
    int8_t     j = -127;
    for (uint8_t i = 0; i < 0xff; ++i)
    {
        ser << j;
        ASSERT_EQ(j, static_cast<int8_t>(buffer[i]));
        j++;
    }
    ser << holo::serialization::align;
    ASSERT_EQ(256, ser.GetSize());

    for (int32_t i = 256; i < 1024; i++)
    {
        ser << static_cast<int8_t>(0);
    }
    EXPECT_THROW(ser << static_cast<int8_t>(0), holo::serialization::SerializationBufferOverflowException);
}

TEST(Serializer, serialize_u8)
{
    uint8_t    buffer[1024] = {0};
    Serializer ser(buffer, 1024);
    for (uint8_t i = 0; i < 0xff; ++i)
    {
        ser << i;
        ASSERT_EQ(i, buffer[i]);
    }
    ser << holo::serialization::align;
    ASSERT_EQ(256, ser.GetSize());

    for (int32_t i = 256; i < 1024; i++)
    {
        ser << static_cast<uint8_t>(0);
    }
    EXPECT_THROW(ser << static_cast<uint8_t>(0), holo::serialization::SerializationBufferOverflowException);
}

TEST(Serializer, serialize_char)
{
    uint8_t    buffer[1024] = {0};
    Serializer   ser(buffer, 1024);
    holo::char_t expected_buf[] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    };
    for (uint8_t i = 0; i < 16; ++i)
    {
        ser << expected_buf[i];
        ASSERT_EQ(expected_buf[i], static_cast<int8_t>(buffer[i]));
    }
    ser << holo::serialization::align;
    ASSERT_EQ(16, ser.GetSize());

    for (int32_t i = 16; i < 1024; i++)
    {
        ser << static_cast<holo::char_t>(0);
    }
    EXPECT_THROW(ser << static_cast<holo::char_t>(0), holo::serialization::SerializationBufferOverflowException);
}

TEST(Serializer, serialize_char_unaligned)
{
    uint8_t    buffer[1024] = {0};
    Serializer   ser(buffer, 1024);
    holo::char_t expected_buf[] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    };
    ser << 'X';
    for (uint8_t i = 0; i < 16; ++i)
    {
        ser << expected_buf[i];
        ASSERT_EQ(expected_buf[i], static_cast<int8_t>(buffer[i + 1]));
    }
    ser << holo::serialization::align;
    ASSERT_EQ(20, ser.GetSize());

    for (int32_t i = 20; i < 1024; i++)
    {
        ser << static_cast<holo::char_t>(0);
    }
    EXPECT_THROW(ser << static_cast<holo::char_t>(0), holo::serialization::SerializationBufferOverflowException);
}

TEST(Serializer, serialize_i16)
{
    uint8_t    buffer[1024] = {0};
    Serializer ser(buffer, 1024);

    for (uint8_t i = 0; i < 0xff; ++i)
    {
        int16_t value = static_cast<int16_t>((0x00ff - i) << 8 | i);
        ser << value;
        ASSERT_EQ(0xff - i, buffer[i * 2]);
        ASSERT_EQ(i, buffer[i * 2 + 1]);

        ASSERT_EQ(0xff - i, buffer[i * 2]);
        ASSERT_EQ(i, buffer[i * 2 + 1]);
    }
    ser << holo::serialization::align;
    ASSERT_EQ(512, ser.GetSize());

    for (int32_t i = 0; i < 256; i++)
    {
        ser << static_cast<int16_t>(0);
    }
    EXPECT_THROW(ser << static_cast<int16_t>(0), holo::serialization::SerializationBufferOverflowException);
}

TEST(Serializer, serialize_i16_unaligned)
{
    uint8_t    buffer[1024] = {0};
    Serializer ser(buffer, 1024);
    ser << static_cast<uint8_t>(0x00);
    for (uint8_t i = 0; i < 0xff; ++i)
    {
        int16_t value = static_cast<int16_t>((0x00ff - i) << 8 | i);
        ser << value;

        ASSERT_EQ(0xff - i, buffer[i * 2 + 2]);
        ASSERT_EQ(i, buffer[i * 2 + 1 + 2]);

        ASSERT_EQ(0xff - i, buffer[i * 2 + 2]);
        ASSERT_EQ(i, buffer[i * 2 + 1 + 2]);
    }
    ser << holo::serialization::align;
    ASSERT_EQ(512, ser.GetSize());

    for (int32_t i = 0; i < 256; i++)
    {
        ser << static_cast<int16_t>(0);
    }
    EXPECT_THROW(ser << static_cast<int16_t>(0), holo::serialization::SerializationBufferOverflowException);
}

TEST(Serializer, serialize_u16)
{
    uint8_t    buffer[1024] = {0};
    Serializer ser(buffer, 1024);

    for (uint8_t i = 0; i < 0xff; ++i)
    {
        uint16_t value = ((0x00ff - i) << 8 | i);
        ser << value;
        ASSERT_EQ(0xff - i, buffer[i * 2]);
        ASSERT_EQ(i, buffer[i * 2 + 1]);

        ASSERT_EQ(0xff - i, buffer[i * 2]);
        ASSERT_EQ(i, buffer[i * 2 + 1]);
    }
    ser << holo::serialization::align;
    ASSERT_EQ(512, ser.GetSize());

    for (int32_t i = 0; i < 256; i++)
    {
        ser << static_cast<uint16_t>(0);
    }
    EXPECT_THROW(ser << static_cast<uint16_t>(0), holo::serialization::SerializationBufferOverflowException);
}

TEST(Serializer, serialize_u16_unaligned)
{
    uint8_t    buffer[1024] = {0};
    Serializer ser(buffer, 1024);
    ser << static_cast<uint8_t>(0x00);
    for (uint8_t i = 0; i < 0xff; ++i)
    {
        uint16_t value = ((0x00ff - i) << 8 | i);
        ser << value;
        ASSERT_EQ(0xff - i, buffer[i * 2 + 2]);
        ASSERT_EQ(i, buffer[i * 2 + 1 + 2]);

        ASSERT_EQ(0xff - i, buffer[i * 2 + 2]);
        ASSERT_EQ(i, buffer[i * 2 + 1 + 2]);
    }
    ser << holo::serialization::align;
    ASSERT_EQ(512, ser.GetSize());

    for (int32_t i = 0; i < 256; i++)
    {
        ser << static_cast<uint16_t>(0);
    }
    EXPECT_THROW(ser << static_cast<uint16_t>(0), holo::serialization::SerializationBufferOverflowException);
}

TEST(Serializer, serialize_i32)
{
    uint8_t    buffer[1024] = {0};
    Serializer ser(buffer, 1024);
    for (uint8_t i = 0; i < 32; ++i)
    {
        int32_t value = i;
        ser << value;

        ASSERT_EQ(((static_cast<uint32_t>(value)) & 0x000000FF), buffer[i * 4 + 3]);
        ASSERT_EQ(((static_cast<uint32_t>(value)) & 0x0000FF00) >> 8, buffer[i * 4 + 2]);
        ASSERT_EQ(((static_cast<uint32_t>(value)) & 0x00FF0000) >> 16, buffer[i * 4 + 1]);
        ASSERT_EQ(((static_cast<uint32_t>(value)) & 0xFF000000) >> 24, buffer[i * 4]);
    }
    ser << holo::serialization::align;
    ASSERT_EQ(128, ser.GetSize());

    for (int32_t i = 0; i < 224; i++)
    {
        ser << static_cast<uint32_t>(0);
    }
    EXPECT_THROW(ser << static_cast<uint32_t>(0), holo::serialization::SerializationBufferOverflowException);
}

TEST(Serializer, serialize_i32_unaligned)
{
    uint8_t    buffer[1024] = {0};
    Serializer ser(buffer, 1024);
    ser << static_cast<uint8_t>(5);
    for (uint8_t i = 0; i < 32; ++i)
    {
        int32_t value = i;
        ser << value;

        ASSERT_EQ(((static_cast<uint32_t>(value)) & 0x000000FF), buffer[i * 4 + 3 + 4]);
        ASSERT_EQ(((static_cast<uint32_t>(value)) & 0x0000FF00) >> 8, buffer[i * 4 + 2 + 4]);
        ASSERT_EQ(((static_cast<uint32_t>(value)) & 0x00FF0000) >> 16, buffer[i * 4 + 1 + 4]);
        ASSERT_EQ(((static_cast<uint32_t>(value)) & 0xFF000000) >> 24, buffer[i * 4 + 0 + 4]);
    }
    ser << holo::serialization::align;
    ASSERT_EQ(132, ser.GetSize());

    for (int32_t i = 0; i < 223; i++)
    {
        ser << static_cast<uint32_t>(0);
    }
    EXPECT_THROW(ser << static_cast<uint32_t>(0), holo::serialization::SerializationBufferOverflowException);
}

TEST(Serializer, serialize_u32)
{
    uint8_t    buffer[1024] = {0};
    Serializer ser(buffer, 1024);
    for (uint8_t i = 0; i < 32; ++i)
    {
        uint32_t value = i;
        ser << value;

        ASSERT_EQ((value & 0x000000FF), buffer[i * 4 + 3]);
        ASSERT_EQ((value & 0x0000FF00) >> 8, buffer[i * 4 + 2]);
        ASSERT_EQ((value & 0x00FF0000) >> 16, buffer[i * 4 + 1]);
        ASSERT_EQ((value & 0xFF000000) >> 24, buffer[i * 4 + 0]);
    }
    ser << holo::serialization::align;
    ASSERT_EQ(128, ser.GetSize());

    for (int32_t i = 0; i < 224; i++)
    {
        ser << static_cast<uint32_t>(0);
    }
    EXPECT_THROW(ser << static_cast<uint32_t>(0), holo::serialization::SerializationBufferOverflowException);
}

TEST(Serializer, serialize_u32_unaligned)
{
    uint8_t    buffer[1024] = {0};
    Serializer ser(buffer, 1024);
    ser << static_cast<uint8_t>(5);
    for (uint8_t i = 0; i < 32; ++i)
    {
        uint32_t value = i;
        ser << value;

        ASSERT_EQ((value & 0x000000FF), buffer[i * 4 + 3 + 4]);
        ASSERT_EQ((value & 0x0000FF00) >> 8, buffer[i * 4 + 2 + 4]);
        ASSERT_EQ((value & 0x00FF0000) >> 16, buffer[i * 4 + 1 + 4]);
        ASSERT_EQ((value & 0xFF000000) >> 24, buffer[i * 4 + 0 + 4]);
    }
    ser << holo::serialization::align;
    ASSERT_EQ(132, ser.GetSize());

    for (int32_t i = 0; i < 223; i++)
    {
        ser << static_cast<uint32_t>(0);
    }
    EXPECT_THROW(ser << static_cast<uint32_t>(0), holo::serialization::SerializationBufferOverflowException);
}

TEST(Serializer, serialize_i64)
{
    uint8_t    buffer[1024] = {0};
    Serializer ser(buffer, 1024);
    for (uint8_t i = 0; i < 32; ++i)
    {
        int64_t value = i;
        ser << value;

        ASSERT_EQ(((static_cast<uint64_t>(value)) & 0x00000000000000FF), buffer[i * 8 + 7]);
        ASSERT_EQ(((static_cast<uint64_t>(value)) & 0x000000000000FF00) >> 8, buffer[i * 8 + 6]);
        ASSERT_EQ(((static_cast<uint64_t>(value)) & 0x0000000000FF0000) >> 16, buffer[i * 8 + 5]);
        ASSERT_EQ(((static_cast<uint64_t>(value)) & 0x00000000FF000000) >> 24, buffer[i * 8 + 4]);
        ASSERT_EQ(((static_cast<uint64_t>(value)) & 0x000000FF00000000) >> 32, buffer[i * 8 + 3]);
        ASSERT_EQ(((static_cast<uint64_t>(value)) & 0x0000FF0000000000) >> 40, buffer[i * 8 + 2]);
        ASSERT_EQ(((static_cast<uint64_t>(value)) & 0x00FF000000000000) >> 48, buffer[i * 8 + 1]);
        ASSERT_EQ(((static_cast<uint64_t>(value)) & 0xFF00000000000000) >> 56, buffer[i * 8 + 0]);
    }
    ser << holo::serialization::align;
    ASSERT_EQ(256, ser.GetSize());
}

TEST(Serializer, serialize_i64_unaligned)
{
    uint8_t    buffer[1024] = {0};
    Serializer ser(buffer, 1024);
    ser << static_cast<uint8_t>(5);
    for (uint8_t i = 0; i < 32; ++i)
    {
        int64_t value = i;
        ser << value;

        ASSERT_EQ(((static_cast<uint64_t>(value)) & 0x00000000000000FF), buffer[i * 8 + 7 + 4]);
        ASSERT_EQ(((static_cast<uint64_t>(value)) & 0x000000000000FF00) >> 8, buffer[i * 8 + 6 + 4]);
        ASSERT_EQ(((static_cast<uint64_t>(value)) & 0x0000000000FF0000) >> 16, buffer[i * 8 + 5 + 4]);
        ASSERT_EQ(((static_cast<uint64_t>(value)) & 0x00000000FF000000) >> 24, buffer[i * 8 + 4 + 4]);
        ASSERT_EQ(((static_cast<uint64_t>(value)) & 0x000000FF00000000) >> 32, buffer[i * 8 + 3 + 4]);
        ASSERT_EQ(((static_cast<uint64_t>(value)) & 0x0000FF0000000000) >> 40, buffer[i * 8 + 2 + 4]);
        ASSERT_EQ(((static_cast<uint64_t>(value)) & 0x00FF000000000000) >> 48, buffer[i * 8 + 1 + 4]);
        ASSERT_EQ(((static_cast<uint64_t>(value)) & 0xFF00000000000000) >> 56, buffer[i * 8 + 0 + 4]);
    }
    ser << holo::serialization::align;
    ASSERT_EQ(260, ser.GetSize());

    for (int32_t i = 0; i < 95; i++)
    {
        ser << static_cast<int64_t>(0);
    }
    EXPECT_THROW(ser << static_cast<int64_t>(0), holo::serialization::SerializationBufferOverflowException);
}

TEST(Serializer, serialize_u64)
{
    uint8_t    buffer[1024] = {0};
    Serializer ser(buffer, 1024);
    for (uint8_t i = 0; i < 32; ++i)
    {
        uint64_t value = i;
        ser << value;

        ASSERT_EQ((value & 0x00000000000000FF), buffer[i * 8 + 7]);
        ASSERT_EQ((value & 0x000000000000FF00) >> 8, buffer[i * 8 + 6]);
        ASSERT_EQ((value & 0x0000000000FF0000) >> 16, buffer[i * 8 + 5]);
        ASSERT_EQ((value & 0x00000000FF000000) >> 24, buffer[i * 8 + 4]);
        ASSERT_EQ((value & 0x000000FF00000000) >> 32, buffer[i * 8 + 3]);
        ASSERT_EQ((value & 0x0000FF0000000000) >> 40, buffer[i * 8 + 2]);
        ASSERT_EQ((value & 0x00FF000000000000) >> 48, buffer[i * 8 + 1]);
        ASSERT_EQ((value & 0xFF00000000000000) >> 56, buffer[i * 8 + 0]);
    }
    ser << holo::serialization::align;
    ASSERT_EQ(256, ser.GetSize());

    for (int32_t i = 0; i < 96; i++)
    {
        ser << static_cast<uint64_t>(0);
    }
    EXPECT_THROW(ser << static_cast<uint64_t>(0), holo::serialization::SerializationBufferOverflowException);
}

TEST(Serializer, serialize_u64_unaligned)
{
    uint8_t    buffer[1024] = {0};
    Serializer ser(buffer, 1024);
    ser << static_cast<uint8_t>(5);
    for (uint8_t i = 0; i < 32; ++i)
    {
        uint64_t value = i;
        ser << value;

        ASSERT_EQ((value & 0x00000000000000FF), buffer[i * 8 + 7 + 4]);
        ASSERT_EQ((value & 0x000000000000FF00) >> 8, buffer[i * 8 + 6 + 4]);
        ASSERT_EQ((value & 0x0000000000FF0000) >> 16, buffer[i * 8 + 5 + 4]);
        ASSERT_EQ((value & 0x00000000FF000000) >> 24, buffer[i * 8 + 4 + 4]);
        ASSERT_EQ((value & 0x000000FF00000000) >> 32, buffer[i * 8 + 3 + 4]);
        ASSERT_EQ((value & 0x0000FF0000000000) >> 40, buffer[i * 8 + 2 + 4]);
        ASSERT_EQ((value & 0x00FF000000000000) >> 48, buffer[i * 8 + 1 + 4]);
        ASSERT_EQ((value & 0xFF00000000000000) >> 56, buffer[i * 8 + 0 + 4]);
    }
    ser << holo::serialization::align;
    ASSERT_EQ(260, ser.GetSize());

    for (int32_t i = 0; i < 95; i++)
    {
        ser << static_cast<uint64_t>(0);
    }
    EXPECT_THROW(ser << static_cast<uint64_t>(0), holo::serialization::SerializationBufferOverflowException);
}

TEST(Serializer, serialize_f32)
{
    uint8_t    buffer[1024] = {0};
    Serializer ser(buffer, 1024);
    for (uint8_t i = 0; i < 32; ++i)
    {
        holo::float32_t value = static_cast<holo::float32_t>(i);
        ser << value;

        uint32_t value0 = *(reinterpret_cast<uint32_t const*>(ser.GetData() + 4 * i));
        value0          = (value0 << 24) | ((value0 & 0x0000FF00) << 8) | ((value0 & 0x00FF0000) >> 8) | (value0 >> 24);
        holo::float32_t* f_ptr_0         = reinterpret_cast<holo::float32_t*>(&value0);
        holo::float32_t  expected_value0 = *f_ptr_0;
        uint32_t         value1          = *(reinterpret_cast<uint32_t const*>(buffer + 4 * i));
        value1 = (value1 << 24) | ((value1 & 0x0000FF00) << 8) | ((value1 & 0x00FF0000) >> 8) | (value1 >> 24);
        holo::float32_t* f_ptr_1         = reinterpret_cast<holo::float32_t*>(&value1);
        holo::float32_t  expected_value1 = *f_ptr_1;

        ASSERT_EQ(value, expected_value0);
        ASSERT_EQ(value, expected_value1);
    }
    ser << holo::serialization::align;
    ASSERT_EQ(128, ser.GetSize());

    for (int32_t i = 0; i < 224; i++)
    {
        ser << static_cast<holo::float32_t>(0.0);
    }
    EXPECT_THROW(ser << static_cast<holo::float32_t>(0.0), holo::serialization::SerializationBufferOverflowException);
}

TEST(Serializer, serialize_f32_unaligned)
{
    uint8_t    buffer[1024] = {0};
    Serializer ser(buffer, 1024);
    ser << static_cast<uint8_t>(5);
    for (uint8_t i = 0; i < 32; ++i)
    {
        holo::float32_t value = static_cast<holo::float32_t>(i);
        ser << value;

        uint32_t value0 = *(reinterpret_cast<uint32_t const*>(ser.GetData() + 4 * i + 4));
        value0          = (value0 << 24) | ((value0 & 0x0000FF00) << 8) | ((value0 & 0x00FF0000) >> 8) | (value0 >> 24);
        holo::float32_t* f_ptr_0         = reinterpret_cast<holo::float32_t*>(&value0);
        holo::float32_t  expected_value0 = *f_ptr_0;
        uint32_t         value1          = *(reinterpret_cast<uint32_t const*>(buffer + 4 * i + 4));
        value1 = (value1 << 24) | ((value1 & 0x0000FF00) << 8) | ((value1 & 0x00FF0000) >> 8) | (value1 >> 24);
        holo::float32_t* f_ptr_1         = reinterpret_cast<holo::float32_t*>(&value1);
        holo::float32_t  expected_value1 = *f_ptr_1;

        ASSERT_EQ(value, expected_value0);
        ASSERT_EQ(value, expected_value1);
    }
    ser << holo::serialization::align;
    ASSERT_EQ(132, ser.GetSize());

    for (int32_t i = 0; i < 223; i++)
    {
        ser << static_cast<holo::float32_t>(0.0);
    }
    EXPECT_THROW(ser << static_cast<holo::float32_t>(0.0), holo::serialization::SerializationBufferOverflowException);
}

TEST(Serializer, serialize_f64)
{
    uint8_t    buffer[1024] = {0};
    Serializer ser(buffer, 1024);
    for (uint8_t i = 0; i < 32; ++i)
    {
        holo::float64_t value = static_cast<holo::float64_t>(i);
        ser << value;

        uint64_t value0 = *(reinterpret_cast<uint64_t const*>(ser.GetData() + 8 * i));
        value0 = (value0 << 56) | ((value0 & 0x000000000000FF00) << 40) | ((value0 & 0x0000000000FF0000) << 24) |
                 ((value0 & 0x00000000FF000000) << 8) | ((value0 & 0x000000FF00000000) >> 8) |
                 ((value0 & 0x0000FF0000000000) >> 24) | ((value0 & 0x00FF000000000000) >> 40) | (value0 >> 56);
        holo::float64_t* f_ptr_0         = reinterpret_cast<holo::float64_t*>(&value0);
        holo::float64_t  expected_value0 = *f_ptr_0;
        uint64_t         value1          = *(reinterpret_cast<uint64_t const*>(buffer + 8 * i));
        value1 = (value1 << 56) | ((value1 & 0x000000000000FF00) << 40) | ((value1 & 0x0000000000FF0000) << 24) |
                 ((value1 & 0x00000000FF000000) << 8) | ((value1 & 0x000000FF00000000) >> 8) |
                 ((value1 & 0x0000FF0000000000) >> 24) | ((value1 & 0x00FF000000000000) >> 40) | (value1 >> 56);
        holo::float64_t* f_ptr_1         = reinterpret_cast<holo::float64_t*>(&value1);
        holo::float64_t  expected_value1 = *f_ptr_1;

        ASSERT_EQ(value, expected_value0);
        ASSERT_EQ(value, expected_value1);
    }
    ser << holo::serialization::align;
    ASSERT_EQ(256, ser.GetSize());

    for (int32_t i = 0; i < 96; i++)
    {
        ser << static_cast<holo::float64_t>(0.0);
    }
    EXPECT_THROW(ser << static_cast<holo::float64_t>(0.0), holo::serialization::SerializationBufferOverflowException);
}

TEST(Serializer, serialize_f64_unaligned)
{
    uint8_t    buffer[1024] = {0};
    Serializer ser(buffer, 1024);
    ser << static_cast<uint8_t>(5);
    for (uint8_t i = 0; i < 32; ++i)
    {
        holo::float64_t value = static_cast<holo::float64_t>(i);
        ser << value;

        uint64_t value0 = *(reinterpret_cast<uint64_t const*>(ser.GetData() + 8 * i + 4));
        value0 = (value0 << 56) | ((value0 & 0x000000000000FF00) << 40) | ((value0 & 0x0000000000FF0000) << 24) |
                 ((value0 & 0x00000000FF000000) << 8) | ((value0 & 0x000000FF00000000) >> 8) |
                 ((value0 & 0x0000FF0000000000) >> 24) | ((value0 & 0x00FF000000000000) >> 40) | (value0 >> 56);
        holo::float64_t* f_ptr_0         = reinterpret_cast<holo::float64_t*>(&value0);
        holo::float64_t  expected_value0 = *f_ptr_0;
        uint64_t         value1          = *(reinterpret_cast<uint64_t const*>(buffer + 8 * i + 4));
        value1 = (value1 << 56) | ((value1 & 0x000000000000FF00) << 40) | ((value1 & 0x0000000000FF0000) << 24) |
                 ((value1 & 0x00000000FF000000) << 8) | ((value1 & 0x000000FF00000000) >> 8) |
                 ((value1 & 0x0000FF0000000000) >> 24) | ((value1 & 0x00FF000000000000) >> 40) | (value1 >> 56);
        holo::float64_t* f_ptr_1         = reinterpret_cast<holo::float64_t*>(&value1);
        holo::float64_t  expected_value1 = *f_ptr_1;

        ASSERT_EQ(value, expected_value0);
        ASSERT_EQ(value, expected_value1);
    }
    ser << holo::serialization::align;
    ASSERT_EQ(260, ser.GetSize());

    for (int32_t i = 0; i < 95; i++)
    {
        ser << static_cast<holo::float64_t>(0.0);
    }
    EXPECT_THROW(ser << static_cast<holo::float64_t>(0.0), holo::serialization::SerializationBufferOverflowException);
}

TEST(Serializer, serialize_string)
{
    uint8_t    buffer[1024] = {0};
    Serializer  ser(buffer, 1024);
    std::string str = "hello holomatic";
    ser << str << holo::serialization::align;

    ASSERT_EQ('h', buffer[0]);
    ASSERT_EQ('e', buffer[1]);
    ASSERT_EQ('l', buffer[2]);
    ASSERT_EQ('l', buffer[3]);
    ASSERT_EQ('o', buffer[4]);
    ASSERT_EQ(' ', buffer[5]);
    ASSERT_EQ('h', buffer[6]);
    ASSERT_EQ('o', buffer[7]);
    ASSERT_EQ('l', buffer[8]);
    ASSERT_EQ('o', buffer[9]);
    ASSERT_EQ('m', buffer[10]);
    ASSERT_EQ('a', buffer[11]);
    ASSERT_EQ('t', buffer[12]);
    ASSERT_EQ('i', buffer[13]);
    ASSERT_EQ('c', buffer[14]);
    ASSERT_EQ(0, buffer[15]);

    ASSERT_EQ(16, ser.GetSize());

    for (int32_t i = 16; i < 1024; i++)
    {
        ser << static_cast<uint8_t>(0);
    }
    EXPECT_THROW(ser << str, holo::serialization::SerializationBufferOverflowException);
}

TEST(Serializer, tail_align)
{
    uint8_t    buffer[1024] = {0};
    Serializer ser(buffer, 1024);
    ASSERT_EQ(0, ser.GetSize());
    ser << static_cast<uint64_t>(4);
    ser << 'a' << 'b' << 'c';
    ASSERT_EQ(11, ser.GetSize());
    ser << holo::serialization::align;
    ASSERT_EQ(12, ser.GetSize());
}

TEST(Serializer, serialize_custom_object)
{
    uint8_t    buffer[1024] = {0};
    Serializer ser(buffer, 1024);
    TestPoint  pt;
    pt.x = 0x12345678;
    pt.y = 0x87654321;

    ser << pt << holo::serialization::align;

    ASSERT_EQ(0x12, buffer[0]);
    ASSERT_EQ(0x34, buffer[1]);
    ASSERT_EQ(0x56, buffer[2]);
    ASSERT_EQ(0x78, buffer[3]);
    ASSERT_EQ(0x87, buffer[4]);
    ASSERT_EQ(0x65, buffer[5]);
    ASSERT_EQ(0x43, buffer[6]);
    ASSERT_EQ(0x21, buffer[7]);

    ASSERT_EQ(8, ser.GetSize());
}

TEST(Serializer, serialize_prealign_custom_object)
{
    uint8_t    buffer[1024] = {0};
    Serializer ser(buffer, 1024);
    uint8_t    v0 = 0x01U, v1 = 0x02U;
    TestPoint  pt;
    pt.x = 0x12345678;
    pt.y = 0x87654321;

    ser << v0 << v1;
    ser << pt.x << pt.y << holo::serialization::align;
//    ser << pt << holo::serialization::align;

    ASSERT_EQ(0x01, buffer[0]);
    ASSERT_EQ(0x02, buffer[1]);
    ASSERT_EQ(0x00, buffer[2]);
    ASSERT_EQ(0x00, buffer[3]);
    ASSERT_EQ(0x12, buffer[4]);
    ASSERT_EQ(0x34, buffer[5]);
    ASSERT_EQ(0x56, buffer[6]);
    ASSERT_EQ(0x78, buffer[7]);
    ASSERT_EQ(0x87, buffer[8]);
    ASSERT_EQ(0x65, buffer[9]);
    ASSERT_EQ(0x43, buffer[10]);
    ASSERT_EQ(0x21, buffer[11]);

    ASSERT_EQ(12, ser.GetSize());
}

TEST(Serializer, serialize_test_hybrid_object)
{
    uint8_t    buffer[1024] = {0};
    Serializer ser(buffer, 1024);
    TestObject obj;
    obj.a = 0x01U;
    obj.b = 0x0201U;
    obj.c = 0x04030201U;
    obj.d = 0x0807060504030201U;
    obj.e = 1.0f;
    obj.f = 1.0;
    obj.g = 0x0304U;
    obj.h = 0x0807060504030201U;
    obj.i = 0x01U;
    obj.j = 1.0f;
    obj.k = 0x02;
    obj.l = std::string("hello holomatic");

    ser << obj << holo::serialization::align;

    uint8_t expected_buf[] = {0x01, 0x00, 0x02, 0x01, 0x04, 0x03, 0x02, 0x01, 
                              0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 
                              0x3f, 0x80, 0x00, 0x00, 0x3f, 0xf0, 0x00, 0x00, 
                              0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x00, 0x00, 
                              0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 
                              0x01, 0x00, 0x00, 0x00, 0x3f, 0x80, 0x00, 0x00, 
                              0x02, 'h',  'e',  'l',  'l',  'o',  ' ',  'h',
                              'o',  'l',  'o',  'm',  'a',  't',  'i',  'c',  0x00, 0x00, 0x00, 0x00};

    for (uint32_t i = 0; i < sizeof(expected_buf); i++)
    {
        ASSERT_EQ(expected_buf[i], buffer[i]);
    }

    ASSERT_EQ(68, ser.GetSize());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
