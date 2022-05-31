/*!
 * @brief Unit test for vehicle can driver.
 * @author liuya@holomaitc.com
 * @date 2019-9-25
 * @attention Copyright@Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo_c/common/chassis_state.h>
#include <holo_c/sensors/can/vehicle_can_driver.h>
#include <holo_c/sensors/vehicle_body_state/vehicle_body_state.h>
#include <holo_c/utils/serialization.h>
#include <string.h>
#include <time.h>
#include <unity.h>

struct CanMessage
{
    uint32_t id;
    uint8_t  len;
    uint8_t  data[8];
};

uint8_t                        buffer[100];
struct CanMessage              can_msg;
static struct ChassisState     chassis_state;
static struct ChassisState     deserialized_chassis_state;
static struct VehicleBodyState vehicle_body_state;

static void test_light_can_raw_data_process(void)
{
    time_t           utc_seconds;
    struct Timestamp sys_time;

    utc_seconds = time((time_t*)NULL);
    timestamp_init_from_sec(&sys_time, utc_seconds);

    can_msg.id      = 0x400;
    can_msg.len     = 8;
    can_msg.data[0] = 0x00;
    can_msg.data[1] = 0x00;
    can_msg.data[2] = 0x90;
    can_msg.data[3] = 0x01;
    can_msg.data[4] = 0x00;
    can_msg.data[5] = 0x00;
    can_msg.data[6] = 0x00;
    can_msg.data[7] = 0x00;

    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));

    TEST_ASSERT_TRUE(timestamp_is_equal(&sys_time, chassis_state_get_timestamp(&chassis_state)));
    TEST_ASSERT_EQUAL_HEX16(0x01, chassis_state_is_left_turn_signal_on(&chassis_state));
    TEST_ASSERT_EQUAL_HEX16(0x01, chassis_state_is_right_turn_signal_on(&chassis_state));
    TEST_ASSERT_EQUAL_HEX16(0x01, chassis_state_is_hazard_flasher_on(&chassis_state));
}

static void test_brake_can_raw_data_process(void)
{
    time_t           utc_seconds;
    struct Timestamp sys_time;

    utc_seconds = time((time_t*)NULL);
    timestamp_init_from_sec(&sys_time, utc_seconds);

    can_msg.id      = 0x401;
    can_msg.len     = 8;
    can_msg.data[0] = 0x00;
    can_msg.data[1] = 0x00;
    can_msg.data[2] = 0x21;
    can_msg.data[3] = 0x04;
    can_msg.data[4] = 0x00;
    can_msg.data[5] = 0x00;
    can_msg.data[6] = 0x00;
    can_msg.data[7] = 0x20;

    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));

    TEST_ASSERT_TRUE(timestamp_is_equal(&sys_time, chassis_state_get_timestamp(&chassis_state)));
    TEST_ASSERT_EQUAL_HEX16(0x01, chassis_state_is_longitudinal_takeover(&chassis_state));

    can_msg.data[2] = 0x64;
    can_msg.data[3] = 0x00;
    can_msg.data[7] = 0x00;
    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));
    TEST_ASSERT_EQUAL_HEX16(0x00, chassis_state_is_longitudinal_takeover(&chassis_state));
}

static void test_door_can_raw_data_process(void)
{
    time_t           utc_seconds;
    struct Timestamp sys_time;

    utc_seconds = time((time_t*)NULL);
    timestamp_init_from_sec(&sys_time, utc_seconds);

    can_msg.id      = 0x402;
    can_msg.len     = 8;
    can_msg.data[0] = 0x00;
    can_msg.data[1] = 0x00;
    can_msg.data[2] = 0x30;
    can_msg.data[3] = 0x05;
    can_msg.data[4] = 0x00;
    can_msg.data[5] = 0x00;
    can_msg.data[6] = 0x00;
    can_msg.data[7] = 0x00;

    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));

    TEST_ASSERT_TRUE(timestamp_is_equal(&sys_time, chassis_state_get_timestamp(&chassis_state)));
    TEST_ASSERT_EQUAL_HEX16(0x01, chassis_state_is_front_left_door_open(&chassis_state));
    TEST_ASSERT_EQUAL_HEX16(0x01, chassis_state_is_front_right_door_open(&chassis_state));
    TEST_ASSERT_EQUAL_HEX16(0x01, chassis_state_is_rear_left_door_open(&chassis_state));
    TEST_ASSERT_EQUAL_HEX16(0x01, chassis_state_is_rear_right_door_open(&chassis_state));
}

static void test_epb_can_raw_data_process(void)
{
    time_t           utc_seconds;
    struct Timestamp sys_time;

    utc_seconds = time((time_t*)NULL);
    timestamp_init_from_sec(&sys_time, utc_seconds);

    can_msg.id      = 0x403;
    can_msg.len     = 8;
    can_msg.data[0] = 0x00;
    can_msg.data[1] = 0x00;
    can_msg.data[2] = 0x00;
    can_msg.data[3] = 0x00;
    can_msg.data[4] = 0x00;
    can_msg.data[5] = 0x00;
    can_msg.data[6] = 0x00;
    can_msg.data[7] = 0x20;

    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));

    TEST_ASSERT_TRUE(timestamp_is_equal(&sys_time, chassis_state_get_timestamp(&chassis_state)));
    TEST_ASSERT_EQUAL_HEX16(0x01, chassis_state_is_handbrake_hold(&chassis_state));

    can_msg.data[7] = 0x00;
    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));
    TEST_ASSERT_EQUAL_HEX16(0x00, chassis_state_is_handbrake_hold(&chassis_state));
}

static void test_gear_can_raw_data_process(void)
{
    time_t           utc_seconds;
    struct Timestamp sys_time;

    utc_seconds = time((time_t*)NULL);
    timestamp_init_from_sec(&sys_time, utc_seconds);

    can_msg.id      = 0x404;
    can_msg.len     = 8;
    can_msg.data[0] = 0x00;
    can_msg.data[1] = 0x00;
    can_msg.data[2] = 0x00;
    can_msg.data[3] = 0x00;
    can_msg.data[4] = 0x00;
    can_msg.data[5] = 0x20;
    can_msg.data[6] = 0x00;
    can_msg.data[7] = 0x00;

    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));

    TEST_ASSERT_TRUE(timestamp_is_equal(&sys_time, chassis_state_get_timestamp(&chassis_state)));
    TEST_ASSERT_EQUAL_HEX16(GEAR_POSITION_D, chassis_state_get_gear_position(&chassis_state));

    can_msg.data[5] = 0x14;
    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));
    TEST_ASSERT_EQUAL_HEX16(GEAR_POSITION_P, chassis_state_get_gear_position(&chassis_state));

    can_msg.data[5] = 0x18;
    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));
    TEST_ASSERT_EQUAL_HEX16(GEAR_POSITION_R, chassis_state_get_gear_position(&chassis_state));

    can_msg.data[5] = 0x1C;
    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));
    TEST_ASSERT_EQUAL_HEX16(GEAR_POSITION_N, chassis_state_get_gear_position(&chassis_state));

    can_msg.data[5] = 0xFF;
    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));
    TEST_ASSERT_EQUAL_HEX16(GEAR_POSITION_UNKNOWN, chassis_state_get_gear_position(&chassis_state));
}

static void test_acc_status_can_raw_data_process(void)
{
    time_t           utc_seconds;
    struct Timestamp sys_time;

    utc_seconds = time((time_t*)NULL);
    timestamp_init_from_sec(&sys_time, utc_seconds);

    can_msg.id      = 0x405;
    can_msg.len     = 8;
    can_msg.data[0] = 0x00;
    can_msg.data[1] = 0x00;
    can_msg.data[2] = 0x00;
    can_msg.data[3] = 0x03;
    can_msg.data[4] = 0x00;
    can_msg.data[5] = 0x00;
    can_msg.data[6] = 0x00;
    can_msg.data[7] = 0x00;

    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));

    TEST_ASSERT_TRUE(timestamp_is_equal(&sys_time, chassis_state_get_timestamp(&chassis_state)));
    TEST_ASSERT_EQUAL_HEX16(ACTUATOR_STATE_ACTIVE, chassis_state_get_longitudinal_actuator_state(&chassis_state));

    can_msg.data[3] = 0x02;
    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));
    TEST_ASSERT_EQUAL_HEX16(ACTUATOR_STATE_READY, chassis_state_get_longitudinal_actuator_state(&chassis_state));

    can_msg.data[3] = 0x06;
    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));
    TEST_ASSERT_EQUAL_HEX16(ACTUATOR_STATE_FAULT, chassis_state_get_longitudinal_actuator_state(&chassis_state));
}

static void test_lat_torque_can_raw_data_process(void)
{
    time_t           utc_seconds;
    struct Timestamp sys_time;

    utc_seconds = time((time_t*)NULL);
    timestamp_init_from_sec(&sys_time, utc_seconds);

    can_msg.id      = 0x406;
    can_msg.len     = 8;
    can_msg.data[0] = 0x00;
    can_msg.data[1] = 0x00;
    can_msg.data[2] = 0x00;
    can_msg.data[3] = 0x00;
    can_msg.data[4] = 0x05;
    can_msg.data[5] = 0x20;
    can_msg.data[6] = 0x83;
    can_msg.data[7] = 0x00;

    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));

    TEST_ASSERT_TRUE(timestamp_is_equal(&sys_time, chassis_state_get_timestamp(&chassis_state)));
    TEST_ASSERT_EQUAL_HEX16(ACTUATOR_STATE_FAULT, chassis_state_get_lateral_actuator_state(&chassis_state));

    can_msg.data[4] = 0x03;
    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));
    TEST_ASSERT_EQUAL_HEX16(ACTUATOR_STATE_FAULT, chassis_state_get_lateral_actuator_state(&chassis_state));

    can_msg.data[4] = 0x04;
    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));
    TEST_ASSERT_EQUAL_HEX16(ACTUATOR_STATE_FAULT, chassis_state_get_lateral_actuator_state(&chassis_state));
}

static void test_lat_angle_can_raw_data_process(void)
{
    time_t           utc_seconds;
    struct Timestamp sys_time;

    utc_seconds = time((time_t*)NULL);
    timestamp_init_from_sec(&sys_time, utc_seconds);

    can_msg.id      = 0x407;
    can_msg.len     = 8;
    can_msg.data[0] = 0x00;
    can_msg.data[1] = 0x00;
    can_msg.data[2] = 0x00;
    can_msg.data[3] = 0x40;
    can_msg.data[4] = 0x02;
    can_msg.data[5] = 0x00;
    can_msg.data[6] = 0x00;
    can_msg.data[7] = 0x00;

    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));

    TEST_ASSERT_TRUE(timestamp_is_equal(&sys_time, chassis_state_get_timestamp(&chassis_state)));
}

static void test_steering_status_can_raw_data_process(void)
{
    time_t           utc_seconds;
    struct Timestamp sys_time;

    utc_seconds = time((time_t*)NULL);
    timestamp_init_from_sec(&sys_time, utc_seconds);

    can_msg.id      = 0x408;
    can_msg.len     = 8;
    can_msg.data[0] = 0x00;
    can_msg.data[1] = 0x10;
    can_msg.data[2] = 0x82;
    can_msg.data[3] = 0x60;
    can_msg.data[4] = 0x02;
    can_msg.data[5] = 0x00;
    can_msg.data[6] = 0x00;
    can_msg.data[7] = 0x00;

    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));

    TEST_ASSERT_TRUE(timestamp_is_equal(&sys_time, chassis_state_get_timestamp(&chassis_state)));

    TEST_ASSERT_EQUAL_FLOAT(-13.0, 13.6 * chassis_state_get_front_wheel_angle(&chassis_state) / M_PI * 180.0f);
}

static void test_button_can_raw_data_process(void)
{
    time_t           utc_seconds;
    struct Timestamp sys_time;

    utc_seconds = time((time_t*)NULL);
    timestamp_init_from_sec(&sys_time, utc_seconds);

    can_msg.id      = 0x409;
    can_msg.len     = 8;
    can_msg.data[0] = 0x00;
    can_msg.data[1] = 0x90;
    can_msg.data[2] = 0x0F;
    can_msg.data[3] = 0x00;
    can_msg.data[4] = 0x00;
    can_msg.data[5] = 0x00;
    can_msg.data[6] = 0x00;
    can_msg.data[7] = 0x00;

    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));

    TEST_ASSERT_TRUE(timestamp_is_equal(&sys_time, chassis_state_get_timestamp(&chassis_state)));
}

static void test_vehicle_speed_can_raw_data_process(void)
{
    time_t           utc_seconds;
    struct Timestamp sys_time;

    utc_seconds = time((time_t*)NULL);
    timestamp_init_from_sec(&sys_time, utc_seconds);

    can_msg.id      = 0x40A;
    can_msg.len     = 8;
    can_msg.data[0] = 0x00;
    can_msg.data[1] = 0x00;
    can_msg.data[2] = 0x00;
    can_msg.data[3] = 0x00;
    can_msg.data[4] = 0x48;
    can_msg.data[5] = 0x0D;
    can_msg.data[6] = 0x00;
    can_msg.data[7] = 0x00;

    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));

    TEST_ASSERT_TRUE(timestamp_is_equal(&sys_time, chassis_state_get_timestamp(&chassis_state)));
    TEST_ASSERT_EQUAL_FLOAT(34.0f, 3.6f * chassis_state_get_vehicle_speed(&chassis_state));
}

static void test_wheel_speed_can_raw_data_process(void)
{
    time_t           utc_seconds;
    struct Timestamp sys_time;

    utc_seconds = time((time_t*)NULL);
    timestamp_init_from_sec(&sys_time, utc_seconds);

    can_msg.id      = 0x40B;
    can_msg.len     = 8;
    can_msg.data[0] = 0x75;
    can_msg.data[1] = 0x06;
    can_msg.data[2] = 0x3D;
    can_msg.data[3] = 0x00;
    can_msg.data[4] = 0xE0;
    can_msg.data[5] = 0x2E;
    can_msg.data[6] = 0x8B;
    can_msg.data[7] = 0x3F;

    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));

    TEST_ASSERT_TRUE(timestamp_is_equal(&sys_time, chassis_state_get_timestamp(&chassis_state)));

    TEST_ASSERT_EQUAL_FLOAT(90.0f, chassis_state_get_front_left_wheel_speed(&chassis_state));
    TEST_ASSERT_EQUAL_FLOAT(122.0025f, chassis_state_get_front_right_wheel_speed(&chassis_state));
    TEST_ASSERT_EQUAL_FLOAT(12.3975f, chassis_state_get_rear_left_wheel_speed(&chassis_state));
    TEST_ASSERT_EQUAL_FLOAT(0.4575f, chassis_state_get_rear_right_wheel_speed(&chassis_state));
}

static void test_acc_can_raw_data_process(void)
{
    time_t           utc_seconds;
    struct Timestamp sys_time;

    utc_seconds = time((time_t*)NULL);
    timestamp_init_from_sec(&sys_time, utc_seconds);

    can_msg.id      = 0x40C;
    can_msg.len     = 8;
    can_msg.data[0] = 0x00;
    can_msg.data[1] = 0x00;
    can_msg.data[2] = 0xFE;
    can_msg.data[3] = 0x63;
    can_msg.data[4] = 0x02;
    can_msg.data[5] = 0xD0;
    can_msg.data[6] = 0x47;
    can_msg.data[7] = 0x00;

    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));

    TEST_ASSERT_TRUE(timestamp_is_equal(&sys_time, chassis_state_get_timestamp(&chassis_state)));

    TEST_ASSERT_EQUAL_FLOAT(1.27f, chassis_state_get_lateral_acceleration(&chassis_state));
    TEST_ASSERT_EQUAL_FLOAT(3.09375f, chassis_state_get_longitudinal_acceleration(&chassis_state));
    TEST_ASSERT_EQUAL_FLOAT(-20.0, chassis_state_get_yaw_rate(&chassis_state));
}

static void test_holo_can_plus_epb_data_process(void)
{
    time_t           utc_seconds;
    struct Timestamp sys_time;

    utc_seconds = time((time_t*)NULL);
    timestamp_init_from_sec(&sys_time, utc_seconds);

    can_msg.id      = 0x104;
    can_msg.len     = 8;
    can_msg.data[0] = 0x00;
    can_msg.data[1] = 0x00;
    can_msg.data[2] = 0x00;
    can_msg.data[3] = 0x00;
    can_msg.data[4] = 0x00;
    can_msg.data[5] = 0x00;
    can_msg.data[6] = 0x00;
    can_msg.data[7] = 0x20;

    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));

    TEST_ASSERT_TRUE(timestamp_is_equal(&sys_time, vehicle_body_state_get_timestamp(&vehicle_body_state)));
}

static void test_holo_can_plus_abs_data_process(void)
{
    time_t           utc_seconds;
    struct Timestamp sys_time;

    utc_seconds = time((time_t*)NULL);
    timestamp_init_from_sec(&sys_time, utc_seconds);

    can_msg.id      = 0x106;
    can_msg.len     = 8;
    can_msg.data[0] = 0x00;
    can_msg.data[1] = 0x00;
    can_msg.data[2] = 0x00;
    can_msg.data[3] = 0x00;
    can_msg.data[4] = 0x00;
    can_msg.data[5] = 0x02;
    can_msg.data[6] = 0x00;
    can_msg.data[7] = 0x08;

    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));

    TEST_ASSERT_TRUE(timestamp_is_equal(&sys_time, vehicle_body_state_get_timestamp(&vehicle_body_state)));

    TEST_ASSERT_EQUAL(1, vehicle_body_state_get_brake_light(&vehicle_body_state));
}

static void test_holo_can_plus_esp_data_process(void)
{
    time_t           utc_seconds;
    struct Timestamp sys_time;

    utc_seconds = time((time_t*)NULL);
    timestamp_init_from_sec(&sys_time, utc_seconds);

    can_msg.id      = 0xFD;
    can_msg.len     = 8;
    can_msg.data[0] = 0x00;
    can_msg.data[1] = 0x00;
    can_msg.data[2] = 0x00;
    can_msg.data[3] = 0x00;
    can_msg.data[4] = 0x00;
    can_msg.data[5] = 0x00;
    can_msg.data[6] = 0x00;
    can_msg.data[7] = 0x01;

    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));

    TEST_ASSERT_TRUE(timestamp_is_equal(&sys_time, vehicle_body_state_get_timestamp(&vehicle_body_state)));
}

static void test_holo_can_plus_button_data_process(void)
{
    time_t           utc_seconds;
    struct Timestamp sys_time;

    utc_seconds = time((time_t*)NULL);
    timestamp_init_from_sec(&sys_time, utc_seconds);

    can_msg.id      = 0x12B;
    can_msg.len     = 8;
    can_msg.data[0] = 0x00;
    can_msg.data[1] = 0x90;
    can_msg.data[2] = 0x0F;
    can_msg.data[3] = 0x00;
    can_msg.data[4] = 0x00;
    can_msg.data[5] = 0x00;
    can_msg.data[6] = 0x00;
    can_msg.data[7] = 0x00;

    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));

    TEST_ASSERT_TRUE(timestamp_is_equal(&sys_time, vehicle_body_state_get_timestamp(&vehicle_body_state)));

    TEST_ASSERT_EQUAL(1, vehicle_body_state_get_button_io(&vehicle_body_state));
    TEST_ASSERT_EQUAL(1, vehicle_body_state_get_button_mode(&vehicle_body_state));
    TEST_ASSERT_EQUAL(1, vehicle_body_state_get_button_set(&vehicle_body_state));
    TEST_ASSERT_EQUAL(1, vehicle_body_state_get_button_plus(&vehicle_body_state));
    TEST_ASSERT_EQUAL(1, vehicle_body_state_get_button_minus(&vehicle_body_state));
    TEST_ASSERT_EQUAL(1, vehicle_body_state_get_button_res(&vehicle_body_state));
}

static void test_holo_can_plus_belt_warning_data_process(void)
{
    time_t           utc_seconds;
    struct Timestamp sys_time;

    utc_seconds = time((time_t*)NULL);
    timestamp_init_from_sec(&sys_time, utc_seconds);

    can_msg.id      = 0x40;
    can_msg.len     = 8;
    can_msg.data[0] = 0x00;
    can_msg.data[1] = 0x00;
    can_msg.data[2] = 0x00;
    can_msg.data[3] = 0x00;
    can_msg.data[4] = 0x03;
    can_msg.data[5] = 0x00;
    can_msg.data[6] = 0x00;
    can_msg.data[7] = 0x00;

    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));

    TEST_ASSERT_TRUE(timestamp_is_equal(&sys_time, vehicle_body_state_get_timestamp(&vehicle_body_state)));

    TEST_ASSERT_EQUAL(1, vehicle_body_state_get_driver_seatbelt(&vehicle_body_state));
    TEST_ASSERT_EQUAL(1, vehicle_body_state_get_passenger_seatbelt(&vehicle_body_state));
}

static void test_holo_can_plus_door_data_process(void)
{
    time_t           utc_seconds;
    struct Timestamp sys_time;

    utc_seconds = time((time_t*)NULL);
    timestamp_init_from_sec(&sys_time, utc_seconds);

    can_msg.id      = 0x3DB;
    can_msg.len     = 8;
    can_msg.data[0] = 0x00;
    can_msg.data[1] = 0x00;
    can_msg.data[2] = 0x30;
    can_msg.data[3] = 0x65;
    can_msg.data[4] = 0x00;
    can_msg.data[5] = 0x00;
    can_msg.data[6] = 0x00;
    can_msg.data[7] = 0x00;

    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));

    TEST_ASSERT_TRUE(timestamp_is_equal(&sys_time, vehicle_body_state_get_timestamp(&vehicle_body_state)));

    TEST_ASSERT_EQUAL(1, vehicle_body_state_get_rear_left_door(&vehicle_body_state));
    TEST_ASSERT_EQUAL(1, vehicle_body_state_get_rear_right_door(&vehicle_body_state));
    TEST_ASSERT_EQUAL(1, vehicle_body_state_get_front_right_door(&vehicle_body_state));
    TEST_ASSERT_EQUAL(1, vehicle_body_state_get_front_left_door(&vehicle_body_state));
    TEST_ASSERT_EQUAL(1, vehicle_body_state_get_car_hood(&vehicle_body_state));
    TEST_ASSERT_EQUAL(1, vehicle_body_state_get_trunk_door(&vehicle_body_state));
}

static void test_holo_can_plus_belt_data_process(void)
{
    time_t           utc_seconds;
    struct Timestamp sys_time;

    utc_seconds = time((time_t*)NULL);
    timestamp_init_from_sec(&sys_time, utc_seconds);

    can_msg.id      = 0x520;
    can_msg.len     = 8;
    can_msg.data[0] = 0x00;
    can_msg.data[1] = 0x00;
    can_msg.data[2] = 0x00;
    can_msg.data[3] = 0x00;
    can_msg.data[4] = 0x00;
    can_msg.data[5] = 0x55;
    can_msg.data[6] = 0x01;
    can_msg.data[7] = 0x00;

    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));

    TEST_ASSERT_TRUE(timestamp_is_equal(&sys_time, vehicle_body_state_get_timestamp(&vehicle_body_state)));
}

static void test_holo_can_plus_wiper_data_process(void)
{
    time_t           utc_seconds;
    struct Timestamp sys_time;

    utc_seconds = time((time_t*)NULL);
    timestamp_init_from_sec(&sys_time, utc_seconds);

    can_msg.id      = 0x5A0;
    can_msg.len     = 5;
    can_msg.data[0] = 0x00;
    can_msg.data[1] = 0x00;
    can_msg.data[2] = 0x00;
    can_msg.data[3] = 0x08;
    can_msg.data[4] = 0x05;

    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));

    TEST_ASSERT_TRUE(timestamp_is_equal(&sys_time, vehicle_body_state_get_timestamp(&vehicle_body_state)));
    TEST_ASSERT_EQUAL(1, vehicle_body_state_get_front_wiper_state(&vehicle_body_state));
    TEST_ASSERT_EQUAL(80, vehicle_body_state_get_rainfall(&vehicle_body_state));

    can_msg.data[3] = 0x01;
    can_msg.data[4] = 0x00;
    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));

    TEST_ASSERT_EQUAL(0, vehicle_body_state_get_front_wiper_state(&vehicle_body_state));
    TEST_ASSERT_EQUAL(10, vehicle_body_state_get_rainfall(&vehicle_body_state));
}

static void test_holo_can_plus_light_data_process(void)
{
    time_t           utc_seconds;
    struct Timestamp sys_time;

    utc_seconds = time((time_t*)NULL);
    timestamp_init_from_sec(&sys_time, utc_seconds);

    can_msg.id      = 0x658;
    can_msg.len     = 8;
    can_msg.data[0] = 0x00;
    can_msg.data[1] = 0xE0;
    can_msg.data[2] = 0x01;
    can_msg.data[3] = 0x00;
    can_msg.data[4] = 0x00;
    can_msg.data[5] = 0x00;
    can_msg.data[6] = 0x00;
    can_msg.data[7] = 0x00;

    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));

    TEST_ASSERT_TRUE(timestamp_is_equal(&sys_time, vehicle_body_state_get_timestamp(&vehicle_body_state)));
    TEST_ASSERT_EQUAL(1, vehicle_body_state_get_low_beam(&vehicle_body_state));
    TEST_ASSERT_EQUAL(1, vehicle_body_state_get_high_beam(&vehicle_body_state));
    TEST_ASSERT_EQUAL(1, vehicle_body_state_get_front_fog_light(&vehicle_body_state));
    TEST_ASSERT_EQUAL(1, vehicle_body_state_get_rear_fog_light(&vehicle_body_state));
}

static void test_holo_can_plus_blinker_data_process(void)
{
    time_t           utc_seconds;
    struct Timestamp sys_time;

    utc_seconds = time((time_t*)NULL);
    timestamp_init_from_sec(&sys_time, utc_seconds);

    can_msg.id      = 0x366;
    can_msg.len     = 8;
    can_msg.data[0] = 0x00;
    can_msg.data[1] = 0x00;
    can_msg.data[2] = 0x90;
    can_msg.data[3] = 0x01;
    can_msg.data[4] = 0x00;
    can_msg.data[5] = 0x00;
    can_msg.data[6] = 0x00;
    can_msg.data[7] = 0x00;

    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                        can_msg.id, can_msg.data, can_msg.len));

    TEST_ASSERT_TRUE(timestamp_is_equal(&sys_time, vehicle_body_state_get_timestamp(&vehicle_body_state)));
}

static void test_invalid_can_raw_data_process(void)
{
    time_t           utc_seconds;
    struct Timestamp sys_time;

    utc_seconds = time((time_t*)NULL);
    timestamp_init_from_sec(&sys_time, utc_seconds);

    can_msg.id      = 0xFF;
    can_msg.len     = 8;
    can_msg.data[0] = 0x00;
    can_msg.data[1] = 0x00;
    can_msg.data[2] = 0xFE;
    can_msg.data[3] = 0x63;
    can_msg.data[4] = 0x02;
    can_msg.data[5] = 0xD0;
    can_msg.data[6] = 0x47;
    can_msg.data[7] = 0x00;

    TEST_ASSERT_EQUAL_INT64(RC_FAIL, vehicle_can_driver_process_data(&chassis_state, &vehicle_body_state, &sys_time,
                                                                     can_msg.id, can_msg.data, can_msg.len));
}

void test_chassis_state_serialize_and_deserialize(void)
{
    memset(buffer, 0, 100);

    chassis_state_serialize(&chassis_state, buffer, 100);
    chassis_state_deserialize(&deserialized_chassis_state, buffer, 100);

    TEST_ASSERT_EQUAL_HEX64(chassis_state.stamp.sec, deserialized_chassis_state.stamp.sec);
    TEST_ASSERT_EQUAL_HEX64(chassis_state.stamp.nsec, deserialized_chassis_state.stamp.nsec);

    TEST_ASSERT_EQUAL_FLOAT(chassis_state_get_vehicle_speed(&chassis_state),
                            chassis_state_get_vehicle_speed(&deserialized_chassis_state));
    TEST_ASSERT_EQUAL_FLOAT(chassis_state_get_front_left_wheel_speed(&chassis_state),
                            chassis_state_get_front_left_wheel_speed(&deserialized_chassis_state));
    TEST_ASSERT_EQUAL_FLOAT(chassis_state_get_front_right_wheel_speed(&chassis_state),
                            chassis_state_get_front_right_wheel_speed(&deserialized_chassis_state));
    TEST_ASSERT_EQUAL_FLOAT(chassis_state_get_rear_left_wheel_speed(&chassis_state),
                            chassis_state_get_rear_left_wheel_speed(&deserialized_chassis_state));
    TEST_ASSERT_EQUAL_FLOAT(chassis_state_get_rear_right_wheel_speed(&chassis_state),
                            chassis_state_get_rear_right_wheel_speed(&deserialized_chassis_state));
    TEST_ASSERT_EQUAL_FLOAT(chassis_state_get_longitudinal_acceleration(&chassis_state),
                            chassis_state_get_longitudinal_acceleration(&deserialized_chassis_state));
    TEST_ASSERT_EQUAL_FLOAT(chassis_state_get_lateral_acceleration(&chassis_state),
                            chassis_state_get_lateral_acceleration(&deserialized_chassis_state));
    TEST_ASSERT_EQUAL_FLOAT(chassis_state_get_yaw_rate(&chassis_state),
                            chassis_state_get_yaw_rate(&deserialized_chassis_state));
    TEST_ASSERT_EQUAL_FLOAT(chassis_state_get_front_wheel_angle(&chassis_state),
                            chassis_state_get_front_wheel_angle(&deserialized_chassis_state));

    TEST_ASSERT_EQUAL_HEX16(chassis_state_is_left_turn_signal_on(&chassis_state),
                            chassis_state_is_left_turn_signal_on(&deserialized_chassis_state));
    TEST_ASSERT_EQUAL_HEX16(chassis_state_is_right_turn_signal_on(&chassis_state),
                            chassis_state_is_right_turn_signal_on(&deserialized_chassis_state));
    TEST_ASSERT_EQUAL_HEX16(chassis_state_is_hazard_flasher_on(&chassis_state),
                            chassis_state_is_hazard_flasher_on(&deserialized_chassis_state));

    TEST_ASSERT_EQUAL_HEX16(chassis_state_is_front_left_door_open(&chassis_state),
                            chassis_state_is_front_left_door_open(&deserialized_chassis_state));
    TEST_ASSERT_EQUAL_HEX16(chassis_state_is_front_right_door_open(&chassis_state),
                            chassis_state_is_front_right_door_open(&deserialized_chassis_state));
    TEST_ASSERT_EQUAL_HEX16(chassis_state_is_rear_left_door_open(&chassis_state),
                            chassis_state_is_rear_left_door_open(&deserialized_chassis_state));
    TEST_ASSERT_EQUAL_HEX16(chassis_state_is_rear_right_door_open(&chassis_state),
                            chassis_state_is_rear_right_door_open(&deserialized_chassis_state));

    TEST_ASSERT_EQUAL_HEX16(chassis_state_get_gear_actuator_state(&chassis_state),
                            chassis_state_get_gear_actuator_state(&deserialized_chassis_state));

    TEST_ASSERT_EQUAL_HEX16(chassis_state_is_handbrake_hold(&chassis_state),
                            chassis_state_is_handbrake_hold(&deserialized_chassis_state));

    TEST_ASSERT_EQUAL_HEX16(chassis_state_get_longitudinal_actuator_state(&chassis_state),
                            chassis_state_get_longitudinal_actuator_state(&deserialized_chassis_state));

    TEST_ASSERT_EQUAL_HEX16(chassis_state_get_lateral_actuator_state(&chassis_state),
                            chassis_state_get_lateral_actuator_state(&deserialized_chassis_state));
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_light_can_raw_data_process);
    RUN_TEST(test_brake_can_raw_data_process);
    RUN_TEST(test_door_can_raw_data_process);
    RUN_TEST(test_epb_can_raw_data_process);
    RUN_TEST(test_gear_can_raw_data_process);
    RUN_TEST(test_acc_status_can_raw_data_process);
    RUN_TEST(test_lat_torque_can_raw_data_process);
    RUN_TEST(test_lat_angle_can_raw_data_process);
    RUN_TEST(test_steering_status_can_raw_data_process);
    RUN_TEST(test_button_can_raw_data_process);
    RUN_TEST(test_vehicle_speed_can_raw_data_process);
    RUN_TEST(test_wheel_speed_can_raw_data_process);
    RUN_TEST(test_acc_can_raw_data_process);
    RUN_TEST(test_holo_can_plus_abs_data_process);
    RUN_TEST(test_holo_can_plus_belt_warning_data_process);
    RUN_TEST(test_holo_can_plus_belt_data_process);
    RUN_TEST(test_holo_can_plus_blinker_data_process);
    RUN_TEST(test_holo_can_plus_button_data_process);
    RUN_TEST(test_holo_can_plus_door_data_process);
    RUN_TEST(test_holo_can_plus_epb_data_process);
    RUN_TEST(test_holo_can_plus_esp_data_process);
    RUN_TEST(test_holo_can_plus_light_data_process);
    RUN_TEST(test_holo_can_plus_wiper_data_process);
    RUN_TEST(test_invalid_can_raw_data_process);
    RUN_TEST(test_chassis_state_serialize_and_deserialize);

    return UNITY_END();
}
