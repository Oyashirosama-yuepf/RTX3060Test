/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file geo_circle.h
 * @brief Auto generated code for GeoCircle format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_COMMON_GEO_CIRCLE_H_
#define HOLO_MAP_FORMAT_COMMON_GEO_CIRCLE_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/common/geo_circle.pb.h>

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

class  GeoCircle: public Base
{
public:




private:
    GeoPoint center_point_; 
    double range_; 

private:
    void DecodeProto(const ::holo::map::proto::common::GeoCircle& _proto_handler);
    ::holo::map::proto::common::GeoCircle EncodeProto();

public:
    GeoCircle();
    explicit GeoCircle(const ::holo::map::proto::common::GeoCircle& _proto_handler);
    // init all format data
    GeoCircle(const GeoPoint& _center_point,const double _range);
    ~GeoCircle();

    bool operator==(const ::holo::map::format::GeoCircle& _other) const;
    GeoCircle& operator=(const ::holo::map::proto::common::GeoCircle& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::common::GeoCircle GetProtoHandler()
    {
        return EncodeProto();
    }

    


    const GeoPoint& GetCenterPoint() const
    {
        return center_point_;
    }
    void SetCenterPoint(const GeoPoint& _center_point)
    {
        center_point_ = _center_point;
    }

    double GetRange() const
    {
        return range_;
    }
    void SetRange(const double _range)
    {
        range_ = _range;
    }











};  // class GeoCircle

typedef ::std::shared_ptr<GeoCircle> PtrGeoCircle;
typedef const ::std::vector<GeoCircle>* ConstRawPtrVecGeoCircle;
typedef ::std::vector<GeoCircle>* RawPtrVecGeoCircle;
typedef ::std::shared_ptr<GeoCircle const> ConstPtrGeoCircle;
typedef ::std::shared_ptr<::std::vector<GeoCircle> const> ConstPtrVecGeoCircle;
typedef ::std::unordered_map<::std::uint64_t, PtrGeoCircle> HashmapGeoCircle;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_COMMON_GEO_CIRCLE_H_