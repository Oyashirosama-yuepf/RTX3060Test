/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file utility.h
 * @brief utility functions in numerics
 * @author jiaxing.zhao, duyanwei
 * @date 2019-09-04
 */

#ifndef HOLO_NUMERICS_UTILITY_H_
#define HOLO_NUMERICS_UTILITY_H_

#include <cmath>
#include <set>
#include <vector>

#include <holo/core/type_traits.h>
#include <holo/math/math.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>

namespace holo
{
namespace numerics
{
/**
 * @addtogroup numerics
 * @{
 *
 */

/**
 * @brief this function aims at computing mean and standard deviation of input data
 *
 * @tparam Scalar, float32_t or float64_t
 * @param[in] v input data
 * @param[out] mean mean value
 * @param[out] stdev standard deviation
 */
template <typename Scalar>
void ComputeMeanAndStdev(const std::vector<Scalar>& v, Scalar& mean, Scalar& stdev) noexcept;

/**
 * @brief this function aims at computing max and min of input data
 *
 * @tparam Scalar, float32_t or float64_t
 * @param[in] data input data
 * @param[out] max_value max value
 * @param[out] min_value min value
 */
template <typename Scalar>
void ComputeMaxAndMinValue(const std::vector<Scalar>& data, Scalar& max_value, Scalar& min_value) noexcept;

/**
 * @brief this function aims at computing root mean square (rms) of input data
 *
 * @tparam Scalar, float32_t or float64_t
 * @param[in] data input data
 * @return rms
 */
template <typename Scalar>
Scalar ComputeRMS(const std::vector<Scalar>& data) noexcept;

/**
 * @brief This function computes the mean vector and covariance matrix
 *
 * @tparam Scalar, float32_t or float64_t
 * @param[in] samples input data, each row of the matrix corresponds to one sample
 * @param[out] mean mean vector
 * @param[out] covariance covariance matrix
 */
template <typename Scalar>
void ComputeCovarianceMatrix(const MatrixXT<Scalar>& samples, VectorXT<Scalar>& mean,
                             MatrixXT<Scalar>& covariance) noexcept;

/**
 * @brief This function computes the roots of a polynomial
 *
 * @tparam Scalar, float32_t or float64_t
 * @details given a defined polynomial f(x) = a_0 + a_1 * x^1 + a_2 * x^2 + ....+ a_n * x^n, we evaluate the value of x
 *          when f(x) = 0
 * @ref http://mathworld.wolfram.com/PolynomialRoots.html
 * @param[in] coeffs polynomial coefficients, e.g. a_0 = coeffs(0), a_1 = coeffs(1), ...
 * @param[out] roots solutions including all unique real and imaginary results
 */
template <typename Scalar>
void ComputePolynomialRoots(const VectorXT<Scalar>& coeffs, std::set<std::pair<Scalar, Scalar> >& roots) noexcept;

/**
 * @brief Bernstein polynomial object
 * @details Bernstein polynomial is represented by @f$b_{\nu,n}(t)=\binom{n}{\nu}t^\nu(1-t)^{n-\nu}@f$
 *
 * @tparam T Polynomial scalar type
 * @tparam I Index number
 * @tparam Degree Degree value of Bernstein polynomial
 */
template <typename T, size_t I, size_t Degree, typename std::enable_if<(I <= Degree) && (Degree >= 0U)>::type* = nullptr>
class BernsteinPolynomial
{
public:
    using ScalarType = T;

    static size_t const DEGREE_VALUE = Degree;
    static size_t const ORDER_VALUE  = Degree + 1;

    /**
     * @brief Evaluate polynomial value at t.
     *
     * @param t Variable value
     *
     * @return Evaluated value.
     */
    ScalarType operator[](ScalarType t) const noexcept
    {
        return CalculateDerivative<0U>(t);
    }

    /**
     * @brief Evaluate polynomial value at t.
     *
     * @param t Variable value
     *
     * @return Evaluated value.
     */
    ScalarType GetValue(ScalarType t) const noexcept
    {
        return CalculateDerivative<0U>(t);
    }

