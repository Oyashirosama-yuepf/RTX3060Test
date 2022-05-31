/**
 * @file control_command.h
 * @brief This is used to describe the control's command
 * @author Huishuang Zhou(zhouhuishuang@holomatic.com)
 * @date 2021-10-18
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_COMMON_CONTROL_COMMAND_H_
#define HOLO_COMMON_CONTROL_COMMAND_H_

#include <holo/common/chassis_state.h>
#include <holo/common/timestamp.h>

namespace holo
{
namespace common
{
/**
 * @ingroup common
 *
 * @brief this class is used to describe the control command that sends to vehicle
 */
class ControlCommand
{
public:
    /**
     * @brief Define lateral control model
     */
    enum class LateralControlModel : uint8_t
    {
        DISABLE           = 0U,
        TORQUE            = 1U,  ///< steering wheel torque
        FRONT_WHEEL_ANGLE = 2U,  ///< front wheel angle
        STEERING_ANGLE    = 3U,  ///< steering wheel angle
    };

    /**
     * @brief Define longitudinal control model
     */
    enum class LongitudinalControlModel : uint8_t
    {
        DISABLE             = 0U,
        ACCELERATE          = 1U,
        ACCELERATION        = 1U,
        DECELERATE          = 2U,
        DECELERATION        = 2U,
        TORQUE              = 3U,
        TORQUE_DECELERATE   = 4U,
        TORQUE_DECELERATION = 4U,
        PARK                = 5U,
    };

    /**
     * @brief Define gear control model
     */
    enum class GearControlModel : uint8_t
    {
        DISABLE      = 0U,
        GEAR_CONTROL = 1U,
    };

    /**
     * @brief default constructor
     */
    ControlCommand() noexcept
      : timestamp_{}
      , lateral_control_model_{LateralControlModel::DISABLE}
      , longitudinal_control_model_{LongitudinalControlModel::DISABLE}
      , gear_control_model_{GearControlModel::DISABLE}
      , gear_control_command_{}
      , lateral_control_value_{0.0f}
      , longitudinal_control_value1_{0.0f}
      , longitudinal_control_value2_{0.0f}
    {
    }

    /**
     * @brief Get timestamp
     *
     * @return timestamp
     */
    Timestamp GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    /**
     * @brief Set timestamp
     *
     * @param timestamp
     */
    void SetTimestamp(Timestamp const timestamp)
    {
        timestamp_ = timestamp;
    }

    /**
     * @brief Get lateral control model
     *
     * @return lateral control model
     */
    LateralControlModel GetLateralControlModel() const noexcept
    {
        return lateral_control_model_;
    }

    /**
     * @brief Set lateral control model
     *
     * @param lateral_control_model
     */
    void SetLateralControlModel(LateralControlModel const lateral_control_model)
    {
        lateral_control_model_ = lateral_control_model;
    }

    /**
     * @brief Get longitudinal control model
     *
     * @return longitudinal control model
     */
    LongitudinalControlModel GetLongitudinalControlModel() const noexcept
    {
        return longitudinal_control_model_;
    }

    /**
     * @brief Set longitudinal control model
     *
     * @param longitudinal_control_model
     */
    void SetLongitudinalControlModel(LongitudinalControlModel const longitudinal_control_model)
    {
        longitudinal_control_model_ = longitudinal_control_model;
    }

    /**
     * @brief Get gear control model
     *
     * @return gear control model
     */
    GearControlModel GetGearControlModel() const noexcept
    {
        return gear_control_model_;
    }

    /**
     * @brief Set gear control model
     *
     * @param gear_control_model
     */
    void SetGearControlModel(GearControlModel const gear_control_model)
    {
        gear_control_model_ = gear_control_model;
    }

    /**
     * @brief Get lateral control value
     *
     * @details if the lateral control mode is TORQUE, return value is the lateral torque of vehicle [Nm],
     * if the lateral control mode is FRONT_WHEEL_ANGLE, return value is the front wheel angle of vehicle [rad],
     * if the lateral control mode is STEERING_ANGLE, return value is the steering angle of vehicle [rad]
     *
     * @return lateral control value
     */
    float32_t GetLateralControlValue() const noexcept
    {
        return lateral_control_value_;
    }

