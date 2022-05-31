/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mobileye_laneboundary.h
 * @brief A class to describe mobileye laneboundary
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/01/14
 */

#ifndef HOLO_SENSORS_COMMON_SMART_CAMERA_MOBILEYE_LANEBOUNDARY_H_
#define HOLO_SENSORS_COMMON_SMART_CAMERA_MOBILEYE_LANEBOUNDARY_H_

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
namespace mobileye
{
using HoloLaneBoundaryType = holo::common::LaneBoundary<holo::numerics::Polynomial<float32_t, 3>>;

static const uint32_t  MOBILEYE_POLYFIT_POINTS_NUM      = 10U;
static const float32_t MOBILEYE_LANEBOUNDARY_LENGTH_MIN = 1.0f;

class MobileyeLaneBoundary
{
public:
    /**
     * @brief Default constructor.
     */
    MobileyeLaneBoundary() noexcept
      : timestamp_()
      , c0_(0.0f)
      , c1_(0.0f)
      , c2_(0.0f)
      , c3_(0.0f)
      , range_start_(0.0f)
      , range_end_(0.0f)
      , width_(0.0f)
      , tlc_(0.0f)
      , location_(0)
      , type_(0)
      , color_(0)
      , quality_(0)
      , crossing_(false)
      , part0_valid_(false)
      , part1_valid_(false)
      , part2_valid_(false)
    {
    }
    /**
     * @brief Copy constructor
     *
     * @param other The other MobileyeLaneBoundary.
     */
    MobileyeLaneBoundary(const MobileyeLaneBoundary& other) noexcept
      : timestamp_(other.timestamp_)
      , c0_(other.c0_)
      , c1_(other.c1_)
      , c2_(other.c2_)
      , c3_(other.c3_)
      , range_start_(other.range_start_)
      , range_end_(other.range_end_)
      , width_(other.width_)
      , tlc_(other.tlc_)
      , location_(other.location_)
      , type_(other.type_)
      , color_(other.color_)
      , quality_(other.quality_)
      , crossing_(other.crossing_)
      , part0_valid_(other.part0_valid_)
      , part1_valid_(other.part1_valid_)
      , part2_valid_(other.part2_valid_)
    {
    }
    /**
     * @brief Copy assign operator
     *
     * @param other The other MobileyeLaneBoundary.
     *
     * @return Reference to this laneboundary.
     */
    MobileyeLaneBoundary& operator=(const MobileyeLaneBoundary& other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }
        timestamp_   = other.timestamp_;
        c0_          = other.c0_;
        c1_          = other.c1_;
        c2_          = other.c2_;
        c3_          = other.c3_;
        range_start_ = other.range_start_;
        range_end_   = other.range_end_;
        width_       = other.width_;
        tlc_         = other.tlc_;
        location_    = other.location_;
        type_        = other.type_;
        color_       = other.color_;
        quality_     = other.quality_;
        crossing_    = other.crossing_;
        part0_valid_ = other.part0_valid_;
        part1_valid_ = other.part1_valid_;
        part2_valid_ = other.part2_valid_;
        return *this;
    }
    /**
     * @brief      Convert MobileyeLaneBoundary to HoloLaneBoundary with
     *             transform
     *
     * @param      output     The HoloLaneBoundary
     * @param[in]  extrinsic  The extrinsic to target coordinate
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
     * @brief      Sets the c0.
     *
     * @param[in]  c0    The new value
     */
    inline void SetC0(float32_t c0) noexcept
    {
        c0_ = c0;
    }
    /**
     * @brief      Gets the c0.
     *
     * @return     The c0.
     */
    inline float32_t GetC0() const noexcept
    {
        return c0_;
    }
    /**
     * @brief      Sets the c1.
     *
     * @param[in]  c1    The new value
     */
    inline void SetC1(float32_t c1) noexcept
    {
        c1_ = c1;
    }
    /**
     * @brief      Gets the c1.
     *
     * @return     The c1.
     */
    inline float32_t GetC1() const noexcept
    {
        return c1_;
    }
    /**
     * @brief      Sets the c 2.
     *
     * @param[in]  c2    The new value
     */
    inline void SetC2(float32_t c2) noexcept
    {
        c2_ = c2;
    }
    /**
     * @brief      Gets the c 2.
     *
     * @return     The c2.
     */
    inline float32_t GetC2() const noexcept
    {
        return c2_;
    }
    /**
     * @brief      Sets the c3.
     *
     * @param[in]  c3    The new value
     */
    inline void SetC3(float32_t c3) noexcept
    {
        c3_ = c3;
    }
    /**
     * @brief      Gets the c3.
     *
     * @return     The c3.
     */
    inline float32_t GetC3() const noexcept
    {
        return c3_;
    }
    /**
     * @brief      Sets the range start.
     *
     * @param[in]  range_start  The range start
     */
    inline void SetRangeStart(float32_t range_start) noexcept
    {
        range_start_ = range_start;
    }
    /**
     * @brief      Gets the range start.
     *
     * @return     The range start.
     */
    inline float32_t GetRangeStart() const noexcept
    {
        return range_start_;
    }
    /**
     * @brief      Sets the range end.
     *
     * @param[in]  range_end  The range end
     */
    inline void SetRangeEnd(float32_t range_end) noexcept
    {
        range_end_ = range_end;
    }
    /**
     * @brief      Gets the range end.
     *
     * @return     The range end.
     */
    inline float32_t GetRangeEnd() const noexcept
    {
        return range_end_;
    }
    /**
     * @brief      Sets the mark width.
     *
     * @param[in]  width  The mark width
     */
    inline void SetMarkWidth(float32_t width) noexcept
    {
        width_ = width;
    }
    /**
     * @brief      Gets the mark width.
     *
     * @return     The mark width.
     */
    inline float32_t GetMarkWidth() const noexcept
    {
        return width_;
    }
    /**
     * @brief      Sets the tlc.
     *
     * @param[in]  tlc   The new value
     */
    inline void SetTlc(float32_t tlc) noexcept
    {
        tlc_ = tlc;
    }
    /**
     * @brief      Gets the tlc.
     *
     * @return     The tlc.
     */
    inline float32_t GetTlc() const noexcept
    {
        return tlc_;
    }
    /**
     * @brief      Sets the location.
     *
     * @param[in]  location  The location
     */
    inline void SetLocation(uint8_t location) noexcept
    {
        location_ = location;
    }
    /**
     * @brief      Gets the location.
     *
     * @return     The location.
     */
    inline uint8_t GetLocation() const noexcept
    {
        return location_;
    }
    /**
     * @brief      Sets the type.
     *
     * @param[in]  type  The type
     */
    inline void SetType(uint8_t type) noexcept
    {
        type_ = type;
    }
    /**
     * @brief      Gets the type.
     *
     * @return     The type.
     */
    inline uint8_t GetType() const noexcept
    {
        return type_;
    }
    /**
     * @brief      Sets the color.
     *
     * @param[in]  color  The color
     */
    inline void SetColor(uint8_t color) noexcept
    {
        color_ = color;
    }
    /**
     * @brief      Gets the color.
     *
     * @return     The color.
     */
    inline uint8_t GetColor() const noexcept
    {
        return color_;
    }
    /**
     * @brief      Sets the quality.
     *
     * @param[in]  quality  The quality
     */
    inline void SetQuality(uint8_t quality) noexcept
    {
        quality_ = quality;
    }
    /**
     * @brief      Gets the quality.
     *
     * @return     The quality.
     */
    inline uint8_t GetQuality() const noexcept
    {
        return quality_;
    }
    /**
     * @brief      Sets the crossing indicator.
     *
     * @param[in]  crossing  The crossing
     */
    inline void SetCrossing(bool_t crossing) noexcept
    {
        crossing_ = crossing;
    }
    /**
     * @brief      Gets the crossing indicator.
     *
     * @return     The crossing.
     */
    inline bool_t GetCrossing() const noexcept
    {
        return crossing_;
    }
    /**
     * @brief      Sets the part 0 valid.
     *
     * @param[in]  part0_valid  The part 0 valid
     */
    inline void SetPart0Valid(bool_t part0_valid) noexcept
    {
        part0_valid_ = part0_valid;
    }
    /**
     * @brief      Gets the part 0 valid.
     *
     * @return     The part 0 valid.
     */
    inline bool_t GetPart0Valid() const noexcept
    {
        return part0_valid_;
    }
    /**
     * @brief      Sets the part 1 valid.
     *
     * @param[in]  part1_valid  The part 1 valid
     */
    inline void SetPart1Valid(bool_t part1_valid) noexcept
    {
        part1_valid_ = part1_valid;
    }
    /**
     * @brief      Gets the part 1 valid.
     *
     * @return     The part 1 valid.
     */
    inline bool_t GetPart1Valid() const noexcept
    {
        return part1_valid_;
    }
    /**
     * @brief      Sets the part 2 valid.
     *
     * @param[in]  part2_valid  The part 2 valid
     */
    inline void SetPart2Valid(bool_t part2_valid) noexcept
    {
        part2_valid_ = part2_valid;
    }
    /**
     * @brief      Gets the part 2 valid.
     *
     * @return     The part 2 valid.
     */
    inline bool_t GetPart2Valid() const noexcept
    {
        return part2_valid_;
    }
    /**
     * @brief      Determines if valid.
     *
     * @return     True if valid, False otherwise.
     */
    inline bool_t IsAllPartsValid() const noexcept
    {
        return part0_valid_ && part1_valid_ && part2_valid_;
    }

private:
    /* data timestamp */
    holo::common::Timestamp timestamp_;  //! timestamp
    /* data members */
    float32_t c0_;           //!  0|12@1+ (0.01,-20.48) [-20.48|20.47] "m"
    float32_t c1_;           //! 12|10@1+ (0.0009765625,-0.357) [-0.357|0.357] "rad"
    float32_t c2_;           //! 32|16@1+ (0.000001,-0.032768) [-0.032768|0.032767] "1/m"
    float32_t c3_;           //!  0|16@1+ (0.000000004,-0.000131072) [-0.000131072|0.000131068] "1/m2"
    float32_t range_start_;  //! 40|8@1+ (0.5,0) [0|63.5] "m"
    float32_t range_end_;    //! 22|10@1+ (0.5,0) [0|150] "m"
    float32_t width_;        //! 33|7@1+ (0.01,0) [0|0.8] "m"
    float32_t tlc_;          //! 24|8@1+ (0.01,0) [0|2] "sec"
    uint8_t   location_;     //! 24|2@1+ (1,0) [0|3] "ENUM" 0:Left, 1:Right, 2:Next Left, 3:Next Right
    uint8_t   type_;         //! 26|4@1+ (1,0) [0|6] "ENUM"
    uint8_t   color_;        //! 16|2@1+ (1,0) [0|3] "ENUM"
    uint8_t   quality_;      //! 30|2@1+ (1,0) [0|3] "ENUM"
    bool_t    crossing_;     //! 32|1@1+ (1,0) [0|1] "bool"
    bool_t    part0_valid_;  //! part 0 valid indicator
    bool_t    part1_valid_;  //! part 1 valid indicator
    bool_t    part2_valid_;  //! part 2 valid indicator
    /* const values */
    static const holo::common::BoundaryStyle ktype_remap_table_[16];
    static const holo::common::BoundaryColor kcolor_remap_table_[4];
    static const float32_t                   kquality_remap_table_[4];
};

}  // namespace mobileye
}  // namespace sensors
}  // namespace holo
#endif
