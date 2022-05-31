/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file filter.h
 * @brief This header file defines common filter class as parent class of different sensor type.
 * @author sunzhenqiang(sunzhenqiang@holomaitc.com)
 * @date "2019-12-23"
 */

#ifndef HOLO_PERCEPTION_FUSION_FILTER_H_
#define HOLO_PERCEPTION_FUSION_FILTER_H_

#include <holo/geometry/convex_polygon2.h>
#include <holo/obstacle/obstacle_base.h>
#include <holo/perception/tracking/filter_state.h>
#include <holo/perception/tracking/track.h>
#include <holo/perception/tracking/impl/track.hpp>

namespace holo
{
namespace perception
{
/**
 * @addtogroup fusion
 *
 * @{
 */

/**
 * @brief Commnon filetr rule implement, and just for fusion.
 * @details Implement some common filters, such as filter by work zone, filter by map roi and so on, and it will be
 * expended with demand
 *
 * @tparam T Obstacle scalar. Now support float32_t or float64_t.
 */
template <typename T>
class FilterT
{
public:
    /**
     * @brief smart pointer
     *
     */
    using Ptr           = std::shared_ptr<FilterT<T> >;
    using ConstPtr      = std::shared_ptr<const FilterT<T> >;
    using Track         = TrackT<holo::ObstacleBaseT<T> >;
    using ConvexPolygon = holo::geometry::details::ConvexPolygon2T<T>;
    using Point         = holo::geometry::details::Point2T<T>;

    /**
     * @brief filter track by map roi
     *
     * @param track filter object
     * @param roi map roi
     * @return bool_t if track is in map roi, return true, else return false
     */
    static bool_t FilterByRoi(const Track& track, const ConvexPolygon& roi);
};

/**
 * @}
 *
 */
}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_TRACKING_FILTER_H_
