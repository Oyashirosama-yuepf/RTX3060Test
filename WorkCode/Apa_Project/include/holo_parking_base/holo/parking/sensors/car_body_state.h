/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file car_body_state.h
 * @brief This header file defines Parking CarBodyState class
 * @author songbo(songbo@holomatic.com)
 * @date 2022-03-08
 */

#ifndef CAR_BODY_STATE_H
#define CAR_BODY_STATE_H

#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/serialization/serialization.h>

namespace holo {
namespace parking {
namespace sensors {
class CarBodyState
{
/**
 * @brief ChassisState class provide abstracted vehicle chassis information.
 */
// public:
//     enum class GearPosition : uint8_t
//     {
        //    UNKNOWN = 0,
        //    P       = 1,
        //    R       = 2,
        //    N       = 3,
        //    D       = 4,
        //    S       = 5,
        //    INVALID = 6
//     };

//     enum class DoorState : uint8_t
//     {
//         CLOSE = 0,
//         OPEN  = 1,
//     };

//     enum class LockState : uint8_t
//     {
//         UNLOCK = 0,
//         LOCK   = 1,
//     };

//     enum class PedalState : uint8_t
//     {
//         RELEASE = 0,
//         PRESS   = 1,
//     };

//     enum class MirrorState : uint8_t
//     {
//         UNFOLD = 0,
//         FOLD   = 1,
//     };

//     enum class SafeBeltState : uint8_t
//     {
//         FASTENED   = 0,
//         UNFASTENED = 1,
//         NOT_USED   = 2,
//         INVALID    = 3,
//     };

public:
    CarBodyState() noexcept
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
      , gear_position_{}
      , driver_door_ajar_status_{}
      , passenger_door_ajar_status_{}
      , rear_left_door_ajar_status_{}
      , rear_right_door_ajar_status_{}
      , trunk_ajar_status_{}
      , bonnet_ajar_status_{}
      , brake_pedal_status_{}
      , accelerator_pedal_status_{}
      , epb_system_status_{}
      , passenger_seat_belt_status_{}
      , driver_seat_belt_status_{}
      , right_mirror_status_{}
      , left_mirror_status_{}
      , key_status_{}
      , steering_abort_{}
      , engine_running_status_{}
      , gear_take_over_state_(0U)
    {
    }

    Timestamp GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    void SetTimestamp(Timestamp const timestamp)
    {
        timestamp_ = timestamp;
    }

    uint8_t GetGearTakeOverState() const noexcept
    {
        return gear_take_over_state_;
    }

    void SetGearTakeOverState(uint8_t const gear_take_over_state)
    {
        gear_take_over_state_ = gear_take_over_state;
    }

    float GetVehicleSpeed() const noexcept
    {
        return vehicle_speed_;
    }

    void SetVehicleSpeed(float const value)
    {
        vehicle_speed_ = value;
    }

    float GetFrontLeftWheelSpeed() const noexcept
    {
        return front_left_wheel_speed_;
    }

    void SetFrontLeftWheelSpeed(float const value)
    {
        front_left_wheel_speed_ = value;
    }

    float GetFrontRightWheelSpeed() const noexcept
    {
        return front_right_wheel_speed_;
    }

    void SetFrontRightWheelSpeed(float const value)
    {
        front_right_wheel_speed_ = value;
    }

    float GetRearLeftWheelSpeed() const noexcept
    {
        return rear_left_wheel_speed_;
    }

    void SetRearLeftWheelSpeed(float const value)
    {
        rear_left_wheel_speed_ = value;
    }

    float GetRearRightWheelSpeed() const noexcept
    {
        return rear_right_wheel_speed_;
    }

    void SetRearRightWheelSpeed(float const value)
    {
        rear_right_wheel_speed_ = value;
    }

    uint32_t GetFrontLeftWheelPulse() const noexcept
    {
        return front_left_wheel_pulse_;
    }

    void SetFrontLeftWheelPulse(uint32_t const value)
    {
        front_left_wheel_pulse_ = value;
    }

    uint32_t GetFrontRightWheelPulse() const noexcept
    {
        return front_right_wheel_pulse_;
    }

    void SetFrontRightWheelPulse(uint32_t const value)
    {
        front_right_wheel_pulse_ = value;
    }

    uint32_t GetRearLeftWheelPulse() const noexcept
    {
        return rear_left_wheel_pulse_;
    }

    void SetRearLeftWheelPulse(uint32_t const value)
    {
        rear_left_wheel_pulse_ = value;
    }

    uint32_t GetRearRightWheelPulse() const noexcept
    {
        return rear_right_wheel_pulse_;
    }

    void SetRearRightWheelPulse(uint32_t const value)
    {
        rear_right_wheel_pulse_ = value;
    }

    void SetLongitudinalAcceleration(float const value)
    {
        longitudinal_acceleration_ = value;
    }

