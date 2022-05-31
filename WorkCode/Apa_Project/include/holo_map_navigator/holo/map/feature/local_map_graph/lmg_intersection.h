/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lmg_intersection.h
 * @brief define intersection infos for local map graph.
 * @author chanqiliang(chanqiliang@holomaitc.com)
 * @date 2022-2-25
 */

#ifndef HOLO_MAP_FEATURE_LOCAL_MAP_GRAPH_INTERSECTION_H_
#define HOLO_MAP_FEATURE_LOCAL_MAP_GRAPH_INTERSECTION_H_

#include <holo/map/feature/local_map_graph/lmg_common.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace graph
{
/**
 * @addtogroup graph
 *
 * @{
 */
template <typename FeatureIdT, typename PointT, size_t CONNECTION_INNER_SIZE = 1024>
class IntersectionConnection  : public FeatureBase<FeatureIdT>
{
public:
    using FeatureIdType                  = FeatureIdT;
    using PointType                      = PointT;
    using ConnectionVectorType = holo::container::Vector<FeatureIdType, CONNECTION_INNER_SIZE>;

    IntersectionConnection() : FeatureBase<FeatureIdType>(holo::map::navigator::graph::FeatureType::FEATURE_TYPE_INTERSECTION)
    {
    }
    ~IntersectionConnection()               = default;
    IntersectionConnection(IntersectionConnection const&) = default;
    IntersectionConnection(IntersectionConnection&&)      = delete;
    IntersectionConnection& operator=(IntersectionConnection const&) = default;
    IntersectionConnection& operator=(IntersectionConnection&&) = delete;
    
    enum class ConnectedLevel : uint8_t
    {
        CONNECTED_LEVEL_LANE=  0,  
        CONNECTED_LEVEL_LINK=  1,  
    };

    enum class ContractPointType : uint8_t
    {
        CONTRACT_POINT_TYPE_START=  0,  
        CONTRACT_POINT_TYPE_END=  1,  
    };

    enum class ConnectType : uint8_t
    {
        CONNECT_TYPE_DEFAULT=  0,  
        CONNECT_TYPE_VIRTUAL=  1,  
        CONNECT_TYPE_DIRECT=  2,  
    };

    /**
     * @brief Set connected ids.
     *
     * @param connected_ids connected ids.
     */
    void SetConnectedIds(ConnectionVectorType const& connected_ids) noexcept
    {
        this->connected_ids_ = connected_ids;
    }

    /**
     * @brief Get connected  ids.
     *
     * @return connected ids.
     */
    ConnectionVectorType const& GetConnectedIds() const noexcept
    {
        return this->connected_ids_;
    }

    /**
     * @brief Set  connection level
     *
     * @param   connected_level connected level.
     */
    void SetConnectedLevel(ConnectedLevel const& connected_level) noexcept
    {
        this->connected_level_ = connected_level;
    }

    /**
     * @brief Get connection level.
     *
     * @return Connected level.
     */
    ConnectedLevel const& GetConnectedLevel() const noexcept
    {
        return this->connected_level_;
    }

    /**
     * @brief Set  contract type.
     *
     * @param   
     */
    void SetContractType(ContractPointType const& contract_point_type) noexcept
    {
        this->contract_point_type_ = contract_point_type;
    }

    /**
     * @brief Get contract type.
     *
     * @return Contract point type.
     */
    ContractPointType const& GetContractType() const noexcept
    {
        return this->contract_point_type_;
    }

    /**
     * @brief Set  connection type
     *
     * @param   connected_level connected level.
     */
    void SetConnectType(ConnectType const& connect_type) noexcept
    {
        this->connect_type_ = connect_type;
    }

    /**
     * @brief Get connection type.
     *
     * @return Connected type.
     */
    ConnectType const& GetConnectType() const noexcept
    {
        return this->connect_type_;
    }

    /**
     * @brief Set  incoming id.
     *
     * @param   incoming_id incoming id.
     */
    void SetIncomingId(FeatureIdType const incoming_id) noexcept
    {
        this->incoming_id_ = incoming_id;
    }

    /**
     * @brief Get incoming id.
     *
     * @return Incoming id.
     */
    FeatureIdType GetIncomingId() const noexcept
    {
        return this->incoming_id_;
    }

    /**
     * @brief Set  outgoing id.
     *
     * @param   outgoing_id outgoing id.
     */
    void SetOutgoingId(FeatureIdType const outgoing_id) noexcept
    {
        this->outgoing_id_ = outgoing_id;
    }

    /**
     * @brief Get outgoing id.
     *
     * @return Outgoing id.
     */
    FeatureIdType GetOutgoingId() const noexcept
    {
        return this->outgoing_id_;
    }

    /**
     * @brief Set  incoming node.
     *
     * @param   incoming_node incoming node.
     */
    void SetIncomingNode(PointType const& incoming_node) noexcept
    {
        this->incoming_node_ = incoming_node;
    }

    /**
     * @brief Get incoming node.
     *
     * @return Incoming node.
     */
    PointType const& GetIncomingNode() const noexcept
    {
        return this->incoming_node_;
    }

    /**
     * @brief Set  outgoing node.
     *
     * @param   incoming_node outgoing node.
     */
    void SetOutgoingNode(PointType const& outgoing_node) noexcept
    {
        this->outgoing_node_ = outgoing_node;
    }

    /**
     * @brief Get outgoing node.
     *
     * @return Outgoing node.
     */
    PointType const& GetOutgoingNode() const noexcept
    {
        return this->outgoing_node_;
    }

private:
    ConnectionVectorType connected_ids_; 
    ConnectedLevel connected_level_; 
    ContractPointType contract_point_type_; 
    ConnectType connect_type_; 
    FeatureIdType incoming_id_; 
    FeatureIdType outgoing_id_; 
    PointType incoming_node_; 
    PointType outgoing_node_; 
};


/**
 * @brief Define Intersection
 */
template <typename FeatureIdT, typename PointT, size_t INTERSECTION_ID_SIZE = 128U,size_t LINE_SIZE = 1024U, size_t CONNECTION_SIZE = 1024U,
                    size_t OBJECT_SIZE = 1024U>
class Intersection : public FeatureBase<FeatureIdT>
{
public:
    using FeatureIdType                  = FeatureIdT;
    using PointType                      = PointT;
    using IntersectionVectorType           = holo::container::Vector<FeatureIdT, INTERSECTION_ID_SIZE>;
    using Point3dVectorType              = holo::container::Vector<PointType, LINE_SIZE>;
    using IntersectionConnectionType = IntersectionConnection<FeatureIdType, PointType>;
    using ConnectionVectorType = holo::container::Vector<IntersectionConnectionType, CONNECTION_SIZE>;
    using ObjectVectorType = holo::container::Vector<FeatureIdType, OBJECT_SIZE>;

    enum class IntersectionType : uint8_t
    {
        INTERSECTION_TYPE_UNDEFINED=  0,  
        INTERSECTION_TYPE_CROSSROAD=  1,  
        INTERSECTION_TYPE_T_JUNCTION=  2,  
        INTERSECTION_TYPE_Y_JUNCTION=  3,  
        INTERSECTION_TYPE_MULTI_FORK_JUNCTION=  4,  
        INTERSECTION_TYPE_ROUNDABOUT=  5,  
        INTERSECTION_TYPE_OTHERS=  255,
    };

    Intersection() : FeatureBase<FeatureIdType>(holo::map::navigator::graph::FeatureType::FEATURE_TYPE_INTERSECTION)
    {
    }
    ~Intersection()               = default;
    Intersection(Intersection const&) = default;
    Intersection(Intersection&&)      = delete;
    Intersection& operator=(Intersection const&) = default;
    Intersection& operator=(Intersection&&) = delete;
    
     /**
     * @brief Set  intersection id
     *
     * @param   intersection_id intersection id
     */
    void SetIntersectionId(FeatureIdType const intersection_id) noexcept
    {
        this->intersection_id_ = intersection_id;
    }

    /**
     * @brief Get intersection id
     *
     * @return Intersection id
     */
    FeatureIdType GetIntersectionId() const noexcept
    {
        return this->intersection_id_;
    }

    /**
     * @brief Set  geometry
     *
     * @param   geometry geometry polygon
     */
    void SetGeometry(Point3dVectorType const& geometry) noexcept
    {
        this->geometry_ = geometry;
    }

    /**
     * @brief Get geometry
     *
     * @return Geometry polygon
     */
    Point3dVectorType const& GetGeometry() const noexcept
    {
        return this->geometry_;
    }

    /**
     * @brief Set  lane connections
     *
     * @param   lane_connections lane connections
     */
    void SetLaneConnections(ConnectionVectorType const& lane_connections) noexcept
    {
        this->lane_connections_ = lane_connections;
    }

    /**
     * @brief Get lane connections
     *
     * @return Lane connections
     */
    ConnectionVectorType const& GetLaneConnections() const noexcept
    {
        return this->lane_connections_;
    }

    /**
     * @brief Set  link connections
     *
     * @param   link_connections link connections
     */
    void SetLinkConnections(ConnectionVectorType const& link_connections) noexcept
    {
        this->link_connections_ = link_connections;
    }

    /**
     * @brief Get link connections
     *
     * @return Link connections
     */
    ConnectionVectorType const& GetLinkConnections() const noexcept
    {
        return this->link_connections_;
    }
    
    /**
     * @brief Set  intresection type
     *
     * @param   type intresection type
     */
    void SetIntersectionType(IntersectionType const& type) noexcept
    {
        this->type_ = type;
    }

    /**
     * @brief Get intersection type.
     *
     * @return Intersection type.
     */
    IntersectionType const& GetIntersectionType() const noexcept
    {
        return this->type_;
    }
    
    /**
     * @brief Set  associated  stop lines
     *
     * @param   associated_stop_lines_  associated stop lines
     */
    void SetAssociatedStopLines(ObjectVectorType const& associated_stop_lines) noexcept
    {
        this->associated_stop_lines_ =associated_stop_lines;
    }

    /**
     * @brief Get associated stop lines
     *
     * @return Associated  stop lines
     */
    ObjectVectorType const& GetAssociatedStopLines() const noexcept
    {
        return this->associated_stop_lines_;
    }
    
    /**
     * @brief Set  associated  traffic lights
     *
     * @param   associated_traffic_lights_  associated traffic lights
     */
    void SetAssociatedTrafficLights(ObjectVectorType const& associated_traffic_lights) noexcept
    {
        this->associated_traffic_lights_ =associated_traffic_lights;
    }

    /**
     * @brief Get associated traffic lights
     *
     * @return Associated  traffic lights
     */
    ObjectVectorType const& GetAssociatedTrafficLights() const noexcept
    {
        return this->associated_traffic_lights_;
    }
    
    /**
     * @brief Set  associated  safe islands
     *
     * @param   associated_safe_islands_  associated safe islands
     */
    void SetAssociatedSafeIslands(ObjectVectorType const& associated_safe_islands) noexcept
    {
        this->associated_safe_islands_ =associated_safe_islands;
    }

    /**
     * @brief Get associated safe islands
     *
     * @return Associated  safe islands
     */
    ObjectVectorType const& GetAssociatedSafeIslands() const noexcept
    {
        return this->associated_safe_islands_;
    }

    /**
     * @brief Set  associated  pedestrian crosswalk
     *
     * @param   associated_pedestrian_crosswalk  associated pedestrian crosswalk
     */
    void SetAssociatedPedestrianCrosswalk(ObjectVectorType const& associated_pedestrian_crosswalk) noexcept
    {
        this->associated_pedestrian_crosswalk_ =associated_pedestrian_crosswalk;
    }

    /**
     * @brief Get associated pedestrian crosswalk
     *
     * @return Associated  pedestrian crosswalk
     */
    ObjectVectorType const& GetAssociatedPedestrianCrosswalk() const noexcept
    {
        return this->associated_pedestrian_crosswalk_;
    }

    /**
     * @brief Set  associated  parking space
     *
     * @param   associated_pedestrian_crosswalk  associated parking space
     */
    void SetAssociatedParkingSpace(ObjectVectorType const& associated_parking_space) noexcept
    {
        this->associated_parking_space_ =associated_parking_space;
    }

    /**
     * @brief Get associated parking space
     *
     * @return Associated  parking space
     */
    ObjectVectorType const& GetAssociatedParkingSpace() const noexcept
    {
        return this->associated_parking_space_;
    }


private:
    FeatureIdType intersection_id_ = static_cast<FeatureIdType>(0);  /// intersection id, invalid intersection id: 0.
    Point3dVectorType geometry_;
    ConnectionVectorType lane_connections_;
    ConnectionVectorType link_connections_;
    IntersectionType type_ = IntersectionType::INTERSECTION_TYPE_UNDEFINED;
    ObjectVectorType associated_stop_lines_; 
    ObjectVectorType associated_traffic_lights_; 
    ObjectVectorType associated_safe_islands_; 
    ObjectVectorType associated_pedestrian_crosswalk_; 
    ObjectVectorType associated_parking_space_;   
};

/**
 * @}
 */
}  // namespace graph
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif  // HOLO_MAP_FEATURE_LOCAL_MAP_GRAPH_INTERSECTION_H_