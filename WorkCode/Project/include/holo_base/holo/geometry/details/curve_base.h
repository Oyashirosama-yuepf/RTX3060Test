/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file curve_base.h
 * @brief This header file defines Curve base objects.
 * @author ZhangJiannan(zhangjiannan@holomatic.com)
 * @date 2020-05-18
 */

#ifndef HOLO_GEOMETRY_DETAILS_CURVE_BASE_H_
#define HOLO_GEOMETRY_DETAILS_CURVE_BASE_H_

#include <holo/container/vector.h>
#include <holo/core/exception.h>
#include <holo/geometry/exception.h>
#include <holo/numerics/exception.h>
#include <holo/serialization/serialization.h>

#include "curve_traits.h"

namespace holo
{
namespace geometry
{
/**
 * @addtogroup geometry
 * @{
 */

namespace details
{
/**
 * @brief Boundary condition type of curve.
 */
enum class ConditionType : uint8_t
{
    DEFAULT           = 0U,
    FIRST_DERIVATIVE  = 1U,
    SECOND_DERIVATIVE = 2U,
};
}  // namespace details

/**
 * @brief Base class for all curves
 * @details A base curve is defined by a set of knot points. Knots are points that this curve must pass through.
 *
 * @tparam Point Knot point type.
 * @tparam SIZE Max size of knots this curve can hold.
 */
template <typename Point, size_t SIZE = 256>
class CurveBaseT
{
public:
    static size_t const SIZE_VALUE = SIZE;

    using PointType     = Point;
    using ScalarType    = typename PointType::ScalarType;
    using ContainerType = holo::container::Vector<PointType, SIZE_VALUE>;

    using value_type             = typename ContainerType::value_type;
    using size_type              = typename ContainerType::size_type;
    using difference_type        = typename ContainerType::difference_type;
    using reference              = typename ContainerType::reference;
    using const_reference        = typename ContainerType::const_reference;
    using pointer                = typename ContainerType::pointer;
    using const_pointer          = typename ContainerType::const_pointer;
    using iterator               = typename ContainerType::iterator;
    using const_iterator         = typename ContainerType::const_iterator;
    using reverse_iterator       = typename ContainerType::reverse_iterator;
    using const_reverse_iterator = typename ContainerType::const_reverse_iterator;

    using ConditionType = details::ConditionType;

    /**
     * @brief Default constructor. Creates a curve with empty knots.
     */
    CurveBaseT()
      : knots_{}
      , start_condition_{}
      , end_condition_{}
      , start_type_{ConditionType::DEFAULT}
      , end_type_{ConditionType::DEFAULT}
      , ready_{false}
    {
    }

    /**
     * @brief Construct a curve with knots defined by iterator range [first, last)
     *
     * @tparam InputIt Input iterator type. Value type of InputIt should be PointType
     * @param first Start of iterator range.
     * @param last End of iterator range.
     *
     * @throws std::bad_alloc if last - first > SIZE
     */
    template <typename InputIt>
    CurveBaseT(InputIt first, InputIt last)
      : knots_(first, last)
      , start_condition_{}
      , end_condition_{}
      , start_type_{ConditionType::DEFAULT}
      , end_type_{ConditionType::DEFAULT}
      , ready_{false}
    {
    }

    /**
     * @brief Construct a curve with knots defined by initializer list
     *
     * @param init The initializer list
     *
     * @throws std::bad_alloc if init.size() > SIZE
     */
    CurveBaseT(std::initializer_list<PointType> init)
      : knots_(init)
      , start_condition_{}
      , end_condition_{}
      , start_type_{ConditionType::DEFAULT}
      , end_type_{ConditionType::DEFAULT}
      , ready_{false}
    {
    }

    /**
     * @brief Construct a curve from another curve object.
     *
     * @tparam SIZE_ Knot size of the other curve object.
     * @param other The other curve object.
     */
    template <size_t SIZE_>
    CurveBaseT(CurveBaseT<PointType, SIZE_> const& other)
      : knots_(other.knots_)
      , start_condition_{other.start_condition_}
      , end_condition_{other.end_condition_}
      , start_type_{other.start_type_}
      , end_type_{other.end_type_}
      , ready_{false}
    {
    }

    /**
     * @brief Construct a curve from another curve object.
     *
     * @tparam SIZE_ Knot size of the other curve object.
     * @param other The other curve object.
     */
    template <size_t SIZE_>
    CurveBaseT(CurveBaseT<PointType, SIZE_>&& other)
      : knots_(std::move(other.knots_))
      , start_condition_{std::move(other.start_condition_)}
      , end_condition_{std::move(other.end_condition_)}
      , start_type_{std::move(other.start_type_)}
      , end_type_{std::move(other.end_type_)}
      , ready_{false}
    {
    }

    /**
     * @brief Access a curve knot with bound check.
     *
     * @param pos Index of the knot
     *
     * @return Reference to the knot
     *
     * @throws holo::exception::OutOfRangeException if pos >= size()
     */
    const_reference at(size_type pos) const
    {
        return knots_.at(pos);
    }

    /**
     * @brief Access a curve knot without bound check.
     *
     * @param pos Index of the knot.
     *
     * @return Reference to the knot
     */
    const_reference operator[](size_type pos) const
    {
        return knots_[pos];
    }

    /**
     * @brief Access the first knot
     *
     * @return Reference to first knot
     */
    const_reference front() const
    {
        return knots_.front();
    }

    /**
     * @brief Access the last knot
     *
     * @return Reference to last knot
     */
    const_reference back() const
    {
        return knots_.back();
    }

    /**
     * @brief Get iterator to the begining
     *
     * @return Iterator to the beginning
     */
    const_iterator begin() const noexcept
    {
        return knots_.begin();
    }

    /**
     * @brief Get iterator to the begining
     *
     * @return Iterator to the beginning
     */
    const_iterator cbegin() const noexcept
    {
        return knots_.cbegin();
    }

