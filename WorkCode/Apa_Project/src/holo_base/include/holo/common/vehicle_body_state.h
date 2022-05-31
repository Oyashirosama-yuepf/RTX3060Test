/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
/**
 * @file vehicle_body_state.h
 * @brief This header file defines VehicleBodyState Object.
 * @author houyujian(houyujian@holomaitc.com)
 * @date 2020-03-02
 */

#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/serialization/serialization.h>

#ifndef HOLO_COMMON_VEHICLE_BODY_STATE_H_
#define HOLO_COMMON_VEHICLE_BODY_STATE_H_

namespace holo
{
namespace common
{
/**
 * @addtogroup common
 * @{
 *
 */

/**
 * @brief VehicleBodyState class provide vehicle chassis about information of body.
 *
 */
class VehicleBodyState
{
public:
    enum class State : uint32_t
    {
        LEFT_TURN_SIGNAL_ON  = 1U << 0U,
        RIGHT_TURN_SIGNAL_ON = 1U << 1U,
        HARZARD_FLASHER_ON   = 1U << 2U,
        LOW_BEAM_ON          = 1U << 3U,
        HIGH_BEAM_ON         = 1U << 4U,
        BRAKE_LIGHT_ON       = 1U << 5U,
        FRONT_FOG_LIGHT_ON   = 1U << 6U,
        REAR_FOG_LIGHT_ON    = 1U << 7U,

        CHARGING_CAP_OPEN          = 1U << 8U,
        FAST_CHARGING_CAP_OPEN     = 1U << 9U,
        LEFT_REARVIEW_MIRROR_FOLD  = 1U << 10U,
        RIGHT_REARVIEW_MIRROR_FOLD = 1U << 11U,
        DRIVER_SEATBELT_UNLOCK     = 1U << 12U,
        CODRIVER_SEATBELT_UNLOCK   = 1U << 13U,
        PASSENGER_SEATBELT_UNLOCK  = 1U << 14U,
        DRIVER_ABSENT              = 1U << 15U,

        FRONT_WIPER_ON          = 1U << 16U,
        REAR_WIPER_ON           = 1U << 17U,
        FRONT_LEFT_DOOR_OPEN    = 1U << 18U,
        FRONT_RIGHT_DOOR_OPEN   = 1U << 19U,
        REAR_LEFT_DOOR_OPEN     = 1U << 20U,
        REAR_RIGHT_DOOR_OPEN    = 1U << 21U,
        CAR_HOOD_OPEN           = 1U << 22U,
        TRUNK_DOOR_OPEN         = 1U << 23U,
        FRONT_LEFT_WINDOW_OPEN  = 1U << 24U,
        FRONT_RIGHT_WINDOW_OPEN = 1U << 25U,
        REAR_LEFT_WINDOW_OPEN   = 1U << 26U,
        REAR_RIGHT_WINDOW_OPEN  = 1U << 27U,
        SUNROOF_WINDOW_OPEN     = 1U << 28U,
        POWERTRAIN_NOT_READY    = 1U << 29U,
    };

    enum class InvalidFlag : uint32_t
    {
        LEFT_TURN_SIGNAL_INVALID  = 1U << 0U,
        RIGHT_TURN_SIGNAL_INVALID = 1U << 1U,
        HARZARD_FLASHER_INVALID   = 1U << 2U,
        LOW_BEAM_INVALID          = 1U << 3U,
        HIGH_BEAM_INVALID         = 1U << 4U,
        BRAKE_LIGHT_INVALID       = 1U << 5U,
        FRONT_FOG_LIGHT_INVALID   = 1U << 6U,
        REAR_FOG_LIGHT_INVALID    = 1U << 7U,

        CHARGING_CAP_INVALID       = 1U << 8U,
        FAST_CHARGING_CAP_INVALID  = 1U << 9U,
        LEFT_REARVIEW_MIRROR_FOLD  = 1U << 10U,
        RIGHT_REARVIEW_MIRROR_FOLD = 1U << 11U,
        DRIVER_SEATBELT_INVALID    = 1U << 12U,
        CODRIVER_SEATBELT_INVALID  = 1U << 13U,
        PASSENGER_SEATBELT_INVALID = 1U << 14U,
        DRIVER_ABSENT_INVALID      = 1U << 15U,

