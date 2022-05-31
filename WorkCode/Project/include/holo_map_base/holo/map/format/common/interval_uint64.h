/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file interval_uint64.h
 * @brief Auto generated code for IntervalUint64 format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_COMMON_INTERVAL_UINT64_H_
#define HOLO_MAP_FORMAT_COMMON_INTERVAL_UINT64_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/common/interval_uint64.pb.h>


#include <holo/map/format/base/base.h>


#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  IntervalUint64: public Base
{
public:




private:
    ::std::uint64_t first_value_; 
    ::std::uint64_t second_value_; 

private:
    void DecodeProto(const ::holo::map::proto::common::IntervalUint64& _proto_handler);
    ::holo::map::proto::common::IntervalUint64 EncodeProto();

public:
    IntervalUint64();
    explicit IntervalUint64(const ::holo::map::proto::common::IntervalUint64& _proto_handler);
    // init all format data
    IntervalUint64(const ::std::uint64_t _first_value,const ::std::uint64_t _second_value);
    ~IntervalUint64();

    bool operator==(const ::holo::map::format::IntervalUint64& _other) const;
    IntervalUint64& operator=(const ::holo::map::proto::common::IntervalUint64& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::common::IntervalUint64 GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetFirstValue() const
    {
        return first_value_;
    }
    void SetFirstValue(const ::std::uint64_t _first_value)
    {
        first_value_ = _first_value;
    }

    ::std::uint64_t GetSecondValue() const
    {
        return second_value_;
    }
    void SetSecondValue(const ::std::uint64_t _second_value)
    {
        second_value_ = _second_value;
    }











};  // class IntervalUint64

typedef ::std::shared_ptr<IntervalUint64> PtrIntervalUint64;
typedef const ::std::vector<IntervalUint64>* ConstRawPtrVecIntervalUint64;
typedef ::std::vector<IntervalUint64>* RawPtrVecIntervalUint64;
typedef ::std::shared_ptr<IntervalUint64 const> ConstPtrIntervalUint64;
typedef ::std::shared_ptr<::std::vector<IntervalUint64> const> ConstPtrVecIntervalUint64;
typedef ::std::unordered_map<::std::uint64_t, PtrIntervalUint64> HashmapIntervalUint64;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_COMMON_INTERVAL_UINT64_H_