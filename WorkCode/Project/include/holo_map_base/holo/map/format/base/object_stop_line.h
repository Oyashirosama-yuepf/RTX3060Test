/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file object_stop_line.h
 * @brief Auto generated code for ObjectStopLine format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_BASE_OBJECT_STOP_LINE_H_
#define HOLO_MAP_FORMAT_BASE_OBJECT_STOP_LINE_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/base/object_stop_line.pb.h>

#include <holo/map/proto/common/coordinate.pb.h>

#include <holo/map/proto/common/geo_line.pb.h>

#include <holo/map/proto/common/geo_point.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/coordinate.h>

#include <holo/map/format/common/geo_line.h>

#include <holo/map/format/common/geo_point.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  ObjectStopLine: public Base
{
public:

        
    enum StopLineType
    {
        STOP_LINE_TYPE_UNDEFINED=  0,  
        STOP_LINE_TYPE_STRAIGHT=  1,  
        STOP_LINE_TYPE_TURN=  2,  
        STOP_LINE_TYPE_BICYCLE=  3,  
        STOP_LINE_TYPE_MOTORCYCLE=  4,  
    };

        
    enum StopLineStyle
    {
        STOP_LINE_STYLE_UNDEFINED=  0,  
        STOP_LINE_STYLE_SINGLE_SOLID_LINE=  1,  
        STOP_LINE_STYLE_DOUBLE_SOLID_LINE=  2,  
    };

        
    enum StopLineColor
    {
        STOP_LINE_COLOR_UNDEFINED=  0,  
        STOP_LINE_COLOR_WHITE=  1,  
        STOP_LINE_COLOR_YELLOW=  2,  
    };

    static const ::std::map<::std::string, StopLineType>& ENUMSTR_STOPLINETYPE() 
    { 
        static const ::std::map<::std::string, StopLineType> data{
        { "UNDEFINED", StopLineType::STOP_LINE_TYPE_UNDEFINED },
        { "STRAIGHT", StopLineType::STOP_LINE_TYPE_STRAIGHT },
        { "TURN", StopLineType::STOP_LINE_TYPE_TURN },
        { "BICYCLE", StopLineType::STOP_LINE_TYPE_BICYCLE },
        { "MOTORCYCLE", StopLineType::STOP_LINE_TYPE_MOTORCYCLE }};
        return data;
    }

    static const ::std::map<::std::string, StopLineStyle>& ENUMSTR_STOPLINESTYLE() 
    { 
        static const ::std::map<::std::string, StopLineStyle> data{
        { "UNDEFINED", StopLineStyle::STOP_LINE_STYLE_UNDEFINED },
        { "SINGLE_SOLID_LINE", StopLineStyle::STOP_LINE_STYLE_SINGLE_SOLID_LINE },
        { "DOUBLE_SOLID_LINE", StopLineStyle::STOP_LINE_STYLE_DOUBLE_SOLID_LINE }};
        return data;
    }

    static const ::std::map<::std::string, StopLineColor>& ENUMSTR_STOPLINECOLOR() 
    { 
        static const ::std::map<::std::string, StopLineColor> data{
        { "UNDEFINED", StopLineColor::STOP_LINE_COLOR_UNDEFINED },
        { "WHITE", StopLineColor::STOP_LINE_COLOR_WHITE },
        { "YELLOW", StopLineColor::STOP_LINE_COLOR_YELLOW }};
        return data;
    }


private:
    ::std::uint64_t object_stop_line_id_; 
    StopLineType stop_line_type_; 
    StopLineStyle stop_line_style_; 
    StopLineColor stop_line_color_; 
    ::std::vector<::std::uint64_t> tile_ids_; 
    ::std::vector<::std::uint64_t> associated_lane_ids_; 
    ::std::vector<::std::uint64_t> associated_lane_group_ids_; 
    ::std::uint32_t zone_id_; 
    ::std::uint32_t extra_zone_id_; 
    bool south_flag_; 
    ::std::vector<GeoPoint> first_line_; 
    ::std::map<::std::uint32_t, GeoLine> extra_first_line_; 
    ::std::vector<GeoPoint> second_line_; 
    ::std::map<::std::uint32_t, GeoLine> extra_second_line_; 
    Coordinate coordinate_; 

private:
    void DecodeProto(const ::holo::map::proto::base::ObjectStopLine& _proto_handler);
    ::holo::map::proto::base::ObjectStopLine EncodeProto();

public:
    ObjectStopLine();
    explicit ObjectStopLine(const ::holo::map::proto::base::ObjectStopLine& _proto_handler);
    // init all format data
    ObjectStopLine(const ::std::uint64_t _object_stop_line_id,const StopLineType& _stop_line_type,const StopLineStyle& _stop_line_style,const StopLineColor& _stop_line_color,const ::std::vector<::std::uint64_t>& _tile_ids,const ::std::vector<::std::uint64_t>& _associated_lane_ids,const ::std::vector<::std::uint64_t>& _associated_lane_group_ids,const ::std::uint32_t _zone_id,const ::std::uint32_t _extra_zone_id,const bool _south_flag,const ::std::vector<GeoPoint>& _first_line,const ::std::map<::std::uint32_t, GeoLine>& _extra_first_line,const ::std::vector<GeoPoint>& _second_line,const ::std::map<::std::uint32_t, GeoLine>& _extra_second_line,const Coordinate& _coordinate);
    ~ObjectStopLine();

    bool operator==(const ::holo::map::format::ObjectStopLine& _other) const;
    ObjectStopLine& operator=(const ::holo::map::proto::base::ObjectStopLine& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::base::ObjectStopLine GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetObjectStopLineId() const
    {
        return object_stop_line_id_;
    }
    void SetObjectStopLineId(const ::std::uint64_t _object_stop_line_id)
    {
        object_stop_line_id_ = _object_stop_line_id;
    }

    const StopLineType& GetStopLineType() const
    {
        return stop_line_type_;
    }
    void SetStopLineType(const StopLineType& _stop_line_type)
    {
        stop_line_type_ = _stop_line_type;
    }

    const StopLineStyle& GetStopLineStyle() const
    {
        return stop_line_style_;
    }
    void SetStopLineStyle(const StopLineStyle& _stop_line_style)
    {
        stop_line_style_ = _stop_line_style;
    }

    const StopLineColor& GetStopLineColor() const
    {
        return stop_line_color_;
    }
    void SetStopLineColor(const StopLineColor& _stop_line_color)
    {
        stop_line_color_ = _stop_line_color;
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

    const ::std::map<::std::uint32_t, GeoLine>* GetPtrExtraFirstLine() const
    {
        return &extra_first_line_;
    }
    void SetExtraFirstLine(const ::std::map<::std::uint32_t, GeoLine>& _extra_first_line)
    {
        extra_first_line_ = _extra_first_line;
    }

    const ::std::map<::std::uint32_t, GeoLine>* GetPtrExtraSecondLine() const
    {
        return &extra_second_line_;
    }
    void SetExtraSecondLine(const ::std::map<::std::uint32_t, GeoLine>& _extra_second_line)
    {
        extra_second_line_ = _extra_second_line;
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

    void ClearFirstLine()
    {
        first_line_.clear();
    }
    void AddFirstLineElement(const GeoPoint& _value)
    {
        first_line_.push_back(_value);
    }
    void UniqueAddFirstLineElements(const ::std::vector<GeoPoint>& _value)
    {
        UniqueAppend(first_line_, _value);
    }

    void ClearSecondLine()
    {
        second_line_.clear();
    }
    void AddSecondLineElement(const GeoPoint& _value)
    {
        second_line_.push_back(_value);
    }
    void UniqueAddSecondLineElements(const ::std::vector<GeoPoint>& _value)
    {
        UniqueAppend(second_line_, _value);
    }




    const ::std::vector<GeoPoint>* GetPtrFirstLine() const;
    void SetFirstLine(const ::std::vector<GeoPoint>& _first_line)
    {
        this->first_line_ = _first_line;
    }

    const ::std::vector<GeoPoint>* GetPtrSecondLine() const;
    void SetSecondLine(const ::std::vector<GeoPoint>& _second_line)
    {
        this->second_line_ = _second_line;
    }





};  // class ObjectStopLine

typedef ::std::shared_ptr<ObjectStopLine> PtrObjectStopLine;
typedef const ::std::vector<ObjectStopLine>* ConstRawPtrVecObjectStopLine;
typedef ::std::vector<ObjectStopLine>* RawPtrVecObjectStopLine;
typedef ::std::shared_ptr<ObjectStopLine const> ConstPtrObjectStopLine;
typedef ::std::shared_ptr<::std::vector<ObjectStopLine> const> ConstPtrVecObjectStopLine;
typedef ::std::unordered_map<::std::uint64_t, PtrObjectStopLine> HashmapObjectStopLine;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_BASE_OBJECT_STOP_LINE_H_