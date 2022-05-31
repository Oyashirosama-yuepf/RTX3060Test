/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file object_parking_lot.h
 * @brief Auto generated code for ObjectParkingLot format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_PARKING_OBJECT_PARKING_LOT_H_
#define HOLO_MAP_FORMAT_PARKING_OBJECT_PARKING_LOT_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/parking/object_parking_lot.pb.h>

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

class  ObjectParkingLot: public Base
{
public:




private:
    ::std::uint64_t object_parking_lot_id_; 
    ::std::string name_; 
    ::std::vector<::std::uint64_t> associated_object_parking_floor_ids_; 
    bool is_use_; 
    GeoPoint position_point_; 
    GeoPoint display_point_; 
    ::std::vector<::std::uint64_t> tile_ids_; 
    Coordinate coordinate_; 
    ::std::uint32_t zone_id_; 
    ::std::uint32_t extra_zone_id_; 
    bool south_flag_; 
    ::std::vector<GeoPoint> geometry_points_; 
    ::std::map<::std::uint32_t, GeoLine> extra_geometry_points_; 

private:
    void DecodeProto(const ::holo::map::proto::parking::ObjectParkingLot& _proto_handler);
    ::holo::map::proto::parking::ObjectParkingLot EncodeProto();

public:
    ObjectParkingLot();
    explicit ObjectParkingLot(const ::holo::map::proto::parking::ObjectParkingLot& _proto_handler);
    // init all format data
    ObjectParkingLot(const ::std::uint64_t _object_parking_lot_id,const ::std::string& _name,const ::std::vector<::std::uint64_t>& _associated_object_parking_floor_ids,const bool _is_use,const GeoPoint& _position_point,const GeoPoint& _display_point,const ::std::vector<::std::uint64_t>& _tile_ids,const Coordinate& _coordinate,const ::std::uint32_t _zone_id,const ::std::uint32_t _extra_zone_id,const bool _south_flag,const ::std::vector<GeoPoint>& _geometry_points,const ::std::map<::std::uint32_t, GeoLine>& _extra_geometry_points);
    ~ObjectParkingLot();

    bool operator==(const ::holo::map::format::ObjectParkingLot& _other) const;
    ObjectParkingLot& operator=(const ::holo::map::proto::parking::ObjectParkingLot& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::parking::ObjectParkingLot GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetObjectParkingLotId() const
    {
        return object_parking_lot_id_;
    }
    void SetObjectParkingLotId(const ::std::uint64_t _object_parking_lot_id)
    {
        object_parking_lot_id_ = _object_parking_lot_id;
    }

    const ::std::string& GetName() const
    {
        return name_;
    }
    void SetName(const ::std::string& _name)
    {
        name_ = _name;
    }

    const ::std::vector<::std::uint64_t>* GetPtrAssociatedObjectParkingFloorIds() const
    {
        return &associated_object_parking_floor_ids_;
    }
    void SetAssociatedObjectParkingFloorIds(const ::std::vector<::std::uint64_t>& _associated_object_parking_floor_ids)
    {
        associated_object_parking_floor_ids_ = _associated_object_parking_floor_ids;
    }

    bool GetIsUse() const
    {
        return is_use_;
    }
    void SetIsUse(const bool _is_use)
    {
        is_use_ = _is_use;
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

    const ::std::vector<::std::uint64_t>* GetPtrTileIds() const
    {
        return &tile_ids_;
    }
    void SetTileIds(const ::std::vector<::std::uint64_t>& _tile_ids)
    {
        tile_ids_ = _tile_ids;
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


    void ClearAssociatedObjectParkingFloorIds()
    {
        associated_object_parking_floor_ids_.clear();
    }
    void AddAssociatedObjectParkingFloorIdsElement(const ::std::uint64_t& _value)
    {
        associated_object_parking_floor_ids_.push_back(_value);
    }
    void UniqueAddAssociatedObjectParkingFloorIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(associated_object_parking_floor_ids_, _value);
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





};  // class ObjectParkingLot

typedef ::std::shared_ptr<ObjectParkingLot> PtrObjectParkingLot;
typedef const ::std::vector<ObjectParkingLot>* ConstRawPtrVecObjectParkingLot;
typedef ::std::vector<ObjectParkingLot>* RawPtrVecObjectParkingLot;
typedef ::std::shared_ptr<ObjectParkingLot const> ConstPtrObjectParkingLot;
typedef ::std::shared_ptr<::std::vector<ObjectParkingLot> const> ConstPtrVecObjectParkingLot;
typedef ::std::unordered_map<::std::uint64_t, PtrObjectParkingLot> HashmapObjectParkingLot;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_PARKING_OBJECT_PARKING_LOT_H_