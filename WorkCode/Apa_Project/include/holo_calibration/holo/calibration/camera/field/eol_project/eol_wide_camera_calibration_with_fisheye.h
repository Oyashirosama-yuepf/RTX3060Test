/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file eol_wide_camera_calibration_with_fisheye.h
 * @brief class for EOL(end of line) fisheye calibration
 * @author jiaxing.zhao @ zhaojiaxing@holomatic.com
 * @date 2021-06-03
 */

#ifndef HOLO_CALIBRATION_CAMERA_FIELD_EOL_PROJECT_EOL_WIDE_CAMERA_CALIBRATION_WITH_FISHEYE_H_
#define HOLO_CALIBRATION_CAMERA_FIELD_EOL_PROJECT_EOL_WIDE_CAMERA_CALIBRATION_WITH_FISHEYE_H_

#include <iostream>
#include <memory>

#include <holo/calibration/camera/field/eol_camera_calibration_base.h>
#include <holo/calibration/camera/field/eol_project/types.h>
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
 *        is not currently optimized.
 */
class EOLWideCameraCalibration : public EOLCameraCalibrationBase
{
public:
    using Base                 = EOLCameraCalibrationBase;
    using Correspondence       = std::pair<std::vector<Point3>, std::vector<Point2>>;
    using CharucoIDsAndCorners = std::pair<std::vector<int>, std::vector<cv::Point2f>>;

    /**
     * @brief ChArUcob parameter
     */
    struct ChArUcobParameter
    {
        /**
         * @brief interior number of row corners.
         */
        uint8_t corner_rows = 4U;

        /**
         * @brief interior number of column corners.
         */
        uint8_t corner_columns = 6U;

        /**
         * @brief number of bits per dimension in dictionary, such as 6 in cv::aruco::DICT_6X6_250
         */
        uint8_t marker_size = 6U;

        /**
         * @brief maximum number of bits that can be corrected in dictionary, such as 250 in cv::aruco::DICT_6X6_250
         */
        uint32_t max_marker_num = 250U;

        /**
         * @brief  dictionary: DICT_4X4_50   =0,  DICT_4X4_100        =1,  DICT_4X4_250  =2,
         *                     DICT_4X4_1000 =3,  DICT_5X5_50         =4,  DICT_5X5_100  =5,
         *                     DICT_5X5_250  =6,  DICT_5X5_1000       =7,  DICT_6X6_50   =8,
         *                     DICT_6X6_100  =9,  DICT_6X6_250        =10, DICT_6X6_1000 =11,
         *                     DICT_7X7_50   =12, DICT_7X7_100        =13, DICT_7X7_250  =14,
         *                     DICT_7X7_1000 =15, DICT_ARUCO_ORIGINAL = 16
         */
        uint16_t dictionary_id = 10U;

        /**
         * @brief whether dictionary id pattern
         */
        bool_t is_dictionary_id_pattern = true;

        /**
         * @brief the length of the squares,it can be provided in any unit, having in mind that the estimated pose
         * for this board would be measured in the same units (usually meters are used)
         */
        Scalar square_length = 0.04;

        /**
         * @brief the length of the markers,it can be provided in any unit, having in mind that the estimated pose for
         * this board would be measured in the same units (usually meters are used)
         */
        Scalar marker_length = 0.02;

        /**
         * @brief whether convert id for guangqi EOL that customized pattern (guangi Charuco board is truncated a large
         * board and take part of it)
         * @date 2021-10-18
         * @note X3v project
         */
        bool_t is_id_pattern_for_guangqi = false;

    };  // ChArUcobParameter

    /**
     * @brief  chessboard parameter
     */
    struct ChessboardParameter
    {
        /**
         * @brief interior number of row corners.
         */
        uint8_t corner_rows = 1U;

        /**
         * @brief interior number of column corners.
         */
        uint8_t corner_columns = 4U;

        /**
         * @brief the roi is half image of cols offset, unit: pixel
         */
        Scalar roi_cols_offset = Scalar(0.0);

        /**
         * @brief the roi is half image of rows offset, unit: pixel
         */
        Scalar roi_rows_offset = Scalar(0.0);

    };  // ChessboardParameter

    /**
     * @brief Parameters
     */
    struct Parameters
    {
        /**
         * @brief Chessboard Parameter
         */
        ChessboardParameter chessboard_param;

