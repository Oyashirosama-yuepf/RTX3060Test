/*!
 * @brief Unit test for bosch uss driver.
 * @author liuya@holomaitc.com
 * @date 2019-12-25
 * @attention Copyright@Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <string.h>
#include <time.h>
#include <unity.h>

#include <holo_c/sensors/uss/bosch_uss_driver.h>

struct CanMessage
{
    uint32_t id;
    uint8_t  len;
    uint8_t  data[8];
};

uint8_t                          buffer[40];
uint8_t                          error_buf[24];
struct CanMessage                fde_can_msg, rde_can_msg;
static struct BoschUssObjectList list;
static struct BoschUssObjectList deserialized_list;

static void test_bosch_uss_driver_process(void)
{
    time_t           utc_seconds;
    struct Timestamp sys_time;

    utc_seconds = time((time_t*)NULL);
    timestamp_init_from_sec(&sys_time, utc_seconds);

    fde_can_msg.id      = 0x276;
    fde_can_msg.len     = 8;
    fde_can_msg.data[0] = 0x00;
    fde_can_msg.data[1] = 0x40;
    fde_can_msg.data[2] = 0x20;
    fde_can_msg.data[3] = 0x0C;
    fde_can_msg.data[4] = 0x04;
    fde_can_msg.data[5] = 0x01;
    fde_can_msg.data[6] = 0x40;
    fde_can_msg.data[7] = 0x60;

    rde_can_msg.id      = 0x286;
    rde_can_msg.len     = 8;
    rde_can_msg.data[0] = 0x01;
    rde_can_msg.data[1] = 0xC0;
    rde_can_msg.data[2] = 0x80;
    rde_can_msg.data[3] = 0x24;
    rde_can_msg.data[4] = 0x0A;
    rde_can_msg.data[5] = 0x02;
    rde_can_msg.data[6] = 0xC0;
    rde_can_msg.data[7] = 0xC0;

    TEST_ASSERT_EQUAL(RC_FAIL,
                      bosch_uss_driver_process_data(&list, &sys_time, 0xFF, fde_can_msg.data, fde_can_msg.len));

    TEST_ASSERT_EQUAL(RC_BOSCH_USS_PARSE_ERROR, bosch_uss_driver_process_data(&list, &sys_time, rde_can_msg.id,
                                                                              rde_can_msg.data, rde_can_msg.len));

    TEST_ASSERT_EQUAL(RC_SUCCESS, bosch_uss_can_id_is_valid(fde_can_msg.id));
    TEST_ASSERT_EQUAL_INT64(
        RC_BOSCH_USS_PARSE_CONTINUE,
        bosch_uss_driver_process_data(&list, &sys_time, fde_can_msg.id, fde_can_msg.data, fde_can_msg.len));

    TEST_ASSERT_EQUAL(RC_SUCCESS, bosch_uss_can_id_is_valid(rde_can_msg.id));
    TEST_ASSERT_EQUAL_INT64(RC_BOSCH_USS_PARSE_OK, bosch_uss_driver_process_data(&list, &sys_time, rde_can_msg.id,
                                                                                 rde_can_msg.data, rde_can_msg.len));

    TEST_ASSERT_TRUE(timestamp_is_equal(&sys_time, bosch_uss_object_list_get_timestamp(&list)));
    TEST_ASSERT_EQUAL_HEX16(0x01, bosch_uss_object_list_get_object(&list, 0));
    TEST_ASSERT_EQUAL_HEX16(0x02, bosch_uss_object_list_get_object(&list, 1));
    TEST_ASSERT_EQUAL_HEX16(0x03, bosch_uss_object_list_get_object(&list, 2));
    TEST_ASSERT_EQUAL_HEX16(0x04, bosch_uss_object_list_get_object(&list, 3));
    TEST_ASSERT_EQUAL_HEX16(0x05, bosch_uss_object_list_get_object(&list, 4));
    TEST_ASSERT_EQUAL_HEX16(0x06, bosch_uss_object_list_get_object(&list, 5));
    TEST_ASSERT_EQUAL_HEX16(0x07, bosch_uss_object_list_get_object(&list, 6));
    TEST_ASSERT_EQUAL_HEX16(0x08, bosch_uss_object_list_get_object(&list, 7));
    TEST_ASSERT_EQUAL_HEX16(0x09, bosch_uss_object_list_get_object(&list, 8));
    TEST_ASSERT_EQUAL_HEX16(0x0A, bosch_uss_object_list_get_object(&list, 9));
    TEST_ASSERT_EQUAL_HEX16(0x0B, bosch_uss_object_list_get_object(&list, 10));
    TEST_ASSERT_EQUAL_HEX16(0x0C, bosch_uss_object_list_get_object(&list, 11));
}

static void test_bosch_uss_4byte_aligned_serialize_and_deserialize(void)
{
    uint8_t i;
    memset(buffer, 0, 40);

    TEST_ASSERT_EQUAL(32, bosch_uss_object_list_get_serialized_size_4byte_aligned(&list));

    TEST_ASSERT_EQUAL_HEX16(RC_SERIALIZATION_BUFFER_OVERFLOW,
                            bosch_uss_object_list_serialize_4byte_aligned(&list, error_buf, 24));
    TEST_ASSERT_EQUAL_HEX16(32, bosch_uss_object_list_serialize_4byte_aligned(&list, buffer, 40));

    TEST_ASSERT_EQUAL_HEX16(RC_DESERIALIZATION_BUFFER_UNDERFLOW,
                            bosch_uss_object_list_deserialize_4byte_aligned(&deserialized_list, error_buf, 24));
    TEST_ASSERT_EQUAL_HEX16(32, bosch_uss_object_list_deserialize_4byte_aligned(&deserialized_list, buffer, 40));

    TEST_ASSERT_TRUE(timestamp_is_equal(bosch_uss_object_list_get_timestamp(&list),
                                        bosch_uss_object_list_get_timestamp(&deserialized_list)));
    for (i = 0; i < OBJECT_LIST_NUM; i++)
    {
        TEST_ASSERT_EQUAL_HEX16(bosch_uss_object_list_get_object(&list, i),
                                bosch_uss_object_list_get_object(&deserialized_list, i));
    }
}

static void test_bosch_uss_8byte_aligned_serialize_and_deserialize(void)
{
    uint8_t i;
    memset(buffer, 0, 40);

    TEST_ASSERT_EQUAL(32, bosch_uss_object_list_get_serialized_size_8byte_aligned(&list));

    TEST_ASSERT_EQUAL_HEX16(RC_SERIALIZATION_BUFFER_OVERFLOW,
                            bosch_uss_object_list_serialize_8byte_aligned(&list, error_buf, 24));
    TEST_ASSERT_EQUAL_HEX16(32, bosch_uss_object_list_serialize_8byte_aligned(&list, buffer, 40));

    TEST_ASSERT_EQUAL_HEX16(RC_DESERIALIZATION_BUFFER_UNDERFLOW,
                            bosch_uss_object_list_deserialize_8byte_aligned(&deserialized_list, error_buf, 24));
    TEST_ASSERT_EQUAL_HEX16(32, bosch_uss_object_list_deserialize_8byte_aligned(&deserialized_list, buffer, 40));

    TEST_ASSERT_TRUE(timestamp_is_equal(bosch_uss_object_list_get_timestamp(&list),
                                        bosch_uss_object_list_get_timestamp(&deserialized_list)));
    for (i = 0; i < OBJECT_LIST_NUM; i++)
    {
        TEST_ASSERT_EQUAL_HEX16(bosch_uss_object_list_get_object(&list, i),
                                bosch_uss_object_list_get_object(&deserialized_list, i));
    }
}

static void test_bosch_uss_default_serialize_and_deserialize(void)
{
    uint8_t i;
    memset(buffer, 0, 40);

    TEST_ASSERT_EQUAL(32, bosch_uss_object_list_get_serialized_size(&list));
    TEST_ASSERT_EQUAL_HEX16(32, bosch_uss_object_list_serialize(&list, buffer, 40));
    TEST_ASSERT_EQUAL_HEX16(32, bosch_uss_object_list_deserialize(&deserialized_list, buffer, 40));
    TEST_ASSERT_TRUE(timestamp_is_equal(bosch_uss_object_list_get_timestamp(&list),
                                        bosch_uss_object_list_get_timestamp(&deserialized_list)));
    for (i = 0; i < OBJECT_LIST_NUM; i++)
    {
        TEST_ASSERT_EQUAL_HEX16(bosch_uss_object_list_get_object(&list, i),
                                bosch_uss_object_list_get_object(&deserialized_list, i));
    }
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_bosch_uss_driver_process);
    RUN_TEST(test_bosch_uss_4byte_aligned_serialize_and_deserialize);
    RUN_TEST(test_bosch_uss_8byte_aligned_serialize_and_deserialize);
    RUN_TEST(test_bosch_uss_default_serialize_and_deserialize);

    return UNITY_END();
}
