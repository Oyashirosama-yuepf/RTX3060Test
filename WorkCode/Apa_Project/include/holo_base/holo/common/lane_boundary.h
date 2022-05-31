/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_boundary.h
 * @brief This header file defines LaneBoundary.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-09-11
 */

#ifndef HOLO_COMMON_LANE_BOUNDARY_H_
#define HOLO_COMMON_LANE_BOUNDARY_H_

#include <array>
#include <memory>
#include <sstream>

#include <holo/geometry/curve_descriptor.h>
#include <holo/geometry/point3.h>
#include <holo/geometry/polynomial_curve2d.h>
#include <holo/serialization/serialization.h>

namespace holo
{
/**
 * @addtogroup common
 *
 * @{
 */

static const uint32_t LANE_BOUNDARY_MAX_POINT_NUM = 512U;  ///< point count for array in lane boundary

/**
 * @brief LaneBoundary type
 * @deprecated Use holo::common::LaneBoundary instead. Will be removed in v0.5.0
 *
 * @details LaneBoundary has two different implement way: curve formulation and points. LaneBonudary can be represented
 * only by curve or points, or by both. Points size must be less or equal LANE_BOUNDARY_MAX_POINT_NUM. Curve is
 * described by polynomial curve
 *
 */

class [[deprecated]] LaneBoundary
{
public:
    /**
     * @brief Enum class used to describe id of laneboundary
     */
    enum class LaneBoundaryId : int8_t
    {
        LEFT_3RD_LINE  = -5,
        LEFT_2ND_LINE  = -3,
        LEFT_1ST_LINE  = -1,
        RIGHT_1ST_LINE = 1,
        RIGHT_2ND_LINE = 3,
        RIGHT_3RD_LINE = 5,
        INVALID        = 15,
    };

    /**
     * @brief Enum class used to describe the line type of laneboundary
     */
    enum class LaneBoundaryType : uint8_t
    {
        UNDECIDED            = 0U,
        SOLID                = 1U,
        ROAD_EDGE            = 2U,
        DASHED               = 3U,
        DOUBLE_LANE          = 4U,
        BOTTS_DOT            = 5U,
        BARRIER              = 6U,
        LEFT_DOT_RIGHT_SOLID = 7U,
        LEFT_SOLID_RIGHT_DOT = 8U,
        CENTERLINE           = 14U,
        INVALID              = 15U
    };

    /**
     * @brief Enum class describes the color of lane markers
     */
    enum class LaneMarkColor : uint8_t
    {
        WHITE   = 0U,
        YELLOW  = 1U,
        BLUE    = 2U,
        INVALID = 15U
    };

public:
    template <typename T>
    using CurveDescriptorT = geometry::CurveDescriptorT<T>;
    using Point3f = holo::geometry::Point3f;
    /**
     * @brief Default constructor
     */
    LaneBoundary() noexcept;

    /**
     * @brief constructor with parameters
     *
     * @param lane_boundary_id lane boundary id
     * @param lane_boundary_type lane boundary type
     * @param lane_mark_color lane mark color
     * @param lane_boundary_params lane boundary params from CurveDescriptorT
     * @param lane_mark_width lane mark width
     * @param confidence lane boundary confidence
     * @param predicted true if lane boundary is predicted not detected by algorithm
     */
    LaneBoundary(const LaneBoundaryId lane_boundary_id, const LaneBoundaryType lane_boundary_type,
                 const LaneMarkColor                                     lane_mark_color,
                 const std::shared_ptr<CurveDescriptorT<float32_t>>&     lane_boundary_params,
                 const uint32_t                                          num_lane_boundary_points,
                 const std::array<Point3f, LANE_BOUNDARY_MAX_POINT_NUM>& lane_boundary_points,
                 const float32_t lane_mark_width, const float32_t confidence, const bool_t predicted) noexcept;