    float GetLongitudinalAcceleration() const noexcept
    {
        return longitudinal_acceleration_;
    }

    void SetLateralAcceleration(float const value)
    {
        lateral_acceleration_ = value;
    }

    float GetLateralAcceleration() const noexcept
    {
        return lateral_acceleration_;
    }

    float GetYawRate() const noexcept
    {
        return yaw_rate_;
    }

    void SetYawRate(float const value)
    {
        yaw_rate_ = value;
    }

    float GetFrontWheelAngle() const noexcept
    {
        return front_wheel_angle_;
    }

    void SetFrontWheelAngle(float const value)
    {
        front_wheel_angle_ = value;
    }

    float GetLongitudinalControlValue() const noexcept
    {
        return longitudinal_control_value_;
    }

    void SetLongitudinalControlValue(float const value)
    {
        longitudinal_control_value_ = value;
    }

    uint8_t GetGearPosition() const noexcept
    {
        return gear_position_;
    }

    void SetGearPosition(uint8_t const value)
    {
        gear_position_ = value;
    }

    uint8_t GetDriverDoorAjarStatus() const noexcept
    {
        return driver_door_ajar_status_;
    }

    void SetDriverDoorAjarStatus(uint8_t const value)
    {
        driver_door_ajar_status_ = value;
    }

    uint8_t GetPassengerDoorAjarStatus() const noexcept
    {
        return passenger_door_ajar_status_;
    }

    void SetPassengerDoorAjarStatus(uint8_t const value)
    {
        passenger_door_ajar_status_ = value;
    }

    uint8_t GetRearLeftDoorAjarStatus() const noexcept
    {
        return rear_left_door_ajar_status_;
    }

    void SetRearLeftDoorAjarStatus(uint8_t const value)
    {
        rear_left_door_ajar_status_ = value;
    }

    uint8_t GetRearRightDoorAjarStatus() const noexcept
    {
        return rear_right_door_ajar_status_;
    }

    void SetRearRightDoorAjarStatus(uint8_t const value)
    {
        rear_right_door_ajar_status_ = value;
    }

    uint8_t GetTrunkAjarStatus() const noexcept
    {
        return trunk_ajar_status_;
    }

    void SetTrunkAjarStatus(uint8_t const value)
    {
        trunk_ajar_status_ = value;
    }

    uint8_t GetBonnetAjarStatus() const noexcept
    {
        return bonnet_ajar_status_;
    }

    void SetBonnetAjarStatus(uint8_t const value)
    {
        bonnet_ajar_status_ = value;
    }

    uint8_t GetBrakePedalStatus() const noexcept
    {
        return brake_pedal_status_;
    }

    void SetBrakePedalStatus(uint8_t const value)
    {
        brake_pedal_status_ = value;
    }

    uint8_t GetAcceleratorPedalStatus() const noexcept
    {
        return accelerator_pedal_status_;
    }

    void SetAcceleratorPedalStatus(uint8_t const value)
    {
        accelerator_pedal_status_ = value;
    }

    uint8_t GetEpbSystemStatus() const noexcept
    {
        return epb_system_status_;
    }

    void SetEpbSystemStatus(uint8_t const value)
    {
        epb_system_status_ = value;
    }

    uint8_t GetPassengerSeatBeltStatus() const noexcept
    {
        return passenger_seat_belt_status_;
    }

    void SetPassengerSeatBeltStatus(uint8_t const value)
    {
        passenger_seat_belt_status_ = value;
    }

    uint8_t GetDriverSeatBeltStatus() const noexcept
    {
        return driver_seat_belt_status_;
    }

    void SetDriverSeatBeltStatus(uint8_t const value)
    {
        driver_seat_belt_status_ = value;
    }

    uint8_t GetRightMirrorStatus() const noexcept
    {
        return right_mirror_status_;
    }

    void SetRightMirrorStatus(uint8_t const value)
    {
        right_mirror_status_ = value;
    }

    uint8_t GetLeftMirrorStatus() const noexcept
    {
        return left_mirror_status_;
    }

    void SetLeftMirrorStatus(uint8_t const value)
    {
        left_mirror_status_ = value;
    }

    uint8_t GetKeyStatus() const noexcept
    {
        return key_status_;
    }

    void SetKeyStatus(uint8_t const value)
    {
        key_status_ = value;
    }

    uint8_t GetSteeringAbort() const noexcept
    {
        return steering_abort_;
    }

    void SetSteeringAbort(uint8_t const value)
    {
        steering_abort_ = value;
    }

    uint8_t GetEngineRunningStatus() const noexcept
    {
        return engine_running_status_;
    }

