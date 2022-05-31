/**
 * @file chassis_state.h
 * @brief This header file defines ChassisState Object.
 * @author zhangjiannan(zhangjiannan@holomaitc.com)
 * @date 2019-8-12
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_C_COMMON_CHASSIS_STATE_H_
#define HOLO_C_COMMON_CHASSIS_STATE_H_

#include <holo_c/core/config.h>
#include <holo_c/core/retcode.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>
#include <holo_c/common/timestamp.h>
#include<stdio.h>
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Enumerate gear positions.
 */
enum GearPosition
{
    GEAR_POSITION_UNKNOWN = 0, ///< Gear at unknown position.
    GEAR_POSITION_P       = 1, ///< Gear at P position.
    GEAR_POSITION_R       = 2, ///< Gear at R position.
    GEAR_POSITION_N       = 3, ///< Gear at N position.
    GEAR_POSITION_D       = 4, ///< Gear at D position.
    GEAR_POSITION_S       = 5, ///< Gear at S position.
    GEAR_POSITION_INVALID = 6, ///< Gear at invalid position.
};

/**
 * @brief Enumerate actuator state.
 */
enum ActuatorState
{
    ACTUATOR_STATE_NOT_READY = 0, ///< Actuator is not ready.
    ACTUATOR_STATE_READY     = 1, ///< Actuator is ready.
    ACTUATOR_STATE_FAULT     = 2, ///< Actuator is in fault state.
    ACTUATOR_STATE_ACTIVE    = 3, ///< Actuator is active.
};

/**
 * @brief This structure describes information from vehicle chassis.
 */
struct ChassisState
{
    struct Timestamp stamp;

    /* Motion */
    float32_t vehicle_speed;               ///< Vehicle speed from vehicle chassis in m/s.
    float32_t front_left_wheel_speed;      ///< Front left wheel speed in m/s.
    float32_t front_right_wheel_speed;     ///< Front right wheel speed in m/s.
    float32_t rear_left_wheel_speed;       ///< Rear left wheel speed in m/s.
    float32_t rear_right_wheel_speed;      ///< Rear right wheel speed in m/s.
    float32_t longitudinal_acceleration;   ///< Acceleration in longitudinal direction.
    float32_t lateral_acceleration;        ///< Acceleration in latitudinal direction.
    float32_t yaw_rate;                    ///< Vehicle yaw rate at Z axis in rad/s^2
    float32_t front_wheel_angle;           ///< Front wheel angle in rad. Center is 0, positive value for turn left
    float32_t longitudinal_control_value;  ///< Longitudinal actuator output control value, m/s^2
    uint32_t  front_left_wheel_pulse;      ///< Front left wheel pulse counter.
    uint32_t  front_right_wheel_pulse;     ///< Front right wheel pulse counter.
    uint32_t  rear_left_wheel_pulse;       ///< Rear left wheel pulse counter.
    uint32_t  rear_right_wheel_pulse;      ///< Rear right wheel pulse counter.
	uint8_t   front_left_wheel_direction;  ///< front left wheel direction>
	uint8_t   front_right_wheel_direction; ///< front right wheel direction>
	uint8_t   rear_left_wheel_direction;   ///< rear left wheel direction>
	uint8_t   rear_right_wheel_direction;  ///< rear right wheel direction>
    uint8_t   vehicle_stand_still;         // 0:not standstill, 1: standstill
    uint8_t   brake_pedal_status;          // 0: not pressed, 1:pressed
	uint8_t   eps_apa_abortfeedback;
	uint8_t   eps_apa_sys_status;
	float32_t steering_wheel_angle;
    float32_t steering_torque;             // Steering Wheel Torque Value in Nm, Left: positive, Right: Negative.
    float32_t steering_angle_speed;        // Steering wheel rotation speed, rad/s.
    float32_t Accelerograph_depth;         // Accelerograph Depth in %.

    /** light system state */
    struct
    {
        uint16_t rear_fog_light:1;    ///< Rear fog light: 1=on, 0=off
        uint16_t front_fog_light:1;   ///< Front fog light: 1=on, 0=off
        uint16_t brake_light:1;       ///< Break light signal: 1=on, 0=off
        uint16_t high_beam:1;         ///< High beam light: 1=on, 0=off
        uint16_t low_beam:1;          ///< Low beam light: 1=on, 0=off
        uint16_t hazard_flasher:1;    ///< Warning blink signal: 1=on, 0=off
        uint16_t right_turn_signal:1; ///< Right turn signal: 1=on, 0=off
        uint16_t left_turn_signal:1;  ///< Left turn signal: 1=on, 0=off
        uint16_t reserved:8;
    } light_system_state;

    /** cockpit system state */
    struct
    {
        uint16_t rear_window_defroster:1;  ///< Rear window defroster: 1=open, 0=close
        uint16_t front_window_defroster:1; ///< Front window defroster: 1=open, 0=close
        uint16_t rear_wiper:1;             ///< Rear wiper: 1=open, 0=close
        uint16_t front_wiper:1;            ///< Front wiper: 1=open, 0=close
        uint16_t rear_right_window:1;      ///< Rear right window: 1=open, 0=close
        uint16_t rear_left_window:1;       ///< Rear left window: 1=open, 0=close
        uint16_t front_right_window:1;     ///< Front right window: 1=open, 0=close
        uint16_t front_left_window:1;      ///< Front left window: 1=open, 0=close
        uint16_t trunk_door:1;             ///< Trunk door: 1=open, 0=close
        uint16_t rear_right_door:1;        ///< Rear left door: 1=open, 0=close
        uint16_t rear_left_door:1;         ///< Rear right door: 1=open, 0=close
        uint16_t front_right_door:1;       ///< Front right door: 1=open, 0=close
        uint16_t front_left_door:1;        ///< Front left door: 1=open, 0=close
        uint16_t driver_seatbelt:1;        ///< Driver seat belt: 1=on, 0=off
        uint16_t reserved:2;
    } cockpit_system_state;

    /** Fuel or battery level in percetage. */
    uint8_t energy_source_level;

    /* gear */
    struct
    {
        uint8_t handbrake:1;     ///< Hand brake status: 1=hold, 0=release
        uint8_t gear_level:4;    ///< 0: Invalid, 1-15: gear level 1-15
        uint8_t gear_position:3; ///< See enum GearPosition for possible values.
    } gear_system_state;

