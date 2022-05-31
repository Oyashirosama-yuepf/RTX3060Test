/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parking_slot_vertex_factor.cpp
 * @brief source file of ParkingSlotVertexFactor class
 * @author Heiko Yu(yuchangsong@holomaitc.com)
 * @author Changxi CHeng(chengchangxi@holomatic.com)
 * @date "Dec-01-2021"
 */

#include <holo/localization/vision/vslam/semantic/parking_slot_vertex_factor.h>

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
ParkingSlotVertexFactor::ParkingSlotVertexFactor(const gtsam::Key& pose_key, const gtsam::Key& vertex_key,
                                                 const gtsam::Point3& measurement, const gtsam::SharedNoiseModel& model)
  : Base(model, pose_key, vertex_key), parking_slot_vertex_measurement_(measurement)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const gtsam::Point3& ParkingSlotVertexFactor::GetParkingSlotVertexMeasurement() const
{
    return parking_slot_vertex_measurement_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Vector ParkingSlotVertexFactor::evaluateError(const gtsam::Pose3& T_wb, const gtsam::Point3& P_w,
                                                     const boost::optional<gtsam::Matrix&> H_pose,
                                                     const boost::optional<gtsam::Matrix&> H_vertex) const
{
    // transform landmark to camera frame
    gtsam::Matrix       H0;          // 3 x 6
    gtsam::Matrix       H_vertex_0;  // 3 x 3
    const gtsam::Point3 q = T_wb.transform_to(P_w, H0, H_vertex_0);

    const gtsam::Point3 p = parking_slot_vertex_measurement_;

    // compute error
    const gtsam::Vector3 error = q - p;

    if (H_pose)
    {
        *H_pose = H0;
    }

    if (H_vertex)
    {
        *H_vertex = H_vertex_0;
    }

    return error;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PointOnlySlotVertexFactor::PointOnlySlotVertexFactor(const gtsam::Key& vertex_key, const gtsam::Pose3& measurement_wTb,
                                                     const gtsam::Point3&           measurement_pb,
                                                     const gtsam::SharedNoiseModel& model)
  : Base(model, vertex_key), measurement_wTb_(measurement_wTb), measurement_Pb_(measurement_pb)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const gtsam::Point3& PointOnlySlotVertexFactor::GetParkingSlotVertexMeasurement() const
{
    return measurement_Pb_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Vector PointOnlySlotVertexFactor::evaluateError(const gtsam::Point3&                  P_w,
                                                       const boost::optional<gtsam::Matrix&> H_vertex) const
{
    // transform landmark to camera frame
    gtsam::Matrix       H0;          // 3 x 6
    gtsam::Matrix       H_vertex_0;  // 3 x 3
    const gtsam::Point3 q = measurement_wTb_.transform_to(P_w, H0, H_vertex_0);

    const gtsam::Point3 p = measurement_Pb_;

    // compute error
    const gtsam::Vector3 error = q - p;

    if (H_vertex)
    {
        *H_vertex = H_vertex_0;
    }

    return error;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PoseOnlySlotVertexFactor::PoseOnlySlotVertexFactor(const gtsam::Key& pose_key, const gtsam::Point3& measurement_Pw,
                                                   const gtsam::Point3&           measurement_Pb,
                                                   const gtsam::SharedNoiseModel& model)
  : Base(model, pose_key), measurement_Pw_(measurement_Pw), measurement_Pb_(measurement_Pb)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const std::pair<gtsam::Point3, gtsam::Point3> PoseOnlySlotVertexFactor::GetParkingSlotVertexMeasurement() const
{
    return std::make_pair(measurement_Pw_, measurement_Pb_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Vector PoseOnlySlotVertexFactor::evaluateError(const gtsam::Pose3&                   wTb,
                                                      const boost::optional<gtsam::Matrix&> H_pose) const
{
    // transform landmark to camera frame
    gtsam::Matrix       H0;          // 3 x 6
    gtsam::Matrix       H_vertex_0;  // 3 x 3
    const gtsam::Point3 q = wTb.transform_to(measurement_Pw_, H0, H_vertex_0);

    const gtsam::Point3 p = measurement_Pb_;

    // compute error
    const gtsam::Vector3 error = q - p;

    if (H_pose)
    {
        *H_pose = H0;
    }

    return error;
}

}  // namespace semantic
}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo