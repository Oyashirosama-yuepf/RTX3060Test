/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file jet.h
 * @brief This header file defines jets for automatic derivatives.
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-11-02"
 */

#ifndef HOLO_PERCEPTION_MATH_JET_H_
#define HOLO_PERCEPTION_MATH_JET_H_

#include <array>
#include <cmath>
#include <sstream>

#include <holo/core/types.h>

namespace holo
{
namespace perception
{
/**
 * @addtogroup math
 *
 * @{
 */

/**
 * @brief jet for automatic derivatives
 * @ref http://www.ceres-solver.org/automatic_derivatives.html#dual-numbers-jets
 *
 * @tparam Scalar data type, float or double
 * @tparam N variable number
 */
template <typename Scalar, int N>
struct Jet
{
    /**
     * @brief Construct a new Jet object
     *
     */
    Jet() : a(static_cast<Scalar>(0.0))
    {
        v.fill(static_cast<Scalar>(0.0));
    }

    /**
     * @brief operator -
     *
     * @return Jet<Scalar, N> -jet
     */
    Jet<Scalar, N> operator-()
    {
        Jet<Scalar, N> r;
        r.a = -a;
        for (size_t i = 0U; i < N; ++i)
        {
            r.v[i] = -v[i];
        }
        return r;
    }

    /**
     * @brief operator +
     *
     * @return Jet<Scalar, N> +jet
     */
    Jet<Scalar, N> operator+()
    {
        return *this;
    }

