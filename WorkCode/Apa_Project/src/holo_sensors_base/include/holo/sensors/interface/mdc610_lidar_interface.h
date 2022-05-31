/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mdc610_lidar_interface.h
 * @brief define the mdc610 lidar interface class
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2021-07-03
 */

#ifndef HOLO_SENSORS_CMW_APP_INTERFACE_MDC610_LIDAR_INTERFACE_H
#define HOLO_SENSORS_CMW_APP_INTERFACE_MDC610_LIDAR_INTERFACE_H

#include <adsf/lidar_receive_base.h>
#include <holo/sensors/lidar/mdc610/mdc610_lidar_structure.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace sensors
{
namespace interface
{
struct Mdc610LidarInterfaceParam
{
public:
    Mdc610LidarInterfaceParam() = default;
    Mdc610LidarInterfaceParam(int32_t ins) : instance(ins)
    {
    }

public:
    int32_t instance;
};

class Mdc610LidarInterface
{
public:
    using LidarFrame   = holo::sensors::mdc610::huawei::LidarFrame<holo::sensors::mdc610::huawei::PointXYZIRT>;
    using CallbackType = std::function<void(std::shared_ptr<const LidarFrame>)>;

    Mdc610LidarInterface() = delete;
    Mdc610LidarInterface(const Mdc610LidarInterfaceParam& param);
    Mdc610LidarInterface(const holo::yaml::Node& node);
    ~Mdc610LidarInterface();

    void InstallCallback(const CallbackType& handler) noexcept
    {
        callback_ = handler;
    }

private:
    void Init(const Mdc610LidarInterfaceParam& param);
    void Thread();

private:
    bool                                     running_;
    int32_t                                  instance_;
    std::unique_ptr<Adsfi::LidarReceiveBase> proxy_;
    CallbackType                             callback_;
    std::shared_ptr<std::thread>             thread_;

private:
    static constexpr int32_t INSTANCEID_MIN = 3;
    static constexpr int32_t INSTANCEID_MAX = 7;
};

}  // namespace interface
}  // namespace sensors
}  // namespace holo

#endif