        FRONT_WIPER_INVALID        = 1U << 16U,
        REAR_WIPER_INVALID         = 1U << 17U,
        FRONT_LEFT_DOOR_INVALID    = 1U << 18U,
        FRONT_RIGHT_DOOR_INVALID   = 1U << 19U,
        REAR_LEFT_DOOR_INVALID     = 1U << 20U,
        REAR_RIGHT_DOOR_INVALID    = 1U << 21U,
        CAR_HOOD_INVALID           = 1U << 22U,
        TRUNK_DOOR_INVALID         = 1U << 23U,
        FRONT_LEFT_WINDOW_INVALID  = 1U << 24U,
        FRONT_RIGHT_WINDOW_INVALID = 1U << 25U,
        REAR_LEFT_WINDOW_INVALID   = 1U << 26U,
        REAR_RIGHT_WINDOW_INVALID  = 1U << 27U,
        SUNROOF_WINDOW_INVALID     = 1U << 28U,
        POWERTRAIN_INVALID         = 1U << 29U,
    };

    /**
     * @brief Default constructor.
     */
    VehicleBodyState()
      : timestamp_(0.0f)
      , front_left_tire_pressure_(0.0f)
      , front_right_tire_pressure_(0.0f)
      , rear_left_tire_pressure_(0.0f)
      , rear_right_tire_pressure_(0.0f)
      , state_flags_(0U)
      , invalid_flags_(0U)
    {
    }

    /**
     * @brief Get time stamp
     *
     * @return timestamp_
     */
    Timestamp GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    /**
     * @brief Get front left tire pressure from vehicle chassis.
     *
     * @return Front left tire pressure in kpa.
     */
    float32_t GetFrontLeftTirePressure() const noexcept
    {
        return front_left_tire_pressure_;
    }

    /**
     * @brief Get front right tire pressure from vehicle chassis.
     *
     * @return Front right tire pressure in kpa.
     */
    float32_t GetFrontRightTirePressure() const noexcept
    {
        return front_right_tire_pressure_;
    }

    /**
     * @brief Get rear left tire pressure from vehicle chassis.
     *
     * @return rear left tire pressure in kpa.
     */
    float32_t GetRearLeftTirePressure() const noexcept
    {
        return rear_left_tire_pressure_;
    }

    /**
     * @brief Get rear right tire pressure from vehicle chassis.
     *
     * @return rear right tire pressure in kpa.
     */
    float32_t GetRearRightTirePressure() const noexcept
    {
        return rear_right_tire_pressure_;
    }

    bool_t IsStateSet() const noexcept
    {
        return state_flags_ != 0U;
    }

    template <typename... Args>
    bool_t IsStateSet(Args&&... args) const noexcept
    {
        return (state_flags_ & getFlags(std::forward<Args>(args)...)) == getFlags(std::forward<Args>(args)...);
    }

    template <typename... Args>
    bool_t IsStateSetAny(Args&&... args) const noexcept
    {
        return (state_flags_ & getFlags(std::forward<Args>(args)...)) != 0U;
    }

    template <typename... Args>
    void SetState(Args&&... args) noexcept
    {
        state_flags_ |= getFlags(std::forward<Args>(args)...);
    }

    template <typename... Args>
    void ResetState(Args&&... args) noexcept
    {
        state_flags_ &= ~getFlags(std::forward<Args>(args)...);
    }

    void ResetState() noexcept
    {
        state_flags_ = 0U;
    }

    bool_t IsInvalidFlagSet() const noexcept
    {
        return invalid_flags_ != 0U;
    }

    template <typename... Args>
    bool_t IsInvalidFlagSet(Args&&... args) const noexcept
    {
        return (invalid_flags_ & getFlags(std::forward<Args>(args)...)) == getFlags(std::forward<Args>(args)...);
    }

    template <typename... Args>
    bool_t IsInvalidFlagSetAny(Args&&... args) const noexcept
    {
        return (invalid_flags_ & getFlags(std::forward<Args>(args)...)) != 0U;
    }

    template <typename... Args>
    void SetInvalidFlag(Args&&... args) noexcept
    {
        invalid_flags_ |= getFlags(std::forward<Args>(args)...);
    }

