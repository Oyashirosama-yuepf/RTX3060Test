/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file road_frame2.h
 * @brief This header file defines RoadFrame object.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-05-07
 */

#ifndef HOLO_COMMON_ROAD_FRAME2_H_
#define HOLO_COMMON_ROAD_FRAME2_H_

#include <array>
#include <memory>

#include <holo/common/lane2.h>
#include <holo/common/lane_boundary2.h>
#include <holo/common/timestamp.h>
#include <holo/container/vector.h>
#include <holo/serialization/serialization.h>

namespace holo
{
namespace common
{
/**
 * @brief RoadFrame is used to represent road details in body coordinate
 *
 * @tparam Curve Curve type
 * @tparam SIZE number of curve store in RoadFrame
 */
template <typename Curve, size_t SIZE = 16U>
class RoadFrame
{
public:
    using CurveType    = Curve;
    using ScalarType   = typename CurveType::ScalarType;
    using PointType    = typename CurveType::PointType;
    using BoundaryType = holo::common::LaneBoundary<CurveType>;
    using LaneType     = holo::common::Lane<CurveType>;
#if __GNUC__ > 5
    template <typename T, size_t S = SIZE>
    using SequenceType = holo::container::Vector<T, S>;
#else
    //template <typename T, size_t S = SIZE>
    //using SequenceType = std::vector<T>;
    template <typename T, size_t S = SIZE>
    using SequenceType = holo::container::Vector<T, S>;
#endif

    template <bool CONST>
    class Iterator;
    using iterator       = Iterator<false>;
    using const_iterator = Iterator<true>;
    using GraphNode      = iterator;
    using ConstGraphNode = const_iterator;

    template <bool CONST>
    friend class Iterator;

    static size_t const   SIZE_VALUE = SIZE;
    static uint32_t const ID_INVALID = std::numeric_limits<uint32_t>::max();

    enum class Direction : uint8_t
    {
        NEXT      = 0U,  ///< Extended lane
        OUT_LEFT  = 1U,  ///< Split left lane
        OUT_RIGHT = 2U,  ///< Split right lane
        LEFT      = 3U,  ///< Left lane
        RIGHT     = 4U,  ///< Right lane
        PREV      = 5U,  ///< Previous lane
        IN_LEFT   = 6U,  ///< Merge in from left lane
        IN_RIGHT  = 7U,  ///< Merge in from right lane
    };

    struct ConflictPathType
    {
        using PathType = SequenceType<PointType, CurveType::SIZE_VALUE>;
        ConflictPathType(){};

        ConflictPathType(uint64_t path_id, PathType path)
        {
            this->path_id = path_id;
            this->path    = path;
        };

        template <size_t ALIGN = 4U>
        size_t GetSerializedSize() const noexcept
        {
            return holo::serialization::SerializedSize<ALIGN>(path_id) + path.template GetSerializedSize<ALIGN>();
        }

        template <typename S>
        void Serialize(S& serializer) const
        {
            serializer << holo::serialization::align << path_id << path;
        }

        template <typename D>
        void Deserialize(D& deserializer)
        {
            deserializer >> holo::serialization::align >> path_id >> path;
        }

        uint64_t path_id;
        PathType path;
    };

    class Adjacency
    {
    public:
        Adjacency()
          : adjacencies_{ID_INVALID, ID_INVALID, ID_INVALID, ID_INVALID, ID_INVALID, ID_INVALID, ID_INVALID, ID_INVALID}
        {
        }

        uint32_t& operator[](Direction dir) noexcept
        {
            return adjacencies_[static_cast<size_t>(dir)];
        }

        uint32_t const& operator[](Direction dir) const noexcept
        {
            return adjacencies_[static_cast<size_t>(dir)];
        }

        template <size_t ALIGN = 4U>
        size_t GetSerializedSize() const noexcept
        {
            return holo::serialization::AlignedSize<ALIGN>(8U * sizeof(uint32_t));
        }

        template <typename S>
        void Serialize(S& serializer) const
        {
            for (size_t i = 0; i < 8U; ++i)
            {
                serializer << adjacencies_[i];
            }
        }

        template <typename D>
        void Deserialize(D& deserializer)
        {
            for (size_t i = 0; i < 8U; ++i)
            {
                deserializer >> adjacencies_[i];
            }
        }

    private:
        std::array<uint32_t, 8U> adjacencies_;
    };

    /**
     * @brief Get timestamp
     *
     * @return timestamp
     */
    Timestamp const& GetTimestamp() const noexcept
    {
        return stamp_;
    }

    /**
     * @brief Get timestamp
     *
     * @return timestamp
     */
    Timestamp& GetTimestamp() noexcept
    {
        return stamp_;
    }

    /**
     * @brief Set timestamp
     *
     * @param stamp Timestamp
     */
    void SetTimestamp(Timestamp const& stamp) noexcept
    {
        stamp_ = stamp;
    }

    /**
     * @brief Default constructor
     */
    RoadFrame()
      : stamp_{}
      , default_index_{0U}
      , conflict_paths_{}
      , curves_{std::make_shared<CurveType>(), std::make_shared<CurveType>()}
      , boundaries_{}
      , lanes_{}
      , adjacencies_{}
    {
        boundaries_.emplace_back(std::make_shared<BoundaryType>(0U, 0U, curves_[0U]));
        boundaries_.emplace_back(std::make_shared<BoundaryType>(1U, 1U, curves_[1U]));
        lanes_.emplace_back(std::make_shared<LaneType>(0U, boundaries_[0U], boundaries_[1U]));
        adjacencies_.emplace_back();
    }

    RoadFrame(RoadFrame const& other)
    {
        stamp_          = other.stamp_;
        default_index_  = other.default_index_;
        conflict_paths_ = other.conflict_paths_;

        curves_.clear();
        for (size_t i = 0U; i < other.curves_.size(); ++i)
        {
            curves_.emplace_back(std::make_shared<CurveType>(*(other.curves_[i])));
        }
        boundaries_.clear();
        for (size_t i = 0U; i < other.boundaries_.size(); ++i)
        {
            boundaries_.emplace_back(std::make_shared<BoundaryType>(*(other.boundaries_[i])));
            boundaries_.back()->SetCurvePtr(curves_[boundaries_.back()->GetCurveIndex()]);
        }
        lanes_.clear();
        for (size_t i = 0U; i < other.lanes_.size(); ++i)
        {
            lanes_.emplace_back(std::make_shared<LaneType>(*(other.lanes_[i])));
            lanes_.back()->SetLeftBoundary(boundaries_[lanes_.back()->GetLeftBoundary().GetIndex()]);
            lanes_.back()->SetRightBoundary(boundaries_[lanes_.back()->GetRightBoundary().GetIndex()]);
        }
        adjacencies_ = other.adjacencies_;
    }