    /**
     * @brief Set lateral control value
     *
     * @details if the lateral control mode is TORQUE, param value is the lateral torque of vehicle [Nm],
     * if the lateral control mode is FRONT_WHEEL_ANGLE, param value is the front wheel angle of vehicle [rad],
     * if the lateral control mode is STEERING_ANGLE, param value is the steering angle of vehicle [rad]
     *
     * @param lateral_control_value
     */
    void SetLateralControlValue(float32_t const lateral_control_value)
    {
        lateral_control_value_ = lateral_control_value;
    }

    /**
     * @brief Get lateral torque
     *
     * @return lateral torque
     */
    float32_t GetLateralTorque() const noexcept
    {
        return lateral_control_value_;
    }

    /**
     * @brief Set lateral torque
     *
     * @param lateral_torque
     */
    void SetLateralTorque(float32_t const lateral_torque)
    {
        lateral_control_value_ = lateral_torque;
    }

    /**
     * @brief Get lateral front wheel angle
     *
     * @return front wheel angle
     */
    float32_t GetLateralFrontWheelAngle() const noexcept
    {
        return lateral_control_value_;
    }

    /**
     * @brief Set lateral front wheel angle
     *
     * @param front_wheel_angle
     */
    void SetLateralFrontWheelAngle(float32_t const front_wheel_angle)
    {
        lateral_control_value_ = front_wheel_angle;
    }

    /**
     * @brief Get lateral steering angle
     *
     * @return steering angle
     */
    float32_t GetLateralSteeringAngle() const noexcept
    {
        return lateral_control_value_;
    }

    /**
     * @brief Set lateral steering angle
     *
     * @param steering_angle
     */
    void SetLateralSteeringAngle(float32_t const steering_angle)
    {
        lateral_control_value_ = steering_angle;
    }

    /**
     * @brief Get longitudinal control value1
     *
     * @details if the longitudinal control mode is ACCELERATE, return value is the acceleration of the vehicle [m/s^2],
     * if the longitudinal control mode is DECELERATE, return value is the deceleration of the vehicle [m/s^2],
     * if the longitudinal control mode is TORQUE, return value is the longitudinal torque of the vehicle [Nm],
     * if the longitudinal control mode is TORQUE_DECELERATE, return value is the longitudinal torque deceleration of
     * vehicle, if the longitudinal control mode is PARK, return value is the speed limit [m/s]
     *
     * @return longitudinal control value1
     */
    float32_t GetLongitudinalControlValue1() const noexcept
    {
        return longitudinal_control_value1_;
    }

    /**
     * @brief Set longitudinal control value1
     *
     * @details if the longitudinal control mode is ACCELERATE, param value is the acceleration of the vehicle [m/s^2]
     （0.0<=param<=4.0）
     *
     * if the longitudinal control mode is DECELERATE, param value is the deceleration of the vehicle [m/s^2]
     （-4.0<=param<=0.0）
     *
     * if the longitudinal control mode is TORQUE, param value is the longitudinal torque of the vehicle [Nm]
     （0.0<=param<=1000.0）
     *
     * if the longitudinal control mode is TORQUE_DECELERATE, param value is the longitudinal torque deceleration of
     vehicle （-100.0<=param<=0.0）

     * if the longitudinal control mode is PARK, param value is the speed limit [m/s] （0.0<=param<-3.0）
     *
     * @param longitudinal_control_value1
     */
    void SetLongitudinalControlValue1(float32_t const longitudinal_control_value1)
    {
        longitudinal_control_value1_ = longitudinal_control_value1;
    }

