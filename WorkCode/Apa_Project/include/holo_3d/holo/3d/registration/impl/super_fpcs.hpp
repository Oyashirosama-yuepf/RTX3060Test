/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file super_fpcs.hpp
 * @brief This header file defines implementation of super fpcs base class
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2021-03-16
 */

#ifndef HOLO_3D_REGISTRATION_SUPER_FPCS_HPP_
#define HOLO_3D_REGISTRATION_SUPER_FPCS_HPP_

#include <holo/3d/registration/super_fpcs.h>

namespace holo
{
namespace pointcloud
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
SuperFPCST<PointSourceT, PointTargetT, Scalar>::SuperFPCST(Parameters const& params) : Base(params)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
SuperFPCST<PointSourceT, PointTargetT, Scalar>::~SuperFPCST()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
bool_t SuperFPCST<PointSourceT, PointTargetT, Scalar>::preCompute()
{
    if (!Base::preCompute())
    {
        return false;
    }

    pair_creation_functor_.Initialize(source_, indices_source_);

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
void SuperFPCST<PointSourceT, PointTargetT, Scalar>::extractPairs(size_t base_index1, size_t base_index2,
                                                                  PairsVector& pairs) const
{
    Scalar max_pair_diff = params_.delta * params_.distance_factor;
    pair_creation_functor_.pairs.clear();
    pair_creation_functor_.pairs.reserve(2 * indices_source_.size());

    Vector3Type const& base_point1 = target_->at(base_index1).template As<Vector3Type>();
    Vector3Type const& base_point2 = target_->at(base_index2).template As<Vector3Type>();

    pair_creation_functor_.max_pair_diff            = max_pair_diff;
    pair_creation_functor_.max_translation_distance = params_.max_translation_distance;
    pair_creation_functor_.max_angle                = params_.max_angle;

    pair_creation_functor_.SetRadius((base_point2 - base_point1).GetNorm());
    pair_creation_functor_.SetBase(base_point1, base_point2);

    internal::IntersectionFunctor intersection_functor;

    Scalar       epsilon       = pair_creation_functor_.GetNormalizedEpsilon(max_pair_diff);
    size_t const min_node_size = 50u;
    intersection_functor.Process(min_node_size, pair_creation_functor_, epsilon);

    pairs = pair_creation_functor_.pairs;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
bool_t SuperFPCST<PointSourceT, PointTargetT, Scalar>::findCongruentQuadrilaterals(
    Scalar invariant1, Scalar invariant2, PairsVector const& pairs1, PairsVector const& pairs2,
    std::vector<Quadrilateral>& quadrilaterals) const
{
    quadrilaterals.clear();
    Scalar const distance_threshold = coincidence_distance_limit_;

    Point3Type const base_point1 = target_->at(quad_base_[0]).template As<Point3Type>();
    Point3Type const base_point2 = target_->at(quad_base_[1]).template As<Point3Type>();
    Point3Type const base_point3 = target_->at(quad_base_[2]).template As<Point3Type>();
    Point3Type const base_point4 = target_->at(quad_base_[3]).template As<Point3Type>();

    LineSegement3Type segment1(base_point1, base_point2);
    LineSegement3Type segment2(base_point3, base_point4);

    Scalar const cos_alpha = segment1.GetDirection().Dot(segment2.GetDirection());
    Scalar const eps       = pair_creation_functor_.GetNormalizedEpsilon(distance_threshold);

    IndexedNormalSetType nset(eps);

    for (size_t i = 0; i < pairs1.size(); ++i)
    {
        Point3Type const& p1 = pair_creation_functor_.points[pairs1[i].first];
        Point3Type const& p2 = pair_creation_functor_.points[pairs1[i].second];
        Vector3Type       n  = (p2 - p1).template As<Vector3Type>().GetNormalized();

        nset.AddElement(p1 + invariant1 * (p2 - p1), Point3Type(n[0], n[1], n[2]), i);
    }

    std::set<std::pair<size_t, size_t> > comb;
    std::vector<size_t>                  nei;

    for (size_t i = 0; i < pairs2.size(); ++i)
    {
        Point3Type const& p1  = pair_creation_functor_.points[pairs2[i].first];
        Point3Type const& p2  = pair_creation_functor_.points[pairs2[i].second];
        Point3Type const& pq1 = source_->at(indices_source_[pairs2[i].first]).template As<Point3Type>();
        Point3Type const& pq2 = source_->at(indices_source_[pairs2[i].second]).template As<Point3Type>();

        nei.clear();
        Point3Type const  query        = p1 + invariant2 * (p2 - p1);
        Point3Type const  query_source = pq1 + invariant2 * (pq2 - pq1);
        Vector3Type const query_n      = (p2 - p1).template As<Vector3Type>().GetNormalized();

        Point3Type query_normal(query_n[0], query_n[1], query_n[2]);
        nset.GetNeighbors(query, query_normal, cos_alpha, nei);

        Point3Type invariant_point;

        for (size_t j = 0; j != nei.size(); ++j)
        {
            size_t const& id = nei[j];

            Point3Type const& pp1 = source_->at(indices_source_[pairs1[id].first]).template As<Point3Type>();
            Point3Type const& pp2 = source_->at(indices_source_[pairs1[id].second]).template As<Point3Type>();

            invariant_point = pp1 + invariant1 * (pp2 - pp1);

            // use also distance_threshold for inv 1 and 2 in 4PCS
            if (query_source.Dist(invariant_point) <= distance_threshold)
            {
                comb.emplace(id, i);
            }
        }
    }

    for (auto const& pair : comb)
    {
        size_t const& id = pair.first;
        size_t const& i  = pair.second;

        size_t const& v0 = indices_source_[pairs1[id].first];
        size_t const& v1 = indices_source_[pairs1[id].second];
        size_t const& v2 = indices_source_[pairs2[i].first];
        size_t const& v3 = indices_source_[pairs2[i].second];

        quadrilaterals.emplace_back(Quadrilateral(v0, v1, v2, v3, invariant1, invariant2));
    }

    return quadrilaterals.size() != 0;
}
}  // namespace pointcloud
}  // namespace holo

#endif  // HOLO_3D_REGISTRATION_SUPER_FPCS_HPP_
