/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file box_filter.hpp
 * @brief Implementation of box filter
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2020-12-03
 */

#ifndef HOLO_3D_FILTER_BOX_FILTER_HPP_
#define HOLO_3D_FILTER_BOX_FILTER_HPP_

#include <holo/3d/filter/box_filter.h>

namespace holo
{
namespace pointcloud
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
BoxFilterT<PointT>::BoxFilterT(BoxType const& box, bool_t keep) : box_(box), keep_(keep)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
BoxFilterT<PointT>::~BoxFilterT()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
typename BoxFilterT<PointT>::PointCloudPtr BoxFilterT<PointT>::Compute()
{
    if (!PreCompute())
    {
        LOG(ERROR) << "PreCompute failed!";
        return nullptr;
    }

    PointCloudPtr output(new PointCloud);
    output->reserve(cloud_->size());

    for (size_t i = 0U; i < cloud_->size(); ++i)
    {
        PointT const& pt        = cloud_->at(i);
        bool          contained = box_.Contains(Point3Type(pt[0], pt[1], pt[2]));

        if ((contained && keep_) || (!contained && !keep_))
        {
            kept_indices_.push_back(i);
            output->push_back(pt);
        }
        else
        {
            removed_indices_.push_back(i);
        }
    }

    if (!PostCompute())
    {
        LOG(ERROR) << "PostCompute failed!";
        return nullptr;
    }

    return output;
}

}  // namespace pointcloud
}  // namespace holo
#endif
