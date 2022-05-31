/*!
 * @file epsilon.h
 * @brief This header file defines epsilon
 * @author duyanwei@holomatic.com
 * @date 2022-04-21
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_CORE_EPSILON_H_
#define HOLO_CORE_EPSILON_H_

#include <holo/core/types.h>
#include <cmath>

namespace holo
{
/**
 * @brief Compares whether two value are equal
 */
template <typename T>
class ScalarEqualT
{
public:
    using ScalarType = T;
    /**
     * @brief Compare whether value and expected are equal
     *
     * @param value value
     * @param expected expected value
     * @return equal return true otherwise false
     */
    bool_t operator()(ScalarType const value, ScalarType const expected) noexcept
    {
        return value == expected;
    }

    /**
     * @brief Get epsilon value
     *
     * @return epsilon value
     */
    ScalarType GetEpsilonValue()
    {
        return static_cast<ScalarType>(0U);
    }
};

/**
 * @brief Compares whether the values of two float32 type are equal
 */
template <>
class ScalarEqualT<float32_t>
{
public:
    /**
     * @brief Constructor
     *
     * Construct from epsilon value
     * @param eps epsilon value
     */
    ScalarEqualT(float32_t const eps = 1e-5f) noexcept : eps_{eps}
    {
    }

    /**
     * @brief Compare whether value and expected are equal
     *
     * @param value float32_t type value
     * @param expected float32_t type value
     * @return equal return true otherwise false
     */
    bool_t operator()(float32_t const value, float32_t const expected) noexcept
    {
        return std::fabs(value - expected) < eps_;
    }

    /**
     * @brief Compare whether value and expected are equal
     *
     * @param value float32_t type value
     * @param expected float32_t type value
     * @param eps precision in geometry class
     * @return equal return true otherwise false
     */
    bool_t operator()(float32_t const value, float32_t const expected, float32_t const eps) noexcept
    {
        return std::fabs(value - expected) < eps;
    }

    /**
     * @brief Get epsilon value
     *
     * @return epsilon value
     */
    float32_t GetEpsilonValue()
    {
        return eps_;
    }

private:
    float32_t eps_;
};

/**
 * @brief Compares whether the values of two float64 type are equal
 */
template <>
class ScalarEqualT<float64_t>
{
public:
    /**
     * @brief Constructor
     *
     * Construct from epsilon value
     * @param eps epsilon value
     */
    ScalarEqualT(float64_t const& eps = 1e-10) noexcept : eps_{eps}
    {
    }

    /**
     * @brief Compare whether value and expected are equal
     *
     * @param value float64_t type value
     * @param expected float64_t type value
     * @return equal return true otherwise false
     */
    bool_t operator()(float64_t const& value, float64_t const& expected) noexcept
    {
        return std::fabs(value - expected) < eps_;
    }

    /**
     * @brief Compare whether value and expected are equal
     *
     * @param value float64_t type value
     * @param expected float64_t type value
     * @param eps precision in geometry class
     * @return equal return true otherwise false
     */
    bool_t operator()(float64_t const& value, float64_t const& expected, float64_t const& eps) noexcept
    {
        return std::fabs(value - expected) < eps;
    }

    /**
     * @brief Get epsilon value
     *
     * @return epsilon value
     */
    float64_t GetEpsilonValue()
    {
        return eps_;
    }

private:
    float64_t eps_;
};

/**
 * @ingroup geometry
 *
 * @brief epsilon struct to define the precision in geometry class
 * @deprecated replaced by Float32Equal and Float64Equal
 *
 * @tparam T
 */
template <typename T>
struct [[deprecated]] EpsilonT {};  // Epsilon

/**
 * @brief template specialization of bool
 * @deprecated deprecated soon!
 *
 * @tparam T bool
 */
template <>
struct [[deprecated]] EpsilonT<bool_t> { static const bool_t value; };

/**
 * @brief template specialization of int32_t
 * @deprecated deprecated soon!
 *
 * @tparam T int32_t
 */
template <>
struct [[deprecated]] EpsilonT<int32_t> { static const int32_t value; };

/**
 * @brief template specialization of int32_t
 * @deprecated deprecated soon!
 *
 * @tparam T uint32_t
 */
template <>
struct [[deprecated]] EpsilonT<uint32_t> { static const uint32_t value; };

/**
 * @brief template specialization of uint64_t
 * @deprecated deprecated soon!
 *
 * @tparam T uint64_t
 */
template <>
struct [[deprecated]] EpsilonT<uint64_t> { static const uint64_t value; };

/**
 * @brief template specialization of float32_t
 * @deprecated deprecated soon!
 *
 * @tparam T float32_t
 */
template <>
struct [[deprecated]] EpsilonT<float32_t> { static const float32_t value; };

/**
 * @brief template specialization of float64_t
 * @deprecated deprecated soon!
 *
 * @tparam T float64_t
 */
template <>
struct [[deprecated]] EpsilonT<float64_t> { static const float64_t value; };

}  // namespace holo

#endif  // HOLO_GEOMETRY_EPSILON_H_