    void SetEngineRunningStatus(uint8_t const value)
    {
        engine_running_status_ = value;
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return timestamp_.GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(
                   vehicle_speed_, front_left_wheel_speed_, front_right_wheel_speed_, rear_left_wheel_speed_,
                   rear_right_wheel_speed_, front_left_wheel_pulse_, front_right_wheel_pulse_,
                   rear_left_wheel_pulse_, rear_right_wheel_pulse_, longitudinal_acceleration_,
                   lateral_acceleration_, yaw_rate_, front_wheel_angle_, longitudinal_control_value_,
                   gear_position_, driver_door_ajar_status_, passenger_door_ajar_status_,
                   rear_left_door_ajar_status_, rear_right_door_ajar_status_, trunk_ajar_status_, 
                   bonnet_ajar_status_, brake_pedal_status_, accelerator_pedal_status_, epb_system_status_, 
                   passenger_seat_belt_status_, driver_seat_belt_status_, right_mirror_status_, left_mirror_status_,
                   key_status_, steering_abort_, engine_running_status_, gear_take_over_state_);
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << timestamp_ << vehicle_speed_ << front_left_wheel_speed_ << front_right_wheel_speed_
                   << rear_left_wheel_speed_ << rear_right_wheel_speed_ << front_left_wheel_pulse_
                   << front_right_wheel_pulse_ << rear_left_wheel_pulse_ << rear_right_wheel_pulse_ 
                   << longitudinal_acceleration_ << lateral_acceleration_ << yaw_rate_ << front_wheel_angle_
                   << longitudinal_control_value_ << gear_position_ << driver_door_ajar_status_
                   << passenger_door_ajar_status_ << rear_left_door_ajar_status_
                   << rear_right_door_ajar_status_ << trunk_ajar_status_ << bonnet_ajar_status_
                   << brake_pedal_status_ << accelerator_pedal_status_ << epb_system_status_
                   << passenger_seat_belt_status_ << driver_seat_belt_status_
                   << right_mirror_status_ << left_mirror_status_ << key_status_ << steering_abort_
                   << engine_running_status_ <<gear_take_over_state_ <<  holo::serialization::align;
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        uint8_t gear_pos = 0U;
        deserializer >> timestamp_ >> vehicle_speed_ >> front_left_wheel_speed_ >> front_right_wheel_speed_
                     >> rear_left_wheel_speed_ >> rear_right_wheel_speed_ >> front_left_wheel_pulse_
                     >> front_right_wheel_pulse_ >> rear_left_wheel_pulse_ >> rear_right_wheel_pulse_ 
                     >> longitudinal_acceleration_ >> lateral_acceleration_ >> yaw_rate_ >> front_wheel_angle_
                     >> longitudinal_control_value_ >> gear_position_ >> driver_door_ajar_status_
                     >> passenger_door_ajar_status_ >> rear_left_door_ajar_status_
                     >> rear_right_door_ajar_status_ >> trunk_ajar_status_ >> bonnet_ajar_status_
                     >> brake_pedal_status_ >> accelerator_pedal_status_ >> epb_system_status_
                     >> passenger_seat_belt_status_ >> driver_seat_belt_status_
                     >> right_mirror_status_ >> left_mirror_status_ >> key_status_ >> steering_abort_
                     >> engine_running_status_ >> gear_take_over_state_>> holo::serialization::align;

    }

private:
    holo::common::Timestamp timestamp_;

    float    vehicle_speed_;
    float    front_left_wheel_speed_;
    float    front_right_wheel_speed_;
    float    rear_left_wheel_speed_;
    float    rear_right_wheel_speed_;
    uint32_t front_left_wheel_pulse_;
    uint32_t front_right_wheel_pulse_;
    uint32_t rear_left_wheel_pulse_;
    uint32_t rear_right_wheel_pulse_;
    float    longitudinal_acceleration_;
    float    lateral_acceleration_;
    float    yaw_rate_;
    float    front_wheel_angle_;
    float    longitudinal_control_value_;
    uint8_t  gear_position_;
    uint8_t  driver_door_ajar_status_;
    uint8_t  passenger_door_ajar_status_;
    uint8_t  rear_left_door_ajar_status_;
    uint8_t  rear_right_door_ajar_status_;
    uint8_t  trunk_ajar_status_;
    uint8_t  bonnet_ajar_status_;
    uint8_t  brake_pedal_status_;
    uint8_t  accelerator_pedal_status_;
    uint8_t  epb_system_status_;
    uint8_t  passenger_seat_belt_status_;
    uint8_t  driver_seat_belt_status_;
    uint8_t  right_mirror_status_;
    uint8_t  left_mirror_status_;
    uint8_t  key_status_;
    uint8_t  steering_abort_;
    uint8_t  engine_running_status_;
    uint8_t  gear_take_over_state_;
};
}  // namespace sensors
}  // namespace parking
}  // namespace holo
#endif  // CAR_BODY_STATE_H
