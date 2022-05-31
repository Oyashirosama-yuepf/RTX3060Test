/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file eol_fisheye_camera_calibration.h
 * @brief class for EOL(end of line) fisheye calibration
 * @author bin.chen @ chenbin@holomatic.com
 * @date 2020-09-01
 */

#ifndef HOLO_CALIBRATION_CAMERA_FIELD_EOL_FISHEYE_CAMERA_CALIBRATION_H_
#define HOLO_CALIBRATION_CAMERA_FIELD_EOL_FISHEYE_CAMERA_CALIBRATION_H_

#include <iostream>
#include <memory>

#include <holo/calibration/camera/field/camera_calibration_with_apriltag_base.h>
#include <holo/calibration/camera/field/types.h>
#include <holo/geometry/quaternion.h>

namespace holo
{
namespace calibration
{
namespace camera
{
/**
 * @addtogroup camera
 * @{
 *
 */

/**
 * @brief A class aims at calibrating the extrinsic(rotation and translation)
 *        and intrinsic(f_x, f_y, c_x, c_y, k_1, k_2) parameters of the camera
 *        using a single image.
 * @note Prior information of intrinsic and extrinsic is required.
 */
class EolFisheyeCameraCalibration : public CameraCalibrationWithApriltagBase
{
public:
    using CameraModel = holo::calibration::camera::CameraModel;

    /**
     * @brief Disable default constructor
     */
    EolFisheyeCameraCalibration() = delete;

    /**
     * @brief Constructor
     * @param[in] apriltag_db  Shared pointer of AprilTagDatabase, which should be generated using
     *                         the specified application "generate_apriltag_database", for details
     *                         information please refer to it's documentation.
     * @param[in] source_image Source image(just one image for EOL calibration), sufficient number
     *                         of AprilTag should be contained.
     * @param[in] camera_model Camera lens model, currently only PINHOLE and FISHEYE are supported,
     *                         other types are not supported!
     * @param[in] parameters calibration algorithm parameters
     *
     * @throw if the camera model is not FISHEYE, throw
     */
    EolFisheyeCameraCalibration(AprilTagDatabasePtr const& apriltag_db, holo::Image const& source_image,
                                CameraModel const& camera_model, Parameters const& parameters);

    /**
     * @brief Destruction
     */
    virtual ~EolFisheyeCameraCalibration()
    {
    }

    /**
     * @brief Interface function to calibrate camera intrinsic and extrinsic.
     * @return True if the calibrated algorithm is successfully; otherwise, false.
     * @throw if calibration failed, throw log information
     */
    virtual bool_t Compute() override;

    /**
     * @brief Set the initial value of the camera fisheye intrinsic.
     * @param[in] intrinsic initial intrinsic.
     */
    void SetInitFisheyeIntrinsic(FisheyeIntrinsic const& intrinsic)
    {
        fisheye_intrinsic_        = intrinsic;
        is_intrinsic_initialized_ = true;
    }

    /**
     * @brief Set the initial value of the camera extrinsic.
     * @param[in] extrinsic initial extrinsic about camera, from world to camera.
     */
    void SetInitExtrinsic(Extrinsic const& extrinsic)
    {
        extrinsic_                = extrinsic;
        is_extrinsic_initialized_ = true;
    }

protected:
    /**
     * @brief Init camera extrinsic corresponding to image using pnp.
     * @param[in] obj_points Vector of corresponding object points.
     * @param[in] img_points Vector of image points in the image coordinate.
     * @param[in] origin_extrinsic initial value of extrinsic
     * @param[in] undistort_point whether use intrinsic to undistort the projection point,
     *                            Default value is false.
     * @return external parameter which solved by PnP algorithm.
     */
    Extrinsic computeExtrinsicWithPnP(std::vector<Point3> const& obj_points, std::vector<Point2> const& img_points,
                                      Extrinsic const& origin_extrinsic, bool_t undistort_point = false) const;

    /**
     * @brief Optimize intrinsic and extrinsic using bundle adjustment.
     * @param[in] obj_points Vector of corresponding object points.
     * @param[in] img_points Vector of image points in the image coordinate.
     * @return Return true if the reprojection error is less than the set threshold;
     *         otherwise, return false
     */
    bool_t optimize(std::vector<Point3> const& obj_points, std::vector<Point2> const& img_points);

    /**
     * @brief Initial optimization parameters from intrinsic.
     * @param[in] initial_intrinsic Initial intrinsic.
     * @return Vector representation of the camera intrinsic.
     */
    std::vector<Scalar> initializeOptimizationParametersFromIntrinsic(FisheyeIntrinsic const& initial_intrinsic) const;

    /**
     * @brief Update optimization parameters to intrinsic.
     * @param[in] camera Intrinsic parameters after optimization (std::vector form).
     * @return Updated camera intrinsic.
     */
    FisheyeIntrinsic updateOptimizationParametersToIntrinsic(std::vector<Scalar> const& camera) const;

    /**
     * @brief Analyse calibration error by reprojection error.
     * @param[in] cTw Camera pose.
     * @param[in] camera_k Camera intrinsic matrix should be
     *            \f$A = \vecthreethree{f_x}{0}{c_x}{0}{f_y}{c_y}{0}{0}{_1}\f$.
     * @param[in] camera_d Input vector of distortion coefficients, shoud be
     *            \f$(k_1, k_2, p_1, p_2, k_3, k_4, k_5, k_6)\f$.
     * @return reprojection error.
     */
    virtual Scalar analyseError(Pose3 const& cTw, Matrix3 const& camera_k, Vector5 const& camera_d) const override;

    /**
     * @brief Project 3D points to the image plane given intrinsic and extrinsic parameters.
     *        will be used to evaluate the reprojection error.
     * @param[in] object_point 3D point in the world coordinate system.
     * @param[in/out] project_point image points(in image plane).
     * @param[in] cTw camera pose, world to camera.
     * @param[in] camera_k camera intrinsic matrix should be
     *            \f$A = \vecthreethree{f_x}{0}{c_x}{0}{f_y}{c_y}{0}{0}{_1}\f$.
     * @param[in] camera_d distCoeffs Input vector of distortion coefficients, shoud be
     *            \f$(k_1, k_2, p_1, p_2, k_3, k_4, k_5, k_6)\f$.
     */
    virtual Point2 projectPoint(Point3 const& object_point, Pose3 const& cTw, Matrix3 const& camera_k,
                                Vector5 const& camera_d) const override;

protected:
    /**
     * @brief input init intrinsic flag. True if the initial value of
     *        the intrinsic has been set, otherwise false.
     */
    bool_t is_intrinsic_initialized_;

    /**
     * @brief input init extrinsic flag. True if the initial value of
     *        the extrinsic has been set, otherwise false.
     */
    bool_t is_extrinsic_initialized_;

    /**
     * @brief Optimize parameters
     */
    Parameters parameters_;

};  // EolFisheyeCameraCalibration

/**
 * @}
 *
 */

}  // namespace camera

}  // namespace calibration

}  // namespace holo

#endif /* ----- #ifndef HOLO_CALIBRATION_CAMERA_FIELD_EOL_FISHEYE_CAMERA_CALIBRATION_H_  ----- */
