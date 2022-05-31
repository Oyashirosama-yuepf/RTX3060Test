/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file keypoint3.h
 * @brief This header file defines .
 * @author lanshayun(lanshayun@holomatic.com)
 * @date "2022-04-06"
 */

#ifndef HOLO_VISION_KEYPOINT3_H_
#define HOLO_VISION_KEYPOINT3_H_

#include <assert.h>
#include <cmath>
#include <vector>

#include <holo/core/epsilon.h>
#include <holo/core/types.h>
#include <holo/geometry/point3.h>
#include <holo/serialization/serialization.h>

namespace holo
{
namespace vision
{
template <typename T>
class KeyPoint3T : public holo::geometry::Point3T<T>
{
public:
    using ScalarType                = T;
    using KeyPoint3Type             = KeyPoint3T<ScalarType>;
    using Base                      = holo::geometry::Point3T<ScalarType>;
    using EpsilonType[[deprecated]] = EpsilonT<ScalarType>;

    KeyPoint3T() noexcept : Base{}, confidence_{0.0f}, visibility_{false}
    {
    }

    KeyPoint3T(ScalarType const x, ScalarType const y, ScalarType const z, holo::float32_t const confidence,
               holo::bool_t const visibility) noexcept
      : Base{x, y, z}, confidence_{confidence}, visibility_{visibility}
    {
    }

    KeyPoint3T(KeyPoint3T const& keypoint3) noexcept
      : Base{keypoint3.GetX(), keypoint3.GetY(), keypoint3.GetZ()}
      , confidence_{keypoint3.confidence_}
      , visibility_{keypoint3.visibility_}
    {
    }

    ~KeyPoint3T() noexcept
    {
        static_assert(std::is_arithmetic<ScalarType>::value, "KeyPoint3T need take arthimetic");
    }

    KeyPoint3Type& operator=(KeyPoint3Type const& other) noexcept
    {
        this->SetX(other.GetX());
        this->SetY(other.GetY());
        this->SetZ(other.GetZ());
        confidence_ = other.confidence_;
        visibility_ = other.visibility_;
        return *this;
    }

    bool_t operator==(KeyPoint3Type const& other) const noexcept
    {
        if (!ScalarEqualT<ScalarType>()(this->GetX(), other.GetX()))
        {
            return false;
        }

        if (!ScalarEqualT<ScalarType>()(this->GetY(), other.GetY()))
        {
            return false;
        }

        if (!ScalarEqualT<ScalarType>()(this->GetZ(), other.GetZ()))
        {
            return false;
        }

        if (!ScalarEqualT<holo::float32_t>()(confidence_, other.confidence_))
        {
            return false;
        }

        if (visibility_ != other.visibility_)
        {
            return false;
        }

        return true;
    }

    ScalarType DistSqr(KeyPoint3T const& target) const noexcept
    {
        const ScalarType dx = (this->GetX() - target.GetX()), dy = (this->GetY() - target.GetY()),
                         dz = (this->GetZ() - target.GetZ());
        return (dx * dx) + (dy * dy) + (dz * dz);
    }

    ScalarType Dist(KeyPoint3T const& target) const noexcept
    {
        return std::sqrt(DistSqr(target));
    }

    void SetConfidence(holo::float32_t const confidence) noexcept
    {
        confidence_ = confidence;
    }

    void SetVisibility(holo::bool_t const visibility) noexcept
    {
        visibility_ = visibility;
    }

    holo::float32_t GetConfidence() const noexcept
    {
        return confidence_;
    }

    holo::bool_t IsVisible() const noexcept
    {
        return visibility_;
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
        return Base::template GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(confidence_, visibility_);
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
        Base::Serialize(serializer);
        serializer << confidence_ << (uint8_t)visibility_ << holo::serialization::align;
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
        holo::uint8_t cur_visibility = 0U;
        Base::Deserialize(deserializer);
        deserializer >> confidence_ >> cur_visibility >> holo::serialization::align;
        visibility_ = static_cast<holo::bool_t>(cur_visibility);
    }

private:
    holo::float32_t confidence_;
    holo::bool_t    visibility_;
};

/**
 * @brief handy typedefs
 */
using KeyPoint3f        = KeyPoint3T<float32_t>;
using KeyPoint3d        = KeyPoint3T<float64_t>;
using KeyPoint3         = KeyPoint3T<float64_t>;
using ObjectKeyPoints3f = std::vector<KeyPoint3f>;
using ObjectKeyPoints3d = std::vector<KeyPoint3d>;
using ObjectKeyPoints3  = std::vector<KeyPoint3f>;
/**
 * @}
 */
}  // namespace vision
}  // namespace holo

#endif  // !HOLO_VISION_KEYPOINT3_H_
