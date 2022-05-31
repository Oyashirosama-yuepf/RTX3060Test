/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file polynomial_curve.h
 * @brief This header file defines algorithms related to polynomial curve.
 * @author ZhangJiannan(zhangjiannan@holomatic.com)
 * @date 2020-05-18
 */

#ifndef HOLO_GEOMETRY_DETAILS_POLYNOMIAL_CURVE_H_
#define HOLO_GEOMETRY_DETAILS_POLYNOMIAL_CURVE_H_

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
 * @brief Algorithm for piecewise polynomial curve
 *
 * @tparam Point Point type
 * @tparam SIZE Maximum knot size
 * @tparam DEGREE Degree value
 */
template <typename Point, size_t SIZE, size_t DEGREE = 3U>
class CurvePolynomial;

/**
 * @brief  Piecewise linear polynomial curve algorithm
 *
 * @tparam Point Point type.
 * @tparam SIZE Max knot size.
 */
template <typename Point, size_t SIZE>
class CurvePolynomial<Point, SIZE, 1U>
{
public:
    using PointType  = Point;
    using ScalarType = typename PointType::ScalarType;
    using TagType    = CurveExplicitTag;

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
        state.distances.push_back(0);

        for (size_t idx = 0U; idx < curve.size() - 1U; ++idx)
        {
            state.distances.push_back(state.distances[idx] + curve[idx + 1U].Dist(curve[idx]));
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
        if (segment_len < ScalarEqualT<ScalarType>().GetEpsilonValue())
        {
            return curve[idx];
        }
        else
        {
            ScalarType t = (len - state.distances[idx]) / segment_len;
            return getDerivative<D>(curve[idx], curve[idx + 1U], t);
        }
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
        segment_len = state.distances[idx + 1U] - state.distances[idx];
        if (segment_len > ScalarEqualT<ScalarType>().GetEpsilonValue())
        {
            t = (*first - state.distances[idx]) / segment_len;
        }
        *out = getDerivative<D>(curve[idx], curve[idx + 1U], t);
        ++out;
        ++first;

        while (first != last)
        {
            idx         = utility::SearchSectionWithHint(idx, state.distances, *first, std::less_equal<ScalarType>());
            segment_len = state.distances[idx + 1U] - state.distances[idx];
            if (segment_len > ScalarEqualT<ScalarType>().GetEpsilonValue())
            {
                t = (*first - state.distances[idx]) / segment_len;
            }
            *out = getDerivative<D>(curve[idx], curve[idx + 1U], t);
            ++out;
            ++first;
        }
    }

    /**
     * @brief Get point on curve at given x coordinate
     *
     * @tparam D Derivative order
     * @param curve The explicit form curve object.
     * @param state The curve state.
     * @param x x coordinate.
     *
     * @return Point on curve
     */
    template <size_t D>
    PointType GetDerivativeByCoordinate(CurveBaseT<PointType, SIZE_VALUE> const& curve, StateType const&, ScalarType x)
    {
        size_t     idx         = utility::SearchSection(curve, x, pointCoordinateLessEqualCompare());
        ScalarType segment_len = curve[idx + 1][0U] - curve[idx][0U];
        ScalarType t           = 0;
        if (segment_len > ScalarEqualT<ScalarType>().GetEpsilonValue())
        {
            t = (x - curve[idx][0U]) / segment_len;
        }
        return getDerivative<D>(curve[idx], curve[idx + 1U], t);
    }

