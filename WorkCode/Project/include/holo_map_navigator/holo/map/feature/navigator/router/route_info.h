/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file route_info.h
 * @brief Route info for navigation
 * @author yuhongbo(yuhongbo@holomaitc.com)
 * @date "2021-10-08"
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ROUTER_ROUTE_INFO_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ROUTER_ROUTE_INFO_H_

#include <deque>
#include <memory>

#include <holo/map/common/common_define.h>
#include <holo/map/common/common_type_define.h>
#include <holo/map/format/common/geo_point.h>

namespace holo
{
namespace map
{
/**
 * @brief The result for route calculation
 * 
 */
class RouteInfo2
{
public:
    
    using Ptr = std::shared_ptr<RouteInfo2>;
    using RouteInfo2SPtrType = std::shared_ptr<RouteInfo2>;

    enum class RoutePlace : holo::uint8_t
    {
       FRONT,
       CURRENT,
       BACK,
       UNKNONWN
    };

    enum class RouteState : holo::uint8_t
    {
        ON_HD_ROUTE  = 0,
        ON_SD_ROUTE  = 1,
        NOT_ON_ROUTE = 2
    };

    /**
     * @brief Basic item in route info
     * 
     */
    struct RouteItem
    {
        /// Unique id
        std::size_t id = 0;
        LinkIdType link_id = 0;
        /// Length(meter) of link.
        Distance link_length = 0.0;
        /// Length(meter) between start point of current link and end point of destination link.
        Distance distance_to_destination = 0.0;
        /// Point at the start of link.
        format::GeoPoint link_start_point;
        /// Point at the end of link.
        format::GeoPoint link_end_point;
    };

    using RouteHash  = std::set<IdType>;
    using RouteQueue = std::deque<RouteItem>;
    using RouteItemType = RouteItem;

    /**
     * @brief Find index of link_id in route path.
     * @param [in] _path Route path.
     * @param [in] _id Link id.
     * @param [out] _index route index.
     * @return true If find _id in _path, return true;
     *         false Otherwise return false.
     */
    static bool FindLinkIndex(const RouteQueue& _path, const IdType _id, std::size_t& _index);

    /**
     * @brief Format RouteItemType object to json string.
     * 
     * @param[in] route_item A RouteItemType object
     * @return Json string
     */
    static std::string FormatToString(RouteItemType const& route_item);

    /**
     * @brief Format RouteQueue object to json string.
     * 
     * @param[in] route_que A RouteQueue object
     * @return Json string
     */
    static std::string FormatToString(RouteQueue const& route_que);

    /**
     * @brief Format RouteInfo to json string.
     *
     * @param route_info
     * @return std::string
     */
    static std::string FormatToString(RouteInfo2 const& route_info);

    /**
     * @brief Format link array
     * 
     * @param route_que 
     * @return std::string 
     */
    static std::string FormatArrayToString(RouteQueue const& route_que);

public :
        /**
         * @brief Contructor.
         */
        RouteInfo2() = default;

    /**
     * @brief Decontructor.
     */
    virtual ~RouteInfo2() = default;

    /**
     * @brief Add link id to route path.
     * @param [in] _id Link id.
     * @param [in] _len Link length.
     * @param [in] _start_point Link start point.
     * @param [in] _end_point Link end point.
     * @return true Success;
     *         false Failure.
     */
    bool AddRouteItem(const IdType _id,
                      const Distance _len,
                      const format::GeoPoint& _start_point,
                      const format::GeoPoint& _end_point);

    /**
     * @brief Add route item.
     * @param [in] item Route item.
     */
    void AddRouteItem(RouteItem const& item);

    /**
     * @brief Access original in routing path.
     * 
     * @note If router in prediction mode, original link id is 0.
     * @return Return original link id.
     */
    IdType GetOriginalLinkID() const;

    /**
     * @brief Update original.
     * 
     * @param[in] id Origin link id in the routing path.
     * @note If router in prediction mode, set 0 to it.
     * @return Nothing.
     */
    void SetOriginalLinkID(const IdType id); 
    
    /**
     * @brief Access destination in routing path.
     * 
     * @note If router in prediction mode, destination link id is 0.
     * @return Return destination link id.
     */
    IdType GetDestinationLinkID() const;

     /**
     * @brief Update destination.
     * 
     * @param[in] id Destination link id in the routing path.
     * @note If router in prediction mode, set 0 to it.
     * @return Nothing.
     */
    void SetDestinationLinkID(const IdType id);


