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

#ifndef HOLO_PARKING_BASE_SYSTEM_APA_EVENT_REQUEST_H_
#define HOLO_PARKING_BASE_SYSTEM_APA_EVENT_REQUEST_H_

#include <holo/common/timestamp.h>
#include <holo/core/types.h>

namespace holo
{
namespace parking
{
namespace system
{

class ApaEventRequest
{
public:   /// 枚举体定义，用于区分设置内容
    enum class Search_Method : uint8_t
    {
        SEARCHING            = 0U,
        BACKGROUND_SEARCHING = 1U,
    };

    enum class Park_Direction : uint8_t
    {
        BOTH_SIDE = 0U,
        LEFT_SIDE = 1U,
        RIGHT_SIDE = 2U,
    };

    enum class Slot_Direction : uint8_t
    {
        FREEDOM = 0U,
        BACK_TO_PARKING_POSITION = 1U,
        SLIDE_TO_PARKING_POSITION = 2U,
    };

public:    /// 构造函数
    ApaEventRequest() noexcept
      : time_stamp_()
      , event_id_(0)
      , enable_apa_(false)
      , search_method_(Search_Method::SEARCHING)
      , park_direction_(Park_Direction::BOTH_SIDE)
      , slot_direction_(Slot_Direction::FREEDOM) {}
      
public:   /// 析构函数
    ~ApaEventRequest() noexcept {}

private:   /// 私有变量定义，对外需要通过接口修改
    holo::common::Timestamp time_stamp_;  // 时间戳
    uint32_t event_id_;                   // 任务id，用于确定任务是否接受成功
    bool_t enable_apa_;                   // 使能apa功能；
    Search_Method search_method_;         // 搜索模式：0 搜索 1 后台搜索
    Park_Direction park_direction_;       // 车位方向：0 两侧搜索 1 左侧搜索 2 右侧搜索
    Slot_Direction slot_direction_;       // 泊入方向：0 无限制 1 倒车入库 2 侧方入库

public:   /// 中间件通信需求
    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return time_stamp_.GetSerializedSize<ALIGN>() + 
        holo::serialization::SerializedSize<ALIGN>(event_id_, enable_apa_, search_method_, park_direction_, slot_direction_);
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        /* serialize data */
        serializer << time_stamp_ << event_id_ << enable_apa_ << static_cast<uint8_t>(search_method_) << 
        static_cast<uint8_t>(park_direction_) << static_cast<uint8_t>(slot_direction_) << holo::serialization::align;
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        /* deserialize data */
        uint8_t search_method, park_direction, slot_direction;
        deserializer >> time_stamp_ >> event_id_ >> enable_apa_ >> search_method >> park_direction >> slot_direction >> holo::serialization::align;
        search_method_ = static_cast<Search_Method>(search_method);
        park_direction_ = static_cast<Park_Direction>(park_direction);
        slot_direction_ = static_cast<Slot_Direction>(slot_direction);
    }

public:   /// 私有变量对外的获取接口
    holo::common::Timestamp GetTimestamp() const noexcept {
        return time_stamp_;
    }
    uint32_t GetEventId() const noexcept {
        return event_id_;
    }
    bool_t GetEnableApaStatus() const noexcept {
        return enable_apa_;
    }
    uint8_t GetSearchMethod() const noexcept {
        return static_cast<uint8_t>(search_method_);
    }
    uint8_t GetParkDirection() const noexcept {
        return static_cast<uint8_t>(park_direction_) ;
    }
    uint8_t GetSlotDirection() const noexcept {
        return static_cast<uint8_t>(slot_direction_);
    }

public:   /// 私有变量对外的赋值接口
    void SetTimestamp(holo::common::Timestamp const time_stamp) {
        time_stamp_ = time_stamp;
    }
    void SetEventId(uint32_t const event_id) {
        event_id_ = event_id;
    }
    void SetEnableApaStatus(bool_t const enable_apa) {
        enable_apa_ = enable_apa;
    }
    void SetSearchMethod(uint8_t const search_method) {
        search_method_ = static_cast<Search_Method>(search_method);
    }
    void SetParkDirection(uint8_t const park_direction) {
        park_direction_ = static_cast<Park_Direction>(park_direction);
    }
    void SetSlotDirection(uint8_t const slot_direction) {
        slot_direction_ = static_cast<Slot_Direction>(slot_direction);
    }
};

}  // namespace system
}  // namespace parking
}  // namespace holo

#endif   /// HOLO_PARKING_BASE_SYSTEM_APA_EVENT_REQUEST_H_
