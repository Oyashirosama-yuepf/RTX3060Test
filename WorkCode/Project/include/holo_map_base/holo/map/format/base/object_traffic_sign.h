/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file object_traffic_sign.h
 * @brief Auto generated code for ObjectTrafficSign format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_BASE_OBJECT_TRAFFIC_SIGN_H_
#define HOLO_MAP_FORMAT_BASE_OBJECT_TRAFFIC_SIGN_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/base/object_traffic_sign.pb.h>

#include <holo/map/proto/common/coordinate.pb.h>

#include <holo/map/proto/common/geo_box4.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/coordinate.h>

#include <holo/map/format/common/geo_box4.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  ObjectTrafficSign: public Base
{
public:

        
    enum TrafficSignType
    {
        TRAFFIC_SIGN_TYPE_UNDEFINED=  0,  
        TRAFFIC_SIGN_TYPE_WARNING=  1,  
        TRAFFIC_SIGN_TYPE_BAN=  2,  
        TRAFFIC_SIGN_TYPE_MANDATORY=  3,  
        TRAFFIC_SIGN_TYPE_GUIDE=  4,  
        TRAFFIC_SIGN_TYPE_TOURIST_AREAS=  5,  
        TRAFFIC_SIGN_TYPE_OPERATION_AREA=  6,  
        TRAFFIC_SIGN_TYPE_NOTICE=  7,  
        TRAFFIC_SIGN_TYPE_AUXILIARY=  8,  
        TRAFFIC_SIGN_TYPE_VARIABLE=  9,  
        TRAFFIC_SIGN_TYPE_OTHER=  10,  
    };

        
    enum TrafficSignContent
    {
        TRAFFIC_SIGN_CONTENT_UNDEFINED=  0,  
        TRAFFIC_SIGN_CONTENT_CURVE_RIGHT=  1,  
        TRAFFIC_SIGN_CONTENT_CURVE_LEFT=  2,  
        TRAFFIC_SIGN_CONTENT_NO_OVERTAKING=  3,  
        TRAFFIC_SIGN_CONTENT_NO_OVERTAKING_END=  4,  
        TRAFFIC_SIGN_CONTENT_SPEED_LIMIT=  5,  
        TRAFFIC_SIGN_CONTENT_SPEED_LIMIT_END=  6,  
        TRAFFIC_SIGN_CONTENT_ADVISORY_SPEED_LIMIT=  7,  
        TRAFFIC_SIGN_CONTENT_VARIABLE_SPEED_LIMIT=  8,  
        TRAFFIC_SIGN_CONTENT_VARIABLE_INFO=  9,  
        TRAFFIC_SIGN_CONTENT_DO_NOT_ENTER=  10,  
        TRAFFIC_SIGN_CONTENT_OTHER=  11,  
    };

        
    enum TrafficSignColor
    {
        TRAFFIC_SIGN_COLOR_UNKNOWN=  0,  
        TRAFFIC_SIGN_COLOR_LIGHT_GRAY=  1,  
        TRAFFIC_SIGN_COLOR_GRAY=  2,  
        TRAFFIC_SIGN_COLOR_DARK_GRAY=  3,  
        TRAFFIC_SIGN_COLOR_BLACK=  4,  
        TRAFFIC_SIGN_COLOR_RED=  5,  
        TRAFFIC_SIGN_COLOR_YELLOW=  6,  
        TRAFFIC_SIGN_COLOR_GREEN=  7,  
        TRAFFIC_SIGN_COLOR_CYAN=  8,  
        TRAFFIC_SIGN_COLOR_BLUE=  9,  
        TRAFFIC_SIGN_COLOR_ORANGE=  10,  
        TRAFFIC_SIGN_COLOR_WHITE=  11,  
    };

        
    enum TrafficSignShape
    {
        TRAFFIC_SIGN_SHAPE_UNDEFINED=  0,  
        TRAFFIC_SIGN_SHAPE_RECTANGLE=  1,  
        TRAFFIC_SIGN_SHAPE_ROUND=  2,  
        TRAFFIC_SIGN_SHAPE_OCTAGON=  3,  
        TRAFFIC_SIGN_SHAPE_DIAMOND=  4,  
        TRAFFIC_SIGN_SHAPE_CROSBUCK=  5,  
        TRAFFIC_SIGN_SHAPE_TRIANGLE_TIP_DOWN=  6,  
        TRAFFIC_SIGN_SHAPE_ELLIPSE=  7,  
        TRAFFIC_SIGN_SHAPE_OTHER=  8,  
        TRAFFIC_SIGN_SHAPE_TRIANGLE_TIP_UP=  9,  
        TRAFFIC_SIGN_SHAPE_UNKNOWN=  10,  
    };

    static const ::std::map<::std::string, TrafficSignType>& ENUMSTR_TRAFFICSIGNTYPE() 
    { 
        static const ::std::map<::std::string, TrafficSignType> data{
        { "UNDEFINED", TrafficSignType::TRAFFIC_SIGN_TYPE_UNDEFINED },
        { "WARNING", TrafficSignType::TRAFFIC_SIGN_TYPE_WARNING },
        { "BAN", TrafficSignType::TRAFFIC_SIGN_TYPE_BAN },
        { "MANDATORY", TrafficSignType::TRAFFIC_SIGN_TYPE_MANDATORY },
        { "GUIDE", TrafficSignType::TRAFFIC_SIGN_TYPE_GUIDE },
        { "TOURIST_AREAS", TrafficSignType::TRAFFIC_SIGN_TYPE_TOURIST_AREAS },
        { "OPERATION_AREA", TrafficSignType::TRAFFIC_SIGN_TYPE_OPERATION_AREA },
        { "NOTICE", TrafficSignType::TRAFFIC_SIGN_TYPE_NOTICE },
        { "AUXILIARY", TrafficSignType::TRAFFIC_SIGN_TYPE_AUXILIARY },
        { "VARIABLE", TrafficSignType::TRAFFIC_SIGN_TYPE_VARIABLE },
        { "OTHER", TrafficSignType::TRAFFIC_SIGN_TYPE_OTHER }};
        return data;
    }

    static const ::std::map<::std::string, TrafficSignContent>& ENUMSTR_TRAFFICSIGNCONTENT() 
    { 
        static const ::std::map<::std::string, TrafficSignContent> data{
        { "UNDEFINED", TrafficSignContent::TRAFFIC_SIGN_CONTENT_UNDEFINED },
        { "CURVE_RIGHT", TrafficSignContent::TRAFFIC_SIGN_CONTENT_CURVE_RIGHT },
        { "CURVE_LEFT", TrafficSignContent::TRAFFIC_SIGN_CONTENT_CURVE_LEFT },
        { "NO_OVERTAKING", TrafficSignContent::TRAFFIC_SIGN_CONTENT_NO_OVERTAKING },
        { "NO_OVERTAKING_END", TrafficSignContent::TRAFFIC_SIGN_CONTENT_NO_OVERTAKING_END },
        { "SPEED_LIMIT", TrafficSignContent::TRAFFIC_SIGN_CONTENT_SPEED_LIMIT },
        { "SPEED_LIMIT_END", TrafficSignContent::TRAFFIC_SIGN_CONTENT_SPEED_LIMIT_END },
        { "ADVISORY_SPEED_LIMIT", TrafficSignContent::TRAFFIC_SIGN_CONTENT_ADVISORY_SPEED_LIMIT },
        { "VARIABLE_SPEED_LIMIT", TrafficSignContent::TRAFFIC_SIGN_CONTENT_VARIABLE_SPEED_LIMIT },
        { "VARIABLE_INFO", TrafficSignContent::TRAFFIC_SIGN_CONTENT_VARIABLE_INFO },
        { "DO_NOT_ENTER", TrafficSignContent::TRAFFIC_SIGN_CONTENT_DO_NOT_ENTER },
        { "OTHER", TrafficSignContent::TRAFFIC_SIGN_CONTENT_OTHER }};
        return data;
    }

    static const ::std::map<::std::string, TrafficSignColor>& ENUMSTR_TRAFFICSIGNCOLOR() 
    { 
        static const ::std::map<::std::string, TrafficSignColor> data{
        { "UNKNOWN", TrafficSignColor::TRAFFIC_SIGN_COLOR_UNKNOWN },
        { "LIGHT_GRAY", TrafficSignColor::TRAFFIC_SIGN_COLOR_LIGHT_GRAY },
        { "GRAY", TrafficSignColor::TRAFFIC_SIGN_COLOR_GRAY },
        { "DARK_GRAY", TrafficSignColor::TRAFFIC_SIGN_COLOR_DARK_GRAY },
        { "BLACK", TrafficSignColor::TRAFFIC_SIGN_COLOR_BLACK },
        { "RED", TrafficSignColor::TRAFFIC_SIGN_COLOR_RED },
        { "YELLOW", TrafficSignColor::TRAFFIC_SIGN_COLOR_YELLOW },
        { "GREEN", TrafficSignColor::TRAFFIC_SIGN_COLOR_GREEN },
        { "CYAN", TrafficSignColor::TRAFFIC_SIGN_COLOR_CYAN },
        { "BLUE", TrafficSignColor::TRAFFIC_SIGN_COLOR_BLUE },
        { "ORANGE", TrafficSignColor::TRAFFIC_SIGN_COLOR_ORANGE },
        { "WHITE", TrafficSignColor::TRAFFIC_SIGN_COLOR_WHITE }};
        return data;
    }

    static const ::std::map<::std::string, TrafficSignShape>& ENUMSTR_TRAFFICSIGNSHAPE() 
    { 
        static const ::std::map<::std::string, TrafficSignShape> data{
        { "UNDEFINED", TrafficSignShape::TRAFFIC_SIGN_SHAPE_UNDEFINED },
        { "RECTANGLE", TrafficSignShape::TRAFFIC_SIGN_SHAPE_RECTANGLE },
        { "ROUND", TrafficSignShape::TRAFFIC_SIGN_SHAPE_ROUND },
        { "OCTAGON", TrafficSignShape::TRAFFIC_SIGN_SHAPE_OCTAGON },
        { "DIAMOND", TrafficSignShape::TRAFFIC_SIGN_SHAPE_DIAMOND },
        { "CROSBUCK", TrafficSignShape::TRAFFIC_SIGN_SHAPE_CROSBUCK },
        { "TRIANGLE_TIP_DOWN", TrafficSignShape::TRAFFIC_SIGN_SHAPE_TRIANGLE_TIP_DOWN },
        { "ELLIPSE", TrafficSignShape::TRAFFIC_SIGN_SHAPE_ELLIPSE },
        { "OTHER", TrafficSignShape::TRAFFIC_SIGN_SHAPE_OTHER },
        { "TRIANGLE_TIP_UP", TrafficSignShape::TRAFFIC_SIGN_SHAPE_TRIANGLE_TIP_UP },
        { "UNKNOWN", TrafficSignShape::TRAFFIC_SIGN_SHAPE_UNKNOWN }};
        return data;
    }


private:
    ::std::uint64_t object_traffic_sign_id_; 
    TrafficSignType traffic_sign_type_; 
    TrafficSignContent traffic_sign_content_; 
    ::std::string traffic_sign_content_data_; 
    TrafficSignColor traffic_sign_color_; 
    TrafficSignShape traffic_sign_shape_; 
    ::std::uint64_t traffic_sign_heading_; 
    ::std::vector<::std::uint64_t> tile_ids_; 
    ::std::vector<::std::uint64_t> associated_lane_ids_; 
    ::std::vector<::std::uint64_t> associated_lane_group_ids_; 
    ::std::uint32_t zone_id_; 
    ::std::uint32_t extra_zone_id_; 
    bool south_flag_; 
    GeoBox4 geometry_; 
    ::std::map<::std::uint32_t, GeoBox4> extra_geometry_; 
    Coordinate coordinate_; 

private:
    void DecodeProto(const ::holo::map::proto::base::ObjectTrafficSign& _proto_handler);
    ::holo::map::proto::base::ObjectTrafficSign EncodeProto();

public:
    ObjectTrafficSign();
    explicit ObjectTrafficSign(const ::holo::map::proto::base::ObjectTrafficSign& _proto_handler);
    // init all format data
    ObjectTrafficSign(const ::std::uint64_t _object_traffic_sign_id,const TrafficSignType& _traffic_sign_type,const TrafficSignContent& _traffic_sign_content,const ::std::string& _traffic_sign_content_data,const TrafficSignColor& _traffic_sign_color,const TrafficSignShape& _traffic_sign_shape,const ::std::uint64_t _traffic_sign_heading,const ::std::vector<::std::uint64_t>& _tile_ids,const ::std::vector<::std::uint64_t>& _associated_lane_ids,const ::std::vector<::std::uint64_t>& _associated_lane_group_ids,const ::std::uint32_t _zone_id,const ::std::uint32_t _extra_zone_id,const bool _south_flag,const GeoBox4& _geometry,const ::std::map<::std::uint32_t, GeoBox4>& _extra_geometry,const Coordinate& _coordinate);
    ~ObjectTrafficSign();

    bool operator==(const ::holo::map::format::ObjectTrafficSign& _other) const;
    ObjectTrafficSign& operator=(const ::holo::map::proto::base::ObjectTrafficSign& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::base::ObjectTrafficSign GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetObjectTrafficSignId() const
    {
        return object_traffic_sign_id_;
    }
    void SetObjectTrafficSignId(const ::std::uint64_t _object_traffic_sign_id)
    {
        object_traffic_sign_id_ = _object_traffic_sign_id;
    }

    const TrafficSignType& GetTrafficSignType() const
    {
        return traffic_sign_type_;
    }
    void SetTrafficSignType(const TrafficSignType& _traffic_sign_type)
    {
        traffic_sign_type_ = _traffic_sign_type;
    }

    const TrafficSignContent& GetTrafficSignContent() const
    {
        return traffic_sign_content_;
    }
    void SetTrafficSignContent(const TrafficSignContent& _traffic_sign_content)
    {
        traffic_sign_content_ = _traffic_sign_content;
    }

    const ::std::string& GetTrafficSignContentData() const
    {
        return traffic_sign_content_data_;
    }
    void SetTrafficSignContentData(const ::std::string& _traffic_sign_content_data)
    {
        traffic_sign_content_data_ = _traffic_sign_content_data;
    }

    const TrafficSignColor& GetTrafficSignColor() const
    {
        return traffic_sign_color_;
    }
    void SetTrafficSignColor(const TrafficSignColor& _traffic_sign_color)
    {
        traffic_sign_color_ = _traffic_sign_color;
    }

    const TrafficSignShape& GetTrafficSignShape() const
    {
        return traffic_sign_shape_;
    }
    void SetTrafficSignShape(const TrafficSignShape& _traffic_sign_shape)
    {
        traffic_sign_shape_ = _traffic_sign_shape;
    }

    ::std::uint64_t GetTrafficSignHeading() const
    {
        return traffic_sign_heading_;
    }
    void SetTrafficSignHeading(const ::std::uint64_t _traffic_sign_heading)
    {
        traffic_sign_heading_ = _traffic_sign_heading;
    }

    const ::std::vector<::std::uint64_t>* GetPtrTileIds() const
    {
        return &tile_ids_;
    }
    void SetTileIds(const ::std::vector<::std::uint64_t>& _tile_ids)
    {
        tile_ids_ = _tile_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrAssociatedLaneIds() const
    {
        return &associated_lane_ids_;
    }
    void SetAssociatedLaneIds(const ::std::vector<::std::uint64_t>& _associated_lane_ids)
    {
        associated_lane_ids_ = _associated_lane_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrAssociatedLaneGroupIds() const
    {
        return &associated_lane_group_ids_;
    }
    void SetAssociatedLaneGroupIds(const ::std::vector<::std::uint64_t>& _associated_lane_group_ids)
    {
        associated_lane_group_ids_ = _associated_lane_group_ids;
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

    const ::std::map<::std::uint32_t, GeoBox4>* GetPtrExtraGeometry() const
    {
        return &extra_geometry_;
    }
    void SetExtraGeometry(const ::std::map<::std::uint32_t, GeoBox4>& _extra_geometry)
    {
        extra_geometry_ = _extra_geometry;
    }

    const Coordinate& GetCoordinate() const
    {
        return coordinate_;
    }
    void SetCoordinate(const Coordinate& _coordinate)
    {
        coordinate_ = _coordinate;
    }


    void ClearTileIds()
    {
        tile_ids_.clear();
    }
    void AddTileIdsElement(const ::std::uint64_t& _value)
    {
        tile_ids_.push_back(_value);
    }
    void UniqueAddTileIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(tile_ids_, _value);
    }

    void ClearAssociatedLaneIds()
    {
        associated_lane_ids_.clear();
    }
    void AddAssociatedLaneIdsElement(const ::std::uint64_t& _value)
    {
        associated_lane_ids_.push_back(_value);
    }
    void UniqueAddAssociatedLaneIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(associated_lane_ids_, _value);
    }

    void ClearAssociatedLaneGroupIds()
    {
        associated_lane_group_ids_.clear();
    }
    void AddAssociatedLaneGroupIdsElement(const ::std::uint64_t& _value)
    {
        associated_lane_group_ids_.push_back(_value);
    }
    void UniqueAddAssociatedLaneGroupIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(associated_lane_group_ids_, _value);
    }


    const GeoBox4& GetGeometry() const;
    void SetGeometry(const GeoBox4& _geometry)
    {
        this->geometry_ = _geometry;
    }







};  // class ObjectTrafficSign

typedef ::std::shared_ptr<ObjectTrafficSign> PtrObjectTrafficSign;
typedef const ::std::vector<ObjectTrafficSign>* ConstRawPtrVecObjectTrafficSign;
typedef ::std::vector<ObjectTrafficSign>* RawPtrVecObjectTrafficSign;
typedef ::std::shared_ptr<ObjectTrafficSign const> ConstPtrObjectTrafficSign;
typedef ::std::shared_ptr<::std::vector<ObjectTrafficSign> const> ConstPtrVecObjectTrafficSign;
typedef ::std::unordered_map<::std::uint64_t, PtrObjectTrafficSign> HashmapObjectTrafficSign;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_BASE_OBJECT_TRAFFIC_SIGN_H_