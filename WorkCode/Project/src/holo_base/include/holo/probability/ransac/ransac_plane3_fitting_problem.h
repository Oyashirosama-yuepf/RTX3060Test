/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ransac_plane3_fitting_problem.h
 * @brief this class represents ransac solving specific fitting plane3 problem
 * @author zhaojiaxing(zhaojiaxing@holomaitc.com)
 * @date "2022-01-12"
 */

#ifndef HOLO_PROBABILITY_RANSAC_PLANE3_FITTING_PROBLEM_H_
#define HOLO_PROBABILITY_RANSAC_PLANE3_FITTING_PROBLEM_H_

#include <holo/geometry/plane3.h>
#include <holo/geometry/point3.h>
#include <holo/log/hololog.h>
#include <holo/numerics/matrix.h>
#include <holo/probability/ransac/ransac_problem.h>
#include <holo/probability/ransac/ransac_problem_data_container_adapter.h>

namespace holo
{
template <typename T>
class RansacPlane3FittingProblemT : public RansacProblemT<holo::geometry::Plane3T<T>>
{
public:
    using Base        = RansacProblemT<holo::geometry::Plane3T<T>>;
    using ScalarType  = T;
    using Point3Type  = holo::geometry::Point3T<ScalarType>;
    using Vector4Type = holo::numerics::Vector4T<ScalarType>;
    using AdapterType = RansacProblemDataContainerAdapterBaseT<Point3Type>;
    using typename Base::ModelType;
    using Vector3Type = holo::numerics::Vector3T<ScalarType>;

    /**
     * @brief disable default constructor, copy constructor and assignment operator
     *
     */
    RansacPlane3FittingProblemT() = delete;

    RansacPlane3FittingProblemT(RansacPlane3FittingProblemT const&) = delete;

    RansacPlane3FittingProblemT& operator=(RansacPlane3FittingProblemT const&) = delete;

    /**
     * @brief Construct with adapter and random_seed
     *
     * @param adapter data container adapter
     * @param random_seed random_seed
     */
    RansacPlane3FittingProblemT(AdapterType const& adapter, bool random_seed = true);

    /**
     * @brief Destructor
     */
    virtual ~RansacPlane3FittingProblemT() noexcept;

    /**
     * @brief Check if a set of samples for model generation is degenerate
     *
     * @param sample The indices of the samples we attempt to use for
     *            model instantiation.
     * @return Is this set of samples ok?
     */
    virtual bool_t IsSampleGood(std::vector<uint64_t> const& sample) const override;

    /**
     * @brief Get the number of samples needed for a hypothesis generation
     *
     * @return number of samples
     */
    virtual size_t GetRequiredSampleSize() const override
    {
        return 3u;
    }

    /**
     * @brief Compute a model from a set of samples.
     *
     * @param[in] indices The indices of the samples we use for the hypothesis
     * @param[out] out_model The computed model.
     */
    virtual bool ComputeModel(std::vector<size_t> const& indices, ModelType& out_model) const override;

    /**
     * @brief Refine the model over a given set (inliers)
     * @ref
     https://math.stackexchange.com/questions/3869/what-is-the-intuitive-relationship-between-svd-and-pca/3871#3871

     * @param inliers The indices of the inlier samples supporting the model.
     * @param model current estimated model
     * @return optimized model
     */
    virtual ModelType OptimizeModel(std::vector<size_t> const& inliers, ModelType const& model) const override;

    /**
     * @brief Compute the distances of all samples whith respect to given model.
     *
     * @param model The model hypothesis.
     * @param indices The indices of the samples of which we compute distances.
     * @return scores The resultant distances of the selected samples. Low distances mean a good fit.
     */
    virtual float64_t GetDistanceToModel(ModelType const& model, size_t const index) const override;

private:
    AdapterType const& adapter_;
};  /// RansacPlane3FittingProblemT

}  // namespace holo
#endif