    /* User op */
    struct
    {
        uint8_t lateral_takeover:1;      ///< User action to takeover lateral control.
        uint8_t longitudinal_takeover:1; ///< User action to takeover longitudinal control.
        uint8_t lateral_activate:1;      ///< User input command to activate lateral control.
        uint8_t longitudinal_activate:1; ///< User input command to activate longitudinal control.
        uint8_t reserved:4;
    } user_operation_state;

    /* Chassis actuator status */
    struct
    {
        uint8_t gear_actuator_ready:1;          ///< gear actuator ready flag.
        uint8_t gear_actuator_active:1;         ///< gear actuator active flag.
        uint8_t lateral_actuator_ready:1;       ///< lateral actuator ready flag.
        uint8_t lateral_actuator_active:1;      ///< lateral actuator active flag.
        uint8_t longitudinal_actuator_ready:1;  ///< longitudinal actuator ready flag.
        uint8_t longitudinal_actuator_active:1; ///< longitudinal actuator active flag.
        uint8_t reserved:2;
    } chassis_actuator_state;
};
HOLO_STATIC_ASSERT(sizeof(struct ChassisState) == 96);

/**
 * @brief Default constructor
 *
 * @param state The input chassis state object.
 *
 * @return RC_SUCCESS
 */
retcode_t chassis_state_init_default(struct ChassisState* state);

/**
 * @{
 * Begin getter API group.
 */

/**
 * @brief Get chassis state timestamp
 *
 * @param state The chassis state object.
 *
 * @return timestamp.
 */
static inline const struct Timestamp* chassis_state_get_timestamp(const struct ChassisState* state)
{
    return &state->stamp;
}

/**
 * @brief Get vehicle speed from vehicle chassis.
 *
 * @param state The chassis state object.
 *
 * @return Vehicle speed in @f$m/s@f$. Forward is positive direction.
 */
static inline float32_t chassis_state_get_vehicle_speed(const struct ChassisState* state)
{
    return state->vehicle_speed;
}

/**
 * @brief Get front left wheel speed from vehicle chassis.
 *
 * @param state The chassis state object.
 *
 * @return Front left wheel speed in @f$m/s@f$. Forward is positive direction.
 */
static inline float32_t chassis_state_get_front_left_wheel_speed(const struct ChassisState* state)
{
    return state->front_left_wheel_speed;
}

/**
 * @brief Get front right wheel speed from vehicle chassis.
 *
 * @param state The chassis state object.
 *
 * @return Front right wheel speed in @f$m/s@f$. Forward is positive direction.
 */
static inline float32_t chassis_state_get_front_right_wheel_speed(const struct ChassisState* state)
{
    return state->front_right_wheel_speed;
}

/**
 * @brief Get rear left wheel speed from vehicle chassis.
 *
 * @param state The chassis state object.
 *
 * @return Rear left wheel speed in @f$m/s@f$. Forward is positive direction.
 */
static inline float32_t chassis_state_get_rear_left_wheel_speed(const struct ChassisState* state)
{
    return state->rear_left_wheel_speed;
}

/**
 * @brief Get rear right wheel speed from vehicle chassis.
 *
 * @param state The chassis state object.
 *
 * @return Rear right wheel speed in @f$m/s@f$. Forward is positive direction.
 */
static inline float32_t chassis_state_get_rear_right_wheel_speed(const struct ChassisState* state)
{
    return state->rear_right_wheel_speed;
}

/**
 * @brief Get longitudinal acceleration from vehicle chassis.
 *
 * @param state The chassis state object.
 *
 * @return Longitudinal acceleration in @f$m/s^2@f$. Forward is positive direction.
 */
static inline float32_t chassis_state_get_longitudinal_acceleration(const struct ChassisState* state)
{
    return state->longitudinal_acceleration;
}

/**
 * @brief Get lateral acceleration from vehicle chassis.
 *
 * @param state The chassis state object.
 *
 * @return Lateral acceleration in @f$m/s^2@f$. Left is positive direction.
 */
static inline float32_t chassis_state_get_lateral_acceleration(const struct ChassisState* state)
{
    return state->lateral_acceleration;
}

/**
 * @brief Get raw rate from vehicle chassis.
 *
 * @param state The chassis state object.
 *
 * @return Yaw rate in @f$rad/s^2@f$.
 */
static inline float32_t chassis_state_get_yaw_rate(const struct ChassisState* state)
{
    return state->yaw_rate;
}

/**
 * @brief Get front wheel angle from vehicle chassis.
 *
 * @param state The chassis state object.
 *
 * @return Front wheel angle in @f$rad@f$. Left is positive direction.
 */
static inline float32_t chassis_state_get_front_wheel_angle(const struct ChassisState* state)
{
    return state->front_wheel_angle;
}

/**
 * @brief Get longitudinal control value vehicle chassis.
 *
 * @param state The chassis state object.
 *
 * @return longitudinal control value in @f$m/s^2@f$.
 */
static inline float32_t chassis_state_get_longitudinal_control_value(const struct ChassisState* state)
{
    return state->longitudinal_control_value;
}

/**
 * @brief Get light system state.
 *
 * @param state The chassis state object.
 *
 * @return Light state.
 */
static inline uint16_t chassis_state_get_light_state(const struct ChassisState* state)
{
    return  state->light_system_state.rear_fog_light    << 0 |
            state->light_system_state.front_fog_light   << 1 |
            state->light_system_state.brake_light       << 2 |
            state->light_system_state.high_beam         << 3 |
            state->light_system_state.low_beam          << 4 |
            state->light_system_state.hazard_flasher    << 5 |
            state->light_system_state.right_turn_signal << 6 |
            state->light_system_state.left_turn_signal  << 7;
}

