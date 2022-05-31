/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file wheel_preintegration.h
 * @brief define wheel preintegration
 * @author Binbin.Wang wangbinbin@holomatic.com
 * @date 2020-08-04
 */

#ifndef HOLO_LOCALIZATION_WHEEL_PREINTEGRATION_H_
#define HOLO_LOCALIZATION_WHEEL_PREINTEGRATION_H_

#include <holo/localization/common/types.h>

namespace holo
{
namespace localization
{
/**
 * @brief Wheel Preintegration Measurements class
 *
 */
class WheelPreintegrationMeasurement
{
public:
    using Ptr      = std::shared_ptr<WheelPreintegrationMeasurement>;
    using ConstPtr = std::shared_ptr<const WheelPreintegrationMeasurement>;

    /**
     * @brief wheel preintegration params
     *
     */
    struct WheelPreintegrationParams
    {
        ///< continuous-time "Covariance" of velocity
        Matrix3Type velocity_covariance;

        ///< continuous-time "Covariance" describing gyro integration uncertainty
        Matrix3Type integration_covariance;

        /**
         * @brief construct a new wheel preintegration params
         *
         * @param _velocity_covariance continuous-time "Covariance" of velocity
         * @param _integration_covariance continuous-time "Covariance" describing gyro integration uncertainty
         */
        WheelPreintegrationParams(
            const Matrix3Type& _velocity_covariance    = (Vector3Type(1e-4, 1e-4, 1e-4)).AsDiagonal(),
            const Matrix3Type& _integration_covariance = (Vector3Type(1e-4, 1e-4, 1e-4)).AsDiagonal())
          : velocity_covariance(_velocity_covariance), integration_covariance(_integration_covariance)
        {
        }

    };  // WheelPreintegrationParams

    /**
     * @brief construct a new wheel preintegration measurements
     *
     * @param _params parameters
     * @param _iEb_Hat body pose in imu frame
     * @param _preintegrated the displacement between wheel odometer in imu frame
     * @param _preintegrated_H_Rib derivative of preintegrated displacement to R_ib
     * @param _preintegratedmeascov preintegrated measurement covariance
     * @param _delta_Tij time interval from i to j
     * @param _start_time timestamp of the first wheel measurement
     * @param _end_time timestamp of the last wheel measurement
     */
    WheelPreintegrationMeasurement(const WheelPreintegrationParams& _params               = WheelPreintegrationParams(),
                                   const Pose3Type&                 _iEb_Hat              = Pose3Type::Identity(),
                                   const Vector3Type&               _preintegrated        = Vector3Type(0.0,0.0,0.0),
                                   const Matrix3Type&               _preintegrated_H_Rib  = Matrix3Type(),
                                   const Matrix3Type&               _preintegratedmeascov = Matrix3Type(),
                                   const Scalar _delta_Tij = 0.0, const Timestamp& _start_time = Timestamp(0u, 0u),
                                   const Timestamp& _end_time = Timestamp(0u, 0u))
      : params_(_params)
      , iEb_Hat_(_iEb_Hat)
      , preintegrated_(_preintegrated)
      , preintegrated_H_Rib_(_preintegrated_H_Rib)
      , preintegratedmeascov_(_preintegratedmeascov)
      , delta_Tij_(_delta_Tij)
      , start_time_(_start_time)
      , end_time_(_end_time)
    {
    }

    /**
     * @brief destroy the wheel preintegration measurements object
     *
     */
    ~WheelPreintegrationMeasurement() noexcept
    {
    }

