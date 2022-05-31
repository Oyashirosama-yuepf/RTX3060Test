/**
 * @brief Unit test for ChassisState objects.
 * @author zhangjiannan(zhangjiannan@holomaitc.com)
 * @date 2019-9-4
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#include <holo_c/common/chassis_state.h>
#include <holo_c/core/types.h>
#include <holo_c/core/retcode.h>
#include <unity.h>

/**
 * @brief Test retcode_t chassis_state_init_default(struct ChassisState* state)
 */
static void test_chassis_state_init_default(void)
{
    struct ChassisState state;
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, chassis_state_init_default(&state));

    TEST_ASSERT_EQUAL_FLOAT(0.0f, chassis_state_get_vehicle_speed(&state));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, chassis_state_get_front_left_wheel_speed(&state));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, chassis_state_get_front_right_wheel_speed(&state));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, chassis_state_get_rear_left_wheel_speed(&state));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, chassis_state_get_rear_right_wheel_speed(&state));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, chassis_state_get_longitudinal_acceleration(&state));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, chassis_state_get_lateral_acceleration(&state));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, chassis_state_get_yaw_rate(&state));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, chassis_state_get_front_wheel_angle(&state));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, chassis_state_get_longitudinal_control_value(&state));

    TEST_ASSERT_FALSE(chassis_state_is_signal_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_left_turn_signal_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_right_turn_signal_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_hazard_flasher_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_head_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_low_beam_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_high_beam_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_brake_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_fog_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_fog_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_fog_light_on(&state));
    TEST_ASSERT_EQUAL(0x0000, chassis_state_get_light_state(&state));

    TEST_ASSERT_FALSE(chassis_state_is_driver_seatbelt_locked(&state));
    TEST_ASSERT_FALSE(chassis_state_is_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_left_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_right_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_left_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_right_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_trunk_door_open(&state));

    TEST_ASSERT_FALSE(chassis_state_is_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_left_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_right_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_left_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_right_window_open(&state));

    TEST_ASSERT_FALSE(chassis_state_is_wiper_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_wiper_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_wiper_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_window_defroster_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_window_defroster_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_window_defroster_on(&state));
    TEST_ASSERT_EQUAL(0x0000, chassis_state_get_cockpit_state(&state));

    TEST_ASSERT_EQUAL_UINT8(0u, chassis_state_get_energy_source_level(&state));

    TEST_ASSERT_EQUAL_UINT8(GEAR_POSITION_UNKNOWN, chassis_state_get_gear_position(&state));
    TEST_ASSERT_EQUAL_UINT8(0u, chassis_state_get_gear_level(&state));

    TEST_ASSERT_FALSE(chassis_state_is_handbrake_hold(&state));
    TEST_ASSERT_EQUAL(0x00, chassis_state_get_gear_state(&state));

    TEST_ASSERT_FALSE(chassis_state_is_system_activated(&state));
    TEST_ASSERT_FALSE(chassis_state_is_longitudinal_activated(&state));
    TEST_ASSERT_FALSE(chassis_state_is_lateral_activated(&state));
    TEST_ASSERT_FALSE(chassis_state_is_driver_takeover(&state));
    TEST_ASSERT_FALSE(chassis_state_is_longitudinal_takeover(&state));
    TEST_ASSERT_FALSE(chassis_state_is_lateral_takeover(&state));
    TEST_ASSERT_EQUAL(0x00, chassis_state_get_user_operation_state(&state));

    TEST_ASSERT_FALSE(chassis_state_is_actuators_ready(&state));
    TEST_ASSERT_FALSE(chassis_state_is_longitudinal_actuator_ready(&state));
    TEST_ASSERT_FALSE(chassis_state_is_lateral_actuator_ready(&state));
    TEST_ASSERT_FALSE(chassis_state_is_gear_actuator_ready(&state));

    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_NOT_READY, chassis_state_get_longitudinal_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_NOT_READY, chassis_state_get_lateral_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_NOT_READY, chassis_state_get_gear_actuator_state(&state));
    TEST_ASSERT_EQUAL(0x00, chassis_state_get_actuator_state(&state));
}

static void test_chassis_state_motion_state(void)
{
    struct ChassisState state;
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, chassis_state_init_default(&state));

    chassis_state_set_vehicle_speed(&state, 1.0f);
    chassis_state_set_front_left_wheel_speed(&state, 1.0f);
    chassis_state_set_front_right_wheel_speed(&state, 1.0f);
    chassis_state_set_rear_left_wheel_speed(&state, 1.0f);
    chassis_state_set_rear_right_wheel_speed(&state, 1.0f);
    chassis_state_set_longitudinal_acceleration(&state, 1.0f);
    chassis_state_set_lateral_acceleration(&state, 1.0f);
    chassis_state_set_yaw_rate(&state, 1.0f);
    chassis_state_set_front_wheel_angle(&state, 1.0f);
    chassis_state_set_longitudinal_control_value(&state, 1.0f);

    TEST_ASSERT_EQUAL_FLOAT(1.0f, chassis_state_get_vehicle_speed(&state));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, chassis_state_get_front_left_wheel_speed(&state));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, chassis_state_get_front_right_wheel_speed(&state));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, chassis_state_get_rear_left_wheel_speed(&state));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, chassis_state_get_rear_right_wheel_speed(&state));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, chassis_state_get_longitudinal_acceleration(&state));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, chassis_state_get_lateral_acceleration(&state));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, chassis_state_get_yaw_rate(&state));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, chassis_state_get_front_wheel_angle(&state));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, chassis_state_get_longitudinal_control_value(&state));
}

