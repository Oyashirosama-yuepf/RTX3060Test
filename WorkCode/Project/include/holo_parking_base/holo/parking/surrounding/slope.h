/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file slope.h
 * @brief This header file defines slope.
 * @author chengxiang(chengxiang@holomaitc.com)
 * @date 2021-07-31
 */

#ifndef HOLO_PARKING_BASE_SURROUNDING_SLOPE_H_
#define HOLO_PARKING_BASE_SURROUNDING_SLOPE_H_

#include <holo/common/timestamp.h>
#include <holo/core/types.h>

namespace holo
{
namespace parking
{
namespace surroundings
{
/**
 * @brief This class defines slope of the road in degree, great than 0 means uphill,
 *        conversely downhill
 */
class Slope
{
public:
    Slope() noexcept
        :timestamp_()
        ,slope_(0.0)
    {}

    /* timestamp_ */
    holo::common::Timestamp GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    void SetTimestamp(holo::common::Timestamp const timestamp)
    {
        timestamp_ = timestamp;
    }

    /* intensity_ */
    float32_t GetSlope() const noexcept
    {
        return slope_;
    }

    void SetSlope( float32_t slope )
    {
        slope_ = slope;
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
                holo::serialization::SerializedSize<ALIGN>( slope_ );
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
        serializer << timestamp_ << slope_ << holo::serialization::align;
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
        deserializer >> timestamp_ >> slope_ >> holo::serialization::align;
    }

private:
    holo::common::Timestamp timestamp_;  ///< timestamp

    float32_t               slope_;      ///< slope value
};

}  // namespace surroundings
}  // namespace parking
}  // namespace holo

#endif
