/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_boundary2.h
 * @brief This header file defines LaneBoundary object.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-05-07
 */

#ifndef HOLO_COMMON_LANE_BOUNDARY2_H_
#define HOLO_COMMON_LANE_BOUNDARY2_H_

#include <memory>

#include <holo/common/boundary_feature.h>
#include <holo/core/exception.h>
#include <holo/core/types.h>
#include <holo/geometry/details/curve_traits.h>
#include <holo/geometry/point2.h>
#include <holo/numerics/utility.h>

namespace holo
{
namespace common
{
/**
 * @brief LaneBoundary object defines a line on a road.
 * @details LaneBoundary must constructed with a curve reference. The life time of curve reference must longer than this
 * LaneBoundary object.
 *
 * @tparam Curve Type of underlying curve
 */
template <typename Curve>
class LaneBoundary
{
public:
    using CurveType  = Curve;
    using PointType  = typename CurveType::PointType;
    using ScalarType = typename CurveType::ScalarType;

    /**
     * @brief Construct with curve object reference.
     *
     * @param curve The curve object.
     */
    explicit LaneBoundary(uint32_t curve_index, uint32_t index, std::shared_ptr<CurveType> curve)
      : curve_(curve)
      , start_(curve->size() > 0U ? curve->size() - 1U : 0U)
      , end_(curve->size())
      , curve_index_{curve_index}
      , index_{index}
      , style_(BoundaryStyle::UNKNOWN)
      , color_(BoundaryColor::UNKNOWN)
      , width_(0U)
      , confidence_(0U)
    {
    }

    /**
     * @brief Construct with another bound object and specify start/end knots
     *
     * @param bound boundary object
     * @param start start knot
     * @param end end knot
     */
    LaneBoundary(uint32_t index, LaneBoundary const& bound, size_t start, size_t end)
      : curve_(bound.curve_)
      , start_(start)
      , end_(end)
      , curve_index_(bound.curve_index_)
      , index_(index)
      , style_(bound.style_)
      , color_(bound.color_)
      , width_(bound.width_)
      , confidence_(bound.confidence_)
    {
    }

    /**
     * @brief Construct with curve object reference and knot range.
     *
     * @param curve The curve object.
     * @param start Start knot index
     * @param end End knot index
     */
    LaneBoundary(uint32_t curve_index, uint32_t index, std::shared_ptr<CurveType> curve, size_t start, size_t end)
      : curve_(curve)
      , start_(start)
      , end_(end)
      , curve_index_{curve_index}
      , index_{index}
      , style_(BoundaryStyle::UNKNOWN)
      , color_(BoundaryColor::UNKNOWN)
      , width_(0U)
      , confidence_(0U)
    {
        if ((start > end) || (end > curve->size()))
        {
            throw holo::exception::OutOfRangeException("");
        }
    }

    /**
     * @brief Number of knots in this lane boundary
     *
     * @return Number of knots.
     */
    size_t size() const noexcept
    {
        return end_ - start_;
    }

    /**
     * @brief Access boundary knots without bound check
     *
     * @param pos Index of knot.
     *
     * @return Reference to the knot
     */
    PointType const& operator[](size_t pos) const noexcept
    {
        return (*curve_)[start_ + pos];
    }

    /**
     * @brief Access boundary knots with bound check
     *
     * @param pos Index of knot.
     *
     * @return Reference to the knot
     */
    PointType const& at(size_t pos) const
    {
        if (start_ + pos >= end_)
        {
            throw holo::exception::OutOfRangeException("");
        }
        return (*curve_)[start_ + pos];
    }

    /**
     * @brief Access first boundary knot
     *
     * @return Reference to first boundary knot
     */
    PointType const& front() const noexcept
    {
        return (*curve_)[start_];
    }

    /**
     * @brief Access last boundary knot
     *
     * @return Reference to last boundary knot
     */
    PointType const& back() const noexcept
    {
        return (*curve_)[end_ - 1U];
    }

    CurveType const& GetCurve() const noexcept
    {
        return *curve_;
    }

    /**
     * @brief Get length of this boundary
     *
     * @return  length of this boundary
     */
    ScalarType GetLength() const noexcept
    {
        return IsValid() ? curve_->GetLength(end_ - 1U) - curve_->GetLength(start_) : 0U;
    }

