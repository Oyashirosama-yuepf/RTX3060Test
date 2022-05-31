/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file vehicle_state.h
 * @brief vehicle state
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-12-02
 */

#ifndef HOLO_COMMON_VEHICLE_STATE_H_
#define HOLO_COMMON_VEHICLE_STATE_H_

#include <utility>

#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/serialization/serialization.h>

namespace holo
{
namespace common
{
class UserOperation
{
public:
    enum class Operation : uint32_t
    {
        BUTTON_INC        = 1U << 0U,
        BUTTON_DEC        = 1U << 1U,
        BUTTON_UP         = 1U << 2U,
        BUTTON_DOWN       = 1U << 3U,
        BUTTON_START      = 1U << 4U,
        BUTTON_CANCEL     = 1U << 5U,
        BUTTON_MODE       = 1U << 6U,
        ASL_CONFIRM       = 1U << 16U,
        PLC_LEFT_CONFIRM  = 1U << 17U,
        PLC_RIGHT_CONFIRM = 1U << 18U,

        BRAKE_PEDAL  = 1U << 19U,
        ACC_PEDAL    = 1U << 20U,
        ACC_OVERRIDE = 1U << 21U,

        VEHICLE_STANDSTILL = 1U << 30U,
        NO_BRAKE_FORCE     = 1U << 31U,
    };

    enum class Configuration : uint32_t
    {
        LDW            = 1U << 0U,
        LKA            = 1U << 1U,
        ASL            = 1U << 2U,
        ALC            = 1U << 3U,
        ACC            = 1U << 4U,
        ASSIST         = 1U << 5U,
        PILOT          = 1U << 6U,
        SS             = 1U << 7U,
        ALC_AUTOENABLE = 1U << 16,
        TJA_AUTOENABLE = 1U << 17,
        ASL_AUTOENABLE = 1U << 18,
    };

    enum class InvalidFlag : uint32_t
    {
        STERRING_WHEEL_TORQUE_INVALID = 1U << 0U,
        RES_BUTTON_INVALID            = 1U << 1U,
        BRAKE_PEDAL_INVALID           = 1U << 2U,
        ACC_PEDAL_INVALID             = 1U << 3U,
        TURN_SIGNAL_LEVEL_INVALID     = 1U << 4U,
    };

    UserOperation() noexcept
      : target_speed_{0U}
      , lka_ldw_sensitivity_{0U}
      , alc_sensitivity_{0U}
      , operations_{0U}
      , configurations_{0U}
      , invalid_flags_{0U}
      , steering_wheel_torque_{0.0f}
      , acc_pedal_{0.0f}
    {
    }

    holo::common::Timestamp GetTimestamp() const noexcept
    {
        return stamp_;
    }

    void SetTimestamp(holo::common::Timestamp stamp) noexcept
    {
        stamp_ = stamp;
    }

    /**
     * @brief Get user configured target speed. Unit: km/h
     *
     * @return Target speed
     */
    uint8_t GetTargetSpeed() const noexcept
    {
        return target_speed_;
    }

    /**
     * @brief Set user configured target speed. Unit: km/h
     *
     * @param value Target speed
     */
    void SetTargetSpeed(uint8_t value) noexcept
    {
        target_speed_ = value;
    }

    /**
     * @brief Get LKA/LDW sensitivity.
     *
     * @return LKA/LDW sensitivity
     */
    uint8_t GetLkaLdwSensitivity() const noexcept
    {
        return lka_ldw_sensitivity_;
    }

    /**
     * @brief Set LKA/LDW sensitivity.
     *
     * @param value LKA/LDW sensitivity
     */
    void SetLkaLdwSensitivity(uint8_t value) noexcept
    {
        lka_ldw_sensitivity_ = value;
    }

    /**
     * @brief Get ALC sensitivity.
     *
     * @return ALC sensitivity
     */
    uint8_t GetAlcSensitivity() const noexcept
    {
        return alc_sensitivity_;
    }