    /**
     * @brief Get iterator to the end
     *
     * @return Iterator to the end
     */
    const_iterator end() const noexcept
    {
        return knots_.end();
    }

    /**
     * @brief Get iterator to the end
     *
     * @return Iterator to the end
     */
    const_iterator cend() const noexcept
    {
        return knots_.cend();
    }

    /**
     * @brief Get reverse iterator to the begining
     *
     * @return Reverse iterator to the beginning
     */
    const_reverse_iterator rbegin() const noexcept
    {
        return knots_.rbegin();
    }

    /**
     * @brief Get reverse iterator to the begining
     *
     * @return Reverse iterator to the beginning
     */
    const_reverse_iterator crbegin() const noexcept
    {
        return knots_.crbegin();
    }

    /**
     * @brief Get reverse iterator to the end
     *
     * @return Reverse iterator to the end
     */
    const_reverse_iterator rend() const noexcept
    {
        return knots_.rend();
    }

    /**
     * @brief Get reverse iterator to the end
     *
     * @return Reverse iterator to the end
     */
    const_reverse_iterator crend() const noexcept
    {
        return knots_.crend();
    }

    /**
     * @brief Check if knots are empty
     *
     * @return true if there are no knots defined.
     */
    bool_t empty() const noexcept
    {
        return knots_.empty();
    }

    /**
     * @brief Get number of knots in the curve
     *
     * @return Number of knots
     */
    size_t size() const noexcept
    {
        return knots_.size();
    }

    /**
     * @brief Get maximum possible number of knots
     *
     * @return Maximum possible number of knots
     */
    size_t max_size() const noexcept
    {
        return knots_.max_size();
    }

    /**
     * @brief Get number of knots that can be held in currently allocated storage
     *
     * @return Number of knots.
     */
    size_t capacity() const noexcept
    {
        return knots_.capacity();
    }

    /**
     * @brief Clear all knots
     */
    void clear()
    {
        knots_.clear();
        ready_ = false;
    }

    /**
     * @brief Remove knot at pos
     *
     * @param pos Iterator pointing to the knot to remove
     *
     * @return Iterator following the last removed knot. If pos refers to last knot, then the end() iterator is
     * returned.
     */
    const_iterator erase(const_iterator pos)
    {
        ready_ = false;
        return knots_.erase(pos);
    }

    /**
     * @brief Remove knot in the range [first, last)
     *
     * @param first Start of range to remove knots
     * @param last End of range to remove knots
     *
     * @return Iterator following the last removed element. If last == end(), then the updated end() iterator is
     * returned. If [first, last) is an empty range, then last is returned.
     */
    const_iterator erase(const_iterator first, const_iterator last)
    {
        if (first == last)
        {
            return last;
        }
        ready_ = false;
        return knots_.erase(first, last);
    }

    /**
     * @brief Removes the last element.
     */
    void pop_back()
    {
        ready_ = false;
        return knots_.pop_back();
    }

    /**
     * @brief Check if a curve is valid.
     *
     * @return true if curve is valid otherwise false.
     */
    bool_t IsValid() const noexcept
    {
        return !(knots_.size() < 2);
    }

    /**
     * @brief Check if a curve is ready
     *
     * @return true if curve is ready otherwise false.
     */
    bool_t IsReady() const noexcept
    {
        return ready_;
    }

    /**
     * @brief Get curve start condition type
     *
     * @return Start condition type
     */
    ConditionType GetStartType() const noexcept
    {
        return start_type_;
    }

    /**
     * @brief Get curve end condition type
     *
     * @return End condition type
     */
    ConditionType GetEndType() const noexcept
    {
        return end_type_;
    }

    /**
     * @brief Get start condition
     *
     * @return Start condition
     */
    PointType const& GetStartCondition() const noexcept
    {
        return start_condition_;
    }

    /**
     * @brief Get end condition
     *
     * @return End condition
     */
    PointType const& GetEndCondition() const noexcept
    {
        return end_condition_;
    }

    /**
     * @brief Set curve start condition
     *
     * @param type Type of start condition
     * @param condition Value of start condition.
     */
    void SetStartCondition(ConditionType type, PointType const& condition) noexcept
    {
        start_type_      = type;
        start_condition_ = condition;
    }

    /**
     * @brief Set curve end condition
     *
     * @param type Type of end condition
     * @param condition Value of end condition.
     */
    void SetEndCondition(ConditionType type, PointType const& condition) noexcept
    {
        end_type_      = type;
        end_condition_ = condition;
    }

    template <typename T_, size_t SIZE_>
    friend class CurveBaseT;

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        uint32_t count        = knots_.size();
        size_t   aligned_size = holo::serialization::AlignedSize<ALIGN>(sizeof(count)) +
                              count * knots_[0U].template GetSerializedSize<ALIGN>() +
                              holo::serialization::AlignedSize<ALIGN>(2U * sizeof(ConditionType));
        if (start_type_ != holo::geometry::details::ConditionType::DEFAULT)
        {
            aligned_size += this->start_condition_.template GetSerializedSize<ALIGN>();
        }

        if (end_type_ != holo::geometry::details::ConditionType::DEFAULT)
        {
            aligned_size += this->end_condition_.template GetSerializedSize<ALIGN>();
        }
        return holo::serialization::AlignedSize<ALIGN>(aligned_size);
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        uint32_t count = knots_.size();
        serializer << count;
        for (std::size_t i = 0; i < count; ++i)
        {
            serializer << this->knots_[i];
        }

        serializer << static_cast<holo::uint8_t>(start_type_) << static_cast<holo::uint8_t>(end_type_);

        if (start_type_ != holo::geometry::details::ConditionType::DEFAULT)
        {
            serializer << static_cast<holo::uint8_t>(1U);
        }

        if (end_type_ != holo::geometry::details::ConditionType::DEFAULT)
        {
            serializer << static_cast<holo::uint8_t>(1U);
        }

