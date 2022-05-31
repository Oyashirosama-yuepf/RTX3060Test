/**
 * @file control_command.h
 * @brief This header file define control command.
 * @author lijiawen@holomatic.com
 * @date 2019-09-10
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *  notice.
 */

#ifndef HOLO_C_COMMON_CONTROL_COMMAND_H_
#define HOLO_C_COMMON_CONTROL_COMMAND_H_

#include <holo_c/common/chassis_state.h>
#include <holo_c/common/timestamp.h>
#include <holo_c/core/config.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Define lateral control model
 */
enum LateralControlModel
{
    LATERAL_CONTROL_MODEL_DISABLE           = 0U,
    LATERAL_CONTROL_MODEL_TORQUE            = 1U,
    LATERAL_CONTROL_MODEL_FRONT_WHEEL_ANGLE = 2U,
    LATERAL_CONTROL_MODEL_STEERING_ANGLE    = 3U,
};

/**
 * @brief Define longitudinal control model
 */
enum LongitudinalControlModel
{
    LONGITUDINAL_CONTROL_MODEL_DISABLE             = 0U,
    LONGITUDINAL_CONTROL_MODEL_ACCELERATE          = 1U,
    LONGITUDINAL_CONTROL_MODEL_ACCELERATION        = 1U,
    LONGITUDINAL_CONTROL_MODEL_DECELERATE          = 2U,
    LONGITUDINAL_CONTROL_MODEL_DECELERATION        = 2U,
    LONGITUDINAL_CONTROL_MODEL_TORQUE              = 3U,
    LONGITUDINAL_CONTROL_MODEL_TORQUE_DECELERATE   = 4U,
    LONGITUDINAL_CONTROL_MODEL_TORQUE_DECELERATION = 4U,
    LONGITUDINAL_CONTROL_MODEL_PARK                = 5U,
};

/**
 * @brief Define gear control model
 */
enum GearControlModel
{
    GEAR_CONTROL_MODEL_DISABLE      = 0U,
    GEAR_CONTROL_MODEL_GEAR_CONTROL = 1U,
};

/**
 * @brief this struct is used to describe the control command that sends to vehicle
 */
struct ControlCommand
{
    struct Timestamp stamp;  ///< timestamp

    enum LateralControlModel      lateral_control_model;
    enum LongitudinalControlModel longitudinal_control_model;
    enum GearControlModel         gear_control_model;

    float32_t lateral_control_value;
    float32_t longitudinal_control_value1;
    float32_t longitudinal_control_value2;

    /** Command for gear system. */
    struct
    {
        uint8_t handbrake : 1;      ///< Hand brake status: 1=hold, 0=release
        uint8_t gear_level : 4;     ///< 0: Invalid, 1-15: gear level 1-15
        uint8_t gear_position : 3;  ///< See enum GearPosition for possible values.
    } gear_control_command;

    uint8_t reserved[3];  ///< reserved for data alignment.
};
HOLO_STATIC_ASSERT(sizeof(struct ControlCommand) == 36UL);

/**
 * @brief initialize ControlCommand from default values
 *
 * @param command a ControlCommand
 */
void control_command_init_default(struct ControlCommand* command);

/**
 * @brief get the timestamp from ControlCommand
 *
 * @param controlcommand ControlCommand
 *
 * @return Timestamp
 */
const struct Timestamp* control_command_get_timestamp(const struct ControlCommand* controlcommand);

/**
 * @brief set the timestamp from ControlCommand
 *
 * @param controlcommand ControlCommand
 * @param stamp input timestamp
 */
void control_command_set_timestamp(struct ControlCommand* controlcommand, const struct Timestamp* stamp);

/**
 * @brief get the lateral control model from ControlCommand
 *
 * @param command a ControlCommand
 *
 * @return lateral control model
 */
enum LateralControlModel control_command_get_lateral_control_model(const struct ControlCommand* command);

/**
 * @brief set the lateral control model of ControlCommand
 *
 * @param command a ControlCommand
 * @param lateral_control_model The lateral control model to be set in
 */
void control_command_set_lateral_control_model(struct ControlCommand*         command,
                                               const enum LateralControlModel lateral_control_model);

/**
 * @brief get the longitudinal control model from ControlCommand
 *
 * @param command a ControlCommand
 *
 * @return longitudinal control model
 */
enum LongitudinalControlModel control_command_get_longitudinal_control_model(const struct ControlCommand* command);

/**
 * @brief set the longitudinal control model of ControlCommand
 *
 * @param command a ControlCommand
 * @param longitudinal_control_model The longitudinal control model to be set in
 */
