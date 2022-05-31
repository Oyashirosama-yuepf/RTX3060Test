/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file bspline.h
 * @brief This file defines BSpline class
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-3-18
 */

#ifndef HOLO_NUMERICS_BSPLINE_H_
#define HOLO_NUMERICS_BSPLINE_H_

#include <holo/core/epsilon.h>
#include <holo/core/exception.h>
#include <holo/core/types.h>
#include <holo/numerics/exception.h>
#include <holo/numerics/matrix.h>

#include <vector>

namespace holo
{
namespace numerics
{
/**
 * @brief A B-Spline curve.
 * @details A BSpline curve is defined as
 * @f$
 * \begin{bmatrix} 1 & u & u^2 & \cdots & u^{k-1} \end{bmatrix}
 * \bm{M}^k(i)
 * \begin{bmatrix} \bm{V}_{i-k+1} \\ \bm{V}_{i-k+2} \\ \vdots \\ \bm{V}_{i} \end{bmatrix}
 * @f$
 * where @f$u=\frac{(t-t_i)}{t_{i+1}-t_i},u \in [0,1)@f$. @f$\bm{M}^k(i)@f$ is referred to as the ith basis matrix of
 * the B-spline basis functions of degree k - 1. @f$\bm{V}@f$ is control point vector.
 *
 * basis matrix is calculated with following formular:
 * @f{eqnarray*}{
 * \bm{M}^k(i)=\left\{
 *     \begin{array}{rcl}
 *         \bm{M_a}^{k-1}(i) \times \bm{A}^{k-1} + \bm{M_b}^{k-1}(i) \times \bm{B}^{k-1} & & {k > 1}\\
 *         \begin{bmatrix} 1 \end{bmatrix} & & {k = 1}
 *     \end{array} \right.
 * @f}
 *
 * where
 *
 * @f{eqnarray*}{
 * \bm{M_a}^{k-1}(i) &=& \begin{bmatrix} \bm{M}^{k-1}(i) \\ \bm{0} \end{bmatrix} \\
 *
 * \bm{A}^{k-1} &=& \begin{bmatrix}
 *                  1-d_{0,i-k+2} & d_{0,i-k+2}   &             &           & \bm{0}  \\
 *                                & 1-d_{0,i-k+3} & d_{0,i-k+3} &           &         \\
 *                                &               & \ddots      & \ddots    &         \\
 *                  \bm{0}        &               &             & 1-d_{0,i} & d_{0,i} \\
 *                  \end{bmatrix} \\
 *
 * \bm{M_b}^{k-1}(i) &=& \begin{bmatrix} \bm{0} \\ \bm{M}^{k-1}(i) \end{bmatrix} \\
 *
 * \bm{B}^{k-1} &=& \begin{bmatrix}
 *                  -d_{1,i-k+2} & d_{1,i-k+2}  &             &          & \bm{0}  \\
 *                               & -d_{1,i-k+3} & d_{1,i-k+3} &          &         \\
 *                               &              & \ddots      & \ddots   &         \\
 *                  \bm{0}       &              &             & -d_{1,i} & d_{1,i} \\
 *                  \end{bmatrix} \\
 *
 * d_{0,j} &=& \frac{t_i - t_j}{t_{j+k-1}-t_j} \\
 *
 * d_{1,j} &=& \frac{t_{i+1} - t_i}{t_{j+k-1}-t_j}
 *
 * @f}
 *
 * @tparam T Scalar type
 * @tparam P Point type. This type shall satisfy following restrictions: @n
 * P shall default contructible. And default contructed object @b pt shall satisfy: For any scalar of type T
 * pt * scalar == pt. @n
 * P shall copy constructible. ( pt1(pt2) ) @n
 * P shall support multiplication with scalar of type T. (pt1 * scalar) @n
 * P shall support addition operation. (pt1 + pt2) @n
 * @tparam Degree Degree of this spline
 * @tparam Uniform Whether this spline is uniformed.
 *
 * @ref Qin Kaihuai, General matrix representations for B-splines, The Visual Computer(2000) 16:177-186
 */
template <typename T, typename P, size_t Degree = 3, bool_t Uniform = false>
class BSpline
{
public:
    using ScalarType                = T;
    using PointType                 = P;
    static size_t const DegreeValue = Degree;
    static size_t const OrderValue  = Degree + 1;