    RoadFrame& operator=(RoadFrame const& other)
    {
        stamp_          = other.stamp_;
        default_index_  = other.default_index_;
        conflict_paths_ = other.conflict_paths_;

        curves_.clear();
        for (size_t i = 0U; i < other.curves_.size(); ++i)
        {
            curves_.emplace_back(std::make_shared<CurveType>(*(other.curves_[i])));
        }
        boundaries_.clear();
        for (size_t i = 0U; i < other.boundaries_.size(); ++i)
        {
            boundaries_.emplace_back(std::make_shared<BoundaryType>(*(other.boundaries_[i])));
            boundaries_.back()->SetCurvePtr(curves_[boundaries_.back()->GetCurveIndex()]);
        }
        lanes_.clear();
        for (size_t i = 0U; i < other.lanes_.size(); ++i)
        {
            lanes_.emplace_back(std::make_shared<LaneType>(*(other.lanes_[i])));
            lanes_.back()->SetLeftBoundary(boundaries_[lanes_.back()->GetLeftBoundary().GetIndex()]);
            lanes_.back()->SetRightBoundary(boundaries_[lanes_.back()->GetRightBoundary().GetIndex()]);
        }
        adjacencies_ = other.adjacencies_;
        return *this;
    }

    RoadFrame(RoadFrame&& other) = default;

    RoadFrame& operator=(RoadFrame&& other) = default;

    ~RoadFrame() = default;

    /**
     * @brief Clear the Road Frame
     *
     * @details Erases all elements from the container and just create default lane.
     *          After this call, size() returns 1.
     */
    void clear()
    {
        default_index_ = 0U;
        this->conflict_paths_.clear();

        this->curves_.clear();
        this->boundaries_.clear();
        this->lanes_.clear();
        this->adjacencies_.clear();

        this->curves_ = {std::make_shared<CurveType>(), std::make_shared<CurveType>()};
        this->boundaries_.emplace_back(std::make_shared<BoundaryType>(0U, 0U, curves_[0U]));
        this->boundaries_.emplace_back(std::make_shared<BoundaryType>(1U, 1U, curves_[1U]));
        this->lanes_.emplace_back(std::make_shared<LaneType>(0U, boundaries_[0U], boundaries_[1U]));
        this->adjacencies_.emplace_back();
    }

    /**
     * @brief Get number of lanes
     *
     * @return lane number
     */
    size_t size() const noexcept
    {
        return lanes_.size();
    }

    /**
     * @brief Get default graph node
     *
     * @return Default graph node
     */
    iterator GetDefaultLane() noexcept
    {
        return iterator(this, default_index_);
    }

    /**
     * @brief Get default graph node
     *
     * @return Default graph node
     */
    const_iterator GetDefaultLane() const noexcept
    {
        return const_iterator(this, default_index_);
    }

    /**
     * @brief Set default lane
     *
     * @param node graph node
     */
    void SetDefaultLane(iterator node) noexcept
    {
        default_index_ = node.GetId();
    }

    /**
     * @brief Clear conflict paths
     */
    void ClearConflictPaths()
    {
        conflict_paths_.clear();
    }

    /**
     * @brief Push back conflict path
     *
     * @param path path
     */
    void PushBackConflictPath(ConflictPathType const& path)
    {
        conflict_paths_.push_back(path);
    }

    /**
     * @brief Emplace back conflict path
     *
     * @param path path
     */
    template <typename... Args>
    void EmplaceBackConflictPath(Args&&... args)
    {
        conflict_paths_.emplace_back(std::forward<Args>(args)...);
    }

    /**
     * @brief Get conflict path
     *
     * @param index path index
     *
     * @return const reference to path
     */
    ConflictPathType const& GetConflictPath(size_t index) const noexcept
    {
        return conflict_paths_.at(index);
    }

    /**
     * @brief Get conflict paths
     *
     * @return conflict paths
     */
    SequenceType<ConflictPathType> const& GetConflictPaths() const noexcept
    {
        return conflict_paths_;
    }

    /**
     * @brief Get lane node
     *
     * @param id node id
     *
     * @return Graph node
     */
    iterator GetLane(size_t id) noexcept
    {
        return iterator(this, id);
    }

    /**
     * @brief Get lane node
     *
     * @param id node id
     *
     * @return Graph node
     */
    const_iterator GetLane(size_t id) const noexcept
    {
        return const_iterator(this, id);
    }

    /**
     * @brief Add a lane node to left
     *
     * @param current_node Current lane node
     *
     * @return New lane node
     */
    iterator AddLaneToLeft(iterator current_node)
    {
        assert(!current_node.HasNeighbour(Direction::LEFT));

        // create new node
        lanes_.emplace_back(std::make_shared<LaneType>(lanes_.size()));
        adjacencies_.emplace_back();
        iterator new_node(this, lanes_.size() - 1U);
        new_node.Set(Direction::RIGHT, current_node);
        current_node.Set(Direction::LEFT, new_node);

        // new node's right bound is current node's left bound
        new_node->SetRightBoundary(current_node->GetLeftBoundaryPtr());

        iterator p_node = current_node.GetPrev().GetLeft();
        if (p_node)
        {
            p_node.Set(Direction::NEXT, new_node);
            new_node.Set(Direction::PREV, p_node);
            BoundaryType& boundary  = p_node->GetLeftBoundary();
            size_t        end_index = boundary.GetKnotRange().second;
            boundaries_.emplace_back(std::make_shared<BoundaryType>(
                boundaries_.size(), boundary, end_index > 0 ? end_index - 1 : end_index, end_index));
            new_node->SetLeftBoundary(boundaries_.back());
        }
        else
        {
            curves_.emplace_back(std::make_shared<CurveType>());
            boundaries_.emplace_back(
                std::make_shared<BoundaryType>(curves_.size() - 1U, boundaries_.size(), curves_.back()));
            new_node->SetLeftBoundary(boundaries_.back());
        }
        return new_node;
    }

