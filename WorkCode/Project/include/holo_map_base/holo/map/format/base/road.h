/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file road.h
 * @brief Auto generated code for Road format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_BASE_ROAD_H_
#define HOLO_MAP_FORMAT_BASE_ROAD_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/base/road.pb.h>

#include <holo/map/proto/common/coordinate.pb.h>

#include <holo/map/proto/common/geo_box.pb.h>

#include <holo/map/proto/common/geo_line.pb.h>

#include <holo/map/proto/common/geo_point.pb.h>

#include <holo/map/proto/common/position.pb.h>

#include <holo/map/proto/common/multi_position.pb.h>

#include <holo/map/proto/base/speed_limit_info.pb.h>

#include <holo/map/proto/base/road_attribute.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/coordinate.h>

#include <holo/map/format/common/geo_box.h>

#include <holo/map/format/common/geo_line.h>

#include <holo/map/format/common/geo_point.h>

#include <holo/map/format/common/position.h>

#include <holo/map/format/common/multi_position.h>

#include <holo/map/format/base/speed_limit_info.h>

#include <holo/map/format/base/road_attribute.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  Road: public Base
{
public:

        
    enum RoadType
    {
        ROAD_TYPE_NO_SPECIAL=  0,  
        ROAD_TYPE_RAMP=  1,  
        ROAD_TYPE_ROUNDABOUT_ROAD=  2,  
        ROAD_TYPE_PARALLEL=  3,  
        ROAD_TYPE_SERVICE_ROAD=  4,  
        ROAD_TYPE_MAIN_ROAD=  5,  
        ROAD_TYPE_SQUARE=  6,  
        ROAD_TYPE_PEDESTRIAN_ZONE=  8,  
        ROAD_TYPE_PEDESTRIAN=  9,  
        ROAD_TYPE_ROUNDABOUT_INTERIOR=  10,  
        ROAD_TYPE_SLIP_ROAD=  11,  
        ROAD_TYPE_SPECIAL_TRAFFIC_FIGURE=  12,  
        ROAD_TYPE_BOUNDARY=  13,  
        ROAD_TYPE_PARKING_NORMAL=  14,  
        ROAD_TYPE_PARKING_WALK=  15,  
        ROAD_TYPE_PARKING_CONN_PARKING=  16,  
        ROAD_TYPE_PARKING_INTERNAL=  17,  
        ROAD_TYPE_PARKING_INTERNAL_CONN=  18,  
        ROAD_TYPE_PARKING_INTERNAL_CROSS=  19,  
        ROAD_TYPE_PARKING_EXTERNAL_CONN=  20,  
        ROAD_TYPE_PARKING_ENTRANCE_EXIT_CONN=  21,  
        ROAD_TYPE_PARKING_TURN_AROUND=  22,  
    };

        
    enum Direction
    {
        DIRECTION_UNDEFINED=  0,  
        DIRECTION_BIDIRECTIONAL=  1,  
        DIRECTION_POSITIVE_DIRECTION=  2,  
        DIRECTION_NEGATIVE_DIRECTION=  3,  
    };

        
    enum FuncClass
    {
        FUNC_CLASS_NOT_APPLICABLE=  0,  
        FUNC_CLASS_CLASS_1=  1,  
        FUNC_CLASS_CLASS_2=  2,  
        FUNC_CLASS_CLASS_3=  3,  
        FUNC_CLASS_CLASS_4=  4,  
        FUNC_CLASS_CLASS_5=  5,  
        FUNC_CLASS_CLASS_11=  11,  
    };

        
    enum RoadTypeV2
    {
        ROAD_TYPE_V2_UNDEFINED=  0,  
        ROAD_TYPE_V2_EXPRESSWAY=  1,  
        ROAD_TYPE_V2_FREEWAY=  2,  
        ROAD_TYPE_V2_ENTRY_RAMP=  3,  
        ROAD_TYPE_V2_EXIT_RAMP=  4,  
        ROAD_TYPE_V2_RAMP=  5,  
        ROAD_TYPE_V2_JCT=  6,  
        ROAD_TYPE_V2_SERVICE=  7,  
        ROAD_TYPE_V2_REGULAR=  8,  
        ROAD_TYPE_V2_AUXILIARY=  9,  
        ROAD_TYPE_V2_INTERSECTION=  10,  
        ROAD_TYPE_V2_ROUNDABOUT=  11,  
        ROAD_TYPE_V2_PEDESTRIAN=  12,  
        ROAD_TYPE_V2_PARALLEL=  13,  
        ROAD_TYPE_V2_SERVICE_AREA=  14,  
        ROAD_TYPE_V2_TOLL_BOOTH=  15,  
        ROAD_TYPE_V2_RESERVED_1=  250,  
        ROAD_TYPE_V2_RESERVED_2=  251,  
        ROAD_TYPE_V2_RESERVED_3=  252,  
        ROAD_TYPE_V2_RESERVED_4=  253,  
        ROAD_TYPE_V2_RESERVED_5=  254,  
        ROAD_TYPE_V2_OTHERS=  255,  
    };

        
    enum RoadClass
    {
        ROAD_CLASS_UNKNOWN=  0,  
        ROAD_CLASS_EXPRESS=  1,  
        ROAD_CLASS_FREEWAY=  2,  
        ROAD_CLASS_STATE_ROAD=  3,  
        ROAD_CLASS_PROVINCE_ROAD=  4,  
        ROAD_CLASS_CITY_MAIN_ROAD=  5,  
        ROAD_CLASS_CITY_SECONDARY_ROAD=  6,  
        ROAD_CLASS_CITY_BRANCH_ROAD=  7,  
        ROAD_CLASS_CITY_AUXILIARY_ROAD=  8,  
        ROAD_CLASS_RESERVE_1=  9,  
        ROAD_CLASS_RESERVE_2=  10,  
        ROAD_CLASS_RESERVE_3=  11,  
        ROAD_CLASS_RESERVE_4=  12,  
        ROAD_CLASS_RESERVE_5=  13,  
        ROAD_CLASS_COUNTY_ROAD=  14,  
        ROAD_CLASS_TOWNSHIP_ROAD=  15,  
        ROAD_CLASS_RESERVE_6=  16,  
        ROAD_CLASS_RESERVE_7=  17,  
        ROAD_CLASS_RESERVE_8=  18,  
        ROAD_CLASS_RESERVE_9=  19,  
        ROAD_CLASS_OTHERS=  255,  
    };

    static const ::std::map<::std::string, RoadType>& ENUMSTR_ROADTYPE() 
    { 
        static const ::std::map<::std::string, RoadType> data{
        { "NO_SPECIAL", RoadType::ROAD_TYPE_NO_SPECIAL },
        { "RAMP", RoadType::ROAD_TYPE_RAMP },
        { "ROUNDABOUT_ROAD", RoadType::ROAD_TYPE_ROUNDABOUT_ROAD },
        { "PARALLEL", RoadType::ROAD_TYPE_PARALLEL },
        { "SERVICE_ROAD", RoadType::ROAD_TYPE_SERVICE_ROAD },
        { "MAIN_ROAD", RoadType::ROAD_TYPE_MAIN_ROAD },
        { "SQUARE", RoadType::ROAD_TYPE_SQUARE },
        { "PEDESTRIAN_ZONE", RoadType::ROAD_TYPE_PEDESTRIAN_ZONE },
        { "PEDESTRIAN", RoadType::ROAD_TYPE_PEDESTRIAN },
        { "ROUNDABOUT_INTERIOR", RoadType::ROAD_TYPE_ROUNDABOUT_INTERIOR },
        { "SLIP_ROAD", RoadType::ROAD_TYPE_SLIP_ROAD },
        { "SPECIAL_TRAFFIC_FIGURE", RoadType::ROAD_TYPE_SPECIAL_TRAFFIC_FIGURE },
        { "BOUNDARY", RoadType::ROAD_TYPE_BOUNDARY },
        { "PARKING_NORMAL", RoadType::ROAD_TYPE_PARKING_NORMAL },
        { "PARKING_WALK", RoadType::ROAD_TYPE_PARKING_WALK },
        { "PARKING_CONN_PARKING", RoadType::ROAD_TYPE_PARKING_CONN_PARKING },
        { "PARKING_INTERNAL", RoadType::ROAD_TYPE_PARKING_INTERNAL },
        { "PARKING_INTERNAL_CONN", RoadType::ROAD_TYPE_PARKING_INTERNAL_CONN },
        { "PARKING_INTERNAL_CROSS", RoadType::ROAD_TYPE_PARKING_INTERNAL_CROSS },
        { "PARKING_EXTERNAL_CONN", RoadType::ROAD_TYPE_PARKING_EXTERNAL_CONN },
        { "PARKING_ENTRANCE_EXIT_CONN", RoadType::ROAD_TYPE_PARKING_ENTRANCE_EXIT_CONN },
        { "PARKING_TURN_AROUND", RoadType::ROAD_TYPE_PARKING_TURN_AROUND }};
        return data;
    }

    static const ::std::map<::std::string, Direction>& ENUMSTR_DIRECTION() 
    { 
        static const ::std::map<::std::string, Direction> data{
        { "UNDEFINED", Direction::DIRECTION_UNDEFINED },
        { "BIDIRECTIONAL", Direction::DIRECTION_BIDIRECTIONAL },
        { "POSITIVE_DIRECTION", Direction::DIRECTION_POSITIVE_DIRECTION },
        { "NEGATIVE_DIRECTION", Direction::DIRECTION_NEGATIVE_DIRECTION }};
        return data;
    }

    static const ::std::map<::std::string, FuncClass>& ENUMSTR_FUNCCLASS() 
    { 
        static const ::std::map<::std::string, FuncClass> data{
        { "NOT_APPLICABLE", FuncClass::FUNC_CLASS_NOT_APPLICABLE },
        { "CLASS_1", FuncClass::FUNC_CLASS_CLASS_1 },
        { "CLASS_2", FuncClass::FUNC_CLASS_CLASS_2 },
        { "CLASS_3", FuncClass::FUNC_CLASS_CLASS_3 },
        { "CLASS_4", FuncClass::FUNC_CLASS_CLASS_4 },
        { "CLASS_5", FuncClass::FUNC_CLASS_CLASS_5 },
        { "CLASS_11", FuncClass::FUNC_CLASS_CLASS_11 }};
        return data;
    }

    static const ::std::map<::std::string, RoadTypeV2>& ENUMSTR_ROADTYPEV2() 
    { 
        static const ::std::map<::std::string, RoadTypeV2> data{
        { "UNDEFINED", RoadTypeV2::ROAD_TYPE_V2_UNDEFINED },
        { "EXPRESSWAY", RoadTypeV2::ROAD_TYPE_V2_EXPRESSWAY },
        { "FREEWAY", RoadTypeV2::ROAD_TYPE_V2_FREEWAY },
        { "ENTRY_RAMP", RoadTypeV2::ROAD_TYPE_V2_ENTRY_RAMP },
        { "EXIT_RAMP", RoadTypeV2::ROAD_TYPE_V2_EXIT_RAMP },
        { "RAMP", RoadTypeV2::ROAD_TYPE_V2_RAMP },
        { "JCT", RoadTypeV2::ROAD_TYPE_V2_JCT },
        { "SERVICE", RoadTypeV2::ROAD_TYPE_V2_SERVICE },
        { "REGULAR", RoadTypeV2::ROAD_TYPE_V2_REGULAR },
        { "AUXILIARY", RoadTypeV2::ROAD_TYPE_V2_AUXILIARY },
        { "INTERSECTION", RoadTypeV2::ROAD_TYPE_V2_INTERSECTION },
        { "ROUNDABOUT", RoadTypeV2::ROAD_TYPE_V2_ROUNDABOUT },
        { "PEDESTRIAN", RoadTypeV2::ROAD_TYPE_V2_PEDESTRIAN },
        { "PARALLEL", RoadTypeV2::ROAD_TYPE_V2_PARALLEL },
        { "SERVICE_AREA", RoadTypeV2::ROAD_TYPE_V2_SERVICE_AREA },
        { "TOLL_BOOTH", RoadTypeV2::ROAD_TYPE_V2_TOLL_BOOTH },
        { "RESERVED_1", RoadTypeV2::ROAD_TYPE_V2_RESERVED_1 },
        { "RESERVED_2", RoadTypeV2::ROAD_TYPE_V2_RESERVED_2 },
        { "RESERVED_3", RoadTypeV2::ROAD_TYPE_V2_RESERVED_3 },
        { "RESERVED_4", RoadTypeV2::ROAD_TYPE_V2_RESERVED_4 },
        { "RESERVED_5", RoadTypeV2::ROAD_TYPE_V2_RESERVED_5 },
        { "OTHERS", RoadTypeV2::ROAD_TYPE_V2_OTHERS }};
        return data;
    }

    static const ::std::map<::std::string, RoadClass>& ENUMSTR_ROADCLASS() 
    { 
        static const ::std::map<::std::string, RoadClass> data{
        { "UNKNOWN", RoadClass::ROAD_CLASS_UNKNOWN },
        { "EXPRESS", RoadClass::ROAD_CLASS_EXPRESS },
        { "FREEWAY", RoadClass::ROAD_CLASS_FREEWAY },
        { "STATE_ROAD", RoadClass::ROAD_CLASS_STATE_ROAD },
        { "PROVINCE_ROAD", RoadClass::ROAD_CLASS_PROVINCE_ROAD },
        { "CITY_MAIN_ROAD", RoadClass::ROAD_CLASS_CITY_MAIN_ROAD },
        { "CITY_SECONDARY_ROAD", RoadClass::ROAD_CLASS_CITY_SECONDARY_ROAD },
        { "CITY_BRANCH_ROAD", RoadClass::ROAD_CLASS_CITY_BRANCH_ROAD },
        { "CITY_AUXILIARY_ROAD", RoadClass::ROAD_CLASS_CITY_AUXILIARY_ROAD },
        { "RESERVE_1", RoadClass::ROAD_CLASS_RESERVE_1 },
        { "RESERVE_2", RoadClass::ROAD_CLASS_RESERVE_2 },
        { "RESERVE_3", RoadClass::ROAD_CLASS_RESERVE_3 },
        { "RESERVE_4", RoadClass::ROAD_CLASS_RESERVE_4 },
        { "RESERVE_5", RoadClass::ROAD_CLASS_RESERVE_5 },
        { "COUNTY_ROAD", RoadClass::ROAD_CLASS_COUNTY_ROAD },
        { "TOWNSHIP_ROAD", RoadClass::ROAD_CLASS_TOWNSHIP_ROAD },
        { "RESERVE_6", RoadClass::ROAD_CLASS_RESERVE_6 },
        { "RESERVE_7", RoadClass::ROAD_CLASS_RESERVE_7 },
        { "RESERVE_8", RoadClass::ROAD_CLASS_RESERVE_8 },
        { "RESERVE_9", RoadClass::ROAD_CLASS_RESERVE_9 },
        { "OTHERS", RoadClass::ROAD_CLASS_OTHERS }};
        return data;
    }


private:
    ::std::uint64_t road_id_; 
    RoadType road_type_; 
    Direction direction_; 
    FuncClass func_class_; 
    ::std::vector<::std::uint64_t> lane_groups_; 
    ::std::vector<::std::uint64_t> pre_connected_roads_; 
    ::std::vector<::std::uint64_t> suc_connected_roads_; 
    ::std::vector<::std::uint64_t> object_ids_; 
    ::std::vector<::std::uint64_t> left_road_boundaries_; 
    ::std::vector<::std::uint64_t> right_road_boundaries_; 
    RoadTypeV2 road_type_v2_; 
    RoadClass road_class_; 
    ::std::uint32_t road_length_cm_; 
    ::std::vector<::std::uint64_t> valid_signals_; 
    ::std::vector<SpeedLimitInfo> lane_speed_limit_; 
    ::std::vector<RoadAttribute> attributes_; 
    ::std::vector<::std::uint64_t> tile_ids_; 
    ::std::uint64_t intersection_id_; 
    ::std::uint64_t begin_intersection_id_; 
    ::std::uint64_t end_intersection_id_; 
    ::std::uint32_t level_; 
    ::std::uint64_t object_parking_lot_id_; 
    ::std::uint64_t object_parking_floor_id_; 
    ::std::string road_name_; 
    Coordinate coordinate_; 
    ::std::uint32_t zone_id_; 
    ::std::uint32_t extra_zone_id_; 
    bool south_flag_; 
    GeoBox region_; 
    ::std::map<::std::uint32_t, GeoBox> extra_region_; 
    ::std::vector<GeoPoint> geometry_points_; 
    ::std::map<::std::uint32_t, GeoLine> extra_geometry_points_; 
    ::std::vector<Position> positions_; 
    ::std::map<::std::uint32_t, MultiPosition> extra_positions_; 

private:
    void DecodeProto(const ::holo::map::proto::base::Road& _proto_handler);
    ::holo::map::proto::base::Road EncodeProto();

public:
    Road();
    explicit Road(const ::holo::map::proto::base::Road& _proto_handler);
    // init all format data
    Road(const ::std::uint64_t _road_id,const RoadType& _road_type,const Direction& _direction,const FuncClass& _func_class,const ::std::vector<::std::uint64_t>& _lane_groups,const ::std::vector<::std::uint64_t>& _pre_connected_roads,const ::std::vector<::std::uint64_t>& _suc_connected_roads,const ::std::vector<::std::uint64_t>& _object_ids,const ::std::vector<::std::uint64_t>& _left_road_boundaries,const ::std::vector<::std::uint64_t>& _right_road_boundaries,const RoadTypeV2& _road_type_v2,const RoadClass& _road_class,const ::std::uint32_t _road_length_cm,const ::std::vector<::std::uint64_t>& _valid_signals,const ::std::vector<SpeedLimitInfo>& _lane_speed_limit,const ::std::vector<RoadAttribute>& _attributes,const ::std::vector<::std::uint64_t>& _tile_ids,const ::std::uint64_t _intersection_id,const ::std::uint64_t _begin_intersection_id,const ::std::uint64_t _end_intersection_id,const ::std::uint32_t _level,const ::std::uint64_t _object_parking_lot_id,const ::std::uint64_t _object_parking_floor_id,const ::std::string& _road_name,const Coordinate& _coordinate,const ::std::uint32_t _zone_id,const ::std::uint32_t _extra_zone_id,const bool _south_flag,const GeoBox& _region,const ::std::map<::std::uint32_t, GeoBox>& _extra_region,const ::std::vector<GeoPoint>& _geometry_points,const ::std::map<::std::uint32_t, GeoLine>& _extra_geometry_points,const ::std::vector<Position>& _positions,const ::std::map<::std::uint32_t, MultiPosition>& _extra_positions);
    ~Road();

    bool operator==(const ::holo::map::format::Road& _other) const;
    Road& operator=(const ::holo::map::proto::base::Road& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::base::Road GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetRoadId() const
    {
        return road_id_;
    }
    void SetRoadId(const ::std::uint64_t _road_id)
    {
        road_id_ = _road_id;
    }

    const RoadType& GetRoadType() const
    {
        return road_type_;
    }
    void SetRoadType(const RoadType& _road_type)
    {
        road_type_ = _road_type;
    }

    const Direction& GetDirection() const
    {
        return direction_;
    }
    void SetDirection(const Direction& _direction)
    {
        direction_ = _direction;
    }

    const FuncClass& GetFuncClass() const
    {
        return func_class_;
    }
    void SetFuncClass(const FuncClass& _func_class)
    {
        func_class_ = _func_class;
    }

    const ::std::vector<::std::uint64_t>* GetPtrLaneGroups() const
    {
        return &lane_groups_;
    }
    void SetLaneGroups(const ::std::vector<::std::uint64_t>& _lane_groups)
    {
        lane_groups_ = _lane_groups;
    }

    const ::std::vector<::std::uint64_t>* GetPtrPreConnectedRoads() const
    {
        return &pre_connected_roads_;
    }
    void SetPreConnectedRoads(const ::std::vector<::std::uint64_t>& _pre_connected_roads)
    {
        pre_connected_roads_ = _pre_connected_roads;
    }

    const ::std::vector<::std::uint64_t>* GetPtrSucConnectedRoads() const
    {
        return &suc_connected_roads_;
    }
    void SetSucConnectedRoads(const ::std::vector<::std::uint64_t>& _suc_connected_roads)
    {
        suc_connected_roads_ = _suc_connected_roads;
    }

    const ::std::vector<::std::uint64_t>* GetPtrObjectIds() const
    {
        return &object_ids_;
    }
    void SetObjectIds(const ::std::vector<::std::uint64_t>& _object_ids)
    {
        object_ids_ = _object_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrLeftRoadBoundaries() const
    {
        return &left_road_boundaries_;
    }
    void SetLeftRoadBoundaries(const ::std::vector<::std::uint64_t>& _left_road_boundaries)
    {
        left_road_boundaries_ = _left_road_boundaries;
    }

    const ::std::vector<::std::uint64_t>* GetPtrRightRoadBoundaries() const
    {
        return &right_road_boundaries_;
    }
    void SetRightRoadBoundaries(const ::std::vector<::std::uint64_t>& _right_road_boundaries)
    {
        right_road_boundaries_ = _right_road_boundaries;
    }

    const RoadTypeV2& GetRoadTypeV2() const
    {
        return road_type_v2_;
    }
    void SetRoadTypeV2(const RoadTypeV2& _road_type_v2)
    {
        road_type_v2_ = _road_type_v2;
    }

    const RoadClass& GetRoadClass() const
    {
        return road_class_;
    }
    void SetRoadClass(const RoadClass& _road_class)
    {
        road_class_ = _road_class;
    }

    ::std::uint32_t GetRoadLengthCm() const
    {
        return road_length_cm_;
    }
    void SetRoadLengthCm(const ::std::uint32_t _road_length_cm)
    {
        road_length_cm_ = _road_length_cm;
    }

    const ::std::vector<::std::uint64_t>* GetPtrValidSignals() const
    {
        return &valid_signals_;
    }
    void SetValidSignals(const ::std::vector<::std::uint64_t>& _valid_signals)
    {
        valid_signals_ = _valid_signals;
    }

    const ::std::vector<SpeedLimitInfo>* GetPtrLaneSpeedLimit() const
    {
        return &lane_speed_limit_;
    }
    void SetLaneSpeedLimit(const ::std::vector<SpeedLimitInfo>& _lane_speed_limit)
    {
        lane_speed_limit_ = _lane_speed_limit;
    }

    const ::std::vector<RoadAttribute>* GetPtrAttributes() const
    {
        return &attributes_;
    }
    void SetAttributes(const ::std::vector<RoadAttribute>& _attributes)
    {
        attributes_ = _attributes;
    }

    const ::std::vector<::std::uint64_t>* GetPtrTileIds() const
    {
        return &tile_ids_;
    }
    void SetTileIds(const ::std::vector<::std::uint64_t>& _tile_ids)
    {
        tile_ids_ = _tile_ids;
    }

    ::std::uint64_t GetIntersectionId() const
    {
        return intersection_id_;
    }
    void SetIntersectionId(const ::std::uint64_t _intersection_id)
    {
        intersection_id_ = _intersection_id;
    }

    ::std::uint64_t GetBeginIntersectionId() const
    {
        return begin_intersection_id_;
    }
    void SetBeginIntersectionId(const ::std::uint64_t _begin_intersection_id)
    {
        begin_intersection_id_ = _begin_intersection_id;
    }

    ::std::uint64_t GetEndIntersectionId() const
    {
        return end_intersection_id_;
    }
    void SetEndIntersectionId(const ::std::uint64_t _end_intersection_id)
    {
        end_intersection_id_ = _end_intersection_id;
    }

    ::std::uint32_t GetLevel() const
    {
        return level_;
    }
    void SetLevel(const ::std::uint32_t _level)
    {
        level_ = _level;
    }

    ::std::uint64_t GetObjectParkingLotId() const
    {
        return object_parking_lot_id_;
    }
    void SetObjectParkingLotId(const ::std::uint64_t _object_parking_lot_id)
    {
        object_parking_lot_id_ = _object_parking_lot_id;
    }

    ::std::uint64_t GetObjectParkingFloorId() const
    {
        return object_parking_floor_id_;
    }
    void SetObjectParkingFloorId(const ::std::uint64_t _object_parking_floor_id)
    {
        object_parking_floor_id_ = _object_parking_floor_id;
    }

    const ::std::string& GetRoadName() const
    {
        return road_name_;
    }
    void SetRoadName(const ::std::string& _road_name)
    {
        road_name_ = _road_name;
    }

    const Coordinate& GetCoordinate() const
    {
        return coordinate_;
    }
    void SetCoordinate(const Coordinate& _coordinate)
    {
        coordinate_ = _coordinate;
    }

    ::std::uint32_t GetZoneId() const
    {
        return zone_id_;
    }
    void SetZoneId(const ::std::uint32_t _zone_id)
    {
        zone_id_ = _zone_id;
    }

    ::std::uint32_t GetExtraZoneId() const
    {
        return extra_zone_id_;
    }
    void SetExtraZoneId(const ::std::uint32_t _extra_zone_id)
    {
        extra_zone_id_ = _extra_zone_id;
    }

    bool GetSouthFlag() const
    {
        return south_flag_;
    }
    void SetSouthFlag(const bool _south_flag)
    {
        south_flag_ = _south_flag;
    }

    const ::std::map<::std::uint32_t, GeoBox>* GetPtrExtraRegion() const
    {
        return &extra_region_;
    }
    void SetExtraRegion(const ::std::map<::std::uint32_t, GeoBox>& _extra_region)
    {
        extra_region_ = _extra_region;
    }

    const ::std::map<::std::uint32_t, GeoLine>* GetPtrExtraGeometryPoints() const
    {
        return &extra_geometry_points_;
    }
    void SetExtraGeometryPoints(const ::std::map<::std::uint32_t, GeoLine>& _extra_geometry_points)
    {
        extra_geometry_points_ = _extra_geometry_points;
    }

    const ::std::map<::std::uint32_t, MultiPosition>* GetPtrExtraPositions() const
    {
        return &extra_positions_;
    }
    void SetExtraPositions(const ::std::map<::std::uint32_t, MultiPosition>& _extra_positions)
    {
        extra_positions_ = _extra_positions;
    }


    void ClearLaneGroups()
    {
        lane_groups_.clear();
    }
    void AddLaneGroupsElement(const ::std::uint64_t& _value)
    {
        lane_groups_.push_back(_value);
    }
    void UniqueAddLaneGroupsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(lane_groups_, _value);
    }

    void ClearPreConnectedRoads()
    {
        pre_connected_roads_.clear();
    }
    void AddPreConnectedRoadsElement(const ::std::uint64_t& _value)
    {
        pre_connected_roads_.push_back(_value);
    }
    void UniqueAddPreConnectedRoadsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(pre_connected_roads_, _value);
    }

    void ClearSucConnectedRoads()
    {
        suc_connected_roads_.clear();
    }
    void AddSucConnectedRoadsElement(const ::std::uint64_t& _value)
    {
        suc_connected_roads_.push_back(_value);
    }
    void UniqueAddSucConnectedRoadsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(suc_connected_roads_, _value);
    }

    void ClearObjectIds()
    {
        object_ids_.clear();
    }
    void AddObjectIdsElement(const ::std::uint64_t& _value)
    {
        object_ids_.push_back(_value);
    }
    void UniqueAddObjectIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(object_ids_, _value);
    }

    void ClearLeftRoadBoundaries()
    {
        left_road_boundaries_.clear();
    }
    void AddLeftRoadBoundariesElement(const ::std::uint64_t& _value)
    {
        left_road_boundaries_.push_back(_value);
    }
    void UniqueAddLeftRoadBoundariesElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(left_road_boundaries_, _value);
    }

    void ClearRightRoadBoundaries()
    {
        right_road_boundaries_.clear();
    }
    void AddRightRoadBoundariesElement(const ::std::uint64_t& _value)
    {
        right_road_boundaries_.push_back(_value);
    }
    void UniqueAddRightRoadBoundariesElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(right_road_boundaries_, _value);
    }

    void ClearValidSignals()
    {
        valid_signals_.clear();
    }
    void AddValidSignalsElement(const ::std::uint64_t& _value)
    {
        valid_signals_.push_back(_value);
    }
    void UniqueAddValidSignalsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(valid_signals_, _value);
    }

    void ClearLaneSpeedLimit()
    {
        lane_speed_limit_.clear();
    }
    void AddLaneSpeedLimitElement(const SpeedLimitInfo& _value)
    {
        lane_speed_limit_.push_back(_value);
    }
    void UniqueAddLaneSpeedLimitElements(const ::std::vector<SpeedLimitInfo>& _value)
    {
        UniqueAppend(lane_speed_limit_, _value);
    }

    void ClearAttributes()
    {
        attributes_.clear();
    }
    void AddAttributesElement(const RoadAttribute& _value)
    {
        attributes_.push_back(_value);
    }
    void UniqueAddAttributesElements(const ::std::vector<RoadAttribute>& _value)
    {
        UniqueAppend(attributes_, _value);
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

    void ClearGeometryPoints()
    {
        geometry_points_.clear();
    }
    void AddGeometryPointsElement(const GeoPoint& _value)
    {
        geometry_points_.push_back(_value);
    }
    void UniqueAddGeometryPointsElements(const ::std::vector<GeoPoint>& _value)
    {
        UniqueAppend(geometry_points_, _value);
    }

    void ClearPositions()
    {
        positions_.clear();
    }
    void AddPositionsElement(const Position& _value)
    {
        positions_.push_back(_value);
    }
    void UniqueAddPositionsElements(const ::std::vector<Position>& _value)
    {
        UniqueAppend(positions_, _value);
    }


    const GeoBox& GetRegion() const;
    void SetRegion(const GeoBox& _region)
    {
        this->region_ = _region;
    }


    const ::std::vector<GeoPoint>* GetPtrGeometryPoints() const;
    void SetGeometryPoints(const ::std::vector<GeoPoint>& _geometry_points)
    {
        this->geometry_points_ = _geometry_points;
    }


    const ::std::vector<Position>* GetPtrPositions() const;
    void SetPositions(const ::std::vector<Position>& _positions)
    {
        this->positions_ = _positions;
    }



};  // class Road

typedef ::std::shared_ptr<Road> PtrRoad;
typedef const ::std::vector<Road>* ConstRawPtrVecRoad;
typedef ::std::vector<Road>* RawPtrVecRoad;
typedef ::std::shared_ptr<Road const> ConstPtrRoad;
typedef ::std::shared_ptr<::std::vector<Road> const> ConstPtrVecRoad;
typedef ::std::unordered_map<::std::uint64_t, PtrRoad> HashmapRoad;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_BASE_ROAD_H_