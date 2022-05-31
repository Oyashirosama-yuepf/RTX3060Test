/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mpc2_spd_limit_sign.h
 * @brief This header file defines the structure of speed limit sign from bosch mpc.
 * @author zhangtongyang<zhangtongyang@holomatic.com>
 * @date 2021/12/30
 */

#ifndef HOLO_SENSORS_COMMON_BOSCH_MPC_SPD_LIMIT_SIGN_H_
#define HOLO_SENSORS_COMMON_BOSCH_MPC_SPD_LIMIT_SIGN_H_

#include <holo/common/coordinate.h>
#include <holo/common/extrinsic.h>
#include <holo/common/timestamp.h>
#include <holo/core/common.h>
#include <holo/core/types.h>
#include <holo/sensors/format/spd_limit_sign.h>

namespace holo
{
namespace sensors
{
namespace bosch_mpc
{
using holo::common::Timestamp;
class BoschMpcSpdLimitSign
{
public:
    BoschMpcSpdLimitSign()
      : pos_x_(0.0f)
      , pos_y_(0.0f)
      , pos_z_(0.0f)
      , stable_(false)
      , embedded_(0)
      , goodness_(0)
      , quality_(false)
      , vms_(false)
      , classfication_(0)
      , id_(0)
      , timestamp_(0, 0)
    {
    }

    BoschMpcSpdLimitSign(const BoschMpcSpdLimitSign& other) noexcept
      : pos_x_(other.pos_x_)
      , pos_y_(other.pos_y_)
      , pos_z_(other.pos_z_)
      , stable_(other.stable_)
      , embedded_(other.embedded_)
      , goodness_(other.goodness_)
      , quality_(other.quality_)
      , vms_(other.vms_)
      , classfication_(other.classfication_)
      , id_(other.id_)
      , timestamp_(other.timestamp_)
    {
    }

    BoschMpcSpdLimitSign& operator=(const BoschMpcSpdLimitSign& other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }
        pos_x_         = other.pos_x_;
        pos_y_         = other.pos_y_;
        pos_z_         = other.pos_z_;
        stable_        = other.stable_;
        embedded_      = other.embedded_;
        goodness_      = other.goodness_;
        quality_       = other.quality_;
        vms_           = other.vms_;
        classfication_ = other.classfication_;
        id_            = other.id_;
        timestamp_     = other.timestamp_;
    }

    void ConvertToHoloSpdLimtSign(holo::sensors::format::SpdLimitSign& output) const
    {
        output.SetId(id_);
        holo::geometry::Point3f position(pos_x_, pos_y_, pos_z_);
        output.SetPosition(position);
        output.SetTimestamp(timestamp_);
        if ((quality_) && (classfication_ > static_cast<uint8_t>(holo::sensors::format::SpdLimitSignClass::UNKNOWN)) &&
            (classfication_ <= static_cast<uint8_t>(holo::sensors::format::SpdLimitSignClass::SL105)))
        {
            output.SetConfidence(1.0f);
        }
        else
        {
            output.SetConfidence(0.0f);
        }
        output.SetClassification(static_cast<holo::sensors::format::SpdLimitSignClass>(classfication_));
    }

    inline void SetPosX(float32_t pos_x) noexcept
    {
        pos_x_ = pos_x;
    }

    inline float32_t GetPosX() const noexcept
    {
        return pos_x_;
    }

    inline void SetPosY(float32_t pos_y) noexcept
    {
        pos_y_ = pos_y;
    }

    inline float32_t GetPosY() const noexcept
    {
        return pos_y_;
    }

    inline void SetPosZ(float32_t pos_z) noexcept
    {
        pos_z_ = pos_z;
    }

    inline float32_t GetPosZ() const noexcept
    {
        return pos_z_;
    }

    inline void SetStable(bool_t stable) noexcept
    {
        stable_ = stable;
    }

    inline bool_t GetStable() const noexcept
    {
        return stable_;
    }

    inline void SetEmbedded(uint8_t embedded) noexcept
    {
        embedded_ = embedded;
    }

    inline uint8_t GetEmbedded() const noexcept
    {
        return embedded_;
    }

    inline void SetGoodness(uint8_t goodness) noexcept
    {
        goodness_ = goodness;
    }

    inline uint8_t GetGoodness() const noexcept
    {
        return goodness_;
    }

    inline void SetQuality(bool_t quality) noexcept
    {
        quality_ = quality;
    }

    inline bool_t GetQuality() const noexcept
    {
        return quality_;
    }

    inline void SetVms(bool_t vms) noexcept
    {
        vms_ = vms;
    }

    inline bool_t GetVms() const noexcept
    {
        return vms_;
    }

    inline void SetClassfication(uint8_t classfication) noexcept
    {
        classfication_ = classfication;
    }

    inline uint8_t GetClassfication() const noexcept
    {
        return classfication_;
    }

    inline void SetId(uint8_t id) noexcept
    {
        id_ = id;
    }

    inline uint8_t GetId() const noexcept
    {
        return id_;
    }

    inline void SetTimestamp(const holo::common::Timestamp& timestamp) noexcept
    {
        this->timestamp_ = timestamp;
    }

    inline holo::common::Timestamp GetTimestamp() const noexcept
    {
        return timestamp_;
    }

private:
    float32_t pos_x_;
    float32_t pos_y_;
    float32_t pos_z_;
    bool_t    stable_;
    uint8_t   embedded_;
    uint8_t   goodness_;
    bool_t    quality_;
    bool_t    vms_;
    uint8_t   classfication_;
    uint8_t   id_;
    Timestamp timestamp_;
};
}  // namespace bosch_mpc
}  // namespace sensors
}  // namespace holo

#endif