    /**
     * @brief Set boundary knot range in curve
     *
     * @param start start knot index
     * @param end past-the-end knot index
     */
    void SetKnotRange(size_t start, size_t end)
    {
        if ((start > end) || (end > curve_->size()))
        {
            throw holo::exception::OutOfRangeException("");
        }
        start_ = start;
        end_   = end;
    }

    /**
     * @brief Get boundary knot range in curve
     *
     * @return start, past-the-end knot index pair
     */
    std::pair<size_t, size_t> GetKnotRange() const noexcept
    {
        return std::pair<size_t, size_t>(start_, end_);
    }

    /**
     * @brief Get x coordinate range of this boundary
     *
     * @return start, end coordinate pair
     */
    template <typename TAG_ = typename CurveType::TagType,
              typename std::enable_if<std::is_same<TAG_, holo::geometry::CurveExplicitTag>::value>::type* = nullptr>
    std::pair<ScalarType, ScalarType> GetCoordinateRange() const noexcept
    {
        return IsValid() ? std::pair<ScalarType, ScalarType>((*curve_)[start_][0U], (*curve_)[end_ - 1U][0U]) :
                           std::pair<ScalarType, ScalarType>(0, 0);
    }

    /**
     * @brief Get D-th derivative of boundary by arc length
     *
     * @tparam D Derivative order
     * @param len length to start of boundary
     *
     * @return Derivative value
     */
    template <size_t D>
    PointType GetDerivativeByArcLength(ScalarType len) const
    {
        ScalarType base_len = curve_->template GetLength(start_);
        return curve_->template GetDerivativeByArcLength<D>(base_len + len);
    }

    /**
     * @brief Get sample point of boundary by arc length
     *
     * @param len length to start of boundary
     *
     * @return Sample point
     */
    PointType GetSampleByArcLength(ScalarType len) const
    {
        ScalarType base_len = curve_->GetLength(start_);
        return curve_->template GetDerivativeByArcLength<0>(base_len + len);
    }

    /**
     * @brief Get D-th derivative of boundary by x coordinate
     *
     * @param x x coordinate value
     *
     * @return Derivative value
     */
    template <size_t D, typename TAG_ = typename CurveType::TagType,
              typename std::enable_if<std::is_same<TAG_, holo::geometry::CurveExplicitTag>::value>::type* = nullptr>
    PointType GetDerivativeByCoordinate(ScalarType x) const
    {
        return curve_->template GetDerivativeByCoordinate<D>(x);
    }

    /**
     * @brief Get sample point of boundary by x coordinate
     *
     * @param x x coordinate value
     *
     * @return Sample point
     */
    template <typename TAG_ = typename CurveType::TagType,
              typename std::enable_if<std::is_same<TAG_, holo::geometry::CurveExplicitTag>::value>::type* = nullptr>
    PointType GetSampleByCoordinate(ScalarType x) const
    {
        return curve_->template GetDerivativeByCoordinate<0>(x);
    }

    /**
     * @brief Append lane boundary with one knot point
     *
     * @param pt The knot to extend
     *
     * @throws holo::exception::OperationNotPermittedException if boundary end is not the last knot of curve.
     */
    void push_back(PointType const& pt)
    {
        if (end_ != curve_->size())
        {
            throw holo::exception::OperationNotPermittedException();
        }
        curve_->push_back(pt);
        ++end_;
    }

    /**
     * @brief Update boundary point
     *
     * @param pos pos of knot in lane boundary
     * @param pt New knot value
     */
    void UpdateKnot(size_t pos, PointType const& pt)
    {
        if (!(pos < size()))
        {
            throw holo::exception::OperationNotPermittedException();
        }
        curve_->UpdateKnot(curve_->begin() + start_ + pos, pt);
    }

    /**
     * @brief Set first derivative at start point.
     * @details Only when the start knot is the start point of underlying curve, this operation will success.
     *
     * @param value derivative value
     *
     * @return true if set success, false otherwise.
     */
    bool SetStartFirstDerivative(PointType const& value)
    {
        if (start_ != 0U)
        {
            return false;
        }
        curve_->SetStartCondition(CurveType::ConditionType::FIRST_DERIVATIVE, value);
        return true;
    }

