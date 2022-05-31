/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file camera_imu_extrinsic_factor_inl.h
 * @brief this file defines camera and imu extrinsic factor which can be used to calibrate
 *        roll, pitch, yaw and translation of camera in imu frame individually
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "2020-04-20"
 */
#ifndef HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_CAMERA_IMU_EXTRINSIC_FACTOR_INL_H_
#define HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_CAMERA_IMU_EXTRINSIC_FACTOR_INL_H_

#include <gtsam/geometry/Cal3_S2.h>
#include <gtsam/geometry/PinholeCamera.h>
#include <gtsam/geometry/Point2.h>
#include <gtsam/geometry/Point3.h>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/nonlinear/NonlinearFactor.h>

namespace holo
{
namespace localization
{
namespace internal
{
/**
 * @addtogroup sam
 * @{
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief this factor optimize Pose3(wTi), Point3(ptw), {rpy(roll, pitch, yaw), itc}(iTc)
 * @details
 *        Optimization variables:
 *        wTi is the pose of imu frame in world frames
 *        ptw is a 3d point in world frames
 *        iTc is the extrinsic of camera frame in imu frame:
 *            rpy(roll, pitch and yaw) is euler angle representation, itc is translation
 *
 *        Measurement: Point2(pt_pixel) pixel coordinate on image
 *        Camera projection matrix: K
 *        Error term: error = projected_pt_pixel - pt_pixel
 *                    projected_pt_pixel = (K * (pt_c.vector() / pt_c.z()).head(2)
 *                    pt_c = Point3([Rot3(roll).inverse()] *[Rot3(pitch).inverse()] * [Rot3(yaw).inverse()] *
 *                           [pt_i.vector() - itc.vector()]) // 3d point in camera frame
 *                    pt_i =  wTi.transformTo(ptw) // 3d point in imu frame
 */
class CameraImuExtrinsicFactor
  : public gtsam::NoiseModelFactor4<gtsam::Pose3, gtsam::Point3, gtsam::Vector3, gtsam::Vector3>
{
public:
    /**
     * @brief define smart pointer
     */
    using ConstPtr = boost::shared_ptr<const CameraImuExtrinsicFactor>;
    using Ptr      = boost::shared_ptr<CameraImuExtrinsicFactor>;
    using Base     = gtsam::NoiseModelFactor4<gtsam::Pose3, gtsam::Point3, gtsam::Vector3, gtsam::Vector3>;

    /**
     * @brief default constructor
     * @note for holo::OptionalT, do not use it directly
     */
    CameraImuExtrinsicFactor() noexcept;

    /**
     * @brief Construct a new Camera Imu Extrinsic Factor object
     *
     * @param[in] noise_model noise model for the error
     * @param[in] wTi_key key of imu in world frame pose(wTi)
     * @param[in] ptw_key key of 3d point in world frame(ptw)
     * @param[in] rpy_key eluer angle key of camera in imu frame's rotation
     * @param[in] itc_key translation key of camera in imu frame's translation
     * @param[in] K camera matrix
     * @param[in] measurement 2d point on image
     * @param[in] fix_wTi whether fix wTi during optimization
     * @param[in] fix_ptw whether fix ptw during optimization
     * @param[in] fix_roll whether fix roll during optimization
     * @param[in] fix_pitch whether fix pitch during optimization
     * @param[in] fix_yaw whether fix yaw during optimization
     * @param[in] fix_itc whether fix translation during optimization
     */
    CameraImuExtrinsicFactor(gtsam::SharedNoiseModel const& noise_model, gtsam::Key const& wTi_key,
                             gtsam::Key const& ptw_key, gtsam::Key const& rpy_key, gtsam::Key const& itc_key,
                             gtsam::Cal3_S2::shared_ptr const& K, gtsam::Point2 const& measurement,
                             bool const fix_wTi = true, bool const fix_ptw = true, bool const fix_roll = true,
                             bool const fix_pitch = true, bool const fix_yaw = true, bool const fix_itc = true);

    /**
     * @brief Get the Measurement object
     *
     * @return the 2d point measurement
     */
    gtsam::Point2 const& GetMeasurement() const noexcept;

    /**
     * @brief Get the Calibration object
     *
     * @return the calibration parameters
     */
    gtsam::Cal3_S2::shared_ptr const& GetCalibration() const noexcept;

    /**
     * @brief evalute error term and jacobian
     *
     * @param[in] wTi pose of imu in world frame
     * @param[in] ptw 3d point in world frame
     * @param[in] rpy euler angle of extrinsic camera in imu frame
     * @param[in] itc translation of extrinsic camera in imu frame
     * @param[in] HwTi the optional Jacobian matrix for wTi, *HwTi will be set to zero if fix_wTi_ == true
     * @param[in] Hptw the optional Jacobian matrix for ptw, *Hptw will be set to zero if fix_ptw_ == true
     * @param[in] Hrpy the optional Jacobian matrix for euler angle, *Hrpy's 0 1 2 column will be set to zero if
     *            fix_roll_ == true, fix_pitch_ = true or fix_yaw_ == true
     * @param[in] Hitc the optional Jacobian matrix for translation, *Hitc will be set to zero if fix_itc_ == true
     * @return gtsam::Vector pixel error
     */
    virtual gtsam::Vector evaluateError(gtsam::Pose3 const& wTi, gtsam::Point3 const& ptw, gtsam::Vector3 const& rpy,
                                        gtsam::Vector3 const& itc, boost::optional<gtsam::Matrix&> HwTi = boost::none,
                                        boost::optional<gtsam::Matrix&> Hptw = boost::none,
                                        boost::optional<gtsam::Matrix&> Hrpy = boost::none,
                                        boost::optional<gtsam::Matrix&> Hitc = boost::none) const override;

protected:
    /**
     * @brief unrotate 3d point with euler angle representation
     *
     * @param[in] pt 3d point
     * @param[in] roll roll angle
     * @param[in] pitch pitch angle
     * @param[in] yaw yaw angle
     * @param[in] Hroll jacobian of roll
     * @param[in] Hpitch jacobian of pitch
     * @param[in] Hyaw jacobian of yaw
     * @return unrotated 3d point
     */
    gtsam::Point3 RpyUnrotate(gtsam::Point3 const& pt, double const roll, double const pitch, double const yaw,
                              gtsam::OptionalJacobian<3, 3> Hpt    = boost::none,
                              gtsam::OptionalJacobian<3, 1> Hroll  = boost::none,
                              gtsam::OptionalJacobian<3, 1> Hpitch = boost::none,
                              gtsam::OptionalJacobian<3, 1> Hyaw   = boost::none) const;

    /**
     * @brief unrotate a point with roll angle
     *
     * @param[in] roll roll angle of euler angle
     * @param[in] pt 3d point
     * @param[in] H1 jacobian of roll
     * @param[in] H2 jacobian of pt
     * @return the unrotated 3d point
     */
    gtsam::Point3 RollUnrotate(double const roll, gtsam::Point3 const& pt,
                               gtsam::OptionalJacobian<3, 1> H1 = boost::none,
                               gtsam::OptionalJacobian<3, 3> H2 = boost::none) const;

    /**
     * @brief unrotate 3d point with pitch angle
     *
     * @param[in] pitch pitch angle of euler angle
     * @param[in] pt 3d point
     * @param[in] H1 jacobian of pitch
     * @param[in] H2 jacobian of pt
     * @return the unrotated 3d point
     */
    gtsam::Point3 PitchUnrotate(double const pitch, gtsam::Point3 const& pt,
                                gtsam::OptionalJacobian<3, 1> H1 = boost::none,
                                gtsam::OptionalJacobian<3, 3> H2 = boost::none) const;

    /**
     * @brief unrotate 3d point with yaw angle
     *
     * @param[in] yaw yaw angle of euler angle
     * @param[in] pt 3d point
     * @param[in] H1 jacobian of yaw
     * @param[in] H2 jacobian of pt
     * @return the unrotated 3d point
     */
    gtsam::Point3 YawUnrotate(double const yaw, gtsam::Point3 const& pt, gtsam::OptionalJacobian<3, 1> H1 = boost::none,
                              gtsam::OptionalJacobian<3, 3> H2 = boost::none) const;

protected:
    gtsam::Cal3_S2::shared_ptr K_;            ///< camera projection matrix
    gtsam::Point2              measurement_;  ///< measured pixel on image[pixel]
    bool                       fix_wTi_;      ///< whether fix wTi during optimization
    bool                       fix_ptw_;      ///< whether fix ptw during optimization
    bool                       fix_roll_;     ///< whether fix roll during optimization
    bool                       fix_pitch_;    ///< whether fix pitch during optimization
    bool                       fix_yaw_;      ///< whether fix yaw during optimization
    bool                       fix_itc_;      ///< whether fix itc during optimization
};

/**
 * @}
 *
 */
}  // namespace internal
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_CAMERA_IMU_EXTRINSIC_FACTOR_INL_H_
