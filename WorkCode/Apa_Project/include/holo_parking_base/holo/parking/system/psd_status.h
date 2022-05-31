
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
 * @date 2022-05-24
 */

#ifndef HOLO_PARKING_BASE_SYSTEM_PSD_STATUS_H_
#define HOLO_PARKING_BASE_SYSTEM_PSD_STATUS_H_

#include <holo/common/timestamp.h>
#include <holo/core/types.h>

namespace holo
{

namespace parking
{

namespace system
{

class PsdStatus
{
public:   /// 枚举体定义，用于区分设置内容
public:   /// 构造函数
    PsdStatus() noexcept
    : slot_state_(0),
      slot_node_state_(0),
      app_run_state_(0) {}

public:   /// 析构函数
    ~PsdStatus() = default;

private:  /// 私有变量定义，对外需要通过接口修改
    uint8_t slot_state_;
    uint8_t slot_node_state_;
    uint8_t app_run_state_;

public:  /// 中间件通信需求
    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return holo::serialization::SerializedSize<ALIGN>(slot_state_, slot_node_state_, app_run_state_);
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        /* serialize data */
        serializer << slot_state_ << slot_node_state_ << app_run_state_ << holo::serialization::align;
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        /* deserialize data */
        deserializer >> slot_state_ >> slot_node_state_ >> app_run_state_ >> holo::serialization::align;
    }

public:   /// 私有变量对外的获取接口
    uint8_t GetSlotState() const noexcept {
        return slot_state_;
    }

    uint8_t GetSlotNodeState() const noexcept {
        return slot_node_state_;
    }

    uint8_t GetAppRunState() const noexcept {
        return app_run_state_;
    }
public:   /// 私有变量对外的赋值接口
    void SetSlotState(uint8_t slot_state) {
        slot_state_ = slot_state;
    }

    void SetSlotNodeState(uint8_t slot_node_state) {
        slot_node_state_ = slot_node_state;
    }

    void SetAppRunState(uint8_t app_run_state) {
        app_run_state_ = app_run_state;
    }
};


}  // namespace system
}  // namespace parking
}  // namespace holo

#endif   /// HOLO_PARKING_BASE_SYSTEM_PSD_STATUS_H_