    /**
     * @brief Add a lane node to right
     *
     * @param current_node Current lane node
     *
     * @return New lane node
     */
    iterator AddLaneToRight(iterator current_node)
    {
        assert(!current_node.HasNeighbour(Direction::RIGHT));

        // create new node
        lanes_.emplace_back(std::make_shared<LaneType>(lanes_.size()));
        adjacencies_.emplace_back();
        iterator new_node(this, lanes_.size() - 1U);
        new_node.Set(Direction::LEFT, current_node);
        current_node.Set(Direction::RIGHT, new_node);

        // new node's left bound is current node's right bound
        new_node->SetLeftBoundary(current_node->GetRightBoundaryPtr());

        iterator p_node = current_node.GetPrev().GetRight();
        if (p_node)
        {
            p_node.Set(Direction::NEXT, new_node);
            new_node.Set(Direction::PREV, p_node);
            BoundaryType& boundary  = p_node->GetRightBoundary();
            size_t        end_index = boundary.GetKnotRange().second;
            boundaries_.emplace_back(std::make_shared<BoundaryType>(
                boundaries_.size(), boundary, end_index > 0 ? end_index - 1 : end_index, end_index));
            new_node->SetRightBoundary(boundaries_.back());
        }
        else
        {
            curves_.emplace_back(std::make_shared<CurveType>());
            boundaries_.emplace_back(
                std::make_shared<BoundaryType>(curves_.size() - 1U, boundaries_.size(), curves_.back()));
            new_node->SetRightBoundary(boundaries_.back());
        }
        return new_node;
    }

    /**
     * @brief Add a lane node to next level
     *
     * @param current_node Current lane node
     * @param neighbour_left Whether set left lane as neighbour
     * @param neighbour_right Whether set right lane as neighbour
     *
     * @return New lane node
     */
    iterator AddLaneToNext(iterator current_node, bool_t neighbour_left = true, bool_t neighbour_right = true)
    {
        assert(!current_node.HasOut());

        // create new node
        lanes_.emplace_back(std::make_shared<LaneType>(lanes_.size()));
        adjacencies_.emplace_back();
        iterator new_node(this, lanes_.size() - 1U);
        current_node.Set(Direction::NEXT, new_node);
        new_node.Set(Direction::PREV, current_node);

        setLeftBoundary(new_node, current_node, neighbour_left);

        setRightBoundary(new_node, current_node, neighbour_right);

        return new_node;
    }

    /**
     * @brief Merge two lane node in current level to next level.
     *
     * @param left_node Left lane node
     * @param right_node Right lane node
     * @param neighbour_left Whether set left lane as neighbour
     * @param neighbour_right Whether set right lane as neighbour
     *
     * @return New lane node.
     */
    iterator AddLaneToNext(iterator left_node, iterator right_node, bool_t neighbour_left = true,
                           bool_t neighbour_right = true)
    {
        assert(!left_node.HasOut());
        assert(!right_node.HasOut());

        // create new node
        lanes_.emplace_back(std::make_shared<LaneType>(lanes_.size()));
        adjacencies_.emplace_back();
        iterator new_node(this, lanes_.size() - 1U);
        new_node.Set(Direction::IN_LEFT, left_node);
        new_node.Set(Direction::IN_RIGHT, right_node);
        left_node.Set(Direction::OUT_RIGHT, new_node);
        right_node.Set(Direction::OUT_LEFT, new_node);

        setLeftBoundary(new_node, left_node, neighbour_left);

        setRightBoundary(new_node, right_node, neighbour_right);

        return new_node;
    }

    /**
     * @brief Merge three lane node in current level to next level
     *
     * @param left_node Left lane node
     * @param middle_node Middle lane node
     * @param right_node Right lane node
     * @param neighbour_left Whether set left lane as neighbour
     * @param neighbour_right Whether set right lane as neighbour
     *
     * @return New lane node
     */
    iterator AddLaneToNext(iterator left_node, iterator middle_node, iterator right_node, bool_t neighbour_left = true,
                           bool_t neighbour_right = true)
    {
        assert(!left_node.HasOut());
        assert(!middle_node.HasOut());
        assert(!right_node.HasOut());

        // create new node
        lanes_.emplace_back(std::make_shared<LaneType>(lanes_.size()));
        adjacencies_.emplace_back();
        iterator new_node(this, lanes_.size() - 1U);
        new_node.Set(Direction::PREV, middle_node);
        new_node.Set(Direction::IN_LEFT, left_node);
        new_node.Set(Direction::IN_RIGHT, right_node);
        middle_node.Set(Direction::NEXT, new_node);
        left_node.Set(Direction::OUT_RIGHT, new_node);
        right_node.Set(Direction::OUT_LEFT, new_node);

        setLeftBoundary(new_node, left_node, neighbour_left);

        setRightBoundary(new_node, right_node, neighbour_right);

        return new_node;
    }

    /**
     * @brief Split one lane node in current level to two lane node in next level.
     *
     * @param current_node Current lane node
     * @param neighbour_left Whether set left lane as neighbour
     * @param neighbour_right Whether set right lane as neighbour
     * @param split_middle Whether new left lane and new right lane are splited.
     *
     * @return Left lane node of next level.
     */
    iterator AddLaneToNext2(iterator current_node, bool_t neighbour_left = true, bool_t neighbour_right = true,
                            bool_t split_middle = false)
    {
        assert(!current_node.HasOut());

        // create new node
        lanes_.emplace_back(std::make_shared<LaneType>(lanes_.size()));
        adjacencies_.emplace_back();
        iterator new_left(this, lanes_.size() - 1U);
        lanes_.emplace_back(std::make_shared<LaneType>(lanes_.size()));
        adjacencies_.emplace_back();
        iterator new_right(this, lanes_.size() - 1U);

        new_left.Set(Direction::IN_RIGHT, current_node);
        new_right.Set(Direction::IN_LEFT, current_node);
        current_node.Set(Direction::OUT_LEFT, new_left);
        current_node.Set(Direction::OUT_RIGHT, new_right);

        // new node's bound
        curves_.emplace_back(std::make_shared<CurveType>());
        boundaries_.emplace_back(
            std::make_shared<BoundaryType>(curves_.size() - 1U, boundaries_.size(), curves_.back()));
        new_left->SetRightBoundary(boundaries_.back());
        if (split_middle)
        {
            curves_.emplace_back(std::make_shared<CurveType>());
            boundaries_.emplace_back(
                std::make_shared<BoundaryType>(curves_.size() - 1U, boundaries_.size(), curves_.back()));
        }
        else
        {
            new_left.Set(Direction::RIGHT, new_right);
            new_right.Set(Direction::LEFT, new_left);
        }
        new_right->SetLeftBoundary(boundaries_.back());

        setLeftBoundary(new_left, current_node, neighbour_left);

        setRightBoundary(new_right, current_node, neighbour_right);

        return new_left;
    }

