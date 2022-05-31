/*
 * Copyright (C) HoloMatic Technology (Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lidar2camera_calibrator.h
 * @brief Class for camera-lidar calibration
 * @author cuijiashuo@holomatic.com (Jiashuo Cui)
 * @date 2021-12-01
 */

#ifndef HOLO_CALIBRATION_DEV_LIDAR2CAMERA_CALIBRATOR_H_
#define HOLO_CALIBRATION_DEV_LIDAR2CAMERA_CALIBRATOR_H_

#include <holo/3d/filter/voxel_grid_filter.h>
#include <holo/calibration/dev/sensors_extrinsic_calibration_base.h>
#include <holo/calibration/dev/utils/evaluator.h>
#include <holo/localization/sam/sam.h>

using namespace holo::localization;

namespace holo
{
namespace calibration
{
class Lidar2CameraCalibrator : public SensorsExtrinsicCalibrationBase
{
    using Base = SensorsExtrinsicCalibrationBase;

public:
    /**
     * @brief Advanced constructor
     *
     * @param[in] src_images Source images
     * @param[in] apriltag_db AprilTag database
     * @param[in] lidar_pointclouds Lidar point clouds
     * @param[in] riegl_pointcloud_ptr Riegl point cloud ptr
     * @param[in] camera_intrinsic_ptr Camera intrinsic base ptr
     * @param[in] algo_para_node Yaml node of calibration algorithm parameters
     * @param[in] verbose Whether to print verbose log
     * @param[in] visualize Whether to visualize the crucial processes.
     */
    Lidar2CameraCalibrator(std::vector<camera::CvMat> const& src_images, camera::AprilTagDatabasePtr const& apriltag_db,
                           std::vector<PointCloud> const& lidar_pointclouds, PointCloudPtr const& riegl_pointcloud_ptr,
                           std::shared_ptr<camera::CameraIntrinsicBase> const& camera_intrinsic_ptr,
                           holo::yaml::Node const& algo_para_node, bool_t const verbose, bool_t const visualize);

    /**
     * @brief Destructor
     *
     */
    virtual ~Lidar2CameraCalibrator() override = default;

    /**
     * @brief Implementation of camera-lidar calibration
     *
     * @return True, if success, otherwise, false.
     */
    bool_t Compute() override;

    /**
     * @brief Get Nth camera pose (cTw) and its status
     *
     * @param[in] index Camera pose index
     * @return Camera pose in world coordinate, and its status
     */
    std::pair<bool_t, Pose3> GetCameraPose(uint32_t const index) const
    {
        return camera_pose_seq_[index];
    }

    /**
     * @brief Get Nth lidar pose (lTw) and its status
     *
     * @param[in] index Lidar pose index
     * @return Lidar pose in world coordinate, and its status
     */
    std::pair<bool_t, Pose3> GetLidarPose(uint32_t const index) const
    {
        return lidar_pose_seq_[index];
    }

    /**
     * @brief Get camera pose (cTw) sequence with statuses
     *
     * @return camera pose sequence with statuses
     */
    std::vector<std::pair<bool_t, Pose3>> GetAllCameraPoses() const
    {
        return camera_pose_seq_;
    }

    /**
     * @brief Get lidar pose (lTw) sequence with statuses
     *
     * @return lidar pose sequence with statuses
     */
    std::vector<std::pair<bool_t, Pose3>> GetAllLidarPoses() const
    {
        return lidar_pose_seq_;
    }

    /**
     * @brief Set calibration parameters from the yaml file
     *
     * @param[in] parameters_node Yaml node holding algorithm parameters
     */
    void SetCalibrationParameters(YAML::Node const& parameters_node)
    {
        camera_parameters_ = camera::CameraCalibrateParameters(parameters_node["Camera"]);
        lidar_parameters_  = lidar::LidarCalibrateParameters(parameters_node["Lidar"]);
    }

private:
    /**
     * @brief Initialize camera poses and camera-lidar extrinsic (cTl)
     *
     * @param[in,out] camera_pose_seq Camera pose sequence with their statuses
     * @return Initialized extrinsic cTl and success flag of initialization
     */
    std::pair<bool_t, Pose3> initializeCameraPoseAndExtrinsic(std::vector<std::pair<bool_t, Pose3>>& camera_pose_seq);

    /**
     * @brief Initialize camera poses only
     *
     * @param[in,out] camera_pose_seq Camera pose sequence with their statuses
     */
    void initializeCameraPose(std::vector<std::pair<bool_t, Pose3>>& camera_pose_seq);

    /**
     * @brief Calculate the mean projection error.
     *
     * @param[in] camera_correspondence_seq A sequence of 2D-3D corresponding points.
     * @param[in] camera_pose_seq A set of camera pose (from world frame to camera frame).
     * @return The mean projection errors in each camera view.
     */
    std::vector<Scalar>
    evaluateProjectionError(std::vector<std::vector<camera::PointCorrespondence>> const& camera_correspondence_seq,
                            std::vector<std::pair<bool_t, Pose3>> const&                 camera_pose_seq) const;

    /**
     * @brief Project 3D points to the image plane if get a specific intrinsic and extrinsic.
     *
     * @param[in] camera_intrinsic Type of camera's intrinsic, currently Pinhole, Fisheye, Omnidirectional are
     *                             supported.
     * @param[in] camera_correspondences a pair of 2D-3D corresponding points.
     * @param[in] cTw Camera's pose (from world frame to camera frame).
     * @return Projected point of a 3D point and its status.
     */
    std::pair<bool_t, camera::CvPoint2f> projectCameraPoint(camera::CameraIntrinsicBase const& camera_intrinsic,
                                                            camera::PointCorrespondence const& camera_correspondences,
                                                            Pose3 const&                       cTw) const;

