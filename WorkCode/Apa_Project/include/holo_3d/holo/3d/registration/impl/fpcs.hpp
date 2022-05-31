/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file fpcs.hpp
 * @brief This header file defines implementation of fpcs class
 * @author zhaojiaxing(zhaojiaxing@holomatic.com)
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2021-03-11
 */

#ifndef HOLO_3D_REGISTRATION_FPCS_HPP_
#define HOLO_3D_REGISTRATION_FPCS_HPP_

#include <holo/3d/registration/fpcs.h>

namespace holo
{
namespace pointcloud
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
FPCST<PointSourceT, PointTargetT, Scalar>::FPCST(Parameters const& params) : Base(params)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
FPCST<PointSourceT, PointTargetT, Scalar>::~FPCST()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
void FPCST<PointSourceT, PointTargetT, Scalar>::extractPairs(size_t base_index1, size_t base_index2,
                                                             PairsVector& pairs) const
{
    Scalar const max_angle                = params_.max_angle;
    Scalar const max_translation_distance = params_.max_translation_distance;
    size_t const num_points_src           = indices_source_.size();
    Scalar const max_pair_diff            = params_.delta * params_.distance_factor;

    pairs.clear();
    pairs.reserve(2 * num_points_src);

    Vector3Type const& base_point1 = target_->at(base_index1).template As<Vector3Type>();
    Vector3Type const& base_point2 = target_->at(base_index2).template As<Vector3Type>();

    Vector3Type  segment1      = base_point2 - base_point1;
    Scalar const pair_distance = segment1.GetNorm();

    segment1.Normalize();

    for (size_t i = 0; i < num_points_src; ++i)
    {
        Vector3Type p = source_->at(indices_source_[i]).template As<Vector3Type>();

        for (size_t j = i + 1; j < num_points_src; ++j)
        {
            Vector3Type q = source_->at(indices_source_[j]).template As<Vector3Type>();

            Scalar const dist = (q - p).GetNorm();

            if (std::fabs(dist - pair_distance) > max_pair_diff)
            {
                continue;
            }

            if (max_translation_distance > 0)
            {
                Scalar const dist_p    = (p - base_point1).GetNorm();
                Scalar const dist_q    = (q - base_point2).GetNorm();
                bool_t const dist_good = dist_p < max_translation_distance && dist_q < max_translation_distance;

                if (!dist_good)
                {
                    continue;
                }
            }

            if (max_angle > 0)
            {
                Vector3Type segment2 = q - p;
                segment2.Normalize();

                if (std::acos(segment1.Dot(segment2)) < geometry::Radian(max_angle))
                {
                    pairs.emplace_back(j, i);
                }

                if (std::acos(segment1.Dot(-segment2)) < geometry::Radian(max_angle))
                {
                    pairs.emplace_back(i, j);
                }

                continue;
            }

            pairs.emplace_back(j, i);
            pairs.emplace_back(i, j);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
bool_t FPCST<PointSourceT, PointTargetT, Scalar>::findCongruentQuadrilaterals(
    Scalar invariant1, Scalar invariant2, PairsVector const& pairs1, PairsVector const& pairs2,
    std::vector<Quadrilateral>& quadrilaterals) const
{
    quadrilaterals.clear();

    PointCloudSourcePtr cloud(new PointCloudSource);
    cloud->resize(pairs1.size());

    for (size_t i = 0u; i < pairs1.size(); ++i)
    {
        PointSourceT const& q1 = source_->at(indices_source_[pairs1[i].first]);
        PointSourceT const& q2 = source_->at(indices_source_[pairs1[i].second]);

        cloud->at(i) = q1 + invariant1 * (q2 - q1);
    }

    KdTreeSourcePtr tree(new KdTreeSource);
    tree->SetInputPointCloud(cloud);

    std::vector<size_t> nn_indices;
    std::vector<Scalar> nn_dists_sqr;

    for (size_t i = 0u; i < pairs2.size(); ++i)
    {
        PointSourceT const& q3 = source_->at(indices_source_[pairs2[i].first]);
        PointSourceT const& q4 = source_->at(indices_source_[pairs2[i].second]);

        PointSourceT e = q3 + invariant2 * (q4 - q3);

        if (tree->RadiusSearch(e, coincidence_distance_limit_, nn_indices, nn_dists_sqr))
        {
            size_t const& v0 = indices_source_[pairs1[nn_indices[0]].first];
            size_t const& v1 = indices_source_[pairs1[nn_indices[0]].second];
            size_t const& v2 = indices_source_[pairs2[i].first];
            size_t const& v3 = indices_source_[pairs2[i].second];
            quadrilaterals.emplace_back(Quadrilateral(v0, v1, v2, v3, invariant1, invariant2));
        }
    }

    return quadrilaterals.size() > 0u;
}
}  // namespace pointcloud
}  // namespace holo
#endif  // HOLO_3D_REGISTRATION_FPCS_HPP_
