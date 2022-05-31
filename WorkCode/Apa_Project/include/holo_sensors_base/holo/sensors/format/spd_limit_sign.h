/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file spd_limit_sign.h
 * @brief define the speed limit sign structure format class
 * @author zhzangtongyang<zhzangtongyang@holomatic.com>
 * @date 2021-12-30
 */

#ifndef _HOLO_SENSORS_FORMAT_SPD_LIMIT_SIGN_H
#define _HOLO_SENSORS_FORMAT_SPD_LIMIT_SIGN_H

#include <holo/common/coordinate.h>
#include <holo/common/extrinsic.h>
#include <holo/common/timestamp.h>
#include <holo/core/common.h>
#include <holo/core/types.h>
#include <holo/sensors/format/format.h>
#include <holo/serialization/serialization.h>
#include <holo_c/core/static_assert.h>
#include <cstring>

namespace holo
{
namespace sensors
{
namespace format
{
using holo::common::Timestamp;
enum class SpdLimitSignClass : uint8_t
{
    UNKNOWN = 0,
    SL5,
    SL10,
    SL15,
    SL20,
    SL25,
    SL30,
    SL35,
    SL40,
    SL45,
    SL50,
    SL55,
    SL60,
    SL65,
    SL70,
    SL75,
    SL80,
    SL85,
    SL90,
    SL95,
    SL100,
    SL105,
};

class SpdLimitSign : public FormatBase
{
public:
    SpdLimitSign() noexcept
      : id_(0)
      , classification_(static_cast<uint8_t>(SpdLimitSignClass::UNKNOWN))
      , confidence_(0.0f)
      , position_(0.0f, 0.0f, 0.0f)
      , timestamp_(0, 0)
    {
    }

    inline void SetId(const uint8_t& id) noexcept
    {
        id_ = id;
    }

    inline uint8_t GetId() const noexcept
    {
        return id_;
    }

    inline void SetConfidence(const float32_t& confidence) noexcept
    {
        confidence_ = confidence;
    }

    inline float32_t GetConfidence() const noexcept
    {
        return confidence_;
    }

    inline void SetClassification(const SpdLimitSignClass& classification) noexcept
    {
        classification_ = static_cast<uint8_t>(classification);
    }

    inline SpdLimitSignClass GetClassification() const noexcept
    {
        return static_cast<SpdLimitSignClass>(classification_);
    }

    inline void SetPosition(const holo::geometry::Point3f& position) noexcept
    {
        position_ = position;
    }

    inline holo::geometry::Point3f GetPosition() const noexcept
    {
        return position_;
    }

    inline void SetTimestamp(const holo::common::Timestamp& timestamp) noexcept
    {
        this->timestamp_ = timestamp;
    }

    inline holo::common::Timestamp GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    uint32_t GetSerializedSize() const noexcept
    {
        return SIZE;
    }

    uint32_t Serialize(uint8_t* data, uint32_t bytes) const noexcept
    {
        if (bytes < SIZE)
        {
            return 0;
        }
        uint8_t                                  buffer[bytes];
        holo::serialization::Serializer<true, 4> serializer(buffer, bytes);
        serializer << id_ << classification_ << confidence_ << position_ << timestamp_ << holo::serialization::align;
        (void)std::memcpy(data, serializer.GetData(), bytes);

        return SIZE;
    }

    uint32_t Deserialize(const uint8_t* data, uint32_t bytes)
    {
        if (bytes < SIZE)
        {
            return 0;
        }
        holo::serialization::Deserializer<true, 4> deserializer(data, bytes);
        deserializer >> id_ >> classification_ >> confidence_ >> position_ >> timestamp_ >> holo::serialization::align;

        return bytes;
    }

private:
    uint8_t                 id_;
    uint8_t                 classification_;
    float32_t               confidence_;
    holo::geometry::Point3f position_;
    Timestamp               timestamp_;

private:
    static constexpr uint32_t SIZE = 4 + sizeof(confidence_) + sizeof(position_) + sizeof(timestamp_);
};
}  // namespace format
}  // namespace sensors
}  // namespace holo

#endif