    /**
     * @brief Get D-th derivative value at t.
     *
     * @tparam D Derivative order
     * @param t Variable value
     *
     * @return D-th derivative at t
     */
    template <size_t D>
    ScalarType GetDerivative(ScalarType t) const noexcept
    {
        return CalculateDerivative<D>(t);
    }

    /**
     * @brief Calculate D-th derivative value at t.
     *
     * @tparam D Derivative order
     * @param t Variable value
     *
     * @return D-th derivative at t
     */
    template <size_t D, typename std::enable_if<D == 0>::type* = nullptr>
    static constexpr ScalarType CalculateDerivative(ScalarType t)
    {
        return holo::math::Factorial<DEGREE_VALUE>() /
               (holo::math::Factorial<I>() * holo::math::Factorial<DEGREE_VALUE - I>()) *
               holo::math::Pow<DEGREE_VALUE - I>(1 - t) * holo::math::Pow<I>(t);
    }

    /**
     * @brief Calculate D-th derivative value at t.
     *
     * @tparam D Derivative order
     * @param t Variable value
     *
     * @return D-th derivative at t
     */
    template <size_t D, typename std::enable_if<(D > 0U) && (I == 0U)>::type* = nullptr>
    static constexpr ScalarType CalculateDerivative(ScalarType t)
    {
        return DEGREE_VALUE *
               (-BernsteinPolynomial<ScalarType, I, DEGREE_VALUE - 1U>::template CalculateDerivative<D - 1U>(t));
    }

    /**
     * @brief Calculate D-th derivative value at t.
     *
     * @tparam D Derivative order
     * @param t Variable value
     *
     * @return D-th derivative at t
     */
    template <size_t D, typename std::enable_if<(D > 0U) && (I == DEGREE_VALUE)>::type* = nullptr>
    static constexpr ScalarType CalculateDerivative(ScalarType t)
    {
        return DEGREE_VALUE *
               BernsteinPolynomial<ScalarType, I - 1U, DEGREE_VALUE - 1U>::template CalculateDerivative<D - 1U>(t);
    }

    /**
     * @brief Calculate D-th derivative value at t.
     *
     * @tparam D Derivative order
     * @param t Variable value
     *
     * @return D-th derivative at t
     */
    template <size_t D, typename std::enable_if<(D > 0U) && (I > 0) && (I < DEGREE_VALUE)>::type* = nullptr>
    static constexpr ScalarType CalculateDerivative(ScalarType t)
    {
        return DEGREE_VALUE *
               (BernsteinPolynomial<ScalarType, I - 1U, DEGREE_VALUE - 1U>::template CalculateDerivative<D - 1U>(t) -
                BernsteinPolynomial<ScalarType, I, DEGREE_VALUE - 1U>::template CalculateDerivative<D - 1U>(t));
    }
};

/**
 * @brief Polynomial object
 * @details A polynomial is represented by @f$a_0+a_1x+a_2x^2+\cdots+a_nx^n@f$
 *
 * @tparam T Scalar type
 * @tparam Degree Polynomial degree value (Max value of "n")
 */
template <typename T, size_t Degree>
class Polynomial
{
public:
    using ScalarType = T;

    static size_t const DEGREE_VALUE = Degree;
    static size_t const ORDER_VALUE  = Degree + 1;

    /**
     * @brief Default constructor
     */
    Polynomial() : coefficients_{}
    {
    }

    /**
     * @brief Construct polynomial with coefficients of each degree. The i-th arguments corresponds to i-th degree.
     *
     * @tparam Args Types of each coefficient.
     * @param args Coefficient values.
     */
    template <typename... Args,
              typename std::enable_if<(sizeof...(Args) <= ORDER_VALUE) &&
                                      And<std::is_convertible<Args, ScalarType>::value...>::value>::type* = nullptr>
    Polynomial(Args&&... args) : coefficients_{static_cast<ScalarType>(std::forward<Args>(args))...}
    {
    }

    /**
     * @brief Default copy constructor
     */
    Polynomial(Polynomial const&) = default;

    /**
     * @brief Default move constructor
     */
    Polynomial(Polynomial&&)      = default;

    /**
     * @brief Default copy assign operator
     */
    Polynomial& operator=(Polynomial const&) = default;

    /**
     * @brief Default move assign operator
     */
    Polynomial& operator=(Polynomial&&) = default;

