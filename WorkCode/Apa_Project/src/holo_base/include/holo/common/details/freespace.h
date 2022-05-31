/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file freespace.h
 * @brief This header file defines freespace object
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @author Li Zhijian(lizhijian@holomatic.com)
 * @date 2020-12-21
 */

#ifndef HOLO_COMMON_DETAILS_FREESPACE_H_
#define HOLO_COMMON_DETAILS_FREESPACE_H_

#include <holo/common/coordinate.h>
#include <holo/common/timestamp.h>
#include <holo/container/vector.h>
#include <holo/serialization/serialization.h>
#include <assert.h>

namespace holo
{
namespace common
{
namespace details
{
template <typename Point, size_t POINT_SIZE>
class FreespacePolygonBaseT : public holo::container::details::VectorBase<Point, POINT_SIZE>
{
public:
    using BoundaryType = uint32_t;
    using PointType    = Point;
    using ScalarType   = typename PointType::ScalarType;
    using Base         = holo::container::details::VectorBase<Point, POINT_SIZE>;

    static size_t const POINT_SIZE_VALUE = POINT_SIZE;

    using Base::Base;

    /**
     * @brief Set boundary type for idx-th edge
     *
     * @param eidx edge index
     * @param type boundary type
     */
    void SetBoundaryType(size_t eidx, BoundaryType type)
    {
        insertSegment(eidx, eidx + 1U, type);
    }

    /**
     * @brief Set boundary type in edge index range [start, end), start == end means set all boundaries' type.
     *
     * @param start start edge index
     * @param end end edge index
     * @param type boundary type
     */
    void SetBoundaryType(size_t start, size_t end, BoundaryType type)
    {
        insertSegment(start, end, type);
    }

    /**
     * @brief Get number of boundaries.
     *
     * @return Number of boundary type segments.
     */
    size_t GetBoundarySize() const noexcept
    {
        return boundaries_.size();
    }

    /**
     * @brief Clear all boundaries
     */
    void ClearBoundaries() noexcept
    {
        boundaries_.clear();
    }

    /**
     * @brief Get boundary type by boundary index
     *
     * @param bidx boundary index
     *
     * @return boundary type
     */
    BoundaryType GetBoundaryTypeByIndex(size_t bidx) const noexcept
    {
        return boundaries_[bidx].type;
    }

    /**
     * @brief Get edge index range of a boundary
     *
     * @param bidx boundary index
     *
     * @return [start, end) edge index pair.
     */
    std::pair<size_t, size_t> GetBoundaryRangeByIndex(size_t bidx) const noexcept
    {
        return std::pair<size_t, size_t>(boundaries_[bidx].start, boundaries_[bidx].end);
    }

    /**
     * @brief Get type of boundary that a specific edge belongs to
     *
     * @param eidx edge index
     *
     * @return Boundary type
     */
    BoundaryType GetBoundaryType(size_t eidx) const
    {
        BoundaryType res = 0U;
        for (size_t i = 0; i < boundaries_.size(); ++i)
        {
            if ((eidx >= boundaries_[i].start && eidx < boundaries_[i].end) || (i == boundaries_.size() - 1))
            {
                res = boundaries_[i].type;
                break;
            }
        }
        return res;
    }

    /**
     * @brief Get edge index range of boundary that a specific edge belongs to
     *
     * @param eidx edge index
     *
     * @return [start, end) edge index pair.
     */
    std::pair<size_t, size_t> GetBoundaryRange(size_t eidx) const
    {
        std::pair<size_t, size_t> res{0, 0};
        for (size_t i = 0; i < boundaries_.size(); ++i)
        {
            if ((eidx >= boundaries_[i].start && eidx < boundaries_[i].end) || (i == boundaries_.size() - 1))
            {
                res = {boundaries_[i].start, boundaries_[i].end};
                break;
            }
        }
        return res;
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return Base::template GetSerializedSize<ALIGN>() + boundaries_.template GetSerializedSize<ALIGN>();
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        Base::Serialize(serializer);
        serializer << boundaries_;
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        Base::Deserialize(deserializer);
        deserializer >> boundaries_;
    }

private:
    struct SegmentInfo
    {
        size_t       start;
        size_t       end;
        BoundaryType type;

        SegmentInfo() : start{0U}, end{0U}, type{0u}
        {
        }