    /**
     * @brief integrate wheel speed measurement
     *         |  |  |  |  |  |  |
     *         i     l l+1       j
     *
     * @param velocity average velocity of l and l + 1 frames
     * @param delta_Ril frame l orientation in frame i
     * @param dt delta t of frame l to frame l+1 [s]
     */
    void IntegrateMeasurement(const Vector3Type& velocity, const Rot3Type& delta_Ril, const Scalar dt)
    {
        delta_Tij_ += dt;

        // update preintegrate
        preintegrated_ += delta_Ril.ToMatrix() * iEb_Hat_.GetRotation().ToMatrix() * velocity * dt;

        const Vector3Type vel = iEb_Hat_.GetRotation().ToMatrix() * velocity;
        const Matrix3Type A   = -((delta_Ril.ToMatrix()) * vel.ToSkewSymmetric() * dt);
        const Matrix3Type B   = -(delta_Ril.ToMatrix() * iEb_Hat_.GetRotation().ToMatrix() * dt);

        // update jacobian preintegrated_H_Rib
        preintegrated_H_Rib_ +=
            -(delta_Ril.ToMatrix() * iEb_Hat_.GetRotation().ToMatrix() * velocity.ToSkewSymmetric() * dt);

        const Matrix3Type& v_cov   = params_.velocity_covariance;
        const Matrix3Type& int_cov = params_.integration_covariance;

        // update covariance
        // (1/dt) allows to pass from continuous time noise to discrete time noise
        preintegratedmeascov_ += A * (int_cov / dt) * A.Transpose();
        //@todo get imu gyroscope preintegrate covariance from pim
        preintegratedmeascov_ += B * (v_cov / dt) * B.Transpose();
    }

    /**
     * @brief get the iEb Hat object
     *
     * @return const Pose3Type&
     */
    const Pose3Type& GetEibHat() const
    {
        return iEb_Hat_;
    }

    /**
     * @brief get the wheel speed preintegrated measurements
     *
     * @return const Vector3Type&
     */
    const Vector3Type& GetPreintegrated() const
    {
        return preintegrated_;
    }

    /**
     * @brief get the params object
     *
     * @return const WheelPreintegrationParams&
     */
    const WheelPreintegrationParams& GetParams() const
    {
        return params_;
    }

    /**
     * @brief get the derivative of preintegrated to Rib
     *
     * @return derivative
     */
    const Matrix3Type& GetPreintegratedHRib() const
    {
        return preintegrated_H_Rib_;
    }

    /**
     * @brief get the preintegrated measurement covariance
     *
     * @return const Matrix3Type&
     */
    const Matrix3Type& GetPreintegratedMeasurementCovariance() const
    {
        return preintegratedmeascov_;
    }

    /**
     * @brief get delta t of frame i to frame j
     *
     * @return Scalar
     */
    const Scalar& GetDeltaTij() const
    {
        return delta_Tij_;
    }

    /**
     * @brief set the timestamp of the first wheel measurement
     *
     * @param[in] start_time timestamp of first wheel measurement
     */
    void SetStartTime(const Timestamp& start_time)
    {
        start_time_ = start_time;
    }

    /**
     * @brief get the timestamp of the first wheel measurement
     *
     * @return const Timestamp&
     */
    const Timestamp& GetStartTime() const
    {
        return start_time_;
    }

    /**
     * @brief set the timestamp of the last wheel measurement
     *
     * @param[in] end_time timestamp of last wheel measurement
     */
    void SetEndTime(const Timestamp& end_time)
    {
        end_time_ = end_time;
    }

    /**
     * @brief get the timestamp of the last wheel measurement
     *
     * @return const Timestamp&
     */
    const Timestamp& GetEndTime() const
    {
        return end_time_;
    }

private:
    /// @brief parameters
    WheelPreintegrationParams params_;

    /// @brief body pose in imu frame
    Pose3Type iEb_Hat_;

    /// @brief the displacement between wheel odometer in imu frame
    Vector3Type preintegrated_;

    /// @brief derivative of preintegrated displacement to R_ib
    Matrix3Type preintegrated_H_Rib_;

    /// @brief preintegrated measurement covariance
    Matrix3Type preintegratedmeascov_;

    /// @brief time interval from i to j
    Scalar delta_Tij_;

    ///< start and end time of wheel preintegration measurement
    Timestamp start_time_;
    Timestamp end_time_;
};

}  // namespace localization

}  // namespace holo

#endif  // HOLO_LOCALIZATION_WHEEL_PREINTEGRATION