    /**
     * @brief Reset start point condition.
     * @details Only when the start knot is the start point of underlying curve, this operation will success.
     *
     * @return true if reset success, false otherwise.
     */
    bool ResetStartCondition()
    {
        if (start_ != 0U)
        {
            return false;
        }
        curve_->SetStartCondition(CurveType::ConditionType::DEFAULT, PointType{});
        return true;
    }

    /**
     * @brief Set first derivative at end point
     * @details Only when the end knot is the start point of underlying curve, this operation will success.
     *
     * @param value derivative value
     *
     * @return true if set success, false otherwise.
     */
    bool SetEndFirstDerivative(PointType const& value)
    {
        if (end_ != curve_->size())
        {
            return false;
        }
        curve_->SetEndCondition(CurveType::ConditionType::FIRST_DERIVATIVE, value);
        return true;
    }

    /**
     * @brief Reset end point condition.
     * @details Only when the start knot is the start point of underlying curve, this operation will success.
     *
     * @return true if reset success, false otherwise.
     */
    bool ResetEndCondition()
    {
        if (end_ != curve_->size())
        {
            return false;
        }
        curve_->SetEndCondition(CurveType::ConditionType::DEFAULT, PointType{});
        return true;
    }

    /**
     * @brief Check if boundary parameters are valid.
     *
     * @return True if boundary is valid otherwise false.
     */
    bool_t IsValid() const noexcept
    {
        if ((start_ + 2U <= end_) && (end_ <= curve_->size()))
        {
            return true;
        }
        return false;
    }

    /**
     * @brief Get boundary style
     *
     * @return style value
     */
    BoundaryStyle GetStyle() const noexcept
    {
        return style_;
    }

    /**
     * @brief Set boundary style
     *
     * @param value style value
     */
    void SetStyle(BoundaryStyle value) noexcept
    {
        style_ = value;
    }

    /**
     * @brief Get boundary color
     *
     * @return boundary color value
     */
    BoundaryColor GetColor() const noexcept
    {
        return color_;
    }

    /**
     * @brief Set boundary color
     *
     * @param value boundary color value
     */
    void SetColor(BoundaryColor value) noexcept
    {
        color_ = value;
    }

    /**
     * @brief Get width of this boundary
     *
     * @return width in cm.
     */
    uint8_t GetWidth() const noexcept
    {
        return width_;
    }

    /**
     * @brief Set width of this boundary
     *
     * @param width Width in cm
     */
    void SetWidth(uint8_t width) noexcept
    {
        width_ = width;
    }

    /**
     * @brief Get confidence value. Unit %.
     *
     * @return confidence value
     */
    uint8_t GetConfidence() const noexcept
    {
        return confidence_;
    }

    /**
     * @brief Set confidence value. Unit: %.
     *
     * @param confidence confidence value
     */
    void SetConfidence(uint8_t confidence) noexcept
    {
        confidence_ = confidence;
    }

    /**
     * @brief Check if this lane boundary is predicted
     *
     * @return true if boundary is predicted otherwise false.
     */
    bool_t IsPredicted() const noexcept
    {
        return confidence_ == 0;
    }