        /**
         * @brief charucob Parameter
         */
        ChArUcobParameter charucob_param;

        /**
         * @brief algorithm param
         */
        AlgorithmParameters algorithm_param;

        /**
         * @brief detect minimum point num
         */
        Scalar detect_minimum_point_num = 8;

        /**
         * @brief whether show debug information and intermediate result
         */
        bool_t verbose = false;

    };  // Parameters

    /**
     * @brief Disable default constructor
     */
    EOLWideCameraCalibration() : Base()
    {
    }

    /**
     * @brief Constructor
     * @param[in] chessboard_db  Shared pointer of ChessboardDatabase, which should be generated using
     *                         the specified application "generate_chessboard_database", for details
     *                         information please refer to it's documentation.
     * @param[in] source_images Source images, sufficient number of Chessboard should be contained.
     * @param[in] camera_model Camera lens model, currently only PINHOLE and FISHEYE are supported,
     *                         other types are not supported!
     * @param[in] parameters calibration algorithm parameters
     *
     * @throw if the camera model is not FISHEYE, throw
     */
    EOLWideCameraCalibration(ChessboardDatabasePtr const& chessboard_db, std::vector<Image> const& source_images,
                             CameraModel const& camera_model, Parameters const& parameters);

    /**
     * @brief Constructor
     * @param[in] charucob_db  Shared pointer of ChArUcobDatabaseDatabase, which should be generated using
     *                         the specified application "generate_ChArUcobDatabase_database", for details
     *                         information please refer to it's documentation.
     * @param[in] camera_model Camera lens model, currently only PINHOLE and FISHEYE are supported,
     *                         other types are not supported!
     * @param[in] source_images Source images, sufficient number of ChArUcobDatabase should be contained.
     * @param[in] parameters calibration algorithm parameters
     *
     * @throw if the camera model is not FISHEYE, throw
     */
    EOLWideCameraCalibration(ChArUcobDatabasePtr const& charucob_db, CameraModel const& camera_model,
                             std::vector<Image> const& source_images, Parameters const& parameters);

    /**
     * @brief Destruction
     */
    virtual ~EOLWideCameraCalibration()
    {
    }

    /**
     * @brief Set the Chessboard Database object
     *
     * @param[in] chessboard_db chessboard database
     */
    void SetChessboardDatabase(ChessboardDatabasePtr const& chessboard_db)
    {
        chessboard_db_ = chessboard_db;
        tag_type_      = TagType::Chessboard;
    }

    /**
     * @brief Set the ChArUcob Database object
     *
     * @param[in] charucob_db ChArUcob database
     */
    void SetChArUcobDatabase(ChArUcobDatabasePtr const& charucob_db)
    {
        charucob_db_ = charucob_db;
        tag_type_    = TagType::ChArUcob;
    }

    /**
     * @brief Set the Parameters object
     *
     * @param[in] params parameters
     */
    void SetParameters(Parameters const& params)
    {
        params_ = params;
    }

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
     * @brief Save the fisheye intrinsic file to the specified path.
     * @param[in] output_path The path to which the file should be written.
     * @param[in] camera_intrinsic camera's intrinsic
     * @note Currently, only absolute paths(output_path) are supported.
     */
    void SaveFisheyeIntrinsic(std::string const& output_path, FisheyeIntrinsic const& camera_intrinsic) const;

    /**
     * @brief Get fisheye intrinsic
     */
    FisheyeIntrinsic GetFisheyeIntrinsic() const
    {
        return fisheye_intrinsic_;
    }

    /**
     * @brief Interface function to calibrate camera intrinsic and extrinsic.
     * @return True if the calibrated algorithm is successfully; otherwise, false.
     * @throw if calibration failed, throw log information
     */
    virtual bool_t Compute() override;

protected:
    /**
     * @brief Process source image to get associations between 2d points and 3d points, the
     *        results obtained will be used for subsequent pose estimation.
     * @param[in] source_images Origin images.
     * @param[in] verbose Whether output detailed log information default value is false.
     * @return a set of 2D-3D corresponding points.
     */
    Correspondence processImages(std::vector<Image> const& source_images, TagType const& tag_type,
                                 bool_t verbose = false);
    /**
     * @brief Get the Correspondence By Chessboard object
     *
     * @param gray_image
     * @param rgb_image
     * @param chessboard_db
     * @param params
     * @param tag_type
     * @return a set of 2D-3D corresponding points.
     */
    Correspondence getCorrespondenceByChessboard(cv::Mat const& gray_image, cv::Mat const& rgb_image,
                                                 ChessboardDatabasePtr const& chessboard_db, Parameters const& params,
                                                 TagType const& tag_type);

