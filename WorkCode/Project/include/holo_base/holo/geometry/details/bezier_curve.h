/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file bezier_curve.h
 * @brief This header file defines algorithms related to bezier curve.
 * @author ZhangJiannan(zhangjiannan@holomatic.com)
 * @date 2020-05-18
 */

#ifndef HOLO_GEOMETRY_DETAILS_BEZIER_CURVE_H_
#define HOLO_GEOMETRY_DETAILS_BEZIER_CURVE_H_

#include <holo/core/epsilon.h>
#include <holo/geometry/details/curve_base.h>
#include <holo/numerics/utility.h>
#include "utility.h"

namespace holo
{
namespace geometry
{
namespace details
{
/**
 * @addtogroup geometry
 * @{
 */

/**
 * @brief Bezier curve algorithm
 *
 * @tparam Point Point type
 * @tparam SIZE Maximum knot size
 * @tparam DEGREE Degree value
 */
template <typename Point, size_t SIZE, size_t DEGREE = 3U>
class CurveBezier;

/**
 * @brief Linear bezier curve algorithm
 *
 * @tparam Point PointType
 * @tparam SIZE Max knot size.
 */
template <typename Point, size_t SIZE>
class CurveBezier<Point, SIZE, 1U>
{
public:
    using PointType  = Point;
    using ScalarType = typename PointType::ScalarType;
    using TagType    = CurveParametricTag;

    static size_t const SIZE_VALUE   = SIZE;
    static size_t const DEGREE_VALUE = 1U;

    /**
     * @brief Algorithm related state.
     */
    struct State
    {
        holo::container::Vector<ScalarType, SIZE> distances;  ///< distance to start point of each knot.
    };

    using StateType = State;

    /**
     * @brief Update state of a curve
     *
     * @param curve The basic curve object.
     * @param state Curve state
     *
     * @return true if update state succeeded.
     */
    bool_t Update(CurveBaseT<PointType, SIZE_VALUE> const& curve, StateType& state)
    {
        if (curve.size() < 2U)
        {
            throw holo::exception::BadKnotNumberException();
        }
        state.distances.clear();
        size_t idx = 0U;
        state.distances.push_back(static_cast<ScalarType>(0));

        while (idx < curve.size() - 1U)
        {
            state.distances.push_back(state.distances[idx] + curve[idx + 1U].Dist(curve[idx]));
            ++idx;
        }
        return true;
    }

    /**
     * @brief Get arc length of idx-th knot
     *
     * @param curve The basic curve object.
     * @param state The curve state.
     * @param idx knot index
     *
     * @return Arc length of idx-th knot
     */
    ScalarType GetLength(CurveBaseT<PointType, SIZE_VALUE> const& curve, StateType const& state, size_t idx) const
    {
        if (!(idx < curve.size()))
        {
            throw holo::exception::OutOfRangeException("");
        }
        return state.distances[idx];
    }

    /**
     * @brief Get D-th derivative of curve at given arc length.
     *
     * @tparam D Derivative order
     * @param curve The basic curve object.
     * @param state The curve state.
     * @param len Length of arc.
     *
     * @return D-th derivative of the curve at arc length
     */
    template <size_t D>
    PointType GetDerivativeByArcLength(CurveBaseT<PointType, SIZE_VALUE> const& curve, StateType const& state,
                                       ScalarType len)
    {
        size_t     idx         = utility::SearchSection(state.distances, len, std::less_equal<ScalarType>());
        ScalarType segment_len = state.distances[idx + 1] - state.distances[idx];
        ScalarType t           = 0;
        if (segment_len > ScalarEqualT<ScalarType>().GetEpsilonValue())
        {
            t = (len - state.distances[idx]) / segment_len;
        }
        return getDerivative<D>(curve[idx], curve[idx + 1], t);
    }

