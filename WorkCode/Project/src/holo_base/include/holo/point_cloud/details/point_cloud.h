/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file point_type.h
 * @brief This header file defines point types used by point cloud.
 * @author zhangjiannan(zhangjiannan@holomaitc.com)
 * @date 2020-10-29
 */

#ifndef HOLO_POINT_CLOUD_DETAILS_POINT_CLOUD_H_
#define HOLO_POINT_CLOUD_DETAILS_POINT_CLOUD_H_

#include <holo/common/coordinate.h>
#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/geometry/pose3.h>
#include "linear_storage.h"

namespace holo
{
namespace point_cloud
{
namespace details
{
/**
 * @brief Tag for unorganized point cloud type
 */
class UnorganizedLayoutTag
{
};

/**
 * @brief Tag for organized point cloud type
 */
class OrganizedLayoutTag
{
};

/**
 * @brief Base class for point cloud. By default point cloud use linear storage to store points.
 *
 * @tparam Point Point type
 * @tparam SIZE Size of point cloud. 0 mean dynamic size.
 * @tparam STRIDE Stride of each point element.
 * @tparam LAYOUT Point cloud layout.
 */
template <typename Point, size_t SIZE, size_t STRIDE, typename LayoutTag>
class PointCloudBaseT : public LinearStorageBase<Point, SIZE, STRIDE>
{
public:
    using Base = LinearStorageBase<Point, SIZE, STRIDE>;
    using Base::Base;

    using PointType  = typename Base::value_type;
    using ScalarType = typename PointType::ScalarType;
    using PoseType   = holo::geometry::Pose3T<ScalarType>;
    using LayoutType = LayoutTag;

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
     * @brief Get idx-th element
     *
     * @param idx Element index
     *
     * @return idx-th element
     */
    value_type& operator()(size_t idx) noexcept
    {
        return this->operator[](idx);
    }

    /**
     * @brief Get idx-th element
     *
     * @param idx Element index
     *
     * @return idx-th element
     */
    value_type const& operator()(size_t idx) const noexcept
    {
        return this->operator[](idx);
    }

    /**
     * @brief Get timestamp
     *
     * @return Timestamp value
     */
    holo::common::Timestamp GetTimestamp() const noexcept
    {
        return stamp_;
    }

    /**
     * @brief Set timestamp value
     *
     * @param value Timestamp value
     */
    void SetTimestamp(holo::common::Timestamp value) noexcept
    {
        stamp_ = value;
    }

    /**
     * @brief Get coordinate
     *
     * @return Coordinate value
     */
    holo::common::Coordinate GetCoordinate() const noexcept
    {
        return coordinate_;
    }

    /**
     * @brief Set coordinate value
     *
     * @param value Coordinate value
     */
    void SetCoordinate(holo::common::Coordinate value) noexcept
    {
        coordinate_ = value;
    }

    /**
     * @brief Get Pose
     *
     * @return Reference to PoseType
     */
    PoseType const& GetPose() const noexcept
    {
        return pose_;
    }

    /**
     * @brief Get Pose
     *
     * @return Reference to PoseType
     */
    PoseType& GetPose() noexcept
    {
        return pose_;
    }

    /**
     * @brief Set pose value
     *
     * @param value Pose value
     */
    void SetPose(PoseType const& value) noexcept
    {
        pose_ = value;
    }

    /**
     * @brief Check if point cloud is dense
     *
     * @return dense flag
     */
    holo::bool_t IsDense() const noexcept
    {
        return is_dense_;
    }

