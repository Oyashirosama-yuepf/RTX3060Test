/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file box_filter.h
 * @brief This header file defines box filter
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2020-12-03
 */

#ifndef HOLO_3D_FILTER_BOX_FILTER_H_
#define HOLO_3D_FILTER_BOX_FILTER_H_

#include <holo/3d/filter/filter.h>
#include <holo/geometry/box3.h>

namespace holo
{
namespace pointcloud
{
/**
 * @brief Box filter class, will allows the user to filter all the data inside of a given box
 *
 * @tparam PointT
 */
template <typename PointT>
class BoxFilterT : public FilterIndicesT<PointT>
{
public:
    using Base       = FilterIndicesT<PointT>;
    using ScalarType = typename PointT::ScalarType;
    using BoxType    = geometry::Box3T<ScalarType>;
    using Point3Type = geometry::Point3T<ScalarType>;
    using Base::cloud_;
    using Base::kept_indices_;
    using Base::removed_indices_;
    using typename Base::PointCloud;
    using typename Base::PointCloudPtr;

    /**
     * @brief Construct a new Box Filter with a box
     *
     * @param box input box
     * @param keep keep flag remove points that are in the box if set true
     */
    BoxFilterT(BoxType const& box, bool_t keep = true);

    /**
     * @brief Emptry destructor
     *
     */
    virtual ~BoxFilterT();

    /**
     * @brief Calls the box filtering method and return the filtered point cloud
     *
     * @return PointCloudPtr the resultant filtered point cloud
     */
    PointCloudPtr Compute() override;

protected:
    using Base::PostCompute;
    using Base::PreCompute;

private:
    BoxType box_;   ///< box3 for filtering
    bool_t  keep_;  ///< false to remove points that are in the box, otherwise remove points that are outside the box
};
}  // namespace pointcloud
}  // namespace holo
#endif