    /**
     * @brief Get required buffer size to serialize this object
     *
     * @tparam S Class that used to serializing this object
     * @param serializer the instance of Serializer
     *
     * @return Required buffer size
     */
    template <typename S>
    size_t GetSerializedAttributesSize(S const&) const noexcept
    {
        constexpr size_t Alignment = S::GetAlignment();

        size_t aligned_size =
            sizeof(BoundaryStyle) + sizeof(BoundaryColor) + sizeof(uint8_t) * 2;  // width_ and confidence_
        return holo::serialization::AlignedSize<Alignment>(aligned_size);
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedAttributesSize() const noexcept
    {
        return holo::serialization::AlignedSize<ALIGN>(sizeof(BoundaryStyle) + sizeof(BoundaryColor) +
                                                       sizeof(uint8_t) * 2U);  // width_ and confidence_
    }

    template <typename S>
    void SerializeAttributes(S& serializer) const
    {
        serializer << static_cast<uint8_t>(style_) << static_cast<uint8_t>(color_) << width_ << confidence_
                   << holo::serialization::align;
    }

    template <typename D>
    void DeserializeAttributes(D& deserializer)
    {
        uint8_t style, color;
        deserializer >> style >> color >> width_ >> confidence_ >> holo::serialization::align;
        style_ = static_cast<BoundaryStyle>(style);
        color_ = static_cast<BoundaryColor>(color);
    }

    std::shared_ptr<CurveType> GetCurvePtr() noexcept
    {
        return curve_;
    }

    std::shared_ptr<CurveType const> GetCurvePtr() const noexcept
    {
        return curve_;
    }

    uint32_t GetCurveIndex() const noexcept
    {
        return curve_index_;
    }

    void SetCurvePtr(std::shared_ptr<CurveType> value) noexcept
    {
        curve_ = value;
    }

    void SetCurveIndex(uint32_t index) noexcept
    {
        curve_index_ = index;
    }

    uint32_t GetIndex() const noexcept
    {
        return index_;
    }

    void SetIndex(uint32_t index) noexcept
    {
        index_ = index;
    }

private:
    std::shared_ptr<CurveType> curve_;  ///< The referenced curve object
    size_t                     start_;  ///< Start knot index of this boundary
    size_t                     end_;    ///< End knot index of this boundary

    uint32_t curve_index_;
    uint32_t index_;

    BoundaryStyle style_;       ///< boundary style
    BoundaryColor color_;       ///< boundary color
    uint8_t       width_;       ///< width of this boundary. 0 mean unknown. Unit: cm.
    uint8_t       confidence_;  ///< confidence of this boundary. Unit: %.
};

/**
 * @brief Polynomial curve type lane boundary.
 *
 * @tparam T ScalarType of polynomial
 * @tparam Degree Degree value of polynomial
 */
template <typename T, size_t Degree>
class LaneBoundary<holo::numerics::Polynomial<T, Degree>>
{
public:
    using ScalarType = T;
    using PointType  = holo::geometry::Point2T<ScalarType>;
    using CurveType  = holo::numerics::Polynomial<ScalarType, Degree>;

    /**
     * @brief Construct with curve object.
     *
     * @param curve The curve object.
     */
    LaneBoundary(CurveType curve, ScalarType start = static_cast<ScalarType>(0),
                 ScalarType end = static_cast<ScalarType>(0))
      : curve_(curve)
      , start_(start)
      , end_(end)
      , style_(BoundaryStyle::UNKNOWN)
      , color_(BoundaryColor::UNKNOWN)
      , width_(0U)
      , confidence_(0U)
    {
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
        derivatives[0U] = curve_.template GetDerivative<1>(start_);
        derivatives[1U] = curve_.template GetDerivative<1>((2 * start_ + end_) / 3);
        derivatives[2U] = curve_.template GetDerivative<1>((start_ + 2 * end_) / 3);
        derivatives[3U] = curve_.template GetDerivative<1>(end_);
        return (end_ - start_) / 8 *
               (sqrt(1 + derivatives[0U] * derivatives[0U]) + 3 * sqrt(1 + derivatives[1U] * derivatives[1U]) +
                3 * sqrt(1 + derivatives[2U] * derivatives[2U]) + sqrt(1 + derivatives[3U] * derivatives[3U]));
    }

    /**
     * @brief Set boundary coordinate range
     *
     * @param start Start coordinate
     * @param end End coordinate
     */
    void SetCoordinateRange(ScalarType start, ScalarType end)
    {
        if (!(start < end))
        {
            throw holo::exception::OutOfRangeException("");
        }
        start_ = start;
        end_   = end;
    }
    /**
     * @brief Get x coordinate range of this boundary
     *
     * @return start, end coordinate pair
     */
    std::pair<ScalarType, ScalarType> GetCoordinateRange() const noexcept
    {
        return std::pair<ScalarType, ScalarType>(start_, end_);
    }

    /**
     * @brief Get D-th derivative of boundary by arc length
     * @details As in most cases the polynomial in defined section is near to linear. Here use ratio of arc length to
     * approximate ratio of coordinate x.
     *
     * @tparam D Derivative order
     * @param len length to start of boundary
     *
     * @return Derivative value
     */
    template <size_t D>
    PointType GetDerivativeByArcLength(ScalarType len) const
    {
        assert(len <= GetLength());

        ScalarType t = len / GetLength();
        ScalarType x = (1 - t) * start_ + t * end_;
        return PointType(x, curve_.template GetDerivative<D>(x));
    }

