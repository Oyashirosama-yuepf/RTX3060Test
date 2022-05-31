/*!
 *  \brief
 *  \author panhu (panhu@holomatic.com)
 *  \date 2019-04-15
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _VEC2Y_H_
#define _VEC2Y_H_

#include <holo/core/types.h>

namespace holo
{
namespace planning
{
constexpr float64_t kMathEpsilon = 1e-10;
/**
 * @class Vec2d
 *
 * @brief Implements a class of 2-dimensional vectors.
 */
class Vec2d
{
public:
    /**
     * @brief Constructor which takes x- and y-coordinates.
     */
    constexpr Vec2d(const float64_t x, const float64_t y) noexcept : x_(x), y_(y)
    {
    }

    /**
     * @brief Constructor returning the zero vector.
     */
    constexpr Vec2d() noexcept : Vec2d(0, 0)
    {
    }

    /**
     * @brief Getter for x component
     */
    float64_t x() const
    {
        return x_;
    }

    /**
     * @brief Setter for x component
     */
    void x(float64_t x)
    {
        x_ = x;
    }

    /**
     * @brief Getter for y component
     */
    float64_t y() const
    {
        return y_;
    }

    /**
     * @brief Setter for y component
     */
    void y(float64_t y)
    {
        y_ = y;
    }

    /**
     * @brief Gets the length of the vector
     */
    float64_t Length() const;

    /**
     * @brief Gets the angle between the vector and the positive x semi-axis
     */
    float64_t Angle() const;

    /**
     * @brief Returns the "cross" product between these two Vec2d (non-standard).
     */
    float64_t CrossProd(const Vec2d& other) const;

    /**
     * @brief Subtracts two Vec2d
     */
    Vec2d operator-(const Vec2d& other) const;

protected:
    float64_t x_ = 0.0;
    float64_t y_ = 0.0;
};

}  // namespace planning
}  // namespace holo
#endif