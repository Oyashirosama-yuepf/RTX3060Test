/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file me8_laneboundary.h
 * @brief A class to describe me8 laneboundary
 * @author zhangtongyang<zhangtongyang@holomatic.com>
 * @date 2021/12/16
 */

#ifndef HOLO_SENSORS_COMMON_SMART_CAMERA_ME8_LANEBOUNDARY_H_
#define HOLO_SENSORS_COMMON_SMART_CAMERA_ME8_LANEBOUNDARY_H_

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
namespace me8
{
using HoloLaneBoundaryType = holo::common::LaneBoundary<holo::numerics::Polynomial<float32_t, 3>>;

static const float32_t ME8_LANEBOUNDARY_LENGTH_MIN = 1.0f;

enum class Me8AdjacentLineRole: uint8_t
{
        NONE  = 0U,
        LEFT_LEFT,
        LEFT_RIGHT,
        RIGHT_LEFT,
        RIGHT_RIGHT
};
enum class Me8HostLineSide: uint8_t
{
        UNKNOWN  = 0U,
        LEFT,
        RIGHT
};

class Me8LaneBoundaryHost
{
public:
    Me8LaneBoundaryHost()
      : lh_confidence_(0.0f)
      , lh_lanemark_type_(0)
      , lh_side_(0)
      , lh_vr_start_(0.0f)
      , lh_vr_end_(0.0f)
      , lh_c0_(0.0f)
      , lh_c1_(0.0f)
      , lh_c2_(0.0f)
      , lh_c3_(0.0f)
      , part_a_valid_(false)
      , part_b_valid_(false)
    {
    }

    Me8LaneBoundaryHost(const Me8LaneBoundaryHost& other) noexcept
      : lh_confidence_(other.lh_confidence_)
      , lh_lanemark_type_(other.lh_lanemark_type_)
      , lh_side_(other.lh_side_)
      , lh_vr_start_(other.lh_vr_start_)
      , lh_vr_end_(other.lh_vr_end_)
      , lh_c0_(other.lh_c0_)
      , lh_c1_(other.lh_c1_)
      , lh_c2_(other.lh_c2_)
      , lh_c3_(other.lh_c3_)
      , part_a_valid_(other.part_a_valid_)
      , part_b_valid_(other.part_b_valid_)
    {
    }

    Me8LaneBoundaryHost& operator=(const Me8LaneBoundaryHost& other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }
        lh_confidence_    = other.lh_confidence_;
        lh_lanemark_type_ = other.lh_lanemark_type_;
        lh_side_          = other.lh_side_;
        lh_vr_start_      = other.lh_vr_start_;
        lh_vr_end_        = other.lh_vr_end_;
        lh_c0_            = other.lh_c0_;
        lh_c1_            = other.lh_c1_;
        lh_c2_            = other.lh_c2_;
        lh_c3_            = other.lh_c3_;
        part_a_valid_     = other.part_a_valid_;
        part_b_valid_     = other.part_b_valid_;
    }

    void ConvertToHoloLaneBoundary(std::shared_ptr<HoloLaneBoundaryType>& output,
                                   const holo::common::Extrinsicf&        extrinsic) const;

    inline void SetLHConfidence(float32_t lh_confidence) noexcept
    {
        lh_confidence_ = lh_confidence;
    }

    inline float32_t GetLHConfidence() const noexcept
    {
        return lh_confidence_;
    }

    inline void SetLHLanemarkType(uint8_t lh_lanemark_type) noexcept
    {
        lh_lanemark_type_ = lh_lanemark_type;
    }

    inline uint8_t GetLHLanemarkType() const noexcept
    {
        return lh_lanemark_type_;
    }

    inline void SetLHSide(uint8_t lh_side) noexcept
    {
        lh_side_ = lh_side;
    }

    inline uint8_t GetLHSide() const noexcept
    {
        return lh_side_;
    }

    inline void SetLHVrStart(float32_t lh_vr_start) noexcept
    {
        lh_vr_start_ = lh_vr_start;
    }

    inline float32_t GetLHVrStart() const noexcept
    {
        return lh_vr_start_;
    }

    inline void SetLHVrEnd(float32_t lh_vr_end) noexcept
    {
        lh_vr_end_ = lh_vr_end;
    }

    inline float32_t GetLHVrEnd() const noexcept
    {
        return lh_vr_end_;
    }

    inline void SetLHC0(float32_t lh_c0) noexcept
    {
        lh_c0_ = lh_c0;
    }

    inline float32_t GetLHC0() const noexcept
    {
        return lh_c0_;
    }

    inline void SetLHC1(float32_t lh_c1) noexcept
    {
        lh_c1_ = lh_c1;
    }

    inline float32_t GetLHC1() const noexcept
    {
        return lh_c1_;
    }

