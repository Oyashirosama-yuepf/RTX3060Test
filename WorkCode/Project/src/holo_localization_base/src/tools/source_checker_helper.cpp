/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file source_checker_helper.cpp
 * @brief source checker unique functions implementation.
 * @author Wenzhi Liu(liuwenzhi@holomatic.com)
 * @date 2020-09-15
 */

#include <holo/localization/tools/source_checker_helper.h>

namespace holo
{
namespace localization
{
namespace internal
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t CheckOdometryUniqueState(const OdometryCheckerUniqueParameters& params, const OdometryType& odometry)
{
    if (odometry.GetStatus() == OdometryType::Status::UNKNOWN)
    {
        LOG(WARNING) << "Odometry --- 0x" << std::hex << (uint32_t)odometry.GetCoordinate()
                     << " statue is UNKNOWN";
        return false;
    }

    if (odometry.GetPoseCovariance()(0u, 0u) > params.translation_x_cov_threshold ||
        odometry.GetPoseCovariance()(1u, 1u) > params.translation_y_cov_threshold ||
        odometry.GetPoseCovariance()(2u, 2u) > params.translation_z_cov_threshold ||
        odometry.GetPoseCovariance()(3u, 3u) > params.rotation_x_cov_threshold || 
        odometry.GetPoseCovariance()(4u, 4u) > params.rotation_y_cov_threshold || 
        odometry.GetPoseCovariance()(5u, 5u) > params.rotation_z_cov_threshold)
    {
        LOG(WARNING) << "Odometry --- 0x" << std::hex << (uint32_t)odometry.GetCoordinate()
                     << " covariance exceeds the threshold";
        return false;
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t CheckRoadFrameUniqueState(const RoadFrameCheckerUniqueParameters& params, const RoadFrame& road_frame)
{
    using LaneBoundaryType = holo::common::LaneBoundary<holo::numerics::Polynomial<holo::float32_t, 3UL>>;
    
    const LaneBoundaryType& left_lane  = road_frame[1u];
    const LaneBoundaryType& right_lane = road_frame[2u];

    const bool_t is_left_lane_good  = (left_lane.IsValid() && left_lane.GetConfidence() > params.detected_lane_confidence_threshold);
    const bool_t is_right_lane_good = (right_lane.IsValid() && right_lane.GetConfidence() > params.detected_lane_confidence_threshold);

    /* The logic here is:
     * 1, if the confidence of left lane and right lane is low -- return false
     * 2, if one of them has high confidence and the other has low -- return true
     * 3, if the confidence of left lane and right lane is high, need to judge the width of the road
     *    1> if the width of the road too narrow or to wide -- return false
     *    2> else -- return true
     **/
    if (!is_left_lane_good && !is_right_lane_good)
    {
        LOG(WARNING) << "RoadFrame both left lane and right lane are low confidence "
                     << "left lane confidence = " << static_cast<uint32_t>(left_lane.GetConfidence())
                     << "right lane confidence = " << static_cast<uint32_t>(right_lane.GetConfidence());
        return false;
    }
    else if (is_left_lane_good && is_right_lane_good)
    {
        const Scalar left_distance  = std::fabs(static_cast<Scalar>(left_lane.GetSampleByCoordinate(Scalar(0.0)).GetY()));
        const Scalar right_distance = std::fabs(static_cast<Scalar>(right_lane.GetSampleByCoordinate(Scalar(0.0)).GetY()));

        const bool_t is_lane_too_narrow = (left_distance + right_distance) < params.detected_lane_too_narrow_threshold;
        const bool_t is_lane_too_width  = (left_distance + right_distance) > params.detected_lane_too_wide_threshold;

        if (!is_lane_too_narrow && !is_lane_too_width)
        {
            return true;
        }
        else
        {
            LOG(WARNING) << "Distance between two lane lines = " << left_distance + right_distance << "m. "
                         << "It is not reasonable.";
            return false;
        }
    }
    
    return true;
}

} /* namespace internal */
} /* namespace localization */
} /* namespace holo */
