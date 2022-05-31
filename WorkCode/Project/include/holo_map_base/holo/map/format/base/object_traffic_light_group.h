/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file object_traffic_light_group.h
 * @brief Auto generated code for ObjectTrafficLightGroup format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_BASE_OBJECT_TRAFFIC_LIGHT_GROUP_H_
#define HOLO_MAP_FORMAT_BASE_OBJECT_TRAFFIC_LIGHT_GROUP_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/base/object_traffic_light_group.pb.h>

#include <holo/map/proto/common/coordinate.pb.h>

#include <holo/map/proto/common/geo_box.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/coordinate.h>

#include <holo/map/format/common/geo_box.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  ObjectTrafficLightGroup: public Base
{
public:




private:
    ::std::uint64_t object_traffic_light_group_id_; 
    ::std::vector<::std::uint64_t> traffic_light_ids_; 
    ::std::vector<::std::uint64_t> intersection_id_; 
    ::std::vector<::std::uint64_t> tile_ids_; 
    ::std::uint32_t zone_id_; 
    ::std::uint32_t extra_zone_id_; 
    bool south_flag_; 
    GeoBox geo_box_; 
    ::std::map<::std::uint32_t, GeoBox> extra_geo_box_; 
    Coordinate coordinate_; 

private:
    void DecodeProto(const ::holo::map::proto::base::ObjectTrafficLightGroup& _proto_handler);
    ::holo::map::proto::base::ObjectTrafficLightGroup EncodeProto();

public:
    ObjectTrafficLightGroup();
    explicit ObjectTrafficLightGroup(const ::holo::map::proto::base::ObjectTrafficLightGroup& _proto_handler);
    // init all format data
    ObjectTrafficLightGroup(const ::std::uint64_t _object_traffic_light_group_id,const ::std::vector<::std::uint64_t>& _traffic_light_ids,const ::std::vector<::std::uint64_t>& _intersection_id,const ::std::vector<::std::uint64_t>& _tile_ids,const ::std::uint32_t _zone_id,const ::std::uint32_t _extra_zone_id,const bool _south_flag,const GeoBox& _geo_box,const ::std::map<::std::uint32_t, GeoBox>& _extra_geo_box,const Coordinate& _coordinate);
    ~ObjectTrafficLightGroup();

    bool operator==(const ::holo::map::format::ObjectTrafficLightGroup& _other) const;
    ObjectTrafficLightGroup& operator=(const ::holo::map::proto::base::ObjectTrafficLightGroup& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::base::ObjectTrafficLightGroup GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetObjectTrafficLightGroupId() const
    {
        return object_traffic_light_group_id_;
    }
    void SetObjectTrafficLightGroupId(const ::std::uint64_t _object_traffic_light_group_id)
    {
        object_traffic_light_group_id_ = _object_traffic_light_group_id;
    }

    const ::std::vector<::std::uint64_t>* GetPtrTrafficLightIds() const
    {
        return &traffic_light_ids_;
    }
    void SetTrafficLightIds(const ::std::vector<::std::uint64_t>& _traffic_light_ids)
    {
        traffic_light_ids_ = _traffic_light_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrIntersectionId() const
    {
        return &intersection_id_;
    }
    void SetIntersectionId(const ::std::vector<::std::uint64_t>& _intersection_id)
    {
        intersection_id_ = _intersection_id;
    }

    const ::std::vector<::std::uint64_t>* GetPtrTileIds() const
    {
        return &tile_ids_;
    }
    void SetTileIds(const ::std::vector<::std::uint64_t>& _tile_ids)
    {
        tile_ids_ = _tile_ids;
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

    const ::std::map<::std::uint32_t, GeoBox>* GetPtrExtraGeoBox() const
    {
        return &extra_geo_box_;
    }
    void SetExtraGeoBox(const ::std::map<::std::uint32_t, GeoBox>& _extra_geo_box)
    {
        extra_geo_box_ = _extra_geo_box;
    }

    const Coordinate& GetCoordinate() const
    {
        return coordinate_;
    }
    void SetCoordinate(const Coordinate& _coordinate)
    {
        coordinate_ = _coordinate;
    }


    void ClearTrafficLightIds()
    {
        traffic_light_ids_.clear();
    }
    void AddTrafficLightIdsElement(const ::std::uint64_t& _value)
    {
        traffic_light_ids_.push_back(_value);
    }
    void UniqueAddTrafficLightIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(traffic_light_ids_, _value);
    }

    void ClearIntersectionId()
    {
        intersection_id_.clear();
    }
    void AddIntersectionIdElement(const ::std::uint64_t& _value)
    {
        intersection_id_.push_back(_value);
    }
    void UniqueAddIntersectionIdElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(intersection_id_, _value);
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


    const GeoBox& GetGeoBox() const;
    void SetGeoBox(const GeoBox& _geo_box)
    {
        this->geo_box_ = _geo_box;
    }







};  // class ObjectTrafficLightGroup

typedef ::std::shared_ptr<ObjectTrafficLightGroup> PtrObjectTrafficLightGroup;
typedef const ::std::vector<ObjectTrafficLightGroup>* ConstRawPtrVecObjectTrafficLightGroup;
typedef ::std::vector<ObjectTrafficLightGroup>* RawPtrVecObjectTrafficLightGroup;
typedef ::std::shared_ptr<ObjectTrafficLightGroup const> ConstPtrObjectTrafficLightGroup;
typedef ::std::shared_ptr<::std::vector<ObjectTrafficLightGroup> const> ConstPtrVecObjectTrafficLightGroup;
typedef ::std::unordered_map<::std::uint64_t, PtrObjectTrafficLightGroup> HashmapObjectTrafficLightGroup;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_BASE_OBJECT_TRAFFIC_LIGHT_GROUP_H_