    /**
     * @brief Assign from initializer list
     * @details i-th element in initializer list represents coefficient of i-th degree.
     * If size of initializer list is smaller than polynomial ORDER_VALUE, the rest of coefficent values will be left as
     * they are. If size of initializer list is greater than polynomial ORDER_VALUE, only the first ORDER_VALUE elements
     * will be used.
     *
     * @param ilist initializer list
     *
     * @return Reference to this object.
     */
    Polynomial& operator=(std::initializer_list<ScalarType> ilist) noexcept
    {
        size_t idx         = 0;
        size_t assign_size = std::min(ilist.size(), ORDER_VALUE);
        for (; idx < assign_size; ++idx)
        {
            coefficients_[idx] = ilist[idx];
        }
        for (; idx < ORDER_VALUE; ++idx)
        {
            coefficients_[idx] = static_cast<ScalarType>(0);
        }
        return *this;
    }

    /**
     * @brief Evaluate polynomial value at t.
     *
     * @param t Variable value
     *
     * @return Evaluated value.
     */
    ScalarType operator[](ScalarType t) const noexcept
    {
        return GetValue(t);
    }

    /**
     * @brief Evaluate polynomial value at t.
     *
     * @param t Variable value
     *
     * @return Evaluated value.
     */
    ScalarType GetValue(ScalarType t) const noexcept
    {
        return GetDerivative<0>(t);
    }

    /**
     * @brief Get D-th derivative value at t.
     *
     * @tparam D Derivative order
     * @param t Variable value
     *
     * @return D-th derivative at t
     */
    template <size_t D>
    ScalarType GetDerivative(ScalarType t) const noexcept
    {
        return derivativeInternal<D, D>(t);
    }

    /**
     * @brief Get I-th degree coefficient.
     *
     * @tparam I Degree index
     *
     * @return Coefficient of I-th degree.
     */
    template <size_t I, typename std::enable_if<(I <= DEGREE_VALUE)>::type* = nullptr>
    ScalarType GetCoefficient() const noexcept
    {
        return coefficients_[I];
    }

    /**
     * @brief Set I-th degree coefficient
     *
     * @tparam I Degree index
     * @param value Coefficient value
     */
    template <size_t I, typename std::enable_if<(I <= DEGREE_VALUE)>::type* = nullptr>
    void SetCoefficient(ScalarType value) noexcept
    {
        coefficients_[I] = value;
    }

    /**
     * @brief Get derivative polynomial
     *
     * @tparam D Derivative order
     *
     * @return Derivative polynomial.
     */
    template <size_t D>
    Polynomial<ScalarType, DEGREE_VALUE - D> GetDerivativePolynomial() const noexcept
    {
        Polynomial<ScalarType, DEGREE_VALUE - D> poly;
        setDerivativePolynomialCoefficients<0U, D>(poly);
        return poly;
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return holo::serialization::AlignedSize<ALIGN>(sizeof(ScalarType) * (Degree + 1U));
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::serialization::SerializationBufferOverflowException if buffer size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        for(size_t i=0; i<Degree+1; ++i)
        {
            serializer << coefficients_[i];
        }
        serializer << holo::serialization::align;
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        for(size_t i=0; i<Degree+1; ++i)
        {
            deserializer >> coefficients_[i];
        }
        deserializer >> holo::serialization::align;
    }

protected:
    /**
     * @brief calculate derivative coefficient of @f$(x^I)^D@f$.
     *
     * @tparam I Degree index
     * @tparam D derivative order
     *
     * @return Coefficient of D-th derivative of @f$(x^I)^D@f$.
     */
    template <size_t I, size_t D, typename std::enable_if<(I > 0) && (D > 0)>::type* = nullptr>
    static constexpr size_t derivativeCoefficient() noexcept
    {
        return I * derivativeCoefficient<I - 1, D - 1>();
    }

    /**
     * @brief calculate derivative coefficient of @f$(x^I)^D@f$.
     *
     * @tparam I Degree index
     * @tparam D derivative order
     *
     * @return Coefficient of D-th derivative of @f$(x^I)^D@f$.
     */
    template <size_t I, size_t D, typename std::enable_if<(I > 0) && (D == 0)>::type* = nullptr>
    static constexpr size_t derivativeCoefficient() noexcept
    {
        return 1U;
    }

