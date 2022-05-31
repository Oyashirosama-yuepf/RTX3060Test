/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file camera_calibration_with_apriltag_base.h
 * @brief Base class for EOL(end of line) camera calibration
 * @author jiaxing.zhao @ zhaojiaxing@holomatic.com
 * @date 2021-06-01
 */

#ifndef HOLO_CALIBRATION_CAMERA_FIELD_EOL_CAMERA_CALIBRATION_BASE_H_
#define HOLO_CALIBRATION_CAMERA_FIELD_EOL_CAMERA_CALIBRATION_BASE_H_

#include <holo/calibration/camera/field/eol_project/types.h>
#include <holo/core/exception.h>
#include <holo/geometry/pose3.h>
#include <holo/log/hololog.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>

#include <iostream>
#include <string>
#include <vector>

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
 * @brief This is a base class for calibrate camera with apriltag ChArUcob Chessboard
 */
class EOLCameraCalibrationBase
{
public:
    /**
     * @brief Parameters
     */
    struct AlgorithmParameters
    {
        /**
         * @brief threshold of minimum detection points
         */
        uint8_t minimum_detection_points = 2U;

        /**
         * @brief noise sigma, unit: pixel
         */
        Scalar noise_sigma = Scalar(2.0);

        /**
         * @brief the threshold of huber loss
         */
        Scalar huber_loss_threshold = Scalar(1.345);

        /**
         * @brief whether fix x, y, z when optimize
         */
        bool_t is_xyz_fixed = false;

        /**
         * @brief whether fix roll, pitch, yaw when optimize
         */
        bool_t is_roll_fixed  = false;
        bool_t is_pitch_fixed = false;
        bool_t is_yaw_fixed   = false;

        /**
         * @brief whether optimize intrinsic variable
         */
        bool_t is_focal_length_fixed;
        bool_t is_principal_point_fixed;
        bool_t is_distortion_param_fixed;

        /**
         * @brief calibration error tolerance
         */
        Scalar error_tolerance = 1.0;

    };  // AlgorithmParameters

    /**
     * @brief Construct a new EOLCameraCalibrationBase object
     */
    EOLCameraCalibrationBase()
      : tag_type_(TagType::UNKNOWN), is_intrinsic_initialized_(false), is_extrinsic_initialized_(false)
    {
    }

    /**
     * @brief Constructor
     *
     * @param[in] source_images Source images
     * @param[in] camera_model Camera lens model, currently only PINHOLE and FISHEYE are supported,
     *                         other types are not supported!
     */
    EOLCameraCalibrationBase(std::vector<Image> const& source_images, CameraModel const& camera_model)
      : source_images_(source_images)
      , tag_type_(TagType::UNKNOWN)
      , camera_model_(camera_model)
      , is_intrinsic_initialized_(false)
      , is_extrinsic_initialized_(false)
    {
    }

    /**
     * @brief Destructor
     */
    virtual ~EOLCameraCalibrationBase() noexcept
    {
    }

    /**
     * @brief Pure virtual function, interface function to calibrate camera.
     * @return True if the calibrated algorithm is successfully; otherwise, false.
     */
    virtual bool_t Compute() = 0;

    /**
     * @brief Set the Images object
     *
     * @param[in] source_images source images
     */
    void SetImages(std::vector<Image> const& source_images)
    {
        source_images_ = source_images;
    }

