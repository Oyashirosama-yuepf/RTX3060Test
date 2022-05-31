/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file helper.h
 * @brief helper.h
 * @author wanghaiyang@holomatic.com
 * @date "2020-11-19"
 */

#ifndef HOLO_MAP_SERVICE_CLIENT_ENGINE_HELPER_H_
#define HOLO_MAP_SERVICE_CLIENT_ENGINE_HELPER_H_

#include <holo/core/types.h>
#include <holo/map/common/geometry.h>
#include <holo/map/common/marshal.h>
#include <holo/map/common/preprocess.h>
#include <holo/map/common/types.h>
#include <holo/map/format/base/base.h>
#include <holo/map/format/base/lane.h>
#include <holo/map/format/base/lane_boundary.h>
#include <holo/map/format/base/lane_group.h>
#include <holo/map/format/base/object_info.h>
#include <holo/map/format/base/road.h>
#include <holo/map/format/common/geo_box.h>
#include <holo/map/format/common/geo_circle.h>
#include <holo/map/format/common/geo_point.h>
#include <holo/map/format/navigation/routing_path.h>
#include <holo/map/service/client/engine/retriever.h>

namespace holo
{
namespace map
{
namespace service
{
namespace client
{
namespace engine
{
namespace helper
{
namespace raw
{

/**
 * @addtogroup raw
 * @{
 *
 */

/// Redefine distance of length type for raw distance type.
using DistanceTypeV0 = holo::map::Distance;

/// Redefine direction for raw map direction;
using DirectionTypeV0           = holo::map::Direction;
using DrivingDirectionTypeV0    = holo::map::DrivingDirection;

/// Redefine raw map feature id types.
using RawFeatureIdTypeV0        = holo::map::MapFeatureIdType;
using RawFeatureIdVectorTypeV0  = holo::map::MapFeatureIdVectorType;

using RawFeatureIntervalIdTypeV0        = holo::map::format::IdIntervalFloat64;
using RawFeatureIntervalIdVectorTypeV0  = std::vector<RawFeatureIntervalIdTypeV0>;

/// Redefine data types for raw map data features.
using RawFeatureTypeV0                  = holo::map::format::helper::FeatureType;
using RawFeatureVectorTypeV0            = holo::map::format::helper::FeatureVectorType;
using RawBaseTypeV0                     = holo::map::format::Base;
using RawRoadTypeV0                     = holo::map::format::Road;
using RawLaneTypeV0                     = holo::map::format::Lane;
using RawLaneGroupTypeV0                = holo::map::format::LaneGroup;
using RawLaneBoundaryTypeV0             = holo::map::format::LaneBoundary;
using RawObjectTypeV0                   = holo::map::format::ObjectInfo;
using RawObjectLinearInfoTypeV0         = holo::map::format::ObjectLinearInfo;
using RawObjectRegionalInfoTypeV0       = holo::map::format::ObjectRegionalInfo;
using RawObjectPedestrianCrossingTypeV0 = holo::map::format::ObjectPedestrianCrossing;
using RawObjectStopLineTypeV0           = holo::map::format::ObjectStopLine;
using RawTrafficLightTypeV0             = holo::map::format::ObjectTrafficLight;
using RawTrafficLightGroupTypeV0        = holo::map::format::ObjectTrafficLightGroup;
using RawObjectTrafficSignTypeV0        = holo::map::format::ObjectTrafficSign;
using RawObjecgParkingLotTypeV0         = holo::map::format::ObjectParkingLot;
using RawObjectParkingFloorTypeV0       = holo::map::format::ObjectParkingFloor;
using RawObjectParkingPoiTypeV0         = holo::map::format::ObjectParkingPoi;
using RawObjectParkingSpaceTypeV0       = holo::map::format::ObjectParkingSpace;
using RawObjectParkingBackgroundTypeV0  = holo::map::format::ObjectParkingBackground;
using RawQuasiDynamicLaneTypeV0         = holo::map::format::QuasiDynamicLane;
using RawQuasiDynamicLaneGroupTypeV0    = holo::map::format::QuasiDynamicLaneGroup;
using RawQuasiDynamicRegionTypeV0       = holo::map::format::QuasiDynamicRegion;

/// Redefine auxiliary attribute types.
using RawLaneSequenceTypeV0                 = holo::int8_t;
using RawRoadAttributeTypeV0                = holo::map::format::RoadAttribute;
using RawRoadAttributeVectorTypeV0          = std::vector<RawRoadAttributeTypeV0>;
using RawLaneWidthInfoTypeV0                = holo::map::format::LaneWidthInfo;
using RawLaneWidthInfoVectorTypeV0          = std::vector<RawLaneWidthInfoTypeV0>;
using RawSpeedLimitInfoTypeV0               = holo::map::format::SpeedLimitInfo;
using RawSpeedLimitInfoVectorTypeV0         = std::vector<RawSpeedLimitInfoTypeV0>;
using RawLaneBoundaryInfoTypeV0             = holo::map::format::LaneBoundaryInfo;
using RawLaneBoundaryInfoVectorTypeV0       = std::vector<RawLaneBoundaryInfoTypeV0>;
using RawLaneBoundaryElementTypeV0          = holo::map::format::LaneBoundaryElement;
using RawLaneBoundaryElementVectorTypeV0    = std::vector<RawLaneBoundaryElementTypeV0>;
using RawMapConditionTypeV0                 = holo::map::format::MapCondition;
using RawMapConditionVectorTypeV0           = std::vector<RawMapConditionTypeV0>;

/// Redefine shared pointer types for raw map data features.
using RawBaseSPtrTypeV0                     = std::shared_ptr<RawBaseTypeV0>;
using RawRoadSPtrTypeV0                     = std::shared_ptr<RawRoadTypeV0>;
using RawLaneSPtrTypeV0                     = std::shared_ptr<RawLaneTypeV0>;
using RawLaneGroupSPtrTypeV0                = std::shared_ptr<RawLaneGroupTypeV0>;
using RawLaneBoundarySPtrTypeV0             = std::shared_ptr<RawLaneBoundaryTypeV0>;
using RawObjectSPtrTypeV0                   = std::shared_ptr<RawObjectTypeV0>;
using RawObjectLinearInfoSPtrTypeV0         = std::shared_ptr<RawObjectLinearInfoTypeV0>;
using RawObjectRegionalInfoSPtrTypeV0       = std::shared_ptr<RawObjectRegionalInfoTypeV0>;
using RawObjectPedestrianCrossingSPtrTypeV0 = std::shared_ptr<RawObjectPedestrianCrossingTypeV0>;
using RawObjectStopLineSPtrTypeV0           = std::shared_ptr<RawObjectStopLineTypeV0>;
using RawTrafficLightSPtrTypeV0             = std::shared_ptr<RawTrafficLightTypeV0>;
using RawTrafficLightGroupSPtrTypeV0        = std::shared_ptr<RawTrafficLightGroupTypeV0>;
using RawObjectTrafficSignSPtrTypeV0        = std::shared_ptr<RawObjectTrafficSignTypeV0>;
using RawObjectParkingLotSPtrTypeV0         = std::shared_ptr<RawObjecgParkingLotTypeV0>;
using RawObjectParkingFloorSPtrTypeV0       = std::shared_ptr<RawObjectParkingFloorTypeV0>;
using RawObjectParkingPoiSPtrTypeV0         = std::shared_ptr<RawObjectParkingPoiTypeV0>;
using RawObjectParkingSpaceSPtrTypeV0       = std::shared_ptr<RawObjectParkingSpaceTypeV0>;
using RawObjectParkingBackgroundSPtrTypeV0  = std::shared_ptr<RawObjectParkingBackgroundTypeV0>;
using RawQuasiDynamicLaneSPtrTypeV0         = std::shared_ptr<RawQuasiDynamicLaneTypeV0>;
using RawQuasiDynamicLaneGroupSPtrTypeV0    = std::shared_ptr<RawQuasiDynamicLaneGroupTypeV0>;
using RawQuasiDynamicRegionSPtrTypeV0       = std::shared_ptr<RawQuasiDynamicRegionTypeV0>;

/// Redefine vector types for raw map data features.
using RawBaseSPtrVectorTypeV0                       = std::vector<RawBaseSPtrTypeV0>;
using RawRoadSPtrVectorTypeV0                       = std::vector<RawRoadSPtrTypeV0>;
using RawLaneSPtrVectorTypeV0                       = std::vector<RawLaneSPtrTypeV0>;
using RawLaneGroupSPtrVectorTypeV0                  = std::vector<RawLaneGroupSPtrTypeV0>;
using RawLaneBoundarySPtrVectorTypeV0               = std::vector<RawLaneBoundarySPtrTypeV0>;
using RawObjectSPtrVectorTypeV0                     = std::vector<RawObjectSPtrTypeV0>;
using RawObjectLinearInfoSPtrVectorTypeV0           = std::vector<RawObjectLinearInfoSPtrTypeV0>;
using RawObjectRegionalInfoSPtrVectorTypeV0         = std::vector<RawObjectRegionalInfoSPtrTypeV0>;
using RawObjectPedestrianCrossingSPtrVectorTypeV0   = std::vector<RawObjectPedestrianCrossingSPtrTypeV0>;
using RawObjectStopLineSPtrVectorTypeV0             = std::vector<RawObjectStopLineSPtrTypeV0>;
using RawTrafficLightSPtrVectorTypeV0               = std::vector<RawTrafficLightSPtrTypeV0>;
using RawTrafficLightGroupSPtrVectorTypeV0          = std::vector<RawTrafficLightGroupSPtrTypeV0>;
using RawObjectTrafficSignSPtrVectorTypeV0          = std::vector<RawObjectTrafficSignSPtrTypeV0>;
using RawObjectParkingLotSPtrVectorTypeV0           = std::vector<RawObjectParkingLotSPtrTypeV0>;
using RawObjectParkingFloorSPtrVectorTypeV0         = std::vector<RawObjectParkingFloorSPtrTypeV0>;
using RawObjectParkingPoiSPtrVectorTypeV0           = std::vector<RawObjectParkingPoiSPtrTypeV0>;
using RawObjectParkingSpaceSPtrVectorTypeV0         = std::vector<RawObjectParkingSpaceSPtrTypeV0>;
using RawObjectParkingBackgroundSPtrVectorTypeV0    = std::vector<RawObjectParkingBackgroundSPtrTypeV0>;
using RawQuasiDynamicLaneSPtrVectorTypeV0           = std::vector<RawQuasiDynamicLaneSPtrTypeV0>;
using RawQuasiDynamicLaneGroupSPtrVectorTypeV0      = std::vector<RawQuasiDynamicLaneGroupSPtrTypeV0>;
using RawQuasiDynamicRegionSPtrVectorTypeV0         = std::vector<RawQuasiDynamicRegionSPtrTypeV0>;

/// Redefine geometry type for raw map data features.
using RawGeoBoxTypeV0           = holo::map::format::GeoBox;
using RawGeoPointTypeV0         = holo::map::format::GeoPoint;
using RawGeoCircleTypeV0        = holo::map::format::GeoCircle;
using RawGeometryTypeV0         = std::vector<RawGeoPointTypeV0>;
using RawPositionTypeV0         = holo::map::format::Position;
using RawPositionVectorTypeV0   = std::vector<RawPositionTypeV0>;

using OdometryType              = holo::common::Odometryd;
using MatchingResultType        = holo::common::LocalMapOdometryd::MatchingResult;
using MatchingResultVectorType  = holo::container::Vector<holo::common::LocalMapOdometryd::MatchingResult, 16>;

template <typename T>
using RawGeographicParameterTypeV0 = holo::map::format::geometry::GeographicParameter<T, holo::common::Coordinate>;

using RawGeoBoxParameterTypeV0 = holo::map::format::geometry::GeographicParameter<
    holo::map::format::GeoBox, holo::common::Coordinate>;

/// Redefine new version map data retriever.
using RetrieverSPtrType = holo::map::service::client::engine::RetrieverSPtrType;

class RawRetriever final
{
public:
    using ProfileType          = holo::map::service::client::engine::Retriever::ProfileType;
    using ProfileBaseCSPtrType = holo::map::service::client::engine::Retriever::ProfileBaseCSPtrType;