        if (start_type_ != holo::geometry::details::ConditionType::DEFAULT)
        {
            serializer << start_condition_;
        }

        if (end_type_ != holo::geometry::details::ConditionType::DEFAULT)
        {
            serializer << end_condition_;
        }

        serializer << holo::serialization::align;
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        uint32_t count = 0;
        deserializer >> count >> holo::serialization::align;
        this->knots_.resize(count);
        for (std::size_t i = 0; i < count; ++i)
        {
            deserializer >> this->knots_[i];
        }

        holo::uint8_t value = 0;
        deserializer >> value;
        start_type_ = static_cast<ConditionType>(value);
        deserializer >> value >> holo::serialization::align;
        end_type_ = static_cast<ConditionType>(value);

        if (start_type_ != holo::geometry::details::ConditionType::DEFAULT)
        {
            deserializer >> this->start_condition_;
        }
        if (end_type_ != holo::geometry::details::ConditionType::DEFAULT)
        {
            deserializer >> this->end_condition_;
        }
        deserializer >> holo::serialization::align;
        ready_ = false;
    }

protected:
    /**
     * @brief Default destructor.
     */
    ~CurveBaseT() = default;

    ContainerType knots_;            ///< knots of this curve
    PointType     start_condition_;  ///< start condition value
    PointType     end_condition_;    ///< end condition value
    ConditionType start_type_;       ///< start condition type
    ConditionType end_type_;         ///< end condition type
    bool_t        ready_;            ///< ready flag used to indicate if internal state of the curve is ready.
};

/**
 * @brief Base class for all parametric form curves
 * @details For parametric form curves, there is no limitations on order of knots and value of knots.
 *
 * @tparam Point Knot point type
 * @tparam SIZE Maximum number of knot
 */
template <typename Point, size_t SIZE = 256>
class CurveParametricBaseT : public CurveBaseT<Point, SIZE>
{
public:
    static size_t const SIZE_VALUE = SIZE;

    using PointType  = Point;
    using ScalarType = typename PointType::ScalarType;
    using Base       = CurveBaseT<Point, SIZE>;

    // Inherit constructors from base class.
    using Base::CurveBaseT;

    using value_type             = typename Base::value_type;
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
    CurveParametricBaseT() = default;

    /**
     * @brief Construct a curve from another curve object.
     *
     * @tparam SIZE_ Knot size of the other curve object.
     * @param other The other curve object.
     */
    template <size_t SIZE_>
    CurveParametricBaseT(CurveBaseT<PointType, SIZE_> const& other) : Base{other}
    {
    }

    /**
     * @brief Construct a curve from another curve object.
     *
     * @tparam SIZE_ Knot size of the other curve object.
     * @param other The other curve object.
     */
    template <size_t SIZE_>
    CurveParametricBaseT(CurveBaseT<PointType, SIZE_>&& other) : Base{std::move(other)}
    {
    }

    /**
     * @brief Replace knots with copies of those in the range [first, last)
     *
     * @tparam InputIt Input iterator type.
     * @param first Start of range to copy knots
     * @param last End of range to copy knots
     *
     * @throws std::bad_alloc if last - first > SIZE
     */
    template <typename InputIt>
    void assign(InputIt first, InputIt last)
    {
        this->knots_.assign(first, last);
        this->ready_ = false;
    }

    /**
     * @brief Replace knots with those identified by initializer list
     *
     * @param ilist The initializer list
     *
     * @throws std::bad_alloc if ilist.size() > SIZE
     */
    void assign(std::initializer_list<PointType> ilist)
    {
        this->knots_.assign(ilist);
        this->ready_ = false;
    }

    /**
     * @brief insert value before pos
     *
     * @param pos Iterator to insert value before
     * @param value The value to insert
     *
     * @return iterator to inserted element
     *
     * @throws std::bad_alloc if number of knots exceeded the maximum size.
     */
    const_iterator insert(const_iterator pos, PointType const& value)
    {
        this->ready_ = false;
        return this->knots_.insert(pos, value);
    }

    /**
     * @brief insert value before pos
     *
     * @param pos Iterator to insert value before
     * @param value The value to insert
     *
     * @return iterator to inserted element
     *
     * @throws std::bad_alloc if number of knots exceeded the maximum size.
     */
    const_iterator insert(const_iterator pos, PointType&& value)
    {
        this->ready_ = false;
        return this->knots_.insert(pos, std::move(value));
    }

    /**
     * @brief Inserts knots from range [first, last) before pos
     *
     * @tparam InputIt Input iterator type.
     * @param pos Iterator to insert value before
     * @param first Start of range to inserted knots
     * @param last End of range to inserted knots
     *
     * @return iterator pointing to the first knot inserted or pos if first == last
     *
     * @throws std::bad_alloc if container size + (last - first) > SIZE.
     */
    template <typename InputIt>
    const_iterator insert(const_iterator pos, InputIt first, InputIt last)
    {
        if (first == last)
        {
            return pos;
        }
        this->ready_ = false;
        return this->knots_.insert(pos, first, last);
    }

    /**
     * @brief Inserts knots from initializer list before pos
     *
     * @param pos Iterator to insert value before
     * @param ilist The initializer list
     *
     * @return iterator pointing to the first knot inserted or pos if ilist is empty
     *
     * @throws std::bad_alloc if container size + ilist.size() > SIZE.
     */
    const_iterator insert(const_iterator pos, std::initializer_list<PointType> ilist)
    {
        if (ilist.size() == 0)
        {
            return pos;
        }
        this->ready_ = false;
        return this->knots_.insert(pos, ilist);
    }

    /**
     * @brief Construct knot in-place
     *
     * @tparam Args Types of arguments
     * @param pos Iterator to insert value before
     * @param args arguments to forward to the constructor of the knot point
     *
     * @return iterator pointing to the emplaced knot
     *
     * @throws std::bad_alloc if number of knots exceeded the maximum size.
     */
    template <typename... Args>
    const_iterator emplace(const_iterator pos, Args&&... args)
    {
        this->ready_ = false;
        return this->knots_.emplace(pos, std::forward<Args>(args)...);
    }

