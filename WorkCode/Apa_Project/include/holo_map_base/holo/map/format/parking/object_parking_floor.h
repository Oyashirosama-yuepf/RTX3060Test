/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file object_parking_floor.h
 * @brief Auto generated code for ObjectParkingFloor format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_PARKING_OBJECT_PARKING_FLOOR_H_
#define HOLO_MAP_FORMAT_PARKING_OBJECT_PARKING_FLOOR_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/parking/object_parking_floor.pb.h>

#include <holo/map/proto/common/coordinate.pb.h>

#include <holo/map/proto/common/geo_point.pb.h>

#include <holo/map/proto/common/geo_line.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/coordinate.h>

#include <holo/map/format/common/geo_point.h>

#include <holo/map/format/common/geo_line.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  ObjectParkingFloor: public Base
{
public:




private:
    ::std::uint64_t object_parking_floor_id_; 
    ::std::uint32_t floor_seq_; 
    ::std::string name_; 
    ::std::uint64_t object_parking_lot_id_; 
    bool is_use_; 
    ::std::uint32_t height_cm_; 
    ::std::vector<::std::uint64_t> associated_enter_exit_ids_; 
    ::std::vector<::std::uint64_t> associated_background_ids_; 
    ::std::vector<::std::uint64_t> associated_road_ids_; 
    ::std::vector<::std::uint64_t> associated_lane_group_ids_; 
    ::std::vector<::std::uint64_t> associated_lane_ids_; 
    ::std::vector<::std::uint64_t> associated_boundary_ids_; 
    ::std::vector<::std::uint64_t> associated_parking_poi_ids_; 
    ::std::vector<::std::uint64_t> associated_parking_background_ids_; 
    ::std::vector<::std::uint64_t> associated_parking_space_ids_; 
    ::std::vector<::std::uint64_t> tile_ids_; 
    ::std::vector<::std::uint64_t> object_linear_info_ids_; 
    ::std::vector<::std::uint64_t> object_regional_info_ids_; 
    ::std::vector<::std::uint64_t> object_stop_line_ids_; 
    ::std::vector<::std::uint64_t> object_traffic_light_ids_; 
    ::std::vector<::std::uint64_t> object_traffic_light_group_ids_; 
    ::std::vector<::std::uint64_t> object_pedestrian_crossing_ids_; 
    ::std::vector<::std::uint64_t> object_traffic_sign_ids_; 
    ::std::vector<::std::uint64_t> object_intersection_ids_; 
    Coordinate coordinate_; 
    ::std::uint32_t zone_id_; 
    ::std::uint32_t extra_zone_id_; 
    bool south_flag_; 
    ::std::vector<GeoPoint> geometry_points_; 
    ::std::map<::std::uint32_t, GeoLine> extra_geometry_points_; 

private:
    void DecodeProto(const ::holo::map::proto::parking::ObjectParkingFloor& _proto_handler);
    ::holo::map::proto::parking::ObjectParkingFloor EncodeProto();

public:
    ObjectParkingFloor();
    explicit ObjectParkingFloor(const ::holo::map::proto::parking::ObjectParkingFloor& _proto_handler);
    // init all format data
    ObjectParkingFloor(const ::std::uint64_t _object_parking_floor_id,const ::std::uint32_t _floor_seq,const ::std::string& _name,const ::std::uint64_t _object_parking_lot_id,const bool _is_use,const ::std::uint32_t _height_cm,const ::std::vector<::std::uint64_t>& _associated_enter_exit_ids,const ::std::vector<::std::uint64_t>& _associated_background_ids,const ::std::vector<::std::uint64_t>& _associated_road_ids,const ::std::vector<::std::uint64_t>& _associated_lane_group_ids,const ::std::vector<::std::uint64_t>& _associated_lane_ids,const ::std::vector<::std::uint64_t>& _associated_boundary_ids,const ::std::vector<::std::uint64_t>& _associated_parking_poi_ids,const ::std::vector<::std::uint64_t>& _associated_parking_background_ids,const ::std::vector<::std::uint64_t>& _associated_parking_space_ids,const ::std::vector<::std::uint64_t>& _tile_ids,const ::std::vector<::std::uint64_t>& _object_linear_info_ids,const ::std::vector<::std::uint64_t>& _object_regional_info_ids,const ::std::vector<::std::uint64_t>& _object_stop_line_ids,const ::std::vector<::std::uint64_t>& _object_traffic_light_ids,const ::std::vector<::std::uint64_t>& _object_traffic_light_group_ids,const ::std::vector<::std::uint64_t>& _object_pedestrian_crossing_ids,const ::std::vector<::std::uint64_t>& _object_traffic_sign_ids,const ::std::vector<::std::uint64_t>& _object_intersection_ids,const Coordinate& _coordinate,const ::std::uint32_t _zone_id,const ::std::uint32_t _extra_zone_id,const bool _south_flag,const ::std::vector<GeoPoint>& _geometry_points,const ::std::map<::std::uint32_t, GeoLine>& _extra_geometry_points);
    ~ObjectParkingFloor();

    bool operator==(const ::holo::map::format::ObjectParkingFloor& _other) const;
    ObjectParkingFloor& operator=(const ::holo::map::proto::parking::ObjectParkingFloor& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::parking::ObjectParkingFloor GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetObjectParkingFloorId() const
    {
        return object_parking_floor_id_;
    }
    void SetObjectParkingFloorId(const ::std::uint64_t _object_parking_floor_id)
    {
        object_parking_floor_id_ = _object_parking_floor_id;
    }

    ::std::uint32_t GetFloorSeq() const
    {
        return floor_seq_;
    }
    void SetFloorSeq(const ::std::uint32_t _floor_seq)
    {
        floor_seq_ = _floor_seq;
    }

    const ::std::string& GetName() const
    {
        return name_;
    }
    void SetName(const ::std::string& _name)
    {
        name_ = _name;
    }

    ::std::uint64_t GetObjectParkingLotId() const
    {
        return object_parking_lot_id_;
    }
    void SetObjectParkingLotId(const ::std::uint64_t _object_parking_lot_id)
    {
        object_parking_lot_id_ = _object_parking_lot_id;
    }

    bool GetIsUse() const
    {
        return is_use_;
    }
    void SetIsUse(const bool _is_use)
    {
        is_use_ = _is_use;
    }

    ::std::uint32_t GetHeightCm() const
    {
        return height_cm_;
    }
    void SetHeightCm(const ::std::uint32_t _height_cm)
    {
        height_cm_ = _height_cm;
    }

    const ::std::vector<::std::uint64_t>* GetPtrAssociatedEnterExitIds() const
    {
        return &associated_enter_exit_ids_;
    }
    void SetAssociatedEnterExitIds(const ::std::vector<::std::uint64_t>& _associated_enter_exit_ids)
    {
        associated_enter_exit_ids_ = _associated_enter_exit_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrAssociatedBackgroundIds() const
    {
        return &associated_background_ids_;
    }
    void SetAssociatedBackgroundIds(const ::std::vector<::std::uint64_t>& _associated_background_ids)
    {
        associated_background_ids_ = _associated_background_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrAssociatedRoadIds() const
    {
        return &associated_road_ids_;
    }
    void SetAssociatedRoadIds(const ::std::vector<::std::uint64_t>& _associated_road_ids)
    {
        associated_road_ids_ = _associated_road_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrAssociatedLaneGroupIds() const
    {
        return &associated_lane_group_ids_;
    }
    void SetAssociatedLaneGroupIds(const ::std::vector<::std::uint64_t>& _associated_lane_group_ids)
    {
        associated_lane_group_ids_ = _associated_lane_group_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrAssociatedLaneIds() const
    {
        return &associated_lane_ids_;
    }
    void SetAssociatedLaneIds(const ::std::vector<::std::uint64_t>& _associated_lane_ids)
    {
        associated_lane_ids_ = _associated_lane_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrAssociatedBoundaryIds() const
    {
        return &associated_boundary_ids_;
    }
    void SetAssociatedBoundaryIds(const ::std::vector<::std::uint64_t>& _associated_boundary_ids)
    {
        associated_boundary_ids_ = _associated_boundary_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrAssociatedParkingPoiIds() const
    {
        return &associated_parking_poi_ids_;
    }
    void SetAssociatedParkingPoiIds(const ::std::vector<::std::uint64_t>& _associated_parking_poi_ids)
    {
        associated_parking_poi_ids_ = _associated_parking_poi_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrAssociatedParkingBackgroundIds() const
    {
        return &associated_parking_background_ids_;
    }
    void SetAssociatedParkingBackgroundIds(const ::std::vector<::std::uint64_t>& _associated_parking_background_ids)
    {
        associated_parking_background_ids_ = _associated_parking_background_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrAssociatedParkingSpaceIds() const
    {
        return &associated_parking_space_ids_;
    }
    void SetAssociatedParkingSpaceIds(const ::std::vector<::std::uint64_t>& _associated_parking_space_ids)
    {
        associated_parking_space_ids_ = _associated_parking_space_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrTileIds() const
    {
        return &tile_ids_;
    }
    void SetTileIds(const ::std::vector<::std::uint64_t>& _tile_ids)
    {
        tile_ids_ = _tile_ids;
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

    const ::std::vector<::std::uint64_t>* GetPtrObjectIntersectionIds() const
    {
        return &object_intersection_ids_;
    }
    void SetObjectIntersectionIds(const ::std::vector<::std::uint64_t>& _object_intersection_ids)
    {
        object_intersection_ids_ = _object_intersection_ids;
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

    const ::std::map<::std::uint32_t, GeoLine>* GetPtrExtraGeometryPoints() const
    {
        return &extra_geometry_points_;
    }
    void SetExtraGeometryPoints(const ::std::map<::std::uint32_t, GeoLine>& _extra_geometry_points)
    {
        extra_geometry_points_ = _extra_geometry_points;
    }


    void ClearAssociatedEnterExitIds()
    {
        associated_enter_exit_ids_.clear();
    }
    void AddAssociatedEnterExitIdsElement(const ::std::uint64_t& _value)
    {
        associated_enter_exit_ids_.push_back(_value);
    }
    void UniqueAddAssociatedEnterExitIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(associated_enter_exit_ids_, _value);
    }

    void ClearAssociatedBackgroundIds()
    {
        associated_background_ids_.clear();
    }
    void AddAssociatedBackgroundIdsElement(const ::std::uint64_t& _value)
    {
        associated_background_ids_.push_back(_value);
    }
    void UniqueAddAssociatedBackgroundIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(associated_background_ids_, _value);
    }

    void ClearAssociatedRoadIds()
    {
        associated_road_ids_.clear();
    }
    void AddAssociatedRoadIdsElement(const ::std::uint64_t& _value)
    {
        associated_road_ids_.push_back(_value);
    }
    void UniqueAddAssociatedRoadIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(associated_road_ids_, _value);
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

    void ClearAssociatedLaneIds()
    {
        associated_lane_ids_.clear();
    }
    void AddAssociatedLaneIdsElement(const ::std::uint64_t& _value)
    {
        associated_lane_ids_.push_back(_value);
    }
    void UniqueAddAssociatedLaneIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(associated_lane_ids_, _value);
    }

    void ClearAssociatedBoundaryIds()
    {
        associated_boundary_ids_.clear();
    }
    void AddAssociatedBoundaryIdsElement(const ::std::uint64_t& _value)
    {
        associated_boundary_ids_.push_back(_value);
    }
    void UniqueAddAssociatedBoundaryIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(associated_boundary_ids_, _value);
    }

    void ClearAssociatedParkingPoiIds()
    {
        associated_parking_poi_ids_.clear();
    }
    void AddAssociatedParkingPoiIdsElement(const ::std::uint64_t& _value)
    {
        associated_parking_poi_ids_.push_back(_value);
    }
    void UniqueAddAssociatedParkingPoiIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(associated_parking_poi_ids_, _value);
    }

    void ClearAssociatedParkingBackgroundIds()
    {
        associated_parking_background_ids_.clear();
    }
    void AddAssociatedParkingBackgroundIdsElement(const ::std::uint64_t& _value)
    {
        associated_parking_background_ids_.push_back(_value);
    }
    void UniqueAddAssociatedParkingBackgroundIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(associated_parking_background_ids_, _value);
    }

    void ClearAssociatedParkingSpaceIds()
    {
        associated_parking_space_ids_.clear();
    }
    void AddAssociatedParkingSpaceIdsElement(const ::std::uint64_t& _value)
    {
        associated_parking_space_ids_.push_back(_value);
    }
    void UniqueAddAssociatedParkingSpaceIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(associated_parking_space_ids_, _value);
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

    void ClearObjectIntersectionIds()
    {
        object_intersection_ids_.clear();
    }
    void AddObjectIntersectionIdsElement(const ::std::uint64_t& _value)
    {
        object_intersection_ids_.push_back(_value);
    }
    void UniqueAddObjectIntersectionIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(object_intersection_ids_, _value);
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




    const ::std::vector<GeoPoint>* GetPtrGeometryPoints() const;
    void SetGeometryPoints(const ::std::vector<GeoPoint>& _geometry_points)
    {
        this->geometry_points_ = _geometry_points;
    }





};  // class ObjectParkingFloor

typedef ::std::shared_ptr<ObjectParkingFloor> PtrObjectParkingFloor;
typedef const ::std::vector<ObjectParkingFloor>* ConstRawPtrVecObjectParkingFloor;
typedef ::std::vector<ObjectParkingFloor>* RawPtrVecObjectParkingFloor;
typedef ::std::shared_ptr<ObjectParkingFloor const> ConstPtrObjectParkingFloor;
typedef ::std::shared_ptr<::std::vector<ObjectParkingFloor> const> ConstPtrVecObjectParkingFloor;
typedef ::std::unordered_map<::std::uint64_t, PtrObjectParkingFloor> HashmapObjectParkingFloor;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_PARKING_OBJECT_PARKING_FLOOR_H_