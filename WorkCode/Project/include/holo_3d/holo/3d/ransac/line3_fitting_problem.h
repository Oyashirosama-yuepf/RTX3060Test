/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file line3_fitting_problem.h
 * @brief This header file defines RansacLine3FittingProblem class
 * @author cuijiashuo@holomatic.com (Jiashuo Cui)
 * @date 2022-04-06
 */

#ifndef HOLO_3D_RANSAC_LINE3_FITTING_PROBLEM_H_
#define HOLO_3D_RANSAC_LINE3_FITTING_PROBLEM_H_

#include <holo/3d/common/point_types.h>
#include <holo/geometry/line_segment3.h>
#include <holo/log/hololog.h>
#include <holo/numerics/matrix.h>
#include <holo/probability/ransac/ransac_problem.h>
#include <holo/probability/ransac/ransac_problem_data_container_adapter.h>

namespace holo
{
namespace pointcloud
{
/**
 * @brief RansacLine3FittingProblem defines a RANSAC problem for fitting a 3D line segmentation
 *
 * @details The model coefficients are defined as:
 *          - point_on_line.x : the X coordinate of a point on the line
 *          - point_on_line.y : the Y coordinate of a point on the line
 *          - point_on_line.z : the Z coordinate of a point on the line
 *          - line_direction.x : the X coordinate of a line's direction
 *          - line_direction.y : the Y coordinate of a line's direction
 *          - line_direction.z : the Z coordinate of a line's direction
 * @tparam T Data type
 */
template <typename T>
class RansacLine3FittingProblem : public holo::RansacProblemT<holo::geometry::LineSegment3T<T>>
{
public:
    using Scalar       = T;
    using Point3Type   = holo::geometry::Point3T<Scalar>;
    using AdapeterType = holo::RansacProblemDataContainerAdapterBaseT<Point3Type>;
    using Base         = holo::RansacProblemT<holo::geometry::LineSegment3T<T>>;
    using ModelType    = typename Base::ModelType;

    /**
     * @brief Disable default constructor.
     */
    RansacLine3FittingProblem() = delete;

    /**
     * @brief Disable copy constructor.
     */
    RansacLine3FittingProblem(RansacLine3FittingProblem const&) = delete;

    /**
     * @brief Disable assigment operator.
     */
    RansacLine3FittingProblem& operator=(RansacLine3FittingProblem const&) = delete;

    /**
     * @brief Advanced constructor for RansacLine3FittingProblem class.
     *
     * @param[in] adapter Data container adapter.
     * @param[in] random If true set the random seed to the current time, else set to 12345 (default: false)
     */
    RansacLine3FittingProblem(AdapeterType const& adapter, bool_t const random = true)
      : Base(adapter.GetSampleSize(), random), adapter_(adapter)
    {
        LOG(INFO) << "RansacLine3FittingProblem::RansacLine3FittingProblem() --- Call advanced constructor!";
    }

    /**
     * @brief Destructor for RansacLine3FittingProblem class.
     */
    virtual ~RansacLine3FittingProblem() noexcept = default;

    /**
     * @brief Compute a model from a set of samples. Needs implementation in the child-class.
     *
     * @param[in] indices The indices of the samples we use for the hypothesis.
     * @param[out] out_model The computed model.
     */
    virtual bool_t ComputeModel(std::vector<uint64_t> const& indices, ModelType& model) const override;

    /**
     * @brief Refine the model over a given set (inliers).
     *
     * @details Needs implementation in the child-class.
     * @param[in] inliers The indices of the inlier samples supporting the model.
     * @param[in] model The initial guess for the model.
     * @return optimized_model The resultant refined model.
     */
    virtual ModelType OptimizeModel(std::vector<uint64_t> const& inliers, ModelType const& model) const override;

    /**
     * @brief Compute the distances of all samples whith respect to given model.
     *        Needs implementation in the child-class.
     *
     * @param[in] model The model hypothesis.
     * @param[in] index The index of the samples of which we compute distances.
     * @return scores The resultant distances of the selected samples. Low distances mean a good fit.
     */
    virtual float64_t GetDistanceToModel(ModelType const& model, uint64_t const index) const override;

    /**
     * @brief Check if a sample of indices results for model generation is degenerate.
     *
     * @param[in] samples The indices of the samples that we attempt to use for model generation.
     * @return bool_t, true if samples is good.
     */
    virtual bool_t IsSampleGood(std::vector<uint64_t> const& sample) const override;

    /**
     * @brief Get the number of samples needed for a hypothesis generation.
     *
     * @return The number of samples needed for hypothesis generation.
     */
    virtual uint64_t GetRequiredSampleSize() const override
    {
        return required_sample_size_;
    }

private:
    /**
     * @brief Data container adapter
     */
    AdapeterType const& adapter_;

    /**
     * @brief The least required sample size for fitting model.
     */
    static const uint64_t required_sample_size_ = 2u;
};
}  // namespace pointcloud
}  // namespace holo

#endif  // HOLO_3D_RANSAC_LINE3_FITTING_PROBLEM_H_