    template <typename... Args>
    void ResetInvalidFlag(Args&&... args) noexcept
    {
        invalid_flags_ &= ~getFlags(std::forward<Args>(args)...);
    }

    void ResetInvalidFlag() noexcept
    {
        invalid_flags_ = 0U;
    }

    /**
     * @brief Check if left turn light is on.
     *
     * @return true or false.
     */
    bool_t IsLeftTurnSignalOn() const noexcept
    {
        return IsStateSet(State::LEFT_TURN_SIGNAL_ON);
    }

    /**
     * @brief Check if right turn light is on.
     *
     * @return true or false.
     */
    bool_t IsRightTurnSignalOn() const noexcept
    {
        return IsStateSet(State::RIGHT_TURN_SIGNAL_ON);
    }

    /**
     * @brief Check if warn blink light is on.
     *
     * @return true or false.
     */
    bool_t IsHazardFlasherOn() const noexcept
    {
        return IsStateSet(State::HARZARD_FLASHER_ON);
    }

    /**
     * @brief Check if low beam is on.
     *
     * @return true or false.
     */
    bool_t IsLowBeamOn() const noexcept
    {
        return IsStateSet(State::LOW_BEAM_ON);
    }

    /**
     * @brief Check if high beam is on.
     *
     * @return true or false.
     */
    bool_t IsHighBeamOn() const noexcept
    {
        return IsStateSet(State::HIGH_BEAM_ON);
    }

    /**
     * @brief Check if brake light is on.
     *
     * @return true or false.
     */
    bool_t IsBrakeLightOn() const noexcept
    {
        return IsStateSet(State::BRAKE_LIGHT_ON);
    }

    /**
     * @brief Check if front fog light is on.
     *
     * @return true or false.
     */
    bool_t IsFrontFogLightOn() const noexcept
    {
        return IsStateSet(State::FRONT_FOG_LIGHT_ON);
    }

    /**
     * @brief Check if rear fog light is on.
     *
     * @return true or false.
     */
    bool_t IsRearFogLightOn() const noexcept
    {
        return IsStateSet(State::REAR_FOG_LIGHT_ON);
    }

    /**
     * @brief Check if Driver need fastening seat belt
     *
     * @return yes or no.
     */
    bool_t DoDriverSeatbeltNeedFastening() const noexcept
    {
        return IsStateSet(State::DRIVER_SEATBELT_UNLOCK);
    }

    /**
     * @brief Check if Front passenger need fastening seat belt
     *
     * @return yes or no.
     */
    bool_t DoPassengerSeatbeltNeedFastening() const noexcept
    {
        return IsStateSet(State::PASSENGER_SEATBELT_UNLOCK);
    }

    /**
     * @brief Check if any door is open.
     *
     * @return true or false.
     */
    bool_t IsDoorOpen() const noexcept
    {
        return IsStateSetAny(State::FRONT_LEFT_DOOR_OPEN, State::FRONT_RIGHT_DOOR_OPEN, State::REAR_LEFT_DOOR_OPEN,
                             State::REAR_RIGHT_DOOR_OPEN, State::CAR_HOOD_OPEN, State::TRUNK_DOOR_OPEN);
    }

    /**
     * @brief Check if front left door is open.
     *
     * @return true or false.
     */
    bool_t IsFrontLeftDoorOpen() const noexcept
    {
        return IsStateSet(State::FRONT_LEFT_DOOR_OPEN);
    }

    /**
     * @brief Check if front right door is open.
     *
     * @return true or false.
     */
    bool_t IsFrontRightDoorOpen() const noexcept
    {
        return IsStateSet(State::FRONT_RIGHT_DOOR_OPEN);
    }

    /**
     * @brief Check if rear left door is open.
     *
     * @return true or false.
     */
    bool_t IsRearLeftDoorOpen() const noexcept
    {
        return IsStateSet(State::REAR_LEFT_DOOR_OPEN);
    }

    /**
     * @brief Check if rear right door is open.
     *
     * @return true or false.
     */
    bool_t IsRearRightDoorOpen() const noexcept
    {
        return IsStateSet(State::REAR_RIGHT_DOOR_OPEN);
    }

    /**
     * @brief Check if trunk door is open.
     *
     * @return true or false.
     */
    bool_t IsTrunkDoorOpen() const noexcept
    {
        return IsStateSet(State::TRUNK_DOOR_OPEN);
    }

