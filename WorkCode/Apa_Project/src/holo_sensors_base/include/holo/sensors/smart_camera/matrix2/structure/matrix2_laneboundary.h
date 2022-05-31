/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file horizon_matrix2_laneboundary.h
 * @brief A class to describe delphi horizon matrix2 laneboundary
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/05/21
 */

#ifndef HOLO_SENSORS_COMMON_SMART_CAMERA_HORIZON_MATRIX2_LANEBOUNDARY_H_
#define HOLO_SENSORS_COMMON_SMART_CAMERA_HORIZON_MATRIX2_LANEBOUNDARY_H_

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
namespace horizon_matrix2
{
using HoloLaneBoundaryType = holo::common::LaneBoundary<holo::numerics::Polynomial<float32_t, 3>>;

static const uint32_t  HORIZON_MATRIX2_POLYFIT_POINTS_NUM      = 10U;
static const float32_t HORIZON_MATRIX2_LANEBOUNDARY_LENGTH_MIN = 1.0f;

class HorizonMatrix2LaneBoundary
{
public:
    /**
     * @brief Default constructor.
     */
    HorizonMatrix2LaneBoundary() noexcept
      : timestamp_()
      , type_class_(0)
      , mark_color_(0)
      , quality_(0)
      , crossing_(0)
      , confidence_(0.0f)
      , c0_(0.0f)
      , c1_(0.0f)
      , c2_(0.0f)
      , c3_(0.0f)
      , tlc_(0.0f)
      , width_marking_(0.0f)
      , view_range_start_(0.0f)
      , view_range_end_(0.0f)
      , part_a_valid_(0)
      , part_b_valid_(0)
    {
    }
    /**
     * @brief Copy constructor
     *
     * @param other The other HorizonMatrix2LaneBoundary.
     */
    HorizonMatrix2LaneBoundary(const HorizonMatrix2LaneBoundary& other) noexcept
      : timestamp_(other.timestamp_)
      , type_class_(other.type_class_)
      , mark_color_(other.mark_color_)
      , quality_(other.quality_)
      , crossing_(other.crossing_)
      , confidence_(other.confidence_)
      , c0_(other.c0_)
      , c1_(other.c1_)
      , c2_(other.c2_)
      , c3_(other.c3_)
      , tlc_(other.tlc_)
      , width_marking_(other.width_marking_)
      , view_range_start_(other.view_range_start_)
      , view_range_end_(other.view_range_end_)
      , part_a_valid_(other.part_a_valid_)
      , part_b_valid_(other.part_b_valid_)
    {
    }
    /**
     * @brief Copy assign operator
     *
     * @param other The other HorizonMatrix2LaneBoundary.
     *
     * @return Reference to this laneboundary.
     */
    HorizonMatrix2LaneBoundary& operator=(const HorizonMatrix2LaneBoundary& other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }
        timestamp_        = other.timestamp_;
        type_class_       = other.type_class_;
        mark_color_       = other.mark_color_;
        quality_          = other.quality_;
        crossing_         = other.crossing_;
        confidence_       = other.confidence_;
        c0_               = other.c0_;
        c1_               = other.c1_;
        c2_               = other.c2_;
        c3_               = other.c3_;
        tlc_              = other.tlc_;
        width_marking_    = other.width_marking_;
        view_range_start_ = other.view_range_start_;
        view_range_end_   = other.view_range_end_;
        part_a_valid_     = other.part_a_valid_;
        part_b_valid_     = other.part_b_valid_;
        return *this;
    }
    /**
     * @brief      Convert HorizonMatrix2LaneBoundary to HoloLaneBoundary with transform
     *
     * @param[in]  extrinsic         The extrinsic
     * @param      output            the HoloLaneBoundary
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
    inline void SetConfidence(float32_t confidence) noexcept
    {
        confidence_ = confidence;
    }
    inline float32_t GetConfidence() const noexcept
    {
        return confidence_;
    }
    inline void SetTypeClass(uint8_t type_class) noexcept
    {
        type_class_ = type_class;
    }
    inline uint8_t GetTypeClass() const noexcept
    {
        return type_class_;
    }
    inline void SetMarkColor(uint8_t mark_color) noexcept
    {
        mark_color_ = mark_color;
    }
    inline uint8_t GetMarkColor() const noexcept
    {
        return mark_color_;
    }
    inline void SetQuality(uint8_t quality) noexcept
    {
        quality_ = quality;
    }
    inline uint8_t GetQuality() const noexcept
    {
        return quality_;
    }
    inline void SetCrossing(bool_t crossing) noexcept
    {
        crossing_ = crossing;
    }
    inline bool_t GetCrossing() const noexcept
    {
        return crossing_;
    }
    inline void SetC0(float32_t c0) noexcept
    {
        c0_ = c0;
    }
    inline float32_t GetC0() const noexcept
    {
        return c0_;
    }
    inline void SetC1(float32_t c1) noexcept
    {
        c1_ = c1;
    }
    inline float32_t GetC1() const noexcept
    {
        return c1_;
    }
    inline void SetC2(float32_t c2) noexcept
    {
        c2_ = c2;
    }
    inline float32_t GetC2() const noexcept
    {
        return c2_;
    }
    inline void SetC3(float32_t c3) noexcept
    {
        c3_ = c3;
    }
    inline float32_t GetC3() const noexcept
    {
        return c3_;
    }
    inline void SetTlc(float32_t tlc) noexcept
    {
        tlc_ = tlc;
    }
    inline float32_t GetTlc() const noexcept
    {
        return tlc_;
    }
    inline void SetWidthMarking(float32_t width_marking) noexcept
    {
        width_marking_ = width_marking;
    }
    inline float32_t GetWidthMarking() const noexcept
    {
        return width_marking_;
    }
    inline void SetViewRangeStart(float32_t view_range_start) noexcept
    {
        view_range_start_ = view_range_start;
    }
    inline float32_t GetViewRangeStart() const noexcept
    {
        return view_range_start_;
    }
    inline void SetViewRangeEnd(float32_t view_range_end) noexcept
    {
        view_range_end_ = view_range_end;
    }
    inline float32_t GetViewRangeEnd() const noexcept
    {
        return view_range_end_;
    }
    inline void SetPartAValid(bool_t part_a_valid) noexcept
    {
        part_a_valid_ = part_a_valid;
    }
    inline bool_t GetPartAValid() const noexcept
    {
        return part_a_valid_;
    }
    inline void SetPartBValid(bool_t part_b_valid) noexcept
    {
        part_b_valid_ = part_b_valid;
    }
    inline bool_t GetPartBValid() const noexcept
    {
        return part_b_valid_;
    }
    /**
     * @brief      Gets the valid.
     *
     * @return     The valid.
     */
    inline bool_t IsAllPartsValid() const noexcept
    {
        return part_a_valid_ && part_b_valid_;
    }

private:
    /* data timestamp */
    holo::common::Timestamp timestamp_;  //! timestamp

