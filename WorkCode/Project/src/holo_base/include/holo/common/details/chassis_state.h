/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file chassis_state.h
 * @brief This header file defines ChassisState class
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-12-24
 */

#ifndef HOLO_COMMON_DETAILS_CHASSIS_STATE_H_
#define HOLO_COMMON_DETAILS_CHASSIS_STATE_H_

#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/serialization/serialization.h>

namespace holo
{
namespace common
{
namespace details
{
/**
 * @brief ChassisState class provide abstracted vehicle chassis information.
 */
class ChassisState
{
public:
    /**
     * @brief enumerate gear position.
     */
    enum class GearPosition : uint8_t
    {
        UNKNOWN = 0,  ///< Gear at unknown position.
        P       = 1,  ///< Gear at P position.
        R       = 2,  ///< Gear at R position.
        N       = 3,  ///< Gear at N position.
        D       = 4,  ///< Gear at D position.
        S       = 5,  ///< Gear at S position.
        INVALID = 6   ///< Gear at invalid position.
    };

    enum class State : uint32_t
    {
        HAND_BRAKE_HOLD                 = 1U << 0U,   ///< handbrake is hold
        LATERAL_TAKEOVER                = 1U << 1U,   ///< lateral control takeover
        LATERAL_INACTIVE                = 1U << 2U,   ///< lateral control is inactive
        LONGITUDINAL_TAKEOVER           = 1U << 3U,   ///< longitudinal control takeover
        LONGITUDINAL_INACTIVE           = 1U << 4U,   ///< longitudinal control inactive
        GEAR_ACTUATOR_INACTIVE          = 1U << 5U,   ///< gear actuator is inactive
        GEAR_ACTUATOR_NOT_READY         = 1U << 6U,   ///< gear actuator is not ready
        LATERAL_ACTUATOR_INACTIVE       = 1U << 7U,   ///< lateral actuator is inactive
        LATERAL_ACTUATOR_NOT_READY      = 1U << 8U,   ///< lateral actuator is not ready
        LONGITUDINAL_ACTUATOR_INACTIVE  = 1U << 9U,   ///< longitudinal actuator is inactive
        LONGITUDINAL_ACTUATOR_NOT_READY = 1U << 10U,  ///< longitudinal actuator is not ready
        VEHICLE_MOVE_BACKWARD           = 1U << 11U,  ///< vehicle is moving backward
        VEHICLE_STANDSTILL              = 1U << 12U,  ///< vehicle is standstill
        VEHICLE_SLIDE                   = 1U << 13U,  ///< vehicle is sliding
    };

    enum class InvalidFlag : uint32_t
    {
        VEHICLE_SPEED_INVALID              = 1U << 0U,
        FL_WHEEL_SPEED_INVALID             = 1U << 1U,
        FR_WHEEL_SPEED_INVALID             = 1U << 2U,
        RL_WHEEL_SPEED_INVALID             = 1U << 3U,
        RR_WHEEL_SPEED_INVALID             = 1U << 4U,
        FL_WHEEL_PULSE_INVALID             = 1U << 5U,
        FR_WHEEL_PULSE_INVALID             = 1U << 6U,
        RL_WHEEL_PULSE_INVALID             = 1U << 7U,
        RR_WHEEL_PULSE_INVALID             = 1U << 8U,
        FRONT_WHEEL_ANGLE_INVALID          = 1U << 9U,
        LONGITUDINAL_CONTROL_VALUE_INVALID = 1U << 10U,
        BRAKE_INVALID                      = 1U << 11U,
        GEAR_ACTUATOR_INVALID              = 1U << 12U,
        LATERAL_ACTUATOR_INVALID           = 1U << 13U,
        LONGITUDINAL_ACTUATOR_INVALID      = 1U << 14U,
    };

public:
    /**
     * @brief Default constructor.
     */
    ChassisState() noexcept
      : timestamp_{}
      , vehicle_speed_{}
      , front_left_wheel_speed_{}
      , front_right_wheel_speed_{}
      , rear_left_wheel_speed_{}
      , rear_right_wheel_speed_{}
      , front_left_wheel_pulse_{}
      , front_right_wheel_pulse_{}
      , rear_left_wheel_pulse_{}
      , rear_right_wheel_pulse_{}
      , longitudinal_acceleration_{}
      , lateral_acceleration_{}
      , yaw_rate_{}
      , front_wheel_angle_{}
      , longitudinal_control_value_{}
      , energy_source_level_{}
      , gear_pos_{}
      , gear_level_{}
      , state_flags_{}
      , invalid_flags_{}
    {
    }

