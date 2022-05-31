/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file connection.h
 * @brief Auto generated code for Connection format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_NAVIGATION_CONNECTION_H_
#define HOLO_MAP_FORMAT_NAVIGATION_CONNECTION_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/navigation/connection.pb.h>

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

class  Connection: public Base
{
public:




private:
    ::std::uint64_t connection_id_; 
    ::std::uint64_t incoming_lane_id_; 
    GeoPoint incoming_lane_contact_node_; 
    ::std::uint64_t outgoing_lane_id_; 
    GeoPoint outgoing_lane_contact_node_; 
    ::std::uint64_t lane_id_; 
    bool is_allowed_; 

private:
    void DecodeProto(const ::holo::map::proto::navigation::Connection& _proto_handler);
    ::holo::map::proto::navigation::Connection EncodeProto();

public:
    Connection();
    explicit Connection(const ::holo::map::proto::navigation::Connection& _proto_handler);
    // init all format data
    Connection(const ::std::uint64_t _connection_id,const ::std::uint64_t _incoming_lane_id,const GeoPoint& _incoming_lane_contact_node,const ::std::uint64_t _outgoing_lane_id,const GeoPoint& _outgoing_lane_contact_node,const ::std::uint64_t _lane_id,const bool _is_allowed);
    ~Connection();

    bool operator==(const ::holo::map::format::Connection& _other) const;
    Connection& operator=(const ::holo::map::proto::navigation::Connection& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::navigation::Connection GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetConnectionId() const
    {
        return connection_id_;
    }
    void SetConnectionId(const ::std::uint64_t _connection_id)
    {
        connection_id_ = _connection_id;
    }

    ::std::uint64_t GetIncomingLaneId() const
    {
        return incoming_lane_id_;
    }
    void SetIncomingLaneId(const ::std::uint64_t _incoming_lane_id)
    {
        incoming_lane_id_ = _incoming_lane_id;
    }

    const GeoPoint& GetIncomingLaneContactNode() const
    {
        return incoming_lane_contact_node_;
    }
    void SetIncomingLaneContactNode(const GeoPoint& _incoming_lane_contact_node)
    {
        incoming_lane_contact_node_ = _incoming_lane_contact_node;
    }

    ::std::uint64_t GetOutgoingLaneId() const
    {
        return outgoing_lane_id_;
    }
    void SetOutgoingLaneId(const ::std::uint64_t _outgoing_lane_id)
    {
        outgoing_lane_id_ = _outgoing_lane_id;
    }

    const GeoPoint& GetOutgoingLaneContactNode() const
    {
        return outgoing_lane_contact_node_;
    }
    void SetOutgoingLaneContactNode(const GeoPoint& _outgoing_lane_contact_node)
    {
        outgoing_lane_contact_node_ = _outgoing_lane_contact_node;
    }

    ::std::uint64_t GetLaneId() const
    {
        return lane_id_;
    }
    void SetLaneId(const ::std::uint64_t _lane_id)
    {
        lane_id_ = _lane_id;
    }

    bool GetIsAllowed() const
    {
        return is_allowed_;
    }
    void SetIsAllowed(const bool _is_allowed)
    {
        is_allowed_ = _is_allowed;
    }











};  // class Connection

typedef ::std::shared_ptr<Connection> PtrConnection;
typedef const ::std::vector<Connection>* ConstRawPtrVecConnection;
typedef ::std::vector<Connection>* RawPtrVecConnection;
typedef ::std::shared_ptr<Connection const> ConstPtrConnection;
typedef ::std::shared_ptr<::std::vector<Connection> const> ConstPtrVecConnection;
typedef ::std::unordered_map<::std::uint64_t, PtrConnection> HashmapConnection;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_NAVIGATION_CONNECTION_H_