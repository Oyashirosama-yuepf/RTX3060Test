/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file routing_edge.h
 * @brief Auto generated code for RoutingEdge format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_NAVIGATION_ROUTING_EDGE_H_
#define HOLO_MAP_FORMAT_NAVIGATION_ROUTING_EDGE_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/navigation/routing_edge.pb.h>


#include <holo/map/format/base/base.h>


#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  RoutingEdge: public Base
{
public:




private:
    ::std::uint64_t routing_edge_id_; 
    ::std::uint64_t incoming_routing_node_id_; 
    ::std::uint64_t outgoing_routing_node_id_; 
    double cost_; 
    ::std::uint64_t routing_graph_id_; 

private:
    void DecodeProto(const ::holo::map::proto::navigation::RoutingEdge& _proto_handler);
    ::holo::map::proto::navigation::RoutingEdge EncodeProto();

public:
    RoutingEdge();
    explicit RoutingEdge(const ::holo::map::proto::navigation::RoutingEdge& _proto_handler);
    // init all format data
    RoutingEdge(const ::std::uint64_t _routing_edge_id,const ::std::uint64_t _incoming_routing_node_id,const ::std::uint64_t _outgoing_routing_node_id,const double _cost,const ::std::uint64_t _routing_graph_id);
    ~RoutingEdge();

    bool operator==(const ::holo::map::format::RoutingEdge& _other) const;
    RoutingEdge& operator=(const ::holo::map::proto::navigation::RoutingEdge& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::navigation::RoutingEdge GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetRoutingEdgeId() const
    {
        return routing_edge_id_;
    }
    void SetRoutingEdgeId(const ::std::uint64_t _routing_edge_id)
    {
        routing_edge_id_ = _routing_edge_id;
    }

    ::std::uint64_t GetIncomingRoutingNodeId() const
    {
        return incoming_routing_node_id_;
    }
    void SetIncomingRoutingNodeId(const ::std::uint64_t _incoming_routing_node_id)
    {
        incoming_routing_node_id_ = _incoming_routing_node_id;
    }

    ::std::uint64_t GetOutgoingRoutingNodeId() const
    {
        return outgoing_routing_node_id_;
    }
    void SetOutgoingRoutingNodeId(const ::std::uint64_t _outgoing_routing_node_id)
    {
        outgoing_routing_node_id_ = _outgoing_routing_node_id;
    }

    double GetCost() const
    {
        return cost_;
    }
    void SetCost(const double _cost)
    {
        cost_ = _cost;
    }

    ::std::uint64_t GetRoutingGraphId() const
    {
        return routing_graph_id_;
    }
    void SetRoutingGraphId(const ::std::uint64_t _routing_graph_id)
    {
        routing_graph_id_ = _routing_graph_id;
    }











};  // class RoutingEdge

typedef ::std::shared_ptr<RoutingEdge> PtrRoutingEdge;
typedef const ::std::vector<RoutingEdge>* ConstRawPtrVecRoutingEdge;
typedef ::std::vector<RoutingEdge>* RawPtrVecRoutingEdge;
typedef ::std::shared_ptr<RoutingEdge const> ConstPtrRoutingEdge;
typedef ::std::shared_ptr<::std::vector<RoutingEdge> const> ConstPtrVecRoutingEdge;
typedef ::std::unordered_map<::std::uint64_t, PtrRoutingEdge> HashmapRoutingEdge;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_NAVIGATION_ROUTING_EDGE_H_