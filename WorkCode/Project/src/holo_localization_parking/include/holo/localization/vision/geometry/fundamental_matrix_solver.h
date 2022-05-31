/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file fundamental_matrix_solver.h
 * @brief this file defines fundamental matrix solver class
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "2019-07-23"
 */

#ifndef HOLO_LOCALIZATION_VISION_GEOMETRY_FUNDAMENTAL_MATRIX_SOLVER_H_
#define HOLO_LOCALIZATION_VISION_GEOMETRY_FUNDAMENTAL_MATRIX_SOLVER_H_

#include <holo/localization/vision/geometry/fundamental_matrix_algorithm.h>

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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief this class is used to manage different fundamenmtal matrix algorithm
 */
template <typename T>
class FundamentalMatrixSolverT
{
public:
    using Scalar                   = T;
    using Point2                   = Point2T<Scalar>;
    using Matrix3                  = Matrix3T<Scalar>;
    using FundamentalMatrix8Points = FundamentalMatrix8PointsT<Scalar>;

    /**
     * @brief define method type
     */
    enum class MethodType
    {
        FM_8POINT,
    };

    /**
     * @brief constructor
     *
     * @param[in] method_type method type used to compute fundamental matrix
     */
    FundamentalMatrixSolverT(const MethodType& method_type = MethodType::FM_8POINT) noexcept;

    /**
     * @brief destructor
     */
    ~FundamentalMatrixSolverT() noexcept;

    /**
     * @brief compute fundamental matrix with given point pairs
     *
     * @param[in] pairs corresponding points in two images
     * @param[out] models fundamental matrix result, there might be several result
     * @return bool_t true if the result is valid, otherwise false
     * @throw when the method is invalid
     */
    bool_t ComputeModels(const std::vector<std::pair<Point2, Point2> >& pairs, std::vector<Matrix3>& models) const;

    /**
     * @brief get method type used to compute fundamental matrix
     *
     * @return MethodType method type
     */
    MethodType GetMethodType() const noexcept;

private:
    /**
     * @brief method type
     */
    MethodType method_type_;
};  // FundamentalMatrixSolverT

/**
 * @}
 *
 */
}  // namespace vision
}  // namespace localization
}  // namespace holo
#endif  // HOLO_LOCALIZATION_VISION_GEOMETRY_FUNDAMENTAL_MATRIX_SOLVER_H_
