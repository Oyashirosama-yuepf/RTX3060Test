/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file routing_path.h
 * @brief Auto generated code for RoutingPath format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_NAVIGATION_ROUTING_PATH_H_
#define HOLO_MAP_FORMAT_NAVIGATION_ROUTING_PATH_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/navigation/routing_path.pb.h>

#include <holo/map/proto/navigation/routing_path_element.pb.h>

#include <holo/map/proto/navigation/routing_position.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/navigation/routing_path_element.h>

#include <holo/map/format/navigation/routing_position.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  RoutingPath: public Base
{
public:

        
    enum PathType
    {
        PATH_TYPE_UNDEFINED=  0,  
        PATH_TYPE_WHOLE_MAIN_PATH=  1,  
        PATH_TYPE_PARTIAL_MAIN_PATH=  2,  
        PATH_TYPE_BRANCH_PATH=  3,  
    };

        
    enum RoutingMode
    {
        ROUTING_MODE_UNDEFINED=  0,  
        ROUTING_MODE_OUT_ROUTE=  1,  
        ROUTING_MODE_ON_HD_ROUTE=  2,  
        ROUTING_MODE_ON_SD_ROUTE=  3,  
        ROUTING_MODE_ON_SD_HD_ROUTE=  4,  
        ROUTING_MODE_RESERVED_1=  200,  
        ROUTING_MODE_RESERVED_2=  201,  
        ROUTING_MODE_RESERVED_3=  202,  
        ROUTING_MODE_RESERVED_4=  203,  
        ROUTING_MODE_RESERVED_5=  204,  
        ROUTING_MODE_OTHERS=  255,  
    };

        
    enum OperationMode
    {
        OPERATION_MODE_INVALID=  0,  
        OPERATION_MODE_NAVIGATION=  1,  
        OPERATION_MODE_CRUISER=  2,  
        OPERATION_MODE_YAWING=  3,  
        OPERATION_MODE_RENAVIGATION=  4,  
        OPERATION_MODE_RESERVED_1=  200,  
        OPERATION_MODE_RESERVED_2=  201,  
        OPERATION_MODE_RESERVED_3=  202,  
        OPERATION_MODE_RESERVED_4=  203,  
        OPERATION_MODE_RESERVED_5=  204,  
        OPERATION_MODE_OTHERS=  255,  
    };

    static const ::std::map<::std::string, PathType>& ENUMSTR_PATHTYPE() 
    { 
        static const ::std::map<::std::string, PathType> data{
        { "UNDEFINED", PathType::PATH_TYPE_UNDEFINED },
        { "WHOLE_MAIN_PATH", PathType::PATH_TYPE_WHOLE_MAIN_PATH },
        { "PARTIAL_MAIN_PATH", PathType::PATH_TYPE_PARTIAL_MAIN_PATH },
        { "BRANCH_PATH", PathType::PATH_TYPE_BRANCH_PATH }};
        return data;
    }

    static const ::std::map<::std::string, RoutingMode>& ENUMSTR_ROUTINGMODE() 
    { 
        static const ::std::map<::std::string, RoutingMode> data{
        { "UNDEFINED", RoutingMode::ROUTING_MODE_UNDEFINED },
        { "OUT_ROUTE", RoutingMode::ROUTING_MODE_OUT_ROUTE },
        { "ON_HD_ROUTE", RoutingMode::ROUTING_MODE_ON_HD_ROUTE },
        { "ON_SD_ROUTE", RoutingMode::ROUTING_MODE_ON_SD_ROUTE },
        { "ON_SD_HD_ROUTE", RoutingMode::ROUTING_MODE_ON_SD_HD_ROUTE },
        { "RESERVED_1", RoutingMode::ROUTING_MODE_RESERVED_1 },
        { "RESERVED_2", RoutingMode::ROUTING_MODE_RESERVED_2 },
        { "RESERVED_3", RoutingMode::ROUTING_MODE_RESERVED_3 },
        { "RESERVED_4", RoutingMode::ROUTING_MODE_RESERVED_4 },
        { "RESERVED_5", RoutingMode::ROUTING_MODE_RESERVED_5 },
        { "OTHERS", RoutingMode::ROUTING_MODE_OTHERS }};
        return data;
    }

    static const ::std::map<::std::string, OperationMode>& ENUMSTR_OPERATIONMODE() 
    { 
        static const ::std::map<::std::string, OperationMode> data{
        { "INVALID", OperationMode::OPERATION_MODE_INVALID },
        { "NAVIGATION", OperationMode::OPERATION_MODE_NAVIGATION },
        { "CRUISER", OperationMode::OPERATION_MODE_CRUISER },
        { "YAWING", OperationMode::OPERATION_MODE_YAWING },
        { "RENAVIGATION", OperationMode::OPERATION_MODE_RENAVIGATION },
        { "RESERVED_1", OperationMode::OPERATION_MODE_RESERVED_1 },
        { "RESERVED_2", OperationMode::OPERATION_MODE_RESERVED_2 },
        { "RESERVED_3", OperationMode::OPERATION_MODE_RESERVED_3 },
        { "RESERVED_4", OperationMode::OPERATION_MODE_RESERVED_4 },
        { "RESERVED_5", OperationMode::OPERATION_MODE_RESERVED_5 },
        { "OTHERS", OperationMode::OPERATION_MODE_OTHERS }};
        return data;
    }


private:
    ::std::uint64_t routing_path_id_; 
    ::std::uint64_t rolling_counter_; 
    ::std::uint64_t start_index_; 
    ::std::uint64_t end_index_; 
    ::std::uint32_t total_count_; 
    ::std::vector<RoutingPathElement> elements_; 
    ::std::uint32_t priority_; 
    ::std::uint64_t timestamp_; 
    PathType path_type_; 
    RoutingPosition start_position_; 
    RoutingPosition end_position_; 
    ::std::vector<RoutingPosition> middle_positions_; 
    ::std::vector<::std::uint64_t> tile_ids_; 
    ::std::vector<::std::uint64_t> road_ids_; 
    ::std::vector<::std::uint64_t> lane_group_ids_; 
    ::std::vector<::std::uint64_t> lane_ids_; 
    ::std::vector<::std::uint64_t> lane_boundary_ids_; 
    ::std::vector<::std::uint64_t> sub_routing_path_ids_; 
    ::std::vector<::std::uint64_t> object_linear_info_ids_; 
    ::std::vector<::std::uint64_t> object_regional_info_ids_; 
    ::std::vector<::std::uint64_t> object_stop_line_ids_; 
    ::std::vector<::std::uint64_t> object_traffic_light_ids_; 
    ::std::vector<::std::uint64_t> object_traffic_light_group_ids_; 
    ::std::vector<::std::uint64_t> object_pedestrian_crossing_ids_; 
    ::std::vector<::std::uint64_t> object_traffic_sign_ids_; 
    ::std::vector<::std::uint64_t> object_safe_island_ids_; 
    ::std::vector<::std::uint64_t> intersection_ids_; 
    ::std::vector<::std::uint64_t> object_parking_lot_ids_; 
    ::std::vector<::std::uint64_t> object_parking_floor_ids_; 
    ::std::vector<::std::uint64_t> object_parking_poi_ids_; 
    ::std::vector<::std::uint64_t> object_parking_background_ids_; 
    ::std::vector<::std::uint64_t> object_parking_space_ids_; 
    ::std::int32_t distance_to_sd_destination_cm_; 
    ::std::int32_t distance_to_hd_destination_cm_; 
    RoutingMode routing_mode_; 
    OperationMode operation_mode_; 

private:
    void DecodeProto(const ::holo::map::proto::navigation::RoutingPath& _proto_handler);
    ::holo::map::proto::navigation::RoutingPath EncodeProto();

public:
    RoutingPath();
    explicit RoutingPath(const ::holo::map::proto::navigation::RoutingPath& _proto_handler);
    // init all format data
    RoutingPath(const ::std::uint64_t _routing_path_id,const ::std::uint64_t _rolling_counter,const ::std::uint64_t _start_index,const ::std::uint64_t _end_index,const ::std::uint32_t _total_count,const ::std::vector<RoutingPathElement>& _elements,const ::std::uint32_t _priority,const ::std::uint64_t _timestamp,const PathType& _path_type,const RoutingPosition& _start_position,const RoutingPosition& _end_position,const ::std::vector<RoutingPosition>& _middle_positions,const ::std::vector<::std::uint64_t>& _tile_ids,const ::std::vector<::std::uint64_t>& _road_ids,const ::std::vector<::std::uint64_t>& _lane_group_ids,const ::std::vector<::std::uint64_t>& _lane_ids,const ::std::vector<::std::uint64_t>& _lane_boundary_ids,const ::std::vector<::std::uint64_t>& _sub_routing_path_ids,const ::std::vector<::std::uint64_t>& _object_linear_info_ids,const ::std::vector<::std::uint64_t>& _object_regional_info_ids,const ::std::vector<::std::uint64_t>& _object_stop_line_ids,const ::std::vector<::std::uint64_t>& _object_traffic_light_ids,const ::std::vector<::std::uint64_t>& _object_traffic_light_group_ids,const ::std::vector<::std::uint64_t>& _object_pedestrian_crossing_ids,const ::std::vector<::std::uint64_t>& _object_traffic_sign_ids,const ::std::vector<::std::uint64_t>& _object_safe_island_ids,const ::std::vector<::std::uint64_t>& _intersection_ids,const ::std::vector<::std::uint64_t>& _object_parking_lot_ids,const ::std::vector<::std::uint64_t>& _object_parking_floor_ids,const ::std::vector<::std::uint64_t>& _object_parking_poi_ids,const ::std::vector<::std::uint64_t>& _object_parking_background_ids,const ::std::vector<::std::uint64_t>& _object_parking_space_ids,const ::std::int32_t _distance_to_sd_destination_cm,const ::std::int32_t _distance_to_hd_destination_cm,const RoutingMode& _routing_mode,const OperationMode& _operation_mode);
    ~RoutingPath();

    bool operator==(const ::holo::map::format::RoutingPath& _other) const;
    RoutingPath& operator=(const ::holo::map::proto::navigation::RoutingPath& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::navigation::RoutingPath GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetRoutingPathId() const
    {
        return routing_path_id_;
    }
    void SetRoutingPathId(const ::std::uint64_t _routing_path_id)
    {
        routing_path_id_ = _routing_path_id;
    }

    ::std::uint64_t GetRollingCounter() const
    {
        return rolling_counter_;
    }
    void SetRollingCounter(const ::std::uint64_t _rolling_counter)
    {
        rolling_counter_ = _rolling_counter;
    }

    ::std::uint64_t GetStartIndex() const
    {
        return start_index_;
    }
    void SetStartIndex(const ::std::uint64_t _start_index)
    {
        start_index_ = _start_index;
    }

    ::std::uint64_t GetEndIndex() const
    {
        return end_index_;
    }
    void SetEndIndex(const ::std::uint64_t _end_index)
    {
        end_index_ = _end_index;
    }

    ::std::uint32_t GetTotalCount() const
    {
        return total_count_;
    }
    void SetTotalCount(const ::std::uint32_t _total_count)
    {
        total_count_ = _total_count;
    }

    const ::std::vector<RoutingPathElement>* GetPtrElements() const
    {
        return &elements_;
    }
    void SetElements(const ::std::vector<RoutingPathElement>& _elements)
    {
        elements_ = _elements;
    }

    ::std::uint32_t GetPriority() const
    {
        return priority_;
    }
    void SetPriority(const ::std::uint32_t _priority)
    {
        priority_ = _priority;
    }

    ::std::uint64_t GetTimestamp() const
    {
        return timestamp_;
    }
    void SetTimestamp(const ::std::uint64_t _timestamp)
    {
        timestamp_ = _timestamp;
    }

    const PathType& GetPathType() const
    {
        return path_type_;
    }
    void SetPathType(const PathType& _path_type)
    {
        path_type_ = _path_type;
    }

    const RoutingPosition& GetStartPosition() const
    {
        return start_position_;
    }
    void SetStartPosition(const RoutingPosition& _start_position)
    {
        start_position_ = _start_position;
    }

    const RoutingPosition& GetEndPosition() const
    {
        return end_position_;
    }
    void SetEndPosition(const RoutingPosition& _end_position)
    {
        end_position_ = _end_position;
    }

    const ::std::vector<RoutingPosition>* GetPtrMiddlePositions() const
    {
        return &middle_positions_;
    }
    void SetMiddlePositions(const ::std::vector<RoutingPosition>& _middle_positions)
    {
        middle_positions_ = _middle_positions;
    }

    const ::std::vector<::std::uint64_t>* GetPtrTileIds() const
    {
        return &tile_ids_;
    }
    void SetTileIds(const ::std::vector<::std::uint64_t>& _tile_ids)
    {
        tile_ids_ = _tile_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrRoadIds() const
    {
        return &road_ids_;
    }
    void SetRoadIds(const ::std::vector<::std::uint64_t>& _road_ids)
    {
        road_ids_ = _road_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrLaneGroupIds() const
    {
        return &lane_group_ids_;
    }
    void SetLaneGroupIds(const ::std::vector<::std::uint64_t>& _lane_group_ids)
    {
        lane_group_ids_ = _lane_group_ids;
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

    const ::std::vector<::std::uint64_t>* GetPtrSubRoutingPathIds() const
    {
        return &sub_routing_path_ids_;
    }
    void SetSubRoutingPathIds(const ::std::vector<::std::uint64_t>& _sub_routing_path_ids)
    {
        sub_routing_path_ids_ = _sub_routing_path_ids;
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

    const ::std::vector<::std::uint64_t>* GetPtrObjectSafeIslandIds() const
    {
        return &object_safe_island_ids_;
    }
    void SetObjectSafeIslandIds(const ::std::vector<::std::uint64_t>& _object_safe_island_ids)
    {
        object_safe_island_ids_ = _object_safe_island_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrIntersectionIds() const
    {
        return &intersection_ids_;
    }
    void SetIntersectionIds(const ::std::vector<::std::uint64_t>& _intersection_ids)
    {
        intersection_ids_ = _intersection_ids;
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

    const ::std::vector<::std::uint64_t>* GetPtrObjectParkingSpaceIds() const
    {
        return &object_parking_space_ids_;
    }
    void SetObjectParkingSpaceIds(const ::std::vector<::std::uint64_t>& _object_parking_space_ids)
    {
        object_parking_space_ids_ = _object_parking_space_ids;
    }

    ::std::int32_t GetDistanceToSdDestinationCm() const
    {
        return distance_to_sd_destination_cm_;
    }
    void SetDistanceToSdDestinationCm(const ::std::int32_t _distance_to_sd_destination_cm)
    {
        distance_to_sd_destination_cm_ = _distance_to_sd_destination_cm;
    }

    ::std::int32_t GetDistanceToHdDestinationCm() const
    {
        return distance_to_hd_destination_cm_;
    }
    void SetDistanceToHdDestinationCm(const ::std::int32_t _distance_to_hd_destination_cm)
    {
        distance_to_hd_destination_cm_ = _distance_to_hd_destination_cm;
    }

    const RoutingMode& GetRoutingMode() const
    {
        return routing_mode_;
    }
    void SetRoutingMode(const RoutingMode& _routing_mode)
    {
        routing_mode_ = _routing_mode;
    }

    const OperationMode& GetOperationMode() const
    {
        return operation_mode_;
    }
    void SetOperationMode(const OperationMode& _operation_mode)
    {
        operation_mode_ = _operation_mode;
    }


    void ClearElements()
    {
        elements_.clear();
    }
    void AddElementsElement(const RoutingPathElement& _value)
    {
        elements_.push_back(_value);
    }
    void UniqueAddElementsElements(const ::std::vector<RoutingPathElement>& _value)
    {
        UniqueAppend(elements_, _value);
    }

    void ClearMiddlePositions()
    {
        middle_positions_.clear();
    }
    void AddMiddlePositionsElement(const RoutingPosition& _value)
    {
        middle_positions_.push_back(_value);
    }
    void UniqueAddMiddlePositionsElements(const ::std::vector<RoutingPosition>& _value)
    {
        UniqueAppend(middle_positions_, _value);
    }

    void ClearTileIds()
    {
        tile_ids_.clear();
    }
    void AddTileIdsElement(const ::std::uint64_t& _value)
    {
        tile_ids_.push_back(_value);
    }
    void UniqueAddTileIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(tile_ids_, _value);
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

    void ClearSubRoutingPathIds()
    {
        sub_routing_path_ids_.clear();
    }
    void AddSubRoutingPathIdsElement(const ::std::uint64_t& _value)
    {
        sub_routing_path_ids_.push_back(_value);
    }
    void UniqueAddSubRoutingPathIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(sub_routing_path_ids_, _value);
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









};  // class RoutingPath

typedef ::std::shared_ptr<RoutingPath> PtrRoutingPath;
typedef const ::std::vector<RoutingPath>* ConstRawPtrVecRoutingPath;
typedef ::std::vector<RoutingPath>* RawPtrVecRoutingPath;
typedef ::std::shared_ptr<RoutingPath const> ConstPtrRoutingPath;
typedef ::std::shared_ptr<::std::vector<RoutingPath> const> ConstPtrVecRoutingPath;
typedef ::std::unordered_map<::std::uint64_t, PtrRoutingPath> HashmapRoutingPath;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_NAVIGATION_ROUTING_PATH_H_