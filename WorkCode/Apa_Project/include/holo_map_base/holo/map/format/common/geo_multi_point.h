/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file geo_multi_point.h
 * @brief Auto generated code for GeoMultiPoint format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_COMMON_GEO_MULTI_POINT_H_
#define HOLO_MAP_FORMAT_COMMON_GEO_MULTI_POINT_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/common/geo_multi_point.pb.h>

#include <holo/map/proto/common/geo_point.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/geo_point.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  GeoMultiPoint: public Base
{
public:




private:
    ::std::vector<GeoPoint> points_; 

private:
    void DecodeProto(const ::holo::map::proto::common::GeoMultiPoint& _proto_handler);
    ::holo::map::proto::common::GeoMultiPoint EncodeProto();

public:
    GeoMultiPoint();
    explicit GeoMultiPoint(const ::holo::map::proto::common::GeoMultiPoint& _proto_handler);
    // init all format data
    GeoMultiPoint(const ::std::vector<GeoPoint>& _points);
    ~GeoMultiPoint();

    bool operator==(const ::holo::map::format::GeoMultiPoint& _other) const;
    GeoMultiPoint& operator=(const ::holo::map::proto::common::GeoMultiPoint& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::common::GeoMultiPoint GetProtoHandler()
    {
        return EncodeProto();
    }

    


    const ::std::vector<GeoPoint>* GetPtrPoints() const
    {
        return &points_;
    }
    void SetPoints(const ::std::vector<GeoPoint>& _points)
    {
        points_ = _points;
    }


    void ClearPoints()
    {
        points_.clear();
    }
    void AddPointsElement(const GeoPoint& _value)
    {
        points_.push_back(_value);
    }
    void UniqueAddPointsElements(const ::std::vector<GeoPoint>& _value)
    {
        UniqueAppend(points_, _value);
    }









};  // class GeoMultiPoint

typedef ::std::shared_ptr<GeoMultiPoint> PtrGeoMultiPoint;
typedef const ::std::vector<GeoMultiPoint>* ConstRawPtrVecGeoMultiPoint;
typedef ::std::vector<GeoMultiPoint>* RawPtrVecGeoMultiPoint;
typedef ::std::shared_ptr<GeoMultiPoint const> ConstPtrGeoMultiPoint;
typedef ::std::shared_ptr<::std::vector<GeoMultiPoint> const> ConstPtrVecGeoMultiPoint;
typedef ::std::unordered_map<::std::uint64_t, PtrGeoMultiPoint> HashmapGeoMultiPoint;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_COMMON_GEO_MULTI_POINT_H_