        SegmentInfo(size_t s, size_t e, BoundaryType t) : start{s}, end{e}, type{t}
        {
        }

        template <size_t ALIGN = 4U>
        size_t GetSerializedSize() const noexcept
        {
            return holo::serialization::SerializedSize<ALIGN>(start, end, type);
        }

        template <typename S>
        void Serialize(S& serializer) const
        {
            serializer << holo::serialization::align << start << end << type << holo::serialization::align;
        }

        template <typename D>
        void Deserialize(D& deserializer)
        {
            deserializer >> holo::serialization::align >> start >> end >> type >> holo::serialization::align;
        }
    };

    using BoundaryContainer = holo::container::Vector<SegmentInfo, POINT_SIZE>;

    void insertSegment(size_t start, size_t end, BoundaryType type)
    {
        if (boundaries_.empty())
        {
            if (start < end)
            {
                boundaries_.emplace_back(start, end, type);
                boundaries_.emplace_back(end, start, 0U);
            }
            else if (start > end)
            {
                boundaries_.emplace_back(end, start, 0U);
                boundaries_.emplace_back(start, end, type);
            }
            else
            {
                boundaries_.emplace_back(0U, 0U, type);
            }
        }
        else
        {
            if (start < end)
            {
                insertPositiveOrder(start, end, type);
            }
            else if (start > end)
            {
                insertNegativeOrder(start, end, type);
            }
            else
            {
                boundaries_.clear();
                boundaries_.emplace_back(0U, 0U, type);
            }
        }
    }

    void insertPositiveOrder(size_t start, size_t end, BoundaryType type)
    {
        auto first = boundaries_.begin();
        auto last  = boundaries_.begin();
        // Search first and last segment that start/end lays in.
        for (; first != boundaries_.end() - 1U; ++first)
        {
            if (start >= first->start && start < first->end)
            {
                break;
            }
        }
        for (last = first; last != boundaries_.end() - 1U; ++last)
        {
            if (end > last->start && end <= last->end)
            {
                break;
            }
        }
        insertPositiveOrderWithIterators(first, last, start, end, type);
    }

    void insertPositiveOrderWithIterators(typename BoundaryContainer::iterator first,
                                          typename BoundaryContainer::iterator last, size_t start, size_t end,
                                          BoundaryType type)
    {
        if (first == last)
        {
            if (first->type == type)
            {
                return;
            }
            insertPositiveOrderSegment(first, start, end, type);
        }
        else
        {
            if (first->type == type)
            {
                start = first->start;
            }
            if (last->type == type)
            {
                end = last->end;
            }
            insertPositiveOrderSegment(first, last, start, end, type);
        }
    }

    void insertNegativeOrder(size_t start, size_t end, BoundaryType type)
    {
        auto first = boundaries_.end() - 1;
        auto last  = boundaries_.end() - 1;
        // Search first and last segment that start/end lays in.
        if (start < boundaries_.back().start)
        {
            for (; first > boundaries_.begin(); --first)
            {
                if (start > first->start && end < first->end)
                {
                    break;
                }
            }
        }
        if (end > boundaries_.front().start)
        {
            for (last = first; last > boundaries_.begin(); --last)
            {
                if (end > last->start && end < last->end)
                {
                    break;
                }
            }
        }

        insertNegativeOrderWithIterators(first, last, start, end, type);
    }

    void insertNegativeOrderWithIterators(typename BoundaryContainer::iterator first,
                                          typename BoundaryContainer::iterator last, size_t start, size_t end,
                                          BoundaryType type)
    {
        if (first == last)
        {
            if (first->type == type)
            {
                return;
            }
            insertNegativeOrderSegment(first, start, end, type);
        }
        else
        {
            if (first->type == type)
            {
                start = first->start;
            }
            if (last->type == type)
            {
                end = last->end;
            }
            insertNegativeOrderSegment(first, last, start, end, type);
        }
    }