    /**
     * @brief Get points on curve at sequence of x coordinates defined in range [first, last)
     *
     * @tparam D Derivative order
     * @tparam InputIt iterator with value_type of ScalarType.
     * @tparam OutputIt iterator with value type of PointType.
     * @param curve The explicit form curve object.
     * @param state The curve state.
     * @param first Start of input range.
     * @param last End of input range
     * @param out Iterator to sampled curve points.
     */
    template <size_t D, typename InputIt, typename OutputIt>
    void GetDerivativeByCoordinate(CurveBaseT<PointType, SIZE_VALUE> const& curve, StateType const&, InputIt first,
                                   InputIt last, OutputIt out)
    {
        if (first == last)
        {
            return;
        }

        ScalarType segment_len = 0;
        ScalarType t           = 0;

        size_t idx  = utility::SearchSection(curve, *first, pointCoordinateLessEqualCompare());
        segment_len = curve[idx + 1U][0U] - curve[idx][0U];
        if (segment_len > ScalarEqualT<ScalarType>().GetEpsilonValue())
        {
            t = (*first - curve[idx][0U]) / segment_len;
        }
        *out = getDerivative<D>(curve[idx], curve[idx + 1U], t);
        ++out;
        ++first;

        while (first != last)
        {
            idx         = utility::SearchSectionWithHint(idx, curve, *first, pointCoordinateLessEqualCompare());
            t           = 0;
            segment_len = curve[idx + 1U][0U] - curve[idx][0U];
            if (segment_len > ScalarEqualT<ScalarType>().GetEpsilonValue())
            {
                t = (*first - curve[idx][0U]) / segment_len;
            }
            *out = getDerivative<D>(curve[idx], curve[idx + 1U], t);
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
    template <size_t D, typename std::enable_if<D == 0U>::type* = nullptr>
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
    template <size_t D, typename std::enable_if<D == 1U>::type* = nullptr>
    PointType getDerivative(PointType const& pt1, PointType const& pt2, ScalarType)
    {
        PointType tangent = -pt1 + pt2;
        return tangent / tangent[0U];
    }

    /**
     * @brief Get D-th derivative value at given uniformed parameter t.
     *
     * @tparam D Derivative order
     *
     * @return D-th derivative value.
     */
    template <size_t D, typename std::enable_if<(D > 1U)>::type* = nullptr>
    PointType getDerivative(PointType const&, PointType const&, ScalarType)
    {
        return PointType{};
    }

    /**
     * @brief Functor to compare between a point type and scalar type.
     */
    class pointCoordinateLessEqualCompare
    {
    public:
        bool_t operator()(ScalarType x, PointType const& pt) const noexcept
        {
            return x <= pt[0U];
        }

        bool_t operator()(PointType const& pt, ScalarType x) const noexcept
        {
            return pt[0U] <= x;
        }
    };
};

/**
 * @brief  Piecewise cubic polynomial curve algorithm
 *
 * @details Piecewise cubic polynomial curve will generate a smooth spline through a set of prescribed points. @n
 * The cubic polynomial curve is given by
 * @f{eqnarray*}{
 * \setcounter{equation}{1}
 * \bm{C}_i(x)=\left\{
 *   \begin{array}{ll}
 *     x = x & x \in [x_i, x_{i+1}] \\
 *     y = f_{i,y} = a_{i,y}(x-x_i)^3+b_{i,y}(x-x_i)^2+c_{i,y}(x-x_i)+d_{i,y} & x \in [x_i, x_{i+1}] \\
 *     z = f_{i,z} = a_{i,z}(x-x_i)^3+b_{i,z}(x-x_i)^2+c_{i,z}(x-x_i)+d_{i,z} & x \in [x_i, x_{i+1}] \\
 *     \cdots
 *   \end{array}
 * \right.
 * @f}
 *
 * Each dimenssion can be resolved seperately.
 *
 * Take @f$y=f_{i,y}@f$ for instance, the piecewise cubic polynomial curve is given by
 * @f{eqnarray}{
 * \bm{C}_i(x)=a_i(x-x_i)^3+b_i(x-x_i)^2+c_i(x-x_i)+d_i
 * @f}
 * where @f$x \in [x_i, x_{i+1}]@f$
 *
 * The first and second derivatives are given by
 * @f{eqnarray}{
 * C_i^{'}(x)&=&3a_i(x-x_i)^2+2b_i(x-x_i)+c_i \\
 * C_i^{''}(x)&=&6a_i(x-x_i)+2b_i
 * @f}
 *
 * The adjacent functions @f$C_{i-1}@f$ and @f$C_{i}@f$ where @f$i =1, \dots, n@f$ should meet at @f$(x_i, y_i)@f$.
 * @f{eqnarray}{
 * C_{i-1}(x_i)&=&C_i(x_i)=y_i \\
 * a_{i-1}h_{i-1}^3+b_{i-1}h_{i-1}^2+c_{i-1}h_{i-1}+d_{i-1}&=&d_i=y_i
 * @f}
 * where @f$h_{i-1}=x_i-x_{i-1}@f$ is width of (i-1)th segment.
 *
 * The first derivatives should be equal at junctions
 * @f{eqnarray}{
 * C_{i-1}^{'}(x_i) = C_{i}^{'}(x_i) \\
 * 3a_{i-1}h_{i-1}^2+2b_{i-1}h_{i-1}+c_{i-1}=c_{i}
 * @f}
 *
 * The second derivatives should be equal at junctions
 * @f{eqnarray}{
 * C_{i-1}^{''}(x_i) = C_{i}^{''}(x_i) \\
 * 6a_{i-1}h_{i-1}+2b_{i-1} = 2b{i}
 * @f}
 *
 * Consider there are n + 1 knots that define n segments. Each segment is presented by a cubic polynomial. There are
 * @f$ 4n @f$ unknowns while only @f$ 4n-2 @f$ equations are defined from (5)(7)(9). To close the system, two more
 * constraits need to be specified.
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
 * C_0^{''}(x_0)=2b_0=0\\
 * C_{n-1}^{''}(x_n)=2b_n=0
 * @f}
 * The default condition implies the spline is linear when it passes through the end points.
 *
 * Equation (5) specify that
 * @f{eqnarray}{
 * d_i=y_i \\
 * c_i=\frac{y_{i+1}-y_i}{h_i} - a_ih_i^2-b_ih_i
 * @f}
 *
 * Equation (9) specify that
 * @f{eqnarray}{
 * a_i=\frac{b_{i+1}-b_i}{3h_i}
 * @f}
 *
 * Put (14) into (13) gives
 * @f{eqnarray}{
 * c_i=\frac{y_{i+1}-y_i}{h_i}-\frac{(b_{i+1}+2b_i)h_i}{3}
 * @f}
 *
 * Put (14)(15) into (7) gives
 * @f{eqnarray}{
 * b_{i-1}h_{i-1}+2b_{i}(h_{i-1}+h_{i})+b_{i+1}h_i=\frac{3(y_{i+1}-y_i)}{h_i}-\frac{3(y_i-y_{i-1})}{h_{i-1}} \quad i = 1
 * \dots n-1
 * @f}
 *
 * For start condition:
 * - Given first derivative of start condition @f$ y_0^{'} @f$. Put (14)(15) into (2) and i=0 gives
 * @f{eqnarray}{
 * 2h_0b_0 +h_0b_1=\frac{3(y_1-y_0)}{h_0}-3y_0^{'}
 * @f}
 * - Given second derivative of start condition @f$ y_0^{''} @f$. Equation (3) gives
 * @f{eqnarray}{
 * b_0 = y_0^{''}
 * @f}
 *
 * For end condition:
 * - Given first derivative of end condition @f$ y_n^{'} @f$. Put (14)(15) into (2) and @f$i=n-1@f$ gives
 *   @f{eqnarray}{
 *   h_{n-1}b_{n-1}+2h{n-1}b_n=3y_n^{'}-\frac{3(y_n-y_{n-1})}{h_{n-1}}
 *   @f}
 * - Given second derivative of end condition @f$ y_n^{''} @f$. Put (14) into (3) and @f$i=n-1@f$ gives
 *   @f{eqnarray}{
 *   2b_n=y_n^{''}
 *   @f}
 *
 *
 * Equation (16) and start/end conditions can be writen in matrix form:
 * @f{eqnarray}{
 * \begin{bmatrix}
 *   s_0    & s_1    & 0      & \cdots  & 0       & 0       & 0       \\
 *   h_0    & p_1    & h_1    & \cdots  & 0       & 0       & 0       \\
 *   0      & h_1    & p_2    & \cdots  & 0       & 0       & 0       \\
 *   \vdots & \vdots & \vdots & \ddots  & \vdots  & \vdots  & \vdots  \\
 *   0      & 0      & 0      & \cdots  & p_{n-2} & h_{n-2} & 0       \\
 *   0      & 0      & 0      & \cdots  & h_{n-2} & p_{n-1} & h_{n-1} \\
 *   0      & 0      & 0      & \cdots  & 0       & e_0     & e_1     \\
 * \end{bmatrix} \
 * \begin{bmatrix}
 *   b_0 \\ b_1 \\ b_2 \\ \vdots \\ b_{n-2} \\ b_{n-1} \\ b_n \\
 * \end{bmatrix} \
 * = \
 * \begin{bmatrix}
 *   q_0 \\ q_1 \\ q_2 \\ \vdots \\ q_{n-2} \\ q_{n-1} \\ q_n \\
 * \end{bmatrix}
 * @f}
 * where
 * @f{eqnarray*}{
 * h_i&=&x_{i+1}-x_{i} \\
 * p_i&=&2(h_{i-1}+h_{i})=2(x_{i+1}-x_{i-1}) \\
 * q_i&=&\frac{3(y_{i+1}-y_i)}{h_i}-\frac{3(y_i-y_{i-1})}{h_{i-1}} \quad i=1 \dots n-1 \\
 * @f}
 * @f$s_0,s_1,e_0,e_1,q_0,q_n@f$ are start/end conditions given by equation  (17)(18)(19)(20)
 *
 * This is a tri-diagonal matrix which can be solved by
 * [Gaussian elimination](https://en.wikipedia.org/wiki/Gaussian_elimination) or
 * [Thomas algorithm](https://en.wikipedia.org/wiki/Tridiagonal_matrix_algorithm)
 */
template <typename Point, size_t SIZE>
class CurvePolynomial<Point, SIZE, 3U>
{
public:
    using PointType  = Point;
    using ScalarType = typename PointType::ScalarType;
    using TagType    = CurveExplicitTag;

    static size_t const SIZE_VALUE   = SIZE;
    static size_t const DEGREE_VALUE = 3U;

    /**
     * @brief Algorithm related state.
     */
    struct State
    {
        using PolynomialType = holo::numerics::Polynomial<ScalarType, DEGREE_VALUE>;

        holo::container::Vector<ScalarType, SIZE>     distances;  ///< distance to start point of each knot.
        holo::container::Vector<PolynomialType, SIZE> polynomials[PointType::SIZE_VALUE - 1U];
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
    template <size_t S_ = SIZE_VALUE, typename std::enable_if<(S_ >= 2U)>::type* = nullptr>
    bool_t Update(CurveBaseT<PointType, SIZE_VALUE> const& curve, StateType& state)
    {
        if (curve.size() < 2U)
        {
            throw holo::exception::BadKnotNumberException();
        }

        updatePolynomials<PointType::SIZE_VALUE>(curve, state);

        state.distances.clear();
        state.distances.push_back(0);

        for (size_t idx = 0U; idx < curve.size() - 1U; ++idx)
        {
            state.distances.push_back(state.distances[idx] + segmentLength(curve, state, idx));
        }
        return true;
    }

    template <size_t S_ = SIZE_VALUE, typename std::enable_if<(S_ < 2U)>::type* = nullptr>
    bool_t Update(CurveBaseT<PointType, SIZE_VALUE> const&, StateType&)
    {
        return false;
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
        ScalarType x           = 0;
        if (segment_len > ScalarEqualT<ScalarType>().GetEpsilonValue())
        {
            x = (curve[idx + 1U][0U] - curve[idx][0U]) * (len - state.distances[idx]) / segment_len;
        }
        return getDerivative<D>(curve, state, curve[idx][0U] + x);
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
        ScalarType x           = 0;

        size_t idx  = utility::SearchSection(state.distances, *first, std::less_equal<ScalarType>());
        segment_len = state.distances[idx + 1U] - state.distances[idx];
        if (segment_len > ScalarEqualT<ScalarType>().GetEpsilonValue())
        {
            x = (curve[idx + 1U][0U] - curve[idx][0U]) * (*first - state.distances[idx]) / segment_len;
        }
        *out = getDerivative<D>(curve, state, curve[idx][0U] + x);
        ++out;
        ++first;

        while (first != last)
        {
            idx         = utility::SearchSectionWithHint(idx, state.distances, *first, std::less_equal<ScalarType>());
            segment_len = state.distances[idx + 1U] - state.distances[idx];
            if (segment_len > ScalarEqualT<ScalarType>().GetEpsilonValue())
            {
                x = (curve[idx + 1U][0U] - curve[idx][0U]) * (*first - state.distances[idx]) / segment_len;
            }
            *out = getDerivative<D>(curve, state, curve[idx][0U] + x);
            ++out;
            ++first;
        }
    }

    /**
     * @brief Get point on curve at given x coordinate
     *
     * @tparam D Derivative order
     * @param curve The explicit form curve object.
     * @param state The curve state.
     * @param x x coordinate.
     *
     * @return Point on curve
     */
    template <size_t D>
    PointType GetDerivativeByCoordinate(CurveBaseT<PointType, SIZE_VALUE> const& curve, StateType const& state,
                                        ScalarType x)
    {
        return getDerivative<D>(curve, state, x);
    }

    /**
     * @brief Get points on curve at sequence of x coordinates defined in range [first, last)
     *
     * @tparam D Derivative order
     * @tparam InputIt iterator with value_type of ScalarType.
     * @tparam OutputIt iterator with value type of PointType.
     * @param curve The explicit form curve object.
     * @param state The curve state.
     * @param first Start of input range.
     * @param last End of input range
     * @param out Iterator to sampled curve points.
     */
    template <size_t D, typename InputIt, typename OutputIt>
    void GetDerivativeByCoordinate(CurveBaseT<PointType, SIZE_VALUE> const& curve, StateType const& state,
                                   InputIt first, InputIt last, OutputIt out)
    {
        if (first == last)
        {
            return;
        }

        size_t idx = utility::SearchSection(curve, *first, pointCoordinateLessEqualCompare());
        *out       = getDerivative<D>(curve, state, *first - curve[idx][0U]);
        ++out;
        ++first;

        while (first != last)
        {
            idx  = utility::SearchSectionWithHint(idx, curve, *first, pointCoordinateLessEqualCompare());
            *out = getDerivative<D>(curve, state, *first - curve[idx][0U]);
            ++out;
            ++first;
        }
    }

private:
    template <size_t DIM>
    void setMatrixStartCondition(CurveBaseT<PointType, SIZE_VALUE> const& curve, ScalarType const& h0, ScalarType& s0,
                                 ScalarType& s1, ScalarType& q0)
    {
        if (curve.GetStartType() == CurveBaseT<PointType, SIZE_VALUE>::ConditionType::FIRST_DERIVATIVE)
        {
            PointType start_cond = curve.GetStartCondition();

            s0 = 2 * h0;
            s1 = h0;
            q0 = 3 * (curve[1U][DIM - 1U] - curve[0U][DIM - 1U]) / h0 - 3 * start_cond[DIM - 1U];
        }
        else if (curve.GetStartType() == CurveBaseT<PointType, SIZE_VALUE>::ConditionType::SECOND_DERIVATIVE)
        {
            PointType start_cond = curve.GetStartCondition();

            s0 = static_cast<ScalarType>(2);
            s1 = static_cast<ScalarType>(0);
            q0 = start_cond[DIM - 1U];
        }
        else
        {
            s0 = static_cast<ScalarType>(1);
            s1 = static_cast<ScalarType>(0);
            q0 = static_cast<ScalarType>(0);
        }
    }

    template <size_t DIM>
    void setMatrixEndCondition(CurveBaseT<PointType, SIZE_VALUE> const& curve, ScalarType const& hn_1, ScalarType& e0,
                               ScalarType& e1, ScalarType& qn)
    {
        size_t const n = curve.size() - 1;
        if (curve.GetEndType() == CurveBaseT<PointType, SIZE_VALUE>::ConditionType::FIRST_DERIVATIVE)
        {
            PointType end_cond = curve.GetEndCondition();

            e0 = hn_1;
            e1 = 2 * hn_1;
            qn = 3 * end_cond[DIM - 1U] - 3 * (curve[n][DIM - 1U] - curve[n - 1][DIM - 1U]) / hn_1;
        }
        else if (curve.GetEndType() == CurveBaseT<PointType, SIZE_VALUE>::ConditionType::SECOND_DERIVATIVE)
        {
            PointType end_cond = curve.GetEndCondition();

            e0 = static_cast<ScalarType>(0);
            e1 = static_cast<ScalarType>(2);
            qn = end_cond[DIM - 1U];
        }
        else
        {
            e0 = static_cast<ScalarType>(0);
            e1 = static_cast<ScalarType>(2);
            qn = static_cast<ScalarType>(0);
        }
    }

    template <size_t DIM>
    void calculatePolynomial(CurveBaseT<PointType, SIZE_VALUE> const& curve, StateType& state)
    {
        size_t const knots = curve.size();
        size_t const n     = knots - 1U;

        if (knots < 2U)
        {
            throw holo::exception::BadKnotNumberException();
        }

        ScalarType h[SIZE_VALUE];
        ScalarType p[SIZE_VALUE];
        ScalarType q[SIZE_VALUE];
        ScalarType b[SIZE_VALUE];

        ScalarType s[2U];  // start condition
        ScalarType e[2U];  // end condition

        // Initialize matrix
        h[0U] = curve[1U][0U] - curve[0U][0U];
        for (size_t i = 1U; i < n; ++i)
        {
            h[i] = curve[i + 1U][0U] - curve[i][0U];
            p[i] = 2 * (curve[i + 1U][0U] - curve[i - 1U][0U]);
            q[i] = 3 * (curve[i + 1U][DIM - 1U] - curve[i][DIM - 1U]) / h[i] -
                   3 * (curve[i][DIM - 1U] - curve[i - 1U][DIM - 1U]) / h[i - 1U];
        }

        setMatrixStartCondition<DIM>(curve, h[0], s[0], s[1], q[0]);
        setMatrixEndCondition<DIM>(curve, h[n - 1], e[0], e[1], q[n]);

        // Gaussian elimination
        if (n == 1)
        {
            e[1U] = e[1U] - s[1U] * e[0U] / s[0U];
            q[1U] = q[1U] - q[0U] * e[0U] / s[0U];
        }
        else
        {
            // start condition
            p[1U] = p[1U] - s[1U] * h[0U] / s[0U];
            q[1U] = q[1U] - q[0U] * h[0U] / s[0U];

            // rows in the middle
            for (size_t i = 2U; i < n; ++i)
            {
                p[i] = p[i] - h[i - 1U] * h[i - 1U] / p[i - 1U];
                q[i] = q[i] - q[i - 1U] * h[i - 1U] / p[i - 1U];
            }

            // end condition
            e[1U] = e[1U] - h[n - 1U] * e[0U] / p[n - 1U];
            q[n]  = q[n] - q[n - 1U] * e[0U] / p[n - 1U];
        }

        // Backsubstitution
        b[n] = q[n] / e[1U];
        for (size_t i = n - 1U; i > 0U; --i)
        {
            b[i] = (q[i] - h[i] * b[i + 1U]) / p[i];
        }
        b[0U] = (q[0U] - s[1U] * b[1U]) / s[0U];

        // Set polynomials
        state.polynomials[DIM - 2U].resize(n);
        state.polynomials[DIM - 2U][0U].template SetCoefficient<3U>((b[1U] - b[0U]) / (3 * h[0U]));
        state.polynomials[DIM - 2U][0U].template SetCoefficient<2U>(b[0U]);
        state.polynomials[DIM - 2U][0U].template SetCoefficient<1U>((curve[1][DIM - 1U] - curve[0U][DIM - 1U]) / h[0U] -
                                                                    (b[1U] + 2 * b[0U]) * h[0U] / 3);
        state.polynomials[DIM - 2U][0U].template SetCoefficient<0U>(curve[0][DIM - 1U]);

        for (size_t i = 1U; i < n; ++i)
        {
            state.polynomials[DIM - 2U][i].template SetCoefficient<3U>((b[i + 1U] - b[i]) / (3 * h[i]));
            state.polynomials[DIM - 2U][i].template SetCoefficient<2U>(b[i]);
            state.polynomials[DIM - 2U][i].template SetCoefficient<1U>(
                (b[i] + b[i - 1U]) * h[i - 1U] + state.polynomials[DIM - 2U][i - 1U].template GetCoefficient<1U>());
            state.polynomials[DIM - 2U][i].template SetCoefficient<0U>(curve[i][DIM - 1U]);
        }
    }

    template <size_t DIM, typename std::enable_if<(DIM > 2U)>::type* = nullptr>
    void updatePolynomials(CurveBaseT<PointType, SIZE_VALUE> const& curve, StateType& state)
    {
        calculatePolynomial<DIM>(curve, state);
        updatePolynomials<DIM - 1U>(curve, state);
    }

    template <size_t DIM, typename std::enable_if<(DIM == 2U)>::type* = nullptr>
    void updatePolynomials(CurveBaseT<PointType, SIZE_VALUE> const& curve, StateType& state)
    {
        calculatePolynomial<DIM>(curve, state);
    }

    template <size_t D>
    PointType getDerivative(CurveBaseT<PointType, SIZE_VALUE> const& curve, StateType const& state, ScalarType x) const
    {
        size_t idx = utility::SearchSection(curve, x, pointCoordinateLessEqualCompare());

        PointType  pt{};
        ScalarType x0 = curve[idx][0U];
        assignDims<D, PointType::SIZE_VALUE>(state, idx, x - x0, pt);
        pt[0U] = x;
        return pt;
    }

    template <size_t D, size_t DIM, typename std::enable_if<(DIM > 2U)>::type* = nullptr>
    void assignDims(StateType const& state, size_t const slot, ScalarType const x, PointType& pt) const
    {
        pt[DIM - 1U] = state.polynomials[DIM - 2U][slot].template GetDerivative<D>(x);
        assignDims<D, DIM - 1U>(state, slot, x, pt);
    }

    template <size_t D, size_t DIM, typename std::enable_if<(DIM == 2U)>::type* = nullptr>
    void assignDims(StateType const& state, size_t const slot, ScalarType const x, PointType& pt) const
    {
        pt[DIM - 1U] = state.polynomials[DIM - 2U][slot].template GetDerivative<D>(x);
    }

    ScalarType segmentLength(CurveBaseT<PointType, SIZE_VALUE> const& curve, StateType const& state, size_t slot,
                             size_t segments = 16U) const
    {
        PointType  sample_pt = curve[slot];
        PointType  target_pt;
        ScalarType len         = 0.0;
        ScalarType x0          = curve[slot][0U];
        ScalarType segment_len = curve[slot + 1U][0U] - curve[slot][0U];
        for (size_t i = 1U; i < segments; ++i)
        {
            ScalarType x = (static_cast<ScalarType>(1.0) / segments) * i * segment_len;
            target_pt    = getDerivative<0U>(curve, state, x0 + x);
            len += sample_pt.Dist(target_pt);
            sample_pt = target_pt;
        }
        len += sample_pt.Dist(curve[slot + 1]);
        return len;
    }

    class pointCoordinateLessEqualCompare
    {
    public:
        bool_t operator()(ScalarType x, PointType const& pt) const noexcept
        {
            return x <= pt[0U];
        }

        bool_t operator()(PointType const& pt, ScalarType x) const noexcept
        {
            return pt[0U] <= x;
        }
    };
};

}  // namespace details
}  // namespace geometry
}  // namespace holo

#endif
