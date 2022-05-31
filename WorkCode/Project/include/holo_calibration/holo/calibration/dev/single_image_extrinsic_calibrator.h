/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file single_image_extrinsic_calibrator.h
 * @brief Class for extrinsic calibration with single image
 * @author Shuaijie Li @ lishuaijie@holomatic.com
 * @date 2022-02-11
 */

#ifndef HOLO_CALIBRATION_DEV_SINGLE_IMAGE_EXTRINSIC_CALIBRATOR_H_
#define HOLO_CALIBRATION_DEV_SINGLE_IMAGE_EXTRINSIC_CALIBRATOR_H_

#include <holo/calibration/dev/common_function.h>
#include <holo/calibration/dev/common_types.h>

namespace holo
{
namespace calibration
{
namespace camera
{
/**
 * @addtogroup camera
 * @{
 */

/**
 * @brief this class aims to compute camera pose with single image after the intrinsic is calibrated
 * @details 1. do 2d-3d data association with pattern detection and database
 *          2. compute initial pose with PnP
 *          3. optimize with PoseOnlyUnit3Factor
 */
class SingleImageExtrinsicCalibrator
{
public:
    using PatternDataBase    = AprilTagDatabase;
    using PatternDataBasePtr = AprilTagDatabase::Ptr;

    /**
     * @brief optimization problem
     */
    struct Problem
    {
        GTNonlinearFactorGraph graph;   ///< factor graph containes all the factor
        GTValues               values;  ///< values contains optimization variables

    };  // Problem

    /**
     * @brief constructor
     *
     * @param[in] database_ptr shared pointer of the pattern database
     * @param[in] tolerance projection error tolerance to judge whether the calibration is successful [unit: pixel]
     * @param[in] noise_sigmas noise sigmas for the corner detection [unit: pixel]
     * @param[in] verbose whether output logs in details
     */
    SingleImageExtrinsicCalibrator(PatternDataBasePtr const& database_ptr, Scalar const tolerance = 2.0,
                                   GTVector2 const& noise_sigmas = GTVector2(1.0, 1.0), bool_t const verbose = false);

    /**
     * @brief destructor
     */
    ~SingleImageExtrinsicCalibrator();

    /**
     * @brief calibrate the extrinsic with the given data
     *
     * @param[in] src_image source image
     * @param[in] intrinsic_ptr shared pointer of the intrinsic corresponding to the source image
     * @param[in] fov field of view in horizontal direction of the camera [unit: degree]
     * @param[in] location_pattern_type the location and type of the pattern, reserved variable which is useless
     * currently
     * @param[in] roi region of interest of the source image, whose size is same as source image. its format is CV_8UC1,
     * the element is 0[not interest] or 255[interest]
     *
     * @return std::pair<bool_t, Pose3> the calibration is successful if the first is true, otherwise failed
     * the second is the extrinsic of camera frame in pattern frame
     */
    std::pair<bool_t, Pose3> Run(CvMat const& src_image, std::shared_ptr<CameraIntrinsicBase> const& intrinsic_ptr,
                                 Scalar const fov = 120.0, uint16_t const location_pattern_type = 0.0,
                                 CvMat const& roi = CvMat()) const;

    /**
     * @brief do 3D-2D data association
     *
     * @param[in] src_image source image
     * @param[in] location_pattern_type the location and type of the pattern, reserved variable which is useless
     * currently
     * @param[in] roi region of interest of the source image, whose size is same as source image. its format is CV_8UC1,
     * the element is 0[not interest] or 255[interest]
     *
     * @return 3D-2D correspondence
     */
    std::vector<PointCorrespondence> createPointCorrespondence(CvMat const&   src_image,
                                                               uint16_t const location_pattern_type,
                                                               CvMat const&   roi) const;

    /**
     * @brief compute the initial extrinsic with the 3D-2D correspondence
     *
     * @param[in] multi_point_correspondence 3D-2D correspondence
     * @param[in] intrinsic_ptr shared pointer of the intrinsic corresponding to the source image
     * @param[in] fov field of view in horizontal direction of the camera [unit: degree]
     *
     * @return std::pair<bool_t, Pose3> the initialization is successful if the first is true, otherwise failed
     * the second is the extrinsic of camera frame in pattern frame
     */
    std::pair<bool_t, Pose3> computeInitialExtrinsic(std::vector<PointCorrespondence> const& multi_point_correspondence,
                                                     std::shared_ptr<CameraIntrinsicBase> const& intrinsic_ptr,
                                                     Scalar const                                fov) const;

    /**
     * @brief create optimization problem
     *
     * @param[in] multi_point_correspondence 3D-2D correspondence
     * @param[in] intrinsic_ptr shared pointer of the intrinsic corresponding to the source image
     * @param[in] initial_wTc initial extrinsic of camera frame in pattern frame
     * @param[in] extrinsic_key key of the extrinsic
     *
     * @return optimization problem
     */
    Problem createProblem(std::vector<PointCorrespondence> const&     multi_point_correspondence,
                          std::shared_ptr<CameraIntrinsicBase> const& intrinsic_ptr, GTPose3 const& initial_wTc,
                          GTKey const extrinsic_key) const;

    /**
     * @brief optimize the extrinsic
     *
     * @param[in] problem optimization problem
     *
     * @return the optimized values
     */
    GTValues optimize(Problem const& problem) const;

    /**
     * @brief evaluate the average projection error in pixel
     *
     * @param[in] multi_point_correspondence 3D-2D correspondence
     * @param[in] intrinsic_ptr shared pointer of the intrinsic corresponding to the source image
     * @param[in] wTc extrinsic of camera frame in pattern frame
     *
     * @return average projection error in pixel
     */
    Scalar evaluateError(std::vector<PointCorrespondence> const&     multi_point_correspondence,
                         std::shared_ptr<CameraIntrinsicBase> const& intrinsic_ptr, Pose3 const& wTc) const;

protected:
    PatternDataBasePtr database_ptr_;  ///< pattern database contains 3d position of pattern corners
    Scalar    tolerance_;  ///< projection error tolerance to judge whether the calibration is successful [unit: pixel]
    GTVector2 noise_sigmas_;  ///< noise sigmas for the corner detection [unit: pixel]
    bool_t    verbose_;       ///< whether output logs in details

};  // SingleImageExtrinsicCalibrator

/**
 * @}
 */
}  // namespace camera
}  // namespace calibration
}  // namespace holo
#endif  // HOLO_CALIBRATION_DEV_SINGLE_IMAGE_EXTRINSIC_CALIBRATOR_H_

