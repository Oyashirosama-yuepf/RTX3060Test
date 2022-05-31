/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ransac_line2_fitting_problem.h
 * @brief this class represents ransac solving specific fitting line2 problem
 * @author jiaxing.zhao
 * @date 2017-08-2
 */

#ifndef HOLO_PROBABILITY_RANSAC_LINE2_FITTING_PROBLEM_H_
#define HOLO_PROBABILITY_RANSAC_LINE2_FITTING_PROBLEM_H_

#include <holo/geometry/line2.h>
#include <holo/numerics/matrix.h>
#include <holo/probability/ransac/ransac_problem.h>
#include <holo/probability/ransac/ransac_problem_data_container_adapter.h>

namespace holo
{
/**
 * @addtogroup numerics
 * @{
 *
 */

/**
 * @brief ransac line2 fitting problem
 *
 * @tparam T scalar type
 */
template <typename T>
class RansacLine2FittingProblemT : public RansacProblemT<holo::geometry::Line2T<T> >
{
public:
    using Scalar      = T;
    using Point2Type  = holo::geometry::Point2T<Scalar>;
    using Vector3Type = holo::numerics::Vector3T<Scalar>;
    using AdapterType = RansacProblemDataContainerAdapterBaseT<Point2Type>;
    using Base        = RansacProblemT<holo::geometry::Line2T<T> >;
    using typename Base::ModelType;

    /**
     * @brief disable default constructor, copy constructor and assignment operator
     *
     */
    RansacLine2FittingProblemT() = delete;

    RansacLine2FittingProblemT(RansacLine2FittingProblemT const&) = delete;

    RansacLine2FittingProblemT& operator=(RansacLine2FittingProblemT const&) = delete;

    /**
     * @brief Construct a new Ransac Line 2 Fitting Problem T object
     *
     * @param adapter data container adapter
     * @param random_seed random_seed
     */
    RansacLine2FittingProblemT(AdapterType const& adapter, bool_t const random_seed = true);

    /**
     * @brief Destroy the Ransac Line 2 Fitting Problem T object
     *
     */
    virtual ~RansacLine2FittingProblemT() noexcept;

    /**
     * @brief Check if a set of samples for model generation is degenerate
     *
     * @param sample The indices of the samples we attempt to use for
     *            model instantiation.
     * @return Is this set of samples ok?
     */
    virtual bool_t IsSampleGood(std::vector<uint64_t> const& sample) const override;

    /**
     * @brief Get the number of samples needed for a hypothesis generation.
     */
    virtual uint64_t GetRequiredSampleSize() const override
    {
        return 2u;
    }

    /**
     * @brief Compute a model from a set of samples.
     * @param[in] indices The indices of the samples we use for the hypothesis.
     * @param[out] out The computed model.
     * @return Success?
     */
    virtual bool_t ComputeModel(std::vector<uint64_t> const& indices, ModelType& out) const override;

    /**
     * @brief Refine the model over a given set (inliers).
     * @ref
     * https://math.stackexchange.com/questions/3869/what-is-the-intuitive-relationship-between-svd-and-pca/3871#3871
     * @param inliers The indices of the inlier samples supporting the model.
     * @param model current estimated model
     * @return optimized model
     */
    virtual ModelType OptimizeModel(std::vector<uint64_t> const& inliers, ModelType const& model) const override;

    /**
     * @brief Compute the distances of all samples whith respect to given model.
     * @param model The model hypothesis.
     * @param index The index of the samples of which we compute distances.
     * @return scores The resultant distances of the selected samples. Low distances mean a good fit.
     */
    virtual float64_t GetDistanceToModel(ModelType const& model, uint64_t const index) const override;

private:
    /**
     * @brief data container adapter
     *
     */
    AdapterType const& adapter_;

};  // class RansacLine2FittingProblemT

/**
 * @}
 *
 */

}  // namespace holo
#endif
