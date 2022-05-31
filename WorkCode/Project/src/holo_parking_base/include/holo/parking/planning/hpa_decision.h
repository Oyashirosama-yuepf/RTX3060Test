/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 *
 * @file hpa_decision.h
 * @brief This header file defines decision
 * @author fanhaowei(fanhaowei@holomaitc.com)
 * @date 2022-04-02
 */

#ifndef __HOLO_PARKING_BASE_PLANNING_DECISION_H_
#define __HOLO_PARKING_BASE_PLANNING_DECISION_H_

#include <holo/common/timestamp.h>
#include <holo/core/types.h>

namespace holo
{
namespace parking
{
namespace planning
{
/**
 * @brief This class defines hpa decision
 */
class Decision
{
public:
    /**
     * @brief default constructor
     */
    Decision() noexcept : timestamp_(), brkflag_(0), brkdist_(0.0), speedlimit_(0.0)
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

    /* brkflag_ */
    uint8_t GetBrkFlag() const noexcept
    {
        return brkflag_;
    }

    void SetBrkFlag(uint8_t const brkflag)
    {
        brkflag_ = brkflag;
    }

    /* brkdist_ */
    float32_t GetBrkDist() const noexcept
    {
        return brkdist_;
    }

    void SetBrkDist(float32_t const brkdist)
    {
        brkdist_ = brkdist;
    }

    /* speedlimit_ */
    float32_t GetSpeedLimit() const noexcept
    {
        return speedlimit_;
    }

    void SetSpeedLimit(float32_t const speedlimit)
    {
        speedlimit_ = speedlimit;
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
               holo::serialization::SerializedSize<ALIGN>(brkflag_, brkdist_, speedlimit_);
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
        serializer << timestamp_ << brkflag_ << brkdist_ << speedlimit_ << holo::serialization::align;
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
        deserializer >> timestamp_ >> brkflag_ >> brkdist_ >> speedlimit_ >> holo::serialization::align;
    }

private:
    holo::common::Timestamp timestamp_;  ///< timestamp

    uint8_t   brkflag_;     ///< 0-NoBrk, 1-ComfortStop, 2-EmergencyStop
    float32_t brkdist_;     ///< break distance
    float32_t speedlimit_;  ///< speed limit
};

}  // namespace planning
}  // namespace parking
}  // namespace holo

#endif
