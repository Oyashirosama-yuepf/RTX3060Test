/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file coordinate.h
 * @brief Auto generated code for Coordinate format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_COMMON_COORDINATE_H_
#define HOLO_MAP_FORMAT_COMMON_COORDINATE_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/common/coordinate.pb.h>


#include <holo/map/format/base/base.h>


#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  Coordinate: public Base
{
public:

        
    enum CoordinateType
    {
        COORDINATE_TYPE_UNDEFINED=  0,  
        COORDINATE_TYPE_WGS84=  1,  
        COORDINATE_TYPE_CGCS2000=  2,  
        COORDINATE_TYPE_GCJ02=  3,  
        COORDINATE_TYPE_UTM6=  4,  
        COORDINATE_TYPE_UTM3=  5,  
        COORDINATE_TYPE_WEBMOCATOR=  6,  
        COORDINATE_TYPE_LOCAL=  7,  
        COORDINATE_TYPE_OTHER=  99,  
    };

    static const ::std::map<::std::string, CoordinateType>& ENUMSTR_COORDINATETYPE() 
    { 
        static const ::std::map<::std::string, CoordinateType> data{
        { "UNDEFINED", CoordinateType::COORDINATE_TYPE_UNDEFINED },
        { "WGS84", CoordinateType::COORDINATE_TYPE_WGS84 },
        { "CGCS2000", CoordinateType::COORDINATE_TYPE_CGCS2000 },
        { "GCJ02", CoordinateType::COORDINATE_TYPE_GCJ02 },
        { "UTM6", CoordinateType::COORDINATE_TYPE_UTM6 },
        { "UTM3", CoordinateType::COORDINATE_TYPE_UTM3 },
        { "WEBMOCATOR", CoordinateType::COORDINATE_TYPE_WEBMOCATOR },
        { "LOCAL", CoordinateType::COORDINATE_TYPE_LOCAL },
        { "OTHER", CoordinateType::COORDINATE_TYPE_OTHER }};
        return data;
    }


private:
    CoordinateType coordinate_type_; 
    ::std::uint32_t utm_zone_id_; 
    bool utm_south_flag_; 

private:
    void DecodeProto(const ::holo::map::proto::common::Coordinate& _proto_handler);
    ::holo::map::proto::common::Coordinate EncodeProto();

public:
    Coordinate();
    explicit Coordinate(const ::holo::map::proto::common::Coordinate& _proto_handler);
    // init all format data
    Coordinate(const CoordinateType& _coordinate_type,const ::std::uint32_t _utm_zone_id,const bool _utm_south_flag);
    ~Coordinate();

    bool operator==(const ::holo::map::format::Coordinate& _other) const;
    Coordinate& operator=(const ::holo::map::proto::common::Coordinate& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::common::Coordinate GetProtoHandler()
    {
        return EncodeProto();
    }

    


    const CoordinateType& GetCoordinateType() const
    {
        return coordinate_type_;
    }
    void SetCoordinateType(const CoordinateType& _coordinate_type)
    {
        coordinate_type_ = _coordinate_type;
    }

    ::std::uint32_t GetUtmZoneId() const
    {
        return utm_zone_id_;
    }
    void SetUtmZoneId(const ::std::uint32_t _utm_zone_id)
    {
        utm_zone_id_ = _utm_zone_id;
    }

    bool GetUtmSouthFlag() const
    {
        return utm_south_flag_;
    }
    void SetUtmSouthFlag(const bool _utm_south_flag)
    {
        utm_south_flag_ = _utm_south_flag;
    }











};  // class Coordinate

typedef ::std::shared_ptr<Coordinate> PtrCoordinate;
typedef const ::std::vector<Coordinate>* ConstRawPtrVecCoordinate;
typedef ::std::vector<Coordinate>* RawPtrVecCoordinate;
typedef ::std::shared_ptr<Coordinate const> ConstPtrCoordinate;
typedef ::std::shared_ptr<::std::vector<Coordinate> const> ConstPtrVecCoordinate;
typedef ::std::unordered_map<::std::uint64_t, PtrCoordinate> HashmapCoordinate;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_COMMON_COORDINATE_H_