/**
 * @brief Check if any signal(left turn signal, right turn signal, warn signal) light is on.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_signal_light_on(const struct ChassisState* state)
{
    return state->light_system_state.brake_light       ||
           state->light_system_state.hazard_flasher    ||
           state->light_system_state.right_turn_signal ||
           state->light_system_state.left_turn_signal  ;
}

/**
 * @brief Check if left turn light is on.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_left_turn_signal_on(const struct ChassisState* state)
{
    return state->light_system_state.left_turn_signal;
}

/**
 * @brief Check if right turn light is on.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_right_turn_signal_on(const struct ChassisState* state)
{
    return state->light_system_state.right_turn_signal;
}

/**
 * @brief Check if warn blink light is on.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_hazard_flasher_on(const struct ChassisState* state)
{
    return state->light_system_state.hazard_flasher;
}

/**
 * @brief Check if head light(low beam or high beam) is on.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_head_light_on(const struct ChassisState* state)
{
    return state->light_system_state.high_beam || state->light_system_state.low_beam;
}

/**
 * @brief Check if low beam is on.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_low_beam_on(const struct ChassisState* state)
{
    return state->light_system_state.low_beam;
}

/**
 * @brief Check if high beam is on.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_high_beam_on(const struct ChassisState* state)
{
    return state->light_system_state.high_beam;
}

/**
 * @brief Check if brake light is on.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_brake_light_on(const struct ChassisState* state)
{
    return state->light_system_state.brake_light;
}

/**
 * @brief Check if fog light is on.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_fog_light_on(const struct ChassisState* state)
{
    return state->light_system_state.front_fog_light || state->light_system_state.rear_fog_light;
}

/**
 * @brief Check if front fog light is on.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_front_fog_light_on(const struct ChassisState* state)
{
    return state->light_system_state.front_fog_light;
}

/**
 * @brief Check if rear fog light is on.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_rear_fog_light_on(const struct ChassisState* state)
{
    return state->light_system_state.rear_fog_light;
}

/**
 * @brief Get cockpit state. This state includes seatbelt, doors, windows, wipers and defrosters state.
 * @detail This API is mainly used for serialization and deserailzation.
 *
 * @param state The chassis state object.
 *
 * @return Cockpit state.
 */
static inline uint16_t chassis_state_get_cockpit_state(const struct ChassisState* state)
{
    return state->cockpit_system_state.rear_window_defroster  << 0  |
           state->cockpit_system_state.front_window_defroster << 1  |
           state->cockpit_system_state.rear_wiper             << 2  |
           state->cockpit_system_state.front_wiper            << 3  |
           state->cockpit_system_state.rear_right_window      << 4  |
           state->cockpit_system_state.rear_left_window       << 5  |
           state->cockpit_system_state.front_right_window     << 6  |
           state->cockpit_system_state.front_left_window      << 7  |
           state->cockpit_system_state.trunk_door             << 8  |
           state->cockpit_system_state.rear_right_door        << 9  |
           state->cockpit_system_state.rear_left_door         << 10 |
           state->cockpit_system_state.front_right_door       << 11 |
           state->cockpit_system_state.front_left_door        << 12 |
           state->cockpit_system_state.driver_seatbelt        << 13 ;
}

/**
 * @brief Check if driver seatbelt is locked.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_driver_seatbelt_locked(const struct ChassisState* state)
{
    return state->cockpit_system_state.driver_seatbelt;
}

/**
 * @brief Check if any door is open.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_door_open(const struct ChassisState* state)
{
    return state->cockpit_system_state.front_left_door  ||
           state->cockpit_system_state.front_right_door ||
           state->cockpit_system_state.rear_left_door   ||
           state->cockpit_system_state.rear_right_door  ||
           state->cockpit_system_state.trunk_door;
}

/**
 * @brief Check if front left door is open.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_front_left_door_open(const struct ChassisState* state)
{
    return state->cockpit_system_state.front_left_door;
}

/**
 * @brief Check if front right door is open.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_front_right_door_open(const struct ChassisState* state)
{
    return state->cockpit_system_state.front_right_door;
}

/**
 * @brief Check if rear left door is open.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_rear_left_door_open(const struct ChassisState* state)
{
    return state->cockpit_system_state.rear_left_door;
}

/**
 * @brief Check if rear right door is open.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_rear_right_door_open(const struct ChassisState* state)
{
    return state->cockpit_system_state.rear_right_door;
}

/**
 * @brief Check if trunk door is open.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_trunk_door_open(const struct ChassisState* state)
{
    return state->cockpit_system_state.trunk_door;
}

/**
 * @brief Check if any window is open.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_window_open(const struct ChassisState* state)
{
    return state->cockpit_system_state.front_left_window ||
           state->cockpit_system_state.front_right_window ||
           state->cockpit_system_state.rear_left_window ||
           state->cockpit_system_state.rear_right_window;
}

/**
 * @brief Check if front left window is open.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_front_left_window_open(const struct ChassisState* state)
{
    return state->cockpit_system_state.front_left_window;
}

/**
 * @brief Check if front rear window is open.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_front_right_window_open(const struct ChassisState* state)
{
    return state->cockpit_system_state.front_right_window;
}

/**
 * @brief Check if rear left window is open.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_rear_left_window_open(const struct ChassisState* state)
{
    return state->cockpit_system_state.rear_left_window;
}

/**
 * @brief Check if rear right window is open.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_rear_right_window_open(const struct ChassisState* state)
{
    return state->cockpit_system_state.rear_right_window;
}

/**
 * @brief Check if any wiper is on.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_wiper_on(const struct ChassisState* state)
{
    return state->cockpit_system_state.front_wiper ||
           state->cockpit_system_state.rear_wiper;
}

/**
 * @brief Check if front wiper is on.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_front_wiper_on(const struct ChassisState* state)
{
    return state->cockpit_system_state.front_wiper;
}

/**
 * @brief Check if rear wiper is on.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_rear_wiper_on(const struct ChassisState* state)
{
    return state->cockpit_system_state.rear_wiper;
}

/**
 * @brief Check if any window defroster is on.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_window_defroster_on(const struct ChassisState* state)
{
    return state->cockpit_system_state.front_window_defroster || state->cockpit_system_state.rear_window_defroster;
}

/**
 * @brief Check if front window defroster is on.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_front_window_defroster_on(const struct ChassisState* state)
{
    return state->cockpit_system_state.front_window_defroster;
}

/**
 * @brief Check if rear window defroster is on.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_rear_window_defroster_on(const struct ChassisState* state)
{
    return state->cockpit_system_state.rear_window_defroster;
}

/**
 * @brief Get energy source level(fuel level or battery level).
 *
 * @return Energy level percentage.
 */
static inline uint8_t chassis_state_get_energy_source_level(const struct ChassisState* state)
{
    return state->energy_source_level;
}

/**
 * @brief Get gear state.
 *
 * @param state The chassis state object.
 *
 * @return Gear state.
 */
static inline uint8_t chassis_state_get_gear_state(const struct ChassisState* state)
{
    return state->gear_system_state.handbrake     << 0 |
           state->gear_system_state.gear_level    << 1 |
           state->gear_system_state.gear_position << 5;
}