    inline void SetLHC2(float32_t lh_c2) noexcept
    {
        lh_c2_ = lh_c2;
    }

    inline float32_t GetLHC2() const noexcept
    {
        return lh_c2_;
    }

    inline void SetLHC3(float32_t lh_c3) noexcept
    {
        lh_c3_ = lh_c3;
    }

    inline float32_t GetLHC3() const noexcept
    {
        return lh_c3_;
    }

    inline void SetPartAValid(bool_t valid) noexcept
    {
        part_a_valid_ = valid;
    }

    inline bool_t GetPartAValid() const noexcept
    {
        return part_a_valid_;
    }

    inline void SetPartBValid(bool_t valid) noexcept
    {
        part_b_valid_ = valid;
    }

    inline bool_t GetPartBValid() const noexcept
    {
        return part_b_valid_;
    }

    inline bool_t IsValid() const noexcept
    {
        return part_a_valid_ && part_b_valid_;
    }

private:
    /* part A */
    float32_t lh_confidence_;     //! 0|7@1+ (0.01,0) [0|1] "NA" Vector__XXX
    uint8_t   lh_lanemark_type_;  //! 7|4@1+ (1,0) [0|6] "ENUM" Vector__XXX
    uint8_t   lh_side_;           //! 11|2@1+ (1,0) [0|2] "ENUM" Vector__XXX
    float32_t lh_vr_start_;       //! 13|15@1+ (0.01,0) [0|200] "m" Vector__XXX
    float32_t lh_vr_end_;         //! 28|15@1+ (0.01,0) [0|200] "m" Vector__XXX

    /* part B */
    float32_t lh_c0_;  //! 0|11@1+ (0.01,-10) [-10|10] "meter" Vector__XXX
    float32_t lh_c1_;  //! 11|10@1+ (0.000977,-0.357) [-0.357|0.357] "rad" Vector__XXX
    float32_t lh_c2_;  //! 21|16@1+ (9.77E-007,-0.032) [-0.032|0.032] "1/m" Vector__XXX
    float32_t lh_c3_;  //! 37|16@1+ (3.73E-009,-0.000122) [-0.000122|0.000122] "1/m2" Vector__XXX

    bool_t part_a_valid_;  //! part a valid indicator
    bool_t part_b_valid_;  //! part b valid indicator

    static const holo::common::BoundaryStyle ktype_remap_table_[7];
    static const float32_t                   kboundary_width_;
};

class Me8LaneBoundaryAdjacent
{
public:
    Me8LaneBoundaryAdjacent()
      : adjacent_type_(0)
      , adjacent_confidence_(0.0f)
      , adjacent_view_range_start_(0.0f)
      , adjacent_view_range_end_(0.0f)
      , adjacent_line_role_(0)
      , adjacent_line_c0_(0.0f)
      , adjacent_line_c1_(0.0f)
      , adjacent_line_c2_(0.0f)
      , adjacent_line_c3_(0.0f)
      , part_a_valid_(false)
      , part_b_valid_(false)
    {
    }

    Me8LaneBoundaryAdjacent(const Me8LaneBoundaryAdjacent& other) noexcept
      : adjacent_type_(other.adjacent_type_)
      , adjacent_confidence_(other.adjacent_confidence_)
      , adjacent_view_range_start_(other.adjacent_view_range_start_)
      , adjacent_view_range_end_(other.adjacent_view_range_end_)
      , adjacent_line_role_(other.adjacent_line_role_)
      , adjacent_line_c0_(other.adjacent_line_c0_)
      , adjacent_line_c1_(other.adjacent_line_c1_)
      , adjacent_line_c2_(other.adjacent_line_c2_)
      , adjacent_line_c3_(other.adjacent_line_c3_)
      , part_a_valid_(other.part_a_valid_)
      , part_b_valid_(other.part_b_valid_)
    {
    }

    Me8LaneBoundaryAdjacent& operator=(const Me8LaneBoundaryAdjacent& other) noexcept
    {    
        if (this == &other)
        {
            return *this;
        }
        adjacent_type_             = other.adjacent_type_;
        adjacent_confidence_       = other.adjacent_confidence_;
        adjacent_view_range_start_ = other.adjacent_view_range_start_;
        adjacent_view_range_end_   = other.adjacent_view_range_end_;
        adjacent_line_role_        = other.adjacent_line_role_;
        adjacent_line_c0_          = other.adjacent_line_c0_;
        adjacent_line_c1_          = other.adjacent_line_c1_;
        adjacent_line_c2_          = other.adjacent_line_c2_;
        adjacent_line_c3_          = other.adjacent_line_c3_;
        part_a_valid_              = other.part_a_valid_;
        part_b_valid_              = other.part_b_valid_;
    }
    void ConvertToHoloLaneBoundary(std::shared_ptr<HoloLaneBoundaryType>& output,
                                   const holo::common::Extrinsicf&        extrinsic) const;

