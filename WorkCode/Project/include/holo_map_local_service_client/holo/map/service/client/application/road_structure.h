/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file road_structure.h
 * @brief RoadStructure
 * @author wanghaiyang@holomatic.com
 * @date "2020-10-23"
 */

#ifndef HOLO_MAP_SERVICE_CLIENT_APPLICATION_ROAD_STRUCTURE_H_
#define HOLO_MAP_SERVICE_CLIENT_APPLICATION_ROAD_STRUCTURE_H_

#include <memory>
#include <vector>

#include <holo/common/odometry.h>
#include <holo/core/types.h>
#include <holo/map/common/types.h>
#include <holo/map/service/client/matcher/matcher.h>
#include <holo/map/service/client/profile/lane.h>
#include <holo/map/service/client/profile/lane_boundary.h>
#include <holo/map/service/client/profile/lane_group.h>

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

class RoadStructure
{
public:
    using ScalarType        = holo::float64_t;
    using ScalarVectorType  = std::vector<ScalarType>;
    using PointType         = holo::geometry::Point3d;
    using LaneType = holo::map::service::client::profile::Lane;
    using LaneGroupType = holo::map::service::client::profile::LaneGroup;
    using LaneBoundaryType = holo::map::service::client::profile::LaneBoundary;
    using ProfileIdType         = holo::map::service::client::profile::ProfileIdType;
    using LaneCSPtrType         = holo::map::service::client::profile::LaneCSPtrType;
    using LaneCSPtrVectorType   = std::vector<LaneCSPtrType>;
    using LaneGroupCSPtrType    = holo::map::service::client::profile::LaneGroupCSPtrType;
    using LaneBoundaryCSPtrType = holo::map::service::client::profile::LaneBoundaryCSPtrType;
    using LaneBoundaryCSPtrVectorType = std::vector<LaneBoundaryCSPtrType>;

    using RoadStructureSPtrType     = std::shared_ptr<RoadStructure>;
    using RoadStructureCSPtrType    = std::shared_ptr<RoadStructure const>;

    RoadStructure();
    virtual ~RoadStructure();

    LaneGroupCSPtrType GetLaneGroup() const;

    std::size_t GetLanesSize() const;
    LaneCSPtrType AtLane(std::size_t const i) const;
    LaneCSPtrType GetLane(ProfileIdType const id) const;
    LaneCSPtrVectorType const& GetLanes() const;

    std::size_t GetLaneBoundariesSize() const;
    LaneBoundaryCSPtrType AtLaneBoundary(std::size_t const i) const;
    LaneBoundaryCSPtrType GetLaneBoundary(ProfileIdType const id) const;
    LaneBoundaryCSPtrVectorType const& GetBoundaries() const;

    std::size_t GetSucceedingStructureSize() const;
    RoadStructureCSPtrType AtSucceedingStructure(std::size_t const index) const;

    std::size_t GetPrecedingStructureSize() const;
    RoadStructureCSPtrType AtPrecedingStructure(std::size_t const index) const;

private:
    class RoadStructureInner;
    std::unique_ptr<RoadStructureInner> inner_;

    friend class RoadStructureBuilder;
};

class RoadStructures
{
public:
    using DistanceType              = RoadStructure::ScalarType;
    using DistanceVectorType        = RoadStructure::ScalarVectorType;
    using RoadStructureSPtrType  = RoadStructure::RoadStructureSPtrType;
    using RoadStructureCSPtrType = RoadStructure::RoadStructureCSPtrType;

    RoadStructures();
    virtual ~RoadStructures();

    RoadStructureCSPtrType GetCurrentStructure();

    holo::bool_t IsWithInSingleRoad(DistanceType const front_distance, DistanceType const rear_distance,
        holo::bool_t& result) const;

    holo::bool_t IsLaneNumberChanged(DistanceType const front_distance, DistanceType const rear_distance,
        holo::bool_t& result) const;

    holo::bool_t IsLaneBoundaryTypeChanged(DistanceType const front_distance, DistanceType const rear_distance,
        holo::bool_t& result) const;

    holo::bool_t IsLaneParallel(DistanceType const front_distance, DistanceType const rear_distance,
        holo::bool_t& result) const;

    /**
     * @brief Get all the lane width values which are close to current map matching point.
     * 
     * @note If a map matching point is out of current Road(Lane Group), we will return the
     *       closest width infos.
     * @param[out] Width values for all lanes related to current map matching result.
     * @return true: No error;
     *         false: An error occurs in this function.
     */
    holo::bool_t GetLaneWidth(DistanceVectorType& width) const;

private:
    class RoadStructuresInner;
    std::unique_ptr<RoadStructuresInner> inner_;

    friend class RoadStructureBuilder;
};

using RoadStructureSPtrType     = std::shared_ptr<RoadStructure>;
using RoadStructureCSPtrType    = std::shared_ptr<RoadStructure const>;

using RoadStructuresSPtrType  = std::shared_ptr<RoadStructures>;
using RoadStructuresCSPtrType = std::shared_ptr<RoadStructures const>;

} ///< namespace application
} ///< namespace client
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_CLIENT_APPLICATION_ROAD_STRUCTURE_H_ */