    /**
     * @brief Check if car hood is open.
     *
     * @return true or false
     */
    bool_t IsCarHoodOpen() const noexcept
    {
        return IsStateSet(State::CAR_HOOD_OPEN);
    }

    /**
     * @brief Check if any window is open.
     *
     * @return true or false.
     */
    bool_t IsWindowOpen() const noexcept
    {
        return IsStateSetAny(State::FRONT_LEFT_WINDOW_OPEN, State::FRONT_RIGHT_WINDOW_OPEN,
                             State::REAR_LEFT_WINDOW_OPEN, State::REAR_RIGHT_WINDOW_OPEN, State::SUNROOF_WINDOW_OPEN);
    }

    /**
     * @brief Check if front left window is open.
     *
     * @return true or false.
     */
    bool_t IsFrontLeftWindowOpen() const noexcept
    {
        return IsStateSet(State::FRONT_LEFT_WINDOW_OPEN);
    }

    /**
     * @brief Check if front rear window is open.
     *
     * @return true or false.
     */
    bool_t IsFrontRightWindowOpen() const noexcept
    {
        return IsStateSet(State::FRONT_RIGHT_WINDOW_OPEN);
    }

    /**
     * @brief Check if rear left window is open.
     *
     * @return true or false.
     */
    bool_t IsRearLeftWindowOpen() const noexcept
    {
        return IsStateSet(State::REAR_LEFT_WINDOW_OPEN);
    }

    /**
     * @brief Check if rear right window is open.
     *
     * @return true or false.
     */
    bool_t IsRearRightWindowOpen() const noexcept
    {
        return IsStateSet(State::REAR_RIGHT_WINDOW_OPEN);
    }

    /**
     * @brief Check if auto sunroof is open.
     *
     * @return true or false.
     */
    bool_t IsAutoSunroofOpen() const noexcept
    {
        return IsStateSet(State::SUNROOF_WINDOW_OPEN);
    }

    /**
     * @brief Check if front wiper is open.
     *
     * @return true or false
     */
    bool_t IsFrontWiperOpen() const noexcept
    {
        return IsStateSet(State::FRONT_WIPER_ON);
    }

    /**
     * @brief Check if rear wiper is open.
     *
     * @return true or false
     */
    bool_t IsRearWiperOpen() const noexcept
    {
        return IsStateSet(State::REAR_WIPER_ON);
    }

    /**
     * @brief Get front wiper speed
     *
     * @return true or false
     */
    [[deprecated]] uint32_t GetFrontWiperSpeed() const noexcept
    {
        return 0U;
    }

    /**
     * @brief Get rear wiper speed
     *
     * @return true or false
     */
    [[deprecated]] uint32_t GetRearWiperSpeed() const noexcept
    {
        return 0U;
    }

    /**
     * @brief Set time stamp
     *
     * @param[in] time_stamp - time stmap
     */
    void SetTimestamp(Timestamp const timestamp)
    {
        timestamp_ = timestamp;
    }

    /**
     * @brief Set front left tire pressure.
     *
     * @param value Front left tire pressure in kPa.
     */
    void SetFrontLeftTirePressure(float32_t value) noexcept
    {
        front_left_tire_pressure_ = value;
    }

    /**
     * @brief Set front right tire pressure.
     *
     * @param value Front right tire pressure in kPa.
     */
    void SetFrontRightTirePressure(float32_t value) noexcept
    {
        front_right_tire_pressure_ = value;
    }

    /**
     * @brief Set rear left tire pressure.
     *
     * @param value Rear left tire pressure in kPa.
     */
    void SetRearLeftTirePressure(float32_t value) noexcept
    {
        rear_left_tire_pressure_ = value;
    }

    /**
     * @brief Set rear right tire pressure.
     *
     * @param value Rear right tire pressure in kPa.
     */
    void SetRearRightTirePressure(float32_t value) noexcept
    {
        rear_right_tire_pressure_ = value;
    }

    /**
     * @brief Set left turn light state.
     *
     * @param value true means light on, false otherwise.
     */
    void SetLeftTurnSignal(bool_t value) noexcept
    {
        value ? SetState(State::LEFT_TURN_SIGNAL_ON) : ResetState(State::LEFT_TURN_SIGNAL_ON);
    }

