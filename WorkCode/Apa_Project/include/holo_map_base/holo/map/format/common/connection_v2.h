/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file connection_v2.h
 * @brief Auto generated code for ConnectionV2 format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_COMMON_CONNECTION_V2_H_
#define HOLO_MAP_FORMAT_COMMON_CONNECTION_V2_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/common/connection_v2.pb.h>

#include <holo/map/proto/common/geo_point.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/geo_point.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  ConnectionV2: public Base
{
public:

        
    enum ConnectedLevel
    {
        CONNECTED_LEVEL_LANE=  0,  
        CONNECTED_LEVEL_LINK=  1,  
    };

        
    enum ContractPointType
    {
        CONTRACT_POINT_TYPE_START=  0,  
        CONTRACT_POINT_TYPE_END=  1,  
    };

        
    enum ConnectType
    {
        CONNECT_TYPE_DEFAULT=  0,  
        CONNECT_TYPE_VIRTUAL=  1,  
        CONNECT_TYPE_DIRECT=  2,  
    };

    static const ::std::map<::std::string, ConnectedLevel>& ENUMSTR_CONNECTEDLEVEL() 
    { 
        static const ::std::map<::std::string, ConnectedLevel> data{
        { "LANE", ConnectedLevel::CONNECTED_LEVEL_LANE },
        { "LINK", ConnectedLevel::CONNECTED_LEVEL_LINK }};
        return data;
    }

    static const ::std::map<::std::string, ContractPointType>& ENUMSTR_CONTRACTPOINTTYPE() 
    { 
        static const ::std::map<::std::string, ContractPointType> data{
        { "START", ContractPointType::CONTRACT_POINT_TYPE_START },
        { "END", ContractPointType::CONTRACT_POINT_TYPE_END }};
        return data;
    }

    static const ::std::map<::std::string, ConnectType>& ENUMSTR_CONNECTTYPE() 
    { 
        static const ::std::map<::std::string, ConnectType> data{
        { "DEFAULT", ConnectType::CONNECT_TYPE_DEFAULT },
        { "VIRTUAL", ConnectType::CONNECT_TYPE_VIRTUAL },
        { "DIRECT", ConnectType::CONNECT_TYPE_DIRECT }};
        return data;
    }


private:
    ::std::vector<::std::uint64_t> connected_ids_; 
    ConnectedLevel connected_level_; 
    ContractPointType contract_point_type_; 
    ConnectType connect_type_; 
    ::std::uint64_t incoming_id_; 
    ::std::uint64_t outgoing_id_; 
    GeoPoint incoming_node_; 
    GeoPoint outgoing_node_; 

private:
    void DecodeProto(const ::holo::map::proto::common::ConnectionV2& _proto_handler);
    ::holo::map::proto::common::ConnectionV2 EncodeProto();

public:
    ConnectionV2();
    explicit ConnectionV2(const ::holo::map::proto::common::ConnectionV2& _proto_handler);
    // init all format data
    ConnectionV2(const ::std::vector<::std::uint64_t>& _connected_ids,const ConnectedLevel& _connected_level,const ContractPointType& _contract_point_type,const ConnectType& _connect_type,const ::std::uint64_t _incoming_id,const ::std::uint64_t _outgoing_id,const GeoPoint& _incoming_node,const GeoPoint& _outgoing_node);
    ~ConnectionV2();

    bool operator==(const ::holo::map::format::ConnectionV2& _other) const;
    ConnectionV2& operator=(const ::holo::map::proto::common::ConnectionV2& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::common::ConnectionV2 GetProtoHandler()
    {
        return EncodeProto();
    }

    


    const ::std::vector<::std::uint64_t>* GetPtrConnectedIds() const
    {
        return &connected_ids_;
    }
    void SetConnectedIds(const ::std::vector<::std::uint64_t>& _connected_ids)
    {
        connected_ids_ = _connected_ids;
    }

    const ConnectedLevel& GetConnectedLevel() const
    {
        return connected_level_;
    }
    void SetConnectedLevel(const ConnectedLevel& _connected_level)
    {
        connected_level_ = _connected_level;
    }

    const ContractPointType& GetContractPointType() const
    {
        return contract_point_type_;
    }
    void SetContractPointType(const ContractPointType& _contract_point_type)
    {
        contract_point_type_ = _contract_point_type;
    }

    const ConnectType& GetConnectType() const
    {
        return connect_type_;
    }
    void SetConnectType(const ConnectType& _connect_type)
    {
        connect_type_ = _connect_type;
    }

    ::std::uint64_t GetIncomingId() const
    {
        return incoming_id_;
    }
    void SetIncomingId(const ::std::uint64_t _incoming_id)
    {
        incoming_id_ = _incoming_id;
    }

    ::std::uint64_t GetOutgoingId() const
    {
        return outgoing_id_;
    }
    void SetOutgoingId(const ::std::uint64_t _outgoing_id)
    {
        outgoing_id_ = _outgoing_id;
    }

    const GeoPoint& GetIncomingNode() const
    {
        return incoming_node_;
    }
    void SetIncomingNode(const GeoPoint& _incoming_node)
    {
        incoming_node_ = _incoming_node;
    }

    const GeoPoint& GetOutgoingNode() const
    {
        return outgoing_node_;
    }
    void SetOutgoingNode(const GeoPoint& _outgoing_node)
    {
        outgoing_node_ = _outgoing_node;
    }


    void ClearConnectedIds()
    {
        connected_ids_.clear();
    }
    void AddConnectedIdsElement(const ::std::uint64_t& _value)
    {
        connected_ids_.push_back(_value);
    }
    void UniqueAddConnectedIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(connected_ids_, _value);
    }









};  // class ConnectionV2

typedef ::std::shared_ptr<ConnectionV2> PtrConnectionV2;
typedef const ::std::vector<ConnectionV2>* ConstRawPtrVecConnectionV2;
typedef ::std::vector<ConnectionV2>* RawPtrVecConnectionV2;
typedef ::std::shared_ptr<ConnectionV2 const> ConstPtrConnectionV2;
typedef ::std::shared_ptr<::std::vector<ConnectionV2> const> ConstPtrVecConnectionV2;
typedef ::std::unordered_map<::std::uint64_t, PtrConnectionV2> HashmapConnectionV2;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_COMMON_CONNECTION_V2_H_