    /**
     * @brief Set ALC sensitivity.
     *
     * @param value ALC sensitivity
     */
    void SetAlcSensitivity(uint8_t value) noexcept
    {
        alc_sensitivity_ = value;
    }

    /**
     * @brief Check if any user operation defined in Operation are performed.
     *
     * @return true if any operation are performed, false otherwise.
     */
    holo::bool_t IsOperationPerformed() const noexcept
    {
        return static_cast<holo::bool_t>(operations_ != 0U);
    }

    template <typename... Args>
    holo::bool_t IsOperationPerformed(Args&&... args) const noexcept
    {
        return (operations_ & getFlags(std::forward<Args>(args)...)) == getFlags(std::forward<Args>(args)...);
    }

    template <typename... Args>
    void SetOperation(Args&&... args) noexcept
    {
        operations_ |= getFlags(std::forward<Args>(args)...);
    }

    template <typename... Args>
    void ResetOperation(Args&&... args) noexcept
    {
        operations_ &= ~getFlags(std::forward<Args>(args)...);
    }

    template <typename... Args>
    holo::bool_t IsConfigurationSet(Args&&... args) const noexcept
    {
        return (configurations_ & getFlags(std::forward<Args>(args)...)) == getFlags(std::forward<Args>(args)...);
    }

    template <typename... Args>
    void SetConfiguration(Args&&... args) noexcept
    {
        configurations_ |= getFlags(std::forward<Args>(args)...);
    }

    template <typename... Args>
    void ResetConfiguration(Args&&... args) noexcept
    {
        configurations_ &= ~getFlags(std::forward<Args>(args)...);
    }

