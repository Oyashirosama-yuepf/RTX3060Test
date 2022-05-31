/*!
 *  \brief a container of mathmatic functions
 *  \author daizhen(daizhen@holomaitc.com)
 *  \date 2017-09-01
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_MAP_COMMON_MATH_H_
#define HOLO_MAP_COMMON_MATH_H_

#include <cmath>
#include <deque>
#include <functional>
#include <vector>

#include <holo/common/odometry.h>
#include <holo/map/common/utility.h>

/**
 * @addtogroup holo
 *
 * @{
 */
namespace holo
{
/**
 * @addtogroup map
 *
 * @{
 */
namespace map
{
/**
 * @addtogroup math
 *
 * @{
 */
namespace math
{
/**
 * @addtogroup internal
 *
 * @{
 */
namespace internal
{
template <typename T>
struct IsDequeOrVector
{
    enum
    {
        value = false
    };
};
template <typename T, typename A>
struct IsDequeOrVector<std::deque<T, A>>
{
    enum
    {
        value = true
    };
};
template <typename T, typename A>
struct IsDequeOrVector<std::vector<T, A>>
{
    enum
    {
        value = true
    };
};

template <typename T>
struct IsVector
{
    enum
    {
        value = false
    };
};
template <typename T, typename A>
struct IsVector<std::vector<T, A>>
{
    enum
    {
        value = true
    };
};

/**
 * @brief Reserve vector capacity.
 *
 * @tparam T vector
 *
 * @param[in, out] _vec  Input vector.
 * @param[in]      _size Size.
 */
template <typename T, typename ::std::enable_if<!IsVector<T>::value, T>::type* = nullptr>
void VecReserve(T& _vec, const Size _size);

/**
 * @brief Reserve vector capacity.
 *
 * @tparam T vector
 *
 * @param[in, out] _vec  Input vector.
 * @param[in]      _size Size.
 */
template <typename T, typename ::std::enable_if<IsVector<T>::value, T>::type* = nullptr>
void VecReserve(T& _vec, const Size _size);

/**
 * @brief Calculate matrix power.
 *
 * @param[in]  _m_a Input matrix.
 * @param[in]  _e_a Input exponent.
 * @param[out] _m_v Output matrix.
 * @param[out] _e_v Output exponent.
 * @param[in]  _n   N power
 */
void MatrixPower(const ::holo::numerics::MatrixXT<::holo::float64_t>& _m_a, const int _e_a,
                 ::holo::numerics::MatrixXT<::holo::float64_t>& _m_v, int& _e_v, const int _n);
}  // namespace internal
/**
 * @}
 */

/**
 * @brief Sort pair vector.
 *
 * @details A pair is composed of <Key, Value>, we sort the Value of all elements and adapt the Key as well.
 *
 * @tparam T PairKeyAndInt/PairKeyAndFloat
 *
 * @param[in,out] _vec_of_pair Pair vector need to be sorted
 */
template <typename T>
void SortPairVec(std::vector<T>& _vec_of_pair);

/**
 * @brief Generate random number between _v1 and _v2
 *
 * @tparam T int/double
 *
 * @param[in] _v1 Minimum value, included
 * @param[in] _v2 Maximum value, not included
 *
 * @return Random holo::float64_t number in a range [_v1, _v2)
 */
template <typename T>
holo::float64_t Random(const T _v1, const T _v2);

/**
 * @brief Check if input value is close to zero, tolerance: 1e-6
 *
 * @param[in] _input Value
 *
 * @return true  This value is close enough to 0.
 * @return false Otherwise.
 */
bool IsAlmostZero(const holo::float64_t _input);

/**
 * @brief Check if two float values are equal.
 * 
 * @tparam T float32_t/float64_t
 * 
 * @param[in] first_value  The first float value.
 * @param[in] second_value The second float value.
 * @param[in] epsilon      A small positive number for tolerance.
 * 
 * @return true:  Two values are equal.
 * @return false: Two values are not equal.
 */
template <typename T>
static inline bool IsFloatEqual(const T first_value, const T second_value, const T epsilon)
{
    return std::fabs(first_value - second_value) <= epsilon;
}

/**
 * @brief Check if input value is close to reference value, tolerance: 1e-6
 *
 * @param[in] _input Value
 * @param[in] _ref   Reference value
 *
 * @return true  This value is close enough to reference value.
 * @return false Otherwise.
 */
bool IsAlmost(const holo::float64_t _input, const holo::float64_t _ref);

/**
 * @brief Calculate Euclidean Distance (L2 distance)
 *
 * @tparam T Deque or vector
 *
 * @param[in] _input
 *
 * @return L2 distance of data
 */
template <typename T>
typename std::enable_if<internal::IsDequeOrVector<T>::value, T>::type::value_type L2Norm(const T& _input);

/**
 * @brief Calculate the sum of the Numbers
 *
 * @tparam T Deque or vector
 *
 * @param[in] _input
 *
 * @return Sum of data
 */
template <typename T>
typename std::enable_if<internal::IsDequeOrVector<T>::value, T>::type::value_type Sum(const T& _input);

/**
 * @brief Calculate the mean of the Numbers
 *
 * @tparam T Deque or vector
 *
 * @param[in] _input
 *
 * @return Mean of data
 */
template <typename T>
typename std::enable_if<internal::IsDequeOrVector<T>::value, T>::type::value_type Mean(const T& _input);

/**
 * @brief Calculate the square sum of the Numbers
 *
 * @tparam T Deque or vector
 *
 * @param[in] _input
 *
 * @return Square sum of data
 */
template <typename T>
typename std::enable_if<internal::IsDequeOrVector<T>::value, T>::type::value_type SqrSum(const T& _input);

/**
 * @brief Calculate standard devision across a sample
 *
 * @tparam T Deque or vector
 *
 * @param[in] _nums
 *
 * @return Standard devision across a sample
 */
template <typename T>
typename std::enable_if<internal::IsDequeOrVector<T>::value, T>::type::value_type StDev(const T& _nums);

/**
 * @brief Calculate standard devision for an entire population
 *
 * @tparam T Deque or vector
 *
 * @param[in] _nums
 *
 * @return Standard devision for an entire population
 */
template <typename T>
typename ::std::enable_if<internal::IsDequeOrVector<T>::value, T>::type::value_type StDevP(const T& _nums);

/**
 * @brief Calculate variance across a sample
 *
 * @tparam T Deque or vector
 *
 * @param[in] _nums
 *
 * @return Variance of data
 */
template <typename T>
typename ::std::enable_if<internal::IsDequeOrVector<T>::value, T>::type::value_type Var(const T& _nums);

/**
 * @brief Calculate variance for an entire population
 *
 * @tparam T Deque or vector
 *
 * @param[in] _nums
 *
 * @return Variance for an entire population
 */
template <typename T>
typename ::std::enable_if<internal::IsDequeOrVector<T>::value, T>::type::value_type VarP(const T& _nums);

/**
 * @brief Calculate value of vector minus constant
 *
 * @tparam T Deque or vector
 *
 * @param[in] _a A vector
 * @param[in] _b A constant value
 *
 * @return Deque or vector
 */
template <typename T>
typename std::enable_if<internal::IsDequeOrVector<T>::value, T>::type VecMinus(const T&                     _a,
                                                                               const typename T::value_type _b);

/**
 * @brief Calculate value of vector multiply constant
 *
 * @tparam T Deque or vector
 *
 * @param[in] _a A vector
 * @param[in] _b A constant value
 *
 * @return Deque or vector
 */
template <typename T>
typename std::enable_if<internal::IsDequeOrVector<T>::value, T>::type VecMult(const T& _a, const T& _b);

/**
 * @brief Calculate elementwise product between two vectors
 *
 * @tparam T Deque or vector
 *
 * @param[in] _a One vector.
 * @param[in] _b Another vector.
 *
 * @return Deque or vector
 */
template <typename T>
typename std::enable_if<internal::IsDequeOrVector<T>::value, T>::type HadamardProduct(const T& _a, const T& _b);

/**
 * @brief Calculate pearson correlation coefficient across a sample
 *
 * @tparam T Deque or vector
 *
 * @param[in] _x One vector.
 * @param[in] _y Another vector.
 *
 * @return Pearson correlation coefficient across a sample
 */
template <typename T>
typename ::std::enable_if<internal::IsDequeOrVector<T>::value, T>::type::value_type PearsonCorrCoeff(const T& _x,
                                                                                                     const T& _y);

/**
 * @brief Calculate pearson correlation coefficient for an entire population
 *
 * @tparam T Deque or vector
 *
 * @param[in] _x One vector.
 * @param[in] _y Another vector.
 *
 * @return Pearson correlation coefficient for an entire population
 */
template <typename T>
typename ::std::enable_if<internal::IsDequeOrVector<T>::value, T>::type::value_type PearsonCorrCoeffP(const T& _x,
                                                                                                      const T& _y);

/**
 * @brief Get the minimum element and it's index from a vector
 *
 * @tparam T Deque or vector
 *
 * @param[in]  _input       A vector.
 * @param[out] _min_element The minimum value.
 * @param[out] _min_id      The index of the minimum value.
 *
 * @return true:  Operation successful.
 * @return false: Otherwise.
 */
template <typename T, typename std::enable_if<internal::IsDequeOrVector<T>::value, T>::type* = nullptr>
bool GetMinElement(const T& _input, typename T::value_type& _min_element, Size& _min_id)
{
    if (!_input.empty())
    {
        const auto it = std::min_element(_input.begin(), _input.end());
        _min_element  = *it;
        _min_id       = static_cast<Size>(it - _input.begin());
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief Get the maximum element and it's index from a vector
 *
 * @tparam T Deque or vector
 *
 * @param[in] _input        A vector.
 * @param[out] _max_element The maximum value.
 * @param[out] _max_id      The index of the maximum value.
 *
 * @return true:  Operation successful.
 * @return false: Otherwise.
 */
template <typename T, typename std::enable_if<internal::IsDequeOrVector<T>::value, T>::type* = nullptr>
bool GetMaxElement(const T& _input, typename T::value_type& _max_element, Size& _max_id)
{
    if (!_input.empty())
    {
        const auto it = std::max_element(_input.begin(), _input.end());
        _max_element  = *it;
        _max_id       = static_cast<Size>(it - _input.begin());
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief Check if elements in vector are in ascending order.
 *
 * @tparam T Deque or vector
 *
 * @param[in] _input     All elements.
 * @param[in] _tolerance From 0 to 1.
 *
 * @return true:  The elements in vector are in ascending order.
 * @return false: Otherwise.
 */
template <typename T, typename std::enable_if<internal::IsDequeOrVector<T>::value, T>::type* = nullptr>
bool IsAscendingOrder(const T& _input, const typename T::value_type _tolerance);

/**
 * @brief Check if elements in vector are in descending order.
 *
 * @tparam T Deque or vector
 *
 * @param[in] _input     All elements.
 * @param[in] _tolerance From 0 to 1
 *
 * @return true:  The elements in vector are in descending order.
 * @return false: Otherwise.
 */
template <typename T, typename std::enable_if<internal::IsDequeOrVector<T>::value, T>::type* = nullptr>
bool IsDecendingOrder(const T& _input, const typename T::value_type _tolerance);

/**
 * @brief Kolmogorov's Distribution
 *
 * @param[in] _n Number of samples
 * @param[in] _d D value.
 *
 * @return Probability of Dn < d
 */
::holo::float64_t KolmogorovSmirnovCDF(const int _n, const ::holo::float64_t _d);

enum class KolmogorovSmirnovTestType
{
    kUnequal,
    kSmaller,
    kLarger
};

/**
 * @brief Two Sample Kolmogorov-Smirnov Test
 *
 * @tparam T Deque or vector
 *
 * @param[in] _x1            One sample.
 * @param[in] _x2            Another sample.
 * @param[in] _type          Kolmogorov-Smirnov Test Type.
 * @param[out] _p_value
 * @param[out] _ks_statistic The Kolmogorov–Smirnov statistic.
 */
template <typename T>
typename ::std::enable_if<internal::IsDequeOrVector<T>::value, void>::type
KolmogorovSmirnovTest2(const T& _x1, const T& _x2, const KolmogorovSmirnovTestType _type, ::holo::float64_t& _p_value,
                       ::holo::float64_t& _ks_statistic);

/**
 * @brief Two Sample Kolmogorov-Smirnov Test
 *
 * @tparam T Deque or vector
 *
 * @param[in] _x             A sample.
 * @param[in] _func_cdf      Function of distribution
 * @param[in] _type          Kolmogorov-Smirnov Test Type.
 * @param[out] _p_value
 * @param[out] _ks_statistic The Kolmogorov–Smirnov statistic.
 */
template <typename T>
typename ::std::enable_if<internal::IsDequeOrVector<T>::value, void>::type
KolmogorovSmirnovTest(const T& _x, const ::std::function<::holo::float64_t(const typename T::value_type)>& _func_cdf,
                      const KolmogorovSmirnovTestType _type, ::holo::float64_t& _p_value,
                      ::holo::float64_t& _ks_statistic);

/**
 * @brief Check if elements in range are uniform distribution.
 *
 * @tparam T Deque or vector
 *
 * @param[in] _input     All elements.
 * @param[in] _range_min The minimum range.
 * @param[in] _range_max The maximum range.
 * @param[in] _alpha     From 0 to 1, usually it's 0.05
 *
 * @return true:  These elements are uniform distribution in this range.
 * @return false: Otherwise.
 */
template <typename T>
typename std::enable_if<internal::IsDequeOrVector<T>::value, bool>::type
IsUniformDistribution(const T& _input, const typename T::value_type _range_min, const typename T::value_type _range_max,
                      const typename ::holo::float64_t _alpha);

/**
 * @brief Check if a vector is tightly centralized at its mean value.
 *
 * @tparam T Deque or vector
 *
 * @param[in] _input     All elements.
 * @param[in] _tolerance Maximal allowance of the divergency.
 *
 * @return true:  All vector/deque elements are close to the mean value.
 * @return false: Otherwise.
 */
template <typename T, typename std::enable_if<internal::IsDequeOrVector<T>::value, T>::type* = nullptr>
bool IsEqualValueVector(const T& _input, const typename T::value_type _tolerance);

/**
 * @brief Check if two lengths are same approximately.
 *
 * @param[in] _v1 One length value
 * @param[in] _v2 Another length value
 *
 * @return true:  Two lengths are same approximately.
 * @return false: Otherwise.
 */
bool IsSameLength(const Distance& _v1, const Distance& _v2);

/**
 * @brief Check if two degrees are same approximately.
 *
 * @param[in] _v1 One degree value
 * @param[in] _v2 Another degree value
 *
 * @return true:  Two degrees are same approximately.
 * @return false: Otherwise.
 */
bool IsSameDegree(const MapDegree& _v1, const MapDegree& _v2);

/**
 * @brief Get velocity from odometry
 *
 * @param[in] _odo odometry
 *
 * @return Velocity
 */
Distance GetVelocityFromOdo(const ::holo::common::Odometryd& _odo);

/**
 * @brief Delete the element in vector, which is larger than N times of deviation.
 *
 * @param[in,out] _vec vector It is to be filtered
 * @param[in]     N           N times of deviation
 *
 * @return true:  Operation successful.
 * @return false: Otherwise.
 */
bool OutlierFilter(std::vector<Distance>& _vec, const holo::float64_t _N = 3.0);

/**
 * @brief Calculate mean absolute error between two vectors.
 *
 * @tparam Deque or Vector
 *
 * @param[in] _x    One vector.
 * @param[in] _y    Another vector.
 * @param[out] _mae Mean absolute error
 *
 * @return true:  Operation successful.
 * @return false: Otherwise.
 */
template <typename T>
typename ::std::enable_if<internal::IsDequeOrVector<T>::value, bool>::type
MeanAbsoluteError(const T& _x, const T& _y, typename T::value_type& _mae);

/**
 * @brief Calculate root mean square error between two vectors.
 *
 * @tparam Deque or Vector
 *
 * @param[in] _x     One vector.
 * @param[in] _y     Another vector.
 * @param[out] _rmse Root mean square error.
 *
 * @return true:  Operation successful.
 * @return false: Otherwise.
 */
template <typename T>
typename ::std::enable_if<internal::IsDequeOrVector<T>::value, bool>::type
RootMeanSquareError(const T& _x, const T& _y, typename T::value_type& _rmse);

/**
 * @brief Get the maximum element of given matrix.
 *
 * @param[in] _input Given matrix
 *
 * @return The maximum element.
 */
::holo::float64_t MaxCoeff(const ::holo::numerics::VectorXT<::holo::float64_t>& _input);

/**
 * @brief Get n elements of given vector head.
 *
 * @details If _length is more than matrix's size, return all matrix's elements.
 *
 * @param[in] _input_matrix Given matrix.
 * @param[in] _length       Number of elements.
 *
 * @return Elements.
 */
::holo::numerics::VectorXT<::holo::float64_t> Head(const ::holo::numerics::VectorXT<::holo::float64_t>& _input_matrix,
                                         const ::holo::uint16_t                     _length);

/**
 * @brief Get n elements of given vector tail.
 *
 * @details If _length is more than matrix's size, return all matrix's elements.
 *
 * @param[in] _input_matrix Given matrix.
 * @param[in] _length       Number of elements.
 *
 * @return Elements.
 */
::holo::numerics::VectorXT<::holo::float64_t> Tail(const ::holo::numerics::VectorXT<::holo::float64_t>& _input_matrix,
                                         const uint16_t                             _length);

/**
 * @brief Linear interpolation calculation
 * 
 *   ^
 *   |
 * y2|                      /---------------
 *   |                    /
 *   |                  /
 *   |                /
 *   |              /
 *   |            /
 * y1|----------/
 *   |          
 *   ----------------------------------------->
 *             x1            x2
 * @param[in] x1 
 * @param[in] y1 
 * @param[in] x2 
 * @param[in] y2 
 * @param[in] x       Linear interpolation input value.
 * @param[out] result Linear interpolation result value.
 *
 * @return true: Operation successful. false: Otherwise
 */
bool LinearInterpolation(const holo::float64_t x1, const holo::float64_t y1,
                         const holo::float64_t x2, const holo::float64_t y2,
                         const holo::float64_t x, holo::float64_t& result);
}  // namespace math
/**
 * @}
 */
}  // namespace map
/**
 * @}
 */
}  // namespace holo
/**
 * @}
 */

#endif /* HOLO_MAP_COMMOM_MATH_H_ */