    /**
     * @brief Get D-th derivative of curve at sequence of arc lengths defined in range [first, last)
     *
     * @tparam D Derivative order
     * @tparam InputIt iterator with value_type of ScalarType.
     * @tparam OutputIt iterator with value type of PointType.
     * @param curve The basic curve object.
     * @param state The curve state.
     * @param first Start of input range.
     * @param last End of input range
     * @param out Iterator to sampled curve points.
     */
    template <size_t D, typename InputIt, typename OutputIt>
    void GetDerivativeByArcLength(CurveBaseT<PointType, SIZE_VALUE> const& curve, StateType const& state, InputIt first,
                                  InputIt last, OutputIt out)
    {
        if (first == last)
        {
            return;
        }

        ScalarType segment_len = 0;
        ScalarType t           = 0;

        size_t idx  = utility::SearchSection(state.distances, *first, std::less_equal<ScalarType>());
        segment_len = state.distances[idx + 1] - state.distances[idx];
        if (segment_len > ScalarEqualT<ScalarType>().GetEpsilonValue())
        {
            t = (*first - state.distances[idx]) / segment_len;
        }
        *out = getDerivative<D>(curve[idx], curve[idx + 1], t);
        ++out;
        ++first;

        while (first != last)
        {
            idx         = utility::SearchSectionWithHint(idx, state.distances, *first, std::less_equal<ScalarType>());
            t           = 0;
            segment_len = state.distances[idx + 1] - state.distances[idx];
            if (segment_len > ScalarEqualT<ScalarType>().GetEpsilonValue())
            {
                t = (*first - state.distances[idx]) / segment_len;
            }
            *out = getDerivative<D>(curve[idx], curve[idx + 1], t);
            ++out;
            ++first;
        }
    }

protected:
    /**
     * @brief Get D-th derivative value at given uniformed parameter t.
     *
     * @tparam D Derivative order
     * @param pt1 Start knot
     * @param pt2 End knot
     * @param t Uniformed parameter.
     *
     * @return D-th derivative value.
     */
    template <size_t D, typename std::enable_if<D == 0>::type* = nullptr>
    PointType getDerivative(PointType const& pt1, PointType const& pt2, ScalarType t)
    {
        return (1 - t) * pt1 + t * pt2;
    }

    /**
     * @brief Get D-th derivative value at given uniformed parameter t.
     *
     * @tparam D Derivative order
     * @param pt1 Start knot
     * @param pt2 End knot
     *
     * @return D-th derivative value.
     */
    template <size_t D, typename std::enable_if<D == 1>::type* = nullptr>
    PointType getDerivative(PointType const& pt1, PointType const& pt2, ScalarType)
    {
        return -pt1 + pt2;
    }