    /**
     * @brief Adds a knot to the end
     *
     * @param value The knot to add at the end
     *
     * @throws std::bad_alloc if number of knots exceeded the maximum size.
     */
    void push_back(PointType const& value)
    {
        this->ready_ = false;
        this->knots_.push_back(value);
    }

    /**
     * @brief Adds a knot to the end
     *
     * @param value The knot to add at the end
     */
    void push_back(PointType&& value)
    {
        this->ready_ = false;
        this->knots_.push_back(std::move(value));
    }

    /**
     * @brief Construct an knot in-place at the end
     *
     * @tparam Args Types of arguments
     * @param args arguments to forward to the constructor of the knot point
     */
    template <typename... Args>
    void emplace_back(Args&&... args)
    {
        this->ready_ = false;
        this->knots_.emplace_back(std::forward<Args>(args)...);
    }

    /**
     * @brief Update a knot value
     *
     * @param pos iterator pointing to the knot to update. If pos == end(), nothing will be performed.
     * @param pt new knot value
     *
     * @return const_iterator pointing to updated knot.
     */
    const_iterator UpdateKnot(const_iterator pos, PointType const& pt) noexcept
    {
        if (pos != this->end())
        {
            this->ready_       = false;
            size_t dist        = std::distance(this->begin(), pos);
            this->knots_[dist] = pt;
        }
        return pos;
    }

    /**
     * @brief Update a knot value
     *
     * @param pos iterator pointing to the knot to update. If pos == end(), nothing will be performed.
     * @param pt new knot value
     *
     * @return const_iterator pointing to updated knot.
     */
    const_iterator UpdateKnot(const_iterator pos, PointType&& pt) noexcept
    {
        if (pos != this->end())
        {
            this->ready_       = false;
            size_t dist        = std::distance(this->begin(), pos);
            this->knots_[dist] = std::move(pt);
        }
        return pos;
    }

protected:
    /**
     * @brief Default destructor
     */
    ~CurveParametricBaseT() = default;
};

/**
 * @brief Base class for all explicit form curves
 * @details For explicit form curves. The x value of knots must be in ascending order. Order check will be performed
 * when new knots are added to curve.
 *
 * @tparam Point Knot point type
 * @tparam SIZE Maxium number of knots
 */
template <typename Point, size_t SIZE = 256>
class CurveExplicitBaseT : public CurveBaseT<Point, SIZE>
{
public:
    static size_t const SIZE_VALUE = SIZE;

    using PointType  = Point;
    using ScalarType = typename PointType::ScalarType;
    using Base       = CurveBaseT<Point, SIZE>;

    using value_type             = typename Base::value_type;
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
    CurveExplicitBaseT() = default;

    /**
     * @brief Construct a curve with knots defined by iterator range [first, last)
     *
     * @tparam InputIt Input iterator type. Value type of InputIt should be PointType
     * @param first Start of iterator range.
     * @param last End of iterator range.
     *
     * @throws std::bad_alloc if last - first > SIZE
     * @throws holo::exception::BadKnotOrderException if x values of knots in range [first, last) is not in ascending
     * order.
     */
    template <typename InputIt>
    CurveExplicitBaseT(InputIt first, InputIt last) : Base(first, last)
    {
        if (first != last)
        {
            checkKnotOrder(first, last);
        }
    }

    /**
     * @brief Construct a curve with knots defined by initializer list
     *
     * @param init The initializer list
     *
     * @throws std::bad_alloc if init.size() > SIZE
     * @throws holo::exception::BadKnotOrderException if x values of knots in init is not in ascending order.
     */
    CurveExplicitBaseT(std::initializer_list<PointType> init) : Base(init)
    {
        if (init.size() > 0)
        {
            checkKnotOrder(init.begin(), init.end());
        }
    }

    /**
     * @brief Construct a curve from another curve object.
     *
     * @tparam SIZE_ Knot size of the other curve object.
     * @param other The other curve object.
     *
     * @throws std::bad_alloc if other.size() > SIZE
     * @throws holo::exception::BadKnotOrderException if x values of knots in other is not in ascending order.
     */
    template <size_t SIZE_>
    CurveExplicitBaseT(CurveBaseT<PointType, SIZE_> const& other) : Base(other)
    {
        if (!this->empty())
        {
            checkKnotOrder(other.begin(), other.end());
        }
    }

    /**
     * @brief Construct a curve from another curve object.
     *
     * @tparam SIZE_ Knot size of the other curve object.
     * @param other The other curve object.
     *
     * @throws std::bad_alloc if other.size() > SIZE
     * @throws holo::exception::BadKnotOrderException if x values of knots in other is not in ascending order.
     */
    template <size_t SIZE_>
    CurveExplicitBaseT(CurveBaseT<PointType, SIZE_>&& other) : Base(std::move(other))
    {
        if (!this->empty())
        {
            checkKnotOrder(this->begin(), this->end());
        }
    }

    /**
     * @brief Replace knots with copies of thoes in the range [first, last)
     *
     * @tparam InputIt Input iterator type.
     * @param first Start of range to copy knots
     * @param last End of range to copy knots
     *
     * @throws std::bad_alloc if last - first > SIZE
     * @throws holo::exception::BadKnotOrderException if x values of knots in range [first, last) is not in ascending
     * order.
     */
    template <typename InputIt>
    void assign(InputIt first, InputIt last)
    {
        if (first != last)
        {
            checkKnotOrder(first, last);
        }
        this->ready_ = false;
        this->knots_.assign(first, last);
    }

    /**
     * @brief Replace knots with those identified by initializer list
     *
     * @param ilist The initializer list
     *
     * @throws std::bad_alloc if ilist.size() > SIZE
     * @throws holo::exception::BadKnotOrderException if x values of knots in ilist is not in ascending order.
     */
    void assign(std::initializer_list<PointType> ilist)
    {
        if (ilist.size() > 0)
        {
            checkKnotOrder(ilist.begin(), ilist.end());
        }
        this->ready_ = false;
        this->knots_.assign(ilist);
    }

