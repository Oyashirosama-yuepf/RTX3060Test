/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file routing_request.h
 * @brief Auto generated code for RoutingRequest format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_NAVIGATION_ROUTING_REQUEST_H_
#define HOLO_MAP_FORMAT_NAVIGATION_ROUTING_REQUEST_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/navigation/routing_request.pb.h>

#include <holo/map/proto/navigation/routing_position.pb.h>

#include <holo/map/proto/common/interval_type.pb.h>

#include <holo/map/proto/common/interval_float64.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/navigation/routing_position.h>

#include <holo/map/format/common/interval_type.h>

#include <holo/map/format/common/interval_float64.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  RoutingRequest: public Base
{
public:

        
    enum Type
    {
        TYPE_FULL_PATH=  1,  
        TYPE_PART_PATH=  2,  
    };

        
    enum Policy
    {
        POLICY_RECOMMEND=  0,  
        POLICY_SHORTEST_DISTANCE=  1,  
        POLICY_SHORTEST_TIME=  2,  
        POLICY_SHORTEST_TOLL=  3,  
        POLICY_SHORTEST_HIGHWAY=  4,  
    };

    static const ::std::map<::std::string, Type>& ENUMSTR_TYPE() 
    { 
        static const ::std::map<::std::string, Type> data{
        { "FULL_PATH", Type::TYPE_FULL_PATH },
        { "PART_PATH", Type::TYPE_PART_PATH }};
        return data;
    }

    static const ::std::map<::std::string, Policy>& ENUMSTR_POLICY() 
    { 
        static const ::std::map<::std::string, Policy> data{
        { "RECOMMEND", Policy::POLICY_RECOMMEND },
        { "SHORTEST_DISTANCE", Policy::POLICY_SHORTEST_DISTANCE },
        { "SHORTEST_TIME", Policy::POLICY_SHORTEST_TIME },
        { "SHORTEST_TOLL", Policy::POLICY_SHORTEST_TOLL },
        { "SHORTEST_HIGHWAY", Policy::POLICY_SHORTEST_HIGHWAY }};
        return data;
    }


private:
    ::std::uint64_t routing_request_id_; 
    RoutingPosition start_position_; 
    RoutingPosition end_position_; 
    ::std::vector<RoutingPosition> middle_position_; 
    Type type_; 
    Policy policy_; 
    ::std::uint32_t result_count_; 
    IntervalType part_path_type_; 
    IntervalFloat64 part_path_range_; 

private:
    void DecodeProto(const ::holo::map::proto::navigation::RoutingRequest& _proto_handler);
    ::holo::map::proto::navigation::RoutingRequest EncodeProto();

public:
    RoutingRequest();
    explicit RoutingRequest(const ::holo::map::proto::navigation::RoutingRequest& _proto_handler);
    // init all format data
    RoutingRequest(const ::std::uint64_t _routing_request_id,const RoutingPosition& _start_position,const RoutingPosition& _end_position,const ::std::vector<RoutingPosition>& _middle_position,const Type& _type,const Policy& _policy,const ::std::uint32_t _result_count,const IntervalType& _part_path_type,const IntervalFloat64& _part_path_range);
    ~RoutingRequest();

    bool operator==(const ::holo::map::format::RoutingRequest& _other) const;
    RoutingRequest& operator=(const ::holo::map::proto::navigation::RoutingRequest& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::navigation::RoutingRequest GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetRoutingRequestId() const
    {
        return routing_request_id_;
    }
    void SetRoutingRequestId(const ::std::uint64_t _routing_request_id)
    {
        routing_request_id_ = _routing_request_id;
    }

    const RoutingPosition& GetStartPosition() const
    {
        return start_position_;
    }
    void SetStartPosition(const RoutingPosition& _start_position)
    {
        start_position_ = _start_position;
    }

    const RoutingPosition& GetEndPosition() const
    {
        return end_position_;
    }
    void SetEndPosition(const RoutingPosition& _end_position)
    {
        end_position_ = _end_position;
    }

    const ::std::vector<RoutingPosition>* GetPtrMiddlePosition() const
    {
        return &middle_position_;
    }
    void SetMiddlePosition(const ::std::vector<RoutingPosition>& _middle_position)
    {
        middle_position_ = _middle_position;
    }

    const Type& GetType() const
    {
        return type_;
    }
    void SetType(const Type& _type)
    {
        type_ = _type;
    }

    const Policy& GetPolicy() const
    {
        return policy_;
    }
    void SetPolicy(const Policy& _policy)
    {
        policy_ = _policy;
    }

    ::std::uint32_t GetResultCount() const
    {
        return result_count_;
    }
    void SetResultCount(const ::std::uint32_t _result_count)
    {
        result_count_ = _result_count;
    }

    const IntervalType& GetPartPathType() const
    {
        return part_path_type_;
    }
    void SetPartPathType(const IntervalType& _part_path_type)
    {
        part_path_type_ = _part_path_type;
    }

    const IntervalFloat64& GetPartPathRange() const
    {
        return part_path_range_;
    }
    void SetPartPathRange(const IntervalFloat64& _part_path_range)
    {
        part_path_range_ = _part_path_range;
    }


    void ClearMiddlePosition()
    {
        middle_position_.clear();
    }
    void AddMiddlePositionElement(const RoutingPosition& _value)
    {
        middle_position_.push_back(_value);
    }
    void UniqueAddMiddlePositionElements(const ::std::vector<RoutingPosition>& _value)
    {
        UniqueAppend(middle_position_, _value);
    }









};  // class RoutingRequest

typedef ::std::shared_ptr<RoutingRequest> PtrRoutingRequest;
typedef const ::std::vector<RoutingRequest>* ConstRawPtrVecRoutingRequest;
typedef ::std::vector<RoutingRequest>* RawPtrVecRoutingRequest;
typedef ::std::shared_ptr<RoutingRequest const> ConstPtrRoutingRequest;
typedef ::std::shared_ptr<::std::vector<RoutingRequest> const> ConstPtrVecRoutingRequest;
typedef ::std::unordered_map<::std::uint64_t, PtrRoutingRequest> HashmapRoutingRequest;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_NAVIGATION_ROUTING_REQUEST_H_