/**
 * @brief Get gear position.
 *
 * @param state The chassis state object.
 *
 * @return GearPosition.
 */
static inline enum GearPosition chassis_state_get_gear_position(const struct ChassisState* state)
{
    return (enum GearPosition)state->gear_system_state.gear_position;
}

/**
 * @brief Get gear level.
 *
 * @detail For gear position P, N, Gear level has no meaning. For gear position R, D and S, 
 * gear level means transmission level.
 *
 * @param state The chassis state object.
 *
 * @return Gear level.
 */
static inline uint8_t chassis_state_get_gear_level(const struct ChassisState* state)
{
    return state->gear_system_state.gear_level;
}

/**
 * @brief Check if hand brake is hold.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_handbrake_hold(const struct ChassisState* state)
{
    return state->gear_system_state.handbrake;
}

/**
 * @brief Get user operation state.
 *
 * @param state The chassis state object.
 *
 * @return User operation state.
 */
static inline uint8_t chassis_state_get_user_operation_state(const struct ChassisState* state)
{
    return state->user_operation_state.lateral_takeover      << 0 |
           state->user_operation_state.longitudinal_takeover << 1 |
           state->user_operation_state.lateral_activate      << 2 |
           state->user_operation_state.longitudinal_activate << 3;
}

/**
 * @brief Check if system is activated by user(driver).
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_system_activated(const struct ChassisState* state)
{
    return state->user_operation_state.longitudinal_activate || state->user_operation_state.lateral_activate;
}

/**
 * @brief Check if longitudinal control is activated by user(driver).
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_longitudinal_activated(const struct ChassisState* state)
{
    return state->user_operation_state.longitudinal_activate;
}

/**
 * @brief Check if lateral control is activated by user(driver).
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_lateral_activated(const struct ChassisState* state)
{
    return state->user_operation_state.lateral_activate;
}

/**
 * @brief Check if user(driver) has takeover vehicle control.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_driver_takeover(const struct ChassisState* state)
{
    return state->user_operation_state.longitudinal_takeover || 
           state->user_operation_state.lateral_takeover;
}

/**
 * @brief Check if user(driver) has takeover longitudinal control.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_longitudinal_takeover(const struct ChassisState* state)
{
    return state->user_operation_state.longitudinal_takeover;
}

/**
 * @brief Check if user(driver) has takeover lateral control.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_lateral_takeover(const struct ChassisState* state)
{
    return state->user_operation_state.lateral_takeover;
}

/**
 * @brief Get actuator state.
 *
 * @param state The chassis state object.
 *
 * @return Actuator state.
 */
static inline uint8_t chassis_state_get_actuator_state(const struct ChassisState* state)
{
    return state->chassis_actuator_state.gear_actuator_ready          << 0 |
           state->chassis_actuator_state.gear_actuator_active         << 1 |
           state->chassis_actuator_state.lateral_actuator_ready       << 2 |
           state->chassis_actuator_state.lateral_actuator_active      << 3 |
           state->chassis_actuator_state.longitudinal_actuator_ready  << 4 |
           state->chassis_actuator_state.longitudinal_actuator_active << 5;
}

/**
 * @brief Check if all actuators are in ready state.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_longitudinal_actuator_ready(const struct ChassisState* state)
{
    return state->chassis_actuator_state.longitudinal_actuator_ready;
}

/**
 * @brief Check if longitudinal actuators are in ready state.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_lateral_actuator_ready(const struct ChassisState* state)
{
    return state->chassis_actuator_state.lateral_actuator_ready;
}

/**
 * @brief Check if lateral actuators are in ready state.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_gear_actuator_ready(const struct ChassisState* state)
{
    return state->chassis_actuator_state.gear_actuator_ready;
}

/**
 * @brief Check if gear actuators are in ready state.
 *
 * @param state The chassis state object.
 *
 * @return true or false.
 */
static inline bool_t chassis_state_is_actuators_ready(const struct ChassisState* state)
{
    return chassis_state_is_longitudinal_actuator_ready(state) &&
           chassis_state_is_lateral_actuator_ready(state) &&
           chassis_state_is_gear_actuator_ready(state);
}

/**
 * @brief Get longitudinal actuator state.
 *
 * @param state The chassis state object.
 *
 * @return ActuatorState.
 */
static inline enum ActuatorState chassis_state_get_longitudinal_actuator_state(const struct ChassisState* state)
{
    return (enum ActuatorState)(state->chassis_actuator_state.longitudinal_actuator_ready |
                                state->chassis_actuator_state.longitudinal_actuator_active << 1);
}

/**
 * @brief Get lateral actuator state.
 *
 * @param state The chassis state object.
 *
 * @return ActuatorState.
 */
static inline enum ActuatorState chassis_state_get_lateral_actuator_state(const struct ChassisState* state)
{
    return (enum ActuatorState)(state->chassis_actuator_state.lateral_actuator_ready |
                                state->chassis_actuator_state.lateral_actuator_active << 1);
}

/**
 * @brief Get gear actuator state.
 *
 * @param state The chassis state object.
 *
 * @return ActuatorState.
 */
static inline enum ActuatorState chassis_state_get_gear_actuator_state(const struct ChassisState* state)
{
    return (enum ActuatorState)(state->chassis_actuator_state.gear_actuator_ready |
                                state->chassis_actuator_state.gear_actuator_active << 1);
}

/**
 * @}
 * End getter API group.
 */

/**
 * @{
 * Begin setter API group.
 */

/**
 * @brief Set chassis state timestamp.
 *
 * @param state The chassis state object.
 * @param stamp The timestamp object.
 */
static inline void chassis_state_set_timestamp(struct ChassisState* state, const struct Timestamp* stamp)
{
    state->stamp = *stamp;
}

/**
 * @brief Set vehicle speed.
 *
 * @param state The chassis state object.
 * @param value Vehicle speed in @f$m/s@f$. Forward is positive direction.
 */
static inline void chassis_state_set_vehicle_speed(struct ChassisState* state, float32_t value)
{
    state->vehicle_speed = value;
}

/**
 * @brief Set front left wheel speed.
 *
 * @param value Front left wheel speed in @f$m/s@f$. Forward is positive direction.
 */
static inline void chassis_state_set_front_left_wheel_speed(struct ChassisState* state, float32_t value)
{
    state->front_left_wheel_speed = value;
}

/**
 * @brief Set front right wheel speed.
 *
 * @param state The chassis state object.
 * @param value Front right wheel speed in @f$m/s@f$. Forward is positive direction.
 */
