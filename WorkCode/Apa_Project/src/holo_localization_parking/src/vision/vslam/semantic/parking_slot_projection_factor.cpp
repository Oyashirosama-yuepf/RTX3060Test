/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parking_slot_projection_factor.cpp
 * @brief source file of ParkingSlotProjectionFactor class
 * @author Yanwei. Du(duyanwei@holomaitc.com)
 * @author Changxi. Cheng(chengchangxi@holomatic.com)
 * @date 2021-05-21
 */

#include <holo/localization/vision/vslam/semantic/parking_slot_projection_factor.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
namespace semantic
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ParkingSlotProjectionFactor::ParkingSlotProjectionFactor(const gtsam::Key& pose_key, const gtsam::Key& vertex_key,
                                                         const gtsam::Point3&           measurement,
                                                         const gtsam::SharedNoiseModel& model)
  : Base(model, pose_key, vertex_key), measurement_(measurement)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Vector ParkingSlotProjectionFactor::evaluateError(const gtsam::Pose3& T_wb, const gtsam::Point3& P_w,
                                                         const boost::optional<gtsam::Matrix&> H_pose,
                                                         const boost::optional<gtsam::Matrix&> H_vertex) const
{
    // transform landmark to camera frame
    gtsam::Matrix       H0;          // 3 x 6
    gtsam::Matrix       H_vertex_0;  // 3 x 3
    const gtsam::Point3 P_c = T_wb.transform_to(P_w, H0, H_vertex_0);

    const gtsam::Point2 prediction(P_c.x() / P_c.z(), P_c.y() / P_c.z());
    const Scalar        inv_depth = 1.0 / P_c.z();
    gtsam::Matrix23     H;
    H << inv_depth, 0.0, -P_c.x() * (inv_depth * inv_depth), 0.0, inv_depth, -P_c.y() * (inv_depth * inv_depth);

    // compute error
    const gtsam::Vector2 error(prediction.x() - measurement_.x() / measurement_.z(),
                               prediction.y() - measurement_.y() / measurement_.z());

    if (H_pose)
    {
        *H_pose = H * H0;
    }

    if (H_vertex)
    {
        *H_vertex = H * H_vertex_0;
    }

    return error;
}
}  // namespace semantic
}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo