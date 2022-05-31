/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file bosch_mpc_laneboundary.h
 * @brief A class to describe bosch mpc laneboundary
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2019/12/10
 */

#ifndef HOLO_SENSORS_COMMON_BOSCH_MPC_LANEBOUNDARY_H_
#define HOLO_SENSORS_COMMON_BOSCH_MPC_LANEBOUNDARY_H_

#include <holo/common/coordinate.h>
#include <holo/common/extrinsic.h>
#include <holo/common/lane_boundary2.h>
#include <holo/common/timestamp.h>
#include <holo/core/common.h>
#include <holo/core/types.h>
#include <holo/geometry/polyfit2.h>

namespace holo
{
namespace sensors
{
namespace bosch_mpc
{
using HoloLaneBoundaryType = holo::common::LaneBoundary<holo::numerics::Polynomial<float32_t, 3>>;

static const uint32_t  BOSCH_MPC_POLYFIT_POINTS_NUM      = 10U;
static const float32_t BOSCH_MPC_LANEBOUNDARY_LENGTH_MIN = 1.0f;

class BoschMpcLaneBoundary
{
public:
    /**
     * @brief Default constructor.
     */
    BoschMpcLaneBoundary() noexcept
      : timestamp_()
      , line_number_(0)
      , line_type_(0)
      , line_color_(0)
      , horizon_curvature_(0)
      , dx_begin_(0.0f)
      , dx_end_(0.0f)
      , dy_(0.0f)
      , angle_diff_(0.0f)
      , line_width_(0.0f)
      , confidence_(0.0f)
      , part_a_valid_(false)
      , part_b_valid_(false)
    {
    }
    /**
     * @brief Copy constructor
     *
     * @param other The other BoschMpcLaneBoundary.
     */
    BoschMpcLaneBoundary(const BoschMpcLaneBoundary& other) noexcept
      : timestamp_(other.timestamp_)
      , line_number_(other.line_number_)
      , line_type_(other.line_type_)
      , line_color_(other.line_color_)
      , horizon_curvature_(other.horizon_curvature_)
      , dx_begin_(other.dx_begin_)
      , dx_end_(other.dx_end_)
      , dy_(other.dy_)
      , angle_diff_(other.angle_diff_)
      , line_width_(other.line_width_)
      , confidence_(other.confidence_)
      , part_a_valid_(other.part_a_valid_)
      , part_b_valid_(other.part_b_valid_)
    {
    }
    /**
     * @brief Copy assign operator
     *
     * @param other The other BoschMpcLaneBoundary.
     *
     * @return Reference to this laneboundary.
     */
    BoschMpcLaneBoundary& operator=(const BoschMpcLaneBoundary& other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }
        timestamp_         = other.timestamp_;
        line_number_       = other.line_number_;
        line_type_         = other.line_type_;
        line_color_        = other.line_color_;
        horizon_curvature_ = other.horizon_curvature_;
        dx_begin_          = other.dx_begin_;
        dx_end_            = other.dx_end_;
        dy_                = other.dy_;
        angle_diff_        = other.angle_diff_;
        line_width_        = other.line_width_;
        confidence_        = other.confidence_;
        part_a_valid_      = other.part_a_valid_;
        part_b_valid_      = other.part_b_valid_;
        return *this;
    }
    /**
     * @brief      Convert BoschMpcLaneBoundary to HoloLaneBoundary with transform
     *
     * @param      output            The output
     * @param[in]  extrinsic         The extrinsic
     *
     */
    void ConvertToHoloLaneBoundary(std::shared_ptr<HoloLaneBoundaryType>& output,
                                   const holo::common::Extrinsicf&        extrinsic) const;
    /**
     * @brief Set time stamp
     *
     * @param[in] time_stamp
     */
    inline void SetTimestamp(const holo::common::Timestamp& timestamp) noexcept
    {
        timestamp_ = timestamp;
    }
    /**
     * @brief Get time stamp
     *
     * @return timestamp_
     */
    inline holo::common::Timestamp GetTimestamp() const noexcept
    {
        return timestamp_;
    }
    /**
     * @brief      Sets the line number.
     *
     * @param[in]  line_number  The line number
     */
    inline void SetLineNumber(uint16_t line_number) noexcept
    {
        line_number_ = line_number;
    }
    /**
     * @brief      Gets the line number.
     *
     * @return     The line number.
     */
    inline uint16_t GetLineNumber() const noexcept
    {
        return line_number_;
    }
    /**
     * @brief      Sets the line type.
     *
     * @param[in]  line_type  The line type
     */
    inline void SetLineType(uint16_t line_type) noexcept
    {
        line_type_ = line_type;
    }
    /**
     * @brief      Gets the line type.
     *
     * @return     The line type.
     */
    inline uint16_t GetLineType() const noexcept
    {
        return line_type_;
    }
    /**
     * @brief      Sets the line color.
     *
     * @param[in]  line_color  The line color
     */
    inline void SetLineColor(uint16_t line_color) noexcept
    {
        line_color_ = line_color;
    }
    /**
     * @brief      Gets the line color.
     *
     * @return     The line color.
     */
    inline uint16_t GetLineColor() const noexcept
    {
        return line_color_;
    }
    /**
     * @brief      Sets the horizon curvature.
     *
     * @param[in]  horizon_curvature  The horizon curvature
     */
    inline void SetHorizonCurvature(int16_t horizon_curvature) noexcept
    {
        horizon_curvature_ = horizon_curvature;
    }
    /**
     * @brief      Gets the horizon curvature.
     *
     * @return     The horizon curvature.
     */
    inline int16_t GetHorizonCurvature() const noexcept
    {
        return horizon_curvature_;
    }
    /**
     * @brief      Sets the dx begin.
     *
     * @param[in]  dx_begin  The dx begin
     */
    inline void SetDxBegin(float32_t dx_begin) noexcept
    {
        dx_begin_ = dx_begin;
    }
    /**
     * @brief      Gets the dx begin.
     *
     * @return     The dx begin.
     */
    inline float32_t GetDxBegin() const noexcept
    {
        return dx_begin_;
    }
    /**
     * @brief      Sets the dx end.
     *
     * @param[in]  dx_end  The dx end
     */
    inline void SetDxEnd(float32_t dx_end) noexcept
    {
        dx_end_ = dx_end;
    }
    /**
     * @brief      Gets the dx end.
     *
     * @return     The dx end.
     */
    inline float32_t GetDxEnd() const noexcept
    {
        return dx_end_;
    }
    /**
     * @brief      Sets the dy.
     *
     * @param[in]  dy    The new value
     */
    inline void SetDy(float32_t dy) noexcept
    {
        dy_ = dy;
    }
    /**
     * @brief      Gets the dy.
     *
     * @return     The dy.
     */
    inline float32_t GetDy() const noexcept
    {
        return dy_;
    }
    /**
     * @brief      Sets the angle difference.
     *
     * @param[in]  angle_diff  The angle difference
     */
    inline void SetAngleDiff(float32_t angle_diff) noexcept
    {
        angle_diff_ = angle_diff;
    }
    /**
     * @brief      Gets the angle difference.
     *
     * @return     The angle difference.
     */
    inline float32_t GetAngleDiff() const noexcept
    {
        return angle_diff_;
    }
    /**
     * @brief      Sets the line width.
     *
     * @param[in]  line_width  The line width
     */
    inline void SetLineWidth(float32_t line_width) noexcept
    {
        line_width_ = line_width;
    }
    /**
     * @brief      Gets the line width.
     *
     * @return     The line width.
     */
    inline float32_t GetLineWidth() const noexcept
    {
        return line_width_;
    }
    /**
     * @brief      Sets the confidence.
     *
     * @param[in]  confidence  The confidence
     */
    inline void SetConfidence(float32_t confidence) noexcept
    {
        confidence_ = confidence;
    }
    /**
     * @brief      Gets the confidence.
     *
     * @return     The confidence.
     */
    inline float32_t GetConfidence() const noexcept
    {
        return confidence_;
    }
    /**
     * @brief Check is this obstacle is valid
     *
     * @return true if the obstacle is valid otherwise return false
     */
    inline bool_t IsValid() const noexcept
    {
        return part_a_valid_ && part_b_valid_;
    }
    /**
     * @brief Set part A of obstacle is valid
     *
     * @param[in] valid
     */
    inline void SetPartAValid(bool_t valid) noexcept
    {
        part_a_valid_ = valid;
    }
    /**
     * @brief Get part_a_valid
     *
     * @return part_a_valid_
     */
    inline bool_t GetPartAValid() const noexcept
    {
        return part_a_valid_;
    }
    /**
     * @brief Set part B of obstacle is valid
     *
     * @param[in] valid
     */
    inline void SetPartBValid(bool_t valid) noexcept
    {
        part_b_valid_ = valid;
    }
    /**
     * @brief Get part_b_valid
     *
     * @return part_b_valid_
     */
    inline bool_t GetPartBValid() const noexcept
    {
        return part_b_valid_;
    }

private:
    /* data timestamp */
    holo::common::Timestamp timestamp_;
    /* data members */
    uint16_t  line_number_;        // line number  | (1,0) [1|15] ""
    uint16_t  line_type_;          // line type    | (1,0) [0|7] ""
    uint16_t  line_color_;         // line color   | (1,0) [0|7] ""
    int16_t   horizon_curvature_;  // hor curvature| (1,-2047) [-2047|2048] ""
    float32_t dx_begin_;           // x start      | (0.25,0) [0|63.75] "Unit_Meter"
    float32_t dx_end_;             // x end        | (0.25,0) [0|127.75] "Unit_Meter"
    float32_t dy_;                 // y0           | (0.00390625,-8) [-8|7.99609375] "Unit_Meter"
    float32_t angle_diff_;         // angle in rad | (0.00048828125,-1) [-1|0.99951171875] "Unit_Radia"
    float32_t line_width_;         // line width   | (0.00390625,-0.5) [-0.5|0.49609375] "Unit_Meter"
    float32_t confidence_;         // confidence   | (0.015625,0) [0|0.984375] "Unit_Meter"
    /* parts valid */
    bool_t part_a_valid_;  //! part a valid indicator
    bool_t part_b_valid_;  //! part b valid indicator
    /* const values */
    static const uint32_t                    klane_boundaries_number_;
    static const float64_t                   khorizon_curvature_factor_;
    static const holo::common::BoundaryStyle ktype_remap_table_[8];
    static const holo::common::BoundaryColor kcolor_remap_table_[8];
};

}  // namespace bosch_mpc
}  // namespace sensors
}  // namespace holo
#endif