static inline void chassis_state_set_front_right_wheel_speed(struct ChassisState* state, float32_t value)
{
    state->front_right_wheel_speed = value;
}

/**
 * @brief Set rear left wheel speed.
 *
 * @param state The chassis state object.
 * @param value Rear left wheel speed in @f$m/s@f$. Forward is positive direction.
 */
static inline void chassis_state_set_rear_left_wheel_speed(struct ChassisState* state, float32_t value)
{
    state->rear_left_wheel_speed = value;
}

/**
 * @brief Set rear right wheel speed.
 *
 * @param state The chassis state object.
 * @param value Rear right wheel speed in @f$m/s@f$. Forward is positive direction.
 */
static inline void chassis_state_set_rear_right_wheel_speed(struct ChassisState* state, float32_t value)
{
    state->rear_right_wheel_speed = value;
}

/**
 * @brief Set longitudinal acceleration.
 *
 * @param state The chassis state object.
 * @param value Longitudinal acceleration in @f$m/s^2@f$. Forward is positive direction.
 */
static inline void chassis_state_set_longitudinal_acceleration(struct ChassisState* state, float32_t value)
{
    state->longitudinal_acceleration = value;
}

/**
 * @brief Set lateral acceleration.
 *
 * @param state The chassis state object.
 * @param value Lateral acceleration in @f$m/s^2@f$. Left is positive direction.
 */
static inline void chassis_state_set_lateral_acceleration(struct ChassisState* state, float32_t value)
{
    state->lateral_acceleration = value;
}

/**
 * @brief Set yaw rate.
 *
 * @param state The chassis state object.
 * @param value Yaw rate in @f$rad/s^2@f$.
 */
static inline void chassis_state_set_yaw_rate(struct ChassisState* state, float32_t value)
{
    state->yaw_rate = value;
}

/**
 * @brief Set front wheel angle.
 *
 * @param state The chassis state object.
 * @param value Front wheel angle in @f$rad@f$.
 */
static inline void chassis_state_set_front_wheel_angle(struct ChassisState* state, float32_t value)
{
    state->front_wheel_angle = value;
}

/**
 * @brief Set longitudinal control value
 *
 * @param state The chassis state object.
 * @param value longitudinal_control_value in @f$m/s^2@f$.
 */
static inline void chassis_state_set_longitudinal_control_value(struct ChassisState* state, float32_t value)
{
    state->longitudinal_control_value = value;
}

/**
 * @brief Set light state.
 *
 * @param state The chassis state object.
 * @param value Light state.
 */
static inline void chassis_state_set_light_state(struct ChassisState* state, uint16_t value)
{
    state->light_system_state.rear_fog_light = value >> 0;
    state->light_system_state.front_fog_light = value >> 1;
    state->light_system_state.brake_light = value >> 2;
    state->light_system_state.high_beam = value >> 3;
    state->light_system_state.low_beam = value >> 4;
    state->light_system_state.hazard_flasher = value >> 5;
    state->light_system_state.right_turn_signal = value >> 6;
    state->light_system_state.left_turn_signal = value >> 7;
}

/**
 * @brief Set vehicle signal light state.
 *
 * @param state The chassis state object.
 * @param left Left turn light signal. true means on, false otherwise.
 * @param right Right turn light signal. true means on, false otherwise.
 * @param warn Warn blink light signal. true means on, false otherwise.
 * @param brake Brake light signal. true means on, false otherwise.
 */
static inline void chassis_state_set_signal_light_state(
            struct ChassisState* state, 
            bool_t left, bool_t right, 
            bool_t warn, 
            bool_t brake)
{
    state->light_system_state.left_turn_signal = left;
    state->light_system_state.right_turn_signal = right;
    state->light_system_state.hazard_flasher = warn;
    state->light_system_state.brake_light = brake;
}

/**
 * @brief Set left turn light state.
 *
 * @param value true means light on, false otherwise.
 */
static inline void chassis_state_set_left_turn_signal(struct ChassisState* state, bool_t value)
{
    state->light_system_state.left_turn_signal = value;
}

/**
 * @brief Set right turn light state.
 *
 * @param state The chassis state object.
 * @param value true means light on, false otherwise.
 */
static inline void chassis_state_set_right_turn_signal(struct ChassisState* state, bool_t value)
{
    state->light_system_state.right_turn_signal = value;
}

/**
 * @brief Set warn blink light state.
 *
 * @param state The chassis state object.
 * @param value true means light on, false otherwise.
 */
static inline void chassis_state_set_hazard_flasher(struct ChassisState* state, bool_t value)
{
    state->light_system_state.hazard_flasher = value;
}

/**
 * @brief Set low beam state.
 *
 * @param state The chassis state object.
 * @param value true means light on, false otherwise.
 */
static inline void chassis_state_set_low_beam(struct ChassisState* state, bool_t value)
{
    state->light_system_state.low_beam = value;
}

/**
 * @brief Set high beam state.
 *
 * @param state The chassis state object.
 * @param value true means light on, false otherwise.
 */
static inline void chassis_state_set_high_beam(struct ChassisState* state, bool_t value)
{
    state->light_system_state.high_beam = value;
}

/**
 * @brief Set brake light state.
 *
 * @param state The chassis state object.
 * @param value true means light on, false otherwise.
 */
static inline void chassis_state_set_brake_light(struct ChassisState* state, bool_t value)
{
    state->light_system_state.brake_light = value;
}

/**
 * @brief Set front fog light state.
 *
 * @param state The chassis state object.
 * @param value true means light on, false otherwise.
 */
static inline void chassis_state_set_front_fog_light(struct ChassisState* state, bool_t value)
{
    state->light_system_state.front_fog_light = value;
}

/**
 * @brief Set rear fog light state.
 *
 * @param state The chassis state object.
 * @param value true means light on, false otherwise.
 */
static inline void chassis_state_set_rear_fog_light(struct ChassisState* state, bool_t value)
{
    state->light_system_state.rear_fog_light = value;
}

/**
 * @brief Set cockpit state. This state includes seatbelt, doors, windows, wipers and defrosters state.
 * @detail This API is mainly used for serialization and deserailzation.
 *
 * @param state The chassis state object.
 * @param value Cockpit state.
 */
