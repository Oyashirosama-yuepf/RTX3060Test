/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file object_parking_background.h
 * @brief Auto generated code for ObjectParkingBackground format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_PARKING_OBJECT_PARKING_BACKGROUND_H_
#define HOLO_MAP_FORMAT_PARKING_OBJECT_PARKING_BACKGROUND_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/parking/object_parking_background.pb.h>

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

class  ObjectParkingBackground: public Base
{
public:

        
    enum ObjectParkingBackgroundType
    {
        OBJECT_PARKING_BACKGROUND_TYPE_UNDEFINED=  0,  
        OBJECT_PARKING_BACKGROUND_TYPE_PARKING_AREA=  1,  
        OBJECT_PARKING_BACKGROUND_TYPE_PARKING_WALL=  2,  
    };

    static const ::std::map<::std::string, ObjectParkingBackgroundType>& ENUMSTR_OBJECTPARKINGBACKGROUNDTYPE() 
    { 
        static const ::std::map<::std::string, ObjectParkingBackgroundType> data{
        { "UNDEFINED", ObjectParkingBackgroundType::OBJECT_PARKING_BACKGROUND_TYPE_UNDEFINED },
        { "PARKING_AREA", ObjectParkingBackgroundType::OBJECT_PARKING_BACKGROUND_TYPE_PARKING_AREA },
        { "PARKING_WALL", ObjectParkingBackgroundType::OBJECT_PARKING_BACKGROUND_TYPE_PARKING_WALL }};
        return data;
    }


private:
    ::std::uint64_t object_parking_background_id_; 
    ObjectParkingBackgroundType object_parking_background_type_; 
    ::std::string name_; 
    ::std::uint64_t object_parking_lot_id_; 
    ::std::uint64_t object_parking_floor_id_; 
    ::std::uint32_t height_cm_; 
    ::std::vector<::std::uint64_t> tile_ids_; 
    Coordinate coordinate_; 
    ::std::uint32_t zone_id_; 
    ::std::uint32_t extra_zone_id_; 
    bool south_flag_; 
    ::std::vector<GeoPoint> geometry_points_; 
    ::std::map<::std::uint32_t, GeoLine> extra_geometry_points_; 

private:
    void DecodeProto(const ::holo::map::proto::parking::ObjectParkingBackground& _proto_handler);
    ::holo::map::proto::parking::ObjectParkingBackground EncodeProto();

public:
    ObjectParkingBackground();
    explicit ObjectParkingBackground(const ::holo::map::proto::parking::ObjectParkingBackground& _proto_handler);
    // init all format data
    ObjectParkingBackground(const ::std::uint64_t _object_parking_background_id,const ObjectParkingBackgroundType& _object_parking_background_type,const ::std::string& _name,const ::std::uint64_t _object_parking_lot_id,const ::std::uint64_t _object_parking_floor_id,const ::std::uint32_t _height_cm,const ::std::vector<::std::uint64_t>& _tile_ids,const Coordinate& _coordinate,const ::std::uint32_t _zone_id,const ::std::uint32_t _extra_zone_id,const bool _south_flag,const ::std::vector<GeoPoint>& _geometry_points,const ::std::map<::std::uint32_t, GeoLine>& _extra_geometry_points);
    ~ObjectParkingBackground();

    bool operator==(const ::holo::map::format::ObjectParkingBackground& _other) const;
    ObjectParkingBackground& operator=(const ::holo::map::proto::parking::ObjectParkingBackground& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::parking::ObjectParkingBackground GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetObjectParkingBackgroundId() const
    {
        return object_parking_background_id_;
    }
    void SetObjectParkingBackgroundId(const ::std::uint64_t _object_parking_background_id)
    {
        object_parking_background_id_ = _object_parking_background_id;
    }

    const ObjectParkingBackgroundType& GetObjectParkingBackgroundType() const
    {
        return object_parking_background_type_;
    }
    void SetObjectParkingBackgroundType(const ObjectParkingBackgroundType& _object_parking_background_type)
    {
        object_parking_background_type_ = _object_parking_background_type;
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

    ::std::uint32_t GetHeightCm() const
    {
        return height_cm_;
    }
    void SetHeightCm(const ::std::uint32_t _height_cm)
    {
        height_cm_ = _height_cm;
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





};  // class ObjectParkingBackground

typedef ::std::shared_ptr<ObjectParkingBackground> PtrObjectParkingBackground;
typedef const ::std::vector<ObjectParkingBackground>* ConstRawPtrVecObjectParkingBackground;
typedef ::std::vector<ObjectParkingBackground>* RawPtrVecObjectParkingBackground;
typedef ::std::shared_ptr<ObjectParkingBackground const> ConstPtrObjectParkingBackground;
typedef ::std::shared_ptr<::std::vector<ObjectParkingBackground> const> ConstPtrVecObjectParkingBackground;
typedef ::std::unordered_map<::std::uint64_t, PtrObjectParkingBackground> HashmapObjectParkingBackground;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_PARKING_OBJECT_PARKING_BACKGROUND_H_