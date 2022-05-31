/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file tile.h
 * @brief Auto generated code for Tile format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_BASE_TILE_H_
#define HOLO_MAP_FORMAT_BASE_TILE_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/base/tile.pb.h>

#include <holo/map/proto/common/geo_box.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/geo_box.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  Tile: public Base
{
public:




private:
    ::std::uint64_t tile_id_; 
    ::std::vector<::std::uint64_t> road_ids_; 
    ::std::vector<::std::uint64_t> lane_ids_; 
    ::std::vector<::std::uint64_t> lane_boundary_ids_; 
    ::std::vector<::std::uint64_t> object_info_ids_; 
    ::std::vector<::std::uint64_t> position_ids_; 
    ::std::vector<::std::uint64_t> ground_roi_ids_; 
    ::std::vector<::std::uint64_t> ground_ids_; 
    ::std::vector<::std::uint64_t> connection_ids_; 
    ::std::vector<::std::uint64_t> junction_ids_; 
    ::std::vector<::std::uint64_t> routing_edge_ids_; 
    ::std::vector<::std::uint64_t> routing_node_ids_; 
    ::std::vector<::std::uint64_t> routing_graph_ids_; 
    ::std::vector<::std::uint64_t> sd_node_ids_; 
    ::std::vector<::std::uint64_t> sd_road_ids_; 
    ::std::uint32_t level_; 
    ::std::vector<::std::uint64_t> lane_group_ids_; 
    ::std::vector<::std::uint64_t> geofence_ids_; 
    GeoBox region_; 
    ::std::vector<::std::uint64_t> object_linear_info_ids_; 
    ::std::vector<::std::uint64_t> object_regional_info_ids_; 
    ::std::vector<::std::uint64_t> object_stop_line_ids_; 
    ::std::vector<::std::uint64_t> object_traffic_light_ids_; 
    ::std::vector<::std::uint64_t> object_traffic_light_group_ids_; 
    ::std::vector<::std::uint64_t> object_pedestrian_crossing_ids_; 
    ::std::vector<::std::uint64_t> object_traffic_sign_ids_; 
    ::std::vector<::std::uint64_t> object_parking_lot_ids_; 
    ::std::vector<::std::uint64_t> object_parking_floor_ids_; 
    ::std::vector<::std::uint64_t> object_parking_poi_ids_; 
    ::std::vector<::std::uint64_t> object_parking_background_ids_; 
    ::std::vector<::std::uint64_t> quasi_dynamic_lane_ids_; 
    ::std::vector<::std::uint64_t> quasi_dynamic_lane_group_ids_; 
    ::std::vector<::std::uint64_t> quasi_dynamic_region_ids_; 
    ::std::vector<::std::uint64_t> object_parking_space_ids_; 
    ::std::vector<::std::uint64_t> routing_path_ids_; 
    ::std::vector<::std::uint64_t> intersection_ids_; 
    ::std::vector<::std::uint64_t> object_safe_island_ids_; 

private:
    void DecodeProto(const ::holo::map::proto::base::Tile& _proto_handler);
    ::holo::map::proto::base::Tile EncodeProto();

public:
    Tile();
    explicit Tile(const ::holo::map::proto::base::Tile& _proto_handler);
    // init all format data
    Tile(const ::std::uint64_t _tile_id,const ::std::vector<::std::uint64_t>& _road_ids,const ::std::vector<::std::uint64_t>& _lane_ids,const ::std::vector<::std::uint64_t>& _lane_boundary_ids,const ::std::vector<::std::uint64_t>& _object_info_ids,const ::std::vector<::std::uint64_t>& _position_ids,const ::std::vector<::std::uint64_t>& _ground_roi_ids,const ::std::vector<::std::uint64_t>& _ground_ids,const ::std::vector<::std::uint64_t>& _connection_ids,const ::std::vector<::std::uint64_t>& _junction_ids,const ::std::vector<::std::uint64_t>& _routing_edge_ids,const ::std::vector<::std::uint64_t>& _routing_node_ids,const ::std::vector<::std::uint64_t>& _routing_graph_ids,const ::std::vector<::std::uint64_t>& _sd_node_ids,const ::std::vector<::std::uint64_t>& _sd_road_ids,const ::std::uint32_t _level,const ::std::vector<::std::uint64_t>& _lane_group_ids,const ::std::vector<::std::uint64_t>& _geofence_ids,const GeoBox& _region,const ::std::vector<::std::uint64_t>& _object_linear_info_ids,const ::std::vector<::std::uint64_t>& _object_regional_info_ids,const ::std::vector<::std::uint64_t>& _object_stop_line_ids,const ::std::vector<::std::uint64_t>& _object_traffic_light_ids,const ::std::vector<::std::uint64_t>& _object_traffic_light_group_ids,const ::std::vector<::std::uint64_t>& _object_pedestrian_crossing_ids,const ::std::vector<::std::uint64_t>& _object_traffic_sign_ids,const ::std::vector<::std::uint64_t>& _object_parking_lot_ids,const ::std::vector<::std::uint64_t>& _object_parking_floor_ids,const ::std::vector<::std::uint64_t>& _object_parking_poi_ids,const ::std::vector<::std::uint64_t>& _object_parking_background_ids,const ::std::vector<::std::uint64_t>& _quasi_dynamic_lane_ids,const ::std::vector<::std::uint64_t>& _quasi_dynamic_lane_group_ids,const ::std::vector<::std::uint64_t>& _quasi_dynamic_region_ids,const ::std::vector<::std::uint64_t>& _object_parking_space_ids,const ::std::vector<::std::uint64_t>& _routing_path_ids,const ::std::vector<::std::uint64_t>& _intersection_ids,const ::std::vector<::std::uint64_t>& _object_safe_island_ids);
    ~Tile();

    bool operator==(const ::holo::map::format::Tile& _other) const;
    Tile& operator=(const ::holo::map::proto::base::Tile& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::base::Tile GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetTileId() const
    {
        return tile_id_;
    }
    void SetTileId(const ::std::uint64_t _tile_id)
    {
        tile_id_ = _tile_id;
    }

    const ::std::vector<::std::uint64_t>* GetPtrRoadIds() const
    {
        return &road_ids_;
    }
    void SetRoadIds(const ::std::vector<::std::uint64_t>& _road_ids)
    {
        road_ids_ = _road_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrLaneIds() const
    {
        return &lane_ids_;
    }
    void SetLaneIds(const ::std::vector<::std::uint64_t>& _lane_ids)
    {
        lane_ids_ = _lane_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrLaneBoundaryIds() const
    {
        return &lane_boundary_ids_;
    }
    void SetLaneBoundaryIds(const ::std::vector<::std::uint64_t>& _lane_boundary_ids)
    {
        lane_boundary_ids_ = _lane_boundary_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrObjectInfoIds() const
    {
        return &object_info_ids_;
    }
    void SetObjectInfoIds(const ::std::vector<::std::uint64_t>& _object_info_ids)
    {
        object_info_ids_ = _object_info_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrPositionIds() const
    {
        return &position_ids_;
    }
    void SetPositionIds(const ::std::vector<::std::uint64_t>& _position_ids)
    {
        position_ids_ = _position_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrGroundRoiIds() const
    {
        return &ground_roi_ids_;
    }
    void SetGroundRoiIds(const ::std::vector<::std::uint64_t>& _ground_roi_ids)
    {
        ground_roi_ids_ = _ground_roi_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrGroundIds() const
    {
        return &ground_ids_;
    }
    void SetGroundIds(const ::std::vector<::std::uint64_t>& _ground_ids)
    {
        ground_ids_ = _ground_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrConnectionIds() const
    {
        return &connection_ids_;
    }
    void SetConnectionIds(const ::std::vector<::std::uint64_t>& _connection_ids)
    {
        connection_ids_ = _connection_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrJunctionIds() const
    {
        return &junction_ids_;
    }
    void SetJunctionIds(const ::std::vector<::std::uint64_t>& _junction_ids)
    {
        junction_ids_ = _junction_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrRoutingEdgeIds() const
    {
        return &routing_edge_ids_;
    }
    void SetRoutingEdgeIds(const ::std::vector<::std::uint64_t>& _routing_edge_ids)
    {
        routing_edge_ids_ = _routing_edge_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrRoutingNodeIds() const
    {
        return &routing_node_ids_;
    }
    void SetRoutingNodeIds(const ::std::vector<::std::uint64_t>& _routing_node_ids)
    {
        routing_node_ids_ = _routing_node_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrRoutingGraphIds() const
    {
        return &routing_graph_ids_;
    }
    void SetRoutingGraphIds(const ::std::vector<::std::uint64_t>& _routing_graph_ids)
    {
        routing_graph_ids_ = _routing_graph_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrSdNodeIds() const
    {
        return &sd_node_ids_;
    }
    void SetSdNodeIds(const ::std::vector<::std::uint64_t>& _sd_node_ids)
    {
        sd_node_ids_ = _sd_node_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrSdRoadIds() const
    {
        return &sd_road_ids_;
    }
    void SetSdRoadIds(const ::std::vector<::std::uint64_t>& _sd_road_ids)
    {
        sd_road_ids_ = _sd_road_ids;
    }

    ::std::uint32_t GetLevel() const
    {
        return level_;
    }
    void SetLevel(const ::std::uint32_t _level)
    {
        level_ = _level;
    }

    const ::std::vector<::std::uint64_t>* GetPtrLaneGroupIds() const
    {
        return &lane_group_ids_;
    }
    void SetLaneGroupIds(const ::std::vector<::std::uint64_t>& _lane_group_ids)
    {
        lane_group_ids_ = _lane_group_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrGeofenceIds() const
    {
        return &geofence_ids_;
    }
    void SetGeofenceIds(const ::std::vector<::std::uint64_t>& _geofence_ids)
    {
        geofence_ids_ = _geofence_ids;
    }

    const GeoBox& GetRegion() const
    {
        return region_;
    }
    void SetRegion(const GeoBox& _region)
    {
        region_ = _region;
    }

    const ::std::vector<::std::uint64_t>* GetPtrObjectLinearInfoIds() const
    {
        return &object_linear_info_ids_;
    }
    void SetObjectLinearInfoIds(const ::std::vector<::std::uint64_t>& _object_linear_info_ids)
    {
        object_linear_info_ids_ = _object_linear_info_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrObjectRegionalInfoIds() const
    {
        return &object_regional_info_ids_;
    }
    void SetObjectRegionalInfoIds(const ::std::vector<::std::uint64_t>& _object_regional_info_ids)
    {
        object_regional_info_ids_ = _object_regional_info_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrObjectStopLineIds() const
    {
        return &object_stop_line_ids_;
    }
    void SetObjectStopLineIds(const ::std::vector<::std::uint64_t>& _object_stop_line_ids)
    {
        object_stop_line_ids_ = _object_stop_line_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrObjectTrafficLightIds() const
    {
        return &object_traffic_light_ids_;
    }
    void SetObjectTrafficLightIds(const ::std::vector<::std::uint64_t>& _object_traffic_light_ids)
    {
        object_traffic_light_ids_ = _object_traffic_light_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrObjectTrafficLightGroupIds() const
    {
        return &object_traffic_light_group_ids_;
    }
    void SetObjectTrafficLightGroupIds(const ::std::vector<::std::uint64_t>& _object_traffic_light_group_ids)
    {
        object_traffic_light_group_ids_ = _object_traffic_light_group_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrObjectPedestrianCrossingIds() const
    {
        return &object_pedestrian_crossing_ids_;
    }
    void SetObjectPedestrianCrossingIds(const ::std::vector<::std::uint64_t>& _object_pedestrian_crossing_ids)
    {
        object_pedestrian_crossing_ids_ = _object_pedestrian_crossing_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrObjectTrafficSignIds() const
    {
        return &object_traffic_sign_ids_;
    }
    void SetObjectTrafficSignIds(const ::std::vector<::std::uint64_t>& _object_traffic_sign_ids)
    {
        object_traffic_sign_ids_ = _object_traffic_sign_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrObjectParkingLotIds() const
    {
        return &object_parking_lot_ids_;
    }
    void SetObjectParkingLotIds(const ::std::vector<::std::uint64_t>& _object_parking_lot_ids)
    {
        object_parking_lot_ids_ = _object_parking_lot_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrObjectParkingFloorIds() const
    {
        return &object_parking_floor_ids_;
    }
    void SetObjectParkingFloorIds(const ::std::vector<::std::uint64_t>& _object_parking_floor_ids)
    {
        object_parking_floor_ids_ = _object_parking_floor_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrObjectParkingPoiIds() const
    {
        return &object_parking_poi_ids_;
    }
    void SetObjectParkingPoiIds(const ::std::vector<::std::uint64_t>& _object_parking_poi_ids)
    {
        object_parking_poi_ids_ = _object_parking_poi_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrObjectParkingBackgroundIds() const
    {
        return &object_parking_background_ids_;
    }
    void SetObjectParkingBackgroundIds(const ::std::vector<::std::uint64_t>& _object_parking_background_ids)
    {
        object_parking_background_ids_ = _object_parking_background_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrQuasiDynamicLaneIds() const
    {
        return &quasi_dynamic_lane_ids_;
    }
    void SetQuasiDynamicLaneIds(const ::std::vector<::std::uint64_t>& _quasi_dynamic_lane_ids)
    {
        quasi_dynamic_lane_ids_ = _quasi_dynamic_lane_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrQuasiDynamicLaneGroupIds() const
    {
        return &quasi_dynamic_lane_group_ids_;
    }
    void SetQuasiDynamicLaneGroupIds(const ::std::vector<::std::uint64_t>& _quasi_dynamic_lane_group_ids)
    {
        quasi_dynamic_lane_group_ids_ = _quasi_dynamic_lane_group_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrQuasiDynamicRegionIds() const
    {
        return &quasi_dynamic_region_ids_;
    }
    void SetQuasiDynamicRegionIds(const ::std::vector<::std::uint64_t>& _quasi_dynamic_region_ids)
    {
        quasi_dynamic_region_ids_ = _quasi_dynamic_region_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrObjectParkingSpaceIds() const
    {
        return &object_parking_space_ids_;
    }
    void SetObjectParkingSpaceIds(const ::std::vector<::std::uint64_t>& _object_parking_space_ids)
    {
        object_parking_space_ids_ = _object_parking_space_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrRoutingPathIds() const
    {
        return &routing_path_ids_;
    }
    void SetRoutingPathIds(const ::std::vector<::std::uint64_t>& _routing_path_ids)
    {
        routing_path_ids_ = _routing_path_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrIntersectionIds() const
    {
        return &intersection_ids_;
    }
    void SetIntersectionIds(const ::std::vector<::std::uint64_t>& _intersection_ids)
    {
        intersection_ids_ = _intersection_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrObjectSafeIslandIds() const
    {
        return &object_safe_island_ids_;
    }
    void SetObjectSafeIslandIds(const ::std::vector<::std::uint64_t>& _object_safe_island_ids)
    {
        object_safe_island_ids_ = _object_safe_island_ids;
    }


    void ClearRoadIds()
    {
        road_ids_.clear();
    }
    void AddRoadIdsElement(const ::std::uint64_t& _value)
    {
        road_ids_.push_back(_value);
    }
    void UniqueAddRoadIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(road_ids_, _value);
    }

    void ClearLaneIds()
    {
        lane_ids_.clear();
    }
    void AddLaneIdsElement(const ::std::uint64_t& _value)
    {
        lane_ids_.push_back(_value);
    }
    void UniqueAddLaneIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(lane_ids_, _value);
    }

    void ClearLaneBoundaryIds()
    {
        lane_boundary_ids_.clear();
    }
    void AddLaneBoundaryIdsElement(const ::std::uint64_t& _value)
    {
        lane_boundary_ids_.push_back(_value);
    }
    void UniqueAddLaneBoundaryIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(lane_boundary_ids_, _value);
    }

    void ClearObjectInfoIds()
    {
        object_info_ids_.clear();
    }
    void AddObjectInfoIdsElement(const ::std::uint64_t& _value)
    {
        object_info_ids_.push_back(_value);
    }
    void UniqueAddObjectInfoIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(object_info_ids_, _value);
    }

    void ClearPositionIds()
    {
        position_ids_.clear();
    }
    void AddPositionIdsElement(const ::std::uint64_t& _value)
    {
        position_ids_.push_back(_value);
    }
    void UniqueAddPositionIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(position_ids_, _value);
    }

    void ClearGroundRoiIds()
    {
        ground_roi_ids_.clear();
    }
    void AddGroundRoiIdsElement(const ::std::uint64_t& _value)
    {
        ground_roi_ids_.push_back(_value);
    }
    void UniqueAddGroundRoiIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(ground_roi_ids_, _value);
    }

    void ClearGroundIds()
    {
        ground_ids_.clear();
    }
    void AddGroundIdsElement(const ::std::uint64_t& _value)
    {
        ground_ids_.push_back(_value);
    }
    void UniqueAddGroundIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(ground_ids_, _value);
    }

    void ClearConnectionIds()
    {
        connection_ids_.clear();
    }
    void AddConnectionIdsElement(const ::std::uint64_t& _value)
    {
        connection_ids_.push_back(_value);
    }
    void UniqueAddConnectionIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(connection_ids_, _value);
    }

    void ClearJunctionIds()
    {
        junction_ids_.clear();
    }
    void AddJunctionIdsElement(const ::std::uint64_t& _value)
    {
        junction_ids_.push_back(_value);
    }
    void UniqueAddJunctionIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(junction_ids_, _value);
    }

    void ClearRoutingEdgeIds()
    {
        routing_edge_ids_.clear();
    }
    void AddRoutingEdgeIdsElement(const ::std::uint64_t& _value)
    {
        routing_edge_ids_.push_back(_value);
    }
    void UniqueAddRoutingEdgeIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(routing_edge_ids_, _value);
    }

    void ClearRoutingNodeIds()
    {
        routing_node_ids_.clear();
    }
    void AddRoutingNodeIdsElement(const ::std::uint64_t& _value)
    {
        routing_node_ids_.push_back(_value);
    }
    void UniqueAddRoutingNodeIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(routing_node_ids_, _value);
    }

    void ClearRoutingGraphIds()
    {
        routing_graph_ids_.clear();
    }
    void AddRoutingGraphIdsElement(const ::std::uint64_t& _value)
    {
        routing_graph_ids_.push_back(_value);
    }
    void UniqueAddRoutingGraphIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(routing_graph_ids_, _value);
    }

    void ClearSdNodeIds()
    {
        sd_node_ids_.clear();
    }
    void AddSdNodeIdsElement(const ::std::uint64_t& _value)
    {
        sd_node_ids_.push_back(_value);
    }
    void UniqueAddSdNodeIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(sd_node_ids_, _value);
    }

    void ClearSdRoadIds()
    {
        sd_road_ids_.clear();
    }
    void AddSdRoadIdsElement(const ::std::uint64_t& _value)
    {
        sd_road_ids_.push_back(_value);
    }
    void UniqueAddSdRoadIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(sd_road_ids_, _value);
    }

    void ClearLaneGroupIds()
    {
        lane_group_ids_.clear();
    }
    void AddLaneGroupIdsElement(const ::std::uint64_t& _value)
    {
        lane_group_ids_.push_back(_value);
    }
    void UniqueAddLaneGroupIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(lane_group_ids_, _value);
    }

    void ClearGeofenceIds()
    {
        geofence_ids_.clear();
    }
    void AddGeofenceIdsElement(const ::std::uint64_t& _value)
    {
        geofence_ids_.push_back(_value);
    }
    void UniqueAddGeofenceIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(geofence_ids_, _value);
    }

    void ClearObjectLinearInfoIds()
    {
        object_linear_info_ids_.clear();
    }
    void AddObjectLinearInfoIdsElement(const ::std::uint64_t& _value)
    {
        object_linear_info_ids_.push_back(_value);
    }
    void UniqueAddObjectLinearInfoIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(object_linear_info_ids_, _value);
    }

    void ClearObjectRegionalInfoIds()
    {
        object_regional_info_ids_.clear();
    }
    void AddObjectRegionalInfoIdsElement(const ::std::uint64_t& _value)
    {
        object_regional_info_ids_.push_back(_value);
    }
    void UniqueAddObjectRegionalInfoIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(object_regional_info_ids_, _value);
    }

    void ClearObjectStopLineIds()
    {
        object_stop_line_ids_.clear();
    }
    void AddObjectStopLineIdsElement(const ::std::uint64_t& _value)
    {
        object_stop_line_ids_.push_back(_value);
    }
    void UniqueAddObjectStopLineIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(object_stop_line_ids_, _value);
    }

    void ClearObjectTrafficLightIds()
    {
        object_traffic_light_ids_.clear();
    }
    void AddObjectTrafficLightIdsElement(const ::std::uint64_t& _value)
    {
        object_traffic_light_ids_.push_back(_value);
    }
    void UniqueAddObjectTrafficLightIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(object_traffic_light_ids_, _value);
    }

    void ClearObjectTrafficLightGroupIds()
    {
        object_traffic_light_group_ids_.clear();
    }
    void AddObjectTrafficLightGroupIdsElement(const ::std::uint64_t& _value)
    {
        object_traffic_light_group_ids_.push_back(_value);
    }
    void UniqueAddObjectTrafficLightGroupIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(object_traffic_light_group_ids_, _value);
    }

    void ClearObjectPedestrianCrossingIds()
    {
        object_pedestrian_crossing_ids_.clear();
    }
    void AddObjectPedestrianCrossingIdsElement(const ::std::uint64_t& _value)
    {
        object_pedestrian_crossing_ids_.push_back(_value);
    }
    void UniqueAddObjectPedestrianCrossingIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(object_pedestrian_crossing_ids_, _value);
    }

    void ClearObjectTrafficSignIds()
    {
        object_traffic_sign_ids_.clear();
    }
    void AddObjectTrafficSignIdsElement(const ::std::uint64_t& _value)
    {
        object_traffic_sign_ids_.push_back(_value);
    }
    void UniqueAddObjectTrafficSignIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(object_traffic_sign_ids_, _value);
    }

    void ClearObjectParkingLotIds()
    {
        object_parking_lot_ids_.clear();
    }
    void AddObjectParkingLotIdsElement(const ::std::uint64_t& _value)
    {
        object_parking_lot_ids_.push_back(_value);
    }
    void UniqueAddObjectParkingLotIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(object_parking_lot_ids_, _value);
    }

    void ClearObjectParkingFloorIds()
    {
        object_parking_floor_ids_.clear();
    }
    void AddObjectParkingFloorIdsElement(const ::std::uint64_t& _value)
    {
        object_parking_floor_ids_.push_back(_value);
    }
    void UniqueAddObjectParkingFloorIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(object_parking_floor_ids_, _value);
    }

    void ClearObjectParkingPoiIds()
    {
        object_parking_poi_ids_.clear();
    }
    void AddObjectParkingPoiIdsElement(const ::std::uint64_t& _value)
    {
        object_parking_poi_ids_.push_back(_value);
    }
    void UniqueAddObjectParkingPoiIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(object_parking_poi_ids_, _value);
    }

    void ClearObjectParkingBackgroundIds()
    {
        object_parking_background_ids_.clear();
    }
    void AddObjectParkingBackgroundIdsElement(const ::std::uint64_t& _value)
    {
        object_parking_background_ids_.push_back(_value);
    }
    void UniqueAddObjectParkingBackgroundIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(object_parking_background_ids_, _value);
    }

    void ClearQuasiDynamicLaneIds()
    {
        quasi_dynamic_lane_ids_.clear();
    }
    void AddQuasiDynamicLaneIdsElement(const ::std::uint64_t& _value)
    {
        quasi_dynamic_lane_ids_.push_back(_value);
    }
    void UniqueAddQuasiDynamicLaneIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(quasi_dynamic_lane_ids_, _value);
    }

    void ClearQuasiDynamicLaneGroupIds()
    {
        quasi_dynamic_lane_group_ids_.clear();
    }
    void AddQuasiDynamicLaneGroupIdsElement(const ::std::uint64_t& _value)
    {
        quasi_dynamic_lane_group_ids_.push_back(_value);
    }
    void UniqueAddQuasiDynamicLaneGroupIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(quasi_dynamic_lane_group_ids_, _value);
    }

    void ClearQuasiDynamicRegionIds()
    {
        quasi_dynamic_region_ids_.clear();
    }
    void AddQuasiDynamicRegionIdsElement(const ::std::uint64_t& _value)
    {
        quasi_dynamic_region_ids_.push_back(_value);
    }
    void UniqueAddQuasiDynamicRegionIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(quasi_dynamic_region_ids_, _value);
    }

    void ClearObjectParkingSpaceIds()
    {
        object_parking_space_ids_.clear();
    }
    void AddObjectParkingSpaceIdsElement(const ::std::uint64_t& _value)
    {
        object_parking_space_ids_.push_back(_value);
    }
    void UniqueAddObjectParkingSpaceIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(object_parking_space_ids_, _value);
    }

    void ClearRoutingPathIds()
    {
        routing_path_ids_.clear();
    }
    void AddRoutingPathIdsElement(const ::std::uint64_t& _value)
    {
        routing_path_ids_.push_back(_value);
    }
    void UniqueAddRoutingPathIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(routing_path_ids_, _value);
    }

    void ClearIntersectionIds()
    {
        intersection_ids_.clear();
    }
    void AddIntersectionIdsElement(const ::std::uint64_t& _value)
    {
        intersection_ids_.push_back(_value);
    }
    void UniqueAddIntersectionIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(intersection_ids_, _value);
    }

    void ClearObjectSafeIslandIds()
    {
        object_safe_island_ids_.clear();
    }
    void AddObjectSafeIslandIdsElement(const ::std::uint64_t& _value)
    {
        object_safe_island_ids_.push_back(_value);
    }
    void UniqueAddObjectSafeIslandIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(object_safe_island_ids_, _value);
    }









};  // class Tile

typedef ::std::shared_ptr<Tile> PtrTile;
typedef const ::std::vector<Tile>* ConstRawPtrVecTile;
typedef ::std::vector<Tile>* RawPtrVecTile;
typedef ::std::shared_ptr<Tile const> ConstPtrTile;
typedef ::std::shared_ptr<::std::vector<Tile> const> ConstPtrVecTile;
typedef ::std::unordered_map<::std::uint64_t, PtrTile> HashmapTile;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_BASE_TILE_H_