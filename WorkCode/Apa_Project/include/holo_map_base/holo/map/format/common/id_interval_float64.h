/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file id_interval_float64.h
 * @brief Auto generated code for IdIntervalFloat64 format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_COMMON_ID_INTERVAL_FLOAT64_H_
#define HOLO_MAP_FORMAT_COMMON_ID_INTERVAL_FLOAT64_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/common/id_interval_float64.pb.h>

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

class  IdIntervalFloat64: public Base
{
public:




private:
    ::std::uint64_t id_; 
    IntervalType type_; 
    IntervalFloat64 interval_; 

private:
    void DecodeProto(const ::holo::map::proto::common::IdIntervalFloat64& _proto_handler);
    ::holo::map::proto::common::IdIntervalFloat64 EncodeProto();

public:
    IdIntervalFloat64();
    explicit IdIntervalFloat64(const ::holo::map::proto::common::IdIntervalFloat64& _proto_handler);
    // init all format data
    IdIntervalFloat64(const ::std::uint64_t _id,const IntervalType& _type,const IntervalFloat64& _interval);
    ~IdIntervalFloat64();

    bool operator==(const ::holo::map::format::IdIntervalFloat64& _other) const;
    IdIntervalFloat64& operator=(const ::holo::map::proto::common::IdIntervalFloat64& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::common::IdIntervalFloat64 GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetId() const
    {
        return id_;
    }
    void SetId(const ::std::uint64_t _id)
    {
        id_ = _id;
    }

    const IntervalType& GetType() const
    {
        return type_;
    }
    void SetType(const IntervalType& _type)
    {
        type_ = _type;
    }

    const IntervalFloat64& GetInterval() const
    {
        return interval_;
    }
    void SetInterval(const IntervalFloat64& _interval)
    {
        interval_ = _interval;
    }











};  // class IdIntervalFloat64

typedef ::std::shared_ptr<IdIntervalFloat64> PtrIdIntervalFloat64;
typedef const ::std::vector<IdIntervalFloat64>* ConstRawPtrVecIdIntervalFloat64;
typedef ::std::vector<IdIntervalFloat64>* RawPtrVecIdIntervalFloat64;
typedef ::std::shared_ptr<IdIntervalFloat64 const> ConstPtrIdIntervalFloat64;
typedef ::std::shared_ptr<::std::vector<IdIntervalFloat64> const> ConstPtrVecIdIntervalFloat64;
typedef ::std::unordered_map<::std::uint64_t, PtrIdIntervalFloat64> HashmapIdIntervalFloat64;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_COMMON_ID_INTERVAL_FLOAT64_H_