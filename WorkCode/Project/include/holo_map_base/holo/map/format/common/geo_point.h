/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file geo_point.h
 * @brief Auto generated code for GeoPoint format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_COMMON_GEO_POINT_H_
#define HOLO_MAP_FORMAT_COMMON_GEO_POINT_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/common/geo_point.pb.h>


#include <holo/map/format/base/base.h>


#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  GeoPoint: public Base
{
public:




private:
    ::std::int64_t height_cm_; 
    double x_; 
    double y_; 

private:
    void DecodeProto(const ::holo::map::proto::common::GeoPoint& _proto_handler);
    ::holo::map::proto::common::GeoPoint EncodeProto();

public:
    GeoPoint();
    explicit GeoPoint(const ::holo::map::proto::common::GeoPoint& _proto_handler);
    // init all format data
    GeoPoint(const ::std::int64_t _height_cm,const double _x,const double _y);
    ~GeoPoint();

    bool operator==(const ::holo::map::format::GeoPoint& _other) const;
    GeoPoint& operator=(const ::holo::map::proto::common::GeoPoint& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::common::GeoPoint GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::int64_t GetHeightCm() const
    {
        return height_cm_;
    }
    void SetHeightCm(const ::std::int64_t _height_cm)
    {
        height_cm_ = _height_cm;
    }

    double GetX() const
    {
        return x_;
    }
    void SetX(const double _x)
    {
        x_ = _x;
    }

    double GetY() const
    {
        return y_;
    }
    void SetY(const double _y)
    {
        y_ = _y;
    }











};  // class GeoPoint

typedef ::std::shared_ptr<GeoPoint> PtrGeoPoint;
typedef const ::std::vector<GeoPoint>* ConstRawPtrVecGeoPoint;
typedef ::std::vector<GeoPoint>* RawPtrVecGeoPoint;
typedef ::std::shared_ptr<GeoPoint const> ConstPtrGeoPoint;
typedef ::std::shared_ptr<::std::vector<GeoPoint> const> ConstPtrVecGeoPoint;
typedef ::std::unordered_map<::std::uint64_t, PtrGeoPoint> HashmapGeoPoint;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_COMMON_GEO_POINT_H_