    void insertPositiveOrderSegment(typename BoundaryContainer::iterator pos, size_t start, size_t end,
                                    BoundaryType type)
    {
        if (start > pos->start && end != pos->end)
        {
            // {pos->start, pos->end} --> {pos->start, start} {start, end} {end, pos->end}
            pos           = boundaries_.insert(pos, {{pos->start, start, pos->type}, {start, end, type}});
            pos[2U].start = end;
        }
        else if (start > pos->start && end == pos->end)
        {
            // {pos->start, pos->end} --> {pos->start, start} {start, end}
            pos           = boundaries_.insert(pos, {pos->start, start, pos->type});
            pos[1U].start = start;
            pos[1U].type  = type;
        }
        else if (start == pos->start && end != pos->end)
        {
            // {pos->start, pos->end} --> {start, end} {end, pos->end}
            pos           = boundaries_.insert(pos, {pos->start, end, type});
            pos[1U].start = end;
        }
        else if (start == pos->start && end == pos->end)
        {
            // only update type
            pos->type = type;
        }
        else if (start < pos->start && end > pos->end)
        {
            // boundaries --> {start, end} {end, start}
            boundaries_.assign({{start, end, type}, {end, start, pos->type}});
        }
        else if (start < pos->start && end < pos->end)
        {
            // {S ... E} {pos->start, pos->end} --> {start, end} {end, S} ... {pos->start, start}
            pos->end = start;
            boundaries_.insert(boundaries_.begin(), {{start, end, type}, {end, boundaries_.front().start, pos->type}});
        }
        else  // start < pos->start && end == pos->end
        {
            // {S ... E} {pos->start, pos->end} --> {start, end} ... {pos->start, start}
            pos->end = start;
            boundaries_.insert(boundaries_.begin(), {start, end, type});
        }
    }

    void insertPositiveOrderSegment(typename BoundaryContainer::iterator first,
                                    typename BoundaryContainer::iterator last, size_t start, size_t end,
                                    BoundaryType type)
    {
        assert(first != last);

        // After this if statement, First will point to first element that may be deleted.
        if (first > last)
        {
            first->end = start;
            first      = boundaries_.begin();
        }
        else
        {
            if (start > first->start)
            {
                first->end = start;
            }
            else
            {
                first->start = start;
                first->end   = end;
                first->type  = type;
            }
            ++first;
        }

        // After this if statement, Last will point to next of last element that may be deleted.
        if (end < last->end)
        {
            last->start = end;
            if ((first - 1)->start != start)
            {
                if (first == last)
                {
                    last = boundaries_.insert(last, {start, end, type});
                }
                else
                {
                    --last;
                    last->start = start;
                    last->end   = end;
                    last->type  = type;
                }
            }
        }
        else
        {
            if ((first - 1)->start == start)
            {
                ++last;
            }
            else
            {
                last->start = start;
                last->end   = end;
                last->type  = type;
            }
        }
        boundaries_.erase(first, last);
    }

    void insertNegativeOrderSegment(typename BoundaryContainer::iterator pos, size_t start, size_t end,
                                    BoundaryType type)
    {
        if (pos->start <= pos->end)
        {
            boundaries_.assign({{end, start, pos->type}, {start, end, type}});
        }
        else
        {
            if (start > pos->start && end != pos->end)
            {
                boundaries_.back().end = start;
                boundaries_.insert(boundaries_.begin(), {end, boundaries_.front().start, pos->type});
                boundaries_.emplace_back(start, end, type);
            }
            else if (start > pos->start && end == pos->end)
            {
                boundaries_.back().end = start;
                boundaries_.emplace_back(start, end, type);
            }
            else if (start == pos->start && end != pos->end)
            {
                boundaries_.insert(boundaries_.begin(), {end, boundaries_.front().start, pos->type});
                boundaries_.back().end  = end;
                boundaries_.back().type = type;
            }
            else  // start == pos->start && end == pos->end
            {
                pos->type = type;
            }
        }
    }

    void insertNegativeOrderSegment(typename BoundaryContainer::iterator first,
                                    typename BoundaryContainer::iterator last, size_t start, size_t end,
                                    BoundaryType type)
    {
        assert(first != last);

        if (first < last)
        {
            typename BoundaryContainer::value_type item;
            if (end == boundaries_.front().start)
            {
                last->start = start;
                last->type  = type;
            }
            else
            {
                item        = {end, last->end, last->type};
                last->end   = end;
                last->start = start;
                last->type  = type;
            }

            if (start == first->start)
            {
                boundaries_.erase(first, last);
            }
            else
            {
                first->end = start;
                boundaries_.erase(first + 1U, last);
            }

            if (boundaries_.front().start != boundaries_.back().end)
            {
                boundaries_.insert(boundaries_.begin(), item);
            }
        }
        else
        {
            if (end < last->end)
            {
                last->start = end;
            }
            else
            {
                ++last;
            }

            if (start > first->start)
            {
                first->end = start;
            }
            else
            {
                --first;
            }
            boundaries_.erase(first + 1U, boundaries_.end());
            boundaries_.erase(boundaries_.begin(), last);
            boundaries_.emplace_back(start, end, type);
        }
    }

