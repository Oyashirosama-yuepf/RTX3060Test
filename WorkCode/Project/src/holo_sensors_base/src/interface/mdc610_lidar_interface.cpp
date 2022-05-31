/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mdc610_lidar_interface.cpp
 * @brief define the mdc610 lidar interface class
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2021-07-03
 */

#include <holo/log/hololog.h>
#include <holo/sensors/interface/mdc610_lidar_interface.h>
#include <exception>

namespace holo
{
namespace sensors
{
namespace interface
{
Mdc610LidarInterface::Mdc610LidarInterface(const Mdc610LidarInterfaceParam& param)
  : running_(true), instance_(-1), proxy_(nullptr), callback_(nullptr), thread_(nullptr)
{
    Init(param);
}

Mdc610LidarInterface::Mdc610LidarInterface(const holo::yaml::Node& node)
  : running_(true), instance_(-1), proxy_(nullptr), callback_(nullptr), thread_(nullptr)
{
    Mdc610LidarInterfaceParam param;
    try
    {
        param.instance = node["instance"].as<int32_t>();
    }
    catch (const std::exception& e)
    {
        std::ostringstream oss;
        oss << "mdc610 lidar interface failed: " << e.what();
        LOG(ERROR) << oss.str();
        throw std::runtime_error(oss.str());
    }
    Init(param);
}

void Mdc610LidarInterface::Init(const Mdc610LidarInterfaceParam& param)
{
    LOG(INFO) << "instance = " << param.instance;
    if ((param.instance < INSTANCEID_MIN) || (param.instance > INSTANCEID_MAX))
    {
        std::ostringstream oss;
        oss << "mdc610 lidar instance id invalid: " << param.instance;
        LOG(ERROR) << oss.str();
        throw std::runtime_error(oss.str());
    }
    instance_ = param.instance;
    proxy_    = std::make_unique<Adsfi::LidarReceiveBase>(instance_);
    if (proxy_ == nullptr)
    {
        std::ostringstream oss;
        oss << "mdc610 lidar failed to create receive base";
        LOG(ERROR) << oss.str();
        throw std::runtime_error(oss.str());
    }
    thread_ = std::make_unique<std::thread>(&Mdc610LidarInterface::Thread, this);
}

void Mdc610LidarInterface::Thread()
{
#if (MDC610_VERSION_NUM == 20211231) || (MDC610_VERSION_NUM == 20220228)
    proxy_->StartFindService();
#else
    proxy_->Run();
#endif

    while (running_)
    {
#if (MDC610_VERSION_NUM == 20211231) || (MDC610_VERSION_NUM == 20220228)
        std::shared_ptr<const Adsfi::LidarFrame<Adsfi::PointXYZIRT>> data = proxy_->GetOneDataBlocking(1000);
        if (data != nullptr)
        {
            /* add more code here */
            if (callback_)
            {
                callback_(std::shared_ptr<const LidarFrame>(data, reinterpret_cast<const LidarFrame*>(data.get())));
            }
        }
#else
        if (proxy_->GetDataPtr()->isValid)
        {
            std::lock_guard<std::shared_timed_mutex> writerLock(*proxy_->GetMtxPtr());
            proxy_->GetDataPtr()->isValid = false;
            /* add more code here */
            if (callback_)
            {
                callback_(proxy_->GetDataPtr());
            }
        }
#endif
    }
}

Mdc610LidarInterface::~Mdc610LidarInterface()
{
    running_ = false;
    if (thread_ && thread_->joinable())
    {
        thread_->join();
    }
    if (proxy_ != nullptr)
    {
#if (MDC610_VERSION_NUM == 20211231) || (MDC610_VERSION_NUM == 20220228)
        proxy_->Stop();
#else
        proxy_->SetStopFlag(true);
#endif
    }
}

}  // namespace interface
}  // namespace sensors
}  // namespace holo