    /**
     * @brief calculate derivative coefficient of @f$(x^I)^D@f$.
     *
     * @tparam I Degree index
     * @tparam D derivative order
     *
     * @return Coefficient of D-th derivative of @f$(x^I)^D@f$.
     */
    template <size_t I, size_t D, typename std::enable_if<(I == 0) && (D == 0)>::type* = nullptr>
    static constexpr size_t derivativeCoefficient() noexcept
    {
        return 1U;
    }

    /**
     * @brief calculate derivative coefficient of @f$(x^I)^D@f$.
     *
     * @tparam I Degree index
     * @tparam D derivative order
     *
     * @return Coefficient of D-th derivative of @f$(x^I)^D@f$.
     */
    template <size_t I, size_t D, typename std::enable_if<(I == 0) && (D > 0)>::type* = nullptr>
    static constexpr size_t derivativeCoefficient() noexcept
    {
        return 0U;
    }

    /**
     * @brief Calculate coefficient of D-th derivative of I-th degree element at value t.
     *
     * @tparam I Element index
     * @tparam D Derivative order
     * @param t Varibale value.
     *
     * @return D-th derivative coefficient of I-th degree element at value t.
     */
    template <size_t I, size_t D, typename std::enable_if<(I == DEGREE_VALUE)>::type* = nullptr>
    constexpr ScalarType derivativeInternal(ScalarType) const noexcept
    {
        return derivativeCoefficient<I, D>() * coefficients_[I];
    }

    /**
     * @brief Calculate coefficient of D-th derivative of I-th degree element at value t.
     *
     * @tparam I Element index
     * @tparam D Derivative order
     * @param t Varibale value.
     *
     * @return D-th derivative coefficient of I-th degree element at value t.
     */
    template <size_t I, size_t D, typename std::enable_if<(I < DEGREE_VALUE)>::type* = nullptr>
    constexpr ScalarType derivativeInternal(ScalarType t) const noexcept
    {
        return derivativeInternal<I + 1U, D>(t) * t + coefficients_[I] * derivativeCoefficient<I, D>();
    }

    /**
     * @brief Calculate coefficient of D-th derivative of I-th degree element at value t.
     *
     * @tparam I Element index
     * @tparam D Derivative order
     * @param t Varibale value.
     *
     * @return D-th derivative coefficient of I-th degree element at value t.
     */
    template <size_t I, size_t D, typename std::enable_if<(I > DEGREE_VALUE)>::type* = nullptr>
    constexpr ScalarType derivativeInternal(ScalarType) const noexcept
    {
        return static_cast<ScalarType>(0);
    }

    /**
     * @brief Set D-th degree derivative polynomial's I-th degree item coefficient
     *
     * @tparam I Element index
     * @tparam D Derivative order
     * @param poly Derivative polynomial
     */
    template <size_t I, size_t D, typename std::enable_if<(I < DEGREE_VALUE - D)>::type* = nullptr>
    void setDerivativePolynomialCoefficients(Polynomial<ScalarType, DEGREE_VALUE - D>& poly) const noexcept
    {
        poly.template SetCoefficient<I>(derivativeCoefficient<I + D, D>() * coefficients_[I + D]);
        setDerivativePolynomialCoefficients<I + 1U, D>(poly);
    }

    /**
     * @brief Set D-th degree derivative polynomial's I-th degree item coefficient
     *
     * @tparam I Element index
     * @tparam D Derivative order
     * @param poly Derivative polynomial
     */
    template <size_t I, size_t D, typename std::enable_if<(I == DEGREE_VALUE - D)>::type* = nullptr>
    void setDerivativePolynomialCoefficients(Polynomial<ScalarType, DEGREE_VALUE - D>& poly) const noexcept
    {
        poly.template SetCoefficient<I>(derivativeCoefficient<I + D, D>() * coefficients_[I + D]);
    }

private:
    ScalarType coefficients_[Degree + 1]; ///< Coefficients of polynomial
};

/**
 * @}
 */

}  // namespace numerics
}  // namespace holo

#endif  // HOLO_NUMERICS_UTILITY_H_
