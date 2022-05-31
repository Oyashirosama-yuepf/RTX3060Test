/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file icp.hpp
 * @brief This header file defines implementation of icp base class
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2021-01-31
 */

#ifndef HOLO_3D_REGISTRATION_ICP_HPP_
#define HOLO_3D_REGISTRATION_ICP_HPP_

#include <holo/3d/registration/icp.h>

namespace holo
{
namespace pointcloud
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
IterativeClosestPointT<PointSourceT, PointTargetT, Scalar>::IterativeClosestPointT()
  : Base(), euclidean_fitness_epsilon_(1e-5), verbose_(false)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
IterativeClosestPointT<PointSourceT, PointTargetT, Scalar>::~IterativeClosestPointT()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
bool_t IterativeClosestPointT<PointSourceT, PointTargetT, Scalar>::preCompute()
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

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
bool_t IterativeClosestPointT<PointSourceT, PointTargetT, Scalar>::postCompute()
{
    return true;
}

}  // namespace pointcloud

}  // namespace holo

#endif /* ----- #ifndef HOLO_3D_REGISTRATION_ICP_HPP_  ----- */