    /**
     * @brief Construct with knots and control points.
     * @details Use @b N to denote number of knots, use @b C to denote number of control_points. @b C and @b N shall
     * satisfy: @n N >= 2 * (DegreeValue + 1) @n C = N - DegreeValue - 1
     *
     * @tparam Tn Knot container type.
     * @tparam Tp Control point container type.
     * @param knots Knot container.
     * @param control_points Control point container.
     *
     * @throws holo::exception::BadKnotNumberException if knots.size() != number of control_points + DegreeValue + 1. @n
     * holo::exception::BadKnotOrderException if knots is not in non-decending order. @n
     * holo::exception::BadControlPointNumberException if control_points.size() != number of knots - DegreeValue - 1. @n
     * @exceptsafe Strong
     */
    template <typename Tn = std::vector<ScalarType>, typename Tp = std::vector<PointType>>
    BSpline(Tn&& knots, Tp&& control_points) : basis_matrices_{}, knots_{}, control_points_{}
    {
        SetKnotsControlPoints(std::forward<Tn>(knots), std::forward<Tp>(control_points));
    }

    /**
     * @brief Set knots and control points.
     * @details Use @b N to denote number of knots, use @b C to denote number of control_points. @b C and @b N shall
     * satisfy: @n N >= 2 * (DegreeValue + 1) @n C = N - DegreeValue - 1
     *
     * @tparam Tn Knot container type.
     * @tparam Tp Control point container type.
     * @param knots Knot container.
     * @param control_points Control point container.
     *
     * @throws holo::exception::BadKnotNumberException if knots.size() != number of control_points + DegreeValue + 1. @n
     * holo::exception::BadKnotOrderException if knots is not in non-decending order. @n
     * holo::exception::BadControlPointNumberException if control_points.size() != number of knots - DegreeValue - 1. @n
     * @exceptsafe Strong
     */
    template <typename Tn = std::vector<ScalarType>, typename Tp = std::vector<PointType>>
    void SetKnotsControlPoints(Tn&& knots, Tp&& control_points)
    {
        if (knots.size() < 2 * (DegreeValue + 1))
        {
            throw holo::exception::BadKnotNumberException();
        }
        for (size_t i = 0; i < knots.size() - 1; ++i)
        {
            if (knots[i] > knots[i + 1])
            {
                throw holo::exception::BadKnotOrderException();
            }
        }
        if (control_points.size() != knots.size() - DegreeValue - 1)
        {
            throw holo::exception::BadControlPointNumberException();
        }
        setKnotsControlPoints(std::forward<Tn>(knots), std::forward<Tp>(control_points));
        updateBasisMatrix();
    }

    /**
     * @brief Set knots. Number of knots shall equal to number of control_points + DegreeValue + 1.
     *
     * @tparam Tn Knots container type.
     * @param knots The knots.
     * @throws holo::exception::BadKnotNumberException if knots.size() != number of control_points + DegreeValue + 1. @n
     * holo::exception::BadKnotOrderException if knots is not in non-decending order.
     * @exceptsafe Strong
     */
    template <typename Tn = std::vector<ScalarType>>
    void SetKnots(Tn&& knots)
    {
        if (knots.size() != knots_.size())
        {
            throw holo::exception::BadKnotNumberException();
        }
        for (size_t i = 0; i < knots.size() - 1; ++i)
        {
            if (knots[i] > knots[i + 1])
            {
                throw holo::exception::BadKnotOrderException();
            }
        }
        setKnots(std::forward<Tn>(knots));
        updateBasisMatrix();
    }

