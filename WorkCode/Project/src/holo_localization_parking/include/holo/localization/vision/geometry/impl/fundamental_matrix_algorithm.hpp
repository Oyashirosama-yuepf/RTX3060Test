/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file fundamental_matrix_algorithm.cpp
 * @brief implementation of fundamental matrix algorightm
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "2019-12-23"
 */
#include <glog/logging.h>
#include <holo/numerics/eigen_solver.h>

namespace holo
{
namespace localization
{
namespace vision
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
FundamentalMatrix8PointsT<T>::FundamentalMatrix8PointsT() noexcept
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
FundamentalMatrix8PointsT<T>::~FundamentalMatrix8PointsT() noexcept
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool_t FundamentalMatrix8PointsT<T>::operator()(const std::vector<std::pair<Point2, Point2> >& pairs,
                                                Matrix3&                                       model) const noexcept
{
    if (static_cast<uint16_t>(pairs.size()) < 8u)
    {
        LOG(ERROR) << "FundamentalMatrix8PointsT---The given point pairs #" << pairs.size() << " is less than 8";
        return false;
    }

    const uint16_t points_size = static_cast<uint16_t>(pairs.size());
    /// @Step1. compute local center of left and right points
    Vector2              left_center(0.0f, 0.0f), right_center(0.0f, 0.0f);
    std::vector<Vector2> left_points(points_size), right_points(points_size);

    for (uint16_t i = 0u; i < points_size; i++)
    {
        left_points.at(i) = pairs.at(i).first.ToVector();
        left_center += left_points.at(i);
        right_points.at(i) = pairs.at(i).second.ToVector();
        right_center += right_points.at(i);
    }

    left_center /= static_cast<Scalar>(points_size);
    right_center /= static_cast<Scalar>(points_size);

    /// @Step2. compute mean distance from each point to local center
    const Scalar left_mean_distance  = computeMeanDistance(left_points, left_center);
    const Scalar right_mean_distance = computeMeanDistance(right_points, right_center);

    if (left_mean_distance < Epsilon::value || right_mean_distance < Epsilon::value)
    {
        LOG(INFO) << "FundamentalMatrix8PointsT---Wrong mean distance!";
        return false;
    }

    /// @Step3. compute scale parameter to normalize points set
    const Scalar left_scale  = std::sqrt(2.0f) / left_mean_distance;
    const Scalar right_scale = std::sqrt(2.0f) / right_mean_distance;

    /// @Step4. de-mean and normalize
    left_points  = deMeanAndNormalization(left_points, left_center, left_scale);
    right_points = deMeanAndNormalization(right_points, right_center, right_scale);

    /// @Step5. construct matrix A and solve fundamental matrix
    const MatrixX A = constructMatrixA(left_points, right_points);
    model           = solveFundamentalMatrix(A, left_center, right_center, left_scale, right_scale);
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
typename FundamentalMatrix8PointsT<T>::Scalar
FundamentalMatrix8PointsT<T>::computeMeanDistance(const std::vector<Vector2>& points, const Vector2& center) const
    noexcept
{
    Scalar distance = 0.0f;

    for (uint16_t i = 0u; i < static_cast<uint16_t>(points.size()); i++)
    {
        distance += (points.at(i) - center).GetNorm();
    }

    return distance / static_cast<Scalar>(points.size());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
std::vector<typename FundamentalMatrix8PointsT<T>::Vector2> FundamentalMatrix8PointsT<T>::deMeanAndNormalization(
    const std::vector<Vector2>& points, const Vector2& center, const Scalar scale) const noexcept
{
    std::vector<Vector2> new_points;
    new_points.reserve(points.size());

    for (uint16_t i = 0u; i < static_cast<uint16_t>(points.size()); i++)
    {
        new_points.emplace_back((points.at(i) - center) * scale);
    }

    return new_points;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
typename FundamentalMatrix8PointsT<T>::MatrixX FundamentalMatrix8PointsT<T>::constructMatrixA(
    const std::vector<Vector2>& left_points, const std::vector<Vector2>& right_points) const noexcept
{
    MatrixX A(9u, 9u);
    A.SetZero();

    for (uint16_t i = 0u; i < static_cast<uint16_t>(left_points.size()); i++)
    {
        /**
         * F=[f00 f01 f02
         *    f10 f11 f12
         *    f20 f21 f22]
         * vF=[f00 f10 f20 f01 f11 f21 f02 f12 f22]^T
         * t * vF = [l.transpose() 1.0] * F * [r ; 1.0]
         */
        const Vector2& l = left_points.at(i);
        const Vector2& r = right_points.at(i);
        Vector9        t;
        t(0u) = l(0u) * r(0u);
        t(1u) = l(1u) * r(0u);
        t(2u) = r(0u);
        t(3u) = l(0u) * r(1u);
        t(4u) = l(1u) * r(1u);
        t(5u) = r(1u);
        t(6u) = l(0u);
        t(7u) = l(1u);
        t(8u) = 1.0f;
        for (uint8_t row = 0u; row < 9u; row++)
        {
            for (uint8_t col = 0u; col < 9u; col++)
            {
                A(row, col) += t(row) * t(col);
            }
        }
    }

    return A;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
typename FundamentalMatrix8PointsT<T>::Matrix3
FundamentalMatrix8PointsT<T>::solveFundamentalMatrix(const MatrixX& A, const Vector2& left_center,
                                                     const Vector2& right_center, const Scalar left_scale,
                                                     const Scalar right_scale) const noexcept
{
    MatrixX AA(A);
    MatrixX U(9u, 9u), V(9u, 9u);
    VectorX S(9u);
    holo::eigen_solver::SVD(AA, U, S, V, 0x10);  ///< compute full V matrix
    typename MatrixX::Base result(3u, 3u, &(V(0u, 8u)), 9u);
    MatrixX                temp_F = result;
    MatrixX                UF, VF;
    VectorX                SF;
    holo::eigen_solver::SVD(temp_F, UF, SF, VF, 0x04 | 0x10);
    SF(2u) = 0.0f;
    temp_F = UF * SF.AsDiagonal() * VF.Transpose();
    Matrix3 F;
    std::memcpy((uint8_t*)(F.GetData()), (uint8_t*)(temp_F.GetData()), temp_F.GetSize() * sizeof(Scalar));

    Matrix3 T_l = Matrix3::Identity();
    T_l(0u, 0u) = left_scale;
    T_l(0u, 2u) = -left_center(0u) * left_scale;
    T_l(1u, 1u) = left_scale;
    T_l(1u, 2u) = -left_center(1u) * left_scale;

    Matrix3 T_r = Matrix3::Identity();
    T_r(0u, 0u) = right_scale;
    T_r(0u, 2u) = -right_center(0u) * right_scale;
    T_r(1u, 1u) = right_scale;
    T_r(1u, 2u) = -right_center(1u) * right_scale;
    F           = T_l.Transpose() * F * T_r;

    if (std::fabs(F(2u, 2u)) > Epsilon::value)
    {
        F /= F(2u, 2u);
    }

    return F;
}
}  // namespace vision
}  // namespace localization
}  // namespace holo