    /**
     * @brief Set dense flag
     *
     * @param value Dense flag value
     */
    void SetDense(holo::bool_t value) noexcept
    {
        is_dense_ = value;
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
        return Base::template GetSerializedSize<ALIGN>() + stamp_.GetSerializedSize<ALIGN>() + pose_.template GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(static_cast<uint32_t>(coordinate_), is_dense_);
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
        serializer << stamp_ << pose_ << static_cast<uint32_t>(coordinate_) << is_dense_ << holo::serialization::align;
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
        uint32_t coordinate = 0;
        Base::Deserialize(deserializer);
        deserializer >> stamp_ >> pose_ >> coordinate >> is_dense_ >> holo::serialization::align;
        SetCoordinate(coordinate);
    }

protected:
    /**
     * @brief Default destructor
     */
    ~PointCloudBaseT() = default;

private:
    holo::common::Timestamp            stamp_      = {};
    holo::geometry::Pose3T<ScalarType> pose_       = {};
    holo::common::Coordinate           coordinate_ = {};
    holo::bool_t                       is_dense_   = false;
};

/**
 * @brief Point cloud type
 *
 * @tparam Point Point type of point cloud
 * @tparam SIZE Element size. 0 means dynamic size
 * @tparam STRIDE Stride of element
 * @tparam LAYOUT Point cloud layout
 */
template <typename Point, size_t SIZE, size_t STRIDE, typename LayoutTag>
class PointCloudT;

template <typename Point, size_t SIZE, size_t STRIDE>
class PointCloudT<Point, SIZE, STRIDE, UnorganizedLayoutTag> final
  : public PointCloudBaseT<Point, SIZE, STRIDE, UnorganizedLayoutTag>
{
public:
    using Base = PointCloudBaseT<Point, SIZE, STRIDE, UnorganizedLayoutTag>;
    using Base::Base;

    using PointType  = typename Base::PointType;
    using ScalarType = typename Base::ScalarType;
    using PoseType   = typename Base::PoseType;
    using LayoutType = typename Base::LayoutType;

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
     * @brief Get width of point cloud
     *
     * @return size of point cloud for unorganized layout
     */
    size_t GetWidth() const noexcept
    {
        return this->size();
    }

    /**
     * @brief Get height of point cloud
     *
     * @return 1 for unorganized point cloud
     */
    constexpr size_t GetHeight() const noexcept
    {
        return 1U;
    }
};

template <typename Point, size_t SIZE, size_t STRIDE>
class PointCloudT<Point, SIZE, STRIDE, OrganizedLayoutTag> final
  : public PointCloudBaseT<Point, SIZE, STRIDE, OrganizedLayoutTag>
{
public:
    using Base = PointCloudBaseT<Point, SIZE, STRIDE, OrganizedLayoutTag>;
    using Base::Base;

    using PointType  = typename Base::PointType;
    using ScalarType = typename Base::ScalarType;
    using PoseType   = typename Base::PoseType;
    using LayoutType = typename Base::LayoutType;

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
     * @brief Get point at row/column
     *
     * @param row Row value
     * @param column Column value
     *
     * @return Reference to point
     */
    value_type& operator()(size_t row, size_t column) noexcept
    {
        return this->operator[](row* width_ + column);
    }

    /**
     * @brief Get point at row/column
     *
     * @param row Row value
     * @param column Column value
     *
     * @return Reference to point
     */
    value_type const& operator()(size_t row, size_t column) const noexcept
    {
        return this->operator[](row* width_ + column);
    }

    /**
     * @brief Get point at row/column with bounds check
     *
     * @param row Row value
     * @param column Column value
     *
     * @return Reference to point
     *
     * @throws std::out_of_range exception
     */
    value_type& at(size_t row, size_t column)
    {
        if (row >= getHeight() || column >= getWidth())
        {
            throw std::out_of_range("row/column out of dimension range");
        }
        return Base::at(row * width_ + column);
    }

    /**
     * @brief Get point at row/column with bounds check
     *
     * @param row Row value
     * @param column Column value
     *
     * @return Reference to point
     *
     * @throws std::out_of_range exception
     */
    value_type const& at(size_t row, size_t column) const
    {
        if (row >= getHeight() || column >= getWidth())
        {
            throw std::out_of_range("row/column out of dimension range");
        }
        return Base::at(row * width_ + column);
    }

    using Base::at;

    /**
     * @brief Get width of point cloud
     * @details If dimension is not specified(width == 0U), will use actual point cloud size as width value.
     *
     * @return Width of point cloud
     */
    size_t GetWidth() const noexcept
    {
        return getWidth();
    }

    /**
     * @brief Get height of point cloud
     * @details If dimension is not specified(width == 0U), height == 1U.
     *
     * @return Height of point cloud
     */
    size_t GetHeight() const noexcept
    {
        return getHeight();
    }

    /**
     * @brief Set point cloud dimension
     *
     * @param width Width of point cloud
     */
    void SetDimension(size_t width) noexcept
    {
        width_ = width;
    }

    /**
     * @brief Set point cloud dimension
     *
     * @param width Width of point cloud
     * @param height Height of point cloud
     */
    void SetDimension(size_t width, size_t height) noexcept
    {
        width_  = width;
        height_ = height;
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
               holo::serialization::SerializedSize<ALIGN>(static_cast<uint32_t>(width_), static_cast<uint32_t>(height_));
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
        serializer << static_cast<uint32_t>(width_) << static_cast<uint32_t>(height_) << holo::serialization::align;
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
        uint32_t width  = 0;
        uint32_t height = 0;

        Base::Deserialize(deserializer);
        deserializer >> width >> height >> holo::serialization::align;

        SetDimension(width, height);
    }

private:
    size_t getWidth() const noexcept
    {
        return width_ == 0U ? this->size() : width_;
    }

    size_t getHeight() const noexcept
    {
        return width_ == 0U ? 1U : height_;
    }

    size_t width_  = 0U;
    size_t height_ = 1U;
};

}  // namespace details
}  // namespace point_cloud
}  // namespace holo

#endif
