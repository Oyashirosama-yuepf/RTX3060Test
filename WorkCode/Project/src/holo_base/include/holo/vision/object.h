/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file object.h
 * @brief This class defines the point object.
 * @author liufangyuan(liufangyuan@holomaitc.com)
 * @date "2020-07-29"
 */

#ifndef HOLO_VISION_OBJECT_H_
#define HOLO_VISION_OBJECT_H_

#include <holo/common/classification.h>
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
 * @brief This class defines the point object.
 * @details An vision object can be expressed by bounding box, keypoints or segmentation and so on.
 * all can be expressed by many points, so give category, confidence and points to create a point object.
 *
 */

template <typename Point, size_t SIZE = 8>
class ObjectT : public holo::container::details::FixedSizeVectorBase<Point, SIZE>
{
public:
    static size_t const SIZE_VALUE = SIZE;

    using Classification = holo::common::Classification;
    using PointType      = Point;
    using Base           = holo::container::details::FixedSizeVectorBase<PointType, SIZE>;

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

    /**
     * @brief Default constructor
     */
    ObjectT() noexcept : Base(), category_(), confidence_(0.0f)
    {
    }

    /**
     * @brief Get the category of the current object
     *
     * @return Classification
     */
    Classification GetCategory() const noexcept
    {
        return category_;
    }

    /**
     * @brief Set the category of the current object
     *
     * @param category Category of current object
     */
    void SetCategory(const Classification& category)
    {
        category_ = category;
    }

    /**
     * @brief Get the category confidence of the current object
     *
     * @return float32_t
     */
    float32_t GetConfidence() const noexcept
    {
        return confidence_;
    }

    /**
     * @brief Set the category confidence of the current object
     *
     * @param confidence Category confidence of current object
     */
    void SetConfidence(const holo::float32_t confidence) noexcept
    {
        confidence_ = confidence;
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
        size_t aligned_size = holo::serialization::SerializedSize<ALIGN>(static_cast<uint32_t>(category_), confidence_,
                                                                         static_cast<uint32_t>(this->size()));
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
        serializer << holo::serialization::align << category_ << confidence_ << static_cast<uint32_t>(this->size())
                   << holo::serialization::align;
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
        uint32_t num_points = 0U;

        deserializer >> holo::serialization::align >> category_ >> confidence_ >> num_points >>
            holo::serialization::align;
        this->resize(num_points);
        for (auto& pt : (*this))
        {
            deserializer >> pt;
        }
    }

private:
    Classification category_{};    ///< category of the current object
    float32_t      confidence_{};  ///< category confidence of the current object
};

/**
 * @}
 *
 */

}  // namespace vision

}  // namespace holo

#endif  // !HOLO_VISION_OBJECT_H_
