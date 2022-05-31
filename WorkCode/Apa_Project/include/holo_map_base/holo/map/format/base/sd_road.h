/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file sd_road.h
 * @brief Auto generated code for SdRoad format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_BASE_SD_ROAD_H_
#define HOLO_MAP_FORMAT_BASE_SD_ROAD_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/base/sd_road.pb.h>

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

class  SdRoad: public Base
{
public:

        
    enum SdRoadType
    {
        SD_ROAD_TYPE_UNKNOWN=  0,  
    };

        
    enum SdRoadClass
    {
        SD_ROAD_CLASS_UNKNOWN=  0,  
    };

        
    enum SdRoadDirection
    {
        SD_ROAD_DIRECTION_UNDEFINED=  0,  
        SD_ROAD_DIRECTION_BIDIRECTIONAL=  1,  
        SD_ROAD_DIRECTION_POSITIVE_DIRECTION=  2,  
        SD_ROAD_DIRECTION_NEGATIVE_DIRECTION=  3,  
    };

    static const ::std::map<::std::string, SdRoadType>& ENUMSTR_SDROADTYPE() 
    { 
        static const ::std::map<::std::string, SdRoadType> data{
        { "UNKNOWN", SdRoadType::SD_ROAD_TYPE_UNKNOWN }};
        return data;
    }

    static const ::std::map<::std::string, SdRoadClass>& ENUMSTR_SDROADCLASS() 
    { 
        static const ::std::map<::std::string, SdRoadClass> data{
        { "UNKNOWN", SdRoadClass::SD_ROAD_CLASS_UNKNOWN }};
        return data;
    }

    static const ::std::map<::std::string, SdRoadDirection>& ENUMSTR_SDROADDIRECTION() 
    { 
        static const ::std::map<::std::string, SdRoadDirection> data{
        { "UNDEFINED", SdRoadDirection::SD_ROAD_DIRECTION_UNDEFINED },
        { "BIDIRECTIONAL", SdRoadDirection::SD_ROAD_DIRECTION_BIDIRECTIONAL },
        { "POSITIVE_DIRECTION", SdRoadDirection::SD_ROAD_DIRECTION_POSITIVE_DIRECTION },
        { "NEGATIVE_DIRECTION", SdRoadDirection::SD_ROAD_DIRECTION_NEGATIVE_DIRECTION }};
        return data;
    }


private:
    ::std::uint64_t sd_road_id_; 
    SdRoadType sd_road_type_; 
    SdRoadClass sd_road_class_; 
    SdRoadDirection sd_road_direction_; 
    ::std::uint32_t length_cm_; 
    ::std::uint32_t start_lane_number_; 
    ::std::uint32_t end_lane_number_; 
    ::std::uint64_t start_node_id_; 
    ::std::uint64_t end_node_id_; 
    ::std::vector<::std::uint64_t> tile_ids_; 
    Coordinate coordinate_; 
    ::std::uint32_t zone_id_; 
    ::std::uint32_t extra_zone_id_; 
    bool south_flag_; 
    ::std::vector<GeoPoint> geometry_points_; 
    ::std::map<::std::uint32_t, GeoLine> extra_geometry_points_; 

private:
    void DecodeProto(const ::holo::map::proto::base::SdRoad& _proto_handler);
    ::holo::map::proto::base::SdRoad EncodeProto();

public:
    SdRoad();
    explicit SdRoad(const ::holo::map::proto::base::SdRoad& _proto_handler);
    // init all format data
    SdRoad(const ::std::uint64_t _sd_road_id,const SdRoadType& _sd_road_type,const SdRoadClass& _sd_road_class,const SdRoadDirection& _sd_road_direction,const ::std::uint32_t _length_cm,const ::std::uint32_t _start_lane_number,const ::std::uint32_t _end_lane_number,const ::std::uint64_t _start_node_id,const ::std::uint64_t _end_node_id,const ::std::vector<::std::uint64_t>& _tile_ids,const Coordinate& _coordinate,const ::std::uint32_t _zone_id,const ::std::uint32_t _extra_zone_id,const bool _south_flag,const ::std::vector<GeoPoint>& _geometry_points,const ::std::map<::std::uint32_t, GeoLine>& _extra_geometry_points);
    ~SdRoad();

    bool operator==(const ::holo::map::format::SdRoad& _other) const;
    SdRoad& operator=(const ::holo::map::proto::base::SdRoad& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::base::SdRoad GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetSdRoadId() const
    {
        return sd_road_id_;
    }
    void SetSdRoadId(const ::std::uint64_t _sd_road_id)
    {
        sd_road_id_ = _sd_road_id;
    }

    const SdRoadType& GetSdRoadType() const
    {
        return sd_road_type_;
    }
    void SetSdRoadType(const SdRoadType& _sd_road_type)
    {
        sd_road_type_ = _sd_road_type;
    }

    const SdRoadClass& GetSdRoadClass() const
    {
        return sd_road_class_;
    }
    void SetSdRoadClass(const SdRoadClass& _sd_road_class)
    {
        sd_road_class_ = _sd_road_class;
    }

    const SdRoadDirection& GetSdRoadDirection() const
    {
        return sd_road_direction_;
    }
    void SetSdRoadDirection(const SdRoadDirection& _sd_road_direction)
    {
        sd_road_direction_ = _sd_road_direction;
    }

    ::std::uint32_t GetLengthCm() const
    {
        return length_cm_;
    }
    void SetLengthCm(const ::std::uint32_t _length_cm)
    {
        length_cm_ = _length_cm;
    }

    ::std::uint32_t GetStartLaneNumber() const
    {
        return start_lane_number_;
    }
    void SetStartLaneNumber(const ::std::uint32_t _start_lane_number)
    {
        start_lane_number_ = _start_lane_number;
    }

    ::std::uint32_t GetEndLaneNumber() const
    {
        return end_lane_number_;
    }
    void SetEndLaneNumber(const ::std::uint32_t _end_lane_number)
    {
        end_lane_number_ = _end_lane_number;
    }

    ::std::uint64_t GetStartNodeId() const
    {
        return start_node_id_;
    }
    void SetStartNodeId(const ::std::uint64_t _start_node_id)
    {
        start_node_id_ = _start_node_id;
    }

    ::std::uint64_t GetEndNodeId() const
    {
        return end_node_id_;
    }
    void SetEndNodeId(const ::std::uint64_t _end_node_id)
    {
        end_node_id_ = _end_node_id;
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





};  // class SdRoad

typedef ::std::shared_ptr<SdRoad> PtrSdRoad;
typedef const ::std::vector<SdRoad>* ConstRawPtrVecSdRoad;
typedef ::std::vector<SdRoad>* RawPtrVecSdRoad;
typedef ::std::shared_ptr<SdRoad const> ConstPtrSdRoad;
typedef ::std::shared_ptr<::std::vector<SdRoad> const> ConstPtrVecSdRoad;
typedef ::std::unordered_map<::std::uint64_t, PtrSdRoad> HashmapSdRoad;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_BASE_SD_ROAD_H_