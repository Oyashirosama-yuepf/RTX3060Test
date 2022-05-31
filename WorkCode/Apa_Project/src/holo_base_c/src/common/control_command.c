/**
 * @file control_command.c
 * @brief This header file define control command.
 * @author lijiawen@holomatic.com
 * @date 2019-09-10
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *  notice.
 */

#include <assert.h>

#include <holo_c/common/control_command.h>
#include <holo_c/utils/serialization.h>

void control_command_init_default(struct ControlCommand* command)
{
    assert(command != NULL);

    (void)timestamp_init(&(command->stamp));

    command->lateral_control_model      = LATERAL_CONTROL_MODEL_DISABLE;
    command->longitudinal_control_model = LONGITUDINAL_CONTROL_MODEL_DISABLE;
    command->gear_control_model         = GEAR_CONTROL_MODEL_DISABLE;

    command->lateral_control_value       = 0.0f;
    command->longitudinal_control_value1 = 0.0f;
    command->longitudinal_control_value2 = 0.0f;

    command->gear_control_command.gear_position = 0;
    command->gear_control_command.gear_level    = 0;
    command->gear_control_command.handbrake     = 0;
}

const struct Timestamp* control_command_get_timestamp(const struct ControlCommand* controlcommand)
{
    assert(controlcommand != NULL);

    return &(controlcommand->stamp);
}

void control_command_set_timestamp(struct ControlCommand* controlcommand, const struct Timestamp* stamp)
{
    assert(controlcommand != NULL);
    assert(stamp != NULL);

    timestamp_init_from_timestamp(&controlcommand->stamp, stamp);
}

enum LateralControlModel control_command_get_lateral_control_model(const struct ControlCommand* command)
{
    assert(command != NULL);

    return command->lateral_control_model;
}

void control_command_set_lateral_control_model(struct ControlCommand*         command,
                                               const enum LateralControlModel lateral_control_model)
{
    assert(command != NULL);

    command->lateral_control_model = lateral_control_model;
}

enum LongitudinalControlModel control_command_get_longitudinal_control_model(const struct ControlCommand* command)
{
    assert(command != NULL);

    return command->longitudinal_control_model;
}

void control_command_set_longitudinal_control_model(struct ControlCommand*              command,
                                                    const enum LongitudinalControlModel longitudinal_control_model)
{
    assert(command != NULL);

    command->longitudinal_control_model = longitudinal_control_model;
}

enum GearControlModel control_command_get_gear_control_model(const struct ControlCommand* command)
{
    assert(command != NULL);

    return command->gear_control_model;
}

void control_command_set_gear_control_model(struct ControlCommand*      command,
                                            const enum GearControlModel gear_control_model)
{
    assert(command != NULL);

    command->gear_control_model = gear_control_model;
}

float32_t control_command_get_lateral_control_value(const struct ControlCommand* command)
{
    assert(command != NULL);

    return command->lateral_control_value;
}

void control_command_set_lateral_control_value(struct ControlCommand* command, const float32_t lateral_control_value)
{
    assert(command != NULL);

    command->lateral_control_value = lateral_control_value;
}

float32_t control_command_get_lateral_torque(const struct ControlCommand* command)
{
    assert(command != NULL);

    return command->lateral_control_value;
}

void control_command_set_lateral_torque(struct ControlCommand* command, const float32_t lateral_torque)
{
    assert(command != NULL);

    command->lateral_control_value = lateral_torque;
}

float32_t control_command_get_lateral_front_wheel_angle(const struct ControlCommand* command)
{
    assert(command != NULL);

    return command->lateral_control_value;
}

void control_command_set_lateral_front_wheel_angle(struct ControlCommand* command, const float32_t front_wheel_angle)
{
    assert(command != NULL);

    command->lateral_control_value = front_wheel_angle;
}

float32_t control_command_get_lateral_steering_angle(const struct ControlCommand* command)
{
    assert(command != NULL);

    return command->lateral_control_value;
}

void control_command_set_lateral_steering_angle(struct ControlCommand* command, const float32_t steering_angle)
{
    assert(command != NULL);

    command->lateral_control_value = steering_angle;
}

float32_t control_command_get_longitudinal_control_value1(const struct ControlCommand* command)
{
    assert(command != NULL);

    return command->longitudinal_control_value1;
}