    /**
     * @brief Copy constructor
     *
     * @param other laneboundary
     */
    LaneBoundary(const LaneBoundary& other) noexcept;

    /**
     * @brief Move constructor
     *
     * @param other laneboundary
     */
    LaneBoundary(LaneBoundary&& other) noexcept;

    /**
     * @brief Copy assignment
     *
     * @param other other lane boundary
     * @return new lane boundary
     */
    LaneBoundary& operator=(const LaneBoundary& other) noexcept;

    /**
     * @brief Move assignment
     *
     * @param other other lane boundary
     * @return new lane boundary
     */
    LaneBoundary& operator=(LaneBoundary&& other) noexcept;

    /**
     * @brief Get lane boundary id
     *
     * @return lane boundary id
     */
    LaneBoundaryId GetLaneBoundaryId() const noexcept
    {
        return lane_boundary_id_;
    }

    /**
     * @brief Set lane boundary id
     *
     * @param lane_boundary_id lane boundary id
     */
    void SetLaneBoundaryId(const LaneBoundaryId lane_boundary_id) noexcept
    {
        this->lane_boundary_id_ = lane_boundary_id;
    }

    /**
     * @brief Get lane boundary type
     *
     * @return lane boundary type
     */
    LaneBoundaryType GetLaneBoundaryType() const noexcept
    {
        return lane_boundary_type_;
    }

    /**
     * @brief Set lane boundary type
     *
     * @param lane_boundary_type lane boundary type
     */
    void SetLaneBoundaryType(const LaneBoundaryType lane_boundary_type) noexcept
    {
        this->lane_boundary_type_ = lane_boundary_type;
    }

    /**
     * @brief Get lane mark color
     *
     * @return lane mark color
     */
    LaneMarkColor GetLaneMarkColor() const noexcept
    {
        return lane_mark_color_;
    }

    /**
     * @brief Set lane mark color
     *
     * @param lane_mark_color lane mark color
     */
    void SetLaneMarkColor(const LaneMarkColor lane_mark_color) noexcept
    {
        this->lane_mark_color_ = lane_mark_color;
    }

    /**
     * @brief Get lane boundary curve parameters with const
     *
     * @return pointer of lane curve params
     */
    const std::shared_ptr<const CurveDescriptorT<float32_t>> GetLaneBoundaryParams() const noexcept
    {
        std::shared_ptr<const CurveDescriptorT<float32_t>> ret =
            std::const_pointer_cast<const CurveDescriptorT<float32_t>>(lane_boundary_params_);
        return ret;
    }

    /**
     * @brief Get lane boundary curve parameters without cv-qualifier
     *
     * @return non const pointer of lane curve params
     */
    std::shared_ptr<CurveDescriptorT<float32_t>> GetLaneBoundaryParams() noexcept
    {
        return lane_boundary_params_;
    }

    /**
     * @brief Set lane boundary curve parameters
     *
     * @param lane_boundary_params pointer of lane curve polynomial object
     */
    void SetLaneBoundaryParams(const std::shared_ptr<CurveDescriptorT<float32_t>>& lane_boundary_params) noexcept
    {
        this->lane_boundary_params_ = lane_boundary_params;
    }

    /**
     * @brief Get size of lane boundary points
     *
     * @return size of lane boundary points
     */
    uint32_t GetNumLaneBoundaryPoints() const noexcept
    {
        return num_lane_boundary_points_;
    }

    /**
     * @brief Set size of lane boundary points
     *
     * @param num_lane_boundary_points size of lane boundary points
     */
    void SetNumLaneBoundaryPoints(const uint32_t num_lane_boundary_points) noexcept
    {
        this->num_lane_boundary_points_ = num_lane_boundary_points;
    }

    /**
     * @brief Get const reference points of lane boundary
     *
     * @return lane boundary points array
     */
    const std::array<Point3f, LANE_BOUNDARY_MAX_POINT_NUM>& GetLaneBoundaryPoints() const noexcept
    {
        return lane_boundary_points_;
    }