    inline void SetAdjacentType(uint8_t adjacent_type) noexcept
    {
        adjacent_type_ = adjacent_type;
    }

    inline uint8_t GetAdjacentType() const noexcept
    {
        return adjacent_type_;
    }

    inline void SetAdjacentConfidence(float32_t adjacent_confidence) noexcept
    {
        adjacent_confidence_ = adjacent_confidence;
    }

    inline float32_t GetAdjacentConfidence() const noexcept
    {
        return adjacent_confidence_;
    }

    inline void SetAdjacentViewRangeStart(float32_t adjacent_view_range_start) noexcept
    {
        adjacent_view_range_start_ = adjacent_view_range_start;
    }

    inline float32_t GetAdjacentViewRangeStart() const noexcept
    {
        return adjacent_view_range_start_;
    }

    inline void SetAdjacentViewRangeEnd(float32_t adjacent_view_range_end) noexcept
    {
        adjacent_view_range_end_ = adjacent_view_range_end;
    }

    inline float32_t GetAdjacentViewRangeEnd() const noexcept
    {
        return adjacent_view_range_end_;
    }

    inline void SetAdjacentLineRole(uint8_t adjacent_line_role) noexcept
    {
        adjacent_line_role_ = adjacent_line_role;
    }

    inline uint8_t GetAdjacentLineRole() const noexcept
    {
        return adjacent_line_role_;
    }

    inline void SetAdjacentC0(float32_t adjacent_line_c0) noexcept
    {
        adjacent_line_c0_ = adjacent_line_c0;
    }

    inline float32_t GetAdjacentC0() const noexcept
    {
        return adjacent_line_c0_;
    }

    inline void SetAdjacentC1(float32_t adjacent_line_c1) noexcept
    {
        adjacent_line_c1_ = adjacent_line_c1;
    }

    inline float32_t GetAdjacentC1() const noexcept
    {
        return adjacent_line_c1_;
    }

    inline void SetAdjacentC2(float32_t adjacent_line_c2) noexcept
    {
        adjacent_line_c2_ = adjacent_line_c2;
    }

    inline float32_t GetAdjacentC2() const noexcept
    {
        return adjacent_line_c2_;
    }

    inline void SetAdjacentC3(float32_t adjacent_line_c3) noexcept
    {
        adjacent_line_c3_ = adjacent_line_c3;
    }

    inline float32_t GetAdjacentC3() const noexcept
    {
        return adjacent_line_c3_;
    }

    inline void SetPartAValid(bool_t valid) noexcept
    {
        part_a_valid_ = valid;
    }

    inline bool_t GetPartAValid() const noexcept
    {
        return part_a_valid_;
    }

    inline void SetPartBValid(bool_t valid) noexcept
    {
        part_b_valid_ = valid;
    }

    inline bool_t GetPartBValid() const noexcept
    {
        return part_b_valid_;
    }

    inline bool_t IsValid() const noexcept
    {
        return part_a_valid_ && part_b_valid_;
    }

private:
    /* part A */
    uint8_t   adjacent_type_;              //! 0|4@1+ (1,0) [0|15] "ENUM" Vector__XXX
    float32_t adjacent_confidence_;        //! 4|7@1+ (0.01,0) [0|1] "conf" Vector__XXX
    float32_t adjacent_view_range_start_;  //! 11|15@1+ (0.01,0) [0|200] "m" Vector__XXX
    float32_t adjacent_view_range_end_;    //! 26|15@1+ (0.01,0) [0|200] "m" Vector__XXX
    uint8_t   adjacent_line_role_;         //! 41|4@1+ (1,0) [0|8] "ENUM" Vector__XXX

    /* part B */
    float32_t adjacent_line_c0_;  //! 0|11@1+ (0.01,-10) [-10|10] "meter" Vector__XXX
    float32_t adjacent_line_c1_;  //! 11|10@1+ (0.000977,-0.357) [-0.357|0.357] "rad" Vector__XXX
    float32_t adjacent_line_c2_;  //! 21|16@1+ (9.77E-007,-0.032) [-0.032|0.032] "1/m" Vector__XXX
    float32_t adjacent_line_c3_;  //! 37|16@1+ (3.73E-009,-0.000122) [-0.000122|0.000122] "1/m2" Vector__XXX

    bool_t part_a_valid_;  //! part a valid indicator
    bool_t part_b_valid_;  //! part b valid indicator

    static const holo::common::BoundaryStyle ktype_remap_table_[16];
    static const float32_t                   kboundary_width_;
};
}  // namespace me8
}  // namespace sensors
}  // namespace holo
#endif