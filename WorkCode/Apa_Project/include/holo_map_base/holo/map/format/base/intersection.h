/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file intersection.h
 * @brief Auto generated code for Intersection format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_BASE_INTERSECTION_H_
#define HOLO_MAP_FORMAT_BASE_INTERSECTION_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/base/intersection.pb.h>

#include <holo/map/proto/common/connection_v2.pb.h>

#include <holo/map/proto/common/geo_polygon.pb.h>

#include <holo/map/proto/common/coordinate.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/connection_v2.h>

#include <holo/map/format/common/geo_polygon.h>

#include <holo/map/format/common/coordinate.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  Intersection: public Base
{
public:

        
    enum Type
    {
        TYPE_UNDEFINED=  0,  
        TYPE_CROSSROAD=  1,  
        TYPE_T_JUNCTION=  2,  
        TYPE_Y_JUNCTION=  3,  
        TYPE_MULTI_FORK_JUNCTION=  4,  
        TYPE_ROUNDABOUT=  5,  
        TYPE_RESERVE_1=  250,  
        TYPE_RESERVE_2=  251,  
        TYPE_RESERVE_3=  252,  
        TYPE_RESERVE_4=  253,  
        TYPE_RESERVE_5=  254,  
        TYPE_OTHERS=  255,  
    };

    static const ::std::map<::std::string, Type>& ENUMSTR_TYPE() 
    { 
        static const ::std::map<::std::string, Type> data{
        { "UNDEFINED", Type::TYPE_UNDEFINED },
        { "CROSSROAD", Type::TYPE_CROSSROAD },
        { "T_JUNCTION", Type::TYPE_T_JUNCTION },
        { "Y_JUNCTION", Type::TYPE_Y_JUNCTION },
        { "MULTI_FORK_JUNCTION", Type::TYPE_MULTI_FORK_JUNCTION },
        { "ROUNDABOUT", Type::TYPE_ROUNDABOUT },
        { "RESERVE_1", Type::TYPE_RESERVE_1 },
        { "RESERVE_2", Type::TYPE_RESERVE_2 },
        { "RESERVE_3", Type::TYPE_RESERVE_3 },
        { "RESERVE_4", Type::TYPE_RESERVE_4 },
        { "RESERVE_5", Type::TYPE_RESERVE_5 },
        { "OTHERS", Type::TYPE_OTHERS }};
        return data;
    }


private:
    ::std::uint64_t intersection_id_; 
    bool has_geometry_; 
    Type type_; 
    ::std::uint64_t intersection_group_id_; 
    ::std::vector<ConnectionV2> lane_connections_; 
    ::std::vector<ConnectionV2> link_connections_; 
    GeoPolygon geometry_points_; 
    Coordinate coordinate_; 
    ::std::vector<::std::uint64_t> tile_ids_; 
    ::std::vector<::std::uint64_t> associated_stop_lines_; 
    ::std::vector<::std::uint64_t> associated_traffic_lights_; 
    ::std::vector<::std::uint64_t> associated_safe_islands_; 
    ::std::vector<::std::uint64_t> associated_pedestrian_crosswalk_; 
    ::std::vector<::std::uint64_t> associated_parking_space_; 

private:
    void DecodeProto(const ::holo::map::proto::base::Intersection& _proto_handler);
    ::holo::map::proto::base::Intersection EncodeProto();

public:
    Intersection();
    explicit Intersection(const ::holo::map::proto::base::Intersection& _proto_handler);
    // init all format data
    Intersection(const ::std::uint64_t _intersection_id,const bool _has_geometry,const Type& _type,const ::std::uint64_t _intersection_group_id,const ::std::vector<ConnectionV2>& _lane_connections,const ::std::vector<ConnectionV2>& _link_connections,const GeoPolygon& _geometry_points,const Coordinate& _coordinate,const ::std::vector<::std::uint64_t>& _tile_ids,const ::std::vector<::std::uint64_t>& _associated_stop_lines,const ::std::vector<::std::uint64_t>& _associated_traffic_lights,const ::std::vector<::std::uint64_t>& _associated_safe_islands,const ::std::vector<::std::uint64_t>& _associated_pedestrian_crosswalk,const ::std::vector<::std::uint64_t>& _associated_parking_space);
    ~Intersection();

    bool operator==(const ::holo::map::format::Intersection& _other) const;
    Intersection& operator=(const ::holo::map::proto::base::Intersection& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::base::Intersection GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetIntersectionId() const
    {
        return intersection_id_;
    }
    void SetIntersectionId(const ::std::uint64_t _intersection_id)
    {
        intersection_id_ = _intersection_id;
    }

    bool GetHasGeometry() const
    {
        return has_geometry_;
    }
    void SetHasGeometry(const bool _has_geometry)
    {
        has_geometry_ = _has_geometry;
    }

    const Type& GetType() const
    {
        return type_;
    }
    void SetType(const Type& _type)
    {
        type_ = _type;
    }

    ::std::uint64_t GetIntersectionGroupId() const
    {
        return intersection_group_id_;
    }
    void SetIntersectionGroupId(const ::std::uint64_t _intersection_group_id)
    {
        intersection_group_id_ = _intersection_group_id;
    }

    const ::std::vector<ConnectionV2>* GetPtrLaneConnections() const
    {
        return &lane_connections_;
    }
    void SetLaneConnections(const ::std::vector<ConnectionV2>& _lane_connections)
    {
        lane_connections_ = _lane_connections;
    }

    const ::std::vector<ConnectionV2>* GetPtrLinkConnections() const
    {
        return &link_connections_;
    }
    void SetLinkConnections(const ::std::vector<ConnectionV2>& _link_connections)
    {
        link_connections_ = _link_connections;
    }

    const GeoPolygon& GetGeometryPoints() const
    {
        return geometry_points_;
    }
    void SetGeometryPoints(const GeoPolygon& _geometry_points)
    {
        geometry_points_ = _geometry_points;
    }

    const Coordinate& GetCoordinate() const
    {
        return coordinate_;
    }
    void SetCoordinate(const Coordinate& _coordinate)
    {
        coordinate_ = _coordinate;
    }

    const ::std::vector<::std::uint64_t>* GetPtrTileIds() const
    {
        return &tile_ids_;
    }
    void SetTileIds(const ::std::vector<::std::uint64_t>& _tile_ids)
    {
        tile_ids_ = _tile_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrAssociatedStopLines() const
    {
        return &associated_stop_lines_;
    }
    void SetAssociatedStopLines(const ::std::vector<::std::uint64_t>& _associated_stop_lines)
    {
        associated_stop_lines_ = _associated_stop_lines;
    }

    const ::std::vector<::std::uint64_t>* GetPtrAssociatedTrafficLights() const
    {
        return &associated_traffic_lights_;
    }
    void SetAssociatedTrafficLights(const ::std::vector<::std::uint64_t>& _associated_traffic_lights)
    {
        associated_traffic_lights_ = _associated_traffic_lights;
    }

    const ::std::vector<::std::uint64_t>* GetPtrAssociatedSafeIslands() const
    {
        return &associated_safe_islands_;
    }
    void SetAssociatedSafeIslands(const ::std::vector<::std::uint64_t>& _associated_safe_islands)
    {
        associated_safe_islands_ = _associated_safe_islands;
    }

    const ::std::vector<::std::uint64_t>* GetPtrAssociatedPedestrianCrosswalk() const
    {
        return &associated_pedestrian_crosswalk_;
    }
    void SetAssociatedPedestrianCrosswalk(const ::std::vector<::std::uint64_t>& _associated_pedestrian_crosswalk)
    {
        associated_pedestrian_crosswalk_ = _associated_pedestrian_crosswalk;
    }

    const ::std::vector<::std::uint64_t>* GetPtrAssociatedParkingSpace() const
    {
        return &associated_parking_space_;
    }
    void SetAssociatedParkingSpace(const ::std::vector<::std::uint64_t>& _associated_parking_space)
    {
        associated_parking_space_ = _associated_parking_space;
    }


    void ClearLaneConnections()
    {
        lane_connections_.clear();
    }
    void AddLaneConnectionsElement(const ConnectionV2& _value)
    {
        lane_connections_.push_back(_value);
    }
    void UniqueAddLaneConnectionsElements(const ::std::vector<ConnectionV2>& _value)
    {
        UniqueAppend(lane_connections_, _value);
    }

    void ClearLinkConnections()
    {
        link_connections_.clear();
    }
    void AddLinkConnectionsElement(const ConnectionV2& _value)
    {
        link_connections_.push_back(_value);
    }
    void UniqueAddLinkConnectionsElements(const ::std::vector<ConnectionV2>& _value)
    {
        UniqueAppend(link_connections_, _value);
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

    void ClearAssociatedStopLines()
    {
        associated_stop_lines_.clear();
    }
    void AddAssociatedStopLinesElement(const ::std::uint64_t& _value)
    {
        associated_stop_lines_.push_back(_value);
    }
    void UniqueAddAssociatedStopLinesElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(associated_stop_lines_, _value);
    }

    void ClearAssociatedTrafficLights()
    {
        associated_traffic_lights_.clear();
    }
    void AddAssociatedTrafficLightsElement(const ::std::uint64_t& _value)
    {
        associated_traffic_lights_.push_back(_value);
    }
    void UniqueAddAssociatedTrafficLightsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(associated_traffic_lights_, _value);
    }

    void ClearAssociatedSafeIslands()
    {
        associated_safe_islands_.clear();
    }
    void AddAssociatedSafeIslandsElement(const ::std::uint64_t& _value)
    {
        associated_safe_islands_.push_back(_value);
    }
    void UniqueAddAssociatedSafeIslandsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(associated_safe_islands_, _value);
    }

    void ClearAssociatedPedestrianCrosswalk()
    {
        associated_pedestrian_crosswalk_.clear();
    }
    void AddAssociatedPedestrianCrosswalkElement(const ::std::uint64_t& _value)
    {
        associated_pedestrian_crosswalk_.push_back(_value);
    }
    void UniqueAddAssociatedPedestrianCrosswalkElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(associated_pedestrian_crosswalk_, _value);
    }

    void ClearAssociatedParkingSpace()
    {
        associated_parking_space_.clear();
    }
    void AddAssociatedParkingSpaceElement(const ::std::uint64_t& _value)
    {
        associated_parking_space_.push_back(_value);
    }
    void UniqueAddAssociatedParkingSpaceElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(associated_parking_space_, _value);
    }









};  // class Intersection

typedef ::std::shared_ptr<Intersection> PtrIntersection;
typedef const ::std::vector<Intersection>* ConstRawPtrVecIntersection;
typedef ::std::vector<Intersection>* RawPtrVecIntersection;
typedef ::std::shared_ptr<Intersection const> ConstPtrIntersection;
typedef ::std::shared_ptr<::std::vector<Intersection> const> ConstPtrVecIntersection;
typedef ::std::unordered_map<::std::uint64_t, PtrIntersection> HashmapIntersection;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_BASE_INTERSECTION_H_