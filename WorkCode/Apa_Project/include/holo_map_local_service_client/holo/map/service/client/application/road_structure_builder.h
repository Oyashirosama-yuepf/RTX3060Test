/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file road_structure_builder.h
 * @brief RoadStructureBuilder
 * @author wanghaiyang@holomatic.com
 * @date "2020-10-23"
 */

#ifndef HOLO_MAP_SERVICE_CLIENT_APPLICATION_ROAD_STRUCTURE_BUILDER_H_
#define HOLO_MAP_SERVICE_CLIENT_APPLICATION_ROAD_STRUCTURE_BUILDER_H_

#include <memory>
#include <vector>

#include <holo/common/odometry.h>
#include <holo/core/types.h>
#include <holo/map/common/types.h>
#include <holo/map/service/client/application/road_boundary.h>
#include <holo/map/service/client/application/road_structure.h>
#include <holo/map/service/client/matcher/matcher.h>
#include <holo/map/service/client/profile/lane_boundary.h>

namespace holo
{
namespace map
{
namespace service
{
namespace client
{
namespace application
{

class RoadStructureBuilder
{
public:
    using ScalarType = holo::float64_t;
    using DistanceType = ScalarType;
    using OdometryType  = holo::common::Odometryd;
    using Point3dType   = OdometryType::Pose3Type::Point3Type;

    using RetrieverSPtrType     = holo::map::service::client::engine::RetrieverSPtrType;
    using MatchingResultType    = holo::map::service::client::matcher::MatchingResult;

    using ProfileIdType                = RoadStructure::ProfileIdType;
    using LaneBoundaryType             = holo::map::service::client::profile::LaneBoundary;
    using LaneBoundarySPtrType         = holo::map::service::client::profile::LaneBoundarySPtrType;
    using LaneBoundaryCSPtrType         = holo::map::service::client::profile::LaneBoundaryCSPtrType;
    using LaneBoundarySPtrVectorType   = std::vector<holo::map::service::client::profile::LaneBoundarySPtrType>;
    using LaneBoundaryCSPtrVectorType  = std::vector<holo::map::service::client::profile::LaneBoundaryCSPtrType>;

    using RoadBoundaryType              = holo::map::service::client::application::RoadBoundary;
    using RoadBoundarySPtrType          = holo::map::service::client::application::RoadBoundarySPtrType;
    using RoadBoundaryCSPtrType         = holo::map::service::client::application::RoadBoundaryCSPtrType;
    using RoadBoundarySPtrVectorType    = std::vector<RoadBoundarySPtrType>;
    using RoadBoundaryCSPtrVectorType   = std::vector<RoadBoundaryCSPtrType>;
    
    RoadStructureBuilder();
    virtual ~RoadStructureBuilder();

    holo::bool_t Init(RetrieverSPtrType ret);

    RetrieverSPtrType GetRetriever() const;

#if 1 /*TEMPORARY_CODE_FOR_URBAN_PILOT*/
    holo::bool_t GetDegradingFlag() const;

    void SetDegradingFlag(holo::bool_t const f);
#endif /* TEMPORARY_CODE_FOR_URBAN_PILOT */

    MapErrorCode MakeRoadStructures(MatchingResultType const& r, RoadStructuresCSPtrType& structures,
        DistanceType const front_distance = 200.0f, DistanceType const rear_distance = 200.0f);

    MapErrorCode MakeRoadStructures(Point3dType const p, ProfileIdType const group_id,
        RoadStructuresCSPtrType& structures, DistanceType const front_distance = 200.0f, DistanceType const rear_distance = 200.0f);

    MapErrorCode MakeRoadBoundaries(MatchingResultType const& r, RoadBoundaryCSPtrVectorType& left_boundaries,
        RoadBoundaryCSPtrVectorType& right_boundaries, DistanceType const distance = 200.0f);

    MapErrorCode MakeRoadBoundaries(Point3dType const p, ProfileIdType const group_id, ProfileIdType const lane_id,
        RoadBoundaryCSPtrVectorType& left_boundaries, RoadBoundaryCSPtrVectorType& right_boundaries,
        DistanceType const distance = 200.0f);

    MapErrorCode MakeRoadBoundaries(MatchingResultType const& r, RoadBoundaryCSPtrVectorType& boundaries,
        DistanceType const distance = 200.0f);

