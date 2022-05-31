/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file gnss_position_velocity_factor_inl.h
 * @brief This file define GNSS position and velocity factor used to constraint a pose and a velocity value.
 * @author Lei Gehang (leigehang@holomatic.com)
 * @author Yanwei Du (duyanwei@holomatic.com)
 * @date Aug 24, 2020
 */
#ifndef HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_GNSS_POSITION_VELOCITY_FACTOR_INL_H_
#define HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_GNSS_POSITION_VELOCITY_FACTOR_INL_H_

#include <gtsam/geometry/Pose3.h>
#include <gtsam/inference/Symbol.h>
#include <gtsam/navigation/ImuFactor.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>

namespace holo
{
namespace localization
{
namespace internal
{
/**
 * @addtogroup sam
 * @{
 *
 */

/**
 * @brief GNSS position and velocity factor
 *
 * @ref Tightly-coupled Fusion of Global Positional Measurements in Optimization-based Visual-Inertial Odometry,
 * Giovanni Cioffi, David Scaramuzza
 *
 */
class GnssPositionVelocityFactor : public gtsam::NoiseModelFactor2<gtsam::Pose3, gtsam::Vector3>
{
public:
    /**
     * @brief Define some common type
     */
    using Ptr             = boost::shared_ptr<GnssPositionVelocityFactor>;
    using ConstPtr        = boost::shared_ptr<const GnssPositionVelocityFactor>;
    using Base            = gtsam::NoiseModelFactor2<gtsam::Pose3, gtsam::Vector3>;
    using PimType         = gtsam::PreintegratedImuMeasurements;
    using OptionalPimType = boost::optional<PimType>;

    /**
     * @brief Construct a new Gnss Position Factor object
     *
     * @param[in] pose_key Associated pose variable key
     * @param[in] velocity_key Associated velocity variable key
     * @param[in] gnss_position gps position measurement
     * @param[in] gnss_velocity gps velocity measurement
     * @param[in] pim preintegrated measurements
     * @param[in] wRb rotation in navigation frame
     */
    GnssPositionVelocityFactor(gtsam::Key const& pose_key, gtsam::Key const& velocity_key,
                               gtsam::Point3 const& gnss_position, gtsam::Vector3 const& gnss_velocity,
                               gtsam::Vector6 const& gnss_sigmas, OptionalPimType const& pim = boost::none,
                               gtsam::Matrix3 const& wRb = gtsam::Matrix3::Identity());

    /**
     * @brief Destroy the Gnss Position Velocity Factor object
     *
     */
    virtual ~GnssPositionVelocityFactor() noexcept;

    /**
     * @brief Override function to evaluate factor error with jacobian
     *
     * @param[in] wTb Pose of the body frame with respect to the world frame
     * @param[in] velocity The velocity in the world frame (ENU)
     * @param[out] e_H_pose(6x6) Jacobian d(error) / d(wTb)
     * @param[out] e_H_velocity(6x3) Jacobian d(error) / d(velocity)
     * @return Error of this factor
     *
     */
    virtual gtsam::Vector evaluateError(gtsam::Pose3 const& wTb, gtsam::Vector3 const& velocity,
                                        boost::optional<gtsam::Matrix&> e_H_pose     = boost::none,
                                        boost::optional<gtsam::Matrix&> e_H_velocity = boost::none) const override;

private:
    /**
     * @brief construct noise model
     *
     * @param[in] sigmas gnss sigmas
     * @param[in] pim preintegrated imu measurements
     * @param[in] wRb rotation in navigation frame
     * @return gtsam::SharedNoiseModel
     */
    gtsam::SharedNoiseModel constructNoiseModel(gtsam::Vector6 const& sigmas, OptionalPimType const& pim,
                                                gtsam::Matrix3 const& wRb) const;

    gtsam::Point3 const  gnss_position_;  ///< The GNSS position
    gtsam::Vector3 const gnss_velocity_;  ///< The GNSS velocity
    gtsam::Vector6 const gnss_sigmas_;    ///< The GNSS sigmas

    OptionalPimType      pim_;
    gtsam::Matrix3 const wRb_;
};

/**
 * @}
 *
 */
}  // namespace internal
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_GNSS_POSITION_VELOCITY_FACTOR_INL_H_