void control_command_set_longitudinal_control_model(struct ControlCommand*              command,
                                                    const enum LongitudinalControlModel longitudinal_control_model);

/**
 * @brief get the gear control model from ControlCommand
 *
 * @param command a ControlCommand
 *
 * @return gear control model
 */
enum GearControlModel control_command_get_gear_control_model(const struct ControlCommand* command);

/**
 * @brief set the gear control model of ControlCommand
 *
 * @param command a ControlCommand
 * @param gear_control_model The gear control model to be set in
 */
void control_command_set_gear_control_model(struct ControlCommand*      command,
                                            const enum GearControlModel gear_control_model);

/**
 * @brief get the lateral control value from ControlCommand
 *
 * @details if the lateral control mode is LATERAL_CONTROL_MODEL_TORQUE, return value is the lateral torque of vehicle
 * [Nm],
 *
 * if the lateral control mode is LATERAL_CONTROL_MODEL_FRONT_WHEEL_ANGLE, return value is the front wheel angle of
 * vehicle [rad],
 *
 * if the lateral control mode is LATERAL_CONTROL_MODEL_STEERING_ANGLE, return value is the steering angle of vehicle
 * [rad]
 *
 * @param command a ControlCommand
 *
 * @return lateral control value
 */
float32_t control_command_get_lateral_control_value(const struct ControlCommand* command);

/**
 * @brief set the lateral control value of ControlCommand
 *
 * @details if the lateral control mode is LATERAL_CONTROL_MODEL_TORQUE, param value is the lateral torque of vehicle
 * [Nm],
 *
 * if the lateral control mode is LATERAL_CONTROL_MODEL_FRONT_WHEEL_ANGLE, param value is the front wheel angle of
 * vehicle [rad],
 *
 * if the lateral control mode is LATERAL_CONTROL_MODEL_STEERING_ANGLE, param value is the steering angle of vehicle
 * [rad]
 *
 * @param command a ControlCommand
 * @param lateral_control_value The lateral control value to be set in
 */
void control_command_set_lateral_control_value(struct ControlCommand* command, const float32_t lateral_control_value);

/**
 * @brief get the lateral torque from ControlCommand
 *
 * @param command a ControlCommand
 *
 * @return lateral torque
 */
float32_t control_command_get_lateral_torque(const struct ControlCommand* command);

/**
 * @brief set the lateral torque of ControlCommand
 *
 * @param command a ControlCommand
 * @param lateral_torque The lateral torque to be set in
 */
void control_command_set_lateral_torque(struct ControlCommand* command, const float32_t lateral_torque);

/**
 * @brief get the lateral front wheel angle from ControlCommand
 *
 * @param command a ControlCommand
 *
 * @return front wheel angle
 */
float32_t control_command_get_lateral_front_wheel_angle(const struct ControlCommand* command);

/**
 * @brief set the lateral front wheel angle of ControlCommand
 *
 * @param command a ControlCommand
 * @param front_wheel_angle The front wheel angle to be set in
 */
void control_command_set_lateral_front_wheel_angle(struct ControlCommand* command, const float32_t front_wheel_angle);

/**
 * @brief get the lateral steering angle from ControlCommand
 *
 * @param command a ControlCommand
 *
 * @return steering_angle
 */
float32_t control_command_get_lateral_steering_angle(const struct ControlCommand* command);

/**
 * @brief set the lateral steering angle of ControlCommand
 *
 * @param command a ControlCommand
 * @param steering_angle The steering angle to be set in
 */
void control_command_set_lateral_steering_angle(struct ControlCommand* command, const float32_t steering_angle);

/**
 * @brief get the longitudinal control value1 from ControlCommand
 *
 * @details if the longitudinal control mode is LONGITUDINAL_CONTROL_MODEL_ACCELERATE, return value is the acceleration
 * of the vehicle [m/s^2],
 *
 * if the longitudinal control mode is LONGITUDINAL_CONTROL_MODEL_DECELERATE, return value is the deceleration of the
 * vehicle [m/s^2],
 *
 * if the longitudinal control mode is LONGITUDINAL_CONTROL_MODEL_TORQUE, return value is the longitudinal torque of the
 * vehicle [Nm],
 *
 * if the longitudinal control mode is LONGITUDINAL_CONTROL_MODEL_TORQUE_DECELERATE, return value is the longitudinal
 * torque deceleration of vehicle, if the longitudinal control mode is LONGITUDINAL_CONTROL_MODEL_PARK, return value is
 * the speed limit [m/s]
 *
 * @param command a ControlCommand
 *
 * @return longitudinal control value1
 */
float32_t control_command_get_longitudinal_control_value1(const struct ControlCommand* command);

