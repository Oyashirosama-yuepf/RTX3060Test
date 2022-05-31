/*
 * Copyright (C) HoloMatic Technology (Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file camera2camera_calibrator.h
 * @brief Class for camera-camera extrinsic calibration
 * @author cuijiashuo@holomatic.com (Jiashuo Cui)
 * @date 2022-01-20
 */

#ifndef HOLO_CALIBRATION_DEV_CAMERA2CAMERA_CALIBRATOR_H_
#define HOLO_CALIBRATION_DEV_CAMERA2CAMERA_CALIBRATOR_H_

#include <holo/calibration/dev/sensors_extrinsic_calibration_base.h>
#include <holo/localization/sam/sam.h>

using namespace holo::localization;

namespace holo
{
namespace calibration
{
class Camera2CameraCalibrator : public SensorsExtrinsicCalibrationBase
{
    using Base                       = SensorsExtrinsicCalibrationBase;
    using CameraIntrinsicBaseT       = holo::common::details::CameraIntrinsicBaseT<Scalar>;
    using CameraIntrinsicBaseTypePtr = std::shared_ptr<CameraIntrinsicBaseT>;

public:
    /**
     * @brief Advanced constructor
     *
     * @param[in] src_images Images collected from source camera.
     * @param[in] tgt_images Images collected from target camera.
     * @param[in] apriltag_db AprilTag database
     * @param[in] src_camera_intrinsic_ptr Intrinsic base ptr of source camera.
     * @param[in] tgt_camera_intrinsic_ptr Intrinsic base ptr of target camera.
     * @param[in] verbose Whether to print verbose log.
     * @param[in] visualize Whether to visualize the crucial processes.
     */
    Camera2CameraCalibrator(std::vector<camera::CvMat> const& src_images, std::vector<camera::CvMat> const& tgt_images,
                            camera::AprilTagDatabasePtr const& apriltag_db,
                            CameraIntrinsicBaseTypePtr const&  src_camera_intrinsic_ptr,
                            CameraIntrinsicBaseTypePtr const& tgt_camera_intrinsic_ptr, bool_t const verbose,
                            bool_t const visualize);

    /**
     * @brief Destructor
     *
     */
    ~Camera2CameraCalibrator() override = default;

    /**
     * @brief Implementation of camera-camera extrinsic calibration.
     *
     * @return True, if success, otherwise, false.
     */
    bool_t Compute() override;

    /**
     * @brief Get Nth source camera pose (wTsc) and its status.
     *
     * @param[in] index Index of source camera pose.
     * @return Source camera pose in world coordinate, and its status.
     */
    std::pair<bool_t, Pose3> GetSourceCameraPose(uint32_t const index) const
    {
        return src_camera_pose_seq_[index];
    }

    /**
     * @brief Get Nth target camera pose (wTtc) and its status.
     *
     * @param[in] index Index of target camera pose.
     * @return Target camera pose in world coordinate, and its status.
     */
    std::pair<bool_t, Pose3> GetTargetCameraPose(uint32_t const index) const
    {
        return tgt_camera_pose_seq_[index];
    }

    /**
     * @brief Get source camera pose (wTsc) sequence with theirs statuses.
     *
     * @return Source camera pose sequence with theirs statuses.
     */
    std::vector<std::pair<bool_t, Pose3>> GetSourceCameraPoses() const
    {
        return src_camera_pose_seq_;
    }

    /**
     * @brief Get target camera pose (wTtc) sequence with theirs statuses.
     *
     * @return Target camera pose sequence with theirs statuses.
     */
    std::vector<std::pair<bool_t, Pose3>> GetTargetCameraPoses() const
    {
        return tgt_camera_pose_seq_;
    }

    /**
     * @brief Set calibration parameters from the yaml file
     *
     * @param[in] parameters_node Yaml node holding camera parameters
     */
    void SetCalibrationParameters(YAML::Node const& parameters_node)
    {
        src_camera_parameters_ = camera::CameraCalibrateParameters(parameters_node, "source");
        tgt_camera_parameters_ = camera::CameraCalibrateParameters(parameters_node, "target");
    }

private:
    /**
     * @brief Initialize (source camera)-(target camera) extrinsic (tcTsc)
     *
     * @param[in] src_correspondences_seq 3D-2D correspondences sequence of source images.
     * @param[in] tgt_correspondences_seq 3D-2D correspondences sequence of target images.
     * @param[in,out] src_camera_pose_seq Source camera pose sequence with theirs statuses.
     * @param[in,out] tgt_camera_pose_seq Target camera pose sequence with theirs statuses.
     * @return Initialized extrinsic tcTsc and its status.
     */
    std::pair<bool_t, Pose3>
    initializeExtrinsic(std::vector<std::vector<camera::PointCorrespondence>> const& src_correspondences_seq,
                        std::vector<std::vector<camera::PointCorrespondence>> const& tgt_correspondences_seq,
                        std::vector<std::pair<bool_t, Pose3>>&                       src_camera_pose_seq,
                        std::vector<std::pair<bool_t, Pose3>>&                       tgt_camera_pose_seq) const;

