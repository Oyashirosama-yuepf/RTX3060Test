/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file object_parking_space.h
 * @brief Auto generated code for ObjectParkingSpace format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_PARKING_OBJECT_PARKING_SPACE_H_
#define HOLO_MAP_FORMAT_PARKING_OBJECT_PARKING_SPACE_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/parking/object_parking_space.pb.h>

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

class  ObjectParkingSpace: public Base
{
public:

        
    enum ObjectParkingSpaceType
    {
        OBJECT_PARKING_SPACE_TYPE_UNDEFINED=  0,  
        OBJECT_PARKING_SPACE_TYPE_PARKING_SPACE_NORMAL=  1,  
        OBJECT_PARKING_SPACE_TYPE_PARKING_SPACE_AVP=  2,  
    };

        
    enum RoadSide
    {
        ROAD_SIDE_NONE=  0,  
        ROAD_SIDE_LEFT=  1,  
        ROAD_SIDE_RIGHT=  2,  
        ROAD_SIDE_ON_ROAD=  3,  
    };

    static const ::std::map<::std::string, ObjectParkingSpaceType>& ENUMSTR_OBJECTPARKINGSPACETYPE() 
    { 
        static const ::std::map<::std::string, ObjectParkingSpaceType> data{
        { "UNDEFINED", ObjectParkingSpaceType::OBJECT_PARKING_SPACE_TYPE_UNDEFINED },
        { "PARKING_SPACE_NORMAL", ObjectParkingSpaceType::OBJECT_PARKING_SPACE_TYPE_PARKING_SPACE_NORMAL },
        { "PARKING_SPACE_AVP", ObjectParkingSpaceType::OBJECT_PARKING_SPACE_TYPE_PARKING_SPACE_AVP }};
        return data;
    }

    static const ::std::map<::std::string, RoadSide>& ENUMSTR_ROADSIDE() 
    { 
        static const ::std::map<::std::string, RoadSide> data{
        { "NONE", RoadSide::ROAD_SIDE_NONE },
        { "LEFT", RoadSide::ROAD_SIDE_LEFT },
        { "RIGHT", RoadSide::ROAD_SIDE_RIGHT },
        { "ON_ROAD", RoadSide::ROAD_SIDE_ON_ROAD }};
        return data;
    }


private:
    ::std::uint64_t object_parking_space_id_; 
    ObjectParkingSpaceType object_parking_space_type_; 
    ::std::string name_; 
    ::std::uint64_t object_parking_lot_id_; 
    ::std::uint64_t object_parking_floor_id_; 
    ::std::vector<::std::uint64_t> road_ids_; 
    ::std::vector<::std::uint64_t> lane_ids_; 
    RoadSide road_side_; 
    bool is_use_; 
    ::std::uint32_t high_limit_cm_; 
    GeoPoint position_point_; 
    GeoPoint display_point_; 
    ::std::uint32_t geometry_enter_start_; 
    ::std::uint32_t geometry_enter_end_; 
    ::std::vector<::std::uint64_t> tile_ids_; 
    ::std::uint64_t object_parking_background_id_; 
    Coordinate coordinate_; 
    ::std::uint32_t zone_id_; 
    ::std::uint32_t extra_zone_id_; 
    bool south_flag_; 
    ::std::vector<GeoPoint> geometry_points_; 
    ::std::map<::std::uint32_t, GeoLine> extra_geometry_points_; 

private:
    void DecodeProto(const ::holo::map::proto::parking::ObjectParkingSpace& _proto_handler);
    ::holo::map::proto::parking::ObjectParkingSpace EncodeProto();

public:
    ObjectParkingSpace();
    explicit ObjectParkingSpace(const ::holo::map::proto::parking::ObjectParkingSpace& _proto_handler);
    // init all format data
    ObjectParkingSpace(const ::std::uint64_t _object_parking_space_id,const ObjectParkingSpaceType& _object_parking_space_type,const ::std::string& _name,const ::std::uint64_t _object_parking_lot_id,const ::std::uint64_t _object_parking_floor_id,const ::std::vector<::std::uint64_t>& _road_ids,const ::std::vector<::std::uint64_t>& _lane_ids,const RoadSide& _road_side,const bool _is_use,const ::std::uint32_t _high_limit_cm,const GeoPoint& _position_point,const GeoPoint& _display_point,const ::std::uint32_t _geometry_enter_start,const ::std::uint32_t _geometry_enter_end,const ::std::vector<::std::uint64_t>& _tile_ids,const ::std::uint64_t _object_parking_background_id,const Coordinate& _coordinate,const ::std::uint32_t _zone_id,const ::std::uint32_t _extra_zone_id,const bool _south_flag,const ::std::vector<GeoPoint>& _geometry_points,const ::std::map<::std::uint32_t, GeoLine>& _extra_geometry_points);
    ~ObjectParkingSpace();