    /**
     * @brief Set control points. Number of control points shall equal to number of knots - DegreeValue - 1.
     *
     * @tparam Tp Control point container type.
     * @param control_points The control points.
     * @throws holo::exception::BadControlPointNumberException if control_points.size() != number of knots - DegreeValue
     * - 1.
     * @exceptsafe Strong
     */
    template <typename Tp = std::vector<PointType>>
    void SetControlPoints(Tp&& control_points)
    {
        if (control_points.size() != knots_.size() - DegreeValue - 1)
        {
            throw holo::exception::BadControlPointNumberException();
        }
        setControlPoints(std::forward<Tp>(control_points));
    }

    /**
     * @brief Get knot vector.
     *
     * @return Knot vector.
     */
    std::vector<ScalarType> const& GetKnots() const noexcept
    {
        return knots_;
    }

    /**
     * @brief Get control points.
     *
     * @return Control points.
     */
    std::vector<PointType> const& GetControlPoints() const noexcept
    {
        return control_points_;
    }

    /**
     * @brief Get BSpline parameter range.
     *
     * @return std::pair with start value as first element, end value as second element.
     */
    std::pair<ScalarType, ScalarType> GetParamRange() const noexcept
    {
        return std::pair<ScalarType, ScalarType>(knots_[DegreeValue], knots_[knots_.size() - DegreeValue - 1]);
    }

    /**
     * @brief Get BSpline value at param
     *
     * @param param The BSpline parameter.
     *
     * @return PointType value.
     */
    PointType GetValue(ScalarType param) const
    {
        return GetDerivation<0>(param);
    }

    /**
     * @brief Get "DerivationOrder"th derivation value at param
     *
     * @tparam DerivationOrder Order of derivation.
     * @param param The BSpline parameter.
     *
     * @return PointType value.
     */
    template <size_t DerivationOrder>
    PointType GetDerivation(ScalarType param) const
    {
        if (param < *(knots_.begin() + DegreeValue) || param > *(knots_.end() - DegreeValue - 1))
        {
            throw holo::exception::OutOfRangeException("");
        }
        size_t     slot;
        ScalarType u;
        ScalarType coefficients[DegreeValue + 1] = {};  // coefficients for each control points.

        getSlotAndU(param, slot, u);

        computeCoefficientsToParam<DerivationOrder>(u, slot, coefficients);

        PointType pt;
        for (size_t i = 0; i <= DegreeValue; ++i)
        {
            pt = pt + control_points_[slot - DegreeValue + i] * coefficients[i];
        }
        return pt;
    }

protected:
    using BasisMatrixType = MatrixT<ScalarType, Degree + 1, Degree + 1>;

    /**
     * @brief Set knots and control points
     *
     * @tparam Tn Knots container type.
     * @tparam Tp Control points container type.
     * @param knots
     * @param control_points
     *
     */
    template <typename Tn, typename Tp>
    void setKnotsControlPoints(Tn&& knots, Tp&& control_points) noexcept
    {
        setKnots(std::forward<Tn>(knots));
        setControlPoints(std::forward<Tp>(control_points));
    }

    /**
     * @brief Set knots.
     *
     * @tparam Tn Knots container type.
     * @param knots Knots container.
     *
     */
    template <typename Tn,
              typename std::enable_if<std::is_same<Tn, std::vector<ScalarType>>::value, void>::type* = nullptr>
    void setKnots(Tn&& knots) noexcept
    {
        knots_ = std::forward<Tn>(knots);
    }

    /**
     * @brief Set knots.
     *
     * @tparam Tn Knots container type.
     * @param knots Knots container.
     *
     */
    template <typename Tn,
              typename std::enable_if<!std::is_same<Tn, std::vector<ScalarType>>::value, void>::type* = nullptr>
    void setKnots(Tn&& knots) noexcept
    {
        knots_.clear();
        for (auto const& knot : knots)
        {
            knots_.push_back(knot);
        }
    }

