/*
 * Copyright (C) HoloMatic Technology (Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ocam_calibrator.h
 * @brief Class for omnidirectional camera calibration
 * @author cuijiashuo@holomatic.com (Jiashuo Cui)
 * @date 2021-10-15
 */

#ifndef HOLO_CALIBRATION_DEV_OCAM_CALIBRATOR_H_
#define HOLO_CALIBRATION_DEV_OCAM_CALIBRATOR_H_

#include <holo/calibration/dev/camera_intrinsic_calibration_base.h>
#include <holo/calibration/dev/common_types.h>
#include <holo/calibration/dev/factors/ocam_intrinsic_factor.h>
#include <holo/localization/sam/sam.h>
#include <holo/localization/sam/type_converter.h>
#include <holo/localization/vision/common/image_undistorter.h>
#include <holo/numerics/eigen_solver.h>

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
 * @brief A class aims at calibrating the extrinsic (camera' pose, from world frame to camera frame) and intrinsic
 *        (c, d, e, cx, cy, a_0, a_1, ..., a_taylor) of the omnidirectional camera via a image sequence.
 *
 */
class OcamCalibrator : public CameraIntrinsicCalibrationBase
{
public:
    using Base = CameraIntrinsicCalibrationBase;

    /**
     * @brief Default constructor
     *
     */
    OcamCalibrator() : Base(), is_intrinsic_initialized_(false)
    {
    }

    /**
     * @brief Advanced constructor
     *
     * @param[in] apriltag_db  Shared pointer of AprilTagDatabase, which should be generated using
     *                         the specified application "generate_apriltag_database", please see it's
     *                         documentation for details.
     * @param[in] camera_model Camera len models, currently PINHOLE, FISHEYE and OMNIDIRECTIONAL are supported. But in
     *                         this class the camera len model should be OMNIDIRECTIONAL!
     * @param[in] sensor_id A sensor-id is consist of three parts: Category, Model and Location.
     * @param[in] verbose Whether print log information.
     * @param[in] visualize Whether visualize crucial processes.
     * @param[in] taylor_order Order of the inverse projection polynomial.
     * @param[in] is_plane_mode Whether all calibration objects on one plane.
     * @throw LOG(ERROR), if the camera model is not OMNIDIRECTIONAL.
     */
    OcamCalibrator(AprilTagDatabasePtr const apriltag_db, Model const& camera_model,
                   holo::common::SensorId const& sensor_id, bool_t const verbose, bool_t const visualize,
                   uint16_t const taylor_order, bool_t const is_plane_mode);

    /**
     * @brief Destructor
     *
     */
    ~OcamCalibrator() noexcept override = default;

    /**
     * @brief Set the initial value of the omnidirectional camera intrinsic.
     *
     * @param[in] intrinsic Initial intrinsic
     */
    void SetInitOcamIntrinsic(OmnidirectionalIntrinsic const& intrinsic)
    {
        intrinsic_                = intrinsic;
        is_intrinsic_initialized_ = true;
    }

    /**
     * @brief Get omnidirectional camera intrinsic.
     *
     * @return Omnidirectional intrinsic type
     */
    OmnidirectionalIntrinsic GetOcamIntrinsic() const
    {
        return intrinsic_;
    }

    /**
     * @brief Set order of the inverse projection polynomial.
     *
     * @param taylor_order Order of the inverse projection polynomial.
     */
    void SetTaylorOrder(uint16_t taylor_order)
    {
        taylor_order_ = taylor_order;
    }

    /**
     * @brief Set the measure noise (unit: pixel) of 2D corner points.
     *
     * @param[in] noise_measured Measure noise
     */
    void SetMeasureNoise(Scalar noise_measured)
    {
        noise_measured_ = noise_measured;
    }

    /**
     * @brief Set the threshold of 'Cauchy' robust loss function.
     *
     * @param[in] robust_loss_threshold Threshold
     */
    void SetRobustLoss(Scalar robust_loss_threshold)
    {
        robust_loss_threshold_ = robust_loss_threshold;
    }

    /**
     * @brief Set the error tolerance of calibration
     *
     * @param[in] error_tolerance Error tolerance
     */
    void SetErrorTolerance(Scalar error_tolerance)
    {
        error_tolerance_ = error_tolerance;
    }

private:
    /**
     * @brief The interface for performing omnidirectional camera calibration.
     *
     * @param[in] multi_images Input image sequence
     * @return True if the calibration algorithm is successful; otherwise, false.
     */
    bool_t run(std::vector<CvMat> const& multi_images) override;

    /**
     * @brief Initialize both extrinsic and intrinsic for omnidirectional camera.
     *
     * @param[in] correspondences_seq A sequence of 2D-3D corresponding points.
     * @return Extrinsic with status and intrinsic.
     */
    std::pair<std::vector<std::pair<bool_t, Pose3>>, OmnidirectionalIntrinsic>
    initializeExtrinsicAndIntrinsic(std::vector<std::vector<PointCorrespondence>> const& correspondences_seq);

    /**
     * @brief Initial omnidirectional camera Extrinsic via DLT in non-plane mode.
     *
     * @param[in] multi_correspondences A set of 2D-3D corresponding points.
     * @return pair, Extrinsic and it status.
     */
    std::pair<bool_t, Pose3> computeExtrinsicByDLT(std::vector<PointCorrespondence> const& multi_correspondences) const;

    /**
     * @brief Initial omnidirectional camera Extrinsic via DLT in plane mode.
     *
     * @param[in] multi_correspondences A set of 2D-3D corresponding points.
     * @return pair, Extrinsic and it status.
     */
    std::pair<bool_t, Pose3>
    computeExtrinsicByDLTPlaneMode(std::vector<PointCorrespondence> const& multi_correspondences) const;

    /**
     * @brief Construct coefficient matrix according to the first two row of Eq.(5) ℹn paper
     *        'Improved Wide-Angle, Fisheye and Omnidirectional Camera Calibration'.
     *
     * @note Only for one image.
     * @param[in] image_points A vector of image points.
     * @param[in] object_points A vector of object points.
     * @param[in] cTw Camera pose, from world coordinate to camera coordinate.
     * @param[in] taylor_order Order of the inverse projection polynomial.
     * @return pair, Coefficient matrix and vector b
     */
    std::pair<Eigen::MatrixXd, Eigen::VectorXd> constructSubMatrix(std::vector<CvPoint2f> const& image_points,
                                                                   std::vector<CvPoint3f> const& object_points,
                                                                   Pose3 const& cTw, uint16_t const taylor_order) const;

    /**
     * @brief Initialize distort coefficient according to the first two row of Eq.(5) ℹn paper
     *        'Improved Wide-Angle, Fisheye and Omnidirectional Camera Calibration'.
     * @note For all images.
     *
     * @param[in] correspondences_seq A sequence of 2D-3D corresponding points.
     * @param[in] extrinsic A set of camera pose and its status.
     * @param[in] taylor_order Order of the inverse projection polynomial.
     * @return Distortion coefficients
     */
    numerics::VectorXd computeDistortionCoefficients(
        std::vector<std::vector<PointCorrespondence>> const& correspondences_seq,
        std::vector<std::pair<bool_t, Pose3>> const& extrinsic, uint16_t const taylor_order) const;

    /**
     * @brief Obtain projection polynomial via numerical method.
     *
     * @note Inverse projection polynomial must be known.
     * @param[in] cx x-coordinate of principle point
     * @param[in] cy y-coordinate of principle point
     * @param[in] image_size Image size
     * @param[in] tolerance Tolerance of fitting error.
     * @param[in] inv_poly Inverse projection polynomial of omnidirectional camera.
     * @return Projection polynomial
     */
    numerics::VectorXd computePolynomialParameters(Scalar const cx, Scalar const cy, CvSize const& image_size,
                                                   Scalar const tolerance, numerics::VectorXd const& inv_poly) const;

    /**
     * @brief Automatically called by function run(), performing factor graph optimization
     *        implemented by the GTSAM library.
     *
     * @param[in][out] init_intrinsic Input initial camera intrinsic and output optimized camera intrinsic.
     * @param[in][out] init_extrinsic Input initial camera extrinsic and output optimized camera extrinsic.
     * @return True, if the optimization algorithm is successful; otherwise, false.
     */
    bool_t optimize(OmnidirectionalIntrinsic& init_intrinsic, std::vector<std::pair<bool_t, Pose3>>& init_extrinsic);

    /**
     * @brief Initial optimization parameters from camera intrinsic.
     *
     * @note Now, OmnidirectionalIntrinsic class doesn't have 'Get' method, so vector_intrinsic_ should be
     *       initialized simultaneously.
     * @param[in] initial_intrinsic Initialized camera intrinsic.
     * @return Camera intrinsic in GTSAM form.
     */
    GTVectorXd initializeOptimizationParametersFromIntrinsic(OmnidirectionalIntrinsic const& initial_intrinsic) const;

    /**
     * @brief Update optimization parameters to intrinsic.
     *
     * @note Now, OmnidirectionalIntrinsic class doesn't have 'Get' method, so vector_intrinsic_ should be
     *       updated simultaneously.
     * @param[in] intrinsic Intrinsic after optimization in GTSAM form.
     * @return Optimized camera intrinsic.
     */
    OmnidirectionalIntrinsic updateOptimizationParametersToIntrinsic(GTVectorXd const& intrinsic);

    /**
     * @brief Initialize extrinsic vis PNP algorithm.
     *
     * @note Some extrinsic could not be initialized by DLT algorithm, so we try to use PNP algorithm.
     * @param[in] multi_correspondences A set of 2D-3D corresponding points.
     * @param[in] intrinsic Camera intrinsic
     * @param[in][out] extrinsic Camera extrinsic
     * @return Camera pose and its status.
     */
    std::vector<std::pair<bool_t, Pose3>> initCameraPoses(
        std::vector<std::vector<PointCorrespondence>> const& correspondences_seq,
        OmnidirectionalIntrinsic const& intrinsic, std::vector<std::pair<bool_t, Pose3>>& origin_cTw_with_status) const;

private:
    ///@brief Shared pointer of AprilTagDatabase
    AprilTagDatabase::Ptr apriltag_db_;

    /**
     * @brief Camera Intrinsic initialized flag. True, if the camera intrinsic
     *        has been initialized, otherwise false.
     */
    bool_t is_intrinsic_initialized_;

    ///@brief Noise of measurement [unit-less]
    Scalar noise_measured_ = 0.5;

    ///@brief The threshold of 'Cauchy' loss function
    Scalar robust_loss_threshold_ = std::sqrt(6.251);

    ///@brief Tolerance of projection error after optimization.
    Scalar error_tolerance_ = 3.0;

    ///@brief Extrinsic, refer to camera poses (from world frame to camera frame), with status.
    std::vector<std::pair<bool_t, Pose3>> extrinsic_;

    ///@brief Omnidirectional camera intrinsic (c, d, e, c_x, c_y, a_0, a_1, ..., a_taylor).
    OmnidirectionalIntrinsic intrinsic_;

    uint16_t taylor_order_ = 4u;  ///< Order of the inverse projection polynomial.
};
/**
 * @}
 */
}  // namespace camera
}  // namespace calibration
}  // namespace holo

#endif  // HOLO_CALIBRATION_DEV_OCAM_CALIBRATOR_H_
