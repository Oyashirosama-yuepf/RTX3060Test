/*!
 * @brief Unit test for vehicle body state.
 * @author liuya@holomaitc.com
 * @date 2020-03-13
 * @attention Copyright@Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo_c/sensors/vehicle_body_state/vehicle_body_state.h>
#include <holo_c/utils/serialization.h>
#include <string.h>
#include <time.h>
#include <unity.h>

static void test_vehicle_body_state_init_default(void)
{
    struct Timestamp        time_stamp;
    struct VehicleBodyState vehicle_body_state;

    vehicle_body_state_init_default(&vehicle_body_state);

    memcpy(&time_stamp, vehicle_body_state_get_timestamp(&vehicle_body_state), sizeof(struct Timestamp));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_sec(&time_stamp));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_nsec(&time_stamp));

    TEST_ASSERT_EQUAL_FLOAT(0.0f, vehicle_body_state_get_temperature(&vehicle_body_state));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, vehicle_body_state_get_front_left_tire_pressure(&vehicle_body_state));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, vehicle_body_state_get_front_right_tire_pressure(&vehicle_body_state));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, vehicle_body_state_get_rear_left_tire_pressure(&vehicle_body_state));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, vehicle_body_state_get_rear_right_tire_pressure(&vehicle_body_state));

    TEST_ASSERT_EQUAL_UINT8(0, vehicle_body_state_get_rear_fog_light(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT8(0, vehicle_body_state_get_front_fog_light(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT8(0, vehicle_body_state_get_brake_light(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT8(0, vehicle_body_state_get_high_beam(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT8(0, vehicle_body_state_get_low_beam(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT8(0, vehicle_body_state_get_hazard_flasher(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT8(0, vehicle_body_state_get_right_turn_signal(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT8(0, vehicle_body_state_get_left_turn_signal(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_light_state(&vehicle_body_state));

    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_rear_right_window(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_rear_left_window(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_front_right_window(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_front_left_window(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_auto_sunroof(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_trunk_door(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_car_hood(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_rear_right_door(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_rear_left_door(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_front_right_door(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_front_left_door(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_driver_seatbelt(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_passenger_seatbelt(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_front_wiper_state(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_rear_wiper_state(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_cockpit_state(&vehicle_body_state));

    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_button_set(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_button_res(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_button_plus(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_button_minus(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_button_mode(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_button_io(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_button_state(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_button_volume_up(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_button_volume_down(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_button_voice(&vehicle_body_state));

    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_rainfall(&vehicle_body_state));

    TEST_ASSERT_EQUAL_UINT8(44, vehicle_body_state_get_serialized_size(&vehicle_body_state));
}

static void test_vehicle_body_state_set_and_get(void)
{
    time_t                  utc_seconds;
    struct Timestamp        time_stamp;
    struct Timestamp        read_time_stamp;
    struct VehicleBodyState vehicle_body_state;

    utc_seconds = time((time_t*)NULL);

    timestamp_init_from_sec(&time_stamp, utc_seconds);

    vehicle_body_state_set_timestamp(&vehicle_body_state, &time_stamp);

    vehcile_body_state_set_temperature(&vehicle_body_state, 37.5f);
    vehicle_body_state_set_front_left_tire_pressure(&vehicle_body_state, 2.35f);
    vehicle_body_state_set_front_right_tire_pressure(&vehicle_body_state, 1.89f);
    vehicle_body_state_set_rear_left_tire_pressure(&vehicle_body_state, 3.022f);
    vehicle_body_state_set_rear_right_tire_pressure(&vehicle_body_state, 2.67f);

    vehicle_body_state_set_rear_fog_light(&vehicle_body_state, 1);
    vehicle_body_state_set_front_fog_light(&vehicle_body_state, 1);
    vehicle_body_state_set_brake_light(&vehicle_body_state, 1);
    vehicle_body_state_set_high_beam(&vehicle_body_state, 1);
    vehicle_body_state_set_low_beam(&vehicle_body_state, 1);
    vehicle_body_state_set_hazard_flasher(&vehicle_body_state, 1);
    vehicle_body_state_set_right_turn_signal(&vehicle_body_state, 1);
    vehicle_body_state_set_left_turn_signal(&vehicle_body_state, 1);

    vehicle_body_state_set_rear_right_window(&vehicle_body_state, 1);
    vehicle_body_state_set_rear_left_window(&vehicle_body_state, 1);
    vehicle_body_state_set_front_right_window(&vehicle_body_state, 1);
    vehicle_body_state_set_front_left_window(&vehicle_body_state, 1);
    vehicle_body_state_set_auto_sunroof(&vehicle_body_state, 1);
    vehicle_body_state_set_trunk_door(&vehicle_body_state, 1);
    vehicle_body_state_set_car_hood(&vehicle_body_state, 1);
    vehicle_body_state_set_rear_right_door(&vehicle_body_state, 1);
    vehicle_body_state_set_rear_left_door(&vehicle_body_state, 1);
    vehicle_body_state_set_front_right_door(&vehicle_body_state, 1);
    vehicle_body_state_set_front_left_door(&vehicle_body_state, 1);
    vehicle_body_state_set_driver_seatbelt(&vehicle_body_state, 1);
    vehicle_body_state_set_passenger_seatbelt(&vehicle_body_state, 1);
    vehicle_body_state_set_front_wiper_state(&vehicle_body_state, 1);
    vehicle_body_state_set_rear_wiper_state(&vehicle_body_state, 1);

    vehicle_body_state_set_button_set(&vehicle_body_state, 1);
    vehicle_body_state_set_button_res(&vehicle_body_state, 0);
    vehicle_body_state_set_button_plus(&vehicle_body_state, 1);
    vehicle_body_state_set_button_minus(&vehicle_body_state, 0);
    vehicle_body_state_set_button_mode(&vehicle_body_state, 1);
    vehicle_body_state_set_button_io(&vehicle_body_state, 0);
    vehicle_body_state_set_button_volume_up(&vehicle_body_state, 1);
    vehicle_body_state_set_button_volume_down(&vehicle_body_state, 1);
    vehicle_body_state_set_button_voice(&vehicle_body_state, 1);

    vehicle_body_state_set_rainfall(&vehicle_body_state, 33);

    timestamp_init_from_timestamp(&read_time_stamp, vehicle_body_state_get_timestamp(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT32(timestamp_get_sec(&time_stamp), timestamp_get_sec(&read_time_stamp));
    TEST_ASSERT_EQUAL_UINT32(timestamp_get_nsec(&time_stamp), timestamp_get_nsec(&read_time_stamp));

    TEST_ASSERT_EQUAL_FLOAT(37.5f, vehicle_body_state_get_temperature(&vehicle_body_state));
    TEST_ASSERT_EQUAL_FLOAT(2.35f, vehicle_body_state_get_front_left_tire_pressure(&vehicle_body_state));
    TEST_ASSERT_EQUAL_FLOAT(1.89f, vehicle_body_state_get_front_right_tire_pressure(&vehicle_body_state));
    TEST_ASSERT_EQUAL_FLOAT(3.022f, vehicle_body_state_get_rear_left_tire_pressure(&vehicle_body_state));
    TEST_ASSERT_EQUAL_FLOAT(2.67f, vehicle_body_state_get_rear_right_tire_pressure(&vehicle_body_state));

    TEST_ASSERT_EQUAL_UINT8(1, vehicle_body_state_get_rear_fog_light(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT8(1, vehicle_body_state_get_front_fog_light(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT8(1, vehicle_body_state_get_brake_light(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT8(1, vehicle_body_state_get_high_beam(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT8(1, vehicle_body_state_get_low_beam(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT8(1, vehicle_body_state_get_hazard_flasher(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT8(1, vehicle_body_state_get_right_turn_signal(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT8(1, vehicle_body_state_get_left_turn_signal(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0xFF, vehicle_body_state_get_light_state(&vehicle_body_state));

    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_rear_right_window(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_rear_left_window(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_front_right_window(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_front_left_window(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_auto_sunroof(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_trunk_door(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_car_hood(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_rear_right_door(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_rear_left_door(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_front_right_door(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_front_left_door(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_driver_seatbelt(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_passenger_seatbelt(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_front_wiper_state(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_rear_wiper_state(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT32(0xB91FFF, vehicle_body_state_get_cockpit_state(&vehicle_body_state));

    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_button_set(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_button_res(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_button_plus(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_button_minus(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_button_mode(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_button_io(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_button_volume_up(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_button_volume_down(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_button_voice(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0x1D5, vehicle_body_state_get_button_state(&vehicle_body_state));

    TEST_ASSERT_EQUAL_UINT16(33, vehicle_body_state_get_rainfall(&vehicle_body_state));

    vehicle_body_state_set_light_state(&vehicle_body_state, 0x00);
    TEST_ASSERT_EQUAL_UINT8(0, vehicle_body_state_get_rear_fog_light(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT8(0, vehicle_body_state_get_front_fog_light(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT8(0, vehicle_body_state_get_brake_light(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT8(0, vehicle_body_state_get_high_beam(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT8(0, vehicle_body_state_get_low_beam(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT8(0, vehicle_body_state_get_hazard_flasher(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT8(0, vehicle_body_state_get_right_turn_signal(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT8(0, vehicle_body_state_get_left_turn_signal(&vehicle_body_state));

    vehicle_body_state_set_light_state(&vehicle_body_state, 0xFF);
    TEST_ASSERT_EQUAL_UINT8(1, vehicle_body_state_get_rear_fog_light(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT8(1, vehicle_body_state_get_front_fog_light(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT8(1, vehicle_body_state_get_brake_light(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT8(1, vehicle_body_state_get_high_beam(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT8(1, vehicle_body_state_get_low_beam(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT8(1, vehicle_body_state_get_hazard_flasher(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT8(1, vehicle_body_state_get_right_turn_signal(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT8(1, vehicle_body_state_get_left_turn_signal(&vehicle_body_state));

    vehicle_body_state_set_cockpit_state(&vehicle_body_state, 0x0000);
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_rear_right_window(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_rear_left_window(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_front_right_window(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_front_left_window(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_auto_sunroof(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_trunk_door(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_car_hood(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_rear_right_door(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_rear_left_door(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_front_right_door(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_front_left_door(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_driver_seatbelt(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_passenger_seatbelt(&vehicle_body_state));

    vehicle_body_state_set_cockpit_state(&vehicle_body_state, 0xB91FFF);
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_rear_right_window(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_rear_left_window(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_front_right_window(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_front_left_window(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_auto_sunroof(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_trunk_door(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_car_hood(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_rear_right_door(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_rear_left_door(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_front_right_door(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_front_left_door(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_driver_seatbelt(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_passenger_seatbelt(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_front_wiper_state(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_rear_wiper_state(&vehicle_body_state));

    vehicle_body_state_set_button_state(&vehicle_body_state, 0x2A);
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_button_set(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_button_res(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_button_plus(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_button_minus(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_button_mode(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_button_io(&vehicle_body_state));

    vehicle_body_state_set_button_state(&vehicle_body_state, 0x0F);
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_button_set(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_button_res(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_button_plus(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_button_minus(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_button_mode(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_button_io(&vehicle_body_state));

    vehicle_body_state_set_button_state(&vehicle_body_state, 0x30);
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_button_set(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_button_res(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_button_plus(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_button_minus(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_button_mode(&vehicle_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_button_io(&vehicle_body_state));
}

static void test_vehicle_body_state_serialize_and_deserialize(void)
{
    time_t                  utc_seconds;
    struct Timestamp        time_stamp;
    struct Timestamp        read_time_stamp;
    struct VehicleBodyState vehicle_body_state;
    struct VehicleBodyState deserialize_body_state;
    uint8_t                 serialize_buf[48];
    uint8_t                 serialize_error_buf[24];

    utc_seconds = time((time_t*)NULL);

    timestamp_init_from_sec(&time_stamp, utc_seconds);

    vehicle_body_state_set_timestamp(&vehicle_body_state, &time_stamp);

    vehcile_body_state_set_temperature(&vehicle_body_state, 32.3f);
    vehicle_body_state_set_front_left_tire_pressure(&vehicle_body_state, 2.35f);
    vehicle_body_state_set_front_right_tire_pressure(&vehicle_body_state, 1.89f);
    vehicle_body_state_set_rear_left_tire_pressure(&vehicle_body_state, 3.022f);
    vehicle_body_state_set_rear_right_tire_pressure(&vehicle_body_state, 2.67f);

    vehicle_body_state_set_rear_fog_light(&vehicle_body_state, 1);
    vehicle_body_state_set_front_fog_light(&vehicle_body_state, 1);
    vehicle_body_state_set_brake_light(&vehicle_body_state, 1);
    vehicle_body_state_set_high_beam(&vehicle_body_state, 1);
    vehicle_body_state_set_low_beam(&vehicle_body_state, 1);
    vehicle_body_state_set_hazard_flasher(&vehicle_body_state, 1);
    vehicle_body_state_set_right_turn_signal(&vehicle_body_state, 1);
    vehicle_body_state_set_left_turn_signal(&vehicle_body_state, 1);

    vehicle_body_state_set_rear_right_window(&vehicle_body_state, 1);
    vehicle_body_state_set_rear_left_window(&vehicle_body_state, 1);
    vehicle_body_state_set_front_right_window(&vehicle_body_state, 1);
    vehicle_body_state_set_front_left_window(&vehicle_body_state, 1);
    vehicle_body_state_set_auto_sunroof(&vehicle_body_state, 1);
    vehicle_body_state_set_trunk_door(&vehicle_body_state, 1);
    vehicle_body_state_set_car_hood(&vehicle_body_state, 1);
    vehicle_body_state_set_rear_right_door(&vehicle_body_state, 1);
    vehicle_body_state_set_rear_left_door(&vehicle_body_state, 1);
    vehicle_body_state_set_front_right_door(&vehicle_body_state, 1);
    vehicle_body_state_set_front_left_door(&vehicle_body_state, 1);
    vehicle_body_state_set_driver_seatbelt(&vehicle_body_state, 1);
    vehicle_body_state_set_passenger_seatbelt(&vehicle_body_state, 1);
    vehicle_body_state_set_front_wiper_state(&vehicle_body_state, 1);
    vehicle_body_state_set_rear_wiper_state(&vehicle_body_state, 1);

    vehicle_body_state_set_button_set(&vehicle_body_state, 1);
    vehicle_body_state_set_button_res(&vehicle_body_state, 0);
    vehicle_body_state_set_button_plus(&vehicle_body_state, 1);
    vehicle_body_state_set_button_minus(&vehicle_body_state, 0);
    vehicle_body_state_set_button_mode(&vehicle_body_state, 1);
    vehicle_body_state_set_button_io(&vehicle_body_state, 0);
    vehicle_body_state_set_button_volume_up(&vehicle_body_state, 1);
    vehicle_body_state_set_button_volume_down(&vehicle_body_state, 1);
    vehicle_body_state_set_button_voice(&vehicle_body_state, 1);

    vehicle_body_state_set_rainfall(&vehicle_body_state, 33);

    memset(serialize_error_buf, 0, sizeof(serialize_error_buf));
    TEST_ASSERT_EQUAL_INT32(
        RC_SERIALIZATION_BUFFER_OVERFLOW,
        vehicle_body_state_serialize(&vehicle_body_state, serialize_error_buf, sizeof(serialize_error_buf)));
    TEST_ASSERT_EQUAL_INT32(
        RC_DESERIALIZATION_BUFFER_UNDERFLOW,
        vehicle_body_state_deserialize(&deserialize_body_state, serialize_error_buf, sizeof(serialize_error_buf)));

    memset(serialize_buf, 0, sizeof(serialize_buf));
    TEST_ASSERT_EQUAL_INT32(vehicle_body_state_get_serialized_size(&vehicle_body_state),
                            vehicle_body_state_serialize(&vehicle_body_state, serialize_buf, sizeof(serialize_buf)));
    TEST_ASSERT_EQUAL_INT32(
        vehicle_body_state_get_serialized_size(&deserialize_body_state),
        vehicle_body_state_deserialize(&deserialize_body_state, serialize_buf, sizeof(serialize_buf)));

    timestamp_init_from_timestamp(&read_time_stamp, vehicle_body_state_get_timestamp(&deserialize_body_state));
    TEST_ASSERT_EQUAL_UINT32(timestamp_get_sec(&time_stamp), timestamp_get_sec(&read_time_stamp));
    TEST_ASSERT_EQUAL_UINT32(timestamp_get_nsec(&time_stamp), timestamp_get_nsec(&read_time_stamp));

    TEST_ASSERT_EQUAL_FLOAT(32.3f, vehicle_body_state_get_temperature(&deserialize_body_state));
    TEST_ASSERT_EQUAL_FLOAT(2.35f, vehicle_body_state_get_front_left_tire_pressure(&deserialize_body_state));
    TEST_ASSERT_EQUAL_FLOAT(1.89f, vehicle_body_state_get_front_right_tire_pressure(&deserialize_body_state));
    TEST_ASSERT_EQUAL_FLOAT(3.022f, vehicle_body_state_get_rear_left_tire_pressure(&deserialize_body_state));
    TEST_ASSERT_EQUAL_FLOAT(2.67f, vehicle_body_state_get_rear_right_tire_pressure(&deserialize_body_state));

    TEST_ASSERT_EQUAL_UINT8(1, vehicle_body_state_get_rear_fog_light(&deserialize_body_state));
    TEST_ASSERT_EQUAL_UINT8(1, vehicle_body_state_get_front_fog_light(&deserialize_body_state));
    TEST_ASSERT_EQUAL_UINT8(1, vehicle_body_state_get_brake_light(&deserialize_body_state));
    TEST_ASSERT_EQUAL_UINT8(1, vehicle_body_state_get_high_beam(&deserialize_body_state));
    TEST_ASSERT_EQUAL_UINT8(1, vehicle_body_state_get_low_beam(&deserialize_body_state));
    TEST_ASSERT_EQUAL_UINT8(1, vehicle_body_state_get_hazard_flasher(&deserialize_body_state));
    TEST_ASSERT_EQUAL_UINT8(1, vehicle_body_state_get_right_turn_signal(&deserialize_body_state));
    TEST_ASSERT_EQUAL_UINT8(1, vehicle_body_state_get_left_turn_signal(&deserialize_body_state));
    TEST_ASSERT_EQUAL_UINT16(0xFF, vehicle_body_state_get_light_state(&deserialize_body_state));

    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_rear_right_window(&deserialize_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_rear_left_window(&deserialize_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_front_right_window(&deserialize_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_front_left_window(&deserialize_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_auto_sunroof(&deserialize_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_trunk_door(&deserialize_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_car_hood(&deserialize_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_rear_right_door(&deserialize_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_rear_left_door(&deserialize_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_front_right_door(&deserialize_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_front_left_door(&deserialize_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_driver_seatbelt(&deserialize_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_passenger_seatbelt(&deserialize_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_front_wiper_state(&deserialize_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_rear_wiper_state(&deserialize_body_state));
    TEST_ASSERT_EQUAL_UINT32(0xB91FFF, vehicle_body_state_get_cockpit_state(&deserialize_body_state));

    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_button_set(&deserialize_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_button_res(&deserialize_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_button_plus(&deserialize_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_button_minus(&deserialize_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_button_mode(&deserialize_body_state));
    TEST_ASSERT_EQUAL_UINT16(0, vehicle_body_state_get_button_io(&deserialize_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_button_volume_up(&deserialize_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_button_volume_down(&deserialize_body_state));
    TEST_ASSERT_EQUAL_UINT16(1, vehicle_body_state_get_button_voice(&deserialize_body_state));
    TEST_ASSERT_EQUAL_UINT16(0x1D5, vehicle_body_state_get_button_state(&deserialize_body_state));

    TEST_ASSERT_EQUAL_UINT16(33, vehicle_body_state_get_rainfall(&deserialize_body_state));
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_vehicle_body_state_init_default);
    RUN_TEST(test_vehicle_body_state_set_and_get);
    RUN_TEST(test_vehicle_body_state_serialize_and_deserialize);

    UNITY_END();

    return 0;
}
