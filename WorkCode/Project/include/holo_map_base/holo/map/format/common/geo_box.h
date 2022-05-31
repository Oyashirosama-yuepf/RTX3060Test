/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file geo_box.h
 * @brief Auto generated code for GeoBox format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_COMMON_GEO_BOX_H_
#define HOLO_MAP_FORMAT_COMMON_GEO_BOX_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/common/geo_box.pb.h>

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

class  GeoBox: public Base
{
public:




private:
    GeoPoint left_back_bottom_; 
    GeoPoint right_forward_top_; 

private:
    void DecodeProto(const ::holo::map::proto::common::GeoBox& _proto_handler);
    ::holo::map::proto::common::GeoBox EncodeProto();

public:
    GeoBox();
    explicit GeoBox(const ::holo::map::proto::common::GeoBox& _proto_handler);
    // init all format data
    GeoBox(const GeoPoint& _left_back_bottom,const GeoPoint& _right_forward_top);
    ~GeoBox();

    bool operator==(const ::holo::map::format::GeoBox& _other) const;
    GeoBox& operator=(const ::holo::map::proto::common::GeoBox& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::common::GeoBox GetProtoHandler()
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

    const GeoPoint& GetRightForwardTop() const
    {
        return right_forward_top_;
    }
    void SetRightForwardTop(const GeoPoint& _right_forward_top)
    {
        right_forward_top_ = _right_forward_top;
    }











};  // class GeoBox

typedef ::std::shared_ptr<GeoBox> PtrGeoBox;
typedef const ::std::vector<GeoBox>* ConstRawPtrVecGeoBox;
typedef ::std::vector<GeoBox>* RawPtrVecGeoBox;
typedef ::std::shared_ptr<GeoBox const> ConstPtrGeoBox;
typedef ::std::shared_ptr<::std::vector<GeoBox> const> ConstPtrVecGeoBox;
typedef ::std::unordered_map<::std::uint64_t, PtrGeoBox> HashmapGeoBox;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_COMMON_GEO_BOX_H_