    /**
     * @{
     * Begin getter API group.
     */

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
     * @brief Get vehicle speed from vehicle chassis.
     *
     * @return Vehicle speed in @f$m/s@f$. Forward is positive direction.
     */
    holo::float32_t GetVehicleSpeed() const noexcept
    {
        return vehicle_speed_;
    }

    /**
     * @brief Get front left wheel speed from vehicle chassis.
     *
     * @return Front left wheel speed in @f$m/s@f$. Forward is positive direction.
     */
    holo::float32_t GetFrontLeftWheelSpeed() const noexcept
    {
        return front_left_wheel_speed_;
    }

    /**
     * @brief Get front right wheel speed from vehicle chassis.
     *
     * @return Front right wheel speed in @f$m/s@f$. Forward is positive direction.
     */
    holo::float32_t GetFrontRightWheelSpeed() const noexcept
    {
        return front_right_wheel_speed_;
    }

    /**
     * @brief Get rear left wheel speed from vehicle chassis.
     *
     * @return Rear left wheel speed in @f$m/s@f$. Forward is positive direction.
     */
    holo::float32_t GetRearLeftWheelSpeed() const noexcept
    {
        return rear_left_wheel_speed_;
    }

    /**
     * @brief Get rear right wheel speed from vehicle chassis.
     *
     * @return Rear right wheel speed in @f$m/s@f$. Forward is positive direction.
     */
    holo::float32_t GetRearRightWheelSpeed() const noexcept
    {
        return rear_right_wheel_speed_;
    }

    /**
     * @brief Get front left wheel pulse from vehicle chassis.
     *
     * @return Front left wheel pulse count.
     */
    holo::uint32_t GetFrontLeftWheelPulse() const noexcept
    {
        return front_left_wheel_pulse_;
    }

    /**
     * @brief Get front right wheel pulse from vehicle chassis.
     *
     * @return Front right wheel pulse count.
     */
    holo::uint32_t GetFrontRightWheelPulse() const noexcept
    {
        return front_right_wheel_pulse_;
    }

    /**
     * @brief Get rear left wheel pulse from vehicle chassis.
     *
     * @return Rear left wheel pulse count.
     */
    holo::uint32_t GetRearLeftWheelPulse() const noexcept
    {
        return rear_left_wheel_pulse_;
    }

    /**
     * @brief Get rear right wheel pulse from vehicle chassis.
     *
     * @return Rear right wheel pulse count.
     */
    holo::uint32_t GetRearRightWheelPulse() const noexcept
    {
        return rear_right_wheel_pulse_;
    }

    /**
     * @brief Get longitudinal acceleration from vehicle chassis.
     *
     * @return Longitudinal acceleration in @f$m/s^2@f$. Forward is positive direction.
     */
    holo::float32_t GetLongitudinalAcceleration() const noexcept
    {
        return longitudinal_acceleration_;
    }

    /**
     * @brief Get lateral acceleration from vehicle chassis.
     *
     * @return Lateral acceleration in @f$m/s^2@f$. Left is positive direction.
     */
    holo::float32_t GetLateralAcceleration() const noexcept
    {
        return lateral_acceleration_;
    }

    /**
     * @brief Get yaw rate from vehicle chassis.
     *
     * @return Raw rate in @f$rad/s^2@f$.
     */
    holo::float32_t GetYawRate() const noexcept
    {
        return yaw_rate_;
    }

    /**
     * @brief Get front wheel angle from vehicle chassis.
     *
     * @return Front wheel angle in @f$rad@f$. Left is positive direction.
     */
    holo::float32_t GetFrontWheelAngle() const noexcept
    {
        return front_wheel_angle_;
    }

    /**
     * @brief Get external ecu longitudinal control value.
     *
     * @return Longitudinal control value read from actuator.
     * - For torque control actuators, unit is N m
     * - For acc control actuators, unit is m/s^2
     */
    holo::float32_t GetLongitudinalControlValue() const noexcept
    {
        return longitudinal_control_value_;
    }

