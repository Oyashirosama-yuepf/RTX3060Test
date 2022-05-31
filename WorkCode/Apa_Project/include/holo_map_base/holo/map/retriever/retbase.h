/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file retbase.h
 * @brief Base for retriever
 * @author jiangdianqin(jiangdianqin@holomaitc.com)
 * @date 2017-09-01
 */

#ifndef HOLO_MAP_RETRIEVER_RETBASE_H_
#define HOLO_MAP_RETRIEVER_RETBASE_H_

#include <sqlite3.h>

#include <stdio.h>

#include <holo/map/common/common_type_define.h>

#include <holo/map/common/map_setting.h>

#include <holo/map/retriever/memcache.h>

#include <holo/map/format/parking/object_parking_space.h>

#include <holo/map/format/parking/object_parking_floor.h>

#include <holo/map/format/parking/object_parking_lot.h>

#include <holo/map/format/parking/object_parking_poi.h>

#include <holo/map/format/parking/object_parking_background.h>

#include <holo/map/format/hfl/quasi_dynamic_lane_group.h>

#include <holo/map/format/hfl/quasi_dynamic_lane.h>

#include <holo/map/format/hfl/quasi_dynamic_region.h>

#include <holo/map/format/base/tile.h>

#include <holo/map/format/base/sd_road.h>

#include <holo/map/format/base/object_traffic_sign.h>

#include <holo/map/format/base/object_regional_info.h>

#include <holo/map/format/base/object_safe_island.h>

#include <holo/map/format/base/object_info.h>

#include <holo/map/format/base/object_linear_info.h>

#include <holo/map/format/base/object_traffic_light_group.h>

#include <holo/map/format/base/object_stop_line.h>

#include <holo/map/format/base/junction.h>

#include <holo/map/format/base/geofence.h>

#include <holo/map/format/base/road.h>

#include <holo/map/format/base/lane_group.h>

#include <holo/map/format/base/lane_boundary.h>

#include <holo/map/format/base/lane.h>

#include <holo/map/format/base/object_traffic_light.h>

#include <holo/map/format/base/object_pedestrian_crossing.h>

#include <holo/map/format/base/sd_node.h>

#include <holo/map/format/base/intersection.h>

#include <holo/map/format/navigation/routing_path.h>

#include <holo/map/format/navigation/routing_graph.h>

#include <holo/map/format/navigation/routing_edge.h>

#include <holo/map/format/navigation/connection.h>

#include <holo/map/format/navigation/routing_node.h>

#include <holo/map/format/base/header.h>

namespace holo
{
namespace map
{

/**
 * @addtogroup map
 * @{
 *
 */

class RetBase
{
public:
    /**
     * @brief The type indicates where we read data from.
     */
    enum class EngineType : uint8_t
    {
        ENGINE_TYPE_UNKNOWN             = 0,   ///< Placeholder.
        ENGINE_TYPE_HOLO_NDS_DB         = 1,   ///< Read data from Holo NDS database.
        ENGINE_TYPE_NAVINFO_NDS_DB      = 2,   ///< Read data from Navinfo NDS database by Navinfo SDK.
        ENGINE_TYPE_BAIDU_NDS_DB        = 3,   ///< Read data from Baidu NDS database by Baidu SDK.
        ENGINE_TYPE_AUTONAVI_EHP_DB     = 4,   ///< Read data from Autonavi-EHP database by Autonavi-EHP SDK.
    };

    /// Redefine map feature type for RetBase.
    using FeatureType = holo::map::format::Base::FeatureType;

    /// Prohibit default copy constructor and default constructor
    RetBase(const RetBase&) = delete;
    RetBase& operator=(const RetBase&) = delete;
    RetBase() = delete;

    /**
     * @brief Constructor with special parameters.
     *
     * @param[in] db_path Root directory of target map database.
     * @param[in] et Engine type, refer to @EngineType for more details, if it's not ENGINE_TYPE_HOLO_NDS_DB,
     *               RetBase will not read real database, just be a memory cache.
     * @param[in] capacity Max memory cache capacity, if @et is not ENGINE_TYPE_HOLO_NDS_DB, you should be careful
                           of this value, if this value is too small, memory cache may discard some legal features.
     */
    RetBase(const char* db_path, EngineType const et = EngineType::ENGINE_TYPE_HOLO_NDS_DB,
        const std::size_t capacity = 500);

    /**
     * @brief Default destructor.
     */
    virtual ~RetBase();

    /**
     * @brief Access engine type.
     *
     * @return Retriever engine type.
     */
    EngineType GetEngineType() const noexcept;

    /// Clear cache
    virtual void Clear();

    /**
     * @brief Check if a special feature exists.
     *
     * @param[in] type Feature type, refer to @FeatureType for more details.
     * @param[in] id Feature id, UUID for map data feature.
     * @return true: Target feature does exist;
     *         false: Otherwise.
     */
    holo::bool_t Exist(const FeatureType type, const MapFeatureIdType id);

    /**
     * @brief Get current feature count in cache by feature type.
     *
     * @param[in] type Feature type, refer to @FeatureType for more details.
     * @return Feature count.
     */
    std::size_t GetCachedFeatureCount(const FeatureType type) const noexcept;



    /**
     * @brief Get object_parking_space by id
     *
     * @note If the target data is not existent actually, this function will return false.
     * @param[in] _object_parking_space_id object_parking_space id
     * @param[out] _ptr_object_parking_space pointer of object_parking_space
     * @return true: result is fetched successfully; 
     *         false: An error occurs or the target data is not existent.
     */
    virtual bool GetObjectParkingSpaceById(const MapFeatureIdType _object_parking_space_id, format::PtrObjectParkingSpace& _ptr_object_parking_space);
    


    /**
     * @brief Get object_parking_floor by id
     *
     * @note If the target data is not existent actually, this function will return false.
     * @param[in] _object_parking_floor_id object_parking_floor id
     * @param[out] _ptr_object_parking_floor pointer of object_parking_floor
     * @return true: result is fetched successfully; 
     *         false: An error occurs or the target data is not existent.
     */
    virtual bool GetObjectParkingFloorById(const MapFeatureIdType _object_parking_floor_id, format::PtrObjectParkingFloor& _ptr_object_parking_floor);
    


    /**
     * @brief Get object_parking_lot by id
     *
     * @note If the target data is not existent actually, this function will return false.
     * @param[in] _object_parking_lot_id object_parking_lot id
     * @param[out] _ptr_object_parking_lot pointer of object_parking_lot
     * @return true: result is fetched successfully; 
     *         false: An error occurs or the target data is not existent.
     */
    virtual bool GetObjectParkingLotById(const MapFeatureIdType _object_parking_lot_id, format::PtrObjectParkingLot& _ptr_object_parking_lot);
    


    /**
     * @brief Get object_parking_poi by id
     *
     * @note If the target data is not existent actually, this function will return false.
     * @param[in] _object_parking_poi_id object_parking_poi id
     * @param[out] _ptr_object_parking_poi pointer of object_parking_poi
     * @return true: result is fetched successfully; 
     *         false: An error occurs or the target data is not existent.
     */
    virtual bool GetObjectParkingPoiById(const MapFeatureIdType _object_parking_poi_id, format::PtrObjectParkingPoi& _ptr_object_parking_poi);
    


    /**
     * @brief Get object_parking_background by id
     *
     * @note If the target data is not existent actually, this function will return false.
     * @param[in] _object_parking_background_id object_parking_background id
     * @param[out] _ptr_object_parking_background pointer of object_parking_background
     * @return true: result is fetched successfully; 
     *         false: An error occurs or the target data is not existent.
     */
    virtual bool GetObjectParkingBackgroundById(const MapFeatureIdType _object_parking_background_id, format::PtrObjectParkingBackground& _ptr_object_parking_background);
    


    /**
     * @brief Get quasi_dynamic_lane_group by id
     *
     * @note If the target data is not existent actually, this function will return false.
     * @param[in] _quasi_dynamic_lane_group_id quasi_dynamic_lane_group id
     * @param[out] _ptr_quasi_dynamic_lane_group pointer of quasi_dynamic_lane_group
     * @return true: result is fetched successfully; 
     *         false: An error occurs or the target data is not existent.
     */
    virtual bool GetQuasiDynamicLaneGroupById(const MapFeatureIdType _quasi_dynamic_lane_group_id, format::PtrQuasiDynamicLaneGroup& _ptr_quasi_dynamic_lane_group);
    


    /**
     * @brief Get quasi_dynamic_lane by id
     *
     * @note If the target data is not existent actually, this function will return false.
     * @param[in] _quasi_dynamic_lane_id quasi_dynamic_lane id
     * @param[out] _ptr_quasi_dynamic_lane pointer of quasi_dynamic_lane
     * @return true: result is fetched successfully; 
     *         false: An error occurs or the target data is not existent.
     */
    virtual bool GetQuasiDynamicLaneById(const MapFeatureIdType _quasi_dynamic_lane_id, format::PtrQuasiDynamicLane& _ptr_quasi_dynamic_lane);
    


    /**
     * @brief Get quasi_dynamic_region by id
     *
     * @note If the target data is not existent actually, this function will return false.
     * @param[in] _quasi_dynamic_region_id quasi_dynamic_region id
     * @param[out] _ptr_quasi_dynamic_region pointer of quasi_dynamic_region
     * @return true: result is fetched successfully; 
     *         false: An error occurs or the target data is not existent.
     */
    virtual bool GetQuasiDynamicRegionById(const MapFeatureIdType _quasi_dynamic_region_id, format::PtrQuasiDynamicRegion& _ptr_quasi_dynamic_region);
    


    /**
     * @brief Get tile by id
     *
     * @note If the target data is not existent actually, this function will return false.
     * @param[in] _tile_id tile id
     * @param[out] _ptr_tile pointer of tile
     * @return true: result is fetched successfully; 
     *         false: An error occurs or the target data is not existent.
     */
    virtual bool GetTileById(const MapFeatureIdType _tile_id, format::PtrTile& _ptr_tile);
    


    /**
     * @brief Get sd_road by id
     *
     * @note If the target data is not existent actually, this function will return false.
     * @param[in] _sd_road_id sd_road id
     * @param[out] _ptr_sd_road pointer of sd_road
     * @return true: result is fetched successfully; 
     *         false: An error occurs or the target data is not existent.
     */
    virtual bool GetSdRoadById(const MapFeatureIdType _sd_road_id, format::PtrSdRoad& _ptr_sd_road);
    


    /**
     * @brief Get object_traffic_sign by id
     *
     * @note If the target data is not existent actually, this function will return false.
     * @param[in] _object_traffic_sign_id object_traffic_sign id
     * @param[out] _ptr_object_traffic_sign pointer of object_traffic_sign
     * @return true: result is fetched successfully; 
     *         false: An error occurs or the target data is not existent.
     */
    virtual bool GetObjectTrafficSignById(const MapFeatureIdType _object_traffic_sign_id, format::PtrObjectTrafficSign& _ptr_object_traffic_sign);
    


    /**
     * @brief Get object_regional_info by id
     *
     * @note If the target data is not existent actually, this function will return false.
     * @param[in] _object_regional_info_id object_regional_info id
     * @param[out] _ptr_object_regional_info pointer of object_regional_info
     * @return true: result is fetched successfully; 
     *         false: An error occurs or the target data is not existent.
     */
    virtual bool GetObjectRegionalInfoById(const MapFeatureIdType _object_regional_info_id, format::PtrObjectRegionalInfo& _ptr_object_regional_info);
    


    /**
     * @brief Get object_safe_island by id
     *
     * @note If the target data is not existent actually, this function will return false.
     * @param[in] _object_safe_island_id object_safe_island id
     * @param[out] _ptr_object_safe_island pointer of object_safe_island
     * @return true: result is fetched successfully; 
     *         false: An error occurs or the target data is not existent.
     */
    virtual bool GetObjectSafeIslandById(const MapFeatureIdType _object_safe_island_id, format::PtrObjectSafeIsland& _ptr_object_safe_island);
    


    /**
     * @brief Get object_info by id
     *
     * @note If the target data is not existent actually, this function will return false.
     * @param[in] _object_info_id object_info id
     * @param[out] _ptr_object_info pointer of object_info
     * @return true: result is fetched successfully; 
     *         false: An error occurs or the target data is not existent.
     */
    virtual bool GetObjectInfoById(const MapFeatureIdType _object_info_id, format::PtrObjectInfo& _ptr_object_info);
    


    /**
     * @brief Get object_linear_info by id
     *
     * @note If the target data is not existent actually, this function will return false.
     * @param[in] _object_linear_info_id object_linear_info id
     * @param[out] _ptr_object_linear_info pointer of object_linear_info
     * @return true: result is fetched successfully; 
     *         false: An error occurs or the target data is not existent.
     */
    virtual bool GetObjectLinearInfoById(const MapFeatureIdType _object_linear_info_id, format::PtrObjectLinearInfo& _ptr_object_linear_info);
    


    /**
     * @brief Get object_traffic_light_group by id
     *
     * @note If the target data is not existent actually, this function will return false.
     * @param[in] _object_traffic_light_group_id object_traffic_light_group id
     * @param[out] _ptr_object_traffic_light_group pointer of object_traffic_light_group
     * @return true: result is fetched successfully; 
     *         false: An error occurs or the target data is not existent.
     */
    virtual bool GetObjectTrafficLightGroupById(const MapFeatureIdType _object_traffic_light_group_id, format::PtrObjectTrafficLightGroup& _ptr_object_traffic_light_group);
    


    /**
     * @brief Get object_stop_line by id
     *
     * @note If the target data is not existent actually, this function will return false.
     * @param[in] _object_stop_line_id object_stop_line id
     * @param[out] _ptr_object_stop_line pointer of object_stop_line
     * @return true: result is fetched successfully; 
     *         false: An error occurs or the target data is not existent.
     */
    virtual bool GetObjectStopLineById(const MapFeatureIdType _object_stop_line_id, format::PtrObjectStopLine& _ptr_object_stop_line);
    


    /**
     * @brief Get junction by id
     *
     * @note If the target data is not existent actually, this function will return false.
     * @param[in] _junction_id junction id
     * @param[out] _ptr_junction pointer of junction
     * @return true: result is fetched successfully; 
     *         false: An error occurs or the target data is not existent.
     */
    virtual bool GetJunctionById(const MapFeatureIdType _junction_id, format::PtrJunction& _ptr_junction);
    


    /**
     * @brief Get geofence by id
     *
     * @note If the target data is not existent actually, this function will return false.
     * @param[in] _geofence_id geofence id
     * @param[out] _ptr_geofence pointer of geofence
     * @return true: result is fetched successfully; 
     *         false: An error occurs or the target data is not existent.
     */
    virtual bool GetGeofenceById(const MapFeatureIdType _geofence_id, format::PtrGeofence& _ptr_geofence);
    


    /**
     * @brief Get road by id
     *
     * @note If the target data is not existent actually, this function will return false.
     * @param[in] _road_id road id
     * @param[out] _ptr_road pointer of road
     * @return true: result is fetched successfully; 
     *         false: An error occurs or the target data is not existent.
     */
    virtual bool GetRoadById(const MapFeatureIdType _road_id, format::PtrRoad& _ptr_road);
    


    /**
     * @brief Get lane_group by id
     *
     * @note If the target data is not existent actually, this function will return false.
     * @param[in] _lane_group_id lane_group id
     * @param[out] _ptr_lane_group pointer of lane_group
     * @return true: result is fetched successfully; 
     *         false: An error occurs or the target data is not existent.
     */
    virtual bool GetLaneGroupById(const MapFeatureIdType _lane_group_id, format::PtrLaneGroup& _ptr_lane_group);
    


    /**
     * @brief Get lane_boundary by id
     *
     * @note If the target data is not existent actually, this function will return false.
     * @param[in] _lane_boundary_id lane_boundary id
     * @param[out] _ptr_lane_boundary pointer of lane_boundary
     * @return true: result is fetched successfully; 
     *         false: An error occurs or the target data is not existent.
     */
    virtual bool GetLaneBoundaryById(const MapFeatureIdType _lane_boundary_id, format::PtrLaneBoundary& _ptr_lane_boundary);
    


    /**
     * @brief Get lane by id
     *
     * @note If the target data is not existent actually, this function will return false.
     * @param[in] _lane_id lane id
     * @param[out] _ptr_lane pointer of lane
     * @return true: result is fetched successfully; 
     *         false: An error occurs or the target data is not existent.
     */
    virtual bool GetLaneById(const MapFeatureIdType _lane_id, format::PtrLane& _ptr_lane);
    


    /**
     * @brief Get object_traffic_light by id
     *
     * @note If the target data is not existent actually, this function will return false.
     * @param[in] _object_traffic_light_id object_traffic_light id
     * @param[out] _ptr_object_traffic_light pointer of object_traffic_light
     * @return true: result is fetched successfully; 
     *         false: An error occurs or the target data is not existent.
     */
    virtual bool GetObjectTrafficLightById(const MapFeatureIdType _object_traffic_light_id, format::PtrObjectTrafficLight& _ptr_object_traffic_light);
    


    /**
     * @brief Get object_pedestrian_crossing by id
     *
     * @note If the target data is not existent actually, this function will return false.
     * @param[in] _object_pedestrian_crossing_id object_pedestrian_crossing id
     * @param[out] _ptr_object_pedestrian_crossing pointer of object_pedestrian_crossing
     * @return true: result is fetched successfully; 
     *         false: An error occurs or the target data is not existent.
     */
    virtual bool GetObjectPedestrianCrossingById(const MapFeatureIdType _object_pedestrian_crossing_id, format::PtrObjectPedestrianCrossing& _ptr_object_pedestrian_crossing);
    


    /**
     * @brief Get sd_node by id
     *
     * @note If the target data is not existent actually, this function will return false.
     * @param[in] _sd_node_id sd_node id
     * @param[out] _ptr_sd_node pointer of sd_node
     * @return true: result is fetched successfully; 
     *         false: An error occurs or the target data is not existent.
     */
    virtual bool GetSdNodeById(const MapFeatureIdType _sd_node_id, format::PtrSdNode& _ptr_sd_node);
    


    /**
     * @brief Get intersection by id
     *
     * @note If the target data is not existent actually, this function will return false.
     * @param[in] _intersection_id intersection id
     * @param[out] _ptr_intersection pointer of intersection
     * @return true: result is fetched successfully; 
     *         false: An error occurs or the target data is not existent.
     */
    virtual bool GetIntersectionById(const MapFeatureIdType _intersection_id, format::PtrIntersection& _ptr_intersection);
    


    /**
     * @brief Get routing_path by id
     *
     * @note If the target data is not existent actually, this function will return false.
     * @param[in] _routing_path_id routing_path id
     * @param[out] _ptr_routing_path pointer of routing_path
     * @return true: result is fetched successfully; 
     *         false: An error occurs or the target data is not existent.
     */
    virtual bool GetRoutingPathById(const MapFeatureIdType _routing_path_id, format::PtrRoutingPath& _ptr_routing_path);
    


    /**
     * @brief Get routing_graph by id
     *
     * @note If the target data is not existent actually, this function will return false.
     * @param[in] _routing_graph_id routing_graph id
     * @param[out] _ptr_routing_graph pointer of routing_graph
     * @return true: result is fetched successfully; 
     *         false: An error occurs or the target data is not existent.
     */
    virtual bool GetRoutingGraphById(const MapFeatureIdType _routing_graph_id, format::PtrRoutingGraph& _ptr_routing_graph);
    


    /**
     * @brief Get routing_edge by id
     *
     * @note If the target data is not existent actually, this function will return false.
     * @param[in] _routing_edge_id routing_edge id
     * @param[out] _ptr_routing_edge pointer of routing_edge
     * @return true: result is fetched successfully; 
     *         false: An error occurs or the target data is not existent.
     */
    virtual bool GetRoutingEdgeById(const MapFeatureIdType _routing_edge_id, format::PtrRoutingEdge& _ptr_routing_edge);
    


    /**
     * @brief Get connection by id
     *
     * @note If the target data is not existent actually, this function will return false.
     * @param[in] _connection_id connection id
     * @param[out] _ptr_connection pointer of connection
     * @return true: result is fetched successfully; 
     *         false: An error occurs or the target data is not existent.
     */
    virtual bool GetConnectionById(const MapFeatureIdType _connection_id, format::PtrConnection& _ptr_connection);
    


    /**
     * @brief Get routing_node by id
     *
     * @note If the target data is not existent actually, this function will return false.
     * @param[in] _routing_node_id routing_node id
     * @param[out] _ptr_routing_node pointer of routing_node
     * @return true: result is fetched successfully; 
     *         false: An error occurs or the target data is not existent.
     */
    virtual bool GetRoutingNodeById(const MapFeatureIdType _routing_node_id, format::PtrRoutingNode& _ptr_routing_node);
    


    /**
     * @brief Get object_parking_space by id
     *
     * @note If the target data is not existent actually, this function will return true,
     *       but _valid will be set false.
     * @param[in] _object_parking_space_id object_parking_space id
     * @param[out] _ptr_object_parking_space pointer of object_parking_space
     * @param[out] _valid Whether of not the target data is valid.
     * @return true: No error, although the target data is not existent, so you should
     *               check _valid always.
     *         false: An error occurs in this function.
     */
    virtual bool GetObjectParkingSpaceByIdV2(const MapFeatureIdType _object_parking_space_id, format::PtrObjectParkingSpace& _ptr_object_parking_space, bool& _valid);
    


    /**
     * @brief Get object_parking_floor by id
     *
     * @note If the target data is not existent actually, this function will return true,
     *       but _valid will be set false.
     * @param[in] _object_parking_floor_id object_parking_floor id
     * @param[out] _ptr_object_parking_floor pointer of object_parking_floor
     * @param[out] _valid Whether of not the target data is valid.
     * @return true: No error, although the target data is not existent, so you should
     *               check _valid always.
     *         false: An error occurs in this function.
     */
    virtual bool GetObjectParkingFloorByIdV2(const MapFeatureIdType _object_parking_floor_id, format::PtrObjectParkingFloor& _ptr_object_parking_floor, bool& _valid);
    


    /**
     * @brief Get object_parking_lot by id
     *
     * @note If the target data is not existent actually, this function will return true,
     *       but _valid will be set false.
     * @param[in] _object_parking_lot_id object_parking_lot id
     * @param[out] _ptr_object_parking_lot pointer of object_parking_lot
     * @param[out] _valid Whether of not the target data is valid.
     * @return true: No error, although the target data is not existent, so you should
     *               check _valid always.
     *         false: An error occurs in this function.
     */
    virtual bool GetObjectParkingLotByIdV2(const MapFeatureIdType _object_parking_lot_id, format::PtrObjectParkingLot& _ptr_object_parking_lot, bool& _valid);
    