    /**
     * @brief Set control points
     *
     * @tparam Tp Control points container type.
     * @param control_points
     *
     */
    template <typename Tp,
              typename std::enable_if<std::is_same<Tp, std::vector<PointType>>::value, void>::type* = nullptr>
    void setControlPoints(Tp&& control_points) noexcept
    {
        control_points_ = std::forward<Tp>(control_points);
    }

    /**
     * @brief Set control points
     *
     * @tparam Tp Control points container type.
     * @param control_points
     *
     */
    template <typename Tp,
              typename std::enable_if<!std::is_same<Tp, std::vector<PointType>>::value, void>::type* = nullptr>
    void setControlPoints(Tp&& control_points) noexcept
    {
        control_points_.clear();
        for (auto const& pt : control_points)
        {
            control_points_.push_back(pt);
        }
    }

    /**
     * @brief Update internal basis matrix.
     */
    void updateBasisMatrix() noexcept
    {
        /* num_curves == num_control_points - degree == num_knots - degree - 1 - degree */
        size_t curves_num = control_points_.size() - DegreeValue;
        /* Initialize basis matrix for each curve */
        for (size_t i = 0; i < (basis_matrices_.size() > curves_num ? curves_num : basis_matrices_.size()); ++i)
        {
            /* If basis matrix already allocated. Set all elements in matrix to zero */
            basis_matrices_[i].SetZero();
        }
        for (size_t i = basis_matrices_.size(); i < curves_num; ++i)
        {
            /* Allocate basis matrix for curves */
            basis_matrices_.emplace_back();
        }

        /* Compute basis matrix for each curve */
        for (size_t i = 0; i < curves_num; ++i)
        {
            computeM_i(i + Degree, basis_matrices_[i]);
        }
    }

    /**
     * @brief Compute coefficients with respect to param.
     *
     * @tparam DerivationOrder derivative order.
     * @param[in] u Normalized param.
     * @param[in] slot slot index.
     * @param[out] coefficients The coefficients result.
     */
    template <size_t DerivationOrder>
    void computeCoefficientsToParam(ScalarType u, ScalarType slot, ScalarType (&coefficients)[DegreeValue + 1]) const
        noexcept
    {
        auto const& basis = getBasisMatrix(slot);  // basis matrix for this knot slot.

        computeCoefficientsToU<DerivationOrder, DegreeValue>(basis, u, coefficients);

        if (DerivationOrder > 0)
        {
            ScalarType s      = static_cast<ScalarType>(1) / (knots_[slot + 1] - knots_[slot]);
            ScalarType dparam = s;
            for (size_t i = 1U; i < DerivationOrder; ++i)
            {
                dparam *= s;
            }

            for (size_t i = 0U; i < DegreeValue + 1; ++i)
            {
                coefficients[i] *= dparam;
            }
        }
    }

    /**
     * @brief Get slot index which param lays in and its normalized param u.
     *
     * @param param Bspline param.
     * @param slot Slot index.
     * @param u Normalized param.
     */
    void getSlotAndU(ScalarType param, size_t& slot, ScalarType& u) const noexcept
    {
        for (slot = DegreeValue; slot < knots_.size() - DegreeValue - 1; ++slot)
        {
            if (param < knots_[slot + 1])
            {
                break;
            }
        }
        if (slot >= knots_.size() - DegreeValue - 1)
        {
            slot = knots_.size() - DegreeValue - 2;
        }
        u = param - knots_[slot];
        if (u > ScalarEqualT<ScalarType>().GetEpsilonValue())
        {
            // in case knots_[slot + 1] == knots_[slot]
            u /= (knots_[slot + 1] - knots_[slot]);
        }
    }

