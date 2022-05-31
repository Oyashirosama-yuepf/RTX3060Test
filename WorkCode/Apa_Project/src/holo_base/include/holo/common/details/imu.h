/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file imu.h
 * @brief This header file define the measurement of inertial measurement unit
 * @author zhouhuishuang@holomatic.com
 * @date 2020-11-06
 */

#ifndef HOLO_COMMON_DETAILS_IMU_H_
#define HOLO_COMMON_DETAILS_IMU_H_

#include <assert.h>
#include <holo/common/coordinate.h>
#include <holo/common/timestamp.h>
#include <holo/geometry/point3.h>
#include <holo/numerics/vector.h>
#include <holo/serialization/serialization.h>

namespace holo
{

/**
 * @brief define imu status enum class
 *
 * @deprecated holo::ImuStatus replaced by holo::common::details::ImuT<T>::Status
 */

enum [[deprecated]]ImuStatus
{
    IMU_STATUS_ALLGOOD        = 0x0000,  // status is good
    IMU_STATUS_GYROXERROR     = 0x0001,  // x axis of gyroscope is bad
    IMU_STATUS_GYROYERROR     = 0x0002,  // y axis of gyroscope is bad
    IMU_STATUS_GYROZERROR     = 0x0004,  // z axis of gyroscope is bad
    IMU_STATUS_ACCLXERROR     = 0x0008,  // x axis of accelerometer is bad
    IMU_STATUS_ACCLYERROR     = 0x0010,  // y axis of accelerometer is bad
    IMU_STATUS_ACCLZERROR     = 0x0020,  // z axis of accelerometer is bad
    IMU_STATUS_UNDEFINEDERROR = 0xFFFF,  // undefined error
};

namespace common
{
namespace details
{
/**
 * @brief This class represents measurement of inertial measurement unit.
 *
 * @tparam T the precision type
 */
template <typename T>
class ImuT
{
public:
    using ScalarType  = T;
    using Vector3Type = holo::numerics::VectorT<T, 3>;
    using Point3Type  = holo::geometry::Point3T<ScalarType>;

    /**
     * @brief define status enum class
     */
    enum class Status
    {
        ALLGOOD        = 0x0000,  // status is good
        GYROXERROR     = 0x0001,  // x axis of gyroscope is bad
        GYROYERROR     = 0x0002,  // y axis of gyroscope is bad
        GYROZERROR     = 0x0004,  // z axis of gyroscope is bad
        ACCLXERROR     = 0x0008,  // x axis of accelerometer is bad
        ACCLYERROR     = 0x0010,  // y axis of accelerometer is bad
        ACCLZERROR     = 0x0020,  // z axis of accelerometer is bad
        UNDEFINEDERROR = 0xFFFF,  // undefined error
    };

    /**
     * @brief constructor for ImuT
     */
    ImuT()
      : timestamp_(0, 0)
      , coordinate_(Coordinate::UNKNOWN)
      , status_(Status::ALLGOOD)
      , angular_velocity_()
      , linear_acceleration_()
    {
    }

    /**
     * @brief get timestamp
     *
     * @return Timestamp
     */
    Timestamp GetTimestamp() const
    {
        return timestamp_;
    }

    /**
     * @brief set timestamp
     *
     * @param Timestamp
     */
    void SetTimestamp(Timestamp const timestamp)
    {
        timestamp_ = timestamp;
    }

    /**
     * @brief get coordinate
     *
     * @return Coordinate
     */
    Coordinate GetCoordinate() const
    {
        return coordinate_;
    }

    /**
     * @brief set coordinate id
     *
     * @param coord
     */
    void SetCoordinate(Coordinate const coord)
    {
        coordinate_ = coord;
    }

    /**
     * @brief get imu status
     *
     * @return Status
     */
    Status GetStatus() const
    {
        return status_;
    }

    /**
     * @brief set status
     *
     * @param status
     */
    void SetStatus(Status status)
    {
        status_ = status;
    }

    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    /**
     * @brief set status
     * @deprecated deprecated SetStatus(holo::ImuStatus status)
     * @param ImuStatus
     */
    [[deprecated]] void SetStatus(holo::ImuStatus status) 
    { 
        status_ = static_cast<Status>(status); 
    }
    #pragma GCC diagnostic pop

