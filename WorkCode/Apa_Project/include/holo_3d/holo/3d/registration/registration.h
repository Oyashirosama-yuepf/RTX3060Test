/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file registration.h
 * @brief This header file defines registration base class
 * @author luopei(luopei@holomaitc.com)
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2021-01-22
 */

#ifndef HOLO_3D_REGISTRATION_REGISTRATION_H_
#define HOLO_3D_REGISTRATION_REGISTRATION_H_

#include <numeric>

#include <holo/3d/common/kdtree.h>
#include <holo/3d/common/point_cloud.h>
#include <holo/3d/common/point_types.h>
#include <holo/3d/common/point_traits.h>
#include <holo/3d/registration/transformation_estimation.h>
#include <holo/geometry/pose3.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>

namespace holo
{
namespace pointcloud
{
/**
 * @brief Registration base class
 *
 * @tparam PointSourceT
 * @tparam PointTargetT
 * @tparam Scalar
 */
template <typename PointSourceT, typename PointTargetT, typename Scalar = float64_t>
class RegistrationBaseT
{
public:
    // point cloud
    using PointCloudSource         = PointCloudT<PointSourceT>;
    using PointCloudTarget         = PointCloudT<PointTargetT>;
    using PointCloudSourcePtr      = std::shared_ptr<PointCloudSource>;
    using PointCloudSourceConstPtr = std::shared_ptr<const PointCloudSource>;
    using PointCloudTargetPtr      = std::shared_ptr<PointCloudTarget>;
    using PointCloudTargetConstPtr = std::shared_ptr<const PointCloudTarget>;

    // kdtree
    using KdTreeSource         = KdTreeT<PointSourceT, Scalar>;
    using KdTreeTarget         = KdTreeT<PointTargetT, Scalar>;
    using KdTreeSourcePtr      = std::shared_ptr<KdTreeSource>;
    using KdTreeTargetPtr      = std::shared_ptr<KdTreeTarget>;
    using KdTreeSourceConstPtr = std::shared_ptr<const KdTreeSource>;
    using KdTreeTargetConstPtr = std::shared_ptr<const KdTreeTarget>;

    // numerics and geometry
    using Pose3Type   = holo::geometry::Pose3T<Scalar>;
    using Point3Type  = holo::geometry::Point3T<Scalar>;
    using Vector3Type = holo::numerics::Vector3T<Scalar>;
    using Vector6Type = holo::numerics::Vector6T<Scalar>;
    using VectorXType = holo::numerics::VectorXT<Scalar>;
    using Matrix3Type = holo::numerics::Matrix3T<Scalar>;
    using Matrix4Type = holo::numerics::Matrix4T<Scalar>;
    using Matrix6Type = holo::numerics::Matrix6T<Scalar>;
    using MatrixXType = holo::numerics::MatrixXT<Scalar>;

    using Correspondence       = std::pair<int32_t, int32_t>;
    using CorrespondenceVector = std::vector<Correspondence>;

    using TransformationEstimation         = TransformationEstimationBaseT<PointSourceT, PointTargetT, Scalar>;
    using TransformationEstimationPtr      = std::shared_ptr<TransformationEstimation>;
    using TransformationEstimationConstPtr = std::shared_ptr<const TransformationEstimation>;

    /**
     * @brief Construct a new Registration Base object
     *
     */
    RegistrationBaseT()
      : source_(nullptr)
      , target_(nullptr)
      , tree_source_(nullptr)
      , tree_target_(nullptr)
      , max_iterations_(0)
      , max_correspondence_distance_(1.0)
      , min_number_correspondences_(3)
      , rotation_epsilon_(1e-5)
      , translation_epsilon_(1e-5)
      , converged_(false)
    {
        static_assert(std::is_floating_point<typename PointSourceT::ScalarType>::value,
                      "PointSourceT::Scalar is not a floating-point type!");
        static_assert(std::is_floating_point<typename PointTargetT::ScalarType>::value,
                      "PointTargetT::Scalar is not a floating-point type!");
    }

    /**
     * @brief Destroy the Registration Base object
     *
     */
    virtual ~RegistrationBaseT()
    {
    }

    /**
     * @brief Get the Source Point Cloud
     *
     * @return PointCloudSourceConstPtr
     */
    PointCloudSourceConstPtr GetSourcePointCloud() const
    {
        return source_;
    }

    /**
     * @brief Set the Source Point Cloud
     *
     * @param source
     */
    void SetSourcePointCloud(PointCloudSourcePtr const& source)
    {
        source_ = source;
        // since we reset input point cloud, we have to reset the indices too.
        indices_source_.resize(source_->size());
        std::iota(indices_source_.begin(), indices_source_.end(), 0);
    }

    /**
     * @brief Get the Target Point Cloud
     *
     * @return PointCloudTargetConstPtr
     */
    PointCloudTargetConstPtr GetTargetPointCloud() const
    {
        return target_;
    }

    /**
     * @brief Set the Target Point Cloud
     *
     * @param target
     */
    void SetTargetPointCloud(PointCloudTargetPtr const& target)
    {
        target_ = target;
        // since we reset input point cloud, we have to reset the indices too.
        indices_target_.resize(target_->size());
        std::iota(indices_target_.begin(), indices_target_.end(), 0);
    }

    /**
     * @brief Get the Source Tree
     *
     * @return const KdTreeSourceConstPtr
     */
    const KdTreeSourceConstPtr GetSourceTree() const
    {
        return tree_source_;
    }

    /**
     * @brief Set the Source Tree
     *
     * @param tree
     */
    void SetSourceTree(KdTreeSourcePtr const& tree)
    {
        tree_source_ = tree;
    }

    /**
     * @brief Get the Target Tree
     *
     * @return const KdTreeTargetConstPtr
     */
    const KdTreeTargetConstPtr GetTargetTree() const
    {
        return tree_target_;
    }

