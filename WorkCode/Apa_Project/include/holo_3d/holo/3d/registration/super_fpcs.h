/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file super_fpcs.h
 * @brief This header file defines super 4PCS class
 * @author zhaojiaxing(zhaojiaxing@holomatic.com)
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2021-03-16
 */

#ifndef HOLO_3D_REGISTRATION_SUPER_FPCS_H_
#define HOLO_3D_REGISTRATION_SUPER_FPCS_H_

#include <holo/3d/registration/details/indexed_normal_set.h>
#include <holo/3d/registration/details/intersection_functor.h>
#include <holo/3d/registration/details/pair_creation_functor.h>
#include <holo/3d/registration/fpcs_base.h>

#include <holo/geometry/line_segment3.h>

namespace holo
{
namespace pointcloud
{
/**
 * @brief this class aims at implementation of the super 4-points Congruent Sets (super 4PCS) algorithm
 * @details given a pair of scans, a source pointcloud P and a target pointcloud Q,in arbitrary initial poses, the
 * problem is to find the best aligning rigid transformation T , such that T (P) ≈ Q under suitable distance measure.
 * The state-of-the-art algorithm is 4PCS that utilizes particular sets of congruent points for global registration. The
 * key insight is to remove the quadratic complexity in the original 4PCS algorithm by using an efficient yet practical
 * data structure to solve the core instance problem, i.e., finding all point pairs that are within a distance range.
 * @ref Mellado N, Aiger D, Mitra N J. Super 4PCS Fast Global Pointcloud Registration via Smart Indexing[J]. Computer
 * Graphics Forum, 2015, 33(5):205-215.
 *
 * @tparam PointSourceT
 * @tparam PointTargetT
 * @tparam Scalar
 */
template <typename PointSourceT, typename PointTargetT, typename Scalar = float64_t>
class SuperFPCST : public FPCSBaseT<PointSourceT, PointTargetT, Scalar>
{
public:
    using Base      = FPCSBaseT<PointSourceT, PointTargetT, Scalar>;
    using SuperFPCS = SuperFPCST<PointSourceT, PointTargetT, Scalar>;
    using Ptr       = std::shared_ptr<SuperFPCS>;
    using ConstPtr  = std::shared_ptr<const SuperFPCS>;

    // point cloud
    using typename Base::PointCloudSource;
    using typename Base::PointCloudSourceConstPtr;
    using typename Base::PointCloudSourcePtr;
    using typename Base::PointCloudTarget;
    using typename Base::PointCloudTargetConstPtr;
    using typename Base::PointCloudTargetPtr;

    // numerics and geometry
    using typename Base::Matrix4Type;
    using typename Base::Point3Type;
    using typename Base::Pose3Type;
    using typename Base::Vector3Type;

    using typename Base::PairsVector;
    using typename Base::Parameters;
    using typename Base::Quadrilateral;

    using Base::coincidence_distance_limit_;
    using Base::Compute;
    using Base::indices_source_;
    using Base::indices_target_;
    using Base::params_;
    using Base::postCompute;
    using Base::quad_base_;
    using Base::source_;
    using Base::target_;

    using PairCreationFunctor  = internal::PairCreationFunctorT<PointSourceT, Scalar>;
    using IndexedNormalSetType = internal::IndexedNormalSetT<Point3Type, 3, 7, Scalar>;
    using LineSegement3Type    = geometry::LineSegment3T<Scalar>;
    using AngularGrid          = typename IndexedNormalSetType::AngularGrid;
    using AngularGridPtr       = typename IndexedNormalSetType::AngularGridPtr;

public:
    /**
     * @brief Construct a new Super FPCS object
     *
     * @param[in] params parameters
     */
    SuperFPCST(Parameters const& params = Parameters());

    /**
     * @brief Destroy the Super FPCS object
     *
     */
    virtual ~SuperFPCST();

protected:
    /**
     * @brief pre-computation before main algorithm
     *
     * @return bool_t
     */
    bool_t preCompute() override;

    /**
     * @brief constructs pairs of points in source, corresponding to a single pair base in target
     *
     * @param[in] base_index1 the index of the first point in target
     * @param[in] base_index2 the index of the second point in target
     * @param[out] pairs a set of pairs indices in source indices that match the pair in target
     */
    void extractPairs(size_t base_index1, size_t base_index2, PairsVector& pairs) const override;

    /**
     * @brief find congruent candidates in the source, given the invariants.
     *
     * @param[in] invariant1 the first invariant
     * @param[in] invariant2 the second invariant
     * @param[in] pairs1 the first set of pairs
     * @param[in] pairs2 the second set of pairs
     * @param[out] quadrilaterals the set of congruent quadrilateral.
     * @return bool_t return true if a non-empty set can be found. false otherwise
     */
    bool_t findCongruentQuadrilaterals(Scalar invariant1, Scalar invariant2, PairsVector const& pairs1,
                                       PairsVector const&          pairs2,
                                       std::vector<Quadrilateral>& quadrilaterals) const override;

protected:
    mutable PairCreationFunctor pair_creation_functor_;
};
}  // namespace pointcloud
}  // namespace holo
#endif  // HOLO_3D_REGISTRATION_SUPER_FPCS_H_
