/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane.h
 * @brief Auto generated code for Lane format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_BASE_LANE_H_
#define HOLO_MAP_FORMAT_BASE_LANE_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/base/lane.pb.h>

#include <holo/map/proto/common/coordinate.pb.h>

#include <holo/map/proto/common/geo_box.pb.h>

#include <holo/map/proto/common/geo_line.pb.h>

#include <holo/map/proto/common/geo_point.pb.h>

#include <holo/map/proto/common/id_interval_float64.pb.h>

#include <holo/map/proto/common/condition.pb.h>

#include <holo/map/proto/base/lane_width_info.pb.h>

#include <holo/map/proto/base/speed_limit_info.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/coordinate.h>

#include <holo/map/format/common/geo_box.h>

#include <holo/map/format/common/geo_line.h>

#include <holo/map/format/common/geo_point.h>

#include <holo/map/format/common/id_interval_float64.h>

#include <holo/map/format/common/condition.h>

#include <holo/map/format/base/lane_width_info.h>

#include <holo/map/format/base/speed_limit_info.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  Lane: public Base
{
public:

        
    enum LaneDir
    {
        LANE_DIR_UNDEFINED=  0,  
        LANE_DIR_POSITIVE_DIRECTION=  1,  
        LANE_DIR_NEGATIVE_DIRECTION=  2,  
        LANE_DIR_BI_DIRECTION=  3,  
    };

        
    enum LaneType
    {
        LANE_TYPE_UNDEFINED=  0,  
        LANE_TYPE_REGULAR=  1,  
        LANE_TYPE_EXPRESS=  2,  
        LANE_TYPE_CARPOOL=  3,  
        LANE_TYPE_TRAM=  5,  
        LANE_TYPE_TRUCK_PARKING=  6,  
        LANE_TYPE_SLOW=  7,  
        LANE_TYPE_HARD_SHOULDER=  9,  
        LANE_TYPE_REGULATED_ACCESS=  11,  
        LANE_TYPE_ACCELERATE=  12,  
        LANE_TYPE_DECELERATE=  13,  
        LANE_TYPE_DEDICATED_BUS=  19,  
        LANE_TYPE_BICYCLE=  20,  
        LANE_TYPE_PARKING_LANE=  26,  
        LANE_TYPE_EMERGENCY=  27,  
        LANE_TYPE_EMERGENCY_PARKING_STRIP=  28,  
        LANE_TYPE_ENTRY=  29,  
        LANE_TYPE_EXIT=  30,  
        LANE_TYPE_RAMP_ALL=  31,  
        LANE_TYPE_RAMP_ABOARD=  32,  
        LANE_TYPE_RAMP_ASHORE=  33,  
        LANE_TYPE_RAMP_JCT=  34,  
        LANE_TYPE_TOLL_BOOTH=  41,  
        LANE_TYPE_TOLL_GATE=  42,  
        LANE_TYPE_TOLL_GATE_ETC=  43,  
        LANE_TYPE_CLIMBING=  44,  
        LANE_TYPE_ESCAPE=  45,  
        LANE_TYPE_NON_DRIVE_WAY=  46,  
        LANE_TYPE_DEDICATED_CUSTOM=  47,  
        LANE_TYPE_REVERSIBLE=  48,  
        LANE_TYPE_VARIABLE=  49,  
        LANE_TYPE_DRIVABLE_SHOULDER=  50,  
        LANE_TYPE_DIS_DRIVABLE_SHOULDER=  51,  
        LANE_TYPE_REGULAR_DIVERSION=  52,  
        LANE_TYPE_RESERVED_1=  250,  
        LANE_TYPE_RESERVED_2=  251,  
        LANE_TYPE_RESERVED_3=  252,  
        LANE_TYPE_RESERVED_4=  253,  
        LANE_TYPE_RESERVED_5=  254,  
        LANE_TYPE_OTHER=  255,  
    };

        
    enum TurnType
    {
        TURN_TYPE_UNDEFINED=  0,  
        TURN_TYPE_STRAIGHT=  1,  
        TURN_TYPE_TURN_LEFT=  2,  
        TURN_TYPE_TURN_RIGHT=  3,  
        TURN_TYPE_TURN_LEFT_AROUND=  4,  
        TURN_TYPE_TURN_RIGHT_AROUND=  5,  
        TURN_TYPE_TURN_LEFT_AREA=  6,  
        TURN_TYPE_TURN_RIGHT_AREA=  7,  
        TURN_TYPE_RESERVE_1=  250,  
        TURN_TYPE_RESERVE_2=  251,  
        TURN_TYPE_RESERVE_3=  252,  
        TURN_TYPE_RESERVE_4=  253,  
        TURN_TYPE_RESERVE_5=  254,  
        TURN_TYPE_OTHERS=  255,  
    };

        
    enum TranType
    {
        TRAN_TYPE_UNDEFINED=  0,  
        TRAN_TYPE_LANE_OPENING=  1,  
        TRAN_TYPE_LANE_ENDING=  2,  
        TRAN_TYPE_LOGICAL_TRANSITION_LANE=  3,  
        TRAN_TYPE_EXIT_AND_ENTRY_LANE=  4,  
        TRAN_TYPE_EXIT_OR_ENTRY_LANE=  5,  
        TRAN_TYPE_TRAIN_TRACK=  6,  
        TRAN_TYPE_PUBLIC_TRANSPORT_STOP=  7,  
        TRAN_TYPE_WAITING_AREA=  8,  
        TRAN_TYPE_ENTRY_LANE=  9,  
        TRAN_TYPE_EXIT_LANE=  10,  
        TRAN_TYPE_NORMAL_LANE=  11,  
        TRAN_TYPE_LANE_OPENING_AND_ENDING=  12,  
        TRAN_TYPE_LANE_ENDING_AND_OPENING=  13,  
        TRAN_TYPE_WIDE_STEP=  14,  
        TRAN_TYPE_NARROW_STEP=  15,  
        TRAN_TYPE_SPLITING=  16,  
        TRAN_TYPE_MERGING=  17,  
        TRAN_TYPE_NEWBORN=  18,  
        TRAN_TYPE_BREAKUP=  19,  
        TRAN_TYPE_NOT_APPLICABLE=  200,  
        TRAN_TYPE_RESERVED_1=  250,  
        TRAN_TYPE_RESERVED_2=  251,  
        TRAN_TYPE_RESERVED_3=  252,  
        TRAN_TYPE_RESERVED_4=  253,  
        TRAN_TYPE_RESERVED_5=  254,  
        TRAN_TYPE_OTHERS=  255,  
    };

    static const ::std::map<::std::string, LaneDir>& ENUMSTR_LANEDIR() 
    { 
        static const ::std::map<::std::string, LaneDir> data{
        { "UNDEFINED", LaneDir::LANE_DIR_UNDEFINED },
        { "POSITIVE_DIRECTION", LaneDir::LANE_DIR_POSITIVE_DIRECTION },
        { "NEGATIVE_DIRECTION", LaneDir::LANE_DIR_NEGATIVE_DIRECTION },
        { "BI_DIRECTION", LaneDir::LANE_DIR_BI_DIRECTION }};
        return data;
    }

    static const ::std::map<::std::string, LaneType>& ENUMSTR_LANETYPE() 
    { 
        static const ::std::map<::std::string, LaneType> data{
        { "UNDEFINED", LaneType::LANE_TYPE_UNDEFINED },
        { "REGULAR", LaneType::LANE_TYPE_REGULAR },
        { "EXPRESS", LaneType::LANE_TYPE_EXPRESS },
        { "CARPOOL", LaneType::LANE_TYPE_CARPOOL },
        { "TRAM", LaneType::LANE_TYPE_TRAM },
        { "TRUCK_PARKING", LaneType::LANE_TYPE_TRUCK_PARKING },
        { "SLOW", LaneType::LANE_TYPE_SLOW },
        { "HARD_SHOULDER", LaneType::LANE_TYPE_HARD_SHOULDER },
        { "REGULATED_ACCESS", LaneType::LANE_TYPE_REGULATED_ACCESS },
        { "ACCELERATE", LaneType::LANE_TYPE_ACCELERATE },
        { "DECELERATE", LaneType::LANE_TYPE_DECELERATE },
        { "DEDICATED_BUS", LaneType::LANE_TYPE_DEDICATED_BUS },
        { "BICYCLE", LaneType::LANE_TYPE_BICYCLE },
        { "PARKING_LANE", LaneType::LANE_TYPE_PARKING_LANE },
        { "EMERGENCY", LaneType::LANE_TYPE_EMERGENCY },
        { "EMERGENCY_PARKING_STRIP", LaneType::LANE_TYPE_EMERGENCY_PARKING_STRIP },
        { "ENTRY", LaneType::LANE_TYPE_ENTRY },
        { "EXIT", LaneType::LANE_TYPE_EXIT },
        { "RAMP_ALL", LaneType::LANE_TYPE_RAMP_ALL },
        { "RAMP_ABOARD", LaneType::LANE_TYPE_RAMP_ABOARD },
        { "RAMP_ASHORE", LaneType::LANE_TYPE_RAMP_ASHORE },
        { "RAMP_JCT", LaneType::LANE_TYPE_RAMP_JCT },
        { "TOLL_BOOTH", LaneType::LANE_TYPE_TOLL_BOOTH },
        { "TOLL_GATE", LaneType::LANE_TYPE_TOLL_GATE },
        { "TOLL_GATE_ETC", LaneType::LANE_TYPE_TOLL_GATE_ETC },
        { "CLIMBING", LaneType::LANE_TYPE_CLIMBING },
        { "ESCAPE", LaneType::LANE_TYPE_ESCAPE },
        { "NON_DRIVE_WAY", LaneType::LANE_TYPE_NON_DRIVE_WAY },
        { "DEDICATED_CUSTOM", LaneType::LANE_TYPE_DEDICATED_CUSTOM },
        { "REVERSIBLE", LaneType::LANE_TYPE_REVERSIBLE },
        { "VARIABLE", LaneType::LANE_TYPE_VARIABLE },
        { "DRIVABLE_SHOULDER", LaneType::LANE_TYPE_DRIVABLE_SHOULDER },
        { "DIS_DRIVABLE_SHOULDER", LaneType::LANE_TYPE_DIS_DRIVABLE_SHOULDER },
        { "REGULAR_DIVERSION", LaneType::LANE_TYPE_REGULAR_DIVERSION },
        { "RESERVED_1", LaneType::LANE_TYPE_RESERVED_1 },
        { "RESERVED_2", LaneType::LANE_TYPE_RESERVED_2 },
        { "RESERVED_3", LaneType::LANE_TYPE_RESERVED_3 },
        { "RESERVED_4", LaneType::LANE_TYPE_RESERVED_4 },
        { "RESERVED_5", LaneType::LANE_TYPE_RESERVED_5 },
        { "OTHER", LaneType::LANE_TYPE_OTHER }};
        return data;
    }

    static const ::std::map<::std::string, TurnType>& ENUMSTR_TURNTYPE() 
    { 
        static const ::std::map<::std::string, TurnType> data{
        { "UNDEFINED", TurnType::TURN_TYPE_UNDEFINED },
        { "STRAIGHT", TurnType::TURN_TYPE_STRAIGHT },
        { "TURN_LEFT", TurnType::TURN_TYPE_TURN_LEFT },
        { "TURN_RIGHT", TurnType::TURN_TYPE_TURN_RIGHT },
        { "TURN_LEFT_AROUND", TurnType::TURN_TYPE_TURN_LEFT_AROUND },
        { "TURN_RIGHT_AROUND", TurnType::TURN_TYPE_TURN_RIGHT_AROUND },
        { "TURN_LEFT_AREA", TurnType::TURN_TYPE_TURN_LEFT_AREA },
        { "TURN_RIGHT_AREA", TurnType::TURN_TYPE_TURN_RIGHT_AREA },
        { "RESERVE_1", TurnType::TURN_TYPE_RESERVE_1 },
        { "RESERVE_2", TurnType::TURN_TYPE_RESERVE_2 },
        { "RESERVE_3", TurnType::TURN_TYPE_RESERVE_3 },
        { "RESERVE_4", TurnType::TURN_TYPE_RESERVE_4 },
        { "RESERVE_5", TurnType::TURN_TYPE_RESERVE_5 },
        { "OTHERS", TurnType::TURN_TYPE_OTHERS }};
        return data;
    }

    static const ::std::map<::std::string, TranType>& ENUMSTR_TRANTYPE() 
    { 
        static const ::std::map<::std::string, TranType> data{
        { "UNDEFINED", TranType::TRAN_TYPE_UNDEFINED },
        { "LANE_OPENING", TranType::TRAN_TYPE_LANE_OPENING },
        { "LANE_ENDING", TranType::TRAN_TYPE_LANE_ENDING },
        { "LOGICAL_TRANSITION_LANE", TranType::TRAN_TYPE_LOGICAL_TRANSITION_LANE },
        { "EXIT_AND_ENTRY_LANE", TranType::TRAN_TYPE_EXIT_AND_ENTRY_LANE },
        { "EXIT_OR_ENTRY_LANE", TranType::TRAN_TYPE_EXIT_OR_ENTRY_LANE },
        { "TRAIN_TRACK", TranType::TRAN_TYPE_TRAIN_TRACK },
        { "PUBLIC_TRANSPORT_STOP", TranType::TRAN_TYPE_PUBLIC_TRANSPORT_STOP },
        { "WAITING_AREA", TranType::TRAN_TYPE_WAITING_AREA },
        { "ENTRY_LANE", TranType::TRAN_TYPE_ENTRY_LANE },
        { "EXIT_LANE", TranType::TRAN_TYPE_EXIT_LANE },
        { "NORMAL_LANE", TranType::TRAN_TYPE_NORMAL_LANE },
        { "LANE_OPENING_AND_ENDING", TranType::TRAN_TYPE_LANE_OPENING_AND_ENDING },
        { "LANE_ENDING_AND_OPENING", TranType::TRAN_TYPE_LANE_ENDING_AND_OPENING },
        { "WIDE_STEP", TranType::TRAN_TYPE_WIDE_STEP },
        { "NARROW_STEP", TranType::TRAN_TYPE_NARROW_STEP },
        { "SPLITING", TranType::TRAN_TYPE_SPLITING },
        { "MERGING", TranType::TRAN_TYPE_MERGING },
        { "NEWBORN", TranType::TRAN_TYPE_NEWBORN },
        { "BREAKUP", TranType::TRAN_TYPE_BREAKUP },
        { "NOT_APPLICABLE", TranType::TRAN_TYPE_NOT_APPLICABLE },
        { "RESERVED_1", TranType::TRAN_TYPE_RESERVED_1 },
        { "RESERVED_2", TranType::TRAN_TYPE_RESERVED_2 },
        { "RESERVED_3", TranType::TRAN_TYPE_RESERVED_3 },
        { "RESERVED_4", TranType::TRAN_TYPE_RESERVED_4 },
        { "RESERVED_5", TranType::TRAN_TYPE_RESERVED_5 },
        { "OTHERS", TranType::TRAN_TYPE_OTHERS }};
        return data;
    }


private:
    ::std::uint64_t lane_id_; 
    ::std::uint64_t lane_group_id_; 
    LaneDir lane_dir_; 
    ::std::int32_t lane_seq_; 
    ::std::uint64_t left_lane_boundary_id_; 
    ::std::uint64_t right_lane_boundary_id_; 
    ::std::uint64_t intersection_id_; 
    ::std::uint64_t adas_id_; 
    LaneType lane_type_; 
    TurnType turn_type_; 
    ::std::vector<Condition> condition_; 
    TranType tran_type_; 
    bool has_geometry_; 
    ::std::uint64_t begin_intersection_id_; 
    ::std::uint64_t end_intersection_id_; 
    ::std::vector<::std::uint64_t> pre_lane_ids_; 
    ::std::vector<::std::uint64_t> succ_lane_ids_; 
    ::std::vector<::std::uint64_t> parking_space_ids_; 
    ::std::uint32_t lane_length_cm_; 
    ::std::vector<LaneWidthInfo> lane_percent_width_; 
    ::std::vector<::std::uint64_t> tile_ids_; 
    ::std::uint64_t road_id_; 
    bool is_intersection_lane_; 
    bool is_restrict_; 
    ::std::vector<SpeedLimitInfo> lane_speed_limit_; 
    ::std::vector<::std::uint64_t> opposite_lane_ids_; 
    ::std::vector<IdIntervalFloat64> associated_safe_islands_; 
    ::std::vector<IdIntervalFloat64> associated_stop_lines_; 
    ::std::vector<IdIntervalFloat64> associated_traffic_lights_; 
    ::std::vector<IdIntervalFloat64> associated_painted_markings_; 
    ::std::vector<IdIntervalFloat64> associated_pedestrian_crossings_; 
    ::std::vector<IdIntervalFloat64> associated_traffic_signs_; 
    ::std::vector<IdIntervalFloat64> associated_quasi_poles_; 
    ::std::uint64_t object_parking_lot_id_; 
    ::std::uint64_t object_parking_floor_id_; 
    Coordinate coordinate_; 
    ::std::uint32_t zone_id_; 
    ::std::uint32_t extra_zone_id_; 
    bool south_flag_; 
    GeoBox region_; 
    ::std::map<::std::uint32_t, GeoBox> extra_region_; 
    ::std::vector<GeoPoint> geometry_points_; 
    ::std::map<::std::uint32_t, GeoLine> extra_geometry_points_; 

private:
    void DecodeProto(const ::holo::map::proto::base::Lane& _proto_handler);
    ::holo::map::proto::base::Lane EncodeProto();

public:
    Lane();
    explicit Lane(const ::holo::map::proto::base::Lane& _proto_handler);
    // init all format data
    Lane(const ::std::uint64_t _lane_id,const ::std::uint64_t _lane_group_id,const LaneDir& _lane_dir,const ::std::int32_t _lane_seq,const ::std::uint64_t _left_lane_boundary_id,const ::std::uint64_t _right_lane_boundary_id,const ::std::uint64_t _intersection_id,const ::std::uint64_t _adas_id,const LaneType& _lane_type,const TurnType& _turn_type,const ::std::vector<Condition>& _condition,const TranType& _tran_type,const bool _has_geometry,const ::std::uint64_t _begin_intersection_id,const ::std::uint64_t _end_intersection_id,const ::std::vector<::std::uint64_t>& _pre_lane_ids,const ::std::vector<::std::uint64_t>& _succ_lane_ids,const ::std::vector<::std::uint64_t>& _parking_space_ids,const ::std::uint32_t _lane_length_cm,const ::std::vector<LaneWidthInfo>& _lane_percent_width,const ::std::vector<::std::uint64_t>& _tile_ids,const ::std::uint64_t _road_id,const bool _is_intersection_lane,const bool _is_restrict,const ::std::vector<SpeedLimitInfo>& _lane_speed_limit,const ::std::vector<::std::uint64_t>& _opposite_lane_ids,const ::std::vector<IdIntervalFloat64>& _associated_safe_islands,const ::std::vector<IdIntervalFloat64>& _associated_stop_lines,const ::std::vector<IdIntervalFloat64>& _associated_traffic_lights,const ::std::vector<IdIntervalFloat64>& _associated_painted_markings,const ::std::vector<IdIntervalFloat64>& _associated_pedestrian_crossings,const ::std::vector<IdIntervalFloat64>& _associated_traffic_signs,const ::std::vector<IdIntervalFloat64>& _associated_quasi_poles,const ::std::uint64_t _object_parking_lot_id,const ::std::uint64_t _object_parking_floor_id,const Coordinate& _coordinate,const ::std::uint32_t _zone_id,const ::std::uint32_t _extra_zone_id,const bool _south_flag,const GeoBox& _region,const ::std::map<::std::uint32_t, GeoBox>& _extra_region,const ::std::vector<GeoPoint>& _geometry_points,const ::std::map<::std::uint32_t, GeoLine>& _extra_geometry_points);
    ~Lane();

    bool operator==(const ::holo::map::format::Lane& _other) const;
    Lane& operator=(const ::holo::map::proto::base::Lane& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::base::Lane GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetLaneId() const
    {
        return lane_id_;
    }
    void SetLaneId(const ::std::uint64_t _lane_id)
    {
        lane_id_ = _lane_id;
    }

    ::std::uint64_t GetLaneGroupId() const
    {
        return lane_group_id_;
    }
    void SetLaneGroupId(const ::std::uint64_t _lane_group_id)
    {
        lane_group_id_ = _lane_group_id;
    }

    const LaneDir& GetLaneDir() const
    {
        return lane_dir_;
    }
    void SetLaneDir(const LaneDir& _lane_dir)
    {
        lane_dir_ = _lane_dir;
    }

    ::std::int32_t GetLaneSeq() const
    {
        return lane_seq_;
    }
    void SetLaneSeq(const ::std::int32_t _lane_seq)
    {
        lane_seq_ = _lane_seq;
    }

    ::std::uint64_t GetLeftLaneBoundaryId() const
    {
        return left_lane_boundary_id_;
    }
    void SetLeftLaneBoundaryId(const ::std::uint64_t _left_lane_boundary_id)
    {
        left_lane_boundary_id_ = _left_lane_boundary_id;
    }

    ::std::uint64_t GetRightLaneBoundaryId() const
    {
        return right_lane_boundary_id_;
    }
    void SetRightLaneBoundaryId(const ::std::uint64_t _right_lane_boundary_id)
    {
        right_lane_boundary_id_ = _right_lane_boundary_id;
    }

    ::std::uint64_t GetIntersectionId() const
    {
        return intersection_id_;
    }
    void SetIntersectionId(const ::std::uint64_t _intersection_id)
    {
        intersection_id_ = _intersection_id;
    }

    ::std::uint64_t GetAdasId() const
    {
        return adas_id_;
    }
    void SetAdasId(const ::std::uint64_t _adas_id)
    {
        adas_id_ = _adas_id;
    }

    const LaneType& GetLaneType() const
    {
        return lane_type_;
    }
    void SetLaneType(const LaneType& _lane_type)
    {
        lane_type_ = _lane_type;
    }

    const TurnType& GetTurnType() const
    {
        return turn_type_;
    }
    void SetTurnType(const TurnType& _turn_type)
    {
        turn_type_ = _turn_type;
    }

    const ::std::vector<Condition>* GetPtrCondition() const
    {
        return &condition_;
    }
    void SetCondition(const ::std::vector<Condition>& _condition)
    {
        condition_ = _condition;
    }

    const TranType& GetTranType() const
    {
        return tran_type_;
    }
    void SetTranType(const TranType& _tran_type)
    {
        tran_type_ = _tran_type;
    }

    bool GetHasGeometry() const
    {
        return has_geometry_;
    }
    void SetHasGeometry(const bool _has_geometry)
    {
        has_geometry_ = _has_geometry;
    }

    ::std::uint64_t GetBeginIntersectionId() const
    {
        return begin_intersection_id_;
    }
    void SetBeginIntersectionId(const ::std::uint64_t _begin_intersection_id)
    {
        begin_intersection_id_ = _begin_intersection_id;
    }

    ::std::uint64_t GetEndIntersectionId() const
    {
        return end_intersection_id_;
    }
    void SetEndIntersectionId(const ::std::uint64_t _end_intersection_id)
    {
        end_intersection_id_ = _end_intersection_id;
    }

    const ::std::vector<::std::uint64_t>* GetPtrPreLaneIds() const
    {
        return &pre_lane_ids_;
    }
    void SetPreLaneIds(const ::std::vector<::std::uint64_t>& _pre_lane_ids)
    {
        pre_lane_ids_ = _pre_lane_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrSuccLaneIds() const
    {
        return &succ_lane_ids_;
    }
    void SetSuccLaneIds(const ::std::vector<::std::uint64_t>& _succ_lane_ids)
    {
        succ_lane_ids_ = _succ_lane_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrParkingSpaceIds() const
    {
        return &parking_space_ids_;
    }
    void SetParkingSpaceIds(const ::std::vector<::std::uint64_t>& _parking_space_ids)
    {
        parking_space_ids_ = _parking_space_ids;
    }

    ::std::uint32_t GetLaneLengthCm() const
    {
        return lane_length_cm_;
    }
    void SetLaneLengthCm(const ::std::uint32_t _lane_length_cm)
    {
        lane_length_cm_ = _lane_length_cm;
    }

    const ::std::vector<LaneWidthInfo>* GetPtrLanePercentWidth() const
    {
        return &lane_percent_width_;
    }
    void SetLanePercentWidth(const ::std::vector<LaneWidthInfo>& _lane_percent_width)
    {
        lane_percent_width_ = _lane_percent_width;
    }

    const ::std::vector<::std::uint64_t>* GetPtrTileIds() const
    {
        return &tile_ids_;
    }
    void SetTileIds(const ::std::vector<::std::uint64_t>& _tile_ids)
    {
        tile_ids_ = _tile_ids;
    }

    ::std::uint64_t GetRoadId() const
    {
        return road_id_;
    }
    void SetRoadId(const ::std::uint64_t _road_id)
    {
        road_id_ = _road_id;
    }

    bool GetIsIntersectionLane() const
    {
        return is_intersection_lane_;
    }
    void SetIsIntersectionLane(const bool _is_intersection_lane)
    {
        is_intersection_lane_ = _is_intersection_lane;
    }

    bool GetIsRestrict() const
    {
        return is_restrict_;
    }
    void SetIsRestrict(const bool _is_restrict)
    {
        is_restrict_ = _is_restrict;
    }

    const ::std::vector<SpeedLimitInfo>* GetPtrLaneSpeedLimit() const
    {
        return &lane_speed_limit_;
    }
    void SetLaneSpeedLimit(const ::std::vector<SpeedLimitInfo>& _lane_speed_limit)
    {
        lane_speed_limit_ = _lane_speed_limit;
    }

    const ::std::vector<::std::uint64_t>* GetPtrOppositeLaneIds() const
    {
        return &opposite_lane_ids_;
    }
    void SetOppositeLaneIds(const ::std::vector<::std::uint64_t>& _opposite_lane_ids)
    {
        opposite_lane_ids_ = _opposite_lane_ids;
    }

    const ::std::vector<IdIntervalFloat64>* GetPtrAssociatedSafeIslands() const
    {
        return &associated_safe_islands_;
    }
    void SetAssociatedSafeIslands(const ::std::vector<IdIntervalFloat64>& _associated_safe_islands)
    {
        associated_safe_islands_ = _associated_safe_islands;
    }

    const ::std::vector<IdIntervalFloat64>* GetPtrAssociatedStopLines() const
    {
        return &associated_stop_lines_;
    }
    void SetAssociatedStopLines(const ::std::vector<IdIntervalFloat64>& _associated_stop_lines)
    {
        associated_stop_lines_ = _associated_stop_lines;
    }

    const ::std::vector<IdIntervalFloat64>* GetPtrAssociatedTrafficLights() const
    {
        return &associated_traffic_lights_;
    }
    void SetAssociatedTrafficLights(const ::std::vector<IdIntervalFloat64>& _associated_traffic_lights)
    {
        associated_traffic_lights_ = _associated_traffic_lights;
    }

    const ::std::vector<IdIntervalFloat64>* GetPtrAssociatedPaintedMarkings() const
    {
        return &associated_painted_markings_;
    }
    void SetAssociatedPaintedMarkings(const ::std::vector<IdIntervalFloat64>& _associated_painted_markings)
    {
        associated_painted_markings_ = _associated_painted_markings;
    }

    const ::std::vector<IdIntervalFloat64>* GetPtrAssociatedPedestrianCrossings() const
    {
        return &associated_pedestrian_crossings_;
    }
    void SetAssociatedPedestrianCrossings(const ::std::vector<IdIntervalFloat64>& _associated_pedestrian_crossings)
    {
        associated_pedestrian_crossings_ = _associated_pedestrian_crossings;
    }

    const ::std::vector<IdIntervalFloat64>* GetPtrAssociatedTrafficSigns() const
    {
        return &associated_traffic_signs_;
    }
    void SetAssociatedTrafficSigns(const ::std::vector<IdIntervalFloat64>& _associated_traffic_signs)
    {
        associated_traffic_signs_ = _associated_traffic_signs;
    }

    const ::std::vector<IdIntervalFloat64>* GetPtrAssociatedQuasiPoles() const
    {
        return &associated_quasi_poles_;
    }
    void SetAssociatedQuasiPoles(const ::std::vector<IdIntervalFloat64>& _associated_quasi_poles)
    {
        associated_quasi_poles_ = _associated_quasi_poles;
    }

    ::std::uint64_t GetObjectParkingLotId() const
    {
        return object_parking_lot_id_;
    }
    void SetObjectParkingLotId(const ::std::uint64_t _object_parking_lot_id)
    {
        object_parking_lot_id_ = _object_parking_lot_id;
    }

    ::std::uint64_t GetObjectParkingFloorId() const
    {
        return object_parking_floor_id_;
    }
    void SetObjectParkingFloorId(const ::std::uint64_t _object_parking_floor_id)
    {
        object_parking_floor_id_ = _object_parking_floor_id;
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

    const ::std::map<::std::uint32_t, GeoLine>* GetPtrExtraGeometryPoints() const
    {
        return &extra_geometry_points_;
    }
    void SetExtraGeometryPoints(const ::std::map<::std::uint32_t, GeoLine>& _extra_geometry_points)
    {
        extra_geometry_points_ = _extra_geometry_points;
    }


    void ClearCondition()
    {
        condition_.clear();
    }
    void AddConditionElement(const Condition& _value)
    {
        condition_.push_back(_value);
    }
    void UniqueAddConditionElements(const ::std::vector<Condition>& _value)
    {
        UniqueAppend(condition_, _value);
    }

    void ClearPreLaneIds()
    {
        pre_lane_ids_.clear();
    }
    void AddPreLaneIdsElement(const ::std::uint64_t& _value)
    {
        pre_lane_ids_.push_back(_value);
    }
    void UniqueAddPreLaneIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(pre_lane_ids_, _value);
    }

    void ClearSuccLaneIds()
    {
        succ_lane_ids_.clear();
    }
    void AddSuccLaneIdsElement(const ::std::uint64_t& _value)
    {
        succ_lane_ids_.push_back(_value);
    }
    void UniqueAddSuccLaneIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(succ_lane_ids_, _value);
    }

    void ClearParkingSpaceIds()
    {
        parking_space_ids_.clear();
    }
    void AddParkingSpaceIdsElement(const ::std::uint64_t& _value)
    {
        parking_space_ids_.push_back(_value);
    }
    void UniqueAddParkingSpaceIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(parking_space_ids_, _value);
    }

    void ClearLanePercentWidth()
    {
        lane_percent_width_.clear();
    }
    void AddLanePercentWidthElement(const LaneWidthInfo& _value)
    {
        lane_percent_width_.push_back(_value);
    }
    void UniqueAddLanePercentWidthElements(const ::std::vector<LaneWidthInfo>& _value)
    {
        UniqueAppend(lane_percent_width_, _value);
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

    void ClearLaneSpeedLimit()
    {
        lane_speed_limit_.clear();
    }
    void AddLaneSpeedLimitElement(const SpeedLimitInfo& _value)
    {
        lane_speed_limit_.push_back(_value);
    }
    void UniqueAddLaneSpeedLimitElements(const ::std::vector<SpeedLimitInfo>& _value)
    {
        UniqueAppend(lane_speed_limit_, _value);
    }

    void ClearOppositeLaneIds()
    {
        opposite_lane_ids_.clear();
    }
    void AddOppositeLaneIdsElement(const ::std::uint64_t& _value)
    {
        opposite_lane_ids_.push_back(_value);
    }
    void UniqueAddOppositeLaneIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(opposite_lane_ids_, _value);
    }

    void ClearAssociatedSafeIslands()
    {
        associated_safe_islands_.clear();
    }
    void AddAssociatedSafeIslandsElement(const IdIntervalFloat64& _value)
    {
        associated_safe_islands_.push_back(_value);
    }
    void UniqueAddAssociatedSafeIslandsElements(const ::std::vector<IdIntervalFloat64>& _value)
    {
        UniqueAppend(associated_safe_islands_, _value);
    }

    void ClearAssociatedStopLines()
    {
        associated_stop_lines_.clear();
    }
    void AddAssociatedStopLinesElement(const IdIntervalFloat64& _value)
    {
        associated_stop_lines_.push_back(_value);
    }
    void UniqueAddAssociatedStopLinesElements(const ::std::vector<IdIntervalFloat64>& _value)
    {
        UniqueAppend(associated_stop_lines_, _value);
    }

    void ClearAssociatedTrafficLights()
    {
        associated_traffic_lights_.clear();
    }
    void AddAssociatedTrafficLightsElement(const IdIntervalFloat64& _value)
    {
        associated_traffic_lights_.push_back(_value);
    }
    void UniqueAddAssociatedTrafficLightsElements(const ::std::vector<IdIntervalFloat64>& _value)
    {
        UniqueAppend(associated_traffic_lights_, _value);
    }

    void ClearAssociatedPaintedMarkings()
    {
        associated_painted_markings_.clear();
    }
    void AddAssociatedPaintedMarkingsElement(const IdIntervalFloat64& _value)
    {
        associated_painted_markings_.push_back(_value);
    }
    void UniqueAddAssociatedPaintedMarkingsElements(const ::std::vector<IdIntervalFloat64>& _value)
    {
        UniqueAppend(associated_painted_markings_, _value);
    }

    void ClearAssociatedPedestrianCrossings()
    {
        associated_pedestrian_crossings_.clear();
    }
    void AddAssociatedPedestrianCrossingsElement(const IdIntervalFloat64& _value)
    {
        associated_pedestrian_crossings_.push_back(_value);
    }
    void UniqueAddAssociatedPedestrianCrossingsElements(const ::std::vector<IdIntervalFloat64>& _value)
    {
        UniqueAppend(associated_pedestrian_crossings_, _value);
    }

    void ClearAssociatedTrafficSigns()
    {
        associated_traffic_signs_.clear();
    }
    void AddAssociatedTrafficSignsElement(const IdIntervalFloat64& _value)
    {
        associated_traffic_signs_.push_back(_value);
    }
    void UniqueAddAssociatedTrafficSignsElements(const ::std::vector<IdIntervalFloat64>& _value)
    {
        UniqueAppend(associated_traffic_signs_, _value);
    }

    void ClearAssociatedQuasiPoles()
    {
        associated_quasi_poles_.clear();
    }
    void AddAssociatedQuasiPolesElement(const IdIntervalFloat64& _value)
    {
        associated_quasi_poles_.push_back(_value);
    }
    void UniqueAddAssociatedQuasiPolesElements(const ::std::vector<IdIntervalFloat64>& _value)
    {
        UniqueAppend(associated_quasi_poles_, _value);
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


    const GeoBox& GetRegion() const;
    void SetRegion(const GeoBox& _region)
    {
        this->region_ = _region;
    }


    const ::std::vector<GeoPoint>* GetPtrGeometryPoints() const;
    void SetGeometryPoints(const ::std::vector<GeoPoint>& _geometry_points)
    {
        this->geometry_points_ = _geometry_points;
    }





};  // class Lane

typedef ::std::shared_ptr<Lane> PtrLane;
typedef const ::std::vector<Lane>* ConstRawPtrVecLane;
typedef ::std::vector<Lane>* RawPtrVecLane;
typedef ::std::shared_ptr<Lane const> ConstPtrLane;
typedef ::std::shared_ptr<::std::vector<Lane> const> ConstPtrVecLane;
typedef ::std::unordered_map<::std::uint64_t, PtrLane> HashmapLane;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_BASE_LANE_H_