    /**
     * @brief Get longitudinal control value2
     *
     * @details if the longitudinal control mode is ACCELERATE, return value is no meaning
     * if the longitudinal control mode is DECELERATE, return value is no meaning
     * if the longitudinal control mode is TORQUE, return value is no meaning
     * if the longitudinal control mode is TORQUE_DECELERATE, return value is no meaning
     * if the longitudinal control mode is PARK, return value is the stop distance [m]
     *
     * @return longitudinal control value2
     */
    float32_t GetLongitudinalControlValue2() const noexcept
    {
        return longitudinal_control_value2_;
    }

    /**
     * @brief Set longitudinal control value2
     *
     * @details if the longitudinal control mode is ACCELERATE, param value is no meaning
     * if the longitudinal control mode is DECELERATE, param value is no meaning
     * if the longitudinal control mode is TORQUE, param value is no meaning
     * if the longitudinal control mode is TORQUE_DECELERATE, param value is no meaning
     * if the longitudinal control mode is PARK, param value is the stop distance [m] （0.0<=param<=100.0）
     *
     * @param longitudinal_control_value2
     */
    void SetLongitudinalControlValue2(float32_t const longitudinal_control_value2)
    {
        longitudinal_control_value2_ = longitudinal_control_value2;
    }

    /**
     * @brief Get longitudinal acceleration
     *
     * @return longitudinal acceleration
     */
    float32_t GetLongitudinalAcceleration() const noexcept
    {
        return longitudinal_control_value1_;
    }

    /**
     * @brief Set longitudinal acceleration
     *
     * @param longitudinal_acceleration
     */
    void SetLongitudinalAcceleration(float32_t const acceleration)
    {
        longitudinal_control_value1_ = acceleration;
    }

    /**
     * @brief Get longitudinal deceleration
     *
     * @return longitudinal deceleration
     */
    float32_t GetLongitudinalDeceleration() const noexcept
    {
        return longitudinal_control_value1_;
    }

    /**
     * @brief Set longitudinal deceleration
     *
     * @param longitudinal_deceleration
     */
    void SetLongitudinalDeceleration(float32_t const deceleration)
    {
        longitudinal_control_value1_ = deceleration;
    }

    /**
     * @brief Get longitudinal torque
     *
     * @return longitudinal torque
     */
    float32_t GetLongitudinalTorque() const noexcept
    {
        return longitudinal_control_value1_;
    }

    /**
     * @brief Set longitudinal torque
     *
     * @param torque
     */
    void SetLongitudinalTorque(float32_t const torque)
    {
        longitudinal_control_value1_ = torque;
    }

    /**
     * @brief Get longitudinal torque deceleration
     *
     * @return longitudinal torque deceleration
     */
    float32_t GetLongitudinalTorqueDeceleration() const noexcept
    {
        return longitudinal_control_value1_;
    }

    /**
     * @brief Set longitudinal torque deceleration
     *
     * @param torque_deceleration
     */
    void SetLongitudinalTorqueDeceleration(float32_t const torque_deceleration)
    {
        longitudinal_control_value1_ = torque_deceleration;
    }

    /**
     * @brief Get longitudinal speed limit
     *
     * @return speed limit
     */
    float32_t GetLongitudinalSpeedLimit() const noexcept
    {
        return longitudinal_control_value1_;
    }

    /**
     * @brief Set longitudinal speed limit
     *
     * @param speed_limit
     */
    void SetLongitudinalSpeedLimit(float32_t const speed_limit)
    {
        longitudinal_control_value1_ = speed_limit;
    }

    /**
     * @brief Get longitudinal stop distance
     *
     * @return stop distance
     */
    float32_t GetLongitudinalStopDistance() const noexcept
    {
        return longitudinal_control_value2_;
    }

    /**
     * @brief Set longitudinal stop distance
     *
     * @param stop_distance
     */
    void SetLongitudinalStopDistance(float32_t const stop_distance)
    {
        longitudinal_control_value2_ = stop_distance;
    }

    /**
     * @brief Get gear position
     *
     * @return gear position
     */
    enum ChassisState::GearPosition GetGearPosition() const noexcept
    {
        return (enum ChassisState::GearPosition)gear_control_command_.gear_position_;
    }