    /**
     * @brief Calculate the average of camera projection errors.
     *
     * @param[in] camera_correspondence_seq A sequence of 2D-3D corresponding points.
     * @param[in] camera_pose_seq A set of camera pose (from world frame to camera frame).
     * @param[in] camera_intrinsic_ptr Ptr of camera intrinsic.
     * @param[in] draw_image Image for projection.
     * @return The mean projection errors in each camera view.
     */
    std::vector<Scalar> evaluateCameraProjectionError(
        std::vector<std::vector<camera::PointCorrespondence>> const& camera_correspondence_seq,
        std::vector<std::pair<bool_t, Pose3>> const&                 camera_pose_seq,
        CameraIntrinsicBaseTypePtr const& camera_intrinsic_ptr, std::vector<camera::CvMat> const& draw_image) const;

    /**
     * @brief Draw the detected points and re-projected points on a image.
     *
     * @param[in] detected_points Detected 2D corner points.
     * @param[in] reprojected_points Re-projected 3D world points.
     * @param[in] draw_image Origin image for drawing all points.
     * @note Better to use RGB image for visualization.
     * @return Visualization image
     */
    camera::CvMat drawCameraProjectionResult(std::vector<camera::CvPoint2f> const& detected_points,
                                             std::vector<camera::CvPoint2f> const& reprojected_points,
                                             camera::CvMat const&                  draw_image) const;

    /**
     * @brief Optimize (source camera)-(target camera) extrinsic and camera poses
     *
     * @param[in,out] tcTsc (source camera)-(target camera) extrinsic extrinsic
     * @return True, if success, otherwise, false.
     */
    bool_t optimize(Pose3& tcTsc);

    /**
     * @brief Initial optimization parameters from a specific extrinsic.
     *
     * @param[in] holo_tcTsc (source camera)-(target camera) extrinsic extrinsic in h
     * @return Extrinsic in GTSAM type.
     */
    GTPose3 initializeOptimizationParametersFromExtrinsic(Pose3 const& holo_tcTsc) const;

    /**
     * @brief Update optimization parameters to extrinsic.
     *
     * @param[in] gtsam_tcTsc Camera-lidar extrinsic after optimization.
     * @return Extrinsic in holo type.
     */
    Pose3 updateOptimizationParametersToExtrinsic(GTPose3 const& gtsam_tcTsc) const;

    /**
     * @brief Images collected from source camera
     *
     */
    std::vector<camera::CvMat> src_images_;

    /**
     * @brief Images collected from target camera
     *
     */
    std::vector<camera::CvMat> tgt_images_;

    /**
     * @brief Shared pointer of AprilTagDatabase
     *
     */
    camera::AprilTagDatabasePtr apriltag_db_;

    /**
     * @brief 3D-2D correspondences sequence of source images.
     *
     * @note For compute camera poses
     */
    std::vector<std::vector<camera::PointCorrespondence>> src_correspondences_seq_;

    /**
     * @brief 3D-2D correspondences sequence of target images.
     *
     * @note For compute camera poses
     */
    std::vector<std::vector<camera::PointCorrespondence>> tgt_correspondences_seq_;

    /**
     * @brief Intrinsic base ptr of source camera
     *
     */
    CameraIntrinsicBaseTypePtr src_camera_intrinsic_ptr_;

    /**
     * @brief Intrinsic base ptr of target camera
     *
     */
    CameraIntrinsicBaseTypePtr tgt_camera_intrinsic_ptr_;

    /**
     * @brief The calibration parameters of source camera
     *
     */
    camera::CameraCalibrateParameters src_camera_parameters_;

    /**
     * @brief The calibration parameters of target camera
     *
     */
    camera::CameraCalibrateParameters tgt_camera_parameters_;

    /**
     * @brief Source camera pose (wTsc) sequence with theirs statuses
     *
     * @note wTsc means source camera pose in world coordinate
     */
    std::vector<std::pair<bool_t, Pose3>> src_camera_pose_seq_;

    /**
     * @brief Target camera pose (wTtc) sequence with theirs statuses
     *
     * @note wTtc means target camera pose in world coordinate
     */
    std::vector<std::pair<bool_t, Pose3>> tgt_camera_pose_seq_;
};
}  // namespace calibration
}  // namespace holo

#endif  // HOLO_CALIBRATION_DEV_CAMERA2CAMERA_CALIBRATOR_H_
