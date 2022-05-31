/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file map_condition.h
 * @brief Auto generated code for MapCondition format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_HFL_MAP_CONDITION_H_
#define HOLO_MAP_FORMAT_HFL_MAP_CONDITION_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/hfl/map_condition.pb.h>

#include <holo/map/proto/common/id_interval_float64.pb.h>

#include <holo/map/proto/hfl/map_reason.pb.h>

#include <holo/map/proto/hfl/speed_limit_condition.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/id_interval_float64.h>

#include <holo/map/format/hfl/map_reason.h>

#include <holo/map/format/hfl/speed_limit_condition.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  MapCondition: public Base
{
public:




private:
    ::std::uint64_t map_condition_id_; 
    bool is_map_expire_; 
    ::std::uint64_t lastest_update_timestamp_; 
    ::std::uint64_t estimated_invalid_timestamp_; 
    ::std::uint64_t create_timestamp_; 
    ::std::uint64_t update_timestamp_; 
    ::std::vector<SpeedLimitCondition> speed_limit_info_; 
    ::std::uint64_t associated_intersection_id_; 
    MapReason associated_intersection_id_reason_; 
    ::std::vector<IdIntervalFloat64> associated_traffic_lights_; 
    ::std::vector<MapReason> associated_traffic_lights_reasons_; 

private:
    void DecodeProto(const ::holo::map::proto::hfl::MapCondition& _proto_handler);
    ::holo::map::proto::hfl::MapCondition EncodeProto();

public:
    MapCondition();
    explicit MapCondition(const ::holo::map::proto::hfl::MapCondition& _proto_handler);
    // init all format data
    MapCondition(const ::std::uint64_t _map_condition_id,const bool _is_map_expire,const ::std::uint64_t _lastest_update_timestamp,const ::std::uint64_t _estimated_invalid_timestamp,const ::std::uint64_t _create_timestamp,const ::std::uint64_t _update_timestamp,const ::std::vector<SpeedLimitCondition>& _speed_limit_info,const ::std::uint64_t _associated_intersection_id,const MapReason& _associated_intersection_id_reason,const ::std::vector<IdIntervalFloat64>& _associated_traffic_lights,const ::std::vector<MapReason>& _associated_traffic_lights_reasons);
    ~MapCondition();

    bool operator==(const ::holo::map::format::MapCondition& _other) const;
    MapCondition& operator=(const ::holo::map::proto::hfl::MapCondition& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::hfl::MapCondition GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetMapConditionId() const
    {
        return map_condition_id_;
    }
    void SetMapConditionId(const ::std::uint64_t _map_condition_id)
    {
        map_condition_id_ = _map_condition_id;
    }

    bool GetIsMapExpire() const
    {
        return is_map_expire_;
    }
    void SetIsMapExpire(const bool _is_map_expire)
    {
        is_map_expire_ = _is_map_expire;
    }

    ::std::uint64_t GetLastestUpdateTimestamp() const
    {
        return lastest_update_timestamp_;
    }
    void SetLastestUpdateTimestamp(const ::std::uint64_t _lastest_update_timestamp)
    {
        lastest_update_timestamp_ = _lastest_update_timestamp;
    }

    ::std::uint64_t GetEstimatedInvalidTimestamp() const
    {
        return estimated_invalid_timestamp_;
    }
    void SetEstimatedInvalidTimestamp(const ::std::uint64_t _estimated_invalid_timestamp)
    {
        estimated_invalid_timestamp_ = _estimated_invalid_timestamp;
    }

    ::std::uint64_t GetCreateTimestamp() const
    {
        return create_timestamp_;
    }
    void SetCreateTimestamp(const ::std::uint64_t _create_timestamp)
    {
        create_timestamp_ = _create_timestamp;
    }

    ::std::uint64_t GetUpdateTimestamp() const
    {
        return update_timestamp_;
    }
    void SetUpdateTimestamp(const ::std::uint64_t _update_timestamp)
    {
        update_timestamp_ = _update_timestamp;
    }

    const ::std::vector<SpeedLimitCondition>* GetPtrSpeedLimitInfo() const
    {
        return &speed_limit_info_;
    }
    void SetSpeedLimitInfo(const ::std::vector<SpeedLimitCondition>& _speed_limit_info)
    {
        speed_limit_info_ = _speed_limit_info;
    }

    ::std::uint64_t GetAssociatedIntersectionId() const
    {
        return associated_intersection_id_;
    }
    void SetAssociatedIntersectionId(const ::std::uint64_t _associated_intersection_id)
    {
        associated_intersection_id_ = _associated_intersection_id;
    }

    const MapReason& GetAssociatedIntersectionIdReason() const
    {
        return associated_intersection_id_reason_;
    }
    void SetAssociatedIntersectionIdReason(const MapReason& _associated_intersection_id_reason)
    {
        associated_intersection_id_reason_ = _associated_intersection_id_reason;
    }

    const ::std::vector<IdIntervalFloat64>* GetPtrAssociatedTrafficLights() const
    {
        return &associated_traffic_lights_;
    }
    void SetAssociatedTrafficLights(const ::std::vector<IdIntervalFloat64>& _associated_traffic_lights)
    {
        associated_traffic_lights_ = _associated_traffic_lights;
    }

    const ::std::vector<MapReason>* GetPtrAssociatedTrafficLightsReasons() const
    {
        return &associated_traffic_lights_reasons_;
    }
    void SetAssociatedTrafficLightsReasons(const ::std::vector<MapReason>& _associated_traffic_lights_reasons)
    {
        associated_traffic_lights_reasons_ = _associated_traffic_lights_reasons;
    }


    void ClearSpeedLimitInfo()
    {
        speed_limit_info_.clear();
    }
    void AddSpeedLimitInfoElement(const SpeedLimitCondition& _value)
    {
        speed_limit_info_.push_back(_value);
    }
    void UniqueAddSpeedLimitInfoElements(const ::std::vector<SpeedLimitCondition>& _value)
    {
        UniqueAppend(speed_limit_info_, _value);
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

    void ClearAssociatedTrafficLightsReasons()
    {
        associated_traffic_lights_reasons_.clear();
    }
    void AddAssociatedTrafficLightsReasonsElement(const MapReason& _value)
    {
        associated_traffic_lights_reasons_.push_back(_value);
    }
    void UniqueAddAssociatedTrafficLightsReasonsElements(const ::std::vector<MapReason>& _value)
    {
        UniqueAppend(associated_traffic_lights_reasons_, _value);
    }









};  // class MapCondition

typedef ::std::shared_ptr<MapCondition> PtrMapCondition;
typedef const ::std::vector<MapCondition>* ConstRawPtrVecMapCondition;
typedef ::std::vector<MapCondition>* RawPtrVecMapCondition;
typedef ::std::shared_ptr<MapCondition const> ConstPtrMapCondition;
typedef ::std::shared_ptr<::std::vector<MapCondition> const> ConstPtrVecMapCondition;
typedef ::std::unordered_map<::std::uint64_t, PtrMapCondition> HashmapMapCondition;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_HFL_MAP_CONDITION_H_