/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file v4l2_interface.h
 * @brief define the v4l2 interface class
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020-09-22
 */

#ifndef HOLO_SENSORS_CMW_APP_INTERFACE_V4L2_INTERFACE_H
#define HOLO_SENSORS_CMW_APP_INTERFACE_V4L2_INTERFACE_H

#include <holo/os/timer.h>
#include <holo/sensors/camera/image_structure.h>
#include <holo/sensors/interface/v4l2/v4l2_driver.h>
#include <holo/utils/yaml.h>
#include <holo_c/core/types.h>
#include <functional>
#include <mutex>
#include <thread>

namespace holo
{
namespace sensors
{
namespace interface
{
using holo::common::Timestamp;
using holo::sensors::camera::PixelType;
using holo::sensors::camera::StreamBuffer;

struct V4l2InterfaceParam
{
    std::string device_name;
    uint32_t    rows;
    uint32_t    cols;
    uint8_t     pixel_format;
    bool_t      trigger_mode;
    bool_t      exposure_ctrl;
    uint32_t    exposure_gain;
    uint32_t    exposure_value;
};

template <typename T>
class V4l2Interface
{
public:
    using BufferCallbackType            = std::function<void(const StreamBuffer&)>;
    using TimestampedBufferCallbackType = std::function<void(const StreamBuffer&, const Timestamp&)>;

    V4l2Interface() = delete;
    V4l2Interface(const V4l2InterfaceParam& param) : initialized_(false), timeout_(1000), running_(true)
    {
        Init(param);
    }

    V4l2Interface(const holo::yaml::Node& node) : initialized_(false), timeout_(1000), running_(true)
    {
        V4l2InterfaceParam param;
        try
        {
            param.device_name    = node["device_name"].as<std::string>();
            param.cols           = node["cols"].as<uint32_t>();
            param.rows           = node["rows"].as<uint32_t>();
            param.pixel_format   = node["pixel_format"].as<uint32_t>();
            param.trigger_mode   = node["trigger_mode"].as<bool_t>();
            param.exposure_ctrl  = node["exposure_ctrl"].as<bool_t>();
            param.exposure_gain  = node["exposure_gain"].as<uint32_t>();
            param.exposure_value = node["exposure_value"].as<uint32_t>();
        }
        catch (std::exception& e)
        {
            std::string info = "failed to load v4l2 configure parameters";
            LOG(ERROR) << info << ":" << e.what();
            throw std::runtime_error(info);
        }
        LOG(INFO) << "device_name    = " << param.device_name;
        LOG(INFO) << "cols           = " << param.cols;
        LOG(INFO) << "rows           = " << param.rows;
        LOG(INFO) << "pixel_format   = " << static_cast<uint32_t>(param.pixel_format);
        LOG(INFO) << "trigger_mode   = " << param.trigger_mode;
        LOG(INFO) << "exposure_ctrl  = " << param.exposure_ctrl;
        LOG(INFO) << "exposure_gain  = " << param.exposure_gain;
        LOG(INFO) << "exposure_value = " << param.exposure_value;
        Init(param);
    }

    ~V4l2Interface()
    {
        running_ = false;
        if (thread_ && thread_->joinable())
        {
            thread_->join();
        }
    }

    void InstallCallback(const BufferCallbackType& handler) noexcept
    {
        device_->SetCallback(handler);
    }

    void InstallCallback(TimestampedBufferCallbackType& handler) noexcept
    {
        device_->SetCallback(handler);
    }

private:
    void Init(const V4l2InterfaceParam& param)
    {
        param_ = param;
        try
        {
            device_ = std::make_shared<T>();
        }
        catch (const std::exception& e)
        {
            std::ostringstream oss;
            oss << "v4l2 interface constructor failed: " << e.what();
            LOG(ERROR) << oss.str();
            throw std::runtime_error(oss.str());
        }
        /* cteate thread */
        std::function<void()> handler = std::bind(&V4l2Interface::Thread, this);
        thread_                       = std::make_shared<std::thread>(handler);
    }

    void Configure()
    {
        LOG(INFO) << "----------------";
        holo::Timer timer(1.0f);
        while (running_)
        {
            timer.Start();
            if (!device_->Open(param_.device_name))
            {
                LOG(ERROR) << "failed to open device, will retry after 1s...";
                break;
            }
            LOG(INFO) << "open device successfully";
            if (!device_->Init(param_.cols, param_.rows, static_cast<PixelType>(param_.pixel_format)))
            {
                LOG(ERROR) << "failed to init device, will retry after 1s...";
                break;
            }
            LOG(INFO) << "init device successfully";
            if (param_.exposure_ctrl)
            {
                if (!device_->SetExposure(param_.exposure_value))
                {
                    LOG(ERROR) << "failed to set exposure.value, will retry after 1s...";
                    break;
                }
                LOG(INFO) << "init device successfully";
                if (!device_->SetGain(param_.exposure_gain))
                {
                    LOG(ERROR) << "failed to set exposure.gain, will retry after 1s...";
                    break;
                }
                LOG(INFO) << "init device successfully";
            }
            if (!device_->SetTrigger(param_.trigger_mode))
            {
                LOG(ERROR) << "failed to set trigger mode, will retry after 1s...";
                break;
            }
            LOG(INFO) << "set device trigger mode successfully";
            if (!device_->InitMmap())
            {
                LOG(ERROR) << "failed to init mmap, will retry after 1s...";
                break;
            }
            LOG(INFO) << "init device mmap successfully";
            /* finished */
            LOG(INFO) << "start to capture";
            device_->StartCapture();
            initialized_ = true;
            break;
        }
        /* delay if init failed */
        if (!initialized_)
        {
            timer.Stop();
        }
    }

    void Grab()
    {
        fd_set         fds;
        struct timeval tv;
        while (initialized_ && running_)
        {
            FD_ZERO(&fds);
            FD_SET(device_->GetFd(), &fds);
            /* Timeout. */
            tv.tv_sec  = static_cast<int32_t>(timeout_ / 1000);
            tv.tv_usec = static_cast<int32_t>((timeout_ % 1000) * 1000);
            int32_t r  = select(device_->GetFd() + 1, &fds, NULL, NULL, &tv);
            if (r == -1)
            {
                if (errno == EINTR)
                {
                    continue;
                }
                LOG(ERROR) << "failed to grab image: " << strerror(errno);
                initialized_ = false;
                break;
            }
            if (r == 0)
            {
                LOG(ERROR) << "failed to read image";
                initialized_ = false;
                break;
            }
            if (!device_->ReadFrame())
            {
                LOG(ERROR) << "failed to read frame: " << strerror(errno);
                initialized_ = false;
                break;
            }
        }
        device_->Close();
    }

    void Thread()
    {
        while (running_)
        {
            Configure();
            Grab();
        }
    }

private:
    bool_t                       initialized_;
    int32_t                      timeout_;
    bool_t                       running_;
    V4l2InterfaceParam           param_;
    std::shared_ptr<T>           device_;
    std::shared_ptr<std::thread> thread_;
};
}  // namespace interface
}  // namespace sensors
}  // namespace holo

#endif
