/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file luminous_intensity.h
 * @brief This header file defines luminous intensity.
 * @author chengxiang(chengxiang@holomaitc.com)
 * @date 2021-07-30
 */

#ifndef HOLO_PARKING_BASE_SURROUNDING_LUMINOUS_INTENSITY_H_
#define HOLO_PARKING_BASE_SURROUNDING_LUMINOUS_INTENSITY_H_

#include <holo/common/timestamp.h>
#include <holo/core/types.h>

namespace holo
{
namespace parking
{
namespace surroundings
{
/**
 * @brief This class defines luminous intensity of the surroundings.
 */
class LuminousIntensity
{
public:
    LuminousIntensity() noexcept
        :timestamp_()
        ,intensity_(0.0)
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
    float32_t GetIntensity() const 
    {
        return intensity_;
    }

    void SetIntensity( float32_t intensity )
    {
        intensity_ = intensity;
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
                holo::serialization::SerializedSize<ALIGN>( intensity_ );
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
        serializer << timestamp_ << intensity_ << holo::serialization::align;
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
        deserializer >> timestamp_ >> intensity_ >> holo::serialization::align;
    }

private:
    holo::common::Timestamp timestamp_;  ///< timestamp

    float32_t               intensity_;  ///< intensity of luminous
};

}  // namespace surroundings
}  // namespace parking
}  // namespace holo

#endif
