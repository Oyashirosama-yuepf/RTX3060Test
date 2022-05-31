/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file camera_lane_boundary.h
 * @brief This header file defines CameraLaneBoundaryT class
 * @author zhouhuishuang@holomatic.com
 * @date 2022-04-01
 */

#ifndef HOLO_COMMON_CAMERA_LANE_BOUNDARY_H_
#define HOLO_COMMON_CAMERA_LANE_BOUNDARY_H_

#include <holo/common/boundary_feature.h>
#include <holo/common/coordinate.h>
#include <holo/common/timestamp.h>
#include <holo/container/vector.h>
#include <holo/core/types.h>
#include <holo/geometry/point2.h>
#include <holo/numerics/utility.h>
#include <holo/serialization/serialization.h>

namespace holo
{
namespace common
{
/**
 * @brief camera lane boundary class.
 *
 * @tparam T ScalarType of polynomial
 * @tparam Degree Degree value of polynomial
 * @tparam AttributeSize the size of attributes
 * @note Reference to: https://holomatic.feishu.cn/docs/doccnu1JjKZCD5dL2MUDtRKVHbe#
 */
template <typename T, size_t Degree, size_t AttributeSize = 4U>
class CameraLaneBoundaryT
{
public:
    using ScalarType                         = T;
    using PointType                          = holo::geometry::Point2T<ScalarType>;
    using CurveType                          = holo::numerics::Polynomial<ScalarType, Degree>;
    static const size_t ATTRIBUTE_SIZE_VALUE = AttributeSize;

    /**
     * @brief BoundaryStylesType indicate the style of a lane boundary
     *
     * @details lane boundary are divided into n segments (n <= ATTRIBUTE_SIZE_VALUE), the float32_t type represents the
     * starting coordinates of each lane boundary in the polynomial. BoundaryStyle type represents the lane boundary
     * style of the corresponding segment
     */
    using BoundaryStylesType = holo::container::Vector<std::pair<float32_t, BoundaryStyle>, ATTRIBUTE_SIZE_VALUE>;

    /**
     * @brief BoundaryColorsType indicate the color of a lane boundary
     *
     * @details lane boundary are divided into n segments (n <= ATTRIBUTE_SIZE_VALUE), the float32_t type represents the
     * starting coordinates of each lane boundary in the polynomial. BoundaryColor type represents the lane boundary
     * color of the corresponding segment
     */
    using BoundaryColorsType = holo::container::Vector<std::pair<float32_t, BoundaryColor>, ATTRIBUTE_SIZE_VALUE>;

    /**
     * @brief BoundaryWidthsType indicate the width of a lane boundary
     *
     * @details lane boundary are divided into n segments (n <= ATTRIBUTE_SIZE_VALUE), the first float32_t type
     * represents the starting coordinates of each lane boundary in the polynomial. the second float32_t type represents
     * the lane boundary width of the corresponding segment
     */
    using BoundaryWidthsType = holo::container::Vector<std::pair<float32_t, float32_t>, ATTRIBUTE_SIZE_VALUE>;

    /**
     * @brief Construct with curve object.
     *
     * @param curve the curve object.
     * @param start_x start coordinate of this boundary
     * @param end_x end coordinate of this boundary
     */
    CameraLaneBoundaryT(CurveType curve, ScalarType start_x = static_cast<ScalarType>(0),
                        ScalarType end_x = static_cast<ScalarType>(0))
      : track_id_{}
      , boundary_index_{}
      , confidence_{static_cast<float32_t>(1.0f)}
      , start_x_{start_x}
      , end_x_{end_x}
      , curve_{curve}
      , boundary_styles_{}
      , boundary_colors_{}
      , boundary_widths_{}
    {
    }

    /**
     * @brief Copy constructor
     *
     * @param other other camera lane boundary
     */
    CameraLaneBoundaryT(CameraLaneBoundaryT const&) = default;

    /**
     * @brief Move constructor
     *
     * @param other other camera lane boundary
     */
    CameraLaneBoundaryT(CameraLaneBoundaryT&&) = default;

    /**
     * @brief Copy assignment
     *
     * @param other camera lane boundary to assign
     * @return new camera lane boundary
     */
    CameraLaneBoundaryT& operator=(CameraLaneBoundaryT const&) = default;

    /**
     * @brief Move assignment
     *
     * @param other other camera lane boundary
     * @return new camera lane boundary
     */
    CameraLaneBoundaryT& operator=(CameraLaneBoundaryT&&) = default;

