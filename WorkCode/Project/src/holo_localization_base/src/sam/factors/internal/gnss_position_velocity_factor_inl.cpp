/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file gnss_position_velocity_factor_inl.cpp
 * @brief source file of GNSS position and velocity factor used to constraint a pose and a velocity value.
 * @author Lei Gehang (leigehang@holomatic.com)
 * @author Yanwei Du (duyanwei@holomatic.com)
 * @date Aug 24, 2020
 */

#include <holo/localization/sam/factors/internal/gnss_position_velocity_factor_inl.h>

namespace holo
{
namespace localization
{
namespace internal
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GnssPositionVelocityFactor::GnssPositionVelocityFactor(gtsam::Key const& pose_key, gtsam::Key const& velocity_key,
                                                       gtsam::Point3 const&  gnss_position,
                                                       gtsam::Vector3 const& gnss_velocity,
                                                       gtsam::Vector6 const& gnss_sigmas, OptionalPimType const& pim,
                                                       gtsam::Matrix3 const& wRb)
  : Base(constructNoiseModel(gnss_sigmas, pim, wRb), pose_key, velocity_key)
  , gnss_position_(gnss_position)
  , gnss_velocity_(gnss_velocity)
  , gnss_sigmas_(gnss_sigmas)
  , pim_(pim)
  , wRb_(wRb)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GnssPositionVelocityFactor::~GnssPositionVelocityFactor()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Vector GnssPositionVelocityFactor::evaluateError(gtsam::Pose3 const& wTb, gtsam::Vector3 const& velocity,
                                                        boost::optional<gtsam::Matrix&> e_H_pose,
                                                        boost::optional<gtsam::Matrix&> e_H_velocity) const
{
    // to make life easier, check gpm first (duyanwei@holomatic.com)

    if (!pim_)
    {
        /**
         * @brief a simple case, the error is measured in world frame
         *
         * @details
         *
         * error = [predicted_position - gnss_position;
         *          predicted_velocity - gnss_velocity];
         * H = [e_H_pose, e_H_velocity];
         */

        gtsam::Matrix36      position_H_pose;
        gtsam::Point3 const& position = wTb.translation(position_H_pose);

        if (e_H_pose)
        {
            gtsam::Matrix63 e_H_position;
            e_H_position << gtsam::Matrix3::Identity(), gtsam::Matrix3::Zero();
            *e_H_pose = e_H_position * position_H_pose;
        }

        if (e_H_velocity)
        {
            *e_H_velocity = (gtsam::Matrix63() << gtsam::Matrix3::Zero(), gtsam::Matrix3::Identity()).finished();
        }

        gtsam::Vector3 const position_error = position - gnss_position_;
        gtsam::Vector3 const velocity_error = velocity - gnss_velocity_;
        gtsam::Vector6       error;
        error << position_error, velocity_error;

        return error;
    }

    // else a complex case, the error is measured in body frame

    /**
     * @brief the error and jacobian matrix
     *
     * @details
     *
     * state = [wTb, velocity]
     *       = [w_R_bk, w_t_bk, w_v_bk]; // 9X1
     *
     * error = [ePosition;
     *          eVelocity]; // 6x1
     *
     * H = [ePosition_H_pose, ePosition_H_velocity;
     *      eVelocity_H_pose, eVelocity_H_velocity]; // 6x9
     *
     * Specially,
     *
     * ePosition = bk_R_w *(gnss_position - w_t_bk - w_v_bk * dt + 0.5 * w_g * dt^2) - bk_dp_bj; // 3x1
     * eVelocity = bk_R_w *(gnss_velocity -          w_v_bk +            w_g * dt  ) - bk_dv_bj; // 3x1
     *
     * // pose jacobian
     * ePosition_H_pose = (ePosition_H_(rotation^t) * (rotation^t)_H_rotation * rotation_H_pose) + // rotation part
     *                    (ePosition_H_position * position_H_pose)                              // translation part
     * eVelocity_H_pose = eVelocity_H_(rotation^t) * (rotation^t)_H_rotation * rotation_H_pose
     *
     * // velocity jacobian
     * ePosition_H_velocity = -bk_R_w * dt
     * eVelocity_H_velocity = -bk_R_w
     *
     * !!! Concerns !!! (duyanwei@holomatic.com).
     * In the following implementation, we ignore the rotation part until further improvement. The reason is that
     * the rotation influences both the error and the noise matrix, so either we change them together or keep them
     * fixed. Currently(Feb-07-2021), I cannot find a proper API to change the noise during optimization.
     */

    gtsam::Matrix36      position_H_pose;
    gtsam::Point3 const& position = wTb.translation(position_H_pose);
    gtsam::Matrix3 const bRw      = wRb_.transpose();
    const double         dt       = pim_->deltaTij();
    const double         dt2      = dt * dt;
    const gtsam::Vector3 g        = pim_->params()->n_gravity;

    if (e_H_pose)
    {
        *e_H_pose = gtsam::Matrix6::Zero();

        e_H_pose->block(0, 0, 3, 6) = -bRw * position_H_pose;
    }

    if (e_H_velocity)
    {
        *e_H_velocity                   = gtsam::Matrix63::Zero();
        e_H_velocity->block(0, 0, 3, 3) = -bRw * dt;
        e_H_velocity->block(3, 0, 3, 3) = -bRw;
    }

    gtsam::Vector3 const position_error =
        bRw * (gnss_position_ - position - velocity * dt - 0.5 * g * dt2) - pim_->deltaPij();
    gtsam::Vector3 const velocity_error = bRw * (gnss_velocity_ - velocity - g * dt) - pim_->deltaVij();

    gtsam::Vector6 error;
    error << position_error, velocity_error;

    return error;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::SharedNoiseModel GnssPositionVelocityFactor::constructNoiseModel(gtsam::Vector6 const&  sigmas,
                                                                        OptionalPimType const& pim,
                                                                        gtsam::Matrix3 const&  wRb) const
{
    if (!pim)
    {
        return gtsam::noiseModel::Diagonal::Sigmas(sigmas);
    }

    gtsam::Matrix6 gnss_cov = gtsam::Matrix6::Zero();
    {
        gtsam::Matrix3 const position_cov = gtsam::Vector3(sigmas.head(3).array().square()).asDiagonal();
        gtsam::Matrix3 const velocity_cov = gtsam::Vector3(sigmas.tail(3).array().square()).asDiagonal();

        gtsam::Matrix3 const bRw = wRb.transpose();

        gnss_cov.topLeftCorner(3, 3)     = bRw * position_cov * wRb;
        gnss_cov.bottomRightCorner(3, 3) = bRw * velocity_cov * wRb;
    }
    gtsam::Matrix6 const pim_cov = pim->preintMeasCov().block<6, 6>(3, 3);

    return gtsam::noiseModel::Gaussian::Covariance(pim_cov + gnss_cov);
}

}  // namespace internal
}  // namespace localization
}  // namespace holo
