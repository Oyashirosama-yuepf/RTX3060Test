/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file geo_line.h
 * @brief Auto generated code for GeoLine format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_COMMON_GEO_LINE_H_
#define HOLO_MAP_FORMAT_COMMON_GEO_LINE_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/common/geo_line.pb.h>

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

class  GeoLine: public Base
{
public:




private:
    ::std::vector<GeoPoint> vertices_; 

private:
    void DecodeProto(const ::holo::map::proto::common::GeoLine& _proto_handler);
    ::holo::map::proto::common::GeoLine EncodeProto();

public:
    GeoLine();
    explicit GeoLine(const ::holo::map::proto::common::GeoLine& _proto_handler);
    // init all format data
    GeoLine(const ::std::vector<GeoPoint>& _vertices);
    ~GeoLine();

    bool operator==(const ::holo::map::format::GeoLine& _other) const;
    GeoLine& operator=(const ::holo::map::proto::common::GeoLine& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::common::GeoLine GetProtoHandler()
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









};  // class GeoLine

typedef ::std::shared_ptr<GeoLine> PtrGeoLine;
typedef const ::std::vector<GeoLine>* ConstRawPtrVecGeoLine;
typedef ::std::vector<GeoLine>* RawPtrVecGeoLine;
typedef ::std::shared_ptr<GeoLine const> ConstPtrGeoLine;
typedef ::std::shared_ptr<::std::vector<GeoLine> const> ConstPtrVecGeoLine;
typedef ::std::unordered_map<::std::uint64_t, PtrGeoLine> HashmapGeoLine;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_COMMON_GEO_LINE_H_