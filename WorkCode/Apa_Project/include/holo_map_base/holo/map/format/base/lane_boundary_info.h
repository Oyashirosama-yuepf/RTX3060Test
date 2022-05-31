/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_boundary_info.h
 * @brief Auto generated code for LaneBoundaryInfo format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_BASE_LANE_BOUNDARY_INFO_H_
#define HOLO_MAP_FORMAT_BASE_LANE_BOUNDARY_INFO_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/base/lane_boundary_info.pb.h>

#include <holo/map/proto/common/coordinate.pb.h>

#include <holo/map/proto/common/geo_line.pb.h>

#include <holo/map/proto/common/geo_point.pb.h>

#include <holo/map/proto/base/lane_boundary_element.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/coordinate.h>

#include <holo/map/format/common/geo_line.h>

#include <holo/map/format/common/geo_point.h>

#include <holo/map/format/base/lane_boundary_element.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  LaneBoundaryInfo: public Base
{
public:

        
    enum LaneBoundaryElementsPosType
    {
        LANE_BOUNDARY_ELEMENTS_POS_TYPE_UNKNOWN=  0,  
        LANE_BOUNDARY_ELEMENTS_POS_TYPE_POS_INDEX=  1,  
        LANE_BOUNDARY_ELEMENTS_POS_TYPE_POS_PERCENT=  2,  
        LANE_BOUNDARY_ELEMENTS_POS_TYPE_POS_DISTANCE=  3,  
    };

    static const ::std::map<::std::string, LaneBoundaryElementsPosType>& ENUMSTR_LANEBOUNDARYELEMENTSPOSTYPE() 
    { 
        static const ::std::map<::std::string, LaneBoundaryElementsPosType> data{
        { "UNKNOWN", LaneBoundaryElementsPosType::LANE_BOUNDARY_ELEMENTS_POS_TYPE_UNKNOWN },
        { "POS_INDEX", LaneBoundaryElementsPosType::LANE_BOUNDARY_ELEMENTS_POS_TYPE_POS_INDEX },
        { "POS_PERCENT", LaneBoundaryElementsPosType::LANE_BOUNDARY_ELEMENTS_POS_TYPE_POS_PERCENT },
        { "POS_DISTANCE", LaneBoundaryElementsPosType::LANE_BOUNDARY_ELEMENTS_POS_TYPE_POS_DISTANCE }};
        return data;
    }


private:
    ::std::vector<LaneBoundaryElement> lane_boundary_elements_; 
    ::std::uint64_t lane_boundary_id_; 
    ::std::uint32_t index_; 
    ::std::int32_t offset_cm_; 
    LaneBoundaryElementsPosType lane_boundary_elements_pos_type_; 
    Coordinate coordinate_; 
    ::std::uint32_t zone_id_; 
    ::std::uint32_t extra_zone_id_; 
    bool south_flag_; 
    ::std::vector<GeoPoint> geometry_points_; 
    ::std::map<::std::uint32_t, GeoLine> extra_geometry_points_; 

private:
    void DecodeProto(const ::holo::map::proto::base::LaneBoundaryInfo& _proto_handler);
    ::holo::map::proto::base::LaneBoundaryInfo EncodeProto();

public:
    LaneBoundaryInfo();
    explicit LaneBoundaryInfo(const ::holo::map::proto::base::LaneBoundaryInfo& _proto_handler);
    // init all format data
    LaneBoundaryInfo(const ::std::vector<LaneBoundaryElement>& _lane_boundary_elements,const ::std::uint64_t _lane_boundary_id,const ::std::uint32_t _index,const ::std::int32_t _offset_cm,const LaneBoundaryElementsPosType& _lane_boundary_elements_pos_type,const Coordinate& _coordinate,const ::std::uint32_t _zone_id,const ::std::uint32_t _extra_zone_id,const bool _south_flag,const ::std::vector<GeoPoint>& _geometry_points,const ::std::map<::std::uint32_t, GeoLine>& _extra_geometry_points);
    ~LaneBoundaryInfo();

    bool operator==(const ::holo::map::format::LaneBoundaryInfo& _other) const;
    LaneBoundaryInfo& operator=(const ::holo::map::proto::base::LaneBoundaryInfo& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::base::LaneBoundaryInfo GetProtoHandler()
    {
        return EncodeProto();
    }

    


    const ::std::vector<LaneBoundaryElement>* GetPtrLaneBoundaryElements() const
    {
        return &lane_boundary_elements_;
    }
    void SetLaneBoundaryElements(const ::std::vector<LaneBoundaryElement>& _lane_boundary_elements)
    {
        lane_boundary_elements_ = _lane_boundary_elements;
    }

    ::std::uint64_t GetLaneBoundaryId() const
    {
        return lane_boundary_id_;
    }
    void SetLaneBoundaryId(const ::std::uint64_t _lane_boundary_id)
    {
        lane_boundary_id_ = _lane_boundary_id;
    }

    ::std::uint32_t GetIndex() const
    {
        return index_;
    }
    void SetIndex(const ::std::uint32_t _index)
    {
        index_ = _index;
    }

    ::std::int32_t GetOffsetCm() const
    {
        return offset_cm_;
    }
    void SetOffsetCm(const ::std::int32_t _offset_cm)
    {
        offset_cm_ = _offset_cm;
    }

    const LaneBoundaryElementsPosType& GetLaneBoundaryElementsPosType() const
    {
        return lane_boundary_elements_pos_type_;
    }
    void SetLaneBoundaryElementsPosType(const LaneBoundaryElementsPosType& _lane_boundary_elements_pos_type)
    {
        lane_boundary_elements_pos_type_ = _lane_boundary_elements_pos_type;
    }

    const Coordinate& GetCoordinate() const
    {
        return coordinate_;
    }
    void SetCoordinate(const Coordinate& _coordinate)
    {
        coordinate_ = _coordinate;
    }

    ::std::uint32_t GetZoneId() const
    {
        return zone_id_;
    }
    void SetZoneId(const ::std::uint32_t _zone_id)
    {
        zone_id_ = _zone_id;
    }

    ::std::uint32_t GetExtraZoneId() const
    {
        return extra_zone_id_;
    }
    void SetExtraZoneId(const ::std::uint32_t _extra_zone_id)
    {
        extra_zone_id_ = _extra_zone_id;
    }

    bool GetSouthFlag() const
    {
        return south_flag_;
    }
    void SetSouthFlag(const bool _south_flag)
    {
        south_flag_ = _south_flag;
    }

    const ::std::map<::std::uint32_t, GeoLine>* GetPtrExtraGeometryPoints() const
    {
        return &extra_geometry_points_;
    }
    void SetExtraGeometryPoints(const ::std::map<::std::uint32_t, GeoLine>& _extra_geometry_points)
    {
        extra_geometry_points_ = _extra_geometry_points;
    }


    void ClearLaneBoundaryElements()
    {
        lane_boundary_elements_.clear();
    }
    void AddLaneBoundaryElementsElement(const LaneBoundaryElement& _value)
    {
        lane_boundary_elements_.push_back(_value);
    }
    void UniqueAddLaneBoundaryElementsElements(const ::std::vector<LaneBoundaryElement>& _value)
    {
        UniqueAppend(lane_boundary_elements_, _value);
    }

    void ClearGeometryPoints()
    {
        geometry_points_.clear();
    }
    void AddGeometryPointsElement(const GeoPoint& _value)
    {
        geometry_points_.push_back(_value);
    }
    void UniqueAddGeometryPointsElements(const ::std::vector<GeoPoint>& _value)
    {
        UniqueAppend(geometry_points_, _value);
    }




    const ::std::vector<GeoPoint>* GetPtrGeometryPoints() const;
    void SetGeometryPoints(const ::std::vector<GeoPoint>& _geometry_points)
    {
        this->geometry_points_ = _geometry_points;
    }





};  // class LaneBoundaryInfo

typedef ::std::shared_ptr<LaneBoundaryInfo> PtrLaneBoundaryInfo;
typedef const ::std::vector<LaneBoundaryInfo>* ConstRawPtrVecLaneBoundaryInfo;
typedef ::std::vector<LaneBoundaryInfo>* RawPtrVecLaneBoundaryInfo;
typedef ::std::shared_ptr<LaneBoundaryInfo const> ConstPtrLaneBoundaryInfo;
typedef ::std::shared_ptr<::std::vector<LaneBoundaryInfo> const> ConstPtrVecLaneBoundaryInfo;
typedef ::std::unordered_map<::std::uint64_t, PtrLaneBoundaryInfo> HashmapLaneBoundaryInfo;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_BASE_LANE_BOUNDARY_INFO_H_