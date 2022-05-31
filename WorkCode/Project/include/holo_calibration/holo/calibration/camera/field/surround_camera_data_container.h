/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file surround_camera_data_container.h
 * @brief data container for surround camera calibration
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @author jiaxing zhao(zhaojiaxing@holomaitc.com)
 * @date "2021-04-14"
 */

#ifndef HOLO_CALIBRATION_CAMERA_FIELD_SURROUND_CAMERA_DATA_CONTAINER_H_
#define HOLO_CALIBRATION_CAMERA_FIELD_SURROUND_CAMERA_DATA_CONTAINER_H_

#include <vector>

#include <holo/log/hololog.h>
#include <opencv2/core/core.hpp>

#include <holo/calibration/apriltag_cpp/apriltags2_adapter.h>
#include <holo/calibration/camera/field/types.h>
#include <holo/calibration/common/field/apriltag_database.h>
#include <holo/geometry/pose3.h>

namespace holo
{
namespace calibration
{
namespace camera
{
/**
 * @brief this class aims to manage data for surround camera calibration
 */
class SurroundCameraDataContainer
{
public:
    using Scalar              = holo::float64_t;
    using AprilTag            = holo::calibration::AprilTagDatabase::AprilTag;
    using AprilTagDetector    = AprilTags2::AprilTags2Adapter;
    using AprilTagDetectorPtr = typename AprilTagDetector::Ptr;
    using TagDetection        = AprilTags2::TagDetection;

    /**
     * @brief Construct a new Surround Camera Data Container object
     *
     * @param[in] src
     * @param[in] intrinsic
     * @param[in] apriltag_db_ptr
     * @param[in] scale_for_ocam
     */
    SurroundCameraDataContainer(cv::Mat const& src, OmnidirectionalIntrinsic const& intrinsic,
                                AprilTagDatabasePtr const& apriltag_db_ptr, Scalar const scale_for_ocam = 1.0,
                                bool const& visualization = false);

    /**
     * @brief Destroy the Surround Camera Data Container object
     *
     */
    ~SurroundCameraDataContainer();

    /**
     * @brief Get the 2d points in image frame
     *
     * @return std::vector<cv::Point2f> const&
     */
    std::vector<cv::Point2f> const& GetSource() const;

    /**
     * @brief Get the 2d points in world frame
     *
     * @return std::vector<cv::Point2f> const&
     */
    std::vector<cv::Point2f> const& GetTarget() const;

    /**
     * @brief Set the Homography Matrix object
     *
     * @param[in] H
     */
    void SetHomographyMatrix(cv::Mat const& H);

    /**
     * @brief Get the Homography Matrix object
     *
     * @return cv::Mat const&
     */
    cv::Mat const& GetHomographyMatrix() const;

    /**
     * @brief set camera pose in world frame
     * @param[in] wTc camera pose in world frame
     */
    void SetPose(Pose3 const& wTc)
    {
        wTc_ = wTc;
    }

    /**
     * @brief get camera pose in world frame
     * @return camera pose in world frame
     */
    Pose3 const& GetPose() const
    {
        return wTc_;
    }

    /**
     * @brief Set the Camera Matrix object
     *
     * @param[in] K
     */
    void SetCameraMatrix(cv::Mat const& K);

    /**
     * @brief Get the Camera Matrix object
     *
     * @return cv::Mat const&
     */
    cv::Mat const& GetCameraMatrix() const;

    /**
     * @brief Get the Intrinsic object
     *
     * @return Intrinsic const&
     */
    OmnidirectionalIntrinsic const& GetIntrinsic() const;

    /**
     * @brief update internal members by undistort image, detect apriltag and data association
     */
    void UpdataStatus();

    /**
     * @brief get the undistorted image
     * @return cv::Mat of undistorted image
     */
    cv::Mat const& GetUndistortedImage() const;

    /**
     * @brief get the raw image
     * @return cv::Mat of raw image
     */
    cv::Mat const& GetSourceImage() const;

    /**
     * @brief Bilinear Interpolation
     *
     * @param[in] image source image
     * @param[in] x pixel's position of x
     * @param[in] y pixel's position of y
     * @return Pixel value after interpolation
     */
    cv::Vec3b BilinearInterpolation(cv::Mat const& image, Scalar const& x, Scalar const& y) const;

protected:
    /**
     * @brief generate camera matrix
     *
     * @param[in] intrinsic camera intrinsic
     * @param[in] scale_for_ocam scale used to generate camera matrix for ocam camera
     * @return cv::Mat camera matrix
     */
    cv::Mat generateCameraMatrix(OmnidirectionalIntrinsic const& intrinsic, Scalar const scale_for_ocam) const;

    /**
     * @brief Get the Undistorted Image object
     *
     * @param[in] src source image
     * @param[in] K camera matrix
     * @param[in] intrinsic intrinsic
     * @return cv::Mat undistorted image
     */
    cv::Mat getUndistortedImage(cv::Mat const& src, cv::Mat const& K, OmnidirectionalIntrinsic const& intrinsic) const;

    /**
     * @brief associate the position of image feature and real world
     *
     * @param[in] undistorted_image undistorted image
     * @return std::pair<std::vector<cv::Point2f>, std::vector<cv::Point2f>> associated 2d-2d data
     */
    std::pair<std::vector<cv::Point2f>, std::vector<cv::Point2f>>
    doDataAssociation(cv::Mat const& undistorted_image) const;

    /**
     * @brief judge whether the position is in image area
     *
     * @param[in] x position of col
     * @param[in] y position of row
     * @param[in] margin the margin of at the image border
     * @return true or false
     */
    bool isInImage(Scalar const& x, Scalar const& y, int32_t const& margin = 2) const;

    /**
     * @brief according to the results of feature detection to find the coordinate of world for each feature
     * @param[in] tag_results the results of feature detection (id, tag's corner position)
     * @param[out] vpoint2_pixel feature's position in image coord
     * @param[out] vpoint2_world feature's position in world coord
     */
    void processTags(std::vector<TagDetection> const& tag_results, std::vector<cv::Point2f>& vpoint2_pixel,
                     std::vector<cv::Point2f>& vpoint2_world) const;

private:
    cv::Mat                  src_;                ///< source image
    OmnidirectionalIntrinsic intrinsic_;          ///< used to unproject a distorted point
    AprilTagDatabasePtr      apriltag_db_ptr_;    ///< database ptr
    cv::Mat                  K_;                  ///< camera matrix for fisheye and pinhole is K from intrinsic,
                                                  ///  for OCAM it is generated
    cv::Mat                  undistorted_image_;  ///< undistorted image by K_
    std::vector<cv::Point2f> camera_p2d_;         ///< 2d point detected from undistorted image
    std::vector<cv::Point2f> world_2d_;           ///< 2d from apriltag database
    cv::Mat                  H_;                  ///< homography matrix    pixel -> world
    bool                     visualization_;      ///< control whether to show image during the calibration
    Pose3                    wTc_;                ///< camera pose in world frame
};
}  // namespace camera
}  // namespace calibration
}  // namespace holo

#endif  // HOLO_CALIBRATION_CAMERA_FIELD_SURROUND_CAMERA_DATA_CONTAINER_H_