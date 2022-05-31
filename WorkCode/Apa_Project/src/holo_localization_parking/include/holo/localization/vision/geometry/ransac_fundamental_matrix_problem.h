/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ransac_fundamental_matrix_problem.h
 * @brief this file defines ransac fundamental matrix problem
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "2019-07-09"
 */

#ifndef HOLO_LOCALIZATION_VISION_GEOMETRY_RANSAC_FUNDAMENTAL_MATRIX_PROBLEM_H_
#define HOLO_LOCALIZATION_VISION_GEOMETRY_RANSAC_FUNDAMENTAL_MATRIX_PROBLEM_H_

#include <holo/geometry/line2.h>
#include <holo/geometry/point2.h>
#include <holo/localization/vision/geometry/fundamental_matrix_solver.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>
#include <holo/probability/ransac/ransac_problem.h>
#include <holo/probability/ransac/ransac_problem_data_container_adapter.h>

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
/*
 * @biref this class aims to compute fundamental matrix with ransac
 */
template <typename T>
class RansacFundamentalMatrixProblemT : public RansacProblemT<Matrix3T<T> >
{
public:
    using Scalar                  = T;
    using Line2                   = Line2T<Scalar>;
    using Point2                  = Point2T<Scalar>;
    using Vector3                 = Vector3T<Scalar>;
    using Epsilon                 = EpsilonT<Scalar>;
    using FundamentalMatrixSolver = FundamentalMatrixSolverT<Scalar>;
    using MethodType              = typename FundamentalMatrixSolver::MethodType;
    using AdapterType             = RansacProblemDataContainerAdapterStdVectorT<Point2>;
    using Base                    = RansacProblemT<Matrix3T<T> >;
    using typename Base::ModelType;

    /**
     * @brief constructor
     *
     * @param[in] left_hand_side points from left image
     * @param[in] right_hand_side points from right image
     * @param[in] method_type method used to compute fundamental matrix e.g. FM_8POINT
     * @throw when the given left and right hand side data does not equal
     */
    RansacFundamentalMatrixProblemT(const AdapterType& left_hand_side, const AdapterType& right_hand_side,
                                    const MethodType& method_type = MethodType::FM_8POINT,
                                    const bool_t      random_seed = true);

    /**
     * @brief destructor
     */
    ~RansacFundamentalMatrixProblemT();

    /**
     * @brief check whether the sampled data is good to compute fundamental matrix
     * @details the sampled data is seen as good when each 3-points subset of the sampled data is not collinear
     * @param[in] sample sample index in the data container
     * @return true if it is good, otherwise false
     */
    virtual bool_t IsSampleGood(const std::vector<uint64_t>& sample) const override;

    /**
     * @brief number of data required to compute fundamental matrix
     *
     * @return number of sample required which is used to compute fundamental matrix
     */
    virtual uint64_t GetRequiredSampleSize() const override;

    /**
     * @brief compute fundamental matrix with sampled data
     *
     * @param[in] indices sample indices used to compute fundamental matrix
     * @param[in] out_model computed fundamental matrix
     * @return bool_t true if success, false failure
     */
    virtual bool_t ComputeModel(const std::vector<uint64_t>& indices, ModelType& out_model) const override;

    /**
     * @brief evaluate distance from data to epipolar line
     * @details the distance to model: means the maximum value of the distance from image point to the epipolar line
     * obtained by the model in left and right image
     *
     * @param[in] model computed fundamental matrix
     * @param[in] index index in the data container
     * @return distance of the {index}th data to the computed fundamental matrix
     */
    virtual float64_t GetDistanceToModel(const ModelType& model, const uint64_t index) const override;

    /**
     * @brief Refine fundamental matrix over a given set (inliers).
     *
     * @param[in] inliers The indices of the inlier samples supporting the model.
     * @param[in] model The initial guess for the model.
     * @return optimized_model The resultant refined model.
     */
    virtual ModelType OptimizeModel(const std::vector<uint64_t>& inliers, const ModelType& model) const override;

protected:
    /**
     * @brief check whether there are collinear points
     */
    bool_t isPointSetCollinear(const std::vector<uint64_t>& sample, const AdapterType& adapter) const;

private:
    /**
     * @brief corresponds from left and right image in pixel unit
     */
    const AdapterType& left_hand_side_;
    const AdapterType& right_hand_side_;

    /**
     * @brief FundamentalMatrixSolver
     */
    const FundamentalMatrixSolver fundamental_matrix_solver_;

    /**
     * @brief required sample data size
     */
    const uint64_t required_sample_size_;

};  // class RansacFundamentalMatrixProblemT

/**
 * @}
 *
 */
}  // namespace vision
}  // namespace localization
}  // namespace holo
#endif  // HOLO_LOCALIZATION_VISION_GEOMETRY_RANSAC_FUNDAMENTAL_MATRIX_PROBLEM_H_
