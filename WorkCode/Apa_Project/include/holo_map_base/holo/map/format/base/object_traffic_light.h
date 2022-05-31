/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file object_traffic_light.h
 * @brief Auto generated code for ObjectTrafficLight format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_BASE_OBJECT_TRAFFIC_LIGHT_H_
#define HOLO_MAP_FORMAT_BASE_OBJECT_TRAFFIC_LIGHT_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/base/object_traffic_light.pb.h>

#include <holo/map/proto/common/coordinate.pb.h>

#include <holo/map/proto/common/geo_box.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/coordinate.h>

#include <holo/map/format/common/geo_box.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  ObjectTrafficLight: public Base
{
public:

        
    enum TrafficLightState
    {
        TRAFFIC_LIGHT_STATE_UNKNOWN=  0,  
        TRAFFIC_LIGHT_STATE_INVALID=  1,  
        TRAFFIC_LIGHT_STATE_GREEN=  2,  
        TRAFFIC_LIGHT_STATE_YELLOW=  3,  
        TRAFFIC_LIGHT_STATE_RED=  4,  
    };

        
    enum TrafficLightLongitudinalPosition
    {
        TRAFFIC_LIGHT_LONGITUDINAL_POSITION_UNKNOWN=  0,  
        TRAFFIC_LIGHT_LONGITUDINAL_POSITION_BEFORE_INTERSECTION=  1,  
        TRAFFIC_LIGHT_LONGITUDINAL_POSITION_CENTER_INTERSECTION=  2,  
        TRAFFIC_LIGHT_LONGITUDINAL_POSITION_AFTER_INTERSECTION=  3,  
    };

        
    enum TrafficLightLateralPosition
    {
        TRAFFIC_LIGHT_LATERAL_POSITION_UNKNOWN=  0,  
        TRAFFIC_LIGHT_LATERAL_POSITION_LEFT=  1,  
        TRAFFIC_LIGHT_LATERAL_POSITION_RIGHT=  2,  
        TRAFFIC_LIGHT_LATERAL_POSITION_ABOVE=  3,  
        TRAFFIC_LIGHT_LATERAL_POSITION_SURFACE=  4,  
        TRAFFIC_LIGHT_LATERAL_POSITION_LEFT_ABOVE=  5,  
        TRAFFIC_LIGHT_LATERAL_POSITION_RIGHT_ABOVE=  6,  
    };

        
    enum TrafficLightContentType
    {
        TRAFFIC_LIGHT_CONTENT_TYPE_UNKNOWN=  0,  
        TRAFFIC_LIGHT_CONTENT_TYPE_NONE=  1,  
        TRAFFIC_LIGHT_CONTENT_TYPE_ARROW=  2,  
        TRAFFIC_LIGHT_CONTENT_TYPE_DIGITS=  3,  
        TRAFFIC_LIGHT_CONTENT_TYPE_CHARACTERS=  4,  
        TRAFFIC_LIGHT_CONTENT_TYPE_ADMIXTURE=  5,  
        TRAFFIC_LIGHT_CONTENT_TYPE_OTHERS=  6,  
    };

        
    enum TrafficLightOrientation
    {
        TRAFFIC_LIGHT_ORIENTATION_UNKNOWN=  0,  
        TRAFFIC_LIGHT_ORIENTATION_SINGLE=  1,  
        TRAFFIC_LIGHT_ORIENTATION_HORIZONTAL=  2,  
        TRAFFIC_LIGHT_ORIENTATION_VERTICAL=  3,  
    };

    static const ::std::map<::std::string, TrafficLightState>& ENUMSTR_TRAFFICLIGHTSTATE() 
    { 
        static const ::std::map<::std::string, TrafficLightState> data{
        { "UNKNOWN", TrafficLightState::TRAFFIC_LIGHT_STATE_UNKNOWN },
        { "INVALID", TrafficLightState::TRAFFIC_LIGHT_STATE_INVALID },
        { "GREEN", TrafficLightState::TRAFFIC_LIGHT_STATE_GREEN },
        { "YELLOW", TrafficLightState::TRAFFIC_LIGHT_STATE_YELLOW },
        { "RED", TrafficLightState::TRAFFIC_LIGHT_STATE_RED }};
        return data;
    }

    static const ::std::map<::std::string, TrafficLightLongitudinalPosition>& ENUMSTR_TRAFFICLIGHTLONGITUDINALPOSITION() 
    { 
        static const ::std::map<::std::string, TrafficLightLongitudinalPosition> data{
        { "UNKNOWN", TrafficLightLongitudinalPosition::TRAFFIC_LIGHT_LONGITUDINAL_POSITION_UNKNOWN },
        { "BEFORE_INTERSECTION", TrafficLightLongitudinalPosition::TRAFFIC_LIGHT_LONGITUDINAL_POSITION_BEFORE_INTERSECTION },
        { "CENTER_INTERSECTION", TrafficLightLongitudinalPosition::TRAFFIC_LIGHT_LONGITUDINAL_POSITION_CENTER_INTERSECTION },
        { "AFTER_INTERSECTION", TrafficLightLongitudinalPosition::TRAFFIC_LIGHT_LONGITUDINAL_POSITION_AFTER_INTERSECTION }};
        return data;
    }

    static const ::std::map<::std::string, TrafficLightLateralPosition>& ENUMSTR_TRAFFICLIGHTLATERALPOSITION() 
    { 
        static const ::std::map<::std::string, TrafficLightLateralPosition> data{
        { "UNKNOWN", TrafficLightLateralPosition::TRAFFIC_LIGHT_LATERAL_POSITION_UNKNOWN },
        { "LEFT", TrafficLightLateralPosition::TRAFFIC_LIGHT_LATERAL_POSITION_LEFT },
        { "RIGHT", TrafficLightLateralPosition::TRAFFIC_LIGHT_LATERAL_POSITION_RIGHT },
        { "ABOVE", TrafficLightLateralPosition::TRAFFIC_LIGHT_LATERAL_POSITION_ABOVE },
        { "SURFACE", TrafficLightLateralPosition::TRAFFIC_LIGHT_LATERAL_POSITION_SURFACE },
        { "LEFT_ABOVE", TrafficLightLateralPosition::TRAFFIC_LIGHT_LATERAL_POSITION_LEFT_ABOVE },
        { "RIGHT_ABOVE", TrafficLightLateralPosition::TRAFFIC_LIGHT_LATERAL_POSITION_RIGHT_ABOVE }};
        return data;
    }

    static const ::std::map<::std::string, TrafficLightContentType>& ENUMSTR_TRAFFICLIGHTCONTENTTYPE() 
    { 
        static const ::std::map<::std::string, TrafficLightContentType> data{
        { "UNKNOWN", TrafficLightContentType::TRAFFIC_LIGHT_CONTENT_TYPE_UNKNOWN },
        { "NONE", TrafficLightContentType::TRAFFIC_LIGHT_CONTENT_TYPE_NONE },
        { "ARROW", TrafficLightContentType::TRAFFIC_LIGHT_CONTENT_TYPE_ARROW },
        { "DIGITS", TrafficLightContentType::TRAFFIC_LIGHT_CONTENT_TYPE_DIGITS },
        { "CHARACTERS", TrafficLightContentType::TRAFFIC_LIGHT_CONTENT_TYPE_CHARACTERS },
        { "ADMIXTURE", TrafficLightContentType::TRAFFIC_LIGHT_CONTENT_TYPE_ADMIXTURE },
        { "OTHERS", TrafficLightContentType::TRAFFIC_LIGHT_CONTENT_TYPE_OTHERS }};
        return data;
    }

    static const ::std::map<::std::string, TrafficLightOrientation>& ENUMSTR_TRAFFICLIGHTORIENTATION() 
    { 
        static const ::std::map<::std::string, TrafficLightOrientation> data{
        { "UNKNOWN", TrafficLightOrientation::TRAFFIC_LIGHT_ORIENTATION_UNKNOWN },
        { "SINGLE", TrafficLightOrientation::TRAFFIC_LIGHT_ORIENTATION_SINGLE },
        { "HORIZONTAL", TrafficLightOrientation::TRAFFIC_LIGHT_ORIENTATION_HORIZONTAL },
        { "VERTICAL", TrafficLightOrientation::TRAFFIC_LIGHT_ORIENTATION_VERTICAL }};
        return data;
    }


private:
    ::std::uint64_t object_traffic_light_id_; 
    ::std::uint64_t traffic_light_group_id_; 
    TrafficLightState traffic_light_state_; 
    TrafficLightLongitudinalPosition traffic_light_longitudinal_position_; 
    TrafficLightLateralPosition traffic_light_lateral_position_; 
    TrafficLightContentType traffic_light_content_type_; 
    TrafficLightOrientation traffic_light_orientation_; 
    ::std::uint32_t traffic_light_row_count_; 
    ::std::uint32_t traffic_light_column_count_; 
    ::std::uint64_t intersection_id_; 
    ::std::vector<::std::uint64_t> tile_ids_; 
    ::std::vector<::std::uint64_t> associated_lane_ids_; 
    ::std::vector<::std::uint64_t> associated_lane_group_ids_; 
    ::std::uint32_t zone_id_; 
    ::std::uint32_t extra_zone_id_; 
    bool south_flag_; 
    GeoBox geometry_; 
    ::std::map<::std::uint32_t, GeoBox> extra_geometry_; 
    Coordinate coordinate_; 

private:
    void DecodeProto(const ::holo::map::proto::base::ObjectTrafficLight& _proto_handler);
    ::holo::map::proto::base::ObjectTrafficLight EncodeProto();

public:
    ObjectTrafficLight();
    explicit ObjectTrafficLight(const ::holo::map::proto::base::ObjectTrafficLight& _proto_handler);
    // init all format data
    ObjectTrafficLight(const ::std::uint64_t _object_traffic_light_id,const ::std::uint64_t _traffic_light_group_id,const TrafficLightState& _traffic_light_state,const TrafficLightLongitudinalPosition& _traffic_light_longitudinal_position,const TrafficLightLateralPosition& _traffic_light_lateral_position,const TrafficLightContentType& _traffic_light_content_type,const TrafficLightOrientation& _traffic_light_orientation,const ::std::uint32_t _traffic_light_row_count,const ::std::uint32_t _traffic_light_column_count,const ::std::uint64_t _intersection_id,const ::std::vector<::std::uint64_t>& _tile_ids,const ::std::vector<::std::uint64_t>& _associated_lane_ids,const ::std::vector<::std::uint64_t>& _associated_lane_group_ids,const ::std::uint32_t _zone_id,const ::std::uint32_t _extra_zone_id,const bool _south_flag,const GeoBox& _geometry,const ::std::map<::std::uint32_t, GeoBox>& _extra_geometry,const Coordinate& _coordinate);
    ~ObjectTrafficLight();

    bool operator==(const ::holo::map::format::ObjectTrafficLight& _other) const;
    ObjectTrafficLight& operator=(const ::holo::map::proto::base::ObjectTrafficLight& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::base::ObjectTrafficLight GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetObjectTrafficLightId() const
    {
        return object_traffic_light_id_;
    }
    void SetObjectTrafficLightId(const ::std::uint64_t _object_traffic_light_id)
    {
        object_traffic_light_id_ = _object_traffic_light_id;
    }

    ::std::uint64_t GetTrafficLightGroupId() const
    {
        return traffic_light_group_id_;
    }
    void SetTrafficLightGroupId(const ::std::uint64_t _traffic_light_group_id)
    {
        traffic_light_group_id_ = _traffic_light_group_id;
    }

    const TrafficLightState& GetTrafficLightState() const
    {
        return traffic_light_state_;
    }
    void SetTrafficLightState(const TrafficLightState& _traffic_light_state)
    {
        traffic_light_state_ = _traffic_light_state;
    }

    const TrafficLightLongitudinalPosition& GetTrafficLightLongitudinalPosition() const
    {
        return traffic_light_longitudinal_position_;
    }
    void SetTrafficLightLongitudinalPosition(const TrafficLightLongitudinalPosition& _traffic_light_longitudinal_position)
    {
        traffic_light_longitudinal_position_ = _traffic_light_longitudinal_position;
    }

    const TrafficLightLateralPosition& GetTrafficLightLateralPosition() const
    {
        return traffic_light_lateral_position_;
    }
    void SetTrafficLightLateralPosition(const TrafficLightLateralPosition& _traffic_light_lateral_position)
    {
        traffic_light_lateral_position_ = _traffic_light_lateral_position;
    }

    const TrafficLightContentType& GetTrafficLightContentType() const
    {
        return traffic_light_content_type_;
    }
    void SetTrafficLightContentType(const TrafficLightContentType& _traffic_light_content_type)
    {
        traffic_light_content_type_ = _traffic_light_content_type;
    }

    const TrafficLightOrientation& GetTrafficLightOrientation() const
    {
        return traffic_light_orientation_;
    }
    void SetTrafficLightOrientation(const TrafficLightOrientation& _traffic_light_orientation)
    {
        traffic_light_orientation_ = _traffic_light_orientation;
    }

    ::std::uint32_t GetTrafficLightRowCount() const
    {
        return traffic_light_row_count_;
    }
    void SetTrafficLightRowCount(const ::std::uint32_t _traffic_light_row_count)
    {
        traffic_light_row_count_ = _traffic_light_row_count;
    }

    ::std::uint32_t GetTrafficLightColumnCount() const
    {
        return traffic_light_column_count_;
    }
    void SetTrafficLightColumnCount(const ::std::uint32_t _traffic_light_column_count)
    {
        traffic_light_column_count_ = _traffic_light_column_count;
    }

    ::std::uint64_t GetIntersectionId() const
    {
        return intersection_id_;
    }
    void SetIntersectionId(const ::std::uint64_t _intersection_id)
    {
        intersection_id_ = _intersection_id;
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

    const ::std::map<::std::uint32_t, GeoBox>* GetPtrExtraGeometry() const
    {
        return &extra_geometry_;
    }
    void SetExtraGeometry(const ::std::map<::std::uint32_t, GeoBox>& _extra_geometry)
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


    const GeoBox& GetGeometry() const;
    void SetGeometry(const GeoBox& _geometry)
    {
        this->geometry_ = _geometry;
    }







};  // class ObjectTrafficLight

typedef ::std::shared_ptr<ObjectTrafficLight> PtrObjectTrafficLight;
typedef const ::std::vector<ObjectTrafficLight>* ConstRawPtrVecObjectTrafficLight;
typedef ::std::vector<ObjectTrafficLight>* RawPtrVecObjectTrafficLight;
typedef ::std::shared_ptr<ObjectTrafficLight const> ConstPtrObjectTrafficLight;
typedef ::std::shared_ptr<::std::vector<ObjectTrafficLight> const> ConstPtrVecObjectTrafficLight;
typedef ::std::unordered_map<::std::uint64_t, PtrObjectTrafficLight> HashmapObjectTrafficLight;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_BASE_OBJECT_TRAFFIC_LIGHT_H_