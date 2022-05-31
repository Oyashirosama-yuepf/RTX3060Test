/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lmg_boundary_builder.h
 * @brief builder for local_map_graph's boundary
 * @author chanqiliang(chanqiliang@holomaitc.com)
 * @date 2021-12-15
 */

#ifndef HOLO_MAP_LOCAL_MAP_GRAPH_BUILDER_LMG_BOUNDARY_BUILDER__H_
#define HOLO_MAP_LOCAL_MAP_GRAPH_BUILDER_LMG_BOUNDARY_BUILDER__H_

#include <holo/map/common/common_type_define.h>
#include <holo/map/feature/local_map_graph/adaptor/lmg_builder_utility.h>
#include <holo/map/feature/local_map_graph/lmg_boundary.h>
#include <holo/map/feature/local_map_graph/lmg_common.h>
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
class LmgBoundaryBuilder
{
public:
    using BoundaryBuilderType         = holo::map::navigator::graph::Boundary<holo::uint64_t, holo::geometry::Point3d>;
    using BoundaryIntervalBuilderType = BoundaryBuilderType::BoundaryIntervalInfoType;
    using BoundaryBuilderSPtrType     = std::shared_ptr<BoundaryBuilderType>;
    using BoundaryFormatType          = holo::map::format::LaneBoundary;
    using BoundaryFormatPtrType       = holo::map::format::PtrLaneBoundary;
    using BoundaryElementFormatType   = holo::map::format::LaneBoundaryElement;

public:
    LmgBoundaryBuilder() = default;

    virtual ~LmgBoundaryBuilder() = default;

    holo::bool_t Build(BoundaryFormatPtrType const& ptr_boundary, BoundaryBuilderSPtrType& info);

private:
    holo::bool_t adaptCenterLine(BoundaryFormatPtrType const& ptr_boundary, BoundaryBuilderSPtrType& info);

    void adaptBoundaryElement(holo::map::format::LaneBoundaryInfo const& boundary_info, BoundaryBuilderSPtrType& info);

    holo::bool_t isPaintedBoundaryElement(BoundaryElementFormatType::BoundaryType const type);

    holo::bool_t isPaintedBoundaryInfo(format::LaneBoundaryInfo const& lb_info);

    holo::bool_t hasPaintedBoundary(BoundaryFormatPtrType const& ptr_boundary);

    holo::bool_t adaptSegments(BoundaryFormatPtrType const& ptr_boundary, BoundaryBuilderSPtrType& info);

    void adaptLineStyle(format::LaneBoundaryElement const& ele, BoundaryIntervalBuilderType& boundary_interval);

    void adaptBoundaryType(BoundaryElementFormatType const& element, BoundaryIntervalBuilderType& interval);
};
}  // namespace builder
}  // namespace graph
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif  // HOLO_MAP_LOCAL_MAP_GRAPH_BUILDER_LMG_BOUNDARY_BUILDER__H_