/**
 * @brief set the longitudinal control value1 of ControlCommand
 *
 * @details if the longitudinal control mode is LONGITUDINAL_CONTROL_MODEL_ACCELERATE, param value is the acceleration
 * of the vehicle [m/s^2]（0.0<=param<=4.0）
 *
 * if the longitudinal control mode is LONGITUDINAL_CONTROL_MODEL_DECELERATE, param value is the deceleration of the
 * vehicle [m/s^2] （-4.0<=param<=0.0）
 *
 * if the longitudinal control mode is LONGITUDINAL_CONTROL_MODEL_TORQUE, param value is the longitudinal torque of the
 * vehicle [Nm] （0.0<=param<=1000.0）
 *
 * if the longitudinal control mode is LONGITUDINAL_CONTROL_MODEL_TORQUE_DECELERATE, param value is the longitudinal
 * torque deceleration of vehicle （-100.0<=param<=0.0）
 *
 * if the longitudinal control mode is LONGITUDINAL_CONTROL_MODEL_PARK, param value is the speed limit [m/s]
 * （0.0<=param<-3.0）
 *
 * @param command a ControlCommand
 * @param longitudinal_control_value1 The longitudinal control value1 to be set in
 */
void control_command_set_longitudinal_control_value1(struct ControlCommand* command,
                                                     const float32_t        longitudinal_control_value1);
/**
 * @brief get the longitudinal control value2 from ControlCommand
 *
 * @details if the longitudinal control mode is LONGITUDINAL_CONTROL_MODEL_ACCELERATE, return value is no meaning
 *
 * if the longitudinal control mode is LONGITUDINAL_CONTROL_MODEL_DECELERATE, return value is no meaning
 *
 * if the longitudinal control mode is LONGITUDINAL_CONTROL_MODEL_TORQUE, return value is no meaning
 *
 * if the longitudinal control mode is LONGITUDINAL_CONTROL_MODEL_TORQUE_DECELERATE, return value is no meaning
 *
 * if the longitudinal control mode is LONGITUDINAL_CONTROL_MODEL_PARK, return value is the stop distance [m]
 *
 * @param command a ControlCommand
 *
 * @return longitudinal control value2
 */
float32_t control_command_get_longitudinal_control_value2(const struct ControlCommand* command);

/**
 * @brief set the longitudinal control value2 of ControlCommand
 *
 * @details if the longitudinal control mode is LONGITUDINAL_CONTROL_MODEL_ACCELERATE, param value is no meaning
 *
 * if the longitudinal control mode is LONGITUDINAL_CONTROL_MODEL_DECELERATE, param value is no meaning
 *
 * if the longitudinal control mode is LONGITUDINAL_CONTROL_MODEL_TORQUE, param value is no meaning
 *
 * if the longitudinal control mode is LONGITUDINAL_CONTROL_MODEL_TORQUE_DECELERATE, param value is no meaning
 *
 * if the longitudinal control mode is LONGITUDINAL_CONTROL_MODEL_PARK, param value is the stop distance [m]
 * （0.0<=param<=100.0）
 *
 * @param command a ControlCommand
 * @param longitudinal_control_value2 The longitudinal control value2 to be set in
 */
void control_command_set_longitudinal_control_value2(struct ControlCommand* command,
                                                     const float32_t        longitudinal_control_value1);
/**
 * @brief get the longitudinal acceleration from ControlCommand
 *
 * @param command a ControlCommand
 *
 * @return acceleration
 */
float32_t control_command_get_longitudinal_acceleration(const struct ControlCommand* command);

/**
 * @brief set the longitudinal acceleration of ControlCommand
 *
 * @param command a ControlCommand
 * @param acceleration The acceleration to be set in
 */
void control_command_set_longitudinal_acceleration(struct ControlCommand* command, const float32_t acceleration);

/**
 * @brief get the longitudinal deceleration from ControlCommand
 *
 * @param command a ControlCommand
 *
 * @return deceleration
 */
float32_t control_command_get_longitudinal_deceleration(const struct ControlCommand* command);

/**
 * @brief set the longitudinal deceleration of ControlCommand
 *
 * @param command a ControlCommand
 * @param deceleration The deceleration to be set in
 */
void control_command_set_longitudinal_deceleration(struct ControlCommand* command, const float32_t deceleration);

/**
 * @brief get the longitudinal torque from ControlCommand
 *
 * @param command a ControlCommand
 *
 * @return torque
 */
float32_t control_command_get_longitudinal_torque(const struct ControlCommand* command);

/**
 * @brief set the longitudinal torque of ControlCommand
 *
 * @param command a ControlCommand
 * @param torque The torque to be set in
 */
