/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file projection_line_factor_inl.h
 * @brief A class to define projection lane factor
 * @author Bai Pengfei (baipengfei@holomatic.com)
 * @date June 20, 2020
 */

#ifndef HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_PROJECTION_LINE_FACTOR_INL_H_
#define HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_PROJECTION_LINE_FACTOR_INL_H_

#include <gtsam/geometry/CalibratedCamera.h>
#include <gtsam/geometry/Point2.h>
#include <gtsam/geometry/Point3.h>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/inference/Key.h>
#include <gtsam/linear/NoiseModel.h>
#include <gtsam/nonlinear/NonlinearFactor.h>
#include <gtsam/nonlinear/Values.h>
#include <gtsam/slam/ProjectionFactor.h>
#include <holo/localization/common/types.h>

namespace holo
{
namespace localization
{
namespace internal
{
/**
 * @addtogroup sam
 *
 */

/**
 * @brief This class define ProjectionLineFactor that optimize the pose of body in world frame
 *
 */
class ProjectionLineFactor : public gtsam::NoiseModelFactor1<gtsam::Pose3>
{
public:
    using shared_ptr = boost::shared_ptr<ProjectionLineFactor>;

    /**
     * @brief Default constructor
     *
     */
    ProjectionLineFactor() noexcept;

    /**
     * @brief Constructor a new ProjectionLineFactor object
     *
     * @param[in] key key of pose
     * @param[in] model noise model
     * @param[in] point map point in world frame
     * @param[in] bTc pose of camera in body frame
     * @param[in] k calibration
     * @param[in] line fitted line
     * @param[in] enable_rotation_constraint enable rotation constraint, if false, the rotation is not optimized
     */
    ProjectionLineFactor(gtsam::Key const& key, gtsam::SharedNoiseModel const& model, gtsam::Point3 const& point,
                         gtsam::Pose3 const& bTc, gtsam::Cal3_S2 const& K, Line2Type const& line,
                         bool_t const enable_rotation_constraint = true);

    /**
     * @brief EvaluateError function of ProjectionLineFactor
     * @details the error term is distance between point and line
     *          the point is projected map point on image plane
     *          the line is fitted line in image plane
     *
     * @param[in] wTb vehicle pose
     * @param[in] H Jacobian Matrix of cost to pose
     * @return pixel error
     */
    gtsam::Vector evaluateError(gtsam::Pose3 const& wTb, boost::optional<gtsam::Matrix&> H = boost::none) const;

private:
    gtsam::Point3  point_;                       ///< map point
    gtsam::Pose3   bTc_;                         ///< pose of camera in body frame
    gtsam::Cal3_S2 K_;                           ///< intrinsic of camera
    Line2Type      line_;                        ///< fitted line
    bool_t         enable_rotation_constraint_;  ///< enable rotation constraint

};  // ProjectionLineFactor

/**
 * @}
 *
 */
}  // namespace internal
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_PROJECTION_LINE_FACTOR_INL_H_
