/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lmg_link_builder.h
 * @brief builder for local_map_graph's link
 * @author chanqiliang(chanqiliang@holomaitc.com)
 * @date 2021-12-27
 */

#ifndef HOLO_MAP_LOCAL_MAP_GRAPH_BUILDER_BUILDER_LINK_H_
#define HOLO_MAP_LOCAL_MAP_GRAPH_BUILDER_BUILDER_LINK_H_

#include <holo/map/common/common_type_define.h>
#include <holo/map/feature/local_map_graph/lmg_common.h>
#include <holo/map/format/base/base.h>
#include <holo/map/service/client/engine/helper.h>
#include <holo/map/feature/local_map_graph/adaptor/lmg_builder_utility.h>
#include <holo/map/feature/local_map_graph/lmg_link.h>

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
class LmgLinkBuilder
{
public:
    using LinkBuilderType     = holo::map::navigator::graph::Link<holo::uint64_t>;
    using LinkBuilderSPtrType = std::shared_ptr<LinkBuilderType>;

    using LinkFormatType      = holo::map::format::LaneGroup;
    using LinkFormatPtrType   = holo::map::format::PtrLaneGroup;

    using RoadFormatType      = holo::map::format::Road;
    using RoadFormatPtrType   = holo::map::format::PtrRoad;

public:
    LmgLinkBuilder() = default;

    virtual ~LmgLinkBuilder() = default;

    holo::bool_t Build(format::PtrRoad const& ptr_road, LinkFormatPtrType const& ptr_link, LinkBuilderSPtrType& info);

private:
    holo::bool_t adaptLaneIds(LinkFormatPtrType const& ptr_lanegroup, LinkBuilderSPtrType& link_info);

    holo::bool_t adaptLinkType(LinkFormatPtrType const& ptr_lanegroup, LinkBuilderSPtrType& link_info);

    holo::bool_t adaptLinkClass(LinkFormatPtrType const& ptr_lanegroup, LinkBuilderSPtrType& link_info);

    holo::bool_t adaptLinkAttribute(LinkFormatPtrType const& ptr_lanegroup, LinkBuilderSPtrType& link_info);
};
}  // namespace builder
}  // namespace graph
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif  // HOLO_MAP_LOCAL_MAP_GRAPH_BUILDER_BUILDER_LINK_H_