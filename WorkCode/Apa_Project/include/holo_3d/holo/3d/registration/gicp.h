/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file gicp.h
 * @brief This header file defines gicp class
 * @author mengzhili(mengzhili@holomatic.com)
 * @date "2021-05-26"
 */

#ifndef HOLO_3D_REGISTRATION_GICP_H_
#define HOLO_3D_REGISTRAITON_GICP_H_

#include <memory>

#include <holo/3d/common/common.h>
#include <holo/3d/registration/icp.h>

namespace holo
{
namespace pointcloud
{
/**
 * @brief generailizd icp
 *
 * @tparam PointSourceT
 * @tparam PointTargetT
 * @tparam Scalar
 */
template <typename PointSourceT, typename PointTargetT, typename Scalar>
class GICPT : public IterativeClosestPointT<PointSourceT, PointTargetT, Scalar>
{
public:
    using Base         = IterativeClosestPointT<PointSourceT, PointTargetT, Scalar>;
    using Matrix36Type = holo::numerics::MatrixT<Scalar, 3, 6>;
    using EigenMatrix3 = Eigen::Matrix<Scalar, 3, 3>;
    using EigenMatrix6 = Eigen::Matrix<Scalar, 6, 6>;
    using EigenVector3 = Eigen::Matrix<Scalar, 3, 1>;
    using EigenVector6 = Eigen::Matrix<Scalar, 6, 1>;

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

    /**
     * @brief Construct a new GICP object
     *
     */
    GICPT();

    /**
     * @brief Destroy the GICP object
     *
     */
    virtual ~GICPT();

    /**
     * @brief Set the knn search for computing covariance
     *
     * @param k
     */
    void SetSearchK(size_t k)
    {
        knn_ = k;
    }

    /**
     * @brief Get the knn search for computing covariance
     *
     * @return size_t
     */
    size_t GetSearchK() const
    {
        return knn_;
    }

    /**
     * @brief Set the source cloud covariances
     *
     * @param covariances_source
     */
    void SetSourceCovariance(std::vector<Matrix3Type> const& covariances_source)
    {
        covariances_source_ = covariances_source;
    }

    /**
     * @brief Get the source cloud covariances
     *
     * @return std::vector<Matrix3Type> const&
     */
    std::vector<Matrix3Type> const& GetSourceCovariance() const
    {
        return covariances_source_;
    }

    /**
     * @brief Set the target cloud covariances
     *
     * @param covariances_target
     */
    void SetTargetCovariance(std::vector<Matrix3Type> const& covariances_target)
    {
        covariances_target_ = covariances_target;
    }

    /**
     * @brief Get the target cloud covariances
     *
     * @return std::vector<Matrix3Type> const&
     */
    std::vector<Matrix3Type> const& GetTargetCovariance() const
    {
        return covariances_target_;
    }

    /**
     * @brief transformation computation method point2point with initial guess
     *
     * @param guess initial pose
     * @return true if success
     */
    bool_t Compute(const Pose3Type& guess = Pose3Type::Identity()) override;

protected:
    /**
     * @brief check point cloud and create kdtree
     *
     * @return true
     * @return false
     */
    bool_t preCompute() override;

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

    /**
     * @brief compute point cloud covariances
     *
     * @tparam PointT PointType
     * @param[in] cloud input point cloud
     * @param[in] kdtree input point cloud kdtree
     * @param[in] covariances output covariances
     * @return bool
     */
    template <typename PointT>
    bool_t computeCovariance(std::shared_ptr<PointCloudT<PointT> > const& cloud, KdTreeT<PointT, Scalar>& kdtree,
                             std::vector<Matrix3Type>& covariances);

private:
    size_t                   knn_;                 ///< k neighbors for computing covariances
    std::vector<Matrix3Type> covariances_source_;  ///< source point cloud covariances
    std::vector<Matrix3Type> covariances_target_;  ///< target point cloud covariances
    std::vector<Matrix3Type> mahalanobis_;         ///< mahalanobis distance between correspondences

};  // GICPT

}  // namespace pointcloud
}  // namespace holo

#endif  // HOLO_3D_REGISTRATION_GICP_H_
