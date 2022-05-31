/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file interval_float64.h
 * @brief Auto generated code for IntervalFloat64 format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_COMMON_INTERVAL_FLOAT64_H_
#define HOLO_MAP_FORMAT_COMMON_INTERVAL_FLOAT64_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/common/interval_float64.pb.h>


#include <holo/map/format/base/base.h>


#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  IntervalFloat64: public Base
{
public:




private:
    float first_value_; 
    float second_value_; 

private:
    void DecodeProto(const ::holo::map::proto::common::IntervalFloat64& _proto_handler);
    ::holo::map::proto::common::IntervalFloat64 EncodeProto();

public:
    IntervalFloat64();
    explicit IntervalFloat64(const ::holo::map::proto::common::IntervalFloat64& _proto_handler);
    // init all format data
    IntervalFloat64(const float _first_value,const float _second_value);
    ~IntervalFloat64();

    bool operator==(const ::holo::map::format::IntervalFloat64& _other) const;
    IntervalFloat64& operator=(const ::holo::map::proto::common::IntervalFloat64& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::common::IntervalFloat64 GetProtoHandler()
    {
        return EncodeProto();
    }

    


    float GetFirstValue() const
    {
        return first_value_;
    }
    void SetFirstValue(const float _first_value)
    {
        first_value_ = _first_value;
    }

    float GetSecondValue() const
    {
        return second_value_;
    }
    void SetSecondValue(const float _second_value)
    {
        second_value_ = _second_value;
    }











};  // class IntervalFloat64

typedef ::std::shared_ptr<IntervalFloat64> PtrIntervalFloat64;
typedef const ::std::vector<IntervalFloat64>* ConstRawPtrVecIntervalFloat64;
typedef ::std::vector<IntervalFloat64>* RawPtrVecIntervalFloat64;
typedef ::std::shared_ptr<IntervalFloat64 const> ConstPtrIntervalFloat64;
typedef ::std::shared_ptr<::std::vector<IntervalFloat64> const> ConstPtrVecIntervalFloat64;
typedef ::std::unordered_map<::std::uint64_t, PtrIntervalFloat64> HashmapIntervalFloat64;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_COMMON_INTERVAL_FLOAT64_H_