    /**
     * @brief Get object_parking_poi by id
     *
     * @note If the target data is not existent actually, this function will return true,
     *       but _valid will be set false.
     * @param[in] _object_parking_poi_id object_parking_poi id
     * @param[out] _ptr_object_parking_poi pointer of object_parking_poi
     * @param[out] _valid Whether of not the target data is valid.
     * @return true: No error, although the target data is not existent, so you should
     *               check _valid always.
     *         false: An error occurs in this function.
     */
    virtual bool GetObjectParkingPoiByIdV2(const MapFeatureIdType _object_parking_poi_id, format::PtrObjectParkingPoi& _ptr_object_parking_poi, bool& _valid);
    


    /**
     * @brief Get object_parking_background by id
     *
     * @note If the target data is not existent actually, this function will return true,
     *       but _valid will be set false.
     * @param[in] _object_parking_background_id object_parking_background id
     * @param[out] _ptr_object_parking_background pointer of object_parking_background
     * @param[out] _valid Whether of not the target data is valid.
     * @return true: No error, although the target data is not existent, so you should
     *               check _valid always.
     *         false: An error occurs in this function.
     */
    virtual bool GetObjectParkingBackgroundByIdV2(const MapFeatureIdType _object_parking_background_id, format::PtrObjectParkingBackground& _ptr_object_parking_background, bool& _valid);
    


    /**
     * @brief Get quasi_dynamic_lane_group by id
     *
     * @note If the target data is not existent actually, this function will return true,
     *       but _valid will be set false.
     * @param[in] _quasi_dynamic_lane_group_id quasi_dynamic_lane_group id
     * @param[out] _ptr_quasi_dynamic_lane_group pointer of quasi_dynamic_lane_group
     * @param[out] _valid Whether of not the target data is valid.
     * @return true: No error, although the target data is not existent, so you should
     *               check _valid always.
     *         false: An error occurs in this function.
     */
    virtual bool GetQuasiDynamicLaneGroupByIdV2(const MapFeatureIdType _quasi_dynamic_lane_group_id, format::PtrQuasiDynamicLaneGroup& _ptr_quasi_dynamic_lane_group, bool& _valid);
    


    /**
     * @brief Get quasi_dynamic_lane by id
     *
     * @note If the target data is not existent actually, this function will return true,
     *       but _valid will be set false.
     * @param[in] _quasi_dynamic_lane_id quasi_dynamic_lane id
     * @param[out] _ptr_quasi_dynamic_lane pointer of quasi_dynamic_lane
     * @param[out] _valid Whether of not the target data is valid.
     * @return true: No error, although the target data is not existent, so you should
     *               check _valid always.
     *         false: An error occurs in this function.
     */
    virtual bool GetQuasiDynamicLaneByIdV2(const MapFeatureIdType _quasi_dynamic_lane_id, format::PtrQuasiDynamicLane& _ptr_quasi_dynamic_lane, bool& _valid);
    


    /**
     * @brief Get quasi_dynamic_region by id
     *
     * @note If the target data is not existent actually, this function will return true,
     *       but _valid will be set false.
     * @param[in] _quasi_dynamic_region_id quasi_dynamic_region id
     * @param[out] _ptr_quasi_dynamic_region pointer of quasi_dynamic_region
     * @param[out] _valid Whether of not the target data is valid.
     * @return true: No error, although the target data is not existent, so you should
     *               check _valid always.
     *         false: An error occurs in this function.
     */
    virtual bool GetQuasiDynamicRegionByIdV2(const MapFeatureIdType _quasi_dynamic_region_id, format::PtrQuasiDynamicRegion& _ptr_quasi_dynamic_region, bool& _valid);
    


    /**
     * @brief Get tile by id
     *
     * @note If the target data is not existent actually, this function will return true,
     *       but _valid will be set false.
     * @param[in] _tile_id tile id
     * @param[out] _ptr_tile pointer of tile
     * @param[out] _valid Whether of not the target data is valid.
     * @return true: No error, although the target data is not existent, so you should
     *               check _valid always.
     *         false: An error occurs in this function.
     */
    virtual bool GetTileByIdV2(const MapFeatureIdType _tile_id, format::PtrTile& _ptr_tile, bool& _valid);
    


    /**
     * @brief Get sd_road by id
     *
     * @note If the target data is not existent actually, this function will return true,
     *       but _valid will be set false.
     * @param[in] _sd_road_id sd_road id
     * @param[out] _ptr_sd_road pointer of sd_road
     * @param[out] _valid Whether of not the target data is valid.
     * @return true: No error, although the target data is not existent, so you should
     *               check _valid always.
     *         false: An error occurs in this function.
     */
    virtual bool GetSdRoadByIdV2(const MapFeatureIdType _sd_road_id, format::PtrSdRoad& _ptr_sd_road, bool& _valid);
    


    /**
     * @brief Get object_traffic_sign by id
     *
     * @note If the target data is not existent actually, this function will return true,
     *       but _valid will be set false.
     * @param[in] _object_traffic_sign_id object_traffic_sign id
     * @param[out] _ptr_object_traffic_sign pointer of object_traffic_sign
     * @param[out] _valid Whether of not the target data is valid.
     * @return true: No error, although the target data is not existent, so you should
     *               check _valid always.
     *         false: An error occurs in this function.
     */
    virtual bool GetObjectTrafficSignByIdV2(const MapFeatureIdType _object_traffic_sign_id, format::PtrObjectTrafficSign& _ptr_object_traffic_sign, bool& _valid);
    


    /**
     * @brief Get object_regional_info by id
     *
     * @note If the target data is not existent actually, this function will return true,
     *       but _valid will be set false.
     * @param[in] _object_regional_info_id object_regional_info id
     * @param[out] _ptr_object_regional_info pointer of object_regional_info
     * @param[out] _valid Whether of not the target data is valid.
     * @return true: No error, although the target data is not existent, so you should
     *               check _valid always.
     *         false: An error occurs in this function.
     */
    virtual bool GetObjectRegionalInfoByIdV2(const MapFeatureIdType _object_regional_info_id, format::PtrObjectRegionalInfo& _ptr_object_regional_info, bool& _valid);
    


    /**
     * @brief Get object_safe_island by id
     *
     * @note If the target data is not existent actually, this function will return true,
     *       but _valid will be set false.
     * @param[in] _object_safe_island_id object_safe_island id
     * @param[out] _ptr_object_safe_island pointer of object_safe_island
     * @param[out] _valid Whether of not the target data is valid.
     * @return true: No error, although the target data is not existent, so you should
     *               check _valid always.
     *         false: An error occurs in this function.
     */
    virtual bool GetObjectSafeIslandByIdV2(const MapFeatureIdType _object_safe_island_id, format::PtrObjectSafeIsland& _ptr_object_safe_island, bool& _valid);
    


    /**
     * @brief Get object_info by id
     *
     * @note If the target data is not existent actually, this function will return true,
     *       but _valid will be set false.
     * @param[in] _object_info_id object_info id
     * @param[out] _ptr_object_info pointer of object_info
     * @param[out] _valid Whether of not the target data is valid.
     * @return true: No error, although the target data is not existent, so you should
     *               check _valid always.
     *         false: An error occurs in this function.
     */
    virtual bool GetObjectInfoByIdV2(const MapFeatureIdType _object_info_id, format::PtrObjectInfo& _ptr_object_info, bool& _valid);
    


    /**
     * @brief Get object_linear_info by id
     *
     * @note If the target data is not existent actually, this function will return true,
     *       but _valid will be set false.
     * @param[in] _object_linear_info_id object_linear_info id
     * @param[out] _ptr_object_linear_info pointer of object_linear_info
     * @param[out] _valid Whether of not the target data is valid.
     * @return true: No error, although the target data is not existent, so you should
     *               check _valid always.
     *         false: An error occurs in this function.
     */
    virtual bool GetObjectLinearInfoByIdV2(const MapFeatureIdType _object_linear_info_id, format::PtrObjectLinearInfo& _ptr_object_linear_info, bool& _valid);
    


    /**
     * @brief Get object_traffic_light_group by id
     *
     * @note If the target data is not existent actually, this function will return true,
     *       but _valid will be set false.
     * @param[in] _object_traffic_light_group_id object_traffic_light_group id
     * @param[out] _ptr_object_traffic_light_group pointer of object_traffic_light_group
     * @param[out] _valid Whether of not the target data is valid.
     * @return true: No error, although the target data is not existent, so you should
     *               check _valid always.
     *         false: An error occurs in this function.
     */
    virtual bool GetObjectTrafficLightGroupByIdV2(const MapFeatureIdType _object_traffic_light_group_id, format::PtrObjectTrafficLightGroup& _ptr_object_traffic_light_group, bool& _valid);
    


    /**
     * @brief Get object_stop_line by id
     *
     * @note If the target data is not existent actually, this function will return true,
     *       but _valid will be set false.
     * @param[in] _object_stop_line_id object_stop_line id
     * @param[out] _ptr_object_stop_line pointer of object_stop_line
     * @param[out] _valid Whether of not the target data is valid.
     * @return true: No error, although the target data is not existent, so you should
     *               check _valid always.
     *         false: An error occurs in this function.
     */
    virtual bool GetObjectStopLineByIdV2(const MapFeatureIdType _object_stop_line_id, format::PtrObjectStopLine& _ptr_object_stop_line, bool& _valid);
    


    /**
     * @brief Get junction by id
     *
     * @note If the target data is not existent actually, this function will return true,
     *       but _valid will be set false.
     * @param[in] _junction_id junction id
     * @param[out] _ptr_junction pointer of junction
     * @param[out] _valid Whether of not the target data is valid.
     * @return true: No error, although the target data is not existent, so you should
     *               check _valid always.
     *         false: An error occurs in this function.
     */
    virtual bool GetJunctionByIdV2(const MapFeatureIdType _junction_id, format::PtrJunction& _ptr_junction, bool& _valid);
    


    /**
     * @brief Get geofence by id
     *
     * @note If the target data is not existent actually, this function will return true,
     *       but _valid will be set false.
     * @param[in] _geofence_id geofence id
     * @param[out] _ptr_geofence pointer of geofence
     * @param[out] _valid Whether of not the target data is valid.
     * @return true: No error, although the target data is not existent, so you should
     *               check _valid always.
     *         false: An error occurs in this function.
     */
    virtual bool GetGeofenceByIdV2(const MapFeatureIdType _geofence_id, format::PtrGeofence& _ptr_geofence, bool& _valid);
    


    /**
     * @brief Get road by id
     *
     * @note If the target data is not existent actually, this function will return true,
     *       but _valid will be set false.
     * @param[in] _road_id road id
     * @param[out] _ptr_road pointer of road
     * @param[out] _valid Whether of not the target data is valid.
     * @return true: No error, although the target data is not existent, so you should
     *               check _valid always.
     *         false: An error occurs in this function.
     */
    virtual bool GetRoadByIdV2(const MapFeatureIdType _road_id, format::PtrRoad& _ptr_road, bool& _valid);
    


    /**
     * @brief Get lane_group by id
     *
     * @note If the target data is not existent actually, this function will return true,
     *       but _valid will be set false.
     * @param[in] _lane_group_id lane_group id
     * @param[out] _ptr_lane_group pointer of lane_group
     * @param[out] _valid Whether of not the target data is valid.
     * @return true: No error, although the target data is not existent, so you should
     *               check _valid always.
     *         false: An error occurs in this function.
     */
    virtual bool GetLaneGroupByIdV2(const MapFeatureIdType _lane_group_id, format::PtrLaneGroup& _ptr_lane_group, bool& _valid);
    


    /**
     * @brief Get lane_boundary by id
     *
     * @note If the target data is not existent actually, this function will return true,
     *       but _valid will be set false.
     * @param[in] _lane_boundary_id lane_boundary id
     * @param[out] _ptr_lane_boundary pointer of lane_boundary
     * @param[out] _valid Whether of not the target data is valid.
     * @return true: No error, although the target data is not existent, so you should
     *               check _valid always.
     *         false: An error occurs in this function.
     */
    virtual bool GetLaneBoundaryByIdV2(const MapFeatureIdType _lane_boundary_id, format::PtrLaneBoundary& _ptr_lane_boundary, bool& _valid);
    


    /**
     * @brief Get lane by id
     *
     * @note If the target data is not existent actually, this function will return true,
     *       but _valid will be set false.
     * @param[in] _lane_id lane id
     * @param[out] _ptr_lane pointer of lane
     * @param[out] _valid Whether of not the target data is valid.
     * @return true: No error, although the target data is not existent, so you should
     *               check _valid always.
     *         false: An error occurs in this function.
     */
    virtual bool GetLaneByIdV2(const MapFeatureIdType _lane_id, format::PtrLane& _ptr_lane, bool& _valid);
    


    /**
     * @brief Get object_traffic_light by id
     *
     * @note If the target data is not existent actually, this function will return true,
     *       but _valid will be set false.
     * @param[in] _object_traffic_light_id object_traffic_light id
     * @param[out] _ptr_object_traffic_light pointer of object_traffic_light
     * @param[out] _valid Whether of not the target data is valid.
     * @return true: No error, although the target data is not existent, so you should
     *               check _valid always.
     *         false: An error occurs in this function.
     */
    virtual bool GetObjectTrafficLightByIdV2(const MapFeatureIdType _object_traffic_light_id, format::PtrObjectTrafficLight& _ptr_object_traffic_light, bool& _valid);
    


    /**
     * @brief Get object_pedestrian_crossing by id
     *
     * @note If the target data is not existent actually, this function will return true,
     *       but _valid will be set false.
     * @param[in] _object_pedestrian_crossing_id object_pedestrian_crossing id
     * @param[out] _ptr_object_pedestrian_crossing pointer of object_pedestrian_crossing
     * @param[out] _valid Whether of not the target data is valid.
     * @return true: No error, although the target data is not existent, so you should
     *               check _valid always.
     *         false: An error occurs in this function.
     */
    virtual bool GetObjectPedestrianCrossingByIdV2(const MapFeatureIdType _object_pedestrian_crossing_id, format::PtrObjectPedestrianCrossing& _ptr_object_pedestrian_crossing, bool& _valid);
    


    /**
     * @brief Get sd_node by id
     *
     * @note If the target data is not existent actually, this function will return true,
     *       but _valid will be set false.
     * @param[in] _sd_node_id sd_node id
     * @param[out] _ptr_sd_node pointer of sd_node
     * @param[out] _valid Whether of not the target data is valid.
     * @return true: No error, although the target data is not existent, so you should
     *               check _valid always.
     *         false: An error occurs in this function.
     */
    virtual bool GetSdNodeByIdV2(const MapFeatureIdType _sd_node_id, format::PtrSdNode& _ptr_sd_node, bool& _valid);
    


    /**
     * @brief Get intersection by id
     *
     * @note If the target data is not existent actually, this function will return true,
     *       but _valid will be set false.
     * @param[in] _intersection_id intersection id
     * @param[out] _ptr_intersection pointer of intersection
     * @param[out] _valid Whether of not the target data is valid.
     * @return true: No error, although the target data is not existent, so you should
     *               check _valid always.
     *         false: An error occurs in this function.
     */
    virtual bool GetIntersectionByIdV2(const MapFeatureIdType _intersection_id, format::PtrIntersection& _ptr_intersection, bool& _valid);
    


    /**
     * @brief Get routing_path by id
     *
     * @note If the target data is not existent actually, this function will return true,
     *       but _valid will be set false.
     * @param[in] _routing_path_id routing_path id
     * @param[out] _ptr_routing_path pointer of routing_path
     * @param[out] _valid Whether of not the target data is valid.
     * @return true: No error, although the target data is not existent, so you should
     *               check _valid always.
     *         false: An error occurs in this function.
     */
    virtual bool GetRoutingPathByIdV2(const MapFeatureIdType _routing_path_id, format::PtrRoutingPath& _ptr_routing_path, bool& _valid);
    


    /**
     * @brief Get routing_graph by id
     *
     * @note If the target data is not existent actually, this function will return true,
     *       but _valid will be set false.
     * @param[in] _routing_graph_id routing_graph id
     * @param[out] _ptr_routing_graph pointer of routing_graph
     * @param[out] _valid Whether of not the target data is valid.
     * @return true: No error, although the target data is not existent, so you should
     *               check _valid always.
     *         false: An error occurs in this function.
     */
    virtual bool GetRoutingGraphByIdV2(const MapFeatureIdType _routing_graph_id, format::PtrRoutingGraph& _ptr_routing_graph, bool& _valid);
    


    /**
     * @brief Get routing_edge by id
     *
     * @note If the target data is not existent actually, this function will return true,
     *       but _valid will be set false.
     * @param[in] _routing_edge_id routing_edge id
     * @param[out] _ptr_routing_edge pointer of routing_edge
     * @param[out] _valid Whether of not the target data is valid.
     * @return true: No error, although the target data is not existent, so you should
     *               check _valid always.
     *         false: An error occurs in this function.
     */
    virtual bool GetRoutingEdgeByIdV2(const MapFeatureIdType _routing_edge_id, format::PtrRoutingEdge& _ptr_routing_edge, bool& _valid);
    


    /**
     * @brief Get connection by id
     *
     * @note If the target data is not existent actually, this function will return true,
     *       but _valid will be set false.
     * @param[in] _connection_id connection id
     * @param[out] _ptr_connection pointer of connection
     * @param[out] _valid Whether of not the target data is valid.
     * @return true: No error, although the target data is not existent, so you should
     *               check _valid always.
     *         false: An error occurs in this function.
     */
    virtual bool GetConnectionByIdV2(const MapFeatureIdType _connection_id, format::PtrConnection& _ptr_connection, bool& _valid);
    


    /**
     * @brief Get routing_node by id
     *
     * @note If the target data is not existent actually, this function will return true,
     *       but _valid will be set false.
     * @param[in] _routing_node_id routing_node id
     * @param[out] _ptr_routing_node pointer of routing_node
     * @param[out] _valid Whether of not the target data is valid.
     * @return true: No error, although the target data is not existent, so you should
     *               check _valid always.
     *         false: An error occurs in this function.
     */
    virtual bool GetRoutingNodeByIdV2(const MapFeatureIdType _routing_node_id, format::PtrRoutingNode& _ptr_routing_node, bool& _valid);
    
    /**
     * @brief Get header by id
     *
     * @param[in] _header_id header id
     * @param[out] _ptr_header pointer of header
     * @return true: result is fetched successfully; false: otherwise
     */
    virtual bool GetHeader(const MapFeatureIdType _header_id, format::PtrHeader& _ptr_header);


    /**
     * @brief Get ids of cached object_parking_space
     *
     * @param[out] _ids vector of cached object_parking_space ids
     * @return true: result is fetched successfully; false: otherwise
     */
    virtual bool GetCachedObjectParkingSpaceIds(MapFeatureIdVectorType& _ids);

    /**
     * @brief Get ids of cached object_parking_floor
     *
     * @param[out] _ids vector of cached object_parking_floor ids
     * @return true: result is fetched successfully; false: otherwise
     */
    virtual bool GetCachedObjectParkingFloorIds(MapFeatureIdVectorType& _ids);

    /**
     * @brief Get ids of cached object_parking_lot
     *
     * @param[out] _ids vector of cached object_parking_lot ids
     * @return true: result is fetched successfully; false: otherwise
     */
    virtual bool GetCachedObjectParkingLotIds(MapFeatureIdVectorType& _ids);

    /**
     * @brief Get ids of cached object_parking_poi
     *
     * @param[out] _ids vector of cached object_parking_poi ids
     * @return true: result is fetched successfully; false: otherwise
     */
    virtual bool GetCachedObjectParkingPoiIds(MapFeatureIdVectorType& _ids);

    /**
     * @brief Get ids of cached object_parking_background
     *
     * @param[out] _ids vector of cached object_parking_background ids
     * @return true: result is fetched successfully; false: otherwise
     */
    virtual bool GetCachedObjectParkingBackgroundIds(MapFeatureIdVectorType& _ids);

    /**
     * @brief Get ids of cached quasi_dynamic_lane_group
     *
     * @param[out] _ids vector of cached quasi_dynamic_lane_group ids
     * @return true: result is fetched successfully; false: otherwise
     */
    virtual bool GetCachedQuasiDynamicLaneGroupIds(MapFeatureIdVectorType& _ids);

    /**
     * @brief Get ids of cached quasi_dynamic_lane
     *
     * @param[out] _ids vector of cached quasi_dynamic_lane ids
     * @return true: result is fetched successfully; false: otherwise
     */
    virtual bool GetCachedQuasiDynamicLaneIds(MapFeatureIdVectorType& _ids);

    /**
     * @brief Get ids of cached quasi_dynamic_region
     *
     * @param[out] _ids vector of cached quasi_dynamic_region ids
     * @return true: result is fetched successfully; false: otherwise
     */
    virtual bool GetCachedQuasiDynamicRegionIds(MapFeatureIdVectorType& _ids);

    /**
     * @brief Get ids of cached tile
     *
     * @param[out] _ids vector of cached tile ids
     * @return true: result is fetched successfully; false: otherwise
     */
    virtual bool GetCachedTileIds(MapFeatureIdVectorType& _ids);

    /**
     * @brief Get ids of cached sd_road
     *
     * @param[out] _ids vector of cached sd_road ids
     * @return true: result is fetched successfully; false: otherwise
     */
    virtual bool GetCachedSdRoadIds(MapFeatureIdVectorType& _ids);

    /**
     * @brief Get ids of cached object_traffic_sign
     *
     * @param[out] _ids vector of cached object_traffic_sign ids
     * @return true: result is fetched successfully; false: otherwise
     */
    virtual bool GetCachedObjectTrafficSignIds(MapFeatureIdVectorType& _ids);

    /**
     * @brief Get ids of cached object_regional_info
     *
     * @param[out] _ids vector of cached object_regional_info ids
     * @return true: result is fetched successfully; false: otherwise
     */
    virtual bool GetCachedObjectRegionalInfoIds(MapFeatureIdVectorType& _ids);

    /**
     * @brief Get ids of cached object_safe_island
     *
     * @param[out] _ids vector of cached object_safe_island ids
     * @return true: result is fetched successfully; false: otherwise
     */
    virtual bool GetCachedObjectSafeIslandIds(MapFeatureIdVectorType& _ids);

    /**
     * @brief Get ids of cached object_info
     *
     * @param[out] _ids vector of cached object_info ids
     * @return true: result is fetched successfully; false: otherwise
     */
    virtual bool GetCachedObjectInfoIds(MapFeatureIdVectorType& _ids);

    /**
     * @brief Get ids of cached object_linear_info
     *
     * @param[out] _ids vector of cached object_linear_info ids
     * @return true: result is fetched successfully; false: otherwise
     */
    virtual bool GetCachedObjectLinearInfoIds(MapFeatureIdVectorType& _ids);

    /**
     * @brief Get ids of cached object_traffic_light_group
     *
     * @param[out] _ids vector of cached object_traffic_light_group ids
     * @return true: result is fetched successfully; false: otherwise
     */
    virtual bool GetCachedObjectTrafficLightGroupIds(MapFeatureIdVectorType& _ids);

    /**
     * @brief Get ids of cached object_stop_line
     *
     * @param[out] _ids vector of cached object_stop_line ids
     * @return true: result is fetched successfully; false: otherwise
     */
    virtual bool GetCachedObjectStopLineIds(MapFeatureIdVectorType& _ids);