    /**
     * @brief Get D-th derivative value at given uniformed parameter t.
     *
     * @tparam D Derivative order
     *
     * @return D-th derivative value.
     */
    template <size_t D, typename std::enable_if<(D > 1)>::type* = nullptr>
    PointType getDerivative(PointType const&, PointType const&, ScalarType)
    {
        return PointType{};
    }
};

/**
 * @brief Piecewise cubic bezier curve algorithm.
 *
 * @details Piecewise cubic bezier curve will generate a smooth spline through a set of prescribed points.@n
 * The cubic bezier curve is given by
 * @f{equation}{
 * \bm{B}(t)=(1-t)^3\bm{P}_0+3(1-t)^2t\bm{P}_1+3(1-t)t^2\bm{P}_2+t^3\bm{P}_3
 * @f}
 * The @f$\bm{P}_0@f$ and @f$\bm{P}_3@f$ correspond to the end points. The other two points are control points that
 * determine the shape of the curve. To ensure the spline is smooth, we need the first and second derivatives to be
 * continuous across the spline boundary.@n
 *
 * The first derivative is given by:
 * @f{equation}{
 * \bm{B}^{'}(t)=-3(1-t)^2\bm{P}_0+3(1-4t+3t^2)\bm{P}_1+3(2t-3t^2)\bm{P}_2+3t^2\bm{P}_3
 * @f}
 * At the left boundary of i-th segment:
 * @f{equation}{
 * \bm{B}_{i}^{'}(0)=B_{i-1}^{'}(1)
 * @f}
 * Then
 * @f{equation}{
 * -3\bm{P}_{0,i}+3\bm{P}_{1,i}=-3\bm{P}_{2,i-1}+3\bm{P}_{3,i-1}
 * @f}
 * Denote @f$\bm{K}_i@f$ the i-th prescribed point(knot point). Since the curve is continuous, @f$
 * \bm{P}_{0,i}=\bm{P}_{3,i-1}=\bm{K}_{i}@f$
 *
 * @f{equation}{
 * 2\bm{K}_{i}=\bm{P}_{1,i}+\bm{P}_{2,i-1}
 * @f}
 *
 * The second derivative is given by:
 * @f{equation}{
 * \bm{B}^{''}(t)=6(1-t)\bm{P}_0+3(-4+6t)\bm{P}_1+3(2-6t)\bm{P}_2+6t\bm{P}_3
 * @f}
 * At the left boundary of i-th segment
 * @f{equation}{
 * \bm{B}^{''}_{i}(0)=\bm{B}^{''}_{i-1}(1)\label{1}
 * @f}
 * Then
 * @f{equation}{
 * 6\bm{P}_{0,i}-12\bm{P}_{1,i}+6\bm{P}_{2,i}=6\bm{P}_{1,i-1}-12\bm{P}_{2,i-1}+6\bm{P}_{3,i-1}
 * @f}
 * Simplify the last equation:
 * @f{equation}{
 * -2\bm{P}_{1,i}+\bm{P}_{2,i}=\bm{P}_{1,i-1}-2\bm{P}_{2,i-1}
 * @f}
 * Consider there are @f$n+1@f$ knots that define @f$n@f$ segments. Each segment is presented by a cubic bezier curve.
 * There are @f$ 2n @f$ unknowns control points while only @f$ 2n-2 @f$ equations are defined from (5) and (9). To close
 * the system, two more constraits need to be specified.
 *
 * The two constrains are specified by two curve end conditions:
 * - Start condition
 *   1. Value of first derivative at start point.
 *   2. Value of second derivative at start point.
 * - End condition
 *   1. Value of first derivative at end point.
 *   2. Value of second derivative at end point.
 *
 * By default both ends of the curve will be left free.
 * @f{eqnarray}{
 * B_0^{''}(0)=0\\
 * B_{n-1}^{''}(1)=0
 * @f}
 * The default condition implies the spline is linear when it passes through the end points.
 *
 * Substituting (5) into (9) gives:
 * @f{equation}{
 *     \bm{P}_{1,i-1}+4\bm{P}_{1,i} + \bm{P}_{1,i+1}=4\bm{K}_{i}+2{K}_{i+1} \quad i=1 \dots n-1
 * @f}
 *
 * For start condition:
 * - Given first derivative of start condition @f$ \bm{B}_0^{'} @f$. Equation (2) gives
 * @f{eqnarray}{
 * \bm{B}_0^{'}=-3\bm{P}_{0,0}+3\bm{P}_{1,0} \\
 * 3\bm{P}_{1,0}=\bm{B}_0^{'}+3\bm{K}_0
 * @f}
 * - Given second derivative of start condition @f$ \bm{B}_0^{''} @f$. Equation (6) gives
 * @f{eqnarray}{
 * \bm{B}_0^{''}=6\bm{P}_{0,0}-12\bm{P}_{1,0}+6\bm{P}_{2,0}
 * @f}
 * Substitute (5) into (15) gives
 * @f{eqnarray}{
 * 12\bm{P}_{1,0}+6\bm{P}_{2,0}=6\bm{K}_0+12\bm{K}_1-\bm{B}_0^{''}
 * @f}
 *
 * For end condition:
 * - Given first derivative of end condition @f$ \bm{B}_n^{'} @f$. Equation (2) gives
 * @f{eqnarray}{
 * \bm{B}_n^{'}=-3\bm{P}_{2,n-1}+3\bm{P}_{3,n-1} \\
 * 3\bm{P}_{1,n}=\bm{B}_n^{'}+3\bm{K}_n
 * @f}
 * - Given second derivative of end condition @f$ \bm{B}_n^{''} @f$. Equation (6) gives
 * @f{eqnarray}{
 * \bm{B}_n^{''}=6\bm{P}_{1,n-1}-12\bm{P}_{2,n-1}+6\bm{P}_{3,n-1}
 * @f}
 * Substitute (5) into (19) gives
 * @f{eqnarray}{
 * 6\bm{P}_{1,n-1}+12\bm{P}_{1,n}=18\bm{K}_n+\bm{B}_n^{''}
 * @f}
 *
 * Equation (12) and start/end conditions can be written in matrix form:
 * @f{eqnarray}{
 * \begin{bmatrix}
 *   s_0    & s_1    & 0      & \cdots  & 0       & 0       & 0       \\
 *   1      & 4      & 1      & \cdots  & 0       & 0       & 0       \\
 *   0      & 1      & 4      & \cdots  & 0       & 0       & 0       \\
 *   \vdots & \vdots & \vdots & \ddots  & \vdots  & \vdots  & \vdots  \\
 *   0      & 0      & 0      & \cdots  & 4       & 1       & 0       \\
 *   0      & 0      & 0      & \cdots  & 1       & 4       & 1       \\
 *   0      & 0      & 0      & \cdots  & 0       & e_0     & e_1     \\
 * \end{bmatrix} \
 * \begin{bmatrix}
 *     \bm{P}_{1,0} \\ \bm{P}_{1,1} \\ \bm{P}_{1,2} \\ \vdots \\ \bm{P}_{1,n-3} \\ \bm{P}_{1,n-2} \\ \bm{P}_{1,n} \\
 * \end{bmatrix} \
 * = \
 * \begin{bmatrix}
 *     d_0 \\
 *     4\bm{K}_1 + 2\bm{K}_2 \\
 *     4\bm{K}_2 + 2\bm{K}_3 \\
 *     \vdots \\
 *     4\bm{K}_{n-2} + 2\bm{K}_{n-1} \\
 *     4\bm{K}_{n-1} + 2\bm{K}_{n} \\
 *     d_n \\
 * \end{bmatrix}
 * @f}
 *
 * @f$s_0,s_1,e_0,e_1,d_0,d_n@f$ are start/end conditions given by equation  (14)(16)(18)(20)
 *
 *
 * This is a tri-diagonal matrix which can be solved by
 * [Gaussian elimination](https://en.wikipedia.org/wiki/Gaussian_elimination) or
 * [Thomas algorithm](https://en.wikipedia.org/wiki/Tridiagonal_matrix_algorithm)
 */
template <typename Point, size_t SIZE>
class CurveBezier<Point, SIZE, 3U>
{
public:
    using PointType  = Point;
    using ScalarType = typename PointType::ScalarType;
    using TagType    = CurveParametricTag;