static void test_chassis_state_light_state(void)
{
    struct ChassisState state;
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, chassis_state_init_default(&state));

    TEST_ASSERT_FALSE(chassis_state_is_signal_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_left_turn_signal_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_right_turn_signal_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_hazard_flasher_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_head_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_low_beam_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_high_beam_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_brake_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_fog_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_fog_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_fog_light_on(&state));

    chassis_state_set_left_turn_signal(&state, true);
    TEST_ASSERT_TRUE(chassis_state_is_signal_light_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_left_turn_signal_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_right_turn_signal_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_hazard_flasher_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_brake_light_on(&state));
    TEST_ASSERT_EQUAL(0x0080, chassis_state_get_light_state(&state));

    chassis_state_set_light_state(&state, 0x0080);
    TEST_ASSERT_TRUE(chassis_state_is_signal_light_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_left_turn_signal_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_right_turn_signal_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_hazard_flasher_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_brake_light_on(&state));

    chassis_state_set_left_turn_signal(&state, false);
    chassis_state_set_right_turn_signal(&state, true);
    TEST_ASSERT_TRUE(chassis_state_is_signal_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_left_turn_signal_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_right_turn_signal_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_hazard_flasher_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_brake_light_on(&state));
    TEST_ASSERT_EQUAL(0x0040, chassis_state_get_light_state(&state));

    chassis_state_set_light_state(&state, 0x0040);
    TEST_ASSERT_TRUE(chassis_state_is_signal_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_left_turn_signal_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_right_turn_signal_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_hazard_flasher_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_brake_light_on(&state));

    chassis_state_set_right_turn_signal(&state, false);
    chassis_state_set_hazard_flasher(&state, true);
    TEST_ASSERT_TRUE(chassis_state_is_signal_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_left_turn_signal_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_right_turn_signal_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_hazard_flasher_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_brake_light_on(&state));
    TEST_ASSERT_EQUAL(0x0020, chassis_state_get_light_state(&state));

    chassis_state_set_light_state(&state, 0x0020);
    TEST_ASSERT_TRUE(chassis_state_is_signal_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_left_turn_signal_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_right_turn_signal_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_hazard_flasher_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_brake_light_on(&state));

    chassis_state_set_hazard_flasher(&state, false);
    chassis_state_set_brake_light(&state, true);
    TEST_ASSERT_TRUE(chassis_state_is_signal_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_left_turn_signal_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_right_turn_signal_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_hazard_flasher_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_brake_light_on(&state));
    TEST_ASSERT_EQUAL(0x0004, chassis_state_get_light_state(&state));

    chassis_state_set_light_state(&state, 0x0004);
    TEST_ASSERT_TRUE(chassis_state_is_signal_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_left_turn_signal_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_right_turn_signal_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_hazard_flasher_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_brake_light_on(&state));
    
    chassis_state_set_brake_light(&state, false);
    TEST_ASSERT_FALSE(chassis_state_is_signal_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_left_turn_signal_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_right_turn_signal_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_hazard_flasher_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_brake_light_on(&state));
    TEST_ASSERT_EQUAL(0x0000, chassis_state_get_light_state(&state));

    chassis_state_set_signal_light_state(&state, true, true, true, true);
    TEST_ASSERT_TRUE(chassis_state_is_signal_light_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_left_turn_signal_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_right_turn_signal_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_hazard_flasher_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_brake_light_on(&state));
    TEST_ASSERT_EQUAL(0x00e4, chassis_state_get_light_state(&state));

    chassis_state_set_light_state(&state, 0x00e4);
    TEST_ASSERT_TRUE(chassis_state_is_signal_light_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_left_turn_signal_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_right_turn_signal_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_hazard_flasher_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_brake_light_on(&state));

    chassis_state_set_signal_light_state(&state, false, false, false, false);
    TEST_ASSERT_FALSE(chassis_state_is_signal_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_left_turn_signal_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_right_turn_signal_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_hazard_flasher_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_brake_light_on(&state));
    TEST_ASSERT_EQUAL(0x0000, chassis_state_get_light_state(&state));

    chassis_state_set_light_state(&state, 0x0000);
    TEST_ASSERT_FALSE(chassis_state_is_signal_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_left_turn_signal_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_right_turn_signal_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_hazard_flasher_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_brake_light_on(&state));

    chassis_state_set_low_beam(&state, true);
    TEST_ASSERT_TRUE(chassis_state_is_head_light_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_low_beam_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_high_beam_on(&state));
    TEST_ASSERT_EQUAL(0x0010, chassis_state_get_light_state(&state));

    chassis_state_set_light_state(&state, 0x0010);
    TEST_ASSERT_TRUE(chassis_state_is_head_light_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_low_beam_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_high_beam_on(&state));

    chassis_state_set_low_beam(&state, false);
    chassis_state_set_high_beam(&state, true);
    TEST_ASSERT_TRUE(chassis_state_is_head_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_low_beam_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_high_beam_on(&state));
    TEST_ASSERT_EQUAL(0x0008, chassis_state_get_light_state(&state));

    chassis_state_set_light_state(&state, 0x0008);
    TEST_ASSERT_TRUE(chassis_state_is_head_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_low_beam_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_high_beam_on(&state));

    chassis_state_set_high_beam(&state, false);
    TEST_ASSERT_FALSE(chassis_state_is_head_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_low_beam_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_high_beam_on(&state));
    TEST_ASSERT_EQUAL(0x0000, chassis_state_get_light_state(&state));

    chassis_state_set_light_state(&state, 0x0000);
    TEST_ASSERT_FALSE(chassis_state_is_head_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_low_beam_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_high_beam_on(&state));

    chassis_state_set_front_fog_light(&state, true);
    TEST_ASSERT_TRUE(chassis_state_is_fog_light_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_front_fog_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_fog_light_on(&state));
    TEST_ASSERT_EQUAL(0x0002, chassis_state_get_light_state(&state));

    chassis_state_set_light_state(&state, 0x0002);
    TEST_ASSERT_TRUE(chassis_state_is_fog_light_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_front_fog_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_fog_light_on(&state));

    chassis_state_set_front_fog_light(&state, false);
    chassis_state_set_rear_fog_light(&state, true);
    TEST_ASSERT_TRUE(chassis_state_is_fog_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_fog_light_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_rear_fog_light_on(&state));
    TEST_ASSERT_EQUAL(0x0001, chassis_state_get_light_state(&state));

    chassis_state_set_light_state(&state, 0x0001);
    TEST_ASSERT_TRUE(chassis_state_is_fog_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_fog_light_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_rear_fog_light_on(&state));

    chassis_state_set_rear_fog_light(&state, false);
    TEST_ASSERT_FALSE(chassis_state_is_fog_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_fog_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_fog_light_on(&state));
    TEST_ASSERT_EQUAL(0x0000, chassis_state_get_light_state(&state));

    chassis_state_set_light_state(&state, 0x0000);
    TEST_ASSERT_FALSE(chassis_state_is_fog_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_fog_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_fog_light_on(&state));
}

