/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file nds_adapter.h
 * @brief This header file defines the ehr map reconstructor.
 * @author zhengshulei@holomatic.com
 * @date 2021-11-3
 */
#ifndef HOLO_MAP_ADASIS_EHR_NDS_CONVERTER_H_
#define HOLO_MAP_ADASIS_EHR_NDS_CONVERTER_H_

#include <holo/core/types.h>
#include <holo/map/adasis/ehr/types.h>
#include <holo/map/adasis/ehr/msg_buffer.h>
#include <holo/map/adasis/ehr/path_tree.h>
#include <holo/map/common/common_type_define.h>

#include <map>
#include <vector>

namespace holo
{
namespace map
{
namespace adasis
{
namespace ehr
{

/**
 * @addtogroup ehr
 * @{
 *
 */

/**
 * @brief Adapter for ADASIS V3 --> HoloNDS.
 */
class NDSAdapter
{

public:
    NDSAdapter()
    {
    }
    ~NDSAdapter()
    {
    }

public:
    /**
     * @brief Adapter for ADASIS V3 positoin --> HoloNDS LocalMapOdometry.
     * @param[in] positon positon message
     * @param[out] odo local map odometry
     */
    holo::bool_t AdaptPosition(const PositionEntry& position, LocalMapOdometryType& odo);
    /**
     * @brief Adapter for ADASIS V3 path cache --> HoloNDS cache.
     * @param[in] map ehp map model
     * @param[in] cache ehp path cache
     */
    holo::bool_t Adapt(EhpMapModel& map, EhpLinkSequence& cache);
    /**
     * @brief Adapter for ADASIS V3 path cache --> HoloNDS routing path.
     * @param[in] cache ehp path cache
     * @param[in] is_main_path is ehp mmp?
     */
    holo::bool_t AdaptRoutingPath(EhpLinkSequence& cache, holo::bool_t is_main_path);
    
    /**
     * @brief HoloNDS cache of increasing adapted map.
     * @return HoloNDS features
     */
    MapDataGroup& GetAdaptedData()
    {
        return data_;
    }

    /**
     * @brief Assign verbose flag.
     *
     * @param[in] v If true, reader object will print debug message to log.
     */
    void SetVerbose(holo::bool_t const v) noexcept
    {
        this->verbose_ = v;
    }

private:
    holo::bool_t WGS84ToUTM6(const GeoPointType& in_point, GeographicParameterType& out_geo_param);
    holo::bool_t CheckLaneGeometrySequence(LaneGeometryVecContainerType& vec);
    holo::uint32_t GetLengthCm(GeoPointVectorType& geometry_points);
    holo::bool_t AdaptGeoPoints(LaneGeometryPtr& lg, GeoPointVectorType& geometry_points, CoordinateType& coord_system);
    void PrintInfo(std::vector<LinkId>& links);
    holo::bool_t AdaptRoad(const EhpLinkPtr& link);
    holo::bool_t AdaptLink(EhpLinkSequence& cache, LinkId link_id);
    holo::bool_t AdaptLaneGroup(EhpLinkSequence& cache, LinkId link_id, LaneGroupSPtrType& lane_group);
    holo::bool_t AdaptLane(EhpLinkSequence& cache, LinkId link_id, LaneGroupSPtrType& lane_group);
    holo::bool_t AdaptLaneBoundary(const EhpLinkPtr& link, const LinearObjId& lane_boundary_id,
        v3_1_1::LinearObject& lo, LaneBoundaryVectorType& lane_boundaries);
    holo::bool_t AdaptLaneBoundary(const EhpLinkPtr& link, LaneBoundaryVectorType& lane_boundaries);
    holo::bool_t AdaptLaneBoundary(EhpLinkSequence& cache, LinkId link_id, std::vector<MapFeatureIdType>& lane_boundary_ids);
    holo::bool_t AdaptLaneTopology(EhpMapModel& map, EhpLinkSequence& cache, LinkId link_id, LaneGroupSPtrType& lane_group);

private:
    MapDataGroup data_;
    holo::bool_t verbose_ = false; ///< If true, print debug message to log.
};

/**
 * @}
 */

} // namespace ehr
} // namespace adasis
} // namespace map
} // namespace holo

#endif /* HOLO_MAP_ADASIS_EHR_NDS_CONVERTER_H_ */