    /**
     * @brief Get ids of cached junction
     *
     * @param[out] _ids vector of cached junction ids
     * @return true: result is fetched successfully; false: otherwise
     */
    virtual bool GetCachedJunctionIds(MapFeatureIdVectorType& _ids);

    /**
     * @brief Get ids of cached geofence
     *
     * @param[out] _ids vector of cached geofence ids
     * @return true: result is fetched successfully; false: otherwise
     */
    virtual bool GetCachedGeofenceIds(MapFeatureIdVectorType& _ids);

    /**
     * @brief Get ids of cached road
     *
     * @param[out] _ids vector of cached road ids
     * @return true: result is fetched successfully; false: otherwise
     */
    virtual bool GetCachedRoadIds(MapFeatureIdVectorType& _ids);

    /**
     * @brief Get ids of cached lane_group
     *
     * @param[out] _ids vector of cached lane_group ids
     * @return true: result is fetched successfully; false: otherwise
     */
    virtual bool GetCachedLaneGroupIds(MapFeatureIdVectorType& _ids);

    /**
     * @brief Get ids of cached lane_boundary
     *
     * @param[out] _ids vector of cached lane_boundary ids
     * @return true: result is fetched successfully; false: otherwise
     */
    virtual bool GetCachedLaneBoundaryIds(MapFeatureIdVectorType& _ids);

    /**
     * @brief Get ids of cached lane
     *
     * @param[out] _ids vector of cached lane ids
     * @return true: result is fetched successfully; false: otherwise
     */
    virtual bool GetCachedLaneIds(MapFeatureIdVectorType& _ids);

    /**
     * @brief Get ids of cached object_traffic_light
     *
     * @param[out] _ids vector of cached object_traffic_light ids
     * @return true: result is fetched successfully; false: otherwise
     */
    virtual bool GetCachedObjectTrafficLightIds(MapFeatureIdVectorType& _ids);

    /**
     * @brief Get ids of cached object_pedestrian_crossing
     *
     * @param[out] _ids vector of cached object_pedestrian_crossing ids
     * @return true: result is fetched successfully; false: otherwise
     */
    virtual bool GetCachedObjectPedestrianCrossingIds(MapFeatureIdVectorType& _ids);

    /**
     * @brief Get ids of cached sd_node
     *
     * @param[out] _ids vector of cached sd_node ids
     * @return true: result is fetched successfully; false: otherwise
     */
    virtual bool GetCachedSdNodeIds(MapFeatureIdVectorType& _ids);

    /**
     * @brief Get ids of cached intersection
     *
     * @param[out] _ids vector of cached intersection ids
     * @return true: result is fetched successfully; false: otherwise
     */
    virtual bool GetCachedIntersectionIds(MapFeatureIdVectorType& _ids);

    /**
     * @brief Get ids of cached routing_path
     *
     * @param[out] _ids vector of cached routing_path ids
     * @return true: result is fetched successfully; false: otherwise
     */
    virtual bool GetCachedRoutingPathIds(MapFeatureIdVectorType& _ids);

    /**
     * @brief Get ids of cached routing_graph
     *
     * @param[out] _ids vector of cached routing_graph ids
     * @return true: result is fetched successfully; false: otherwise
     */
    virtual bool GetCachedRoutingGraphIds(MapFeatureIdVectorType& _ids);

    /**
     * @brief Get ids of cached routing_edge
     *
     * @param[out] _ids vector of cached routing_edge ids
     * @return true: result is fetched successfully; false: otherwise
     */
    virtual bool GetCachedRoutingEdgeIds(MapFeatureIdVectorType& _ids);

    /**
     * @brief Get ids of cached connection
     *
     * @param[out] _ids vector of cached connection ids
     * @return true: result is fetched successfully; false: otherwise
     */
    virtual bool GetCachedConnectionIds(MapFeatureIdVectorType& _ids);

    /**
     * @brief Get ids of cached routing_node
     *
     * @param[out] _ids vector of cached routing_node ids
     * @return true: result is fetched successfully; false: otherwise
     */
    virtual bool GetCachedRoutingNodeIds(MapFeatureIdVectorType& _ids);

    /**
     * @brief Get all object_parking_space ids which belong to specific tile
     *
     * @note If the target tile is not existent actually, this function
     *       will return false.
     * @param[in] _tile_id tile id
     * @param[out] _object_parking_space_ids vector of object_parking_space ids
     * @return true: ids are read successfully, 
     *         false: An error occurs or the target is not existent or the 
     *                _object_parking_space_ids is empty.
     */
    virtual bool GetAllObjectParkingSpaceIds(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _object_parking_space_ids);

    /**
     * @brief Get all object_parking_floor ids which belong to specific tile
     *
     * @note If the target tile is not existent actually, this function
     *       will return false.
     * @param[in] _tile_id tile id
     * @param[out] _object_parking_floor_ids vector of object_parking_floor ids
     * @return true: ids are read successfully, 
     *         false: An error occurs or the target is not existent or the 
     *                _object_parking_floor_ids is empty.
     */
    virtual bool GetAllObjectParkingFloorIds(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _object_parking_floor_ids);

    /**
     * @brief Get all object_parking_lot ids which belong to specific tile
     *
     * @note If the target tile is not existent actually, this function
     *       will return false.
     * @param[in] _tile_id tile id
     * @param[out] _object_parking_lot_ids vector of object_parking_lot ids
     * @return true: ids are read successfully, 
     *         false: An error occurs or the target is not existent or the 
     *                _object_parking_lot_ids is empty.
     */
    virtual bool GetAllObjectParkingLotIds(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _object_parking_lot_ids);

    /**
     * @brief Get all object_parking_poi ids which belong to specific tile
     *
     * @note If the target tile is not existent actually, this function
     *       will return false.
     * @param[in] _tile_id tile id
     * @param[out] _object_parking_poi_ids vector of object_parking_poi ids
     * @return true: ids are read successfully, 
     *         false: An error occurs or the target is not existent or the 
     *                _object_parking_poi_ids is empty.
     */
    virtual bool GetAllObjectParkingPoiIds(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _object_parking_poi_ids);

    /**
     * @brief Get all object_parking_background ids which belong to specific tile
     *
     * @note If the target tile is not existent actually, this function
     *       will return false.
     * @param[in] _tile_id tile id
     * @param[out] _object_parking_background_ids vector of object_parking_background ids
     * @return true: ids are read successfully, 
     *         false: An error occurs or the target is not existent or the 
     *                _object_parking_background_ids is empty.
     */
    virtual bool GetAllObjectParkingBackgroundIds(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _object_parking_background_ids);

    /**
     * @brief Get all quasi_dynamic_lane_group ids which belong to specific tile
     *
     * @note If the target tile is not existent actually, this function
     *       will return false.
     * @param[in] _tile_id tile id
     * @param[out] _quasi_dynamic_lane_group_ids vector of quasi_dynamic_lane_group ids
     * @return true: ids are read successfully, 
     *         false: An error occurs or the target is not existent or the 
     *                _quasi_dynamic_lane_group_ids is empty.
     */
    virtual bool GetAllQuasiDynamicLaneGroupIds(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _quasi_dynamic_lane_group_ids);

    /**
     * @brief Get all quasi_dynamic_lane ids which belong to specific tile
     *
     * @note If the target tile is not existent actually, this function
     *       will return false.
     * @param[in] _tile_id tile id
     * @param[out] _quasi_dynamic_lane_ids vector of quasi_dynamic_lane ids
     * @return true: ids are read successfully, 
     *         false: An error occurs or the target is not existent or the 
     *                _quasi_dynamic_lane_ids is empty.
     */
    virtual bool GetAllQuasiDynamicLaneIds(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _quasi_dynamic_lane_ids);

    /**
     * @brief Get all quasi_dynamic_region ids which belong to specific tile
     *
     * @note If the target tile is not existent actually, this function
     *       will return false.
     * @param[in] _tile_id tile id
     * @param[out] _quasi_dynamic_region_ids vector of quasi_dynamic_region ids
     * @return true: ids are read successfully, 
     *         false: An error occurs or the target is not existent or the 
     *                _quasi_dynamic_region_ids is empty.
     */
    virtual bool GetAllQuasiDynamicRegionIds(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _quasi_dynamic_region_ids);

    /**
     * @brief Get all sd_road ids which belong to specific tile
     *
     * @note If the target tile is not existent actually, this function
     *       will return false.
     * @param[in] _tile_id tile id
     * @param[out] _sd_road_ids vector of sd_road ids
     * @return true: ids are read successfully, 
     *         false: An error occurs or the target is not existent or the 
     *                _sd_road_ids is empty.
     */
    virtual bool GetAllSdRoadIds(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _sd_road_ids);

    /**
     * @brief Get all object_traffic_sign ids which belong to specific tile
     *
     * @note If the target tile is not existent actually, this function
     *       will return false.
     * @param[in] _tile_id tile id
     * @param[out] _object_traffic_sign_ids vector of object_traffic_sign ids
     * @return true: ids are read successfully, 
     *         false: An error occurs or the target is not existent or the 
     *                _object_traffic_sign_ids is empty.
     */
    virtual bool GetAllObjectTrafficSignIds(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _object_traffic_sign_ids);

    /**
     * @brief Get all object_regional_info ids which belong to specific tile
     *
     * @note If the target tile is not existent actually, this function
     *       will return false.
     * @param[in] _tile_id tile id
     * @param[out] _object_regional_info_ids vector of object_regional_info ids
     * @return true: ids are read successfully, 
     *         false: An error occurs or the target is not existent or the 
     *                _object_regional_info_ids is empty.
     */
    virtual bool GetAllObjectRegionalInfoIds(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _object_regional_info_ids);

    /**
     * @brief Get all object_safe_island ids which belong to specific tile
     *
     * @note If the target tile is not existent actually, this function
     *       will return false.
     * @param[in] _tile_id tile id
     * @param[out] _object_safe_island_ids vector of object_safe_island ids
     * @return true: ids are read successfully, 
     *         false: An error occurs or the target is not existent or the 
     *                _object_safe_island_ids is empty.
     */
    virtual bool GetAllObjectSafeIslandIds(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _object_safe_island_ids);

    /**
     * @brief Get all object_info ids which belong to specific tile
     *
     * @note If the target tile is not existent actually, this function
     *       will return false.
     * @param[in] _tile_id tile id
     * @param[out] _object_info_ids vector of object_info ids
     * @return true: ids are read successfully, 
     *         false: An error occurs or the target is not existent or the 
     *                _object_info_ids is empty.
     */
    virtual bool GetAllObjectInfoIds(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _object_info_ids);

    /**
     * @brief Get all object_linear_info ids which belong to specific tile
     *
     * @note If the target tile is not existent actually, this function
     *       will return false.
     * @param[in] _tile_id tile id
     * @param[out] _object_linear_info_ids vector of object_linear_info ids
     * @return true: ids are read successfully, 
     *         false: An error occurs or the target is not existent or the 
     *                _object_linear_info_ids is empty.
     */
    virtual bool GetAllObjectLinearInfoIds(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _object_linear_info_ids);

    /**
     * @brief Get all object_traffic_light_group ids which belong to specific tile
     *
     * @note If the target tile is not existent actually, this function
     *       will return false.
     * @param[in] _tile_id tile id
     * @param[out] _object_traffic_light_group_ids vector of object_traffic_light_group ids
     * @return true: ids are read successfully, 
     *         false: An error occurs or the target is not existent or the 
     *                _object_traffic_light_group_ids is empty.
     */
    virtual bool GetAllObjectTrafficLightGroupIds(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _object_traffic_light_group_ids);

    /**
     * @brief Get all object_stop_line ids which belong to specific tile
     *
     * @note If the target tile is not existent actually, this function
     *       will return false.
     * @param[in] _tile_id tile id
     * @param[out] _object_stop_line_ids vector of object_stop_line ids
     * @return true: ids are read successfully, 
     *         false: An error occurs or the target is not existent or the 
     *                _object_stop_line_ids is empty.
     */
    virtual bool GetAllObjectStopLineIds(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _object_stop_line_ids);

    /**
     * @brief Get all junction ids which belong to specific tile
     *
     * @note If the target tile is not existent actually, this function
     *       will return false.
     * @param[in] _tile_id tile id
     * @param[out] _junction_ids vector of junction ids
     * @return true: ids are read successfully, 
     *         false: An error occurs or the target is not existent or the 
     *                _junction_ids is empty.
     */
    virtual bool GetAllJunctionIds(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _junction_ids);

    /**
     * @brief Get all geofence ids which belong to specific tile
     *
     * @note If the target tile is not existent actually, this function
     *       will return false.
     * @param[in] _tile_id tile id
     * @param[out] _geofence_ids vector of geofence ids
     * @return true: ids are read successfully, 
     *         false: An error occurs or the target is not existent or the 
     *                _geofence_ids is empty.
     */
    virtual bool GetAllGeofenceIds(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _geofence_ids);

    /**
     * @brief Get all road ids which belong to specific tile
     *
     * @note If the target tile is not existent actually, this function
     *       will return false.
     * @param[in] _tile_id tile id
     * @param[out] _road_ids vector of road ids
     * @return true: ids are read successfully, 
     *         false: An error occurs or the target is not existent or the 
     *                _road_ids is empty.
     */
    virtual bool GetAllRoadIds(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _road_ids);

    /**
     * @brief Get all lane_group ids which belong to specific tile
     *
     * @note If the target tile is not existent actually, this function
     *       will return false.
     * @param[in] _tile_id tile id
     * @param[out] _lane_group_ids vector of lane_group ids
     * @return true: ids are read successfully, 
     *         false: An error occurs or the target is not existent or the 
     *                _lane_group_ids is empty.
     */
    virtual bool GetAllLaneGroupIds(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _lane_group_ids);

    /**
     * @brief Get all lane_boundary ids which belong to specific tile
     *
     * @note If the target tile is not existent actually, this function
     *       will return false.
     * @param[in] _tile_id tile id
     * @param[out] _lane_boundary_ids vector of lane_boundary ids
     * @return true: ids are read successfully, 
     *         false: An error occurs or the target is not existent or the 
     *                _lane_boundary_ids is empty.
     */
    virtual bool GetAllLaneBoundaryIds(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _lane_boundary_ids);

    /**
     * @brief Get all lane ids which belong to specific tile
     *
     * @note If the target tile is not existent actually, this function
     *       will return false.
     * @param[in] _tile_id tile id
     * @param[out] _lane_ids vector of lane ids
     * @return true: ids are read successfully, 
     *         false: An error occurs or the target is not existent or the 
     *                _lane_ids is empty.
     */
    virtual bool GetAllLaneIds(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _lane_ids);

    /**
     * @brief Get all object_traffic_light ids which belong to specific tile
     *
     * @note If the target tile is not existent actually, this function
     *       will return false.
     * @param[in] _tile_id tile id
     * @param[out] _object_traffic_light_ids vector of object_traffic_light ids
     * @return true: ids are read successfully, 
     *         false: An error occurs or the target is not existent or the 
     *                _object_traffic_light_ids is empty.
     */
    virtual bool GetAllObjectTrafficLightIds(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _object_traffic_light_ids);

    /**
     * @brief Get all object_pedestrian_crossing ids which belong to specific tile
     *
     * @note If the target tile is not existent actually, this function
     *       will return false.
     * @param[in] _tile_id tile id
     * @param[out] _object_pedestrian_crossing_ids vector of object_pedestrian_crossing ids
     * @return true: ids are read successfully, 
     *         false: An error occurs or the target is not existent or the 
     *                _object_pedestrian_crossing_ids is empty.
     */
    virtual bool GetAllObjectPedestrianCrossingIds(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _object_pedestrian_crossing_ids);

    /**
     * @brief Get all sd_node ids which belong to specific tile
     *
     * @note If the target tile is not existent actually, this function
     *       will return false.
     * @param[in] _tile_id tile id
     * @param[out] _sd_node_ids vector of sd_node ids
     * @return true: ids are read successfully, 
     *         false: An error occurs or the target is not existent or the 
     *                _sd_node_ids is empty.
     */
    virtual bool GetAllSdNodeIds(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _sd_node_ids);

    /**
     * @brief Get all intersection ids which belong to specific tile
     *
     * @note If the target tile is not existent actually, this function
     *       will return false.
     * @param[in] _tile_id tile id
     * @param[out] _intersection_ids vector of intersection ids
     * @return true: ids are read successfully, 
     *         false: An error occurs or the target is not existent or the 
     *                _intersection_ids is empty.
     */
    virtual bool GetAllIntersectionIds(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _intersection_ids);

    /**
     * @brief Get all routing_path ids which belong to specific tile
     *
     * @note If the target tile is not existent actually, this function
     *       will return false.
     * @param[in] _tile_id tile id
     * @param[out] _routing_path_ids vector of routing_path ids
     * @return true: ids are read successfully, 
     *         false: An error occurs or the target is not existent or the 
     *                _routing_path_ids is empty.
     */
    virtual bool GetAllRoutingPathIds(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _routing_path_ids);

    /**
     * @brief Get all routing_graph ids which belong to specific tile
     *
     * @note If the target tile is not existent actually, this function
     *       will return false.
     * @param[in] _tile_id tile id
     * @param[out] _routing_graph_ids vector of routing_graph ids
     * @return true: ids are read successfully, 
     *         false: An error occurs or the target is not existent or the 
     *                _routing_graph_ids is empty.
     */
    virtual bool GetAllRoutingGraphIds(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _routing_graph_ids);

    /**
     * @brief Get all routing_edge ids which belong to specific tile
     *
     * @note If the target tile is not existent actually, this function
     *       will return false.
     * @param[in] _tile_id tile id
     * @param[out] _routing_edge_ids vector of routing_edge ids
     * @return true: ids are read successfully, 
     *         false: An error occurs or the target is not existent or the 
     *                _routing_edge_ids is empty.
     */
    virtual bool GetAllRoutingEdgeIds(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _routing_edge_ids);

    /**
     * @brief Get all connection ids which belong to specific tile
     *
     * @note If the target tile is not existent actually, this function
     *       will return false.
     * @param[in] _tile_id tile id
     * @param[out] _connection_ids vector of connection ids
     * @return true: ids are read successfully, 
     *         false: An error occurs or the target is not existent or the 
     *                _connection_ids is empty.
     */
    virtual bool GetAllConnectionIds(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _connection_ids);

    /**
     * @brief Get all routing_node ids which belong to specific tile
     *
     * @note If the target tile is not existent actually, this function
     *       will return false.
     * @param[in] _tile_id tile id
     * @param[out] _routing_node_ids vector of routing_node ids
     * @return true: ids are read successfully, 
     *         false: An error occurs or the target is not existent or the 
     *                _routing_node_ids is empty.
     */
    virtual bool GetAllRoutingNodeIds(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _routing_node_ids);

    /**
     * @brief Get all object_parking_space ids which belong to specific tile.
     *
     * @note If the target tile is not existent actually, this function
     *       will return true, but the _object_parking_space_id will be empty.
     * @param[in] _tile_id tile id
     * @param[out] _object_parking_space_ids vector of object_parking_space ids
     * @return true: No error, although the target tile is not existent or
     *               _object_parking_space_ids is empty.
     *         false: An error occurs in this function.
     */
    virtual bool GetAllObjectParkingSpaceIdsV2(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _object_parking_space_ids);

    /**
     * @brief Get all object_parking_floor ids which belong to specific tile.
     *
     * @note If the target tile is not existent actually, this function
     *       will return true, but the _object_parking_floor_id will be empty.
     * @param[in] _tile_id tile id
     * @param[out] _object_parking_floor_ids vector of object_parking_floor ids
     * @return true: No error, although the target tile is not existent or
     *               _object_parking_floor_ids is empty.
     *         false: An error occurs in this function.
     */
    virtual bool GetAllObjectParkingFloorIdsV2(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _object_parking_floor_ids);

    /**
     * @brief Get all object_parking_lot ids which belong to specific tile.
     *
     * @note If the target tile is not existent actually, this function
     *       will return true, but the _object_parking_lot_id will be empty.
     * @param[in] _tile_id tile id
     * @param[out] _object_parking_lot_ids vector of object_parking_lot ids
     * @return true: No error, although the target tile is not existent or
     *               _object_parking_lot_ids is empty.
     *         false: An error occurs in this function.
     */
    virtual bool GetAllObjectParkingLotIdsV2(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _object_parking_lot_ids);

    /**
     * @brief Get all object_parking_poi ids which belong to specific tile.
     *
     * @note If the target tile is not existent actually, this function
     *       will return true, but the _object_parking_poi_id will be empty.
     * @param[in] _tile_id tile id
     * @param[out] _object_parking_poi_ids vector of object_parking_poi ids
     * @return true: No error, although the target tile is not existent or
     *               _object_parking_poi_ids is empty.
     *         false: An error occurs in this function.
     */
    virtual bool GetAllObjectParkingPoiIdsV2(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _object_parking_poi_ids);

    /**
     * @brief Get all object_parking_background ids which belong to specific tile.
     *
     * @note If the target tile is not existent actually, this function
     *       will return true, but the _object_parking_background_id will be empty.
     * @param[in] _tile_id tile id
     * @param[out] _object_parking_background_ids vector of object_parking_background ids
     * @return true: No error, although the target tile is not existent or
     *               _object_parking_background_ids is empty.
     *         false: An error occurs in this function.
     */
    virtual bool GetAllObjectParkingBackgroundIdsV2(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _object_parking_background_ids);

    /**
     * @brief Get all quasi_dynamic_lane_group ids which belong to specific tile.
     *
     * @note If the target tile is not existent actually, this function
     *       will return true, but the _quasi_dynamic_lane_group_id will be empty.
     * @param[in] _tile_id tile id
     * @param[out] _quasi_dynamic_lane_group_ids vector of quasi_dynamic_lane_group ids
     * @return true: No error, although the target tile is not existent or
     *               _quasi_dynamic_lane_group_ids is empty.
     *         false: An error occurs in this function.
     */
    virtual bool GetAllQuasiDynamicLaneGroupIdsV2(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _quasi_dynamic_lane_group_ids);

    /**
     * @brief Get all quasi_dynamic_lane ids which belong to specific tile.
     *
     * @note If the target tile is not existent actually, this function
     *       will return true, but the _quasi_dynamic_lane_id will be empty.
     * @param[in] _tile_id tile id
     * @param[out] _quasi_dynamic_lane_ids vector of quasi_dynamic_lane ids
     * @return true: No error, although the target tile is not existent or
     *               _quasi_dynamic_lane_ids is empty.
     *         false: An error occurs in this function.
     */
    virtual bool GetAllQuasiDynamicLaneIdsV2(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _quasi_dynamic_lane_ids);