static void test_chassis_state_door_seatbelt_state(void)
{
    struct ChassisState state;
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, chassis_state_init_default(&state));

    TEST_ASSERT_FALSE(chassis_state_is_driver_seatbelt_locked(&state));
    TEST_ASSERT_FALSE(chassis_state_is_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_left_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_right_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_left_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_right_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_trunk_door_open(&state));
    TEST_ASSERT_EQUAL(0x0000, chassis_state_get_cockpit_state(&state));

    chassis_state_set_driver_seatbelt(&state, true);
    TEST_ASSERT_TRUE(chassis_state_is_driver_seatbelt_locked(&state));
    TEST_ASSERT_EQUAL(0x2000, chassis_state_get_cockpit_state(&state));
    chassis_state_set_cockpit_state(&state, 0x2000);
    TEST_ASSERT_TRUE(chassis_state_is_driver_seatbelt_locked(&state));
    chassis_state_set_driver_seatbelt(&state, false);
    TEST_ASSERT_FALSE(chassis_state_is_driver_seatbelt_locked(&state));
    TEST_ASSERT_EQUAL(0x0000, chassis_state_get_cockpit_state(&state));
    chassis_state_set_cockpit_state(&state, 0x0000);
    TEST_ASSERT_FALSE(chassis_state_is_driver_seatbelt_locked(&state));

    chassis_state_set_front_left_door(&state, true);
    TEST_ASSERT_TRUE(chassis_state_is_door_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_front_left_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_right_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_left_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_right_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_trunk_door_open(&state));
    TEST_ASSERT_EQUAL(0x1000, chassis_state_get_cockpit_state(&state));

    chassis_state_set_cockpit_state(&state, 0x1000);
    TEST_ASSERT_TRUE(chassis_state_is_door_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_front_left_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_right_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_left_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_right_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_trunk_door_open(&state));
    
    chassis_state_set_front_left_door(&state, false);
    chassis_state_set_front_right_door(&state, true);
    TEST_ASSERT_TRUE(chassis_state_is_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_left_door_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_front_right_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_left_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_right_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_trunk_door_open(&state));
    TEST_ASSERT_EQUAL(0x0800, chassis_state_get_cockpit_state(&state));

    chassis_state_set_cockpit_state(&state, 0x0800);
    TEST_ASSERT_TRUE(chassis_state_is_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_left_door_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_front_right_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_left_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_right_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_trunk_door_open(&state));
    
    chassis_state_set_front_right_door(&state, false);
    chassis_state_set_rear_left_door(&state, true);
    TEST_ASSERT_TRUE(chassis_state_is_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_left_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_right_door_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_rear_left_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_right_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_trunk_door_open(&state));
    TEST_ASSERT_EQUAL(0x0400, chassis_state_get_cockpit_state(&state));

    chassis_state_set_cockpit_state(&state, 0x0400);
    TEST_ASSERT_TRUE(chassis_state_is_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_left_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_right_door_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_rear_left_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_right_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_trunk_door_open(&state));
    
    chassis_state_set_rear_left_door(&state, false);
    chassis_state_set_rear_right_door(&state, true);
    TEST_ASSERT_TRUE(chassis_state_is_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_left_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_right_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_left_door_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_rear_right_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_trunk_door_open(&state));
    TEST_ASSERT_EQUAL(0x0200, chassis_state_get_cockpit_state(&state));

    chassis_state_set_cockpit_state(&state, 0x0200);
    TEST_ASSERT_TRUE(chassis_state_is_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_left_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_right_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_left_door_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_rear_right_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_trunk_door_open(&state));

    chassis_state_set_rear_right_door(&state, false);
    chassis_state_set_trunk_door(&state, true);
    TEST_ASSERT_TRUE(chassis_state_is_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_left_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_right_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_left_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_right_door_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_trunk_door_open(&state));
    TEST_ASSERT_EQUAL(0x0100, chassis_state_get_cockpit_state(&state));

    chassis_state_set_cockpit_state(&state, 0x0100);
    TEST_ASSERT_TRUE(chassis_state_is_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_left_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_right_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_left_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_right_door_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_trunk_door_open(&state));

    chassis_state_set_trunk_door(&state, false);
    TEST_ASSERT_FALSE(chassis_state_is_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_left_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_right_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_left_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_right_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_trunk_door_open(&state));
    TEST_ASSERT_EQUAL(0x0000, chassis_state_get_cockpit_state(&state));

    chassis_state_set_cockpit_state(&state, 0x0000);
    TEST_ASSERT_FALSE(chassis_state_is_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_left_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_right_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_left_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_right_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_trunk_door_open(&state));

    chassis_state_set_door_state(&state, true, true, true, true, true);
    TEST_ASSERT_TRUE(chassis_state_is_door_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_front_left_door_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_front_right_door_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_rear_left_door_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_rear_right_door_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_trunk_door_open(&state));
    TEST_ASSERT_EQUAL(0x1f00, chassis_state_get_cockpit_state(&state));

    chassis_state_set_cockpit_state(&state, 0x1f00);
    TEST_ASSERT_TRUE(chassis_state_is_door_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_front_left_door_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_front_right_door_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_rear_left_door_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_rear_right_door_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_trunk_door_open(&state));

    chassis_state_set_door_state(&state, false, false, false, false, false);
    TEST_ASSERT_FALSE(chassis_state_is_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_left_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_right_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_left_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_right_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_trunk_door_open(&state));
    TEST_ASSERT_EQUAL(0x0000, chassis_state_get_cockpit_state(&state));

    chassis_state_set_cockpit_state(&state, 0x0000);
    TEST_ASSERT_FALSE(chassis_state_is_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_left_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_right_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_left_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_right_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_trunk_door_open(&state));
}

static void test_chassis_state_window_state(void)
{
    struct ChassisState state;
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, chassis_state_init_default(&state));

    TEST_ASSERT_FALSE(chassis_state_is_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_left_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_right_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_left_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_right_window_open(&state));
    TEST_ASSERT_EQUAL(0x0000, chassis_state_get_cockpit_state(&state));

    chassis_state_set_front_left_window(&state, true);
    TEST_ASSERT_TRUE(chassis_state_is_window_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_front_left_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_right_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_left_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_right_window_open(&state));
    TEST_ASSERT_EQUAL(0x0080, chassis_state_get_cockpit_state(&state));

    chassis_state_set_cockpit_state(&state, 0x0080);
    TEST_ASSERT_TRUE(chassis_state_is_window_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_front_left_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_right_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_left_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_right_window_open(&state));
    
    chassis_state_set_front_left_window(&state, false);
    chassis_state_set_front_right_window(&state, true);
    TEST_ASSERT_TRUE(chassis_state_is_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_left_window_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_front_right_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_left_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_right_window_open(&state));
    TEST_ASSERT_EQUAL(0x0040, chassis_state_get_cockpit_state(&state));

    chassis_state_set_cockpit_state(&state, 0x0040);
    TEST_ASSERT_TRUE(chassis_state_is_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_left_window_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_front_right_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_left_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_right_window_open(&state));
    
    chassis_state_set_front_right_window(&state, false);
    chassis_state_set_rear_left_window(&state, true);
    TEST_ASSERT_TRUE(chassis_state_is_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_left_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_right_window_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_rear_left_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_right_window_open(&state));
    TEST_ASSERT_EQUAL(0x0020, chassis_state_get_cockpit_state(&state));

    chassis_state_set_cockpit_state(&state, 0x0020);
    TEST_ASSERT_TRUE(chassis_state_is_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_left_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_right_window_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_rear_left_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_right_window_open(&state));
    
    chassis_state_set_rear_left_window(&state, false);
    chassis_state_set_rear_right_window(&state, true);
    TEST_ASSERT_TRUE(chassis_state_is_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_left_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_right_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_left_window_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_rear_right_window_open(&state));
    TEST_ASSERT_EQUAL(0x0010, chassis_state_get_cockpit_state(&state));

    chassis_state_set_cockpit_state(&state, 0x0010);
    TEST_ASSERT_TRUE(chassis_state_is_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_left_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_right_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_left_window_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_rear_right_window_open(&state));

    chassis_state_set_rear_right_window(&state, false);
    TEST_ASSERT_FALSE(chassis_state_is_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_left_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_right_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_left_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_right_window_open(&state));
    TEST_ASSERT_EQUAL(0x0000, chassis_state_get_cockpit_state(&state));

    chassis_state_set_cockpit_state(&state, 0x0000);
    TEST_ASSERT_FALSE(chassis_state_is_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_left_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_right_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_left_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_right_window_open(&state));

    chassis_state_set_window_state(&state, true, true, true, true);
    TEST_ASSERT_TRUE(chassis_state_is_window_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_front_left_window_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_front_right_window_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_rear_left_window_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_rear_right_window_open(&state));
    TEST_ASSERT_EQUAL(0x00f0, chassis_state_get_cockpit_state(&state));

    chassis_state_set_cockpit_state(&state, 0x00f0);
    TEST_ASSERT_TRUE(chassis_state_is_window_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_front_left_window_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_front_right_window_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_rear_left_window_open(&state));
    TEST_ASSERT_TRUE(chassis_state_is_rear_right_window_open(&state));

    chassis_state_set_window_state(&state, false, false, false, false);
    TEST_ASSERT_FALSE(chassis_state_is_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_left_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_right_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_left_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_right_window_open(&state));
    TEST_ASSERT_EQUAL(0x0000, chassis_state_get_cockpit_state(&state));

    chassis_state_set_cockpit_state(&state, 0x0000);
    TEST_ASSERT_FALSE(chassis_state_is_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_left_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_right_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_left_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_right_window_open(&state));
}

