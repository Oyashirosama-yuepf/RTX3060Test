/*!
 * @file vehicle_can_driver.c
 * @brief This source file implements vehicle can driver functions
 * @author liuya@holomatic.com
 * @date 2019-09-25
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo_c/sensors/can/vehicle_can_driver.h>
#include <math.h>


void Function5BF(struct VehicleBodyState* body_state, uint16_t raw_value)
{
    switch (raw_value)
    {
        case 0x10:
            vehicle_body_state_set_button_volume_up(body_state, 1);
            vehicle_body_state_set_button_volume_down(body_state, 0);
            vehicle_body_state_set_button_voice(body_state, 0);
            break;

        case 0x11:
            vehicle_body_state_set_button_volume_down(body_state, 1);
            vehicle_body_state_set_button_volume_up(body_state, 0);
            vehicle_body_state_set_button_voice(body_state, 0);
            break;

        case 0x19:
            vehicle_body_state_set_button_voice(body_state, 1);
            vehicle_body_state_set_button_volume_up(body_state, 0);
            vehicle_body_state_set_button_volume_down(body_state, 0);
            break;

        default:
            vehicle_body_state_set_button_volume_up(body_state, 0);
            vehicle_body_state_set_button_volume_down(body_state, 0);
            vehicle_body_state_set_button_voice(body_state, 0);
            break;
    }
}

void ParseIdPart0(struct VehicleBodyState* body_state, uint32_t id, uint8_t* data)
{
    uint16_t  raw_value;
    float32_t physical_value;

    switch (id)
    {   
        case (0x40):
            raw_value = GET_Airbag_01_front_driver_belt_warning(data);
            vehicle_body_state_set_driver_seatbelt(body_state, raw_value);

            raw_value = GET_Airbag_01_front_passenger_belt_warning(data);
            vehicle_body_state_set_passenger_seatbelt(body_state, raw_value);
            break;

        case (0x3DB):
            raw_value = GET_Gateway_72_trunk_status(data);
            vehicle_body_state_set_trunk_door(body_state, raw_value);

            raw_value = GET_Gateway_72_front_left_door(data);
            vehicle_body_state_set_front_left_door(body_state, raw_value);

            raw_value = GET_Gateway_72_front_right_door(data);
            vehicle_body_state_set_front_right_door(body_state, raw_value);

            raw_value = GET_Gateway_72_rear_left_door(data);
            vehicle_body_state_set_rear_left_door(body_state, raw_value);

            raw_value = GET_Gateway_72_rear_right_door(data);
            vehicle_body_state_set_rear_right_door(body_state, raw_value);

            raw_value = GET_Gateway_72_engine_hood_status(data);
            vehicle_body_state_set_car_hood(body_state, raw_value);

            raw_value      = data[7] & 0xFF;
            physical_value = raw_value * 0.5 - 50;
            vehcile_body_state_set_temperature(body_state, physical_value);
            break;

        case (0x121):
            raw_value      = data[2] & 0xFF;
            physical_value = raw_value * 0.4;
            vehicle_body_state_set_accelerator_pedal(body_state, physical_value);
            break;

        case (0x12B):
            raw_value = GET_GRA_ACC_01_wheel_button_io(data);
            vehicle_body_state_set_button_io(body_state, raw_value);

            raw_value = GET_GRA_ACC_01_wheel_button_mode(data);
            vehicle_body_state_set_button_mode(body_state, raw_value);

            raw_value = GET_GRA_ACC_01_wheel_button_set(data);
            vehicle_body_state_set_button_set(body_state, raw_value);

            raw_value = GET_GRA_ACC_01_wheel_button_plus(data);
            vehicle_body_state_set_button_plus(body_state, raw_value);

            raw_value = GET_GRA_ACC_01_wheel_button_minus(data);
            vehicle_body_state_set_button_minus(body_state, raw_value);

            raw_value = GET_GRA_ACC_01_wheel_button_resume(data);
            vehicle_body_state_set_button_res(body_state, raw_value);
            break;

        case (0x658):
            raw_value = GET_Licht_vorne_01_rear_frog_light(data);
            vehicle_body_state_set_rear_fog_light(body_state, raw_value);

            raw_value = GET_Licht_vorne_01_front_frog_light(data);
            vehicle_body_state_set_front_fog_light(body_state, raw_value);

            raw_value = GET_Licht_vorne_01_high_beam_light(data);
            vehicle_body_state_set_high_beam(body_state, raw_value);

            raw_value = GET_Licht_vorne_01_low_beam_light(data);
            vehicle_body_state_set_low_beam(body_state, raw_value);
            break;
    }
}

void ParseIdPart1(struct VehicleBodyState* body_state, uint32_t id, uint8_t* data)
{
    uint16_t  raw_value;

    switch (id)
    {
        case (0x5A0):
            raw_value = GET_RLS_01_front_wiper_speed(data);
            // vehicle_body_state_set_front_wiper_speed(body_state, raw_value);
            if (raw_value == 0)
            {
                vehicle_body_state_set_front_wiper_state(body_state, 0);
            }
            else
            {
                vehicle_body_state_set_front_wiper_state(body_state, 1);
            }

            raw_value = GET_RLS_01_rainfall(data);
            raw_value = CALC_RLS_01_rainfall(raw_value, 1);
            vehicle_body_state_set_rainfall(body_state, raw_value);
            break;

        case (0x5BF):
            raw_value = data[0];
            Function5BF(body_state, raw_value);
            break;

        case (0x106):
            raw_value = GET_ESP_05_ECD_Bremslicht(data);
            vehicle_body_state_set_brake_light(body_state, raw_value);
            break;

        case (0x520):
        case (0x366):
        case (0x104):
        case (0xFD):
            break;
    }
}

void ParseIdPart2(struct ChassisState* chassis_state, uint32_t id, uint8_t* data)
{
    uint16_t  raw_value;

    switch (id)
    {
        case (0x403):
            raw_value = GET_epb_status_epb_status(data);
            if (raw_value)
            {
                chassis_state_set_handbrake(chassis_state, 1);
            }
            else
            {
                chassis_state_set_handbrake(chassis_state, 0);
            }
            break;

        case (0x405):
            raw_value = GET_longitudinal_status_longitudinal_status(data);
            switch (raw_value)
            {
                case 0:
                    chassis_state_set_longitudinal_actuator_state(chassis_state, ACTUATOR_STATE_NOT_READY);
                    break;

                case 2:
                    chassis_state_set_longitudinal_actuator_state(chassis_state, ACTUATOR_STATE_READY);
                    // chassis_state_set_longitudinal_takeover(chassis_state, 1);
                    // chassis_state_set_longitudinal_activated(chassis_state, 1);
                    break;
                case 3:
                case 4:
                case 5:
                    chassis_state_set_longitudinal_actuator_state(chassis_state, ACTUATOR_STATE_ACTIVE);
                    break;
                default:
                    chassis_state_set_longitudinal_actuator_state(chassis_state, ACTUATOR_STATE_FAULT);
                    break;
            }
            break;
    }
}

void ParseIdPart3(struct ChassisState* chassis_state, uint32_t id, uint8_t* data)
{    
    uint16_t  raw_value;

    switch (id)
    {
        case (0x402):
            raw_value = GET_door_status_front_left(data);
            chassis_state_set_front_left_door(chassis_state, raw_value);

            raw_value = GET_door_status_front_right(data);
            chassis_state_set_front_right_door(chassis_state, raw_value);

            raw_value = GET_door_status_rear_left(data);
            chassis_state_set_rear_left_door(chassis_state, raw_value);

            raw_value = GET_door_status_rear_right(data);
            chassis_state_set_rear_right_door(chassis_state, raw_value);
            break;

        case (0x404):
            raw_value = GET_gear_status_actual_gear(data);
            switch (raw_value)
            {
                case 5:
                    chassis_state_set_gear_position(chassis_state, GEAR_POSITION_P);
                    break;
                case 6:
                    chassis_state_set_gear_position(chassis_state, GEAR_POSITION_R);
                    break;
                case 7:
                    chassis_state_set_gear_position(chassis_state, GEAR_POSITION_N);
                    break;
                case 8:
                case 9:
                case 10:
                    chassis_state_set_gear_position(chassis_state, GEAR_POSITION_D);
                    break;
                default:
                    chassis_state_set_gear_position(chassis_state, GEAR_POSITION_UNKNOWN);
                    break;
            }
            break;
    }
}

void ParseIdPart4(struct ChassisState* chassis_state, uint32_t id, uint8_t* data)
{
    uint16_t  raw_value;
    float32_t physical_value;

    switch (id)
    {
        case (0x401):
            raw_value      = GET_brake_status_brake_torque(data);
            physical_value = CALC_brake_status_brake_torque(raw_value, 1.0f);

            raw_value = GET_brake_status_brake_status(data);
            if (raw_value || physical_value > 0.8)
            {
                chassis_state_set_longitudinal_takeover(chassis_state, 1);
                // chassis_state_set_longitudinal_activated(chassis_state, 0);
            }
            else
            {
                chassis_state_set_longitudinal_takeover(chassis_state, 0);
                // chassis_state_set_longitudinal_activated(chassis_state, 1);
            }
            break;

        case (0x406):
            raw_value = GET_lateral_torque_status_torque_status(data);
            switch (raw_value)
            {
                case 0:
                    chassis_state_set_lateral_actuator_state(chassis_state, ACTUATOR_STATE_NOT_READY);
                    break;
                case 6:
                    chassis_state_set_lateral_actuator_state(chassis_state, ACTUATOR_STATE_ACTIVE);
                    break;
                case 8:
                case 10:
                    chassis_state_set_lateral_actuator_state(chassis_state, ACTUATOR_STATE_READY);
                    break;
                default:
                    chassis_state_set_lateral_actuator_state(chassis_state, ACTUATOR_STATE_FAULT);
                    break;
            }
            /**
             * @brief torque value and torque direction cannot convert to chassis state
             *
             */
            break;
    }
}

