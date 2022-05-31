/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file assist.h
 * @brief Assist for lane naivgation
 * @author yuhongbo(yuhongbo@holomaitc.com)
 * @date "2021-10-08"
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE2_LANE_NAVIGATOR_ASSIST_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE2_LANE_NAVIGATOR_ASSIST_H_

#include <memory>

#include <holo/common/road_type.h>
#include <holo/core/types.h>

#include <holo/map/common/common_define.h>

#include <holo/map/feature/navigator/advice/lane_navigator/target_region.h>
#include <holo/map/feature/navigator/advice/lane_navigator/entity.h>
#include <holo/map/feature/navigator/router/route_info.h>
#include <holo/map/format/base/lane.h>
#include <holo/map/format/base/base.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
class LaneItem;
class LanePath;
/**
 * @brief The basic element of lane path
 *
 */
class Assist
{
public:
    using LanePathSPtrType = std::shared_ptr<LanePath>;
    using Seed             = holo::map::navigator::advice::SceneSeed;
    using VecSeed          = std::vector<Seed>;
    using PtrLaneType      = holo::map::format::PtrLane;

public:
    static holo::bool_t CreateTargetRegionAndLanePath(RetrieverSPType              ret,
                                                      VecLaneBoundaryIdType const& lane_boundary_ids,
                                                      holo::bool_t const left, LanePathSPtrType& lane_path);

    static holo::bool_t CheckSuccessiveRelation(RetrieverSPType ret, holo::uint64_t const before_id, holo::uint64_t const after_id,
                                   holo::bool_t& has_relation);

    static holo::bool_t CheckBoundariesRelation(RetrieverSPType ret, holo::uint64_t const before_id,
                                                holo::uint64_t const after_id, holo::bool_t& has_relation);

    static holo::bool_t CheckLaneForward(RetrieverSPType ret, holo::uint64_t const before_id,
                                         holo::uint64_t const after_id, holo::bool_t& has_relation);

    static holo::bool_t CalculateSeedsFromLink(IdType const main_id, IdType const branch_id, VecSeed& seeds);

    static holo::bool_t CheckLinkIsInIntersection(IdType const link_id, holo::bool_t& is_in);
    
    static holo::bool_t CheckLaneIsInIntersection(IdType const lane_id, holo::bool_t& is_in);

    static holo::float64_t CalculateLogistic(holo::float64_t const z);

    static holo::bool_t CheckLaneValid(format::PtrLane lane);

    static holo::bool_t GetNextLinkId(RouteInfo2::Ptr route_info, holo::uint64_t const link_id, holo::bool_t& has_next,
                                      holo::uint64_t& next_link_id);

    static holo::bool_t GetForwardLaneId(IdType const curr_lane_id, holo::bool_t& has, PtrLaneType& forward_lane);

    static holo::bool_t GetBehindLaneId(IdType const curr_lane_id, holo::bool_t& has, PtrLaneType& behind_lane);

    static holo::bool_t GetHeadWidthOfLane(PtrLaneType lane, holo::float64_t& width);

    static holo::bool_t GetRearWidthOfLane(PtrLaneType lane, holo::float64_t& width);

    static holo::geometry::Point2d ConvertGeoPointToPoint2d(holo::map::format::GeoPoint const& pt);
};
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE2_LANE_NAVIGATOR_ASSIST_H_ */
