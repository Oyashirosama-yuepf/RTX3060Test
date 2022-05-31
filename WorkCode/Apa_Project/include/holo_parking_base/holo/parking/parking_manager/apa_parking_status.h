/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 *
 * @file apa_event_request.h
 * @brief This header file defines apa event request
 * @author yuepengfei(yuepengfei@holomaitc.com)
 * @date 2022-05-23
 */
#ifndef HOLO_PARKING_BASE_APA_PARKING_STATE_H_
#define HOLO_PARKING_BASE_APA_PARKING_STATE_H_

namespace holo
{

namespace parking
{

namespace parking_manager
{

class APAParkingState {

public:  /// 枚举体定义，用于区分设置内容
    enum class ApaStateOutput : uint8_t
    {
        POWER_OFF = 0x00,
        STANDBY = 0x01,
        ACTIVE  = 0x02,
        APA_READY = 0x03,
        RUNNING = 0x04,
        SUCCESS = 0x05,
        SUSPEND = 0x06,
        INTERRUPTION = 0x07,
        EXIT = 0x08
    };

public:    /// 构造函数
    APAParkingState() noexcept
      : time_stamp_()
      , current_state_(ApaStateOutput::POWER_OFF)
      , last_state_(ApaStateOutput::POWER_OFF) {}
      
public:   /// 析构函数
    ~APAParkingState() = default;
    
private:
    holo::common::Timestamp time_stamp_;
    ApaStateOutput current_state_;
    ApaStateOutput last_state_;

public:   /// 中间件通信需求
    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return time_stamp_.GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(static_cast<uint8_t>(current_state_), 
               static_cast<uint8_t>(last_state_));
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        /* serialize data */
        serializer << time_stamp_ << static_cast<uint8_t>(current_state_) << 
        static_cast<uint8_t>(last_state_) << holo::serialization::align;
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        /* deserialize data */
        uint8_t current_state, last_state;
        deserializer >> time_stamp_ >> current_state >> last_state >> holo::serialization::align;
        current_state_ = static_cast<ApaStateOutput>(current_state);
        last_state_ = static_cast<ApaStateOutput>(last_state);
    }

public:   /// 私有变量对外的获取接口
    holo::common::Timestamp GetTimestamp() const noexcept {
        return time_stamp_;
    }
    uint8_t GetCurrentState() const noexcept {
        return static_cast<uint8_t>(current_state_);
    }
    uint8_t GetLastState() const noexcept {
        return static_cast<uint8_t>(last_state_);
    }


public:   /// 私有变量对外的赋值接口
    void SetTimestamp(holo::common::Timestamp const time_stamp) {
        time_stamp_ = time_stamp;
    }
    void SetCurrentState(uint8_t current_state) {
        current_state_ = static_cast<ApaStateOutput>(current_state);
    }
    void SetLastCurrentState(uint8_t last_state) {
        last_state_ = static_cast<ApaStateOutput>(last_state);
    }
};

}  // namespace system

}  // namespace parking

}  // namespace holo

#endif  /// HOLO_PARKING_BASE_APA_PARKING_STATE_H_