    holo::bool_t Init(RetrieverSPtrType ret);

    RetrieverSPtrType GetRetriever();

    holo::bool_t GetRoadById(RawFeatureIdTypeV0 const id, RawRoadSPtrTypeV0& feature);
    holo::bool_t GetRoadByIdV2(RawFeatureIdTypeV0 const id, RawRoadSPtrTypeV0& feature, holo::bool_t& valid);

    holo::bool_t GetLaneById(RawFeatureIdTypeV0 const id, RawLaneSPtrTypeV0& feature);
    holo::bool_t GetLaneByIdV2(RawFeatureIdTypeV0 const id, RawLaneSPtrTypeV0& feature, holo::bool_t& valid);

    holo::bool_t GetLaneGroupById(RawFeatureIdTypeV0 const id, RawLaneGroupSPtrTypeV0& feature);
    holo::bool_t GetLaneGroupByIdV2(RawFeatureIdTypeV0 const id, RawLaneGroupSPtrTypeV0& feature, holo::bool_t& valid);

    holo::bool_t GetLaneBoundaryById(RawFeatureIdTypeV0 const id, RawLaneBoundarySPtrTypeV0& feature);
    holo::bool_t GetLaneBoundaryByIdV2(RawFeatureIdTypeV0 const id, RawLaneBoundarySPtrTypeV0& feature, holo::bool_t& valid);