    Scalar                a; /* value */
    std::array<Scalar, N> v; /* jacobian */
};

/**
 * @brief c + f
 *
 * @tparam N variable number
 * @param c scalar
 * @param f jet
 * @return Jet<Scalar, N> c + f
 */
template <typename Scalar, int N>
Jet<Scalar, N> operator+(float32_t c, Jet<Scalar, N> const& f)
{
    Jet<Scalar, N> r;
    r.a = c + f.a;
    r.v = f.v;
    return r;
}

/**
 * @brief f + c
 *
 * @tparam N variable number
 * @param f jet
 * @param c scalar
 * @return Jet<Scalar, N> f + c
 */
template <typename Scalar, int N>
Jet<Scalar, N> operator+(Jet<Scalar, N> const& f, Scalar c)
{
    Jet<Scalar, N> r;
    r.a = f.a + c;
    r.v = f.v;
    return r;
}

/**
 * @brief f + g
 *
 * @tparam N variable number
 * @param f jet
 * @param g jet
 * @return Jet<Scalar, N> f + g
 */
template <typename Scalar, int N>
Jet<Scalar, N> operator+(Jet<Scalar, N> const& f, Jet<Scalar, N> const& g)
{
    Jet<Scalar, N> r;
    r.a = f.a + g.a;
    for (size_t i = 0U; i < N; ++i)
    {
        r.v[i] = f.v[i] + g.v[i];
    }
    return r;
}

/**
 * @brief c - f
 *
 * @tparam N variable number
 * @param c scalar
 * @param f jet
 * @return Jet<Scalar, N> c - f
 */
template <typename Scalar, int N>
Jet<Scalar, N> operator-(Scalar c, Jet<Scalar, N> const& f)
{
    Jet<Scalar, N> r;
    r.a = c - f.a;
    for (size_t i = 0U; i < N; ++i)
    {
        r.v[i] = -f.v[i];
    }
    return r;
}

/**
 * @brief f - c
 *
 * @tparam N variable number
 * @param f jet
 * @param c scalar
 * @return Jet<Scalar, N> f - c
 */
template <typename Scalar, int N>
Jet<Scalar, N> operator-(Jet<Scalar, N> const& f, Scalar c)
{
    Jet<Scalar, N> r;
    r.a = f.a - c;
    r.v = f.v;
    return r;
}

/**
 * @brief f - g
 *
 * @tparam N variable number
 * @param f jet
 * @param g jet
 * @return Jet<Scalar, N> f - g
 */
template <typename Scalar, int N>
Jet<Scalar, N> operator-(Jet<Scalar, N> const& f, Jet<Scalar, N> const& g)
{
    Jet<Scalar, N> r;
    r.a = f.a - g.a;
    for (size_t i = 0U; i < N; ++i)
    {
        r.v[i] = f.v[i] - g.v[i];
    }
    return r;
}

/**
 * @brief c * f
 *
 * @tparam N variable number
 * @param c scalar
 * @param f jet
 * @return Jet<Scalar, N> c * f
 */
template <typename Scalar, int N>
Jet<Scalar, N> operator*(Scalar c, Jet<Scalar, N> const& f)
{
    Jet<Scalar, N> r;
    r.a = c * f.a;
    for (size_t i = 0U; i < N; ++i)
    {
        r.v[i] = c * f.v[i];
    }
    return r;
}

/**
 * @brief f * c
 *
 * @tparam N variable number
 * @param f jet
 * @param c scalar
 * @return Jet<Scalar, N> f * c
 */
template <typename Scalar, int N>
Jet<Scalar, N> operator*(Jet<Scalar, N> const& f, Scalar c)
{
    Jet<Scalar, N> r;
    r.a = f.a * c;
    for (size_t i = 0U; i < N; ++i)
    {
        r.v[i] = f.v[i] * c;
    }
    return r;
}

/**
 * @brief f * g
 *
 * @tparam N variable number
 * @param f jet
 * @param g jet
 * @return Jet<Scalar, N> f * g
 */
template <typename Scalar, int N>
Jet<Scalar, N> operator*(Jet<Scalar, N> const& f, Jet<Scalar, N> const& g)
{
    Jet<Scalar, N> r;
    r.a = f.a * g.a;
    for (size_t i = 0U; i < N; ++i)
    {
        r.v[i] = f.a * g.v[i] + g.a * f.v[i];
    }
    return r;
}

/**
 * @brief c / f
 *
 * @tparam N variable number
 * @param c scalar
 * @param f jet
 * @return Jet<Scalar, N> c / f
 */
template <typename Scalar, int N>
Jet<Scalar, N> operator/(Scalar c, Jet<Scalar, N> const& f)
{
    Jet<Scalar, N> r;
    r.a = c / f.a;
    for (size_t i = 0U; i < N; ++i)
    {
        r.v[i] = -c * f.v[i] / (f.a * f.a);
    }
    return r;
}

/**
 * @brief f / c
 *
 * @tparam N variable number
 * @param f jet
 * @param c scalar
 * @return Jet<Scalar, N> f / c
 */
template <typename Scalar, int N>
Jet<Scalar, N> operator/(Jet<Scalar, N> const& f, Scalar c)
{
    Jet<Scalar, N> r;
    r.a = f.a / c;
    for (size_t i = 0U; i < N; ++i)
    {
        r.v[i] = f.v[i] / c;
    }
    return r;
}

/**
 * @brief f / g
 *
 * @tparam N variable number
 * @param f jet
 * @param g jet
 * @return Jet<Scalar, N> f / g
 */
template <typename Scalar, int N>
Jet<Scalar, N> operator/(Jet<Scalar, N> const& f, Jet<Scalar, N> const& g)
{
    Jet<Scalar, N> r;
    r.a = f.a / g.a;
    for (size_t i = 0U; i < N; ++i)
    {
        r.v[i] = f.v[i] / g.a - f.a * g.v[i] / (g.a * g.a);
    }
    return r;
}

/**
 * @brief sin(f)
 *
 * @tparam N variable number
 * @param f jet
 * @return Jet<Scalar, N> sin(f)
 */
template <typename Scalar, int N>
Jet<Scalar, N> sin(Jet<Scalar, N> const& f)
{
    Jet<Scalar, N> r;
    r.a = sinf(f.a);
    for (size_t i = 0U; i < N; ++i)
    {
        r.v[i] = cosf(f.a) * f.v[i];
    }
    return r;
}

/**
 * @brief cos(f)
 *
 * @tparam N variable number
 * @param f jet
 * @return Jet<Scalar, N> cos(f)
 */
template <typename Scalar, int N>
Jet<Scalar, N> cos(Jet<Scalar, N> const& f)
{
    Jet<Scalar, N> r;
    r.a = cosf(f.a);
    for (size_t i = 0U; i < N; ++i)
    {
        r.v[i] = -sinf(f.a) * f.v[i];
    }
    return r;
}

/**
 * @brief sqrt(f)
 *
 * @tparam N variable number
 * @param f jet
 * @return Jet<Scalar, N> sqrt(f)
 */
template <typename Scalar, int N>
Jet<Scalar, N> sqrt(Jet<Scalar, N> const& f)
{
    Jet<Scalar, N> r;
    r.a = sqrtf(f.a);
    for (size_t i = 0U; i < N; ++i)
    {
        r.v[i] = static_cast<Scalar>(0.5) / sqrtf(f.a) * f.v[i];
    }
    return r;
}

/**
 * @brief atan(f)
 *
 * @tparam N variable number
 * @param f jet
 * @return Jet<Scalar, N> atan(f)
 */
template <typename Scalar, int N>
Jet<Scalar, N> atan(Jet<Scalar, N> const& f)
{
    Jet<Scalar, N> r;
    r.a = atanf(f.a);
    for (size_t i = 0U; i < N; ++i)
    {
        r.v[i] = f.v[i] / (static_cast<Scalar>(1.0) + f.a * f.a);
    }
    return r;
}

template <int N>
using Jetf = Jet<float32_t, N>;

template <int N>
using Jetd = Jet<float64_t, N>;

/**
 * @}
 */
}  // namespace perception
}  // namespace holo

#endif