    uint8_t   type_class_;        //!  0| 4@1+ (1,0) [0|15] "Enum" Matrix
    uint8_t   mark_color_;        //! 29| 3@1+ (1,0) [0|3] "Enum" Matrix
    uint8_t   quality_;           //!  4| 2@1+ (1,0) [0|3] "Enum" Matrix
    uint8_t   crossing_;          //! 28| 1@1+ (1,0) [0|1] "NA" Matrix
    float32_t confidence_;        //! 57| 4@1+ (0.1,0) [0|1] "prob" Matrix
    float32_t c0_;                //!  6|11@1- (0.01,0) [-10|10] "meter" Matrix
    float32_t c1_;                //!  0|10@1- (0.0009765625,0) [-0.357|0.357] "rad" Matrix
    float32_t c2_;                //! 17|16@1- (9.77E-007,0) [-0.032|0.032] "1/meter" Matrix
    float32_t c3_;                //! 33|16@1- (3.7252902985E-009,0) [-0.000122|0.000122] "1/meter^2" Matrix
    float32_t tlc_;               //! 56| 8@1+ (0.01,0) [0|2] "s" Matrix
    float32_t width_marking_;     //! 49| 8@1+ (0.01,0) [0|2.5] "m" Matrix
    float32_t view_range_start_;  //! 10| 9@1+ (0.5,0) [0|200] "meter" Matrix
    float32_t view_range_end_;    //! 19| 9@1+ (0.5,0) [0|200] "meter" Matrix
    bool_t    part_a_valid_;      //! part a valid indicator
    bool_t    part_b_valid_;      //! part a valid indicator
    /* const values */
    static const holo::common::BoundaryStyle type_remap_table_const_[16];
    static const holo::common::BoundaryColor color_remap_table_const_[4];
};

}  // namespace horizon_matrix2
}  // namespace sensors
}  // namespace holo
#endif