    /**
     * @brief Set gear position
     *
     * @param gear_position
     */
    void SetGearPosition(enum ChassisState::GearPosition gear_position) noexcept
    {
        gear_control_command_.gear_position_ = (uint8_t)gear_position;
    }

    /**
     * @brief Get gear level
     *
     * @return gear level
     */
    uint8_t GetGearLevel() const noexcept
    {
        return gear_control_command_.gear_level_;
    }

    /**
     * @brief Set gear level
     *
     * @param gear_level
     */
    void SetGearLevel(uint8_t gear_level) noexcept
    {
        gear_control_command_.gear_level_ = gear_level > 15 ? 15 : gear_level;
    }

    /**
     * @brief Get handbrake
     *
     * @return handbrake
     */
    bool GetHandbrake() const noexcept
    {
        return gear_control_command_.handbrake_;
    }

    /**
     * @brief Set handbrake
     *
     * @param handbrake
     */
    void SetHandbrake(bool handbrake) noexcept
    {
        gear_control_command_.handbrake_ = handbrake;
    }

    /**
     * @brief Get gear position, gear level and handbrake.
     *
     * @return GearCommand
     */
    uint8_t GetGearCommand() const noexcept
    {
        return static_cast<uint8_t>(gear_control_command_.handbrake_) |
               static_cast<uint8_t>(static_cast<uint8_t>(gear_control_command_.gear_level_) << 1) |
               static_cast<uint8_t>(static_cast<uint8_t>(gear_control_command_.gear_position_) << 5);
    }

    /**
     * @brief Set gear position, gear level and handbrake.
     *
     * @param value GearCommand.
     */
    void SetGearCommand(uint8_t value) noexcept
    {
        gear_control_command_.handbrake_     = value >> 0;
        gear_control_command_.gear_level_    = value >> 1;
        gear_control_command_.gear_position_ = value >> 5;
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
               holo::serialization::SerializedSize<ALIGN>(lateral_control_model_, longitudinal_control_model_,
                                                          gear_control_model_, GetGearCommand(), lateral_control_value_,
                                                          longitudinal_control_value1_, longitudinal_control_value2_);
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::serialization::SerializationBufferOverflowException if buffer size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << timestamp_ << static_cast<uint8_t>(lateral_control_model_)
                   << static_cast<uint8_t>(longitudinal_control_model_) << static_cast<uint8_t>(gear_control_model_)
                   << GetGearCommand() << lateral_control_value_ << longitudinal_control_value1_
                   << longitudinal_control_value2_ << holo::serialization::align;
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        uint8_t gear_command;
        uint8_t lateral_control_model;
        uint8_t longitudinal_control_model;
        uint8_t gear_control_model;

        deserializer >> timestamp_ >> lateral_control_model >> longitudinal_control_model >> gear_control_model >>
            gear_command >> lateral_control_value_ >> longitudinal_control_value1_ >> longitudinal_control_value2_ >>
            holo::serialization::align;

        SetGearCommand(gear_command);
        lateral_control_model_      = static_cast<LateralControlModel>(lateral_control_model);
        longitudinal_control_model_ = static_cast<LongitudinalControlModel>(longitudinal_control_model);
        gear_control_model_         = static_cast<GearControlModel>(gear_control_model);
    }

private:
    holo::common::Timestamp timestamp_;  ///< timestamp

    LateralControlModel      lateral_control_model_;
    LongitudinalControlModel longitudinal_control_model_;
    GearControlModel         gear_control_model_;

    struct
    {
        uint8_t handbrake_ : 1;      ///< Hand brake status: 1=hold, 0=release
        uint8_t gear_level_ : 4;     ///< 0: Invalid, 1-15: gear level 1-15
        uint8_t gear_position_ : 3;  ///< See enum GearPosition for possible values.
    } gear_control_command_;

    float32_t lateral_control_value_;
    float32_t longitudinal_control_value1_;
    float32_t longitudinal_control_value2_;
};
}  // namespace common
}  // namespace holo

#endif