    /**
     * @brief Split three lane nodes in current level to two lane node in next level.
     *
     * @param left_node Left lane node
     * @param middle_node Middle lane node
     * @param right_node Right lane node
     * @param neighbour_left Whether set left lane as neighbour
     * @param neighbour_right Whether set right lane as neighbour
     * @param split_middle Whether new left lane and new right lane are splited.
     *
     * @return Left lane node of next level.
     */
    iterator AddLaneToNext2(iterator left_node, iterator middle_node, iterator right_node, bool_t neighbour_left = true,
                            bool_t neighbour_right = true, bool_t split_middle = false)
    {
        assert(!left_node.HasOut());
        assert(!middle_node.HasOut());
        assert(!right_node.HasOut());

        // create new node
        lanes_.emplace_back(std::make_shared<LaneType>(lanes_.size()));
        adjacencies_.emplace_back();
        iterator new_left(this, lanes_.size() - 1U);
        lanes_.emplace_back(std::make_shared<LaneType>(lanes_.size()));
        adjacencies_.emplace_back();
        iterator new_right(this, lanes_.size() - 1U);

        new_left.Set(Direction::IN_LEFT, left_node);
        new_left.Set(Direction::IN_RIGHT, middle_node);
        new_right.Set(Direction::IN_LEFT, middle_node);
        new_right.Set(Direction::IN_RIGHT, right_node);
        left_node.Set(Direction::OUT_RIGHT, new_left);
        middle_node.Set(Direction::OUT_LEFT, new_left);
        middle_node.Set(Direction::OUT_RIGHT, new_right);
        right_node.Set(Direction::OUT_LEFT, new_right);

        // new node's bound
        curves_.emplace_back(std::make_shared<CurveType>());
        boundaries_.emplace_back(
            std::make_shared<BoundaryType>(curves_.size() - 1U, boundaries_.size(), curves_.back()));
        new_left->SetRightBoundary(boundaries_.back());
        if (split_middle)
        {
            curves_.emplace_back(std::make_shared<CurveType>());
            boundaries_.emplace_back(
                std::make_shared<BoundaryType>(curves_.size() - 1U, boundaries_.size(), curves_.back()));
        }
        else
        {
            new_left.Set(Direction::RIGHT, new_right);
            new_right.Set(Direction::LEFT, new_left);
        }
        new_right->SetLeftBoundary(boundaries_.back());

        setLeftBoundary(new_left, left_node, neighbour_left);

        setRightBoundary(new_right, right_node, neighbour_right);

        return new_left;
    }

    /**
     * @brief Split one lane node in current level into three lane nodes in next level
     *
     * @param current_node Current lane node.
     * @param neighbour_left Whether set left lane as neighbour
     * @param neighbour_right Whether set right lane as neighbour
     * @param split_left Whether new left lane and new middle lane are splited.
     * @param split_right Whether new middle lane and new right lane are splited.
     *
     * @return Left lane node of next level.
     */
    iterator AddLaneToNext3(iterator current_node, bool_t neighbour_left = true, bool_t neighbour_right = true,
                            bool_t split_left = false, bool_t split_right = false)
    {
        assert(!current_node.HasOut());

        // create new node
        lanes_.emplace_back(std::make_shared<LaneType>(lanes_.size()));
        adjacencies_.emplace_back();
        iterator new_left(this, lanes_.size() - 1U);
        lanes_.emplace_back(std::make_shared<LaneType>(lanes_.size()));
        adjacencies_.emplace_back();
        iterator new_middle(this, lanes_.size() - 1U);
        lanes_.emplace_back(std::make_shared<LaneType>(lanes_.size()));
        adjacencies_.emplace_back();
        iterator new_right(this, lanes_.size() - 1U);

        new_left.Set(Direction::IN_RIGHT, current_node);
        new_middle.Set(Direction::PREV, current_node);
        new_right.Set(Direction::IN_LEFT, current_node);
        current_node.Set(Direction::OUT_LEFT, new_left);
        current_node.Set(Direction::NEXT, new_middle);
        current_node.Set(Direction::OUT_RIGHT, new_right);

        // new node's bound
        curves_.emplace_back(std::make_shared<CurveType>());
        boundaries_.emplace_back(
            std::make_shared<BoundaryType>(curves_.size() - 1U, boundaries_.size(), curves_.back()));
        new_left->SetRightBoundary(boundaries_.back());
        if (split_left)
        {
            curves_.emplace_back(std::make_shared<CurveType>());
            boundaries_.emplace_back(
                std::make_shared<BoundaryType>(curves_.size() - 1U, boundaries_.size(), curves_.back()));
        }
        else
        {
            new_left.Set(Direction::RIGHT, new_middle);
            new_middle.Set(Direction::LEFT, new_left);
        }
        new_middle->SetLeftBoundary(boundaries_.back());

        curves_.emplace_back(std::make_shared<CurveType>());
        boundaries_.emplace_back(std::make_shared<BoundaryType>(curves_.size() - 1U, boundaries_.size(), curves_.back()));
        new_middle->SetRightBoundary(boundaries_.back());
        if (split_right)
        {
            curves_.emplace_back(std::make_shared<CurveType>());
            boundaries_.emplace_back(
                std::make_shared<BoundaryType>(curves_.size() - 1U, boundaries_.size(), curves_.back()));
        }
        else
        {
            new_middle.Set(Direction::RIGHT, new_right);
            new_right.Set(Direction::LEFT, new_middle);
        }
        new_right->SetLeftBoundary(boundaries_.back());

        setLeftBoundary(new_left, current_node, neighbour_left);

        setRightBoundary(new_right, current_node, neighbour_right);

        return new_left;
    }

