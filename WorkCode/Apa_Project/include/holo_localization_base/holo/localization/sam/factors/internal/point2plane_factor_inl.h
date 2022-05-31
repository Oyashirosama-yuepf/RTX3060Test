/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file plane_factor_inl.h
 * @brief This header file defines point2plane factor
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2021-03-31
 */
#ifndef HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_POINT2PLANE_FACTOR_INL_H_
#define HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_POINT2PLANE_FACTOR_INL_H_

#include <gtsam/geometry/Point3.h>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/inference/Key.h>
#include <gtsam/linear/NoiseModel.h>
#include <gtsam/nonlinear/NonlinearFactor.h>

namespace holo
{
namespace localization
{
namespace internal
{
/**
 * @addtogroup sam
 * @{
 *
 */

/**
 * @brief Point2Plane factor defines point to plane distance error
 * @details error = tgt_normal^T * (T_wb.TransformTo(pt_src) - pt_tgt)
 */
class Point2PlaneFactor : public gtsam::NoiseModelFactor1<gtsam::Pose3>
{
public:
    /**
     * @brief Define some common type
     */
    using Base     = gtsam::NoiseModelFactor1<gtsam::Pose3>;
    using Ptr      = boost::shared_ptr<Point2PlaneFactor>;
    using ConstPtr = boost::shared_ptr<const Point2PlaneFactor>;

    /**
     * @brief Construct a new Plane Factor object
     *
     * @param[in] pose_key key of the pose to be optimized
     * @param[in] source_pt source point in source frame, eg. body
     * @param[in] target_pt target point in target frame, eg. world
     * @param[in] target_normal target point normal vector
     * @param[in] noise_model noise model for measurement
     */
    Point2PlaneFactor(gtsam::Key const& pose_key, gtsam::Point3 const& source_pt, gtsam::Point3 const& target_pt,
                      gtsam::Vector3 const& target_normal, gtsam::SharedNoiseModel const& noise_model);

    /**
     * @brief Destroy the Plane Factor object
     *
     */
    virtual ~Point2PlaneFactor() noexcept;

    /**
     * @brief evaluate error and compute jacobian matrix
     *
     * @param[in] pose the pose to be optimized which can transform source point to target frame
     * @param[out] H jacobian of error w.r.t pose
     * @return gtsam::Vector point to plane error
     */
    virtual gtsam::Vector evaluateError(gtsam::Pose3 const&             pose,
                                        boost::optional<gtsam::Matrix&> H = boost::none) const override;

private:
    gtsam::Point3  source_pt_;      ///< source point eg. point in body frame
    gtsam::Point3  target_pt_;      ///< target point eg. point in world frame
    gtsam::Vector3 target_normal_;  ///< target point normal vector

};  // Point2PlaneFactor
/**
 * @}
 *
 */
}  // namespace internal
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_POINT2PLANE_FACTOR_INL_H_