static void test_chassis_state_wiper_and_defroster_state(void)
{
    struct ChassisState state;
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, chassis_state_init_default(&state));

    TEST_ASSERT_FALSE(chassis_state_is_wiper_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_wiper_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_wiper_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_window_defroster_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_window_defroster_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_window_defroster_on(&state));
    TEST_ASSERT_EQUAL(0x0000, chassis_state_get_cockpit_state(&state));

    chassis_state_set_front_wiper(&state, true);
    TEST_ASSERT_TRUE(chassis_state_is_wiper_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_front_wiper_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_wiper_on(&state));
    TEST_ASSERT_EQUAL(0x0008, chassis_state_get_cockpit_state(&state));

    chassis_state_set_cockpit_state(&state, 0x0008);
    TEST_ASSERT_TRUE(chassis_state_is_wiper_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_front_wiper_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_wiper_on(&state));

    chassis_state_set_front_wiper(&state, false);
    chassis_state_set_rear_wiper(&state, true);
    TEST_ASSERT_TRUE(chassis_state_is_wiper_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_wiper_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_rear_wiper_on(&state));
    TEST_ASSERT_EQUAL(0x0004, chassis_state_get_cockpit_state(&state));

    chassis_state_set_cockpit_state(&state, 0x0004);
    TEST_ASSERT_TRUE(chassis_state_is_wiper_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_wiper_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_rear_wiper_on(&state));

    chassis_state_set_rear_wiper(&state, false);
    TEST_ASSERT_FALSE(chassis_state_is_wiper_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_wiper_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_wiper_on(&state));
    TEST_ASSERT_EQUAL(0x0000, chassis_state_get_cockpit_state(&state));

    chassis_state_set_cockpit_state(&state, 0x0000);
    TEST_ASSERT_FALSE(chassis_state_is_wiper_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_wiper_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_wiper_on(&state));

    chassis_state_set_wiper_state(&state, true, true);
    TEST_ASSERT_TRUE(chassis_state_is_wiper_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_front_wiper_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_rear_wiper_on(&state));
    TEST_ASSERT_EQUAL(0x000c, chassis_state_get_cockpit_state(&state));

    chassis_state_set_cockpit_state(&state, 0x000c);
    TEST_ASSERT_TRUE(chassis_state_is_wiper_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_front_wiper_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_rear_wiper_on(&state));

    chassis_state_set_wiper_state(&state, false, false);
    TEST_ASSERT_FALSE(chassis_state_is_wiper_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_wiper_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_wiper_on(&state));
    TEST_ASSERT_EQUAL(0x0000, chassis_state_get_cockpit_state(&state));

    chassis_state_set_cockpit_state(&state, 0x0000);
    TEST_ASSERT_FALSE(chassis_state_is_wiper_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_wiper_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_wiper_on(&state));

    chassis_state_set_front_window_defroster(&state, true);
    TEST_ASSERT_TRUE(chassis_state_is_window_defroster_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_front_window_defroster_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_window_defroster_on(&state));
    TEST_ASSERT_EQUAL(0x0002, chassis_state_get_cockpit_state(&state));

    chassis_state_set_cockpit_state(&state, 0x0002);
    TEST_ASSERT_TRUE(chassis_state_is_window_defroster_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_front_window_defroster_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_window_defroster_on(&state));

    chassis_state_set_front_window_defroster(&state, false);
    chassis_state_set_rear_window_defroster(&state, true);
    TEST_ASSERT_TRUE(chassis_state_is_window_defroster_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_window_defroster_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_rear_window_defroster_on(&state));
    TEST_ASSERT_EQUAL(0x0001, chassis_state_get_cockpit_state(&state));

    chassis_state_set_cockpit_state(&state, 0x0001);
    TEST_ASSERT_TRUE(chassis_state_is_window_defroster_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_window_defroster_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_rear_window_defroster_on(&state));

    chassis_state_set_rear_window_defroster(&state, false);
    TEST_ASSERT_FALSE(chassis_state_is_window_defroster_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_window_defroster_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_window_defroster_on(&state));
    TEST_ASSERT_EQUAL(0x0000, chassis_state_get_cockpit_state(&state));

    chassis_state_set_cockpit_state(&state, 0x0000);
    TEST_ASSERT_FALSE(chassis_state_is_window_defroster_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_window_defroster_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_window_defroster_on(&state));

    chassis_state_set_window_defroster_state(&state, true, true);
    TEST_ASSERT_TRUE(chassis_state_is_window_defroster_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_front_window_defroster_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_rear_window_defroster_on(&state));
    TEST_ASSERT_EQUAL(0x0003, chassis_state_get_cockpit_state(&state));

    chassis_state_set_cockpit_state(&state, 0x0003);
    TEST_ASSERT_TRUE(chassis_state_is_window_defroster_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_front_window_defroster_on(&state));
    TEST_ASSERT_TRUE(chassis_state_is_rear_window_defroster_on(&state));

    chassis_state_set_window_defroster_state(&state, false, false);
    TEST_ASSERT_FALSE(chassis_state_is_window_defroster_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_window_defroster_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_window_defroster_on(&state));
    TEST_ASSERT_EQUAL(0x0000, chassis_state_get_cockpit_state(&state));

    chassis_state_set_cockpit_state(&state, 0x0000);
    TEST_ASSERT_FALSE(chassis_state_is_window_defroster_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_window_defroster_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_window_defroster_on(&state));
}

