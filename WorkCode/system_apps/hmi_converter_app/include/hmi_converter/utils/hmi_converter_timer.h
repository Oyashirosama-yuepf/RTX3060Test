/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file hmi_converter_timer.h
 * @brief This header file defines hmi converter timer class
 * @author yangzhongtao(yangzhongtao@holomatic.com)
 * @date 2021/09/15
 */

#ifndef HOLO_PARKING_HMI_CONVERTER_TIMER_H_
#define HOLO_PARKING_HMI_CONVERTER_TIMER_H_

#include <chrono>
#include <iostream>

namespace holo
{
namespace parking_cmw_app
{
namespace hmi_converter
{
class TimerClock
{
public:
    TimerClock() : is_working_(false)
    {
        start_ = std::chrono::high_resolution_clock::now();
    }

    ~TimerClock()
    {
    }

    void Start()
    {
        start_      = std::chrono::high_resolution_clock::now();
        is_working_ = true;
    }

    void Stop()
    {
        is_working_ = false;
    }

    void Update()
    {
        start_ = std::chrono::high_resolution_clock::now();
    }

    void SetStartSubtraction(std::chrono::seconds subtraction_value)
    {
        start_ = start_ - subtraction_value;
    }

    void SetStartSubtraction(std::chrono::milliseconds subtraction_value)
    {
        start_ = start_ - subtraction_value;
    }

    bool IsWorking() const
    {
        return is_working_;
    }

    int32_t GetTimerSecond() const
    {
        return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start_)
            .count();
    }

    int32_t GetTimerMilliSec() const
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_)
            .count();
    }

    int64_t GetTimerMicroSec() const
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start_)
            .count();
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_;
    bool                                                        is_working_;
};

}  // namespace hmi_converter
}  // namespace parking_cmw_app
}  // namespace holo

#endif