    /**
     * @brief Set right turn light state.
     *
     * @param value true means light on, false otherwise.
     */
    void SetRightTurnSignal(bool_t value) noexcept
    {
        value ? SetState(State::RIGHT_TURN_SIGNAL_ON) : ResetState(State::RIGHT_TURN_SIGNAL_ON);
    }

    /**
     * @brief Set warn blink light state.
     *
     * @param value true means light on, false otherwise.
     */
    void SetHazardFlasher(bool_t value) noexcept
    {
        value ? SetState(State::HARZARD_FLASHER_ON) : ResetState(State::HARZARD_FLASHER_ON);
    }

    /**
     * @brief Set low beam state.
     *
     * @param value true means light on, false otherwise.
     */
    void SetLowBeam(bool_t value) noexcept
    {
        value ? SetState(State::LOW_BEAM_ON) : ResetState(State::LOW_BEAM_ON);
    }

    /**
     * @brief Set high beam state.
     *
     * @param value true means light on, false otherwise.
     */
    void SetHighBeam(bool_t value) noexcept
    {
        value ? SetState(State::HIGH_BEAM_ON) : ResetState(State::HIGH_BEAM_ON);
    }

    /**
     * @brief Set brake light state.
     *
     * @param value true means light on, false otherwise.
     */
    void SetBrakeLight(bool_t value) noexcept
    {
        value ? SetState(State::BRAKE_LIGHT_ON) : ResetState(State::BRAKE_LIGHT_ON);
    }

    /**
     * @brief Set front fog light state.
     *
     * @param value true means light on, false otherwise.
     */
    void SetFrontFogLight(bool_t value) noexcept
    {
        value ? SetState(State::FRONT_FOG_LIGHT_ON) : ResetState(State::FRONT_FOG_LIGHT_ON);
    }

    /**
     * @brief Set rear fog light state.
     *
     * @param value true means light on, false otherwise.
     */
    void SetRearFogLight(bool_t value) noexcept
    {
        value ? SetState(State::REAR_FOG_LIGHT_ON) : ResetState(State::REAR_FOG_LIGHT_ON);
    }

    /**
     * @brief Set Need Fastening Seatbelt state.
     *
     * @param driver Driver need fastening seatbelt state. true means need, false otherwise.
     * @param passenger  Front passenger need fastening seatbelt state. true means need, false otherwise.
     */
    void SetNeedFasteningSeatbelt(bool_t driver, bool_t passenger) noexcept
    {
        driver ? SetState(State::DRIVER_SEATBELT_UNLOCK) : ResetState(State::DRIVER_SEATBELT_UNLOCK);
        passenger ? SetState(State::PASSENGER_SEATBELT_UNLOCK) : ResetState(State::PASSENGER_SEATBELT_UNLOCK);
    }

    /**
     * @brief Set vehicle door state
     *
     * @param fl Front left door state. true means open, false otherwise.
     * @param fr Front right door state. true means open, false otherwise.
     * @param rl Rear left door state. true means open, false otherwise.
     * @param rr Rear right door state. true means open, false otherwise.
     * @param trunk Trunk door state. true means open, false otherwise.
     * @param ch Car hood state. true means open, false otherwise.
     */
    void SetDoorState(bool_t fl, bool_t fr, bool_t rl, bool_t rr, bool_t trunk, bool_t hood) noexcept
    {
        fl ? SetState(State::FRONT_LEFT_DOOR_OPEN) : ResetState(State::FRONT_LEFT_DOOR_OPEN);
        fr ? SetState(State::FRONT_RIGHT_DOOR_OPEN) : ResetState(State::FRONT_RIGHT_DOOR_OPEN);
        rl ? SetState(State::REAR_LEFT_DOOR_OPEN) : ResetState(State::REAR_LEFT_DOOR_OPEN);
        rr ? SetState(State::REAR_RIGHT_DOOR_OPEN) : ResetState(State::REAR_RIGHT_DOOR_OPEN);
        trunk ? SetState(State::TRUNK_DOOR_OPEN) : ResetState(State::TRUNK_DOOR_OPEN);
        hood ? SetState(State::CAR_HOOD_OPEN) : ResetState(State::CAR_HOOD_OPEN);
    }