    holo::bool_t GetObjectInfoById(RawFeatureIdTypeV0 const id, RawObjectSPtrTypeV0& feature);
    holo::bool_t GetObjectInfoByIdV2(RawFeatureIdTypeV0 const id, RawObjectSPtrTypeV0& feature, holo::bool_t& valid);

    holo::bool_t HasRoad(RawFeatureIdTypeV0 const id);
    holo::bool_t HasLanes(RawFeatureIdTypeV0 const id);
    holo::bool_t HasLaneGroup(RawFeatureIdTypeV0 const id);
    holo::bool_t HasLaneBoundary(RawFeatureIdTypeV0 const id);
    holo::bool_t HasObjectInfo(RawFeatureIdTypeV0 const id);
    /**
     * @brief Get lane group and lanes by lane group id at same time.
     * @param [in] _id lane group id.
     * @param [out] _lane_group Lane group with id is _id.
     * @param [out] _lanes Lanes of _lane_group are sorted by lane sequence in ascending order,
     *              if _lane_group hasn't lane, it will be empty.
     * @return true Success;
     *         false Failure.
     */
    holo::bool_t GetLaneGroupAndLanesByLaneGroupID(RawFeatureIdTypeV0 const group_id, RawLaneGroupSPtrTypeV0& group,
        RawLaneSPtrVectorTypeV0& lanes, holo::bool_t const sort = false);

    /**
     * @brief Get lane group, lanes and lane boundaries by lane group id at same time.
     * @param [in] _id Lane group id.
     * @param [out] _lane_group Lane group with id is _id.
     * @param [out] _lanes Lanes of _lane_group are sorted by lane sequence in ascending order,
     *             if _lane_group hasn't lane, it will be empty.
     * @param [out] _boundaries LaneMarks of _lanes, they will sorted from left to right by lane sequence,
     *              if lane group hasn't lane, it will contain lane group left and right boundary,
     *              if lane group hasn't boundary, it will be empty.
     * @return true Success;
     *         false Failure.
     */
    holo::bool_t GetLaneGroupAndLanesAndBoundariesByLaneGroupID(RawFeatureIdTypeV0 const group_id, RawLaneGroupSPtrTypeV0& group,
        RawLaneSPtrVectorTypeV0& lanes, RawLaneBoundarySPtrVectorTypeV0& boundaries, holo::bool_t const sort = false);

    /**
     * @brief Get lane, left boundary and right boundary by lane id at same time.
     * @param [in] _id Lane id.
     * @param [out] _lane Lane with id is _id.
     * @param [out] _left_boundary Left lane boundary object of _lane, if _lane hasn't left lane boundary,
     *                             it will be nullptr.
     * @param [out] _right_boundary Right lane boundary object of _lane, if _lane hasn't right lane boundary,
     *                              it will be nullptr.
     * @return true Success;
     *         false Failure.
     */
    holo::bool_t GetLaneAndLaneBoundaryByLaneID(RawFeatureIdTypeV0 const lane_id, RawLaneSPtrTypeV0& lane,
        RawLaneBoundarySPtrTypeV0& left_boundary, RawLaneBoundarySPtrTypeV0& right_boundary);

    /**
     * @brief Get lane group and lanes by lane id at the same time.
     * 
     * @param[in] id A lane id.
     * @param[out] lane_group Lane group contained the target lane.
     * @param[out] lanes Lanes sorted by lane sequence in ascending order,
     *             if no lane in lane_group, it will be empty.
     * @return true: Success;
     *         false: An error occurs in this function.
     */
    holo::bool_t GetLaneGroupAndLanesByLaneId(RawFeatureIdTypeV0 const id, RawLaneGroupSPtrTypeV0& group,
                                      RawLaneSPtrVectorTypeV0& lanes, holo::bool_t const sort = false);