    static size_t const SIZE_VALUE   = SIZE;
    static size_t const DEGREE_VALUE = 3U;

    /**
     * @brief Algorithm related state.
     */
    struct State
    {
        holo::container::Vector<PointType, SIZE * 2U> control_points;
        holo::container::Vector<ScalarType, SIZE>     distances;
    };

    using StateType = State;

    /**
     * @brief Update state of a curve
     *
     * @param curve The basic curve object.
     * @param state Curve state
     *
     * @return true if update state succeeded.
     */
    bool_t Update(CurveBaseT<PointType, SIZE_VALUE> const& curve, StateType& state)
    {
        size_t knots = curve.size();
        size_t n     = knots - 1U;

        if (knots < 2U)
        {
            throw holo::exception::BadKnotNumberException();
        }

        ScalarType b[SIZE_VALUE];
        PointType  d[SIZE_VALUE];
        ScalarType c0;
        ScalarType an;

        // Initialize matrix
        // Items in row [1, n - 2]
        ScalarType const ai = static_cast<ScalarType>(1);
        ScalarType const bi = static_cast<ScalarType>(4);
        ScalarType const ci = static_cast<ScalarType>(1);

        for (size_t i = 1U; i < n; ++i)
        {
            d[i] = 4 * curve[i] + 2 * curve[i + 1U];
        }

        // Set start conditions
        if (curve.GetStartType() == CurveBaseT<PointType>::ConditionType::FIRST_DERIVATIVE)
        {
            b[0U] = static_cast<ScalarType>(3);
            c0    = static_cast<ScalarType>(0);
            d[0U] = 3 * curve[0] + curve.GetStartCondition();
        }
        else if (curve.GetStartType() == CurveBaseT<PointType>::ConditionType::SECOND_DERIVATIVE)
        {
            b[0U] = static_cast<ScalarType>(12);
            c0    = static_cast<ScalarType>(6);
            d[0U] = 6 * curve[0] + 12 * curve[1] + -curve.GetStartCondition();
        }
        else
        {
            b[0U] = static_cast<ScalarType>(2);
            c0    = static_cast<ScalarType>(1);
            d[0U] = curve[0U] + 2 * curve[1U];
        }

        // Set end conditions
        if (curve.GetEndType() == CurveBaseT<PointType>::ConditionType::FIRST_DERIVATIVE)
        {
            an   = static_cast<ScalarType>(0);
            b[n] = static_cast<ScalarType>(3);
            d[n] = 3 * curve[n] + curve.GetEndCondition();
        }
        else if (curve.GetEndType() == CurveBaseT<PointType>::ConditionType::SECOND_DERIVATIVE)
        {
            an   = static_cast<ScalarType>(6);
            b[n] = static_cast<ScalarType>(12);
            d[n] = 18 * curve[n] + curve.GetEndCondition();
        }
        else
        {
            an   = static_cast<ScalarType>(1);
            b[n] = static_cast<ScalarType>(2);
            d[n] = 3 * curve[n];
        }

        // Gaussian elimination
        if (n == 1)
        {
            b[1U] = b[1U] - c0 * an / b[0U];
            d[1U] = d[1U] + -d[0U] * an / b[0U];
        }
        else
        {
            // start condition
            b[1U] = bi - c0 * ai / b[0U];
            d[1U] = d[1U] + -d[0U] * ai / b[0U];

            // rows in the middle
            for (size_t i = 2U; i < n; ++i)
            {
                b[i] = bi - ci * ai / b[i - 1U];
                d[i] = d[i] + -d[i - 1] * ai / b[i - 1U];
            }

            // end condition
            b[n] = b[n] - ci * an / b[n - 1U];
            d[n] = d[n] + -d[n - 1] * an / b[n - 1U];
        }

        // Backsubstitution
        state.control_points.resize(2 * n + 1);  // The last element is used to store cp_{1,n}
        state.control_points[2 * n] = d[n] / b[n];
        for (size_t i = n - 1U; i > 0U; --i)
        {
            state.control_points[2 * i]     = (d[i] + -ci * state.control_points[2 * (i + 1)]) / b[i];
            state.control_points[2 * i + 1] = 2 * curve[i + 1] + -state.control_points[2 * (i + 1)];
        }
        state.control_points[0U] = (d[0] + -c0 * state.control_points[2U]) / b[0U];
        state.control_points[1U] = 2 * curve[1] + -state.control_points[2U];
        state.control_points.pop_back();

        state.distances.clear();
        state.distances.push_back(0);
        for (size_t i = 0U; i < n; ++i)
        {
            state.distances.push_back(state.distances[i] + segmentLength(curve[i], state.control_points[i * 2U],
                                                                         state.control_points[i * 2U + 1U],
                                                                         curve[i + 1U]));
        }
        return true;
    }

