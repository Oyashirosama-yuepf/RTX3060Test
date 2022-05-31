/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_group.h
 * @brief Auto generated code for LaneGroup format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_BASE_LANE_GROUP_H_
#define HOLO_MAP_FORMAT_BASE_LANE_GROUP_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/base/lane_group.pb.h>

#include <holo/map/proto/common/coordinate.pb.h>

#include <holo/map/proto/common/geo_box.pb.h>

#include <holo/map/proto/common/geo_line.pb.h>

#include <holo/map/proto/common/geo_point.pb.h>

#include <holo/map/proto/base/lane_group_attribute.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/coordinate.h>

#include <holo/map/format/common/geo_box.h>

#include <holo/map/format/common/geo_line.h>

#include <holo/map/format/common/geo_point.h>

#include <holo/map/format/base/lane_group_attribute.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  LaneGroup: public Base
{
public:

        
    enum AssociationType
    {
        ASSOCIATION_TYPE_UNDEFINED=  0,  
        ASSOCIATION_TYPE_SAME_TRAVEL_DIRECTION=  1,  
        ASSOCIATION_TYPE_OPPOSITE_TRAVEL_DIRECTION=  2,  
        ASSOCIATION_TYPE_INTERSECTION=  3,  
    };

        
    enum LaneGroupType
    {
        LANE_GROUP_TYPE_UNDEFINED=  0,  
        LANE_GROUP_TYPE_EXPRESSWAY=  1,  
        LANE_GROUP_TYPE_FREEWAY=  2,  
        LANE_GROUP_TYPE_ENTRY_RAMP=  3,  
        LANE_GROUP_TYPE_EXIT_RAMP=  4,  
        LANE_GROUP_TYPE_RAMP=  5,  
        LANE_GROUP_TYPE_JCT=  6,  
        LANE_GROUP_TYPE_SERVICE=  7,  
        LANE_GROUP_TYPE_REGULAR=  8,  
        LANE_GROUP_TYPE_AUXILIARY=  9,  
        LANE_GROUP_TYPE_INTERSECTION=  10,  
        LANE_GROUP_TYPE_ROUNDABOUT=  11,  
        LANE_GROUP_TYPE_PEDESTRIAN=  12,  
        LANE_GROUP_TYPE_PARALLEL=  13,  
        LANE_GROUP_TYPE_SERVICE_AREA=  14,  
        LANE_GROUP_TYPE_TOLL_BOOTH=  15,  
        LANE_GROUP_TYPE_RESERVED_1=  250,  
        LANE_GROUP_TYPE_RESERVED_2=  251,  
        LANE_GROUP_TYPE_RESERVED_3=  252,  
        LANE_GROUP_TYPE_RESERVED_4=  253,  
        LANE_GROUP_TYPE_RESERVED_5=  254,  
        LANE_GROUP_TYPE_OTHERS=  255,  
    };

        
    enum LaneGroupClass
    {
        LANE_GROUP_CLASS_UNKNOWN=  0,  
        LANE_GROUP_CLASS_EXPRESS=  1,  
        LANE_GROUP_CLASS_FREEWAY=  2,  
        LANE_GROUP_CLASS_STATE_ROAD=  3,  
        LANE_GROUP_CLASS_PROVINCE_ROAD=  4,  
        LANE_GROUP_CLASS_CITY_MAIN_ROAD=  5,  
        LANE_GROUP_CLASS_CITY_SECONDARY_ROAD=  6,  
        LANE_GROUP_CLASS_CITY_BRANCH_ROAD=  7,  
        LANE_GROUP_CLASS_RESERVE_1=  8,  
        LANE_GROUP_CLASS_RESERVE_2=  9,  
        LANE_GROUP_CLASS_RESERVE_3=  10,  
        LANE_GROUP_CLASS_RESERVE_4=  11,  
        LANE_GROUP_CLASS_RESERVE_5=  12,  
        LANE_GROUP_CLASS_COUNTY_ROAD=  13,  
        LANE_GROUP_CLASS_TOWNSHIP_ROAD=  14,  
        LANE_GROUP_CLASS_RESERVE_6=  15,  
        LANE_GROUP_CLASS_RESERVE_7=  16,  
        LANE_GROUP_CLASS_RESERVE_8=  17,  
        LANE_GROUP_CLASS_RESERVE_9=  18,  
        LANE_GROUP_CLASS_OTHERS=  255,  
    };

    static const ::std::map<::std::string, AssociationType>& ENUMSTR_ASSOCIATIONTYPE() 
    { 
        static const ::std::map<::std::string, AssociationType> data{
        { "UNDEFINED", AssociationType::ASSOCIATION_TYPE_UNDEFINED },
        { "SAME_TRAVEL_DIRECTION", AssociationType::ASSOCIATION_TYPE_SAME_TRAVEL_DIRECTION },
        { "OPPOSITE_TRAVEL_DIRECTION", AssociationType::ASSOCIATION_TYPE_OPPOSITE_TRAVEL_DIRECTION },
        { "INTERSECTION", AssociationType::ASSOCIATION_TYPE_INTERSECTION }};
        return data;
    }

    static const ::std::map<::std::string, LaneGroupType>& ENUMSTR_LANEGROUPTYPE() 
    { 
        static const ::std::map<::std::string, LaneGroupType> data{
        { "UNDEFINED", LaneGroupType::LANE_GROUP_TYPE_UNDEFINED },
        { "EXPRESSWAY", LaneGroupType::LANE_GROUP_TYPE_EXPRESSWAY },
        { "FREEWAY", LaneGroupType::LANE_GROUP_TYPE_FREEWAY },
        { "ENTRY_RAMP", LaneGroupType::LANE_GROUP_TYPE_ENTRY_RAMP },
        { "EXIT_RAMP", LaneGroupType::LANE_GROUP_TYPE_EXIT_RAMP },
        { "RAMP", LaneGroupType::LANE_GROUP_TYPE_RAMP },
        { "JCT", LaneGroupType::LANE_GROUP_TYPE_JCT },
        { "SERVICE", LaneGroupType::LANE_GROUP_TYPE_SERVICE },
        { "REGULAR", LaneGroupType::LANE_GROUP_TYPE_REGULAR },
        { "AUXILIARY", LaneGroupType::LANE_GROUP_TYPE_AUXILIARY },
        { "INTERSECTION", LaneGroupType::LANE_GROUP_TYPE_INTERSECTION },
        { "ROUNDABOUT", LaneGroupType::LANE_GROUP_TYPE_ROUNDABOUT },
        { "PEDESTRIAN", LaneGroupType::LANE_GROUP_TYPE_PEDESTRIAN },
        { "PARALLEL", LaneGroupType::LANE_GROUP_TYPE_PARALLEL },
        { "SERVICE_AREA", LaneGroupType::LANE_GROUP_TYPE_SERVICE_AREA },
        { "TOLL_BOOTH", LaneGroupType::LANE_GROUP_TYPE_TOLL_BOOTH },
        { "RESERVED_1", LaneGroupType::LANE_GROUP_TYPE_RESERVED_1 },
        { "RESERVED_2", LaneGroupType::LANE_GROUP_TYPE_RESERVED_2 },
        { "RESERVED_3", LaneGroupType::LANE_GROUP_TYPE_RESERVED_3 },
        { "RESERVED_4", LaneGroupType::LANE_GROUP_TYPE_RESERVED_4 },
        { "RESERVED_5", LaneGroupType::LANE_GROUP_TYPE_RESERVED_5 },
        { "OTHERS", LaneGroupType::LANE_GROUP_TYPE_OTHERS }};
        return data;
    }

    static const ::std::map<::std::string, LaneGroupClass>& ENUMSTR_LANEGROUPCLASS() 
    { 
        static const ::std::map<::std::string, LaneGroupClass> data{
        { "UNKNOWN", LaneGroupClass::LANE_GROUP_CLASS_UNKNOWN },
        { "EXPRESS", LaneGroupClass::LANE_GROUP_CLASS_EXPRESS },
        { "FREEWAY", LaneGroupClass::LANE_GROUP_CLASS_FREEWAY },
        { "STATE_ROAD", LaneGroupClass::LANE_GROUP_CLASS_STATE_ROAD },
        { "PROVINCE_ROAD", LaneGroupClass::LANE_GROUP_CLASS_PROVINCE_ROAD },
        { "CITY_MAIN_ROAD", LaneGroupClass::LANE_GROUP_CLASS_CITY_MAIN_ROAD },
        { "CITY_SECONDARY_ROAD", LaneGroupClass::LANE_GROUP_CLASS_CITY_SECONDARY_ROAD },
        { "CITY_BRANCH_ROAD", LaneGroupClass::LANE_GROUP_CLASS_CITY_BRANCH_ROAD },
        { "RESERVE_1", LaneGroupClass::LANE_GROUP_CLASS_RESERVE_1 },
        { "RESERVE_2", LaneGroupClass::LANE_GROUP_CLASS_RESERVE_2 },
        { "RESERVE_3", LaneGroupClass::LANE_GROUP_CLASS_RESERVE_3 },
        { "RESERVE_4", LaneGroupClass::LANE_GROUP_CLASS_RESERVE_4 },
        { "RESERVE_5", LaneGroupClass::LANE_GROUP_CLASS_RESERVE_5 },
        { "COUNTY_ROAD", LaneGroupClass::LANE_GROUP_CLASS_COUNTY_ROAD },
        { "TOWNSHIP_ROAD", LaneGroupClass::LANE_GROUP_CLASS_TOWNSHIP_ROAD },
        { "RESERVE_6", LaneGroupClass::LANE_GROUP_CLASS_RESERVE_6 },
        { "RESERVE_7", LaneGroupClass::LANE_GROUP_CLASS_RESERVE_7 },
        { "RESERVE_8", LaneGroupClass::LANE_GROUP_CLASS_RESERVE_8 },
        { "RESERVE_9", LaneGroupClass::LANE_GROUP_CLASS_RESERVE_9 },
        { "OTHERS", LaneGroupClass::LANE_GROUP_CLASS_OTHERS }};
        return data;
    }


private:
    ::std::uint64_t lane_group_id_; 
    ::std::vector<::std::uint64_t> lanes_; 
    ::std::vector<::std::uint64_t> preceding_lane_group_ids_; 
    ::std::vector<::std::uint64_t> succeeding_lane_group_ids_; 
    ::std::uint64_t left_boundary_; 
    ::std::uint64_t right_boundary_; 
    ::std::vector<::std::uint64_t> associated_lane_group_ids_; 
    AssociationType association_type_; 
    LaneGroupType lane_group_type_; 
    ::std::uint64_t intersection_id_; 
    LaneGroupClass lane_group_class_; 
    ::std::vector<LaneGroupAttribute> lane_group_attributes_; 
    ::std::uint64_t begin_intersection_id_; 
    ::std::uint64_t end_intersection_id_; 
    ::std::uint32_t level_; 
    bool is_intersection_lane_group_; 
    ::std::uint64_t road_id_; 
    ::std::vector<::std::uint64_t> tile_ids_; 
    ::std::vector<::std::uint64_t> all_lane_boundaries_; 
    ::std::vector<::std::uint64_t> trajectory_ids_; 
    ::std::uint64_t adas_id_; 
    ::std::uint32_t lane_group_length_cm_; 
    ::std::uint64_t object_parking_lot_id_; 
    ::std::uint64_t object_parking_floor_id_; 
    Coordinate coordinate_; 
    ::std::uint32_t zone_id_; 
    ::std::uint32_t extra_zone_id_; 
    bool south_flag_; 
    GeoBox region_; 
    ::std::map<::std::uint32_t, GeoBox> extra_region_; 
    ::std::vector<GeoPoint> geometry_points_; 
    ::std::map<::std::uint32_t, GeoLine> extra_geometry_points_; 

private:
    void DecodeProto(const ::holo::map::proto::base::LaneGroup& _proto_handler);
    ::holo::map::proto::base::LaneGroup EncodeProto();

public:
    LaneGroup();
    explicit LaneGroup(const ::holo::map::proto::base::LaneGroup& _proto_handler);
    // init all format data
    LaneGroup(const ::std::uint64_t _lane_group_id,const ::std::vector<::std::uint64_t>& _lanes,const ::std::vector<::std::uint64_t>& _preceding_lane_group_ids,const ::std::vector<::std::uint64_t>& _succeeding_lane_group_ids,const ::std::uint64_t _left_boundary,const ::std::uint64_t _right_boundary,const ::std::vector<::std::uint64_t>& _associated_lane_group_ids,const AssociationType& _association_type,const LaneGroupType& _lane_group_type,const ::std::uint64_t _intersection_id,const LaneGroupClass& _lane_group_class,const ::std::vector<LaneGroupAttribute>& _lane_group_attributes,const ::std::uint64_t _begin_intersection_id,const ::std::uint64_t _end_intersection_id,const ::std::uint32_t _level,const bool _is_intersection_lane_group,const ::std::uint64_t _road_id,const ::std::vector<::std::uint64_t>& _tile_ids,const ::std::vector<::std::uint64_t>& _all_lane_boundaries,const ::std::vector<::std::uint64_t>& _trajectory_ids,const ::std::uint64_t _adas_id,const ::std::uint32_t _lane_group_length_cm,const ::std::uint64_t _object_parking_lot_id,const ::std::uint64_t _object_parking_floor_id,const Coordinate& _coordinate,const ::std::uint32_t _zone_id,const ::std::uint32_t _extra_zone_id,const bool _south_flag,const GeoBox& _region,const ::std::map<::std::uint32_t, GeoBox>& _extra_region,const ::std::vector<GeoPoint>& _geometry_points,const ::std::map<::std::uint32_t, GeoLine>& _extra_geometry_points);
    ~LaneGroup();

    bool operator==(const ::holo::map::format::LaneGroup& _other) const;
    LaneGroup& operator=(const ::holo::map::proto::base::LaneGroup& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::base::LaneGroup GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetLaneGroupId() const
    {
        return lane_group_id_;
    }
    void SetLaneGroupId(const ::std::uint64_t _lane_group_id)
    {
        lane_group_id_ = _lane_group_id;
    }

    const ::std::vector<::std::uint64_t>* GetPtrLanes() const
    {
        return &lanes_;
    }
    void SetLanes(const ::std::vector<::std::uint64_t>& _lanes)
    {
        lanes_ = _lanes;
    }

    const ::std::vector<::std::uint64_t>* GetPtrPrecedingLaneGroupIds() const
    {
        return &preceding_lane_group_ids_;
    }
    void SetPrecedingLaneGroupIds(const ::std::vector<::std::uint64_t>& _preceding_lane_group_ids)
    {
        preceding_lane_group_ids_ = _preceding_lane_group_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrSucceedingLaneGroupIds() const
    {
        return &succeeding_lane_group_ids_;
    }
    void SetSucceedingLaneGroupIds(const ::std::vector<::std::uint64_t>& _succeeding_lane_group_ids)
    {
        succeeding_lane_group_ids_ = _succeeding_lane_group_ids;
    }

    ::std::uint64_t GetLeftBoundary() const
    {
        return left_boundary_;
    }
    void SetLeftBoundary(const ::std::uint64_t _left_boundary)
    {
        left_boundary_ = _left_boundary;
    }

    ::std::uint64_t GetRightBoundary() const
    {
        return right_boundary_;
    }
    void SetRightBoundary(const ::std::uint64_t _right_boundary)
    {
        right_boundary_ = _right_boundary;
    }

    const ::std::vector<::std::uint64_t>* GetPtrAssociatedLaneGroupIds() const
    {
        return &associated_lane_group_ids_;
    }
    void SetAssociatedLaneGroupIds(const ::std::vector<::std::uint64_t>& _associated_lane_group_ids)
    {
        associated_lane_group_ids_ = _associated_lane_group_ids;
    }

    const AssociationType& GetAssociationType() const
    {
        return association_type_;
    }
    void SetAssociationType(const AssociationType& _association_type)
    {
        association_type_ = _association_type;
    }

    const LaneGroupType& GetLaneGroupType() const
    {
        return lane_group_type_;
    }
    void SetLaneGroupType(const LaneGroupType& _lane_group_type)
    {
        lane_group_type_ = _lane_group_type;
    }

    ::std::uint64_t GetIntersectionId() const
    {
        return intersection_id_;
    }
    void SetIntersectionId(const ::std::uint64_t _intersection_id)
    {
        intersection_id_ = _intersection_id;
    }

    const LaneGroupClass& GetLaneGroupClass() const
    {
        return lane_group_class_;
    }
    void SetLaneGroupClass(const LaneGroupClass& _lane_group_class)
    {
        lane_group_class_ = _lane_group_class;
    }

    const ::std::vector<LaneGroupAttribute>* GetPtrLaneGroupAttributes() const
    {
        return &lane_group_attributes_;
    }
    void SetLaneGroupAttributes(const ::std::vector<LaneGroupAttribute>& _lane_group_attributes)
    {
        lane_group_attributes_ = _lane_group_attributes;
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

    bool GetIsIntersectionLaneGroup() const
    {
        return is_intersection_lane_group_;
    }
    void SetIsIntersectionLaneGroup(const bool _is_intersection_lane_group)
    {
        is_intersection_lane_group_ = _is_intersection_lane_group;
    }

    ::std::uint64_t GetRoadId() const
    {
        return road_id_;
    }
    void SetRoadId(const ::std::uint64_t _road_id)
    {
        road_id_ = _road_id;
    }

    const ::std::vector<::std::uint64_t>* GetPtrTileIds() const
    {
        return &tile_ids_;
    }
    void SetTileIds(const ::std::vector<::std::uint64_t>& _tile_ids)
    {
        tile_ids_ = _tile_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrAllLaneBoundaries() const
    {
        return &all_lane_boundaries_;
    }
    void SetAllLaneBoundaries(const ::std::vector<::std::uint64_t>& _all_lane_boundaries)
    {
        all_lane_boundaries_ = _all_lane_boundaries;
    }

    const ::std::vector<::std::uint64_t>* GetPtrTrajectoryIds() const
    {
        return &trajectory_ids_;
    }
    void SetTrajectoryIds(const ::std::vector<::std::uint64_t>& _trajectory_ids)
    {
        trajectory_ids_ = _trajectory_ids;
    }

    ::std::uint64_t GetAdasId() const
    {
        return adas_id_;
    }
    void SetAdasId(const ::std::uint64_t _adas_id)
    {
        adas_id_ = _adas_id;
    }

    ::std::uint32_t GetLaneGroupLengthCm() const
    {
        return lane_group_length_cm_;
    }
    void SetLaneGroupLengthCm(const ::std::uint32_t _lane_group_length_cm)
    {
        lane_group_length_cm_ = _lane_group_length_cm;
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


    void ClearLanes()
    {
        lanes_.clear();
    }
    void AddLanesElement(const ::std::uint64_t& _value)
    {
        lanes_.push_back(_value);
    }
    void UniqueAddLanesElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(lanes_, _value);
    }

    void ClearPrecedingLaneGroupIds()
    {
        preceding_lane_group_ids_.clear();
    }
    void AddPrecedingLaneGroupIdsElement(const ::std::uint64_t& _value)
    {
        preceding_lane_group_ids_.push_back(_value);
    }
    void UniqueAddPrecedingLaneGroupIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(preceding_lane_group_ids_, _value);
    }

    void ClearSucceedingLaneGroupIds()
    {
        succeeding_lane_group_ids_.clear();
    }
    void AddSucceedingLaneGroupIdsElement(const ::std::uint64_t& _value)
    {
        succeeding_lane_group_ids_.push_back(_value);
    }
    void UniqueAddSucceedingLaneGroupIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(succeeding_lane_group_ids_, _value);
    }

    void ClearAssociatedLaneGroupIds()
    {
        associated_lane_group_ids_.clear();
    }
    void AddAssociatedLaneGroupIdsElement(const ::std::uint64_t& _value)
    {
        associated_lane_group_ids_.push_back(_value);
    }
    void UniqueAddAssociatedLaneGroupIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(associated_lane_group_ids_, _value);
    }

    void ClearLaneGroupAttributes()
    {
        lane_group_attributes_.clear();
    }
    void AddLaneGroupAttributesElement(const LaneGroupAttribute& _value)
    {
        lane_group_attributes_.push_back(_value);
    }
    void UniqueAddLaneGroupAttributesElements(const ::std::vector<LaneGroupAttribute>& _value)
    {
        UniqueAppend(lane_group_attributes_, _value);
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

    void ClearAllLaneBoundaries()
    {
        all_lane_boundaries_.clear();
    }
    void AddAllLaneBoundariesElement(const ::std::uint64_t& _value)
    {
        all_lane_boundaries_.push_back(_value);
    }
    void UniqueAddAllLaneBoundariesElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(all_lane_boundaries_, _value);
    }

    void ClearTrajectoryIds()
    {
        trajectory_ids_.clear();
    }
    void AddTrajectoryIdsElement(const ::std::uint64_t& _value)
    {
        trajectory_ids_.push_back(_value);
    }
    void UniqueAddTrajectoryIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(trajectory_ids_, _value);
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





};  // class LaneGroup

typedef ::std::shared_ptr<LaneGroup> PtrLaneGroup;
typedef const ::std::vector<LaneGroup>* ConstRawPtrVecLaneGroup;
typedef ::std::vector<LaneGroup>* RawPtrVecLaneGroup;
typedef ::std::shared_ptr<LaneGroup const> ConstPtrLaneGroup;
typedef ::std::shared_ptr<::std::vector<LaneGroup> const> ConstPtrVecLaneGroup;
typedef ::std::unordered_map<::std::uint64_t, PtrLaneGroup> HashmapLaneGroup;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_BASE_LANE_GROUP_H_