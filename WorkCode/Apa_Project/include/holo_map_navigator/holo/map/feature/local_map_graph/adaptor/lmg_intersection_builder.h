/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lmg_intersection_builder.h
 * @brief builder for local_map_graph's intersection
 * @author chanqiliang(chanqiliang@holomaitc.com)
 * @date 2022-2-26
 */

#ifndef HOLO_MAP_LOCAL_MAP_GRAPH_BUILDER_LMG_INTERSECTION_BUILDER__H_
#define HOLO_MAP_LOCAL_MAP_GRAPH_BUILDER_LMG_INTERSECTION_BUILDER__H_

#include <holo/map/common/common_type_define.h>
#include <holo/map/feature/local_map_graph/adaptor/lmg_builder_utility.h>
#include <holo/map/feature/local_map_graph/lmg_common.h>
#include <holo/map/feature/local_map_graph/lmg_intersection.h>
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
class LmgIntersectionBuilder
{
public:
    using IntersectionBuilderType = holo::map::navigator::graph::Intersection<holo::uint64_t, holo::geometry::Point3f>;
    using IntersectionBuilderSPtrType = std::shared_ptr<IntersectionBuilderType>;
    using IntersectionFormatType      = holo::map::format::Intersection;
    using IntersectionFormatPtrType   = holo::map::format::PtrIntersection;
    using ConnectionFormatType        = holo::map::format::ConnectionV2;

public:
    LmgIntersectionBuilder() = default;

    ~LmgIntersectionBuilder() = default;

    holo::bool_t Build(IntersectionFormatPtrType const& ptr_intersection, IntersectionBuilderSPtrType& info);

private:
    holo::bool_t AdaptIntersectionType(IntersectionFormatPtrType const& ptr_intersection,
                                       IntersectionBuilderSPtrType&     info);

    void AdaptConnection(ConnectionFormatType const&                          format_connection,
                         IntersectionBuilderType::IntersectionConnectionType& connection_info);
};
}  // namespace builder
}  // namespace graph
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif  // HOLO_MAP_LOCAL_MAP_GRAPH_BUILDER_LMG_INTERSECTION_BUILDER__H_