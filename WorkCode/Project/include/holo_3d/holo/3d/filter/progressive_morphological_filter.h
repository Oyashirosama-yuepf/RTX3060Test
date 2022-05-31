/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file approximate_progressive_morphological_filter.h
 * @brief This header file defines morphological filter class .
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2021-07-02
 */

#ifndef HOLO_3D_FILTER_APPROXIMATE_PROGRESSIVE_MORPHOLOGICAL_FILTER_H
#define HOLO_3D_FILTER_APPROXIMATE_PROGRESSIVE_MORPHOLOGICAL_FILTER_H

#include <holo/3d/common/point_cloud.h>
#include <holo/3d/filter/filter.h>

namespace holo
{
namespace pointcloud
{
template <typename PointT>
class ProgressiveMorphologicalFilterT : public FilterIndicesT<PointT>
{
public:
    typedef float64_t              Scalar;
    typedef FilterIndicesT<PointT> Base;

    using Base::cloud_;
    using Base::kept_indices_;
    using Base::removed_indices_;
    using typename Base::PointCloud;
    using typename Base::PointCloudConstPtr;
    using typename Base::PointCloudPtr;

    struct Parameters
    {
        /// @brief Maximum window size to be used in filtering ground returns.
        int32_t max_window_size;
        /// @brief Slope value to be used in computing the height threshold.
        Scalar slope;
        /// @brief Maximum height above the parameterized ground surface to be considered a ground return.
        Scalar max_distance;
        /// @brief  Initial height above the parameterized ground surface to be considered a ground return.
        Scalar initial_distance;
        /// @brief Cell size.
        Scalar cell_size;

        Parameters() : max_window_size(33), slope(0.7), max_distance(10.0), initial_distance(0.15), cell_size(1.0)
        {
        }
    };

public:
    /**
     * @brief Construct
     *
     * @param[in] params parameters
     */
    ProgressiveMorphologicalFilterT(const Parameters& params = Parameters());

    virtual ~ProgressiveMorphologicalFilterT();

    /**
     * @brief Check if an input point cloud is given, input parameters is valid
     *
     * @return bool_t
     */
    bool_t PreCompute() override;

    /**
     * @brief Calls the progressive morphological filtering method and return the filtered point cloud
     *
     * @return PointCloudPtr the resultant filtered point cloud
     */
    PointCloudPtr Compute() override;

    /**
     * @brief call this after computation is done
     */
    bool_t PostCompute() override;

private:
    Parameters          params_;  ///< progressive  morphological filtering  paramters
    std::vector<size_t> indices_;
};

}  // namespace pointcloud

}  // namespace holo
#endif