    /**
     * @brief destructor
     */
    ~CameraLaneBoundaryT() noexcept = default;

    /**
     * @brief Get track id
     *
     * @return track id
     */
    uint32_t GetTrackId() const noexcept
    {
        return track_id_;
    }

    /**
     * @brief Set track id
     *
     * @param id track id
     */
    void SetTrackId(uint32_t const id) noexcept
    {
        track_id_ = id;
    }

    /**
     * @brief Get boundary index
     *
     * @return boundary index
     */
    int8_t GetBoundaryIndex() const noexcept
    {
        return boundary_index_;
    }

    /**
     * @brief Set boundary index
     *
     * @param index boundary index
     */
    void SetBoundaryIndex(int8_t const index) noexcept
    {
        boundary_index_ = index;
    }

    /**
     * @brief Get confidence
     *
     * @return confidence
     */
    float32_t GetConfidence() const noexcept
    {
        return confidence_;
    }

    /**
     * @brief Set confidence
     *
     * @param confidence
     */
    void SetConfidence(float32_t const confidence) noexcept
    {
        confidence_ = confidence;
    }

    /**
     * @brief Get start x
     *
     * @return start x
     */
    ScalarType GetStartX() const noexcept
    {
        return start_x_;
    }

    /**
     * @brief Set start x
     *
     * @param value start x value
     */
    void SetStartX(ScalarType const value) noexcept
    {
        start_x_ = value;
    }

    /**
     * @brief Get end x
     *
     * @return end x
     */
    ScalarType GetEndX() const noexcept
    {
        return end_x_;
    }

    /**
     * @brief Set end x
     *
     * @param value end x value
     */
    void SetEndX(ScalarType const value) noexcept
    {
        end_x_ = value;
    }

    /**
     * @brief Get boundary styles
     *
     * @return Const reference of BoundaryStylesType
     */
    BoundaryStylesType const& GetBoundaryStyles() const noexcept
    {
        return boundary_styles_;
    }

    /**
     * @brief Get boundary styles
     *
     * @return reference of BoundaryStylesType
     */
    BoundaryStylesType& GetBoundaryStyles() noexcept
    {
        return boundary_styles_;
    }

    /**
     * @brief Set boundary styles
     *
     * @param boundary_styles
     */
    void SetBoundaryStyles(BoundaryStylesType const& boundary_styles) noexcept
    {
        boundary_styles_ = boundary_styles;
    }

    /**
     * @brief Get boundary color
     *
     * @return Const reference of BoundaryColorsType
     */
    BoundaryColorsType const& GetBoundaryColors() const noexcept
    {
        return boundary_colors_;
    }

    /**
     * @brief Get boundary color
     *
     * @return reference of BoundaryColorsType
     */
    BoundaryColorsType& GetBoundaryColors() noexcept
    {
        return boundary_colors_;
    }

    /**
     * @brief Set boundary color
     *
     * @param colors
     */
    void SetBoundaryColorCategories(BoundaryColorsType const& colors) noexcept
    {
        boundary_colors_ = colors;
    }

    /**
     * @brief Get boundary widths
     *
     * @return Const reference of BoundaryWidthsType
     */
    BoundaryWidthsType const& GetBoundaryWidths() const noexcept
    {
        return boundary_widths_;
    }

    /**
     * @brief Get boundary widths
     *
     * @return reference of BoundaryWidthsType
     */
    BoundaryWidthsType& GetBoundaryWidths() noexcept
    {
        return boundary_widths_;
    }

    /**
     * @brief Set boundary widths
     *
     * @param boundary_widths
     */
    void SetBoundaryWidths(BoundaryWidthsType const& boundary_widths) noexcept
    {
        boundary_widths_ = boundary_widths;
    }

    /**
     * @brief Check if boundary parameters are valid.
     *
     * @return True if boundary is valid otherwise false.
     */
    bool_t IsValid() const noexcept
    {
        if (start_x_ < end_x_)
        {
            return true;
        }
        return false;
    }

    /**
     * @brief Get sample point of boundary by x coordinate
     *
     * @param x x coordinate value
     *
     * @return Sample point
     */
    PointType GetSampleByCoordinate(ScalarType x) const
    {
        return PointType(x, curve_.GetValue(x));
    }

    /**
     * @brief Get curve
     * 
     * @return reference of curve
     */
    CurveType& GetCurve() noexcept
    {
        return curve_;
    }

