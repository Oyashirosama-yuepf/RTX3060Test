/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file point2line_factor_inl.h
 * @brief This header file defines point2line factor
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2021-04-23
 */
#ifndef HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_POINT2LINE_FACTOR_INL_H_
#define HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_POINT2LINE_FACTOR_INL_H_

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
 * @brief Point2Line factor defines point to 3d line distance error
 * @details let l1 be line direction, l2 = pose_src * source_pt - target_pt1, error = ||l2.cross(l1)||
 */
class Point2LineFactor : public gtsam::NoiseModelFactor1<gtsam::Pose3>
{
public:
    /**
     * @brief Define some common type
     */
    using Base     = gtsam::NoiseModelFactor1<gtsam::Pose3>;
    using Ptr      = boost::shared_ptr<Point2LineFactor>;
    using ConstPtr = boost::shared_ptr<const Point2LineFactor>;

    /**
     * @brief Construct a new Point2Line Factor object
     *
     * @param[in] pose_key key of the pose to be optimized
     * @param[in] source_pt source point in source frame, eg. body
     * @param[in] target_pt1 the first line point in target frame, eg. world
     * @param[in] target_pt2 the second line point in target frame, eg. world
     * @param[in] noise_model noise model for measurement
     */
    Point2LineFactor(gtsam::Key const& pose_key, gtsam::Point3 const& source_pt, gtsam::Point3 const& target_pt1,
                     gtsam::Point3 const& target_pt2, gtsam::SharedNoiseModel const& noise_model);

    /**
     * @brief Construct a new Point2Line Factor object
     *
     * @param[in] pose_key key of the pose to be optimized
     * @param[in] source_pt source point in source frame, eg. body
     * @param[in] target_pt the first line point in target frame, eg. world
     * @param[in] target_line_dir the target line direction in target frame, eg. world
     * @param[in] noise_model noise model for measurement
     */
    Point2LineFactor(gtsam::Key const& pose_key, gtsam::Point3 const& source_pt, gtsam::Point3 const& target_pt,
                     gtsam::Vector3 const& target_line_dir, gtsam::SharedNoiseModel const& noise_model);

    /**
     * @brief Destroy the Point2Line Factor object
     *
     */
    virtual ~Point2LineFactor()noexcept;

    /**
     * @brief evaluate error and compute jacobian matrix
     *
     * @param[in] pose the pose to be optimized which can transform source point to target frame
     * @param[out] e_H_pose jacobian of error w.r.t pose
     * @return gtsam::Vector point to line error
     */
    virtual gtsam::Vector evaluateError(gtsam::Pose3 const&             pose,
                                        boost::optional<gtsam::Matrix&> e_H_pose = boost::none) const override;

private:
    gtsam::Point3  source_pt_;  ///< source point eg. point in body frame
    gtsam::Point3  target_pt_;  ///< the target line point eg. point in world frame
    gtsam::Vector3 direction_;  ///< the target line direction

};  // Point2LineFactor
/**
 * @}
 *
 */
}  // namespace internal
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_POINT2LINE_FACTOR_INL_H_
