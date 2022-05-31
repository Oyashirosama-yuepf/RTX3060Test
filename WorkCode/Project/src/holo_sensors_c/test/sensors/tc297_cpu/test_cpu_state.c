/*!
 * @brief Unit test for cpu state driver.
 * @author liuya@holomaitc.com
 * @date 2020-02-24
 * @attention Copyright@Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <string.h>
#include <time.h>
#include <unity.h>

#include <holo_c/sensors/tc297_cpu/cpu_state.h>

struct CpuState cpu_state;

void test_cpu_state_set_and_get(void)
{
    time_t           utc_seconds;
    struct Timestamp time_stamp;

    utc_seconds = time((time_t*)NULL);

    timestamp_init_from_sec(&time_stamp, utc_seconds);

    TEST_ASSERT_EQUAL(RC_SUCCESS, cpu_state_set_timestamp(&cpu_state, &time_stamp));

    TEST_ASSERT_EQUAL(RC_SUCCESS, cpu_state_set_core_id(&cpu_state, 1));
    TEST_ASSERT_EQUAL(RC_SUCCESS, cpu_state_set_task_num(&cpu_state, 5));

    TEST_ASSERT_EQUAL(RC_SUCCESS, cpu_state_set_task_name(&cpu_state, 0, "IDLE"));
    TEST_ASSERT_EQUAL(RC_SUCCESS, cpu_state_set_cpu_load(&cpu_state, 0, 0.355));
    TEST_ASSERT_EQUAL(RC_SUCCESS, cpu_state_set_task_name(&cpu_state, 1, "SHA_MEM"));
    TEST_ASSERT_EQUAL(RC_SUCCESS, cpu_state_set_cpu_load(&cpu_state, 1, 0.2785));
    TEST_ASSERT_EQUAL(RC_SUCCESS, cpu_state_set_task_name(&cpu_state, 2, "HACP_CLIENT"));
    TEST_ASSERT_EQUAL(RC_SUCCESS, cpu_state_set_cpu_load(&cpu_state, 2, 0.0532));
    TEST_ASSERT_EQUAL(RC_SUCCESS, cpu_state_set_task_name(&cpu_state, 3, "UBLOX"));
    TEST_ASSERT_EQUAL(RC_SUCCESS, cpu_state_set_cpu_load(&cpu_state, 3, 0.1109));
    TEST_ASSERT_EQUAL(RC_SUCCESS, cpu_state_set_task_name(&cpu_state, 4, "CPU_STATE"));
    TEST_ASSERT_EQUAL(RC_SUCCESS, cpu_state_set_cpu_load(&cpu_state, 4, 0.774));

    timestamp_init_from_timestamp(&time_stamp, cpu_state_get_timestamp(&cpu_state));
    TEST_ASSERT_EQUAL_INT64(utc_seconds, timestamp_get_sec(&time_stamp));

    TEST_ASSERT_EQUAL_HEX16(1, cpu_state_get_core_id(&cpu_state));
    TEST_ASSERT_EQUAL_HEX16(5, cpu_state_get_task_num(&cpu_state));

    TEST_ASSERT_EQUAL_STRING("IDLE", cpu_state_get_task_name(&cpu_state, 0));
    TEST_ASSERT_EQUAL_FLOAT(0.355, cpu_state_get_cpu_load(&cpu_state, 0));
    TEST_ASSERT_EQUAL_STRING("SHA_MEM", cpu_state_get_task_name(&cpu_state, 1));
    TEST_ASSERT_EQUAL_FLOAT(0.2785, cpu_state_get_cpu_load(&cpu_state, 1));
    TEST_ASSERT_EQUAL_STRING("HACP_CLIENT", cpu_state_get_task_name(&cpu_state, 2));
    TEST_ASSERT_EQUAL_FLOAT(0.0532, cpu_state_get_cpu_load(&cpu_state, 2));
    TEST_ASSERT_EQUAL_STRING("UBLOX", cpu_state_get_task_name(&cpu_state, 3));
    TEST_ASSERT_EQUAL_FLOAT(0.1109, cpu_state_get_cpu_load(&cpu_state, 3));
    TEST_ASSERT_EQUAL_STRING("CPU_STATE", cpu_state_get_task_name(&cpu_state, 4));
    TEST_ASSERT_EQUAL_FLOAT(0.774, cpu_state_get_cpu_load(&cpu_state, 4));
}

void test_cpu_state_serialize_and_deserialize(void)
{
    uint8_t         buffer[400];
    uint8_t         error_buffer[100];
    struct CpuState deserialized_cpu_state;

    memset(buffer, 0, 400);
    memset(error_buffer, 0, 100);

    TEST_ASSERT_EQUAL(RC_SERIALIZATION_BUFFER_OVERFLOW, cpu_state_serialize(&cpu_state, error_buffer, 100));

    TEST_ASSERT_EQUAL(112, cpu_state_serialize(&cpu_state, buffer, 400));

    memcpy(error_buffer, buffer, 100);
    TEST_ASSERT_EQUAL(RC_DESERIALIZATION_BUFFER_UNDERFLOW,
                      cpu_state_deserialize(&deserialized_cpu_state, error_buffer, 100));

    TEST_ASSERT_EQUAL(112, cpu_state_deserialize(&deserialized_cpu_state, buffer, 400));

    TEST_ASSERT_EQUAL_HEX(cpu_state.timestamp.sec, deserialized_cpu_state.timestamp.sec);
    TEST_ASSERT_EQUAL_HEX(cpu_state.timestamp.nsec, deserialized_cpu_state.timestamp.nsec);

    TEST_ASSERT_EQUAL_HEX16(1, cpu_state_get_core_id(&deserialized_cpu_state));
    TEST_ASSERT_EQUAL_HEX16(5, cpu_state_get_task_num(&deserialized_cpu_state));

    TEST_ASSERT_EQUAL_STRING("IDLE", cpu_state_get_task_name(&deserialized_cpu_state, 0));
    TEST_ASSERT_EQUAL_FLOAT(0.355, cpu_state_get_cpu_load(&deserialized_cpu_state, 0));
    TEST_ASSERT_EQUAL_STRING("SHA_MEM", cpu_state_get_task_name(&deserialized_cpu_state, 1));
    TEST_ASSERT_EQUAL_FLOAT(0.2785, cpu_state_get_cpu_load(&deserialized_cpu_state, 1));
    TEST_ASSERT_EQUAL_STRING("HACP_CLIENT", cpu_state_get_task_name(&deserialized_cpu_state, 2));
    TEST_ASSERT_EQUAL_FLOAT(0.0532, cpu_state_get_cpu_load(&deserialized_cpu_state, 2));
    TEST_ASSERT_EQUAL_STRING("UBLOX", cpu_state_get_task_name(&deserialized_cpu_state, 3));
    TEST_ASSERT_EQUAL_FLOAT(0.1109, cpu_state_get_cpu_load(&deserialized_cpu_state, 3));
    TEST_ASSERT_EQUAL_STRING("CPU_STATE", cpu_state_get_task_name(&deserialized_cpu_state, 4));
    TEST_ASSERT_EQUAL_FLOAT(0.774, cpu_state_get_cpu_load(&deserialized_cpu_state, 4));
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_cpu_state_set_and_get);
    RUN_TEST(test_cpu_state_serialize_and_deserialize);

    return UNITY_END();
}
