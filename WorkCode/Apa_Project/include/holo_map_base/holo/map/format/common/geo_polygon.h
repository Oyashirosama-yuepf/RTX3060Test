/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file geo_polygon.h
 * @brief Auto generated code for GeoPolygon format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_COMMON_GEO_POLYGON_H_
#define HOLO_MAP_FORMAT_COMMON_GEO_POLYGON_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/common/geo_polygon.pb.h>

#include <holo/map/proto/common/geo_point.pb.h>

#include <holo/map/proto/common/geo_line.pb.h>

#include <holo/map/proto/common/geo_multi_line.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/geo_point.h>

#include <holo/map/format/common/geo_line.h>

#include <holo/map/format/common/geo_multi_line.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  GeoPolygon: public Base
{
public:




private:
    ::std::vector<GeoPoint> vertices_; 
    GeoLine exterior_ring_; 
    GeoMultiLine internal_rings_; 

private:
    void DecodeProto(const ::holo::map::proto::common::GeoPolygon& _proto_handler);
    ::holo::map::proto::common::GeoPolygon EncodeProto();

public:
    GeoPolygon();
    explicit GeoPolygon(const ::holo::map::proto::common::GeoPolygon& _proto_handler);
    // init all format data
    GeoPolygon(const ::std::vector<GeoPoint>& _vertices,const GeoLine& _exterior_ring,const GeoMultiLine& _internal_rings);
    ~GeoPolygon();

    bool operator==(const ::holo::map::format::GeoPolygon& _other) const;
    GeoPolygon& operator=(const ::holo::map::proto::common::GeoPolygon& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::common::GeoPolygon GetProtoHandler()
    {
        return EncodeProto();
    }

    


    const ::std::vector<GeoPoint>* GetPtrVertices() const
    {
        return &vertices_;
    }
    void SetVertices(const ::std::vector<GeoPoint>& _vertices)
    {
        vertices_ = _vertices;
    }

    const GeoLine& GetExteriorRing() const
    {
        return exterior_ring_;
    }
    void SetExteriorRing(const GeoLine& _exterior_ring)
    {
        exterior_ring_ = _exterior_ring;
    }

    const GeoMultiLine& GetInternalRings() const
    {
        return internal_rings_;
    }
    void SetInternalRings(const GeoMultiLine& _internal_rings)
    {
        internal_rings_ = _internal_rings;
    }


    void ClearVertices()
    {
        vertices_.clear();
    }
    void AddVerticesElement(const GeoPoint& _value)
    {
        vertices_.push_back(_value);
    }
    void UniqueAddVerticesElements(const ::std::vector<GeoPoint>& _value)
    {
        UniqueAppend(vertices_, _value);
    }









};  // class GeoPolygon

typedef ::std::shared_ptr<GeoPolygon> PtrGeoPolygon;
typedef const ::std::vector<GeoPolygon>* ConstRawPtrVecGeoPolygon;
typedef ::std::vector<GeoPolygon>* RawPtrVecGeoPolygon;
typedef ::std::shared_ptr<GeoPolygon const> ConstPtrGeoPolygon;
typedef ::std::shared_ptr<::std::vector<GeoPolygon> const> ConstPtrVecGeoPolygon;
typedef ::std::unordered_map<::std::uint64_t, PtrGeoPolygon> HashmapGeoPolygon;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_COMMON_GEO_POLYGON_H_