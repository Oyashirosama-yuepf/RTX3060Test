/*!
 * \brief unit test of serialization
 * \author zhangjiannan@holomatic.com
 * \date 2019-11-2
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <unity.h>

#include <holo_c/utils/serialization.h>
#include <holo_c/port/endian.h>

static void test_serialization_4byte_aligned_size(void)
{
    //Zero
    TEST_ASSERT_EQUAL_UINT32(0U, serialization_4byte_aligned_size(0));

    //1
    TEST_ASSERT_EQUAL_UINT32(4U, serialization_4byte_aligned_size(1));

    //4
    TEST_ASSERT_EQUAL_UINT32(4U, serialization_4byte_aligned_size(4));

    //5
    TEST_ASSERT_EQUAL_UINT32(8U, serialization_4byte_aligned_size(5));

    //8
    TEST_ASSERT_EQUAL_UINT32(8U, serialization_4byte_aligned_size(8));
}

static void test_serialization_8byte_aligned_size(void)
{
    //Zero
    TEST_ASSERT_EQUAL_UINT32(0U, serialization_8byte_aligned_size(0));

    //1
    TEST_ASSERT_EQUAL_UINT32(8U, serialization_8byte_aligned_size(1));

    //4
    TEST_ASSERT_EQUAL_UINT32(8U, serialization_8byte_aligned_size(4));
    
    //5
    TEST_ASSERT_EQUAL_UINT32(8U, serialization_8byte_aligned_size(5));

    //8
    TEST_ASSERT_EQUAL_UINT32(8U, serialization_8byte_aligned_size(8));
}

static void test_serialize_int8(void)
{
    uint8_t buffer[8];
    int8_t value = 0;
    {
        value = 0;
        uint8_t expected_buffer[8] = {0x00};
        TEST_ASSERT_EQUAL_INT32(1, serialize_int8(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 1);
    }
    {
        value = 1;
        uint8_t expected_buffer[8] = {0x01};
        TEST_ASSERT_EQUAL_INT32(1, serialize_int8(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 1);
    }
    {
        value = -1;
        uint8_t expected_buffer[8] = {0xff};
        TEST_ASSERT_EQUAL_INT32(1, serialize_int8(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 1);
    }
    
    TEST_ASSERT_EQUAL_INT32(RC_SERIALIZATION_BUFFER_OVERFLOW, serialize_int8(&value, buffer, 0));
}

static void test_serialize_uint8(void)
{
    uint8_t buffer[8];
    uint8_t value = 0;
    {
        value = 0;
        uint8_t expected_buffer[8] = {0x00};
        TEST_ASSERT_EQUAL_INT32(1, serialize_uint8(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 1);
    }
    {
        value = 1;
        uint8_t expected_buffer[8] = {0x01};
        TEST_ASSERT_EQUAL_INT32(1, serialize_uint8(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 1);
    }
    {
        value = 255;
        uint8_t expected_buffer[8] = {0xff};
        TEST_ASSERT_EQUAL_INT32(1, serialize_uint8(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 1);
    }
    
    TEST_ASSERT_EQUAL_INT32(RC_SERIALIZATION_BUFFER_OVERFLOW, serialize_uint8(&value, buffer, 0));
}

static void test_serialize_int16(void)
{
    uint8_t buffer[8];
    int16_t value = 0;
    {
        value = 0;
        uint8_t expected_buffer[8] = {0x00, 0x00};
        TEST_ASSERT_EQUAL_INT32(2, serialize_int16(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 2);
    }
    {
        value = 1;
        uint8_t expected_buffer[8] = {0x00, 0x01};
        TEST_ASSERT_EQUAL_INT32(2, serialize_int16(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 2);
    }
    {
        value = 0x1234;
        uint8_t expected_buffer[8] = {0x12, 0x34};
        TEST_ASSERT_EQUAL_INT32(2, serialize_int16(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 2);
    }
    
    TEST_ASSERT_EQUAL_INT32(RC_SERIALIZATION_BUFFER_OVERFLOW, serialize_int16(&value, buffer, 1));
}

static void test_serialize_uint16(void)
{
    uint8_t buffer[8];
    uint16_t value = 0;
    {
        value = 0;
        uint8_t expected_buffer[8] = {0x00, 0x00};
        TEST_ASSERT_EQUAL_INT32(2, serialize_uint16(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 2);
    }
    {
        value = 1;
        uint8_t expected_buffer[8] = {0x00, 0x01};
        TEST_ASSERT_EQUAL_INT32(2, serialize_uint16(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 2);
    }
    {
        value = 0x1234;
        uint8_t expected_buffer[8] = {0x12, 0x34};
        TEST_ASSERT_EQUAL_INT32(2, serialize_uint16(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 2);
    }
    
    TEST_ASSERT_EQUAL_INT32(RC_SERIALIZATION_BUFFER_OVERFLOW, serialize_uint16(&value, buffer, 1));
}

static void test_serialize_int32(void)
{
    uint8_t buffer[8];
    int32_t value = 0;
    {
        value = 0;
        uint8_t expected_buffer[8] = {0x00, 0x00, 0x00, 0x00};
        TEST_ASSERT_EQUAL_INT32(4, serialize_int32(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 4);
    }
    {
        value = 1;
        uint8_t expected_buffer[8] = {0x00, 0x00, 0x00, 0x01};
        TEST_ASSERT_EQUAL_INT32(4, serialize_int32(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 4);
    }
    {
        value = 0x12345678;
        uint8_t expected_buffer[8] = {0x12, 0x34, 0x56, 0x78};
        TEST_ASSERT_EQUAL_INT32(4, serialize_int32(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 4);
    }
    
    TEST_ASSERT_EQUAL_INT32(RC_SERIALIZATION_BUFFER_OVERFLOW, serialize_int32(&value, buffer, 3));
}

static void test_serialize_uint32(void)
{
    uint8_t buffer[8];
    uint32_t value = 0;
    {
        value = 0;
        uint8_t expected_buffer[8] = {0x00, 0x00, 0x00, 0x00};
        TEST_ASSERT_EQUAL_INT32(4, serialize_uint32(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 4);
    }
    {
        value = 1;
        uint8_t expected_buffer[8] = {0x00, 0x00, 0x00, 0x01};
        TEST_ASSERT_EQUAL_INT32(4, serialize_uint32(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 4);
    }
    {
        value = 0x12345678;
        uint8_t expected_buffer[8] = {0x12, 0x34, 0x56, 0x78};
        TEST_ASSERT_EQUAL_INT32(4, serialize_uint32(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 4);
    }
    
    TEST_ASSERT_EQUAL_INT32(RC_SERIALIZATION_BUFFER_OVERFLOW, serialize_uint32(&value, buffer, 3));
}

static void test_serialize_int64_4byte_aligned(void)
{
    uint8_t buffer[8];
    int64_t value = 0;
    {
        value = 0;
        uint8_t expected_buffer[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        TEST_ASSERT_EQUAL_INT32(8, serialize_int64_4byte_aligned(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 8);
    }
    {
        value = 1;
        uint8_t expected_buffer[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
        TEST_ASSERT_EQUAL_INT32(8, serialize_int64_4byte_aligned(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 8);
    }
    {
        value = 0x123456789abcdef0;
        uint8_t expected_buffer[8] = {0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0};
        TEST_ASSERT_EQUAL_INT32(8, serialize_int64_4byte_aligned(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 8);
    }
    
    TEST_ASSERT_EQUAL_INT32(RC_SERIALIZATION_BUFFER_OVERFLOW, serialize_int64_4byte_aligned(&value, buffer, 7));
}

static void test_serialize_uint64_4byte_aligned(void)
{
    uint8_t buffer[8];
    uint64_t value = 0;
    {
        value = 0;
        uint8_t expected_buffer[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        TEST_ASSERT_EQUAL_INT32(8, serialize_uint64_4byte_aligned(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 8);
    }
    {
        value = 1;
        uint8_t expected_buffer[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
        TEST_ASSERT_EQUAL_INT32(8, serialize_uint64_4byte_aligned(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 8);
    }
    {
        value = 0x123456789abcdef0;
        uint8_t expected_buffer[8] = {0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0};
        TEST_ASSERT_EQUAL_INT32(8, serialize_uint64_4byte_aligned(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 8);
    }
    
    TEST_ASSERT_EQUAL_INT32(RC_SERIALIZATION_BUFFER_OVERFLOW, serialize_uint64(&value, buffer, 7));
}

static void test_serialize_int64_8byte_aligned(void)
{
    uint8_t buffer[8];
    int64_t value = 0;
    {
        value = 0;
        uint8_t expected_buffer[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        TEST_ASSERT_EQUAL_INT32(8, serialize_int64_8byte_aligned(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 8);
    }
    {
        value = 1;
        uint8_t expected_buffer[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
        TEST_ASSERT_EQUAL_INT32(8, serialize_int64_8byte_aligned(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 8);
    }
    {
        value = 0x123456789abcdef0;
        uint8_t expected_buffer[8] = {0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0};
        TEST_ASSERT_EQUAL_INT32(8, serialize_int64_8byte_aligned(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 8);
    }
    
    TEST_ASSERT_EQUAL_INT32(RC_SERIALIZATION_BUFFER_OVERFLOW, serialize_int64_8byte_aligned(&value, buffer, 7));
}


static void test_serialize_uint64_8byte_aligned(void)
{
    uint8_t buffer[8];
    uint64_t value = 0;
    {
        value = 0;
        uint8_t expected_buffer[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        TEST_ASSERT_EQUAL_INT32(8, serialize_uint64_8byte_aligned(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 8);
    }
    {
        value = 1;
        uint8_t expected_buffer[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
        TEST_ASSERT_EQUAL_INT32(8, serialize_uint64_8byte_aligned(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 8);
    }
    {
        value = 0x123456789abcdef0;
        uint8_t expected_buffer[8] = {0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0};
        TEST_ASSERT_EQUAL_INT32(8, serialize_uint64_8byte_aligned(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 8);
    }
    
    TEST_ASSERT_EQUAL_INT32(RC_SERIALIZATION_BUFFER_OVERFLOW, serialize_uint64_8byte_aligned(&value, buffer, 7));
}

static void test_serialize_float32(void)
{
    uint8_t buffer[8];
    float32_t value = 0.0f;
    {
        value = 0.0f;
        uint8_t expected_buffer[8] = {0x00, 0x00, 0x00, 0x00};
        TEST_ASSERT_EQUAL_INT32(4, serialize_float32(&value, buffer, 4));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 4);
    }
    {
        value = 1.0f;
        uint8_t expected_buffer[8] = {0x3f, 0x80, 0x00, 0x00};
        TEST_ASSERT_EQUAL_INT32(4, serialize_float32(&value, buffer, 4));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 4);
    }

    TEST_ASSERT_EQUAL_INT32(RC_SERIALIZATION_BUFFER_OVERFLOW, serialize_float32(&value, buffer, 3));
}

static void test_serialize_float64_4byte_aligned(void)
{
    uint8_t buffer[8];
    float64_t value = 0.0;
    {
        value = 0.0;
        uint8_t expected_buffer[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        TEST_ASSERT_EQUAL_INT32(8, serialize_float64_4byte_aligned(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 8);
    }
    {
        value = 1.0;
        uint8_t expected_buffer[8] = {0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        TEST_ASSERT_EQUAL_INT32(8, serialize_float64_4byte_aligned(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 8);
    }

    TEST_ASSERT_EQUAL_INT32(RC_SERIALIZATION_BUFFER_OVERFLOW, serialize_float64_4byte_aligned(&value, buffer, 7));
}

static void test_serialize_float64_8byte_aligned(void)
{
    uint8_t buffer[8];
    float64_t value = 0.0;
    {
        value = 0.0;
        uint8_t expected_buffer[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        TEST_ASSERT_EQUAL_INT32(8, serialize_float64_8byte_aligned(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 8);
    }
    {
        value = 1.0;
        uint8_t expected_buffer[8] = {0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        TEST_ASSERT_EQUAL_INT32(8, serialize_float64_8byte_aligned(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 8);
    }

    TEST_ASSERT_EQUAL_INT32(RC_SERIALIZATION_BUFFER_OVERFLOW, serialize_float64_8byte_aligned(&value, buffer, 7));
}

static void test_serialize_padding_4byte_aligned(void)
{
    uint8_t buffer[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    uint8_t value = 1;

    uint8_t expected_buffer[8] = {0x01, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff};

    TEST_ASSERT_EQUAL_INT32(1, serialize_uint8(&value, buffer, 8));
    TEST_ASSERT_EQUAL_INT32(3, serialize_padding_4byte_aligned(1, buffer + 1, 7));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 8);

    TEST_ASSERT_EQUAL_INT32(RC_SERIALIZATION_BUFFER_OVERFLOW, serialize_padding_4byte_aligned(1, buffer + 1, 2));
}

static void test_serialize_padding_8byte_aligned(void)
{
    uint8_t buffer[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    uint8_t value = 1;

    uint8_t expected_buffer[8] = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    TEST_ASSERT_EQUAL_INT32(1, serialize_uint8(&value, buffer, 8));
    TEST_ASSERT_EQUAL_INT32(7, serialize_padding_8byte_aligned(1, buffer + 1, 7));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, buffer, 8);

    TEST_ASSERT_EQUAL_INT32(RC_SERIALIZATION_BUFFER_OVERFLOW, serialize_padding_8byte_aligned(1, buffer + 1, 6));
}

static void test_deserialize_int8(void)
{
    int8_t value = 0;
    {
        uint8_t buffer[8] = {0x00};
        TEST_ASSERT_EQUAL_INT32(1, deserialize_int8(&value, buffer, 8));
        TEST_ASSERT_EQUAL_INT8(0, value);
    }
    {
        uint8_t buffer[8] = {0x01};
        TEST_ASSERT_EQUAL_INT32(1, deserialize_int8(&value, buffer, 8));
        TEST_ASSERT_EQUAL_INT8(1, value);
    }
    {
        uint8_t buffer[8] = {0xff};
        TEST_ASSERT_EQUAL_INT32(1, deserialize_int8(&value, buffer, 8));
        TEST_ASSERT_EQUAL_INT8(-1, value);
    }
    
    uint8_t buffer[8];
    TEST_ASSERT_EQUAL_INT32(RC_DESERIALIZATION_BUFFER_UNDERFLOW, deserialize_int8(&value, buffer, 0));
}

static void test_deserialize_uint8(void)
{
    uint8_t value = 0;
    {
        uint8_t buffer[8] = {0x00};
        TEST_ASSERT_EQUAL_INT32(1, deserialize_uint8(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8(0, value);
    }
    {
        uint8_t buffer[8] = {0x01};
        TEST_ASSERT_EQUAL_INT32(1, deserialize_uint8(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8(1, value);
    }
    {
        uint8_t buffer[8] = {0xff};
        TEST_ASSERT_EQUAL_INT32(1, deserialize_uint8(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8(255, value);
    }
    
    uint8_t buffer[8];
    TEST_ASSERT_EQUAL_INT32(RC_DESERIALIZATION_BUFFER_UNDERFLOW, deserialize_uint8(&value, buffer, 0));
}

static void test_deserialize_int16(void)
{
    int16_t value = 0;
    {
        uint8_t buffer[8] = {0x00, 0x00};
        TEST_ASSERT_EQUAL_INT32(2, deserialize_int16(&value, buffer, 8));
        TEST_ASSERT_EQUAL_INT16(0, value);
    }
    {
        uint8_t buffer[8] = {0x00, 0x01};
        TEST_ASSERT_EQUAL_INT32(2, deserialize_int16(&value, buffer, 8));
        TEST_ASSERT_EQUAL_INT16(1, value);
    }
    {
        uint8_t buffer[8] = {0x12, 0x34};
        TEST_ASSERT_EQUAL_INT32(2, deserialize_int16(&value, buffer, 8));
        TEST_ASSERT_EQUAL_INT16(0x1234, value);
    }
    
    uint8_t buffer[8];
    TEST_ASSERT_EQUAL_INT32(RC_DESERIALIZATION_BUFFER_UNDERFLOW, deserialize_int16(&value, buffer, 1));
}

static void test_deserialize_uint16(void)
{
    uint16_t value = 0;
    {
        uint8_t buffer[8] = {0x00, 0x00};
        TEST_ASSERT_EQUAL_INT32(2, deserialize_uint16(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT16(0, value);
    }
    {
        uint8_t buffer[8] = {0x00, 0x01};
        TEST_ASSERT_EQUAL_INT32(2, deserialize_uint16(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT16(1, value);
    }
    {
        uint8_t buffer[8] = {0x12, 0x34};
        TEST_ASSERT_EQUAL_INT32(2, deserialize_uint16(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT16(0x1234, value);
    }
    
    uint8_t buffer[8];
    TEST_ASSERT_EQUAL_INT32(RC_DESERIALIZATION_BUFFER_UNDERFLOW, deserialize_uint16(&value, buffer, 1));
}

static void test_deserialize_int32(void)
{
    int32_t value = 0;
    {
        uint8_t buffer[8] = {0x00, 0x00, 0x00, 0x00};
        TEST_ASSERT_EQUAL_INT32(4, deserialize_int32(&value, buffer, 8));
        TEST_ASSERT_EQUAL_INT32(0, value);
    }
    {
        uint8_t buffer[8] = {0x00, 0x00, 0x00, 0x01};
        TEST_ASSERT_EQUAL_INT32(4, deserialize_int32(&value, buffer, 8));
        TEST_ASSERT_EQUAL_INT32(1, value);
    }
    {
        uint8_t buffer[8] = {0x12, 0x34, 0x56, 0x78};
        TEST_ASSERT_EQUAL_INT32(4, deserialize_int32(&value, buffer, 8));
        TEST_ASSERT_EQUAL_INT32(0x12345678, value);
    }
    
    uint8_t buffer[8];
    TEST_ASSERT_EQUAL_INT32(RC_DESERIALIZATION_BUFFER_UNDERFLOW, deserialize_int32(&value, buffer, 3));
}

static void test_deserialize_uint32(void)
{
    uint32_t value = 0;
    {
        uint8_t buffer[8] = {0x00, 0x00, 0x00, 0x00};
        TEST_ASSERT_EQUAL_INT32(4, deserialize_uint32(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT32(0, value);
    }
    {
        uint8_t buffer[8] = {0x00, 0x00, 0x00, 0x01};
        TEST_ASSERT_EQUAL_INT32(4, deserialize_uint32(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT32(1, value);
    }
    {
        uint8_t buffer[8] = {0x12, 0x34, 0x56, 0x78};
        TEST_ASSERT_EQUAL_INT32(4, deserialize_uint32(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT32(0x12345678, value);
    }
    
    uint8_t buffer[8];
    TEST_ASSERT_EQUAL_INT32(RC_DESERIALIZATION_BUFFER_UNDERFLOW, deserialize_uint32(&value, buffer, 3));
}

static void test_deserialize_int64_4byte_aligned(void)
{
    int64_t value = 0;
    {
        uint8_t buffer[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        TEST_ASSERT_EQUAL_INT32(8, deserialize_int64_4byte_aligned(&value, buffer, 8));
        TEST_ASSERT_EQUAL_INT64(0, value);
    }
    {
        uint8_t buffer[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
        TEST_ASSERT_EQUAL_INT32(8, deserialize_int64_4byte_aligned(&value, buffer, 8));
        TEST_ASSERT_EQUAL_INT64(1, value);
    }
    {
        uint8_t buffer[8] = {0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0};
        TEST_ASSERT_EQUAL_INT32(8, deserialize_int64_4byte_aligned(&value, buffer, 8));
        TEST_ASSERT_EQUAL_INT64(0x123456789abcdef0, value);
    }
    
    uint8_t buffer[8];
    TEST_ASSERT_EQUAL_INT32(RC_DESERIALIZATION_BUFFER_UNDERFLOW, deserialize_int64_4byte_aligned(&value, buffer, 7));
}

static void test_deserialize_uint64_4byte_aligned(void)
{
    uint64_t value = 0;
    {
        uint8_t buffer[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        TEST_ASSERT_EQUAL_INT32(8, deserialize_uint64_4byte_aligned(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT64(0, value);
    }
    {
        uint8_t buffer[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
        TEST_ASSERT_EQUAL_INT32(8, deserialize_uint64_4byte_aligned(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT64(1, value);
    }
    {
        uint8_t buffer[8] = {0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0};
        TEST_ASSERT_EQUAL_INT32(8, deserialize_uint64_4byte_aligned(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT64(0x123456789abcdef0, value);
    }
    
    uint8_t buffer[8];
    TEST_ASSERT_EQUAL_INT32(RC_DESERIALIZATION_BUFFER_UNDERFLOW, deserialize_uint64(&value, buffer, 7));
}

static void test_deserialize_int64_8byte_aligned(void)
{
    int64_t value = 0;
    {
        uint8_t buffer[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        TEST_ASSERT_EQUAL_INT32(8, deserialize_int64_8byte_aligned(&value, buffer, 8));
        TEST_ASSERT_EQUAL_INT64(0, value);
    }
    {
        uint8_t buffer[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
        TEST_ASSERT_EQUAL_INT32(8, deserialize_int64_8byte_aligned(&value, buffer, 8));
        TEST_ASSERT_EQUAL_INT64(1, value);
    }
    {
        uint8_t buffer[8] = {0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0};
        TEST_ASSERT_EQUAL_INT32(8, deserialize_int64_8byte_aligned(&value, buffer, 8));
        TEST_ASSERT_EQUAL_INT64(0x123456789abcdef0, value);
    }
    
    uint8_t buffer[8];
    TEST_ASSERT_EQUAL_INT32(RC_DESERIALIZATION_BUFFER_UNDERFLOW, deserialize_int64_8byte_aligned(&value, buffer, 7));
}


static void test_deserialize_uint64_8byte_aligned(void)
{
    uint64_t value = 0;
    {
        uint8_t buffer[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        TEST_ASSERT_EQUAL_INT32(8, deserialize_uint64_8byte_aligned(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT64(0, value);
    }
    {
        uint8_t buffer[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
        TEST_ASSERT_EQUAL_INT32(8, deserialize_uint64_8byte_aligned(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT64(1, value);
    }
    {
        uint8_t buffer[8] = {0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0};
        TEST_ASSERT_EQUAL_INT32(8, deserialize_uint64_8byte_aligned(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT64(0x123456789abcdef0, value);
    }
    
    uint8_t buffer[8];
    TEST_ASSERT_EQUAL_INT32(RC_DESERIALIZATION_BUFFER_UNDERFLOW, deserialize_uint64_8byte_aligned(&value, buffer, 7));
}

static void test_deserialize_float32(void)
{
    float32_t value = 0.0f;
    {
        uint8_t buffer[8] = {0x00, 0x00, 0x00, 0x00};
        TEST_ASSERT_EQUAL_INT32(4, deserialize_float32(&value, buffer, 4));
        TEST_ASSERT_EQUAL_FLOAT(0.0f, value);
    }
    {
        uint8_t buffer[8] = {0x3f, 0x80, 0x00, 0x00};
        TEST_ASSERT_EQUAL_INT32(4, deserialize_float32(&value, buffer, 4));
        TEST_ASSERT_EQUAL_FLOAT(1.0f, value);
    }

    uint8_t buffer[8];
    TEST_ASSERT_EQUAL_INT32(RC_DESERIALIZATION_BUFFER_UNDERFLOW, deserialize_float32(&value, buffer, 3));
}

static void test_deserialize_float64_4byte_aligned(void)
{
    float64_t value = 0.0;
    {
        uint8_t buffer[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        TEST_ASSERT_EQUAL_INT32(8, deserialize_float64_4byte_aligned(&value, buffer, 8));
        TEST_ASSERT_EQUAL_DOUBLE(0.0, value);
    }
    {
        uint8_t buffer[8] = {0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        TEST_ASSERT_EQUAL_INT32(8, deserialize_float64_4byte_aligned(&value, buffer, 8));
        TEST_ASSERT_EQUAL_DOUBLE(1.0, value);
    }

    uint8_t buffer[8];
    TEST_ASSERT_EQUAL_INT32(RC_DESERIALIZATION_BUFFER_UNDERFLOW, deserialize_float64_4byte_aligned(&value, buffer, 7));
}

static void test_deserialize_float64_8byte_aligned(void)
{
    float64_t value = 0.0;
    {
        uint8_t buffer[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        TEST_ASSERT_EQUAL_INT32(8, deserialize_float64_8byte_aligned(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(buffer, buffer, 8);
        TEST_ASSERT_EQUAL_DOUBLE(0.0, value);
    }
    {
        uint8_t buffer[8] = {0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        TEST_ASSERT_EQUAL_INT32(8, deserialize_float64_8byte_aligned(&value, buffer, 8));
        TEST_ASSERT_EQUAL_UINT8_ARRAY(buffer, buffer, 8);
        TEST_ASSERT_EQUAL_DOUBLE(1.0, value);
    }

    uint8_t buffer[8];
    TEST_ASSERT_EQUAL_INT32(RC_DESERIALIZATION_BUFFER_UNDERFLOW, deserialize_float64_8byte_aligned(&value, buffer, 7));
}

static void test_deserialize_padding_4byte_aligned(void)
{
    uint8_t buffer[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    uint8_t value;

    TEST_ASSERT_EQUAL_INT32(1, deserialize_uint8(&value, buffer, 8));
    TEST_ASSERT_EQUAL_INT32(3, deserialize_padding_4byte_aligned(1, buffer + 1, 7));

    TEST_ASSERT_EQUAL_INT32(RC_DESERIALIZATION_BUFFER_UNDERFLOW, deserialize_padding_4byte_aligned(1, buffer + 1, 2));
}

static void test_deserialize_padding_8byte_aligned(void)
{
    uint8_t buffer[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    uint8_t value;

    TEST_ASSERT_EQUAL_INT32(1, deserialize_uint8(&value, buffer, 8));
    TEST_ASSERT_EQUAL_INT32(7, deserialize_padding_8byte_aligned(1, buffer + 1, 7));

    TEST_ASSERT_EQUAL_INT32(RC_DESERIALIZATION_BUFFER_UNDERFLOW, deserialize_padding_8byte_aligned(1, buffer + 1, 6));
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_serialization_4byte_aligned_size);
    RUN_TEST(test_serialization_8byte_aligned_size);
    RUN_TEST(test_serialize_int8);
    RUN_TEST(test_serialize_uint8);
    RUN_TEST(test_serialize_int16);
    RUN_TEST(test_serialize_uint16);
    RUN_TEST(test_serialize_int32);
    RUN_TEST(test_serialize_uint32);
    RUN_TEST(test_serialize_int64_4byte_aligned);
    RUN_TEST(test_serialize_uint64_4byte_aligned);
    RUN_TEST(test_serialize_int64_8byte_aligned);
    RUN_TEST(test_serialize_uint64_8byte_aligned);
    RUN_TEST(test_serialize_float32);
    RUN_TEST(test_serialize_float64_4byte_aligned);
    RUN_TEST(test_serialize_float64_8byte_aligned);
    RUN_TEST(test_serialize_padding_4byte_aligned);
    RUN_TEST(test_serialize_padding_8byte_aligned);

    RUN_TEST(test_deserialize_int8);
    RUN_TEST(test_deserialize_uint8);
    RUN_TEST(test_deserialize_int16);
    RUN_TEST(test_deserialize_uint16);
    RUN_TEST(test_deserialize_int32);
    RUN_TEST(test_deserialize_uint32);
    RUN_TEST(test_deserialize_int64_4byte_aligned);
    RUN_TEST(test_deserialize_uint64_4byte_aligned);
    RUN_TEST(test_deserialize_int64_8byte_aligned);
    RUN_TEST(test_deserialize_uint64_8byte_aligned);
    RUN_TEST(test_deserialize_float32);
    RUN_TEST(test_deserialize_float64_4byte_aligned);
    RUN_TEST(test_deserialize_float64_8byte_aligned);
    RUN_TEST(test_deserialize_padding_4byte_aligned);
    RUN_TEST(test_deserialize_padding_8byte_aligned);
    return UNITY_END();
}
