/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file geo_multi_line.h
 * @brief Auto generated code for GeoMultiLine format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_COMMON_GEO_MULTI_LINE_H_
#define HOLO_MAP_FORMAT_COMMON_GEO_MULTI_LINE_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/common/geo_multi_line.pb.h>

#include <holo/map/proto/common/geo_line.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/geo_line.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  GeoMultiLine: public Base
{
public:




private:
    ::std::vector<GeoLine> lines_; 

private:
    void DecodeProto(const ::holo::map::proto::common::GeoMultiLine& _proto_handler);
    ::holo::map::proto::common::GeoMultiLine EncodeProto();

public:
    GeoMultiLine();
    explicit GeoMultiLine(const ::holo::map::proto::common::GeoMultiLine& _proto_handler);
    // init all format data
    GeoMultiLine(const ::std::vector<GeoLine>& _lines);
    ~GeoMultiLine();

    bool operator==(const ::holo::map::format::GeoMultiLine& _other) const;
    GeoMultiLine& operator=(const ::holo::map::proto::common::GeoMultiLine& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::common::GeoMultiLine GetProtoHandler()
    {
        return EncodeProto();
    }

    


    const ::std::vector<GeoLine>* GetPtrLines() const
    {
        return &lines_;
    }
    void SetLines(const ::std::vector<GeoLine>& _lines)
    {
        lines_ = _lines;
    }


    void ClearLines()
    {
        lines_.clear();
    }
    void AddLinesElement(const GeoLine& _value)
    {
        lines_.push_back(_value);
    }
    void UniqueAddLinesElements(const ::std::vector<GeoLine>& _value)
    {
        UniqueAppend(lines_, _value);
    }









};  // class GeoMultiLine

typedef ::std::shared_ptr<GeoMultiLine> PtrGeoMultiLine;
typedef const ::std::vector<GeoMultiLine>* ConstRawPtrVecGeoMultiLine;
typedef ::std::vector<GeoMultiLine>* RawPtrVecGeoMultiLine;
typedef ::std::shared_ptr<GeoMultiLine const> ConstPtrGeoMultiLine;
typedef ::std::shared_ptr<::std::vector<GeoMultiLine> const> ConstPtrVecGeoMultiLine;
typedef ::std::unordered_map<::std::uint64_t, PtrGeoMultiLine> HashmapGeoMultiLine;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_COMMON_GEO_MULTI_LINE_H_