    holo::bool_t GetLaneGroupAndLanesByLaneIdWithIndex(RawFeatureIdTypeV0 const id, RawLaneGroupSPtrTypeV0& group,
        RawLaneSPtrVectorTypeV0& lanes, std::size_t& index, holo::bool_t const sort = false);

    holo::bool_t GetRoadLength(RawFeatureIdTypeV0 const id, DistanceTypeV0& length);

    holo::bool_t GetLaneLength(RawFeatureIdTypeV0 const id, DistanceTypeV0& length);

    holo::bool_t GetLaneGroupLength(RawFeatureIdTypeV0 const id, DistanceTypeV0& length);

    holo::bool_t GetParallelLanesOnLaneGroup(RawFeatureIdTypeV0 const group_id, RawFeatureIdVectorTypeV0& lane_ids);

    holo::bool_t GetParallelLaneBoundariesOnLaneGroup(RawFeatureIdTypeV0 const group_id, RawFeatureIdVectorTypeV0& boundary_ids,
        holo::bool_t const sort);

    holo::bool_t GetLaneGroupIdFromLaneId(RawFeatureIdTypeV0 const lane_id, RawFeatureIdTypeV0& group_id);

    holo::bool_t GetLaneGroupIdFromLaneBoundaryId(RawFeatureIdTypeV0 const boundary_id, RawFeatureIdTypeV0& group_id);

    holo::bool_t GetLaneGroupIdsByLaneIds(RawFeatureIdVectorTypeV0 const& lane_ids, RawFeatureIdVectorTypeV0& group_ids);

    holo::bool_t GetConnectedLanesV2(RawFeatureIdTypeV0 const lane_id, DirectionTypeV0 const dir, RawFeatureIdVectorTypeV0& connected_lane_ids);

    holo::bool_t GetLaneRefPoints(RawFeatureIdTypeV0 const lane_id, RawGeometryTypeV0& points);

    holo::bool_t GetLaneGroupRefPoints(RawFeatureIdTypeV0 const group_id, RawGeometryTypeV0& points);

    holo::bool_t GetLaneBoundaryRefPoints(RawFeatureIdTypeV0 const boundary_id, RawGeometryTypeV0& points);

    holo::bool_t GetLaneSeq(RawFeatureIdTypeV0 const lane_id, RawLaneSequenceTypeV0& lane_sequence);

    holo::bool_t IsLaneOfType(RawFeatureIdTypeV0 const lane_id, RawLaneTypeV0::LaneType const lane_type);

