/*
 * Copyright (C) HoloMatic Technology (Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file fisheye_calibrator.h
 * @brief Class for fish-eye camera calibration
 * @author cuijiashuo@holomatic.com (Jiashuo Cui)
 * @date 2021-08-19
 */

#ifndef HOLO_CALIBRATION_DEV_FISHEYE_CALIBRATOR_H_
#define HOLO_CALIBRATION_DEV_FISHEYE_CALIBRATOR_H_

#include <holo/calibration/dev/camera_intrinsic_calibration_base.h>
#include <holo/calibration/dev/factors/fisheye_intrinsic_factor.h>
#include <holo/localization/sam/sam.h>
#include <holo/localization/sam/type_converter.h>

namespace holo
{
namespace calibration
{
namespace camera
{
using namespace holo::localization;
/**
 * @addtogroup camera
 * @{
 */

/**
 * @brief A class aims at calibrating the extrinsic (camera' pose, from world frame to camera frame)
 *        and intrinsic (f_x, f_y, c_x, c_y, k_1, k_2, k_3, k_4) of the fisheye camera via a image sequence.
 * @note Prior information of intrinsic and extrinsic is required.
 */
class FisheyeCalibrator : public CameraIntrinsicCalibrationBase
{
public:
    using Base = CameraIntrinsicCalibrationBase;
    /**
     * @brief Disable default constructor
     */
    FisheyeCalibrator() : Base(), is_intrinsic_initialized_(false)
    {
    }

    /**
     * @brief Constructor
     * @param[in] apriltag_db  Shared pointer of AprilTagDatabase, which should be generated using
     *                         the specified application "generate_apriltag_database", please see it's
     *                         documentation for details.
     * @param[in] camera_model Camera len models, currently PINHOLE, FISHEYE and OCAM are supported. But in this class
     *                         the camera len model should be FISHEYE!
     * @param[in] sensor_id A sensor-id is consist of three parts: Category, Model and Location.
     * @param[in] verbose Whether print log information.
     * @param[in] visualize Whether visualize crucial processes.
     * @param[in] is_plane_mode Whether all calibration objects on one plane.
     * @throw throw, if the camera model is not FISHEYE.
     */
    FisheyeCalibrator(AprilTagDatabase::Ptr const apriltag_db, Model const& camera_model,
                      holo::common::SensorId const& sensor_id, bool_t const verbose, bool_t const visualize,
                      bool_t const is_plane_mode);

    /**
     * @brief Destructor
     */
    virtual ~FisheyeCalibrator()
    {
    }

    /**
     * @brief Set the initial value of the camera fisheye intrinsic.
     * @param[in] intrinsic Initial intrinsic.
     */
    void SetInitFisheyeIntrinsic(FisheyeIntrinsic const& intrinsic)
    {
        intrinsic_                = intrinsic;
        is_intrinsic_initialized_ = true;
    }

    /**
     * @brief Get fisheye intrinsic.
     */
    FisheyeIntrinsic GetFisheyeIntrinsic() const
    {
        return intrinsic_;
    }

    void SetMeasureNoise(Scalar noise_measured)
    {
        noise_measured_ = noise_measured;
    }

    void SetRobustLoss(Scalar robust_loss_threshold)
    {
        robust_loss_threshold_ = robust_loss_threshold;
    }

    void SetErrorTolerance(Scalar error_tolerance)
    {
        error_tolerance_ = error_tolerance;
    }

private:
    /**
     * @brief The interface for performing fisheye camera calibration.
     * @param[in] multi_images Input image sequence.
     * @return True if the calibration algorithm is successful; otherwise, false.
     * @throw throw, if there is no initial intrinsic.
     */
    bool_t run(std::vector<CvMat> const& multi_images) override;

    /**
     * @brief Automatically called by function run(), performing factor graph optimization
     *        implemented by the GTSAM library.
     * @return True if the optimization algorithm is successful; otherwise, false.
     */
    bool_t optimize(FisheyeIntrinsic& init_intrinsic, std::vector<std::pair<bool_t, Pose3>>& init_extrinsic) const;

    /**
     * @brief Initialize camera extrinsic via pnp algorithm.
     * @param[in] correspondences_seq A sequence of 2D-3D corresponding points.
     * @param[in] origin_cTw_with_status Initial extrinsic with status.
     * @param[in] use_undistort_point Whether to dedistort the point
     * @return Extrinsic, which solved by PnP algorithm, and its status.
     */
    std::vector<std::pair<bool_t, Pose3>> initCameraPoses(
        std::vector<std::vector<PointCorrespondence>> const& correspondences_seq,
        std::vector<std::pair<bool_t, Pose3>> const& origin_cTw_with_status, bool_t use_undistort_point) const;

    /**
     * @brief Initial optimization parameters from intrinsic.
     * @param[in] initial_intrinsic Initial intrinsic.
     * @return Camera intrinsic in GTSAM form.
     */
    GTVector8 initializeOptimizationParametersFromIntrinsic(FisheyeIntrinsic const& initial_intrinsic) const;

    /**
     * @brief Update optimization parameters to intrinsic.
     * @param[in] camera Intrinsic after optimization (std::vector form).
     * @return Updated camera intrinsic.
     */
    FisheyeIntrinsic updateOptimizationParametersToIntrinsic(GTVector8 const& intrinsic) const;

    /**
     * @brief Init fisheye intrinsic parameters, optional plane mode or non-plane mode.
     * @return Fisheye intrinsic parameters.
     */
    FisheyeIntrinsic initIntrinsic() const;

private:
    ///@brief Shared pointer of AprilTagDatabase
    AprilTagDatabase::Ptr apriltag_db_;

    /**
     * @brief Init intrinsic flag. True if the initial value of
     *        the intrinsic has been set, otherwise false.
     */
    bool_t is_intrinsic_initialized_;

    ///@brief Noise of measurement
    Scalar noise_measured_ = 2.0;

    ///@brief The threshold of Cauchy loss function
    Scalar robust_loss_threshold_ = std::sqrt(5.991);

    ///@brief Tolerance of projection error after optimization.
    Scalar error_tolerance_ = 3.0;

    ///@brief Extrinsic, refer to camera poses (from world frame to camera frame), with status.
    std::vector<std::pair<bool_t, Pose3>> extrinsic_;

    ///@brief Camera intrinsic (f_x, f_y, c_x, c_y, k_1, k_2, k_3, k_4).
    FisheyeIntrinsic intrinsic_;
};
/**
 * @}
 */
}  // namespace camera
}  // namespace calibration
}  // namespace holo

#endif  // HOLO_CALIBRATION_DEV_FISHEYE_CALIBRATOR_H_