    /**
     * @brief Get arc length of idx-th knot
     *
     * @param curve The basic curve object.
     * @param state The curve state.
     * @param idx knot index
     *
     * @return Arc length of idx-th knot
     */
    ScalarType GetLength(CurveBaseT<PointType, SIZE_VALUE> const& curve, StateType const& state, size_t idx) const
    {
        if (!(idx < curve.size()))
        {
            throw holo::exception::OutOfRangeException("");
        }
        return state.distances[idx];
    }

    /**
     * @brief Get D-th derivative of curve at given arc length.
     *
     * @tparam D Derivative order
     * @param curve The basic curve object.
     * @param state The curve state.
     * @param len Length of arc.
     *
     * @return D-th derivative of the curve at arc length
     */
    template <size_t D>
    PointType GetDerivativeByArcLength(CurveBaseT<PointType, SIZE_VALUE> const& curve, StateType const& state,
                                       ScalarType len)
    {
        size_t     idx         = utility::SearchSection(state.distances, len, std::less_equal<ScalarType>());
        ScalarType segment_len = state.distances[idx + 1U] - state.distances[idx];
        ScalarType t           = 0;
        if (segment_len > ScalarEqualT<ScalarType>().GetEpsilonValue())
        {
            t = (len - state.distances[idx]) / segment_len;
        }
        return getDerivative<D>(curve[idx], state.control_points[idx * 2U], state.control_points[idx * 2U + 1U],
                                curve[idx + 1U], t);
    }