    /**
     * @brief Get non-const reference points of lane boundary
     *
     * @return lane boundary points array
     */
    std::array<Point3f, LANE_BOUNDARY_MAX_POINT_NUM>& GetLaneBoundaryPoints() noexcept
    {
        return lane_boundary_points_;
    }

    /**
     * @brief Set lane boundary points one by one
     *
     * @param lane_boundary_points lane boundary points
     */
    void SetLaneBoundaryPoints(const std::array<Point3f, LANE_BOUNDARY_MAX_POINT_NUM>& lane_boundary_points) noexcept
    {
        this->lane_boundary_points_ = lane_boundary_points;
    }

    /**
     * @brief Set lane boundary in efficient way
     *
     * @param lane_boundary_points lane boundary points
     */
    void SetLaneBoundaryPoints(std::array<Point3f, LANE_BOUNDARY_MAX_POINT_NUM>&& lane_boundary_points) noexcept
    {
        std::swap(this->lane_boundary_points_, lane_boundary_points);
    }

    /**
     * @brief Get start point of lane boundary
     *
     * @param[out] point output point
     * @return return true if num_lane_boundary_points_ > 0 which mean laneboundary has points
     */
    bool_t GetStartPoint(Point3f& point) const noexcept;

    /**
     * @brief Get end point of lane boundary
     *
     * @param[out] point output point
     * @return return true if num_lane_boundary_points_ > 0 which mean laneboundary has points
     */
    bool_t GetEndPoint(Point3f& point) const noexcept;

    /**
     * @brief Get lane mark width
     *
     * @return lane mark width
     */
    float32_t GetLaneMarkWidth() const noexcept
    {
        return lane_mark_width_;
    }

    /**
     * @brief Set lane mark width
     *
     * @param lane_mark_width lane mark width
     */
    void SetLaneMarkWidth(const float32_t lane_mark_width) noexcept
    {
        this->lane_mark_width_ = lane_mark_width;
    }

    /**
     * @brief Get confidence of lane boundary
     *
     * @return confidence of lane boundary
     */
    float32_t GetConfidence() const noexcept
    {
        return confidence_;
    }

    /**
     * @brief Set confidence of lane boundary
     *
     * @param confidence confidence of lane boundary
     */
    void SetConfidence(const float32_t confidence) noexcept
    {
        this->confidence_ = confidence;
    }

    /**
     * @brief Get lane boundary is predicted or not
     *
     * @return predicted lane boundary or not
     */
    bool_t IsPredicted() const noexcept
    {
        return predicted_;
    }

    /**
     * @brief Set lane boundary is predicted or not
     *
     * @param predicted lane boundary predicted property
     */
    void SetPredicted(const bool_t predicted) noexcept
    {
        this->predicted_ = predicted;
    }

    /**
     * @brief Get lane boundary is crossable
     *
     * @return whether lane boundary is crossable according to lane boundary type
     */
    bool_t IsCrossable() noexcept;

    /**
     * @brief Serialize content to string
     *
     * @return serialized string
     */
    std::string ToString() const noexcept;


private:
    LaneBoundaryId                                   lane_boundary_id_;
    LaneBoundaryType                                 lane_boundary_type_;
    LaneMarkColor                                    lane_mark_color_;
    std::shared_ptr<CurveDescriptorT<float32_t>>     lane_boundary_params_;
    uint32_t                                         num_lane_boundary_points_;
    std::array<Point3f, LANE_BOUNDARY_MAX_POINT_NUM> lane_boundary_points_;
    float32_t                                        lane_mark_width_;
    float32_t                                        confidence_;
    bool_t                                           predicted_;

};  // LaneBoundary

/**
 * @}
 */

}  // namespace holo

#endif  // !HOLO_COMMON_LANE_BOUNDARY_H_