    holo::bool_t AreBothLanesInSameLaneGroup(RawFeatureIdTypeV0 const lane_id_1, RawFeatureIdTypeV0 const lane_id_2, holo::bool_t& result);

private:
    RetrieverSPtrType retriever_ = nullptr;
}; /// End of class RawRetriever.

/// Redefine raw retriever type for RawRetriever.
using RawRetrieverType = RawRetriever;
/// Redefine shared pointer for RawRetriever.
using RawRetrieverSPtrType = std::shared_ptr<RawRetrieverType>;

namespace access
{
/**
 * @addtogroup access
 * @{
 *
 */


/**
 * @brief Convert and return format::Ptr*** from raw pointer of a Profile.
 * 
 * @tparam ProfileType holo::map::service::client::profile::ProfileBaseCSPtrType.
 * @tparam FeatureType holo::map::format::PtrXXX.
 * @param[in] profile A profile type of holo::map::service::client::profile::XXXCSPtrType.
 * @param[out] feature A pointer to holo::map::format::PtrXXX, if this function return false,
 *             the output parameter will be nullptr.
 * @return true: No error.
 *         false: An error occurs in this function, refer to log for more details.
 */
template <typename T>
holo::bool_t GetRawFeatureFromProfile(holo::map::service::client::profile::ProfileBaseCSPtrType profile,
    typename holo::map::format::helper::FeatureTraits<T>::SPtrType& feature)
{
    feature = nullptr;

    if (nullptr == profile || nullptr == profile->GetRawPtr())
    {
        LOG(ERROR) << "GetRawFeatureFromProfile fail, invalid parameters";
        return false;
    }

    feature = nullptr;

    typename holo::map::format::helper::FeatureTraits<T>::SPtrType raw = std::dynamic_pointer_cast<
        typename holo::map::format::helper::FeatureTraits<T>::RawType>(profile->GetRawPtr());
    if (nullptr == raw)
    {
        LOG(ERROR) << "GetRawFeatureFromProfile fail, invalid pointer, name=" << profile->GetName()
                   << " id=" << profile->GetId();
        return false;
    }

    feature = raw;
    return true;
}

#if 0
template <typename Ret, typename Odometry, typename Distance, typename Id, typename Ids = std::vector<Id>>
MapErrorCode GetPathByDistance(Ret ret, Odometry const& odo, Distance const length, Ids& ids)
{
    ids.clear();

    MatchingResultVectorType results = odo.GetMatchingResults();
    if (results.empty())
    {
        LOG(ERROR) << "GetPathByDistance fail, invalid matching result, odo=" << holo::map::marshal::FormatToString(odo);
        return MapErrorCode::kFAILED;
    }

    holo::map::service::client::profile::ProfileBaseCSPtrType profile = nullptr;
    holo::map::service::client::profile::ProfileType const t 
        = holo::map::service::client::profile::ProfileType::kROUTING_PATH;

    MapErrorCode const status = ret->GetRetriever()->GetProfile(t, 0, profile);
    if (MapErrorCode::kOK != status && MapErrorCode::kNONE != status)
    {
        LOG(ERROR) << "GetPathByDistance fail, profile_type=" << static_cast<int>(t)
                   << " status=" << static_cast<int>(status);
        return status;
    }

    if (MapErrorCode::kOK == status && (nullptr == profile || nullptr == profile->GetRawPtr()))
    {
        LOG(ERROR) << "GetPathByDistance fail, profile_type=" << static_cast<int>(t)
                   << " status=" << static_cast<int>(status);
        return MapErrorCode::kFAILED;
    }

    holo::map::service::client::profile::ProfileBase::RawProfileSPtrType base = profile->GetRawPtr();
    holo::map::format::PtrRoutingPath path = std::dynamic_pointer_cast<holo::map::format::RoutingPath>(base);

    Id const first_id = results.front().link_id;
    Distance sum_length = results.front().longitudinal_off_end;

    std::vector<holo::map::format::RoutingPathElement> const& elements = *path->GetPtrElements();
    std::size_t const size = elements.size();
    
    holo::bool_t find_first = false;;
    for (std::size_t i = 0; i < size; ++i)
    {
        Id const curr_id = elements[i].GetId();
        if (!find_first)
        {
            if (first_id != curr_id)
            {
                continue;
            }
            find_first = true;
        }

        ids.push_back(curr_id);

        Distance curr_length = elements[i].GetLengthCm();
        sum_length += curr_length;
        if (sum_length  > length)
        {
            break;
        }
    }

    if (ids.empty())
    {
        LOG(ERROR) << "GetPathByDistance fail, invalid odometry, odo=" << holo::map::marshal::FormatToString(odo);
        return MapErrorCode::kFAILED;
    }

    return status;
}
#endif

/**
 * @brief Get raw map feature by id from retriever.
 * 
 * @tparam Ret holo::map::service::client::engine::helper::raw::RawRetrieverSPtrType.
 * @tparam Type holo::map::format::helper::FeatureType.
 * @tparam Id holo::map::format::helper::FeatureIdType.
 * @tparam T holo::map::format::Ptr***.
 * @param[in] ret A retriever shared pointer refer to RawRetrieverSPtrType.
 * @param[in] type Map feature type.
 * @param[in] id Map feature id.
 * @param[out] feature Map feature shared pointer.
 * @return kOK: No error.
 *         kNONE: Target map feature not exist in retriever, note: feature will be nullptr.
 *         kFAILED: An error occurs in this function, please see logs for more details.
 */
template <typename Ret, typename Type, typename Id, typename T>
MapErrorCode GetRawFeatureById(Ret ret, Type const type, Id const id, 
    typename holo::map::format::helper::FeatureTraits<T>::SPtrType& feature)
{
    feature = nullptr;

    holo::map::service::client::profile::ProfileBaseCSPtrType profile = nullptr;

    holo::map::service::client::profile::ProfileType const t = 
        holo::map::service::client::profile::helper::FeatureType2ProfileType(type);

    MapErrorCode const status = ret->GetRetriever()->GetProfile(t, id, profile);
    if (MapErrorCode::kOK != status && MapErrorCode::kNONE != status)
    {
        LOG(ERROR) << "GetRawFeatureById fail, GetProfile fail, id=" << id
                   << " feature_type=" << static_cast<int>(type)
                   << " profile_type=" << static_cast<int>(t)
                   << " status=" << static_cast<int>(status);
        return status;
    }

    if (MapErrorCode::kOK == status && (nullptr == profile || nullptr == profile->GetRawPtr()))
    {
        LOG(ERROR) << "GetRawFeatureById fail, invalid profile, id=" << id
                   << " feature_type=" << static_cast<int>(type)
                   << " profile_type=" << static_cast<int>(t)
                   << " status=" << static_cast<int>(status);
        return MapErrorCode::kFAILED;
    }

    if (MapErrorCode::kNONE != status)
    {
        holo::bool_t const ok = GetRawFeatureFromProfile<typename holo::map::format::helper::FeatureTraits<T>::SPtrType>(
            profile, feature);
        if (!ok || nullptr == feature)
        {
            LOG(ERROR) << "GetRawFeatureById fail, GetRawFeatureFromProfile fail, id=" << id
                       << " feature_type=" << static_cast<int>(type)
                       << " profile_type=" << static_cast<int>(t)
                       << " ok=" << ok;
            return MapErrorCode::kFAILED;
        }
    }

    return status;
}

template <typename Ret, typename Box, typename Type, typename Id, typename Ids = std::vector<Id>>
MapErrorCode GetRawFeatureIdsByScopeFromTile(Ret ret, RawGeographicParameterTypeV0<Box> const& box,
    Type const type, Id const id,  Ids& ids)
{
    Ids tile_ids;

    RawGeographicParameterTypeV0<Box> scope = box;

    holo::bool_t ok = false;
    if (box.coordinate.GetType() == holo::common::Coordinate::Type::WGS84)
    {
        ok = holo::map::format::geometry::ConvertWGS84ToUTM(box, scope);
    }
    else if (box.coordinate.GetType() ==  holo::common::Coordinate::Type::UTM6)
    {
        ok = true;
    }

    if (!ok)
    {
        LOG(ERROR) << "GetRawFeatureIdsByScope fail, CalculateTileBy*** fail,"
                   << " coordinate=" << holo::map::marshal::FormatToString(box.coordinate);
        return MapErrorCode::kFAILED;
    }

    holo::map::service::client::profile::ProfileType const profile_type = 
        holo::map::service::client::profile::helper::FeatureType2ProfileType(type);
    holo::map::service::client::profile::ProfileTypeValue const profile_sub_type =
        holo::map::service::client::profile::helper::FeatureType2ProfileSubType(type);

    Ids profile_ids;
    MapErrorCode ec = ret->GetRetriever()->GetProfileIds(profile_type, profile_sub_type, id, profile_ids);
    if (MapErrorCode::kOK != ec)
    {
        LOG(ERROR) << "GetRawFeatureIdsByScope fail, GetProfileIds fail, tile_id=" << id
                   << " profile_type=" << static_cast<int>(profile_type) << " feature_type=" << static_cast<int>(type)
                   << " coordinate=" << holo::map::marshal::FormatToString(box.coordinate);
        return MapErrorCode::kFAILED;
    }

    Ids result_ids;
    for (Id const profile_id : profile_ids)
    {
        holo::map::service::client::profile::ProfileBaseCSPtrType profile = nullptr;
        ec = ret->GetRetriever()->GetProfile(profile_type, profile_id, profile);
        if (MapErrorCode::kNONE == ec)
        {
            continue;
        }
        if (MapErrorCode::kOK != ec || nullptr == profile || nullptr == profile->GetRawPtr())
        {
            LOG(ERROR) << "GetRawFeatureIdsByScope fail, GetProfileIds fail, tile_id=" << id
                       << " profile_id=" << profile_id << " profile_type=" << static_cast<int>(profile_type)
                       << " feature_type=" << static_cast<int>(type);
            return MapErrorCode::kFAILED;
        }

        holo::map::format::helper::FeatureBaseSPtrType feature = profile->GetRawPtr();
        if (feature->GetFeatureType() != type)
        {
            continue;
        }
    
        Box bb;
        ok = holo::map::format::geometry::CalculateBoundingBox2D<holo::map::format::helper::FeatureBaseSPtrType,
            Box>(feature, bb);
        if (!ok)
        {
            LOG(ERROR) << "GetRawFeatureIdsByScope fail, CalculateBoundingBox2D fail, tile_id=" << id
                       << " profile_id=" << profile_id << " profile_type=" << static_cast<int>(profile_type)
                       << " feature_type=" << static_cast<int>(type);
            return MapErrorCode::kFAILED;
        }

        holo::bool_t const overlapped = holo::map::format::geometry::AreBoundingBoxesOverlapped2D
            <Box>(bb, scope.parameter);
        if (overlapped)
        {
            holo::map::utility::UniquePush(result_ids, profile_id);
        }
    }

    ids = std::move(result_ids);
    return MapErrorCode::kOK;
}

/**
 * @brief Get all the raw map feature ids overlapped with target scope.
 * 
 * @tparam Ret holo::map::service::client::engine::helper::raw::RawRetrieverSPtrType.
 * @tparam Box holo::map::format::GeoBox.
 * @tparam Type holo::map::format::helper::FeatureType.
 * @tparam Id holo::map::format::helper::FeatureIdType.
 * @param[in] ret A retriever shared pointer refer to RawRetrieverSPtrType.
 * @param[in] box A bounding box with coordinate reference system.
 * @param[in] type Map feature type.
 * @param[out] ids All the available map feature ids.
 * @return kOK: No error.
 *         kNONE: Target map feature not exist in retriever, note: feature will be nullptr.
 *         kFAILED: An error occurs in this function, please see logs for more details.
 */
template <typename Ret, typename Box, typename Type, typename Id, typename Ids = std::vector<Id>>
MapErrorCode GetRawFeatureIdsByScope(Ret ret, RawGeographicParameterTypeV0<Box> const& box,
    Type const type, Ids& ids)
{
    Ids tile_ids;

    RawGeographicParameterTypeV0<Box> scope = box;

    holo::bool_t ok = false;
    if (box.coordinate.GetType() == RawGeographicParameterTypeV0<Box>::CoordinateType::Type::WGS84)
    {
        ok = holo::map::geometry::CalculateTileByLatLonV2(box.parameter, tile_ids);
        holo::map::format::geometry::ConvertWGS84ToUTM(box, scope);
    }
    else if (box.coordinate.GetType() ==  RawGeographicParameterTypeV0<Box>::CoordinateType::Type::UTM6)
    {
        ok = holo::map::geometry::CalculateTileByUTM(box.parameter, tile_ids, box.coordinate.GetUtmZoneId(),
            box.coordinate.GetUtmSouthFlag());
    }

    if (!ok)
    {
        LOG(ERROR) << "GetRawFeatureIdsByScope fail, CalculateTileBy*** fail,"
                   << " coordinate=" << holo::map::marshal::FormatToString(box.coordinate);
        return MapErrorCode::kFAILED;
    }

    Ids result_ids;
    for (Id const tile_id : tile_ids)
    {
        Ids profile_ids;
        if (!ret->GetRetriever()->IsProfileExist(holo::map::service::client::profile::ProfileType::kTILE, tile_id))
        {
            continue;
        }

        MapErrorCode const ec = GetRawFeatureIdsByScopeFromTile<Ret, Box, Type, Id, Ids>(ret, box, type,
            tile_id, profile_ids);
        if (MapErrorCode::kOK != ec)
        {
            LOG(ERROR) << "GetRawFeatureIdsByScope fail, GetProfileIds fail, tile_id=" << tile_id
                       << " coordinate=" << holo::map::marshal::FormatToString(box.coordinate);
            return MapErrorCode::kFAILED;
        }

        holo::map::utility::UniqueAppend(result_ids, profile_ids);
    }

    ids = std::move(result_ids);
    return MapErrorCode::kOK;
}

/**
 * @brief Check if the map feature is existed in cache.
 * 
 * @tparam Ret holo::map::service::client::engine::helper::raw::RawRetrieverSPtrType.
 * @tparam Type holo::map::format::helper::FeatureType.
 * @tparam Id holo::map::format::helper::FeatureIdType.
 * @param[in] ret A shared pointer refer to RawRetrieverSPtrType.
 * @param[in] type Map feature type.
 * @param[in] id Map feature id.
 * @return true: Target map feature already exist;
 *         false: Otherwise.
 */
template <typename Ret, typename Type, typename Id>
holo::bool_t IsRawFeatureAlreadyExisted(Ret ret, Type const type, Id const id)
{
    holo::map::service::client::profile::ProfileType const profile_type = 
        holo::map::service::client::profile::helper::FeatureType2ProfileType(type);

    return ret->GetRetriever()->IsProfileExist(profile_type, id);
}

/**
 * @brief Get lane group ids in specified scope
 *
 * @details If tile cross through the scope, all lane groups of this tile will be added
 *
 * @tparam T GeoCircle/GeoBox/GeoPoint
 *
 * @param[in]  _ret        Pointer of retriever
 * @param[in]  _geo_extent Specified scope
 * @param[out] _lane_group_ids   lane group ids
 *
 * @return true:  Operation successful.
 * @return false: Otherwise
 */
template <typename T>
holo::bool_t GetLaneGroupIdsInScope(RawRetrieverSPtrType _ret, T const& _geo_extent,
    RawFeatureIdVectorTypeV0& _lanegroup_ids);
template <>
holo::bool_t GetLaneGroupIdsInScope(RawRetrieverSPtrType _ret, RawGeoPointTypeV0 const& _geo_extent,
    RawFeatureIdVectorTypeV0& _lanegroup_ids);
template <>
holo::bool_t GetLaneGroupIdsInScope(RawRetrieverSPtrType _ret, RawGeoCircleTypeV0 const& _geo_extent,
    RawFeatureIdVectorTypeV0& _lanegroup_ids);
template <>
holo::bool_t GetLaneGroupIdsInScope(RawRetrieverSPtrType _ret, RawGeoBoxTypeV0 const& _geo_extent,
    RawFeatureIdVectorTypeV0& _lanegroup_ids);

/**
 * @brief Whether or not the target road is a toll booth.
 *
 * @param[in] ret The handle of database engine.
 * @param[in] road_t A road id.
 * @param[out] result If true, the road is a toll booth;
 *                    If false, the road is not a toll booth.
 *
 * @return true: No error.
 *         false: An error occurs in this function and the result is invalid.
 */
holo::bool_t IsTollBoothByRoadId(RawRetrieverSPtrType ret, RawFeatureIdTypeV0 const road_id, holo::bool_t& result);

/**
 * @brief Whether or not the target road is a toll booth.
 *
 * @param[in] road A road object from database engine.
 * @param[out] result If true, the road is a toll booth;
 *                    If false, the road is not a toll booth.
 *
 * @return true: No error.
 *         false: An error occurs in this function and the result is invalid.
 */
holo::bool_t IsTollBoothByRoad(RawRoadSPtrTypeV0 const road, holo::bool_t& result);

/**
 * @brief Check if the current lane group is a toll booth.
 *
 * @param[in]  ret           Pointer of retriever
 * @param[in]  lane_group_id A lane group id.
 * @param[out] result If true, the road is a toll booth;
 *                    If false, the road is not a toll booth.
 *
 * @return true: No error.
 *         false: An error occurs in this function and the result is invalid.
 */
holo::bool_t IsTollBoothByLaneGroupId(RawRetrieverSPtrType const ret, RawFeatureIdTypeV0 const lane_group_id, holo::bool_t& result);

/**
 * @brief Check if the current lane group is a toll booth.
 *
 * @param[in] ret The handle of database engine.
 * @param[in] lane_group A lane group object.
 * @param[out] result If true, the road is a toll booth;
 *                    If false, the road is not a toll booth.
 *
 * @return true: No error.
 *         false: An error occurs in this function and the result is invalid.
 */
holo::bool_t IsTollBoothByLaneGroup(RawRetrieverSPtrType const ret, RawLaneGroupSPtrTypeV0 const lane_group, holo::bool_t& result);

/**
 * @brief Whether or not the current lane is an emergency lane.
 *
 * @param[in] ret The handle of database engine.
 * @param[in] id Target lane id.
 * @param[out] result If true, the current lane is an emergency lane;
 *                    If false, otherwise.
 * @return true: No error.
 *         false: An error occurs in this function.
 */
holo::bool_t IsEmergencyLane(RawRetrieverSPtrType const ret, RawFeatureIdTypeV0 const id, holo::bool_t& result);

/**
 * @brief Whether or not the current lane is a hard shoulder.
 * 
 * @note The hard shoulder lane is the leftmost lane in a lane group, the width
 *       is less than 2.0 meters in general(Just in china).
 * @param[in] ret The handle of database engine.
 * @param[in] id Target lane id.
 * @param[out] result If true, the current lane is a hardshoulder lane;
 *                    If false, otherwise.
 * @return true: No error.
 *         false: An error occurs in this function.
 */
holo::bool_t IsHardShoulderLane(RawRetrieverSPtrType const ret, RawFeatureIdTypeV0 const id, holo::bool_t& result);

holo::bool_t IsAutoDrivingLane(RawLaneSPtrTypeV0 const lane);

/**
 * @brief Get Auto-Driving Lanes In a LaneGroup
 *
 * @param[in] ret           Pointer of retriever
 * @param[in] lane_group_id Lane Group id. 
 * @param[out] lane_ids     Auto-Driving Lanes
 * @param[in] with_emergency_lane If has emergency lane
 *
 * @return true:  Operation successful.
 * @return false: Otherwise.
 */
holo::bool_t GetDrivingLanes(RawRetrieverSPtrType const ret, RawFeatureIdTypeV0 const lane_group_id, RawFeatureIdVectorTypeV0& lane_ids,
                     holo::bool_t const with_emergency_lane = true);

holo::bool_t GetDrivingLanes(RawRetrieverSPtrType const ret, RawFeatureIdTypeV0 const lane_group_id,
    RawLaneSPtrVectorTypeV0& ptr_lanes, holo::bool_t const with_emergency_lane = true);

/**
 * Describe the speed limit information of a lane/road.
 */
struct SpeedLimitType
{
    /**
     * Redefine the inner type.
     */
    using ValueType  = holo::uint16_t;
    using VectorType = std::vector<SpeedLimitType>;

