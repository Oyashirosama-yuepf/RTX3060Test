/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file line_projection_factor.h
 * @brief This header file defines line projection factor.
 * @author MaYufei(mayufei@holomatic.com)
 * @date "2022-01-11"
 */
#ifndef HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_LINE_PROJECTION_FACTOR_H_
#define HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_LINE_PROJECTION_FACTOR_H_

#include <gtsam/geometry/Cal3_S2.h>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/nonlinear/NonlinearFactor.h>

#include <holo/localization/sam/vision/line/orthonormal_line.h>
#include <holo/localization/sam/vision/line/plucker_line.h>

namespace holo
{
namespace localization
{
namespace internal
{
class LineProjectionFactor : public gtsam::NoiseModelFactor2<gtsam::Pose3, GTOrthonormalLine>
{
public:
    /**
     * @brief define some handy types
     *
     */
    using GTScalar     = double;
    using GTVector     = gtsam::Vector;
    using GTVector2    = gtsam::Vector2;
    using GTVector3    = gtsam::Vector3;
    using GTVector4    = gtsam::Vector4;
    using GTMatrix3    = gtsam::Matrix3;
    using GTPoint3     = gtsam::Point3;
    using GTPose3      = gtsam::Pose3;
    using GTUnit3      = gtsam::Unit3;
    using GTKey        = gtsam::Key;
    using GTCal3       = gtsam::Cal3_S2;
    using GTNoiseModel = gtsam::SharedNoiseModel;
    using Base         = gtsam::NoiseModelFactor2<GTPose3, GTOrthonormalLine>;

    /**
     * @brief measurenet of line
     *
     */
    struct Measurement
    {
        GTUnit3 rays[2u];
    };

    /**
     * @brief default constructor
     *
     */
    LineProjectionFactor() noexcept;

    /**
     * @brief Construct a new Line Projection Factor object
     *
     * @param[in] pose_key  pose key
     * @param[in] orthonormal_line_key orthonormal line key
     * @param[in] noise_model noise model
     * @param[in] measured measured rays
     * @param[in] bTc pose from camera frame to body frame
     * @param[in] K pinhole camera intrinsic matrix
     */
    LineProjectionFactor(GTKey const& pose_key, GTKey const& orthonormal_line_key, GTNoiseModel const& noise_model,
                         Measurement const& measured, GTPose3 const& bTc, GTCal3::shared_ptr const& K = nullptr);

    /**
     * @brief Destroy the Line Projection Factor object
     *
     */
    virtual ~LineProjectionFactor() noexcept
    {
    }

    /**
     * @brief Get the Extrinsic object
     *
     * @return GTPose3
     */
    GTPose3 const& GetExtrinsic();

    /**
     * @brief Get the Measurement object
     *
     * @return Measurement
     */
    Measurement const& GetMeasurement();

    /**
     * @brief Get the Camera Matrix object
     *
     * @return GTCal3
     */
    GTCal3 const& GetCameraMatrix();

    /**
     * @brief evaluate error between detected line and re-projected line
     *
     * @param[in] wTb pose from body frame to world frame
     * @param[in] orthonormal_line orthonormal line
     * @param[in] H1 Jacobian of error w.r.t. wTb
     * @param[in] H2 Jacobian of error w.r.t. orthonormal line
     * @return GTVector
     */
    virtual GTVector evaluateError(GTPose3 const& wTb, GTOrthonormalLine const& orthonormal_line,
                                   boost::optional<gtsam::Matrix&> H1 = boost::none,
                                   boost::optional<gtsam::Matrix&> H2 = boost::none) const;

    /**
     * @brief evaluate angle error between two planes. One plane is determined by camera optical center and detected
     * line, the other is determined by camera optical center and re-projected line
     *
     * @param[in] wTb pose from body frame to world frame
     * @param[in] orthonormal_line orthonormal line
     * @param[in] H1 Jacobian of plane error w.r.t. wTb
     * @param[in] H2 Jacobian of plane error w.r.t. orthonormal line
     * @return GTVector
     */
    GTVector evaluatePlaneError(GTPose3 const& wTb, GTOrthonormalLine const& orthonormal_line,
                                boost::optional<gtsam::Matrix&> H1 = boost::none,
                                boost::optional<gtsam::Matrix&> H2 = boost::none) const;

    /**
     * @brief evaluate distance error between detected endpoint and re-projected line
     *
     * @param[in] wTb pose from body frame to world frame
     * @param[in] orthonormal_line orthonormal line
     * @param[in] H1 Jacobian of distance error w.r.t. wTb
     * @param[in] H2 Jacobian of distance error w.r.t. orthonormal line
     * @return GTVector
     */
    GTVector evaluatePointToLineError(GTPose3 const& wTb, GTOrthonormalLine const& orthonormal_line,
                                      boost::optional<gtsam::Matrix&> H1 = boost::none,
                                      boost::optional<gtsam::Matrix&> H2 = boost::none) const;

    /**
     * @brief project PluckerLine to image plane
     *
     * @param[in] K camera intrinsic matrix
     * @param[in] Lc plucker line in camera frame
     * @return GTVector3
     */
    GTVector3 projectPluckerLineToImagePlane(GTMatrix3 const& K, GTPluckerLine const& Lc,
                                             gtsam::OptionalJacobian<3u, 6u> H) const;

protected:
    Measurement        measured_;  ///< measured rays
    GTPose3            bTc_;       ///< transformation from camera frame to body frame
    GTCal3::shared_ptr K_;         ///< smart pointer of camera intrinsic matrix
};
}  // namespace internal

}  // namespace localization
}  // namespace holo

#endif