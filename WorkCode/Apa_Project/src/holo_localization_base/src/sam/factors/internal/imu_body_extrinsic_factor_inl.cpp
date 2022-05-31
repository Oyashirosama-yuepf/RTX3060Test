/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file imu_body_extrinsic_factor_inl.h
 * @brief source file of imu body extrinsic factor which can be used to calibrate
 *        roll, pitch, yaw of body in imu frame
 * @author Binbin.Wang wangbinbin@holomatic.com
 * @date 2020-08-13
 */

#include <holo/localization/sam/factors/internal/imu_body_extrinsic_factor_inl.h>

namespace holo
{
namespace localization
{
namespace internal
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ImuBodyExtrinsicFactor::ImuBodyExtrinsicFactor() noexcept
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ImuBodyExtrinsicFactor::ImuBodyExtrinsicFactor(gtsam::Key const& pose_i_key, gtsam::Key const& pose_j_key,
                                               gtsam::Key const& iRb_key, gtsam::Point3 const& itb,
                                               gtsam::Matrix3 const& pwm_cov, gtsam::Matrix3 const& D_iRb,
                                               gtsam::Rot3 const& iRb_hat, gtsam::Vector3 const& preintegrated_dist)
  : Base(gtsam::noiseModel::Gaussian::Covariance(pwm_cov), pose_i_key, pose_j_key, iRb_key)
  , itb_(itb)
  , pwm_cov_(pwm_cov)
  , D_iRb_(D_iRb)
  , iRb_hat_(iRb_hat)
  , preintegrated_dist_(preintegrated_dist)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Vector ImuBodyExtrinsicFactor::evaluateError(gtsam::Pose3 const& pose_i, gtsam::Pose3 const& pose_j,
                                                    gtsam::Rot3 const& iRb, boost::optional<gtsam::Matrix&> H_pose_i,
                                                    boost::optional<gtsam::Matrix&> H_pose_j,
                                                    boost::optional<gtsam::Matrix&> H_iRb) const
{
    // @details error = R_ik_w * (P_w_ik+1 - P_w_ik) - P_i_b + R_ik_w * R_w_ik+1 * P_i_b - pwm
    //          error = p1 - P_i_b + p2 - pwm
    //          p1 = R_ik_w * (P_w_ik+1 - P_w_ik)
    //          p2 = R_ik_w * R_w_ik+1 * P_i_b

    gtsam::Matrix36 D_pwj_posej, D_pwi_posei;

    gtsam::Point3 p_w_j = pose_j.translation(H_pose_j ? &D_pwj_posej : 0);
    gtsam::Point3 p_w_i = pose_i.translation(H_pose_i ? &D_pwi_posei : 0);

    gtsam::Point3 delta_p = p_w_j - p_w_i;

    gtsam::Matrix3 D_deltap_pwi = -gtsam::Matrix3::Identity();

    gtsam::Matrix3 D_p1_Ri, D_p1_delta_p;
    gtsam::Point3  p1 =
        pose_i.rotation().unrotate(delta_p, H_pose_i ? &D_p1_Ri : 0, H_pose_i || H_pose_j ? &D_p1_delta_p : 0);

    gtsam::Matrix3 D_Pwoj_Rj;
    gtsam::Point3  p_w_oj = pose_j.rotation().rotate(itb_, H_pose_j ? &D_Pwoj_Rj : 0, boost::none);

    gtsam::Matrix3 D_p2_Ri, D_p2_Pwoj;
    gtsam::Point3  p2 = pose_i.rotation().unrotate(p_w_oj, H_pose_i ? &D_p2_Ri : 0, H_pose_j ? &D_p2_Pwoj : 0);

    if (H_pose_i)
    {
        auto const jr = D_p1_Ri + D_p2_Ri;
        auto const jt = D_p1_delta_p * D_deltap_pwi * D_pwi_posei.rightCols(3);
        *H_pose_i     = (gtsam::Matrix36() << jr, jt).finished();
    }

    if (H_pose_j)
    {
        auto const jr = D_p2_Pwoj * D_Pwoj_Rj;
        auto const jt = D_p1_delta_p * D_pwj_posej.rightCols(3);
        *H_pose_j     = (gtsam::Matrix36() << jr, jt).finished();
    }

    if (H_iRb)
    {
        auto const jr = -D_iRb_;
        *H_iRb        = jr;
    }

    // corrected pwm
    gtsam::Vector3 corrected_pwm =
        preintegrated_dist_ + D_iRb_ * gtsam::Rot3::CayleyChart::Local(iRb_hat_.between(iRb));

    gtsam::Vector3 error = p1 - itb_ + p2 - corrected_pwm;

    return error;
}
}  // namespace internal
}  // namespace localization
}  // namespace holo
