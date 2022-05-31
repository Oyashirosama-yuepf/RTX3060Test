/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file object_safe_island.h
 * @brief Auto generated code for ObjectSafeIsland format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_BASE_OBJECT_SAFE_ISLAND_H_
#define HOLO_MAP_FORMAT_BASE_OBJECT_SAFE_ISLAND_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/base/object_safe_island.pb.h>

#include <holo/map/proto/common/coordinate.pb.h>

#include <holo/map/proto/common/geo_polygon.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/coordinate.h>

#include <holo/map/format/common/geo_polygon.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  ObjectSafeIsland: public Base
{
public:




private:
    ::std::uint64_t object_safe_island_id_; 
    bool is_moveable_; 
    bool is_passable_; 
    ::std::vector<::std::uint64_t> tile_ids_; 
    ::std::vector<::std::uint64_t> associated_lane_ids_; 
    ::std::vector<::std::uint64_t> associated_lane_group_ids_; 
    ::std::uint32_t zone_id_; 
    ::std::uint32_t extra_zone_id_; 
    bool south_flag_; 
    GeoPolygon geometry_; 
    ::std::map<::std::uint32_t, GeoPolygon> extra_geometry_; 
    Coordinate coordinate_; 

private:
    void DecodeProto(const ::holo::map::proto::base::ObjectSafeIsland& _proto_handler);
    ::holo::map::proto::base::ObjectSafeIsland EncodeProto();

public:
    ObjectSafeIsland();
    explicit ObjectSafeIsland(const ::holo::map::proto::base::ObjectSafeIsland& _proto_handler);
    // init all format data
    ObjectSafeIsland(const ::std::uint64_t _object_safe_island_id,const bool _is_moveable,const bool _is_passable,const ::std::vector<::std::uint64_t>& _tile_ids,const ::std::vector<::std::uint64_t>& _associated_lane_ids,const ::std::vector<::std::uint64_t>& _associated_lane_group_ids,const ::std::uint32_t _zone_id,const ::std::uint32_t _extra_zone_id,const bool _south_flag,const GeoPolygon& _geometry,const ::std::map<::std::uint32_t, GeoPolygon>& _extra_geometry,const Coordinate& _coordinate);
    ~ObjectSafeIsland();

    bool operator==(const ::holo::map::format::ObjectSafeIsland& _other) const;
    ObjectSafeIsland& operator=(const ::holo::map::proto::base::ObjectSafeIsland& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::base::ObjectSafeIsland GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetObjectSafeIslandId() const
    {
        return object_safe_island_id_;
    }
    void SetObjectSafeIslandId(const ::std::uint64_t _object_safe_island_id)
    {
        object_safe_island_id_ = _object_safe_island_id;
    }

    bool GetIsMoveable() const
    {
        return is_moveable_;
    }
    void SetIsMoveable(const bool _is_moveable)
    {
        is_moveable_ = _is_moveable;
    }

    bool GetIsPassable() const
    {
        return is_passable_;
    }
    void SetIsPassable(const bool _is_passable)
    {
        is_passable_ = _is_passable;
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

    const ::std::map<::std::uint32_t, GeoPolygon>* GetPtrExtraGeometry() const
    {
        return &extra_geometry_;
    }
    void SetExtraGeometry(const ::std::map<::std::uint32_t, GeoPolygon>& _extra_geometry)
    {
        extra_geometry_ = _extra_geometry;
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


    const GeoPolygon& GetGeometry() const;
    void SetGeometry(const GeoPolygon& _geometry)
    {
        this->geometry_ = _geometry;
    }







};  // class ObjectSafeIsland

typedef ::std::shared_ptr<ObjectSafeIsland> PtrObjectSafeIsland;
typedef const ::std::vector<ObjectSafeIsland>* ConstRawPtrVecObjectSafeIsland;
typedef ::std::vector<ObjectSafeIsland>* RawPtrVecObjectSafeIsland;
typedef ::std::shared_ptr<ObjectSafeIsland const> ConstPtrObjectSafeIsland;
typedef ::std::shared_ptr<::std::vector<ObjectSafeIsland> const> ConstPtrVecObjectSafeIsland;
typedef ::std::unordered_map<::std::uint64_t, PtrObjectSafeIsland> HashmapObjectSafeIsland;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_BASE_OBJECT_SAFE_ISLAND_H_