    /**
     * @brief Split two lane node in current level into three lane node in next level.
     *
     * @param left_node Left lane node.
     * @param right_node Right lane node.
     * @param neighbour_left Whether set left lane as neighbour
     * @param neighbour_right Whether set right lane as neighbour
     * @param split_left Whether new left lane and new middle lane are splited.
     * @param split_right Whether new middle lane and new right lane are splited.
     *
     * @return Left lane node of next level.
     */
    iterator AddLaneToNext3(iterator left_node, iterator right_node, bool_t neighbour_left = true,
                            bool_t neighbour_right = true, bool_t split_left = false, bool_t split_right = false)
    {
        assert(left_node.Get(Direction::RIGHT) == right_node);
        assert(right_node.Get(Direction::LEFT) == left_node);
        assert(!left_node.HasOut());
        assert(!right_node.HasOut());

        // create new node
        lanes_.emplace_back(std::make_shared<LaneType>(lanes_.size()));
        adjacencies_.emplace_back();
        iterator new_left(this, lanes_.size() - 1U);
        lanes_.emplace_back(std::make_shared<LaneType>(lanes_.size()));
        adjacencies_.emplace_back();
        iterator new_middle(this, lanes_.size() - 1U);
        lanes_.emplace_back(std::make_shared<LaneType>(lanes_.size()));
        adjacencies_.emplace_back();
        iterator new_right(this, lanes_.size() - 1U);

        new_left.Set(Direction::IN_RIGHT, left_node);
        new_middle.Set(Direction::IN_LEFT, left_node);
        new_middle.Set(Direction::IN_RIGHT, right_node);
        new_right.Set(Direction::IN_LEFT, right_node);
        left_node.Set(Direction::OUT_LEFT, new_left);
        left_node.Set(Direction::OUT_RIGHT, new_middle);
        right_node.Set(Direction::OUT_LEFT, new_middle);
        right_node.Set(Direction::OUT_RIGHT, new_right);

        // new node's bound
        curves_.emplace_back(std::make_shared<CurveType>());
        boundaries_.emplace_back(
            std::make_shared<BoundaryType>(curves_.size() - 1U, boundaries_.size(), curves_.back()));
        new_left->SetRightBoundary(boundaries_.back());
        if (split_left)
        {
            curves_.emplace_back(std::make_shared<CurveType>());
            boundaries_.emplace_back(
                std::make_shared<BoundaryType>(curves_.size() - 1U, boundaries_.size(), curves_.back()));
        }
        else
        {
            new_left.Set(Direction::RIGHT, new_middle);
            new_middle.Set(Direction::LEFT, new_left);
        }
        new_middle->SetLeftBoundary(boundaries_.back());

        curves_.emplace_back(std::make_shared<CurveType>());
        boundaries_.emplace_back(
            std::make_shared<BoundaryType>(curves_.size() - 1U, boundaries_.size(), curves_.back()));
        new_middle->SetRightBoundary(boundaries_.back());
        if (split_right)
        {
            curves_.emplace_back(std::make_shared<CurveType>());
            boundaries_.emplace_back(
                std::make_shared<BoundaryType>(curves_.size() - 1U, boundaries_.size(), curves_.back()));
        }
        else
        {
            new_middle.Set(Direction::RIGHT, new_right);
            new_right.Set(Direction::LEFT, new_middle);
        }
        new_right->SetLeftBoundary(boundaries_.back());

        setLeftBoundary(new_left, left_node, neighbour_left);

        setRightBoundary(new_right, right_node, neighbour_right);

        return new_left;
    }

    /**
     * @brief Update road frame internal states
     */
    void Update()
    {
        for (auto& curve : curves_)
        {
            if (curve->IsValid())
            {
                curve->Update();
            }
        }
    }

    SequenceType<std::shared_ptr<CurveType>> const& GetCurves() const noexcept
    {
        return curves_;
    }

    SequenceType<std::shared_ptr<BoundaryType>> const& GetBoundaries() const noexcept
    {
        return boundaries_;
    }

    SequenceType<std::shared_ptr<LaneType>> const& GetLanes() const noexcept
    {
        return lanes_;
    }

    SequenceType<Adjacency> const& GetAdjacencies() const noexcept
    {
        return adjacencies_;
    }

    /**
     * @brief Graph node object of lane graph
     */
    template <bool CONST>
    class Iterator
    {
    public:
        using value_type = LaneType;
        using reference  = typename std::conditional<CONST, value_type const&, value_type&>::type;
        using pointer =
            typename std::conditional<CONST, std::shared_ptr<value_type const>, std::shared_ptr<value_type>>::type;

        using RoadFramePtr = typename std::conditional<CONST, RoadFrame const*, RoadFrame*>::type;

        using Direction = RoadFrame::Direction;

        Iterator(RoadFramePtr rf, uint32_t index) : rf_{rf}, index_{index}
        {
        }

        template <bool CONST_ = CONST, typename = typename std::enable_if<CONST_>::type>
        Iterator(Iterator<false> const& other)
        {
        }

        /**
         * @brief Aceess neighbour of current graph node.
         *
         * @param dir Neighbour direction
         *
         * @return Reference to neighbour node.
         */
        Iterator operator[](Direction dir) const noexcept
        {
            if (this->index_ != ID_INVALID)
            {
                uint32_t id = (rf_->adjacencies_)[index_][dir];
                return (id == ID_INVALID) ? Iterator(rf_, ID_INVALID) : Iterator(rf_, id);
            }
            else
            {
                return Iterator(rf_, ID_INVALID);
            }
        }

        bool operator==(Iterator const& other) const noexcept
        {
            return (rf_ == other.rf_) && (index_ == other.index_);
        }

        bool operator==(Iterator<!CONST> const& other) const noexcept
        {
            return (rf_ == other.rf_) && (index_ == other.index_);
        }

        /**
         * @brief Aceess neighbour of current graph node with bound check
         *
         * @param dir Neighbour direction
         *
         * @return Reference to neighbour node.
         *
         * @throws holo::exception::OperationNotPermittedException if neighbour not exist.
         */
        Iterator Get(Direction dir) const noexcept
        {
            if (this->index_ != ID_INVALID)
            {
                uint32_t id = (rf_->adjacencies_)[index_][dir];
                return (id == ID_INVALID) ? Iterator(rf_, ID_INVALID) : Iterator(rf_, id);
            }
            else
            {
                return Iterator(rf_, ID_INVALID);
            }
        }

