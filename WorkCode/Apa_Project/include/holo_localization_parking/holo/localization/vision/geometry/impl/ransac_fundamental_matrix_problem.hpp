/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ransac_fundamental_matrix_problem.h
 * @brief implementation file of ransac fundamental matrix problem class
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "2019-07-09"
 */

#include <glog/logging.h>

namespace holo
{
namespace localization
{
namespace vision
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
RansacFundamentalMatrixProblemT<T>::RansacFundamentalMatrixProblemT(const AdapterType& left_hand_side,
                                                                    const AdapterType& right_hand_side,
                                                                    const MethodType&  method_type,
                                                                    const bool_t       random_seed)
  : Base(left_hand_side.GetSampleSize(), random_seed)
  , left_hand_side_(left_hand_side)
  , right_hand_side_(right_hand_side)
  , fundamental_matrix_solver_(method_type)
  , required_sample_size_(method_type == MethodType::FM_8POINT ? 8u : 7u)
{
    if (left_hand_side.GetSampleSize() != right_hand_side.GetSampleSize())
    {
        LOG(ERROR) << "RansacFundamentalMatrixProblem---Input left and right "
                   << "data size is not equal, "
                   << "left size: " << left_hand_side.GetSampleSize()
                   << " right size: " << right_hand_side.GetSampleSize();
        throw std::runtime_error("RansacFundamentalMatrixProblem---Invalid Input");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
RansacFundamentalMatrixProblemT<T>::~RansacFundamentalMatrixProblemT()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool_t RansacFundamentalMatrixProblemT<T>::IsSampleGood(const std::vector<uint64_t>& sample) const
{
    return !isPointSetCollinear(sample, left_hand_side_) && !isPointSetCollinear(sample, right_hand_side_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
uint64_t RansacFundamentalMatrixProblemT<T>::GetRequiredSampleSize() const
{
    return required_sample_size_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool_t RansacFundamentalMatrixProblemT<T>::ComputeModel(const std::vector<uint64_t>& indices,
                                                        ModelType&                   out_model) const
{
    std::vector<std::pair<Point2, Point2> > pairs;
    pairs.reserve(indices.size());

    // prepare data pair for fundamental matrix solver
    for (uint64_t ind = 0u; ind < static_cast<uint64_t>(indices.size()); ind++)
    {
        uint64_t index = indices.at(ind);
        pairs.emplace_back(left_hand_side_.GetSample(index), right_hand_side_.GetSample(index));
    }

    std::vector<ModelType> models;
    bool_t                 status = fundamental_matrix_solver_.ComputeModels(pairs, models);

    if (!status)
    {
        return status;
    }

    if (fundamental_matrix_solver_.GetMethodType() == MethodType::FM_8POINT)
    {
        out_model = models.at(0u);
    }
    else
    {
        /// @TODO select model for 7 point
        return false;
    }

    return status;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
float64_t RansacFundamentalMatrixProblemT<T>::GetDistanceToModel(const ModelType& model, const uint64_t index) const
{
    /**
     * @details compute point to epipolar line distance: |a * x + b * y + c| / sqrt(a * a + b * b)
     */
    const Point2& pt_left  = left_hand_side_.GetSample(index);
    const Point2& pt_right = right_hand_side_.GetSample(index);

    /// @Step 1. distance in left image
    const Vector3 coeff_left = model * pt_right.Homogeneous();

    /// @brief there is no epipolar constraint when the coefficient is zero assign these points as outliers
    const Scalar distance_left =
        coeff_left.GetNorm() < Epsilon::value ?
            std::numeric_limits<Scalar>::max() :
            std::fabs(pt_left.GetX() * coeff_left(0u) + pt_left.GetY() * coeff_left(1u) + coeff_left(2u)) /
                std::sqrt(coeff_left(0u) * coeff_left(0u) + coeff_left(1u) * coeff_left(1u));

    /// @Step 2. distance in right image
    const Vector3 coeff_right = model.Transpose() * pt_left.Homogeneous();
    const Scalar  distance_right =
        coeff_right.GetNorm() < Epsilon::value ?
            std::numeric_limits<Scalar>::max() :
            std::fabs(pt_right.GetX() * coeff_right(0u) + pt_right.GetY() * coeff_right(1u) + coeff_right(2u)) /
                std::sqrt(coeff_right(0u) * coeff_right(0u) + coeff_right(1u) * coeff_right(1u));

    // return the maximum distance
    return std::max(distance_left, distance_right);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
typename RansacFundamentalMatrixProblemT<T>::ModelType
RansacFundamentalMatrixProblemT<T>::OptimizeModel(const std::vector<uint64_t>& inliers, const ModelType& model) const
{
    ModelType optimized_model;

    if (!ComputeModel(inliers, optimized_model))
    {
        optimized_model = model;
    }

    return optimized_model;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool_t RansacFundamentalMatrixProblemT<T>::isPointSetCollinear(const std::vector<uint64_t>& sample,
                                                               const AdapterType&           adapter) const
{
    uint16_t sample_size = static_cast<uint16_t>(sample.size());

    for (uint16_t i = 0u; i < sample_size; i++)
    {
        const Point2& pt_i = adapter.GetSample(sample.at(i));

        for (uint16_t j = i + 1u; j < sample_size; j++)
        {
            const Point2& pt_j = adapter.GetSample(sample.at(j));

            // check if these two points are almost the same one
            if (pt_i.Dist(pt_j) < Epsilon::value)
            {
                LOG(ERROR) << "RansacFundamentalMatrixProblemT --- there exist exactly the same points in given "
                              "sample. this should not happen!!!";
                LOG(ERROR) << "pt_i: " << pt_i << "\n";
                LOG(ERROR) << "pt_j: " << pt_j << "\n";
                LOG(ERROR) << "index i: " << sample.at(i) << "\n";
                LOG(ERROR) << "index j: " << sample.at(j) << "\n";
                return true;
            }

            const Line2 line_ij(pt_i, pt_j);

            for (uint16_t k = j + 1u; k < sample_size; k++)
            {
                const Point2& pt_k = adapter.GetSample(sample.at(k));

                // check if these two points are almost the same one
                if (pt_k.Dist(pt_j) < Epsilon::value)
                {
                    LOG(ERROR) << "RansacFundamentalMatrixProblemT --- there exist exactly the same points in given "
                                  "sample. this should not happen!!!";
                    LOG(ERROR) << "pt_k: " << pt_k << "\n";
                    LOG(ERROR) << "pt_j: " << pt_j << "\n";
                    LOG(ERROR) << "index k: " << sample.at(k) << "\n";
                    LOG(ERROR) << "index j: " << sample.at(j) << "\n";
                    return true;
                }

                const Line2 line_jk(pt_j, pt_k);

                if (line_ij.IsParallel(line_jk, Epsilon::value))
                {
                    return true;
                }
            }
        }
    }

    return false;
}
}  // namespace vision
}  // namespace localization
}  // namespace holo
