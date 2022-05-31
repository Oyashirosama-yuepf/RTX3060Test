/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file timediff_utils.h
 * @brief This header file define timediff classes
 * @author guoguangchao@holomatic.com
 * @date 2022-02-19
 */

#ifndef _HOLO_CMW_APPS_UTILS_TIMEDIFF_UTILS_H
#define _HOLO_CMW_APPS_UTILS_TIMEDIFF_UTILS_H

#include <holo/sensors/format/holosync.h>
#include <holo/utils/yaml.h>
#include <holo_c/core/types.h>
#include <interface/interface_wrapper.h>
#include <atomic>
#include <exception>
#include <limits>

namespace holo_cmw
{
class TimediffBase
{
public:
    TimediffBase() noexcept : enable_(false), time_diff_(std::numeric_limits<int64_t>::min())
    {
    }

    virtual ~TimediffBase() = default;

    void SetEnable(bool enable) noexcept
    {
        enable_ = enable;
    }

    bool IsEnabled() const noexcept
    {
        return enable_;
    }

    bool IsInitialized() const noexcept
    {
        return time_diff_.load() != std::numeric_limits<int64_t>::min();
    }

    bool IsInitialized(int64_t value) const noexcept
    {
        return value != std::numeric_limits<int64_t>::min();
    }

    void SetValue(int64_t value) noexcept
    {
        time_diff_ = value;
    }

    int64_t GetValue() const noexcept
    {
        return time_diff_;
    }

protected:
    bool                 enable_;
    std::atomic<int64_t> time_diff_;
};

struct TimediffGetterParam
{
    TimediffGetterParam(const holo::yaml::Node& node)
    {
        if ((enable = node["enable"].as<bool_t>(false)))
        {
            param = holo::sensors::interface::UdpInterfaceParam(node);
        }
    }

    ~TimediffGetterParam() = default;

    bool                                        enable;
    holo::sensors::interface::UdpInterfaceParam param;
};

class TimediffGetter
{
public:
    using HoloSyncDiffPacket = holo::sensors::format::HoloSyncDiffPacket;
    using CallbackType       = std::function<void(int64_t)>;

    TimediffGetter(const TimediffGetterParam& param) noexcept : interface_{nullptr}, callback_{nullptr}
    {
        LOG(INFO) << "time compensation eanble = " << param.enable;
        if (param.enable)
        {
            interface_ = std::make_shared<UdpInterface<HoloSyncDiffPacket>>(param.param);
            std::function<void(const HoloSyncDiffPacket&)> h =
                std::bind(&TimediffGetter::TimediffCallback, this, std::placeholders::_1);
            interface_->InstallCallback(h);
        }
    }

    ~TimediffGetter() = default;

    void InstallCallback(const CallbackType& handler) noexcept
    {
        callback_ = handler;
    }

    void TimediffCallback(const HoloSyncDiffPacket& packet)
    {
        int64_t time_diff = packet.GetTimeDiff().ToNsec();
        if ((!packet.IsSourceValid()) || (!packet.IsTargetValid()))
        {
            time_diff = std::numeric_limits<int64_t>::min();
            LOG(ERROR) << "packet.IsHeaderValid() = " << packet.IsHeaderValid();
            LOG(ERROR) << "packet.IsSourceValid() = " << packet.IsSourceValid();
            LOG(ERROR) << "packet.IsTargetValid() = " << packet.IsTargetValid();
        }

        if (callback_)
        {
            callback_(time_diff);
        }
    }

private:
    std::shared_ptr<UdpInterface<HoloSyncDiffPacket>> interface_;
    CallbackType                                      callback_;
};

}  // namespace holo_cmw

#endif
