/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file feature.hpp
 * @brief define FeatureBaseT class
 * @author luopei(luopei@holomatic.com)
 * @author jiangzheng(jiangzheng@holomatic.com)
 * @date 2021-10-22
 */

#ifndef  HOLO_3D_FEATURE_FEATURE_HPP_
#define  HOLO_3D_FEATURE_FEATURE_HPP_

#include <functional>
#include <holo/3d/feature/feature.h>

namespace holo
{
namespace pointcloud
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT, typename FeatureT>
bool_t FeatureBaseT<PointT, FeatureT>::PreCompute()
{
    if (!cloud_.get() || cloud_->size() == 0)
    {
        std::string s = "input point cloud is not set!";
        LOG(ERROR) << s;
        return false;
    }

    if (indices_.size() == 0)
    {
        std::string s = "empty indices!";
        LOG(ERROR) << s;
        return false;
    }

    // init the kdtree if it's not set
    if (!tree_.get())
    {
        tree_.reset(new KdTreeType());
        tree_->SetInputPointCloud(cloud_);
    }
    else if (tree_->GetInputPointCloud() != cloud_)
    {
        tree_->SetInputPointCloud(cloud_);
    }

    if (search_method_ == SearchMethod::RADIUS)
    {
        // radius search
        if (search_parameter_ <= 0)
        {
            std::string s = "invalid search_parameter_, radius : ";
            LOG(ERROR) << s << search_parameter_;
            return false;
        }

        search_function_ = std::bind(&FeatureBaseT::searchKdTreeRadius, this,
                                   std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,
                                   std::placeholders::_4);
    }
    else
    {
        // knn search
        if (search_parameter_ <= 0)
        {
            std::string s = "invalid search_parameter_, knn : ";
            LOG(ERROR) << s << search_parameter_;
            return false;
        }

        search_function_ = std::bind(&FeatureBaseT::searchKdTreeK, this,
                                   std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,
                                   std::placeholders::_4);
    }

    return true;
}

} // namespace pointcloud

} // namespace holo

#endif   /* ----- #ifndef HOLO_3D_FEATURE_FEATURE_HPP_  ----- */
