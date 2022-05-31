/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_factor_inl.h
 * @brief A class to define lane factor
 * @author Zhang Yelin (zhangyelin@holomatic.com)
 * @date Dec 13, 2019
 */

#ifndef HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_LANE_FACTOR_INL_H_
#define HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_LANE_FACTOR_INL_H_

#include <gtsam/geometry/Point2.h>
#include <gtsam/geometry/Point3.h>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/inference/Key.h>
#include <gtsam/linear/NoiseModel.h>
#include <gtsam/nonlinear/NonlinearFactor.h>
#include <gtsam/nonlinear/Values.h>
#include <holo/geometry/polyfit2.h>
#include <holo/localization/common/types.h>

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
// Transform lane from body to world
class Lane2Factor : public gtsam::NoiseModelFactor1<gtsam::Pose3>
{
public:
    using Vector3                = holo::numerics::Vector3T<Scalar>;
    using Line2                  = holo::geometry::Line2T<Scalar>;
    using shared_ptr             = boost::shared_ptr<Lane2Factor>;
    using LaneCorrespondenceType = holo::localization::LaneCorrespondences::Type;

    /**
     * @brief constructor
     */
    Lane2Factor();

    /**
     * @brief constructor
     *
     * @param[in] j Key
     * @param[in] model gtsam::SharedNoiseModel
     * @param[in] point  3D point
     * @param[in] line  line 2d
     * @param[in] lane_correspondence_type type of lane correspondence
     * @param[in] disable_rotation_optimization disable rotation optimization flag
     */
    Lane2Factor(const gtsam::Key& j, const gtsam::SharedNoiseModel& model, const Point3Type& point, const Line2& line,
                const LaneCorrespondenceType& lane_correspondence_type      = LaneCorrespondenceType::PROJECT_TO_WORLD,
                const bool_t                  disable_rotation_optimization = false);

    /**
     * @brief evaluateError function of lane factor
     *
     * @param[in] wTb pose of body in world coordinate frame
     * @param[in] dist_H_pose Jacobian Matrix of cost to pose
     */
    gtsam::Vector evaluateError(const gtsam::Pose3& wTb, boost::optional<gtsam::Matrix&> dist_H_pose) const;

private:
    Point3Type             point_;                          ///< 3D point
    Line2                  line_;                           ///< line 2d
    LaneCorrespondenceType lane_correspondence_type_;       ///< type of lane correspondence
    bool_t                 disable_rotation_optimization_;  ///< disable rotation optimization flag

};  // Lane2Factor
/**
 * @}
 *
 */
}  // namespace internal
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_LANE_FACTOR_INL_H_
