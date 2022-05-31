/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file date_time_cycle.h
 * @brief Auto generated code for DateTimeCycle format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_COMMON_DATE_TIME_CYCLE_H_
#define HOLO_MAP_FORMAT_COMMON_DATE_TIME_CYCLE_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/common/date_time_cycle.pb.h>

#include <holo/map/proto/common/interval_uint64.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/interval_uint64.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  DateTimeCycle: public Base
{
public:

        
    enum CycleType
    {
        CYCLE_TYPE_UNDEFINED=  0,  
        CYCLE_TYPE_YEAR=  1,  
        CYCLE_TYPE_MONTH=  2,  
        CYCLE_TYPE_WEEK=  3,  
        CYCLE_TYPE_DAY=  4,  
    };

        
    enum WorkingTimeType
    {
        WORKING_TIME_TYPE_UNDEFINED=  0,  
        WORKING_TIME_TYPE_YEAR=  1,  
        WORKING_TIME_TYPE_MONTH=  2,  
        WORKING_TIME_TYPE_WEEK=  3,  
        WORKING_TIME_TYPE_DAY=  4,  
    };

        
    enum UnworkingTimeType
    {
        UNWORKING_TIME_TYPE_UNDEFINED=  0,  
        UNWORKING_TIME_TYPE_YEAR=  1,  
        UNWORKING_TIME_TYPE_MONTH=  2,  
        UNWORKING_TIME_TYPE_WEEK=  3,  
        UNWORKING_TIME_TYPE_DAY=  4,  
    };

        
    enum ValidTimeType
    {
        VALID_TIME_TYPE_UNDEFINED=  0,  
        VALID_TIME_TYPE_YEAR=  1,  
        VALID_TIME_TYPE_MONTH=  2,  
        VALID_TIME_TYPE_WEEK=  3,  
        VALID_TIME_TYPE_DAY=  4,  
    };

    static const ::std::map<::std::string, CycleType>& ENUMSTR_CYCLETYPE() 
    { 
        static const ::std::map<::std::string, CycleType> data{
        { "UNDEFINED", CycleType::CYCLE_TYPE_UNDEFINED },
        { "YEAR", CycleType::CYCLE_TYPE_YEAR },
        { "MONTH", CycleType::CYCLE_TYPE_MONTH },
        { "WEEK", CycleType::CYCLE_TYPE_WEEK },
        { "DAY", CycleType::CYCLE_TYPE_DAY }};
        return data;
    }

    static const ::std::map<::std::string, WorkingTimeType>& ENUMSTR_WORKINGTIMETYPE() 
    { 
        static const ::std::map<::std::string, WorkingTimeType> data{
        { "UNDEFINED", WorkingTimeType::WORKING_TIME_TYPE_UNDEFINED },
        { "YEAR", WorkingTimeType::WORKING_TIME_TYPE_YEAR },
        { "MONTH", WorkingTimeType::WORKING_TIME_TYPE_MONTH },
        { "WEEK", WorkingTimeType::WORKING_TIME_TYPE_WEEK },
        { "DAY", WorkingTimeType::WORKING_TIME_TYPE_DAY }};
        return data;
    }

    static const ::std::map<::std::string, UnworkingTimeType>& ENUMSTR_UNWORKINGTIMETYPE() 
    { 
        static const ::std::map<::std::string, UnworkingTimeType> data{
        { "UNDEFINED", UnworkingTimeType::UNWORKING_TIME_TYPE_UNDEFINED },
        { "YEAR", UnworkingTimeType::UNWORKING_TIME_TYPE_YEAR },
        { "MONTH", UnworkingTimeType::UNWORKING_TIME_TYPE_MONTH },
        { "WEEK", UnworkingTimeType::UNWORKING_TIME_TYPE_WEEK },
        { "DAY", UnworkingTimeType::UNWORKING_TIME_TYPE_DAY }};
        return data;
    }

    static const ::std::map<::std::string, ValidTimeType>& ENUMSTR_VALIDTIMETYPE() 
    { 
        static const ::std::map<::std::string, ValidTimeType> data{
        { "UNDEFINED", ValidTimeType::VALID_TIME_TYPE_UNDEFINED },
        { "YEAR", ValidTimeType::VALID_TIME_TYPE_YEAR },
        { "MONTH", ValidTimeType::VALID_TIME_TYPE_MONTH },
        { "WEEK", ValidTimeType::VALID_TIME_TYPE_WEEK },
        { "DAY", ValidTimeType::VALID_TIME_TYPE_DAY }};
        return data;
    }


private:
    CycleType cycle_type_; 
    ::std::vector<IntervalUint64> working_interval_; 
    WorkingTimeType working_time_type_; 
    ::std::vector<IntervalUint64> unworking_interval_; 
    UnworkingTimeType unworking_time_type_; 
    ::std::vector<IntervalUint64> valid_interval_; 
    ValidTimeType valid_time_type_; 

private:
    void DecodeProto(const ::holo::map::proto::common::DateTimeCycle& _proto_handler);
    ::holo::map::proto::common::DateTimeCycle EncodeProto();

public:
    DateTimeCycle();
    explicit DateTimeCycle(const ::holo::map::proto::common::DateTimeCycle& _proto_handler);
    // init all format data
    DateTimeCycle(const CycleType& _cycle_type,const ::std::vector<IntervalUint64>& _working_interval,const WorkingTimeType& _working_time_type,const ::std::vector<IntervalUint64>& _unworking_interval,const UnworkingTimeType& _unworking_time_type,const ::std::vector<IntervalUint64>& _valid_interval,const ValidTimeType& _valid_time_type);
    ~DateTimeCycle();

    bool operator==(const ::holo::map::format::DateTimeCycle& _other) const;
    DateTimeCycle& operator=(const ::holo::map::proto::common::DateTimeCycle& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::common::DateTimeCycle GetProtoHandler()
    {
        return EncodeProto();
    }

    


    const CycleType& GetCycleType() const
    {
        return cycle_type_;
    }
    void SetCycleType(const CycleType& _cycle_type)
    {
        cycle_type_ = _cycle_type;
    }

    const ::std::vector<IntervalUint64>* GetPtrWorkingInterval() const
    {
        return &working_interval_;
    }
    void SetWorkingInterval(const ::std::vector<IntervalUint64>& _working_interval)
    {
        working_interval_ = _working_interval;
    }

    const WorkingTimeType& GetWorkingTimeType() const
    {
        return working_time_type_;
    }
    void SetWorkingTimeType(const WorkingTimeType& _working_time_type)
    {
        working_time_type_ = _working_time_type;
    }

    const ::std::vector<IntervalUint64>* GetPtrUnworkingInterval() const
    {
        return &unworking_interval_;
    }
    void SetUnworkingInterval(const ::std::vector<IntervalUint64>& _unworking_interval)
    {
        unworking_interval_ = _unworking_interval;
    }

    const UnworkingTimeType& GetUnworkingTimeType() const
    {
        return unworking_time_type_;
    }
    void SetUnworkingTimeType(const UnworkingTimeType& _unworking_time_type)
    {
        unworking_time_type_ = _unworking_time_type;
    }

    const ::std::vector<IntervalUint64>* GetPtrValidInterval() const
    {
        return &valid_interval_;
    }
    void SetValidInterval(const ::std::vector<IntervalUint64>& _valid_interval)
    {
        valid_interval_ = _valid_interval;
    }

    const ValidTimeType& GetValidTimeType() const
    {
        return valid_time_type_;
    }
    void SetValidTimeType(const ValidTimeType& _valid_time_type)
    {
        valid_time_type_ = _valid_time_type;
    }


    void ClearWorkingInterval()
    {
        working_interval_.clear();
    }
    void AddWorkingIntervalElement(const IntervalUint64& _value)
    {
        working_interval_.push_back(_value);
    }
    void UniqueAddWorkingIntervalElements(const ::std::vector<IntervalUint64>& _value)
    {
        UniqueAppend(working_interval_, _value);
    }

    void ClearUnworkingInterval()
    {
        unworking_interval_.clear();
    }
    void AddUnworkingIntervalElement(const IntervalUint64& _value)
    {
        unworking_interval_.push_back(_value);
    }
    void UniqueAddUnworkingIntervalElements(const ::std::vector<IntervalUint64>& _value)
    {
        UniqueAppend(unworking_interval_, _value);
    }

    void ClearValidInterval()
    {
        valid_interval_.clear();
    }
    void AddValidIntervalElement(const IntervalUint64& _value)
    {
        valid_interval_.push_back(_value);
    }
    void UniqueAddValidIntervalElements(const ::std::vector<IntervalUint64>& _value)
    {
        UniqueAppend(valid_interval_, _value);
    }









};  // class DateTimeCycle

typedef ::std::shared_ptr<DateTimeCycle> PtrDateTimeCycle;
typedef const ::std::vector<DateTimeCycle>* ConstRawPtrVecDateTimeCycle;
typedef ::std::vector<DateTimeCycle>* RawPtrVecDateTimeCycle;
typedef ::std::shared_ptr<DateTimeCycle const> ConstPtrDateTimeCycle;
typedef ::std::shared_ptr<::std::vector<DateTimeCycle> const> ConstPtrVecDateTimeCycle;
typedef ::std::unordered_map<::std::uint64_t, PtrDateTimeCycle> HashmapDateTimeCycle;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_COMMON_DATE_TIME_CYCLE_H_