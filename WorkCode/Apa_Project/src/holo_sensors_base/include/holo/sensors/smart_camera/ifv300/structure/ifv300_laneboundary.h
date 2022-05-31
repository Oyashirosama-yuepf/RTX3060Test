/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ifv300_laneboundary.h
 * @brief A class to describe delphi ifv300 laneboundary
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2019/12/24
 */

#ifndef HOLO_SENSORS_COMMON_SMART_CAMERA_IFV300_LANEBOUNDARY_H_
#define HOLO_SENSORS_COMMON_SMART_CAMERA_IFV300_LANEBOUNDARY_H_

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
namespace ifv300
{
using HoloLaneBoundaryType = holo::common::LaneBoundary<holo::numerics::Polynomial<float32_t, 3>>;

static const uint32_t  IFV300_POLYFIT_POINTS_NUM      = 10U;
static const float32_t IFV300_LANEBOUNDARY_LENGTH_MIN = 1.0f;

class Ifv300LaneBoundary
{
public:
    /**
     * @brief Default constructor.
     */
    Ifv300LaneBoundary() noexcept
      : timestamp_()
      , a0_(0.0f)
      , a1_(0.0f)
      , a2_(0.0f)
      , a3_(0.0f)
      , range_(0.0f)
      , type_(0)
      , color_(0)
      , quality_(0)
      , valid_(false)
    {
    }
    /**
     * @brief Copy constructor
     *
     * @param other The other Ifv300LaneBoundary.
     */
    Ifv300LaneBoundary(const Ifv300LaneBoundary& other) noexcept
      : timestamp_(other.timestamp_)
      , a0_(other.a0_)
      , a1_(other.a1_)
      , a2_(other.a2_)
      , a3_(other.a3_)
      , range_(other.range_)
      , type_(other.type_)
      , color_(other.color_)
      , quality_(other.quality_)
      , valid_(other.valid_)
    {
    }
    /**
     * @brief Copy assign operator
     *
     * @param other The other Ifv300LaneBoundary.
     *
     * @return Reference to this laneboundary.
     */
    Ifv300LaneBoundary& operator=(const Ifv300LaneBoundary& other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }
        timestamp_ = other.timestamp_;
        a0_        = other.a0_;
        a1_        = other.a1_;
        a2_        = other.a2_;
        a3_        = other.a3_;
        range_     = other.range_;
        type_      = other.type_;
        color_     = other.color_;
        quality_   = other.quality_;
        valid_     = other.valid_;
        return *this;
    }
    /**
     * @brief      Convert Ifv300LaneBoundary to HoloLaneBoundary with transform
     *
     * @param      output            the HoloLaneBoundary
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
     * @brief      Sets a0.
     *
     * @param[in]  a0    The new value
     */
    inline void SetA0(float32_t a0) noexcept
    {
        a0_ = a0;
    }
    /**
     * @brief      Gets a0.
     *
     * @return     a0.
     */
    inline float32_t GetA0() const noexcept
    {
        return a0_;
    }
    /**
     * @brief      Sets a1.
     *
     * @param[in]  a1    The new value
     */
    inline void SetA1(float32_t a1) noexcept
    {
        a1_ = a1;
    }
    /**
     * @brief      Gets a1.
     *
     * @return     a1.
     */
    inline float32_t GetA1() const noexcept
    {
        return a1_;
    }
    /**
     * @brief      Sets a2.
     *
     * @param[in]  a2    The new value
     */
    inline void SetA2(float32_t a2) noexcept
    {
        a2_ = a2;
    }
    /**
     * @brief      Gets a 2.
     *
     * @return     a2.
     */
    inline float32_t GetA2() const noexcept
    {
        return a2_;
    }
    /**
     * @brief      Sets a3.
     *
     * @param[in]  a3    The new value
     */
    inline void SetA3(float32_t a3) noexcept
    {
        a3_ = a3;
    }
    /**
     * @brief      Gets a3.
     *
     * @return     a3.
     */
    inline float32_t GetA3() const noexcept
    {
        return a3_;
    }
    /**
     * @brief      Sets the range.
     *
     * @param[in]  range  The range
     */
    inline void SetRange(float32_t range) noexcept
    {
        range_ = range;
    }
    /**
     * @brief      Gets the range.
     *
     * @return     The range.
     */
    inline float32_t GetRange() const noexcept
    {
        return range_;
    }
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
     * @brief      Sets the valid.
     *
     * @param[in]  valid  The valid
     */
    inline void SetValid(bool_t valid) noexcept
    {
        valid_ = valid;
    }
    /**
     * @brief      Gets the valid.
     *
     * @return     The valid.
     */
    inline bool_t GetValid() const noexcept
    {
        return valid_;
    }

private:
    /* data timestamp */
    holo::common::Timestamp timestamp_;  //! timestamp
    /* data members */
    float32_t a0_;       //! c0
    float32_t a1_;       //! c1
    float32_t a2_;       //! c2
    float32_t a3_;       //! c3
    float32_t range_;    //! range
    uint8_t   type_;     //! type
    uint8_t   color_;    //! mark color
    uint8_t   quality_;  //! mark quality
    /* valid */
    bool_t valid_;  //! valid indicator
    /* const values */
    static const holo::common::BoundaryStyle ktype_remap_table_[16];
    static const holo::common::BoundaryColor kcolor_remap_table_[4];
    static const float32_t                   kquality_remap_table_[4];
    static const float32_t                   kboundary_width_;
};

}  // namespace ifv300
}  // namespace sensors
}  // namespace holo
#endif