    /**
     * @brief Get energy source level(fuel level or battery level).
     *
     * @return Energy level percentage.
     */
    holo::uint8_t GetEnergySourceLevel() const noexcept
    {
        return energy_source_level_;
    }

    /**
     * @brief Get gear position.
     *
     * @return GearPosition.
     */
    GearPosition GetGearPosition() const noexcept
    {
        return gear_pos_;
    }

    /**
     * @brief Get gear level.
     *
     * @detail For gear position P, N, Gear level has no meaning. For gear position R, D and S,
     * gear level means transmission level.
     *
     * @return Gear level.
     */
    holo::uint8_t GetGearLevel() const noexcept
    {
        return gear_level_;
    }

    /**
     * @brief Check if any state is set
     *
     * @return True if any state is set otherwise false.
     */
    holo::bool_t IsStateSet() const noexcept
    {
        return state_flags_ != 0U;
    }

    /**
     * @brief Check if all state in parameter list is set
     *
     * @tparam Args State type
     * @param args State parameter
     *
     * @return True if all state is set otherwise false
     */
    template <typename... Args>
    holo::bool_t IsStateSet(Args&&... args) const noexcept
    {
        return (state_flags_ & getFlags(std::forward<Args>(args)...)) == getFlags(std::forward<Args>(args)...);
    }

    /**
     * @brief Check if any state in parameter list is set
     *
     * @tparam Args State type
     * @param args State parameter
     *
     * @return True if any state is set otherwise false
     */
    template <typename... Args>
    holo::bool_t IsStateSetAny(Args&&... args) const noexcept
    {
        return (state_flags_ & getFlags(std::forward<Args>(args)...)) != 0U;
    }

    /**
     * @brief Check if any invalid flag is set
     *
     * @return True if any invalid flag is set otherwise false.
     */
    holo::bool_t IsInvalidFlagSet() const noexcept
    {
        return invalid_flags_ != 0U;
    }

    /**
     * @brief Check if all invalid flag in parameter list is set
     *
     * @tparam Args InvalidFlag type
     * @param args Invalid flag parameter
     *
     * @return True if all invalid flag is set otherwise false
     */
    template <typename... Args>
    holo::bool_t IsInvalidFlagSet(Args&&... args) const noexcept
    {
        return (invalid_flags_ & getFlags(std::forward<Args>(args)...)) == getFlags(std::forward<Args>(args)...);
    }

    /**
     * @brief Check if any invalid flag in parameter list is set
     *
     * @tparam Args InvalidFlag type
     * @param args Invalid flag parameter
     *
     * @return True if any invalid flag is set otherwise false
     */
    template <typename... Args>
    holo::bool_t IsInvalidFlagSetAny(Args&&... args) const noexcept
    {
        return (invalid_flags_ & getFlags(std::forward<Args>(args)...)) != 0U;
    }

    holo::uint32_t GetStateValue() const noexcept
    {
        return state_flags_;
    }

