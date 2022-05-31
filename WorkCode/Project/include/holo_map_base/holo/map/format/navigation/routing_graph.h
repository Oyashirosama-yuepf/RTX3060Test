/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file routing_graph.h
 * @brief Auto generated code for RoutingGraph format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_NAVIGATION_ROUTING_GRAPH_H_
#define HOLO_MAP_FORMAT_NAVIGATION_ROUTING_GRAPH_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/navigation/routing_graph.pb.h>


#include <holo/map/format/base/base.h>


#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  RoutingGraph: public Base
{
public:

        
    enum Type
    {
        TYPE_UNDEFINED=  0,  
        TYPE_LINK=  1,  
        TYPE_LANE=  2,  
    };

    static const ::std::map<::std::string, Type>& ENUMSTR_TYPE() 
    { 
        static const ::std::map<::std::string, Type> data{
        { "UNDEFINED", Type::TYPE_UNDEFINED },
        { "LINK", Type::TYPE_LINK },
        { "LANE", Type::TYPE_LANE }};
        return data;
    }


private:
    ::std::uint64_t routing_graph_id_; 
    ::std::vector<::std::uint64_t> routing_node_ids_; 
    ::std::vector<::std::uint64_t> routing_edge_ids_; 
    Type type_; 

private:
    void DecodeProto(const ::holo::map::proto::navigation::RoutingGraph& _proto_handler);
    ::holo::map::proto::navigation::RoutingGraph EncodeProto();

public:
    RoutingGraph();
    explicit RoutingGraph(const ::holo::map::proto::navigation::RoutingGraph& _proto_handler);
    // init all format data
    RoutingGraph(const ::std::uint64_t _routing_graph_id,const ::std::vector<::std::uint64_t>& _routing_node_ids,const ::std::vector<::std::uint64_t>& _routing_edge_ids,const Type& _type);
    ~RoutingGraph();

    bool operator==(const ::holo::map::format::RoutingGraph& _other) const;
    RoutingGraph& operator=(const ::holo::map::proto::navigation::RoutingGraph& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::navigation::RoutingGraph GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetRoutingGraphId() const
    {
        return routing_graph_id_;
    }
    void SetRoutingGraphId(const ::std::uint64_t _routing_graph_id)
    {
        routing_graph_id_ = _routing_graph_id;
    }

    const ::std::vector<::std::uint64_t>* GetPtrRoutingNodeIds() const
    {
        return &routing_node_ids_;
    }
    void SetRoutingNodeIds(const ::std::vector<::std::uint64_t>& _routing_node_ids)
    {
        routing_node_ids_ = _routing_node_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrRoutingEdgeIds() const
    {
        return &routing_edge_ids_;
    }
    void SetRoutingEdgeIds(const ::std::vector<::std::uint64_t>& _routing_edge_ids)
    {
        routing_edge_ids_ = _routing_edge_ids;
    }

    const Type& GetType() const
    {
        return type_;
    }
    void SetType(const Type& _type)
    {
        type_ = _type;
    }


    void ClearRoutingNodeIds()
    {
        routing_node_ids_.clear();
    }
    void AddRoutingNodeIdsElement(const ::std::uint64_t& _value)
    {
        routing_node_ids_.push_back(_value);
    }
    void UniqueAddRoutingNodeIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(routing_node_ids_, _value);
    }

    void ClearRoutingEdgeIds()
    {
        routing_edge_ids_.clear();
    }
    void AddRoutingEdgeIdsElement(const ::std::uint64_t& _value)
    {
        routing_edge_ids_.push_back(_value);
    }
    void UniqueAddRoutingEdgeIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(routing_edge_ids_, _value);
    }









};  // class RoutingGraph

typedef ::std::shared_ptr<RoutingGraph> PtrRoutingGraph;
typedef const ::std::vector<RoutingGraph>* ConstRawPtrVecRoutingGraph;
typedef ::std::vector<RoutingGraph>* RawPtrVecRoutingGraph;
typedef ::std::shared_ptr<RoutingGraph const> ConstPtrRoutingGraph;
typedef ::std::shared_ptr<::std::vector<RoutingGraph> const> ConstPtrVecRoutingGraph;
typedef ::std::unordered_map<::std::uint64_t, PtrRoutingGraph> HashmapRoutingGraph;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_NAVIGATION_ROUTING_GRAPH_H_