static void test_chassis_state_energy_source_level(void)
{
    struct ChassisState state;
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, chassis_state_init_default(&state));

    TEST_ASSERT_EQUAL_UINT8(0U, chassis_state_get_energy_source_level(&state));

    chassis_state_set_energy_source_level(&state, 10U);
    TEST_ASSERT_EQUAL_UINT8(10U, chassis_state_get_energy_source_level(&state));

    chassis_state_set_energy_source_level(&state, 100U);
    TEST_ASSERT_EQUAL_UINT8(100U, chassis_state_get_energy_source_level(&state));

    chassis_state_set_energy_source_level(&state, 101U);
    TEST_ASSERT_EQUAL_UINT8(100U, chassis_state_get_energy_source_level(&state));

    chassis_state_set_energy_source_level(&state, 255U);
    TEST_ASSERT_EQUAL_UINT8(100U, chassis_state_get_energy_source_level(&state));
}

static void test_chassis_state_gear_and_handbrake(void)
{
    struct ChassisState state;
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, chassis_state_init_default(&state));

    TEST_ASSERT_EQUAL_UINT8(GEAR_POSITION_UNKNOWN, chassis_state_get_gear_position(&state));
    TEST_ASSERT_EQUAL_UINT8(0u, chassis_state_get_gear_level(&state));
    TEST_ASSERT_FALSE(chassis_state_is_handbrake_hold(&state));
    TEST_ASSERT_EQUAL(0x00, chassis_state_get_gear_state(&state));

    chassis_state_set_gear_position(&state, GEAR_POSITION_P);
    TEST_ASSERT_EQUAL_UINT8(GEAR_POSITION_P, chassis_state_get_gear_position(&state));
    TEST_ASSERT_EQUAL_UINT8(0u, chassis_state_get_gear_level(&state));
    TEST_ASSERT_EQUAL(0x20, chassis_state_get_gear_state(&state));
    chassis_state_set_gear_state(&state, 0x20);
    TEST_ASSERT_EQUAL_UINT8(GEAR_POSITION_P, chassis_state_get_gear_position(&state));
    TEST_ASSERT_EQUAL_UINT8(0u, chassis_state_get_gear_level(&state));

    chassis_state_set_gear_position(&state, GEAR_POSITION_R);
    TEST_ASSERT_EQUAL_UINT8(GEAR_POSITION_R, chassis_state_get_gear_position(&state));
    TEST_ASSERT_EQUAL_UINT8(0u, chassis_state_get_gear_level(&state));
    TEST_ASSERT_EQUAL(0x40, chassis_state_get_gear_state(&state));
    chassis_state_set_gear_state(&state, 0x40);
    TEST_ASSERT_EQUAL_UINT8(GEAR_POSITION_R, chassis_state_get_gear_position(&state));
    TEST_ASSERT_EQUAL_UINT8(0u, chassis_state_get_gear_level(&state));

    chassis_state_set_gear_position(&state, GEAR_POSITION_N);
    TEST_ASSERT_EQUAL_UINT8(GEAR_POSITION_N, chassis_state_get_gear_position(&state));
    TEST_ASSERT_EQUAL_UINT8(0u, chassis_state_get_gear_level(&state));
    TEST_ASSERT_EQUAL(0x60, chassis_state_get_gear_state(&state));
    chassis_state_set_gear_state(&state, 0x60);
    TEST_ASSERT_EQUAL_UINT8(GEAR_POSITION_N, chassis_state_get_gear_position(&state));
    TEST_ASSERT_EQUAL_UINT8(0u, chassis_state_get_gear_level(&state));
    
    chassis_state_set_gear_position(&state, GEAR_POSITION_D);
    TEST_ASSERT_EQUAL_UINT8(GEAR_POSITION_D, chassis_state_get_gear_position(&state));
    TEST_ASSERT_EQUAL_UINT8(0u, chassis_state_get_gear_level(&state));
    TEST_ASSERT_EQUAL(0x80, chassis_state_get_gear_state(&state));
    chassis_state_set_gear_state(&state, 0x80);
    TEST_ASSERT_EQUAL_UINT8(GEAR_POSITION_D, chassis_state_get_gear_position(&state));
    TEST_ASSERT_EQUAL_UINT8(0u, chassis_state_get_gear_level(&state));

    chassis_state_set_gear_position(&state, GEAR_POSITION_S);
    TEST_ASSERT_EQUAL_UINT8(GEAR_POSITION_S, chassis_state_get_gear_position(&state));
    TEST_ASSERT_EQUAL_UINT8(0u, chassis_state_get_gear_level(&state));
    TEST_ASSERT_EQUAL(0xa0, chassis_state_get_gear_state(&state));
    chassis_state_set_gear_state(&state, 0xa0);
    TEST_ASSERT_EQUAL_UINT8(GEAR_POSITION_S, chassis_state_get_gear_position(&state));
    TEST_ASSERT_EQUAL_UINT8(0u, chassis_state_get_gear_level(&state));

    chassis_state_set_gear_level(&state, 1U);
    TEST_ASSERT_EQUAL_UINT8(1U, chassis_state_get_gear_level(&state));
    TEST_ASSERT_EQUAL(0xa2, chassis_state_get_gear_state(&state));
    chassis_state_set_gear_state(&state, 0xa2);
    TEST_ASSERT_EQUAL_UINT8(1U, chassis_state_get_gear_level(&state));

    chassis_state_set_gear_level(&state, 15U);
    TEST_ASSERT_EQUAL_UINT8(15U, chassis_state_get_gear_level(&state));
    TEST_ASSERT_EQUAL(0xbe, chassis_state_get_gear_state(&state));
    chassis_state_set_gear_state(&state, 0xbe);
    TEST_ASSERT_EQUAL_UINT8(15U, chassis_state_get_gear_level(&state));

    chassis_state_set_gear_level(&state, 16U);
    TEST_ASSERT_EQUAL_UINT8(15U, chassis_state_get_gear_level(&state));
    chassis_state_set_gear_level(&state, 16U);
    TEST_ASSERT_EQUAL_UINT8(15U, chassis_state_get_gear_level(&state));

    chassis_state_set_handbrake(&state, true);
    TEST_ASSERT_TRUE(chassis_state_is_handbrake_hold(&state));
    TEST_ASSERT_EQUAL(0xbf, chassis_state_get_gear_state(&state));
    chassis_state_set_gear_state(&state, 0xbf);
    TEST_ASSERT_TRUE(chassis_state_is_handbrake_hold(&state));

    chassis_state_set_handbrake(&state, false);
    TEST_ASSERT_FALSE(chassis_state_is_handbrake_hold(&state));
    TEST_ASSERT_EQUAL(0xbe, chassis_state_get_gear_state(&state));
    chassis_state_set_gear_state(&state, 0xbe);
    TEST_ASSERT_FALSE(chassis_state_is_handbrake_hold(&state));
}