    /**
     * @brief Draw the detected points and projection points on a image.
     *
     * @param[in] detected_points Detected 2D corner points on input image.
     * @param[in] reprojected_points Image points which are the projection results of 3D points use function
     *                               project().
     * @param[in] source_image Source image sequence.
     * @note If the src_image encoding is GRAYSCALE, visual interface GUI may be gray rather than RGB, so it's best
     *       to use RGB images for visualization.
     * @return Visualization image
     */
    camera::CvMat drawCameraProjectionResult(std::vector<camera::CvPoint2f> const& detected_points,
                                             std::vector<camera::CvPoint2f> const& reprojected_points,
                                             camera::CvMat const&                  source_image) const;

    /**
     * @brief Update lidar pose via camera pose and camera-lidar extrinsic
     *
     * @param[in] camera_pose_seq Camera pose sequence with their statuses
     * @param[in] cTl camera-lidar extrinsic
     * @param[in,out] lidar_pose Lidar pose sequence with their statuses
     */
    void updateLidarPose(std::vector<std::pair<bool_t, Pose3>> const& camera_pose_seq, Pose3 const& cTl,
                         std::vector<std::pair<bool_t, Pose3>>& lidar_pose);

    /**
     * @brief Optimize camera-lidar extrinsic and camera poses
     *
     * @param[in,out] cTl Camera-lidar extrinsic
     * @return True, if success, otherwise, false.
     */
    bool_t optimize(Pose3& cTl);

    /**
     * @brief Initial optimization parameters from a specific extrinsic.
     *
     * @param[in] initial_cTl Initial extrinsic.
     * @return Camera-lidar extrinsic in GTSAM type.
     */
    GTPose3 initializeOptimizationParametersFromExtrinsic(Pose3 const& initial_cTl) const;

    /**
     * @brief Update both camera sigma and lidar sigma
     *
     * @param[in] graph Gtsam graph for lidar to camera calibration
     * @param[in] results Optimized values
     * @param[in,out] lidar_factor_errors vector of lidar errors.
     * @return Updated camera sigma and lidar sigma
     */
    std::pair<Scalar, Scalar> updateSigma(GTNonlinearFactorGraph const& graph, GTValues const& results,
                                          std::vector<Scalar>& lidar_factor_errors) const;

    /**
     * @brief Update optimization parameters to extrinsic.
     *
     * @param[in] cTl Camera-lidar extrinsic after optimization.
     * @return  Camera-lidar extrinsic in holo type.
     */
    Pose3 updateOptimizationParametersToExtrinsic(GTPose3 const& cTl) const;

    /**
     * @brief Project source point clouds to source image sequence
     *
     * @param[in] src_pointclouds Source point cloud sequence
     * @param[in] camera_intrinsic_ptr Camera intrinsic base ptr
     * @param[in] cTl Camera-lidar extrinsic
     */
    void projectLidarPointsToImage(std::vector<PointCloud> const&                      src_pointclouds,
                                   std::shared_ptr<camera::CameraIntrinsicBase> const& camera_intrinsic_ptr,
                                   Pose3 const&                                        cTl);

    /**
     * @brief Source image sequence
     *
     */
    std::vector<camera::CvMat> src_images_;

    /**
     * @brief Shared pointer of AprilTagDatabase
     */
    camera::AprilTagDatabasePtr apriltag_db_;

    /**
     * @brief source Point cloud sequence
     *
     */
    std::vector<PointCloud> lidar_pointclouds_;

    /**
     * @brief Filtered source Point cloud sequence
     *
     */
    std::vector<PointCloud> filtered_lidar_pointclouds_;

    /**
     * @brief Riegl point cloud ptr
     *
     */
    PointCloudPtr riegl_pointcloud_ptr_;

    /**
     * @brief Filtered riegl point cloud ptr
     *
     */
    PointCloudPtr filtered_riegl_pointcloud_ptr_;

    /**
     * @brief Filtered riegl point cloud normal ptr
     *
     */
    PointCloudNormalPtr filtered_riegl_pointcloud_normal_ptr_;

    /**
     * @brief Filtered riegl point cloud curvatures
     *
     */
    std::vector<Scalar_32_t> filtered_riegl_pointcloud_curvatures_;

    /**
     * @brief 3D-2D correspondences sequence.
     *
     * @note For compute camera poses
     */
    std::vector<std::vector<camera::PointCorrespondence>> camera_correspondences_seq_;

    /**
     * @brief 3D-3D correspondences sequence.
     *
     * @note For compute lidar poses
     */
    std::vector<std::vector<lidar::LidarCorrespondence>> lidar_correspondences_seq_;

    /**
     * @brief Camera intrinsic base ptr
     *
     */
    std::shared_ptr<camera::CameraIntrinsicBase> camera_intrinsic_ptr_;

    /**
     * @brief The parameters for camera related extrinsic calibration process
     *
     */
    camera::CameraCalibrateParameters camera_parameters_;

    /**
     * @brief The parameters for point clouds registration
     *
     */
    lidar::LidarCalibrateParameters lidar_parameters_;

    /**
     * @brief Camera pose (cTw) sequence with their statuses
     *
     */
    std::vector<std::pair<bool_t, Pose3>> camera_pose_seq_;

    /**
     * @brief Lidar pose (lTw) sequence with theirs statuses
     *
     */
    std::vector<std::pair<bool_t, Pose3>> lidar_pose_seq_;

    Scalar initial_camera_sigma_;  ///< the initial sigma of camera
    Scalar initial_lidar_sigma_;   ///< the initial sigma of lidar
};
}  // namespace calibration
}  // namespace holo

#endif  // HOLO_CALIBRATION_DEV_LIDAR2CAMERA_CALIBRATOR_H_