void control_command_set_longitudinal_control_value1(struct ControlCommand* command,
                                                     const float32_t        longitudinal_control_value)
{
    assert(command != NULL);

    command->longitudinal_control_value1 = longitudinal_control_value;
}

float32_t control_command_get_longitudinal_control_value2(const struct ControlCommand* command)
{
    assert(command != NULL);

    return command->longitudinal_control_value2;
}

void control_command_set_longitudinal_control_value2(struct ControlCommand* command,
                                                     const float32_t        longitudinal_control_value)
{
    assert(command != NULL);

    command->longitudinal_control_value2 = longitudinal_control_value;
}

float32_t control_command_get_longitudinal_acceleration(const struct ControlCommand* command)
{
    assert(command != NULL);

    return command->longitudinal_control_value1;
}

void control_command_set_longitudinal_acceleration(struct ControlCommand* command, const float32_t acceleration)
{
    assert(command != NULL);

    command->longitudinal_control_value1 = acceleration;
}

float32_t control_command_get_longitudinal_deceleration(const struct ControlCommand* command)
{
    assert(command != NULL);

    return command->longitudinal_control_value1;
}

void control_command_set_longitudinal_deceleration(struct ControlCommand* command, const float32_t deceleration)
{
    assert(command != NULL);

    command->longitudinal_control_value1 = deceleration;
}

float32_t control_command_get_longitudinal_torque(const struct ControlCommand* command)
{
    assert(command != NULL);

    return command->longitudinal_control_value1;
}

void control_command_set_longitudinal_torque(struct ControlCommand* command, const float32_t torque)
{
    assert(command != NULL);

    command->longitudinal_control_value1 = torque;
}

float32_t control_command_get_longitudinal_torque_deceleration(const struct ControlCommand* command)
{
    assert(command != NULL);

    return command->longitudinal_control_value1;
}

void control_command_set_longitudinal_torque_deceleration(struct ControlCommand* command,
                                                          const float32_t        torque_deceleration)
{
    assert(command != NULL);

    command->longitudinal_control_value1 = torque_deceleration;
}

float32_t control_command_get_longitudinal_speed_limit(const struct ControlCommand* command)
{
    assert(command != NULL);

    return command->longitudinal_control_value1;
}

void control_command_set_longitudinal_speed_limit(struct ControlCommand* command, const float32_t speed_limit)
{
    assert(command != NULL);

    command->longitudinal_control_value1 = speed_limit;
}

float32_t control_command_get_longitudinal_stop_distance(const struct ControlCommand* command)
{
    assert(command != NULL);

    return command->longitudinal_control_value2;
}

void control_command_set_longitudinal_stop_distance(struct ControlCommand* command, const float32_t stop_distance)
{
    assert(command != NULL);

    command->longitudinal_control_value2 = stop_distance;
}

uint8_t control_command_get_gear_command(const struct ControlCommand* command)
{
    return command->gear_control_command.handbrake << 0 | command->gear_control_command.gear_level << 1 |
           command->gear_control_command.gear_position << 5;
}

void control_command_set_gear_command(struct ControlCommand* command, const uint8_t value)
{
    command->gear_control_command.handbrake     = value >> 0;
    command->gear_control_command.gear_level    = value >> 1;
    command->gear_control_command.gear_position = value >> 5;
}

enum GearPosition control_command_get_gear_position(const struct ControlCommand* command)
{
    assert(command != NULL);

    return (enum GearPosition)command->gear_control_command.gear_position;
}

void control_command_set_gear_position(struct ControlCommand* command, const enum GearPosition value)
{
    assert(command != NULL);

    command->gear_control_command.gear_position = (uint8_t)value;
}

uint8_t control_command_get_gear_level(const struct ControlCommand* command)
{
    assert(command != NULL);

    return command->gear_control_command.gear_level;
}

void control_command_set_gear_level(struct ControlCommand* command, const uint8_t value)
{
    assert(command != NULL);

    command->gear_control_command.gear_level = value > 15 ? 15 : value;
}

bool_t control_command_get_handbrake(const struct ControlCommand* command)
{
    assert(command != NULL);

    return command->gear_control_command.handbrake;
}

void control_command_set_handbrake(struct ControlCommand* command, const bool_t value)
{
    assert(command != NULL);

    command->gear_control_command.handbrake = value;
}

