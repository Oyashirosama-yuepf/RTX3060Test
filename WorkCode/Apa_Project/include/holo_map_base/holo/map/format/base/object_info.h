/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file object_info.h
 * @brief Auto generated code for ObjectInfo format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_BASE_OBJECT_INFO_H_
#define HOLO_MAP_FORMAT_BASE_OBJECT_INFO_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/base/object_info.pb.h>

#include <holo/map/proto/common/coordinate.pb.h>

#include <holo/map/proto/common/geo_box.pb.h>

#include <holo/map/proto/common/geo_point.pb.h>

#include <holo/map/proto/common/geo_line.pb.h>

#include <holo/map/proto/common/geo_multi_line.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/coordinate.h>

#include <holo/map/format/common/geo_box.h>

#include <holo/map/format/common/geo_point.h>

#include <holo/map/format/common/geo_line.h>

#include <holo/map/format/common/geo_multi_line.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  ObjectInfo: public Base
{
public:

        
    enum ObjectType
    {
        OBJECT_TYPE_UNDEFINED=  0,  
        OBJECT_TYPE_SIGN=  1,  
        OBJECT_TYPE_POLE=  2,  
        OBJECT_TYPE_TRAFICLIGHT=  3,  
        OBJECT_TYPE_MARKING=  4,  
        OBJECT_TYPE_WALL=  5,  
        OBJECT_TYPE_OBSTACLE=  6,  
        OBJECT_TYPE_BARRIER=  7,  
        OBJECT_TYPE_OSF=  8,  
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
        TRAFFIC_SIGN_SHAPE_UNKNOWN=  15,  
    };

        
    enum TrafficSignType
    {
        TRAFFIC_SIGN_TYPE_UNDEFINED=  0,  
        TRAFFIC_SIGN_TYPE_SPEED_LIMIT=  1,  
        TRAFFIC_SIGN_TYPE_SPEED_LIMIT_END=  2,  
        TRAFFIC_SIGN_TYPE_ADVISORY_SPEED_LIMIT=  3,  
        TRAFFIC_SIGN_TYPE_ADVISORY_SPEED_LIMIT_END=  4,  
        TRAFFIC_SIGN_TYPE_NO_OVERTAKING=  5,  
        TRAFFIC_SIGN_TYPE_NO_OVERTAKING_END=  6,  
        TRAFFIC_SIGN_TYPE_DO_NOT_ENTER=  7,  
        TRAFFIC_SIGN_TYPE_ANIMALS=  8,  
        TRAFFIC_SIGN_TYPE_BICYCLE_PATH=  9,  
        TRAFFIC_SIGN_TYPE_VEHICLES_PROHIBITED=  10,  
        TRAFFIC_SIGN_TYPE_MOTORWAY_END=  11,  
        TRAFFIC_SIGN_TYPE_FALLING_ROCKS=  12,  
        TRAFFIC_SIGN_TYPE_HEIGHT_RESTRICTION=  13,  
        TRAFFIC_SIGN_TYPE_ICY_ROAD=  14,  
        TRAFFIC_SIGN_TYPE_LENGTH_RESTRICTION=  15,  
        TRAFFIC_SIGN_TYPE_MOTORWAY=  16,  
        TRAFFIC_SIGN_TYPE_NO_OVERTAKING_FOR_TRUCKS=  17,  
        TRAFFIC_SIGN_TYPE_NO_OVERTAKING_FOR_TRUCKS_END=  18,  
        TRAFFIC_SIGN_TYPE_PASSING_RESTRICTION=  19,  
        TRAFFIC_SIGN_TYPE_CARRIAGEWAY_NARROWS=  20,  
        TRAFFIC_SIGN_TYPE_SLIPPERY_ROAD=  21,  
        TRAFFIC_SIGN_TYPE_TRUCK_SPEED_LIMIT=  22,  
        TRAFFIC_SIGN_TYPE_TURN_RESTRICTION=  23,  
        TRAFFIC_SIGN_TYPE_RICTION=  24,  
        TRAFFIC_SIGN_TYPE_WEIGHT_RESTRICTION=  25,  
        TRAFFIC_SIGN_TYPE_YIELD=  26,  
        TRAFFIC_SIGN_TYPE_CURVY_ROAD=  27,  
        TRAFFIC_SIGN_TYPE_NARROW_BRIDGE=  28,  
        TRAFFIC_SIGN_TYPE_TWO_WAY_TRAFFIC=  29,  
        TRAFFIC_SIGN_TYPE_PEDESTRIANS=  30,  
        TRAFFIC_SIGN_TYPE_CHILDREN=  31,  
        TRAFFIC_SIGN_TYPE_WIND=  32,  
        TRAFFIC_SIGN_TYPE_EMBANKMENT=  33,  
        TRAFFIC_SIGN_TYPE_VILLAGE_AHEAD=  34,  
        TRAFFIC_SIGN_TYPE_TUNNEL=  35,  
        TRAFFIC_SIGN_TYPE_FERRY_TERMINAL=  36,  
        TRAFFIC_SIGN_TYPE_HUMPBACK_BRIDGE=  37,  
        TRAFFIC_SIGN_TYPE_UNEVEN_ROAD=  38,  
        TRAFFIC_SIGN_TYPE_BUMP=  39,  
        TRAFFIC_SIGN_TYPE_DIP=  40,  
        TRAFFIC_SIGN_TYPE_ROAD_FLOODS=  41,  
        TRAFFIC_SIGN_TYPE_RAILROAD_CROSSING=  42,  
        TRAFFIC_SIGN_TYPE_HIGH_ACCIDENT_AREA=  43,  
        TRAFFIC_SIGN_TYPE_SLOW_DOWN=  44,  
        TRAFFIC_SIGN_TYPE_PASS_OBSTACLE=  45,  
        TRAFFIC_SIGN_TYPE_GENERAL_HAZARD=  46,  
        TRAFFIC_SIGN_TYPE_ROAD_WORKS=  47,  
        TRAFFIC_SIGN_TYPE_TRAFFIC_CONGESTION=  48,  
        TRAFFIC_SIGN_TYPE_PEDESTRIANS_PROHIBITED=  49,  
        TRAFFIC_SIGN_TYPE_HONKING_PROHIBITED=  50,  
        TRAFFIC_SIGN_TYPE_ONEWAY=  51,  
        TRAFFIC_SIGN_TYPE_PEDESTRIAN_PATH=  52,  
        TRAFFIC_SIGN_TYPE_END_OF_ALL_RESTRICTIONS=  53,  
        TRAFFIC_SIGN_TYPE_PRIORITY_ROAD=  54,  
        TRAFFIC_SIGN_TYPE_PRIORITY_OVER_ONCOMING=  55,  
        TRAFFIC_SIGN_TYPE_PEDESTRIAN_CROSSING=  56,  
        TRAFFIC_SIGN_TYPE_SHARP_CURVY_ROAD=  57,  
        TRAFFIC_SIGN_TYPE_LANE_END=  58,  
        TRAFFIC_SIGN_TYPE_ROLLOVER=  59,  
        TRAFFIC_SIGN_TYPE_TRAFIC_LIGHT_SIGNALS=  60,  
        TRAFFIC_SIGN_TYPE_STOP=  61,  
        TRAFFIC_SIGN_TYPE_NO_PARKING=  62,  
        TRAFFIC_SIGN_TYPE_INTERSECTION=  63,  
        TRAFFIC_SIGN_TYPE_REVERSE_CURVE=  64,  
        TRAFFIC_SIGN_TYPE_STEEP_HILLS=  65,  
        TRAFFIC_SIGN_TYPE_STEEP_DROP=  66,  
        TRAFFIC_SIGN_TYPE_WATCH_HANDICAPPED=  67,  
        TRAFFIC_SIGN_TYPE_LIGHT_UP_IN_TUNNEL=  68,  
        TRAFFIC_SIGN_TYPE_REVERSIBLE_LANE=  69,  
        TRAFFIC_SIGN_TYPE_MAINTAIN_SAFE_DISTANCE=  70,  
        TRAFFIC_SIGN_TYPE_SEPARATED_ROAD=  71,  
        TRAFFIC_SIGN_TYPE_CONFLUENCE=  72,  
        TRAFFIC_SIGN_TYPE_TRUCK_ESCAPE_RAMPS=  73,  
        TRAFFIC_SIGN_TYPE_ADVERSE_WEATHER=  74,  
        TRAFFIC_SIGN_TYPE_STOP_FOR_INSPECTION=  75,  
        TRAFFIC_SIGN_TYPE_CUSTOMS=  76,  
        TRAFFIC_SIGN_TYPE_LANE_DRIVING_DIRECTION=  77,  
        TRAFFIC_SIGN_TYPE_BUS_LANE=  78,  
        TRAFFIC_SIGN_TYPE_VEHICLE_LANE=  79,  
        TRAFFIC_SIGN_TYPE_NON_MOTOR_VEHICLE_LANE=  80,  
        TRAFFIC_SIGN_TYPE_BRT_Lane=  81,  
        TRAFFIC_SIGN_TYPE_HOV_Lane=  82,  
        TRAFFIC_SIGN_TYPE_PARKING=  83,  
        TRAFFIC_SIGN_TYPE_SIGN_TYPE_COUNT=  84,  
        TRAFFIC_SIGN_TYPE_SIGN_TYPE_UNKNOWN=  86,  
    };

        
    enum MarkingColor
    {
        MARKING_COLOR_UNKNOWN=  0,  
        MARKING_COLOR_LIGHT_GRAY=  1,  
        MARKING_COLOR_GRAY=  2,  
        MARKING_COLOR_DARK_GRAY=  3,  
        MARKING_COLOR_BLACK=  4,  
        MARKING_COLOR_RED=  5,  
        MARKING_COLOR_YELLOW=  6,  
        MARKING_COLOR_GREEN=  7,  
        MARKING_COLOR_CYAN=  8,  
        MARKING_COLOR_BLUE=  9,  
        MARKING_COLOR_ORANGE=  10,  
        MARKING_COLOR_WHITE=  11,  
    };

        
    enum MarkingType
    {
        MARKING_TYPE_UNDEFINED=  0,  
        MARKING_TYPE_ARROW_STRAIGHT=  1,  
        MARKING_TYPE_ARROW_LEFT=  2,  
        MARKING_TYPE_ARROW_RIGHT=  3,  
        MARKING_TYPE_ARROW_STRAIGHT_AND_LEFT=  4,  
        MARKING_TYPE_ARROW_STRAIGHT_AND_RIGHT=  5,  
        MARKING_TYPE_ARROW_LEFT_AND_RIGHT=  6,  
        MARKING_TYPE_LINE_ELEMENT=  7,  
        MARKING_TYPE_STOP_LINE=  8,  
        MARKING_TYPE_CROSSWALK=  9,  
        MARKING_TYPE_SIGN=  10,  
        MARKING_TYPE_DASHED_LINE_ELEMENT=  11,  
        MARKING_TYPE_YIELD_INDICATION=  12,  
        MARKING_TYPE_VISUAL_SPEED_BUMP=  13,  
        MARKING_TYPE_SHADED_AREA=  14,  
        MARKING_TYPE_OTHER=  15,  
        MARKING_TYPE_TEXT=  16,  
    };

        
    enum MarkingGeometryType
    {
        MARKING_GEOMETRY_TYPE_UNDEFINED=  0,  
        MARKING_GEOMETRY_TYPE_BOUNDARY_BOX=  1,  
        MARKING_GEOMETRY_TYPE_CENTER_LINE=  2,  
    };

        
    enum PoleObjectType
    {
        POLE_OBJECT_TYPE_UNDEFINED=  0,  
        POLE_OBJECT_TYPE_LIGHT_POLE=  1,  
        POLE_OBJECT_TYPE_DELINEATOR_POST=  2,  
        POLE_OBJECT_TYPE_REFLECTOR_POST=  3,  
        POLE_OBJECT_TYPE_GANTRY_POLE=  4,  
        POLE_OBJECT_TYPE_SIGNPOST=  5,  
        POLE_OBJECT_TYPE_OTHER=  6,  
        POLE_OBJECT_TYPE_UNCLASSIFIED=  7,  
        POLE_OBJECT_TYPE_GUARDRAIL_POST=  8,  
        POLE_OBJECT_TYPE_UNKNOWN=  99,  
    };

    static const ::std::map<::std::string, ObjectType>& ENUMSTR_OBJECTTYPE() 
    { 
        static const ::std::map<::std::string, ObjectType> data{
        { "UNDEFINED", ObjectType::OBJECT_TYPE_UNDEFINED },
        { "SIGN", ObjectType::OBJECT_TYPE_SIGN },
        { "POLE", ObjectType::OBJECT_TYPE_POLE },
        { "TRAFICLIGHT", ObjectType::OBJECT_TYPE_TRAFICLIGHT },
        { "MARKING", ObjectType::OBJECT_TYPE_MARKING },
        { "WALL", ObjectType::OBJECT_TYPE_WALL },
        { "OBSTACLE", ObjectType::OBJECT_TYPE_OBSTACLE },
        { "BARRIER", ObjectType::OBJECT_TYPE_BARRIER },
        { "OSF", ObjectType::OBJECT_TYPE_OSF }};
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

    static const ::std::map<::std::string, TrafficSignType>& ENUMSTR_TRAFFICSIGNTYPE() 
    { 
        static const ::std::map<::std::string, TrafficSignType> data{
        { "UNDEFINED", TrafficSignType::TRAFFIC_SIGN_TYPE_UNDEFINED },
        { "SPEED_LIMIT", TrafficSignType::TRAFFIC_SIGN_TYPE_SPEED_LIMIT },
        { "SPEED_LIMIT_END", TrafficSignType::TRAFFIC_SIGN_TYPE_SPEED_LIMIT_END },
        { "ADVISORY_SPEED_LIMIT", TrafficSignType::TRAFFIC_SIGN_TYPE_ADVISORY_SPEED_LIMIT },
        { "ADVISORY_SPEED_LIMIT_END", TrafficSignType::TRAFFIC_SIGN_TYPE_ADVISORY_SPEED_LIMIT_END },
        { "NO_OVERTAKING", TrafficSignType::TRAFFIC_SIGN_TYPE_NO_OVERTAKING },
        { "NO_OVERTAKING_END", TrafficSignType::TRAFFIC_SIGN_TYPE_NO_OVERTAKING_END },
        { "DO_NOT_ENTER", TrafficSignType::TRAFFIC_SIGN_TYPE_DO_NOT_ENTER },
        { "ANIMALS", TrafficSignType::TRAFFIC_SIGN_TYPE_ANIMALS },
        { "BICYCLE_PATH", TrafficSignType::TRAFFIC_SIGN_TYPE_BICYCLE_PATH },
        { "VEHICLES_PROHIBITED", TrafficSignType::TRAFFIC_SIGN_TYPE_VEHICLES_PROHIBITED },
        { "MOTORWAY_END", TrafficSignType::TRAFFIC_SIGN_TYPE_MOTORWAY_END },
        { "FALLING_ROCKS", TrafficSignType::TRAFFIC_SIGN_TYPE_FALLING_ROCKS },
        { "HEIGHT_RESTRICTION", TrafficSignType::TRAFFIC_SIGN_TYPE_HEIGHT_RESTRICTION },
        { "ICY_ROAD", TrafficSignType::TRAFFIC_SIGN_TYPE_ICY_ROAD },
        { "LENGTH_RESTRICTION", TrafficSignType::TRAFFIC_SIGN_TYPE_LENGTH_RESTRICTION },
        { "MOTORWAY", TrafficSignType::TRAFFIC_SIGN_TYPE_MOTORWAY },
        { "NO_OVERTAKING_FOR_TRUCKS", TrafficSignType::TRAFFIC_SIGN_TYPE_NO_OVERTAKING_FOR_TRUCKS },
        { "NO_OVERTAKING_FOR_TRUCKS_END", TrafficSignType::TRAFFIC_SIGN_TYPE_NO_OVERTAKING_FOR_TRUCKS_END },
        { "PASSING_RESTRICTION", TrafficSignType::TRAFFIC_SIGN_TYPE_PASSING_RESTRICTION },
        { "CARRIAGEWAY_NARROWS", TrafficSignType::TRAFFIC_SIGN_TYPE_CARRIAGEWAY_NARROWS },
        { "SLIPPERY_ROAD", TrafficSignType::TRAFFIC_SIGN_TYPE_SLIPPERY_ROAD },
        { "TRUCK_SPEED_LIMIT", TrafficSignType::TRAFFIC_SIGN_TYPE_TRUCK_SPEED_LIMIT },
        { "TURN_RESTRICTION", TrafficSignType::TRAFFIC_SIGN_TYPE_TURN_RESTRICTION },
        { "RICTION", TrafficSignType::TRAFFIC_SIGN_TYPE_RICTION },
        { "WEIGHT_RESTRICTION", TrafficSignType::TRAFFIC_SIGN_TYPE_WEIGHT_RESTRICTION },
        { "YIELD", TrafficSignType::TRAFFIC_SIGN_TYPE_YIELD },
        { "CURVY_ROAD", TrafficSignType::TRAFFIC_SIGN_TYPE_CURVY_ROAD },
        { "NARROW_BRIDGE", TrafficSignType::TRAFFIC_SIGN_TYPE_NARROW_BRIDGE },
        { "TWO_WAY_TRAFFIC", TrafficSignType::TRAFFIC_SIGN_TYPE_TWO_WAY_TRAFFIC },
        { "PEDESTRIANS", TrafficSignType::TRAFFIC_SIGN_TYPE_PEDESTRIANS },
        { "CHILDREN", TrafficSignType::TRAFFIC_SIGN_TYPE_CHILDREN },
        { "WIND", TrafficSignType::TRAFFIC_SIGN_TYPE_WIND },
        { "EMBANKMENT", TrafficSignType::TRAFFIC_SIGN_TYPE_EMBANKMENT },
        { "VILLAGE_AHEAD", TrafficSignType::TRAFFIC_SIGN_TYPE_VILLAGE_AHEAD },
        { "TUNNEL", TrafficSignType::TRAFFIC_SIGN_TYPE_TUNNEL },
        { "FERRY_TERMINAL", TrafficSignType::TRAFFIC_SIGN_TYPE_FERRY_TERMINAL },
        { "HUMPBACK_BRIDGE", TrafficSignType::TRAFFIC_SIGN_TYPE_HUMPBACK_BRIDGE },
        { "UNEVEN_ROAD", TrafficSignType::TRAFFIC_SIGN_TYPE_UNEVEN_ROAD },
        { "BUMP", TrafficSignType::TRAFFIC_SIGN_TYPE_BUMP },
        { "DIP", TrafficSignType::TRAFFIC_SIGN_TYPE_DIP },
        { "ROAD_FLOODS", TrafficSignType::TRAFFIC_SIGN_TYPE_ROAD_FLOODS },
        { "RAILROAD_CROSSING", TrafficSignType::TRAFFIC_SIGN_TYPE_RAILROAD_CROSSING },
        { "HIGH_ACCIDENT_AREA", TrafficSignType::TRAFFIC_SIGN_TYPE_HIGH_ACCIDENT_AREA },
        { "SLOW_DOWN", TrafficSignType::TRAFFIC_SIGN_TYPE_SLOW_DOWN },
        { "PASS_OBSTACLE", TrafficSignType::TRAFFIC_SIGN_TYPE_PASS_OBSTACLE },
        { "GENERAL_HAZARD", TrafficSignType::TRAFFIC_SIGN_TYPE_GENERAL_HAZARD },
        { "ROAD_WORKS", TrafficSignType::TRAFFIC_SIGN_TYPE_ROAD_WORKS },
        { "TRAFFIC_CONGESTION", TrafficSignType::TRAFFIC_SIGN_TYPE_TRAFFIC_CONGESTION },
        { "PEDESTRIANS_PROHIBITED", TrafficSignType::TRAFFIC_SIGN_TYPE_PEDESTRIANS_PROHIBITED },
        { "HONKING_PROHIBITED", TrafficSignType::TRAFFIC_SIGN_TYPE_HONKING_PROHIBITED },
        { "ONEWAY", TrafficSignType::TRAFFIC_SIGN_TYPE_ONEWAY },
        { "PEDESTRIAN_PATH", TrafficSignType::TRAFFIC_SIGN_TYPE_PEDESTRIAN_PATH },
        { "END_OF_ALL_RESTRICTIONS", TrafficSignType::TRAFFIC_SIGN_TYPE_END_OF_ALL_RESTRICTIONS },
        { "PRIORITY_ROAD", TrafficSignType::TRAFFIC_SIGN_TYPE_PRIORITY_ROAD },
        { "PRIORITY_OVER_ONCOMING", TrafficSignType::TRAFFIC_SIGN_TYPE_PRIORITY_OVER_ONCOMING },
        { "PEDESTRIAN_CROSSING", TrafficSignType::TRAFFIC_SIGN_TYPE_PEDESTRIAN_CROSSING },
        { "SHARP_CURVY_ROAD", TrafficSignType::TRAFFIC_SIGN_TYPE_SHARP_CURVY_ROAD },
        { "LANE_END", TrafficSignType::TRAFFIC_SIGN_TYPE_LANE_END },
        { "ROLLOVER", TrafficSignType::TRAFFIC_SIGN_TYPE_ROLLOVER },
        { "TRAFIC_LIGHT_SIGNALS", TrafficSignType::TRAFFIC_SIGN_TYPE_TRAFIC_LIGHT_SIGNALS },
        { "STOP", TrafficSignType::TRAFFIC_SIGN_TYPE_STOP },
        { "NO_PARKING", TrafficSignType::TRAFFIC_SIGN_TYPE_NO_PARKING },
        { "INTERSECTION", TrafficSignType::TRAFFIC_SIGN_TYPE_INTERSECTION },
        { "REVERSE_CURVE", TrafficSignType::TRAFFIC_SIGN_TYPE_REVERSE_CURVE },
        { "STEEP_HILLS", TrafficSignType::TRAFFIC_SIGN_TYPE_STEEP_HILLS },
        { "STEEP_DROP", TrafficSignType::TRAFFIC_SIGN_TYPE_STEEP_DROP },
        { "WATCH_HANDICAPPED", TrafficSignType::TRAFFIC_SIGN_TYPE_WATCH_HANDICAPPED },
        { "LIGHT_UP_IN_TUNNEL", TrafficSignType::TRAFFIC_SIGN_TYPE_LIGHT_UP_IN_TUNNEL },
        { "REVERSIBLE_LANE", TrafficSignType::TRAFFIC_SIGN_TYPE_REVERSIBLE_LANE },
        { "MAINTAIN_SAFE_DISTANCE", TrafficSignType::TRAFFIC_SIGN_TYPE_MAINTAIN_SAFE_DISTANCE },
        { "SEPARATED_ROAD", TrafficSignType::TRAFFIC_SIGN_TYPE_SEPARATED_ROAD },
        { "CONFLUENCE", TrafficSignType::TRAFFIC_SIGN_TYPE_CONFLUENCE },
        { "TRUCK_ESCAPE_RAMPS", TrafficSignType::TRAFFIC_SIGN_TYPE_TRUCK_ESCAPE_RAMPS },
        { "ADVERSE_WEATHER", TrafficSignType::TRAFFIC_SIGN_TYPE_ADVERSE_WEATHER },
        { "STOP_FOR_INSPECTION", TrafficSignType::TRAFFIC_SIGN_TYPE_STOP_FOR_INSPECTION },
        { "CUSTOMS", TrafficSignType::TRAFFIC_SIGN_TYPE_CUSTOMS },
        { "LANE_DRIVING_DIRECTION", TrafficSignType::TRAFFIC_SIGN_TYPE_LANE_DRIVING_DIRECTION },
        { "BUS_LANE", TrafficSignType::TRAFFIC_SIGN_TYPE_BUS_LANE },
        { "VEHICLE_LANE", TrafficSignType::TRAFFIC_SIGN_TYPE_VEHICLE_LANE },
        { "NON_MOTOR_VEHICLE_LANE", TrafficSignType::TRAFFIC_SIGN_TYPE_NON_MOTOR_VEHICLE_LANE },
        { "BRT_Lane", TrafficSignType::TRAFFIC_SIGN_TYPE_BRT_Lane },
        { "HOV_Lane", TrafficSignType::TRAFFIC_SIGN_TYPE_HOV_Lane },
        { "PARKING", TrafficSignType::TRAFFIC_SIGN_TYPE_PARKING },
        { "SIGN_TYPE_COUNT", TrafficSignType::TRAFFIC_SIGN_TYPE_SIGN_TYPE_COUNT },
        { "SIGN_TYPE_UNKNOWN", TrafficSignType::TRAFFIC_SIGN_TYPE_SIGN_TYPE_UNKNOWN }};
        return data;
    }

    static const ::std::map<::std::string, MarkingColor>& ENUMSTR_MARKINGCOLOR() 
    { 
        static const ::std::map<::std::string, MarkingColor> data{
        { "UNKNOWN", MarkingColor::MARKING_COLOR_UNKNOWN },
        { "LIGHT_GRAY", MarkingColor::MARKING_COLOR_LIGHT_GRAY },
        { "GRAY", MarkingColor::MARKING_COLOR_GRAY },
        { "DARK_GRAY", MarkingColor::MARKING_COLOR_DARK_GRAY },
        { "BLACK", MarkingColor::MARKING_COLOR_BLACK },
        { "RED", MarkingColor::MARKING_COLOR_RED },
        { "YELLOW", MarkingColor::MARKING_COLOR_YELLOW },
        { "GREEN", MarkingColor::MARKING_COLOR_GREEN },
        { "CYAN", MarkingColor::MARKING_COLOR_CYAN },
        { "BLUE", MarkingColor::MARKING_COLOR_BLUE },
        { "ORANGE", MarkingColor::MARKING_COLOR_ORANGE },
        { "WHITE", MarkingColor::MARKING_COLOR_WHITE }};
        return data;
    }

    static const ::std::map<::std::string, MarkingType>& ENUMSTR_MARKINGTYPE() 
    { 
        static const ::std::map<::std::string, MarkingType> data{
        { "UNDEFINED", MarkingType::MARKING_TYPE_UNDEFINED },
        { "ARROW_STRAIGHT", MarkingType::MARKING_TYPE_ARROW_STRAIGHT },
        { "ARROW_LEFT", MarkingType::MARKING_TYPE_ARROW_LEFT },
        { "ARROW_RIGHT", MarkingType::MARKING_TYPE_ARROW_RIGHT },
        { "ARROW_STRAIGHT_AND_LEFT", MarkingType::MARKING_TYPE_ARROW_STRAIGHT_AND_LEFT },
        { "ARROW_STRAIGHT_AND_RIGHT", MarkingType::MARKING_TYPE_ARROW_STRAIGHT_AND_RIGHT },
        { "ARROW_LEFT_AND_RIGHT", MarkingType::MARKING_TYPE_ARROW_LEFT_AND_RIGHT },
        { "LINE_ELEMENT", MarkingType::MARKING_TYPE_LINE_ELEMENT },
        { "STOP_LINE", MarkingType::MARKING_TYPE_STOP_LINE },
        { "CROSSWALK", MarkingType::MARKING_TYPE_CROSSWALK },
        { "SIGN", MarkingType::MARKING_TYPE_SIGN },
        { "DASHED_LINE_ELEMENT", MarkingType::MARKING_TYPE_DASHED_LINE_ELEMENT },
        { "YIELD_INDICATION", MarkingType::MARKING_TYPE_YIELD_INDICATION },
        { "VISUAL_SPEED_BUMP", MarkingType::MARKING_TYPE_VISUAL_SPEED_BUMP },
        { "SHADED_AREA", MarkingType::MARKING_TYPE_SHADED_AREA },
        { "OTHER", MarkingType::MARKING_TYPE_OTHER },
        { "TEXT", MarkingType::MARKING_TYPE_TEXT }};
        return data;
    }

    static const ::std::map<::std::string, MarkingGeometryType>& ENUMSTR_MARKINGGEOMETRYTYPE() 
    { 
        static const ::std::map<::std::string, MarkingGeometryType> data{
        { "UNDEFINED", MarkingGeometryType::MARKING_GEOMETRY_TYPE_UNDEFINED },
        { "BOUNDARY_BOX", MarkingGeometryType::MARKING_GEOMETRY_TYPE_BOUNDARY_BOX },
        { "CENTER_LINE", MarkingGeometryType::MARKING_GEOMETRY_TYPE_CENTER_LINE }};
        return data;
    }

    static const ::std::map<::std::string, PoleObjectType>& ENUMSTR_POLEOBJECTTYPE() 
    { 
        static const ::std::map<::std::string, PoleObjectType> data{
        { "UNDEFINED", PoleObjectType::POLE_OBJECT_TYPE_UNDEFINED },
        { "LIGHT_POLE", PoleObjectType::POLE_OBJECT_TYPE_LIGHT_POLE },
        { "DELINEATOR_POST", PoleObjectType::POLE_OBJECT_TYPE_DELINEATOR_POST },
        { "REFLECTOR_POST", PoleObjectType::POLE_OBJECT_TYPE_REFLECTOR_POST },
        { "GANTRY_POLE", PoleObjectType::POLE_OBJECT_TYPE_GANTRY_POLE },
        { "SIGNPOST", PoleObjectType::POLE_OBJECT_TYPE_SIGNPOST },
        { "OTHER", PoleObjectType::POLE_OBJECT_TYPE_OTHER },
        { "UNCLASSIFIED", PoleObjectType::POLE_OBJECT_TYPE_UNCLASSIFIED },
        { "GUARDRAIL_POST", PoleObjectType::POLE_OBJECT_TYPE_GUARDRAIL_POST },
        { "UNKNOWN", PoleObjectType::POLE_OBJECT_TYPE_UNKNOWN }};
        return data;
    }


private:
    ::std::uint64_t object_id_; 
    ObjectType object_type_; 
    ::std::int32_t height_cm_; 
    TrafficSignShape traffic_sign_shape_; 
    TrafficSignType traffic_sign_type_; 
    ::std::uint32_t pole_upper_dm_; 
    ::std::uint32_t pole_lower_dm_; 
    MarkingColor marking_color_; 
    MarkingType marking_type_; 
    MarkingGeometryType marking_geometry_type_; 
    PoleObjectType pole_object_type_; 
    ::std::vector<::std::uint64_t> road_ids_; 
    ::std::vector<::std::uint64_t> lane_ids_; 
    ::std::vector<::std::uint64_t> tile_ids_; 
    ::std::uint64_t object_info_id_; 
    Coordinate coordinate_; 
    ::std::uint32_t zone_id_; 
    ::std::uint32_t extra_zone_id_; 
    bool south_flag_; 
    GeoBox region_; 
    ::std::map<::std::uint32_t, GeoBox> extra_region_; 
    GeoPoint object_geo_point_; 
    ::std::map<::std::uint32_t, GeoPoint> extra_object_geo_point_; 
    ::std::vector<GeoLine> object_geo_lines_; 
    ::std::map<::std::uint32_t, GeoMultiLine> extra_object_geo_lines_; 

private:
    void DecodeProto(const ::holo::map::proto::base::ObjectInfo& _proto_handler);
    ::holo::map::proto::base::ObjectInfo EncodeProto();

public:
    ObjectInfo();
    explicit ObjectInfo(const ::holo::map::proto::base::ObjectInfo& _proto_handler);
    // init all format data
    ObjectInfo(const ::std::uint64_t _object_id,const ObjectType& _object_type,const ::std::int32_t _height_cm,const TrafficSignShape& _traffic_sign_shape,const TrafficSignType& _traffic_sign_type,const ::std::uint32_t _pole_upper_dm,const ::std::uint32_t _pole_lower_dm,const MarkingColor& _marking_color,const MarkingType& _marking_type,const MarkingGeometryType& _marking_geometry_type,const PoleObjectType& _pole_object_type,const ::std::vector<::std::uint64_t>& _road_ids,const ::std::vector<::std::uint64_t>& _lane_ids,const ::std::vector<::std::uint64_t>& _tile_ids,const ::std::uint64_t _object_info_id,const Coordinate& _coordinate,const ::std::uint32_t _zone_id,const ::std::uint32_t _extra_zone_id,const bool _south_flag,const GeoBox& _region,const ::std::map<::std::uint32_t, GeoBox>& _extra_region,const GeoPoint& _object_geo_point,const ::std::map<::std::uint32_t, GeoPoint>& _extra_object_geo_point,const ::std::vector<GeoLine>& _object_geo_lines,const ::std::map<::std::uint32_t, GeoMultiLine>& _extra_object_geo_lines);
    ~ObjectInfo();

    bool operator==(const ::holo::map::format::ObjectInfo& _other) const;
    ObjectInfo& operator=(const ::holo::map::proto::base::ObjectInfo& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::base::ObjectInfo GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetObjectId() const
    {
        return object_id_;
    }
    void SetObjectId(const ::std::uint64_t _object_id)
    {
        object_id_ = _object_id;
    }

    const ObjectType& GetObjectType() const
    {
        return object_type_;
    }
    void SetObjectType(const ObjectType& _object_type)
    {
        object_type_ = _object_type;
    }

    ::std::int32_t GetHeightCm() const
    {
        return height_cm_;
    }
    void SetHeightCm(const ::std::int32_t _height_cm)
    {
        height_cm_ = _height_cm;
    }

    const TrafficSignShape& GetTrafficSignShape() const
    {
        return traffic_sign_shape_;
    }
    void SetTrafficSignShape(const TrafficSignShape& _traffic_sign_shape)
    {
        traffic_sign_shape_ = _traffic_sign_shape;
    }

    const TrafficSignType& GetTrafficSignType() const
    {
        return traffic_sign_type_;
    }
    void SetTrafficSignType(const TrafficSignType& _traffic_sign_type)
    {
        traffic_sign_type_ = _traffic_sign_type;
    }

    ::std::uint32_t GetPoleUpperDm() const
    {
        return pole_upper_dm_;
    }
    void SetPoleUpperDm(const ::std::uint32_t _pole_upper_dm)
    {
        pole_upper_dm_ = _pole_upper_dm;
    }

    ::std::uint32_t GetPoleLowerDm() const
    {
        return pole_lower_dm_;
    }
    void SetPoleLowerDm(const ::std::uint32_t _pole_lower_dm)
    {
        pole_lower_dm_ = _pole_lower_dm;
    }

    const MarkingColor& GetMarkingColor() const
    {
        return marking_color_;
    }
    void SetMarkingColor(const MarkingColor& _marking_color)
    {
        marking_color_ = _marking_color;
    }

    const MarkingType& GetMarkingType() const
    {
        return marking_type_;
    }
    void SetMarkingType(const MarkingType& _marking_type)
    {
        marking_type_ = _marking_type;
    }

    const MarkingGeometryType& GetMarkingGeometryType() const
    {
        return marking_geometry_type_;
    }
    void SetMarkingGeometryType(const MarkingGeometryType& _marking_geometry_type)
    {
        marking_geometry_type_ = _marking_geometry_type;
    }

    const PoleObjectType& GetPoleObjectType() const
    {
        return pole_object_type_;
    }
    void SetPoleObjectType(const PoleObjectType& _pole_object_type)
    {
        pole_object_type_ = _pole_object_type;
    }

    const ::std::vector<::std::uint64_t>* GetPtrRoadIds() const
    {
        return &road_ids_;
    }
    void SetRoadIds(const ::std::vector<::std::uint64_t>& _road_ids)
    {
        road_ids_ = _road_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrLaneIds() const
    {
        return &lane_ids_;
    }
    void SetLaneIds(const ::std::vector<::std::uint64_t>& _lane_ids)
    {
        lane_ids_ = _lane_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrTileIds() const
    {
        return &tile_ids_;
    }
    void SetTileIds(const ::std::vector<::std::uint64_t>& _tile_ids)
    {
        tile_ids_ = _tile_ids;
    }

    ::std::uint64_t GetObjectInfoId() const
    {
        return object_info_id_;
    }
    void SetObjectInfoId(const ::std::uint64_t _object_info_id)
    {
        object_info_id_ = _object_info_id;
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

    const ::std::map<::std::uint32_t, GeoBox>* GetPtrExtraRegion() const
    {
        return &extra_region_;
    }
    void SetExtraRegion(const ::std::map<::std::uint32_t, GeoBox>& _extra_region)
    {
        extra_region_ = _extra_region;
    }

    const ::std::map<::std::uint32_t, GeoPoint>* GetPtrExtraObjectGeoPoint() const
    {
        return &extra_object_geo_point_;
    }
    void SetExtraObjectGeoPoint(const ::std::map<::std::uint32_t, GeoPoint>& _extra_object_geo_point)
    {
        extra_object_geo_point_ = _extra_object_geo_point;
    }

    const ::std::map<::std::uint32_t, GeoMultiLine>* GetPtrExtraObjectGeoLines() const
    {
        return &extra_object_geo_lines_;
    }
    void SetExtraObjectGeoLines(const ::std::map<::std::uint32_t, GeoMultiLine>& _extra_object_geo_lines)
    {
        extra_object_geo_lines_ = _extra_object_geo_lines;
    }


    void ClearRoadIds()
    {
        road_ids_.clear();
    }
    void AddRoadIdsElement(const ::std::uint64_t& _value)
    {
        road_ids_.push_back(_value);
    }
    void UniqueAddRoadIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(road_ids_, _value);
    }

    void ClearLaneIds()
    {
        lane_ids_.clear();
    }
    void AddLaneIdsElement(const ::std::uint64_t& _value)
    {
        lane_ids_.push_back(_value);
    }
    void UniqueAddLaneIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(lane_ids_, _value);
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

    void ClearObjectGeoLines()
    {
        object_geo_lines_.clear();
    }
    void AddObjectGeoLinesElement(const GeoLine& _value)
    {
        object_geo_lines_.push_back(_value);
    }
    void UniqueAddObjectGeoLinesElements(const ::std::vector<GeoLine>& _value)
    {
        UniqueAppend(object_geo_lines_, _value);
    }


    const GeoBox& GetRegion() const;
    void SetRegion(const GeoBox& _region)
    {
        this->region_ = _region;
    }

    const GeoPoint& GetObjectGeoPoint() const;
    void SetObjectGeoPoint(const GeoPoint& _object_geo_point)
    {
        this->object_geo_point_ = _object_geo_point;
    }







    const ::std::vector<GeoLine>* GetPtrObjectGeoLines() const;
    void SetObjectGeoLines(const ::std::vector<GeoLine>& _object_geo_lines)
    {
        this->object_geo_lines_ = _object_geo_lines;
    }

};  // class ObjectInfo

typedef ::std::shared_ptr<ObjectInfo> PtrObjectInfo;
typedef const ::std::vector<ObjectInfo>* ConstRawPtrVecObjectInfo;
typedef ::std::vector<ObjectInfo>* RawPtrVecObjectInfo;
typedef ::std::shared_ptr<ObjectInfo const> ConstPtrObjectInfo;
typedef ::std::shared_ptr<::std::vector<ObjectInfo> const> ConstPtrVecObjectInfo;
typedef ::std::unordered_map<::std::uint64_t, PtrObjectInfo> HashmapObjectInfo;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_BASE_OBJECT_INFO_H_