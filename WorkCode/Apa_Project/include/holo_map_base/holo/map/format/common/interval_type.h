/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file interval_type.h
 * @brief Auto generated code for IntervalType format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_COMMON_INTERVAL_TYPE_H_
#define HOLO_MAP_FORMAT_COMMON_INTERVAL_TYPE_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/common/interval_type.pb.h>


#include <holo/map/format/base/base.h>


#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  IntervalType: public Base
{
public:

        
    enum Type
    {
        TYPE_UNDEFINED=  0,  
        TYPE_INVALID=  1,  
        TYPE_INDEX=  2,  
        TYPE_PERCENT=  3,  
        TYPE_DISTANCE=  4,  
        TYPE_AT_TAIL=  5,  
        TYPE_AT_HEAD=  6,  
    };

    static const ::std::map<::std::string, Type>& ENUMSTR_TYPE() 
    { 
        static const ::std::map<::std::string, Type> data{
        { "UNDEFINED", Type::TYPE_UNDEFINED },
        { "INVALID", Type::TYPE_INVALID },
        { "INDEX", Type::TYPE_INDEX },
        { "PERCENT", Type::TYPE_PERCENT },
        { "DISTANCE", Type::TYPE_DISTANCE },
        { "AT_TAIL", Type::TYPE_AT_TAIL },
        { "AT_HEAD", Type::TYPE_AT_HEAD }};
        return data;
    }


private:
    Type type_; 

private:
    void DecodeProto(const ::holo::map::proto::common::IntervalType& _proto_handler);
    ::holo::map::proto::common::IntervalType EncodeProto();

public:
    IntervalType();
    explicit IntervalType(const ::holo::map::proto::common::IntervalType& _proto_handler);
    // init all format data
    IntervalType(const Type& _type);
    ~IntervalType();

    bool operator==(const ::holo::map::format::IntervalType& _other) const;
    IntervalType& operator=(const ::holo::map::proto::common::IntervalType& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::common::IntervalType GetProtoHandler()
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











};  // class IntervalType

typedef ::std::shared_ptr<IntervalType> PtrIntervalType;
typedef const ::std::vector<IntervalType>* ConstRawPtrVecIntervalType;
typedef ::std::vector<IntervalType>* RawPtrVecIntervalType;
typedef ::std::shared_ptr<IntervalType const> ConstPtrIntervalType;
typedef ::std::shared_ptr<::std::vector<IntervalType> const> ConstPtrVecIntervalType;
typedef ::std::unordered_map<::std::uint64_t, PtrIntervalType> HashmapIntervalType;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_COMMON_INTERVAL_TYPE_H_