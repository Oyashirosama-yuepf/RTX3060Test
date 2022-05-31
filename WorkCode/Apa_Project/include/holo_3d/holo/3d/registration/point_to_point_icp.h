/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file point2point_icp.h
 * @brief This header file defines point to point icp class
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2021-01-31
 */

#ifndef HOLO_3D_REGISTRATION_POINT_TO_POINT_ICP_H_
#define HOLO_3D_REGISTRAITON_POINT_TO_POINT_ICP_H_

#include <memory>

#include <holo/3d/common/common.h>
#include <holo/3d/registration/icp.h>

namespace holo
{
namespace pointcloud
{
/**
 * @brief Point to plane icp
 *
 * @tparam PointSourceT
 * @tparam PointTargetT
 * @tparam Scalar
 */
template <typename PointSourceT, typename PointTargetT, typename Scalar>
class PointToPointICPT : public IterativeClosestPointT<PointSourceT, PointTargetT, Scalar>
{
public:
    using Base = IterativeClosestPointT<PointSourceT, PointTargetT, Scalar>;

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

    using typename Base::Matrix3Type;
    using typename Base::Matrix4Type;
    using typename Base::Matrix6Type;
    using typename Base::MatrixXType;
    using typename Base::Point3Type;
    using typename Base::Pose3Type;
    using typename Base::Vector3Type;
    using typename Base::Vector6Type;
    using typename Base::VectorXType;

    using typename Base::Correspondence;
    using typename Base::CorrespondenceVector;
    // using IterativeClosestPointT variables
    using Base::converged_;
    using Base::correspondences_;
    using Base::euclidean_fitness_epsilon_;
    using Base::final_transformation_;
    using Base::indices_source_;
    using Base::indices_target_;
    using Base::max_correspondence_distance_;
    using Base::max_iterations_;
    using Base::min_number_correspondences_;
    using Base::previous_transformation_;
    using Base::rotation_epsilon_;
    using Base::source_;
    using Base::target_;
    using Base::transformation_;
    using Base::transformation_estimation_;
    using Base::translation_epsilon_;
    using Base::tree_source_;
    using Base::tree_target_;
    using Base::verbose_;

    using Base::postCompute;
    using Base::preCompute;

    /**
     * @brief Construct a new Point To Point ICP object
     *
     */
    PointToPointICPT();

    /**
     * @brief Destroy the Point To Point ICP object
     *
     */
    virtual ~PointToPointICPT();

    /**
     * @brief transformation computation method point2point with initial guess
     *
     * @param guess initial pose
     * @return true if success
     */
    bool_t Compute(const Pose3Type& guess = Pose3Type::Identity()) override;

protected:
    /**
     * @brief compute point correspondences in each iteration
     *
     * @param[in] cloud_src source point cloud
     * @param[in] cloud_tgt target point cloud
     * @param[in] max_dist_square maximum squared distance between correspondences
     * @return Scalar accumulated correspondences euclidean error
     */
    Scalar computeCorrespondences(PointCloudSource const& cloud_src, PointCloudTarget const& cloud_tgt,
                                  Scalar max_dist_square) override;

};  // PointToPointICPT

}  // namespace pointcloud
}  // namespace holo

#endif  // HOLO_3D_REGISTRATION_POINT_TO_POINT_ICP_H_