    /**
     * @brief Get basis matrix for knot slot
     *
     * @param slot The knot slot
     *
     * @return basis matrix of this slot.
     */
    BasisMatrixType const& getBasisMatrix(size_t slot) const noexcept
    {
        return basis_matrices_[slot - DegreeValue];
    }

private:
    /**
     * @brief Get "DerivationOrder"th derivative for @f$u^{exponent}@f$
     *
     * @tparam DerivationOrder derivation order
     * @tparam Exponent exponent
     *
     * @return derivation coefficient
     */
    template <size_t DerivationOrder, size_t Exponent,
              typename std::enable_if<((DerivationOrder <= Exponent) && (DerivationOrder > 0)), void>::type* = nullptr>
    constexpr size_t derivationCoefficient() const noexcept
    {
        return Exponent * derivationCoefficient<DerivationOrder - 1, Exponent - 1>();
    }

    template <size_t DerivationOrder, size_t Exponent,
              typename std::enable_if<((DerivationOrder <= Exponent) && (DerivationOrder == 0)), void>::type* = nullptr>
    constexpr size_t derivationCoefficient() const noexcept
    {
        return 1U;
    }

    template <size_t DerivationOrder, size_t Exponent,
              typename std::enable_if<(DerivationOrder > Exponent), void>::type* = nullptr>
    constexpr size_t derivationCoefficient() const noexcept
    {
        return 0U;
    }

    /* Helper functions to compute coefficients for each control points */
    template <size_t DerivationOrder, size_t Exponent,
              typename std::enable_if<(DerivationOrder < Exponent) && (Exponent <= DegreeValue), void>::type* = nullptr>
    void computeCoefficientsToU(BasisMatrixType const& basis, ScalarType u,
                                ScalarType (&coefficients)[DegreeValue + 1U]) const noexcept
    {
        for (size_t i = 0U; i < DegreeValue + 1U; ++i)
        {
            coefficients[i] =
                coefficients[i] * u + basis(Exponent, i) * derivationCoefficient<DerivationOrder, Exponent>();
        }
        computeCoefficientsToU<DerivationOrder, Exponent - 1>(basis, u, coefficients);
    }

    template <
        size_t DerivationOrder, size_t Exponent,
        typename std::enable_if<(DerivationOrder == Exponent) && (Exponent <= DegreeValue), void>::type* = nullptr>
    void computeCoefficientsToU(BasisMatrixType const& basis, ScalarType u,
                                ScalarType (&coefficients)[DegreeValue + 1]) const noexcept
    {
        for (size_t i = 0U; i < DegreeValue + 1U; ++i)
        {
            coefficients[i] =
                coefficients[i] * u + basis(Exponent, i) * derivationCoefficient<DerivationOrder, Exponent>();
        }
    }

    /**
     * @brief Compute basis matrix for ith knots slot [knots_[i], knots_[i + 1]).
     *
     * @param[in] i slot index.
     * @param[in,out] M_k Input (k-1)th order basis matrix and output kth order basis matrix.
     */
    void computeM_i(size_t i, BasisMatrixType& M_k) noexcept
    {
        BasisMatrixType M_a_k_1               = {};
        BasisMatrixType M_b_k_1               = {};
        ScalarType      A_k_1[DegreeValue][2] = {};
        ScalarType      B_k_1[DegreeValue][2] = {};
        M_k(0, 0)                             = static_cast<ScalarType>(1);
        for (size_t k = 2; k <= DegreeValue + 1; ++k)
        {
            computeM_i_k(M_a_k_1, M_b_k_1, A_k_1, B_k_1, i, k, M_k);
        }
    }

