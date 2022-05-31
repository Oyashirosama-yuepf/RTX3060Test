/*!
 * @file vehicle_body_state.h
 * @brief This header file defines vehicle body state driver functions
 * @author liuya@holomatic.com
 * @date 2020-03-13
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */
#ifndef HOLO_C_SENSORS_VEHICLE_BODY_STATE_H_
#define HOLO_C_SENSORS_VEHICLE_BODY_STATE_H_

#include <holo_c/common/timestamp.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup sensors
 * @{
 */

enum VehicleBodyStateFlag
{
    VEHICLE_BODY_STATE_FLAG_LEFT_TURN_SIGNAL_ON  = 0U,
    VEHICLE_BODY_STATE_FLAG_RIGHT_TURN_SIGNAL_ON = 1U,
    VEHICLE_BODY_STATE_FLAG_HARZARD_FLASHER_ON   = 2U,
    VEHICLE_BODY_STATE_FLAG_LOW_BEAM_ON          = 3U,
    VEHICLE_BODY_STATE_FLAG_HIGH_BEAM_ON         = 4U,
    VEHICLE_BODY_STATE_FLAG_BRAKE_LIGHT_ON       = 5U,
    VEHICLE_BODY_STATE_FLAG_FRONT_FOG_LIGHT_ON   = 6U,
    VEHICLE_BODY_STATE_FLAG_REAR_FOG_LIGHT_ON    = 7U,

    VEHICLE_BODY_STATE_FLAG_CHARGING_CAP_OPEN          = 8U,
    VEHICLE_BODY_STATE_FLAG_FAST_CHARGING_CAP_OPEN     = 9U,
    VEHICLE_BODY_STATE_FLAG_LEFT_REARVIEW_MIRROR_FOLD  = 10U,
    VEHICLE_BODY_STATE_FLAG_RIGHT_REARVIEW_MIRROR_FOLD = 11U,
    VEHICLE_BODY_STATE_FLAG_DRIVER_SEATBELT_UNLOCK     = 12U,
    VEHICLE_BODY_STATE_FLAG_CODRIVER_SEATBELT_UNLOCK   = 13U,
    VEHICLE_BODY_STATE_FLAG_PASSENGER_SEATBELT_UNLOCK  = 14U,
    VEHICLE_BODY_STATE_FLAG_DRIVER_ABSENT              = 15U,

    VEHICLE_BODY_STATE_FLAG_FRONT_WIPER_ON          = 16U,
    VEHICLE_BODY_STATE_FLAG_REAR_WIPER_ON           = 17U,
    VEHICLE_BODY_STATE_FLAG_FRONT_LEFT_DOOR_OPEN    = 18U,
    VEHICLE_BODY_STATE_FLAG_FRONT_RIGHT_DOOR_OPEN   = 19U,
    VEHICLE_BODY_STATE_FLAG_REAR_LEFT_DOOR_OPEN     = 20U,
    VEHICLE_BODY_STATE_FLAG_REAR_RIGHT_DOOR_OPEN    = 21U,
    VEHICLE_BODY_STATE_FLAG_CAR_HOOD_OPEN           = 22U,
    VEHICLE_BODY_STATE_FLAG_TRUNK_DOOR_OPEN         = 23U,
    VEHICLE_BODY_STATE_FLAG_FRONT_LEFT_WINDOW_OPEN  = 24U,
    VEHICLE_BODY_STATE_FLAG_FRONT_RIGHT_WINDOW_OPEN = 25U,
    VEHICLE_BODY_STATE_FLAG_REAR_LEFT_WINDOW_OPEN   = 26U,
    VEHICLE_BODY_STATE_FLAG_REAR_RIGHT_WINDOW_OPEN  = 27U,
    VEHICLE_BODY_STATE_FLAG_SUNROOF_WINDOW_OPEN     = 28U,
    VEHICLE_BODY_STATE_FLAG_POWERTRAIN_NOT_READY    = 29U,
};

struct VehicleBodyState
{
    struct Timestamp stamp;

    float32_t front_left_tire_pressure;
    float32_t front_right_tire_pressure;
    float32_t rear_left_tire_pressure;
    float32_t rear_right_tire_pressure;

    uint32_t flags;

    float32_t temperature;
    float32_t accelerator_pedal;

    struct
    {
        uint16_t button_set : 1;
        uint16_t button_res : 1;
        uint16_t button_plus : 1;
        uint16_t button_minus : 1;
        uint16_t button_mode : 1;
        uint16_t button_io : 1;
        uint16_t button_volume_up : 1;
        uint16_t button_volume_down : 1;
        uint16_t button_voice : 1;
        uint16_t reserved : 7;
    } steering_button_state;

    uint16_t rain_fall;
};
HOLO_STATIC_ASSERT(sizeof(struct VehicleBodyState) == 40);

/**
 * @brief Default Constructor
 *
 * @param VehicleBodyState Input vehicle body state object
 * @return retcode_t RC_SUCCESS
 */
retcode_t vehicle_body_state_init_default(struct VehicleBodyState* state);

/**
 * @{
 */

bool_t vehicle_body_state_get_state(struct VehicleBodyState const* state, enum VehicleBodyStateFlag flag);

void vehicle_body_state_set_state(struct VehicleBodyState* state, enum VehicleBodyStateFlag flag);

void vehicle_body_state_reset_state(struct VehicleBodyState* state, enum VehicleBodyStateFlag flag);

/**
 * @brief Get vehicle body state timestamp
 *
 * @param state Input vehicle body state object
 * @return struct Timestamp* Timestamp pointer
 */
const struct Timestamp* vehicle_body_state_get_timestamp(struct VehicleBodyState const* state);

/**
 * @brief Get outside temperature value
 *
 * @param state Input vehicle body state object
 * @return float32_t Outside temperature value
 */
float32_t vehicle_body_state_get_temperature(struct VehicleBodyState const* state);

/**
 * @brief Get accelerator pedal value
 *
 * @param state Input vehicle body state object
 * @return float32_t Accelerator pedal value
 */
float32_t vehicle_body_state_get_accelerator_pedal(struct VehicleBodyState const* state);

/**
 * @brief Get front left tire pressure
 *
 * @param state Input vehicle body state object
 * @return float32_t Front left tire pressure
 */
float32_t vehicle_body_state_get_front_left_tire_pressure(struct VehicleBodyState const* state);

/**
 * @brief Get front right tire pressure
 *
 * @param state Input vehicle body state object
 * @return float32_t Front right tire pressure
 */
float32_t vehicle_body_state_get_front_right_tire_pressure(struct VehicleBodyState const* state);

/**
 * @brief Get rear left tire pressure
 *
 * @param state Input vehicle body state object
 * @return float32_t Rear left tire pressure
 */
float32_t vehicle_body_state_get_rear_left_tire_pressure(struct VehicleBodyState const* state);

/**
 * @brief Get rear right tire pressure
 *
 * @param state Input vehicle body state object
 * @return float32_t Rear right tire pressure
 */
float32_t vehicle_body_state_get_rear_right_tire_pressure(struct VehicleBodyState const* state);

/**
 * @brief Get rear fog light state
 *
 * @param state Input vehicle body state object
 * @return bool_t Rear fog light state
 */
bool_t vehicle_body_state_get_rear_fog_light(struct VehicleBodyState const* state);

/**
 * @brief Get front fog light state
 *
 * @param state Input vehicle body state object
 * @return bool_t Front fog light state
 */
bool_t vehicle_body_state_get_front_fog_light(struct VehicleBodyState const* state);

/**
 * @brief Get brake light state
 *
 * @param state Input vehicle body state object
 * @return bool_t Brake light state
 */
bool_t vehicle_body_state_get_brake_light(struct VehicleBodyState const* state);

/**
 * @brief Get high beam state
 *
 * @param state Input vehicle body state object
 * @return bool_t High beam state
 */
bool_t vehicle_body_state_get_high_beam(struct VehicleBodyState const* state);

/**
 * @brief Get low beam state
 *
 * @param state Input vehicle body state object
 * @return bool_t Low beam state
 */
bool_t vehicle_body_state_get_low_beam(struct VehicleBodyState const* state);

/**
 * @brief Get hazard flasher state
 *
 * @param state Input vehicle body state object
 * @return bool_t Hazard flasher state
 */
bool_t vehicle_body_state_get_hazard_flasher(struct VehicleBodyState const* state);

/**
 * @brief Get right turn light state
 *
 * @param state Input vehicle body state object
 * @return bool_t Right turn light state
 */
bool_t vehicle_body_state_get_right_turn_signal(struct VehicleBodyState const* state);

/**
 * @brief Get left turn light state
 *
 * @param state Input vehicle body state object
 * @return bool_t Left turn light state
 */
bool_t vehicle_body_state_get_left_turn_signal(struct VehicleBodyState const* state);

/**
 * @brief Get all light state
 *
 * @param state Input vehicle body state object
 * @return uint32_t Light state value
 */
uint32_t vehicle_body_state_get_light_state(struct VehicleBodyState const* state);

/**
 * @brief Get rear right window state
 *
 * @param state Input vehicle body state object
 * @return bool_t Rear right window state
 */
bool_t vehicle_body_state_get_rear_right_window(struct VehicleBodyState const* state);

/**
 * @brief Get rear left window state
 *
 * @param state Input vehicle body state object
 * @return bool_t Rear left window state
 */
bool_t vehicle_body_state_get_rear_left_window(struct VehicleBodyState const* state);

/**
 * @brief Get front right window state
 *
 * @param state Input vehicle body state object
 * @return bool_t Front right window state
 */
bool_t vehicle_body_state_get_front_right_window(struct VehicleBodyState const* state);

/**
 * @brief Get front left window state
 *
 * @param state Input vehicle body state object
 * @return bool_t Front left window state
 */
bool_t vehicle_body_state_get_front_left_window(struct VehicleBodyState const* state);

/**
 * @brief Get sunroof state
 *
 * @param state Input vehicle body state object
 * @return bool_t Sunroof state
 */
bool_t vehicle_body_state_get_auto_sunroof(struct VehicleBodyState const* state);

/**
 * @brief Get trunk door state
 *
 * @param state Input vehicle body state object
 * @return bool_t Trunk door state
 */
bool_t vehicle_body_state_get_trunk_door(struct VehicleBodyState const* state);

/**
 * @brief Get rear car hood state
 *
 * @param state Input vehicle body state object
 * @return bool_t Car hood state
 */
bool_t vehicle_body_state_get_car_hood(struct VehicleBodyState const* state);

/**
 * @brief Get rear right door state
 *
 * @param state Input vehicle body state object
 * @return bool_t Rear right door state
 */
bool_t vehicle_body_state_get_rear_right_door(struct VehicleBodyState const* state);

/**
 * @brief Get rear left door state
 *
 * @param state Input vehicle body state object
 * @return bool_t Rear left door state
 */
bool_t vehicle_body_state_get_rear_left_door(struct VehicleBodyState const* state);

/**
 * @brief Get front right door state
 *
 * @param state Input vehicle body state object
 * @return bool_t Front right door state
 */
bool_t vehicle_body_state_get_front_right_door(struct VehicleBodyState const* state);

/**
 * @brief Get front left door state
 *
 * @param state Input vehicle body state object
 * @return bool_t Front left door state
 */
bool_t vehicle_body_state_get_front_left_door(struct VehicleBodyState const* state);

/**
 * @brief Get driver seatbelt state
 *
 * @param state Input vehicle body state object
 * @return bool_t Driver seatbelt state
 */
bool_t vehicle_body_state_get_driver_seatbelt(struct VehicleBodyState const* state);

/**
 * @brief Get front passenger seatbelt state
 *
 * @param state Input vehicle body state object
 * @return bool_t Front passenger seatbelt state
 */
bool_t vehicle_body_state_get_passenger_seatbelt(struct VehicleBodyState const* state);

/**
 * @brief Get front wiper state
 *
 * @param state Input vehicle body state object
 * @return bool_t Front wiper state
 */
bool_t vehicle_body_state_get_front_wiper_state(struct VehicleBodyState const* state);

/**
 * @brief Get rear wiper state
 *
 * @param state Input vehicle body state object
 * @return bool_t Rear wiper state
 */
bool_t vehicle_body_state_get_rear_wiper_state(struct VehicleBodyState const* state);

/**
 * @brief Get cockpit state
 *
 * @param state Input vehicle body state object
 * @return uint32_t Cockpit state
 */
uint32_t vehicle_body_state_get_cockpit_state(struct VehicleBodyState const* state);

uint32_t vehicle_body_state_get_state_flags(struct VehicleBodyState* state);

/**
 * @brief Get set button state
 *
 * @param state Input vehicle body state object
 * @return bool_t Set button state
 */
bool_t vehicle_body_state_get_button_set(struct VehicleBodyState const* state);

/**
 * @brief Get res button state
 *
 * @param state Input vehicle body state object
 * @return bool_t Res button state
 */
bool_t vehicle_body_state_get_button_res(struct VehicleBodyState const* state);

/**
 * @brief Get plus button state
 *
 * @param state Input vehicle body state object
 * @return bool_t Plus button state
 */
bool_t vehicle_body_state_get_button_plus(struct VehicleBodyState const* state);

/**
 * @brief Get minus button state
 *
 * @param state Input vehicle body state object
 * @return bool_t Minus button state
 */
bool_t vehicle_body_state_get_button_minus(struct VehicleBodyState const* state);

/**
 * @brief Get mode button state
 *
 * @param state Input vehicle body state object
 * @return bool_t Mode button state
 */
bool_t vehicle_body_state_get_button_mode(struct VehicleBodyState const* state);

/**
 * @brief Get io button state
 *
 * @param state Input vehicle body state object
 * @return bool_t Io button state
 */
bool_t vehicle_body_state_get_button_io(struct VehicleBodyState const* state);

/**
 * @brief Get volume up button state
 *
 * @param state Input vehicle body state object
 * @return bool_t volume up button state
 */
bool_t vehicle_body_state_get_button_volume_up(struct VehicleBodyState const* state);

/**
 * @brief Get volume down button state
 *
 * @param state Input vehicle body state object
 * @return bool_t volume down button state
 */
bool_t vehicle_body_state_get_button_volume_down(struct VehicleBodyState const* state);

/**
 * @brief Get voice button state
 *
 * @param state Input vehicle body state object
 * @return bool_t voice button state
 */
bool_t vehicle_body_state_get_button_voice(struct VehicleBodyState const* state);

/**
 * @brief Get all button state
 *
 * @param state Input vehicle body state object
 * @return uint16_t All button state
 */
uint16_t vehicle_body_state_get_button_state(struct VehicleBodyState const* state);

/**
 * @brief Get rain fall
 *
 * @param state Input vehicle body state object
 * @return uint16_t Rain fall percent
 */
uint16_t vehicle_body_state_get_rainfall(struct VehicleBodyState const* state);

/**
 * @}
 */

/**
 * @{
 */

/**
 * @brief Set body state timestamp
 *
 * @param state Input vehicle body state object
 * @param stamp Timestamp object
 */
void vehicle_body_state_set_timestamp(struct VehicleBodyState* state, const struct Timestamp* stamp);

/**
 * @brief Set outside temperature value
 *
 * @param state Input vehicle body state object
 * @param value Temperature value
 */
void vehcile_body_state_set_temperature(struct VehicleBodyState* state, const float32_t value);

/**
 * @brief Set accelerator pedal value
 *
 * @param state Input vehicle body state object
 * @param value Accelerator pedal value
 */
void vehicle_body_state_set_accelerator_pedal(struct VehicleBodyState* state, const float32_t value);

/**
 * @brief Set front left tire pressure
 *
 * @param state Input vehicle body state object
 * @param value Tire pressure
 */
void vehicle_body_state_set_front_left_tire_pressure(struct VehicleBodyState* state, const float32_t value);

/**
 * @brief Set front right tire pressure
 *
 * @param state Input vehicle body state object
 * @param value Tire pressure
 */
void vehicle_body_state_set_front_right_tire_pressure(struct VehicleBodyState* state, const float32_t value);

/**
 * @brief Set rear left tire pressure
 *
 * @param state Input vehicle body state object
 * @param value Tire pressure
 */
void vehicle_body_state_set_rear_left_tire_pressure(struct VehicleBodyState* state, const float32_t value);

/**
 * @brief Set rear right tire pressure
 *
 * @param state Input vehicle body state object
 * @param value Tire pressure
 */
void vehicle_body_state_set_rear_right_tire_pressure(struct VehicleBodyState* state, const float32_t value);

/**
 * @brief Set rear fog light state
 *
 * @param state Input vehicle body state object
 * @param value Light state
 */
void vehicle_body_state_set_rear_fog_light(struct VehicleBodyState* state, const bool_t value);

/**
 * @brief Set front fog light state
 *
 * @param state Input vehicle body state object
 * @param value Light state
 */
void vehicle_body_state_set_front_fog_light(struct VehicleBodyState* state, const bool_t value);

/**
 * @brief Set brake light state
 *
 * @param state Input vehicle body state object
 * @param value Light state
 */
void vehicle_body_state_set_brake_light(struct VehicleBodyState* state, const bool_t value);

/**
 * @brief Set high beam state
 *
 * @param state Input vehicle body state object
 * @param value Light state
 */
void vehicle_body_state_set_high_beam(struct VehicleBodyState* state, const bool_t value);

/**
 * @brief Set low beam state
 *
 * @param state Input vehicle body state object
 * @param value Light state
 */
void vehicle_body_state_set_low_beam(struct VehicleBodyState* state, const bool_t value);

/**
 * @brief Set hazard flasher state
 *
 * @param state Input vehicle body state object
 * @param value Light state
 */
void vehicle_body_state_set_hazard_flasher(struct VehicleBodyState* state, const bool_t value);

/**
 * @brief Set right turn light state
 *
 * @param state Input vehicle body state object
 * @param value Light state
 */
void vehicle_body_state_set_right_turn_signal(struct VehicleBodyState* state, const bool_t value);

/**
 * @brief Set left turn light state
 *
 * @param state Input vehicle body state object
 * @param value Light state
 */
void vehicle_body_state_set_left_turn_signal(struct VehicleBodyState* state, const bool_t value);

/**
 * @brief Set light state
 *
 * @param state Input vehicle body state object
 * @param value Light state
 */
void vehicle_body_state_set_light_state(struct VehicleBodyState* state, uint32_t const value);

/**
 * @brief Set rear right window state
 *
 * @param state Input vehicle body state object
 * @param value Window state
 */
void vehicle_body_state_set_rear_right_window(struct VehicleBodyState* state, const bool_t value);

/**
 * @brief Set rear left window state
 *
 * @param state Input vehicle body state object
 * @param value Window state
 */
void vehicle_body_state_set_rear_left_window(struct VehicleBodyState* state, const bool_t value);

/**
 * @brief Set front right window state
 *
 * @param state Input vehicle body state object
 * @param value Window state
 */
void vehicle_body_state_set_front_right_window(struct VehicleBodyState* state, const bool_t value);

/**
 * @brief Set front left window state
 *
 * @param state Input vehicle body state object
 * @param value Window state
 */
void vehicle_body_state_set_front_left_window(struct VehicleBodyState* state, const bool_t value);

/**
 * @brief Set auto sunroof state
 *
 * @param state Input vehicle body state object
 * @param value Sunroof state
 */
void vehicle_body_state_set_auto_sunroof(struct VehicleBodyState* state, const bool_t value);

/**
 * @brief Set trunk door state
 *
 * @param state Input vehicle body state object
 * @param value Door state
 */
void vehicle_body_state_set_trunk_door(struct VehicleBodyState* state, const bool_t value);

/**
 * @brief Set car hood state
 *
 * @param state Input vehicle body state object
 * @param value Car hood state
 */
void vehicle_body_state_set_car_hood(struct VehicleBodyState* state, const bool_t value);

/**
 * @brief Set rear right door state
 *
 * @param state Input vehicle body state object
 * @param value Door state
 */
void vehicle_body_state_set_rear_right_door(struct VehicleBodyState* state, const bool_t value);

/**
 * @brief Set rear left door state
 *
 * @param state Input vehicle body state object
 * @param value Door state
 */
void vehicle_body_state_set_rear_left_door(struct VehicleBodyState* state, const bool_t value);

/**
 * @brief Set front right door state
 *
 * @param state Input vehicle body state object
 * @param value Door state
 */
void vehicle_body_state_set_front_right_door(struct VehicleBodyState* state, const bool_t value);

/**
 * @brief Set front left door state
 *
 * @param state Input vehicle body state object
 * @param value Door state
 */
void vehicle_body_state_set_front_left_door(struct VehicleBodyState* state, const bool_t value);

/**
 * @brief Set driver seatbelt state
 *
 * @param state Input vehicle body state object
 * @param value Seatbelt state
 */
void vehicle_body_state_set_driver_seatbelt(struct VehicleBodyState* state, const bool_t value);

/**
 * @brief Set front passenger seatbelt state
 *
 * @param state Input vehicle body state object
 * @param value Seatbelt state
 */
void vehicle_body_state_set_passenger_seatbelt(struct VehicleBodyState* state, const bool_t value);

/**
 * @brief Set front wiper state
 *
 * @param state Input vehicle body state object
 * @param value Wiper state
 */
void vehicle_body_state_set_front_wiper_state(struct VehicleBodyState* state, const bool_t value);

/**
 * @brief Set rear wiper state
 *
 * @param state Input vehicle body state object
 * @param value Wiper state
 */
void vehicle_body_state_set_rear_wiper_state(struct VehicleBodyState* state, const bool_t value);

/**
 * @brief Set cockpit state
 *
 * @param state Input vehicle body state object
 * @param value Cockpit state
 */
void vehicle_body_state_set_cockpit_state(struct VehicleBodyState* state, uint32_t const value);

void vehicle_body_state_set_state_flags(struct VehicleBodyState* state, uint32_t const value);

/**
 * @brief Set set button state
 *
 * @param state Input vehicle body state object
 * @param value Button value
 */
void vehicle_body_state_set_button_set(struct VehicleBodyState* state, bool_t value);

/**
 * @brief Set res button state
 *
 * @param state Input vehicle body state object
 * @param value Button value
 */
void vehicle_body_state_set_button_res(struct VehicleBodyState* state, bool_t value);

/**
 * @brief Set plus button state
 *
 * @param state Input vehicle body state object
 * @param value Button value
 */
void vehicle_body_state_set_button_plus(struct VehicleBodyState* state, bool_t value);

/**
 * @brief Set minus button state
 *
 * @param state Input vehicle body state object
 * @param value Button value
 */
void vehicle_body_state_set_button_minus(struct VehicleBodyState* state, bool_t value);

/**
 * @brief Set mode button state
 *
 * @param state Input vehicle body state object
 * @param value Button value
 */
void vehicle_body_state_set_button_mode(struct VehicleBodyState* state, bool_t value);

/**
 * @brief Set io button state
 *
 * @param state Input vehicle body state object
 * @param value Button value
 */
void vehicle_body_state_set_button_io(struct VehicleBodyState* state, bool_t value);

/**
 * @brief Set volume up button state
 *
 * @param state Input vehicle body state object
 * @param value Button value
 */
void vehicle_body_state_set_button_volume_up(struct VehicleBodyState* state, bool_t value);

/**
 * @brief Set volume down button state
 *
 * @param state Input vehicle body state object
 * @param value Button value
 */
void vehicle_body_state_set_button_volume_down(struct VehicleBodyState* state, bool_t value);

/**
 * @brief Set voice button state
 *
 * @param state Input vehicle body state object
 * @param value Button value
 */
void vehicle_body_state_set_button_voice(struct VehicleBodyState* state, bool_t value);

/**
 * @brief Set all button state
 *
 * @param state Input vehicle body state object
 * @param value All button value
 */
void vehicle_body_state_set_button_state(struct VehicleBodyState* state, uint16_t value);

/**
 * @brief Set rain fall
 *
 * @param state Input vehicle body state object
 * @param value Rain fall value
 */
void vehicle_body_state_set_rainfall(struct VehicleBodyState* state, uint16_t value);

/**
 * @}
 */

/**
 * @brief Get vehicle body state serialized size
 *
 * @param state Input vehicle body state object
 * @return uint32_t Serialized size
 */
uint32_t vehicle_body_state_get_serialized_size(struct VehicleBodyState const* state);

/**
 * @brief Serialize vehicle body state to buffer
 *
 * @param state Input vehicle body state object
 * @param buffer The buffer to store serialized content
 * @param buffer_size Buffer size
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed
 * @return retcode_t Positive interger Number of bytes serialized into buffer
 */
retcode_t vehicle_body_state_serialize(struct VehicleBodyState const* state, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize vehicle body state from buffer
 *
 * @param state Input vehicle body state object
 * @param buffer The buffer deserialized from
 * @param buffer_size Buffer size
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed
 * @return retcode_t Positive integer Number of bytes deserialized from buffer
 */
retcode_t vehicle_body_state_deserialize(struct VehicleBodyState* state, uint8_t const* buffer, uint32_t buffer_size);

/**
 * @}
 *
 */

#ifdef __cplusplus
}
#endif

#endif