uint32_t control_command_get_serialized_size(const struct ControlCommand* command)
{
    (void)command;

    return serialization_aligned_size(sizeof(struct Timestamp) + 3 * sizeof(uint32_t) + 3 * sizeof(float32_t) +
                                      4 * sizeof(uint8_t));
}

retcode_t control_command_serialize(const struct ControlCommand* command, uint8_t* buffer, uint32_t buffer_size)
{
    assert(command != NULL);
    assert(buffer != NULL);

    uint32_t expected_size   = control_command_get_serialized_size(command);
    uint32_t serialized_size = 0;

    retcode_t rc = RC_SUCCESS;

    if (expected_size > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size +=
            timestamp_serialize(&command->stamp, buffer + serialized_size, buffer_size - serialized_size);

        serialized_size +=
            serialize_uint32((uint32_t*)&command->lateral_control_model, buffer + serialized_size, buffer_size - serialized_size);

        serialized_size += serialize_uint32((uint32_t*)&command->longitudinal_control_model, buffer + serialized_size,
                                            buffer_size - serialized_size);

        serialized_size +=
            serialize_uint32((uint32_t*)&command->gear_control_model, buffer + serialized_size, buffer_size - serialized_size);

        serialized_size +=
            serialize_float32(&command->lateral_control_value, buffer + serialized_size, buffer_size - serialized_size);

        serialized_size += serialize_float32(&command->longitudinal_control_value1, buffer + serialized_size,
                                             buffer_size - serialized_size);

        serialized_size += serialize_float32(&command->longitudinal_control_value2, buffer + serialized_size,
                                             buffer_size - serialized_size);

        serialized_size += serialize_uint8((const uint8_t*)&command->gear_control_command, buffer + serialized_size,
                                           buffer_size - serialized_size);

        serialized_size += serialize_uint8((const uint8_t*)&(command->reserved[0]), buffer + serialized_size,
                                           buffer_size - serialized_size);

        serialized_size += serialize_uint8((const uint8_t*)&(command->reserved[1]), buffer + serialized_size,
                                           buffer_size - serialized_size);

        serialized_size += serialize_uint8((const uint8_t*)&(command->reserved[2]), buffer + serialized_size,
                                           buffer_size - serialized_size);

        assert(serialized_size == expected_size);

        rc = serialized_size;
    }
    return rc;
}

retcode_t control_command_deserialize(struct ControlCommand* command, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(command != NULL);
    assert(buffer != NULL);

    control_command_init_default(command);

    uint32_t expected_size     = control_command_get_serialized_size(command);
    uint32_t deserialized_size = 0;

    retcode_t rc = RC_SUCCESS;

    if (expected_size > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size +=
            timestamp_deserialize(&command->stamp, buffer + deserialized_size, buffer_size - deserialized_size);

        deserialized_size += deserialize_uint32((uint32_t*)&command->lateral_control_model, buffer + deserialized_size,
                                                buffer_size - deserialized_size);

        deserialized_size += deserialize_uint32((uint32_t*)&command->longitudinal_control_model,
                                                buffer + deserialized_size, buffer_size - deserialized_size);

        deserialized_size += deserialize_uint32((uint32_t*)&command->gear_control_model, buffer + deserialized_size,
                                                buffer_size - deserialized_size);

        deserialized_size += deserialize_float32(&command->lateral_control_value, buffer + deserialized_size,
                                                 buffer_size - deserialized_size);

        deserialized_size += deserialize_float32(&command->longitudinal_control_value1, buffer + deserialized_size,
                                                 buffer_size - deserialized_size);

        deserialized_size += deserialize_float32(&command->longitudinal_control_value2, buffer + deserialized_size,
                                                 buffer_size - deserialized_size);

        deserialized_size += deserialize_uint8((uint8_t*)&command->gear_control_command, buffer + deserialized_size,
                                               buffer_size - deserialized_size);

        deserialized_size += deserialize_uint8((uint8_t*)&(command->reserved[0]), buffer + deserialized_size,
                                               buffer_size - deserialized_size);

        deserialized_size += deserialize_uint8((uint8_t*)&(command->reserved[1]), buffer + deserialized_size,
                                               buffer_size - deserialized_size);

        deserialized_size += deserialize_uint8((uint8_t*)&(command->reserved[2]), buffer + deserialized_size,
                                               buffer_size - deserialized_size);

        assert(deserialized_size == expected_size);

        rc = deserialized_size;
    }
    return rc;
}