        Iterator& Move(Direction dir) noexcept
        {
            if (this->index_ != ID_INVALID)
            {
                uint32_t id = (rf_->adjacencies_)[index_][dir];
                index_      = id;
            }
            return *this;
        }

        /**
         * @brief Set neighbour of current lane
         *
         * @param dir neighbour direction
         * @param node neighbour node
         *
         * @throws holo::exception::OperationNotPermittedException if neighbour already exist.
         */
        void Set(Direction dir, Iterator const& node)
        {
            if ((rf_->adjacencies_)[index_][dir] != ID_INVALID)
            {
                throw holo::exception::OperationNotPermittedException();
            }
            (rf_->adjacencies_)[index_][dir] = node.GetId();
        }

        /**
         * @brief Reset neighbour node
         *
         * @param dir neighbour direction
         */
        void Reset(Direction dir)
        {
            (rf_->adjacencies_)[index_][dir] = ID_INVALID;
        }

        Iterator GetNext() const
        {
            return Get(Direction::NEXT);
        }

        Iterator ToNext()
        {
            return Move(Direction::NEXT);
        }

        Iterator GetOutLeft() const
        {
            return Get(Direction::OUT_LEFT);
        }

        Iterator ToOutLeft()
        {
            return Move(Direction::OUT_LEFT);
        }

        Iterator GetOutRight() const
        {
            return Get(Direction::OUT_RIGHT);
        }

        Iterator ToOutRight()
        {
            return Move(Direction::OUT_RIGHT);
        }

        Iterator GetLeft() const
        {
            return Get(Direction::LEFT);
        }

        Iterator ToLeft()
        {
            return Move(Direction::Left);
        }

        Iterator GetRight() const
        {
            return Get(Direction::RIGHT);
        }

        Iterator ToRight()
        {
            return Move(Direction::Right);
        }

        Iterator GetPrev() const
        {
            return Get(Direction::PREV);
        }

        Iterator ToPrev()
        {
            return Move(Direction::Prev);
        }

        Iterator GetInLeft() const
        {
            return Get(Direction::IN_LEFT);
        }

        Iterator ToInLeft()
        {
            return Move(Direction::IN_LEFT);
        }

        Iterator GetInRight() const
        {
            return Get(Direction::IN_RIGHT);
        }

        Iterator ToInRight()
        {
            return Move(Direction::IN_RIGHT);
        }

        /**
         * @brief Check if current node has neighbour in specified direction
         *
         * @param dir Neighbour direction
         *
         * @return true if neighbour exists otherwise false
         */
        bool_t HasNeighbour(Direction dir) const noexcept
        {
            return (rf_->adjacencies_)[index_][dir] != ID_INVALID;
        }

        /**
         * @brief Check if lane node has out nodes.
         *
         * @return true if lane has at least one out node.
         */
        bool_t HasOut() const noexcept
        {
            return (rf_->adjacencies_[index_][Direction::OUT_LEFT] != ID_INVALID) ||
                   (rf_->adjacencies_[index_][Direction::OUT_RIGHT] != ID_INVALID) ||
                   (rf_->adjacencies_[index_][Direction::NEXT] != ID_INVALID);
        }

        /**
         * @brief Get number of out nodes
         *
         * @return Out node number.
         */
        size_t GetOutCount() const noexcept
        {
            size_t count = 0;
            if (rf_->adjacencies_[index_][Direction::OUT_LEFT] != ID_INVALID)
            {
                ++count;
            }
            if (rf_->adjacencies_[index_][Direction::NEXT] != ID_INVALID)
            {
                ++count;
            }
            if (rf_->adjacencies_[index_][Direction::OUT_RIGHT] != ID_INVALID)
            {
                ++count;
            }
            return count;
        }

        /**
         * @brief Check if lane node has in nodes.
         *
         * @return true if lane has at least one in node.
         */
        bool_t HasIn() const noexcept
        {
            return (rf_->adjacencies_[index_][Direction::IN_LEFT] != ID_INVALID) ||
                   (rf_->adjacencies_[index_][Direction::IN_RIGHT] != ID_INVALID) ||
                   (rf_->adjacencies_[index_][Direction::PREV] != ID_INVALID);
        }

        /**
         * @brief Get number of in nodes
         *
         * @return In node number
         */
        size_t GetInCount() const noexcept
        {
            size_t count = 0;
            if (rf_->adjacencies_[index_][Direction::IN_LEFT] != ID_INVALID)
            {
                ++count;
            }
            if (rf_->adjacencies_[index_][Direction::PREV] != ID_INVALID)
            {
                ++count;
            }
            if (rf_->adjacencies_[index_][Direction::IN_RIGHT] != ID_INVALID)
            {
                ++count;
            }
            return count;
        }

        /**
         * @brief Check if another lane will merge current lane from left side.
         *
         * @return True if left lane will merge in current lane otherwise false.
         */
        bool_t HasMergeInFromLeft() const noexcept
        {
            bool res = false;
            if (this->GetLeft())
            {
                res = res || (this->GetLeft().GetOutCount() == 0U);  // if left node is dead end, left node may merge to
                                                                     // current lane.
            }
            if (this->GetNext())
            {
                res = res || this->GetNext().GetInLeft();
            }
            if (this->GetOutLeft())
            {
                res = res || this->GetOutLeft().GetInLeft();
            }
            return res;
        }

        /**
         * @brief Check if another lane will merge current lane from right side.
         *
         * @return True if right lane will merge in current lane otherwise false.
         */
        bool_t HasMergeInFromRight() const noexcept
        {
            bool res = false;
            if (this->GetRight())
            {
                res = res || (this->GetRight().GetOutCount() == 0U);  // if right node is dead end, right node may merge
                                                                      // to current lane.
            }
            if (this->GetNext())
            {
                res = res || this->GetNext().GetInRight();
            }
            if (this->GetOutRight())
            {
                res = res || this->GetOutRight().GetInRight();
            }
            return res;
        }

        /**
         * @brief Get graph node lane value.
         *
         * @return Lane object.
         */
        reference operator*() const noexcept
        {
            return *(rf_->lanes_[index_]);
        }