    MapErrorCode MakeRoadBoundaries(Point3dType const p, ProfileIdType const group_id, RoadBoundaryCSPtrVectorType& boundaries,
        DistanceType const distance = 200.0f);

    holo::bool_t AreLanesConnectedDirectly(ProfileIdType const lane_id_1, ProfileIdType const lane_id_2,
        holo::bool_t& result, DistanceType const distance = 200.0f);
    holo::bool_t AreLaneGroupsConnectedDirectly(ProfileIdType const group_id_1, ProfileIdType const group_id_2,
        holo::bool_t& result, DistanceType const distance = 200.0f);
    holo::bool_t AreLaneBoundariesConnectedDirectly(ProfileIdType const boundary_id_1, ProfileIdType const boundary_id_2,
        holo::bool_t& result, DistanceType const distance = 200.0f);

    holo::bool_t AreLanesNeighbors(ProfileIdType const lane_id_1, ProfileIdType const lane_id_2, holo::bool_t& result);

    /**
     * @brief Check if a lane with a forked lane boundary(both left and right).
     * 
     * @detail  |>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Driving Direction>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>|
     *          |---------------------------Left Boundary------------------------------------|
     *          |(Start)                           P1                     (Target lane) (End)|
     *          |---------------------------Right Boundary-----------------------------------|
     *          |<------------Rear Direction------><---------------Front Direction---------->|
     * P1: Target point and projection point.
     * Ref line: Middle(Approximate) line of target lane.
     * 
     * @param[in] p A point will be projected on ref line of the target lane, the front direction between
     *              projection and end point, the rear direction between projection and start point.
     * @param[in] id A lane id.
     * @param[out] left_result If true, in both directions(front and rear), the left boundary is un-forked.
     * @param[out] right_result If true, in both directions(front and rear), the right boundary is un-forked.
     * @param[in] front_distance Required distance in front direction(Unit: meter).
     * @param[in] rear_distance Required distance in rear direction(Unit: meter).
     * @return true: No error.
     *         false: An error occurs in this function.
     */
    holo::bool_t IsLaneBoundaryForkedByLaneId(Point3dType const& p, ProfileIdType const id,
        holo::bool_t& left_result, holo::bool_t& right_result, DistanceType const front_distance = 200.0f,
        DistanceType const rear_distance = 200.0f);

    /**
     * @brief Check if a lane boundary is forked.
     * 
     * @detail  |>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Driving Direction>>>>>>>>>>>>>>>>>>>>>>>>>>>>|
     *          |---------------------------Lane Boundary------------------------------------|
     *          |(Start)                           P1                                   (End)|
     *          |<------------Rear Direction------><---------------Front Direction---------->|
     * P1: Target point and projection point.
     * 
     * @param[in] p A point will be projected on the target lane boundary, the front direction between
     *              projection and end point, the rear direction between projection and start point.
     * @param[in] id A lane boundary id.
     * @param[out] result If true, in both directions(front and rear), the boundary is un-forked.
     * @param[in] front_distance Required distance in front direction(Unit: meter).
     * @param[in] rear_distance Required distance in rear direction(Unit: meter).
     * @return true: No error.
     *         false: An error occurs in this function.
     */
    holo::bool_t IsLaneBoundaryForkedByLaneBoundaryId(Point3dType const& p, ProfileIdType const boundary_id,
        holo::bool_t& result, DistanceType const front_distance = 200.0f, DistanceType const rear_distance = 200.0f);

    static holo::bool_t IsLaneBoundaryTypeChanged(LaneBoundaryCSPtrType boundary, DistanceType const distance,
        holo::bool_t& result, DistanceType const offset = 0.0);

    static holo::bool_t IsLaneBoundariesTypeChanged(LaneBoundaryCSPtrVectorType const& boundaries, DistanceType const distance,
        holo::bool_t& result, DistanceType const offset = 0.0);

private:
    class RoadStructureBuilderInner;
    std::unique_ptr<RoadStructureBuilderInner> inner_;
}; ///< End of class RoadStructure.

using RoadStructureBuilderSPtrType      = std::shared_ptr<RoadStructureBuilder>;
using RoadStructureBuilderCSPtrType     = std::shared_ptr<RoadStructureBuilder const>;

} ///< namespace application
} ///< namespace client
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_CLIENT_APPLICATION_ROAD_STRUCTURE_BUILDER_H_ */