    /**
     * @brief Set vehicle windows state.
     *
     * @param fl Front left window state. true means open, false otherwise.
     * @param fr Front right window state. true means open, false otherwise.
     * @param rl Rear left window state. true means open, false otherwise.
     * @param rr Rear right window state. true means open, false otherwise.
     * @param as Auto sunroof state. true means open, false otherwise.
     */
    void SetWindowState(bool_t fl, bool_t fr, bool_t rl, bool_t rr, bool_t sunroof) noexcept
    {
        fl ? SetState(State::FRONT_LEFT_WINDOW_OPEN) : ResetState(State::FRONT_LEFT_WINDOW_OPEN);
        fr ? SetState(State::FRONT_RIGHT_WINDOW_OPEN) : ResetState(State::FRONT_RIGHT_WINDOW_OPEN);
        rl ? SetState(State::REAR_LEFT_WINDOW_OPEN) : ResetState(State::REAR_LEFT_WINDOW_OPEN);
        rr ? SetState(State::REAR_RIGHT_WINDOW_OPEN) : ResetState(State::REAR_RIGHT_WINDOW_OPEN);
        sunroof ? SetState(State::SUNROOF_WINDOW_OPEN) : ResetState(State::SUNROOF_WINDOW_OPEN);
    }

    /**
     * @brief Set wiper state
     *
     * @param fw Front wiper state. true means open, false otherwise.
     * @param rw Rear wiper door state. true means open, false otherwise.
     */
    void SetWiperState(bool_t fw, bool_t rw) noexcept
    {
        fw ? SetState(State::FRONT_WIPER_ON) : ResetState(State::FRONT_WIPER_ON);
        rw ? SetState(State::REAR_WIPER_ON) : ResetState(State::REAR_WIPER_ON);
    }

    uint32_t GetStateValue() const noexcept
    {
        return state_flags_;
    }

    void SetStateValue(uint32_t value) noexcept
    {
        state_flags_ = value;
    }

    uint32_t GetInvalidFlagValue() const noexcept
    {
        return invalid_flags_;
    }

    void SetInvalidFlagValue(uint32_t value) noexcept
    {
        invalid_flags_ = value;
    }

    /**
     * @brief Get serialized size at give byte alignment value
     *
     * @tparam ALIGN Byte alignment value
     *
     * @return Serialized size
     */
    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return timestamp_.GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(front_left_tire_pressure_, front_right_tire_pressure_,
                                                          rear_left_tire_pressure_, rear_right_tire_pressure_,
                                                          state_flags_, invalid_flags_);
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::serialization::SerializationBufferOverflowException if buffer
     * size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << timestamp_ << front_left_tire_pressure_ << front_right_tire_pressure_ << rear_left_tire_pressure_
                   << rear_right_tire_pressure_ << state_flags_ << invalid_flags_ << holo::serialization::align;
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if
     * buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        deserializer >> timestamp_ >> front_left_tire_pressure_ >> front_right_tire_pressure_ >>
            rear_left_tire_pressure_ >> rear_right_tire_pressure_ >> state_flags_ >> invalid_flags_ >>
            holo::serialization::align;
    }

private:
    template <typename T, typename... Args>
    uint32_t getFlags(T value, Args&&... args) const noexcept
    {
        return static_cast<uint32_t>(value) | getFlags(std::forward<Args>(args)...);
    }

    template <typename T>
    uint32_t getFlags(T value) const noexcept
    {
        return static_cast<uint32_t>(value);
    }

    holo::common::Timestamp timestamp_;  ///< Timestamp of this object.

    /* Motion */
    float32_t front_left_tire_pressure_;   ///< std::NaN -> Invalid.
    float32_t front_right_tire_pressure_;  ///< std::NaN -> Invalid.
    float32_t rear_left_tire_pressure_;    ///< std::NaN -> Invalid.
    float32_t rear_right_tire_pressure_;   ///< std::NaN -> Invalid.
    uint32_t  state_flags_;
    uint32_t  invalid_flags_;
};

/**
 * @}
 *
 */

}  // namespace common

using VehicleBodyState[[deprecated]] = common::VehicleBodyState;

}  // namespace holo

#endif
