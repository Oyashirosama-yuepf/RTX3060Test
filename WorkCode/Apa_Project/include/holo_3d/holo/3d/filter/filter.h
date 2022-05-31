/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file filter.h
 * @brief This header file defines filter base class
 * @author luopei(luopei@holomaitc.com)
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2020-12-02
 */

#ifndef HOLO_3D_FILTER_FILTER_H_
#define HOLO_3D_FILTER_FILTER_H_

#include <memory>

#include <holo/3d/common/point_cloud.h>
#include <holo/3d/common/point_types.h>
#include <holo/log/hololog.h>

namespace holo
{
namespace pointcloud
{
/**
 * @brief point cloud filter base class
 *
 * @tparam PointT
 */
template <typename PointT>
class FilterBaseT
{
public:
    using PointCloud         = PointCloudT<PointT>;
    using PointCloudPtr      = std::shared_ptr<PointCloud>;
    using PointCloudConstPtr = std::shared_ptr<const PointCloud>;

    /**
     * @brief Construct a new Filter Base
     *
     */
    FilterBaseT() : cloud_(nullptr)
    {
    }

    /**
     * @brief Construct a new Filter Base
     *
     * @param[in] cloud the input point cloud
     */
    FilterBaseT(PointCloudPtr const& cloud) : cloud_(cloud)
    {
    }

    /**
     * @brief Destroy the Filter Base
     *
     */
    virtual ~FilterBaseT()
    {
    }

    /**
     * @brief Set the input point cloud
     *
     * @param[in] cloud the input point cloud
     */
    void SetInputPointCloud(PointCloudPtr const& cloud)
    {
        cloud_ = cloud;
    }

    /**
     * @brief Get the input point cloud
     *
     * @return PointCloudPtr
     */
    PointCloudPtr GetInputPointCloud()
    {
        return cloud_;
    }

    /**
     * @brief Compute filtered point cloud
     *
     * @return PointCloudPtr point cloud after filtering
     */
    virtual PointCloudPtr Compute() = 0;

protected:
    /**
     * @brief Computations before filtering started
     *
     * @return true
     * @return false
     */
    virtual bool_t PreCompute()
    {
        if (!cloud_.get() || cloud_->size() == 0)
        {
            std::string s = "input point cloud is not set!";
            LOG(ERROR) << s;
            return false;
        }

        return true;
    }

    /**
     * @brief Computations after filtering
     *
     * @return true
     * @return false
     */
    virtual bool_t PostCompute()
    {
        return true;
    }

protected:
    PointCloudPtr cloud_;
};

/**
 * @brief Filter class that support indices operators.
 *
 * @tparam PointT
 */
template <typename PointT>
class FilterIndicesT : public FilterBaseT<PointT>
{
public:
    using Base          = FilterBaseT<PointT>;
    using PointCloud    = typename Base::PointCloud;
    using PointCloudPtr = typename Base::PointCloudPtr;
    using Base::cloud_;

    /**
     * @brief Construct a new Filter Indices
     *
     */
    FilterIndicesT() : Base()
    {
    }

    /**
     * @brief Destroy the Filter Indices
     *
     */
    virtual ~FilterIndicesT()
    {
    }

    /**
     * @brief The function should also set removed_indices_ and keep_indices_
     *
     * @return PointCloudPtr
     */
    virtual PointCloudPtr Compute() = 0;

    /**
     * @brief Get the Removed Indices
     *
     * @return std::vector<size_t>& const
     */
    std::vector<size_t> const& GetRemovedIndices() const noexcept
    {
        return removed_indices_;
    }

    /**
     * @brief Get the Kept Indices
     *
     * @return std::vector<size_t>& const
     */
    std::vector<size_t> const& GetKeptIndices() const noexcept
    {
        return kept_indices_;
    }

protected:
    /**
     * @brief Computations before filtering started
     *
     * @return true
     * @return false
     */
    virtual bool PreCompute()
    {
        return Base::PreCompute();
    }

    /**
     * @brief Computations after filtering
     *
     * @return true
     * @return false
     */
    virtual bool PostCompute()
    {
        return Base::PostCompute();
    }

protected:
    std::vector<size_t> removed_indices_;
    std::vector<size_t> kept_indices_;
};

}  // namespace pointcloud
}  // namespace holo

#endif
