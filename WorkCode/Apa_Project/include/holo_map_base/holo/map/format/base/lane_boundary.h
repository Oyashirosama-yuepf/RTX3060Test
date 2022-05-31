/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_boundary.h
 * @brief Auto generated code for LaneBoundary format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_BASE_LANE_BOUNDARY_H_
#define HOLO_MAP_FORMAT_BASE_LANE_BOUNDARY_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/base/lane_boundary.pb.h>

#include <holo/map/proto/common/coordinate.pb.h>

#include <holo/map/proto/common/geo_box.pb.h>

#include <holo/map/proto/common/geo_point.pb.h>

#include <holo/map/proto/common/geo_line.pb.h>

#include <holo/map/proto/base/lane_boundary_info.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/coordinate.h>

#include <holo/map/format/common/geo_box.h>

#include <holo/map/format/common/geo_point.h>

#include <holo/map/format/common/geo_line.h>

#include <holo/map/format/base/lane_boundary_info.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  LaneBoundary: public Base
{
public:




private:
    ::std::uint64_t lane_boundary_id_; 
    ::std::vector<::std::uint64_t> tile_ids_; 
    ::std::vector<LaneBoundaryInfo> lane_boundary_info_; 
    ::std::uint64_t left_lane_id_; 
    ::std::uint64_t right_lane_id_; 
    ::std::uint64_t boundary_seq_; 
    ::std::vector<::std::uint64_t> pre_lane_boundary_ids_; 
    ::std::vector<::std::uint64_t> succ_lane_boundary_ids_; 
    ::std::uint64_t road_id_; 
    ::std::uint64_t lane_group_id_; 
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
    void DecodeProto(const ::holo::map::proto::base::LaneBoundary& _proto_handler);
    ::holo::map::proto::base::LaneBoundary EncodeProto();

public:
    LaneBoundary();
    explicit LaneBoundary(const ::holo::map::proto::base::LaneBoundary& _proto_handler);
    // init all format data
    LaneBoundary(const ::std::uint64_t _lane_boundary_id,const ::std::vector<::std::uint64_t>& _tile_ids,const ::std::vector<LaneBoundaryInfo>& _lane_boundary_info,const ::std::uint64_t _left_lane_id,const ::std::uint64_t _right_lane_id,const ::std::uint64_t _boundary_seq,const ::std::vector<::std::uint64_t>& _pre_lane_boundary_ids,const ::std::vector<::std::uint64_t>& _succ_lane_boundary_ids,const ::std::uint64_t _road_id,const ::std::uint64_t _lane_group_id,const ::std::uint64_t _object_parking_lot_id,const ::std::uint64_t _object_parking_floor_id,const Coordinate& _coordinate,const ::std::uint32_t _zone_id,const ::std::uint32_t _extra_zone_id,const bool _south_flag,const GeoBox& _region,const ::std::map<::std::uint32_t, GeoBox>& _extra_region,const ::std::vector<GeoPoint>& _geometry_points,const ::std::map<::std::uint32_t, GeoLine>& _extra_geometry_points);
    ~LaneBoundary();

    bool operator==(const ::holo::map::format::LaneBoundary& _other) const;
    LaneBoundary& operator=(const ::holo::map::proto::base::LaneBoundary& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::base::LaneBoundary GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetLaneBoundaryId() const
    {
        return lane_boundary_id_;
    }
    void SetLaneBoundaryId(const ::std::uint64_t _lane_boundary_id)
    {
        lane_boundary_id_ = _lane_boundary_id;
    }

    const ::std::vector<::std::uint64_t>* GetPtrTileIds() const
    {
        return &tile_ids_;
    }
    void SetTileIds(const ::std::vector<::std::uint64_t>& _tile_ids)
    {
        tile_ids_ = _tile_ids;
    }

    const ::std::vector<LaneBoundaryInfo>* GetPtrLaneBoundaryInfo() const
    {
        return &lane_boundary_info_;
    }
    void SetLaneBoundaryInfo(const ::std::vector<LaneBoundaryInfo>& _lane_boundary_info)
    {
        lane_boundary_info_ = _lane_boundary_info;
    }

    ::std::uint64_t GetLeftLaneId() const
    {
        return left_lane_id_;
    }
    void SetLeftLaneId(const ::std::uint64_t _left_lane_id)
    {
        left_lane_id_ = _left_lane_id;
    }

    ::std::uint64_t GetRightLaneId() const
    {
        return right_lane_id_;
    }
    void SetRightLaneId(const ::std::uint64_t _right_lane_id)
    {
        right_lane_id_ = _right_lane_id;
    }

    ::std::uint64_t GetBoundarySeq() const
    {
        return boundary_seq_;
    }
    void SetBoundarySeq(const ::std::uint64_t _boundary_seq)
    {
        boundary_seq_ = _boundary_seq;
    }

    const ::std::vector<::std::uint64_t>* GetPtrPreLaneBoundaryIds() const
    {
        return &pre_lane_boundary_ids_;
    }
    void SetPreLaneBoundaryIds(const ::std::vector<::std::uint64_t>& _pre_lane_boundary_ids)
    {
        pre_lane_boundary_ids_ = _pre_lane_boundary_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrSuccLaneBoundaryIds() const
    {
        return &succ_lane_boundary_ids_;
    }
    void SetSuccLaneBoundaryIds(const ::std::vector<::std::uint64_t>& _succ_lane_boundary_ids)
    {
        succ_lane_boundary_ids_ = _succ_lane_boundary_ids;
    }

    ::std::uint64_t GetRoadId() const
    {
        return road_id_;
    }
    void SetRoadId(const ::std::uint64_t _road_id)
    {
        road_id_ = _road_id;
    }

    ::std::uint64_t GetLaneGroupId() const
    {
        return lane_group_id_;
    }
    void SetLaneGroupId(const ::std::uint64_t _lane_group_id)
    {
        lane_group_id_ = _lane_group_id;
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

    void ClearLaneBoundaryInfo()
    {
        lane_boundary_info_.clear();
    }
    void AddLaneBoundaryInfoElement(const LaneBoundaryInfo& _value)
    {
        lane_boundary_info_.push_back(_value);
    }
    void UniqueAddLaneBoundaryInfoElements(const ::std::vector<LaneBoundaryInfo>& _value)
    {
        UniqueAppend(lane_boundary_info_, _value);
    }

    void ClearPreLaneBoundaryIds()
    {
        pre_lane_boundary_ids_.clear();
    }
    void AddPreLaneBoundaryIdsElement(const ::std::uint64_t& _value)
    {
        pre_lane_boundary_ids_.push_back(_value);
    }
    void UniqueAddPreLaneBoundaryIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(pre_lane_boundary_ids_, _value);
    }

    void ClearSuccLaneBoundaryIds()
    {
        succ_lane_boundary_ids_.clear();
    }
    void AddSuccLaneBoundaryIdsElement(const ::std::uint64_t& _value)
    {
        succ_lane_boundary_ids_.push_back(_value);
    }
    void UniqueAddSuccLaneBoundaryIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(succ_lane_boundary_ids_, _value);
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





};  // class LaneBoundary

typedef ::std::shared_ptr<LaneBoundary> PtrLaneBoundary;
typedef const ::std::vector<LaneBoundary>* ConstRawPtrVecLaneBoundary;
typedef ::std::vector<LaneBoundary>* RawPtrVecLaneBoundary;
typedef ::std::shared_ptr<LaneBoundary const> ConstPtrLaneBoundary;
typedef ::std::shared_ptr<::std::vector<LaneBoundary> const> ConstPtrVecLaneBoundary;
typedef ::std::unordered_map<::std::uint64_t, PtrLaneBoundary> HashmapLaneBoundary;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_BASE_LANE_BOUNDARY_H_