static inline void chassis_state_set_cockpit_state(struct ChassisState* state, uint16_t value)
{
    state->cockpit_system_state.rear_window_defroster  = value >> 0;
    state->cockpit_system_state.front_window_defroster = value >> 1;
    state->cockpit_system_state.rear_wiper             = value >> 2;
    state->cockpit_system_state.front_wiper            = value >> 3;
    state->cockpit_system_state.rear_right_window      = value >> 4;
    state->cockpit_system_state.rear_left_window       = value >> 5;
    state->cockpit_system_state.front_right_window     = value >> 6;
    state->cockpit_system_state.front_left_window      = value >> 7;
    state->cockpit_system_state.trunk_door             = value >> 8;
    state->cockpit_system_state.rear_right_door        = value >> 9;
    state->cockpit_system_state.rear_left_door         = value >> 10;
    state->cockpit_system_state.front_right_door       = value >> 11;
    state->cockpit_system_state.front_left_door        = value >> 12;
    state->cockpit_system_state.driver_seatbelt        = value >> 13;
}

/**
 * @brief Set driver seatbelt state.
 *
 * @param state The chassis state object.
 * @param value true means locked, false otherwise.
 */
static inline void chassis_state_set_driver_seatbelt(struct ChassisState* state, bool_t value)
{
    state->cockpit_system_state.driver_seatbelt = value;
}

/**
 * @brief Set vehicle door state
 *
 * @param state The chassis state object.
 * @param fl Front left door state. true means open, false otherwise.
 * @param fr Front right door state. true means open, false otherwise.
 * @param rl Rear left door state. true means open, false otherwise.
 * @param rr Rear right door state. true means open, false otherwise.
 * @param trunk Trunk door state. true means open, false otherwise.
 */
static inline void chassis_state_set_door_state(
            struct ChassisState* state, bool_t fl, bool_t fr, bool_t rl, bool_t rr, bool_t trunk)
{
    state->cockpit_system_state.front_left_door = fl;
    state->cockpit_system_state.front_right_door = fr;
    state->cockpit_system_state.rear_left_door = rl;
    state->cockpit_system_state.rear_right_door = rr;
    state->cockpit_system_state.trunk_door = trunk;
}

/**
 * @brief Set front left door state.
 *
 * @param state The chassis state object.
 * @param value true means open, false otherwise.
 */
static inline void chassis_state_set_front_left_door(struct ChassisState* state, bool_t value)
{
    state->cockpit_system_state.front_left_door = value;
}

/**
 * @brief Set front right door state.
 *
 * @param state The chassis state object.
 * @param value true means open, false otherwise.
 */
static inline void chassis_state_set_front_right_door(struct ChassisState* state, bool_t value)
{
    state->cockpit_system_state.front_right_door = value;
}

/**
 * @brief Set rear left door state.
 *
 * @param state The chassis state object.
 * @param value true means open, false otherwise.
 */
static inline void chassis_state_set_rear_left_door(struct ChassisState* state, bool_t value)
{
    state->cockpit_system_state.rear_left_door = value;
}

/**
 * @brief Set rear right door state.
 *
 * @param state The chassis state object.
 * @param value true means open, false otherwise.
 */
static inline void chassis_state_set_rear_right_door(struct ChassisState* state, bool_t value)
{
    state->cockpit_system_state.rear_right_door = value;
}

/**
 * @brief Set trunk door state.
 *
 * @param state The chassis state object.
 * @param value true means open, false otherwise.
 */
static inline void chassis_state_set_trunk_door(struct ChassisState* state, bool_t value)
{
    state->cockpit_system_state.trunk_door = value;
}

/**
 * @brief Set vehicle windows state.
 *
 * @param state The chassis state object.
 * @param fl Front left window state. true means open, false otherwise.
 * @param fr Front right window state. true means open, false otherwise.
 * @param rl Rear left window state. true means open, false otherwise.
 * @param rr Rear right window state. true means open, false otherwise.
 */
static inline void chassis_state_set_window_state(struct ChassisState* state, 
                                                  bool_t fl, 
                                                  bool_t fr, 
                                                  bool_t rl, 
                                                  bool_t rr)
{
    state->cockpit_system_state.front_left_window = fl;
    state->cockpit_system_state.front_right_window = fr;
    state->cockpit_system_state.rear_left_window = rl;
    state->cockpit_system_state.rear_right_window = rr;
}

/**
 * @brief Set front left window state.
 *
 * @param state The chassis state object.
 * @param value true means open, false otherwise.
 */
static inline void chassis_state_set_front_left_window(struct ChassisState* state, bool_t value)
{
    state->cockpit_system_state.front_left_window = value;
}

/**
 * @brief Set front right window state.
 *
 * @param state The chassis state object.
 * @param value true means open, false otherwise.
 */
static inline void chassis_state_set_front_right_window(struct ChassisState* state, bool_t value)
{
    state->cockpit_system_state.front_right_window = value;
}

/**
 * @brief Set rear left window state.
 *
 * @param state The chassis state object.
 * @param value true means open, false otherwise.
 */
static inline void chassis_state_set_rear_left_window(struct ChassisState* state, bool_t value)
{
    state->cockpit_system_state.rear_left_window = value;
}

/**
 * @brief Set rear right window state.
 *
 * @param state The chassis state object.
 * @param value true means open, false otherwise.
 */
static inline void chassis_state_set_rear_right_window(struct ChassisState* state, bool_t value)
{
    state->cockpit_system_state.rear_right_window = value;
}

/**
 * @brief Set wiper state.
 *
 * @param state The chassis state object.
 * @param front Front wiper state. true means open, false otherwise.
 * @param rear Rear wiper state. true means open, false otherwise.
 */
static inline void chassis_state_set_wiper_state(struct ChassisState* state, bool_t front, bool_t rear)
{
    state->cockpit_system_state.front_wiper = front;
    state->cockpit_system_state.rear_wiper = rear;
}

/**
 * @brief Set front wiper state.
 *
 * @param state The chassis state object.
 * @param value true means open, false otherwise.
 */
static inline void chassis_state_set_front_wiper(struct ChassisState* state, bool_t value)
{
    state->cockpit_system_state.front_wiper = value;
}

/**
 * @brief Set rear wiper state.
 *
 * @param state The chassis state object.
 * @param value true means open, false otherwise.
 */
static inline void chassis_state_set_rear_wiper(struct ChassisState* state, bool_t value)
{
    state->cockpit_system_state.rear_wiper = value;
}

/**
 * @brief Set window defroster state.
 *
 * @param state The chassis state object.
 * @param front Front window defroster state. true means on, false otherwise.
 * @param rear Rear window defroster state true means on, false otherwise.
 */
