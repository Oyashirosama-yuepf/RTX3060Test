/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file smart_camera_calibration.h
 * @author jiaxing. zhao
 * @brief main function for smart camera calibration
 * @date 2020-08-07
 */

#ifndef HOLO_CALIBRATION_CAMERA_ONLINE_SMART_CAMERA_CALIBRATION_H_
#define HOLO_CALIBRATION_CAMERA_ONLINE_SMART_CAMERA_CALIBRATION_H_

#include <iostream>
#include <memory>

#include <holo/calibration/camera/online/smart_camera_calibration_data_association.h>
#include <holo/calibration/camera/online/smart_camera_calibration_data_container.h>
#include <holo/calibration/common/calibration_base.h>
#include <holo/common/extrinsic.h>
#include <holo/common/intrinsic.h>
#include <holo/localization/backend/factor_graph.h>
#include <holo/localization/backend/factors/projection_line_factor.h>
#include <holo/localization/backend/smoother.h>
#include <holo/localization/common/localization_base.h>
#include <holo/os/tictoc_timer.h>
#include <holo/os/timer.h>

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
 * @brief This class aims at calibrating the extrinsic(rotation) parameters between
 *         smart camera and holo camera that by aligning smart lane output lane in 3D
 *         and holo camera output lane in 2D.
 *
 */
class SmartCameraCalibration : public CalibrationBaseT<SmartCameraDataContainer>
{
public:
    using Container       = SmartCameraDataContainer;
    using Correspondences = SmartCameraDataAssociation::Correspondences;
    using Base            = CalibrationBaseT<Container>;
    using Smoother        = localization::Smoother;
    using Intrinsic       = holo::common::FisheyeIntrinsicT<Scalar>;
    using Extrinsic       = holo::common::ExtrinsicT<Scalar_32_t>;
    // @TODO replace SmartCameraExtrinsicCalibFactor to ProjectionLineFactor
    // using SmartCameraExtrinsicCalibFactor  = holo::localization::SmartCameraExtrinsicCalibFactor;
    // using SmartCameraExtrinsicCalibFactors = holo::localization::SmartCameraExtrinsicCalibFactors;
    using SmartCameraExtrinsicCalibFactor  = holo::localization::ProjectedLineFactor;
    using SmartCameraExtrinsicCalibFactors = holo::localization::ProjectedLineFactors;
    using Pose3Values                      = holo::localization::Pose3Values;
    using Pose3Value                       = holo::localization::Pose3Value;
    using FactorGraph                      = holo::localization::FactorGraph;
    using SmootherState                    = holo::localization::SmootherState;

    /// @brief smart pointer
    using Ptr      = std::shared_ptr<SmartCameraCalibration>;
    using ConstPtr = std::shared_ptr<const SmartCameraCalibration>;

    /**
     * @brief optimized parameters
     */
    struct OptimizedParameters
    {
        /**
         * @brief smoother params
         */
        Smoother::Parameters smoother_params;

        /**
         * @brief noise sigma
         */
        Scalar noise_sigma = Scalar(0.1);

        /**
         * @brief the threshold of huber loss
         */
        Scalar huber_loss_threshold = Scalar(10.0);

        /**
         * @brief is x y z fixed
         */
        bool_t is_xyz_fixed = true;

        /**
         * @brief is roll fixed
         */
        bool_t is_roll_fixed = true;

        /**
         * @brief is pitch fixed
         */
        bool_t is_pitch_fixed = true;

        /**
         * @brief is yaw fixed
         */
        bool_t is_yaw_fixed = false;

        /**
         * @brief verbose
         */
        bool_t verbose = false;

    };  // OptimizedParameters

    /**
     * @brief parameters
     */
    struct Parameters
    {
        /**
         * @brief correspondence threshold dist in image unit is pixel
         */
        Scalar thresh_dist = Scalar(100);

        /**
         * @brief holo camera intrinsic
         */
        Intrinsic intrinsic = Intrinsic();

        /**
         * @brief holo body to camera extrinsic
         */
        Extrinsic cTb = Extrinsic();

        /**
         * @brief ceres optimized parameters
         */
        OptimizedParameters optimized_param;

        /**
         * @brief verbose
         */
        bool_t verbose = false;

    };  // Parameters

    /**
     * @brief disable constructor
     */
    SmartCameraCalibration() = delete;

    /**
     * @brief Construct a new Smart Camera Calibration object
     *
     * @param params
     */
    SmartCameraCalibration(Parameters const& params);

    /**
     * @brief Destroy the Smart Camera Calibration object
     *
     */
    virtual ~SmartCameraCalibration()
    {
    }

    /**
     * @brief compute compensated transformation matrix between pending optimization body and actual body
     *
     * @details HoloCameraImage(u,v) = K_HoloCamera * E_Body_HoloCamera.Inverse() * E_Body_Body' * P_X(sample smart
     * camera), E_Body_Body' is compensated transformation
     * @param correspondences smart camera lane sample points in 3D in body and holo camera lane in 2D image
     * @param params params
     * @param guess compensated transformation E_Body_Body'
     * @return optimized transformation matrix E_Body_Body' and optimized delta_z(z->height from body to
     * ground)
     */
    OptionalT<Pose3Type> Run(Correspondences const& correspondences, Parameters const& params,
                             Pose3Type const& guess = Pose3::Identity());

    /**
     * @brief compute transformation matrix between source and target
     *
     * @return true
     * @return false
     */
    virtual bool_t Compute() override;

    /**
     * @brief container size
     */
    virtual uint8_t GetContainerNum() const override;

    /**
     * @brief function to get container in case we just have one container
     * @note this function is pure virtual functions in base, this class is not used it.
     */
    virtual const Container& GetContainer() const override;

    /**
     * @brief function to get container in case we just have one container
     * @note this function is pure virtual functions in base, this class is not used it.
     */
    virtual Container& GetContainer() override;

    /**
     * @brief function to get the ith container in case we have multiple containers
     * @note this function is pure virtual functions in base, this class is not used it.
     */
    virtual const Container& GetContainer(uint8_t const index) const override;

    /**
     * @brief function to get the ith container in case we have multiple containers
     * @note this function is pure virtual functions in base, this class is not used it.
     */
    virtual Container& GetContainer(uint8_t const index) override;

private:
    /**
     * @brief Create a Smart Camera Factors object
     *
     * @param correspondences
     * @param params
     * @return OptionalT<SmartCameraExtrinsicCalibFactors>
     */
    OptionalT<SmartCameraExtrinsicCalibFactors> createSmartCameraFactors(Correspondences const& correspondences,
                                                                         Parameters const&      params) const;

    /**
     * @brief Create a Pose3 Values object
     *
     * @param guess
     * @return OptionalT<Pose3Values>
     */
    OptionalT<Pose3Values> createPose3Values(Pose3Type const& guess) const;

    // current in this class NOT use it, because of GetContainer() functions are pure virtual functions in base,
    // we need containers.
    std::vector<Container> containers_;

    // parameter
    Parameters params_;

    // fusion smoother
    Smoother::Ptr smoother_;
};

/**
 * @}
 *
 */

}  // namespace camera

}  // namespace calibration

}  // namespace holo

#endif /* ----- #ifndef HOLO_CALIBRATION_CAMERA_ONLINE_SMART_CAMERA_CALIBRATION_H_  ----- */