    /**
     * @brief get angular velocity which contains Gyro_x, Gyro_y and Gyro_z
     * @deprecated deprecated Vector3Type GetAngularVelocity() const function
     * @return angular velocity in the unit of rad/s
     */
    [[deprecated]] Vector3Type GetAngularVelocity() const
    {
        return angular_velocity_.ToVector();
    }

    /**
     * @brief get angular velocity which template OutputType
     *
     * @return template OutputType
     */
    template <typename OutputType>
    OutputType GetAngularVelocity() const noexcept
    {
        return OutputType{angular_velocity_[0U], angular_velocity_[1U], angular_velocity_[2U]};
    }

    /**
     * @brief set angular velocity which contains Gyro_x, Gyro_y and Gyro_z
     * @deprecated deprecated SetAngularVelocity(Vector3Type const& angular_velocity) function
     * @param angular_velocity in the unit of rad/s
     */
    [[deprecated]] void SetAngularVelocity(Vector3Type const& angular_velocity) 
    {
        angular_velocity_ = static_cast<Point3Type>(angular_velocity);
    }

    /**
     * @brief set angular velocity which ScalarType Gyro_x, Gyro_y and Gyro_z
     *
     * @param x,y,z  in the unit of rad/s
     */
    void SetAngularVelocity(ScalarType x, ScalarType y, ScalarType z) noexcept
    {
        angular_velocity_[0U] = x;
        angular_velocity_[1U] = y;
        angular_velocity_[2U] = z;
    }

    /**
     * @brief set angular velocity which contains Gyro_x, Gyro_y and Gyro_z
     * @param angular_velocity in the unit of rad/s
     */
    void SetAngularVelocity(Point3Type const& angular_velocity)
    {
        angular_velocity_ = angular_velocity;
    }

    /**
     * @brief get linear acceleration which contains Acc_x, Acc_y and Acc_z
     * @deprecated deprecated Vector3Type GetLinearAcceleration() const function
     * @return linear acceleration in the unit of m/s^2
     */
    [[deprecated]] Vector3Type GetLinearAcceleration() const 
    { 
        return linear_acceleration_.ToVector(); 
    }

    /**
     * @brief get linear acceleration which template OutputType
     *
     * @return template OutputType
     */
    template <typename OutputType>
    OutputType GetLinearAcceleration() const noexcept
    {
        return OutputType{linear_acceleration_[0U], linear_acceleration_[1U], linear_acceleration_[2U]};
    }

    /**
     * @brief set linear acceleration which contains Acc_x, Acc_y and Acc_z
     * @deprecated deprecated SetLinearAcceleration(Vector3Type const& linear_acceleration) function
     * @param linear_acceleration in the unit of m/s^2
     */
    [[deprecated]] void SetLinearAcceleration(Vector3Type const& linear_acceleration) 
    {
        linear_acceleration_ = static_cast<Point3Type>(linear_acceleration);
    }

    /**
     * @brief set linear acceleration which ScalarType Acc_x, Acc_y and Acc_z
     *
     * @param x,y,z  in the unit of m/s^2
     */
    void SetLinearAcceleration(ScalarType x, ScalarType y, ScalarType z) noexcept
    {
        linear_acceleration_[0U] = x;
        linear_acceleration_[1U] = y;
        linear_acceleration_[2U] = z;
    }

    /**
     * @brief set linear acceleration which contains Acc_x, Acc_y and Acc_z
     * @param linear_acceleration in the unit of m/s^2
     */
    void SetLinearAcceleration(Point3Type const& linear_acceleration)
    {
        linear_acceleration_ = linear_acceleration;
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
               holo::serialization::SerializedSize<ALIGN>(static_cast<uint32_t>(coordinate_), static_cast<uint32_t>(status_)) +
               angular_velocity_.template GetSerializedSize<ALIGN>() +
               linear_acceleration_.template GetSerializedSize<ALIGN>();
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
        serializer << timestamp_ << coordinate_ << static_cast<uint32_t>(status_) << angular_velocity_
                   << linear_acceleration_;
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
        uint32_t status = 0U;
        deserializer >> timestamp_ >> coordinate_ >> status >> angular_velocity_ >> linear_acceleration_;
        SetStatus(static_cast<Status>(status));
    }

private:
    Timestamp  timestamp_;
    Coordinate coordinate_;
    Status     status_;
    Point3Type angular_velocity_;
    Point3Type linear_acceleration_;
};
}  // namespace details
}  // namespace common
}  // namespace holo

#endif /* HOLO_COMMON_DETAILS_IMU_H_ */