void ParseIdPart5(struct ChassisState* chassis_state, uint32_t id, uint8_t* data)
{
    uint16_t  raw_value;
    float32_t physical_value;

    switch (id)
    {
        case (0x408):
            /**
             * @brief steering status cannot convert to chassis state
             *
             */
            raw_value      = GET_steering_status_steering_angle(data);
            physical_value = CALC_steering_status_steering_angle(raw_value, 1.0f);
            physical_value = physical_value * M_PI / 13.6f / 180.0f;

            raw_value = GET_steering_status_steering_angle_direction(data);
            if (1 == raw_value)
            {
                physical_value *= -1.0f;
            }
            chassis_state_set_front_wheel_angle(chassis_state, physical_value);

            /**
             * @brief steering and steering velocity cannot convert to chassis state
             *
             */
            break;

        case (0x407):
            /**
             * @brief lateral angle status cannot convert to chassis state
             *
             */
        case (0x409):
            /**
             * @brief button cannot convert to chassis state
             *
             */
            break;

        case (0x40A):
            raw_value      = GET_vehicle_speed_status_real_vehiclespeed(data);
            physical_value = CALC_vehicle_speed_status_real_vehiclespeed(raw_value, 1.0f);
            physical_value /= 3.6f;
            chassis_state_set_vehicle_speed(chassis_state, physical_value);
            break;

        case (0x40B):
            raw_value      = GET_wheel_speed_status_fl_wheelspeed(data);
            physical_value = CALC_wheel_speed_status_fl_wheelspeed(raw_value, 1.0f);
            chassis_state_set_front_left_wheel_speed(chassis_state, physical_value);

            raw_value      = GET_wheel_speed_status_fr_wheelspeed(data);
            physical_value = CALC_wheel_speed_status_fr_wheelspeed(raw_value, 1.0f);
            chassis_state_set_front_right_wheel_speed(chassis_state, physical_value);

            raw_value      = GET_wheel_speed_status_rl_wheelspeed(data);
            physical_value = CALC_wheel_speed_status_rl_wheelspeed(raw_value, 1.0f);
            chassis_state_set_rear_left_wheel_speed(chassis_state, physical_value);

            raw_value      = GET_wheel_speed_status_rr_wheelspeed(data);
            physical_value = CALC_wheel_speed_status_rr_wheelspeed(raw_value, 1.0f);
            chassis_state_set_rear_right_wheel_speed(chassis_state, physical_value);
            break;

        case (0x40C):
            raw_value      = GET_yawrate_status_lateral_acc(data);
            physical_value = CALC_yawrate_status_lateral_acc(raw_value, 1.0f);
            chassis_state_set_lateral_acceleration(chassis_state, physical_value);

            raw_value      = GET_yawrate_status_longitude_acc(data);
            physical_value = CALC_yawrate_status_longitude_acc(raw_value, 1.0f);
            chassis_state_set_longitudinal_acceleration(chassis_state, physical_value);

            raw_value      = GET_yawrate_status_yawrate(data);
            physical_value = CALC_yawrate_status_yawrate(raw_value, 1.0f);

            raw_value = GET_yawrate_status_yawrate_direction(data);
            if (1 == raw_value)
            {
                physical_value *= -1.0f;
            }
            chassis_state_set_yaw_rate(chassis_state, physical_value);
            break;
    }
}