        /**
         * @brief Get the stored lane pointer.
         *
         * @return Pointer to lane object
         */
        pointer operator->() const noexcept
        {
            return rf_->lanes_[index_];
        }

        uint32_t GetId() const noexcept
        {
            return index_;
        }

        operator bool() const noexcept
        {
            return index_ != ID_INVALID;
        }

        bool IsValid() const noexcept
        {
            return index_ != ID_INVALID;
        }

        friend class Iterator<!CONST>;

    private:
        RoadFramePtr rf_;
        uint32_t     index_;
    };

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        std::size_t aligned_size = stamp_.GetSerializedSize<ALIGN>();
        aligned_size += holo::serialization::SerializedSize<ALIGN>(default_index_);
        aligned_size += conflict_paths_.template GetSerializedSize<ALIGN>();

        uint32_t count;

        count = this->curves_.size();
        aligned_size += holo::serialization::AlignedSize<ALIGN>(sizeof(count));
        for (size_t i = 0U; i < count; ++i)
        {
            aligned_size += this->curves_[i]->template GetSerializedSize<ALIGN>();
        }

        // For Boundaries
        count = boundaries_.size();
        aligned_size +=
            holo::serialization::AlignedSize<ALIGN>(sizeof(count)) +
            count * holo::serialization::AlignedSize<ALIGN>(
                        boundaries_[0]->template GetSerializedAttributesSize<ALIGN>() + 3U * sizeof(uint32_t));
        //                                                                              ^^^^^^^^^^^^^^^^^^^^^
        //                                                                        curve index + start/end knot index

        // For Lanes
        count = this->lanes_.size();
        aligned_size += holo::serialization::AlignedSize<ALIGN>(sizeof(count));
        for (std::size_t i = 0U; i < count; ++i)
        {
            aligned_size += holo::serialization::AlignedSize<ALIGN>(
                lanes_[i]->template GetSerializedAttributesSize<ALIGN>() + 2U * sizeof(uint32_t));
            //                                                             ^^^^^^^^^^^^^^^^^^^^^^
            //                                                             left/right bound index
        }

        // For Graph Nodes
        count = this->lanes_.size();
        aligned_size += holo::serialization::AlignedSize<ALIGN>(sizeof(count));
        aligned_size += holo::serialization::AlignedSize<ALIGN>((sizeof(uint32_t) * 8U)) * count;

        return aligned_size;
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        uint32_t count;

        serializer << stamp_ << default_index_ << conflict_paths_;

        count = curves_.size();
        serializer << count << holo::serialization::align;
        for (std::size_t i = 0U; i < count; ++i)
        {
            serializer << *(this->curves_[i]);
        }

        // For Boundaries
        count = this->boundaries_.size();
        serializer << count << holo::serialization::align;
        for (std::size_t i = 0U; i < count; ++i)
        {
            serializer << boundaries_[i]->GetCurveIndex() << static_cast<uint32_t>(boundaries_[i]->GetKnotRange().first)
                       << static_cast<uint32_t>(boundaries_[i]->GetKnotRange().second);

            boundaries_[i]->template SerializeAttributes(serializer);
        }

        // For Lanes
        count = this->lanes_.size();
        serializer << count << holo::serialization::align;
        for (std::size_t i = 0U; i < count; ++i)
        {
            serializer << lanes_[i]->GetLeftBoundary().GetIndex();
            serializer << lanes_[i]->GetRightBoundary().GetIndex();
            this->lanes_[i]->template SerializeAttributes(serializer);
            serializer << holo::serialization::align;
        }

        // For Adjacencies
        count = this->adjacencies_.size();
        serializer << count << holo::serialization::align;
        for (std::size_t i = 0U; i < count; ++i)
        {
            serializer << adjacencies_[i];
        }

        serializer << holo::serialization::align;
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        uint32_t count = 0U;

        deserializer >> stamp_ >> default_index_ >> conflict_paths_;

        // For Curves
        deserializer >> count >> holo::serialization::align;
        this->curves_.clear();
        this->curves_.reserve(count);
        for (std::size_t i = 0; i < count; ++i)
        {
            curves_.emplace_back(std::make_shared<CurveType>());
            deserializer >> (*(curves_.back()));
        }

        // For Boundaries
        deserializer >> count >> holo::serialization::align;
        this->boundaries_.clear();
        this->boundaries_.reserve(count);
        uint32_t curve_index = 0U;
        uint32_t curve_start = 0U;
        uint32_t curve_end   = 0U;

        for (std::size_t i = 0; i < count; ++i)
        {
            deserializer >> curve_index >> curve_start >> curve_end;
            this->boundaries_.emplace_back(std::make_shared<BoundaryType>(
                curve_index, boundaries_.size(), curves_[curve_index], curve_start, curve_end));
            this->boundaries_.back()->template DeserializeAttributes(deserializer);
        }

        // For Lanes
        deserializer >> count >> holo::serialization::align;
        this->lanes_.clear();
        this->lanes_.reserve(count);

        uint32_t left_idx  = 0U;
        uint32_t right_idx = 0U;
        for (std::size_t i = 0; i < count; ++i)
        {
            deserializer >> left_idx >> right_idx;
            this->lanes_.emplace_back(std::make_shared<LaneType>(this->lanes_.size(), this->boundaries_[left_idx],
                                                                 this->boundaries_[right_idx]));
            this->lanes_.back()->template DeserializeAttributes(deserializer);
        }

        // For Adjacencies
        deserializer >> count >> holo::serialization::align;
        this->adjacencies_.clear();
        this->adjacencies_.reserve(count);
        this->adjacencies_.resize(count);

        for (std::size_t i = 0; i < count; ++i)
        {
            deserializer >> this->adjacencies_[i];
        }