    /**
     * @brief insert value before pos
     *
     * @param pos Iterator to insert value before
     * @param value The value to insert
     *
     * @return iterator to inserted element
     *
     * @throws std::bad_alloc if number of knots exceeded the maximum size.
     * @throws holo::exception::BadKnotOrderException if inserted value will break the knots ascending order.
     */
    const_iterator insert(const_iterator pos, PointType const& value)
    {
        if (this->empty())
        {
            return this->knots_.insert(pos, value);
        }
        if (pos == this->begin())
        {
            if ((*pos)[0U] <= value[0U])
            {
                throw exception::BadKnotOrderException();
            }
        }
        else if (pos == this->end())
        {
            if ((*(pos - 1))[0U] >= value[0U])
            {
                throw exception::BadKnotOrderException();
            }
        }
        else
        {
            if (((*pos)[0U] <= value[0U]) || ((*(pos - 1))[0U] >= value[0U]))
            {
                throw exception::BadKnotOrderException();
            }
        }
        this->ready_ = false;
        return this->knots_.insert(pos, value);
    }

    /**
     * @brief insert value before pos
     *
     * @param pos Iterator to insert value before
     * @param value The value to insert
     *
     * @return iterator to inserted element
     *
     * @throws std::bad_alloc if number of knots exceeded the maximum size.
     * @throws holo::exception::BadKnotOrderException if inserted value will break the knots ascending order.
     */
    const_iterator insert(const_iterator pos, PointType&& value)
    {
        if (this->empty())
        {
            return this->knots_.insert(pos, std::move(value));
        }
        if (pos == this->begin())
        {
            if ((*pos)[0U] <= value[0U])
            {
                throw exception::BadKnotOrderException();
            }
        }
        else if (pos == this->end())
        {
            if ((*(pos - 1))[0U] >= value[0U])
            {
                throw exception::BadKnotOrderException();
            }
        }
        else
        {
            if (((*pos)[0U] <= value[0U]) || ((*(pos - 1))[0U] >= value[0U]))
            {
                throw exception::BadKnotOrderException();
            }
        }
        this->ready_ = false;
        return this->knots_.insert(pos, std::move(value));
    }

    /**
     * @brief Inserts knots from range [first, last) before pos
     *
     * @tparam InputIt Input iterator type.
     * @param pos Iterator to insert value before
     * @param first Start of range to inserted knots
     * @param last End of range to inserted knots
     *
     * @return iterator pointing to the first knot inserted or pos if first == last
     *
     * @throws std::bad_alloc if container size + (last - first) > SIZE.
     * @throws holo::exception::BadKnotOrderException if inserted values will break the knots ascending order.
     */
    template <typename InputIt>
    const_iterator insert(const_iterator pos, InputIt first, InputIt last)
    {
        if (first == last)
        {
            return pos;
        }
        checkKnotOrder(first, last);
        if (this->empty())
        {
            return this->knots_.insert(pos, first, last);
        }
        if (pos == this->begin())
        {
            if ((*pos)[0U] <= (*(last - 1))[0U])
            {
                throw exception::BadKnotOrderException();
            }
        }
        else if (pos == this->end())
        {
            if ((*(pos - 1))[0U] >= (*first)[0U])
            {
                throw exception::BadKnotOrderException();
            }
        }
        else
        {
            if (((*pos)[0U] <= (*(last - 1))[0U]) || ((*(pos - 1))[0U] >= (*first)[0U]))
            {
                throw exception::BadKnotOrderException();
            }
        }
        this->ready_ = false;
        return this->knots_.insert(pos, first, last);
    }

    /**
     * @brief Inserts knots from initializer list before pos
     *
     * @param pos Iterator to insert value before
     * @param ilist The initializer list
     *
     * @return iterator pointing to the first knot inserted or pos if ilist is empty
     *
     * @throws std::bad_alloc if container size + ilist.size() > SIZE.
     * @throws holo::exception::BadKnotOrderException if inserted values will break the knots ascending order.
     */
    const_iterator insert(const_iterator pos, std::initializer_list<PointType> ilist)
    {
        if (ilist.size() == 0U)
        {
            return pos;
        }
        checkKnotOrder(ilist.begin(), ilist.end());
        if (this->empty())
        {
            return this->knots_.insert(pos, ilist);
        }
        if (pos == this->begin())
        {
            if ((*pos)[0U] <= (*(ilist.end() - 1))[0U])
            {
                throw exception::BadKnotOrderException();
            }
        }
        else if (pos == this->end())
        {
            if ((*(pos - 1))[0U] >= (*ilist.begin())[0U])
            {
                throw exception::BadKnotOrderException();
            }
        }
        else
        {
            if (((*pos)[0U] <= (*(ilist.end() - 1))[0U]) || ((*(pos - 1))[0U] >= (*ilist.begin())[0U]))
                throw exception::BadKnotOrderException();
        }
        this->ready_ = false;
        return this->knots_.insert(pos, ilist);
    }

    /**
     * @brief Construct knot in-place
     *
     * @tparam Args Types of arguments
     * @param pos Iterator to insert value before
     * @param args arguments to forward to the constructor of the knot point
     *
     * @return iterator pointing to the emplaced knot
     *
     * @throws std::bad_alloc if number of knots exceeded the maximum size.
     * @throws holo::exception::BadKnotOrderException if emplaced value will break the knots ascending order.
     */
    template <typename... Args>
    const_iterator emplace(const_iterator pos, Args&&... args)
    {
        PointType pt(std::forward<Args>(args)...);
        return insert(pos, std::move(pt));
    }