static void test_chassis_state_user_activity(void)
{
    struct ChassisState state;
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, chassis_state_init_default(&state));

    TEST_ASSERT_FALSE(chassis_state_is_system_activated(&state));
    TEST_ASSERT_FALSE(chassis_state_is_longitudinal_activated(&state));
    TEST_ASSERT_FALSE(chassis_state_is_lateral_activated(&state));
    TEST_ASSERT_FALSE(chassis_state_is_driver_takeover(&state));
    TEST_ASSERT_FALSE(chassis_state_is_longitudinal_takeover(&state));
    TEST_ASSERT_FALSE(chassis_state_is_lateral_takeover(&state));
    TEST_ASSERT_EQUAL(0x00, chassis_state_get_user_operation_state(&state));

    chassis_state_set_longitudinal_activated(&state, true);
    TEST_ASSERT_TRUE(chassis_state_is_system_activated(&state));
    TEST_ASSERT_TRUE(chassis_state_is_longitudinal_activated(&state));
    TEST_ASSERT_FALSE(chassis_state_is_lateral_activated(&state));
    TEST_ASSERT_EQUAL(0x08, chassis_state_get_user_operation_state(&state));
    chassis_state_set_user_operation_state(&state, 0x08);
    TEST_ASSERT_TRUE(chassis_state_is_system_activated(&state));
    TEST_ASSERT_TRUE(chassis_state_is_longitudinal_activated(&state));
    TEST_ASSERT_FALSE(chassis_state_is_lateral_activated(&state));

    chassis_state_set_longitudinal_activated(&state, false);
    chassis_state_set_lateral_activated(&state, true);
    TEST_ASSERT_TRUE(chassis_state_is_system_activated(&state));
    TEST_ASSERT_FALSE(chassis_state_is_longitudinal_activated(&state));
    TEST_ASSERT_TRUE(chassis_state_is_lateral_activated(&state));
    TEST_ASSERT_EQUAL(0x04, chassis_state_get_user_operation_state(&state));
    chassis_state_set_user_operation_state(&state, 0x04);
    TEST_ASSERT_TRUE(chassis_state_is_system_activated(&state));
    TEST_ASSERT_FALSE(chassis_state_is_longitudinal_activated(&state));
    TEST_ASSERT_TRUE(chassis_state_is_lateral_activated(&state));

    chassis_state_set_lateral_activated(&state, false);
    TEST_ASSERT_FALSE(chassis_state_is_system_activated(&state));
    TEST_ASSERT_FALSE(chassis_state_is_longitudinal_activated(&state));
    TEST_ASSERT_FALSE(chassis_state_is_lateral_activated(&state));
    TEST_ASSERT_EQUAL(0x00, chassis_state_get_user_operation_state(&state));
    chassis_state_set_user_operation_state(&state, 0x00);
    TEST_ASSERT_FALSE(chassis_state_is_system_activated(&state));
    TEST_ASSERT_FALSE(chassis_state_is_longitudinal_activated(&state));
    TEST_ASSERT_FALSE(chassis_state_is_lateral_activated(&state));

    chassis_state_set_longitudinal_takeover(&state, true);
    TEST_ASSERT_TRUE(chassis_state_is_driver_takeover(&state));
    TEST_ASSERT_TRUE(chassis_state_is_longitudinal_takeover(&state));
    TEST_ASSERT_FALSE(chassis_state_is_lateral_takeover(&state));
    TEST_ASSERT_EQUAL(0x02, chassis_state_get_user_operation_state(&state));
    chassis_state_set_user_operation_state(&state, 0x02);
    TEST_ASSERT_TRUE(chassis_state_is_driver_takeover(&state));
    TEST_ASSERT_TRUE(chassis_state_is_longitudinal_takeover(&state));
    TEST_ASSERT_FALSE(chassis_state_is_lateral_takeover(&state));

    chassis_state_set_longitudinal_takeover(&state, false);
    chassis_state_set_lateral_takeover(&state, true);
    TEST_ASSERT_TRUE(chassis_state_is_driver_takeover(&state));
    TEST_ASSERT_FALSE(chassis_state_is_longitudinal_takeover(&state));
    TEST_ASSERT_TRUE(chassis_state_is_lateral_takeover(&state));
    TEST_ASSERT_EQUAL(0x01, chassis_state_get_user_operation_state(&state));
    chassis_state_set_user_operation_state(&state, 0x01);
    TEST_ASSERT_TRUE(chassis_state_is_driver_takeover(&state));
    TEST_ASSERT_FALSE(chassis_state_is_longitudinal_takeover(&state));
    TEST_ASSERT_TRUE(chassis_state_is_lateral_takeover(&state));

    chassis_state_set_lateral_takeover(&state, false);
    TEST_ASSERT_FALSE(chassis_state_is_driver_takeover(&state));
    TEST_ASSERT_FALSE(chassis_state_is_longitudinal_takeover(&state));
    TEST_ASSERT_FALSE(chassis_state_is_lateral_takeover(&state));
    TEST_ASSERT_EQUAL(0x00, chassis_state_get_user_operation_state(&state));
    chassis_state_set_user_operation_state(&state, 0x00);
    TEST_ASSERT_FALSE(chassis_state_is_driver_takeover(&state));
    TEST_ASSERT_FALSE(chassis_state_is_longitudinal_takeover(&state));
    TEST_ASSERT_FALSE(chassis_state_is_lateral_takeover(&state));
}