    bool operator==(const ::holo::map::format::ObjectParkingSpace& _other) const;
    ObjectParkingSpace& operator=(const ::holo::map::proto::parking::ObjectParkingSpace& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::parking::ObjectParkingSpace GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetObjectParkingSpaceId() const
    {
        return object_parking_space_id_;
    }
    void SetObjectParkingSpaceId(const ::std::uint64_t _object_parking_space_id)
    {
        object_parking_space_id_ = _object_parking_space_id;
    }

    const ObjectParkingSpaceType& GetObjectParkingSpaceType() const
    {
        return object_parking_space_type_;
    }
    void SetObjectParkingSpaceType(const ObjectParkingSpaceType& _object_parking_space_type)
    {
        object_parking_space_type_ = _object_parking_space_type;
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

    ::std::uint64_t GetObjectParkingFloorId() const
    {
        return object_parking_floor_id_;
    }
    void SetObjectParkingFloorId(const ::std::uint64_t _object_parking_floor_id)
    {
        object_parking_floor_id_ = _object_parking_floor_id;
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

    const RoadSide& GetRoadSide() const
    {
        return road_side_;
    }
    void SetRoadSide(const RoadSide& _road_side)
    {
        road_side_ = _road_side;
    }

    bool GetIsUse() const
    {
        return is_use_;
    }
    void SetIsUse(const bool _is_use)
    {
        is_use_ = _is_use;
    }

    ::std::uint32_t GetHighLimitCm() const
    {
        return high_limit_cm_;
    }
    void SetHighLimitCm(const ::std::uint32_t _high_limit_cm)
    {
        high_limit_cm_ = _high_limit_cm;
    }

    const GeoPoint& GetPositionPoint() const
    {
        return position_point_;
    }
    void SetPositionPoint(const GeoPoint& _position_point)
    {
        position_point_ = _position_point;
    }

    const GeoPoint& GetDisplayPoint() const
    {
        return display_point_;
    }
    void SetDisplayPoint(const GeoPoint& _display_point)
    {
        display_point_ = _display_point;
    }

    ::std::uint32_t GetGeometryEnterStart() const
    {
        return geometry_enter_start_;
    }
    void SetGeometryEnterStart(const ::std::uint32_t _geometry_enter_start)
    {
        geometry_enter_start_ = _geometry_enter_start;
    }

    ::std::uint32_t GetGeometryEnterEnd() const
    {
        return geometry_enter_end_;
    }
    void SetGeometryEnterEnd(const ::std::uint32_t _geometry_enter_end)
    {
        geometry_enter_end_ = _geometry_enter_end;
    }

    const ::std::vector<::std::uint64_t>* GetPtrTileIds() const
    {
        return &tile_ids_;
    }
    void SetTileIds(const ::std::vector<::std::uint64_t>& _tile_ids)
    {
        tile_ids_ = _tile_ids;
    }

    ::std::uint64_t GetObjectParkingBackgroundId() const
    {
        return object_parking_background_id_;
    }
    void SetObjectParkingBackgroundId(const ::std::uint64_t _object_parking_background_id)
    {
        object_parking_background_id_ = _object_parking_background_id;
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




    const ::std::vector<GeoPoint>* GetPtrGeometryPoints() const;
    void SetGeometryPoints(const ::std::vector<GeoPoint>& _geometry_points)
    {
        this->geometry_points_ = _geometry_points;
    }





};  // class ObjectParkingSpace

typedef ::std::shared_ptr<ObjectParkingSpace> PtrObjectParkingSpace;
typedef const ::std::vector<ObjectParkingSpace>* ConstRawPtrVecObjectParkingSpace;
typedef ::std::vector<ObjectParkingSpace>* RawPtrVecObjectParkingSpace;
typedef ::std::shared_ptr<ObjectParkingSpace const> ConstPtrObjectParkingSpace;
typedef ::std::shared_ptr<::std::vector<ObjectParkingSpace> const> ConstPtrVecObjectParkingSpace;
typedef ::std::unordered_map<::std::uint64_t, PtrObjectParkingSpace> HashmapObjectParkingSpace;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_PARKING_OBJECT_PARKING_SPACE_H_