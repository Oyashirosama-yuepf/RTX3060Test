/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file speed_limit_condition.h
 * @brief Auto generated code for SpeedLimitCondition format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_HFL_SPEED_LIMIT_CONDITION_H_
#define HOLO_MAP_FORMAT_HFL_SPEED_LIMIT_CONDITION_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/hfl/speed_limit_condition.pb.h>

#include <holo/map/proto/common/interval_float64.pb.h>

#include <holo/map/proto/common/interval_type.pb.h>

#include <holo/map/proto/base/speed_limit_info.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/interval_float64.h>

#include <holo/map/format/common/interval_type.h>

#include <holo/map/format/base/speed_limit_info.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  SpeedLimitCondition: public Base
{
public:

        
    enum SpeedLimitType
    {
        SPEED_LIMIT_TYPE_UNDEFINED=  0,  
        SPEED_LIMIT_TYPE_SPEED_LIMIT_CHANGED=  1,  
        SPEED_LIMIT_TYPE_SPEED_LIMIT_ERROR=  2,  
        SPEED_LIMIT_TYPE_OTHERS=  4,  
    };

    static const ::std::map<::std::string, SpeedLimitType>& ENUMSTR_SPEEDLIMITTYPE() 
    { 
        static const ::std::map<::std::string, SpeedLimitType> data{
        { "UNDEFINED", SpeedLimitType::SPEED_LIMIT_TYPE_UNDEFINED },
        { "SPEED_LIMIT_CHANGED", SpeedLimitType::SPEED_LIMIT_TYPE_SPEED_LIMIT_CHANGED },
        { "SPEED_LIMIT_ERROR", SpeedLimitType::SPEED_LIMIT_TYPE_SPEED_LIMIT_ERROR },
        { "OTHERS", SpeedLimitType::SPEED_LIMIT_TYPE_OTHERS }};
        return data;
    }


private:
    ::std::uint64_t speed_limit_condition_id_; 
    SpeedLimitType speed_limit_type_; 
    ::std::vector<SpeedLimitInfo> speed_limit_info_; 
    IntervalType speed_limit_pos_type_; 
    ::std::vector<IntervalFloat64> exist_timestamp_; 
    ::std::uint64_t create_timestamp_; 
    ::std::uint64_t update_timestamp_; 

private:
    void DecodeProto(const ::holo::map::proto::hfl::SpeedLimitCondition& _proto_handler);
    ::holo::map::proto::hfl::SpeedLimitCondition EncodeProto();

public:
    SpeedLimitCondition();
    explicit SpeedLimitCondition(const ::holo::map::proto::hfl::SpeedLimitCondition& _proto_handler);
    // init all format data
    SpeedLimitCondition(const ::std::uint64_t _speed_limit_condition_id,const SpeedLimitType& _speed_limit_type,const ::std::vector<SpeedLimitInfo>& _speed_limit_info,const IntervalType& _speed_limit_pos_type,const ::std::vector<IntervalFloat64>& _exist_timestamp,const ::std::uint64_t _create_timestamp,const ::std::uint64_t _update_timestamp);
    ~SpeedLimitCondition();

    bool operator==(const ::holo::map::format::SpeedLimitCondition& _other) const;
    SpeedLimitCondition& operator=(const ::holo::map::proto::hfl::SpeedLimitCondition& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::hfl::SpeedLimitCondition GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetSpeedLimitConditionId() const
    {
        return speed_limit_condition_id_;
    }
    void SetSpeedLimitConditionId(const ::std::uint64_t _speed_limit_condition_id)
    {
        speed_limit_condition_id_ = _speed_limit_condition_id;
    }

    const SpeedLimitType& GetSpeedLimitType() const
    {
        return speed_limit_type_;
    }
    void SetSpeedLimitType(const SpeedLimitType& _speed_limit_type)
    {
        speed_limit_type_ = _speed_limit_type;
    }

    const ::std::vector<SpeedLimitInfo>* GetPtrSpeedLimitInfo() const
    {
        return &speed_limit_info_;
    }
    void SetSpeedLimitInfo(const ::std::vector<SpeedLimitInfo>& _speed_limit_info)
    {
        speed_limit_info_ = _speed_limit_info;
    }

    const IntervalType& GetSpeedLimitPosType() const
    {
        return speed_limit_pos_type_;
    }
    void SetSpeedLimitPosType(const IntervalType& _speed_limit_pos_type)
    {
        speed_limit_pos_type_ = _speed_limit_pos_type;
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


    void ClearSpeedLimitInfo()
    {
        speed_limit_info_.clear();
    }
    void AddSpeedLimitInfoElement(const SpeedLimitInfo& _value)
    {
        speed_limit_info_.push_back(_value);
    }
    void UniqueAddSpeedLimitInfoElements(const ::std::vector<SpeedLimitInfo>& _value)
    {
        UniqueAppend(speed_limit_info_, _value);
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









};  // class SpeedLimitCondition

typedef ::std::shared_ptr<SpeedLimitCondition> PtrSpeedLimitCondition;
typedef const ::std::vector<SpeedLimitCondition>* ConstRawPtrVecSpeedLimitCondition;
typedef ::std::vector<SpeedLimitCondition>* RawPtrVecSpeedLimitCondition;
typedef ::std::shared_ptr<SpeedLimitCondition const> ConstPtrSpeedLimitCondition;
typedef ::std::shared_ptr<::std::vector<SpeedLimitCondition> const> ConstPtrVecSpeedLimitCondition;
typedef ::std::unordered_map<::std::uint64_t, PtrSpeedLimitCondition> HashmapSpeedLimitCondition;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_HFL_SPEED_LIMIT_CONDITION_H_