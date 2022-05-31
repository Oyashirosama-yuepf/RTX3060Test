/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file common_define.h
 * @brief transmit interfice from map local service
 * @author jiangdianqin(jiangdianqin@holomaitc.com)
 * @date "2020-12-04"
 */
#ifndef HOLO_MAP_CORE_COMMON_COMMON_DEFINE_H_
#define HOLO_MAP_CORE_COMMON_COMMON_DEFINE_H_
#include <holo/map/service/client/engine/helper.h>
#include <holo/map/service/client/matcher/matcher.h>
#include <holo/map/service/client/matcher/result.h>
#include <holo/map/service/client/matcher/results.h>
#include <holo/map/common/common_type_define.h>
#include <holo/core/types.h>
namespace holo
{
namespace map
{
using RetrieverSPType = holo::map::service::client::engine::helper::raw::RawRetrieverSPtrType;
using MapMatcherType  = holo::map::service::client::matcher::MapMatcher;
using MapErrorCode    = holo::map::MapErrorCode;

using DistanceTypeV0           = holo::map::service::client::engine::helper::raw::DistanceTypeV0;
using RawFeatureIdTypeV0       = holo::map::service::client::engine::helper::raw::RawFeatureIdTypeV0;
using RawFeatureIdVectorTypeV0 = holo::map::service::client::engine::helper::raw::RawFeatureIdVectorTypeV0;
using RawGeoPointTypeV0        = holo::map::service::client::engine::helper::raw::RawGeoPointTypeV0;
using RawGeometryTypeV0        = holo::map::service::client::engine::helper::raw::RawGeometryTypeV0;
using RawRetrieverSPtrType     = holo::map::service::client::engine::helper::raw::RawRetrieverSPtrType;
using RawRoadTypeV0            = holo::map::service::client::engine::helper::raw::RawRoadTypeV0;
using RawRoadSPtrTypeV0        = holo::map::service::client::engine::helper::raw::RawRoadSPtrTypeV0;

using RawPositionTypeV0       = holo::map::service::client::engine::helper::raw::RawPositionTypeV0;
using RawPositionVectorTypeV0 = holo::map::service::client::engine::helper::raw::RawPositionVectorTypeV0;

using RawLaneGroupTypeV0     = holo::map::service::client::engine::helper::raw::RawLaneGroupTypeV0;
using RawLaneGroupSPtrTypeV0 = holo::map::service::client::engine::helper::raw::RawLaneGroupSPtrTypeV0;

using RawRoadAttributeTypeV0       = holo::map::service::client::engine::helper::raw::RawRoadAttributeTypeV0;
using RawRoadAttributeVectorTypeV0 = holo::map::service::client::engine::helper::raw::RawRoadAttributeVectorTypeV0;

using SpeedLimitInfo = holo::map::service::client::engine::helper::raw::RawSpeedLimitInfoTypeV0;

using IdType = holo::uint64_t;
using LaneIdType = IdType;
using LinkIdType = IdType;
using LaneBoundaryIdType = IdType;
using RoadIdType         = IdType;
using ObjectIdType       = IdType;

using VecIdType = std::vector<IdType>;
using VecLaneIdType = std::vector<LaneIdType>;
using VecLinkIdType = std::vector<LinkIdType>;
using VecLaneBoundaryIdType = std::vector<LaneBoundaryIdType>;
using VecRoadIdType         = std::vector<RoadIdType>;
using VecObjectIdType       = std::vector<ObjectIdType>;

using SeqNumber = holo::int8_t;

#define INVALID_BOUNDARY_ID 0

}  // namespace map
}  // namespace holo
#endif  // HOLO_MAP_CORE_COMMON_COMMON_MAP_LOCAL_SERVICE_ROUTER_H_