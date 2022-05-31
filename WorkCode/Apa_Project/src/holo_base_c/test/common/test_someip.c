/*!
 * @brief Unit test for someip.
 * @author liuya@holomatic.com
 * @date Dec 07, 2019
 * @attention Copyright@Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <stdio.h>
#include <string.h>
#include <unity.h>

#include <holo_c/common/someip.h>
#include <holo_c/core/retcode.h>

struct SomeipPacket packet;
struct SomeipPacket deserialized_packet;

uint8_t data_buf[8] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
uint8_t read_buf[8];
uint8_t serialize_buf[1024];

void test_someip_packet_init_default(void)
{
    TEST_ASSERT_EQUAL_HEX8(RC_SUCCESS, someip_packet_init_default(&packet));
}

void test_someip_packet_set_and_get_service_id(void)
{
    someip_packet_set_service_id(&packet, 0xAA);
    TEST_ASSERT_EQUAL_HEX16(0xAA, someip_packet_get_service_id(&packet));
}

void test_someip_packet_set_and_get_method_id(void)
{
    someip_packet_set_method_id(&packet, 0xBB);
    TEST_ASSERT_EQUAL_HEX16(0xBB, someip_packet_get_method_id(&packet));
}

void test_someip_packet_set_and_get_length(void)
{
    someip_packet_set_message_length(&packet, 16);
    TEST_ASSERT_EQUAL_UINT32(16, someip_packet_get_msg_length(&packet));
}

void test_someip_packet_set_and_get_client_id(void)
{
    someip_packet_set_client_id(&packet, 0xCC);
    TEST_ASSERT_EQUAL_HEX16(0xCC, someip_packet_get_client_id(&packet));
}

void test_someip_packet_set_and_get_session_id(void)
{
    someip_packet_set_session_id(&packet, 0xDD);
    TEST_ASSERT_EQUAL_HEX16(0xDD, someip_packet_get_session_id(&packet));
}

void test_someip_packet_set_and_get_protocol_version(void)
{
    someip_packet_set_protocol_version(&packet, 0x20);
    TEST_ASSERT_EQUAL_HEX8(0x20, someip_packet_get_protocol_version(&packet));
}

void test_someip_packet_set_and_get_interface_version(void)
{
    someip_packet_set_interface_version(&packet, 0x30);
    TEST_ASSERT_EQUAL_HEX8(0x30, someip_packet_get_interface_version(&packet));
}

void test_someip_packet_set_and_get_message_type(void)
{
    someip_packet_set_message_type(&packet, 0x40);
    TEST_ASSERT_EQUAL_HEX8(0x40, someip_packet_get_message_type(&packet));
}

void test_someip_packet_set_and_get_return_code(void)
{
    someip_packet_set_return_code(&packet, 0x50);
    TEST_ASSERT_EQUAL_HEX8(0x50, someip_packet_get_return_code(&packet));
}

void test_someip_packet_set_and_get_payload(void)
{
    uint8_t i;

    TEST_ASSERT_EQUAL_INT32(RC_FAIL, someip_packet_set_payload(&packet, data_buf, 10240));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, someip_packet_set_payload(&packet, data_buf, 8));

    TEST_ASSERT_EQUAL_INT32(RC_FAIL, someip_packet_get_payload(&packet, read_buf, 2));
    TEST_ASSERT_EQUAL_INT32(8, someip_packet_get_payload(&packet, read_buf, 8));

    for (i = 0; i < 8; i++)
    {
        TEST_ASSERT_EQUAL_UINT8(data_buf[i], packet.payload[i]);
    }
}

void test_someip_packet_serialize_and_deserialize(void)
{
    uint8_t       i;
    const uint8_t error_buf_size = 20;

    TEST_ASSERT_EQUAL_UINT32(24, someip_packet_get_serialized_size_8byte_aligned(&packet));
    TEST_ASSERT_EQUAL_UINT32(24, someip_packet_get_serialized_size(&packet));

    memset(serialize_buf, 0, 1024);
    TEST_ASSERT_EQUAL_HEX64(RC_SERIALIZATION_BUFFER_OVERFLOW,
                            someip_packet_serialize_8byte_aligned(&packet, serialize_buf, error_buf_size));
    TEST_ASSERT_EQUAL_UINT32(24, someip_packet_serialize_8byte_aligned(&packet, serialize_buf, 1024));

    TEST_ASSERT_EQUAL_HEX64(
        RC_DESERIALIZATION_BUFFER_UNDERFLOW,
        someip_packet_deserialize_8byte_aligned(&deserialized_packet, serialize_buf, error_buf_size));
    TEST_ASSERT_EQUAL_UINT32(24, someip_packet_deserialize_8byte_aligned(&deserialized_packet, serialize_buf, 1024));

    TEST_ASSERT_EQUAL_HEX16(someip_packet_get_service_id(&packet), someip_packet_get_service_id(&deserialized_packet));
    TEST_ASSERT_EQUAL_HEX16(someip_packet_get_method_id(&packet), someip_packet_get_method_id(&deserialized_packet));
    TEST_ASSERT_EQUAL_UINT32(someip_packet_get_msg_length(&packet), someip_packet_get_msg_length(&deserialized_packet));
    TEST_ASSERT_EQUAL_HEX16(someip_packet_get_client_id(&packet), someip_packet_get_client_id(&deserialized_packet));
    TEST_ASSERT_EQUAL_HEX16(someip_packet_get_session_id(&packet), someip_packet_get_session_id(&deserialized_packet));
    TEST_ASSERT_EQUAL_HEX16(someip_packet_get_protocol_version(&packet),
                            someip_packet_get_protocol_version(&deserialized_packet));
    TEST_ASSERT_EQUAL_HEX16(someip_packet_get_interface_version(&packet),
                            someip_packet_get_interface_version(&deserialized_packet));
    TEST_ASSERT_EQUAL_HEX16(someip_packet_get_message_type(&packet),
                            someip_packet_get_message_type(&deserialized_packet));
    TEST_ASSERT_EQUAL_HEX16(someip_packet_get_return_code(&packet),
                            someip_packet_get_return_code(&deserialized_packet));
    for (i = 0; i < 8; i++)
    {
        TEST_ASSERT_EQUAL_UINT8(packet.payload[i], deserialized_packet.payload[i]);
    }

    memset(serialize_buf, 0, 1024);
    TEST_ASSERT_EQUAL_HEX64(RC_SERIALIZATION_BUFFER_OVERFLOW,
                            someip_packet_serialize(&packet, serialize_buf, error_buf_size));
    TEST_ASSERT_EQUAL_UINT32(24, someip_packet_serialize(&packet, serialize_buf, 1024));

    TEST_ASSERT_EQUAL_HEX64(RC_DESERIALIZATION_BUFFER_UNDERFLOW,
                            someip_packet_deserialize(&deserialized_packet, serialize_buf, error_buf_size));
    TEST_ASSERT_EQUAL_UINT32(24, someip_packet_deserialize(&deserialized_packet, serialize_buf, 1024));

    TEST_ASSERT_EQUAL_HEX16(someip_packet_get_service_id(&packet), someip_packet_get_service_id(&deserialized_packet));
    TEST_ASSERT_EQUAL_HEX16(someip_packet_get_method_id(&packet), someip_packet_get_method_id(&deserialized_packet));
    TEST_ASSERT_EQUAL_UINT32(someip_packet_get_msg_length(&packet), someip_packet_get_msg_length(&deserialized_packet));
    TEST_ASSERT_EQUAL_HEX16(someip_packet_get_client_id(&packet), someip_packet_get_client_id(&deserialized_packet));
    TEST_ASSERT_EQUAL_HEX16(someip_packet_get_session_id(&packet), someip_packet_get_session_id(&deserialized_packet));
    TEST_ASSERT_EQUAL_HEX16(someip_packet_get_protocol_version(&packet),
                            someip_packet_get_protocol_version(&deserialized_packet));
    TEST_ASSERT_EQUAL_HEX16(someip_packet_get_interface_version(&packet),
                            someip_packet_get_interface_version(&deserialized_packet));
    TEST_ASSERT_EQUAL_HEX16(someip_packet_get_message_type(&packet),
                            someip_packet_get_message_type(&deserialized_packet));
    TEST_ASSERT_EQUAL_HEX16(someip_packet_get_return_code(&packet),
                            someip_packet_get_return_code(&deserialized_packet));
    for (i = 0; i < 8; i++)
    {
        TEST_ASSERT_EQUAL_UINT8(packet.payload[i], deserialized_packet.payload[i]);
    }
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_someip_packet_init_default);
    RUN_TEST(test_someip_packet_set_and_get_service_id);
    RUN_TEST(test_someip_packet_set_and_get_method_id);
    RUN_TEST(test_someip_packet_set_and_get_length);
    RUN_TEST(test_someip_packet_set_and_get_client_id);
    RUN_TEST(test_someip_packet_set_and_get_session_id);
    RUN_TEST(test_someip_packet_set_and_get_protocol_version);
    RUN_TEST(test_someip_packet_set_and_get_interface_version);
    RUN_TEST(test_someip_packet_set_and_get_message_type);
    RUN_TEST(test_someip_packet_set_and_get_return_code);
    RUN_TEST(test_someip_packet_set_and_get_payload);
    RUN_TEST(test_someip_packet_serialize_and_deserialize);

    return UNITY_END();
}
