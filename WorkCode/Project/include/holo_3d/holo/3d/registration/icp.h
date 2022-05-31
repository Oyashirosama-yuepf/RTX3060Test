/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file icp.h
 * @brief This header file defines icp base class
 * @author luopei(luopei@holomaitc.com)
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2021-01-31
 */

#ifndef HOLO_3D_REGISTRATION_ICP_H_
#define HOLO_3D_REGISTRATION_ICP_H_

#include <holo/3d/registration/registration.h>

namespace holo
{
namespace pointcloud
{
template <typename PointSourceT, typename PointTargetT, typename Scalar = float64_t>
class IterativeClosestPointT : public RegistrationBaseT<PointSourceT, PointTargetT, Scalar>
{
public:
    using Base = RegistrationBaseT<PointSourceT, PointTargetT, Scalar>;
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

    // member variables
    using Base::converged_;
    using Base::correspondences_;
    using Base::final_covariance_;
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

    /**
     * @brief Construct a new Iterative Closest Point object
     *
     */
    IterativeClosestPointT();
    /**
     * @brief Destroy the Iterative Closest Point object
     *
     */
    virtual ~IterativeClosestPointT();

    /**
     * @brief Set the maximum allowed Euclidean error between two consecutive steps in the ICP loop.the error is
     * estimated as the sum of the differences between correspondences in an Euclidean sense, divided by the number of
     * correspondences.
     * @param epsilon
     */
    void SetEuclideanFitnessEpsilon(Scalar epsilon)
    {
        euclidean_fitness_epsilon_ = epsilon;
    }

    /**
     * @brief Get the maximum allowed Euclidean error epsilon
     *
     * @return Scalar
     */
    Scalar GetEuclideanFitnessEpsilon() const
    {
        return euclidean_fitness_epsilon_;
    }

    /**
     * @brief Set the Verbose flag
     *
     * @param verbose
     */
    void SetVerbose(bool_t verbose = true)
    {
        verbose_ = verbose;
    }

    /**
     * @brief Abstract transformation computation method with initial guess
     *
     * @param guess
     * @return true if success
     */
    virtual bool_t Compute(const Pose3Type& guess = Pose3Type::Identity()) = 0;

protected:
    /**
     * @brief check point cloud and create kdtree
     *
     * @return true
     * @return false
     */
    bool_t preCompute() override;

    /**
     * @brief post computation after transformation estimatiion
     *
     * @return true
     * @return false
     */
    bool_t postCompute() override;

    /**
     * @brief compute point correspondences in each iteration
     *
     * @param[in] cloud_src source point cloud
     * @param[in] cloud_tgt target point cloud
     * @param[in] max_dist_square maximum squared distance between correspondences
     * @return Scalar accumulated correspondences euclidean error
     */
    virtual Scalar computeCorrespondences(PointCloudSource const& cloud_src, PointCloudTarget const& cloud_tgt,
                                          Scalar max_dist_square) = 0;

protected:
    Scalar euclidean_fitness_epsilon_;  ///< the maximum allowed Euclidean error between two consecutive icp steps
    bool_t verbose_;                    ///< verbose flag
};

}  // namespace pointcloud
}  // namespace holo

#include "impl/icp.hpp"

#endif  // HOLO_3D_REGISTRATION_ICP_H_