    /**
     * @brief Get all quasi_dynamic_region ids which belong to specific tile.
     *
     * @note If the target tile is not existent actually, this function
     *       will return true, but the _quasi_dynamic_region_id will be empty.
     * @param[in] _tile_id tile id
     * @param[out] _quasi_dynamic_region_ids vector of quasi_dynamic_region ids
     * @return true: No error, although the target tile is not existent or
     *               _quasi_dynamic_region_ids is empty.
     *         false: An error occurs in this function.
     */
    virtual bool GetAllQuasiDynamicRegionIdsV2(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _quasi_dynamic_region_ids);

    /**
     * @brief Get all sd_road ids which belong to specific tile.
     *
     * @note If the target tile is not existent actually, this function
     *       will return true, but the _sd_road_id will be empty.
     * @param[in] _tile_id tile id
     * @param[out] _sd_road_ids vector of sd_road ids
     * @return true: No error, although the target tile is not existent or
     *               _sd_road_ids is empty.
     *         false: An error occurs in this function.
     */
    virtual bool GetAllSdRoadIdsV2(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _sd_road_ids);

    /**
     * @brief Get all object_traffic_sign ids which belong to specific tile.
     *
     * @note If the target tile is not existent actually, this function
     *       will return true, but the _object_traffic_sign_id will be empty.
     * @param[in] _tile_id tile id
     * @param[out] _object_traffic_sign_ids vector of object_traffic_sign ids
     * @return true: No error, although the target tile is not existent or
     *               _object_traffic_sign_ids is empty.
     *         false: An error occurs in this function.
     */
    virtual bool GetAllObjectTrafficSignIdsV2(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _object_traffic_sign_ids);

    /**
     * @brief Get all object_regional_info ids which belong to specific tile.
     *
     * @note If the target tile is not existent actually, this function
     *       will return true, but the _object_regional_info_id will be empty.
     * @param[in] _tile_id tile id
     * @param[out] _object_regional_info_ids vector of object_regional_info ids
     * @return true: No error, although the target tile is not existent or
     *               _object_regional_info_ids is empty.
     *         false: An error occurs in this function.
     */
    virtual bool GetAllObjectRegionalInfoIdsV2(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _object_regional_info_ids);

    /**
     * @brief Get all object_safe_island ids which belong to specific tile.
     *
     * @note If the target tile is not existent actually, this function
     *       will return true, but the _object_safe_island_id will be empty.
     * @param[in] _tile_id tile id
     * @param[out] _object_safe_island_ids vector of object_safe_island ids
     * @return true: No error, although the target tile is not existent or
     *               _object_safe_island_ids is empty.
     *         false: An error occurs in this function.
     */
    virtual bool GetAllObjectSafeIslandIdsV2(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _object_safe_island_ids);

    /**
     * @brief Get all object_info ids which belong to specific tile.
     *
     * @note If the target tile is not existent actually, this function
     *       will return true, but the _object_info_id will be empty.
     * @param[in] _tile_id tile id
     * @param[out] _object_info_ids vector of object_info ids
     * @return true: No error, although the target tile is not existent or
     *               _object_info_ids is empty.
     *         false: An error occurs in this function.
     */
    virtual bool GetAllObjectInfoIdsV2(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _object_info_ids);

    /**
     * @brief Get all object_linear_info ids which belong to specific tile.
     *
     * @note If the target tile is not existent actually, this function
     *       will return true, but the _object_linear_info_id will be empty.
     * @param[in] _tile_id tile id
     * @param[out] _object_linear_info_ids vector of object_linear_info ids
     * @return true: No error, although the target tile is not existent or
     *               _object_linear_info_ids is empty.
     *         false: An error occurs in this function.
     */
    virtual bool GetAllObjectLinearInfoIdsV2(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _object_linear_info_ids);

    /**
     * @brief Get all object_traffic_light_group ids which belong to specific tile.
     *
     * @note If the target tile is not existent actually, this function
     *       will return true, but the _object_traffic_light_group_id will be empty.
     * @param[in] _tile_id tile id
     * @param[out] _object_traffic_light_group_ids vector of object_traffic_light_group ids
     * @return true: No error, although the target tile is not existent or
     *               _object_traffic_light_group_ids is empty.
     *         false: An error occurs in this function.
     */
    virtual bool GetAllObjectTrafficLightGroupIdsV2(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _object_traffic_light_group_ids);

    /**
     * @brief Get all object_stop_line ids which belong to specific tile.
     *
     * @note If the target tile is not existent actually, this function
     *       will return true, but the _object_stop_line_id will be empty.
     * @param[in] _tile_id tile id
     * @param[out] _object_stop_line_ids vector of object_stop_line ids
     * @return true: No error, although the target tile is not existent or
     *               _object_stop_line_ids is empty.
     *         false: An error occurs in this function.
     */
    virtual bool GetAllObjectStopLineIdsV2(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _object_stop_line_ids);

    /**
     * @brief Get all junction ids which belong to specific tile.
     *
     * @note If the target tile is not existent actually, this function
     *       will return true, but the _junction_id will be empty.
     * @param[in] _tile_id tile id
     * @param[out] _junction_ids vector of junction ids
     * @return true: No error, although the target tile is not existent or
     *               _junction_ids is empty.
     *         false: An error occurs in this function.
     */
    virtual bool GetAllJunctionIdsV2(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _junction_ids);

    /**
     * @brief Get all geofence ids which belong to specific tile.
     *
     * @note If the target tile is not existent actually, this function
     *       will return true, but the _geofence_id will be empty.
     * @param[in] _tile_id tile id
     * @param[out] _geofence_ids vector of geofence ids
     * @return true: No error, although the target tile is not existent or
     *               _geofence_ids is empty.
     *         false: An error occurs in this function.
     */
    virtual bool GetAllGeofenceIdsV2(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _geofence_ids);

    /**
     * @brief Get all road ids which belong to specific tile.
     *
     * @note If the target tile is not existent actually, this function
     *       will return true, but the _road_id will be empty.
     * @param[in] _tile_id tile id
     * @param[out] _road_ids vector of road ids
     * @return true: No error, although the target tile is not existent or
     *               _road_ids is empty.
     *         false: An error occurs in this function.
     */
    virtual bool GetAllRoadIdsV2(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _road_ids);

    /**
     * @brief Get all lane_group ids which belong to specific tile.
     *
     * @note If the target tile is not existent actually, this function
     *       will return true, but the _lane_group_id will be empty.
     * @param[in] _tile_id tile id
     * @param[out] _lane_group_ids vector of lane_group ids
     * @return true: No error, although the target tile is not existent or
     *               _lane_group_ids is empty.
     *         false: An error occurs in this function.
     */
    virtual bool GetAllLaneGroupIdsV2(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _lane_group_ids);

    /**
     * @brief Get all lane_boundary ids which belong to specific tile.
     *
     * @note If the target tile is not existent actually, this function
     *       will return true, but the _lane_boundary_id will be empty.
     * @param[in] _tile_id tile id
     * @param[out] _lane_boundary_ids vector of lane_boundary ids
     * @return true: No error, although the target tile is not existent or
     *               _lane_boundary_ids is empty.
     *         false: An error occurs in this function.
     */
    virtual bool GetAllLaneBoundaryIdsV2(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _lane_boundary_ids);

    /**
     * @brief Get all lane ids which belong to specific tile.
     *
     * @note If the target tile is not existent actually, this function
     *       will return true, but the _lane_id will be empty.
     * @param[in] _tile_id tile id
     * @param[out] _lane_ids vector of lane ids
     * @return true: No error, although the target tile is not existent or
     *               _lane_ids is empty.
     *         false: An error occurs in this function.
     */
    virtual bool GetAllLaneIdsV2(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _lane_ids);

    /**
     * @brief Get all object_traffic_light ids which belong to specific tile.
     *
     * @note If the target tile is not existent actually, this function
     *       will return true, but the _object_traffic_light_id will be empty.
     * @param[in] _tile_id tile id
     * @param[out] _object_traffic_light_ids vector of object_traffic_light ids
     * @return true: No error, although the target tile is not existent or
     *               _object_traffic_light_ids is empty.
     *         false: An error occurs in this function.
     */
    virtual bool GetAllObjectTrafficLightIdsV2(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _object_traffic_light_ids);

    /**
     * @brief Get all object_pedestrian_crossing ids which belong to specific tile.
     *
     * @note If the target tile is not existent actually, this function
     *       will return true, but the _object_pedestrian_crossing_id will be empty.
     * @param[in] _tile_id tile id
     * @param[out] _object_pedestrian_crossing_ids vector of object_pedestrian_crossing ids
     * @return true: No error, although the target tile is not existent or
     *               _object_pedestrian_crossing_ids is empty.
     *         false: An error occurs in this function.
     */
    virtual bool GetAllObjectPedestrianCrossingIdsV2(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _object_pedestrian_crossing_ids);

    /**
     * @brief Get all sd_node ids which belong to specific tile.
     *
     * @note If the target tile is not existent actually, this function
     *       will return true, but the _sd_node_id will be empty.
     * @param[in] _tile_id tile id
     * @param[out] _sd_node_ids vector of sd_node ids
     * @return true: No error, although the target tile is not existent or
     *               _sd_node_ids is empty.
     *         false: An error occurs in this function.
     */
    virtual bool GetAllSdNodeIdsV2(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _sd_node_ids);

    /**
     * @brief Get all intersection ids which belong to specific tile.
     *
     * @note If the target tile is not existent actually, this function
     *       will return true, but the _intersection_id will be empty.
     * @param[in] _tile_id tile id
     * @param[out] _intersection_ids vector of intersection ids
     * @return true: No error, although the target tile is not existent or
     *               _intersection_ids is empty.
     *         false: An error occurs in this function.
     */
    virtual bool GetAllIntersectionIdsV2(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _intersection_ids);

    /**
     * @brief Get all routing_path ids which belong to specific tile.
     *
     * @note If the target tile is not existent actually, this function
     *       will return true, but the _routing_path_id will be empty.
     * @param[in] _tile_id tile id
     * @param[out] _routing_path_ids vector of routing_path ids
     * @return true: No error, although the target tile is not existent or
     *               _routing_path_ids is empty.
     *         false: An error occurs in this function.
     */
    virtual bool GetAllRoutingPathIdsV2(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _routing_path_ids);

    /**
     * @brief Get all routing_graph ids which belong to specific tile.
     *
     * @note If the target tile is not existent actually, this function
     *       will return true, but the _routing_graph_id will be empty.
     * @param[in] _tile_id tile id
     * @param[out] _routing_graph_ids vector of routing_graph ids
     * @return true: No error, although the target tile is not existent or
     *               _routing_graph_ids is empty.
     *         false: An error occurs in this function.
     */
    virtual bool GetAllRoutingGraphIdsV2(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _routing_graph_ids);

    /**
     * @brief Get all routing_edge ids which belong to specific tile.
     *
     * @note If the target tile is not existent actually, this function
     *       will return true, but the _routing_edge_id will be empty.
     * @param[in] _tile_id tile id
     * @param[out] _routing_edge_ids vector of routing_edge ids
     * @return true: No error, although the target tile is not existent or
     *               _routing_edge_ids is empty.
     *         false: An error occurs in this function.
     */
    virtual bool GetAllRoutingEdgeIdsV2(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _routing_edge_ids);

    /**
     * @brief Get all connection ids which belong to specific tile.
     *
     * @note If the target tile is not existent actually, this function
     *       will return true, but the _connection_id will be empty.
     * @param[in] _tile_id tile id
     * @param[out] _connection_ids vector of connection ids
     * @return true: No error, although the target tile is not existent or
     *               _connection_ids is empty.
     *         false: An error occurs in this function.
     */
    virtual bool GetAllConnectionIdsV2(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _connection_ids);

    /**
     * @brief Get all routing_node ids which belong to specific tile.
     *
     * @note If the target tile is not existent actually, this function
     *       will return true, but the _routing_node_id will be empty.
     * @param[in] _tile_id tile id
     * @param[out] _routing_node_ids vector of routing_node ids
     * @return true: No error, although the target tile is not existent or
     *               _routing_node_ids is empty.
     *         false: An error occurs in this function.
     */
    virtual bool GetAllRoutingNodeIdsV2(const MapFeatureIdType _tile_id,
                       ::std::vector<MapFeatureIdType>& _routing_node_ids);

private:

    /**
     * @brief Get specific data from corresponding database by id.
     *
     * @note If the specific data is not existent actually, this function will
     *       return false.
     * @param[in] _id primary key
     * @param[in] _sq specific sqlite object
     * @param[in] _db corresponding data base pointer, get by sqlite3_open(path_to_db,
     *                &db)
     * @param[out] _ptr data pointer for the result
     * @param[out] _memcache memcache for the result
     * @return true: result is fetched successfully; 
     *         false: An error occurs or the target data is not existent.
     */
    template <typename KeyType, typename DataType>
    bool GetSpecificDataById(KeyType const _id,
                             ::std::shared_ptr<DataType>& _ptr,
                             ::std::shared_ptr<MemCache<KeyType, DataType> >& _memcache);

    /**
     * @brief Get specific data from corresponding database by id.
     *
     * @note If the specific data is not existent actually, this function will
     *       return true, but _valid will be set false.
     * @param[in] _id primary key
     * @param[in] _sq specific sqlite object
     * @param[in] _db corresponding data base pointer, get by sqlite3_open(path_to_db, 
     *                &db)
     * @param[out] _ptr data pointer for the result
     * @param[out] _memcache memcache for the result
     * @param[out] _valid Whether or not the specific data is valid.
     * @return true: No error, if the specific data is not existent, _valid will
     *               be false, so you should check the _valid always.
     *         false: An error occurs in this function.
     */
    template <typename KeyType, typename DataType>
    bool GetSpecificDataByIdV2(KeyType const _id,
                               ::std::shared_ptr<DataType>& _ptr,
                               ::std::shared_ptr<MemCache<KeyType, DataType> >& _memcache,
                               bool& _valid);

protected:
    /**
     * @brief Add feature to memory cache.
     * 
     * @param[in] ptr Feature with smart pointer.
     * @return true: No error.
     *         false: An error occurs in this function.
     */
    holo::bool_t AddFeatureToMemCache(std::shared_ptr<holo::map::format::Base> ptr);

    /**
     * @brief Remove special feature from memory cache.
     *
     * @param[in] type Feature type, refer to @FeatureType for more details.
     * @param[in] id Feature id.
     */
    void RemoveFeatureFromMemCache(const FeatureType type, const MapFeatureIdType id);

private:
    EngineType engine_type_; ///< Indicate the database engine of current retriverver.

    /// If the engine type is ENGINE_TYPE_HOLO_NDS_DB, the value is the directory of Holo NDS database.
    /// If the engine type is ENGINE_TYPE_NAVINFO_NDS_DB, the value is the absolute config name of Navinfo SDK;
    ::std::string map_data_directory_;

public:
    // cache

    ::std::shared_ptr<MemCache<MapFeatureIdType, format::ObjectParkingSpace > > cache_object_parking_space_;

    ::std::shared_ptr<MemCache<MapFeatureIdType, format::ObjectParkingFloor > > cache_object_parking_floor_;

    ::std::shared_ptr<MemCache<MapFeatureIdType, format::ObjectParkingLot > > cache_object_parking_lot_;

    ::std::shared_ptr<MemCache<MapFeatureIdType, format::ObjectParkingPoi > > cache_object_parking_poi_;

    ::std::shared_ptr<MemCache<MapFeatureIdType, format::ObjectParkingBackground > > cache_object_parking_background_;

    ::std::shared_ptr<MemCache<MapFeatureIdType, format::QuasiDynamicLaneGroup > > cache_quasi_dynamic_lane_group_;

    ::std::shared_ptr<MemCache<MapFeatureIdType, format::QuasiDynamicLane > > cache_quasi_dynamic_lane_;

    ::std::shared_ptr<MemCache<MapFeatureIdType, format::QuasiDynamicRegion > > cache_quasi_dynamic_region_;

    ::std::shared_ptr<MemCache<MapFeatureIdType, format::Tile > > cache_tile_;

    ::std::shared_ptr<MemCache<MapFeatureIdType, format::SdRoad > > cache_sd_road_;

    ::std::shared_ptr<MemCache<MapFeatureIdType, format::ObjectTrafficSign > > cache_object_traffic_sign_;

    ::std::shared_ptr<MemCache<MapFeatureIdType, format::ObjectRegionalInfo > > cache_object_regional_info_;

    ::std::shared_ptr<MemCache<MapFeatureIdType, format::ObjectSafeIsland > > cache_object_safe_island_;

    ::std::shared_ptr<MemCache<MapFeatureIdType, format::ObjectInfo > > cache_object_info_;

    ::std::shared_ptr<MemCache<MapFeatureIdType, format::ObjectLinearInfo > > cache_object_linear_info_;

    ::std::shared_ptr<MemCache<MapFeatureIdType, format::ObjectTrafficLightGroup > > cache_object_traffic_light_group_;

    ::std::shared_ptr<MemCache<MapFeatureIdType, format::ObjectStopLine > > cache_object_stop_line_;

    ::std::shared_ptr<MemCache<MapFeatureIdType, format::Junction > > cache_junction_;

    ::std::shared_ptr<MemCache<MapFeatureIdType, format::Geofence > > cache_geofence_;

    ::std::shared_ptr<MemCache<MapFeatureIdType, format::Road > > cache_road_;

    ::std::shared_ptr<MemCache<MapFeatureIdType, format::LaneGroup > > cache_lane_group_;

    ::std::shared_ptr<MemCache<MapFeatureIdType, format::LaneBoundary > > cache_lane_boundary_;

    ::std::shared_ptr<MemCache<MapFeatureIdType, format::Lane > > cache_lane_;

    ::std::shared_ptr<MemCache<MapFeatureIdType, format::ObjectTrafficLight > > cache_object_traffic_light_;

    ::std::shared_ptr<MemCache<MapFeatureIdType, format::ObjectPedestrianCrossing > > cache_object_pedestrian_crossing_;

    ::std::shared_ptr<MemCache<MapFeatureIdType, format::SdNode > > cache_sd_node_;

    ::std::shared_ptr<MemCache<MapFeatureIdType, format::Intersection > > cache_intersection_;

    ::std::shared_ptr<MemCache<MapFeatureIdType, format::RoutingPath > > cache_routing_path_;

    ::std::shared_ptr<MemCache<MapFeatureIdType, format::RoutingGraph > > cache_routing_graph_;

    ::std::shared_ptr<MemCache<MapFeatureIdType, format::RoutingEdge > > cache_routing_edge_;

    ::std::shared_ptr<MemCache<MapFeatureIdType, format::Connection > > cache_connection_;

    ::std::shared_ptr<MemCache<MapFeatureIdType, format::RoutingNode > > cache_routing_node_;

