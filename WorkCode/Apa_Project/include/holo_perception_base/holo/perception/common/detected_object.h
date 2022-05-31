/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file detected_object.h
 * @brief This header file defines base detected object.
 * @author zhoushengjie(zhoushengjie@holomaitc.com)
 * @date "2019-12-05"
 */

#ifndef HOLO_PERCEPTION_COMMON_DETECTED_OBJECT_H_
#define HOLO_PERCEPTION_COMMON_DETECTED_OBJECT_H_

#include <holo/common/classification.h>
#include <holo/common/timestamp.h>
#include <holo/geometry/point3.h>
#include <holo/numerics/vector.h>

namespace holo
{
namespace perception
{
/**
 * @addtogroup common
 *
 * @{
 */

/**
 * @brief define Base detected object
 * @deprecated This class will be deprecated. This class will be replaced with BoxObjectT, which
 * is a more general type.
 *
 * @tparam T data type
 */
template <typename T>
class DetectedObjectT
{
public:
    using Scalar         = T;
    using IdType         = uint32_t;
    using Point3Type     = holo::geometry::details::Point3T<Scalar>;
    using Vector3Type    = numerics::Vector3T<Scalar>;
    using Timestamp      = holo::common::details::Timestamp;
    using Classification = holo::common::Classification;

    /**
     * @brief Default Constructor
     */
    DetectedObjectT()
      : confidence_(static_cast<T>(0.0))
      , classification_()
      , object_id_(0U)
      , position_(Point3Type::Zero())
      , velocity_(Vector3Type::Zero())
      , timestamp_()
    {
    }

    /**
     * @brief Constructor
     *
     * @param confidence object existence confidence
     * @param classification object classification
     * @param id object track id
     * @param position object position in 3d space
     * @param velocity object relative velocity in 3d space
     * @param timestamp object timestamp
     */
    DetectedObjectT(const Scalar confidence, const Classification& classification, const IdType id,
                    const Point3Type& position, const Vector3Type& velocity, const Timestamp& timestamp);

    /**
     * @brief copy constructor with params
     *
     * @param detected_object detected object
     */
    DetectedObjectT(const DetectedObjectT& detected_object) noexcept;

    /**
     * @brief move constructor with params
     *
     * @param detected_object detected object
     */
    DetectedObjectT(DetectedObjectT&& detected_object) noexcept;

    /**
     * @brief Destroy the Base object
     */
    virtual ~DetectedObjectT();

    /**
     * @brief Copy assign
     *
     * @param other the other DetectedObjectT
     *
     * @return Assigened DetectedObjectT
     */
    DetectedObjectT<Scalar>& operator=(const DetectedObjectT<Scalar>& other);

    /**
     * @brief Move assign
     *
     * @param other the other DetectedObjectT
     *
     * @return Assigned DetectedObjectT
     */
    DetectedObjectT<Scalar>& operator=(DetectedObjectT<Scalar>&& other) noexcept;

    /**
     * @brief Set confidence
     *
     * @param confidence object existence confidence
     */
    void SetConfidence(const Scalar confidence)
    {
        if (confidence < 0.0 || confidence > 1.0)
        {
            throw std::range_error("Confidence should be between 0.0 and 1.0 !");
        }
        confidence_ = confidence;
    }

    /**
     * @brief Set classification
     *
     * @param classification object classification
     */
    void SetClassification(const Classification& classification)
    {
        classification_ = classification;
    }

    /**
     * @brief Set track id of the object
     *
     * @param id object track id
     */
    void SetObjectId(const IdType id)
    {
        object_id_ = id;
    }

    /**
     * @brief Set position
     *
     * @param position object position in 3d space
     */
    void SetPosition(const Point3Type& position)
    {
        position_ = position;
    }

    /**
     * @brief Set relative velocity
     *
     * @param velocity object relative velocity in 3d space
     */
    void SetVelocity(const Vector3Type& velocity)
    {
        velocity_ = velocity;
    }

    /**
     * @brief Set timestamp
     *
     * @param timestamp timestamp of the detected object
     */
    void SetTimestamp(const Timestamp& timestamp)
    {
        timestamp_ = timestamp;
    }

    /**
     * @brief Get confidence
     *
     * @return confidence
     */
    const Scalar GetConfidence() const noexcept
    {
        return confidence_;
    }

    /**
     * @brief Get classification
     *
     * @return classification
     */
    const Classification& GetClassification() const noexcept
    {
        return classification_;
    }

    /**
     * @brief Get track id of the object
     *
     * @return track id
     */
    IdType GetObjectId() const noexcept
    {
        return object_id_;
    }

    /**
     * @brief Get position
     *
     * @return object position in 3d space
     */
    const Point3Type& GetPosition() const noexcept
    {
        return position_;
    }

    /**
     * @brief Get relative velocity
     *
     * @return object relative velocity in 3d space
     */
    const Vector3Type& GetVelocity() const noexcept
    {
        return velocity_;
    }

    /**
     * @brief Get timestamp
     *
     * @return object timestamp
     */
    const Timestamp& GetTimestamp() const noexcept
    {
        return timestamp_;
    }

private:
    Scalar         confidence_;      ///< object existance confidence
    Classification classification_;  ///< object classification
    IdType         object_id_;       ///< object track id
    Point3Type     position_;        ///< object position in 3d space
    Vector3Type    velocity_;        ///< object velocity in 3d space
    Timestamp      timestamp_;       ///< object timestamp
};

/**
 * @brief handy typedefs
 */
using DetectedObjectf = DetectedObjectT<float32_t>;
using DetectedObjectd = DetectedObjectT<float64_t>;

/**
 * @}
 */

}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_COMMON_DETECTED_OBJECT_H_