    /**
     * @brief Adds a knot to the end
     *
     * @param value The knot to add at the end
     *
     * @throws std::bad_alloc if number of knots exceeded the maximum size.
     * @throws holo::exception::BadKnotOrderException if inserted value will break the knots ascending order.
     */
    void push_back(PointType const& value)
    {
        if (this->empty())
        {
            this->knots_.push_back(value);
        }
        else
        {
            if ((this->back())[0] >= value[0])
            {
                throw exception::BadKnotOrderException();
            }
            this->ready_ = false;
            this->knots_.push_back(value);
        }
    }

    /**
     * @brief Adds a knot to the end
     *
     * @param value The knot to add at the end
     *
     * @throws std::bad_alloc if number of knots exceeded the maximum size.
     * @throws holo::exception::BadKnotOrderException if inserted value will break the knots ascending order.
     */
    void push_back(PointType&& value)
    {
        if (this->empty())
        {
            this->knots_.push_back(std::move(value));
        }
        else
        {
            if ((this->back())[0] >= value[0])
            {
                throw exception::BadKnotOrderException();
            }
            this->ready_ = false;
            this->knots_.push_back(std::move(value));
        }
    }

    /**
     * @brief Construct an knot in-place at the end
     *
     * @tparam Args Types of arguments
     * @param args arguments to forward to the constructor of the knot point
     *
     * @throws std::bad_alloc if number of knots exceeded the maximum size.
     * @throws holo::exception::BadKnotOrderException if inserted value will break the knots ascending order.
     */
    template <typename... Args>
    void emplace_back(Args&&... args)
    {
        PointType pt(std::forward<Args>(args)...);
        push_back(std::move(pt));
    }

    /**
     * @brief Update a knot value
     *
     * @param pos iterator pointing to the knot to update. If pos == end(), nothing will be performed.
     * @param pt new knot value
     *
     * @return const_iterator pointing to updated knot.
     */
    const_iterator UpdateKnot(const_iterator pos, PointType const& pt)
    {
        if (pos != this->end())
        {
            if (this->size() > 1)
            {
                if (pos == this->begin())
                {
                    if ((*(pos + 1))[0U] <= pt[0U])
                    {
                        throw exception::BadKnotOrderException();
                    }
                }
                else if (pos == (this->end() - 1))
                {
                    if ((*(pos - 1))[0U] >= pt[0U])
                    {
                        throw exception::BadKnotOrderException();
                    }
                }
                else
                {
                    if (((*(pos + 1))[0U] <= pt[0U]) || ((*(pos - 1))[0U] >= pt[0U]))
                        throw exception::BadKnotOrderException();
                }
            }
            this->ready_       = false;
            size_t dist        = std::distance(this->begin(), pos);
            this->knots_[dist] = pt;
        }
        return pos;
    }

    /**
     * @brief Update a knot value
     *
     * @param pos iterator pointing to the knot to update. If pos == end(), nothing will be performed.
     * @param pt new knot value
     *
     * @return const_iterator pointing to updated knot.
     */
    const_iterator UpdateKnot(const_iterator pos, PointType&& pt)
    {
        if (pos != this->end())
        {
            if (this->size() > 1)
            {
                if (pos == this->begin())
                {
                    if ((*(pos + 1))[0U] <= pt[0U])
                    {
                        throw exception::BadKnotOrderException();
                    }
                }
                else if (pos == (this->end() - 1))
                {
                    if ((*(pos - 1))[0U] >= pt[0U])
                    {
                        throw exception::BadKnotOrderException();
                    }
                }
                else
                {
                    if (((*(pos + 1))[0U] <= pt[0U]) || ((*(pos - 1))[0U] >= pt[0U]))
                        throw exception::BadKnotOrderException();
                }
            }
            this->ready_       = false;
            size_t dist        = std::distance(this->begin(), pos);
            this->knots_[dist] = std::move(pt);
        }
        return pos;
    }

protected:
    /**
     * @brief Check if x values of knots in range [first, last) is in ascending order.
     *
     * @tparam InputIt Input iterator type
     * @param first Start of knots range
     * @param last End of knots range
     */
    template <typename InputIt>
    void checkKnotOrder(InputIt first, InputIt last) const
    {
        while (first != last - 1)
        {
            if ((*first)[0U] >= (*(first + 1))[0U])
            {
                throw exception::BadKnotOrderException();
            }
            ++first;
        }
    }

    /**
     * @brief Default destructor
     */
    ~CurveExplicitBaseT() = default;
};

/**
 * @brief Parametric form curve object.
 *
 * @tparam Point Point type of this curve
 * @tparam SIZE Maximum knot point number
 * @tparam Algorithm Algorithm related to this curve.
 *
 * Algorithm type shall provide following members:
 * - Member type
 *   - ScalarType Scalar type
 *   - PointType Point type of the curve
 *   - StateType State data of the curve
 *   - TagType Tag of the algorithm. Must be CurveParametricTag
 * - Member constant
 *   - DEGREE_VALUE degree of the curve
 * - Member functions
 *   - bool Update(CurveBaseT<PointType, SIZE_VALUE> const&, StateType&);
 *   - ScalarType GetLength(CurveBaseT<PointType, SIZE_VALUE> const&, StateType const&, size_t idx)
 *   - template <size_t D> PointType GetDerivativeByArcLength(CurveBaseT<PointType, SIZE_VALUE> const&, StateType
 * const&, ScalarType len)
 *   - template <size_t D, typename InputIt, typename OutputIt>
 *   void GetDerivativeByArcLength(CurveBaseT<PointType, SIZE_VALUE> const&, StateType const&, InputIt first, InputIt
 * last, OutputIt out)
 *
 * @details Parametric curve is represented by
 * @f{equation}{
 * C_i(t) = \left\{
 *   \begin{array}{rcl}
 *     x = f_{i,x}(t) & & t \in [0,1] \\
 *     y = f_{i,y}(t) & & t \in [0,1] \\
 *     z = f_{i,z}(t) & & t \in [0,1] \\
 *     \cdots
 *   \end{array} \right.
 * @f}
 * where @f$C_i@f$ denotes i-th curve between i-th knot and (i+1)th knot.
 *
 */
template <typename Point, size_t SIZE, typename Algorithm,
          typename std::enable_if<std::is_same<typename Algorithm::TagType, CurveParametricTag>::value>::type* =
              nullptr>
class CurveParametric : public CurveParametricBaseT<Point, SIZE>
{
public:
    using Base = CurveParametricBaseT<Point, SIZE>;
    using Base::CurveParametricBaseT;

