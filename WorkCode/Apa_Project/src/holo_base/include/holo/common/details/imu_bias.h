/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file imu_bias.h
 * @brief This header file define the bias of imu sensor
 * @author zhouhuishuang@holomatic.com
 * @date 2020-11-06
 */

#ifndef HOLO_COMMON_DETAILS_IMU_BIAS_H_
#define HOLO_COMMON_DETAILS_IMU_BIAS_H_

#include <holo/common/coordinate.h>
#include <holo/common/timestamp.h>
#include <holo/geometry/point3.h>
#include <holo/numerics/vector.h>

namespace holo
{
namespace common
{
namespace details
{
/**
 * @brief This class contains the bias for imu gyro and linear acceleration
 *
 * @tparam T
 */
template <typename T>
class ImuBiasT
{
public:
    using ScalarType  = T;
    using Vector3Type = holo::numerics::VectorT<T, 3>;
    using Point3Type  = holo::geometry::Point3T<ScalarType>;

    /**
     * @brief constructor
     */
    ImuBiasT()
      : timestamp_(0, 0)
      , coordinate_(Coordinate::UNKNOWN)  // COORD_UNKNOWN
      , angular_velocity_bias_()
      , linear_acceleration_bias_()
      , angular_velocity_bias_covariance_()
      , linear_acceleration_bias_covariance_()
    {
    }

    /**
     * @brief get Timestamp
     *
     * @return Timestamp
     */
    Timestamp GetTimestamp() const
    {
        return timestamp_;
    }

    /**
     * @brief set Timestamp
     *
     * @param timestamp
     */
    void SetTimestamp(Timestamp const timestamp)
    {
        timestamp_ = timestamp;
    }

    /**
     * @brief return coordinate
     *
     * @return coordinate
     */
    Coordinate GetCoordinate() const
    {
        return coordinate_;
    }

    /**
     * @brief set coordinate
     *
     * @param coord coordinate of imu
     */
    void SetCoordinate(Coordinate const coord)
    {
        coordinate_ = coord;
    }

    /**
     * @brief get angular velocity bias which contains Bias_gx, Bias_gy and Bias_gz
     * @deprecated Deprecated Vector3Type GetAngularVelocityBias() const function
     * @return angular velocity bias in the unit of rad/s
     */
    [[deprecated]] Vector3Type GetAngularVelocityBias() const { return angular_velocity_bias_.ToVector(); }

    /**
     * @brief get angular velocity bias which template OutputType
     *
     * @return template OutputType
     */
    template <typename OutputType>
    OutputType GetAngularVelocityBias() const noexcept
    {
        return OutputType{angular_velocity_bias_[0U], angular_velocity_bias_[1U], angular_velocity_bias_[2U]};
    }

    /**
     * @brief set angular velocity bias which contains Bias_gx, Bias_gy and Bias_gz
     * @deprecated Deprecated SetAngularVelocityBias(Vector3Type const& angular_velocity_bias) function
     * @param angular_velocity_bias angular velocity bias in the unit of rad/s
     */
    [[deprecated]] void SetAngularVelocityBias(Vector3Type const& angular_velocity_bias) {
        angular_velocity_bias_ = static_cast<Point3Type>(angular_velocity_bias);
    }

    /**
     * @brief set angular velocity bias which ScalarType x, ScalarType y and ScalarType z
     *
     * @param x,y,z  angular velocity bias in the unit of rad/s
     */
    void SetAngularVelocityBias(ScalarType x, ScalarType y, ScalarType z) noexcept
    {
        angular_velocity_bias_[0U] = x;
        angular_velocity_bias_[1U] = y;
        angular_velocity_bias_[2U] = z;
    }

    /**
     * @brief set angular velocity bias which contains Bias_gx, Bias_gy and Bias_gz
     * @param angular_velocity_bias angular velocity bias in the unit of rad/s
     */
    void SetAngularVelocityBias(Point3Type const& angular_velocity_bias)
    {
        angular_velocity_bias_ = angular_velocity_bias;
    }

