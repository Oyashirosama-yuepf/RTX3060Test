/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file condition.h
 * @brief Auto generated code for Condition format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_COMMON_CONDITION_H_
#define HOLO_MAP_FORMAT_COMMON_CONDITION_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/common/condition.pb.h>

#include <holo/map/proto/common/interval_float64.pb.h>

#include <holo/map/proto/common/date_time_cycle.pb.h>

#include <holo/map/proto/common/interval_type.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/interval_float64.h>

#include <holo/map/format/common/date_time_cycle.h>

#include <holo/map/format/common/interval_type.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  Condition: public Base
{
public:

        
    enum Type
    {
        TYPE_UNKNOWN=  0,  
        TYPE_DEDICATED_BUS=  1,  
        TYPE_DEDICATED_TURN_LEFT=  2,  
        TYPE_DEDICATED_TURN_RIGHT=  3,  
        TYPE_LOAD=  4,  
    };

    static const ::std::map<::std::string, Type>& ENUMSTR_TYPE() 
    { 
        static const ::std::map<::std::string, Type> data{
        { "UNKNOWN", Type::TYPE_UNKNOWN },
        { "DEDICATED_BUS", Type::TYPE_DEDICATED_BUS },
        { "DEDICATED_TURN_LEFT", Type::TYPE_DEDICATED_TURN_LEFT },
        { "DEDICATED_TURN_RIGHT", Type::TYPE_DEDICATED_TURN_RIGHT },
        { "LOAD", Type::TYPE_LOAD }};
        return data;
    }


private:
    Type type_; 
    DateTimeCycle con_time_; 
    IntervalType offset_type_; 
    IntervalFloat64 offset_; 

private:
    void DecodeProto(const ::holo::map::proto::common::Condition& _proto_handler);
    ::holo::map::proto::common::Condition EncodeProto();

public:
    Condition();
    explicit Condition(const ::holo::map::proto::common::Condition& _proto_handler);
    // init all format data
    Condition(const Type& _type,const DateTimeCycle& _con_time,const IntervalType& _offset_type,const IntervalFloat64& _offset);
    ~Condition();

    bool operator==(const ::holo::map::format::Condition& _other) const;
    Condition& operator=(const ::holo::map::proto::common::Condition& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::common::Condition GetProtoHandler()
    {
        return EncodeProto();
    }

    


    const Type& GetType() const
    {
        return type_;
    }
    void SetType(const Type& _type)
    {
        type_ = _type;
    }

    const DateTimeCycle& GetConTime() const
    {
        return con_time_;
    }
    void SetConTime(const DateTimeCycle& _con_time)
    {
        con_time_ = _con_time;
    }

    const IntervalType& GetOffsetType() const
    {
        return offset_type_;
    }
    void SetOffsetType(const IntervalType& _offset_type)
    {
        offset_type_ = _offset_type;
    }

    const IntervalFloat64& GetOffset() const
    {
        return offset_;
    }
    void SetOffset(const IntervalFloat64& _offset)
    {
        offset_ = _offset;
    }











};  // class Condition

typedef ::std::shared_ptr<Condition> PtrCondition;
typedef const ::std::vector<Condition>* ConstRawPtrVecCondition;
typedef ::std::vector<Condition>* RawPtrVecCondition;
typedef ::std::shared_ptr<Condition const> ConstPtrCondition;
typedef ::std::shared_ptr<::std::vector<Condition> const> ConstPtrVecCondition;
typedef ::std::unordered_map<::std::uint64_t, PtrCondition> HashmapCondition;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_COMMON_CONDITION_H_