    using ScalarType    = typename Point::ScalarType;
    using PointType     = Point;
    using AlgorithmType = Algorithm;
    using StateType     = typename AlgorithmType::StateType;
    using TagType       = typename AlgorithmType::TagType;

    /**
     * @brief Get length of this curve
     *
     * @return length of this curve
     */
    ScalarType GetLength() const
    {
        if (!this->IsReady())
        {
            throw holo::exception::BadCurveStateException();
        }
        return algorithm_.GetLength(*this, state_, (*this).size() - 1);
    }

    /**
     * @brief Get arc length to start of idx-th knot
     *
     * @return Arc length to start of idx-th knot
     */
    ScalarType GetLength(size_t idx) const
    {
        if (!this->IsReady())
        {
            throw holo::exception::BadCurveStateException();
        }
        return algorithm_.GetLength(*this, state_, idx);
    }

    /**
     * @brief Get D-th derivative of curve at given arc length
     *
     * @tparam D Derivative order
     * @param len Length of arc.
     *
     * @return D-th derivative of the curve at arc length
     */
    template <size_t D>
    PointType GetDerivativeByArcLength(ScalarType len) const
    {
        if (!this->IsReady())
        {
            throw holo::exception::BadCurveStateException();
        }
        return algorithm_.template GetDerivativeByArcLength<D>(*this, state_, len);
    }

    /**
     * @brief Get D-th derivative of curve at sequence of arc lengths defined in range [first, last)
     *
     * @tparam InputIt iterator with value_type of ScalarType.
     * @tparam OutputIt iterator with value type of PointType.
     * @param first Start of input range.
     * @param last End of input range
     * @param out Iterator to sampled curve points.
     */
    template <size_t D, typename InputIt, typename OutputIt>
    void GetDerivativeByArcLength(InputIt first, InputIt last, OutputIt out) const
    {
        if (!this->IsReady())
        {
            throw holo::exception::BadCurveStateException();
        }
        algorithm_.template GetDerivativeByArcLength<D>(*this, state_, first, last, out);
    }

    /**
     * @brief Get point on curve at given arc length
     *
     * @param len Length of arc.
     *
     * @return Point on curve
     */
    PointType GetSampleByArcLength(ScalarType len) const
    {
        return GetDerivativeByArcLength<0>(len);
    }

    /**
     * @brief Get points on curve at sequence of arc lengths defined in range [first, last)
     *
     * @tparam InputIt iterator with value_type of ScalarType.
     * @tparam OutputIt iterator with value type of PointType.
     * @param first Start of input range.
     * @param last End of input range
     * @param out Iterator to sampled curve points.
     */
    template <typename InputIt, typename OutputIt>
    void GetSampleByArcLength(InputIt first, InputIt last, OutputIt out) const
    {
        GetDerivativeByArcLength<0>(first, last, out);
    }

    /**
     * @brief Update curve internal state with given algorithm
     *
     * @param algorithm The algorithm object.
     */
    void Update()
    {
        if (!this->IsReady())
        {
            this->ready_ = algorithm_.Update(*this, state_);
        }
    }

private:
    StateType             state_{};
    mutable AlgorithmType algorithm_{};
};

/**
 * @brief Piecewise explicit form curve object
 *
 * @tparam Point Point type of this curve.
 * @tparam SIZE Maximum knot number of this curve
 * @tparam Algorithm Algorithm related to this curve.
 *
 * Algorithm type shall provide following members:
 * - Member type
 *   - ScalarType Scalar type
 *   - PointType Point type of the curve
 *   - StateType State data of the curve
 *   - TagType Tag of the algorithm. Must be CurveExplicitTag
 * - Member constant
 *   - DEGREE_VALUE degree of the curve
 * - Member functions
 *   - bool Update(CurveBaseT<PointType, SIZE_VALUE> const&, StateType&);
 *   - ScalarType GetLength(CurveBaseT<PointType, SIZE_VALUE> const&, StateType const&, size_t idx)
 *   - template <size_t D> PointType GetDerivativeByArcLength(CurveBaseT<PointType, SIZE_VALUE> const&, StateType
 * const&, ScalarType len)
 *   - template <size_t D, typename InputIt, typename OutputIt>
 *   void GetDerivativeByArcLength(CurveBaseT<PointType, SIZE_VALUE> const&, StateType const&, InputIt first, InputIt
 *   - template <size_t D> PointType GetDerivativeByCoordinate(CurveBaseT<PointType, SIZE_VALUE> const&, StateType
 * const&, ScalarType x)
 *   - template <size_t D, typename InputIt, typename OutputIt>
 *   void GetDerivativeByCoordinate(CurveBaseT<PointType, SIZE_VALUE> const&, StateType const&, InputIt first, InputIt
 * last, OutputIt out)
 *
 * @details Piecewise explicit form curve is represented by
 * @f{equation}{
 * C_i(x) = \left\{
 *   \begin{array}{rcl}
 *     y = f_y(x) & & x \in [K_i, K_{i+1}] \\
 *     z = f_z(x) & & x \in [K_i, K_{i+1}] \\
 *     \cdots
 *   \end{array} \right.
 * @f}
 * where C_i denotes i-th explicit form curve between i-th knot and (i+1)th knot.
 * K_i denotes x value of i-th knot of the curve.
 *
 */
template <typename Point, size_t SIZE, typename Algorithm,
          typename std::enable_if<std::is_same<typename Algorithm::TagType, CurveExplicitTag>::value>::type* = nullptr>
class CurveExplicit : public CurveExplicitBaseT<Point, SIZE>
{
public:
    using Base = CurveExplicitBaseT<Point, SIZE>;
    using Base::CurveExplicitBaseT;

