/*!
 * @brief Unit test for light_signal_request.
 * @author lijiawen(lijiawen@holomaitc.com)
 * @date 2019-11-28
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <holo_c/common/light_signal_request.h>
#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>
#include <unity.h>

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test void light_signal_request_init_default(struct LightSignalRequest* request);
 */
void test_light_signal_request_init_default(void)
{
    struct LightSignalRequest request;
    light_signal_request_init_default(&request);

    TEST_ASSERT_EQUAL_UINT32(0u, timestamp_get_sec(light_signal_request_get_timestamp(&request)));
    TEST_ASSERT_EQUAL_UINT32(0u, timestamp_get_nsec(light_signal_request_get_timestamp(&request)));

    TEST_ASSERT_EQUAL_UINT16(0u, light_signal_request_get_light_command(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_left_turn_signal(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_right_turn_signal(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_hazard_flasher(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_brake_light(&request));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test:
 *             1. const struct Timestamp* light_signal_request_get_timestamp(const struct LightSignalRequest* request);
 *             2. void light_signal_request_set_timestamp(struct LightSignalRequest* request, const struct Timestamp* stamp);
 */
static void test_light_signal_request_timestamp(void)
{
    struct LightSignalRequest request;
    struct Timestamp stamp;
    light_signal_request_init_default(&request);
    timestamp_init_from_sec_nsec(&stamp, 1, 2);

    const struct Timestamp* stamp1 = light_signal_request_get_timestamp(&request);
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_sec(stamp1));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_nsec(stamp1));
    light_signal_request_set_timestamp(&request, &stamp);
    TEST_ASSERT_EQUAL_UINT32(1, timestamp_get_sec(stamp1));
    TEST_ASSERT_EQUAL_UINT32(2, timestamp_get_nsec(stamp1));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test:
 */
static void test_light_signal_request_light(void)
{
    struct LightSignalRequest request;
    light_signal_request_init_default(&request);
    TEST_ASSERT_EQUAL_UINT16(0x0000, light_signal_request_get_light_command(&request));

    light_signal_request_set_left_turn_signal(&request, true);
    TEST_ASSERT_EQUAL_UINT16(0x0080, light_signal_request_get_light_command(&request));
    TEST_ASSERT_TRUE(light_signal_request_get_left_turn_signal(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_right_turn_signal(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_hazard_flasher(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_brake_light(&request));
    light_signal_request_set_light_command(&request, 0x0080);
    TEST_ASSERT_TRUE(light_signal_request_get_left_turn_signal(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_right_turn_signal(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_hazard_flasher(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_brake_light(&request));

    light_signal_request_set_left_turn_signal(&request, false);
    light_signal_request_set_right_turn_signal(&request, true);
    TEST_ASSERT_EQUAL_UINT16(0x0040, light_signal_request_get_light_command(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_left_turn_signal(&request));
    TEST_ASSERT_TRUE(light_signal_request_get_right_turn_signal(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_hazard_flasher(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_brake_light(&request));
    light_signal_request_set_light_command(&request, 0x0040);
    TEST_ASSERT_FALSE(light_signal_request_get_left_turn_signal(&request));
    TEST_ASSERT_TRUE(light_signal_request_get_right_turn_signal(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_hazard_flasher(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_brake_light(&request));

    light_signal_request_set_right_turn_signal(&request, false);
    light_signal_request_set_hazard_flasher(&request, true);
    TEST_ASSERT_EQUAL_UINT16(0x0020, light_signal_request_get_light_command(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_left_turn_signal(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_right_turn_signal(&request));
    TEST_ASSERT_TRUE(light_signal_request_get_hazard_flasher(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_brake_light(&request));
    light_signal_request_set_light_command(&request, 0x0020);
    TEST_ASSERT_FALSE(light_signal_request_get_left_turn_signal(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_right_turn_signal(&request));
    TEST_ASSERT_TRUE(light_signal_request_get_hazard_flasher(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_brake_light(&request));

    light_signal_request_set_hazard_flasher(&request, false);
    light_signal_request_set_brake_light(&request, true);
    TEST_ASSERT_EQUAL_UINT16(0x0004, light_signal_request_get_light_command(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_left_turn_signal(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_right_turn_signal(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_hazard_flasher(&request));
    TEST_ASSERT_TRUE(light_signal_request_get_brake_light(&request));
    light_signal_request_set_light_command(&request, 0x0004);
    TEST_ASSERT_FALSE(light_signal_request_get_left_turn_signal(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_right_turn_signal(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_hazard_flasher(&request));
    TEST_ASSERT_TRUE(light_signal_request_get_brake_light(&request));

    light_signal_request_set_brake_light(&request, false);
    TEST_ASSERT_EQUAL_UINT16(0x0000, light_signal_request_get_light_command(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_left_turn_signal(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_right_turn_signal(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_hazard_flasher(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_brake_light(&request));
    light_signal_request_set_light_command(&request, 0x0000);
    TEST_ASSERT_FALSE(light_signal_request_get_left_turn_signal(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_right_turn_signal(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_hazard_flasher(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_brake_light(&request));
    
    light_signal_request_set_light_command(&request, 0x00e4);
    TEST_ASSERT_TRUE(light_signal_request_get_left_turn_signal(&request));
    TEST_ASSERT_TRUE(light_signal_request_get_right_turn_signal(&request));
    TEST_ASSERT_TRUE(light_signal_request_get_hazard_flasher(&request));
    TEST_ASSERT_TRUE(light_signal_request_get_brake_light(&request));
    light_signal_request_set_light_command(&request, 0x0000);
    TEST_ASSERT_FALSE(light_signal_request_get_left_turn_signal(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_right_turn_signal(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_hazard_flasher(&request));
    TEST_ASSERT_FALSE(light_signal_request_get_brake_light(&request));
}

static void test_light_signal_request_serialize_deserialize(void)
{
    struct LightSignalRequest request;
    uint32_t expected_size;
    retcode_t retcode;
    uint8_t buffer[512];

    expected_size = light_signal_request_get_serialized_size(&request);
    printf("expected_size = %d\n", expected_size);

    retcode = light_signal_request_serialize(&request, buffer, 0);
    TEST_ASSERT_EQUAL_INT32(RC_SERIALIZATION_BUFFER_OVERFLOW, retcode);
    retcode = light_signal_request_deserialize(&request, buffer, 0);
    TEST_ASSERT_EQUAL_INT32(RC_DESERIALIZATION_BUFFER_UNDERFLOW, retcode);

    retcode = light_signal_request_serialize(&request, buffer, sizeof(buffer));
    printf("serialize_size = %d\n", retcode);
    TEST_ASSERT_EQUAL_UINT32(expected_size, retcode);
    retcode = light_signal_request_deserialize(&request, buffer, sizeof(buffer));
    printf("deserialize_size = %d\n", retcode);
    TEST_ASSERT_EQUAL_UINT32(expected_size, retcode);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_light_signal_request_init_default);
    RUN_TEST(test_light_signal_request_timestamp);
    RUN_TEST(test_light_signal_request_light);
    RUN_TEST(test_light_signal_request_serialize_deserialize);
    return UNITY_END();
}
