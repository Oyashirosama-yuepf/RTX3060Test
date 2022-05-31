/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file fpcs_base.hpp
 * @brief This header file defines implementation of fpcs base class
 * @author zhaojiaxing(zhaojiaxing@holomatic.com)
 * @author mengzhili(mengzhili@holomatic.com)
 * @date "2021-03-08"
 */

#ifndef HOLO_3D_REGISTRATION_FPCS_BASE_HPP_
#define HOLO_3D_REGISTRATION_FPCS_BASE_HPP_

#include <holo/3d/registration/fpcs_base.h>

#include <holo/3d/registration/transformation_estimation_svd.h>

namespace holo
{
namespace pointcloud
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
FPCSBaseT<PointSourceT, PointTargetT, Scalar>::Quadrilateral::Quadrilateral()
  : vertices({0, 0, 0, 0}), invariants({0.0, 0.0})
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
FPCSBaseT<PointSourceT, PointTargetT, Scalar>::Quadrilateral::Quadrilateral(size_t const vertex0, size_t const vertex1,
                                                                            size_t const vertex2, size_t const vertex3,
                                                                            Scalar const invariant0,
                                                                            Scalar const invariant1)
  : vertices({vertex0, vertex1, vertex2, vertex3}), invariants({invariant0, invariant1})
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
typename FPCSBaseT<PointSourceT, PointTargetT, Scalar>::Quadrilateral&
FPCSBaseT<PointSourceT, PointTargetT, Scalar>::Quadrilateral::operator=(Quadrilateral const& q)
{
    vertices   = {q.vertices[0], q.vertices[1], q.vertices[2], q.vertices[3]};
    invariants = {q.invariants[0], q.invariants[1]};
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
size_t FPCSBaseT<PointSourceT, PointTargetT, Scalar>::Quadrilateral::operator[](size_t const idx) const
{
    if (idx > 4)
    {
        std::string s = "Quadrilateral index out of bound, idx should less than 4";
        LOG(ERROR) << s;
        throw std::out_of_range(s);
    }

    return vertices[idx];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
size_t& FPCSBaseT<PointSourceT, PointTargetT, Scalar>::Quadrilateral::operator[](size_t const idx)
{
    if (idx > 4)
    {
        std::string s = "Quadrilateral index out of bound, idx should less than 4";
        LOG(ERROR) << s;
        throw std::out_of_range(s);
    }

    return vertices[idx];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
FPCSBaseT<PointSourceT, PointTargetT, Scalar>::FPCSBaseT(Parameters const& params)
  : Base()
  , params_(params)
  , diameter_target_(0.0)
  , max_base_diameter_sqr_(0.0)
  , base_diameter_fraction_sqr_(0.0)
  , coincidence_distance_limit_(0.0)
  , max_mse_(0.0)
  , max_inlier_dist_sqr_(0.0)
  , best_lcp_(0.0)
  , re_(std::mt19937::default_seed)
{
    transformation_estimation_.reset(new TransformationEstimationSVDT<PointSourceT, PointTargetT, Scalar>());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
FPCSBaseT<PointSourceT, PointTargetT, Scalar>::~FPCSBaseT()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
Scalar FPCSBaseT<PointSourceT, PointTargetT, Scalar>::GetBestLCP() const
{
    return best_lcp_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
bool_t FPCSBaseT<PointSourceT, PointTargetT, Scalar>::preCompute()
{
    if (!source_.get() || source_->empty())
    {
        std::string msg = "input source point cloud is not set!";
        LOG(ERROR) << msg;
        return false;
    }

    if (!target_.get() || target_->empty())
    {
        std::string msg = "input target point cloud is not set!";
        LOG(ERROR) << msg;
        return false;
    }

    if (indices_source_.empty() || indices_target_.empty())
    {
        std::string msg = "empty indices!";
        LOG(ERROR) << msg;
        return false;
    }

    if (indices_source_.size() > params_.sample_size)
    {
        std::random_shuffle(indices_source_.begin(), indices_source_.end());
        indices_source_.resize(params_.sample_size);
    }

    // init the target tree if it's not set
    if (!tree_target_.get())
    {
        tree_target_.reset(new KdTreeTarget);
        tree_target_->SetInputPointCloud(target_);
    }
    else if (tree_target_->GetInputPointCloud() != target_)
    {
        // tree is set, but the point cloud in tree is not consistent with target_
        // then we have to reset the tree's point cloud
        tree_target_->SetInputPointCloud(target_);
    }

    BBox<PointTargetT, 3> bbox;
    PointTargetT          min_pt, max_pt;
    bbox(*target_, min_pt, max_pt);

    diameter_target_ = (max_pt - min_pt).template As<Vector3Type>().GetNorm();

    // set predefined variables
    Scalar const k_small_error     = 0.00001;
    size_t const k_min_iterations  = 4u;
    Scalar const diameter_fraction = params_.base_diameter_fraction;
    Scalar const approx_overlap    = params_.approximate_overlap;

    Scalar max_base_diameter    = diameter_target_ * approx_overlap;
    max_base_diameter_sqr_      = max_base_diameter * max_base_diameter;
    base_diameter_fraction_sqr_ = std::pow(max_base_diameter * diameter_fraction, 2.0);
    coincidence_distance_limit_ = params_.delta * params_.distance_factor;
    max_mse_                    = std::pow(params_.delta * params_.distance_factor, 2.0);
    max_inlier_dist_sqr_        = std::pow(params_.delta * params_.distance_factor, 2.0);

    // heuristic determination of number of trials to have high probability of finding good solution
    if (max_iterations_ == 0u)
    {
        Scalar first_estimation = std::log(k_small_error) / std::log(1.0 - std::pow(approx_overlap, k_min_iterations));
        max_iterations_         = static_cast<size_t>(first_estimation / (diameter_fraction * approx_overlap * 2.0));
    }

    if (max_iterations_ < k_min_iterations)
    {
        max_iterations_ = k_min_iterations;
    }

    LOG(INFO) << "diameter target: " << diameter_target_;
    LOG(INFO) << "max base diameter: " << max_base_diameter;
    LOG(INFO) << "coincidence_distance_limit: " << coincidence_distance_limit_;
    LOG(INFO) << "max iterations: " << max_iterations_;
    LOG(INFO) << "indices source: " << indices_source_.size();
    LOG(INFO) << "indices target: " << indices_target_.size();

    distribution_.reset(new DistributionType(0, indices_target_.size() - 1));

    random_generator_ = std::bind(*distribution_, re_);

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
bool_t FPCSBaseT<PointSourceT, PointTargetT, Scalar>::Compute(Pose3Type const& guess)
{
    if (!preCompute())
    {
        LOG(ERROR) << "PreCompute failed.";
        return false;
    }

    timer_.Tic();
    float64_t time_elapsed = 0.0;

    transformation_ = guess;
    best_lcp_       = verify(transformation_);

    LOG_IF(INFO, params_.verbose) << "initial lcp: " << best_lcp_;

    if (best_lcp_ > params_.expected_overlap)
    {
        final_transformation_ = transformation_;
        return true;
    }

    for (size_t i = 0u; i < max_iterations_; ++i)
    {
        //@step0 check overtime
        time_elapsed = timer_.Elapsed();
        if (time_elapsed > params_.max_time_elapsed)
        {
            LOG(INFO) << "fpcs compute overtime: " << time_elapsed << " > " << params_.max_time_elapsed;
            break;
        }

        Quadrilateral quad_base;

        //@step1 select four coplanar point base in target point cloud
        if (!selectQuadrilateralBase(quad_base))
        {
            continue;
        }

        LOG_IF(INFO, params_.verbose) << "q: " << quad_base[0] << " " << quad_base[1] << " " << quad_base[2] << " "
                                      << quad_base[3];

        PairsVector pairs1, pairs2;

        //@step2 extract all point pairs have same distance with quadrilateral two diagonals
        extractPairs(quad_base[0], quad_base[1], pairs1);
        extractPairs(quad_base[2], quad_base[3], pairs2);

        LOG_IF(INFO, params_.verbose) << "pairs1 size: " << pairs1.size() << " pairs2 size: " << pairs2.size();

        if (pairs1.empty() || pairs2.empty())
        {
            continue;
        }

        //@step3 find congruent quadrilaterals in source point cloud
        std::vector<Quadrilateral> congruent_quads;
        if (!findCongruentQuadrilaterals(quad_base.invariants[0], quad_base.invariants[1], pairs1, pairs2,
                                         congruent_quads))
        {
            continue;
        }

        LOG_IF(INFO, params_.verbose) << "congruent quadrilaterals: " << congruent_quads.size();

        //@step4 loop over the set of congruent 4-points and test compatibility with the input base
        if (!tryCongruentSet(quad_base, congruent_quads))
        {
            continue;
        }        

        //@step5 check stop criteria
        if (best_lcp_ > params_.expected_overlap)
        {
            final_transformation_ = transformation_;
            break;
        }

        LOG_IF(INFO, params_.verbose) << "iteration: " << i << " best lcp: " << best_lcp_;
    }

    final_transformation_ = transformation_;

    if (!postCompute())
    {
        LOG(ERROR) << "PostCompute failed.";
        return false;
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
bool_t FPCSBaseT<PointSourceT, PointTargetT, Scalar>::postCompute()
{
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
bool_t FPCSBaseT<PointSourceT, PointTargetT, Scalar>::selectQuadrilateralBase(Quadrilateral& q)
{
    Scalar const base_too_small      = base_diameter_fraction_sqr_;
    size_t const num_diameter_trials = params_.num_diameter_trials;

    size_t base4 = std::numeric_limits<size_t>::quiet_NaN();

    for (size_t i = 0u; i < num_diameter_trials; ++i)
    {
        // select a triangle if possible.
        if (!selectRandomTriangle(q[0], q[1], q[2]))
        {
            continue;
        }

        // the 4th point will be a one that is close to be planar to the other 3 while still not too close to them.
        PointTargetT const& pt1 = target_->at(q[0]);
        PointTargetT const& pt2 = target_->at(q[1]);
        PointTargetT const& pt3 = target_->at(q[2]);

        Scalar x1 = pt1[0];
        Scalar y1 = pt1[1];
        Scalar z1 = pt1[2];
        Scalar x2 = pt2[0];
        Scalar y2 = pt2[1];
        Scalar z2 = pt2[2];
        Scalar x3 = pt3[0];
        Scalar y3 = pt3[1];
        Scalar z3 = pt3[2];

        // fit a plane using Method 2 details see https://en.wikipedia.org/wiki/Plane_(geometry)
        Scalar denom = (-x3 * y2 * z1 + x2 * y3 * z1 + x3 * y1 * z2 - x1 * y3 * z2 - x2 * y1 * z3 + x1 * y2 * z3);
        Scalar min_distance = std::numeric_limits<Scalar>::max();

        if (denom > EpsilonT<Scalar>::value)
        {
            Scalar a = (-y2 * z1 + y3 * z1 + y1 * z2 - y3 * z2 - y1 * z3 + y2 * z3) / denom;
            Scalar b = (x2 * z1 - x3 * z1 - x1 * z2 + x3 * z2 + x1 * z3 - x2 * z3) / denom;
            Scalar c = (-x2 * y1 + x3 * y1 + x1 * y2 - x3 * y2 - x1 * y3 + x2 * y3) / denom;

            base4 = std::numeric_limits<size_t>::quiet_NaN();

            for (auto const& idx : indices_target_)
            {
                PointTargetT const& pt4 = target_->at(idx);

                Scalar d1 = (pt4 - pt1).template As<Vector3Type>().GetSquaredNorm();
                Scalar d2 = (pt4 - pt2).template As<Vector3Type>().GetSquaredNorm();
                Scalar d3 = (pt4 - pt3).template As<Vector3Type>().GetSquaredNorm();

                // check distance between points w.r.t minimum sampling distance
                if (d1 < base_too_small || d2 < base_too_small || d3 < base_too_small)
                {
                    continue;
                }

                // check distance to plane
                Scalar const distance = std::abs(a * pt4[0] + b * pt4[1] + c * pt4[2] - 1.0);

                if (distance < min_distance)
                {
                    min_distance = distance;
                    base4        = idx;
                }
            }
        }

        if (base4 != std::numeric_limits<size_t>::quiet_NaN() && min_distance < params_.min_distance_threshold)
        {
            q[3] = base4;

            tryQuadrilateral(q);

            quad_base_ = q;

            return true;
        }
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
bool_t FPCSBaseT<PointSourceT, PointTargetT, Scalar>::selectRandomTriangle(size_t& base1, size_t& base2, size_t& base3)
{
    size_t invalid_value = std::numeric_limits<size_t>::quiet_NaN();
    base1 = base2 = base3 = invalid_value;
    Scalar best_t         = 0.0;  ///< largest triangle area

    // pick the first point at random
    size_t index1 = indices_target_[random_generator_()];

    for (size_t i = 0u; i < params_.num_diameter_trials; ++i)
    {
        size_t index2 = indices_target_[random_generator_()];
        size_t index3 = indices_target_[random_generator_()];

        Vector3Type u = target_->at(index2).template As<Vector3Type>() - target_->at(index1).template As<Vector3Type>();
        Vector3Type v = target_->at(index3).template As<Vector3Type>() - target_->at(index1).template As<Vector3Type>();

        Scalar t = u.Cross(v).GetSquaredNorm();

        if (t > best_t && u.GetSquaredNorm() < max_base_diameter_sqr_ && v.GetSquaredNorm() < max_base_diameter_sqr_)
        {
            best_t = t;
            base1  = index1;
            base2  = index2;
            base3  = index3;
        }
    }

    return base1 != invalid_value && base2 != invalid_value && base3 != invalid_value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
void FPCSBaseT<PointSourceT, PointTargetT, Scalar>::tryQuadrilateral(Quadrilateral& q)
{
    Scalar min_dist   = std::numeric_limits<Scalar>::max();
    Scalar invariant1 = 0.0, invariant2 = 0.0;
    size_t base_index1, base_index2, base_index3, base_index4;
    base_index1 = base_index2 = base_index3 = base_index4 = std::numeric_limits<size_t>::quiet_NaN();

    // go through the combination of 4 points
    for (size_t i = 0u; i < 4u; ++i)
    {
        for (size_t j = 0u; j < 4u; ++j)
        {
            if (i == j)
            {
                continue;
            }

            size_t k = 0u;

            while (k == i || k == j)
            {
                k++;
            }

            size_t l = 0u;

            while (l == i || l == j || l == k)
            {
                l++;
            }

            PointTargetT const& p1 = target_->at(q[i]);
            PointTargetT const& p2 = target_->at(q[j]);
            PointTargetT const& q1 = target_->at(q[k]);
            PointTargetT const& q2 = target_->at(q[l]);

            Scalar local_invariant1;
            Scalar local_invariant2;
            Scalar segment_dist;

            // compute the closet point on both segments, the corresponding invariants and the distance between the
            // closest points. more details please refer to
            // http://geomalgorithms.com/a07-_distance.html#dist3D_Segment_to_Segment
            distSegmentToSegment(p1, p2, q1, q2, local_invariant1, local_invariant2, segment_dist);

            // retain the smallest distance and the best order so far
            if (segment_dist < min_dist)
            {
                min_dist    = segment_dist;
                base_index1 = q[i];
                base_index2 = q[j];
                base_index3 = q[k];
                base_index4 = q[l];
                invariant1  = local_invariant1;
                invariant2  = local_invariant2;
            }
        }
    }

    // setup quadrilateral base
    q = Quadrilateral(base_index1, base_index2, base_index3, base_index4, invariant1, invariant2);

    return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
void FPCSBaseT<PointSourceT, PointTargetT, Scalar>::distSegmentToSegment(PointTargetT const& p1, PointTargetT const& p2,
                                                                         PointTargetT const& q1, PointTargetT const& q2,
                                                                         Scalar& invariant1, Scalar& invariant2,
                                                                         Scalar& dist)
{
    Scalar const thresh_delta = 0.0001;

    Vector3Type u = (p2 - p1).template As<Vector3Type>();
    Vector3Type v = (q2 - q1).template As<Vector3Type>();
    Vector3Type w = (p1 - q1).template As<Vector3Type>();

    Scalar a = u.Dot(u);
    Scalar b = u.Dot(v);
    Scalar c = v.Dot(v);
    Scalar d = u.Dot(w);
    Scalar e = v.Dot(w);

    // delta = ac − b*b = |(p2 − p1) × (q2 − q1)|^2, when delta > 0, the line segments are not parallel.
    // when delta = 0, the line segments are not parallel.
    Scalar f = a * c - b * b;

    // s1,s2 and t1,t2 are the parametric representation of the intersection. they will be the invariants at the end of
    // this simple computation.
    Scalar s1 = 0.0;
    Scalar s2 = f;
    Scalar t1 = 0.0;
    Scalar t2 = f;

    if (f < thresh_delta)  ///> the lines are almost parallel
    {
        s1 = 0.0;
        s2 = 1.0;
        t1 = e;
        t2 = c;
    }
    else
    {
        s1 = (b * e - c * d);
        t1 = (a * e - b * d);
        if (s1 < 0.0)
        {
            s1 = 0.0;
            t1 = e;
            t2 = c;
        }
        else if (s1 > s2)
        {
            s1 = s2;
            t1 = e + b;
            t2 = c;
        }
    }

    if (t1 < 0.0)
    {
        t1 = 0.0;
        if (-d < 0.0)
        {
            s1 = 0.0;
        }
        else if (-d > a)
        {
            s1 = s2;
        }
        else
        {
            s1 = -d;
            s2 = a;
        }
    }
    else if (t1 > t2)
    {
        t1 = t2;
        if ((-d + b) < 0.0)
        {
            s1 = 0;
        }
        else if ((-d + b) > a)
        {
            s1 = s2;
        }
        else
        {
            s1 = (-d + b);
            s2 = a;
        }
    }

    invariant1 = std::abs(s1) < thresh_delta ? 0.0 : s1 / s2;
    invariant2 = std::abs(t1) < thresh_delta ? 0.0 : t1 / t2;

    dist = (w + (invariant1 * u) - (invariant2 * v)).GetNorm();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
bool_t FPCSBaseT<PointSourceT, PointTargetT, Scalar>::tryCongruentSet(Quadrilateral const&              quad_base,
                                                                      std::vector<Quadrilateral> const& congruent_quads)
{
    Scalar const expect_lcp = params_.expected_overlap;

    for (size_t i = 0u; i < congruent_quads.size(); ++i)
    {
        correspondences_.clear();
        Quadrilateral const& quad_match = congruent_quads[i];

        correspondences_.emplace_back(quad_match[0], quad_base[0]);
        correspondences_.emplace_back(quad_match[1], quad_base[1]);
        correspondences_.emplace_back(quad_match[2], quad_base[2]);
        correspondences_.emplace_back(quad_match[3], quad_base[3]);

        Pose3Type transformation;

        transformation_estimation_->ComputeTransformation(*source_, *target_, correspondences_, transformation);

        PointCloudSource    src_transformed;
        std::vector<size_t> match_indices{quad_match[0], quad_match[1], quad_match[2], quad_match[3]};

        TransformPointCloud(*source_, match_indices, transformation, src_transformed);

        size_t num_points = correspondences_.size();
        Scalar mse        = 0.0;

        for (size_t i = 0u; i < num_points; ++i)
        {
            PointSourceT const& pt_src = src_transformed[i];
            PointTargetT const& pt_tgt = target_->at(quad_base[i]);

            Scalar diff_x = pt_src[0] - pt_tgt[0];
            Scalar diff_y = pt_src[1] - pt_tgt[1];
            Scalar diff_z = pt_src[2] - pt_tgt[2];

            mse += diff_x * diff_x + diff_y * diff_y + diff_z * diff_z;
        }

        mse /= static_cast<Scalar>(num_points);

        if (mse < max_mse_)
        {
            Scalar lcp = verify(transformation);

            if (lcp > best_lcp_)
            {
                best_lcp_       = lcp;
                transformation_ = transformation;
            }

            if (best_lcp_ >= expect_lcp)
            {
                break;
            }
        }
    }
    LOG_IF(INFO, params_.verbose) << "best lcp: " << best_lcp_;

    return best_lcp_ >= expect_lcp;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
Scalar FPCSBaseT<PointSourceT, PointTargetT, Scalar>::verify(Pose3Type const& transformation) const
{
    size_t num_points      = indices_source_.size();
    size_t terminate_value = static_cast<size_t>(best_lcp_ * num_points);

    PointCloudSourcePtr src_trans(new PointCloudSource);
    TransformPointCloud(*source_, indices_source_, transformation, *src_trans);

    std::vector<size_t> nn_indices(1);
    std::vector<Scalar> nn_dists_square(1);

    size_t num_good = 0u;

    for (size_t i = 0u; i < num_points; ++i)
    {
        PointSourceT const& pt_src = src_trans->at(i);

        if (tree_target_->KnnSearch(pt_src, 1u, nn_indices, nn_dists_square))
        {
            if (nn_dists_square[0] < max_inlier_dist_sqr_)
            {
                num_good++;
            }
        }

        if (num_points - i + num_good < terminate_value)
        {
            break;
        }
    }

    return static_cast<Scalar>(num_good) / static_cast<Scalar>(num_points);
}

}  // namespace pointcloud

}  // namespace holo

#endif  // HOLO_3D_REGISTRATION_FOUR_PCS_BASE_HPP_