    /**
     * @brief Get D-th derivative of curve at sequence of arc lengths defined in range [first, last)
     *
     * @tparam D Derivative order
     * @tparam InputIt iterator with value_type of ScalarType.
     * @tparam OutputIt iterator with value type of PointType.
     * @param curve The basic curve object.
     * @param state The curve state.
     * @param first Start of input range.
     * @param last End of input range
     * @param out Iterator to sampled curve points.
     */
    template <size_t D, typename InputIt, typename OutputIt>
    void GetDerivativeByArcLength(CurveBaseT<PointType, SIZE_VALUE> const& curve, StateType const& state, InputIt first,
                                  InputIt last, OutputIt out)
    {
        if (first == last)
        {
            return;
        }

        ScalarType segment_len = 0;
        ScalarType t           = 0;

        size_t idx  = utility::SearchSection(state.distances, *first, std::less_equal<ScalarType>());
        segment_len = state.distances[idx + 1] - state.distances[idx];
        if (segment_len > ScalarEqualT<ScalarType>().GetEpsilonValue())
        {
            t = (*first - state.distances[idx]) / segment_len;
        }
        *out = getDerivative<D>(curve[idx], state.control_points[idx * 2U], state.control_points[idx * 2U + 1U],
                                curve[idx + 1U], t);
        ++out;
        ++first;

        while (first != last)
        {
            idx         = utility::SearchSectionWithHint(idx, state.distances, *first, std::less_equal<ScalarType>());
            t           = 0;
            segment_len = state.distances[idx + 1U] - state.distances[idx];
            if (segment_len > ScalarEqualT<ScalarType>().GetEpsilonValue())
            {
                t = (*first - state.distances[idx]) / segment_len;
            }
            *out = getDerivative<D>(curve[idx], state.control_points[idx * 2U], state.control_points[idx * 2U + 1U],
                                    curve[idx + 1U], t);
            ++out;
            ++first;
        }
    }

private:
    /**
     * @brief Get D-th derivative value at given uniformed parameter t.
     *
     * @tparam D Derivative order
     * @param pt1 Start knot
     * @param cp1 Control point1
     * @param cp2 Control point2
     * @param pt2 End knot
     * @param t Uniformed parameter.
     *
     * @return D-th derivative value.
     */
    template <size_t D>
    PointType getDerivative(PointType const& pt1, PointType const& cp1, PointType const& cp2, PointType const& pt2,
                            ScalarType t)
    {
        return holo::numerics::BernsteinPolynomial<ScalarType, 0U, 3U>::template CalculateDerivative<D>(t) * pt1 +
               holo::numerics::BernsteinPolynomial<ScalarType, 1U, 3U>::template CalculateDerivative<D>(t) * cp1 +
               holo::numerics::BernsteinPolynomial<ScalarType, 2U, 3U>::template CalculateDerivative<D>(t) * cp2 +
               holo::numerics::BernsteinPolynomial<ScalarType, 3U, 3U>::template CalculateDerivative<D>(t) * pt2;
    }

    /**
     * @brief Calculate length of a bezier curve segment
     *
     * @param pt1 Start knot
     * @param cp1 Control point1
     * @param cp2 Control point2
     * @param pt2 End knot
     * @param segments sample number.
     *
     * @return Approximate length of this bezier curve segment
     */
    ScalarType segmentLength(PointType const& pt1, PointType const& cp1, PointType const& cp2, PointType const& pt2,
                             size_t segments = 16U) const noexcept
    {
        PointType  sample_pt = pt1;
        PointType  target_pt;
        ScalarType len = 0;
        for (size_t i = 1U; i < segments; ++i)
        {
            ScalarType t = static_cast<ScalarType>((1.0 / segments) * i);
            target_pt    = (1 - t) * (1 - t) * (1 - t) * pt1 + 3 * (1 - t) * (1 - t) * t * cp1 +
                        3 * (1 - t) * t * t * cp2 + t * t * t * pt2;
            len += sample_pt.Dist(target_pt);
            sample_pt = target_pt;
        }
        len += sample_pt.Dist(pt2);
        return len;
    }
};

/**
 * @}
 */

}  // namespace details
}  // namespace geometry
}  // namespace holo
#endif