    /**
     * @brief Clear route path.
     */
    void Clear();

    /**
     * @brief Update value of distance to destination for all links if RouteInfo2 object has been updated.
     * @return true Success;
     *         false Failure.
     */
    bool UpdateDistanceToDestination();

    /**
     * @brief Remove passed route item current map matching link id.
     * @param [in] _id Link id.
     * @return true Success;
     *         false Failure.
     */
    bool RemoveDirtyRouteItem(const IdType _id);

    /**
     * @brief Check if route path is available.
     * @return true Available return true;
     *         false Otherwise return false.
     */
    bool IsAvailable() const;

    /**
     * @brief Check if link is is on route path.
     * @param[in] _id Link id.
     * @return true If on route path, return true;
     *         false Otherwise return false.
     */
    bool IsOnRoute(const IdType _id) const;

    /**
     * @brief Calculate RoutePlace between current link and target link in route path.
     * @param [in] _current_id Link id.
     * @param [in] _target_id Target id.
     * @return return RoutePlace.
     */
    RoutePlace GetRoutePlace(const IdType _current_id, const IdType _target_id) const;

    /**
     * @brief Get first link on route path.
     * @return link id, if the routing path is empty, it will return 0.
     */
    IdType GetFirstLinkID() const;

    /**
     * @brief Get last link on route path.
     * @return link id, if the routing path is empty, it will return 0.
     */
    IdType GetLastLinkID() const;

    /**
     * @brief Get route path.
     * @return Route path.
     */
    const RouteQueue& GetRoutePath() const;

    /**
     * @brief Get route path.
     * @return Get reference of route path.
     */
    RouteQueue& GetRoutePath() noexcept;

    /**
     * @brief Get route item by link id.
     * @param [in] _id Link id.
     * @param [out] _item Route item.
     * @return true Success.
     *         false Failure.
     */
    bool GetRouteItem(const IdType _id, RouteItem& _item) const;

    /**
     * @brief Returns the number of elements in the route queue.
     * 
     * @return The number of elements in the route queue.
     */
    std::size_t GetCount() const;

    /**
     * @brief Returns a reference to the element at position n in the route queue container.
     * 
     * @param [in] i Position of an element in the container.
     * reutrn The element at the specified position in the route queue.
     */
    const RouteItem& operator [] (const std::size_t i) const;

    /**
     * @brief Set the Route State
     * 
     * @param state 
     */
    void SetRouteState(RouteState state);

    /**
     * @brief Get the Route State
     * 
     * @return RouteState 
     */
    RouteState GetRouteState() const;

    /**
     * @brief Set the Distance To Destination object
     * 
     */
    void SetDistanceToDestination(holo::float64_t);

    /**
     * @brief
     *
     * @return holo::float64_t
     */
    holo::float64_t GetDistanceToDestination() const;

    /**
     * @brief Set the Distance To Destination object
     * 
     */
    void SetDistanceToHdMapEnd(holo::float64_t hd_map_end_distance);

    /**
     * @brief
     *
     * @return holo::float64_t
     */
    holo::float64_t GetDistanceToHdMapEnd() const;

    /**
     * @brief Get the Link Ids from certain link id
     * 
     * @param from_link_id Certain link id
     * @param link_ids Get rested link ids
     * @return holo::bool_t True, succeed; false, otherwise
     */
    holo::bool_t GetLinkIds(IdType const from_link_id, std::vector<IdType>& link_ids);

    /**
     * @brief Track another route info
     * 
     * @param other Another route info
     * @return holo::bool_t True, matched and able truck another routeinfo; 
     *                      false, cannot truck another routeinfo
     */
    holo::bool_t Track(RouteInfo2 const& other);

    /**
     * @brief Whether or not has link id
     */ 
    holo::bool_t HasLinkId(IdType const id);

private:
    RouteHash route_hash_map_;
    RouteQueue route_queue_;

    IdType original_link_id_ = 0UL;
    IdType destination_link_id_ = 0UL;

    std::size_t id_generator_ = 0UL;
    RouteState  route_state_;
    /// Distance to destination
    holo::float64_t distance_to_destination_ = -1.0f;
    /// Distance to hdmap's end(at current timestramp)
    holo::float64_t distance_to_hdmap_end_ = -1.0f;
};
}
}
#endif //HOLO_MAP_FEATURE_NAVIGATOR_ROUTER_ROUTE_INFO_H_