    ::std::shared_ptr<MemCache<MapFeatureIdType, format::Header > > cache_header_;
};

namespace retriever
{
namespace helper
{

/**
 * @addtogroup helper
 * @{
 *
 */

/// Define feature type for holo::map::retriever::helper.
using FeatureType           = holo::map::format::helper::FeatureType;
/// Define feature vector type for holo::map::retriever::helper.
using FeatureVectorType     = holo::map::format::helper::FeatureVectorType;

/// Define feature base type for holo::map::retriever::helper.
using FeatureBaseType       = holo::map::format::Base;
/// Define shared pointer type for FeatureBaseType.
using FeatureBaseSPtrType   = std::shared_ptr<FeatureBaseType>;

/**
 * @brief Create a new feature shared pointer by feature type. 
 *
 * @tparam Type FeatureType;
 * @tparam T pointer refer to format::Base(format::Base*, std::shared_ptr<format::Base>);
 *
 * @param[in] feature_type Feature type refer to holo::map::format::Base::FeatureType;
 * @param[out] base A shared pointer refer to base class.
 * @return true: No error;
 *         false: An error occurs in this function or in f.
 */
template<typename Type, typename T>
holo::bool_t CreateFeatureByType(Type const feature_type, typename holo::map::format::helper::FeatureTraits<T>::SPtrType& feature)
{
    feature = nullptr;

    switch (feature_type)
    {

    case Type::OBJECT_PARKING_SPACE:
    {
        feature = std::dynamic_pointer_cast<typename holo::map::format::helper::FeatureTraits<T>::RawType>(
            std::make_shared<holo::map::format::ObjectParkingSpace>());
        break;
    }

    case Type::OBJECT_PARKING_FLOOR:
    {
        feature = std::dynamic_pointer_cast<typename holo::map::format::helper::FeatureTraits<T>::RawType>(
            std::make_shared<holo::map::format::ObjectParkingFloor>());
        break;
    }

    case Type::OBJECT_PARKING_LOT:
    {
        feature = std::dynamic_pointer_cast<typename holo::map::format::helper::FeatureTraits<T>::RawType>(
            std::make_shared<holo::map::format::ObjectParkingLot>());
        break;
    }

    case Type::OBJECT_PARKING_POI:
    {
        feature = std::dynamic_pointer_cast<typename holo::map::format::helper::FeatureTraits<T>::RawType>(
            std::make_shared<holo::map::format::ObjectParkingPoi>());
        break;
    }

    case Type::OBJECT_PARKING_BACKGROUND:
    {
        feature = std::dynamic_pointer_cast<typename holo::map::format::helper::FeatureTraits<T>::RawType>(
            std::make_shared<holo::map::format::ObjectParkingBackground>());
        break;
    }

    case Type::QUASI_DYNAMIC_LANE_GROUP:
    {
        feature = std::dynamic_pointer_cast<typename holo::map::format::helper::FeatureTraits<T>::RawType>(
            std::make_shared<holo::map::format::QuasiDynamicLaneGroup>());
        break;
    }

    case Type::QUASI_DYNAMIC_LANE:
    {
        feature = std::dynamic_pointer_cast<typename holo::map::format::helper::FeatureTraits<T>::RawType>(
            std::make_shared<holo::map::format::QuasiDynamicLane>());
        break;
    }

    case Type::QUASI_DYNAMIC_REGION:
    {
        feature = std::dynamic_pointer_cast<typename holo::map::format::helper::FeatureTraits<T>::RawType>(
            std::make_shared<holo::map::format::QuasiDynamicRegion>());
        break;
    }

    case Type::TILE:
    {
        feature = std::dynamic_pointer_cast<typename holo::map::format::helper::FeatureTraits<T>::RawType>(
            std::make_shared<holo::map::format::Tile>());
        break;
    }

    case Type::SD_ROAD:
    {
        feature = std::dynamic_pointer_cast<typename holo::map::format::helper::FeatureTraits<T>::RawType>(
            std::make_shared<holo::map::format::SdRoad>());
        break;
    }

    case Type::OBJECT_TRAFFIC_SIGN:
    {
        feature = std::dynamic_pointer_cast<typename holo::map::format::helper::FeatureTraits<T>::RawType>(
            std::make_shared<holo::map::format::ObjectTrafficSign>());
        break;
    }

    case Type::OBJECT_REGIONAL_INFO:
    {
        feature = std::dynamic_pointer_cast<typename holo::map::format::helper::FeatureTraits<T>::RawType>(
            std::make_shared<holo::map::format::ObjectRegionalInfo>());
        break;
    }

    case Type::OBJECT_SAFE_ISLAND:
    {
        feature = std::dynamic_pointer_cast<typename holo::map::format::helper::FeatureTraits<T>::RawType>(
            std::make_shared<holo::map::format::ObjectSafeIsland>());
        break;
    }

    case Type::OBJECT_INFO:
    {
        feature = std::dynamic_pointer_cast<typename holo::map::format::helper::FeatureTraits<T>::RawType>(
            std::make_shared<holo::map::format::ObjectInfo>());
        break;
    }

    case Type::OBJECT_LINEAR_INFO:
    {
        feature = std::dynamic_pointer_cast<typename holo::map::format::helper::FeatureTraits<T>::RawType>(
            std::make_shared<holo::map::format::ObjectLinearInfo>());
        break;
    }

    case Type::OBJECT_TRAFFIC_LIGHT_GROUP:
    {
        feature = std::dynamic_pointer_cast<typename holo::map::format::helper::FeatureTraits<T>::RawType>(
            std::make_shared<holo::map::format::ObjectTrafficLightGroup>());
        break;
    }

    case Type::OBJECT_STOP_LINE:
    {
        feature = std::dynamic_pointer_cast<typename holo::map::format::helper::FeatureTraits<T>::RawType>(
            std::make_shared<holo::map::format::ObjectStopLine>());
        break;
    }

    case Type::JUNCTION:
    {
        feature = std::dynamic_pointer_cast<typename holo::map::format::helper::FeatureTraits<T>::RawType>(
            std::make_shared<holo::map::format::Junction>());
        break;
    }

    case Type::GEOFENCE:
    {
        feature = std::dynamic_pointer_cast<typename holo::map::format::helper::FeatureTraits<T>::RawType>(
            std::make_shared<holo::map::format::Geofence>());
        break;
    }

    case Type::ROAD:
    {
        feature = std::dynamic_pointer_cast<typename holo::map::format::helper::FeatureTraits<T>::RawType>(
            std::make_shared<holo::map::format::Road>());
        break;
    }

    case Type::LANE_GROUP:
    {
        feature = std::dynamic_pointer_cast<typename holo::map::format::helper::FeatureTraits<T>::RawType>(
            std::make_shared<holo::map::format::LaneGroup>());
        break;
    }

    case Type::LANE_BOUNDARY:
    {
        feature = std::dynamic_pointer_cast<typename holo::map::format::helper::FeatureTraits<T>::RawType>(
            std::make_shared<holo::map::format::LaneBoundary>());
        break;
    }

    case Type::LANE:
    {
        feature = std::dynamic_pointer_cast<typename holo::map::format::helper::FeatureTraits<T>::RawType>(
            std::make_shared<holo::map::format::Lane>());
        break;
    }

    case Type::OBJECT_TRAFFIC_LIGHT:
    {
        feature = std::dynamic_pointer_cast<typename holo::map::format::helper::FeatureTraits<T>::RawType>(
            std::make_shared<holo::map::format::ObjectTrafficLight>());
        break;
    }

    case Type::OBJECT_PEDESTRIAN_CROSSING:
    {
        feature = std::dynamic_pointer_cast<typename holo::map::format::helper::FeatureTraits<T>::RawType>(
            std::make_shared<holo::map::format::ObjectPedestrianCrossing>());
        break;
    }

    case Type::SD_NODE:
    {
        feature = std::dynamic_pointer_cast<typename holo::map::format::helper::FeatureTraits<T>::RawType>(
            std::make_shared<holo::map::format::SdNode>());
        break;
    }

    case Type::INTERSECTION:
    {
        feature = std::dynamic_pointer_cast<typename holo::map::format::helper::FeatureTraits<T>::RawType>(
            std::make_shared<holo::map::format::Intersection>());
        break;
    }

    case Type::ROUTING_PATH:
    {
        feature = std::dynamic_pointer_cast<typename holo::map::format::helper::FeatureTraits<T>::RawType>(
            std::make_shared<holo::map::format::RoutingPath>());
        break;
    }

    case Type::ROUTING_GRAPH:
    {
        feature = std::dynamic_pointer_cast<typename holo::map::format::helper::FeatureTraits<T>::RawType>(
            std::make_shared<holo::map::format::RoutingGraph>());
        break;
    }

    case Type::ROUTING_EDGE:
    {
        feature = std::dynamic_pointer_cast<typename holo::map::format::helper::FeatureTraits<T>::RawType>(
            std::make_shared<holo::map::format::RoutingEdge>());
        break;
    }

    case Type::CONNECTION:
    {
        feature = std::dynamic_pointer_cast<typename holo::map::format::helper::FeatureTraits<T>::RawType>(
            std::make_shared<holo::map::format::Connection>());
        break;
    }

    case Type::ROUTING_NODE:
    {
        feature = std::dynamic_pointer_cast<typename holo::map::format::helper::FeatureTraits<T>::RawType>(
            std::make_shared<holo::map::format::RoutingNode>());
        break;
    }
    default:
    {
        break;
    }
    }

    holo::bool_t const ok = (nullptr == feature ? false : true);
    if (!ok)
    {
        LOG(ERROR) << "CreateFeatureByType fail, feature_type=" << static_cast<int>(feature_type);
    }
    return ok;
}

/**
 * @brief Access feature id form a pointer by feature type. 
 *
 * @tparam Type FeatureType;
 * @tparam T pointer refer to format::Base(format::Base*, std::shared_ptr<format::Base>);
 * @tparam Id FeatureId;
 *
 * @param[in] feature_type Feature type refer to holo::map::format::Base::FeatureType;
 * @param[in] base A shared pointer refer to a concrete feature.
 * @param[in] feature_id Feature id of target feature.
 * @return true: No error;
 *         false: An error occurs in this function or in f.
 */
template<typename Type, typename T, typename Id>
holo::bool_t GetFeatureIdByType(Type const feature_type, typename holo::map::format::helper::FeatureTraits<T>::SPtrType base,
    Id& feature_id)
{
    feature_id = 0;
    if (nullptr == base)
    {
        LOG(ERROR) << "GetFeatureIdByType fail, invalid parameters, type=" << static_cast<int>(feature_type);
        return false;
    }

    switch (feature_type)
    {

    case Type::OBJECT_PARKING_SPACE:
    {
        std::shared_ptr<holo::map::format::ObjectParkingSpace> feature =
            std::dynamic_pointer_cast<holo::map::format::ObjectParkingSpace>(base);
        if (nullptr == feature)
        {
            LOG(ERROR) << "GetFeatureIdByType fail, invalid pointer, feature_type=" << static_cast<int>(feature_type);
            return false;
        }
        feature_id = feature->GetObjectParkingSpaceId();
        break;
    }

    case Type::OBJECT_PARKING_FLOOR:
    {
        std::shared_ptr<holo::map::format::ObjectParkingFloor> feature =
            std::dynamic_pointer_cast<holo::map::format::ObjectParkingFloor>(base);
        if (nullptr == feature)
        {
            LOG(ERROR) << "GetFeatureIdByType fail, invalid pointer, feature_type=" << static_cast<int>(feature_type);
            return false;
        }
        feature_id = feature->GetObjectParkingFloorId();
        break;
    }

    case Type::OBJECT_PARKING_LOT:
    {
        std::shared_ptr<holo::map::format::ObjectParkingLot> feature =
            std::dynamic_pointer_cast<holo::map::format::ObjectParkingLot>(base);
        if (nullptr == feature)
        {
            LOG(ERROR) << "GetFeatureIdByType fail, invalid pointer, feature_type=" << static_cast<int>(feature_type);
            return false;
        }
        feature_id = feature->GetObjectParkingLotId();
        break;
    }

    case Type::OBJECT_PARKING_POI:
    {
        std::shared_ptr<holo::map::format::ObjectParkingPoi> feature =
            std::dynamic_pointer_cast<holo::map::format::ObjectParkingPoi>(base);
        if (nullptr == feature)
        {
            LOG(ERROR) << "GetFeatureIdByType fail, invalid pointer, feature_type=" << static_cast<int>(feature_type);
            return false;
        }
        feature_id = feature->GetObjectParkingPoiId();
        break;
    }

    case Type::OBJECT_PARKING_BACKGROUND:
    {
        std::shared_ptr<holo::map::format::ObjectParkingBackground> feature =
            std::dynamic_pointer_cast<holo::map::format::ObjectParkingBackground>(base);
        if (nullptr == feature)
        {
            LOG(ERROR) << "GetFeatureIdByType fail, invalid pointer, feature_type=" << static_cast<int>(feature_type);
            return false;
        }
        feature_id = feature->GetObjectParkingBackgroundId();
        break;
    }

    case Type::QUASI_DYNAMIC_LANE_GROUP:
    {
        std::shared_ptr<holo::map::format::QuasiDynamicLaneGroup> feature =
            std::dynamic_pointer_cast<holo::map::format::QuasiDynamicLaneGroup>(base);
        if (nullptr == feature)
        {
            LOG(ERROR) << "GetFeatureIdByType fail, invalid pointer, feature_type=" << static_cast<int>(feature_type);
            return false;
        }
        feature_id = feature->GetQuasiDynamicLaneGroupId();
        break;
    }

    case Type::QUASI_DYNAMIC_LANE:
    {
        std::shared_ptr<holo::map::format::QuasiDynamicLane> feature =
            std::dynamic_pointer_cast<holo::map::format::QuasiDynamicLane>(base);
        if (nullptr == feature)
        {
            LOG(ERROR) << "GetFeatureIdByType fail, invalid pointer, feature_type=" << static_cast<int>(feature_type);
            return false;
        }
        feature_id = feature->GetQuasiDynamicLaneId();
        break;
    }

    case Type::QUASI_DYNAMIC_REGION:
    {
        std::shared_ptr<holo::map::format::QuasiDynamicRegion> feature =
            std::dynamic_pointer_cast<holo::map::format::QuasiDynamicRegion>(base);
        if (nullptr == feature)
        {
            LOG(ERROR) << "GetFeatureIdByType fail, invalid pointer, feature_type=" << static_cast<int>(feature_type);
            return false;
        }
        feature_id = feature->GetQuasiDynamicRegionId();
        break;
    }

    case Type::TILE:
    {
        std::shared_ptr<holo::map::format::Tile> feature =
            std::dynamic_pointer_cast<holo::map::format::Tile>(base);
        if (nullptr == feature)
        {
            LOG(ERROR) << "GetFeatureIdByType fail, invalid pointer, feature_type=" << static_cast<int>(feature_type);
            return false;
        }
        feature_id = feature->GetTileId();
        break;
    }

    case Type::SD_ROAD:
    {
        std::shared_ptr<holo::map::format::SdRoad> feature =
            std::dynamic_pointer_cast<holo::map::format::SdRoad>(base);
        if (nullptr == feature)
        {
            LOG(ERROR) << "GetFeatureIdByType fail, invalid pointer, feature_type=" << static_cast<int>(feature_type);
            return false;
        }
        feature_id = feature->GetSdRoadId();
        break;
    }

    case Type::OBJECT_TRAFFIC_SIGN:
    {
        std::shared_ptr<holo::map::format::ObjectTrafficSign> feature =
            std::dynamic_pointer_cast<holo::map::format::ObjectTrafficSign>(base);
        if (nullptr == feature)
        {
            LOG(ERROR) << "GetFeatureIdByType fail, invalid pointer, feature_type=" << static_cast<int>(feature_type);
            return false;
        }
        feature_id = feature->GetObjectTrafficSignId();
        break;
    }

    case Type::OBJECT_REGIONAL_INFO:
    {
        std::shared_ptr<holo::map::format::ObjectRegionalInfo> feature =
            std::dynamic_pointer_cast<holo::map::format::ObjectRegionalInfo>(base);
        if (nullptr == feature)
        {
            LOG(ERROR) << "GetFeatureIdByType fail, invalid pointer, feature_type=" << static_cast<int>(feature_type);
            return false;
        }
        feature_id = feature->GetObjectRegionalInfoId();
        break;
    }

    case Type::OBJECT_SAFE_ISLAND:
    {
        std::shared_ptr<holo::map::format::ObjectSafeIsland> feature =
            std::dynamic_pointer_cast<holo::map::format::ObjectSafeIsland>(base);
        if (nullptr == feature)
        {
            LOG(ERROR) << "GetFeatureIdByType fail, invalid pointer, feature_type=" << static_cast<int>(feature_type);
            return false;
        }
        feature_id = feature->GetObjectSafeIslandId();
        break;
    }

    case Type::OBJECT_INFO:
    {
        std::shared_ptr<holo::map::format::ObjectInfo> feature =
            std::dynamic_pointer_cast<holo::map::format::ObjectInfo>(base);
        if (nullptr == feature)
        {
            LOG(ERROR) << "GetFeatureIdByType fail, invalid pointer, feature_type=" << static_cast<int>(feature_type);
            return false;
        }
        feature_id = feature->GetObjectInfoId();
        break;
    }

    case Type::OBJECT_LINEAR_INFO:
    {
        std::shared_ptr<holo::map::format::ObjectLinearInfo> feature =
            std::dynamic_pointer_cast<holo::map::format::ObjectLinearInfo>(base);
        if (nullptr == feature)
        {
            LOG(ERROR) << "GetFeatureIdByType fail, invalid pointer, feature_type=" << static_cast<int>(feature_type);
            return false;
        }
        feature_id = feature->GetObjectLinearInfoId();
        break;
    }

    case Type::OBJECT_TRAFFIC_LIGHT_GROUP:
    {
        std::shared_ptr<holo::map::format::ObjectTrafficLightGroup> feature =
            std::dynamic_pointer_cast<holo::map::format::ObjectTrafficLightGroup>(base);
        if (nullptr == feature)
        {
            LOG(ERROR) << "GetFeatureIdByType fail, invalid pointer, feature_type=" << static_cast<int>(feature_type);
            return false;
        }
        feature_id = feature->GetObjectTrafficLightGroupId();
        break;
    }

    case Type::OBJECT_STOP_LINE:
    {
        std::shared_ptr<holo::map::format::ObjectStopLine> feature =
            std::dynamic_pointer_cast<holo::map::format::ObjectStopLine>(base);
        if (nullptr == feature)
        {
            LOG(ERROR) << "GetFeatureIdByType fail, invalid pointer, feature_type=" << static_cast<int>(feature_type);
            return false;
        }
        feature_id = feature->GetObjectStopLineId();
        break;
    }

    case Type::JUNCTION:
    {
        std::shared_ptr<holo::map::format::Junction> feature =
            std::dynamic_pointer_cast<holo::map::format::Junction>(base);
        if (nullptr == feature)
        {
            LOG(ERROR) << "GetFeatureIdByType fail, invalid pointer, feature_type=" << static_cast<int>(feature_type);
            return false;
        }
        feature_id = feature->GetJunctionId();
        break;
    }

    case Type::GEOFENCE:
    {
        std::shared_ptr<holo::map::format::Geofence> feature =
            std::dynamic_pointer_cast<holo::map::format::Geofence>(base);
        if (nullptr == feature)
        {
            LOG(ERROR) << "GetFeatureIdByType fail, invalid pointer, feature_type=" << static_cast<int>(feature_type);
            return false;
        }
        feature_id = feature->GetGeofenceId();
        break;
    }

    case Type::ROAD:
    {
        std::shared_ptr<holo::map::format::Road> feature =
            std::dynamic_pointer_cast<holo::map::format::Road>(base);
        if (nullptr == feature)
        {
            LOG(ERROR) << "GetFeatureIdByType fail, invalid pointer, feature_type=" << static_cast<int>(feature_type);
            return false;
        }
        feature_id = feature->GetRoadId();
        break;
    }

    case Type::LANE_GROUP:
    {
        std::shared_ptr<holo::map::format::LaneGroup> feature =
            std::dynamic_pointer_cast<holo::map::format::LaneGroup>(base);
        if (nullptr == feature)
        {
            LOG(ERROR) << "GetFeatureIdByType fail, invalid pointer, feature_type=" << static_cast<int>(feature_type);
            return false;
        }
        feature_id = feature->GetLaneGroupId();
        break;
    }

    case Type::LANE_BOUNDARY:
    {
        std::shared_ptr<holo::map::format::LaneBoundary> feature =
            std::dynamic_pointer_cast<holo::map::format::LaneBoundary>(base);
        if (nullptr == feature)
        {
            LOG(ERROR) << "GetFeatureIdByType fail, invalid pointer, feature_type=" << static_cast<int>(feature_type);
            return false;
        }
        feature_id = feature->GetLaneBoundaryId();
        break;
    }

    case Type::LANE:
    {
        std::shared_ptr<holo::map::format::Lane> feature =
            std::dynamic_pointer_cast<holo::map::format::Lane>(base);
        if (nullptr == feature)
        {
            LOG(ERROR) << "GetFeatureIdByType fail, invalid pointer, feature_type=" << static_cast<int>(feature_type);
            return false;
        }
        feature_id = feature->GetLaneId();
        break;
    }

    case Type::OBJECT_TRAFFIC_LIGHT:
    {
        std::shared_ptr<holo::map::format::ObjectTrafficLight> feature =
            std::dynamic_pointer_cast<holo::map::format::ObjectTrafficLight>(base);
        if (nullptr == feature)
        {
            LOG(ERROR) << "GetFeatureIdByType fail, invalid pointer, feature_type=" << static_cast<int>(feature_type);
            return false;
        }
        feature_id = feature->GetObjectTrafficLightId();
        break;
    }

    case Type::OBJECT_PEDESTRIAN_CROSSING:
    {
        std::shared_ptr<holo::map::format::ObjectPedestrianCrossing> feature =
            std::dynamic_pointer_cast<holo::map::format::ObjectPedestrianCrossing>(base);
        if (nullptr == feature)
        {
            LOG(ERROR) << "GetFeatureIdByType fail, invalid pointer, feature_type=" << static_cast<int>(feature_type);
            return false;
        }
        feature_id = feature->GetObjectPedestrianCrossingId();
        break;
    }

    case Type::SD_NODE:
    {
        std::shared_ptr<holo::map::format::SdNode> feature =
            std::dynamic_pointer_cast<holo::map::format::SdNode>(base);
        if (nullptr == feature)
        {
            LOG(ERROR) << "GetFeatureIdByType fail, invalid pointer, feature_type=" << static_cast<int>(feature_type);
            return false;
        }
        feature_id = feature->GetSdNodeId();
        break;
    }

    case Type::INTERSECTION:
    {
        std::shared_ptr<holo::map::format::Intersection> feature =
            std::dynamic_pointer_cast<holo::map::format::Intersection>(base);
        if (nullptr == feature)
        {
            LOG(ERROR) << "GetFeatureIdByType fail, invalid pointer, feature_type=" << static_cast<int>(feature_type);
            return false;
        }
        feature_id = feature->GetIntersectionId();
        break;
    }

    case Type::ROUTING_PATH:
    {
        std::shared_ptr<holo::map::format::RoutingPath> feature =
            std::dynamic_pointer_cast<holo::map::format::RoutingPath>(base);
        if (nullptr == feature)
        {
            LOG(ERROR) << "GetFeatureIdByType fail, invalid pointer, feature_type=" << static_cast<int>(feature_type);
            return false;
        }
        feature_id = feature->GetRoutingPathId();
        break;
    }

    case Type::ROUTING_GRAPH:
    {
        std::shared_ptr<holo::map::format::RoutingGraph> feature =
            std::dynamic_pointer_cast<holo::map::format::RoutingGraph>(base);
        if (nullptr == feature)
        {
            LOG(ERROR) << "GetFeatureIdByType fail, invalid pointer, feature_type=" << static_cast<int>(feature_type);
            return false;
        }
        feature_id = feature->GetRoutingGraphId();
        break;
    }

    case Type::ROUTING_EDGE:
    {
        std::shared_ptr<holo::map::format::RoutingEdge> feature =
            std::dynamic_pointer_cast<holo::map::format::RoutingEdge>(base);
        if (nullptr == feature)
        {
            LOG(ERROR) << "GetFeatureIdByType fail, invalid pointer, feature_type=" << static_cast<int>(feature_type);
            return false;
        }
        feature_id = feature->GetRoutingEdgeId();
        break;
    }

    case Type::CONNECTION:
    {
        std::shared_ptr<holo::map::format::Connection> feature =
            std::dynamic_pointer_cast<holo::map::format::Connection>(base);
        if (nullptr == feature)
        {
            LOG(ERROR) << "GetFeatureIdByType fail, invalid pointer, feature_type=" << static_cast<int>(feature_type);
            return false;
        }
        feature_id = feature->GetConnectionId();
        break;
    }

    case Type::ROUTING_NODE:
    {
        std::shared_ptr<holo::map::format::RoutingNode> feature =
            std::dynamic_pointer_cast<holo::map::format::RoutingNode>(base);
        if (nullptr == feature)
        {
            LOG(ERROR) << "GetFeatureIdByType fail, invalid pointer, feature_type=" << static_cast<int>(feature_type);
            return false;
        }
        feature_id = feature->GetRoutingNodeId();
        break;
    }
    default:
    {
        break;
    }
    }

    holo::bool_t const ok = (0 == feature_id ? false : true);
    if (!ok)
    {
        LOG(ERROR) << "GetFeatureIdByType fail, feature_type=" << static_cast<int>(feature_type);
    }
    return ok;
}

/**
 * @brief Get feature by type and id from Retriever. 
 *
 * @tparam R pointer refer to RetBase(RetBase*, std::shared_ptr<RetBase>);
 *
 * @param[in] ret Pointer type refer to RetBase;
 * @param[in] feature_type Feature type refer to holo::map::format::Base::FeatureType;
 * @param[in] feature_id Feature id.
 * @param[in] f Unary function that accepts ret, feature_type, feature_id, and feature pointer.
 *              This can either be a function pointer or a move constructible function object.
                Its return true, if successful.
 * @return true: No error;
 *         false: An error occurs in this function or in f.
 */
template<typename R, typename Type, typename Id, typename F>
holo::bool_t EnumerateFeatureByType(R ret, Type const feature_type, Id const feature_id, F f)
{
    if (nullptr == ret)
    {
        LOG(ERROR) << "EnumerateFeatureByType fail, invalid parameters";
        return false;
    }

    holo::bool_t ok = false;
    holo::bool_t valid = false;

    switch (feature_type)
    {

    case Type::OBJECT_PARKING_SPACE:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectParkingSpace>::SPtrType ptr = nullptr;
        ok = ret->GetObjectParkingSpaceByIdV2(feature_id, ptr, valid);
        ok = ok && f(ret, feature_type, feature_id, ptr, valid);
        break;
    }

    case Type::OBJECT_PARKING_FLOOR:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectParkingFloor>::SPtrType ptr = nullptr;
        ok = ret->GetObjectParkingFloorByIdV2(feature_id, ptr, valid);
        ok = ok && f(ret, feature_type, feature_id, ptr, valid);
        break;
    }

    case Type::OBJECT_PARKING_LOT:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectParkingLot>::SPtrType ptr = nullptr;
        ok = ret->GetObjectParkingLotByIdV2(feature_id, ptr, valid);
        ok = ok && f(ret, feature_type, feature_id, ptr, valid);
        break;
    }

