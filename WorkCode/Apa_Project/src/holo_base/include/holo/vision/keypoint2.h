/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file keypoint2.h
 * @brief This header file defines a single keypoint.
 * @author tanghui(tanghui@holomaitc.com)
 * @date 2019-12-05
 */

#ifndef HOLO_VISION_KEYPOINT2_H_
#define HOLO_VISION_KEYPOINT2_H_

#include <assert.h>
#include <cmath>
#include <vector>

#include <holo/core/epsilon.h>
#include <holo/core/types.h>
#include <holo/geometry/point2.h>
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

template <typename T>
using Point2T[[deprecated]] = holo::geometry::Point2T<T>;

/**
 * @brief This class defines a base class of object keypoint.
 *
 * @details This class defines a base class of object keypoint which is used for obstacle 2d to 3d coverting operation.
 */
template <typename T>
class KeyPoint2T : public holo::geometry::Point2T<T>
{
public:
    using Scalar                    = T;
    using KeyPoint2Type             = KeyPoint2T<Scalar>;
    using Base                      = Point2T<T>;
    using EpsilonType[[deprecated]] = EpsilonT<T>;

    /**
     * @brief Default Constructor
     */
    KeyPoint2T() noexcept : Base(), confidence_(0.0f), visibility_(false)
    {
    }
    /**
     * @brief Constrcutor with params
     *
     * @param x x value
     * @param y y value
     * @param confidence the confidence of point in 2d dimension
     * @param visibility the visibility of point in 2d dimension
     */
    KeyPoint2T(const Scalar x, const Scalar y, const holo::float32_t confidence, const holo::bool_t visibility) noexcept
      : Base(x, y), confidence_(confidence), visibility_(visibility)
    {
    }

    /**
     * @brief copy constructor with params
     *
     * @param keypoint2 keypoint2
     */
    KeyPoint2T(const KeyPoint2T& keypoint2) noexcept
      : Base(keypoint2.GetX(), keypoint2.GetY()), confidence_(keypoint2.confidence_), visibility_(keypoint2.visibility_)
    {
    }

    /**
     * @brief Destroy the Keypoint object
     */
    ~KeyPoint2T() noexcept
    {
        static_assert(std::is_arithmetic<Scalar>::value, "KeyPoint2T need take arthimetic");
    }
    /**
     * @brief Copy assign
     *
     * @param other the other KeyPoint2T object
     *
     * @return Assigened KeyPoint2T object
     */
    KeyPoint2Type& operator=(const KeyPoint2Type& other) noexcept
    {
        this->SetX(other.GetX());
        this->SetY(other.GetY());
        confidence_ = other.confidence_;
        visibility_ = other.visibility_;
        return *this;
    }
    /**
     * @brief operator==
     *
     * @param other other key point
     * @return bool_t return true if two key points equals
     */
    bool_t operator==(const KeyPoint2Type& other) const noexcept
    {
        if (!ScalarEqualT<Scalar>()(this->GetX(), other.GetX()))
        {
            return false;
        }

        if (!ScalarEqualT<Scalar>()(this->GetY(), other.GetY()))
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

    /**
     * @brief squared distance between two keypoints
     *
     * @param other keypoint2
     *
     * @return squared distance
     */
    Scalar DistSqr(const KeyPoint2T& target) const noexcept
    {
        const Scalar dx = (this->GetX() - target.GetX()), dy = (this->GetY() - target.GetY());
        return (dx * dx) + (dy * dy);
    }

    /**
     * @brief distance between two keypoints
     *
     * @param other keypoint2
     *
     * @return distance
     */
    Scalar Dist(const KeyPoint2T& target) const noexcept
    {
        return std::sqrt(DistSqr(target));
    }

    /**
     * @brief Set confidence of keypoint
     *
     * @param confidence confidence of keypoint
     */
    void SetConfidence(const holo::float32_t confidence) noexcept
    {
        confidence_ = confidence;
    }

    /**
     * @brief Set visibility of keypoint
     *
     * @param visibility visibility for keypoint
     */
    void SetVisibility(const holo::bool_t visibility) noexcept
    {
        visibility_ = visibility;
    }

    /**
     * @brief Get confidence of keypoint 2d
     *
     * @return confidence of keypoint
     */
    holo::float32_t GetConfidence() const noexcept
    {
        return confidence_;
    }

    /**
     * @brief Get visibility of keypoint 2d
     *
     * @return visibility of keypoint
     */
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
    /**
     * @brief confidence of keypoint2d
     */
    holo::float32_t confidence_;

    /**
     * @brief visibility of keypoint2d
     */
    holo::bool_t visibility_;
};

/**
 * @brief handy typedefs
 */
using KeyPoint2f        = KeyPoint2T<float32_t>;
using KeyPoint2d        = KeyPoint2T<float64_t>;
using KeyPoint2         = KeyPoint2T<float64_t>;
using ObjectKeyPoints2f = std::vector<KeyPoint2f>;
using ObjectKeyPoints2d = std::vector<KeyPoint2d>;
using ObjectKeyPoints2  = std::vector<KeyPoint2f>;
/**
 * @}
 */
}  // namespace vision
}  // namespace holo

#endif  // !HOLO_VISION_KEYPOINT2_H_
