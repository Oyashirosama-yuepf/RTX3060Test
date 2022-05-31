/*
 * @Author: zhouchengwei
 */
/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file boundary_point2d.h
 * @brief This header file defines special point struct for freespace boundary.
 * @author zhouchengwei (zhouchengwei@holomatic.com)
 * @date "2021-04-26"
 */

#ifndef HOLO_PERCEPTION_COMMON_FREESPACE_BOUNDARY_POINT2D_
#define HOLO_PERCEPTION_COMMON_FREESPACE_BOUNDARY_POINT2D_

#include "holo/common/classification.h"  //< >

namespace holo
{
namespace perception
{
/**
 * @addtogroup common
 *
 * @{
 */

/**
 * @brief define boundary_point2d
 *
 * @note
 * @tparam T data type
 */
template <typename T>
class Boundary_Point2D
{
public:
    using Scalar = T;
    /**
     * @brief Default Constructor
     *
     */
    Boundary_Point2D() noexcept
      : x_(static_cast<Scalar>(0.0))
      , y_(static_cast<Scalar>(0.0))
      , confidence_(static_cast<holo::float32_t>(0.0))
      , classification_(Classification(Classification::MainType::UNKNOWN, Classification::SubType::UNKNOWN))
    {
    }
    /**
     * @brief Construct a new Boundary_Point2D
     *
     * @param x
     * @param y
     * @param confidence, the confidence of boundary
     * @param classification, classification of boundary
     */
    Boundary_Point2D(Scalar x, Scalar y, holo::float32_t confidence = static_cast<holo::float32_t>(0.0),
                     Classification classification = Classification(Classification::MainType::UNKNOWN,
                                                                    Classification::SubType::UNKNOWN))
      : x_(x), y_(y), confidence_(confidence), classification_(classification)
    {
    }

    ~Boundary_Point2D()
    {
    }

    void SetX(Scalar const x) noexcept
    {
        x_ = x;
    }

    void SetY(Scalar const y) noexcept
    {
        y_ = y;
    }

    void SetConfidence(float32_t const confidence) noexcept
    {
        confidence_ = confidence;
    }

    void SetClassification(Classification const classification) noexcept
    {
        classification_ = classification;
    }

    Scalar GetX() const noexcept
    {
        return x_;
    }

    Scalar GetY() const noexcept
    {
        return y_;
    }

    float32_t GetConfidence() const noexcept
    {
        return confidence_;
    }

    Classification GetClassification() const noexcept
    {
        return classification_;
    }

    /**
     * @brief output stream
     *
     * @param os std::ostream
     * @param in  Boundary_Point2D
     * @return std::ostream&
     */
    friend std::ostream& operator<<(std::ostream& os, Boundary_Point2D const& in)
    {
        os << in.ToString();
        return os;
    }

    /**
     * @brief Convert to string for readable
     *
     * @return std::string
     */
    virtual std::string ToString() const
    {
        std::stringstream ss;
        ss << "Boundary point x= " << std::setiosflags(std::ios_base::fixed) << std::setprecision(2) << x_
           << ", y = " << y_ << ", confidence = " << confidence_ << ", classification = " << classification_.ToString()
           << std::endl;
        return ss.str();
    }

private:
    Scalar          x_;
    Scalar          y_;
    holo::float32_t confidence_;
    Classification  classification_;
};
}  // namespace perception
}  // namespace holo

#endif
