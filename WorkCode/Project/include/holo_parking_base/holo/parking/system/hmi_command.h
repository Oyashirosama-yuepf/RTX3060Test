/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 *
 * @file hmi_command.h
 * @brief This header file defines hmi command
 * @author yuepengfei(yangzhongtao@holomaitc.com)
 * @date 2021-05-29
 */

#ifndef HOLO_PARKING_BASE_SYSTEM_HMI_COMMAND_H_
#define HOLO_PARKING_BASE_SYSTEM_HMI_COMMAND_H_

#include <holo/common/timestamp.h>
#include <holo/core/types.h>

namespace holo
{
namespace parking
{
namespace system
{
/**
 * @brief This class defines hmi command
 */
class HmiCommand
{
public:   /// 枚举体定义，用于区分设置内容
    enum class HmiCommandType : uint8_t {
        NO_COMMAND            = 0U,
        CANCEL_APA            = 1U,
        PAUSE_APA             = 2U,
        RESUME_APA            = 3U,
        ENABLE_APA            = 4U,
    };

    enum class HmiParkType : uint8_t {
        PARK_TYPE_UNDEFINED   = 0U,
        PARK_TYPE_APA = 1U,
    };

public:    /// 构造函数
    HmiCommand() noexcept
      : time_stamp_(), 
      command_ (HmiCommandType::NO_COMMAND), 
      park_type_ (HmiParkType::PARK_TYPE_UNDEFINED) {}

public:   /// 析构函数
    ~HmiCommand() = default;

private:   /// 私有变量定义，对外需要通过接口修改
    holo::common::Timestamp time_stamp_;  ///< timestamp
    HmiCommandType command_;          // 
    HmiParkType    park_type_;

public:   /// 中间件通信需求

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return time_stamp_.GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(static_cast<uint8_t>(command_), static_cast<uint8_t>(park_type_));
    }


    template <typename S>
    void Serialize(S& serializer) const
    {
        /* serialize data */
        serializer << time_stamp_ << static_cast<uint8_t>(command_) << static_cast<uint8_t>(park_type_)
         << holo::serialization::align;
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        /* deserialize data */
        uint8_t command, park_type;
        deserializer >> time_stamp_ >> command >> park_type >> holo::serialization::align;
        command_ = static_cast<HmiCommandType>(command);
        park_type_ = static_cast<HmiParkType>(park_type);
    }


public:   /// 私有变量对外的获取接口
    holo::common::Timestamp GetTimestamp() const noexcept {
        return time_stamp_;
    }
    uint8_t GetHmiCommand() const noexcept {
        return static_cast<uint8_t>(command_);
    }
    uint8_t GetHmiParkType() const noexcept {
        return static_cast<uint8_t>(park_type_);
    }
public:   /// 私有变量对外的赋值接口
    void SetTimestamp(holo::common::Timestamp const time_stamp) {
        time_stamp_ = time_stamp;
    }
    void SetHmiCommand(uint8_t const command) {
        command_ = static_cast<HmiCommandType>(command);
    }
    void SetHmiParkType(uint8_t const park_type)
    {
        park_type_ = static_cast<HmiParkType>(park_type);
    }
};

}  // namespace system
}  // namespace parking
}  // namespace holo

#endif