    /**
     * @brief Get curve
     * 
     * @return const reference of curve
     */
    CurveType const& GetCurve() const noexcept
    {
        return curve_;
    }

    /**
     * @brief Get x coordinate range of this boundary
     *
     * @return start, end coordinate pair
     */
    std::pair<ScalarType, ScalarType> GetCoordinateRange() const noexcept
    {
        return std::pair<ScalarType, ScalarType>(start_x_, end_x_);
    }

    /**
     * @brief Get length of this boundary
     *
     * @return  length of this boundary
     */
    ScalarType GetLength() const noexcept
    {
        // Simpson's 3/8 rule
        ScalarType derivatives[4U];
        static_cast<void>(derivatives[0U] = curve_.template GetDerivative<1>(start_x_));
        static_cast<void>(derivatives[1U] = curve_.template GetDerivative<1>((2 * start_x_ + end_x_) / 3));
        static_cast<void>(derivatives[2U] = curve_.template GetDerivative<1>((start_x_ + 2 * end_x_) / 3));
        derivatives[3U] = curve_.template GetDerivative<1>(end_x_);
        return static_cast<ScalarType>((end_x_ - start_x_) / 8 *
               (sqrt(1 + derivatives[0U] * derivatives[0U]) + 3 * sqrt(1 + derivatives[1U] * derivatives[1U]) +
                3 * sqrt(1 + derivatives[2U] * derivatives[2U]) + sqrt(1 + derivatives[3U] * derivatives[3U])));
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        size_t aligned_size =
            holo::serialization::SerializedSize<ALIGN>(track_id_, boundary_index_, confidence_, start_x_, end_x_);
        aligned_size += curve_.template GetSerializedSize<ALIGN>();
        aligned_size += holo::serialization::AlignedSize<ALIGN>(sizeof(uint32_t));
        aligned_size += holo::serialization::AlignedSize<ALIGN>(sizeof(float32_t) + sizeof(BoundaryStyle)) *
                        boundary_styles_.size();

        aligned_size += holo::serialization::AlignedSize<ALIGN>(sizeof(uint32_t));
        aligned_size += holo::serialization::AlignedSize<ALIGN>(sizeof(float32_t) + sizeof(BoundaryColor)) *
                        boundary_colors_.size();

        aligned_size += holo::serialization::AlignedSize<ALIGN>(sizeof(uint32_t));
        aligned_size +=
            holo::serialization::AlignedSize<ALIGN>(sizeof(float32_t) + sizeof(float32_t)) * boundary_widths_.size();

        return aligned_size;
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << holo::serialization::align << track_id_ << boundary_index_ << confidence_ << start_x_ << end_x_
                   << curve_;

        uint32_t size = boundary_styles_.size();
        serializer << holo::serialization::align << size << holo::serialization::align;
        for (auto const& pair : boundary_styles_)
        {
            serializer << pair.first << static_cast<uint8_t>(pair.second) << holo::serialization::align;
        }

        size = boundary_colors_.size();
        serializer << size << holo::serialization::align;
        for (auto const& pair : boundary_colors_)
        {
            serializer << pair.first << static_cast<uint8_t>(pair.second) << holo::serialization::align;
        }

        size = boundary_widths_.size();
        serializer << size << holo::serialization::align;
        for (auto const& pair : boundary_widths_)
        {
            serializer << pair.first << static_cast<uint8_t>(pair.second) << holo::serialization::align;
        }
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        deserializer >> holo::serialization::align >> track_id_ >> boundary_index_ >> confidence_ >> start_x_ >>
            end_x_ >> curve_;

        uint32_t  size;
        float32_t cut_x;

        deserializer >> holo::serialization::align >> size >> holo::serialization::align;
        boundary_styles_.clear();
        boundary_styles_.reserve(size);
        for (size_t i = 0; i < size; ++i)
        {
            uint8_t type;
            deserializer >> cut_x >> type >> holo::serialization::align;
            boundary_styles_.emplace_back(std::make_pair(cut_x, static_cast<BoundaryStyle>(type)));
        }

        deserializer >> holo::serialization::align >> size;
        boundary_colors_.clear();
        boundary_colors_.reserve(size);
        for (size_t i = 0; i < size; ++i)
        {
            uint8_t type;
            deserializer >> cut_x >> type >> holo::serialization::align;
            boundary_colors_.emplace_back(std::make_pair(cut_x, static_cast<BoundaryColor>(type)));
        }

        deserializer >> holo::serialization::align >> size;
        boundary_widths_.clear();
        boundary_widths_.reserve(size);
        for (size_t i = 0; i < size; ++i)
        {
            float32_t width;
            deserializer >> cut_x >> width >> holo::serialization::align;
            boundary_widths_.emplace_back(std::make_pair(cut_x, width));
        }
    }

private:
    uint32_t   track_id_;        ///< lane boundary id
    int8_t     boundary_index_;  ///< boundary position index
    float32_t  confidence_;      ///< [0,1],default = 1
    ScalarType start_x_;         ///< Start coordinate of this boundary
    ScalarType end_x_;           ///< End coordinate of this boundary
    CurveType  curve_;           ///< The curve object