    /**
     * @brief Get sample point of boundary by arc length
     * @details As in most cases the polynomial in defined section is near to linear. Here use ratio of arc length to
     * approximate ratio of coordinate x.
     *
     * @param len length to start of boundary
     *
     * @return Sample point
     */
    PointType GetSampleByArcLength(ScalarType len) const
    {
        assert(len <= GetLength());

        ScalarType t = len / GetLength();
        ScalarType x = (1 - t) * start_ + t * end_;
        return PointType(x, curve_.GetValue(x));
    }

    /**
     * @brief Get D-th derivative of boundary by x coordinate
     *
     * @param x x coordinate value
     *
     * @return Derivative value
     */
    template <size_t D>
    PointType GetDerivativeByCoordinate(ScalarType x) const
    {
        return PointType(x, curve_.template GetDerivative<D>(x));
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
     * @brief Check if boundary parameters are valid.
     *
     * @return True if boundary is valid otherwise false.
     */
    bool_t IsValid() const noexcept
    {
        if (start_ < end_)
        {
            return true;
        }
        return false;
    }

    /**
     * @brief Get boundary style
     *
     * @return style value
     */
    BoundaryStyle GetStyle() const noexcept
    {
        return style_;
    }

    /**
     * @brief Set boundary style
     *
     * @param value style value
     */
    void SetStyle(BoundaryStyle value) noexcept
    {
        style_ = value;
    }

    /**
     * @brief Get boundary color
     *
     * @return boundary color value
     */
    BoundaryColor GetColor() const noexcept
    {
        return color_;
    }

    /**
     * @brief Set boundary color
     *
     * @param value boundary color value
     */
    void SetColor(BoundaryColor value) noexcept
    {
        color_ = value;
    }

    /**
     * @brief Get width of this boundary
     *
     * @return width in cm.
     */
    uint8_t GetWidth() const noexcept
    {
        return width_;
    }

    /**
     * @brief Set width of this boundary
     *
     * @param width Width in cm
     */
    void SetWidth(uint8_t width) noexcept
    {
        width_ = width;
    }

    /**
     * @brief Get confidence value. Unit: %.
     *
     * @return confidence value
     */
    uint8_t GetConfidence() const noexcept
    {
        return confidence_;
    }

    /**
     * @brief Set confidence value. Unit: %.
     *
     * @param confidence confidence value
     */
    void SetConfidence(uint8_t confidence) noexcept
    {
        confidence_ = confidence;
    }

    /**
     * @brief Check if this lane boundary is predicted
     *
     * @return true if boundary is predicted otherwise false.
     */
    bool_t IsPredicted() const noexcept
    {
        return confidence_ == 0;
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return curve_.template GetSerializedSize<ALIGN>() +
               holo::serialization::AlignedSize<ALIGN>(sizeof(ScalarType) * 2U + sizeof(BoundaryStyle) +
                                                       sizeof(BoundaryColor) + sizeof(uint8_t) * 2U);
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
        serializer << curve_ << static_cast<ScalarType>(start_) << static_cast<ScalarType>(end_)
                   << static_cast<uint8_t>(style_) << static_cast<uint8_t>(color_) << width_ << confidence_
                   << holo::serialization::align;
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
        uint8_t style, color;
        deserializer >> curve_ >> start_ >> end_ >> style >> color >> width_ >> confidence_ >>
            holo::serialization::align;
        style_ = static_cast<BoundaryStyle>(style);
        color_ = static_cast<BoundaryColor>(color);
    }

private:
    CurveType  curve_;  ///< The curve object
    ScalarType start_;  ///< Start coordinate of this boundary
    ScalarType end_;    ///< End coordinate of this boundary

    BoundaryStyle style_;       ///< boundary style
    BoundaryColor color_;       ///< boundary color
    uint8_t       width_;       ///< width of this boundary. 0 mean unknown. Unit: cm.
    uint8_t       confidence_;  ///< confidence of this boundary. Unit: %.
};

}  // namespace common
}  // namespace holo

#endif
