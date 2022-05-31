/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_objects.h
 * @brief This class defines the image objects.
 * @author liufangyuan(liufangyuan@holomaitc.com)
 * @date "2020-07-30"
 */

#ifndef HOLO_VISION_IMAGE_OBJECTS_H_
#define HOLO_VISION_IMAGE_OBJECTS_H_

#include <holo/common/sensor_id.h>
#include <holo/common/timestamp.h>
#include <holo/container/details/fixed_size_vector.h>
#include <holo/core/types.h>
#include <holo/serialization/serialization.h>

namespace holo
{
namespace vision
{
/**
 * @addtogroup vision
 *
 * @{
 */

/**
 * @brief This class defines the image object.
 * @details An image frame have lots of objects,
 * creating an ImageObjects with timestamp, sensor_id and objects.
 *
 */

template <typename Object, size_t SIZE = 128>
class ImageObjectsT : public holo::container::details::FixedSizeVectorBase<Object, SIZE>
{
public:
    static size_t const SIZE_VALUE = SIZE;

    using ObjectType = Object;
    using Base       = holo::container::details::FixedSizeVectorBase<ObjectType, SIZE>;

    using Base::FixedSizeVectorBase;
    using value_type             = typename Base::value_type;
    using allocator_type         = typename Base::allocator_type;
    using size_type              = typename Base::size_type;
    using difference_type        = typename Base::difference_type;
    using reference              = typename Base::reference;
    using const_reference        = typename Base::const_reference;
    using pointer                = typename Base::pointer;
    using const_pointer          = typename Base::const_pointer;
    using iterator               = typename Base::iterator;
    using const_iterator         = typename Base::const_iterator;
    using reverse_iterator       = typename Base::reverse_iterator;
    using const_reverse_iterator = typename Base::const_reverse_iterator;
    using Timestamp              = holo::common::Timestamp;
    /**
     * @brief Default constructor
     */
    ImageObjectsT() noexcept : Base(), timestamp_(), sensor_id_()
    {
    }

    /**
     * @brief Get the Timestamp of current image frame
     *
     * @return const Timestamp&
     */
    const Timestamp& GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    /**
     * @brief Get the Timestamp of current image frame
     *
     * @return Timestamp&
     */
    Timestamp& GetTimestamp() noexcept
    {
        return timestamp_;
    }

    /**
     * @brief Set the Timestamp of current image frame
     *
     * @param timestamp Timestamp of current image frame
     */
    void SetTimestamp(const Timestamp& timestamp)
    {
        timestamp_ = timestamp;
    }

    /**
     * @brief Get the SensorId of current image frame
     *
     * @return holo::common::SensorId
     */
    holo::common::SensorId GetSensorId() const noexcept
    {
        return sensor_id_;
    }

    /**
     * @brief Set the SensorId of current image frame
     *
     * @param sensor_id SensorId of the current image
     */
    void SetSensorId(const holo::common::SensorId& sensor_id)
    {
        sensor_id_ = sensor_id;
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
        size_t aligned_size =
            timestamp_.GetSerializedSize<ALIGN>() +
            holo::serialization::SerializedSize<ALIGN>(static_cast<uint32_t>(sensor_id_), static_cast<uint32_t>(this->size()));

        for (auto const& pt : (*this))
        {
            aligned_size += pt.template GetSerializedSize<ALIGN>();
        }
        return aligned_size;
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
        serializer << timestamp_ << sensor_id_ << static_cast<uint32_t>(this->size()) << holo::serialization::align;
        for (auto const& pt : (*this))
        {
            serializer << pt;
        }
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
        uint32_t num_objects = 0U;
        deserializer >> timestamp_ >> sensor_id_ >> num_objects >> holo::serialization::align;
        this->resize(num_objects);
        for (auto& pt : (*this))
        {
            deserializer >> pt;
        }
    }

private:
    Timestamp        timestamp_;  ///< timestamp of the current image frame
    holo::common::SensorId sensor_id_;  ///< sensor_id of the current image frame
};

/**
 * @}
 *
 */

}  // namespace vision

}  // namespace holo

#endif  // !HOLO_VISION_IMAGE_OBJECTS_H_