retcode_t vehicle_can_driver_process_data(struct ChassisState* chassis_state, struct VehicleBodyState* body_state,
                                          const struct Timestamp* timestamp, uint32_t id, uint8_t* data, uint32_t len)
{
    (void)len;
    uint16_t  raw_value;
    retcode_t rc = RC_SUCCESS;

    chassis_state_set_timestamp(chassis_state, timestamp);
    vehicle_body_state_set_timestamp(body_state, timestamp);

    /* parse id */
    switch (id)
    {
         case (0x400):
            raw_value = GET_light_status_Turnleft(data);
            chassis_state_set_left_turn_signal(chassis_state, raw_value);
            vehicle_body_state_set_left_turn_signal(body_state, raw_value);

            raw_value = GET_light_status_TurnRight(data);
            chassis_state_set_right_turn_signal(chassis_state, raw_value);
            vehicle_body_state_set_right_turn_signal(body_state, raw_value);

            raw_value = GET_light_status_WarningBlinker(data);
            chassis_state_set_hazard_flasher(chassis_state, raw_value);
            vehicle_body_state_set_hazard_flasher(body_state, raw_value);
            break;

        case (0x40):
        case (0x3DB):
        case (0x121):
        case (0x12B):
        case (0x658):
            ParseIdPart0(body_state, id, data);
            break;

        case (0x520):
        case (0x366):
        case (0x104):
        case (0xFD):
        case (0x5A0):
        case (0x5BF):
        case (0x106):
            ParseIdPart1(body_state, id, data);
            break;
           
        case (0x403):
        case (0x405):
            ParseIdPart2(chassis_state, id, data);
            break;
 
        case (0x402):
        case (0x404):
            ParseIdPart3(chassis_state, id, data);
            break;

        case (0x401):
        case (0x406):
            ParseIdPart4(chassis_state, id, data);
            break;

        case (0x407):
        case (0x408):
        case (0x409):
        case (0x40A):
        case (0x40B):
        case (0x40C):
            ParseIdPart5(chassis_state, id, data);
            break;

        default:
            rc = RC_FAIL;
            break;
    }
    return rc;
}