    holo::uint32_t GetInvalidFlagValue() const noexcept
    {
        return invalid_flags_;
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
     * @brief Set time stamp
     *
     * @param[in] time_stamp - time stmap
     */
    void SetTimestamp(Timestamp const timestamp)
    {
        this->timestamp_ = timestamp;
    }

    /**
     * @brief Set vehicle speed.
     *
     * @param value Vehicle speed in @f$m/s@f$. Forward is positive direction.
     */
    void SetVehicleSpeed(holo::float32_t value) noexcept
    {
        vehicle_speed_ = value;
    }

    /**
     * @brief Set front left wheel speed.
     *
     * @param value Front left wheel speed in @f$m/s@f$. Forward is positive direction.
     */
    void SetFrontLeftWheelSpeed(holo::float32_t value) noexcept
    {
        front_left_wheel_speed_ = value;
    }

    /**
     * @brief Set front right wheel speed.
     *
     * @param value Front right wheel speed in @f$m/s@f$. Forward is positive direction.
     */
    void SetFrontRightWheelSpeed(holo::float32_t value) noexcept
    {
        front_right_wheel_speed_ = value;
    }

    /**
     * @brief Set rear left wheel speed.
     *
     * @param value Rear left wheel speed in @f$m/s@f$. Forward is positive direction.
     */
    void SetRearLeftWheelSpeed(holo::float32_t value) noexcept
    {
        rear_left_wheel_speed_ = value;
    }

    /**
     * @brief Set rear right wheel speed.
     *
     * @param value Rear right wheel speed in @f$m/s@f$. Forward is positive direction.
     */
    void SetRearRightWheelSpeed(holo::float32_t value) noexcept
    {
        rear_right_wheel_speed_ = value;
    }

    /**
     * @brief Set front left wheel pulse.
     *
     * @param value Front left wheel pulse count.
     */
    void SetFrontLeftWheelPulse(holo::uint32_t value) noexcept
    {
        front_left_wheel_pulse_ = value;
    }

    /**
     * @brief Set front right wheel pulse.
     *
     * @param value Front right wheel pulse count.
     */
    void SetFrontRightWheelPulse(holo::uint32_t value) noexcept
    {
        front_right_wheel_pulse_ = value;
    }

    /**
     * @brief Set rear left wheel pulse.
     *
     * @param value Rear left wheel pulse count.
     */
    void SetRearLeftWheelPulse(holo::uint32_t value) noexcept
    {
        rear_left_wheel_pulse_ = value;
    }

    /**
     * @brief Set rear right wheel pulse.
     *
     * @param value Rear right wheel pulse count.
     */
    void SetRearRightWheelPulse(holo::uint32_t value) noexcept
    {
        rear_right_wheel_pulse_ = value;
    }

    /**
     * @brief Set longitudinal acceleration.
     *
     * @param value Longitudinal acceleration in @f$m/s^2@f$. Forward is positive direction.
     */
    void SetLongitudinalAcceleration(holo::float32_t value) noexcept
    {
        longitudinal_acceleration_ = value;
    }

    /**
     * @brief Set lateral acceleration.
     *
     * @param value Lateral acceleration in @f$m/s^2@f$. Left is positive direction.
     */
    void SetLateralAcceleration(holo::float32_t value) noexcept
    {
        lateral_acceleration_ = value;
    }

    /**
     * @brief Set yaw rate.
     *
     * @param value Yaw rate in @f$rad/s^2@f$.
     */
    void SetYawRate(holo::float32_t value) noexcept
    {
        yaw_rate_ = value;
    }

    /**
     * @brief Set front wheel angle.
     *
     * @param value Front wheel angle in @f$rad@f$.
     */
    void SetFrontWheelAngle(holo::float32_t value) noexcept
    {
        front_wheel_angle_ = value;
    }

    /**
     * @brief Set external ecu longitudinal control value.
     *
     * @param value Longitudinal control value.
     */
    void SetLongitudinalControlValue(holo::float32_t value) noexcept
    {
        longitudinal_control_value_ = value;
    }

    /**
     * @brief Set vehicle energy source level. unit %.
     *
     * @return Energy source level.
     */
    void SetEnergySourceLevel(holo::uint8_t value) noexcept
    {
        energy_source_level_ = value > 100 ? 100 : value;
    }

    /**
     * @brief Set gear position
     *
     * @param value gear position value
     */
    void SetGearPosition(GearPosition value) noexcept
    {
        gear_pos_ = value;
    }

    /**
     * @brief Set gear level
     *
     * @param value gear level value
     */
    void SetGearLevel(holo::uint8_t value) noexcept
    {
        gear_level_ = value;
    }

    /**
     * @brief Set state flags
     *
     * @tparam Args State type
     * @param args State flags
     */
    template <typename... Args>
    void SetState(Args... args) noexcept
    {
        state_flags_ |= getFlags(std::forward<Args>(args)...);
    }

    /**
     * @brief Reset state flags
     *
     * @tparam Args State type
     * @param args State flags
     */
    template <typename... Args>
    void ResetState(Args... args) noexcept
    {
        state_flags_ &= ~getFlags(std::forward<Args>(args)...);
    }

    /**
     * @brief Reset all states
     */
    void ResetState() noexcept
    {
        state_flags_ = 0U;
    }

    /**
     * @brief Set invalid flags
     *
     * @tparam Args InvalidFlag type
     * @param args Invalid flags
     */
    template <typename... Args>
    void SetInvalidFlag(Args... args) noexcept
    {
        invalid_flags_ |= getFlags(std::forward<Args>(args)...);
    }

    /**
     * @brief Reset invalid flags
     *
     * @tparam Args InvalidFlag type
     * @param args Invalid flags
     */
    template <typename... Args>
    void ResetInvalidFlag(Args... args) noexcept
    {
        invalid_flags_ &= ~getFlags(std::forward<Args>(args)...);
    }

    /**
     * @brief Reset all invalid flags
     */
    void ResetInvalidFlag() noexcept
    {
        invalid_flags_ = 0U;
    }

    void SetStateValue(uint32_t value) noexcept
    {
        state_flags_ = value;
    }

    void SetInvalidFlagValue(uint32_t value) noexcept
    {
        invalid_flags_ = value;
    }

    /**
     * @}
     */

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
               holo::serialization::SerializedSize<ALIGN>(
                   vehicle_speed_, front_left_wheel_speed_, front_right_wheel_speed_, rear_left_wheel_speed_,
                   rear_right_wheel_speed_, front_left_wheel_pulse_, front_right_wheel_pulse_, rear_left_wheel_pulse_,
                   rear_right_wheel_pulse_, longitudinal_acceleration_, lateral_acceleration_, yaw_rate_,
                   front_wheel_angle_, longitudinal_control_value_, energy_source_level_, gear_pos_, gear_level_,
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
        serializer << timestamp_ << vehicle_speed_ << front_left_wheel_speed_ << front_right_wheel_speed_
                   << rear_left_wheel_speed_ << rear_right_wheel_speed_ << front_left_wheel_pulse_
                   << front_right_wheel_pulse_ << rear_left_wheel_pulse_ << rear_right_wheel_pulse_
                   << longitudinal_acceleration_ << lateral_acceleration_ << yaw_rate_ << front_wheel_angle_
                   << longitudinal_control_value_ << energy_source_level_ << static_cast<uint8_t>(gear_pos_)
                   << gear_level_ << state_flags_ << invalid_flags_ << holo::serialization::align;
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
        uint8_t gear_pos = 0U;
        deserializer >> timestamp_ >> vehicle_speed_ >> front_left_wheel_speed_ >> front_right_wheel_speed_ >>
            rear_left_wheel_speed_ >> rear_right_wheel_speed_ >> front_left_wheel_pulse_ >> front_right_wheel_pulse_ >>
            rear_left_wheel_pulse_ >> rear_right_wheel_pulse_ >> longitudinal_acceleration_ >> lateral_acceleration_ >>
            yaw_rate_ >> front_wheel_angle_ >> longitudinal_control_value_ >> energy_source_level_ >> gear_pos >>
            gear_level_ >> state_flags_ >> invalid_flags_ >> holo::serialization::align;
        gear_pos_ = static_cast<GearPosition>(gear_pos);
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
    holo::float32_t vehicle_speed_;              ///< Vehicle speed from vehicle chassis in m/s.
    holo::float32_t front_left_wheel_speed_;     ///< Front left wheel speed in m/s.
    holo::float32_t front_right_wheel_speed_;    ///< Front right wheel speed in m/s.
    holo::float32_t rear_left_wheel_speed_;      ///< Rear left wheel speed in m/s.
    holo::float32_t rear_right_wheel_speed_;     ///< Rear right wheel speed in m/s.
    holo::uint32_t  front_left_wheel_pulse_;     ///< Front left wheel pulse.
    holo::uint32_t  front_right_wheel_pulse_;    ///< Front right wheel pulse.
    holo::uint32_t  rear_left_wheel_pulse_;      ///< Rear left wheel pulse.
    holo::uint32_t  rear_right_wheel_pulse_;     ///< Rear right wheel pulse.
    holo::float32_t longitudinal_acceleration_;  ///< Acceleration in longitudinal direction.
    holo::float32_t lateral_acceleration_;       ///< Acceleration in latitudinal direction.
    holo::float32_t yaw_rate_;                   ///< Vehicle yaw rate at Z axis in rad/s^2
    holo::float32_t front_wheel_angle_;  ///< Front wheel angle in rad. Center is 0, positive value for turn left
    holo::float32_t longitudinal_control_value_;  ///< Longitudinal actuator output control value.

    holo::uint8_t energy_source_level_;  ///< Fuel or battery level in percetage.
    GearPosition  gear_pos_;
    holo::uint8_t gear_level_;

    holo::uint32_t state_flags_;
    holo::uint32_t invalid_flags_;
};

/**
 * @}
 */

}  // namespace details
}  // namespace common
}  // namespace holo

#endif
