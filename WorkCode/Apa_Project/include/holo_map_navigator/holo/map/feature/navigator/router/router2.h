/*!
 *  \brief Router, provide route related service
 *  \author Liu Qikang(liuqikang@holomatic.com)
 *  \date 2021-09-13
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for terms of copyright notice.
 */
#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ROUTER_ROUTER2_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ROUTER_ROUTER2_H_

#include <memory>
#include <string>
#include <vector>

#include <holo/map/common/common_define.h>
#include <holo/map/feature/navigator/navigator_config.h>
#include <holo/map/feature/navigator/router/prediction/routing_prediction.h>
#include <holo/map/feature/navigator/router/route_info.h>
#include <holo/os/tictoc_timer.h>

namespace holo
{
namespace map
{
/**
 * @addtogroup map
 *
 * @{
 */

/**
 * @brief Router config information.
 */
class RouterConfig
{
public:
    using RouteConfig        = navigator::config::RouteProperty;
    using FixedRouteConfig   = navigator::config::RoutingPathManager;
    using PredictRouteConfig = navigator::config::RoutingPredictProperty;
    using SDSpecificRoute    = navigator::config::SDNavigationProperty;
    using SingleFixedRoute   = navigator::config::RoutingPath;

public:
    RouterConfig()  = default;
    ~RouterConfig() = default;

    /**
     * @brief Assign router config.
     *
     * @param[in] router_config: Router config.
     */
    void SetRouteConfig(RouteConfig const& router_config);

    /**
     * @brief Get fixed router config.
     * @return Fixed router config.
     */
    FixedRouteConfig const& GetFixedRoute() const noexcept;

    /**
     * @brief Get fixed router config.
     * @param [in] route_index: Route index.
     * @return Single route config.
     */
    SingleFixedRoute const& GetSingleFixedRoute(holo::int32_t const route_index) const;

    /**
     * @brief Get predict route.
     * @return Predict route.
     */
    PredictRouteConfig const& GetPredictRoute() const noexcept;

    /**
     * @brief Get SD specific route.
     * @return SD specific route.
     */
    SDSpecificRoute const& GetSDSPecificRoute() const noexcept;

    /**
     * @brief Whether fixed router used.
     * @return True: If active. False: inactive.
     */
    holo::bool_t IsFixedRouteActive() const;

    /**
     * @brief Whether predict router used.
     * @return True: If active. False: inactive.
     */
    holo::bool_t IsPredictRoute() const;

    /**
     * @brief Whether sd navigation used.
     * @return True: If active. False: inactive.
     */
    holo::bool_t IsSDSpecificRoute() const;

private:
    RouteConfig router_config_;
};

/**
 * @brief Router v2.0.
 */
class Router2
{
public:
    using RouterConfigSPtr = std::shared_ptr<RouterConfig>;

    /**
     * @brief Definition of router status.
     */
    struct RouterStatus
    {
        enum class Status
        {
            ROUTING_USER_SELECTED  = 0,
            ROUTING_SYSTEM_PREDICT = 1,
            ROUTING_SD_SPECIFIED   = 2
        };
        Status        status      = Status::ROUTING_SYSTEM_PREDICT;
        mutable holo::int32_t route_index = 0;
    };

    /**
     * @brief Definition of router input.
     */
    struct Input
    {
        RouterStatus router_status;
        MapMatchInfo match_info;
    };

    /**
     * @brief Definition of router output.
     */
    struct Output
    {
        RouteInfo2::Ptr route_info = nullptr;
        holo::bool_t    on_route   = false;
    };

public:
    /**
     * @brief Default Constructor.
     */
    Router2() = default;
    ~Router2() = default;
    Router2(const Router2&)  = delete;
    Router2(const Router2&&) = delete;
    Router2& operator=(const Router2&) = delete;
    Router2& operator=(Router2&&) = delete;

    /**
     * @brief Initializer
     *
     * @param [in] ptr_ret pointer of retriever
     * @param [in] router_config pointer of router config
     * @return true
     * @return false
     */
    holo::bool_t Init(const RetrieverSPType ptr_ret);

    /**
     * @brief Router reset.
     */
    void Reset();

    /**
     * @brief Assign verbose flag.
     *
     * @param[in] v: True: print detail debug logs.
     *            False: close detail debug logs(default value).
     */
    void SetVerbose(holo::bool_t const v);

    /**
     * @brief Access verbose flag.
     *
     * @return Verbose flag.
     */
    holo::bool_t GetVerbose() const noexcept;

    /**
     * Calculate, predict and update route.
     * @param [in] input Router input.
     * @param [out] output Route info.
     * @return true Success, false Failure.
     */
    holo::bool_t Run(Router2::Input const& input, Output& output);

    /**
     * @brief Get status of route
     * @return Status
     */
    RouterStatus const& GetRouterStatus() const noexcept;

private:
    /**
     * @brief Predict main road on the front 2000 meters.
     * @param [in] _link_id Current link id from MapMatcher.
     * @return true Success;
     *         false Failure.
     */
    holo::bool_t PredictRoute(IdType const _link_id);

    /**
     * @brief Predict route.
     * @param [in] _link_id Current link id.
     * @return true
     *         false
     */
    holo::bool_t MakeRouteInfoByPredict(IdType const _link_id);

    /**
     * @brief Check status and log
     *
     * @param[in] choice Current route choice.
     * @param[in] link_id Current link id.
     * @param[in] result
     * @param[in] status
     * @return true
     * @return false
     */
    holo::bool_t CheckFeedback(holo::int32_t const _choice, IdType const _link_id, RouteInfo2::Ptr& _result,
                               holo::bool_t _status);

    holo::bool_t initializeFixedRoutePaths();

private:
    /// Whether router is initialized successfully or not
    holo::bool_t is_initialized_ = false;
    /// Verbose flag
    holo::bool_t verbose_ = true;
    /// Pointer of retriever
    RetrieverSPType ptr_ret_ = nullptr;
    /// Pointer of routing predict
    PtrRoutingPredict ptr_routing_predict_ = nullptr;
    /// Pointer of route config
    RouterConfigSPtr ptr_route_config_ = nullptr;
    /// Route Choice
    RouterStatus route_status_;
    /// route info
    RouteInfo2::Ptr route_ = nullptr;
    /// time elapsed
    holo::TicTocTimer tic_toc_timer_;
    /// routing paths
    std::map<holo::uint32_t, std::vector<holo::uint64_t>> alternative_routes_;
    /// Whether or not the alternative routes has been initialized
    holo::bool_t alternative_routes_initialized_ = false;
};

using Router2SPtr = std::shared_ptr<Router2>;

/**
 * @}
 */
}  //< namespace map
}  //< namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ROUTER_ROUTER2_H_ */