    /**
     * @brief Get the Correspondence By ChArUcob object
     *
     * @note https://docs.opencv.org/3.4/df/d4a/tutorial_charuco_detection.html
     *
     * @param gray_image
     * @param rgb_image
     * @param charucob_db
     * @param params
     * @param tag_type
     * @return a set of 2D-3D corresponding points.
     */
    Correspondence getCorrespondenceByChArUcob(cv::Mat const& gray_image, cv::Mat const& rgb_image,
                                               ChArUcobDatabasePtr const& charucob_db, Parameters const& params);

    /**
     * @brief Init camera extrinsic corresponding to image using pnp.
     * @param[in] obj_points Vector of corresponding object points.
     * @param[in] img_points Vector of image points in the image coordinate.
     * @param[in] origin_extrinsic initial value of extrinsic
     * @return external parameter which solved by PnP algorithm.
     */
    Extrinsic computeExtrinsicWithPnP(std::vector<Point3> const& obj_points, std::vector<Point2> const& img_points,
                                      Extrinsic const& origin_extrinsic) const;

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
     * @param[in] intrinsic intrinsic.
     * @return reprojection error.
     */
    Scalar analyseError(Pose3 const& cTw, FisheyeIntrinsic const& intrinsic) const;

    /**
     * @brief Project 3D points to the image plane given intrinsic and extrinsic parameters.
     *        will be used to evaluate the reprojection error.
     * @param[in] object_point 3D point in the world coordinate system.
     * @param[in/out] project_point image points(in image plane).
     * @param[in] cTw camera pose, world to camera.
     * @param[in] intrinsic intrinsic.
     */
    Point2 projectPoint(Point3 const& object_point, Pose3 const& cTw, FisheyeIntrinsic const& intrinsic) const;

    /**
     * @brief convert detected Charuco IDs to new id for guangi EOL
     *         guangi Charuco board is truncated a large board and take part of it)
     * @date 2021-10-18
     * @note X3v project
     *
     * @param charuco_ids
     * @param charuco_corners
     */
    CharucoIDsAndCorners convertCharucoIDs(std::vector<int> const&         charuco_ids,
                                           std::vector<cv::Point2f> const& charuco_corners) const;

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
                                Vector5 const& camera_d) const override
    {
        (void)object_point;
        (void)cTw;
        (void)camera_k;
        (void)camera_d;
        LOG(INFO) << "NOT implementation";

        return Point2();
    }

    /**
     * @brief Analyse calibration error by reprojection error.
     * @param[in] cTw Camera pose, pose of world frame in camera frame.
     * @param[in] camera_k Camera intrinsic matrix should be
     *            \f$A = \vecthreethree{f_x}{0}{c_x}{0}{f_y}{c_y}{0}{0}{1}\f$.
     * @param[in] camera_d Input vector of distortion coefficients, shoud be
     *            \f$(k_1, k_2, p_1, p_2[, k_3[, k_4, k_5, k_6)\f$.
     */
    virtual Scalar analyseError(Pose3 const& cTw, Matrix3 const& camera_k, Vector5 const& camera_d) const override
    {
        (void)cTw;
        (void)camera_k;
        (void)camera_d;
        LOG(INFO) << "NOT implementation";

        return -1;
    }

protected:
    /**
     * @brief pointer of chessboard database
     *
     */
    ChessboardDatabasePtr chessboard_db_;

    /**
     * @brief pointer of harucob database
     *
     */
    ChArUcobDatabasePtr charucob_db_;

    /**
     * @brief fisheye intrinsic
     *
     */
    FisheyeIntrinsic fisheye_intrinsic_;

    /**
     * @brief  parameters
     */
    Parameters params_;

};  // EOLWideCameraCalibration

/**
 * @}
 *
 */

}  // namespace camera

}  // namespace calibration

}  // namespace holo

#endif /* ----- #ifndef HOLO_CALIBRATION_CAMERA_FIELD_EOL_FISHEYE_CAMERA_CALIBRATION_H_  ----- */
