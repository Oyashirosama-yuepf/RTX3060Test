/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/*!
 * @file common.h
 * @brief the definition of some common functions
 * @author Zhang Yelin(zhangyelin@holomatic.com)
 * @date 2020-07-21
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_LANE_COMMON_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_LANE_COMMON_H_

#include <holo/localization/tightly_coupled_fusion/lane/types.h>
#include <holo/log/hololog.h>

namespace holo
{
namespace localization
{
namespace tightly_coupled_fusion
{
namespace lane
{
/**
 * @addtogroup lane
 * @{
 *
 */

/**
 * @brief check detected lane valid or not
 * @param[in] lb lane boundary
 * @param[in] min_confidence min confidence of detected lane is valid
 * @return true is the lane is valid or false if is invalid
 */
bool_t IsDetectedLaneValid(const CameraLaneBoundaryType& lb, const Scalar min_confidence);

/**
 * @brief extract points from detected lanes
 * @todo: (zhangyelin@holomatic.com) will use curvature of lane to determinate lane segment in the future.
 * @param[in] detected_lane detected lane
 * @param[in] valid_range valid range of detect lane
 * @param[in] lane_segment_number number of lane segment
 * @param[in] detect_lane_sample_length sample length of detected lane
 * @return extracted points
 */
std::vector<std::vector<Point2Type>> ExtractPoints(const CameraLaneBoundaryType& detected_lane, const Scalar valid_range,
                                                   const uint64_t lane_segment_number,
                                                   const Scalar   detect_lane_sample_length);

/**
 * @brief sample points from detected lane
 * @param[in] detected_lane detected lane
 * @param[in] valid_range valid range of detected lane
 * @param[in] detect_lane_sample_length sample length
 * @param[out] sampled_points sampled points from detected lane
 */
void SamplePoints(const CameraLaneBoundaryType& detected_lane, const Scalar valid_range,
                  const Scalar detect_lane_sample_length, std::vector<Point3Type>& sampled_points);

/**
 * @brief get rough scaled point
 * @param[in] p1 first point
 * @param[in] p2 second point
 * @param[in] scale distance coefficient for get the point
 * @return scaled point
 * @tparam T type of points to be sampled, such as 2D points or 3D points
 */
template <typename T>
T GetRoughScaledPoint(const T& p1, const T& p2, const Scalar scale)
{
    const T scaled_point(p1 + (p2 - p1) * scale);
    return scaled_point;
}

/**
 * @brief insert reference points
 * @param[in] p1 start point
 * @param[in] p2 end point
 * @param[in] step length of every sampled step
 * @param[out] points result points
 * @param[in] include_terminal include origin start end point or not
 * @tparam T type of points to be sampled, such as 2D points or 3D points
 */
template <typename T>
void InsertRefPoints(const T& start_point, const T& end_point, const Scalar step, const bool include_terminal,
                     std::vector<T>& points)
{
    points.clear();
    const Scalar delta_x = start_point.GetX() - end_point.GetX();
    const Scalar delta_y = start_point.GetY() - end_point.GetY();

    const Scalar length = std::sqrt(delta_x * delta_x + delta_y * delta_y);

    if (length < Scalar(0.1) || step < Scalar(0.1))
    {
        return;
    }

    // for the case that length is an integer multiple of step, we would
    // rather conservatively estimate the count of span, so we have here -1e-6
    const uint64_t count               = ::std::max(0.0, std::floor((length - 1e-6) / step));
    const Scalar   percentage_per_step = step / length;
    points.reserve(count + 2);

    // Step 1, push left terminal if required
    if (include_terminal)
    {
        points.push_back(start_point);
    }

    // Step 2, push points in-between
    for (uint64_t i = 0u; i < count; ++i)
    {
        const Scalar ratio = percentage_per_step * (i + 1);
        points.emplace_back(GetRoughScaledPoint(start_point, end_point, ratio));
    }

    // Step 3,push right terminal if required
    if (include_terminal)
    {
        points.push_back(end_point);
    }
}

/**
 * @brief upsample points by a fixed step
 * @param[in] origin_points origin points
 * @param[in] step length of every point
 * @param[out] created_points result points
 * @tparam T type of points to be sampled, such as 2D points or 3D points
 */
template <typename T>
void UpSampleByStepLength(const std::vector<T>& origin_points, const Scalar step, std::vector<T>& created_points)
{
    created_points.clear();
    if (origin_points.empty())
    {
        return;
    }

    for (uint64_t i = 0u; i < origin_points.size() - 1; ++i)
    {
        created_points.push_back(origin_points[i]);
        std::vector<T> new_points;
        InsertRefPoints<T>(origin_points[i], origin_points[i + 1], step, false, new_points);
        created_points.insert(created_points.end(), new_points.begin(), new_points.end());
    }
    created_points.push_back(origin_points.back());
}

/**
 * @}
 *
 */
}  // namespace lane
}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_LANE_COMMON_H_