        deserializer >> holo::serialization::align;
        this->Update();
    }

protected:
    /**
     * @brief Set left boundary of lane node
     *
     * @details The function will set left boundary of a new node. prev should refer to left most lane of node's input
     * lanes. neighbour_left indicates whether use left lane of node as neighbour.
     * - If neighbour_left is true and node's left lane exists, use node's left lane's right boundary as node's left
     * boundary
     * - If neighbour_left is true but node's left lane doesn't exist, use prev's left boundary as node's left boundary.
     * - If neighbour_left is false, Create a new curve object and lane boundary object as left boundary.
     *
     * @param node The node to set
     * @param prev Node in previous level
     * @param neighbour_left Whether use left node as neighbour node.
     */
    void setLeftBoundary(iterator node, iterator prev, bool_t neighbour_left)
    {
        if (neighbour_left)
        {
            iterator p_node = prev.GetLeft().GetOutRight() ?
                                  prev.GetLeft().GetOutRight() :
                                  prev.GetLeft().GetNext() ? prev.GetLeft().GetNext() : prev.GetLeft().GetOutLeft();

            if (p_node)  // use left neighbour's boundary
            {
                p_node.Set(Direction::RIGHT, node);
                node.Set(Direction::LEFT, p_node);
                node->SetLeftBoundary(p_node->GetRightBoundaryPtr());
            }
            else  // use prev's boundary
            {
                size_t end_index = prev->GetLeftBoundary().GetKnotRange().second;
                boundaries_.emplace_back(std::make_shared<BoundaryType>(
                    boundaries_.size(), prev->GetLeftBoundary(), end_index > 0 ? end_index - 1 : end_index, end_index));
                node->SetLeftBoundary(boundaries_.back());
            }
        }
        else
        {
            // use new created curve and boundary
            curves_.emplace_back(std::make_shared<CurveType>());
            boundaries_.emplace_back(
                std::make_shared<BoundaryType>(curves_.size() - 1U, boundaries_.size(), curves_.back()));
            node->SetLeftBoundary(boundaries_.back());
            if (prev->GetLeftBoundary().size() > 0U)
            {
                boundaries_.back()->push_back(prev->GetLeftBoundary().back());
            }
        }
    }

    /**
     * @brief Set right boundary of lane node
     *
     * @details The function will set right boundary of a new node. prev should refer to right most lane of node's input
     * lanes. neighbour_right indicates whether use right lane of node as neighbour.
     * - If neighbour_right is true and node's right lane exists, use node's right lane's right boundary as node's right
     * boundary
     * - If neighbour_right is true but node's right lane doesn't exist, use prev's right boundary as node's right
     * boundary.
     * - If neighbour_right is false, Create a new curve object and lane boundary object as right boundary.
     *
     * @param node The node to set
     * @param prev Node in previous level
     * @param neighbour_right Whether use right node as neighbour node.
     */
    void setRightBoundary(iterator node, iterator prev, bool_t neighbour_right)
    {
        if (neighbour_right)
        {
            iterator p_node = prev.GetRight().GetOutLeft() ?
                                  prev.GetRight().GetOutLeft() :
                                  prev.GetRight().GetNext() ? prev.GetRight().GetNext() : prev.GetRight().GetOutRight();

            if (p_node)  // use right neighbour's boundary
            {
                p_node.Set(Direction::LEFT, node);
                node.Set(Direction::RIGHT, p_node);
                node->SetRightBoundary(p_node->GetLeftBoundaryPtr());
            }
            else  // use prev's boundary
            {
                size_t end_index = prev->GetRightBoundary().GetKnotRange().second;
                boundaries_.emplace_back(std::make_shared<BoundaryType>(boundaries_.size(), prev->GetRightBoundary(),
                                                                        end_index > 0 ? end_index - 1 : end_index,
                                                                        end_index));
                node->SetRightBoundary(boundaries_.back());
            }
        }
        else
        {
            // use new created curve and boundary
            curves_.emplace_back(std::make_shared<CurveType>());
            boundaries_.emplace_back(
                std::make_shared<BoundaryType>(curves_.size() - 1U, boundaries_.size(), curves_.back()));
            node->SetRightBoundary(boundaries_.back());
            if (prev->GetRightBoundary().size() > 0U)
            {
                boundaries_.back()->push_back(prev->GetRightBoundary().back());
            }
        }
    }

private:
    Timestamp                                             stamp_;
    uint32_t                                              default_index_;
    SequenceType<ConflictPathType, SIZE_VALUE> conflict_paths_;

    SequenceType<std::shared_ptr<CurveType>>    curves_;
    SequenceType<std::shared_ptr<BoundaryType>> boundaries_;
    SequenceType<std::shared_ptr<LaneType>>     lanes_;
    SequenceType<Adjacency>                     adjacencies_;
};

template <typename T, size_t Degree, size_t SIZE>
class RoadFrame<holo::numerics::Polynomial<T, Degree>, SIZE>
  : public holo::container::details::FixedSizeVectorBase<
        holo::common::LaneBoundary<holo::numerics::Polynomial<T, Degree>>, SIZE>
{
public:
    using ScalarType   = T;
    using PointType    = holo::geometry::Point2T<ScalarType>;
    using CurveType    = holo::numerics::Polynomial<ScalarType, Degree>;
    using BoundaryType = holo::common::LaneBoundary<CurveType>;
    using LaneType     = holo::common::Lane<CurveType>;
    using Base         = holo::container::details::FixedSizeVectorBase<BoundaryType, SIZE>;

    /**
     * @brief Default constructor
     */
    RoadFrame() : Base{}, stamp_{}
    {
    }

    /**
     * @brief Get timestamp
     *
     * @return timestamp
     */
    Timestamp const& GetTimestamp() const noexcept
    {
        return stamp_;
    }

    /**
     * @brief Get timestamp
     *
     * @return timestamp
     */
    Timestamp& GetTimestamp() noexcept
    {
        return stamp_;
    }

    /**
     * @brief Set timestamp
     *
     * @param stamp Timestamp
     */
    void SetTimestamp(Timestamp const& stamp) noexcept
    {
        stamp_ = stamp;
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return holo::serialization::AlignedSize<ALIGN>(stamp_.GetSerializedSize<ALIGN>() + sizeof(uint32_t)) +
               holo::serialization::AlignedSize<ALIGN>((*this)[0U].template GetSerializedSize<ALIGN>() * this->size());
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
        this->stamp_.Serialize(serializer);

        uint32_t count = this->size();
        serializer << count;
        for (size_t i = 0U; i < count; ++i)
        {
            (*this)[i].Serialize(serializer);
        }

        serializer << holo::serialization::align;
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
        deserializer >> stamp_;

        uint32_t count = 0U;
        deserializer >> count;

        this->resize(count, CurveType{});
        for (size_t i = 0; i < count; ++i)
        {
            deserializer >> (*this)[i];
        }
    }

private:
    Timestamp stamp_;
};

}  // namespace common
}  // namespace holo

#endif
