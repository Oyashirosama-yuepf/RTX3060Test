/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file fpcs.h
 * @brief This header file defines fpcs class
 * @author zhaojiaxing(zhaojiaxing@holomatic.com)
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2021-03-11
 */

#ifndef HOLO_3D_REGISTRATION_FPCS_H_
#define HOLO_3D_REGISTRATION_FPCS_H_

#include <holo/3d/registration/fpcs_base.h>

namespace holo
{
namespace pointcloud
{
template <typename PointSourceT, typename PointTargetT, typename Scalar = float64_t>
class FPCST : public FPCSBaseT<PointSourceT, PointTargetT, Scalar>
{
public:
    using Base = FPCSBaseT<PointSourceT, PointTargetT, Scalar>;

    // point cloud
    using typename Base::PointCloudSource;
    using typename Base::PointCloudSourceConstPtr;
    using typename Base::PointCloudSourcePtr;
    using typename Base::PointCloudTarget;
    using typename Base::PointCloudTargetConstPtr;
    using typename Base::PointCloudTargetPtr;

    // kdtree
    using typename Base::KdTreeSource;
    using typename Base::KdTreeSourceConstPtr;
    using typename Base::KdTreeSourcePtr;
    using typename Base::KdTreeTarget;
    using typename Base::KdTreeTargetConstPtr;
    using typename Base::KdTreeTargetPtr;

    // numerics and geometry
    using typename Base::Matrix4Type;
    using typename Base::Point3Type;
    using typename Base::Pose3Type;
    using typename Base::Vector3Type;

    using typename Base::PairsVector;
    using typename Base::Parameters;
    using typename Base::Quadrilateral;

    using Base::coincidence_distance_limit_;
    using Base::indices_source_;
    using Base::indices_target_;
    using Base::params_;
    using Base::source_;
    using Base::target_;

    /**
     * @brief Construct a new FPCS object
     *
     * @param[in] params parameters
     */
    FPCST(Parameters const& params = Parameters());

    /**
     * @brief Destroy the FPCS object
     *
     */
    virtual ~FPCST();

protected:
    /**
     * @brief constructs pairs of points in source, corresponding to a single pair base in target
     *
     * @param[in] base_index1 the index of the first point in target
     * @param[in] base_index2 the index of the second point in target
     * @param[out] pairs a set of pairs in source that match the pair in target
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
};
}  // namespace pointcloud
}  // namespace holo

#endif  // HOLO_3D_REGISTRATION_FPCS_H_