    /**
     * @brief get linear acceleration bias which contains Bias_ax, Bias_ay and Bias_az
     * @deprecated Deprecated Vector3Type GetLinearAccelerationBias() const function
     * @return linear acceleration bias in the unit of m/s^2
     */
    [[deprecated]] Vector3Type GetLinearAccelerationBias() const { return linear_acceleration_bias_.ToVector(); }

    /**
     * @brief get linear acceleration bias which template OutputType
     *
     * @return template OutputType
     */
    template <typename OutputType>
    OutputType GetLinearAccelerationBias() const noexcept
    {
        return OutputType{linear_acceleration_bias_[0U], linear_acceleration_bias_[1U], linear_acceleration_bias_[2U]};
    }

    /**
     * @brief set linear acceleration bias which contains Bias_ax, Bias_ay and Bias_az
     * @deprecated Deprecated  void SetLinearAccelerationBias(Vector3Type const& linear_acceleration_bias) function
     * @param linear_acceleration_bias linear acceleration bias in the unit of m/s
     */
    [[deprecated]] void SetLinearAccelerationBias(Vector3Type const& linear_acceleration_bias) {
        linear_acceleration_bias_ = static_cast<Point3Type>(linear_acceleration_bias);
    }

    /**
     * @brief set linear acceleration bias which ScalarType x, ScalarType y and ScalarType z
     *
     * @param x,y,z linear acceleration bias in the unit of m/s
     */
    void SetLinearAccelerationBias(ScalarType x, ScalarType y, ScalarType z) noexcept
    {
        linear_acceleration_bias_[0U] = x;
        linear_acceleration_bias_[1U] = y;
        linear_acceleration_bias_[2U] = z;
    }

    /**
     * @brief set linear acceleration bias which contains Bias_ax, Bias_ay and Bias_az
     * @param linear_acceleration_bias linear acceleration bias in the unit of m/s
     */
    void SetLinearAccelerationBias(Point3Type const& linear_acceleration_bias)
    {
        linear_acceleration_bias_ = linear_acceleration_bias;
    }

    /**
     * @brief get angular velocity bias covariance which contains Cov_Bias_gx, Cov_Bias_gy and Cov_Bias_gz
     * @deprecated Deprecated Vector3Type GetAngularVelocityBiasCovariance() const function
     * @return angular velocity bias covariance in the unit of (rad/s)^2
     */
    [[deprecated]] Vector3Type GetAngularVelocityBiasCovariance() const {
        return angular_velocity_bias_covariance_.ToVector();
    }

    /**
     * @brief get angular velocity bias covariance which template OutputType
     *
     * @return template OutputType
     */
    template <typename OutputType>
    OutputType GetAngularVelocityBiasCovariance() const noexcept
    {
        return OutputType{angular_velocity_bias_covariance_[0U], angular_velocity_bias_covariance_[1U],
                          angular_velocity_bias_covariance_[2U]};
    }

    /**
     * @brief set angular velocity bias covariance which contains Cov_Bias_gx, Cov_Bias_gy and Cov_Bias_gz
     * @deprecated Deprecated SetAngularVelocityBiasCovariance(Vector3Type const& angular_velocity_bias_covariance)
     * function
     * @param angular_velocity_bias_covariance angular velocity bias covariance in the unit of (rad/s)^2
     */
    [[deprecated]] void SetAngularVelocityBiasCovariance(Vector3Type const& angular_velocity_bias_covariance) {
        angular_velocity_bias_covariance_ = static_cast<Point3Type>(angular_velocity_bias_covariance);
    }

    /**
     * @brief set angular velocity bias covariance which ScalarType x, ScalarType y and ScalarType z
     *
     * @param x,y,z angular velocity bias covariance in the unit of (rad/s)^2
     */
    void SetAngularVelocityBiasCovariance(ScalarType x, ScalarType y, ScalarType z) noexcept
    {
        angular_velocity_bias_covariance_[0U] = x;
        angular_velocity_bias_covariance_[1U] = y;
        angular_velocity_bias_covariance_[2U] = z;
    }