    /**
     * @brief Set the Target Tree
     *
     * @param tree
     */
    void SetTargetTree(const KdTreeTargetPtr& tree)
    {
        tree_target_ = tree;
    }

    /**
     * @brief Get the Source Indices
     *
     * @return const std::vector<size_t>&
     */
    const std::vector<size_t>& GetSourceIndices() const
    {
        return indices_source_;
    }

    /**
     * @brief Set the Source Indices
     *
     * @param indices
     */
    void SetSourceIndices(const std::vector<size_t>& indices)
    {
        indices_source_ = indices;
    }

    /**
     * @brief Get the Target Indices
     *
     * @return const std::vector<uint32_t>&
     */
    const std::vector<size_t>& GetTargetIndices() const
    {
        return indices_target_;
    }

    /**
     * @brief Set the Target Indices
     *
     * @param indices
     */
    void SetTargetIndices(const std::vector<size_t>& indices)
    {
        indices_target_ = indices;
    }

    /**
     * @brief Get the rotation epsilon (maximum allowable rotation difference between two consecutive
     * transformations)
     *
     * @return Scalar
     */
    Scalar GetRotationEpsilon() const
    {
        return rotation_epsilon_;
    }

    /**
     * @brief Set the rotation epsilon (maximum allowable rotation difference between two consecutive
     * transformations)
     *
     * @param epsilon
     */
    void SetRotationEpsilon(const Scalar& epsilon)
    {
        rotation_epsilon_ = epsilon;
    }

    /**
     * @brief Get the translation epsilon (maximum allowable translation squared difference between two consecutive
     * transformations)
     *
     * @return Scalar
     */
    Scalar GetTranslationEpsilon() const
    {
        return translation_epsilon_;
    }

    /**
     * @brief Set the translation epsilon (maximum allowable translation squared difference between two consecutive
     * transformations)
     *
     * @param epsilon
     */
    void SetTranslationEpsilon(const Scalar& epsilon)
    {
        translation_epsilon_ = epsilon;
    }

    /**
     * @brief Get the maximum number of iterations the optimization should run for
     *
     * @return size_t
     */
    size_t GetMaxIteration() const
    {
        return max_iterations_;
    }

    /**
     * @brief Set the maximum number of iterations the optimization should run for
     *
     * @param max_iterations
     */
    void SetMaxIteration(const size_t& max_iterations)
    {
        max_iterations_ = max_iterations;
    }

    /**
     * @brief Set the maximum distance threshold between two correspondent point in source and target.
     *
     * @return Scalar
     */
    Scalar GetMaxCorrespondenceDistance() const
    {
        return max_correspondence_distance_;
    }

    /**
     * @brief Set the maximum distance threshold between two correspondent point in source and target. If the distance
     * is larger than this threshold, the points will be ignored in the alignment process.
     *
     * @param distance the maximum distance threshold between a point and its nearest neighbor correspondence
     */
    void SetMaxCorrespondenceDistance(const Scalar& distance)
    {
        max_correspondence_distance_ = distance;
    }

    /**
     * @brief Set the Transformation Estimation Method
     *
     * @param te
     */
    void SetTransformationEstimation(TransformationEstimationPtr const& te)
    {
        transformation_estimation_ = te;
    }

    /**
     * @brief Get the Final Transformation
     *
     * @return const Pose3Type&
     */
    const Pose3Type& GetFinalTransformation() const
    {
        return final_transformation_;
    }

    /**
     * @brief Get the Correspondences
     *
     * @return CorrespondenceVector const&
     */
    CorrespondenceVector const& GetCorrespondences() const
    {
        return correspondences_;
    }

    /**
     * @brief Abstract transformation computation method with initial guess
     *
     * @param guess
     * @return true if success
     */
    virtual bool_t Compute(Pose3Type const& guess = Pose3Type::Identity()) = 0;

protected:
    /**
     * @brief precompute before computation
     *
     * @return bool_t
     */
    virtual bool_t preCompute() = 0;

    /**
     * @brief postcompute after computation
     *
     * @return bool_t
     */
    virtual bool_t postCompute() = 0;

protected:
    PointCloudSourcePtr source_;          ///< the input source point cloud
    PointCloudTargetPtr target_;          ///< the input target point cloud
    KdTreeSourcePtr     tree_source_;     ///< the kdtree for source point cloud
    KdTreeTargetPtr     tree_target_;     ///< the kdtree for target point cloud
    std::vector<size_t> indices_source_;  ///< point indices for source point cloud
    std::vector<size_t> indices_target_;  ///< point indices for target point cloud
    size_t              max_iterations_;  ///< the maximum number of iterations the registration algorithm can run for.
    Scalar              max_correspondence_distance_;  ///< the maximum correspondence distance used in kdtree search.
    size_t min_number_correspondences_;  ///< the minimum number of correspondences to estimate the transformation
    Scalar rotation_epsilon_;            ///< the maximum rotation difference between two consecutive transformations
    Scalar translation_epsilon_;         ///< the maximum translation difference between two consecutive transformations
    bool_t converged_;                   ///< bool value indicate whether the algorithm converged or not
    CorrespondenceVector        correspondences_;            ///< correspondences
    Pose3Type                   final_transformation_;       ///< final transformation
    Matrix6Type                 final_covariance_;           ///< final covariance
    Pose3Type                   previous_transformation_;    ///< previous transformation
    Pose3Type                   transformation_;             ///< transformation in one iteration
    TransformationEstimationPtr transformation_estimation_;  ///< pointer to transformation estimation method
};

}  // namespace pointcloud
}  // namespace holo

#endif  // HOLO_3D_REGISTRATION_REGISTRATION_H_
