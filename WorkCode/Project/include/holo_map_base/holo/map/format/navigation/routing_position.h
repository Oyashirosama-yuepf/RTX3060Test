/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file routing_position.h
 * @brief Auto generated code for RoutingPosition format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_NAVIGATION_ROUTING_POSITION_H_
#define HOLO_MAP_FORMAT_NAVIGATION_ROUTING_POSITION_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/navigation/routing_position.pb.h>

#include <holo/map/proto/common/coordinate.pb.h>

#include <holo/map/proto/common/geo_point.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/coordinate.h>

#include <holo/map/format/common/geo_point.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  RoutingPosition: public Base
{
public:




private:
    Coordinate coordinate_; 
    ::std::uint32_t pos_zone_id_; 
    bool pos_south_flag_; 
    GeoPoint pos_position_; 
    ::std::uint64_t poi_id_; 
    ::std::uint64_t link_id_; 
    ::std::uint64_t object_parking_floor_id_; 
    ::std::uint64_t object_parking_lot_id_; 
    ::std::uint32_t distance_cm_; 

private:
    void DecodeProto(const ::holo::map::proto::navigation::RoutingPosition& _proto_handler);
    ::holo::map::proto::navigation::RoutingPosition EncodeProto();

public:
    RoutingPosition();
    explicit RoutingPosition(const ::holo::map::proto::navigation::RoutingPosition& _proto_handler);
    // init all format data
    RoutingPosition(const Coordinate& _coordinate,const ::std::uint32_t _pos_zone_id,const bool _pos_south_flag,const GeoPoint& _pos_position,const ::std::uint64_t _poi_id,const ::std::uint64_t _link_id,const ::std::uint64_t _object_parking_floor_id,const ::std::uint64_t _object_parking_lot_id,const ::std::uint32_t _distance_cm);
    ~RoutingPosition();

    bool operator==(const ::holo::map::format::RoutingPosition& _other) const;
    RoutingPosition& operator=(const ::holo::map::proto::navigation::RoutingPosition& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::navigation::RoutingPosition GetProtoHandler()
    {
        return EncodeProto();
    }

    


    const Coordinate& GetCoordinate() const
    {
        return coordinate_;
    }
    void SetCoordinate(const Coordinate& _coordinate)
    {
        coordinate_ = _coordinate;
    }

    ::std::uint32_t GetPosZoneId() const
    {
        return pos_zone_id_;
    }
    void SetPosZoneId(const ::std::uint32_t _pos_zone_id)
    {
        pos_zone_id_ = _pos_zone_id;
    }

    bool GetPosSouthFlag() const
    {
        return pos_south_flag_;
    }
    void SetPosSouthFlag(const bool _pos_south_flag)
    {
        pos_south_flag_ = _pos_south_flag;
    }

    const GeoPoint& GetPosPosition() const
    {
        return pos_position_;
    }
    void SetPosPosition(const GeoPoint& _pos_position)
    {
        pos_position_ = _pos_position;
    }

    ::std::uint64_t GetPoiId() const
    {
        return poi_id_;
    }
    void SetPoiId(const ::std::uint64_t _poi_id)
    {
        poi_id_ = _poi_id;
    }

    ::std::uint64_t GetLinkId() const
    {
        return link_id_;
    }
    void SetLinkId(const ::std::uint64_t _link_id)
    {
        link_id_ = _link_id;
    }

    ::std::uint64_t GetObjectParkingFloorId() const
    {
        return object_parking_floor_id_;
    }
    void SetObjectParkingFloorId(const ::std::uint64_t _object_parking_floor_id)
    {
        object_parking_floor_id_ = _object_parking_floor_id;
    }

    ::std::uint64_t GetObjectParkingLotId() const
    {
        return object_parking_lot_id_;
    }
    void SetObjectParkingLotId(const ::std::uint64_t _object_parking_lot_id)
    {
        object_parking_lot_id_ = _object_parking_lot_id;
    }

    ::std::uint32_t GetDistanceCm() const
    {
        return distance_cm_;
    }
    void SetDistanceCm(const ::std::uint32_t _distance_cm)
    {
        distance_cm_ = _distance_cm;
    }











};  // class RoutingPosition

typedef ::std::shared_ptr<RoutingPosition> PtrRoutingPosition;
typedef const ::std::vector<RoutingPosition>* ConstRawPtrVecRoutingPosition;
typedef ::std::vector<RoutingPosition>* RawPtrVecRoutingPosition;
typedef ::std::shared_ptr<RoutingPosition const> ConstPtrRoutingPosition;
typedef ::std::shared_ptr<::std::vector<RoutingPosition> const> ConstPtrVecRoutingPosition;
typedef ::std::unordered_map<::std::uint64_t, PtrRoutingPosition> HashmapRoutingPosition;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_NAVIGATION_ROUTING_POSITION_H_