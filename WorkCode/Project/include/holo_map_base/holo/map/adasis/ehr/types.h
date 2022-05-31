/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file types.h
 * @brief This header file defines the ehr typedefs.
 * @author zhengshulei@holomatic.com
 * @date 2021-11-5
 */
#ifndef HOLO_MAP_ADASIS_EHR_TYPES_H_
#define HOLO_MAP_ADASIS_EHR_TYPES_H_

#include <holo/core/types.h>
#include <holo/map/adasis/baidu_v3/msg_types.h>
#include <holo/map/adasis/v3/types.h>
#include <holo/common/coordinate.h>
#include <holo/map/common/preprocess.h>
#include <holo/map/format/base/lane.h>
#include <holo/map/format/base/lane_boundary.h>
#include <holo/map/format/base/lane_boundary_element.h>
#include <holo/map/format/base/lane_group.h>
#include <holo/map/format/base/road.h>
#include <holo/map/format/navigation/routing_path.h>
#include <holo/map/format/navigation/routing_path_element.h>
#include <holo/common/odometry.h>

namespace holo
{
namespace map
{
namespace adasis
{
namespace ehr
{
using LinkId      = holo::uint64_t;
using LinearObjId = v3_1_1::LinearObjId;
using MessageType = holo::map::adasis::baidu_v3::MessageType;
using HDMapStatus         = holo::map::adasis::baidu_v3::HDMap;

using PositionEntry       = baidu_v3::MLM_LOC;
using GlobalDataEntry     = baidu_v3::GlobalDataMessage;
using PathControlEntry    = v3_1_1::PathControl;
using ProfileControlEntry = v3_1_1::ProfileControl;

using LinkEntry             = baidu_v3::LinkIdentifierEntry;
using LinkIdentifierEntry   = baidu_v3::LinkIdentifierEntry;
using InsectionEntry        = baidu_v3::InsectionEntry;
using LaneModelEntry        = baidu_v3::LaneModelEntry;
using LaneConnectivityEntry = baidu_v3::LaneConnectivityEntry;
using LinearObjectEntry     = baidu_v3::LinearObjectEntry;
using GeometryEntry         = baidu_v3::GeometryEntry;
using LineGeometryEntry     = baidu_v3::LineGeometryEntry;
using SpeedLimitEntry       = baidu_v3::SpeedLimitEntry;
using LaneWidthEntry        = baidu_v3::LaneWidthEntry;
using CurvatureEntry        = baidu_v3::CurvatureEntry;
using SlopeEntry            = baidu_v3::SlopeEntry;

using NumOfLaneEntry           = baidu_v3::NumberOfLanesEntry;
using FormOfWayEntry           = baidu_v3::FormOfWayEntry;
using TunnelEntry              = baidu_v3::TunnelEntry;
using FunctionalRoadClassEntry = baidu_v3::FunctionalRoadClassEntry;

using PositionPtr         = std::shared_ptr<PositionEntry>;
using GlobalDataPtr       = std::shared_ptr<GlobalDataEntry>;
using ProfileControlPtr   = std::shared_ptr<ProfileControlEntry>;
using PathControlPtr      = std::shared_ptr<PathControlEntry>;
using LinkIdentifierPtr   = std::shared_ptr<LinkIdentifierEntry>;
using LinkEntryPtr        = std::shared_ptr<LinkEntry>;
using InsectionPtr        = std::shared_ptr<InsectionEntry>;
using LaneConnectivityPtr = std::shared_ptr<LaneConnectivityEntry>;
using LaneModelPtr        = std::shared_ptr<LaneModelEntry>;
using LinearObjectPtr     = std::shared_ptr<LinearObjectEntry>;
using GeometryPtr         = std::shared_ptr<GeometryEntry>;
using LaneGeometryPtr     = std::shared_ptr<LineGeometryEntry>;
using SpeedLimitPtr       = std::shared_ptr<SpeedLimitEntry>;
using LaneWidthPtr        = std::shared_ptr<LaneWidthEntry>;
using CurvaturePtr        = std::shared_ptr<CurvatureEntry>;
using SlopePtr            = std::shared_ptr<SlopeEntry>;

using NumOfLanePtr           = std::shared_ptr<NumOfLaneEntry>;
using FormOfWayPtr           = std::shared_ptr<FormOfWayEntry>;
using TunnelPtr              = std::shared_ptr<TunnelEntry>;
using FunctionalRoadClassPtr = std::shared_ptr<FunctionalRoadClassEntry>;

using LinkEntryCPtr        = LinkEntryPtr;
using InsectionCPtr        = InsectionPtr;
using LaneConnectivityCPtr = LaneConnectivityPtr;
using LaneModelCPtr        = LaneModelPtr;
using LinearObjectCPtr     = LinearObjectPtr;
using GeometryCPtr         = GeometryPtr;
using SpeedLimitCPtr       = SpeedLimitPtr;
using LaneWidthCPtr        = LaneWidthPtr;

using SpeedLimitVecContainerType   = std::vector<SpeedLimitPtr>;
using LaneWidthVecContainerType    = std::vector<LaneWidthPtr>;
using LaneGeometryVecContainerType = std::vector<LaneGeometryPtr>;

using LaneConnectivityVecContainerType = std::vector<LaneConnectivityPtr>;
using LaneGeometryVecContainerType     = std::vector<LaneGeometryPtr>;
using CurvatureVecContainerType        = std::vector<CurvaturePtr>;
using SlopeVecContainerType            = std::vector<SlopePtr>;

using LaneModelContainerType         = std::map<LinkId, LaneModelPtr>;
using LinearObjectContainerType      = std::map<LinkId, LinearObjectPtr>;
using CurvatureContainerType         = std::map<LinkId, CurvaturePtr>;
using SlopeContainerType             = std::map<LinkId, SlopePtr>;
using SpeedLimitContainerType        = std::map<LinkId, SpeedLimitPtr>;
using NumOfLaneContainerType         = std::map<LinkId, holo::uint8_t>;
using RoadFunctionClassContainerType = std::map<LinkId, baidu_v3::BaiduFunctionalRoadClass>;
using FormOfWayContainerType         = std::map<LinkId, baidu_v3::BaiduFormOfWay>;
using TunnelContainerType            = std::map<LinkId, bool_t>;
using LaneWidthContainerType         = std::map<LinkId, LaneWidthPtr>;
using RoadGeometryContainerType      = std::map<LinkId, GeometryPtr>;
using LaneGeometryContainerType      = std::map<v3_1_1::LinearObjId, LaneGeometryVecContainerType>;

using ProfileControlContainerType = std::map<v3_1_1::PathId, ProfileControlPtr>;
using PathTreeContainerType       = std::map<v3_1_1::PathId, PathControlPtr>;

using InsectionVecContainerType      = std::vector<InsectionPtr>;
using LinkIdentifierVecContainerType = std::vector<LinkEntryPtr>;
using LinkIdentifierContainerType    = std::map<LinkId, LinkEntryPtr>;

using PathEndpointLinkContainerType = std::map<v3_1_1::PathId, LinkEntryPtr>;
using LinkConnectivityContainerType = std::map<LinkId, LinkIdentifierVecContainerType>;

using FeatureIdType = holo::map::MapFeatureIdType;

using GeoPointType       = holo::map::format::GeoPoint;
using GeoPointVectorType = std::vector<GeoPointType>;

using CoordinateSystemDefinitionType    = holo::common::Coordinate;
using CoordinateSystem    = CoordinateSystemDefinitionType::Type;
using CoordinateType = holo::map::format::Coordinate;
using GeographicParameterType = holo::map::format::geometry::GeographicParameter<
    GeoPointType, CoordinateSystemDefinitionType>;

using SpeedLimit            = holo::uint32_t;
using SpeedLimitInfoType    = holo::map::format::SpeedLimitInfo;
using SpeedLimitInfoVecType = std::vector<SpeedLimitInfoType>;

using LaneWidthInfoType    = holo::map::format::LaneWidthInfo;
using LaneWidthInfoVecType = std::vector<LaneWidthInfoType>;

using SpeedLimitInfoType    = holo::map::format::SpeedLimitInfo;
using SpeedLimitInfoVecType = std::vector<SpeedLimitInfoType>;

using RoadAttributeType    = holo::map::format::RoadAttribute;
using RoadAttributeVecType = std::vector<RoadAttributeType>;

using RoadType         = holo::map::format::Road;
using LaneType         = holo::map::format::Lane;
using LaneGroupType    = holo::map::format::LaneGroup;
using LaneBoundaryType = holo::map::format::LaneBoundary;

using RoutingPathElementType = holo::map::format::RoutingPathElement;
using RoutingPathType = holo::map::format::RoutingPath;

using RoadSPtrType         = holo::map::format::PtrRoad;
using LaneSPtrType         = holo::map::format::PtrLane;
using LaneGroupSPtrType    = holo::map::format::PtrLaneGroup;
using LaneBoundarySPtrType = holo::map::format::PtrLaneBoundary;

using RoutingPathElementSPtrType = holo::map::format::PtrRoutingPathElement;
using RoutingPathSPtrType = holo::map::format::PtrRoutingPath;

using RoadVectorType         = std::vector<RoadSPtrType>;
using LaneVectorType         = std::vector<LaneSPtrType>;
using LaneGroupVectorType    = std::vector<LaneGroupSPtrType>;
using LaneBoundaryVectorType = std::vector<LaneBoundarySPtrType>;

using RoutingPathElementVectorType = std::vector<RoutingPathElementSPtrType>;
using RoutingPathVectorType = std::vector<RoutingPathSPtrType>;

using RoadContainerType         = std::map<FeatureIdType, RoadSPtrType>;
using LaneContainerType         = std::map<FeatureIdType, LaneSPtrType>;
using LaneGroupContainerType    = std::map<FeatureIdType, LaneGroupSPtrType>;
using LaneBoundaryContainerType = std::map<FeatureIdType, LaneBoundarySPtrType>;

using RoutingPathElementContainerType = std::map<FeatureIdType, RoutingPathElementSPtrType>;
using RoutingPathContainerType = std::map<FeatureIdType, RoutingPathSPtrType>;

using LaneBoundaryInfoType          = holo::map::format::LaneBoundaryInfo;
using LaneBoundaryInfoSPtrType      = std::shared_ptr<LaneBoundaryInfoType>;
using LaneBoundaryInfoVectorType    = std::vector<LaneBoundaryInfoType>;
using LaneBoundaryElementType       = holo::map::format::LaneBoundaryElement;
using LaneBoundaryElementSPtrType   = std::shared_ptr<LaneBoundaryElementType>;
using LaneBoundaryElementVectorType = std::vector<LaneBoundaryElementType>;

using LocalMapOdometryType      = holo::common::LocalMapOdometryd;

struct MapDataGroup
{
    RoutingPathContainerType routing_paths;
    RoadContainerType roads;
    LaneContainerType lanes;
    LaneGroupContainerType groups;
    LaneBoundaryContainerType boundaries;

    void Clear()
    {
        this->routing_paths.clear();
        this->roads.clear();
        this->lanes.clear();
        this->groups.clear();
        this->boundaries.clear();
    }
};

} // namespace ehr
} // namespace adasis
} // namespace map
} // namespace holo

#endif /* HOLO_MAP_ADASIS_EHR_TYPES_H_ */