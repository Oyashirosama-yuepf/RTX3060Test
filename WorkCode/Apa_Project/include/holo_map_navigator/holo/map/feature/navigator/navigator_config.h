/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file navigator_config.h
 * @brief Main function for navigator config
 * @author liuqikang@holomatic.com
 * @date "2021-09-02"
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_NAVIGATOR_CONFIG_H
#define HOLO_MAP_FEATURE_NAVIGATOR_NAVIGATOR_CONFIG_H

#include <memory>

#include <holo/utils/holo_root.h>

#include <holo/map/common/common_define.h>
#include <holo/map/common/common_type_define.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace config
{
/**
 * @addtogroup map
 *
 * @{
 */
// config path
static const std::string HOLO_MAP_CONFIG_PATH = ::holo::GetHoloConfigRootDirectory() + "/holo_map/";

/**
 * @brief Configuration for navigation
 * 
 */
struct NavigationConfig
{
    holo::uint16_t hz = 0U;
    std::string    topic_odometry;
    std::string    topic_navigatiion;
};

/**
 * @brief Point property of a route.
 */
struct RoutingPoint
{
    holo::uint64_t      link_id = 0;
    holo::uint64_t      lane_id = 0;
    holo::map::MapPoint point;
};

/**
 * @brief Geofence property for navigator config.
 */
struct GeofenceProperty
{
    std::string     map_data_directory_;
    holo::float64_t geofence_extractor_period       = 0.0;
    holo::float64_t geofence_extractor_search_range = 3000.0;
};

/**
 * @brief Routing prediction property for navigator config.
 */
struct RoutingPredictProperty
{
    holo::float64_t routing_prediction_period = 1.0 / 30.0;
    holo::bool_t    use_routing_prediction    = true;
    holo::float64_t routing_prediction_length = 2000.0;
};

/**
 * @brief SD navigation property from navigator config.
 */
struct SDNavigationProperty
{
    holo::bool_t is_sd_navigation = false;
};

/**
 * @brief Road type intervals property for navigator config.
 */
struct RoadTypeIntervalsProperty
{
    holo::float64_t road_type_interval_extractor_period       = 0.0;
    holo::float64_t road_type_interval_extractor_search_range = 3000.0;
};

/**
 * @brief Road attributes property for navigator config.
 */
struct RoadAttributesProperty
{
    using RoadAttributesSegments                  = std::vector<holo::float32_t>;
    holo::float32_t        road_attribtues_period = 0.0;
    RoadAttributesSegments road_attributes_segments;
};

/**
 * @brief Road attributes for ODM.
 */
struct RoadAttributorConfig
{
    GeofenceProperty          genfencce_property;
    RoadTypeIntervalsProperty road_type_intervlas_property;
    RoadAttributesProperty    road_attributes_property;
};

/**
 * @brief A routing path information for navigator config.
 */
class RoutingPath
{
public:
    using PathId           = holo::map::IdType;
    using PathIdVectorType = std::vector<PathId>;
    using PointVectorType  = std::vector<RoutingPoint>;

    /**
     * @brief Constructor
     */
    RoutingPath() = default;

    /**
     * @brief Destructor
     */
    ~RoutingPath() = default;

    /**
     * @brief Assign origin.
     *
     * @param[in] origin Start coord of a route.
     * @return Nothing.
     */
    void SetOrigin(RoutingPoint const& origin) noexcept;

    /**
     * @brief Get origin.
     *
     * @return Start coord of a route.
     */
    RoutingPoint const& GetOrigin() const noexcept;

    /**
     * @brief Assign destination.
     *
     * @param[in] destination End coord of a route.
     * @return Nothing.
     */
    void SetDestination(RoutingPoint const& destination) noexcept;

    /**
     * @brief Get destination.
     *
     * @return End coord of a route.
     */
    RoutingPoint const& GetDestination() const noexcept;

    /**
     * @brief Add pass_point.
     *
     * @param[in] pass_point Pass point of a route.
     * @return Nothing.
     */
    void Add(RoutingPoint const& pass_point);

    /**
     * @brief Clear pass_points.
     *
     * @return Nothing.
     */
    void Clear();

    /**
     * @brief Get pass_points.
     *
     * @return pass_points of a route.
     */
    PointVectorType const& GetPassPoints() const noexcept;

    /**
     * @brief Assign routing path.
     *
     * @param[in] routing_path Routing_path of a route.
     * @return Nothing.
     */
    void SetRouteLinkIds(PathIdVectorType const& routing_path) noexcept;

    /**
     * @brief Get routing_path.
     *
     * @return Routing_path of a route.
     */
    PathIdVectorType const& GetRouteLinkIds() const noexcept;

    /**
     * @brief Set the Index of route
     * 
     * @param idx Index of route
     */
    void SetIndex(holo::uint32_t const idx);

    /**
     * @brief Get index of current route
     * 
     * @return holo::uint32_t 
     */
    holo::uint32_t Index() const;

private:
    RoutingPoint     origin_;        // Origin point of a route.
    RoutingPoint     destination_;   // Destination point of a route.
    PointVectorType  pass_points_;   // Pass points of a route.
    PathIdVectorType routing_path_;  // Routing path id sequence of a route.
    holo::uint32_t   index_ = 0U;    // Routing index
};

/**
 * @brief Manage all routing path information for navigator config.
 */
class RoutingPathManager
{
public:
    using RoutingPathGroup = std::vector<RoutingPath>;

    /**
     * @brief Constructor
     */
    RoutingPathManager() = default;

    /**
     * @brief Destructor
     */
    ~RoutingPathManager() = default;

    /**
     * @brief Assign whether use route config.
     *
     * @param[in] use_route_config Whether use route config.
     * @return Nothing.
     */
    void SetIsActiveConfig(holo::bool_t const& use_route_config) noexcept;

    /**
     * @brief Get whether use route config.
     *
     * @return True or false.
     */
    holo::bool_t GetIsActiveConfig() const;

    /**
     * @brief Assign used route index.
     *
     * @param[in] use_route_index Used route index.
     * @return Nothing.
     */
    void SetActiveIndex(holo::int32_t const& use_route_index) noexcept;

    /**
     * @brief Get used route index.
     *
     * @return Used route index.
     */
    holo::int32_t GetActiveIndex() const noexcept;

    /**
     * @brief Add single route path.
     *
     * @param[in] route_path single route path.
     * @return Nothing.
     */
    void Add(RoutingPath const& route_path);

    /**
     * @brief Clear route path.
     *
     * @return Nothing.
     */
    void Clear();

    /**
     * @brief Assign used routing path group.
     *
     * @param[in] routing_path_group Used routing path group.
     * @return Nothing.
     */
    void SetRoutingPathGroup(RoutingPathGroup const& routing_path_group) noexcept;

    /**
     * @brief Get used routing path group.
     *
     * @return Used routing path group.
     */
    RoutingPathGroup const& GetRoutingPathGroup() const noexcept;

private:
    holo::bool_t     use_route_config_ = false;
    holo::int32_t    use_route_index_  = 0;
    RoutingPathGroup routing_path_group_;
};

/**
 * @brief Road speed limit information for navigator config.
 */
class TargetSpeedLimit
{
public:
    /**
     * @brief Definition of target road type,0:main road;1:ramp entrance;2:ramp exit;3:jct
     */
    enum class TargetType : holo::uint8_t
    {
        MainRoad     = 0,
        RampEntrance = 1,
        RampExit     = 2,
        Jct          = 3
    };

    /**
     * @brief Definition of speed limit.
     */
    struct SpeedLimit
    {
        TargetType    type        = TargetType::MainRoad;
        holo::bool_t  road_forced = false;
        holo::uint8_t max_speed   = 60;
        holo::uint8_t min_speed   = 0;
    };

public:
    /**
     * @brief Constructor
     */
    TargetSpeedLimit() = default;

    /**
     * @brief Destructor
     */
    ~TargetSpeedLimit() = default;

    /**
     * @brief Add speed limit.
     *
     * @param[in] speed_limit speed limit.
     * @return True or false.
     */
    void Add(SpeedLimit const& speed_limit);

    /**
     * @brief Clear speed limit.
     *
     * @return Nothing.
     */
    void Clear();

    /**
     * @brief Get speed limit.
     *
     * @return Speed limit of target.
     */
    SpeedLimit const& operator[](TargetType const& road_type) const;

private:
    std::vector<SpeedLimit> road_speed_limits_;
};

/**
 * @brief Route property from navigator config.
 */
struct RouteProperty
{
    RoutingPathManager     routing_path_manager;
    RoutingPredictProperty routing_predict_property;
    SDNavigationProperty   sd_navigation_property;
};

/**
 * @brief Navigator config information.
 */
class NavigatorConfig
{
public:
    NavigatorConfig();
    ~NavigatorConfig();

    NavigatorConfig(const NavigatorConfig&) = delete;
    NavigatorConfig& operator=(const NavigatorConfig&) = delete;
    NavigatorConfig(const NavigatorConfig&&)           = delete;
    NavigatorConfig& operator=(NavigatorConfig&&) = delete;

    /**
     * @brief Get route config.
     *
     * @return Route property.
     */
    RouteProperty const& GetRouteConfig() const noexcept;

    /**
     * @brief Get target SpeedLimit
     *
     * @return Target SpeedLimit
     */
    TargetSpeedLimit const& GetSpeedLimitConfig() const noexcept;

    /**
     * @brief Get road attributes for ODM.
     *
     * @return RoadAttributes.
     */
    RoadAttributorConfig const& GetRoadAttributorConfig() const noexcept;

    /**
     * @brief Get the Navigation Config
     * 
     * @return NavigationConfig const& 
     */
    NavigationConfig const& GetNavigationConfig() const noexcept;

    /**
     * @brief Load default configuration from root directory
     * 
     * @return holo::bool_t 
     */
    holo::bool_t LoadDefaultConfig();

    /**
     * @brief Load navigator configuration
     *
     * @param[in] config_path Path of config
     */
    holo::bool_t Load(std::string const& config_path);

private:
    class NavigatorConfigInner;
    std::unique_ptr<NavigatorConfigInner> inner_;
};

using NavigatorConfigSPtr = ::std::shared_ptr<NavigatorConfig>;

/**
 * @}
 */
}  //< namespace config
}  //< namespace navigator
}  //< namespace map
}  //< namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_NAVIGATOR_CONFIG_H */