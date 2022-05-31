/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file eol_surround_camera_data_container_with_ocam.h
 * @brief data container for surround camera calibration
 * @author jiaxing zhao(zhaojiaxing@holomaitc.com)
 * @date "2021-07-30"
 */

#ifndef HOLO_CALIBRATION_CAMERA_FIELD_EOL_PROJECT_EOL_SURROUND_CAMERA_DATA_CONTAINER_WITH_OCAM_H_
#define HOLO_CALIBRATION_CAMERA_FIELD_EOL_PROJECT_EOL_SURROUND_CAMERA_DATA_CONTAINER_WITH_OCAM_H_

#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

#include <holo/calibration/camera/field/eol_project/types.h>
#include <holo/calibration/common/field/chessboard_database.h>
#include <holo/log/hololog.h>



namespace holo
{
namespace calibration
{
namespace camera
{
/**
 * @brief this class aims to manage data for surround camera calibration
 */
class EOLSurroundCameraCalibrationDataContainer
{
public:
    using Scalar = holo::calibration::camera::Scalar;

    /**
     * @brief  chessboard parameter
     */
    struct ChessboardParameter
    {
        /**
         * @brief interior number of row corners.
         */
        uint8_t chessboard_rows = 0U;

        /**
         * @brief interior number of column corners.
         */
        uint8_t chessboard_columns = 0U;

    };  // ChessboardParameter

    /**
     * @brief  parameters
     */
    struct Parameters
    {
        /**
         * @brief chessboard parameter, support multi different chessboard pattern
         */
        std::vector<ChessboardParameter> chessboards_params;

        /**
         * @brief Maximum allowed reprojection error to treat a point pair as an inlier
         */
        Scalar homograph_ransac_reproj_threshold = 1;

        /**
         * @brief the body extrinsic (from world to body)
         *         x->up, y->left
         */
        Pose3 bTw = Pose3::Identity();

        /**
         * @brief the body extrinsic (from world to body)
         *        y->up, x->right
         */
        Pose3 birdviewTw = Pose3::Identity();

        /**
         * @brief Because of distortion, pixels in the same row and column may be different, 20[pixel] is empirical
         * value
         * @note uint is pixel
         */
        Scalar sort_corners_threshold = Scalar(20);

        /**
         * @brief calibration error tolerance
         */
        Scalar error_tolerance = 1.5;

        /**
         * @brief detect minimum point num
         */
        Scalar detect_minimum_point_num = 8;

        /**
         * @brief database scale, convert unit from milimeter to meter
         *
         */
        Scalar scale = 1000.0;

        /**
         * @brief 5*3 chessboard corner can't be detected, in order to improve the optimization
         *        algorithm accuracy, temporarily select points manually.
         *
         */
        std::vector<std::string> manual_selection_point_files;

        /**
         * @brief interior number of column corners.
         */
        bool_t visualization = false;

        /**
         * @brief verbose
         */
        bool_t verbose = false;

        /**
         * @brief file of the extrinsic which represents camera in ground frame
         */
        std::string camera_in_ground_extrinsic_file;

        /**
         * @brief file of the extrinsic which represents camera in body frame
         */
        std::string camera_in_body_extrinsic_file;

    };  // Parameters

    /**
     * @brief Construct a new Surround Camera Data Container object
     */
    EOLSurroundCameraCalibrationDataContainer();

    /**
     * @brief Destroy the Surround Camera Data Container object
     *
     */
    ~EOLSurroundCameraCalibrationDataContainer();

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
     * @brief Set the Image Data object
     *
     * @param src
     */
    void SetImageData(cv::Mat const& src)
    {
        src_ = src;
    }

    /**
     * @brief Set the Omnidirectional Intrinsic object
     *
     * @param intrinsic
     * @param scale_for_ocam
     */
    void SetOmnidirectionalIntrinsic(OmnidirectionalIntrinsic const& intrinsic, Scalar const scale_for_ocam = 1.0);

    /**
     * @brief Set the Chessboard Database object
     *
     * @param[in] chessboard_db chessboard database
     */
    void SetChessboardDatabase(ChessboardDatabasePtr const& chessboard_db_ptr)
    {
        chessboard_db_ptr_ = chessboard_db_ptr;
        tag_type_          = TagType::Chessboard;
    }

    /**
     * @brief Set the Parameters object
     *
     * @param params
     */
    void SetParameters(Parameters const& params)
    {
        params_ = params;
    }

    /**
     * @brief Get the Parameters object
     *
     * @return params
     */
    Parameters const& GetParameters() const
    {
        return params_;
    }

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
    bool_t UpdataStatus();

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
     * @brief Get the Undistorted Point object
     *
     * @param intrinsic
     * @param distorted_u_v
     * @return Point2
     */
    Point2 getUndistortedPoint(OmnidirectionalIntrinsic const& intrinsic, cv::Mat const& K,
                               Point2 const& distorted_u_v) const;

    /**
     * @brief associate the position of image feature and real world
     *
     * @param[in] distorted_image distorted image
     * @return std::pair<std::vector<cv::Point2f>, std::vector<cv::Point2f>> associated 2d-2d data
     */
    std::pair<std::vector<cv::Point2f>, std::vector<cv::Point2f>>
    doDataAssociation(cv::Mat const& distorted_image) const;

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
     *
     * @param chessboard_db_ptr Shared pointer of ChessboardDatabase, which should be generated using
     *                         the specified application "generate_chessboard_database",
     * @param gray_image gray image
     * @param params parameters
     * @param vpoint2_pixel vpoint2_pixel feature's position in image coord
     * @param vpoint2_world vpoint2_world feature's position in world coord
     */
    void processChessboard(ChessboardDatabasePtr const& chessboard_db_ptr, cv::Mat const& gray_image,
                           Parameters const params, std::vector<cv::Point2f>& vpoint2_pixel,
                           std::vector<cv::Point2f>& vpoint2_world) const;

    /**
     * @brief load Chessboard corners
     * @note This is an interim scheme
     *
     * @param fn
     * @return corners
     */
    std::vector<cv::Point2f> loadChessboardCorners(const std::string& fn) const;

private:
    /**
     * @brief source image
     *
     */
    cv::Mat src_;

    /**
     * @brief used to unproject a distorted point
     *
     */
    OmnidirectionalIntrinsic intrinsic_;

    /**
     * @brief pointer of chessboarddatabase
     *
     */
    ChessboardDatabasePtr chessboard_db_ptr_;

    /**
     * @brief camera matrix for fisheye and pinhole is K from intrinsic,
     *        for OCAM it is generated
     *
     */
    cv::Mat K_;

    /**
     * @brief undistorted image by K_
     *
     */
    cv::Mat undistorted_image_;

    /**
     *  @brief 2d point detected from undistorted image
     *
     */
    std::vector<cv::Point2f> camera_p2d_;

    /**
     * @brief  2d from apriltag or chessboard database
     *
     */
    std::vector<cv::Point2f> world_2d_;

    /**
     * @brief homography matrix
     *        pixel -> world
     *
     */
    cv::Mat H_;

    /**
     * @brief tag type for apriltag chessboard
     *
     */
    TagType tag_type_;

    /**
     * @brief camera pose in world frame
     *
     */
    Pose3 wTc_;

    /**
     * @brief parameters
     *
     */
    Parameters params_;
};
}  // namespace camera
}  // namespace calibration
}  // namespace holo

#endif  // HOLO_CALIBRATION_CAMERA_FIELD_EOL_PROJECT_EOL_SURROUND_CAMERA_DATA_CONTAINER_WITH_OCAM_H_