    case Type::OBJECT_PARKING_POI:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectParkingPoi>::SPtrType ptr = nullptr;
        ok = ret->GetObjectParkingPoiByIdV2(feature_id, ptr, valid);
        ok = ok && f(ret, feature_type, feature_id, ptr, valid);
        break;
    }

    case Type::OBJECT_PARKING_BACKGROUND:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectParkingBackground>::SPtrType ptr = nullptr;
        ok = ret->GetObjectParkingBackgroundByIdV2(feature_id, ptr, valid);
        ok = ok && f(ret, feature_type, feature_id, ptr, valid);
        break;
    }

    case Type::QUASI_DYNAMIC_LANE_GROUP:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::QuasiDynamicLaneGroup>::SPtrType ptr = nullptr;
        ok = ret->GetQuasiDynamicLaneGroupByIdV2(feature_id, ptr, valid);
        ok = ok && f(ret, feature_type, feature_id, ptr, valid);
        break;
    }

    case Type::QUASI_DYNAMIC_LANE:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::QuasiDynamicLane>::SPtrType ptr = nullptr;
        ok = ret->GetQuasiDynamicLaneByIdV2(feature_id, ptr, valid);
        ok = ok && f(ret, feature_type, feature_id, ptr, valid);
        break;
    }

    case Type::QUASI_DYNAMIC_REGION:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::QuasiDynamicRegion>::SPtrType ptr = nullptr;
        ok = ret->GetQuasiDynamicRegionByIdV2(feature_id, ptr, valid);
        ok = ok && f(ret, feature_type, feature_id, ptr, valid);
        break;
    }

    case Type::TILE:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::Tile>::SPtrType ptr = nullptr;
        ok = ret->GetTileByIdV2(feature_id, ptr, valid);
        ok = ok && f(ret, feature_type, feature_id, ptr, valid);
        break;
    }

    case Type::SD_ROAD:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::SdRoad>::SPtrType ptr = nullptr;
        ok = ret->GetSdRoadByIdV2(feature_id, ptr, valid);
        ok = ok && f(ret, feature_type, feature_id, ptr, valid);
        break;
    }

    case Type::OBJECT_TRAFFIC_SIGN:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectTrafficSign>::SPtrType ptr = nullptr;
        ok = ret->GetObjectTrafficSignByIdV2(feature_id, ptr, valid);
        ok = ok && f(ret, feature_type, feature_id, ptr, valid);
        break;
    }

    case Type::OBJECT_REGIONAL_INFO:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectRegionalInfo>::SPtrType ptr = nullptr;
        ok = ret->GetObjectRegionalInfoByIdV2(feature_id, ptr, valid);
        ok = ok && f(ret, feature_type, feature_id, ptr, valid);
        break;
    }

    case Type::OBJECT_SAFE_ISLAND:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectSafeIsland>::SPtrType ptr = nullptr;
        ok = ret->GetObjectSafeIslandByIdV2(feature_id, ptr, valid);
        ok = ok && f(ret, feature_type, feature_id, ptr, valid);
        break;
    }

    case Type::OBJECT_INFO:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectInfo>::SPtrType ptr = nullptr;
        ok = ret->GetObjectInfoByIdV2(feature_id, ptr, valid);
        ok = ok && f(ret, feature_type, feature_id, ptr, valid);
        break;
    }

    case Type::OBJECT_LINEAR_INFO:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectLinearInfo>::SPtrType ptr = nullptr;
        ok = ret->GetObjectLinearInfoByIdV2(feature_id, ptr, valid);
        ok = ok && f(ret, feature_type, feature_id, ptr, valid);
        break;
    }

    case Type::OBJECT_TRAFFIC_LIGHT_GROUP:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectTrafficLightGroup>::SPtrType ptr = nullptr;
        ok = ret->GetObjectTrafficLightGroupByIdV2(feature_id, ptr, valid);
        ok = ok && f(ret, feature_type, feature_id, ptr, valid);
        break;
    }

    case Type::OBJECT_STOP_LINE:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectStopLine>::SPtrType ptr = nullptr;
        ok = ret->GetObjectStopLineByIdV2(feature_id, ptr, valid);
        ok = ok && f(ret, feature_type, feature_id, ptr, valid);
        break;
    }

    case Type::JUNCTION:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::Junction>::SPtrType ptr = nullptr;
        ok = ret->GetJunctionByIdV2(feature_id, ptr, valid);
        ok = ok && f(ret, feature_type, feature_id, ptr, valid);
        break;
    }

    case Type::GEOFENCE:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::Geofence>::SPtrType ptr = nullptr;
        ok = ret->GetGeofenceByIdV2(feature_id, ptr, valid);
        ok = ok && f(ret, feature_type, feature_id, ptr, valid);
        break;
    }

    case Type::ROAD:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::Road>::SPtrType ptr = nullptr;
        ok = ret->GetRoadByIdV2(feature_id, ptr, valid);
        ok = ok && f(ret, feature_type, feature_id, ptr, valid);
        break;
    }

    case Type::LANE_GROUP:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::LaneGroup>::SPtrType ptr = nullptr;
        ok = ret->GetLaneGroupByIdV2(feature_id, ptr, valid);
        ok = ok && f(ret, feature_type, feature_id, ptr, valid);
        break;
    }

    case Type::LANE_BOUNDARY:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::LaneBoundary>::SPtrType ptr = nullptr;
        ok = ret->GetLaneBoundaryByIdV2(feature_id, ptr, valid);
        ok = ok && f(ret, feature_type, feature_id, ptr, valid);
        break;
    }

    case Type::LANE:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::Lane>::SPtrType ptr = nullptr;
        ok = ret->GetLaneByIdV2(feature_id, ptr, valid);
        ok = ok && f(ret, feature_type, feature_id, ptr, valid);
        break;
    }

    case Type::OBJECT_TRAFFIC_LIGHT:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectTrafficLight>::SPtrType ptr = nullptr;
        ok = ret->GetObjectTrafficLightByIdV2(feature_id, ptr, valid);
        ok = ok && f(ret, feature_type, feature_id, ptr, valid);
        break;
    }

    case Type::OBJECT_PEDESTRIAN_CROSSING:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectPedestrianCrossing>::SPtrType ptr = nullptr;
        ok = ret->GetObjectPedestrianCrossingByIdV2(feature_id, ptr, valid);
        ok = ok && f(ret, feature_type, feature_id, ptr, valid);
        break;
    }

    case Type::SD_NODE:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::SdNode>::SPtrType ptr = nullptr;
        ok = ret->GetSdNodeByIdV2(feature_id, ptr, valid);
        ok = ok && f(ret, feature_type, feature_id, ptr, valid);
        break;
    }

    case Type::INTERSECTION:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::Intersection>::SPtrType ptr = nullptr;
        ok = ret->GetIntersectionByIdV2(feature_id, ptr, valid);
        ok = ok && f(ret, feature_type, feature_id, ptr, valid);
        break;
    }

    case Type::ROUTING_PATH:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::RoutingPath>::SPtrType ptr = nullptr;
        ok = ret->GetRoutingPathByIdV2(feature_id, ptr, valid);
        ok = ok && f(ret, feature_type, feature_id, ptr, valid);
        break;
    }

    case Type::ROUTING_GRAPH:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::RoutingGraph>::SPtrType ptr = nullptr;
        ok = ret->GetRoutingGraphByIdV2(feature_id, ptr, valid);
        ok = ok && f(ret, feature_type, feature_id, ptr, valid);
        break;
    }

    case Type::ROUTING_EDGE:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::RoutingEdge>::SPtrType ptr = nullptr;
        ok = ret->GetRoutingEdgeByIdV2(feature_id, ptr, valid);
        ok = ok && f(ret, feature_type, feature_id, ptr, valid);
        break;
    }

    case Type::CONNECTION:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::Connection>::SPtrType ptr = nullptr;
        ok = ret->GetConnectionByIdV2(feature_id, ptr, valid);
        ok = ok && f(ret, feature_type, feature_id, ptr, valid);
        break;
    }

    case Type::ROUTING_NODE:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::RoutingNode>::SPtrType ptr = nullptr;
        ok = ret->GetRoutingNodeByIdV2(feature_id, ptr, valid);
        ok = ok && f(ret, feature_type, feature_id, ptr, valid);
        break;
    }
    default:
    {
        break;
    }
    }

    if (!ok)
    {
        LOG(ERROR) << "EnumerateFeatureByType fail, type=" << static_cast<int>(feature_type)
                   << " id=" << feature_id;
    }

    return ok;
}

/**
 * @brief Get feature by type and id from Retriever, and convert it to shared pointer of
 *        holo::map::format::Base
 *
 * @tparam R pointer refer to RetBase(RetBase*, std::shared_ptr<RetBase>);
 *
 * @param[in] ret Pointer type refer to RetBase;
 * @param[in] feature_type Feature type refer to holo::map::format::Base::FeatureType;
 * @param[in] feature_id Feature id.
 * @param[in] f Unary function that accepts ret, feature_type, feature_id, valid and
 *              feature pointer of holo::map::format::Base.
 *              This can either be a function pointer or a move constructible function object.
                Its return true, if successful.
 * @return true: No error;
 *         false: An error occurs in this function or in f.
 */
template<typename R, typename Type, typename Id, typename F>
holo::bool_t EnumerateFeatureByTypeWithBase(R ret, Type const feature_type, Id const feature_id, F f)
{
    if (nullptr == ret)
    {
        LOG(ERROR) << "EnumerateFeatureByTypeWithBase fail, invalid parameters";
        return false;
    }

    holo::bool_t ok = false;
    holo::bool_t valid = false;

    switch (feature_type)
    {

    case Type::OBJECT_PARKING_SPACE:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectParkingSpace>::SPtrType ptr = nullptr;
        ok = ret->GetObjectParkingSpaceByIdV2(feature_id, ptr, valid);
        if (ok)
        {
            holo::map::format::helper::FeatureTraits<holo::map::format::Base>::SPtrType
                base = (valid && nullptr != ptr) ? ptr : nullptr;
            ok = f(ret, feature_type, feature_id, valid, base);
        }
        break;
    }

    case Type::OBJECT_PARKING_FLOOR:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectParkingFloor>::SPtrType ptr = nullptr;
        ok = ret->GetObjectParkingFloorByIdV2(feature_id, ptr, valid);
        if (ok)
        {
            holo::map::format::helper::FeatureTraits<holo::map::format::Base>::SPtrType
                base = (valid && nullptr != ptr) ? ptr : nullptr;
            ok = f(ret, feature_type, feature_id, valid, base);
        }
        break;
    }

    case Type::OBJECT_PARKING_LOT:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectParkingLot>::SPtrType ptr = nullptr;
        ok = ret->GetObjectParkingLotByIdV2(feature_id, ptr, valid);
        if (ok)
        {
            holo::map::format::helper::FeatureTraits<holo::map::format::Base>::SPtrType
                base = (valid && nullptr != ptr) ? ptr : nullptr;
            ok = f(ret, feature_type, feature_id, valid, base);
        }
        break;
    }

    case Type::OBJECT_PARKING_POI:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectParkingPoi>::SPtrType ptr = nullptr;
        ok = ret->GetObjectParkingPoiByIdV2(feature_id, ptr, valid);
        if (ok)
        {
            holo::map::format::helper::FeatureTraits<holo::map::format::Base>::SPtrType
                base = (valid && nullptr != ptr) ? ptr : nullptr;
            ok = f(ret, feature_type, feature_id, valid, base);
        }
        break;
    }

    case Type::OBJECT_PARKING_BACKGROUND:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectParkingBackground>::SPtrType ptr = nullptr;
        ok = ret->GetObjectParkingBackgroundByIdV2(feature_id, ptr, valid);
        if (ok)
        {
            holo::map::format::helper::FeatureTraits<holo::map::format::Base>::SPtrType
                base = (valid && nullptr != ptr) ? ptr : nullptr;
            ok = f(ret, feature_type, feature_id, valid, base);
        }
        break;
    }

    case Type::QUASI_DYNAMIC_LANE_GROUP:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::QuasiDynamicLaneGroup>::SPtrType ptr = nullptr;
        ok = ret->GetQuasiDynamicLaneGroupByIdV2(feature_id, ptr, valid);
        if (ok)
        {
            holo::map::format::helper::FeatureTraits<holo::map::format::Base>::SPtrType
                base = (valid && nullptr != ptr) ? ptr : nullptr;
            ok = f(ret, feature_type, feature_id, valid, base);
        }
        break;
    }

    case Type::QUASI_DYNAMIC_LANE:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::QuasiDynamicLane>::SPtrType ptr = nullptr;
        ok = ret->GetQuasiDynamicLaneByIdV2(feature_id, ptr, valid);
        if (ok)
        {
            holo::map::format::helper::FeatureTraits<holo::map::format::Base>::SPtrType
                base = (valid && nullptr != ptr) ? ptr : nullptr;
            ok = f(ret, feature_type, feature_id, valid, base);
        }
        break;
    }

    case Type::QUASI_DYNAMIC_REGION:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::QuasiDynamicRegion>::SPtrType ptr = nullptr;
        ok = ret->GetQuasiDynamicRegionByIdV2(feature_id, ptr, valid);
        if (ok)
        {
            holo::map::format::helper::FeatureTraits<holo::map::format::Base>::SPtrType
                base = (valid && nullptr != ptr) ? ptr : nullptr;
            ok = f(ret, feature_type, feature_id, valid, base);
        }
        break;
    }

    case Type::TILE:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::Tile>::SPtrType ptr = nullptr;
        ok = ret->GetTileByIdV2(feature_id, ptr, valid);
        if (ok)
        {
            holo::map::format::helper::FeatureTraits<holo::map::format::Base>::SPtrType
                base = (valid && nullptr != ptr) ? ptr : nullptr;
            ok = f(ret, feature_type, feature_id, valid, base);
        }
        break;
    }

    case Type::SD_ROAD:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::SdRoad>::SPtrType ptr = nullptr;
        ok = ret->GetSdRoadByIdV2(feature_id, ptr, valid);
        if (ok)
        {
            holo::map::format::helper::FeatureTraits<holo::map::format::Base>::SPtrType
                base = (valid && nullptr != ptr) ? ptr : nullptr;
            ok = f(ret, feature_type, feature_id, valid, base);
        }
        break;
    }

    case Type::OBJECT_TRAFFIC_SIGN:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectTrafficSign>::SPtrType ptr = nullptr;
        ok = ret->GetObjectTrafficSignByIdV2(feature_id, ptr, valid);
        if (ok)
        {
            holo::map::format::helper::FeatureTraits<holo::map::format::Base>::SPtrType
                base = (valid && nullptr != ptr) ? ptr : nullptr;
            ok = f(ret, feature_type, feature_id, valid, base);
        }
        break;
    }

    case Type::OBJECT_REGIONAL_INFO:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectRegionalInfo>::SPtrType ptr = nullptr;
        ok = ret->GetObjectRegionalInfoByIdV2(feature_id, ptr, valid);
        if (ok)
        {
            holo::map::format::helper::FeatureTraits<holo::map::format::Base>::SPtrType
                base = (valid && nullptr != ptr) ? ptr : nullptr;
            ok = f(ret, feature_type, feature_id, valid, base);
        }
        break;
    }

    case Type::OBJECT_SAFE_ISLAND:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectSafeIsland>::SPtrType ptr = nullptr;
        ok = ret->GetObjectSafeIslandByIdV2(feature_id, ptr, valid);
        if (ok)
        {
            holo::map::format::helper::FeatureTraits<holo::map::format::Base>::SPtrType
                base = (valid && nullptr != ptr) ? ptr : nullptr;
            ok = f(ret, feature_type, feature_id, valid, base);
        }
        break;
    }

    case Type::OBJECT_INFO:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectInfo>::SPtrType ptr = nullptr;
        ok = ret->GetObjectInfoByIdV2(feature_id, ptr, valid);
        if (ok)
        {
            holo::map::format::helper::FeatureTraits<holo::map::format::Base>::SPtrType
                base = (valid && nullptr != ptr) ? ptr : nullptr;
            ok = f(ret, feature_type, feature_id, valid, base);
        }
        break;
    }

    case Type::OBJECT_LINEAR_INFO:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectLinearInfo>::SPtrType ptr = nullptr;
        ok = ret->GetObjectLinearInfoByIdV2(feature_id, ptr, valid);
        if (ok)
        {
            holo::map::format::helper::FeatureTraits<holo::map::format::Base>::SPtrType
                base = (valid && nullptr != ptr) ? ptr : nullptr;
            ok = f(ret, feature_type, feature_id, valid, base);
        }
        break;
    }

    case Type::OBJECT_TRAFFIC_LIGHT_GROUP:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectTrafficLightGroup>::SPtrType ptr = nullptr;
        ok = ret->GetObjectTrafficLightGroupByIdV2(feature_id, ptr, valid);
        if (ok)
        {
            holo::map::format::helper::FeatureTraits<holo::map::format::Base>::SPtrType
                base = (valid && nullptr != ptr) ? ptr : nullptr;
            ok = f(ret, feature_type, feature_id, valid, base);
        }
        break;
    }

    case Type::OBJECT_STOP_LINE:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectStopLine>::SPtrType ptr = nullptr;
        ok = ret->GetObjectStopLineByIdV2(feature_id, ptr, valid);
        if (ok)
        {
            holo::map::format::helper::FeatureTraits<holo::map::format::Base>::SPtrType
                base = (valid && nullptr != ptr) ? ptr : nullptr;
            ok = f(ret, feature_type, feature_id, valid, base);
        }
        break;
    }

    case Type::JUNCTION:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::Junction>::SPtrType ptr = nullptr;
        ok = ret->GetJunctionByIdV2(feature_id, ptr, valid);
        if (ok)
        {
            holo::map::format::helper::FeatureTraits<holo::map::format::Base>::SPtrType
                base = (valid && nullptr != ptr) ? ptr : nullptr;
            ok = f(ret, feature_type, feature_id, valid, base);
        }
        break;
    }

    case Type::GEOFENCE:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::Geofence>::SPtrType ptr = nullptr;
        ok = ret->GetGeofenceByIdV2(feature_id, ptr, valid);
        if (ok)
        {
            holo::map::format::helper::FeatureTraits<holo::map::format::Base>::SPtrType
                base = (valid && nullptr != ptr) ? ptr : nullptr;
            ok = f(ret, feature_type, feature_id, valid, base);
        }
        break;
    }

    case Type::ROAD:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::Road>::SPtrType ptr = nullptr;
        ok = ret->GetRoadByIdV2(feature_id, ptr, valid);
        if (ok)
        {
            holo::map::format::helper::FeatureTraits<holo::map::format::Base>::SPtrType
                base = (valid && nullptr != ptr) ? ptr : nullptr;
            ok = f(ret, feature_type, feature_id, valid, base);
        }
        break;
    }

    case Type::LANE_GROUP:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::LaneGroup>::SPtrType ptr = nullptr;
        ok = ret->GetLaneGroupByIdV2(feature_id, ptr, valid);
        if (ok)
        {
            holo::map::format::helper::FeatureTraits<holo::map::format::Base>::SPtrType
                base = (valid && nullptr != ptr) ? ptr : nullptr;
            ok = f(ret, feature_type, feature_id, valid, base);
        }
        break;
    }

    case Type::LANE_BOUNDARY:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::LaneBoundary>::SPtrType ptr = nullptr;
        ok = ret->GetLaneBoundaryByIdV2(feature_id, ptr, valid);
        if (ok)
        {
            holo::map::format::helper::FeatureTraits<holo::map::format::Base>::SPtrType
                base = (valid && nullptr != ptr) ? ptr : nullptr;
            ok = f(ret, feature_type, feature_id, valid, base);
        }
        break;
    }

    case Type::LANE:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::Lane>::SPtrType ptr = nullptr;
        ok = ret->GetLaneByIdV2(feature_id, ptr, valid);
        if (ok)
        {
            holo::map::format::helper::FeatureTraits<holo::map::format::Base>::SPtrType
                base = (valid && nullptr != ptr) ? ptr : nullptr;
            ok = f(ret, feature_type, feature_id, valid, base);
        }
        break;
    }

    case Type::OBJECT_TRAFFIC_LIGHT:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectTrafficLight>::SPtrType ptr = nullptr;
        ok = ret->GetObjectTrafficLightByIdV2(feature_id, ptr, valid);
        if (ok)
        {
            holo::map::format::helper::FeatureTraits<holo::map::format::Base>::SPtrType
                base = (valid && nullptr != ptr) ? ptr : nullptr;
            ok = f(ret, feature_type, feature_id, valid, base);
        }
        break;
    }

    case Type::OBJECT_PEDESTRIAN_CROSSING:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectPedestrianCrossing>::SPtrType ptr = nullptr;
        ok = ret->GetObjectPedestrianCrossingByIdV2(feature_id, ptr, valid);
        if (ok)
        {
            holo::map::format::helper::FeatureTraits<holo::map::format::Base>::SPtrType
                base = (valid && nullptr != ptr) ? ptr : nullptr;
            ok = f(ret, feature_type, feature_id, valid, base);
        }
        break;
    }

    case Type::SD_NODE:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::SdNode>::SPtrType ptr = nullptr;
        ok = ret->GetSdNodeByIdV2(feature_id, ptr, valid);
        if (ok)
        {
            holo::map::format::helper::FeatureTraits<holo::map::format::Base>::SPtrType
                base = (valid && nullptr != ptr) ? ptr : nullptr;
            ok = f(ret, feature_type, feature_id, valid, base);
        }
        break;
    }

    case Type::INTERSECTION:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::Intersection>::SPtrType ptr = nullptr;
        ok = ret->GetIntersectionByIdV2(feature_id, ptr, valid);
        if (ok)
        {
            holo::map::format::helper::FeatureTraits<holo::map::format::Base>::SPtrType
                base = (valid && nullptr != ptr) ? ptr : nullptr;
            ok = f(ret, feature_type, feature_id, valid, base);
        }
        break;
    }

    case Type::ROUTING_PATH:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::RoutingPath>::SPtrType ptr = nullptr;
        ok = ret->GetRoutingPathByIdV2(feature_id, ptr, valid);
        if (ok)
        {
            holo::map::format::helper::FeatureTraits<holo::map::format::Base>::SPtrType
                base = (valid && nullptr != ptr) ? ptr : nullptr;
            ok = f(ret, feature_type, feature_id, valid, base);
        }
        break;
    }

    case Type::ROUTING_GRAPH:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::RoutingGraph>::SPtrType ptr = nullptr;
        ok = ret->GetRoutingGraphByIdV2(feature_id, ptr, valid);
        if (ok)
        {
            holo::map::format::helper::FeatureTraits<holo::map::format::Base>::SPtrType
                base = (valid && nullptr != ptr) ? ptr : nullptr;
            ok = f(ret, feature_type, feature_id, valid, base);
        }
        break;
    }

    case Type::ROUTING_EDGE:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::RoutingEdge>::SPtrType ptr = nullptr;
        ok = ret->GetRoutingEdgeByIdV2(feature_id, ptr, valid);
        if (ok)
        {
            holo::map::format::helper::FeatureTraits<holo::map::format::Base>::SPtrType
                base = (valid && nullptr != ptr) ? ptr : nullptr;
            ok = f(ret, feature_type, feature_id, valid, base);
        }
        break;
    }

    case Type::CONNECTION:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::Connection>::SPtrType ptr = nullptr;
        ok = ret->GetConnectionByIdV2(feature_id, ptr, valid);
        if (ok)
        {
            holo::map::format::helper::FeatureTraits<holo::map::format::Base>::SPtrType
                base = (valid && nullptr != ptr) ? ptr : nullptr;
            ok = f(ret, feature_type, feature_id, valid, base);
        }
        break;
    }

    case Type::ROUTING_NODE:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::RoutingNode>::SPtrType ptr = nullptr;
        ok = ret->GetRoutingNodeByIdV2(feature_id, ptr, valid);
        if (ok)
        {
            holo::map::format::helper::FeatureTraits<holo::map::format::Base>::SPtrType
                base = (valid && nullptr != ptr) ? ptr : nullptr;
            ok = f(ret, feature_type, feature_id, valid, base);
        }
        break;
    }
    default:
    {
        break;
    }
    }

    if (!ok)
    {
        LOG(ERROR) << "EnumerateFeatureByTypeWithBase fail, type=" << static_cast<int>(feature_type)
                   << " id=" << feature_id << " valid=" << valid;
    }

    return ok;
}