void control_command_set_longitudinal_torque(struct ControlCommand* command, const float32_t torque);

/**
 * @brief get the longitudinal torque deceleration from ControlCommand
 *
 * @param command a ControlCommand
 *
 * @return torque deceleration
 */
float32_t control_command_get_longitudinal_torque_deceleration(const struct ControlCommand* command);

/**
 * @brief set the longitudinal torque deceleration of ControlCommand
 *
 * @param command a ControlCommand
 * @param torque_deceleration The torque deceleration to be set in
 */
void control_command_set_longitudinal_torque_deceleration(struct ControlCommand* command,
                                                          const float32_t        torque_deceleration);

/**
 * @brief get the longitudinal speed limit from ControlCommand
 *
 * @param command a ControlCommand
 *
 * @return speed limit
 */
float32_t control_command_get_longitudinal_speed_limit(const struct ControlCommand* command);

/**
 * @brief set the longitudinal speed limit of ControlCommand
 *
 * @param command a ControlCommand
 * @param speed_limit The speed limit to be set in
 */
void control_command_set_longitudinal_speed_limit(struct ControlCommand* command, const float32_t speed_limit);

/**
 * @brief get the longitudinal stop distance from ControlCommand
 *
 * @param command a ControlCommand
 *
 * @return stop distance
 */
float32_t control_command_get_longitudinal_stop_distance(const struct ControlCommand* command);

/**
 * @brief set the longitudinal stop distance of ControlCommand
 *
 * @param command a ControlCommand
 * @param stop_distance The stop distance to be set in
 */
void control_command_set_longitudinal_stop_distance(struct ControlCommand* command, const float32_t stop_distance);

/**
 * @brief Get gear system control command.
 *
 * @param command The ControlCommand object.
 *
 * @return Gear system control command.
 */
uint8_t control_command_get_gear_command(const struct ControlCommand* command);

/**
 * @brief Set gear system control command.
 *
 * @param command The ControlCommand object.
 * @param value Gear system control command.
 */
void control_command_set_gear_command(struct ControlCommand* command, const uint8_t value);

/**
 * @brief get the gear_position of ControlCommand
 *
 * @param command a ControlCommand
 *
 * @return gear_position
 */
enum GearPosition control_command_get_gear_position(const struct ControlCommand* command);

/**
 * @brief set the gear_position of ControlCommand
 *
 * @param command a ControlCommand
 * @param gear_position The gear_position to be set in.
 */
void control_command_set_gear_position(struct ControlCommand* command, const enum GearPosition value);

/**
 * @brief get the gear_level of ControlCommand
 *
 * @param command a ControlCommand
 *
 * @return gear_level
 */
uint8_t control_command_get_gear_level(const struct ControlCommand* command);

/**
 * @brief set the gear_level of ControlCommand
 *
 * @param command a ControlCommand
 * @param gear_level The gear_level to be set in.
 */
void control_command_set_gear_level(struct ControlCommand* command, const uint8_t value);

/**
 * @brief get the handbrake of ControlCommand
 *
 * @param command a ControlCommand
 *
 * @return handbrake
 */
bool_t control_command_get_handbrake(const struct ControlCommand* command);

/**
 * @brief set the handbrake of ControlCommand
 *
 * @param command a ControlCommand
 * @param handbrake The handbrake to be set in.
 */
void control_command_set_handbrake(struct ControlCommand* command, const bool_t value);

/**
 * @brief Get serialized buffer size for control_command. Alignment is base on project configuration.
 * @detail Alignment is define by HOLO_CONFIG_SERIALIZATION_ALIGNMENT macro.
 *
 * @param command The control_command object.
 *
 * @return Serialized size
 */
uint32_t control_command_get_serialized_size(const struct ControlCommand* command);
/**
 * @brief Serialize control_command. Alignment is base on project configuration.
 * @detail The buffer alignment is define by HOLO_CONFIG_SERIALIZATION_ALIGNMENT macro.
 *
 * @param command The control_command object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW if buffer_size is smaller than needed.
 * @return Positive integer Number of bytes serialized into buffer
 */
retcode_t control_command_serialize(const struct ControlCommand* command, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize control_command object. Alignment is base on project configuration.
 * @detail The buffer alignment is define by HOLO_CONFIG_SERIALIZATION_ALIGNMENT macro.
 *
 * @param command The control_command object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_BUFFER_UNDERFLOW if buffer_size is smaller than needed.
 * @return Positive integer Number of bytes deserialized from buffer
 */
retcode_t control_command_deserialize(struct ControlCommand* command, const uint8_t* buffer, uint32_t buffer_size);

#ifdef __cplusplus
}
#endif

#endif
