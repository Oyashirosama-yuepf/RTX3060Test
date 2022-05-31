/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file navigator2.h
 * @brief Main function for navigator
 * @author liuqikang@holomatic.com
 * @date "2021-08-30"
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_NAVIGATOR2_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_NAVIGATOR2_H_

#include <memory>

#include <holo/common/odometry.h>
#include <holo/map/advice.h>
#include <holo/map/common/common_define.h>
#include <holo/map/common/navigator_status.h>
#include <holo/map/common/status_code.h>
#include <holo/map/common/yaml_helper.h>
#include <holo/map/feature/map_attributor/attributor/attributor.h>
#include <holo/map/feature/navigator/advice/advice.h>
#include <holo/map/feature/navigator/advice/advisor.h>
#include <holo/map/feature/navigator/navigator_config.h>
#include <holo/map/feature/navigator/router/router2.h>
#include <holo/map/feature/navigator/service/road_frame_helper/road_frame_helper.h>
#include <holo/map/feature/navigator/time_control.h>
#include <holo/map/lane_path.h>
#include <holo/map/service/client/matcher/matcher.h>
#include <holo/map/service/client/router/router.h>
#include <holo/os/tictoc_timer.h>

namespace holo
{
namespace map
{
namespace navigator
{
/**
 * @addtogroup navigator
 *
 * @{
 */

/**
 * @brief Navigator v2.
 */
class Navigator2
{
public:
    using Ptr                     = std::shared_ptr<Navigator2>;
    using LaneItem                = holo::map::LaneItem;
    using LanePath                = holo::map::LanePathT<128U>;
    using LaneAdvice              = holo::map::AdviceT<32U, 128U>;
    using PtrLaneAdice            = std::shared_ptr<LaneAdvice>;
    using LaneAdviceSPtrType      = std::shared_ptr<LaneAdvice>;
    using AdviceSPtrType          = std::shared_ptr<advice::Advice2>;
    using ODMSPtrType             = std::shared_ptr<Attributor::Output>;
    using RetrieverSPtrType       = holo::map::service::client::engine::RetrieverSPtrType;
    using LocalMapOdometryType    = ::holo::common::LocalMapOdometryT<holo::float64_t, 16U>;
    using MatchingResultType      = LocalMapOdometryType::MatchingResult;
    using MatchingResultsType     = holo::container::Vector<MatchingResultType, 16U>;
    using NavigatorConfigSPtrType = std::shared_ptr<navigator::config::NavigatorConfig>;
    using NavigatorStatusType     = holo::map::navigator::NavigatorStatus;
    using OnMapStateType          = NavigatorStatusType::OnMapState;
    using OnRouteStateType        = NavigatorStatusType::OnRouteState;

    /**
     * @brief Definition of navigator2 input.
     */
    struct Input
    {
        /// Current timestamp.
        holo::common::Timestamp current_time;
        /// Fused odometry with current position.
        LocalMapOdometryType odo;
        /// Index for route choice, -1 is for no choice
        holo::int32_t route_choice_index = 0;
        /// Whether or not enable the expectation version 2
        holo::bool_t enable_beta_test = false;
        holo::bool_t enable_repairing    = false;
    };

    /**
     * @brief Definition of navigator2 output.
     */
    struct Output
    {
        /// Whether or not odm message has been updated
        holo::bool_t odm_message_updated = false;
        /// ODM message
        ODMSPtrType odm_message = nullptr;
        /// Whether or not lane advice has been updated
        holo::bool_t lane_advice_updated = false;
        /// The previous lane advices representing lane path
        PtrLaneAdice lane_advices = nullptr;
        /// Whether or not advice has been updated
        holo::bool_t advice_updated = false;
        /// New advice message
        AdviceSPtrType advice = nullptr;
    };

    /**
     * @brief Marshal the input to a JSON string.
     *
     * @param[in] input Input parameters.
     * @return A Json string.
     */
    static std::string FormatToString(Navigator2::Input const& input);

    /**
     * @brief Marshal the output to a JSON string.
     *
     * @param[in] ouput Output parameters.
     * @return A Json string.
     */
    static std::string FormatToString(Navigator2::Output const& output);

    /**
     * @brief Default Constructor.
     */
    Navigator2();

    /**
     * @brief Destructor
     */
    ~Navigator2();

    Navigator2(const Navigator2&) = delete;
    Navigator2(Navigator2&&)      = delete;

    Navigator2& operator=(const Navigator2&) = delete;
    Navigator2& operator=(Navigator2&&) = delete;

    /**
     * @brief 
     * 
     * @param map_local_retriever 
     * @param config_path 
     * @return holo::bool_t 
     */
    holo::bool_t Init(RetrieverSPType const map_local_retriever);

    /**
     * @brief Navigator Reset
     */
    void Reset();

    /**
     * @brief Access verbose flag.
     *
     * @return Verbose flag.
     */
    holo::bool_t GetVerbose() const noexcept;

    /**
     * @brief Assign verbose flag.
     *
     * @param[in] true: Print detail debug logs.
     *            false: Close detail debug logs(default value).
     */
    void SetVerbose(holo::bool_t const v) const;

    /**
     * @brief Make navigator infos.
     *
     * @param[in] input Input parameters.
     * @param[out] output Output parameters.
     * @return true: No error.
     *         false: An error occurs in this function, refer to logs
     *                for more details.
     */
    holo::bool_t Run(Navigator2::Input const& input, Navigator2::Output& output);

private:
    class Navigator2Inner;
    std::unique_ptr<Navigator2Inner> inner_;
};

/**
 * @}
 */
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_NAVIGATOR2_H_ */
