/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 *
 * @file path_point.h
 * @brief This header file defines path_point
 * @author songbo(songbo@holomaitc.com)
 * @date 2022-04-07
 */

#ifndef HOLO_PARKING_BASE_PLANNING_PATH_POINT_H_
#define HOLO_PARKING_BASE_PLANNING_PATH_POINT_H_

#include <holo/common/timestamp.h>
#include <holo/core/types.h>

namespace holo
{
namespace parking
{
namespace planning
{
/**
 * @brief This class defines path point
 */
class Path_Point
{
public:
    /**
     * @brief default constructor
     */
    Path_Point() noexcept
      : timestamp_()
      , vmax_(0.0)
      , curv_(0.0)
      , x_(0.0)
      , y_(0.0)
      , yaw_(0.0)
      , lamp_(0)
    {
    }

    Timestamp GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    void SetTimestamp(Timestamp const value)
    {
        timestamp_ = value;
    }

    float GetVmax() const noexcept
    {
        return vmax_;
    }

    void SetVmax(float const value)
    {
        vmax_ = value;
    }

    float GetCurv() const noexcept
    {
        return curv_;
    }

    void SetCurv(float const value)
    {
        curv_ = value;
    }

    float GetX() const noexcept
    {
        return x_;
    }

    void SetX(float const value)
    {
        x_ = value;
    }

    float GetY() const noexcept
    {
        return y_;
    }

    void SetY(float const value)
    {
        y_ = value;
    }

    float GetYaw() const noexcept
    {
        return yaw_;
    }

    void SetYaw(float const value)
    {
        yaw_ = value;
    }

    uint8_t GetLamp() const noexcept
    {
        return lamp_;
    }

    void SetLamp(uint8_t const value)
    {
        lamp_ = value;
    }

    /**
     * @brief Get serialized size at give byte alignment value
     *
     * @tparam ALIGN Byte alignment value
     *
     * @return Serialized size
     */
    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return timestamp_.GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(timestamp_, vmax_, curv_, x_, y_, yaw_, lamp_);
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::serialization::SerializationBufferOverflowException if buffer size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        /* serialize data */
        serializer << timestamp_ << vmax_ << curv_ << x_ << y_ << yaw_ << lamp_ << holo::serialization::align;
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        /* deserialize data */
        deserializer >> timestamp_ >> vmax_ >> curv_ >> x_ >> y_ >> yaw_ >> lamp_ >> holo::serialization::align;
    }

private:
    holo::common::Timestamp timestamp_;
    float                   vmax_;
    float                   curv_;
    float                   x_;
    float                   y_;
    float                   yaw_;
    uint8_t                 lamp_;
};
}  // namespace planning
}  // namespace parking
}  // namespace holo

#endif
