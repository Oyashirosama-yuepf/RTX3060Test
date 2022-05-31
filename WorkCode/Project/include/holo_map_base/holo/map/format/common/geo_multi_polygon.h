/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file geo_multi_polygon.h
 * @brief Auto generated code for GeoMultiPolygon format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_COMMON_GEO_MULTI_POLYGON_H_
#define HOLO_MAP_FORMAT_COMMON_GEO_MULTI_POLYGON_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/common/geo_multi_polygon.pb.h>

#include <holo/map/proto/common/geo_polygon.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/geo_polygon.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  GeoMultiPolygon: public Base
{
public:




private:
    ::std::vector<GeoPolygon> polygons_; 

private:
    void DecodeProto(const ::holo::map::proto::common::GeoMultiPolygon& _proto_handler);
    ::holo::map::proto::common::GeoMultiPolygon EncodeProto();

public:
    GeoMultiPolygon();
    explicit GeoMultiPolygon(const ::holo::map::proto::common::GeoMultiPolygon& _proto_handler);
    // init all format data
    GeoMultiPolygon(const ::std::vector<GeoPolygon>& _polygons);
    ~GeoMultiPolygon();

    bool operator==(const ::holo::map::format::GeoMultiPolygon& _other) const;
    GeoMultiPolygon& operator=(const ::holo::map::proto::common::GeoMultiPolygon& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::common::GeoMultiPolygon GetProtoHandler()
    {
        return EncodeProto();
    }

    


    const ::std::vector<GeoPolygon>* GetPtrPolygons() const
    {
        return &polygons_;
    }
    void SetPolygons(const ::std::vector<GeoPolygon>& _polygons)
    {
        polygons_ = _polygons;
    }


    void ClearPolygons()
    {
        polygons_.clear();
    }
    void AddPolygonsElement(const GeoPolygon& _value)
    {
        polygons_.push_back(_value);
    }
    void UniqueAddPolygonsElements(const ::std::vector<GeoPolygon>& _value)
    {
        UniqueAppend(polygons_, _value);
    }









};  // class GeoMultiPolygon

typedef ::std::shared_ptr<GeoMultiPolygon> PtrGeoMultiPolygon;
typedef const ::std::vector<GeoMultiPolygon>* ConstRawPtrVecGeoMultiPolygon;
typedef ::std::vector<GeoMultiPolygon>* RawPtrVecGeoMultiPolygon;
typedef ::std::shared_ptr<GeoMultiPolygon const> ConstPtrGeoMultiPolygon;
typedef ::std::shared_ptr<::std::vector<GeoMultiPolygon> const> ConstPtrVecGeoMultiPolygon;
typedef ::std::unordered_map<::std::uint64_t, PtrGeoMultiPolygon> HashmapGeoMultiPolygon;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_COMMON_GEO_MULTI_POLYGON_H_