    /**
     * @brief Compute kth order basis matrix for ith knot slot.
     *
     * @param[in,out] M_a_k_1 Temporary matrix type variable to store @f$\bm{M_a}^{k-1}(i)@f$
     * @param[in,out] M_b_k_1 Temporary matrix type variable to store @f$\bm{M_b}^{k-1}(i)@f$
     * @param[in,out] &A_k_1 Temporary 2-dimension array to store @f$\bm{A}^{k-1}@f$
     * @param[in,out] &B_k_1 Temporary 2-dimension array to store @f$\bm{B}^{k-1}@f$
     * @param[in] i knot slot number.
     * @param[in] k @f$k^{th}@f$ order. k should greater equal to 2.
     * @param[in,out] M_k input @f$ \bm{M}^{k-1}(i) @f$ value and output @f$ \bm{M}^k(i) @f$ value.
     */
    void computeM_i_k(BasisMatrixType& M_a_k_1, BasisMatrixType&  M_b_k_1, ScalarType (&A_k_1)[DegreeValue][2],
                      ScalarType (&B_k_1)[DegreeValue][2], size_t i, size_t k, BasisMatrixType& M_k) const noexcept
    {
        /* Initialize M_a_k_1 and M_b_k_1 */
        for (size_t r = 0u; r < k - 1; ++r)
        {
            for (size_t c = 0u; c < k - 1; ++c)
            {
                M_a_k_1(r, c)     = M_k(r, c);
                M_b_k_1(r + 1, c) = M_k(r, c);
                M_k(r, c)         = 0;
            }
        }

        /* Initialize A_k_1 and B_k_1 */
        for (size_t r = 0u; r < k - 1; ++r)
        {
            ScalarType d0 = d0j(i, i - k + 2 + r, k);
            ScalarType d1 = d1j(i, i - k + 2 + r, k);
            A_k_1[r][0]   = 1 - d0;
            A_k_1[r][1]   = d0;
            B_k_1[r][0]   = -d1;
            B_k_1[r][1]   = d1;
        }

        /*
         * Compute M_a_k_1 * A_k_1 + M_b_k_1 * B_k_1
         * Results are stored in M_k
         */

        /*
         * The first column and the last column of toeplitz matrix A_k_1 and B_k_1 are special,
         * only one element are non-zero.
         */
        for (size_t r = 0; r < k; ++r)
        {
            /* compute column 0 */
            M_k(r, 0) = M_a_k_1(r, 0) * A_k_1[0][0] + M_b_k_1(r, 0) * B_k_1[0][0];
            /* compute column k - 1 */
            M_k(r, k - 1) = M_a_k_1(r, k - 2) * A_k_1[k - 2][1] + M_b_k_1(r, k - 2) * B_k_1[k - 2][1];
        }
        /* For the other columns in toeplitz matrix A_k_1 and B_k_1, only two elements are non-zero */
        for (size_t c = 1; c < k - 1; ++c)
        {
            /* compute column 1 to column k - 2 */
            for (size_t r = 0; r < k; ++r)
            {
                M_k(r, c) = M_a_k_1(r, c - 1) * A_k_1[c - 1][1] + M_a_k_1(r, c) * A_k_1[c][0] +
                            M_b_k_1(r, c - 1) * B_k_1[c - 1][1] + M_b_k_1(r, c) * B_k_1[c][0];
            }
        }
    }

    ScalarType d0j(size_t i, size_t j, size_t k) const noexcept
    {
        if (knots_[j + k - 1] - knots_[j] < ScalarEqualT<ScalarType>().GetEpsilonValue())
        {
            return static_cast<ScalarType>(0);
        }
        return (knots_[i] - knots_[j]) / (knots_[j + k - 1] - knots_[j]);
    }

    ScalarType d1j(size_t i, size_t j, size_t k) const noexcept
    {
        if (knots_[j + k - 1] - knots_[j] < ScalarEqualT<ScalarType>().GetEpsilonValue())
        {
            return static_cast<ScalarType>(0);
        }
        return (knots_[i + 1] - knots_[i]) / (knots_[j + k - 1] - knots_[j]);
    }

    std::vector<BasisMatrixType> basis_matrices_;  // bspline basis matrix
    std::vector<ScalarType>      knots_;           // knot vector. size = number control_points + degree + 1
    std::vector<PointType>       control_points_;  // At least degree + 1 control points should be defined.
};

}  // namespace numerics
}  // namespace holo

#endif
