/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lmg_lane_builder.h
 * @brief builder for local_map_graph's lane
 * @author chanqiliang(chanqiliang@holomaitc.com)
 * @date 2021-12-27
 */

#ifndef HOLO_MAP_LOCAL_MAP_GRAPH_BUILDER_BUILDER_LANE_H_
#define HOLO_MAP_LOCAL_MAP_GRAPH_BUILDER_BUILDER_LANE_H_

#include <holo/map/common/common_type_define.h>
#include <holo/map/feature/local_map_graph/adaptor/lmg_builder_utility.h>
#include <holo/map/feature/local_map_graph/lmg_common.h>
#include <holo/map/feature/local_map_graph/lmg_lane.h>
#include <holo/map/format/base/base.h>
#include <holo/map/service/client/engine/helper.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace graph
{
namespace builder
{
class LmgLaneBuilder
{
public:
    using LaneBuilderType     = holo::map::navigator::graph::Lane<holo::uint64_t, holo::geometry::Point3d>;
    using LaneBuilderSPtrType = std::shared_ptr<LaneBuilderType>;
    using LaneFormatType      = holo::map::format::Lane;
    using LaneFormatPtrType   = holo::map::format::PtrLane;

public:
    LmgLaneBuilder() = default;

    virtual ~LmgLaneBuilder() = default;

    holo::bool_t Build(LaneFormatPtrType const& ptr_lane, LaneBuilderSPtrType& info);

private:
    holo::bool_t adaptLaneType(LaneFormatPtrType const& ptr_lane, LaneBuilderSPtrType& info);

    holo::bool_t adaptTurnType(LaneFormatPtrType const& ptr_lane, LaneBuilderSPtrType& info);

    holo::bool_t adaptTransType(LaneFormatPtrType const& ptr_lane, LaneBuilderSPtrType& info);

    holo::bool_t adaptWidths(LaneFormatPtrType const& ptr_lane, LaneBuilderSPtrType& info);

    holo::bool_t adaptSpeedLimits(LaneFormatPtrType const& ptr_lane, LaneBuilderSPtrType& info);

    holo::bool_t adaptCenterLine(LaneFormatPtrType const& ptr_lane, LaneBuilderSPtrType& info);

    holo::bool_t adaptObjectIds(LaneFormatPtrType const& ptr_lane, LaneBuilderSPtrType& info);
};
}  // namespace builder
}  // namespace graph
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif  // HOLO_MAP_LOCAL_MAP_GRAPH_BUILDER_BUILDER_LANE_H_