    using ScalarType    = typename Point::ScalarType;
    using PointType     = Point;
    using AlgorithmType = Algorithm;
    using StateType     = typename AlgorithmType::StateType;
    using TagType       = typename AlgorithmType::TagType;

    /**
     * @brief Get length of this curve
     *
     * @return length of this curve
     */
    ScalarType GetLength() const
    {
        if (!this->IsReady())
        {
            throw holo::exception::BadCurveStateException();
        }
        return algorithm_.GetLength(*this, state_, (*this).size() - 1);
    }

    /**
     * @brief Get arc length to start of idx-th knot
     *
     * @return Arc length to start of idx-th knot
     */
    ScalarType GetLength(size_t idx) const
    {
        if (!this->IsReady())
        {
            throw holo::exception::BadCurveStateException();
        }
        return algorithm_.GetLength(*this, state_, idx);
    }

    /**
     * @brief Get x coordinate range of this curve
     *
     * @return x coordinate range
     */
    std::pair<ScalarType, ScalarType> GetCoordinateRange() const
    {
        if (!this->IsReady())
        {
            throw holo::exception::BadCurveStateException();
        }
        return std::pair<ScalarType, ScalarType>((*this)[0][0], (*this)[this->size() - 1][0]);
    }

    /**
     * @brief Get D-th derivative of curve at given arc length
     *
     * @tparam D Derivative order
     * @param len Length of arc.
     *
     * @return D-th derivative of the curve at arc length
     */
    template <size_t D>
    PointType GetDerivativeByArcLength(ScalarType len) const
    {
        if (!this->IsReady())
        {
            throw holo::exception::BadCurveStateException();
        }
        return algorithm_.template GetDerivativeByArcLength<D>(*this, state_, len);
    }

    /**
     * @brief Get D-th derivative of curve at sequence of arc lengths defined in range [first, last)
     *
     * @tparam InputIt iterator with value_type of ScalarType.
     * @tparam OutputIt iterator with value type of PointType.
     * @param first Start of input range.
     * @param last End of input range
     * @param out Iterator to sampled curve points.
     */
    template <size_t D, typename InputIt, typename OutputIt>
    void GetDerivativeByArcLength(InputIt first, InputIt last, OutputIt out) const
    {
        if (!this->IsReady())
        {
            throw holo::exception::BadCurveStateException();
        }
        algorithm_.template GetDerivativeByArcLength<D>(*this, state_, first, last, out);
    }

    /**
     * @brief Get point on curve at given arc length
     *
     * @param len Length of arc.
     *
     * @return Point on curve
     */
    PointType GetSampleByArcLength(ScalarType len) const
    {
        return GetDerivativeByArcLength<0>(len);
    }

    /**
     * @brief Get points on curve at sequence of arc lengths defined in range [first, last)
     *
     * @tparam InputIt iterator with value_type of ScalarType.
     * @tparam OutputIt iterator with value type of PointType.
     * @param first Start of input range.
     * @param last End of input range
     * @param out Iterator to sampled curve points.
     */
    template <typename InputIt, typename OutputIt>
    void GetSampleByArcLength(InputIt first, InputIt last, OutputIt out) const
    {
        return GetDerivativeByArcLength<0>(first, last, out);
    }

    /**
     * @brief Get D-th derivative of curve at given x coordinate
     *
     * @tparam D Derivative order
     * @param x X coordinate value.
     *
     * @return D-th derivative of the curve at given x coordinate
     */
    template <size_t D>
    PointType GetDerivativeByCoordinate(ScalarType x) const
    {
        if (!this->IsReady())
        {
            throw holo::exception::BadCurveStateException();
        }
        return algorithm_.template GetDerivativeByCoordinate<D>(*this, state_, x);
    }

    /**
     * @brief Get D-th derivative of curve at sequence of x coordinates defined in range [first, last)
     *
     * @tparam D Derivative order
     * @tparam InputIt iterator with value_type of ScalarType.
     * @tparam OutputIt iterator with value type of PointType.
     * @param first Start of input range.
     * @param last End of input range
     * @param out Iterator to sampled curve points.
     */
    template <size_t D, typename InputIt, typename OutputIt>
    void GetDerivativeByCoordinate(InputIt first, InputIt last, OutputIt out) const
    {
        if (!this->IsReady())
        {
            throw holo::exception::BadCurveStateException();
        }
        algorithm_.template GetDerivativeByCoordinate<D>(*this, state_, first, last, out);
    }

    /**
     * @brief Get point on curve at given x coordinate
     *
     * @param x x coordinate.
     *
     * @return Point on curve
     */
    PointType GetSampleByCoordinate(ScalarType len) const
    {
        return GetDerivativeByCoordinate<0>(len);
    }

    /**
     * @brief Get points on curve at sequence of x coordinates defined in range [first, last)
     *
     * @tparam InputIt iterator with value_type of ScalarType.
     * @tparam OutputIt iterator with value type of PointType.
     * @param first Start of input range.
     * @param last End of input range
     * @param out Iterator to sampled curve points.
     */
    template <typename InputIt, typename OutputIt>
    void GetSampleByCoordinate(InputIt first, InputIt last, OutputIt out) const
    {
        return GetDerivativeByCoordinate<0>(first, last, out);
    }

    /**
     * @brief Update curve internal state with given algorithm
     *
     * @param algorithm The algorithm object.
     */
    void Update()
    {
        if (!this->IsReady())
        {
            this->ready_ = algorithm_.Update(*this, state_);
        }
    }

private:
    StateType             state_{};
    mutable AlgorithmType algorithm_{};
};

/**
 * @}
 */
}  // namespace geometry
}  // namespace holo

#endif
