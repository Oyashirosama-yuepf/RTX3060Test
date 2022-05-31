/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file navigator_status.h
 * @brief Definition of navigator status container
 * @author yuhongbo(yuhongbo@holomatic.com)
 * @date 2021-12-06
 */

#ifndef HOLO_MAP_NAVIGATOR_COMMON_NAVIGATOR_STATUS__H_
#define HOLO_MAP_NAVIGATOR_COMMON_NAVIGATOR_STATUS__H_

#include <memory>

#include <holo/common/app_status.h>
#include <holo/map/common/classes/spin_mutex.h>
#include <holo/map/common/status_code.h>
namespace holo
{
namespace map
{
namespace navigator
{
/**
 * @addtogroup navigator
 * @{
 *
 */
#define ENUM_ON_MAP_STATE_TYPE                                                                                         \
    X(UNDEFINED)                                                                                                       \
    X(ON_HD_MAP)                                                                                                       \
    X(ON_SD_MAP)                                                                                                       \
    X(NOT_ON_MAP)

#define ENUM_ON_ROUTE_STATE_TYPE                                                                                       \
    X(UNDEFINED)                                                                                                       \
    X(ON_ROUTE)                                                                                                        \
    X(NOT_ON_ROUTE)

/**
 * @brief NavigatorStatus is a singleton queue container.
 */
class NavigatorStatus
{

public:
    using NavigatorStatusSPtrType = std::shared_ptr<NavigatorStatus>;

    enum class OnMapState : holo::uint8_t
    {
#define X(type) type,
        ENUM_ON_MAP_STATE_TYPE
#undef X
    };
    char const* const OnMapStateTypeName[4] = {
#define X(name) #name,
        ENUM_ON_MAP_STATE_TYPE
#undef X
    };

    enum class OnRouteState : holo::uint8_t
    {
#define X(type) type,
        ENUM_ON_ROUTE_STATE_TYPE
#undef X
    };
    char const* const OnRouteStateTypeName[3] = {
#define X(name) #name,
        ENUM_ON_ROUTE_STATE_TYPE
#undef X
    };

public:
    /**
     * @brief Access a global instance of NavigatorState container.
     *
     * @return Returns a instance of NavigatorState.
     */
    static NavigatorStatusSPtrType Instance();

    /**
     * @brief Set the On Map State 
     * 
     * @param state On Map state
     */
    void SetOnMapState(OnMapState const state);

    /**
     * @brief Get the On Map State
     * 
     * @return State for on map 
     */
    OnMapState const& GetOnMapState() const;

    /**
     * @brief Set the On Route State
     * 
     * @param state State for on route state
     */
    void SetOnRouteState(OnRouteState const state);

    /**
     * @brief Get the On Route State 
     * 
     * @return State for on route
     */
    OnRouteState const& GetOnRouteState() const;

private:
    NavigatorStatus()                       = default;
    NavigatorStatus(const NavigatorStatus&) = delete;
    NavigatorStatus(NavigatorStatus&&)      = delete;
    NavigatorStatus& operator=(const NavigatorStatus&) = delete;
    NavigatorStatus& operator=(NavigatorStatus&&) = delete;

    static NavigatorStatusSPtrType navigator_status_;

    /// State for on map
    OnMapState   on_map_state_ = OnMapState::UNDEFINED;
    /// State for on route
    OnRouteState on_route_state_ = OnRouteState::UNDEFINED;
};
} 
}  // namespace map
}  // namespace holo
#endif /* HOLO_MAP_NAVIGATOR_COMMON_NAVIGATOR_STATUS__H_ */