    template <typename... Args>
    holo::bool_t IsInvalidFlagSet(Args&&... args) const noexcept
    {
        return (invalid_flags_ & getFlags(std::forward<Args>(args)...)) == getFlags(std::forward<Args>(args)...);
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

    /**
     * @brief Get steering wheel torque (Torque driver applied to steering wheel).
     *
     * @return Steering wheel torque
     */
    holo::float32_t GetSteeringWheelTorque() const noexcept
    {
        return steering_wheel_torque_;
    }

    /**
     * @brief Set steering wheel torque
     *
     * @param value steering wheel torque
     */
    void SetSteeringWheelTorque(holo::float32_t value) noexcept
    {
        steering_wheel_torque_ = value;
    }

    /**
     * @brief Get acc pedal percentage
     *
     * @return Acc pedal percentage
     */
    holo::float32_t GetAccPedal() const noexcept
    {
        return acc_pedal_;
    }

    /**
     * @brief Set acc pedal percentage
     *
     * @param value Acc pedal percentage
     */
    void SetAccPedal(holo::float32_t value) noexcept
    {
        acc_pedal_ = value;
    }

    uint32_t GetOperationsValue() const noexcept
    {
        return operations_;
    }

    void SetOperationsValue(uint32_t value) noexcept
    {
        operations_ = value;
    }

    uint32_t GetConfigurationsValue() const noexcept
    {
        return configurations_;
    }

    void SetConfigurationsValue(uint32_t value) noexcept
    {
        configurations_ = value;
    }

    uint32_t GetInvalidFlagValue() const noexcept
    {
        return invalid_flags_;
    }

    void SetInvalidFlagValue(uint32_t value) noexcept
    {
        invalid_flags_ = value;
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return stamp_.GetSerializedSize<ALIGN>() +
               holo::serialization::AlignedSize<ALIGN>(holo::serialization::AlignedSize<ALIGN>(3U * sizeof(uint8_t)) +
                                               5U * sizeof(uint32_t));
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << stamp_ << target_speed_ << lka_ldw_sensitivity_ << alc_sensitivity_ << operations_
                   << configurations_ << invalid_flags_ << steering_wheel_torque_ << acc_pedal_ << holo::serialization::align;
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        deserializer >> stamp_ >> target_speed_ >> lka_ldw_sensitivity_ >> alc_sensitivity_ >> operations_ >>
            configurations_ >> invalid_flags_ >> steering_wheel_torque_ >> acc_pedal_ >> holo::serialization::align;
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

    holo::common::Timestamp stamp_;

    uint8_t  target_speed_;
    uint8_t  lka_ldw_sensitivity_;
    uint8_t  alc_sensitivity_;
    uint32_t operations_;
    uint32_t configurations_;
    uint32_t invalid_flags_;

    holo::float32_t steering_wheel_torque_;
    holo::float32_t acc_pedal_;
};

/**
 * @brief Vehicle motion actuator state.
 */
struct MotionActuatorState
{
    holo::common::Timestamp timestamp;
    holo::float32_t         steering_wheel_angular_speed;
    holo::float32_t         eps_torque;
    holo::float32_t         esp_deceleration;
    holo::float32_t         request_motor_torque;
    holo::float32_t         motor_torque;

    holo::common::Timestamp GetTimestamp() const noexcept
    {
        return timestamp;
    }

    void SetTimestamp(holo::common::Timestamp stamp) noexcept
    {
        timestamp = stamp;
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return timestamp.GetSerializedSize<ALIGN>() + holo::serialization::AlignedSize<ALIGN>(5U * sizeof(holo::float32_t));
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << timestamp << steering_wheel_angular_speed << eps_torque << esp_deceleration
                   << request_motor_torque << motor_torque << holo::serialization::align;
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        deserializer >> timestamp >> steering_wheel_angular_speed >> eps_torque >> esp_deceleration >>
            request_motor_torque >> motor_torque >> holo::serialization::align;
    }
};

class ExternalState
{
public:
    enum class ActuatorState
    {
        AVAILABLE     = 0U,
        NOT_AVAILABLE = 1U,
        ERROR         = 2U,
    };

    enum class FunctionState
    {
        INACTIVE = 0U,
        STANDBY  = 1U,
        ACTIVE   = 2U,
        ERROR    = 3U,
    };

    enum class Actuator : uint32_t
    {
        EPS             = 0U,
        ESC             = 1U,
        BCM             = 2U,
        HU              = 3U,
        IB              = 4U,
        SCM             = 5U,
        SRS             = 6U,
        VCU             = 7U,
        MASTER_CYLINDER = 16U,
    };

    enum class Function : uint32_t
    {
        HDC       = 0U,
        AVH       = 1U,
        ESP       = 2U,
        TCS       = 3U,
        ABS       = 4U,
        CDD       = 5U,
        PAB       = 6U,
        DTC       = 7U,
        AWB       = 8U,
        CDP       = 9U,
        LIMP_HOME = 10U,
        AEB       = 12U,
        HBB       = 13U,
        EBD       = 14U,
    };

    holo::common::Timestamp GetTimestamp() const noexcept
    {
        return stamp_;
    }

    void SetTimestamp(holo::common::Timestamp stamp) noexcept
    {
        stamp_ = stamp;
    }

    ExternalState() : actuator_states_{0U}, function_states_{0U}
    {
    }

    ExternalState(uint32_t actuator_states, uint32_t function_states)
      : actuator_states_{actuator_states}, function_states_{function_states}
    {
    }

    ActuatorState GetActuatorState(Actuator ecu_id) const noexcept
    {
        return static_cast<ActuatorState>((actuator_states_ >> (static_cast<uint32_t>(ecu_id) * 2U)) & 0x03U);
    }

    void SetActuatorState(Actuator ecu_id, ActuatorState state) noexcept
    {
        actuator_states_ &= ~(0x03U << (static_cast<uint32_t>(ecu_id) * 2U));
        actuator_states_ |= static_cast<uint32_t>(state) << (static_cast<uint32_t>(ecu_id) * 2U);
    }

    template <typename... Args>
    void SetActuatorStateError(Args&&... args) noexcept
    {
        actuator_states_ &= ~generateActuatorMask(std::forward<Args>(args)...);
        actuator_states_ |= generateActuatorErrorMask(std::forward<Args>(args)...);
    }

    template <typename... Args>
    void SetActuatorStateAvailable(Args&&... args) noexcept
    {
        actuator_states_ &= ~generateActuatorMask(std::forward<Args>(args)...);
    }

    template <typename... Args>
    void SetActuatorStateNotAvailable(Args&&... args) noexcept
    {
        actuator_states_ &= ~generateActuatorMask(std::forward<Args>(args)...);
        actuator_states_ |= generateActuatorNotAvailableMask(std::forward<Args>(args)...);
    }

    template <typename... Args>
    bool_t IsActuatorNotAvailable(Args&&... args) const noexcept
    {
        return (actuator_states_ & generateActuatorMask(std::forward<Args>(args)...)) ==
               generateActuatorNotAvailableMask(std::forward<Args>(args)...);
    }

    template <typename... Args>
    bool_t IsActuatorAvailable(Args&&... args) const noexcept
    {
        return (actuator_states_ & generateActuatorMask(std::forward<Args>(args)...)) == 0U;
    }

    template <typename... Args>
    bool_t IsActuatorError(Args&&... args) const noexcept
    {
        return (actuator_states_ & generateActuatorMask(std::forward<Args>(args)...)) ==
               generateActuatorErrorMask(std::forward<Args>(args)...);
    }

    FunctionState GetFunctionState(Function function_id) const noexcept
    {
        return static_cast<FunctionState>((function_states_ >> (static_cast<uint32_t>(function_id) * 2U)) & 0x03U);
    }

    void SetFunctionState(Function function_id, FunctionState state) noexcept
    {
        function_states_ &= ~(0x03U << (static_cast<uint32_t>(function_id) * 2U));
        function_states_ |= static_cast<uint32_t>(state) << (static_cast<uint32_t>(function_id) * 2U);
    }

    template <typename... Args>
    void SetFunctionStateError(Args&&... args) noexcept
    {
        function_states_ |= generateFunctionErrorMask(std::forward<Args>(args)...);
    }

    template <typename... Args>
    void SetFunctionStateActive(Args&&... args) noexcept
    {
        function_states_ &= ~generateFunctionMask(std::forward<Args>(args)...);
        function_states_ |= generateFunctionActiveMask(std::forward<Args>(args)...);
    }

    template <typename... Args>
    void SetFunctionStateStandby(Args&&... args) noexcept
    {
        function_states_ &= ~generateFunctionMask(std::forward<Args>(args)...);
        function_states_ |= generateFunctionStandbyMask(std::forward<Args>(args)...);
    }

    template <typename... Args>
    void SetFunctionStateInactive(Args&&... args) noexcept
    {
        function_states_ &= ~generateFunctionMask(std::forward<Args>(args)...);
    }

    template <typename... Args>
    bool_t IsFunctionInactive(Args&&... args) const noexcept
    {
        return (function_states_ & generateFunctionMask(std::forward<Args>(args)...)) == 0U;
    }

    template <typename... Args>
    bool_t IsFunctionStandby(Args&&... args) const noexcept
    {
        return (function_states_ & generateFunctionMask(std::forward<Args>(args)...)) ==
               generateFunctionStandbyMask(std::forward<Args>(args)...);
    }

    template <typename... Args>
    bool_t IsFunctionActive(Args&&... args) const noexcept
    {
        return (function_states_ & generateFunctionMask(std::forward<Args>(args)...)) ==
               generateFunctionActiveMask(std::forward<Args>(args)...);
    }

    template <typename... Args>
    bool_t IsFunctionError(Args&&... args) const noexcept
    {
        return (function_states_ & generateFunctionMask(std::forward<Args>(args)...)) ==
               generateFunctionErrorMask(std::forward<Args>(args)...);
    }

    uint32_t GetActuatorStateValue() const noexcept
    {
        return actuator_states_;
    }

    uint32_t GetFunctionStateValue() const noexcept
    {
        return function_states_;
    }

    void SetActuatorStateValue(uint32_t value) noexcept
    {
        actuator_states_ = value;
    }

    void SetFunctionStateValue(uint32_t value) noexcept
    {
        function_states_ = value;
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return stamp_.GetSerializedSize<ALIGN>() + holo::serialization::AlignedSize<ALIGN>(2U * sizeof(uint32_t));
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << stamp_ << actuator_states_ << function_states_ << holo::serialization::align;
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        deserializer >> stamp_ >> actuator_states_ >> function_states_ >> holo::serialization::align;
    }

private:
    template <typename... Args>
    uint32_t generateActuatorMask(Actuator ecu_id, Args&&... args) const noexcept
    {
        return (0x03U << (static_cast<uint32_t>(ecu_id) * 2U)) | generateActuatorMask(std::forward<Args>(args)...);
    }

    template <typename... Args>
    uint32_t generateActuatorMask(Actuator ecu_id) const noexcept
    {
        return 0x03U << (static_cast<uint32_t>(ecu_id) * 2U);
    }

    template <typename... Args>
    uint32_t generateActuatorNotAvailableMask(Actuator ecu_id, Args&&... args) const noexcept
    {
        return (0x01U << (static_cast<uint32_t>(ecu_id) * 2U)) |
               generateActuatorNotAvailableMask(std::forward<Args>(args)...);
    }

    template <typename... Args>
    uint32_t generateActuatorNotAvailableMask(Actuator ecu_id) const noexcept
    {
        return 0x01U << (static_cast<uint32_t>(ecu_id) * 2U);
    }

    template <typename... Args>
    uint32_t generateActuatorErrorMask(Actuator ecu_id, Args&&... args) const noexcept
    {
        return (0x02U << (static_cast<uint32_t>(ecu_id) * 2U)) | generateActuatorErrorMask(std::forward<Args>(args)...);
    }

    template <typename... Args>
    uint32_t generateActuatorErrorMask(Actuator ecu_id) const noexcept
    {
        return 0x02U << (static_cast<uint32_t>(ecu_id) * 2U);
    }

    template <typename... Args>
    uint32_t generateFunctionMask(Function function_id, Args&&... args) const noexcept
    {
        return (0x03U << (static_cast<uint32_t>(function_id) * 2U)) | generateFunctionMask(std::forward<Args>(args)...);
    }

    template <typename... Args>
    uint32_t generateFunctionMask(Function function_id) const noexcept
    {
        return 0x03U << (static_cast<uint32_t>(function_id) * 2U);
    }

    template <typename... Args>
    uint32_t generateFunctionStandbyMask(Function function_id, Args&&... args) const noexcept
    {
        return (0x01U << (static_cast<uint32_t>(function_id) * 2U)) |
               generateFunctionStandbyMask(std::forward<Args>(args)...);
    }

    template <typename... Args>
    uint32_t generateFunctionStandbyMask(Function function_id) const noexcept
    {
        return 0x01U << (static_cast<uint32_t>(function_id) * 2U);
    }

    template <typename... Args>
    uint32_t generateFunctionActiveMask(Function function_id, Args&&... args) const noexcept
    {
        return (0x02U << (static_cast<uint32_t>(function_id) * 2U)) |
               generateFunctionActiveMask(std::forward<Args>(args)...);
    }

    template <typename... Args>
    uint32_t generateFunctionActiveMask(Function function_id) const noexcept
    {
        return 0x02U << (static_cast<uint32_t>(function_id) * 2U);
    }

    template <typename... Args>
    uint32_t generateFunctionErrorMask(Function function_id, Args&&... args) const noexcept
    {
        return (0x03U << (static_cast<uint32_t>(function_id) * 2U)) |
               generateFunctionErrorMask(std::forward<Args>(args)...);
    }

    template <typename... Args>
    uint32_t generateFunctionErrorMask(Function function_id) const noexcept
    {
        return 0x03U << (static_cast<uint32_t>(function_id) * 2U);
    }

    holo::common::Timestamp stamp_;

    uint32_t actuator_states_;
    uint32_t function_states_;
};

}  // namespace common
}  // namespace holo

#endif

