/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file point_filter.hpp
 * @brief Implementation of point filter
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2020-12-02
 */

#ifndef HOLO_3D_FILTER_POINT_FILTER_HPP_
#define HOLO_3D_FILTER_POINT_FILTER_HPP_

#include <holo/3d/filter/point_filter.h>

namespace holo
{
namespace pointcloud
{
template <typename PointT>
typename PointFilterT<PointT>::PointCloudPtr PointFilterT<PointT>::Compute()
{
    if (!PreCompute())
    {
        std::string s = "PreCompute failed";
        LOG(ERROR) << s;
        return nullptr;
    }

    size_t        num = cloud_->size();
    PointCloudPtr result(new PointCloud);
    result->SetTimestamp(cloud_->GetTimestamp());
    result->SetCoordinate(cloud_->GetCoordinate());
    result->SetPose(cloud_->GetPose());
    result->reserve(num);

    for (size_t i = 0; i < num; ++i)
    {
        PointT const& p   = cloud_->at(i);
        bool          ret = false;

        for (size_t j = 0; j < checkers_.size(); ++j)
        {
            ret |= checkers_[j]->template operator()(p);
        }

        if (ret)
        {
            continue;
        }

        result->push_back(p);
    }

    if (!PostCompute())
    {
        std::string s = "PostCompute failed!";
        LOG(ERROR) << s;
        return nullptr;
    }

    return result;
}
}  // namespace pointcloud
}  // namespace holo

#endif  // HOLO_3D_FILTER_POINT_FILTER_
