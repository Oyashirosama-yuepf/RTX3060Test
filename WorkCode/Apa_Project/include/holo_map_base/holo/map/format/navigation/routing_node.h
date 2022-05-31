/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file routing_node.h
 * @brief Auto generated code for RoutingNode format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_NAVIGATION_ROUTING_NODE_H_
#define HOLO_MAP_FORMAT_NAVIGATION_ROUTING_NODE_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/navigation/routing_node.pb.h>

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

class  RoutingNode: public Base
{
public:




private:
    ::std::uint64_t routing_node_id_; 
    ::std::uint64_t lane_id_; 
    ::std::uint64_t link_id_; 
    ::std::vector<::std::uint64_t> incoming_routing_edge_ids_; 
    ::std::vector<::std::uint64_t> outgoing_routing_edge_ids_; 
    double in_cost_; 
    double out_cost_; 
    ::std::uint64_t routing_graph_id_; 
    GeoPoint position_; 

private:
    void DecodeProto(const ::holo::map::proto::navigation::RoutingNode& _proto_handler);
    ::holo::map::proto::navigation::RoutingNode EncodeProto();

public:
    RoutingNode();
    explicit RoutingNode(const ::holo::map::proto::navigation::RoutingNode& _proto_handler);
    // init all format data
    RoutingNode(const ::std::uint64_t _routing_node_id,const ::std::uint64_t _lane_id,const ::std::uint64_t _link_id,const ::std::vector<::std::uint64_t>& _incoming_routing_edge_ids,const ::std::vector<::std::uint64_t>& _outgoing_routing_edge_ids,const double _in_cost,const double _out_cost,const ::std::uint64_t _routing_graph_id,const GeoPoint& _position);
    ~RoutingNode();

    bool operator==(const ::holo::map::format::RoutingNode& _other) const;
    RoutingNode& operator=(const ::holo::map::proto::navigation::RoutingNode& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::navigation::RoutingNode GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetRoutingNodeId() const
    {
        return routing_node_id_;
    }
    void SetRoutingNodeId(const ::std::uint64_t _routing_node_id)
    {
        routing_node_id_ = _routing_node_id;
    }

    ::std::uint64_t GetLaneId() const
    {
        return lane_id_;
    }
    void SetLaneId(const ::std::uint64_t _lane_id)
    {
        lane_id_ = _lane_id;
    }

    ::std::uint64_t GetLinkId() const
    {
        return link_id_;
    }
    void SetLinkId(const ::std::uint64_t _link_id)
    {
        link_id_ = _link_id;
    }

    const ::std::vector<::std::uint64_t>* GetPtrIncomingRoutingEdgeIds() const
    {
        return &incoming_routing_edge_ids_;
    }
    void SetIncomingRoutingEdgeIds(const ::std::vector<::std::uint64_t>& _incoming_routing_edge_ids)
    {
        incoming_routing_edge_ids_ = _incoming_routing_edge_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrOutgoingRoutingEdgeIds() const
    {
        return &outgoing_routing_edge_ids_;
    }
    void SetOutgoingRoutingEdgeIds(const ::std::vector<::std::uint64_t>& _outgoing_routing_edge_ids)
    {
        outgoing_routing_edge_ids_ = _outgoing_routing_edge_ids;
    }

    double GetInCost() const
    {
        return in_cost_;
    }
    void SetInCost(const double _in_cost)
    {
        in_cost_ = _in_cost;
    }

    double GetOutCost() const
    {
        return out_cost_;
    }
    void SetOutCost(const double _out_cost)
    {
        out_cost_ = _out_cost;
    }

    ::std::uint64_t GetRoutingGraphId() const
    {
        return routing_graph_id_;
    }
    void SetRoutingGraphId(const ::std::uint64_t _routing_graph_id)
    {
        routing_graph_id_ = _routing_graph_id;
    }

    const GeoPoint& GetPosition() const
    {
        return position_;
    }
    void SetPosition(const GeoPoint& _position)
    {
        position_ = _position;
    }


    void ClearIncomingRoutingEdgeIds()
    {
        incoming_routing_edge_ids_.clear();
    }
    void AddIncomingRoutingEdgeIdsElement(const ::std::uint64_t& _value)
    {
        incoming_routing_edge_ids_.push_back(_value);
    }
    void UniqueAddIncomingRoutingEdgeIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(incoming_routing_edge_ids_, _value);
    }

    void ClearOutgoingRoutingEdgeIds()
    {
        outgoing_routing_edge_ids_.clear();
    }
    void AddOutgoingRoutingEdgeIdsElement(const ::std::uint64_t& _value)
    {
        outgoing_routing_edge_ids_.push_back(_value);
    }
    void UniqueAddOutgoingRoutingEdgeIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(outgoing_routing_edge_ids_, _value);
    }









};  // class RoutingNode

typedef ::std::shared_ptr<RoutingNode> PtrRoutingNode;
typedef const ::std::vector<RoutingNode>* ConstRawPtrVecRoutingNode;
typedef ::std::vector<RoutingNode>* RawPtrVecRoutingNode;
typedef ::std::shared_ptr<RoutingNode const> ConstPtrRoutingNode;
typedef ::std::shared_ptr<::std::vector<RoutingNode> const> ConstPtrVecRoutingNode;
typedef ::std::unordered_map<::std::uint64_t, PtrRoutingNode> HashmapRoutingNode;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_NAVIGATION_ROUTING_NODE_H_