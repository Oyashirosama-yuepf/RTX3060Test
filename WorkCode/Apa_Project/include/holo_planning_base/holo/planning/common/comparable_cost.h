/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file comparable_cost.h
 * @brief the header of the comparable_cost
 * @author lijiawen(lijiawen@holomatic.com)
 * @date 2020-05-13
 */

#ifndef _HOLO_PLANNING_COMMON_COMPARABLE_COST_H_
#define _HOLO_PLANNING_COMMON_COMPARABLE_COST_H_

#include <cmath>
#include <cstdlib>

#include <array>
#include <vector>

#include <holo/core/types.h>

namespace holo
{
namespace planning
{
class ComparableCost
{
public:
    ComparableCost() = default;

    ComparableCost(bool_t    has_collision,
                   bool_t    is_out_of_boundary,
                   bool_t    is_out_of_lane,
                   float64_t safety_cost,
                   float64_t smoothness_cost)
      : safety_cost_(safety_cost), smoothness_cost_(smoothness_cost)
    {
        cost_items_[HAS_COLLISION_]   = has_collision;
        cost_items_[OUT_OF_BOUNDARY_] = is_out_of_boundary;
        cost_items_[OUT_OF_LANE_]     = is_out_of_lane;
    }

    ComparableCost(ComparableCost const&) = default;

public:
    ComparableCost operator+(ComparableCost const& other) const
    {
        ComparableCost lhs = *this;
        return lhs += other;
    }

    ComparableCost& operator+=(ComparableCost const& other)
    {
        for (size_t i = 0; i < cost_items_.size(); ++i)
        {
            cost_items_[i] = (cost_items_[i] || other.cost_items_[i]);
        }
        safety_cost_ += other.safety_cost_;
        smoothness_cost_ += other.smoothness_cost_;
        return *this;
    }

    bool_t operator>(ComparableCost const& other) const
    {
        return this->CompareTo(other) > 0;
    }

    bool_t operator>=(ComparableCost const& other) const
    {
        return this->CompareTo(other) >= 0;
    }

    bool_t operator<(ComparableCost const& other) const
    {
        return this->CompareTo(other) < 0;
    }

    bool_t operator<=(ComparableCost const& other) const
    {
        return this->CompareTo(other) <= 0;
    }

public:
    void SetSmoothnessCost(float64_t input_smoothness_cost) noexcept
    {
        smoothness_cost_ = input_smoothness_cost;
    }

    float64_t GetSmoothnessCost() const noexcept
    {
        return smoothness_cost_;
    }

    void SetSafetyCost(float64_t input_safety_cost) noexcept
    {
        safety_cost_ = input_safety_cost;
    }

    float64_t GetSafetyCost() const noexcept
    {
        return safety_cost_;
    }

    void SetCollisionFlag(bool_t is_collision) noexcept
    {
        cost_items_[HAS_COLLISION_] = is_collision;
    }

    bool_t GetCollisionFlag() const noexcept
    {
        return cost_items_[HAS_COLLISION_];
    }

    void SetOutOfBoundaryFlag(bool_t is_out_of_boundary) noexcept
    {
        cost_items_[OUT_OF_BOUNDARY_] = is_out_of_boundary;
    }

    bool_t GetOutOfBoundaryFlag() const noexcept
    {
        return cost_items_[OUT_OF_BOUNDARY_];
    }

    void SetOutOfLaneFlag(bool_t is_out_of_lane) noexcept
    {
        cost_items_[OUT_OF_LANE_] = is_out_of_lane;
    }

    bool_t GetOutOfLaneFlag() const noexcept
    {
        return cost_items_[OUT_OF_LANE_];
    }

private:
    int8_t CompareTo(ComparableCost const& other) const
    {
        for (size_t i = 0; i < cost_items_.size(); ++i)
        {
            if (cost_items_[i])
            {
                if (other.cost_items_[i])
                {
                    continue;
                }
                else
                {
                    return 1;
                }
            }
            else
            {
                if (other.cost_items_[i])
                {
                    return -1;
                }
                else
                {
                    continue;
                }
            }
        }

        float64_t const kEpsilon = 1e-12;
        float64_t const diff     = safety_cost_ + smoothness_cost_ - other.safety_cost_ - other.smoothness_cost_;
        if (std::fabs(diff) < kEpsilon)
        {
            return 0;
        }
        else if (diff > 0)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }

private:
    /*
     * cost_items_ represents an array of factors that affect the cost,
     * The level is from most critical to less critical.
     * It includes:
     * (0) has_collision or out_of_boundary
     * (1) out_of_lane
     *
     * NOTICE: Items could have same critical levels
     */
    static size_t const   HAS_COLLISION_   = 0;
    static size_t const   OUT_OF_BOUNDARY_ = 1;
    static size_t const   OUT_OF_LANE_     = 2;
    std::array<bool_t, 3> cost_items_      = {{false, false, false}};

    float64_t safety_cost_     = 0.0;  ///< cost from distance to obstacles or boundaries
    float64_t smoothness_cost_ = 0.0;  ///< cost from deviation from lane center, path curvature etc
};

}  // namespace planning
}  // namespace holo

#endif  // _HOLO_PLANNING_COMMON_COMPARABLE_COST_H_
