/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file sd_node.h
 * @brief Auto generated code for SdNode format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_BASE_SD_NODE_H_
#define HOLO_MAP_FORMAT_BASE_SD_NODE_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/base/sd_node.pb.h>

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

class  SdNode: public Base
{
public:




private:
    ::std::uint64_t sd_node_id_; 
    ::std::vector<::std::uint64_t> tile_ids_; 
    Coordinate coordinate_; 
    ::std::uint32_t zone_id_; 
    ::std::uint32_t extra_zone_id_; 
    bool south_flag_; 
    ::std::vector<GeoPoint> geometry_points_; 
    ::std::map<::std::uint32_t, GeoLine> extra_geometry_points_; 

private:
    void DecodeProto(const ::holo::map::proto::base::SdNode& _proto_handler);
    ::holo::map::proto::base::SdNode EncodeProto();

public:
    SdNode();
    explicit SdNode(const ::holo::map::proto::base::SdNode& _proto_handler);
    // init all format data
    SdNode(const ::std::uint64_t _sd_node_id,const ::std::vector<::std::uint64_t>& _tile_ids,const Coordinate& _coordinate,const ::std::uint32_t _zone_id,const ::std::uint32_t _extra_zone_id,const bool _south_flag,const ::std::vector<GeoPoint>& _geometry_points,const ::std::map<::std::uint32_t, GeoLine>& _extra_geometry_points);
    ~SdNode();

    bool operator==(const ::holo::map::format::SdNode& _other) const;
    SdNode& operator=(const ::holo::map::proto::base::SdNode& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::base::SdNode GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetSdNodeId() const
    {
        return sd_node_id_;
    }
    void SetSdNodeId(const ::std::uint64_t _sd_node_id)
    {
        sd_node_id_ = _sd_node_id;
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





};  // class SdNode

typedef ::std::shared_ptr<SdNode> PtrSdNode;
typedef const ::std::vector<SdNode>* ConstRawPtrVecSdNode;
typedef ::std::vector<SdNode>* RawPtrVecSdNode;
typedef ::std::shared_ptr<SdNode const> ConstPtrSdNode;
typedef ::std::shared_ptr<::std::vector<SdNode> const> ConstPtrVecSdNode;
typedef ::std::unordered_map<::std::uint64_t, PtrSdNode> HashmapSdNode;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_BASE_SD_NODE_H_