    BoundaryContainer boundaries_{};
};  // namespace details

template <typename Point, size_t POINT_SIZE>
class FreespaceInteriorPolygon : public FreespacePolygonBaseT<Point, POINT_SIZE>
{
public:
    using Base       = FreespacePolygonBaseT<Point, POINT_SIZE>;
    using PointType  = typename Base::PointType;
    using ScalarType = typename Base::ScalarType;

    static size_t const POINT_SIZE_VALUE = Base::POINT_SIZE_VALUE;

    using Base::Base;
};

template <typename Point, size_t POINT_SIZE, size_t INTERIOR_SIZE>
class FreespaceExteriorPolygon : public FreespacePolygonBaseT<Point, POINT_SIZE>
{
public:
    using Base         = FreespacePolygonBaseT<Point, POINT_SIZE>;
    using PointType    = typename Base::PointType;
    using ScalarType   = typename Base::ScalarType;
    using InteriorType = FreespaceInteriorPolygon<PointType, POINT_SIZE>;

    static size_t const POINT_SIZE_VALUE    = Base::POINT_SIZE_VALUE;
    static size_t const INTERIOR_SIZE_VALUE = INTERIOR_SIZE;

    using Base::Base;

    void AddInterior(InteriorType const& value)
    {
        interiors_.push_back(value);
    }

    void AddInterior(InteriorType&& value)
    {
        interiors_.push_back(std::move(value));
    }

    template <typename... Args>
    void AddInterior(Args&&... args)
    {
        interiors_.emplace_back(std::forward<Args>(args)...);
    }

    size_t GetInteriorSize() const noexcept
    {
        return interiors_.size();
    }

    void ClearInterior() noexcept
    {
        interiors_.clear();
    }

    InteriorType const& GetInterior(size_t idx) const noexcept
    {
        return interiors_[idx];
    }

    InteriorType& GetInterior(size_t idx) noexcept
    {
        return interiors_[idx];
    }

    void EraseInterior(size_t idx) noexcept
    {
        if (idx < interiors_.size())
        {
            interiors_.erase(interiors_.begin() + idx);
        }
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return Base::template GetSerializedSize<ALIGN>() + interiors_.template GetSerializedSize<ALIGN>();
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        Base::Serialize(serializer);
        serializer << interiors_;
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        Base::Deserialize(deserializer);
        deserializer >> interiors_;
    }

private:
    holo::container::Vector<InteriorType, INTERIOR_SIZE_VALUE> interiors_{};
};

template <typename Exterior, size_t POLYGON_SIZE>
class Freespace : public holo::container::details::VectorBase<Exterior, POLYGON_SIZE>
{
public:
    using Base         = holo::container::details::VectorBase<Exterior, POLYGON_SIZE>;
    using ExteriorType = Exterior;
    using PointType    = typename ExteriorType::PointType;
    using ScalarType   = typename ExteriorType::ScalarType;

    static size_t const POLYGON_SIZE_VALUE = POLYGON_SIZE;

    using Base::Base;

    void SetTimestamp(holo::common::Timestamp value) noexcept
    {
        stamp_ = value;
    }

    void SetCoordinate(holo::common::Coordinate value) noexcept
    {
        coordinate_ = value;
    }

    holo::common::Timestamp GetTimestamp() const noexcept
    {
        return stamp_;
    }

    holo::common::Coordinate GetCoordinate() const noexcept
    {
        return coordinate_;
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return stamp_.GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(static_cast<uint32_t>(coordinate_)) +
               Base::template GetSerializedSize<ALIGN>();
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << stamp_ << coordinate_;
        Base::Serialize(serializer);
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        deserializer >> stamp_ >> coordinate_;
        Base::Deserialize(deserializer);
    }

private:
    holo::common::Timestamp  stamp_{};
    holo::common::Coordinate coordinate_{};
};

}  // namespace details
}  // namespace common
}  // namespace holo

#endif

