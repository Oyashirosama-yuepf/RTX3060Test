/**
 * @file chassis_state.c
 * @brief This file implements ChassisState Object related functions.
 * @author zhangjiannan(zhangjiannan@holomaitc.com)
 * @date 2019-11-1
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <assert.h>
#include <string.h>
#include <holo_c/common/chassis_state.h>
#include <holo_c/utils/serialization.h>

retcode_t chassis_state_init_default(struct ChassisState* state)
{
    memset(state, 0x00, sizeof(struct ChassisState));
    return RC_SUCCESS;
}

static retcode_t serialize_data(const struct ChassisState* state, 
                                uint8_t* buffer, 
                                uint32_t buffer_size)
{
    uint32_t serialized_size = 0;

    serialized_size += 
	    timestamp_serialize(&state->stamp, buffer, buffer_size);
    serialized_size +=
        serialize_float32(&state->vehicle_speed, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_float32(&state->front_left_wheel_speed, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_float32(&state->front_right_wheel_speed, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_float32(&state->rear_left_wheel_speed, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_float32(&state->rear_right_wheel_speed, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_float32(&state->longitudinal_acceleration, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_float32(&state->lateral_acceleration, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += 
		serialize_float32(&state->yaw_rate, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_float32(&state->front_wheel_angle, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_float32(&state->longitudinal_control_value, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint32(&state->front_left_wheel_pulse, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint32(&state->front_right_wheel_pulse, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint32(&state->rear_left_wheel_pulse, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint32(&state->rear_right_wheel_pulse, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint8((uint8_t*)&state->front_left_wheel_direction, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint8((uint8_t*)&state->front_right_wheel_direction, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint8((uint8_t*)&state->rear_left_wheel_direction, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint8((uint8_t*)&state->rear_right_wheel_direction, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint8((uint8_t*)&state->vehicle_stand_still, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint8((uint8_t*)&state->brake_pedal_status, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint8((uint8_t*)&state->eps_apa_abortfeedback, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint8((uint8_t*)&state->eps_apa_sys_status, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_float32(&state->steering_wheel_angle, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_float32(&state->steering_torque, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_float32(&state->steering_angle_speed, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_float32(&state->Accelerograph_depth, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += 
        serialize_uint16((uint16_t*)&state->light_system_state, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += 
        serialize_uint16((uint16_t*)&state->cockpit_system_state, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint8(&state->energy_source_level, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_uint8((uint8_t*)&state->gear_system_state, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += 
        serialize_uint8((uint8_t*)&state->user_operation_state, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += 
        serialize_uint8((uint8_t*)&state->chassis_actuator_state, buffer + serialized_size, buffer_size - serialized_size);
    return (retcode_t)serialized_size;
}

static retcode_t deserialize_data(struct ChassisState* state,
                                  const uint8_t* buffer,
                                  uint32_t buffer_size)
{
    uint32_t deserialized_size = 0;

    deserialized_size += timestamp_deserialize(&state->stamp, buffer, buffer_size);
    deserialized_size += deserialize_float32(&state->vehicle_speed,
                                             buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_float32(&state->front_left_wheel_speed,
                                             buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_float32(&state->front_right_wheel_speed,
                                             buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_float32(&state->rear_left_wheel_speed,
                                             buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_float32(&state->rear_right_wheel_speed,
                                             buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_float32(&state->longitudinal_acceleration,
                                             buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_float32(&state->lateral_acceleration,
                                             buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_float32(&state->yaw_rate,
                                             buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_float32(&state->front_wheel_angle,
                                             buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_float32(&state->longitudinal_control_value,
                                             buffer + deserialized_size, buffer_size - deserialized_size);                                             
    deserialized_size += deserialize_uint32(&state->front_left_wheel_pulse,
                                             buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint32(&state->front_right_wheel_pulse,
                                             buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint32(&state->rear_left_wheel_pulse,
                                             buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint32(&state->rear_right_wheel_pulse,
                                             buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->front_left_wheel_direction,
                                             buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->front_right_wheel_direction,
                                             buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->rear_left_wheel_direction,
                                             buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->rear_right_wheel_direction,
                                             buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->vehicle_stand_still,
                                             buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->brake_pedal_status,
                                             buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->eps_apa_abortfeedback,
                                             buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->eps_apa_sys_status,
                                             buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_float32(&state->steering_wheel_angle,
                                             buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_float32(&state->steering_torque,
                                             buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_float32(&state->steering_angle_speed,
                                             buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_float32(&state->Accelerograph_depth,
                                             buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16((uint16_t*)&state->light_system_state,
                                             buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16((uint16_t*)&state->cockpit_system_state,
                                             buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8(&state->energy_source_level,
                                             buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->gear_system_state,
                                             buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->user_operation_state,
                                             buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->chassis_actuator_state,
                                             buffer + deserialized_size, buffer_size - deserialized_size);
    return (retcode_t)deserialized_size;
}

uint32_t chassis_state_get_serialized_size(const struct ChassisState* state)
{
    (void)state;

    return serialization_aligned_size(sizeof(struct ChassisState));
}

retcode_t chassis_state_serialize(const struct ChassisState* state, 
                                  uint8_t* buffer, 
                                  uint32_t buffer_size)
{
    assert(state != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    uint32_t serialized_size = 0;
    uint32_t expected_size = chassis_state_get_serialized_size(state);

    if(buffer_size < expected_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += serialize_data(state, buffer, buffer_size);

        serialized_size += serialize_padding(serialized_size, 
                                             buffer + serialized_size, 
                                             buffer_size - serialized_size);

        assert(expected_size == serialized_size);
        rc = (retcode_t)serialized_size;
    }

    return rc;
}

retcode_t chassis_state_deserialize(struct ChassisState* state, 
                                    const uint8_t* buffer, 
                                    uint32_t buffer_size)
{
    assert(state != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    uint32_t deserialized_size = 0;
    uint32_t expected_size = chassis_state_get_serialized_size(state);

    if(buffer_size < expected_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size += deserialize_data(state, buffer, buffer_size);

        deserialized_size += deserialize_padding(deserialized_size,
                                                 buffer + deserialized_size,
                                                 buffer_size - deserialized_size);

        assert(deserialized_size == expected_size);
        rc = (retcode_t)deserialized_size;
    }
    return rc;
}

