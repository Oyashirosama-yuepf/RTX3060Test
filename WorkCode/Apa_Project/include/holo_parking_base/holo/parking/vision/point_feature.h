/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file point_feature.h
 * @brief This header file defines a single point feature extracted on image.
 * @author lifeng(lifeng@holomaitc.com)
 * @date 2021-01-07
 */

#ifndef HOLO_PARKING_VISION_POINT_FEATURE_H_
#define HOLO_PARKING_VISION_POINT_FEATURE_H_

#include <vector>

#include <holo/core/types.h>
#include <holo/geometry/point2.h>
#include <holo/numerics/vector.h>

namespace holo
{
namespace parking
{
namespace vision
{
/**
 * @addtogroup parking
 *
 * @{
 */

/**
 * @brief This class defines a point feature.
 *
 * @details A point feature is extracted on image by a certain feature extraction algorithm(eg: ORB, SIFT, SuperPoint,
 * etc), contain its 2d position in image coordinate, confidence, descriptor, and can be used in all kinds of
 * multi-view geometry task(eg: visual based SLAM, 3D Reconstruction)
 *
 * @tparam T float32_t or float64_t
 * @tparam Dim dimension of the descriptor
 */

template <typename T>
class PointFeatureT
{
public:
    using ScalarType       = T;
    using Point2Type       = holo::geometry::Point2T<ScalarType>;
    using DescriptorType   = std::vector<ScalarType>;
    using PointFeatureType = PointFeatureT<ScalarType>;

    /**
     * @brief Default Constructor
     */
    PointFeatureT() noexcept : position_(Point2Type()), dimension_(0), descriptor_(DescriptorType()), confidence_(0.0f)
    {
    }

    /**
     * @brief Constrcutor with params
     *
     * @param position point position in image coordinate
     * @param descriptor the descriptor
     * @param confidence the confidence
     */
    PointFeatureT(const Point2Type& position, const DescriptorType& descriptor, ScalarType confidence) noexcept
      : position_(position), dimension_(descriptor.size()), descriptor_(descriptor), confidence_(confidence)
    {
    }

    /**
     * @brief copy constructor with params
     *
     * @param other a point feature
     */
    PointFeatureT(const PointFeatureT& other) noexcept
      : position_(other.GetPointPosition())
      , dimension_(other.GetDescriptorDimension())
      , descriptor_(other.GetDescriptor())
      , confidence_(other.GetConfidence())
    {
    }

    /**
     * @brief Destroy the Keypoint object
     */
    ~PointFeatureT() noexcept
    {
    }

    /**
     * @brief Get point position in image coordinate
     */
    const Point2Type& GetPointPosition() const
    {
        return position_;
    }

    /**
     * @brief Get descriptor
     */
    const DescriptorType& GetDescriptor() const
    {
        return descriptor_;
    }

    /**
     * @brief Get confidence
     */
    const ScalarType GetConfidence() const
    {
        return confidence_;
    }

    /**
     * @brief Get dimention of the descriptor
     */
    uint16_t GetDescriptorDimension() const
    {
        return dimension_;
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
        return position_.template GetSerializedSize<ALIGN>() + holo::serialization::SerializedSize<ALIGN>(dimension_) +
               holo::serialization::AlignedSize<ALIGN>(dimension_ * sizeof(ScalarType)) +
               holo::serialization::AlignedSize<ALIGN>(sizeof(ScalarType));
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
        serializer << position_ << dimension_;
        for (size_t i = 0; i < dimension_; i++)
        {
            serializer << descriptor_[i];
        }

        serializer << confidence_ << holo::serialization::align;
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
        deserializer >> position_ >> dimension_;
        descriptor_.resize(dimension_);
        for (size_t i = 0; i < dimension_; i++)
        {
            ScalarType item;
            deserializer >> item;
            descriptor_[i] = item;
        }
        deserializer >> confidence_ >> holo::serialization::align;
    }

private:
    /**
     * @brief position of the point feature in image coordinate
     */
    Point2Type position_;

    /**
     * @brief the dimension of descriptor
     */
    uint32_t dimension_;

    /**
     * @brief position of the point feature in image coordinate
     */
    DescriptorType descriptor_;

    /**
     * @brief confidence of the point feature
     */
    ScalarType confidence_;
};

/**
 * @brief This class represents a point feature with accuracy of float32_t and dimention of descriptor is
 */
using PointFeaturef = PointFeatureT<float32_t>;

/**
 * @brief This class represents a point feature with accuracy of float64_t and dimention of descriptor is
 */
using PointFeatured = PointFeatureT<float64_t>;

/**
 * @}
 */
}  // namespace vision
}  // namespace parking
}  // namespace holo

#endif  // !HOLO_PARKING_VISION_POINT_FEATURE_H_