/**
 * @brief Get feature by type and id from Retriever, and fetch the tile ids from target feature.
 *
 * @tparam R pointer refer to RetBase(RetBase*, std::shared_ptr<RetBase>);
 *
 * @param[in] ret Pointer type refer to RetBase;
 * @param[in] feature_type Feature type refer to holo::map::format::Base::FeatureType;
 * @param[in] feature_id Feature id.
 * @param[in] f Unary function that accepts ret, feature_type, feature_id, and tile ids of target
 *              feature.
 *              This can either be a function pointer or a move constructible function object.
                Its return true, if successful.
 * @return true: No error;
 *         false: An error occurs in this function or in f.
 */
template<typename R, typename Type, typename Id, typename F>
holo::bool_t EnumerateFeatureByTypeWithTileIds(R ret, Type const feature_type, Id const feature_id, F f)
{
    if (nullptr == ret)
    {
        LOG(ERROR) << "EnumerateFeatureByTypeWithTileIds fail, invalid parameters";
        return false;
    }

    if (Type::TILE == feature_type)
    {
        return true;
    }

    holo::bool_t ok = false;
    holo::bool_t valid = false;
    holo::bool_t empty = false;

    switch (feature_type)
    {

    case Type::SD_NODE:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::SdNode>::SPtrType ptr = nullptr;
        ok = ret->GetSdNodeByIdV2(feature_id, ptr, valid);
        if (ok && valid && nullptr != ptr)
        {
            holo::map::format::helper::FeatureIdVectorType const& ids = *ptr->GetPtrTileIds();
            ok = f(ret, feature_type, feature_id, ids);
        }
        empty = (nullptr == ptr);
        break;
    }

    case Type::SD_ROAD:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::SdRoad>::SPtrType ptr = nullptr;
        ok = ret->GetSdRoadByIdV2(feature_id, ptr, valid);
        if (ok && valid && nullptr != ptr)
        {
            holo::map::format::helper::FeatureIdVectorType const& ids = *ptr->GetPtrTileIds();
            ok = f(ret, feature_type, feature_id, ids);
        }
        empty = (nullptr == ptr);
        break;
    }

    case Type::ROAD:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::Road>::SPtrType ptr = nullptr;
        ok = ret->GetRoadByIdV2(feature_id, ptr, valid);
        if (ok && valid && nullptr != ptr)
        {
            holo::map::format::helper::FeatureIdVectorType const& ids = *ptr->GetPtrTileIds();
            ok = f(ret, feature_type, feature_id, ids);
        }
        empty = (nullptr == ptr);
        break;
    }

    case Type::LANE:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::Lane>::SPtrType ptr = nullptr;
        ok = ret->GetLaneByIdV2(feature_id, ptr, valid);
        if (ok && valid && nullptr != ptr)
        {
            holo::map::format::helper::FeatureIdVectorType const& ids = *ptr->GetPtrTileIds();
            ok = f(ret, feature_type, feature_id, ids);
        }
        empty = (nullptr == ptr);
        break;
    }

    case Type::LANE_GROUP:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::LaneGroup>::SPtrType ptr = nullptr;
        ok = ret->GetLaneGroupByIdV2(feature_id, ptr, valid);
        if (ok && valid && nullptr != ptr)
        {
            holo::map::format::helper::FeatureIdVectorType const& ids = *ptr->GetPtrTileIds();
            ok = f(ret, feature_type, feature_id, ids);
        }
        empty = (nullptr == ptr);
        break;
    }

    case Type::LANE_BOUNDARY:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::LaneBoundary>::SPtrType ptr = nullptr;
        ok = ret->GetLaneBoundaryByIdV2(feature_id, ptr, valid);
        if (ok && valid && nullptr != ptr)
        {
            holo::map::format::helper::FeatureIdVectorType const& ids = *ptr->GetPtrTileIds();
            ok = f(ret, feature_type, feature_id, ids);
        }
        empty = (nullptr == ptr);
        break;
    }

    case Type::OBJECT_INFO:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectInfo>::SPtrType ptr = nullptr;
        ok = ret->GetObjectInfoByIdV2(feature_id, ptr, valid);
        if (ok && valid && nullptr != ptr)
        {
            holo::map::format::helper::FeatureIdVectorType const& ids = *ptr->GetPtrTileIds();
            ok = f(ret, feature_type, feature_id, ids);
        }
        empty = (nullptr == ptr);
        break;
    }

    case Type::OBJECT_LINEAR_INFO:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectLinearInfo>::SPtrType ptr = nullptr;
        ok = ret->GetObjectLinearInfoByIdV2(feature_id, ptr, valid);
        if (ok && valid && nullptr != ptr)
        {
            holo::map::format::helper::FeatureIdVectorType const& ids = *ptr->GetPtrTileIds();
            ok = f(ret, feature_type, feature_id, ids);
        }
        empty = (nullptr == ptr);
        break;
    }

    case Type::OBJECT_REGIONAL_INFO:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectRegionalInfo>::SPtrType ptr = nullptr;
        ok = ret->GetObjectRegionalInfoByIdV2(feature_id, ptr, valid);
        if (ok && valid && nullptr != ptr)
        {
            holo::map::format::helper::FeatureIdVectorType const& ids = *ptr->GetPtrTileIds();
            ok = f(ret, feature_type, feature_id, ids);
        }
        empty = (nullptr == ptr);
        break;
    }

    case Type::OBJECT_PEDESTRIAN_CROSSING:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectPedestrianCrossing>::SPtrType ptr = nullptr;
        ok = ret->GetObjectPedestrianCrossingByIdV2(feature_id, ptr, valid);
        if (ok && valid && nullptr != ptr)
        {
            holo::map::format::helper::FeatureIdVectorType const& ids = *ptr->GetPtrTileIds();
            ok = f(ret, feature_type, feature_id, ids);
        }
        empty = (nullptr == ptr);
        break;
    }

    case Type::OBJECT_STOP_LINE:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectStopLine>::SPtrType ptr = nullptr;
        ok = ret->GetObjectStopLineByIdV2(feature_id, ptr, valid);
        if (ok && valid && nullptr != ptr)
        {
            holo::map::format::helper::FeatureIdVectorType const& ids = *ptr->GetPtrTileIds();
            ok = f(ret, feature_type, feature_id, ids);
        }
        empty = (nullptr == ptr);
        break;
    }

    case Type::OBJECT_TRAFFIC_LIGHT:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectTrafficLight>::SPtrType ptr = nullptr;
        ok = ret->GetObjectTrafficLightByIdV2(feature_id, ptr, valid);
        if (ok && valid && nullptr != ptr)
        {
            holo::map::format::helper::FeatureIdVectorType const& ids = *ptr->GetPtrTileIds();
            ok = f(ret, feature_type, feature_id, ids);
        }
        empty = (nullptr == ptr);
        break;
    }

    case Type::OBJECT_TRAFFIC_LIGHT_GROUP:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectTrafficLightGroup>::SPtrType ptr = nullptr;
        ok = ret->GetObjectTrafficLightGroupByIdV2(feature_id, ptr, valid);
        if (ok && valid && nullptr != ptr)
        {
            holo::map::format::helper::FeatureIdVectorType const& ids = *ptr->GetPtrTileIds();
            ok = f(ret, feature_type, feature_id, ids);
        }
        empty = (nullptr == ptr);
        break;
    }

    case Type::OBJECT_TRAFFIC_SIGN:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectTrafficSign>::SPtrType ptr = nullptr;
        ok = ret->GetObjectTrafficSignByIdV2(feature_id, ptr, valid);
        if (ok && valid && nullptr != ptr)
        {
            holo::map::format::helper::FeatureIdVectorType const& ids = *ptr->GetPtrTileIds();
            ok = f(ret, feature_type, feature_id, ids);
        }
        empty = (nullptr == ptr);
        break;
    }

    case Type::OBJECT_PARKING_LOT:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectParkingLot>::SPtrType ptr = nullptr;
        ok = ret->GetObjectParkingLotByIdV2(feature_id, ptr, valid);
        if (ok && valid && nullptr != ptr)
        {
            holo::map::format::helper::FeatureIdVectorType const& ids = *ptr->GetPtrTileIds();
            ok = f(ret, feature_type, feature_id, ids);
        }
        empty = (nullptr == ptr);
        break;
    }

    case Type::OBJECT_PARKING_FLOOR:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectParkingFloor>::SPtrType ptr = nullptr;
        ok = ret->GetObjectParkingFloorByIdV2(feature_id, ptr, valid);
        if (ok && valid && nullptr != ptr)
        {
            holo::map::format::helper::FeatureIdVectorType const& ids = *ptr->GetPtrTileIds();
            ok = f(ret, feature_type, feature_id, ids);
        }
        empty = (nullptr == ptr);
        break;
    }

    case Type::OBJECT_PARKING_BACKGROUND:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectParkingBackground>::SPtrType ptr = nullptr;
        ok = ret->GetObjectParkingBackgroundByIdV2(feature_id, ptr, valid);
        if (ok && valid && nullptr != ptr)
        {
            holo::map::format::helper::FeatureIdVectorType const& ids = *ptr->GetPtrTileIds();
            ok = f(ret, feature_type, feature_id, ids);
        }
        empty = (nullptr == ptr);
        break;
    }

    case Type::OBJECT_PARKING_POI:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectParkingPoi>::SPtrType ptr = nullptr;
        ok = ret->GetObjectParkingPoiByIdV2(feature_id, ptr, valid);
        if (ok && valid && nullptr != ptr)
        {
            holo::map::format::helper::FeatureIdVectorType const& ids = *ptr->GetPtrTileIds();
            ok = f(ret, feature_type, feature_id, ids);
        }
        empty = (nullptr == ptr);
        break;
    }

    case Type::OBJECT_PARKING_SPACE:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectParkingSpace>::SPtrType ptr = nullptr;
        ok = ret->GetObjectParkingSpaceByIdV2(feature_id, ptr, valid);
        if (ok && valid && nullptr != ptr)
        {
            holo::map::format::helper::FeatureIdVectorType const& ids = *ptr->GetPtrTileIds();
            ok = f(ret, feature_type, feature_id, ids);
        }
        empty = (nullptr == ptr);
        break;
    }

    case Type::QUASI_DYNAMIC_LANE:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::QuasiDynamicLane>::SPtrType ptr = nullptr;
        ok = ret->GetQuasiDynamicLaneByIdV2(feature_id, ptr, valid);
        if (ok && valid && nullptr != ptr)
        {
            holo::map::format::helper::FeatureIdVectorType const& ids = *ptr->GetPtrTileIds();
            ok = f(ret, feature_type, feature_id, ids);
        }
        empty = (nullptr == ptr);
        break;
    }

    case Type::QUASI_DYNAMIC_LANE_GROUP:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::QuasiDynamicLaneGroup>::SPtrType ptr = nullptr;
        ok = ret->GetQuasiDynamicLaneGroupByIdV2(feature_id, ptr, valid);
        if (ok && valid && nullptr != ptr)
        {
            holo::map::format::helper::FeatureIdVectorType const& ids = *ptr->GetPtrTileIds();
            ok = f(ret, feature_type, feature_id, ids);
        }
        empty = (nullptr == ptr);
        break;
    }

    case Type::QUASI_DYNAMIC_REGION:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::QuasiDynamicRegion>::SPtrType ptr = nullptr;
        ok = ret->GetQuasiDynamicRegionByIdV2(feature_id, ptr, valid);
        if (ok && valid && nullptr != ptr)
        {
            holo::map::format::helper::FeatureIdVectorType const& ids = *ptr->GetPtrTileIds();
            ok = f(ret, feature_type, feature_id, ids);
        }
        empty = (nullptr == ptr);
        break;
    }

    case Type::ROUTING_PATH:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::RoutingPath>::SPtrType ptr = nullptr;
        ok = ret->GetRoutingPathByIdV2(feature_id, ptr, valid);
        if (ok && valid && nullptr != ptr)
        {
            holo::map::format::helper::FeatureIdVectorType const& ids = *ptr->GetPtrTileIds();
            ok = f(ret, feature_type, feature_id, ids);
        }
        empty = (nullptr == ptr);
        break;
    }
    default:
    {
        break;
    }
    }

    if (!ok || (valid && empty))
    {
        LOG(ERROR) << "EnumerateFeatureV2 fail, type=" << static_cast<int>(feature_type)
                   << " id=" << feature_id << " valid=" << valid << " empty=" << empty;
    }

    return ok;
}

/**
 * @brief Get feature ids from tile by feature type.
 *
 * @tparam R pointer refer to RetBase(RetBase*, std::shared_ptr<RetBase>);
 *
 * @param[in] ret Pointer type refer to RetBase;
 * @param[in] tile_id Tile id.
 * @param[in] feature_type Feature type refer to holo::map::format::Base::FeatureType;
 * @param[in] f Unary function that accepts ret, tile_id, feature_type, and feature ids.
 *              This can either be a function pointer or a move constructible function object.
                Its return true, if successful.
 * @return true: No error;
 *         false: An error occurs in this function or in f.
 */
template<typename R, typename Id, typename Type, typename F>
holo::bool_t EnumerateTileByType(R ret, Id const tile_id, Type const feature_type, F f)
{
    if (nullptr == ret)
    {
        LOG(ERROR) << "EnumerateTileByType fail, invalid parameters";
        return false;
    }

    holo::bool_t valid = false;
    holo::map::format::PtrTile tile = nullptr;
    
    holo::bool_t ok = ret->GetTileByIdV2(tile_id, tile, valid);
    if (!ok || (valid && nullptr == tile))
    {
        LOG(ERROR) << "EnumerateTileByType fail, GetTileByIdV2 fail, ok=" << ok << " valid=" << valid;
        return false;
    }
    
    if (!valid)
    {
        return true;
    }

    ok = false;

    switch (feature_type)
    {
    case Type::TILE:
    {
        holo::map::format::helper::FeatureIdVectorType ids;
        ok = f(ret, tile_id, feature_type, ids);
        break;
    }

    case Type::OBJECT_PARKING_SPACE:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrObjectParkingSpaceIds();;
        ok = f(ret, tile_id, feature_type, ids);
        break;
    }

    case Type::OBJECT_PARKING_FLOOR:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrObjectParkingFloorIds();;
        ok = f(ret, tile_id, feature_type, ids);
        break;
    }

    case Type::OBJECT_PARKING_LOT:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrObjectParkingLotIds();;
        ok = f(ret, tile_id, feature_type, ids);
        break;
    }

    case Type::OBJECT_PARKING_POI:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrObjectParkingPoiIds();;
        ok = f(ret, tile_id, feature_type, ids);
        break;
    }

    case Type::OBJECT_PARKING_BACKGROUND:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrObjectParkingBackgroundIds();;
        ok = f(ret, tile_id, feature_type, ids);
        break;
    }

    case Type::QUASI_DYNAMIC_LANE_GROUP:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrQuasiDynamicLaneGroupIds();;
        ok = f(ret, tile_id, feature_type, ids);
        break;
    }

    case Type::QUASI_DYNAMIC_LANE:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrQuasiDynamicLaneIds();;
        ok = f(ret, tile_id, feature_type, ids);
        break;
    }

    case Type::QUASI_DYNAMIC_REGION:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrQuasiDynamicRegionIds();;
        ok = f(ret, tile_id, feature_type, ids);
        break;
    }

    case Type::SD_ROAD:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrSdRoadIds();;
        ok = f(ret, tile_id, feature_type, ids);
        break;
    }

    case Type::OBJECT_TRAFFIC_SIGN:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrObjectTrafficSignIds();;
        ok = f(ret, tile_id, feature_type, ids);
        break;
    }

    case Type::OBJECT_REGIONAL_INFO:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrObjectRegionalInfoIds();;
        ok = f(ret, tile_id, feature_type, ids);
        break;
    }

    case Type::OBJECT_SAFE_ISLAND:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrObjectSafeIslandIds();;
        ok = f(ret, tile_id, feature_type, ids);
        break;
    }

    case Type::OBJECT_INFO:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrObjectInfoIds();;
        ok = f(ret, tile_id, feature_type, ids);
        break;
    }

    case Type::OBJECT_LINEAR_INFO:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrObjectLinearInfoIds();;
        ok = f(ret, tile_id, feature_type, ids);
        break;
    }

    case Type::OBJECT_TRAFFIC_LIGHT_GROUP:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrObjectTrafficLightGroupIds();;
        ok = f(ret, tile_id, feature_type, ids);
        break;
    }

    case Type::OBJECT_STOP_LINE:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrObjectStopLineIds();;
        ok = f(ret, tile_id, feature_type, ids);
        break;
    }

    case Type::JUNCTION:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrJunctionIds();;
        ok = f(ret, tile_id, feature_type, ids);
        break;
    }

    case Type::GEOFENCE:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrGeofenceIds();;
        ok = f(ret, tile_id, feature_type, ids);
        break;
    }

    case Type::ROAD:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrRoadIds();;
        ok = f(ret, tile_id, feature_type, ids);
        break;
    }

    case Type::LANE_GROUP:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrLaneGroupIds();;
        ok = f(ret, tile_id, feature_type, ids);
        break;
    }

    case Type::LANE_BOUNDARY:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrLaneBoundaryIds();;
        ok = f(ret, tile_id, feature_type, ids);
        break;
    }

    case Type::LANE:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrLaneIds();;
        ok = f(ret, tile_id, feature_type, ids);
        break;
    }

    case Type::OBJECT_TRAFFIC_LIGHT:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrObjectTrafficLightIds();;
        ok = f(ret, tile_id, feature_type, ids);
        break;
    }

    case Type::OBJECT_PEDESTRIAN_CROSSING:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrObjectPedestrianCrossingIds();;
        ok = f(ret, tile_id, feature_type, ids);
        break;
    }

    case Type::SD_NODE:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrSdNodeIds();;
        ok = f(ret, tile_id, feature_type, ids);
        break;
    }

    case Type::INTERSECTION:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrIntersectionIds();;
        ok = f(ret, tile_id, feature_type, ids);
        break;
    }

    case Type::ROUTING_PATH:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrRoutingPathIds();;
        ok = f(ret, tile_id, feature_type, ids);
        break;
    }

    case Type::ROUTING_GRAPH:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrRoutingGraphIds();;
        ok = f(ret, tile_id, feature_type, ids);
        break;
    }

    case Type::ROUTING_EDGE:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrRoutingEdgeIds();;
        ok = f(ret, tile_id, feature_type, ids);
        break;
    }

    case Type::CONNECTION:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrConnectionIds();;
        ok = f(ret, tile_id, feature_type, ids);
        break;
    }

    case Type::ROUTING_NODE:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrRoutingNodeIds();;
        ok = f(ret, tile_id, feature_type, ids);
        break;
    }
    default:
    {
        break;
    }
    }

    if (!ok)
    {
        LOG(ERROR) << "EnumerateTileByType fail, tile_id=" << tile_id << " feature_type=" << static_cast<int>(feature_type);
    }

    return ok;
}

/**
 * @brief Get feature ids from tile by feature type.
 *
 * @tparam Tile pointer refer to format::Tile(Tile*, std::shared_ptr<Tile>);
 *
 * @param[in] tile A pointer refer to a tile.
 * @param[in] feature_type Feature type refer to holo::map::format::Base::FeatureType;
 * @param[in] f Unary function that accepts tile, feature_type, and feature ids.
 *              This can either be a function pointer or a move constructible function object.
                Its return true, if successful.
 * @return true: No error;
 *         false: An error occurs in this function or in f.
 */
