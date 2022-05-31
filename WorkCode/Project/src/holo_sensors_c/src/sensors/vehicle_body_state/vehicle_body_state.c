/*!
 * @file vehicle_body_state.c
 * @brief This source file implements vehicle body state functions
 * @author liuya@holomatic.com
 * @date 2019-03-13
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <assert.h>
#include <holo_c/sensors/vehicle_body_state/vehicle_body_state.h>
#include <holo_c/utils/serialization.h>
#include <math.h>
#include <string.h>

retcode_t vehicle_body_state_init_default(struct VehicleBodyState* state)
{
    memset(state, 0, sizeof(struct VehicleBodyState));

    return RC_SUCCESS;
}

struct Timestamp const* vehicle_body_state_get_timestamp(struct VehicleBodyState const* state)
{
    return &state->stamp;
}

float32_t vehicle_body_state_get_temperature(struct VehicleBodyState const* state)
{
    return state->temperature;
}
float32_t vehicle_body_state_get_accelerator_pedal(struct VehicleBodyState const* state)
{
    return state->accelerator_pedal;
}
float32_t vehicle_body_state_get_front_left_tire_pressure(struct VehicleBodyState const* state)
{
    return state->front_left_tire_pressure;
}
float32_t vehicle_body_state_get_front_right_tire_pressure(struct VehicleBodyState const* state)
{
    return state->front_right_tire_pressure;
}
float32_t vehicle_body_state_get_rear_left_tire_pressure(struct VehicleBodyState const* state)
{
    return state->rear_left_tire_pressure;
}
float32_t vehicle_body_state_get_rear_right_tire_pressure(struct VehicleBodyState const* state)
{
    return state->rear_right_tire_pressure;
}

static bool_t get_state(struct VehicleBodyState const* state, enum VehicleBodyStateFlag flag)
{
    return ((state->flags & (1U << flag)) > 0U);
}

bool_t vehicle_body_state_get_state(struct VehicleBodyState const* state, enum VehicleBodyStateFlag flag)
{
    return get_state(state, flag);
}

bool_t vehicle_body_state_get_rear_fog_light(struct VehicleBodyState const* state)
{
    return get_state(state, VEHICLE_BODY_STATE_FLAG_REAR_FOG_LIGHT_ON);
}
bool_t vehicle_body_state_get_front_fog_light(struct VehicleBodyState const* state)
{
    return get_state(state, VEHICLE_BODY_STATE_FLAG_FRONT_FOG_LIGHT_ON);
}
bool_t vehicle_body_state_get_brake_light(struct VehicleBodyState const* state)
{
    return get_state(state, VEHICLE_BODY_STATE_FLAG_BRAKE_LIGHT_ON);
}
bool_t vehicle_body_state_get_high_beam(struct VehicleBodyState const* state)
{
    return get_state(state, VEHICLE_BODY_STATE_FLAG_HIGH_BEAM_ON);
}
bool_t vehicle_body_state_get_low_beam(struct VehicleBodyState const* state)
{
    return get_state(state, VEHICLE_BODY_STATE_FLAG_LOW_BEAM_ON);
}
bool_t vehicle_body_state_get_hazard_flasher(struct VehicleBodyState const* state)
{
    return get_state(state, VEHICLE_BODY_STATE_FLAG_HARZARD_FLASHER_ON);
}
bool_t vehicle_body_state_get_right_turn_signal(struct VehicleBodyState const* state)
{
    return get_state(state, VEHICLE_BODY_STATE_FLAG_RIGHT_TURN_SIGNAL_ON);
}
bool_t vehicle_body_state_get_left_turn_signal(struct VehicleBodyState const* state)
{
    return get_state(state, VEHICLE_BODY_STATE_FLAG_LEFT_TURN_SIGNAL_ON);
}

uint32_t vehicle_body_state_get_light_state(struct VehicleBodyState const* state)
{
    uint32_t mask =
        (1U << VEHICLE_BODY_STATE_FLAG_LEFT_TURN_SIGNAL_ON) | (1U << VEHICLE_BODY_STATE_FLAG_RIGHT_TURN_SIGNAL_ON) |
        (1U << VEHICLE_BODY_STATE_FLAG_HARZARD_FLASHER_ON) | (1U << VEHICLE_BODY_STATE_FLAG_LOW_BEAM_ON) |
        (1U << VEHICLE_BODY_STATE_FLAG_HIGH_BEAM_ON) | (1U << VEHICLE_BODY_STATE_FLAG_BRAKE_LIGHT_ON) |
        (1U << VEHICLE_BODY_STATE_FLAG_FRONT_FOG_LIGHT_ON) | (1U << VEHICLE_BODY_STATE_FLAG_REAR_FOG_LIGHT_ON);
    return state->flags & mask;
}

bool_t vehicle_body_state_get_rear_right_window(struct VehicleBodyState const* state)
{
    return get_state(state, VEHICLE_BODY_STATE_FLAG_REAR_RIGHT_WINDOW_OPEN);
}
bool_t vehicle_body_state_get_rear_left_window(struct VehicleBodyState const* state)
{
    return get_state(state, VEHICLE_BODY_STATE_FLAG_REAR_LEFT_WINDOW_OPEN);
}
bool_t vehicle_body_state_get_front_right_window(struct VehicleBodyState const* state)
{
    return get_state(state, VEHICLE_BODY_STATE_FLAG_FRONT_RIGHT_WINDOW_OPEN);
}
bool_t vehicle_body_state_get_front_left_window(struct VehicleBodyState const* state)
{
    return get_state(state, VEHICLE_BODY_STATE_FLAG_FRONT_LEFT_WINDOW_OPEN);
}
bool_t vehicle_body_state_get_auto_sunroof(struct VehicleBodyState const* state)
{
    return get_state(state, VEHICLE_BODY_STATE_FLAG_SUNROOF_WINDOW_OPEN);
}
bool_t vehicle_body_state_get_trunk_door(struct VehicleBodyState const* state)
{
    return get_state(state, VEHICLE_BODY_STATE_FLAG_TRUNK_DOOR_OPEN);
}
bool_t vehicle_body_state_get_car_hood(struct VehicleBodyState const* state)
{
    return get_state(state, VEHICLE_BODY_STATE_FLAG_CAR_HOOD_OPEN);
}
bool_t vehicle_body_state_get_rear_right_door(struct VehicleBodyState const* state)
{
    return get_state(state, VEHICLE_BODY_STATE_FLAG_REAR_RIGHT_DOOR_OPEN);
}
bool_t vehicle_body_state_get_rear_left_door(struct VehicleBodyState const* state)
{
    return get_state(state, VEHICLE_BODY_STATE_FLAG_REAR_LEFT_DOOR_OPEN);
}
bool_t vehicle_body_state_get_front_right_door(struct VehicleBodyState const* state)
{
    return get_state(state, VEHICLE_BODY_STATE_FLAG_FRONT_RIGHT_DOOR_OPEN);
}
bool_t vehicle_body_state_get_front_left_door(struct VehicleBodyState const* state)
{
    return get_state(state, VEHICLE_BODY_STATE_FLAG_FRONT_LEFT_DOOR_OPEN);
}
bool_t vehicle_body_state_get_driver_seatbelt(struct VehicleBodyState const* state)
{
    return get_state(state, VEHICLE_BODY_STATE_FLAG_DRIVER_SEATBELT_UNLOCK);
}
bool_t vehicle_body_state_get_passenger_seatbelt(struct VehicleBodyState const* state)
{
    return get_state(state, VEHICLE_BODY_STATE_FLAG_PASSENGER_SEATBELT_UNLOCK);
}
bool_t vehicle_body_state_get_front_wiper_state(struct VehicleBodyState const* state)
{
    return get_state(state, VEHICLE_BODY_STATE_FLAG_FRONT_WIPER_ON);
}
bool_t vehicle_body_state_get_rear_wiper_state(struct VehicleBodyState const* state)
{
    return get_state(state, VEHICLE_BODY_STATE_FLAG_REAR_WIPER_ON);
}
uint32_t vehicle_body_state_get_cockpit_state(struct VehicleBodyState const* state)
{
    uint32_t mask =
        (1U << VEHICLE_BODY_STATE_FLAG_REAR_RIGHT_WINDOW_OPEN) | (1U << VEHICLE_BODY_STATE_FLAG_REAR_LEFT_WINDOW_OPEN) |
        (1U << VEHICLE_BODY_STATE_FLAG_FRONT_RIGHT_WINDOW_OPEN) |
        (1U << VEHICLE_BODY_STATE_FLAG_FRONT_LEFT_WINDOW_OPEN) | (1U << VEHICLE_BODY_STATE_FLAG_SUNROOF_WINDOW_OPEN) |
        (1U << VEHICLE_BODY_STATE_FLAG_TRUNK_DOOR_OPEN) | (1U << VEHICLE_BODY_STATE_FLAG_CAR_HOOD_OPEN) |
        (1U << VEHICLE_BODY_STATE_FLAG_REAR_RIGHT_DOOR_OPEN) | (1U << VEHICLE_BODY_STATE_FLAG_REAR_LEFT_DOOR_OPEN) |
        (1U << VEHICLE_BODY_STATE_FLAG_FRONT_RIGHT_DOOR_OPEN) | (1U << VEHICLE_BODY_STATE_FLAG_FRONT_LEFT_DOOR_OPEN) |
        (1U << VEHICLE_BODY_STATE_FLAG_DRIVER_SEATBELT_UNLOCK) |
        (1U << VEHICLE_BODY_STATE_FLAG_PASSENGER_SEATBELT_UNLOCK) | (1U << VEHICLE_BODY_STATE_FLAG_FRONT_WIPER_ON) |
        (1U << VEHICLE_BODY_STATE_FLAG_REAR_WIPER_ON);

    return state->flags & mask;
}

uint32_t vehicle_body_state_get_state_flags(struct VehicleBodyState* state)
{
    return state->flags;
}

bool_t vehicle_body_state_get_button_set(struct VehicleBodyState const* state)
{
    return state->steering_button_state.button_set;
}
bool_t vehicle_body_state_get_button_res(struct VehicleBodyState const* state)
{
    return state->steering_button_state.button_res;
}
bool_t vehicle_body_state_get_button_plus(struct VehicleBodyState const* state)
{
    return state->steering_button_state.button_plus;
}
bool_t vehicle_body_state_get_button_minus(struct VehicleBodyState const* state)
{
    return state->steering_button_state.button_minus;
}
bool_t vehicle_body_state_get_button_mode(struct VehicleBodyState const* state)
{
    return state->steering_button_state.button_mode;
}
bool_t vehicle_body_state_get_button_io(struct VehicleBodyState const* state)
{
    return state->steering_button_state.button_io;
}
bool_t vehicle_body_state_get_button_volume_up(struct VehicleBodyState const* state)
{
    return state->steering_button_state.button_volume_up;
}
bool_t vehicle_body_state_get_button_volume_down(struct VehicleBodyState const* state)
{
    return state->steering_button_state.button_volume_down;
}
bool_t vehicle_body_state_get_button_voice(struct VehicleBodyState const* state)
{
    return state->steering_button_state.button_voice;
}
uint16_t vehicle_body_state_get_button_state(struct VehicleBodyState const* state)
{
    uint16_t button_state = 0;

    button_state =
        (state->steering_button_state.button_set << 0 | state->steering_button_state.button_res << 1 |
         state->steering_button_state.button_plus << 2 | state->steering_button_state.button_minus << 3 |
         state->steering_button_state.button_mode << 4 | state->steering_button_state.button_io << 5 |
         state->steering_button_state.button_volume_up << 6 | state->steering_button_state.button_volume_down << 7 |
         state->steering_button_state.button_voice << 8);

    return button_state;
}

uint16_t vehicle_body_state_get_rainfall(struct VehicleBodyState const* state)
{
    return state->rain_fall;
}

void vehicle_body_state_set_timestamp(struct VehicleBodyState* state, struct Timestamp const* stamp)
{
    state->stamp = *stamp;
}

void vehcile_body_state_set_temperature(struct VehicleBodyState* state, float32_t const value)
{
    state->temperature = value;
}
void vehicle_body_state_set_accelerator_pedal(struct VehicleBodyState* state, float32_t const value)
{
    state->accelerator_pedal = value;
}
void vehicle_body_state_set_front_left_tire_pressure(struct VehicleBodyState* state, float32_t const value)
{
    state->front_left_tire_pressure = value;
}
void vehicle_body_state_set_front_right_tire_pressure(struct VehicleBodyState* state, float32_t const value)
{
    state->front_right_tire_pressure = value;
}
void vehicle_body_state_set_rear_left_tire_pressure(struct VehicleBodyState* state, float32_t const value)
{
    state->rear_left_tire_pressure = value;
}
void vehicle_body_state_set_rear_right_tire_pressure(struct VehicleBodyState* state, float32_t const value)
{
    state->rear_right_tire_pressure = value;
}

static void set_state(struct VehicleBodyState* state, enum VehicleBodyStateFlag flag)
{
    state->flags |= (1U << flag);
}

static void reset_state(struct VehicleBodyState* state, enum VehicleBodyStateFlag flag)
{
    state->flags &= ~(1U << flag);
}

void vehicle_body_state_set_state(struct VehicleBodyState* state, enum VehicleBodyStateFlag flag)
{
    set_state(state, flag);
}

void vehicle_body_state_reset_state(struct VehicleBodyState* state, enum VehicleBodyStateFlag flag)
{
    reset_state(state, flag);
}

void vehicle_body_state_set_rear_fog_light(struct VehicleBodyState* state, bool_t const value)
{
    value ? set_state(state, VEHICLE_BODY_STATE_FLAG_REAR_FOG_LIGHT_ON) :
            reset_state(state, VEHICLE_BODY_STATE_FLAG_REAR_FOG_LIGHT_ON);
}
void vehicle_body_state_set_front_fog_light(struct VehicleBodyState* state, bool_t const value)
{
    value ? set_state(state, VEHICLE_BODY_STATE_FLAG_FRONT_FOG_LIGHT_ON) :
            reset_state(state, VEHICLE_BODY_STATE_FLAG_FRONT_FOG_LIGHT_ON);
}
void vehicle_body_state_set_brake_light(struct VehicleBodyState* state, bool_t const value)
{
    value ? set_state(state, VEHICLE_BODY_STATE_FLAG_BRAKE_LIGHT_ON) :
            reset_state(state, VEHICLE_BODY_STATE_FLAG_BRAKE_LIGHT_ON);
}
void vehicle_body_state_set_high_beam(struct VehicleBodyState* state, bool_t const value)
{
    value ? set_state(state, VEHICLE_BODY_STATE_FLAG_HIGH_BEAM_ON) :
            reset_state(state, VEHICLE_BODY_STATE_FLAG_HIGH_BEAM_ON);
}
void vehicle_body_state_set_low_beam(struct VehicleBodyState* state, bool_t const value)
{
    value ? set_state(state, VEHICLE_BODY_STATE_FLAG_LOW_BEAM_ON) :
            reset_state(state, VEHICLE_BODY_STATE_FLAG_LOW_BEAM_ON);
}
void vehicle_body_state_set_hazard_flasher(struct VehicleBodyState* state, bool_t const value)
{
    value ? set_state(state, VEHICLE_BODY_STATE_FLAG_HARZARD_FLASHER_ON) :
            reset_state(state, VEHICLE_BODY_STATE_FLAG_HARZARD_FLASHER_ON);
}
void vehicle_body_state_set_right_turn_signal(struct VehicleBodyState* state, bool_t const value)
{
    value ? set_state(state, VEHICLE_BODY_STATE_FLAG_RIGHT_TURN_SIGNAL_ON) :
            reset_state(state, VEHICLE_BODY_STATE_FLAG_RIGHT_TURN_SIGNAL_ON);
}
void vehicle_body_state_set_left_turn_signal(struct VehicleBodyState* state, bool_t const value)
{
    value ? set_state(state, VEHICLE_BODY_STATE_FLAG_LEFT_TURN_SIGNAL_ON) :
            reset_state(state, VEHICLE_BODY_STATE_FLAG_LEFT_TURN_SIGNAL_ON);
}
void vehicle_body_state_set_light_state(struct VehicleBodyState* state, uint32_t const value)
{
    uint32_t mask =
        (1U << VEHICLE_BODY_STATE_FLAG_LEFT_TURN_SIGNAL_ON) | (1U << VEHICLE_BODY_STATE_FLAG_RIGHT_TURN_SIGNAL_ON) |
        (1U << VEHICLE_BODY_STATE_FLAG_HARZARD_FLASHER_ON) | (1U << VEHICLE_BODY_STATE_FLAG_LOW_BEAM_ON) |
        (1U << VEHICLE_BODY_STATE_FLAG_HIGH_BEAM_ON) | (1U << VEHICLE_BODY_STATE_FLAG_BRAKE_LIGHT_ON) |
        (1U << VEHICLE_BODY_STATE_FLAG_FRONT_FOG_LIGHT_ON) | (1U << VEHICLE_BODY_STATE_FLAG_REAR_FOG_LIGHT_ON);
    state->flags &= ~mask;
    state->flags |= (mask & value);
}

void vehicle_body_state_set_rear_right_window(struct VehicleBodyState* state, bool_t const value)
{
    value ? set_state(state, VEHICLE_BODY_STATE_FLAG_REAR_RIGHT_WINDOW_OPEN) :
            reset_state(state, VEHICLE_BODY_STATE_FLAG_REAR_RIGHT_WINDOW_OPEN);
}
void vehicle_body_state_set_rear_left_window(struct VehicleBodyState* state, bool_t const value)
{
    value ? set_state(state, VEHICLE_BODY_STATE_FLAG_REAR_LEFT_WINDOW_OPEN) :
            reset_state(state, VEHICLE_BODY_STATE_FLAG_REAR_LEFT_WINDOW_OPEN);
}
void vehicle_body_state_set_front_right_window(struct VehicleBodyState* state, bool_t const value)
{
    value ? set_state(state, VEHICLE_BODY_STATE_FLAG_FRONT_RIGHT_WINDOW_OPEN) :
            reset_state(state, VEHICLE_BODY_STATE_FLAG_FRONT_RIGHT_WINDOW_OPEN);
}
void vehicle_body_state_set_front_left_window(struct VehicleBodyState* state, bool_t const value)
{
    value ? set_state(state, VEHICLE_BODY_STATE_FLAG_FRONT_LEFT_WINDOW_OPEN) :
            reset_state(state, VEHICLE_BODY_STATE_FLAG_FRONT_LEFT_WINDOW_OPEN);
}
void vehicle_body_state_set_auto_sunroof(struct VehicleBodyState* state, bool_t const value)
{
    value ? set_state(state, VEHICLE_BODY_STATE_FLAG_SUNROOF_WINDOW_OPEN) :
            reset_state(state, VEHICLE_BODY_STATE_FLAG_SUNROOF_WINDOW_OPEN);
}
void vehicle_body_state_set_trunk_door(struct VehicleBodyState* state, bool_t const value)
{
    value ? set_state(state, VEHICLE_BODY_STATE_FLAG_TRUNK_DOOR_OPEN) :
            reset_state(state, VEHICLE_BODY_STATE_FLAG_TRUNK_DOOR_OPEN);
}
void vehicle_body_state_set_car_hood(struct VehicleBodyState* state, bool_t const value)
{
    value ? set_state(state, VEHICLE_BODY_STATE_FLAG_CAR_HOOD_OPEN) :
            reset_state(state, VEHICLE_BODY_STATE_FLAG_CAR_HOOD_OPEN);
}
void vehicle_body_state_set_rear_right_door(struct VehicleBodyState* state, bool_t const value)
{
    value ? set_state(state, VEHICLE_BODY_STATE_FLAG_REAR_RIGHT_DOOR_OPEN) :
            reset_state(state, VEHICLE_BODY_STATE_FLAG_REAR_RIGHT_DOOR_OPEN);
}
void vehicle_body_state_set_rear_left_door(struct VehicleBodyState* state, bool_t const value)
{
    value ? set_state(state, VEHICLE_BODY_STATE_FLAG_REAR_LEFT_DOOR_OPEN) :
            reset_state(state, VEHICLE_BODY_STATE_FLAG_REAR_LEFT_DOOR_OPEN);
}
void vehicle_body_state_set_front_right_door(struct VehicleBodyState* state, bool_t const value)
{
    value ? set_state(state, VEHICLE_BODY_STATE_FLAG_FRONT_RIGHT_DOOR_OPEN) :
            reset_state(state, VEHICLE_BODY_STATE_FLAG_FRONT_RIGHT_DOOR_OPEN);
}
void vehicle_body_state_set_front_left_door(struct VehicleBodyState* state, bool_t const value)
{
    value ? set_state(state, VEHICLE_BODY_STATE_FLAG_FRONT_LEFT_DOOR_OPEN) :
            reset_state(state, VEHICLE_BODY_STATE_FLAG_FRONT_LEFT_DOOR_OPEN);
}
void vehicle_body_state_set_driver_seatbelt(struct VehicleBodyState* state, bool_t const value)
{
    value ? set_state(state, VEHICLE_BODY_STATE_FLAG_DRIVER_SEATBELT_UNLOCK) :
            reset_state(state, VEHICLE_BODY_STATE_FLAG_DRIVER_SEATBELT_UNLOCK);
}
void vehicle_body_state_set_passenger_seatbelt(struct VehicleBodyState* state, bool_t const value)
{
    value ? set_state(state, VEHICLE_BODY_STATE_FLAG_PASSENGER_SEATBELT_UNLOCK) :
            reset_state(state, VEHICLE_BODY_STATE_FLAG_PASSENGER_SEATBELT_UNLOCK);
}
void vehicle_body_state_set_front_wiper_state(struct VehicleBodyState* state, bool_t const value)
{
    value ? set_state(state, VEHICLE_BODY_STATE_FLAG_FRONT_WIPER_ON) :
            reset_state(state, VEHICLE_BODY_STATE_FLAG_FRONT_WIPER_ON);
}
void vehicle_body_state_set_rear_wiper_state(struct VehicleBodyState* state, bool_t const value)
{
    value ? set_state(state, VEHICLE_BODY_STATE_FLAG_REAR_WIPER_ON) :
            reset_state(state, VEHICLE_BODY_STATE_FLAG_REAR_WIPER_ON);
}
void vehicle_body_state_set_cockpit_state(struct VehicleBodyState* state, uint32_t const value)
{
    uint32_t mask =
        (1U << VEHICLE_BODY_STATE_FLAG_REAR_RIGHT_WINDOW_OPEN) | (1U << VEHICLE_BODY_STATE_FLAG_REAR_LEFT_WINDOW_OPEN) |
        (1U << VEHICLE_BODY_STATE_FLAG_FRONT_RIGHT_WINDOW_OPEN) |
        (1U << VEHICLE_BODY_STATE_FLAG_FRONT_LEFT_WINDOW_OPEN) | (1U << VEHICLE_BODY_STATE_FLAG_SUNROOF_WINDOW_OPEN) |
        (1U << VEHICLE_BODY_STATE_FLAG_TRUNK_DOOR_OPEN) | (1U << VEHICLE_BODY_STATE_FLAG_CAR_HOOD_OPEN) |
        (1U << VEHICLE_BODY_STATE_FLAG_REAR_RIGHT_DOOR_OPEN) | (1U << VEHICLE_BODY_STATE_FLAG_REAR_LEFT_DOOR_OPEN) |
        (1U << VEHICLE_BODY_STATE_FLAG_FRONT_RIGHT_DOOR_OPEN) | (1U << VEHICLE_BODY_STATE_FLAG_FRONT_LEFT_DOOR_OPEN) |
        (1U << VEHICLE_BODY_STATE_FLAG_DRIVER_SEATBELT_UNLOCK) |
        (1U << VEHICLE_BODY_STATE_FLAG_PASSENGER_SEATBELT_UNLOCK) | (1U << VEHICLE_BODY_STATE_FLAG_FRONT_WIPER_ON) |
        (1U << VEHICLE_BODY_STATE_FLAG_REAR_WIPER_ON);
    state->flags &= ~mask;
    state->flags |= (mask & value);
}

void vehicle_body_state_set_state_flags(struct VehicleBodyState* state, uint32_t const value)
{
    state->flags = value;
}

void vehicle_body_state_set_button_set(struct VehicleBodyState* state, bool_t value)
{
    state->steering_button_state.button_set = value;
}
void vehicle_body_state_set_button_res(struct VehicleBodyState* state, bool_t value)
{
    state->steering_button_state.button_res = value;
}
void vehicle_body_state_set_button_plus(struct VehicleBodyState* state, bool_t value)
{
    state->steering_button_state.button_plus = value;
}
void vehicle_body_state_set_button_minus(struct VehicleBodyState* state, bool_t value)
{
    state->steering_button_state.button_minus = value;
}
void vehicle_body_state_set_button_mode(struct VehicleBodyState* state, bool_t value)
{
    state->steering_button_state.button_mode = value;
}
void vehicle_body_state_set_button_io(struct VehicleBodyState* state, bool_t value)
{
    state->steering_button_state.button_io = value;
}
void vehicle_body_state_set_button_volume_up(struct VehicleBodyState* state, bool_t value)
{
    state->steering_button_state.button_volume_up = value;
}
void vehicle_body_state_set_button_volume_down(struct VehicleBodyState* state, bool_t value)
{
    state->steering_button_state.button_volume_down = value;
}
void vehicle_body_state_set_button_voice(struct VehicleBodyState* state, bool_t value)
{
    state->steering_button_state.button_voice = value;
}
void vehicle_body_state_set_button_state(struct VehicleBodyState* state, uint16_t value)
{
    state->steering_button_state.button_set         = (value >> 0) & 0x0001;
    state->steering_button_state.button_res         = (value >> 1) & 0x0001;
    state->steering_button_state.button_plus        = (value >> 2) & 0x0001;
    state->steering_button_state.button_minus       = (value >> 3) & 0x0001;
    state->steering_button_state.button_mode        = (value >> 4) & 0x0001;
    state->steering_button_state.button_io          = (value >> 5) & 0x0001;
    state->steering_button_state.button_volume_up   = (value >> 6) & 0x0001;
    state->steering_button_state.button_volume_down = (value >> 7) & 0x0001;
    state->steering_button_state.button_voice       = (value >> 8) & 0x0001;
}

void vehicle_body_state_set_rainfall(struct VehicleBodyState* state, uint16_t value)
{
    state->rain_fall = value;
}

static retcode_t serialize_data(struct VehicleBodyState const* state, uint8_t* buffer, uint32_t buffer_size)
{
    uint32_t serialized_size = 0;

    serialized_size += timestamp_serialize(&state->stamp, buffer + serialized_size, buffer_size - serialized_size);

    serialized_size +=
        serialize_float32(&state->front_left_tire_pressure, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_float32(&state->front_right_tire_pressure, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_float32(&state->rear_left_tire_pressure, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_float32(&state->rear_right_tire_pressure, buffer + serialized_size, buffer_size - serialized_size);

    serialized_size += serialize_uint32(&state->flags, buffer + serialized_size, buffer_size - serialized_size);

    serialized_size += serialize_float32(&state->temperature, buffer + serialized_size, buffer_size - serialized_size);
    serialized_size +=
        serialize_float32(&state->accelerator_pedal, buffer + serialized_size, buffer_size - serialized_size);

    serialized_size += serialize_uint16((uint16_t*)&state->steering_button_state, buffer + serialized_size,
                                        buffer_size - serialized_size);

    serialized_size += serialize_uint16(&state->rain_fall, buffer + serialized_size, buffer_size - serialized_size);

    return (retcode_t)serialized_size;
}

static retcode_t deserialize_data(struct VehicleBodyState* state, uint8_t const* buffer, uint32_t buffer_size)
{
    uint32_t deserialized_size = 0;

    deserialized_size +=
        timestamp_deserialize(&state->stamp, buffer + deserialized_size, buffer_size - deserialized_size);

    deserialized_size += deserialize_float32(&state->front_left_tire_pressure, buffer + deserialized_size,
                                             buffer_size - deserialized_size);
    deserialized_size += deserialize_float32(&state->front_right_tire_pressure, buffer + deserialized_size,
                                             buffer_size - deserialized_size);
    deserialized_size += deserialize_float32(&state->rear_left_tire_pressure, buffer + deserialized_size,
                                             buffer_size - deserialized_size);
    deserialized_size += deserialize_float32(&state->rear_right_tire_pressure, buffer + deserialized_size,
                                             buffer_size - deserialized_size);

    deserialized_size += deserialize_uint32(&state->flags, buffer + deserialized_size, buffer_size - deserialized_size);

    deserialized_size +=
        deserialize_float32(&state->temperature, buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size +=
        deserialize_float32(&state->accelerator_pedal, buffer + deserialized_size, buffer_size - deserialized_size);

    deserialized_size += deserialize_uint16((uint16_t*)&state->steering_button_state, buffer + deserialized_size,
                                            buffer_size - deserialized_size);

    deserialized_size +=
        deserialize_uint16(&state->rain_fall, buffer + deserialized_size, buffer_size - deserialized_size);

    return (retcode_t)deserialized_size;
}

uint32_t vehicle_body_state_get_serialized_size(struct VehicleBodyState const* state)
{
    (void)state;

    return serialization_aligned_size(sizeof(struct VehicleBodyState));
}

retcode_t vehicle_body_state_serialize(struct VehicleBodyState const* state, uint8_t* buffer, uint32_t buffer_size)
{
    assert(state != NULL);
    assert(buffer != NULL);

    retcode_t rc              = RC_SUCCESS;
    uint32_t  serialized_size = 0;
    uint32_t  expected_size   = vehicle_body_state_get_serialized_size(state);

    if (buffer_size < expected_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += serialize_data(state, buffer, buffer_size);

        serialized_size += serialize_padding(serialized_size, buffer + serialized_size, buffer_size - serialized_size);

        assert(expected_size == serialized_size);
        rc = (retcode_t)serialized_size;
    }

    return rc;
}

retcode_t vehicle_body_state_deserialize(struct VehicleBodyState* state, uint8_t const* buffer, uint32_t buffer_size)
{
    assert(state != NULL);
    assert(buffer != NULL);

    retcode_t rc                = RC_SUCCESS;
    uint32_t  deserialized_size = 0;
    uint32_t  expected_size     = vehicle_body_state_get_serialized_size(state);

    if (buffer_size < expected_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size += deserialize_data(state, buffer, buffer_size);

        deserialized_size +=
            deserialize_padding(deserialized_size, buffer + deserialized_size, buffer_size - deserialized_size);

        assert(deserialized_size == expected_size);

        rc = (retcode_t)deserialized_size;
    }

    return rc;
}
