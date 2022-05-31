/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 *
 * @file pathpoint.h
 * @brief This header file defines pathpoint
 * @author fanhaowei(fanhaowei@holomaitc.com)
 * @date 2022-04-02
 */

#ifndef HOLO_PARKING_BASE_PLANNING_PATH_POINT_H_
#define HOLO_PARKING_BASE_PLANNING_POINT_H_

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
class PathPoint
{
public:
    /**
     * @brief default constructor
     */
    PathPoint() noexcept : timestamp_(), vmax_(0.0), curv_(0.0), x_(0.0), y_(0.0), yaw_(0.0), lamp_(0)
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

    /* vmax_ */
    float32_t GetVmax() const noexcept
    {
        return vmax_;
    }

    void SetVmax(float32_t const vmax)
    {
        vmax_ = vmax;
    }

    /* curv_ */
    float32_t GetCurv() const noexcept
    {
        return curv_;
    }

    void SetCurv(float32_t const curv)
    {
        curv_ = curv;
    }

    /* x_ */
    float32_t GetX() const noexcept
    {
        return x_;
    }

    void SetX(float32_t const x)
    {
        x_ = x;
    }

    /* y_ */
    float32_t GetY() const noexcept
    {
        return y_;
    }

    void SetY(float32_t const y)
    {
        y_ = y;
    }

    /* yaw_ */
    float32_t GetYaw() const noexcept
    {
        return yaw_;
    }

    void SetYaw(float32_t const yaw)
    {
        yaw_ = yaw;
    }

    /* lamp_ */
    uint8_t GetLamp() const noexcept
    {
        return lamp_;
    }

    void SetLamp(uint8_t const lamp)
    {
        lamp_ = lamp;
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
               holo::serialization::SerializedSize<ALIGN>(vmax_, curv_, x_, y_, yaw_, lamp_);
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
    holo::common::Timestamp timestamp_;  ///< timestamp

    float32_t vmax_;  ///< vamx
    float32_t curv_;  ///< cure
    float32_t x_;     ///< x
    float32_t y_;     ///< y
    float32_t yaw_;   ///< yaw
    uint8_t   lamp_;  ///< 0-no req; 1-left lamp; 2-right lamp; 3-both lamp
};

}  // namespace planning
}  // namespace parking
}  // namespace holo

#endif
