/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file conti_radar_app.h
 * @brief A driver for conti radar messages output
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2019/12/12
 */

#include <cmw_wrapper/cmw_bus.h>
#include <holo/sensors/radar/ars408/ars408_holocan.h>
#include <holo/sensors/radar/ars408/ars408_someip.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <holo_base_msg/traits.h>
#include <holo_c/core/types.h>
#include <interface/interface_wrapper.h>
#include <cmw_wrapper/utils/cxxopts.hpp>

namespace holo_cmw
{
using holo::sensors::conti_radar::ContiRadarDriverT;

template <typename Td, typename Ti>
class RadarAppT
{
public:
    using ObstacleType     = holo::obstacle::ObstacleRadarT<holo::float32_t>;
    using ObstaclePtrList  = holo::obstacle::ObstaclePtrListT<ObstacleType, holo::obstacle::RADAR_OBSTACLE_LIST_COMMON_CAPACITY>;
    using LiveCallbackType = std::function<void(uint32_t, uint32_t)>;

    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  id    The identifier
     * @param[in]  ns    namespace
     */
    RadarAppT(int32_t id, const std::string& ns) 
      : frames_(0)
      , thread_(nullptr)
      , live_callback_(nullptr)
    {
        bus_ = std::make_shared<cmw_wrapper::BusType>(id, ns);
    }

    RadarAppT(std::shared_ptr<cmw_wrapper::BusType> bus) 
      : bus_(bus)
      , frames_(0)
      , thread_(nullptr)
      , live_callback_(nullptr)
    {
    }

    ~RadarAppT()
    {
        if (thread_ && thread_->joinable())
        {
            thread_->join();
        }
    }
    /**
     * @brief      set up app configuration file
     *
     * @param[in]  config_file  The configuration file
     */
    void Setup(const std::string& config_file, bool_t blocking_mode = true);
    void InstallLiveCallback(const LiveCallbackType& handler) noexcept
    {
        live_callback_ = handler;
    }

private:
    /**
     * @brief      Gets the parameters from config file
     *
     * @param[in]  config_file  The configuration file
     *
     * @return     true for success, else false
     */
    bool_t GetParameters(const std::string& config_file);
    /**
     * @brief      obstacle callback routine
     *
     * @param      publisher      The publisher will be used
     * @param[in]  obstacle_list  The target obstacle list from lowlevel driver
     */
    void ObstaclesCallback(const ObstaclePtrList& obstacle_list);
    void Background();

private:
    /* variables */
    // cmw_wrapper::BusType                              bus_;
    std::shared_ptr<cmw_wrapper::BusType>             bus_;
    std::string                                       extrinsic_;
    std::string                                       obstacles_topic_;
    #ifdef CMW_WRAPPER_ENABLE_ROS
    cmw_wrapper::BusType::WriterType<ObstaclePtrList,ros_wrapper::DefaultConversionTraits<ObstaclePtrList>> obstacles_pub_;
    #else
    cmw_wrapper::BusType::WriterType<ObstaclePtrList> obstacles_pub_;
    #endif // DEBUG
    
    std::shared_ptr<Td>                               driver_;
    std::shared_ptr<Ti>                               interface_;
    std::atomic<uint32_t>                             frames_;
    std::shared_ptr<std::thread>                      thread_;
    LiveCallbackType                                  live_callback_;
};

}  // namespace holo_cmw