template<typename Tile, typename Type, typename F>
holo::bool_t EnumerateTileByType(Tile& tile, Type const feature_type, F f)
{
    if (nullptr == tile)
    {
        LOG(ERROR) << "EnumerateTileByType fail, invalid parameters";
        return false;
    }

    holo::map::format::helper::FeatureIdType const tile_id = tile->GetTileId();

    holo::bool_t ok = false;

    switch (feature_type)
    {
    case Type::TILE:
    {
        holo::map::format::helper::FeatureIdVectorType ids;
        ok = f(tile, feature_type, ids);
        break;
    }

    case Type::OBJECT_PARKING_SPACE:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrObjectParkingSpaceIds();;
        ok = f(tile, feature_type, ids);
        break;
    }

    case Type::OBJECT_PARKING_FLOOR:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrObjectParkingFloorIds();;
        ok = f(tile, feature_type, ids);
        break;
    }

    case Type::OBJECT_PARKING_LOT:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrObjectParkingLotIds();;
        ok = f(tile, feature_type, ids);
        break;
    }

    case Type::OBJECT_PARKING_POI:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrObjectParkingPoiIds();;
        ok = f(tile, feature_type, ids);
        break;
    }

    case Type::OBJECT_PARKING_BACKGROUND:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrObjectParkingBackgroundIds();;
        ok = f(tile, feature_type, ids);
        break;
    }

    case Type::QUASI_DYNAMIC_LANE_GROUP:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrQuasiDynamicLaneGroupIds();;
        ok = f(tile, feature_type, ids);
        break;
    }

    case Type::QUASI_DYNAMIC_LANE:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrQuasiDynamicLaneIds();;
        ok = f(tile, feature_type, ids);
        break;
    }

    case Type::QUASI_DYNAMIC_REGION:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrQuasiDynamicRegionIds();;
        ok = f(tile, feature_type, ids);
        break;
    }

    case Type::SD_ROAD:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrSdRoadIds();;
        ok = f(tile, feature_type, ids);
        break;
    }

    case Type::OBJECT_TRAFFIC_SIGN:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrObjectTrafficSignIds();;
        ok = f(tile, feature_type, ids);
        break;
    }

    case Type::OBJECT_REGIONAL_INFO:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrObjectRegionalInfoIds();;
        ok = f(tile, feature_type, ids);
        break;
    }

    case Type::OBJECT_SAFE_ISLAND:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrObjectSafeIslandIds();;
        ok = f(tile, feature_type, ids);
        break;
    }

    case Type::OBJECT_INFO:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrObjectInfoIds();;
        ok = f(tile, feature_type, ids);
        break;
    }

    case Type::OBJECT_LINEAR_INFO:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrObjectLinearInfoIds();;
        ok = f(tile, feature_type, ids);
        break;
    }

    case Type::OBJECT_TRAFFIC_LIGHT_GROUP:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrObjectTrafficLightGroupIds();;
        ok = f(tile, feature_type, ids);
        break;
    }

    case Type::OBJECT_STOP_LINE:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrObjectStopLineIds();;
        ok = f(tile, feature_type, ids);
        break;
    }

    case Type::JUNCTION:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrJunctionIds();;
        ok = f(tile, feature_type, ids);
        break;
    }

    case Type::GEOFENCE:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrGeofenceIds();;
        ok = f(tile, feature_type, ids);
        break;
    }

    case Type::ROAD:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrRoadIds();;
        ok = f(tile, feature_type, ids);
        break;
    }

    case Type::LANE_GROUP:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrLaneGroupIds();;
        ok = f(tile, feature_type, ids);
        break;
    }

    case Type::LANE_BOUNDARY:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrLaneBoundaryIds();;
        ok = f(tile, feature_type, ids);
        break;
    }

    case Type::LANE:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrLaneIds();;
        ok = f(tile, feature_type, ids);
        break;
    }

    case Type::OBJECT_TRAFFIC_LIGHT:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrObjectTrafficLightIds();;
        ok = f(tile, feature_type, ids);
        break;
    }

    case Type::OBJECT_PEDESTRIAN_CROSSING:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrObjectPedestrianCrossingIds();;
        ok = f(tile, feature_type, ids);
        break;
    }

    case Type::SD_NODE:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrSdNodeIds();;
        ok = f(tile, feature_type, ids);
        break;
    }

    case Type::INTERSECTION:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrIntersectionIds();;
        ok = f(tile, feature_type, ids);
        break;
    }

    case Type::ROUTING_PATH:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrRoutingPathIds();;
        ok = f(tile, feature_type, ids);
        break;
    }

    case Type::ROUTING_GRAPH:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrRoutingGraphIds();;
        ok = f(tile, feature_type, ids);
        break;
    }

    case Type::ROUTING_EDGE:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrRoutingEdgeIds();;
        ok = f(tile, feature_type, ids);
        break;
    }

    case Type::CONNECTION:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrConnectionIds();;
        ok = f(tile, feature_type, ids);
        break;
    }

    case Type::ROUTING_NODE:
    {
        holo::map::format::helper::FeatureIdVectorType const& ids = *tile->GetPtrRoutingNodeIds();;
        ok = f(tile, feature_type, ids);
        break;
    }
    default:
    {
        break;
    }
    }

    if (!ok)
    {
        LOG(ERROR) << "EnumerateTileByType fail, tile_id=" << tile_id << " feature_type=" << static_cast<int>(feature_type);
    }

    return ok;
}

/**
 * @brief Assign feature ids to tile by feature type.
 *
 * @tparam Tile pointer refer to format::Tile(Tile*, std::shared_ptr<Tile>);
 *
 * @param[in] tile A pointer refer to a tile.
 * @param[in] feature_type Feature type refer to holo::map::format::Base::FeatureType;
 * @param[in] ids Feature ids with feature type.
 * @return true: No error;
 *         false: An error occurs in this function.
 */
template<typename Tile, typename Type, typename Ids>
holo::bool_t EnumerateTileByTypeWithSetFeatureIds(Tile& tile, Type const feature_type, Ids const& ids)
{
    if (nullptr == tile)
    {
        LOG(ERROR) << "EnumerateTileByTypeWithSetFeatureIds fail, invalid parameters";
        return false;
    }

    holo::map::format::helper::FeatureIdType const tile_id = tile->GetTileId();

    holo::bool_t ok = false;

    switch (feature_type)
    {
    case Type::TILE:
    {
        ok = true;
        break;
    }

    case Type::OBJECT_PARKING_SPACE:
    {
        tile->SetObjectParkingSpaceIds(ids);
        ok = true;
        break;
    }

    case Type::OBJECT_PARKING_FLOOR:
    {
        tile->SetObjectParkingFloorIds(ids);
        ok = true;
        break;
    }

    case Type::OBJECT_PARKING_LOT:
    {
        tile->SetObjectParkingLotIds(ids);
        ok = true;
        break;
    }

    case Type::OBJECT_PARKING_POI:
    {
        tile->SetObjectParkingPoiIds(ids);
        ok = true;
        break;
    }

    case Type::OBJECT_PARKING_BACKGROUND:
    {
        tile->SetObjectParkingBackgroundIds(ids);
        ok = true;
        break;
    }

    case Type::QUASI_DYNAMIC_LANE_GROUP:
    {
        tile->SetQuasiDynamicLaneGroupIds(ids);
        ok = true;
        break;
    }

    case Type::QUASI_DYNAMIC_LANE:
    {
        tile->SetQuasiDynamicLaneIds(ids);
        ok = true;
        break;
    }

    case Type::QUASI_DYNAMIC_REGION:
    {
        tile->SetQuasiDynamicRegionIds(ids);
        ok = true;
        break;
    }

    case Type::SD_ROAD:
    {
        tile->SetSdRoadIds(ids);
        ok = true;
        break;
    }

    case Type::OBJECT_TRAFFIC_SIGN:
    {
        tile->SetObjectTrafficSignIds(ids);
        ok = true;
        break;
    }

    case Type::OBJECT_REGIONAL_INFO:
    {
        tile->SetObjectRegionalInfoIds(ids);
        ok = true;
        break;
    }

    case Type::OBJECT_SAFE_ISLAND:
    {
        tile->SetObjectSafeIslandIds(ids);
        ok = true;
        break;
    }

    case Type::OBJECT_INFO:
    {
        tile->SetObjectInfoIds(ids);
        ok = true;
        break;
    }

    case Type::OBJECT_LINEAR_INFO:
    {
        tile->SetObjectLinearInfoIds(ids);
        ok = true;
        break;
    }

    case Type::OBJECT_TRAFFIC_LIGHT_GROUP:
    {
        tile->SetObjectTrafficLightGroupIds(ids);
        ok = true;
        break;
    }

    case Type::OBJECT_STOP_LINE:
    {
        tile->SetObjectStopLineIds(ids);
        ok = true;
        break;
    }

    case Type::JUNCTION:
    {
        tile->SetJunctionIds(ids);
        ok = true;
        break;
    }

    case Type::GEOFENCE:
    {
        tile->SetGeofenceIds(ids);
        ok = true;
        break;
    }

    case Type::ROAD:
    {
        tile->SetRoadIds(ids);
        ok = true;
        break;
    }

    case Type::LANE_GROUP:
    {
        tile->SetLaneGroupIds(ids);
        ok = true;
        break;
    }

    case Type::LANE_BOUNDARY:
    {
        tile->SetLaneBoundaryIds(ids);
        ok = true;
        break;
    }

    case Type::LANE:
    {
        tile->SetLaneIds(ids);
        ok = true;
        break;
    }

    case Type::OBJECT_TRAFFIC_LIGHT:
    {
        tile->SetObjectTrafficLightIds(ids);
        ok = true;
        break;
    }

    case Type::OBJECT_PEDESTRIAN_CROSSING:
    {
        tile->SetObjectPedestrianCrossingIds(ids);
        ok = true;
        break;
    }

    case Type::SD_NODE:
    {
        tile->SetSdNodeIds(ids);
        ok = true;
        break;
    }

    case Type::INTERSECTION:
    {
        tile->SetIntersectionIds(ids);
        ok = true;
        break;
    }

    case Type::ROUTING_PATH:
    {
        tile->SetRoutingPathIds(ids);
        ok = true;
        break;
    }

    case Type::ROUTING_GRAPH:
    {
        tile->SetRoutingGraphIds(ids);
        ok = true;
        break;
    }

    case Type::ROUTING_EDGE:
    {
        tile->SetRoutingEdgeIds(ids);
        ok = true;
        break;
    }

    case Type::CONNECTION:
    {
        tile->SetConnectionIds(ids);
        ok = true;
        break;
    }

    case Type::ROUTING_NODE:
    {
        tile->SetRoutingNodeIds(ids);
        ok = true;
        break;
    }
    default:
    {
        break;
    }
    }

    if (!ok)
    {
        LOG(ERROR) << "EnumerateTileByTypeWithSetFeatureIds fail, tile_id=" << tile_id << " feature_type=" << static_cast<int>(feature_type);
    }

    return ok;
}

/**
 * @brief Get feature by type and id from Retriever.
 *
 * @tparam R pointer refer to RetBase(RetBase*, std::shared_ptr<RetBase>);
 *
 * @param[in] ret Pointer type refer to RetBase;
 * @param[in] feature_type Feature type refer to holo::map::format::Base::FeatureType;
 * @param[in] feature_id Feature id.
 * @param[out] feature A pointer refer to target feature.
 * @param[out] valid If target pointer is valid, it will be true, otherwise false.
 * @return true: No error;
 *         false: An error occurs in this function.
 */
template<typename R, typename Type, typename Id, typename T>
holo::bool_t GetFeatureByIdV2(R ret, Type const feature_type,  Id const feature_id,
    typename holo::map::format::helper::FeatureTraits<T>::SPtrType& feature, holo::bool_t& valid)
{
    valid = false;
    feature = nullptr;

    if (nullptr == ret)
    {
        LOG(ERROR) << "GetFeatureV2 fail, invalid parameter";
        return false;
    }

    holo::bool_t ok = EnumerateFeatureByType(ret, feature_type, feature_id, [&valid, &feature](
        typename holo::map::format::helper::FeatureTraits<T>::SPtrType& f, holo::bool_t& v) -> holo::bool_t {
        valid = v;
        feature = f;
        return true;
    });

    return ok;
}

/**
 * @brief Get all the tile ids from a feature.
 *
 * @param[in] feature Pointer type refer to a feature;
 * @param[out] result If the return value is valid, it's true.
 * @return Feature ids.
 */
template<typename T>
holo::map::format::helper::FeatureIdVectorType const& GetTileIdsFromFeature(
    typename holo::map::format::helper::FeatureTraits<T>::SPtrType feature, holo::bool_t& result)
{
    result = false;

    if (nullptr == feature)
    {
        LOG(ERROR) << "GetTileIdsFromFeature fail, invalid parameter";
        holo::map::format::helper::FeatureIdVectorType ids;
        return std::move(ids);
    }

    result = true;
    return *feature->GetPtrTileIds();
}

/**
 * @brief Get all the tile ids from a feature with FeatureBaseSPtrType.
 *
 * @param[in] base A Pointer refer to a FeatureBaseSPtrType;
 * @param[out] result If the return value is valid, it's true.
 * @return A pointer refer to Tile ids. If this function failed, it will be nullptr.
 */
template<typename T>
holo::map::format::helper::FeatureIdVectorType const* GetTileIdsFromBase(
    typename holo::map::format::helper::FeatureTraits<T>::SPtrType base, holo::bool_t& result)
{
    result = false;

    if (nullptr == base)
    {
        LOG(ERROR) << "GetTileIdsFromBase fail, invalid parameter";
        return nullptr;
    }

    holo::map::format::helper::FeatureType const type = base->GetFeatureType();
    switch (type)
    {

    case holo::map::format::helper::FeatureType::SD_NODE:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::SdNode>::SPtrType ptr = 
            std::dynamic_pointer_cast<holo::map::format::SdNode>(base);
        if (nullptr == ptr)
        {
            LOG(ERROR) << "GetTileIdsFromBase fail, invalid pointer, type=" << static_cast<int>(type);
            return nullptr;
        }
        result = true;
        return ptr->GetPtrTileIds();
    }

    case holo::map::format::helper::FeatureType::SD_ROAD:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::SdRoad>::SPtrType ptr = 
            std::dynamic_pointer_cast<holo::map::format::SdRoad>(base);
        if (nullptr == ptr)
        {
            LOG(ERROR) << "GetTileIdsFromBase fail, invalid pointer, type=" << static_cast<int>(type);
            return nullptr;
        }
        result = true;
        return ptr->GetPtrTileIds();
    }

    case holo::map::format::helper::FeatureType::ROAD:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::Road>::SPtrType ptr = 
            std::dynamic_pointer_cast<holo::map::format::Road>(base);
        if (nullptr == ptr)
        {
            LOG(ERROR) << "GetTileIdsFromBase fail, invalid pointer, type=" << static_cast<int>(type);
            return nullptr;
        }
        result = true;
        return ptr->GetPtrTileIds();
    }

    case holo::map::format::helper::FeatureType::LANE:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::Lane>::SPtrType ptr = 
            std::dynamic_pointer_cast<holo::map::format::Lane>(base);
        if (nullptr == ptr)
        {
            LOG(ERROR) << "GetTileIdsFromBase fail, invalid pointer, type=" << static_cast<int>(type);
            return nullptr;
        }
        result = true;
        return ptr->GetPtrTileIds();
    }

    case holo::map::format::helper::FeatureType::LANE_GROUP:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::LaneGroup>::SPtrType ptr = 
            std::dynamic_pointer_cast<holo::map::format::LaneGroup>(base);
        if (nullptr == ptr)
        {
            LOG(ERROR) << "GetTileIdsFromBase fail, invalid pointer, type=" << static_cast<int>(type);
            return nullptr;
        }
        result = true;
        return ptr->GetPtrTileIds();
    }

    case holo::map::format::helper::FeatureType::LANE_BOUNDARY:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::LaneBoundary>::SPtrType ptr = 
            std::dynamic_pointer_cast<holo::map::format::LaneBoundary>(base);
        if (nullptr == ptr)
        {
            LOG(ERROR) << "GetTileIdsFromBase fail, invalid pointer, type=" << static_cast<int>(type);
            return nullptr;
        }
        result = true;
        return ptr->GetPtrTileIds();
    }

    case holo::map::format::helper::FeatureType::OBJECT_INFO:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectInfo>::SPtrType ptr = 
            std::dynamic_pointer_cast<holo::map::format::ObjectInfo>(base);
        if (nullptr == ptr)
        {
            LOG(ERROR) << "GetTileIdsFromBase fail, invalid pointer, type=" << static_cast<int>(type);
            return nullptr;
        }
        result = true;
        return ptr->GetPtrTileIds();
    }

    case holo::map::format::helper::FeatureType::OBJECT_LINEAR_INFO:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectLinearInfo>::SPtrType ptr = 
            std::dynamic_pointer_cast<holo::map::format::ObjectLinearInfo>(base);
        if (nullptr == ptr)
        {
            LOG(ERROR) << "GetTileIdsFromBase fail, invalid pointer, type=" << static_cast<int>(type);
            return nullptr;
        }
        result = true;
        return ptr->GetPtrTileIds();
    }

    case holo::map::format::helper::FeatureType::OBJECT_REGIONAL_INFO:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectRegionalInfo>::SPtrType ptr = 
            std::dynamic_pointer_cast<holo::map::format::ObjectRegionalInfo>(base);
        if (nullptr == ptr)
        {
            LOG(ERROR) << "GetTileIdsFromBase fail, invalid pointer, type=" << static_cast<int>(type);
            return nullptr;
        }
        result = true;
        return ptr->GetPtrTileIds();
    }

    case holo::map::format::helper::FeatureType::OBJECT_PEDESTRIAN_CROSSING:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectPedestrianCrossing>::SPtrType ptr = 
            std::dynamic_pointer_cast<holo::map::format::ObjectPedestrianCrossing>(base);
        if (nullptr == ptr)
        {
            LOG(ERROR) << "GetTileIdsFromBase fail, invalid pointer, type=" << static_cast<int>(type);
            return nullptr;
        }
        result = true;
        return ptr->GetPtrTileIds();
    }

    case holo::map::format::helper::FeatureType::OBJECT_STOP_LINE:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectStopLine>::SPtrType ptr = 
            std::dynamic_pointer_cast<holo::map::format::ObjectStopLine>(base);
        if (nullptr == ptr)
        {
            LOG(ERROR) << "GetTileIdsFromBase fail, invalid pointer, type=" << static_cast<int>(type);
            return nullptr;
        }
        result = true;
        return ptr->GetPtrTileIds();
    }

    case holo::map::format::helper::FeatureType::OBJECT_TRAFFIC_LIGHT:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectTrafficLight>::SPtrType ptr = 
            std::dynamic_pointer_cast<holo::map::format::ObjectTrafficLight>(base);
        if (nullptr == ptr)
        {
            LOG(ERROR) << "GetTileIdsFromBase fail, invalid pointer, type=" << static_cast<int>(type);
            return nullptr;
        }
        result = true;
        return ptr->GetPtrTileIds();
    }

    case holo::map::format::helper::FeatureType::OBJECT_TRAFFIC_LIGHT_GROUP:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectTrafficLightGroup>::SPtrType ptr = 
            std::dynamic_pointer_cast<holo::map::format::ObjectTrafficLightGroup>(base);
        if (nullptr == ptr)
        {
            LOG(ERROR) << "GetTileIdsFromBase fail, invalid pointer, type=" << static_cast<int>(type);
            return nullptr;
        }
        result = true;
        return ptr->GetPtrTileIds();
    }

    case holo::map::format::helper::FeatureType::OBJECT_TRAFFIC_SIGN:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectTrafficSign>::SPtrType ptr = 
            std::dynamic_pointer_cast<holo::map::format::ObjectTrafficSign>(base);
        if (nullptr == ptr)
        {
            LOG(ERROR) << "GetTileIdsFromBase fail, invalid pointer, type=" << static_cast<int>(type);
            return nullptr;
        }
        result = true;
        return ptr->GetPtrTileIds();
    }

    case holo::map::format::helper::FeatureType::OBJECT_PARKING_LOT:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectParkingLot>::SPtrType ptr = 
            std::dynamic_pointer_cast<holo::map::format::ObjectParkingLot>(base);
        if (nullptr == ptr)
        {
            LOG(ERROR) << "GetTileIdsFromBase fail, invalid pointer, type=" << static_cast<int>(type);
            return nullptr;
        }
        result = true;
        return ptr->GetPtrTileIds();
    }

    case holo::map::format::helper::FeatureType::OBJECT_PARKING_FLOOR:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectParkingFloor>::SPtrType ptr = 
            std::dynamic_pointer_cast<holo::map::format::ObjectParkingFloor>(base);
        if (nullptr == ptr)
        {
            LOG(ERROR) << "GetTileIdsFromBase fail, invalid pointer, type=" << static_cast<int>(type);
            return nullptr;
        }
        result = true;
        return ptr->GetPtrTileIds();
    }

    case holo::map::format::helper::FeatureType::OBJECT_PARKING_BACKGROUND:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectParkingBackground>::SPtrType ptr = 
            std::dynamic_pointer_cast<holo::map::format::ObjectParkingBackground>(base);
        if (nullptr == ptr)
        {
            LOG(ERROR) << "GetTileIdsFromBase fail, invalid pointer, type=" << static_cast<int>(type);
            return nullptr;
        }
        result = true;
        return ptr->GetPtrTileIds();
    }

    case holo::map::format::helper::FeatureType::OBJECT_PARKING_POI:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectParkingPoi>::SPtrType ptr = 
            std::dynamic_pointer_cast<holo::map::format::ObjectParkingPoi>(base);
        if (nullptr == ptr)
        {
            LOG(ERROR) << "GetTileIdsFromBase fail, invalid pointer, type=" << static_cast<int>(type);
            return nullptr;
        }
        result = true;
        return ptr->GetPtrTileIds();
    }

    case holo::map::format::helper::FeatureType::OBJECT_PARKING_SPACE:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::ObjectParkingSpace>::SPtrType ptr = 
            std::dynamic_pointer_cast<holo::map::format::ObjectParkingSpace>(base);
        if (nullptr == ptr)
        {
            LOG(ERROR) << "GetTileIdsFromBase fail, invalid pointer, type=" << static_cast<int>(type);
            return nullptr;
        }
        result = true;
        return ptr->GetPtrTileIds();
    }

    case holo::map::format::helper::FeatureType::QUASI_DYNAMIC_LANE:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::QuasiDynamicLane>::SPtrType ptr = 
            std::dynamic_pointer_cast<holo::map::format::QuasiDynamicLane>(base);
        if (nullptr == ptr)
        {
            LOG(ERROR) << "GetTileIdsFromBase fail, invalid pointer, type=" << static_cast<int>(type);
            return nullptr;
        }
        result = true;
        return ptr->GetPtrTileIds();
    }

    case holo::map::format::helper::FeatureType::QUASI_DYNAMIC_LANE_GROUP:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::QuasiDynamicLaneGroup>::SPtrType ptr = 
            std::dynamic_pointer_cast<holo::map::format::QuasiDynamicLaneGroup>(base);
        if (nullptr == ptr)
        {
            LOG(ERROR) << "GetTileIdsFromBase fail, invalid pointer, type=" << static_cast<int>(type);
            return nullptr;
        }
        result = true;
        return ptr->GetPtrTileIds();
    }

    case holo::map::format::helper::FeatureType::QUASI_DYNAMIC_REGION:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::QuasiDynamicRegion>::SPtrType ptr = 
            std::dynamic_pointer_cast<holo::map::format::QuasiDynamicRegion>(base);
        if (nullptr == ptr)
        {
            LOG(ERROR) << "GetTileIdsFromBase fail, invalid pointer, type=" << static_cast<int>(type);
            return nullptr;
        }
        result = true;
        return ptr->GetPtrTileIds();
    }

    case holo::map::format::helper::FeatureType::ROUTING_PATH:
    {
        holo::map::format::helper::FeatureTraits<holo::map::format::RoutingPath>::SPtrType ptr = 
            std::dynamic_pointer_cast<holo::map::format::RoutingPath>(base);
        if (nullptr == ptr)
        {
            LOG(ERROR) << "GetTileIdsFromBase fail, invalid pointer, type=" << static_cast<int>(type);
            return nullptr;
        }
        result = true;
        return ptr->GetPtrTileIds();
    }
    default:
    {
        break;
    }
    }

    LOG(ERROR) << "GetTileIdsFromBase fail, invalid type, type=" << static_cast<int>(type);
    return nullptr;
}

/**
 * @}
 *
 */

} ///< namespace helper
} ///< namespace retriever

/**
 * @}
 *
 */

}  ///< namespace map
}  ///< namespace holo

#endif /* HOLO_MAP_RETRIEVER_RETBASE_H_ */