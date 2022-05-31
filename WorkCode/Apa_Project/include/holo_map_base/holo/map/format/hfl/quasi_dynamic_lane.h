/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file quasi_dynamic_lane.h
 * @brief Auto generated code for QuasiDynamicLane format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_HFL_QUASI_DYNAMIC_LANE_H_
#define HOLO_MAP_FORMAT_HFL_QUASI_DYNAMIC_LANE_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/hfl/quasi_dynamic_lane.pb.h>

#include <holo/map/proto/common/coordinate.pb.h>

#include <holo/map/proto/common/geo_point.pb.h>

#include <holo/map/proto/common/geo_line.pb.h>

#include <holo/map/proto/base/geofence.pb.h>

#include <holo/map/proto/hfl/pavement_condition.pb.h>

#include <holo/map/proto/hfl/traffic_condition.pb.h>

#include <holo/map/proto/hfl/map_condition.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/coordinate.h>

#include <holo/map/format/common/geo_point.h>

#include <holo/map/format/common/geo_line.h>

#include <holo/map/format/base/geofence.h>

#include <holo/map/format/hfl/pavement_condition.h>

#include <holo/map/format/hfl/traffic_condition.h>

#include <holo/map/format/hfl/map_condition.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  QuasiDynamicLane: public Base
{
public:




private:
    ::std::uint64_t quasi_dynamic_lane_id_; 
    ::std::vector<PavementCondition> pavement_condition_; 
    ::std::vector<TrafficCondition> traffic_condition_; 
    ::std::vector<MapCondition> map_condition_; 
    ::std::vector<Geofence> geofence_condition_; 
    ::std::vector<::std::uint64_t> tile_ids_; 
    ::std::uint64_t associated_lane_id_; 
    Coordinate coordinate_; 
    ::std::uint32_t zone_id_; 
    ::std::uint32_t extra_zone_id_; 
    bool south_flag_; 
    ::std::vector<GeoPoint> geometry_points_; 
    ::std::map<::std::uint32_t, GeoLine> extra_geometry_points_; 

private:
    void DecodeProto(const ::holo::map::proto::hfl::QuasiDynamicLane& _proto_handler);
    ::holo::map::proto::hfl::QuasiDynamicLane EncodeProto();

public:
    QuasiDynamicLane();
    explicit QuasiDynamicLane(const ::holo::map::proto::hfl::QuasiDynamicLane& _proto_handler);
    // init all format data
    QuasiDynamicLane(const ::std::uint64_t _quasi_dynamic_lane_id,const ::std::vector<PavementCondition>& _pavement_condition,const ::std::vector<TrafficCondition>& _traffic_condition,const ::std::vector<MapCondition>& _map_condition,const ::std::vector<Geofence>& _geofence_condition,const ::std::vector<::std::uint64_t>& _tile_ids,const ::std::uint64_t _associated_lane_id,const Coordinate& _coordinate,const ::std::uint32_t _zone_id,const ::std::uint32_t _extra_zone_id,const bool _south_flag,const ::std::vector<GeoPoint>& _geometry_points,const ::std::map<::std::uint32_t, GeoLine>& _extra_geometry_points);
    ~QuasiDynamicLane();

    bool operator==(const ::holo::map::format::QuasiDynamicLane& _other) const;
    QuasiDynamicLane& operator=(const ::holo::map::proto::hfl::QuasiDynamicLane& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::hfl::QuasiDynamicLane GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetQuasiDynamicLaneId() const
    {
        return quasi_dynamic_lane_id_;
    }
    void SetQuasiDynamicLaneId(const ::std::uint64_t _quasi_dynamic_lane_id)
    {
        quasi_dynamic_lane_id_ = _quasi_dynamic_lane_id;
    }

    const ::std::vector<PavementCondition>* GetPtrPavementCondition() const
    {
        return &pavement_condition_;
    }
    void SetPavementCondition(const ::std::vector<PavementCondition>& _pavement_condition)
    {
        pavement_condition_ = _pavement_condition;
    }

    const ::std::vector<TrafficCondition>* GetPtrTrafficCondition() const
    {
        return &traffic_condition_;
    }
    void SetTrafficCondition(const ::std::vector<TrafficCondition>& _traffic_condition)
    {
        traffic_condition_ = _traffic_condition;
    }

    const ::std::vector<MapCondition>* GetPtrMapCondition() const
    {
        return &map_condition_;
    }
    void SetMapCondition(const ::std::vector<MapCondition>& _map_condition)
    {
        map_condition_ = _map_condition;
    }

    const ::std::vector<Geofence>* GetPtrGeofenceCondition() const
    {
        return &geofence_condition_;
    }
    void SetGeofenceCondition(const ::std::vector<Geofence>& _geofence_condition)
    {
        geofence_condition_ = _geofence_condition;
    }

    const ::std::vector<::std::uint64_t>* GetPtrTileIds() const
    {
        return &tile_ids_;
    }
    void SetTileIds(const ::std::vector<::std::uint64_t>& _tile_ids)
    {
        tile_ids_ = _tile_ids;
    }

    ::std::uint64_t GetAssociatedLaneId() const
    {
        return associated_lane_id_;
    }
    void SetAssociatedLaneId(const ::std::uint64_t _associated_lane_id)
    {
        associated_lane_id_ = _associated_lane_id;
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


    void ClearPavementCondition()
    {
        pavement_condition_.clear();
    }
    void AddPavementConditionElement(const PavementCondition& _value)
    {
        pavement_condition_.push_back(_value);
    }
    void UniqueAddPavementConditionElements(const ::std::vector<PavementCondition>& _value)
    {
        UniqueAppend(pavement_condition_, _value);
    }

    void ClearTrafficCondition()
    {
        traffic_condition_.clear();
    }
    void AddTrafficConditionElement(const TrafficCondition& _value)
    {
        traffic_condition_.push_back(_value);
    }
    void UniqueAddTrafficConditionElements(const ::std::vector<TrafficCondition>& _value)
    {
        UniqueAppend(traffic_condition_, _value);
    }

    void ClearMapCondition()
    {
        map_condition_.clear();
    }
    void AddMapConditionElement(const MapCondition& _value)
    {
        map_condition_.push_back(_value);
    }
    void UniqueAddMapConditionElements(const ::std::vector<MapCondition>& _value)
    {
        UniqueAppend(map_condition_, _value);
    }

    void ClearGeofenceCondition()
    {
        geofence_condition_.clear();
    }
    void AddGeofenceConditionElement(const Geofence& _value)
    {
        geofence_condition_.push_back(_value);
    }
    void UniqueAddGeofenceConditionElements(const ::std::vector<Geofence>& _value)
    {
        UniqueAppend(geofence_condition_, _value);
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





};  // class QuasiDynamicLane

typedef ::std::shared_ptr<QuasiDynamicLane> PtrQuasiDynamicLane;
typedef const ::std::vector<QuasiDynamicLane>* ConstRawPtrVecQuasiDynamicLane;
typedef ::std::vector<QuasiDynamicLane>* RawPtrVecQuasiDynamicLane;
typedef ::std::shared_ptr<QuasiDynamicLane const> ConstPtrQuasiDynamicLane;
typedef ::std::shared_ptr<::std::vector<QuasiDynamicLane> const> ConstPtrVecQuasiDynamicLane;
typedef ::std::unordered_map<::std::uint64_t, PtrQuasiDynamicLane> HashmapQuasiDynamicLane;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_HFL_QUASI_DYNAMIC_LANE_H_