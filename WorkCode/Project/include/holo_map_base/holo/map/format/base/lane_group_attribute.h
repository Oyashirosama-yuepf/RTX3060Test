/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_group_attribute.h
 * @brief Auto generated code for LaneGroupAttribute format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_BASE_LANE_GROUP_ATTRIBUTE_H_
#define HOLO_MAP_FORMAT_BASE_LANE_GROUP_ATTRIBUTE_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/base/lane_group_attribute.pb.h>

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

class  LaneGroupAttribute: public Base
{
public:

        
    enum Type
    {
        TYPE_UNKNOWN=  0,  
        TYPE_TUNNEL=  1,  
        TYPE_BRIDGE=  2,  
        TYPE_VIADUCT=  3,  
        TYPE_TOLL_BOOTH=  4,  
        TYPE_TOLL_ENTRY=  5,  
        TYPE_TOLL_EXIT=  6,  
        TYPE_BREAK_UP=  7,  
        TYPE_RESERVED_1=  250,  
        TYPE_RESERVED_2=  251,  
        TYPE_RESERVED_3=  252,  
        TYPE_RESERVED_4=  253,  
        TYPE_RESERVED_5=  254,  
        TYPE_OTHERS=  255,  
    };

    static const ::std::map<::std::string, Type>& ENUMSTR_TYPE() 
    { 
        static const ::std::map<::std::string, Type> data{
        { "UNKNOWN", Type::TYPE_UNKNOWN },
        { "TUNNEL", Type::TYPE_TUNNEL },
        { "BRIDGE", Type::TYPE_BRIDGE },
        { "VIADUCT", Type::TYPE_VIADUCT },
        { "TOLL_BOOTH", Type::TYPE_TOLL_BOOTH },
        { "TOLL_ENTRY", Type::TYPE_TOLL_ENTRY },
        { "TOLL_EXIT", Type::TYPE_TOLL_EXIT },
        { "BREAK_UP", Type::TYPE_BREAK_UP },
        { "RESERVED_1", Type::TYPE_RESERVED_1 },
        { "RESERVED_2", Type::TYPE_RESERVED_2 },
        { "RESERVED_3", Type::TYPE_RESERVED_3 },
        { "RESERVED_4", Type::TYPE_RESERVED_4 },
        { "RESERVED_5", Type::TYPE_RESERVED_5 },
        { "OTHERS", Type::TYPE_OTHERS }};
        return data;
    }


private:
    Type type_; 
    IntervalType offset_type_; 
    IntervalFloat64 offset_; 

private:
    void DecodeProto(const ::holo::map::proto::base::LaneGroupAttribute& _proto_handler);
    ::holo::map::proto::base::LaneGroupAttribute EncodeProto();

public:
    LaneGroupAttribute();
    explicit LaneGroupAttribute(const ::holo::map::proto::base::LaneGroupAttribute& _proto_handler);
    // init all format data
    LaneGroupAttribute(const Type& _type,const IntervalType& _offset_type,const IntervalFloat64& _offset);
    ~LaneGroupAttribute();

    bool operator==(const ::holo::map::format::LaneGroupAttribute& _other) const;
    LaneGroupAttribute& operator=(const ::holo::map::proto::base::LaneGroupAttribute& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::base::LaneGroupAttribute GetProtoHandler()
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











};  // class LaneGroupAttribute

typedef ::std::shared_ptr<LaneGroupAttribute> PtrLaneGroupAttribute;
typedef const ::std::vector<LaneGroupAttribute>* ConstRawPtrVecLaneGroupAttribute;
typedef ::std::vector<LaneGroupAttribute>* RawPtrVecLaneGroupAttribute;
typedef ::std::shared_ptr<LaneGroupAttribute const> ConstPtrLaneGroupAttribute;
typedef ::std::shared_ptr<::std::vector<LaneGroupAttribute> const> ConstPtrVecLaneGroupAttribute;
typedef ::std::unordered_map<::std::uint64_t, PtrLaneGroupAttribute> HashmapLaneGroupAttribute;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_BASE_LANE_GROUP_ATTRIBUTE_H_