    ValueType   min             = 0;    ///< Minimum speed limit value(Uint: km/h).
    ValueType   max             = 0;    ///< Maximum speed limit value(Unit: km/h).
    Distance    start_offset    = 0.0;  ///< Percent of the length of a lane/road(Unit: %).
    Distance    end_offset      = 0.0;  ///< Percent of the length of a lane/road(Unit: %).

    /**
     * @brief Constructor without parameters.
     */
    SpeedLimitType() {}

    /**
     * @brief Constructor with parameters.
     * 
     * @param[in] vmin The minimum speed limit(Uint: km/h).
     * @param[in] vmax The maximux speed limit(Uint: km/h).
     * @param[in] s_offset Percent of the length of a lane/road(Unit: %).
     * @param[in] e_offset Percent of the length of a lane/road(Unit: %).
     * 
     * @return Nothing.
     */
    SpeedLimitType(ValueType const vmin, ValueType const vmax, Distance const s_offset, Distance const e_offset)
        : min(vmin), max(vmax), start_offset(s_offset), end_offset(e_offset)
    {}
};

/**
 * @brief Get speed limit information from a lane.
 * 
 * @param[in] ret The handle of database engine.
 * @param[in] id The target lane id.
 * @param[out] limits Speed limit information.
 * @return true: No error;
 *         false: An error occurs in this function.
 */
holo::bool_t GetSpeedLimitByLaneId(RawRetrieverSPtrType const ret, RawFeatureIdTypeV0 const id,
    SpeedLimitType::VectorType& limits);

/**
 * @brief Definitions for ramp type.
 */
enum class AccessRampType : ::holo::uint8_t
{
    RAMP_TYPE_NOT_ATTRIBUTED = 0, ///< If a road with type of motorway, it shounld be without ramp type.
    RAMP_TYPE_JCT            = 1, ///< A road connected with motorway and motorway.
    RAMP_TYPE_ENTRANCE_RAMP  = 2, ///< A road connected from a ramp to a motorway.
    RAMP_TYPE_EXIT_RAMP      = 3, ///< A road connected fromt a motorway to a ramp.
    RAMP_TYPE_SPLITED_RAMP   = 4, ///< A ramp raod splited to two ramp roads.
    RAMP_TYPE_MERGED_RAMP    = 5, ///< A ramp raod merged from two ramp raods.
    RAMP_TYPE_UNDEFINED      = 6  ///< Placeholder.
};

/**
 * @brief Get ramp type from given lane group.
 *
 * @param[in] _ret Database engine.
 * @param[in] _lane_group A lane group object.
 * @param[out] type The ramp type of target lane group.
 *
 * @return true: No error.
 *         false: An error occurs in this function.
 */
 holo::bool_t GetLaneGroupRampType(RawRetrieverSPtrType _ret, RawLaneGroupSPtrTypeV0 _lane_group, AccessRampType& type);

/**
 * @brief Get minimum/maximum index-on-lane group lane boundary from succeeding lane boundaries.
 *
 * @param[in]  _ptr_ret              Pointer of retriever
 * @param[in]  _lane_ids             Lane ids
 * @param[in]  _current_lane_boundary_id Current lane boundary
 * @param[in]  _invert               True means get succeeding maximum index-on-lane group, vice versa
 * @param[out] _succ_lane_boundary_id    Succeeding minimum/maximum index-on-lane group lane boundary.
 *
 * @return true:  Found a valid lane boundary id
 * @return false: Otherwise.
 */
holo::bool_t GetSuccMinIndexLaneBoundary(RawRetrieverSPtrType _ptr_ret, RawFeatureIdVectorTypeV0 const& _lane_ids,
    RawFeatureIdTypeV0 const _current_lane_boundary_id, holo::bool_t const _invert,
    RawFeatureIdTypeV0& _succ_lane_boundary_id);

/**
 * @brief Get approximate lane boundary info index from a complex lane boundary object for a Road, LaneGroup or Lane.
 *
 * @detail Reference: https://wiki.holomatic.cn/pages/viewpage.action?pageId=56757646
 *
 * @param[in] lb A laneBoundary object.
 * @param[out] info_index Index of LaneBoundaryInfo in LaneBoudary, ref points are calculated from this LaneBoundaryInfo.
 * @param[out] has_lane_boundary If no lane boundary in LaneBoundary, it will be false and this function returns ture,
 *                               otherwise will be true.
 * @param[in] lane_boundary_direction A LaneBoundary with several sorted LaneBoundaryInfos(Sorted from right to left in China),
 *                                    lane_boundary_direction is used to find the real lane boundary info.
 *                                    if the LaneBoundary on the left of target road/lane/lanegroup, the direction is DIR_LEFT,
 *                                    if the LaneBoundary on the right of target road/lane/lanegroup, the direction is DIR_RIGHT.
 * @param[in] driving_direction Driving direction.
 *
 * @return true:  Operation successful.
 * @return false: Otherwise.
 */
holo::bool_t GetApproximateLaneBoundaryInfoIndex(RawLaneBoundarySPtrTypeV0 const& lb,
    std::size_t& info_index, holo::bool_t& has_lane_boundary, DirectionTypeV0 const lane_boundary_direction,
    DrivingDirectionTypeV0 const driving_direction = DrivingDirectionTypeV0::DRIVING_DIR_RIGHT_HAND);

/**
 * @}
 *
 */

} ///< namespace access

/**
 * @}
 *
 */

} ///< namespace raw
} ///< namespace helper
} ///< namespace engine
} ///< namespace client
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_CLIENT_ENGINE_HELPER_H_ */
