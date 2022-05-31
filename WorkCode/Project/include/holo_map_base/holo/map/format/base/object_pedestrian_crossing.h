/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file object_pedestrian_crossing.h
 * @brief Auto generated code for ObjectPedestrianCrossing format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_BASE_OBJECT_PEDESTRIAN_CROSSING_H_
#define HOLO_MAP_FORMAT_BASE_OBJECT_PEDESTRIAN_CROSSING_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/base/object_pedestrian_crossing.pb.h>

#include <holo/map/proto/common/coordinate.pb.h>

#include <holo/map/proto/common/geo_box4.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/coordinate.h>

#include <holo/map/format/common/geo_box4.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  ObjectPedestrianCrossing: public Base
{
public:




private:
    ::std::uint64_t object_pedestrian_crossing_id_; 
    ::std::uint64_t intersection_id_; 
    ::std::vector<::std::uint64_t> tile_ids_; 
    ::std::vector<::std::uint64_t> associated_lane_ids_; 
    ::std::vector<::std::uint64_t> associated_lane_group_ids_; 
    ::std::uint32_t zone_id_; 
    ::std::uint32_t extra_zone_id_; 
    bool south_flag_; 
    GeoBox4 geometry_; 
    ::std::map<::std::uint32_t, GeoBox4> extra_geometry_; 
    Coordinate coordinate_; 

private:
    void DecodeProto(const ::holo::map::proto::base::ObjectPedestrianCrossing& _proto_handler);
    ::holo::map::proto::base::ObjectPedestrianCrossing EncodeProto();

public:
    ObjectPedestrianCrossing();
    explicit ObjectPedestrianCrossing(const ::holo::map::proto::base::ObjectPedestrianCrossing& _proto_handler);
    // init all format data
    ObjectPedestrianCrossing(const ::std::uint64_t _object_pedestrian_crossing_id,const ::std::uint64_t _intersection_id,const ::std::vector<::std::uint64_t>& _tile_ids,const ::std::vector<::std::uint64_t>& _associated_lane_ids,const ::std::vector<::std::uint64_t>& _associated_lane_group_ids,const ::std::uint32_t _zone_id,const ::std::uint32_t _extra_zone_id,const bool _south_flag,const GeoBox4& _geometry,const ::std::map<::std::uint32_t, GeoBox4>& _extra_geometry,const Coordinate& _coordinate);
    ~ObjectPedestrianCrossing();

    bool operator==(const ::holo::map::format::ObjectPedestrianCrossing& _other) const;
    ObjectPedestrianCrossing& operator=(const ::holo::map::proto::base::ObjectPedestrianCrossing& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::base::ObjectPedestrianCrossing GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetObjectPedestrianCrossingId() const
    {
        return object_pedestrian_crossing_id_;
    }
    void SetObjectPedestrianCrossingId(const ::std::uint64_t _object_pedestrian_crossing_id)
    {
        object_pedestrian_crossing_id_ = _object_pedestrian_crossing_id;
    }

    ::std::uint64_t GetIntersectionId() const
    {
        return intersection_id_;
    }
    void SetIntersectionId(const ::std::uint64_t _intersection_id)
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

    const ::std::map<::std::uint32_t, GeoBox4>* GetPtrExtraGeometry() const
    {
        return &extra_geometry_;
    }
    void SetExtraGeometry(const ::std::map<::std::uint32_t, GeoBox4>& _extra_geometry)
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


    const GeoBox4& GetGeometry() const;
    void SetGeometry(const GeoBox4& _geometry)
    {
        this->geometry_ = _geometry;
    }







};  // class ObjectPedestrianCrossing

typedef ::std::shared_ptr<ObjectPedestrianCrossing> PtrObjectPedestrianCrossing;
typedef const ::std::vector<ObjectPedestrianCrossing>* ConstRawPtrVecObjectPedestrianCrossing;
typedef ::std::vector<ObjectPedestrianCrossing>* RawPtrVecObjectPedestrianCrossing;
typedef ::std::shared_ptr<ObjectPedestrianCrossing const> ConstPtrObjectPedestrianCrossing;
typedef ::std::shared_ptr<::std::vector<ObjectPedestrianCrossing> const> ConstPtrVecObjectPedestrianCrossing;
typedef ::std::unordered_map<::std::uint64_t, PtrObjectPedestrianCrossing> HashmapObjectPedestrianCrossing;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_BASE_OBJECT_PEDESTRIAN_CROSSING_H_