/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file imu_body_extrinsic_factor_inl.h
 * @brief this file define imu body extrinsic factor which can be used to calibrate
 *        roll, pitch, yaw of body in imu frame
 * @author Binbin.Wang wangbinbin@holomatic.com
 * @date 2020-08-13
 */

#ifndef HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_IMU_BODY_EXTRINSIC_FACTOR_INL_H_
#define HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_IMU_BODY_EXTRINSIC_FACTOR_INL_H_

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
 * @brief imu body extrinsic factor
 * @details error = bkRw * (wPbk+1 - wPbk) - iPb + bkRw * wRbk+1 * iPb - pwm
 */
class ImuBodyExtrinsicFactor : public gtsam::NoiseModelFactor3<gtsam::Pose3, gtsam::Pose3, gtsam::Rot3>
{
public:
    /**
     * @brief define smart pointer
     */
    using Ptr      = boost::shared_ptr<ImuBodyExtrinsicFactor>;
    using ConstPtr = boost::shared_ptr<const ImuBodyExtrinsicFactor>;
    using Base     = gtsam::NoiseModelFactor3<gtsam::Pose3, gtsam::Pose3, gtsam::Rot3>;

    /**
     * @brief default constructor
     * @note for holo::OptionalT, do not use it directly
     */
    ImuBodyExtrinsicFactor() noexcept;

    /**
     * @brief Construct a new Imu Body Extrinsic Factor object
     *
     * @param pose_i_key gtsam key of pose i
     * @param pose_j_key gtsam key of pose j
     * @param iRb_key iRb key
     * @param itb body translation in imu frame
     * @param pwm_cov pwm covariance
     * @param D_iRb jacobian d(preintegrated) / d(pose_i)
     * @param iRb_hat iRb_hat
     * @param preintegrated_dist displacement measurement of wheel odometry frame
     */
    ImuBodyExtrinsicFactor(gtsam::Key const& pose_i_key, gtsam::Key const& pose_j_key, gtsam::Key const& iRb_key,
                           gtsam::Point3 const& itb, gtsam::Matrix3 const& pwm_cov, gtsam::Matrix3 const& D_iRb,
                           gtsam::Rot3 const& iRb_hat, gtsam::Vector3 const& preintegrated_dist);

    /**
     * @brief override function to evaluate factor error with jacobian
     *
     * @param pose_i pose i
     * @param pose_j pose j
     * @param R_ib body orientation in imu frame
     * @param H_pose_i jacobian d(error) / d(pose_i)
     * @param H_pose_j jacobian d(error) / d(pose_j)
     * @param H_iRb jacobian d(error) / d(iRb)
     * @return gtsam::Vector
     */
    virtual gtsam::Vector evaluateError(gtsam::Pose3 const& pose_i, gtsam::Pose3 const& pose_j, gtsam::Rot3 const& iRb,
                                        boost::optional<gtsam::Matrix&> H_pose_i,
                                        boost::optional<gtsam::Matrix&> H_pose_j,
                                        boost::optional<gtsam::Matrix&> H_iRb) const override;

private:
    /// @brief body translation in imu frame
    gtsam::Point3 itb_;

    /// @brief pwm covariance
    gtsam::Matrix3 pwm_cov_;

    /// @brief jacobian d(preintegrated) / d(pose_i)
    gtsam::Matrix3 D_iRb_;

    /// @brief body orientation in imu frame
    gtsam::Rot3 iRb_hat_;

    /// @brief displacement measurement of wheel odometry frame
    gtsam::Vector3 preintegrated_dist_;

};  // class ImuBodyExtrinsicFactor

/**
 * @}
 *
 */
}  // namespace internal
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_IMU_BODY_EXTRINSIC_FACTOR_INL_H_