    /**
     * @brief set angular velocity bias covariance which contains Cov_Bias_gx, Cov_Bias_gy and Cov_Bias_gz
     * @param angular_velocity_bias_covariance angular velocity bias covariance in the unit of (rad/s)^2
     */
    void SetAngularVelocityBiasCovariance(Point3Type const& angular_velocity_bias_covariance)
    {
        angular_velocity_bias_covariance_ = angular_velocity_bias_covariance;
    }

    /**
     * @brief get linear acceleration bias covariance which contains Cov_Bias_ax, Cov_Bias_ay and Cov_Bias_az
     * @deprecated Deprecated Vector3Type GetLinearAccelerationBiasCovariance() const function
     * @return linear acceleration bias covariance in the unit of (m/s^2)^2
     */
    [[deprecated]] Vector3Type GetLinearAccelerationBiasCovariance() const {
        return linear_acceleration_bias_covariance_.ToVector();
    }

    /**
     * @brief get linear acceleration bias covariance which template OutputType
     *
     * @return template OutputType
     */
    template <typename OutputType>
    OutputType GetLinearAccelerationBiasCovariance() const noexcept
    {
        return OutputType{linear_acceleration_bias_covariance_[0U], linear_acceleration_bias_covariance_[1U],
                          linear_acceleration_bias_covariance_[2U]};
    }

    /**
     * @brief set linear acceleration bias covariance which contains Cov_Bias_ax, Cov_Bias_ay and Cov_Bias_az
     * @deprecated Deprecated SetLinearAccelerationBiasCovariance(Vector3Type const&
     * linear_acceleration_bias_covariance) function
     * @param linear_acceleration_bias_covariance in the unit of (m/s^2)^2
     */
    [[deprecated]] void SetLinearAccelerationBiasCovariance(Vector3Type const& linear_acceleration_bias_covariance) {
        linear_acceleration_bias_covariance_ = static_cast<Point3Type>(linear_acceleration_bias_covariance);
    }

    /**
     * @brief set linear acceleration bias covariance which ScalarType x, ScalarType y and ScalarType z
     *
     * @param x,y,z in the unit of (m/s^2)^2
     */
    void SetLinearAccelerationBiasCovariance(ScalarType x, ScalarType y, ScalarType z) noexcept
    {
        linear_acceleration_bias_covariance_[0U] = x;
        linear_acceleration_bias_covariance_[1U] = y;
        linear_acceleration_bias_covariance_[2U] = z;
    }

    /**
     * @brief set linear acceleration bias covariance which contains Cov_Bias_ax, Cov_Bias_ay and Cov_Bias_az
     * @param linear_acceleration_bias_covariance in the unit of (m/s^2)^2
     */
    void SetLinearAccelerationBiasCovariance(Point3Type const& linear_acceleration_bias_covariance)
    {
        linear_acceleration_bias_covariance_ = linear_acceleration_bias_covariance;
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
        return timestamp_.GetSerializedSize<ALIGN>() + holo::serialization::SerializedSize<ALIGN>(static_cast<uint32_t>(coordinate_)) +
               angular_velocity_bias_.template GetSerializedSize<ALIGN>() +
               linear_acceleration_bias_.template GetSerializedSize<ALIGN>() +
               angular_velocity_bias_covariance_.template GetSerializedSize<ALIGN>() +
               linear_acceleration_bias_covariance_.template GetSerializedSize<ALIGN>();
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
        serializer << timestamp_ << coordinate_ << angular_velocity_bias_ << linear_acceleration_bias_
                   << angular_velocity_bias_covariance_ << linear_acceleration_bias_covariance_;
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
        deserializer >> timestamp_ >> coordinate_ >> angular_velocity_bias_ >> linear_acceleration_bias_ >>
            angular_velocity_bias_covariance_ >> linear_acceleration_bias_covariance_;
    }

private:
    Timestamp  timestamp_;
    Coordinate coordinate_;
    Point3Type angular_velocity_bias_;
    Point3Type linear_acceleration_bias_;
    Point3Type angular_velocity_bias_covariance_;
    Point3Type linear_acceleration_bias_covariance_;
};
}  // namespace details
}  // namespace common
}  // namespace holo

#endif /* HOLO_COMMON_DETAILS_IMU_BIAS_H_ */
