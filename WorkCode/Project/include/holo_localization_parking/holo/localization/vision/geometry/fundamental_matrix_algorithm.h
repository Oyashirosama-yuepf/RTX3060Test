/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file fundamental_matrix_algorithm.h
 * @brief this file defines algorithms to compute fundamental matrix
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @ref Zhengyou Zhang's reprot "Determining the Epipolar Geometry and its Uncertainty: A Review"
 * @date "2019-07-23"
 */

#ifndef HOLO_LOCALIZATION_VISION_GEOMETRY_FUNDAMENTAL_MATRIX_ALGORITHM_H_
#define HOLO_LOCALIZATION_VISION_GEOMETRY_FUNDAMENTAL_MATRIX_ALGORITHM_H_

#include <cmath>
#include <vector>

#include <holo/core/epsilon.h>
#include <holo/geometry/point2.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>

namespace holo
{
namespace localization
{
namespace vision
{
/**
 * @addtogroup geometry
 * @{
 *
 */
/**
 * @TODO add 7 points algorithm if need lishuaijie@holomatic.com
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief This class aims to compute fundamental matix with 8 points
 */
template <typename T>
class FundamentalMatrix8PointsT
{
public:
    using Scalar  = T;
    using Point2  = Point2T<Scalar>;
    using Vector2 = Vector2T<Scalar>;
    using Vector9 = Vector9T<Scalar>;
    using VectorX = VectorXT<Scalar>;
    using Matrix3 = Matrix3T<Scalar>;
    using Matrix9 = Matrix9T<Scalar>;
    using MatrixX = MatrixXT<Scalar>;
    using Epsilon = EpsilonT<Scalar>;

    /**
     * @brief constructor
     */
    FundamentalMatrix8PointsT() noexcept;

    /**
     * @brief destructor
     */
    ~FundamentalMatrix8PointsT() noexcept;

    /**
     * @brief compute fundamental matrix with given point pairs
     * @param[in] pairs point pairs from left and right image in pixel unit
     *            left image point: pair.first
     *            right image point: pair.second
     * @param[out] models fundamental matrix computed from the algorithm
     * @return true -> success false->failure
     */
    bool_t operator()(const std::vector<std::pair<Point2, Point2> >& pairs, Matrix3& model) const noexcept;

private:
    /**
     * @brief compute mean distance of the point set
     * @param[in] points point set
     * @param[in] center center of the point set
     * @return mean distance from the point set to the center
     */
    Scalar computeMeanDistance(const std::vector<Vector2>& points, const Vector2& center) const noexcept;

    /**
     * @brief de-mean and normalization
     * @param[in] points point set
     * @param[in] center center of the point set
     * @param[in] scale scale of the point set
     * @return points after de-mean and normalization
     */
    std::vector<Vector2> deMeanAndNormalization(const std::vector<Vector2>& points, const Vector2& center,
                                                const Scalar scale) const noexcept;

    /**
     * @brief construct Matrix A to solve Ax=0
     * @param[in] left_points points from left image
     * @param[in] right_points points from right image
     * @return Matrix A
     */
    MatrixX constructMatrixA(const std::vector<Vector2>& left_points, const std::vector<Vector2>& right_points) const
        noexcept;

    /**
     * @brief solve F by Ax = 0
     * @param[in] A matrix A
     * @param[in] left_center center of left points
     * @param[in] right_center center of right points
     * @param[in] left_scale scale of left points used to recover F from de-mean and normalized points
     * @param[in] right_scale scale of right points used to recover F from de-mean and normalized points
     * @return final fundamental matrix
     */
    Matrix3 solveFundamentalMatrix(const MatrixX& A, const Vector2& left_center, const Vector2& right_center,
                                   const Scalar left_scale, const Scalar right_scale) const noexcept;

};  // FundamentalMatrix8PointsT

/**
 * @}
 *
 */
}  // namespace vision
}  // namespace localization
}  // namespace holo
#endif  // HOLO_LOCALIZATION_VISION_GEOMETRY_FUNDAMENTAL_MATRIX_ALGORITHM_H_
