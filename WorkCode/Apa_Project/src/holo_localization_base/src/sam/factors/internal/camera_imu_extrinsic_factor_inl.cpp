/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file camera_imu_extrinsic_factor_inl.cpp
 * @brief source file of camera and imu extrinsic factor which can be used to calibrate
 *        roll, pitch, yaw and translation of camera in imu frame individually
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "2020-04-20"
 */

#include <holo/localization/sam/factors/internal/camera_imu_extrinsic_factor_inl.h>

namespace holo
{
namespace localization
{
namespace internal
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CameraImuExtrinsicFactor::CameraImuExtrinsicFactor() noexcept
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CameraImuExtrinsicFactor::CameraImuExtrinsicFactor(gtsam::SharedNoiseModel const& noise_model,
                                                   gtsam::Key const& wTi_key, gtsam::Key const& ptw_key,
                                                   gtsam::Key const& rpy_key, gtsam::Key const& itc_key,
                                                   gtsam::Cal3_S2::shared_ptr const& K,
                                                   gtsam::Point2 const& measurement, bool const fix_wTi,
                                                   bool const fix_ptw, bool const fix_roll, bool const fix_pitch,
                                                   bool const fix_yaw, bool const fix_itc)
  : Base(noise_model, wTi_key, ptw_key, rpy_key, itc_key)
  , K_(K)
  , measurement_(measurement)
  , fix_wTi_(fix_wTi)
  , fix_ptw_(fix_ptw)
  , fix_roll_(fix_roll)
  , fix_pitch_(fix_pitch)
  , fix_yaw_(fix_yaw)
  , fix_itc_(fix_itc)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Point2 const& CameraImuExtrinsicFactor::GetMeasurement() const noexcept
{
    return measurement_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Cal3_S2::shared_ptr const& CameraImuExtrinsicFactor::GetCalibration() const noexcept
{
    return K_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Vector CameraImuExtrinsicFactor::evaluateError(gtsam::Pose3 const& wTi, gtsam::Point3 const& ptw,
                                                      gtsam::Vector3 const& rpy, gtsam::Vector3 const& itc,
                                                      boost::optional<gtsam::Matrix&> HwTi,
                                                      boost::optional<gtsam::Matrix&> Hptw,
                                                      boost::optional<gtsam::Matrix&> Hrpy,
                                                      boost::optional<gtsam::Matrix&> Hitc) const
{
    gtsam::Matrix36     Hpti_wTi;  ///< Hpti_wTi = d(pti) / d(wTi)
    gtsam::Matrix33     Hpti_ptw;  ///<   Hpti_ptw = d(pti) / d(ptw)
    gtsam::Point3 const pti = wTi.transform_to(ptw, HwTi ? &Hpti_wTi : NULL, Hptw ? &Hpti_ptw : NULL);

    gtsam::Matrix33     Hpt0_pti, Hpt0_itc;  ///< Hpt0_pti = d(pt0) / d(pti), Hpt0_itc = d(pt0) / d(itc)
    gtsam::Point3 const pt0 = pti - gtsam::Point3(itc);
    Hpt0_pti                = gtsam::Matrix3::Identity();
    Hpt0_itc                = -gtsam::Matrix3::Identity();

    /** Hptc_pt0 = d(ptc) / d(pt0)
     * Hptc_roll = d(ptc) / d(roll)
     * Hptc_pitch = d(ptc) / d(pitch)
     * Hptc_yaw = d(ptc) / d(yaw)
     */
    gtsam::Matrix33     Hptc_pt0;
    gtsam::Matrix31     Hptc_roll, Hptc_pitch, Hptc_yaw;
    gtsam::Point3 const ptc = RpyUnrotate(pt0, rpy(0u), rpy(1u), rpy(2u), (HwTi || Hptw || Hitc) ? &Hptc_pt0 : NULL,
                                          Hrpy ? &Hptc_roll : NULL, Hrpy ? &Hptc_pitch : NULL, Hrpy ? &Hptc_yaw : NULL);

    gtsam::Matrix23                      Hpt_img_ptc;  ///< Hpt_img_ptc = d(pt_img) / d(ptc)
    gtsam::PinholeCamera<gtsam::Cal3_S2> pinhole_camera(gtsam::Pose3::identity(), *K_);
    bool                                 need_H = (HwTi || Hptw || Hrpy || Hitc);
    gtsam::Point2 pt_img = pinhole_camera.project(ptc, boost::none, need_H ? &Hpt_img_ptc : NULL, boost::none);

    if (HwTi)
    {
        if (fix_wTi_)
        {
            *HwTi = gtsam::Matrix26::Zero();
        }
        else
        {
            *HwTi = Hpt_img_ptc * Hptc_pt0 * Hpt0_pti * Hpti_wTi;
        }
    }

    if (Hptw)
    {
        if (fix_ptw_)
        {
            *Hptw = gtsam::Matrix23::Zero();
        }
        else
        {
            *Hptw = Hpt_img_ptc * Hptc_pt0 * Hpt0_pti * Hpti_ptw;
        }
    }

    if (Hrpy)
    {
        *Hrpy = gtsam::Matrix23::Zero();

        if (!fix_roll_)
        {
            Hrpy->block(0u, 0u, 2u, 1u) = Hpt_img_ptc * Hptc_roll;
        }

        if (!fix_pitch_)
        {
            Hrpy->block(0u, 1u, 2u, 1u) = Hpt_img_ptc * Hptc_pitch;
        }

        if (!fix_yaw_)
        {
            Hrpy->block(0u, 2u, 2u, 1u) = Hpt_img_ptc * Hptc_yaw;
        }
    }

    if (Hitc)
    {
        if (fix_itc_)
        {
            *Hitc = gtsam::Matrix23::Zero();
        }
        else
        {
            *Hitc = Hpt_img_ptc * Hptc_pt0 * Hpt0_itc;
        }
    }

    return pt_img - measurement_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Point3 CameraImuExtrinsicFactor::RpyUnrotate(gtsam::Point3 const& pt, double const roll, double const pitch,
                                                    double const yaw, gtsam::OptionalJacobian<3, 3> Hpt,
                                                    gtsam::OptionalJacobian<3, 1> Hroll,
                                                    gtsam::OptionalJacobian<3, 1> Hpitch,
                                                    gtsam::OptionalJacobian<3, 1> Hyaw) const
{
    gtsam::Matrix31     Hpt1_yaw;
    gtsam::Matrix33     Hpt1_pt;  ///< Hpt1_yaw = d(pt1) / d(yaw), Hpt1_pt = d(pt1) / d(pt)
    gtsam::Point3 const pt1 = YawUnrotate(yaw, pt, Hyaw ? &Hpt1_yaw : NULL, Hpt ? &Hpt1_pt : NULL);

    gtsam::Matrix31     Hpt2_pitch;
    gtsam::Matrix33     Hpt2_pt1;  ///< Hpt2_pitch = d(pt2) / d(pitch), Hpt2_pt1 = d(pt2) / d(pt1)
    gtsam::Point3 const pt2 = PitchUnrotate(pitch, pt1, Hpitch ? &Hpt2_pitch : NULL, (Hyaw || Hpt) ? &Hpt2_pt1 : NULL);

    gtsam::Matrix31     Hpt3_roll;
    gtsam::Matrix33     Hpt3_pt2;  ///< Hpt3_roll = d(pt3) / d(roll), Hpt3_pt2 = d(pt3) / d(pt2)
    gtsam::Point3 const pt3 =
        RollUnrotate(roll, pt2, Hroll ? &Hpt3_roll : NULL, (Hyaw || Hpt || Hpitch) ? &Hpt3_pt2 : NULL);

    if (Hpt)
    {
        *Hpt = Hpt3_pt2 * Hpt2_pt1 * Hpt1_pt;
    }

    if (Hroll)
    {
        *Hroll = Hpt3_roll;
    }

    if (Hpitch)
    {
        *Hpitch = Hpt3_pt2 * Hpt2_pitch;
    }

    if (Hyaw)
    {
        *Hyaw = Hpt3_pt2 * Hpt2_pt1 * Hpt1_yaw;
    }

    return pt3;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Point3 CameraImuExtrinsicFactor::RollUnrotate(double const roll, gtsam::Point3 const& pt,
                                                     gtsam::OptionalJacobian<3, 1> H1,
                                                     gtsam::OptionalJacobian<3, 3> H2) const
{
    gtsam::Rot3 const   Rx = gtsam::Rot3::Roll(roll);
    gtsam::Point3 const q  = Rx.unrotate(pt);

    if (H1)
    {
        *H1 << 0.0, q.z(), -q.y();
    }

    if (H2)
    {
        *H2 = Rx.transpose();
    }

    return q;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Point3 CameraImuExtrinsicFactor::PitchUnrotate(double const pitch, gtsam::Point3 const& pt,
                                                      gtsam::OptionalJacobian<3, 1> H1,
                                                      gtsam::OptionalJacobian<3, 3> H2) const
{
    gtsam::Rot3 const   Ry = gtsam::Rot3::Pitch(pitch);
    gtsam::Point3 const q  = Ry.unrotate(pt);

    if (H1)
    {
        *H1 << -q.z(), 0.0, q.x();
    }

    if (H2)
    {
        *H2 = Ry.transpose();
    }

    return q;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Point3 CameraImuExtrinsicFactor::YawUnrotate(double const yaw, gtsam::Point3 const& pt,
                                                    gtsam::OptionalJacobian<3, 1> H1,
                                                    gtsam::OptionalJacobian<3, 3> H2) const
{
    gtsam::Rot3 const   Rz = gtsam::Rot3::Yaw(yaw);
    gtsam::Point3 const q  = Rz.unrotate(pt);

    if (H1)
    {
        *H1 << q.y(), -q.x(), 0.0;
    }

    if (H2)
    {
        *H2 = Rz.transpose();
    }

    return q;
}

}  // namespace internal
}  // namespace localization
}  // namespace holo
