/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file geo_box4.h
 * @brief Auto generated code for GeoBox4 format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_COMMON_GEO_BOX4_H_
#define HOLO_MAP_FORMAT_COMMON_GEO_BOX4_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/common/geo_box4.pb.h>

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

class  GeoBox4: public Base
{
public:




private:
    GeoPoint left_back_bottom_; 
    GeoPoint left_back_top_; 
    GeoPoint right_forward_top_; 
    GeoPoint right_forward_bottom_; 

private:
    void DecodeProto(const ::holo::map::proto::common::GeoBox4& _proto_handler);
    ::holo::map::proto::common::GeoBox4 EncodeProto();

public:
    GeoBox4();
    explicit GeoBox4(const ::holo::map::proto::common::GeoBox4& _proto_handler);
    // init all format data
    GeoBox4(const GeoPoint& _left_back_bottom,const GeoPoint& _left_back_top,const GeoPoint& _right_forward_top,const GeoPoint& _right_forward_bottom);
    ~GeoBox4();

    bool operator==(const ::holo::map::format::GeoBox4& _other) const;
    GeoBox4& operator=(const ::holo::map::proto::common::GeoBox4& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::common::GeoBox4 GetProtoHandler()
    {
        return EncodeProto();
    }

    


    const GeoPoint& GetLeftBackBottom() const
    {
        return left_back_bottom_;
    }
    void SetLeftBackBottom(const GeoPoint& _left_back_bottom)
    {
        left_back_bottom_ = _left_back_bottom;
    }

    const GeoPoint& GetLeftBackTop() const
    {
        return left_back_top_;
    }
    void SetLeftBackTop(const GeoPoint& _left_back_top)
    {
        left_back_top_ = _left_back_top;
    }

    const GeoPoint& GetRightForwardTop() const
    {
        return right_forward_top_;
    }
    void SetRightForwardTop(const GeoPoint& _right_forward_top)
    {
        right_forward_top_ = _right_forward_top;
    }

    const GeoPoint& GetRightForwardBottom() const
    {
        return right_forward_bottom_;
    }
    void SetRightForwardBottom(const GeoPoint& _right_forward_bottom)
    {
        right_forward_bottom_ = _right_forward_bottom;
    }











};  // class GeoBox4

typedef ::std::shared_ptr<GeoBox4> PtrGeoBox4;
typedef const ::std::vector<GeoBox4>* ConstRawPtrVecGeoBox4;
typedef ::std::vector<GeoBox4>* RawPtrVecGeoBox4;
typedef ::std::shared_ptr<GeoBox4 const> ConstPtrGeoBox4;
typedef ::std::shared_ptr<::std::vector<GeoBox4> const> ConstPtrVecGeoBox4;
typedef ::std::unordered_map<::std::uint64_t, PtrGeoBox4> HashmapGeoBox4;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_COMMON_GEO_BOX4_H_