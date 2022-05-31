/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file routing_path_element.h
 * @brief Auto generated code for RoutingPathElement format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_NAVIGATION_ROUTING_PATH_ELEMENT_H_
#define HOLO_MAP_FORMAT_NAVIGATION_ROUTING_PATH_ELEMENT_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/navigation/routing_path_element.pb.h>


#include <holo/map/format/base/base.h>


#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  RoutingPathElement: public Base
{
public:

        
    enum NavigationType
    {
        NAVIGATION_TYPE_UNKNOWN=  0,  
        NAVIGATION_TYPE_REGULAR=  1,  
        NAVIGATION_TYPE_NAVIGATION_START=  2,  
        NAVIGATION_TYPE_NAVIGATION_END=  3,  
        NAVIGATION_TYPE_NAVIGATION_START_END=  4,  
        NAVIGATION_TYPE_RESERVE_1=  200,  
        NAVIGATION_TYPE_RESERVE_2=  201,  
        NAVIGATION_TYPE_RESERVE_3=  202,  
        NAVIGATION_TYPE_RESERVE_4=  203,  
        NAVIGATION_TYPE_RESERVE_5=  204,  
        NAVIGATION_TYPE_OTHERS=  255,  
    };

        
    enum RoutingType
    {
        ROUTING_TYPE_UNKNOWN=  0,  
        ROUTING_TYPE_REGULAR=  1,  
        ROUTING_TYPE_ROUTING_ENTRY_EDGE=  2,  
        ROUTING_TYPE_ROUTING_EXIT_EDGE=  3,  
        ROUTING_TYPE_ROUTING_ENTRY_EXIT_EDGE=  4,  
        ROUTING_TYPE_RESERVE_1=  200,  
        ROUTING_TYPE_RESERVE_2=  201,  
        ROUTING_TYPE_RESERVE_3=  202,  
        ROUTING_TYPE_RESERVE_4=  203,  
        ROUTING_TYPE_RESERVE_5=  204,  
        ROUTING_TYPE_OTHERS=  255,  
    };

    static const ::std::map<::std::string, NavigationType>& ENUMSTR_NAVIGATIONTYPE() 
    { 
        static const ::std::map<::std::string, NavigationType> data{
        { "UNKNOWN", NavigationType::NAVIGATION_TYPE_UNKNOWN },
        { "REGULAR", NavigationType::NAVIGATION_TYPE_REGULAR },
        { "NAVIGATION_START", NavigationType::NAVIGATION_TYPE_NAVIGATION_START },
        { "NAVIGATION_END", NavigationType::NAVIGATION_TYPE_NAVIGATION_END },
        { "NAVIGATION_START_END", NavigationType::NAVIGATION_TYPE_NAVIGATION_START_END },
        { "RESERVE_1", NavigationType::NAVIGATION_TYPE_RESERVE_1 },
        { "RESERVE_2", NavigationType::NAVIGATION_TYPE_RESERVE_2 },
        { "RESERVE_3", NavigationType::NAVIGATION_TYPE_RESERVE_3 },
        { "RESERVE_4", NavigationType::NAVIGATION_TYPE_RESERVE_4 },
        { "RESERVE_5", NavigationType::NAVIGATION_TYPE_RESERVE_5 },
        { "OTHERS", NavigationType::NAVIGATION_TYPE_OTHERS }};
        return data;
    }

    static const ::std::map<::std::string, RoutingType>& ENUMSTR_ROUTINGTYPE() 
    { 
        static const ::std::map<::std::string, RoutingType> data{
        { "UNKNOWN", RoutingType::ROUTING_TYPE_UNKNOWN },
        { "REGULAR", RoutingType::ROUTING_TYPE_REGULAR },
        { "ROUTING_ENTRY_EDGE", RoutingType::ROUTING_TYPE_ROUTING_ENTRY_EDGE },
        { "ROUTING_EXIT_EDGE", RoutingType::ROUTING_TYPE_ROUTING_EXIT_EDGE },
        { "ROUTING_ENTRY_EXIT_EDGE", RoutingType::ROUTING_TYPE_ROUTING_ENTRY_EXIT_EDGE },
        { "RESERVE_1", RoutingType::ROUTING_TYPE_RESERVE_1 },
        { "RESERVE_2", RoutingType::ROUTING_TYPE_RESERVE_2 },
        { "RESERVE_3", RoutingType::ROUTING_TYPE_RESERVE_3 },
        { "RESERVE_4", RoutingType::ROUTING_TYPE_RESERVE_4 },
        { "RESERVE_5", RoutingType::ROUTING_TYPE_RESERVE_5 },
        { "OTHERS", RoutingType::ROUTING_TYPE_OTHERS }};
        return data;
    }


private:
    ::std::uint64_t id_; 
    ::std::uint32_t length_cm_; 
    bool is_positive_; 
    ::std::vector<::std::uint64_t> branch_path_ids_; 
    NavigationType navigation_type_; 
    RoutingType routing_type_; 

private:
    void DecodeProto(const ::holo::map::proto::navigation::RoutingPathElement& _proto_handler);
    ::holo::map::proto::navigation::RoutingPathElement EncodeProto();

public:
    RoutingPathElement();
    explicit RoutingPathElement(const ::holo::map::proto::navigation::RoutingPathElement& _proto_handler);
    // init all format data
    RoutingPathElement(const ::std::uint64_t _id,const ::std::uint32_t _length_cm,const bool _is_positive,const ::std::vector<::std::uint64_t>& _branch_path_ids,const NavigationType& _navigation_type,const RoutingType& _routing_type);
    ~RoutingPathElement();

    bool operator==(const ::holo::map::format::RoutingPathElement& _other) const;
    RoutingPathElement& operator=(const ::holo::map::proto::navigation::RoutingPathElement& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::navigation::RoutingPathElement GetProtoHandler()
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

    ::std::uint32_t GetLengthCm() const
    {
        return length_cm_;
    }
    void SetLengthCm(const ::std::uint32_t _length_cm)
    {
        length_cm_ = _length_cm;
    }

    bool GetIsPositive() const
    {
        return is_positive_;
    }
    void SetIsPositive(const bool _is_positive)
    {
        is_positive_ = _is_positive;
    }

    const ::std::vector<::std::uint64_t>* GetPtrBranchPathIds() const
    {
        return &branch_path_ids_;
    }
    void SetBranchPathIds(const ::std::vector<::std::uint64_t>& _branch_path_ids)
    {
        branch_path_ids_ = _branch_path_ids;
    }

    const NavigationType& GetNavigationType() const
    {
        return navigation_type_;
    }
    void SetNavigationType(const NavigationType& _navigation_type)
    {
        navigation_type_ = _navigation_type;
    }

    const RoutingType& GetRoutingType() const
    {
        return routing_type_;
    }
    void SetRoutingType(const RoutingType& _routing_type)
    {
        routing_type_ = _routing_type;
    }


    void ClearBranchPathIds()
    {
        branch_path_ids_.clear();
    }
    void AddBranchPathIdsElement(const ::std::uint64_t& _value)
    {
        branch_path_ids_.push_back(_value);
    }
    void UniqueAddBranchPathIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(branch_path_ids_, _value);
    }









};  // class RoutingPathElement

typedef ::std::shared_ptr<RoutingPathElement> PtrRoutingPathElement;
typedef const ::std::vector<RoutingPathElement>* ConstRawPtrVecRoutingPathElement;
typedef ::std::vector<RoutingPathElement>* RawPtrVecRoutingPathElement;
typedef ::std::shared_ptr<RoutingPathElement const> ConstPtrRoutingPathElement;
typedef ::std::shared_ptr<::std::vector<RoutingPathElement> const> ConstPtrVecRoutingPathElement;
typedef ::std::unordered_map<::std::uint64_t, PtrRoutingPathElement> HashmapRoutingPathElement;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_NAVIGATION_ROUTING_PATH_ELEMENT_H_