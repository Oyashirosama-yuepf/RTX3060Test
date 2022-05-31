/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file object_linear_info.h
 * @brief Auto generated code for ObjectLinearInfo format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_BASE_OBJECT_LINEAR_INFO_H_
#define HOLO_MAP_FORMAT_BASE_OBJECT_LINEAR_INFO_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/base/object_linear_info.pb.h>

#include <holo/map/proto/common/coordinate.pb.h>

#include <holo/map/proto/common/geo_line.pb.h>

#include <holo/map/proto/common/geo_point.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/coordinate.h>

#include <holo/map/format/common/geo_line.h>

#include <holo/map/format/common/geo_point.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  ObjectLinearInfo: public Base
{
public:

        
    enum ObjectType
    {
        OBJECT_TYPE_UNDEFINED=  0,  
        OBJECT_TYPE_SING_POLE=  1,  
        OBJECT_TYPE_LIGHT_POLE=  2,  
        OBJECT_TYPE_REGULAR_POLE=  3,  
    };

    static const ::std::map<::std::string, ObjectType>& ENUMSTR_OBJECTTYPE() 
    { 
        static const ::std::map<::std::string, ObjectType> data{
        { "UNDEFINED", ObjectType::OBJECT_TYPE_UNDEFINED },
        { "SING_POLE", ObjectType::OBJECT_TYPE_SING_POLE },
        { "LIGHT_POLE", ObjectType::OBJECT_TYPE_LIGHT_POLE },
        { "REGULAR_POLE", ObjectType::OBJECT_TYPE_REGULAR_POLE }};
        return data;
    }


private:
    ::std::uint64_t object_linear_info_id_; 
    ObjectType object_type_; 
    ::std::uint32_t top_radius_cm_; 
    ::std::uint32_t bottom_radius_cm_; 
    ::std::vector<::std::uint64_t> tile_ids_; 
    ::std::vector<::std::uint64_t> associated_lane_ids_; 
    ::std::vector<::std::uint64_t> associated_lane_group_ids_; 
    ::std::uint32_t zone_id_; 
    ::std::uint32_t extra_zone_id_; 
    bool south_flag_; 
    ::std::vector<GeoPoint> geometry_points_; 
    ::std::map<::std::uint32_t, GeoLine> extra_geometry_points_; 
    Coordinate coordinate_; 

private:
    void DecodeProto(const ::holo::map::proto::base::ObjectLinearInfo& _proto_handler);
    ::holo::map::proto::base::ObjectLinearInfo EncodeProto();

public:
    ObjectLinearInfo();
    explicit ObjectLinearInfo(const ::holo::map::proto::base::ObjectLinearInfo& _proto_handler);
    // init all format data
    ObjectLinearInfo(const ::std::uint64_t _object_linear_info_id,const ObjectType& _object_type,const ::std::uint32_t _top_radius_cm,const ::std::uint32_t _bottom_radius_cm,const ::std::vector<::std::uint64_t>& _tile_ids,const ::std::vector<::std::uint64_t>& _associated_lane_ids,const ::std::vector<::std::uint64_t>& _associated_lane_group_ids,const ::std::uint32_t _zone_id,const ::std::uint32_t _extra_zone_id,const bool _south_flag,const ::std::vector<GeoPoint>& _geometry_points,const ::std::map<::std::uint32_t, GeoLine>& _extra_geometry_points,const Coordinate& _coordinate);
    ~ObjectLinearInfo();

    bool operator==(const ::holo::map::format::ObjectLinearInfo& _other) const;
    ObjectLinearInfo& operator=(const ::holo::map::proto::base::ObjectLinearInfo& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::base::ObjectLinearInfo GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetObjectLinearInfoId() const
    {
        return object_linear_info_id_;
    }
    void SetObjectLinearInfoId(const ::std::uint64_t _object_linear_info_id)
    {
        object_linear_info_id_ = _object_linear_info_id;
    }

    const ObjectType& GetObjectType() const
    {
        return object_type_;
    }
    void SetObjectType(const ObjectType& _object_type)
    {
        object_type_ = _object_type;
    }

    ::std::uint32_t GetTopRadiusCm() const
    {
        return top_radius_cm_;
    }
    void SetTopRadiusCm(const ::std::uint32_t _top_radius_cm)
    {
        top_radius_cm_ = _top_radius_cm;
    }

    ::std::uint32_t GetBottomRadiusCm() const
    {
        return bottom_radius_cm_;
    }
    void SetBottomRadiusCm(const ::std::uint32_t _bottom_radius_cm)
    {
        bottom_radius_cm_ = _bottom_radius_cm;
    }

    const ::std::vector<::std::uint64_t>* GetPtrTileIds() const
    {
        return &tile_ids_;
    }
    void SetTileIds(const ::std::vector<::std::uint64_t>& _tile_ids)
    {
        tile_ids_ = _tile_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrAssociatedLaneIds() const
    {
        return &associated_lane_ids_;
    }
    void SetAssociatedLaneIds(const ::std::vector<::std::uint64_t>& _associated_lane_ids)
    {
        associated_lane_ids_ = _associated_lane_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrAssociatedLaneGroupIds() const
    {
        return &associated_lane_group_ids_;
    }
    void SetAssociatedLaneGroupIds(const ::std::vector<::std::uint64_t>& _associated_lane_group_ids)
    {
        associated_lane_group_ids_ = _associated_lane_group_ids;
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

    const Coordinate& GetCoordinate() const
    {
        return coordinate_;
    }
    void SetCoordinate(const Coordinate& _coordinate)
    {
        coordinate_ = _coordinate;
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





};  // class ObjectLinearInfo

typedef ::std::shared_ptr<ObjectLinearInfo> PtrObjectLinearInfo;
typedef const ::std::vector<ObjectLinearInfo>* ConstRawPtrVecObjectLinearInfo;
typedef ::std::vector<ObjectLinearInfo>* RawPtrVecObjectLinearInfo;
typedef ::std::shared_ptr<ObjectLinearInfo const> ConstPtrObjectLinearInfo;
typedef ::std::shared_ptr<::std::vector<ObjectLinearInfo> const> ConstPtrVecObjectLinearInfo;
typedef ::std::unordered_map<::std::uint64_t, PtrObjectLinearInfo> HashmapObjectLinearInfo;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_BASE_OBJECT_LINEAR_INFO_H_