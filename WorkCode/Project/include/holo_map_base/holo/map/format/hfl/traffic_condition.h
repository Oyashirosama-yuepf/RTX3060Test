/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file traffic_condition.h
 * @brief Auto generated code for TrafficCondition format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_HFL_TRAFFIC_CONDITION_H_
#define HOLO_MAP_FORMAT_HFL_TRAFFIC_CONDITION_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/hfl/traffic_condition.pb.h>

#include <holo/map/proto/common/interval_float64.pb.h>

#include <holo/map/proto/common/interval_type.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/interval_float64.h>

#include <holo/map/format/common/interval_type.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  TrafficCondition: public Base
{
public:

        
    enum TrafficType
    {
        TRAFFIC_TYPE_UNDEFINED=  0,  
        TRAFFIC_TYPE_TRAFFIC_ACCIDENT=  1,  
        TRAFFIC_TYPE_TRAFFIC_JAM=  2,  
        TRAFFIC_TYPE_TRAFFIC_RULES=  3,  
        TRAFFIC_TYPE_OTHERS=  4,  
    };

    static const ::std::map<::std::string, TrafficType>& ENUMSTR_TRAFFICTYPE() 
    { 
        static const ::std::map<::std::string, TrafficType> data{
        { "UNDEFINED", TrafficType::TRAFFIC_TYPE_UNDEFINED },
        { "TRAFFIC_ACCIDENT", TrafficType::TRAFFIC_TYPE_TRAFFIC_ACCIDENT },
        { "TRAFFIC_JAM", TrafficType::TRAFFIC_TYPE_TRAFFIC_JAM },
        { "TRAFFIC_RULES", TrafficType::TRAFFIC_TYPE_TRAFFIC_RULES },
        { "OTHERS", TrafficType::TRAFFIC_TYPE_OTHERS }};
        return data;
    }


private:
    ::std::uint64_t traffic_condition_id_; 
    TrafficType traffic_type_; 
    ::std::vector<IntervalFloat64> traffic_pos_; 
    IntervalType traffic_pos_type_; 
    ::std::uint32_t width_cm_; 
    ::std::vector<IntervalFloat64> exist_timestamp_; 
    ::std::uint64_t create_timestamp_; 
    ::std::uint64_t update_timestamp_; 

private:
    void DecodeProto(const ::holo::map::proto::hfl::TrafficCondition& _proto_handler);
    ::holo::map::proto::hfl::TrafficCondition EncodeProto();

public:
    TrafficCondition();
    explicit TrafficCondition(const ::holo::map::proto::hfl::TrafficCondition& _proto_handler);
    // init all format data
    TrafficCondition(const ::std::uint64_t _traffic_condition_id,const TrafficType& _traffic_type,const ::std::vector<IntervalFloat64>& _traffic_pos,const IntervalType& _traffic_pos_type,const ::std::uint32_t _width_cm,const ::std::vector<IntervalFloat64>& _exist_timestamp,const ::std::uint64_t _create_timestamp,const ::std::uint64_t _update_timestamp);
    ~TrafficCondition();

    bool operator==(const ::holo::map::format::TrafficCondition& _other) const;
    TrafficCondition& operator=(const ::holo::map::proto::hfl::TrafficCondition& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::hfl::TrafficCondition GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetTrafficConditionId() const
    {
        return traffic_condition_id_;
    }
    void SetTrafficConditionId(const ::std::uint64_t _traffic_condition_id)
    {
        traffic_condition_id_ = _traffic_condition_id;
    }

    const TrafficType& GetTrafficType() const
    {
        return traffic_type_;
    }
    void SetTrafficType(const TrafficType& _traffic_type)
    {
        traffic_type_ = _traffic_type;
    }

    const ::std::vector<IntervalFloat64>* GetPtrTrafficPos() const
    {
        return &traffic_pos_;
    }
    void SetTrafficPos(const ::std::vector<IntervalFloat64>& _traffic_pos)
    {
        traffic_pos_ = _traffic_pos;
    }

    const IntervalType& GetTrafficPosType() const
    {
        return traffic_pos_type_;
    }
    void SetTrafficPosType(const IntervalType& _traffic_pos_type)
    {
        traffic_pos_type_ = _traffic_pos_type;
    }

    ::std::uint32_t GetWidthCm() const
    {
        return width_cm_;
    }
    void SetWidthCm(const ::std::uint32_t _width_cm)
    {
        width_cm_ = _width_cm;
    }

    const ::std::vector<IntervalFloat64>* GetPtrExistTimestamp() const
    {
        return &exist_timestamp_;
    }
    void SetExistTimestamp(const ::std::vector<IntervalFloat64>& _exist_timestamp)
    {
        exist_timestamp_ = _exist_timestamp;
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


    void ClearTrafficPos()
    {
        traffic_pos_.clear();
    }
    void AddTrafficPosElement(const IntervalFloat64& _value)
    {
        traffic_pos_.push_back(_value);
    }
    void UniqueAddTrafficPosElements(const ::std::vector<IntervalFloat64>& _value)
    {
        UniqueAppend(traffic_pos_, _value);
    }

    void ClearExistTimestamp()
    {
        exist_timestamp_.clear();
    }
    void AddExistTimestampElement(const IntervalFloat64& _value)
    {
        exist_timestamp_.push_back(_value);
    }
    void UniqueAddExistTimestampElements(const ::std::vector<IntervalFloat64>& _value)
    {
        UniqueAppend(exist_timestamp_, _value);
    }









};  // class TrafficCondition

typedef ::std::shared_ptr<TrafficCondition> PtrTrafficCondition;
typedef const ::std::vector<TrafficCondition>* ConstRawPtrVecTrafficCondition;
typedef ::std::vector<TrafficCondition>* RawPtrVecTrafficCondition;
typedef ::std::shared_ptr<TrafficCondition const> ConstPtrTrafficCondition;
typedef ::std::shared_ptr<::std::vector<TrafficCondition> const> ConstPtrVecTrafficCondition;
typedef ::std::unordered_map<::std::uint64_t, PtrTrafficCondition> HashmapTrafficCondition;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_HFL_TRAFFIC_CONDITION_H_