    /**
     * @brief Set the Camera Model object
     *
     * @param[in] camera_model camera model
     */
    void SetCameraModel(CameraModel const& camera_model)
    {
        camera_model_ = camera_model;
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

    /**
     * @brief Save the camera extrinsic file to the specified path.
     * @param[in] output_path The path to which the file should be written.
     * @param[in] camera_extrinsic camera's extrinsic
     * @note Currently, only absolute paths(output_path) are supported.
     */
    bool_t SaveCameraExtrinsic(std::string const& output_path, Extrinsic const& camera_extrinsic) const;

    /**
     * @brief Get camera extrinsic(Tcw -> from world to camera)
     */
    Extrinsic GetCameraExtrinsic() const
    {
        return extrinsic_;
    }

    /**
     * @brief Set measurement noise about 2D feature point detection.
     * @param[in] standard deviation of 2D points.
     */
    void SetMeasurementNoise(Vector2 const& noise_sigma) noexcept
    {
        noise_sigma_ = noise_sigma;
    }

    /**
     * @brief Get the App Error Status object
     *
     * @param status
     * @return uint32_t
     */
    AppErrorStatus GetAppErrorStatus()
    {
        return app_error_status_;
    }

protected:
    /**
     * @brief Pure virtual function, Project 3D points to the image plane given
     *        intrinsic and extrinsic parameters. will be used to evaluate the
     *        reprojection error.
     * @param[in] object_point 3D point in the world coordinate system.
     * @param[in/out] project_point image points(in image plane).
     * @param[in] cTw camera pose, pose of world frame in camera frame.
     * @param[in] camera_k camera intrinsic matrix should be
     *            \f$A = \vecthreethree{f_x}{0}{c_x}{0}{f_y}{c_y}{0}{0}{1}\f$.
     * @param[in] camera_d distCoeffs Input vector of distortion coefficients, order should be
     *            \f$(k_1, k_2, p_1, p_2, k_3, k_4, k_5, k_6)\f$.
     * @return image point which corresponding to the 3D point.
     */
    virtual Point2 projectPoint(Point3 const& object_point, Pose3 const& cTw, Matrix3 const& camera_k,
                                Vector5 const& camera_d) const = 0;

    /**
     * @brief Analyse calibration error by reprojection error.
     * @param[in] cTw Camera pose, pose of world frame in camera frame.
     * @param[in] camera_k Camera intrinsic matrix should be
     *            \f$A = \vecthreethree{f_x}{0}{c_x}{0}{f_y}{c_y}{0}{0}{1}\f$.
     * @param[in] camera_d Input vector of distortion coefficients, shoud be
     *            \f$(k_1, k_2, p_1, p_2[, k_3[, k_4, k_5, k_6)\f$.
     */
    virtual Scalar analyseError(Pose3 const& cTw, Matrix3 const& camera_k, Vector5 const& camera_d) const = 0;

    /**
     * @brief Pure virtual function, draw the detected points and reprojection points.
     * @param[in] detected_points Coordinates of the points in the original plane.
     * @param[in] reprojected_points Image point which is the result of 3D points use
     *            function projectPoint().
     * @param[in] src_image Source apriltag view .
     * @note If the src_image encoding is GRAYSCALE, visual interface GUI may be gray
     *       rather than RGB, so it's best to use RGB images for visualization.
     * @return visualization image.
     */
    Image drawReprojectionResult(std::vector<Point2> const& detected_points,
                                 std::vector<Point2> const& reprojected_points, Image const& src_image) const;

    /**
     * @brief Save the extrinsic pose to file, just for test.
     * @param[in] ofile C++ standard I/O stream for writting contents to file.
     * @param[in] rvec Rotation vector. See Rodrigues for details.
     * @param[in] tvec Translation vector.
     */
    void savePose(std::ofstream& ofile, Vector3 const& rvec, Vector3 const& tvec) const;

    /**
     * @overload
     * @param[in] ofile C++ standard I/O stream for writting contents to file.
     * @param[in] cTw Camera pose, pose of world frame in camera frame.
     */
    void savePose(std::ofstream& ofile, Pose3 const& cTw) const;

    /**
     * @brief Record the reprojection error to file, just for test.
     * @param[in] ofile C++ standard I/O stream for writting contents to file.
     * @param[in] error_pt Reprojection error.
     */
    void saveError(std::ofstream& ofile, Vector2 const& error_pt) const;

    /**
     * @brief Judge whether a point is in the image.
     * @param[in] u X-coordinate of the image point [unit: pixel].
     * @param[in] v Y-coordinate of the image point [unit: pixel].
     * @param[in] margin Threshold at the edge of the image, default
     *            value is 2 pixel.
     * @return false if a point isn't in the image.
     */
    bool_t isInImage(Scalar const u, Scalar const v, int32_t margin = 2) const;

    /**
     * @brief Subpixel correction
     * @param[in] gray_image Source chessboard view, it must be an 8-bit grayscale.
     * @param[in] vpoint2 Initial coordinates of the input corners.
     * @param[in] tag_type tag type.
     * @param[in] verbose Whether output detailed log information default value is false.
     * @return refined image point.
     */
    std::vector<Point2> refineCorner(cv::Mat const& gray_image, std::vector<Point2> const& vpoint2,
                                     TagType const& tag_type, bool_t verbose = false) const;

protected:
    /**
     * @brief source images
     *
     */
    std::vector<Image> source_images_;

    /**
     * @brief detection tag type
     *
     */
    TagType tag_type_;

    /**
     * @brief app error status
     *
     */
    AppErrorStatus app_error_status_;

    /**
     * @brief 2d points in each image
     *
     */
    std::vector<Point2> image_points_;

    /**
     * @brief 3d points according to 2d points
     *
     */
    std::vector<Point3> object_points_;

    /**
     * @brief camera lens model
     *
     */
    CameraModel camera_model_;

    /**
     * @brief image size
     *
     */
    Vector2 image_size_;

    /**
     * @brief camera_extrinsic
     *
     */
    Extrinsic extrinsic_;

    /**
     * @brief measurement noise [unit: pixel]
     *
     */
    Vector2 noise_sigma_;

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

};  // EOLCameraCalibrationBase

/**
 * @}
 *
 */

}  // namespace camera

}  // namespace calibration

}  // namespace holo

#endif  // HOLO_CALIBRATION_CAMERA_FIELD_EOL_CAMERA_CALIBRATION_BASE_H_