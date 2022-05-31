/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file smart_camera_app.h
 * @brief A driver for smart camera messages output
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/09/09
 */

#ifndef HOLO_CMW_APPS_SMART_CAMERA_APP_H
#define HOLO_CMW_APPS_SMART_CAMERA_APP_H

#include <cmw_wrapper/cmw_bus.h>
#include <holo/sensors/format/spd_limit_sign.h>
#include <holo/sensors/smart_camera/ifv300/ifv300_holocan.h>
#include <holo/sensors/smart_camera/ifv300/ifv300_someip.h>
#include <holo/sensors/smart_camera/matrix2/matrix2_holocan.h>
#include <holo/sensors/smart_camera/me3/me3_holocan.h>
#include <holo/sensors/smart_camera/me3/me3_someip.h>
#include <holo/sensors/smart_camera/me8/me8_holocan.h>
#include <holo/sensors/smart_camera/mpc2/mpc2_holocan.h>
#include <holo/sensors/smart_camera/mpc2/mpc2_someip.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <holo_base_msg/traits.h>
#include <interface/interface_wrapper.h>
#include <cmw_wrapper/utils/cxxopts.hpp>

namespace holo_cmw
{
using holo::sensors::SmartCameraDriverT;
static constexpr size_t SPD_SIGN_DATA_CAPACITY = 1024;

enum class SmtCameraMsgType : uint32_t
{
    OBSTACLES      = 0,
    ROADFRAME      = 1,
    SPD_LIMIT_SIGN = 2,
};

template <typename Td, typename Ti>
class SmartCameraApp
{
public:
    using SerializerType = holo::serialization::Serializer<false, 4>;
    using ObstacleType   = holo::obstacle::ObstacleVisionT<holo::float32_t>;
    using ObstaclePtrListType =
        holo::obstacle::ObstaclePtrListT<ObstacleType, holo::obstacle::VISION_OBSTACLE_LIST_COMMON_CAPACITY>;
    using ObstacleListCallbackType     = std::function<void(const ObstaclePtrListType&)>;
    using LaneboundaryType             = holo::common::LaneBoundary<holo::numerics::Polynomial<holo::float32_t, 3>>;
    using RoadFrameType                = holo::common::RoadFrame<holo::numerics::Polynomial<holo::float32_t, 3>, 8>;
    using RoadFrameCallbackType        = std::function<void(const RoadFrameType&)>;
    using SpdLimitSignType             = holo::sensors::format::SpdLimitSign;
    using SpdLimitSignListType         = std::array<SpdLimitSignType, 7>;
    using SpdLimitSignListCallbackType = std::function<void(const SpdLimitSignListType&)>;
    using LiveCallbackType             = std::function<void(uint32_t, uint32_t)>;
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  argc  The count of arguments
     * @param      argv  The arguments array
     * @param[in]  name  The name
     */
    SmartCameraApp(int32_t id, const std::string& ns) 
        : spd_sign_data_{}
        , frames_obstacles_(0)
        , frames_roadframe_(0)
        , frames_spd_limit_sign_(0)
        , thread_(nullptr)
        , live_callback_(nullptr)
    {
        bus_ = std::make_shared<cmw_wrapper::BusType>(id, ns);
    }

    SmartCameraApp(std::shared_ptr<cmw_wrapper::BusType> bus) 
        : bus_(bus)
        , spd_sign_data_{}
        , frames_obstacles_(0)
        , frames_roadframe_(0)
        , frames_spd_limit_sign_(0)
        , thread_(nullptr)
        , live_callback_(nullptr)
    {
    }
    /**
     * @brief      setup the node by config file
     *
     * @param[in]  config_file  The configuration file
     */
    void Setup(const std::string& config_file, bool_t blocking_mode = true);
    void InstallLiveCallback(const LiveCallbackType& handler) noexcept
    {
        live_callback_ = handler;
    }

    ~SmartCameraApp()
    {
        if (thread_ && thread_->joinable())
        {
            thread_->join();
        }
    }

private:
    /**
     * @brief      Gets the parameters.
     *
     * @param[in]  config_file  The configuration file
     *
     * @return     true for success, else false
     */
    bool GetParameters(const std::string& config_file);
    /**
     * @brief      callback for smart camera road frames, it sends cmw messages
     *
     * @param      publisher   The publisher to be used
     * @param[in]  road_frame  The road frame data from sensor driver
     */
    void RoadFrameCallback(const RoadFrameType& road_frame);
    /**
     * @brief      callback for smart camera obstacles, it sends cmw messages
     *
     * @param      publisher      The publisher
     * @param[in]  obstacle_list  The obstacle list
     */
    void ObstaclesCallback(const ObstaclePtrListType& obstacle_list);
    void SpdLimitSignCallback(const SpdLimitSignListType& spd_sign);
    void Background();

private:
    std::string                                           extrinsic_;
    std::string                                           roadframe_topic_;
    std::string                                           obstacles_topic_;
    std::string                                           spd_limit_sign_topic_;
    // cmw_wrapper::BusType                                  bus_;
    std::shared_ptr<cmw_wrapper::BusType>                 bus_;
    cmw_wrapper::BusType::WriterType<RoadFrameType>       roadframe_pub_;
    cmw_wrapper::BusType::WriterType<ObstaclePtrListType> obstacles_pub_;
    cmw_wrapper::BusType::WriterType<uint8_t*>            spd_limit_sign_pub_;
    std::shared_ptr<Ti>                                   interface_;
    std::shared_ptr<Td>                                   driver_;
    uint8_t                                               spd_sign_data_[SPD_SIGN_DATA_CAPACITY];
    std::atomic<uint32_t>                                 frames_obstacles_;
    std::atomic<uint32_t>                                 frames_roadframe_;
    std::atomic<uint32_t>                                 frames_spd_limit_sign_;
    std::shared_ptr<std::thread>                          thread_;
    LiveCallbackType                                      live_callback_;
};

}  // namespace holo_cmw

#endif
