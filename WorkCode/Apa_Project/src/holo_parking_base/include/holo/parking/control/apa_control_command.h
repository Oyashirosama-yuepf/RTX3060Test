/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 *
 * @file apa_control_command.h
 * @brief This header file defines a control command for apa.
 * @author zhangchun(zhangchun@holomaitc.com)
 * @date 2021-01-11
 */

#ifndef HOLO_PARKING_CONTROL_APA_CONTROL_COMMAND_H_
#define HOLO_PARKING_CONTROL_APA_CONTROL_COMMAND_H_

#include <holo/common/timestamp.h>
#include <holo/core/types.h>

namespace holo
{
namespace parking
{
namespace control
{
/**
 * @brief This class defines control command for apa.
 *这个是针对广汽的一个，和control command是平行的，是一些控制和底层的接口，和以前用的control command有点不一样
 *以前control command是给底层发加速度，发前轮转角，但是广汽那个车不接受这些东西，它是针对apa接口的
 *相当于它自带一个lpc，只要告诉还有多少距离和目标点，它就会自动在目标点停下来
 *另一个不同点是它会接受一个方向盘转角而不是前轮转角
 * @details The ApaControlCommand contain longitudinal and lateral control command.
 */
class ApaControlCommand
{
public:
    /**
     * @brief default constructor
     */
    ApaControlCommand() noexcept
      : timestamp_()
      , lon_auto_mode_(false)
      , target_gear_request_(0)
      , stop_dist_request_(0.0)
      , speed_limit_request_(0.0)
      , apafail_brkmode_request_(0)
      , steer_auto_mode_(false)
      , steering_angle_(0.0)
    {
    }

    /* timestamp_ */
    Timestamp GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    void SetTimestamp(Timestamp const timestamp)
    {
        timestamp_ = timestamp;
    }

    /* lon_auto_mode_ */
    bool_t GetLonAutoMode() const noexcept
    {
        return lon_auto_mode_;
    }

    void SetLonAutoMode(bool_t lon_auto_mode) noexcept
    {
        lon_auto_mode_ = lon_auto_mode;
    }

    /* target_gear_request_ */
    uint8_t GetTargetGearRequest() const noexcept
    {
        return target_gear_request_;
    }

    void SetTargetGearRequest(uint8_t target_gear_request) noexcept
    {
        target_gear_request_ = target_gear_request;
    }

    /* stop_dist_request_ */
    float32_t GetStopDistRequest() const noexcept
    {
        return stop_dist_request_;
    }

    void SetStopDistRequest(float32_t stop_dist_request) noexcept
    {
        stop_dist_request_ = stop_dist_request;
    }

    /* speed_limit_request_ */
    float32_t GetSpeedLimitRequest() const noexcept
    {
        return speed_limit_request_;
    }

    void SetSpeedLimitRequest(float32_t speed_limit_request) noexcept
    {
        speed_limit_request_ = speed_limit_request;
    }

    /* apafail_brkmode_request_ */
    uint8_t GetApafailBrkmodeRequest() const noexcept
    {
        return apafail_brkmode_request_;
    }

    void SetApafailBrkmodeRequest(uint8_t apafail_brkmode_request) noexcept
    {
        apafail_brkmode_request_ = apafail_brkmode_request;
    }

    /* steer_auto_mode_ */
    bool_t GetSteerAutoMode() const noexcept
    {
        return steer_auto_mode_;
    }

    void SetSteerAutoMode(bool_t steer_auto_mode) noexcept
    {
        steer_auto_mode_ = steer_auto_mode;
    }

    /* steering_angle_ */
    float32_t GetSteeringAngle() const noexcept
    {
        return steering_angle_;
    }

    void SetSteeringAngle(float32_t steering_angle) noexcept
    {
        steering_angle_ = steering_angle;
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << timestamp_ << lon_auto_mode_ << target_gear_request_ << holo::serialization::align;
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        deserializer >> timestamp_ >> lon_auto_mode_ >> target_gear_request_ >> holo::serialization::align;
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return timestamp_.GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(lon_auto_mode_, target_gear_request_);
    }

private:
    holo::common::Timestamp timestamp_;  ///< timestamp

    bool_t    lon_auto_mode_;            ///< the enable for longiudinal control
    uint8_t   target_gear_request_;      ///< target gear
    float32_t stop_dist_request_;        ///< stop distance
    float32_t speed_limit_request_;      ///< speed limit
    uint8_t   apafail_brkmode_request_;  ///< emergency stop

    bool_t    steer_auto_mode_;  ///< the enable for steer control
    float32_t steering_angle_;   ///< the steer angle of vehicle [rad]
};

}  // namespace control
}  // namespace parking
}  // namespace holo

#endif