static inline void chassis_state_set_window_defroster_state(struct ChassisState* state, bool_t front, bool_t rear)
{
    state->cockpit_system_state.front_window_defroster = front;
    state->cockpit_system_state.rear_window_defroster = rear;
}

/**
 * @brief Set front window defroster state.
 *
 * @param state The chassis state object.
 * @param value true means on, false otherwise.
 */
static inline void chassis_state_set_front_window_defroster(struct ChassisState* state, bool_t value)
{
    state->cockpit_system_state.front_window_defroster = value;
}

/**
 * @brief Set rear window defroster state.
 *
 * @param state The chassis state object.
 * @param value true means on, false otherwise.
 */
static inline void chassis_state_set_rear_window_defroster(struct ChassisState* state, bool_t value)
{
    state->cockpit_system_state.rear_window_defroster = value;
}

/**
 * @brief Set energy source level.
 *
 * @param state The chassis state object.
 * @param value energy source level in percentage. If value > 100, energy source level will set to 100%.
 */
static inline void chassis_state_set_energy_source_level(struct ChassisState* state, uint8_t value)
{
    state->energy_source_level = value > 100U ? 100U : value;
}

/**
 * @brief Set gear state.
 *
 * @param state The chassis state object.
 * @param value Gear state.
 */
static inline void chassis_state_set_gear_state(struct ChassisState* state, uint8_t value)
{
    state->gear_system_state.handbrake     = value >> 0;
    state->gear_system_state.gear_level    = value >> 1;
    state->gear_system_state.gear_position = value >> 5;
}

/**
 * @brief Set gear position.
 *
 * @param state The chassis state object.
 * @param value GearPosition.
 */
static inline void chassis_state_set_gear_position(struct ChassisState* state, enum GearPosition value)
{
    state->gear_system_state.gear_position = (uint8_t)value;
}

/**
 * @brief Set gear level.
 *
 * @detail For gear position P, N, Gear level has no meaning. For gear position R, D and S, 
 * gear level means transmission level.
 *
 * @param state The chassis state object.
 * @param value Gear level value in range [1, 15]. 0 means not applicable/not avaliable.
 */
static inline void chassis_state_set_gear_level(struct ChassisState* state, uint8_t value)
{
    state->gear_system_state.gear_level = value > 15U ? 15U : value;
}

/**
 * @brief Set hand brake state.
 *
 * @param state The chassis state object.
 * @param value true means hold, false otherwise.
 */
static inline void chassis_state_set_handbrake(struct ChassisState* state, bool_t value)
{
    state->gear_system_state.handbrake = value;
}

/**
 * @brief Set user operation state.
 *
 * @param state The chassis state object.
 * @param value User operation state value.
 */
static inline void chassis_state_set_user_operation_state(struct ChassisState* state, uint8_t value)
{
    state->user_operation_state.lateral_takeover = value >> 0;
    state->user_operation_state.longitudinal_takeover = value >> 1;
    state->user_operation_state.lateral_activate = value >> 2;
    state->user_operation_state.longitudinal_activate = value >> 3;
}

/**
 * @brief Set longitudinal activated state.
 *
 * @param state The chassis state object.
 * @param value true means user(driver) intention is activate longitudinal control. false otherwise.
 */
static inline void chassis_state_set_longitudinal_activated(struct ChassisState* state, bool_t value)
{
    state->user_operation_state.longitudinal_activate = value;
}

/**
 * @brief Set lateral activated state.
 *
 * @param state The chassis state object.
 * @param value true means user(driver) intention is activate longitudinal control. false otherwise.
 */
static inline void chassis_state_set_lateral_activated(struct ChassisState* state, bool_t value)
{
    state->user_operation_state.lateral_activate = value;
}

/**
 * @brief Set user(driver) has takeover longitudinal control.
 *
 * @param state The chassis state object.
 * @param value true means user(driver) has takeover longitudinal control. false otherwise.
 */
static inline void chassis_state_set_longitudinal_takeover(struct ChassisState* state, bool_t value)
{
    state->user_operation_state.longitudinal_takeover = value;
}

/**
 * @brief Set user(driver) has takeover lateral control.
 *
 * @param state The chassis state object.
 * @param value true means user(driver) has takeover lateral control. false otherwise.
 */
static inline void chassis_state_set_lateral_takeover(struct ChassisState* state, bool_t value)
{
    state->user_operation_state.lateral_takeover = value;
}

/**
 * @brief Set actuator state.
 *
 * @param state The chassis state object.
 * @param value Actuator state value.
 */
static inline void chassis_state_set_actuator_state(struct ChassisState* state, uint8_t value)
{
    state->chassis_actuator_state.gear_actuator_ready          = value >> 0;
    state->chassis_actuator_state.gear_actuator_active         = value >> 1;
    state->chassis_actuator_state.lateral_actuator_ready       = value >> 2;
    state->chassis_actuator_state.lateral_actuator_active      = value >> 3;
    state->chassis_actuator_state.longitudinal_actuator_ready  = value >> 4;
    state->chassis_actuator_state.longitudinal_actuator_active = value >> 5;
}

/**
 * @brief Set longitudinal actuator state.
 *
 * @param state The chassis state object.
 * @param value ActuatorState.
 */
static inline void chassis_state_set_longitudinal_actuator_state(struct ChassisState* state, enum ActuatorState value)
{
    state->chassis_actuator_state.longitudinal_actuator_ready = (uint8_t)value;
    state->chassis_actuator_state.longitudinal_actuator_active = (uint8_t)value >> 1;
}

/**
 * @brief Set lateral actuator state.
 *
 * @param state The chassis state object.
 * @param value ActuatorState.
 */
static inline void chassis_state_set_lateral_actuator_state(struct ChassisState* state, enum ActuatorState value)
{
    state->chassis_actuator_state.lateral_actuator_ready = (uint8_t)value;
    state->chassis_actuator_state.lateral_actuator_active = (uint8_t)value >> 1;
}

/**
 * @brief Set Gear actuator state.
 *
 * @param state The chassis state object.
 * @param value ActuatorState.
 */
static inline void chassis_state_set_gear_actuator_state(struct ChassisState* state, enum ActuatorState value)
{
    state->chassis_actuator_state.gear_actuator_ready = (uint8_t)value;
    state->chassis_actuator_state.gear_actuator_active = (uint8_t)value >> 1;
}
//20220220 fmh add for wima start
/**
 * @brief Get front_left_wheel_pulse.
 *
 * @param state The chassis state object.
 *
 * @return front_left_wheel_pulse.
 */