    BoundaryStylesType boundary_styles_;  ///< boundary styles
    BoundaryColorsType boundary_colors_;  ///< boundary colors
    BoundaryWidthsType boundary_widths_;  ///< boundary widths
};

/**
 * @brief camera lane boundaries class.
 *
 * @tparam LaneBoundary camera lane boundary type
 * @tparam SIZE the size of camera lane boundary attribute
 */
template <typename LaneBoundary, size_t SIZE = 16U>
class CameraLaneBoundariesT : public holo::container::details::VectorBase<LaneBoundary, SIZE>
{
public:
    using LaneBoundaryType = LaneBoundary;
    using Base             = holo::container::details::VectorBase<LaneBoundaryType, SIZE>;

    /**
     * @brief Default constructor
     */
    CameraLaneBoundariesT() noexcept : Base{}, timestamp_{}, coordinate_{}
    {
    }

    /**
     * @brief Construct from timestamp and coordinate
     *
     * @param timestamp
     * @param coordinate
     */
    CameraLaneBoundariesT(const Timestamp& timestamp, Coordinate coordinate) noexcept
      : Base{}, timestamp_{timestamp}, coordinate_{coordinate}
    {
    }

    /**
     * @brief Copy constructor
     *
     * @param other other camera lane boundaries
     */
    CameraLaneBoundariesT(CameraLaneBoundariesT const&) = default;

    /**
     * @brief Move constructor
     *
     * @param other other camera lane boundaries
     */
    CameraLaneBoundariesT(CameraLaneBoundariesT&&) = default;

    /**
     * @brief Copy assignment
     *
     * @param other camera lane boundaries to assign
     * @return new camera lane boundaries
     */
    CameraLaneBoundariesT& operator=(CameraLaneBoundariesT const&) = default;

    /**
     * @brief Move assignment
     *
     * @param other other camera lane boundaries
     * @return new camera lane boundaries
     */
    CameraLaneBoundariesT& operator=(CameraLaneBoundariesT&&) = default;

    /**
     * @brief destructor
     */
    ~CameraLaneBoundariesT() noexcept = default;

    /**
     * @brief Set timestamp
     *
     * @return timestamp
     */
    void SetTimestamp(Timestamp const& timestamp) noexcept
    {
        timestamp_ = timestamp;
    }

    /**
     * @brief Get timestamp
     *
     * @return timestamp
     */
    Timestamp const& GetTimestamp() const
    {
        return timestamp_;
    }

    /**
     * @brief Get coordinate
     *
     * @return coordinate
     */
    Coordinate GetCoordinate() const
    {
        return coordinate_;
    }

    /**
     * @brief Set coodinate
     *
     * @return coor coordinate
     */
    void SetCoordinate(Coordinate const coor) noexcept
    {
        coordinate_ = coor;
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return Base::template GetSerializedSize<ALIGN>() + timestamp_.GetSerializedSize<ALIGN>() +
               coordinate_.GetSerializedSize<ALIGN>();
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        uint32_t boundary_size = this->size();
        serializer << timestamp_ << coordinate_ << boundary_size;

        for (size_t i = 0; i < boundary_size; ++i)
        {
            serializer << (*this)[i];
        }
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        uint32_t boundary_size;
        deserializer >> timestamp_ >> coordinate_ >> boundary_size;

        LaneBoundaryType boundary(typename LaneBoundaryType::CurveType(), 0, 0);

        this->clear();
        this->reserve(boundary_size);
        for (size_t i = 0; i < boundary_size; ++i)
        {
            deserializer >> boundary;
            this->push_back(std::move(boundary));
        }
    }

private:
    Timestamp  timestamp_;
    Coordinate coordinate_;
};

}  // namespace common
}  // namespace holo

#endif
