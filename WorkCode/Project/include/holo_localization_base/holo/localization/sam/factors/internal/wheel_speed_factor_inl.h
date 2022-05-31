/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file wheel_speed_factor_inl.h
 * @brief this file deines wheel speed factor class
 * @author Binbin.Wang wangbinbin@holomatic.com
 * @date 2020-08-04
 */

#ifndef HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_WHEEL_SPEED_FACTOR_INL_H_
#define HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_WHEEL_SPEED_FACTOR_INL_H_

#include <gtsam/base/Vector.h>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/inference/Symbol.h>
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief wheel speed factor
 * @details error = bkRw * (wPbk+1 - wPbk) - iPb + bkRw * wRbk+1 * iPb - pwm
 */
class WheelSpeedFactor : public gtsam::NoiseModelFactor2<gtsam::Pose3, gtsam::Pose3>
{
public:
    /**
     * @brief define smart pointer
     */
    using Ptr      = boost::shared_ptr<WheelSpeedFactor>;
    using ConstPtr = boost::shared_ptr<const WheelSpeedFactor>;
    using Base     = gtsam::NoiseModelFactor2<gtsam::Pose3, gtsam::Pose3>;

    /**
     * @brief default constructor
     * @note for holo::OptionalT, do not use it directly
     */
    WheelSpeedFactor() noexcept;

    /**
     * @brief Construct a new Wheel Speed Factor object
     *
     * @param pose_i_key gtsam key of pose i
     * @param pose_j_key gtsam key of pose j
     * @param E_ib extrinsic of body pose in imu frame
     * @param pwm_cov pwm covariance
     * @param preintegrated_dist displacement measurement of wheel odometry
     */
    WheelSpeedFactor(gtsam::Key const& pose_i_key, gtsam::Key const& pose_j_key, gtsam::Pose3 const& E_ib,
                     gtsam::Matrix3 const& pwm_cov, gtsam::Vector3 const& preintegrated_dist);

    /**
     * @brief Get the Eib object
     *
     * @return extrinsic body frame in imu frame
     */
    const gtsam::Pose3& GetEib() const noexcept;

    /**
     * @brief override function to evaluate factor error with jacobian
     *
     * @param pose_i pose i
     * @param pose_j pose j
     * @param H_pose_i jacobian d(error) / d(pose_i)
     * @param H_pose_j jacobian d(error) / d(pose_j)
     * @return error Vector
     */
    virtual gtsam::Vector evaluateError(gtsam::Pose3 const& pose_i, gtsam::Pose3 const& pose_j,
                                        boost::optional<gtsam::Matrix&> H_pose_i,
                                        boost::optional<gtsam::Matrix&> H_pose_j) const override;

private:
    /// @brief measurement velocity in body frame
    gtsam::Pose3 E_ib_;

    /// @brief wheel preintegrated measurements covariance
    gtsam::Matrix3 pwm_cov_;

    /// @brief displacement measurement of wheel odometry
    gtsam::Vector3 preintegrated_dist_;

};  // class WheelSpeedFactor

/**
 * @}
 *
 */
}  // namespace internal
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_WHEEL_SPEED_FACTOR_INL_H_