static inline uint32_t chassis_state_get_front_left_wheel_pulse(const struct ChassisState* state)
{
    return state->front_left_wheel_pulse;
}

/**
 * @brief Set front_left_wheel_pulse.
 *
 * @param state The chassis state object.
 * @param value front_left_wheel_pulse.
 */
static inline void chassis_state_set_front_left_wheel_pulse(struct ChassisState* state, uint32_t value)
{
    state->front_left_wheel_pulse = value;
}

/**
 * @brief Get front_right_wheel_pulse.
 *
 * @param state The chassis state object.
 *
 * @return front_right_wheel_pulse.
 */
static inline uint32_t chassis_state_get_front_right_wheel_pulse(const struct ChassisState* state)
{
    return state->front_right_wheel_pulse;
}

/**
 * @brief Set front_right_wheel_pulse.
 *
 * @param state The chassis state object.
 * @param value front_right_wheel_pulse.
 */
static inline void chassis_state_set_front_right_wheel_pulse(struct ChassisState* state, uint32_t value)
{
    state->front_right_wheel_pulse = value;
}

/**
 * @brief Get rear_left_wheel_pulse.
 *
 * @param state The chassis state object.
 *
 * @return rear_left_wheel_pulse.
 */
static inline uint32_t chassis_state_get_rear_left_wheel_pulse(const struct ChassisState* state)
{
    return state->rear_left_wheel_pulse;
}

/**
 * @brief Set rear_left_wheel_pulse.
 *
 * @param state The chassis state object.
 * @param value rear_left_wheel_pulse.
 */
static inline void chassis_state_set_rear_left_wheel_pulse(struct ChassisState* state, uint32_t value)
{
    state->rear_left_wheel_pulse = value;
}

/**
 * @brief Get rear_right_wheel_pulse.
 *
 * @param state The chassis state object.
 *
 * @return rear_right_wheel_pulse.
 */
static inline uint32_t chassis_state_get_rear_right_wheel_pulse(const struct ChassisState* state)
{
    return state->rear_right_wheel_pulse;
}

/**
 * @brief Set rear_right_wheel_pulse.
 *
 * @param state The chassis state object.
 * @param value rear_right_wheel_pulse.
 */
static inline void chassis_state_set_rear_right_wheel_pulse(struct ChassisState* state, uint32_t value)
{
    state->rear_right_wheel_pulse = value;
}

/**
 * @brief Get vehicle_stand_still.
 *
 * @param state The chassis state object.
 *
 * @return vehicle_stand_still.
 */
static inline uint8_t chassis_state_get_vehicle_stand_still(const struct ChassisState* state)
{
    return state->vehicle_stand_still;
}

/**
 * @brief Set vehicle_stand_still.
 *
 * @param state The chassis state object.
 * @param value vehicle_stand_still.
 */
static inline void chassis_state_set_vehicle_stand_still(struct ChassisState* state, uint8_t value)
{
    state->vehicle_stand_still = value;
}

/**
 * @brief Get brake_pedal_status.
 *
 * @param state The chassis state object.
 *
 * @return brake_pedal_status.
 */
static inline uint8_t chassis_state_get_brake_pedal_status(const struct ChassisState* state)
{
    return state->brake_pedal_status;
}

/**
 * @brief Set brake_pedal_status.
 *
 * @param state The chassis state object.
 * @param value brake_pedal_status.
 */
static inline void chassis_state_set_brake_pedal_status(struct ChassisState* state, uint8_t value)
{
    state->brake_pedal_status = value;
}

/**
 * @brief Get steering_torque.
 *
 * @param state The chassis state object.
 *
 * @return steering_torque.
 */
static inline float32_t chassis_state_get_steering_torque(const struct ChassisState* state)
{
    return state->steering_torque;
}

/**
 * @brief Set steering_torque.
 *
 * @param state The chassis state object.
 * @param value steering_torque.
 */
static inline void chassis_state_set_steering_torque(struct ChassisState* state, float32_t value)
{
    state->steering_torque = value;
}

/**
 * @brief Get steering_angle_speed.
 *
 * @param state The chassis state object.
 *
 * @return steering_angle_speed.
 */
static inline float32_t chassis_state_get_steering_angle_speed(const struct ChassisState* state)
{
    return state->steering_angle_speed;
}

/**
 * @brief Set steering_angle_speed.
 *
 * @param state The chassis state object.
 * @param value steering_angle_speed.
 */
static inline void chassis_state_set_steering_angle_speed(struct ChassisState* state, float32_t value)
{
    state->steering_angle_speed = value;
}

/**
 * @brief Get Accelerograph_depth.
 *
 * @param state The chassis state object.
 *
 * @return Accelerograph_depth.
 */
static inline float32_t chassis_state_get_Accelerograph_depth(const struct ChassisState* state)
{
    return state->Accelerograph_depth;
}

/**
 * @brief Set Accelerograph_depth.
 *
 * @param state The chassis state object.
 * @param value Accelerograph_depth.
 */
static inline void chassis_state_set_Accelerograph_depth(struct ChassisState* state, float32_t value)
{
    state->Accelerograph_depth = value;
}
//20220220 fmh add for wima end
/**
 * @}
 * End setter API group.
 */

/**
 * @{
 * Serialization/Deserialization API group.
 */

/**
 * @brief Get serialized buffer size. 
 *
 * @param state The ChassisState object.
 *
 * @return Serialized size.
 */
uint32_t chassis_state_get_serialized_size(const struct ChassisState* state);

/**
 * @brief Serialize ChassisState object to buffer. 
 *
 * @param state The ChassisState object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return Positive interger Number of bytes serialized into buffer.
 */
retcode_t chassis_state_serialize(const struct ChassisState* state, 
                                  uint8_t* buffer, 
                                  uint32_t buffer_size);

/**
 * @brief Deserialize ChassisState object from buffer. 
 *someip_apa01fer.
 *
 * @return RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return Positive integer Number of bytes deserialized from buffer.
 */
retcode_t chassis_state_deserialize(struct ChassisState* state, 
                                    const uint8_t* buffer, 
                                    uint32_t buffer_size);

/**
 * @}
 * End Serialization/Deserialization API group.
 */


#ifdef __cplusplus
}
#endif

#endif