static void test_chassis_state_actuator_state(void)
{
    struct ChassisState state;
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, chassis_state_init_default(&state));

    TEST_ASSERT_FALSE(chassis_state_is_actuators_ready(&state));
    TEST_ASSERT_FALSE(chassis_state_is_longitudinal_actuator_ready(&state));
    TEST_ASSERT_FALSE(chassis_state_is_lateral_actuator_ready(&state));
    TEST_ASSERT_FALSE(chassis_state_is_gear_actuator_ready(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_NOT_READY, chassis_state_get_longitudinal_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_NOT_READY, chassis_state_get_lateral_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_NOT_READY, chassis_state_get_gear_actuator_state(&state));
    TEST_ASSERT_EQUAL(0x00, chassis_state_get_actuator_state(&state));

    chassis_state_set_longitudinal_actuator_state(&state, ACTUATOR_STATE_READY);
    TEST_ASSERT_FALSE(chassis_state_is_actuators_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_longitudinal_actuator_ready(&state));
    TEST_ASSERT_FALSE(chassis_state_is_lateral_actuator_ready(&state));
    TEST_ASSERT_FALSE(chassis_state_is_gear_actuator_ready(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_READY, chassis_state_get_longitudinal_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_NOT_READY, chassis_state_get_lateral_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_NOT_READY, chassis_state_get_gear_actuator_state(&state));
    TEST_ASSERT_EQUAL(0x10, chassis_state_get_actuator_state(&state));
    chassis_state_set_actuator_state(&state, 0x10);
    TEST_ASSERT_FALSE(chassis_state_is_actuators_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_longitudinal_actuator_ready(&state));
    TEST_ASSERT_FALSE(chassis_state_is_lateral_actuator_ready(&state));
    TEST_ASSERT_FALSE(chassis_state_is_gear_actuator_ready(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_READY, chassis_state_get_longitudinal_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_NOT_READY, chassis_state_get_lateral_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_NOT_READY, chassis_state_get_gear_actuator_state(&state));

    chassis_state_set_lateral_actuator_state(&state, ACTUATOR_STATE_READY);
    TEST_ASSERT_FALSE(chassis_state_is_actuators_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_longitudinal_actuator_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_lateral_actuator_ready(&state));
    TEST_ASSERT_FALSE(chassis_state_is_gear_actuator_ready(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_READY, chassis_state_get_longitudinal_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_READY, chassis_state_get_lateral_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_NOT_READY, chassis_state_get_gear_actuator_state(&state));
    TEST_ASSERT_EQUAL(0x14, chassis_state_get_actuator_state(&state));
    chassis_state_set_actuator_state(&state, 0x14);
    TEST_ASSERT_FALSE(chassis_state_is_actuators_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_longitudinal_actuator_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_lateral_actuator_ready(&state));
    TEST_ASSERT_FALSE(chassis_state_is_gear_actuator_ready(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_READY, chassis_state_get_longitudinal_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_READY, chassis_state_get_lateral_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_NOT_READY, chassis_state_get_gear_actuator_state(&state));

    chassis_state_set_gear_actuator_state(&state, ACTUATOR_STATE_READY);
    TEST_ASSERT_TRUE(chassis_state_is_actuators_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_longitudinal_actuator_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_lateral_actuator_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_gear_actuator_ready(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_READY, chassis_state_get_longitudinal_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_READY, chassis_state_get_lateral_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_READY, chassis_state_get_gear_actuator_state(&state));
    TEST_ASSERT_EQUAL(0x15, chassis_state_get_actuator_state(&state));
    chassis_state_set_actuator_state(&state, 0x15);
    TEST_ASSERT_TRUE(chassis_state_is_actuators_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_longitudinal_actuator_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_lateral_actuator_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_gear_actuator_ready(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_READY, chassis_state_get_longitudinal_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_READY, chassis_state_get_lateral_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_READY, chassis_state_get_gear_actuator_state(&state));


    chassis_state_set_longitudinal_actuator_state(&state, ACTUATOR_STATE_ACTIVE);
    TEST_ASSERT_TRUE(chassis_state_is_actuators_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_longitudinal_actuator_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_lateral_actuator_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_gear_actuator_ready(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_ACTIVE, chassis_state_get_longitudinal_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_READY, chassis_state_get_lateral_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_READY, chassis_state_get_gear_actuator_state(&state));
    TEST_ASSERT_EQUAL(0x35, chassis_state_get_actuator_state(&state));
    chassis_state_set_actuator_state(&state, 0x35);
    TEST_ASSERT_TRUE(chassis_state_is_actuators_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_longitudinal_actuator_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_lateral_actuator_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_gear_actuator_ready(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_ACTIVE, chassis_state_get_longitudinal_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_READY, chassis_state_get_lateral_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_READY, chassis_state_get_gear_actuator_state(&state));

    chassis_state_set_lateral_actuator_state(&state, ACTUATOR_STATE_ACTIVE);
    TEST_ASSERT_TRUE(chassis_state_is_actuators_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_longitudinal_actuator_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_lateral_actuator_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_gear_actuator_ready(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_ACTIVE, chassis_state_get_longitudinal_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_ACTIVE, chassis_state_get_lateral_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_READY, chassis_state_get_gear_actuator_state(&state));
    TEST_ASSERT_EQUAL(0x3d, chassis_state_get_actuator_state(&state));
    chassis_state_set_actuator_state(&state, 0x3d);
    TEST_ASSERT_TRUE(chassis_state_is_actuators_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_longitudinal_actuator_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_lateral_actuator_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_gear_actuator_ready(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_ACTIVE, chassis_state_get_longitudinal_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_ACTIVE, chassis_state_get_lateral_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_READY, chassis_state_get_gear_actuator_state(&state));

    chassis_state_set_gear_actuator_state(&state, ACTUATOR_STATE_ACTIVE);
    TEST_ASSERT_TRUE(chassis_state_is_actuators_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_longitudinal_actuator_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_lateral_actuator_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_gear_actuator_ready(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_ACTIVE, chassis_state_get_longitudinal_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_ACTIVE, chassis_state_get_lateral_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_ACTIVE, chassis_state_get_gear_actuator_state(&state));
    TEST_ASSERT_EQUAL(0x3f, chassis_state_get_actuator_state(&state));
    chassis_state_set_actuator_state(&state, 0x3f);
    TEST_ASSERT_TRUE(chassis_state_is_actuators_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_longitudinal_actuator_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_lateral_actuator_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_gear_actuator_ready(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_ACTIVE, chassis_state_get_longitudinal_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_ACTIVE, chassis_state_get_lateral_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_ACTIVE, chassis_state_get_gear_actuator_state(&state));

    chassis_state_set_longitudinal_actuator_state(&state, ACTUATOR_STATE_FAULT);
    TEST_ASSERT_FALSE(chassis_state_is_actuators_ready(&state));
    TEST_ASSERT_FALSE(chassis_state_is_longitudinal_actuator_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_lateral_actuator_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_gear_actuator_ready(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_FAULT, chassis_state_get_longitudinal_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_ACTIVE, chassis_state_get_lateral_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_ACTIVE, chassis_state_get_gear_actuator_state(&state));
    TEST_ASSERT_EQUAL(0x2f, chassis_state_get_actuator_state(&state));
    chassis_state_set_actuator_state(&state, 0x2f);
    TEST_ASSERT_FALSE(chassis_state_is_actuators_ready(&state));
    TEST_ASSERT_FALSE(chassis_state_is_longitudinal_actuator_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_lateral_actuator_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_gear_actuator_ready(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_FAULT, chassis_state_get_longitudinal_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_ACTIVE, chassis_state_get_lateral_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_ACTIVE, chassis_state_get_gear_actuator_state(&state));

    chassis_state_set_lateral_actuator_state(&state, ACTUATOR_STATE_FAULT);
    TEST_ASSERT_FALSE(chassis_state_is_actuators_ready(&state));
    TEST_ASSERT_FALSE(chassis_state_is_longitudinal_actuator_ready(&state));
    TEST_ASSERT_FALSE(chassis_state_is_lateral_actuator_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_gear_actuator_ready(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_FAULT, chassis_state_get_longitudinal_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_FAULT, chassis_state_get_lateral_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_ACTIVE, chassis_state_get_gear_actuator_state(&state));
    TEST_ASSERT_EQUAL(0x2b, chassis_state_get_actuator_state(&state));
    chassis_state_set_actuator_state(&state, 0x2b);
    TEST_ASSERT_FALSE(chassis_state_is_actuators_ready(&state));
    TEST_ASSERT_FALSE(chassis_state_is_longitudinal_actuator_ready(&state));
    TEST_ASSERT_FALSE(chassis_state_is_lateral_actuator_ready(&state));
    TEST_ASSERT_TRUE(chassis_state_is_gear_actuator_ready(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_FAULT, chassis_state_get_longitudinal_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_FAULT, chassis_state_get_lateral_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_ACTIVE, chassis_state_get_gear_actuator_state(&state));

    chassis_state_set_gear_actuator_state(&state, ACTUATOR_STATE_FAULT);
    TEST_ASSERT_FALSE(chassis_state_is_actuators_ready(&state));
    TEST_ASSERT_FALSE(chassis_state_is_longitudinal_actuator_ready(&state));
    TEST_ASSERT_FALSE(chassis_state_is_lateral_actuator_ready(&state));
    TEST_ASSERT_FALSE(chassis_state_is_gear_actuator_ready(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_FAULT, chassis_state_get_longitudinal_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_FAULT, chassis_state_get_lateral_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_FAULT, chassis_state_get_gear_actuator_state(&state));
    TEST_ASSERT_EQUAL(0x2a, chassis_state_get_actuator_state(&state));
    chassis_state_set_actuator_state(&state, 0x2a);
    TEST_ASSERT_FALSE(chassis_state_is_actuators_ready(&state));
    TEST_ASSERT_FALSE(chassis_state_is_longitudinal_actuator_ready(&state));
    TEST_ASSERT_FALSE(chassis_state_is_lateral_actuator_ready(&state));
    TEST_ASSERT_FALSE(chassis_state_is_gear_actuator_ready(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_FAULT, chassis_state_get_longitudinal_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_FAULT, chassis_state_get_lateral_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_FAULT, chassis_state_get_gear_actuator_state(&state));
}

static void test_chassis_state_serialize_deserialize(void)
{
    struct ChassisState state;
    uint8_t buffer[1024];
    uint32_t buffer_size;
    retcode_t retcode;

    retcode = chassis_state_init_default(&state);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, retcode);

    buffer_size = chassis_state_get_serialized_size(&state);
    TEST_ASSERT_LESS_THAN_UINT32(sizeof(buffer), buffer_size);

    retcode = chassis_state_serialize(&state, buffer, 0);
    TEST_ASSERT_EQUAL_INT32(RC_SERIALIZATION_BUFFER_OVERFLOW, retcode);
    retcode = chassis_state_serialize(&state, buffer, sizeof(buffer));
    TEST_ASSERT_EQUAL_UINT32(buffer_size, retcode);

    retcode = chassis_state_deserialize(&state, buffer, 0);
    TEST_ASSERT_EQUAL_INT32(RC_DESERIALIZATION_BUFFER_UNDERFLOW, retcode);
    retcode = chassis_state_deserialize(&state, buffer, sizeof(buffer));
    TEST_ASSERT_EQUAL_UINT32(buffer_size, retcode);

    TEST_ASSERT_EQUAL_FLOAT(0.0f, chassis_state_get_vehicle_speed(&state));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, chassis_state_get_front_left_wheel_speed(&state));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, chassis_state_get_front_right_wheel_speed(&state));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, chassis_state_get_rear_left_wheel_speed(&state));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, chassis_state_get_rear_right_wheel_speed(&state));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, chassis_state_get_longitudinal_acceleration(&state));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, chassis_state_get_lateral_acceleration(&state));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, chassis_state_get_yaw_rate(&state));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, chassis_state_get_front_wheel_angle(&state));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, chassis_state_get_longitudinal_control_value(&state));

    TEST_ASSERT_FALSE(chassis_state_is_signal_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_left_turn_signal_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_right_turn_signal_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_hazard_flasher_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_head_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_low_beam_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_high_beam_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_brake_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_fog_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_fog_light_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_fog_light_on(&state));
    TEST_ASSERT_EQUAL(0x0000, chassis_state_get_light_state(&state));

    TEST_ASSERT_FALSE(chassis_state_is_driver_seatbelt_locked(&state));
    TEST_ASSERT_FALSE(chassis_state_is_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_left_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_right_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_left_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_right_door_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_trunk_door_open(&state));

    TEST_ASSERT_FALSE(chassis_state_is_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_left_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_right_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_left_window_open(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_right_window_open(&state));

    TEST_ASSERT_FALSE(chassis_state_is_wiper_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_wiper_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_wiper_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_window_defroster_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_front_window_defroster_on(&state));
    TEST_ASSERT_FALSE(chassis_state_is_rear_window_defroster_on(&state));
    TEST_ASSERT_EQUAL(0x0000, chassis_state_get_cockpit_state(&state));

    TEST_ASSERT_EQUAL_UINT8(0u, chassis_state_get_energy_source_level(&state));

    TEST_ASSERT_EQUAL_UINT8(GEAR_POSITION_UNKNOWN, chassis_state_get_gear_position(&state));
    TEST_ASSERT_EQUAL_UINT8(0u, chassis_state_get_gear_level(&state));

    TEST_ASSERT_FALSE(chassis_state_is_handbrake_hold(&state));
    TEST_ASSERT_EQUAL(0x00, chassis_state_get_gear_state(&state));

    TEST_ASSERT_FALSE(chassis_state_is_system_activated(&state));
    TEST_ASSERT_FALSE(chassis_state_is_longitudinal_activated(&state));
    TEST_ASSERT_FALSE(chassis_state_is_lateral_activated(&state));
    TEST_ASSERT_FALSE(chassis_state_is_driver_takeover(&state));
    TEST_ASSERT_FALSE(chassis_state_is_longitudinal_takeover(&state));
    TEST_ASSERT_FALSE(chassis_state_is_lateral_takeover(&state));
    TEST_ASSERT_EQUAL(0x00, chassis_state_get_user_operation_state(&state));

    TEST_ASSERT_FALSE(chassis_state_is_actuators_ready(&state));
    TEST_ASSERT_FALSE(chassis_state_is_longitudinal_actuator_ready(&state));
    TEST_ASSERT_FALSE(chassis_state_is_lateral_actuator_ready(&state));
    TEST_ASSERT_FALSE(chassis_state_is_gear_actuator_ready(&state));

    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_NOT_READY, chassis_state_get_longitudinal_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_NOT_READY, chassis_state_get_lateral_actuator_state(&state));
    TEST_ASSERT_EQUAL_UINT8(ACTUATOR_STATE_NOT_READY, chassis_state_get_gear_actuator_state(&state));
    TEST_ASSERT_EQUAL(0x00, chassis_state_get_actuator_state(&state));
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_chassis_state_init_default);
    RUN_TEST(test_chassis_state_motion_state);
    RUN_TEST(test_chassis_state_light_state);
    RUN_TEST(test_chassis_state_door_seatbelt_state);
    RUN_TEST(test_chassis_state_window_state);
    RUN_TEST(test_chassis_state_wiper_and_defroster_state);
    RUN_TEST(test_chassis_state_energy_source_level);
    RUN_TEST(test_chassis_state_gear_and_handbrake);
    RUN_TEST(test_chassis_state_user_activity);
    RUN_TEST(test_chassis_state_actuator_state);
    RUN_TEST(test_chassis_state_serialize_deserialize);
    return UNITY_END();
}
