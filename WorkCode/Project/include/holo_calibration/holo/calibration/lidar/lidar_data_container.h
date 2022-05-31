/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lidar_data_container.h
 * @brief This header file defines lidar data container
 * @author luopei(luopei@holomatic.com)
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2020-12-09
 */

#ifndef HOLO_CALIBRATION_LIDAR_LIDAR_DATA_CONTAINER_H_
#define HOLO_CALIBRATION_LIDAR_LIDAR_DATA_CONTAINER_H_

#include <holo/3d/filter/point_filter.h>
#include <holo/3d/filter/voxel_grid_filter.h>
#include <holo/calibration/lidar/types.h>
#include <holo/localization/tools/pose_spline.h>

namespace holo
{
namespace calibration
{
namespace lidar
{
/**
 * @brief Lidar data container contains point cloud and pose data
 *
 * @tparam PointT
 */
template <typename PointT>
class LidarDataContainerT : public DataContainerBaseT<PointCloudWrapper<PointT>, Pose3Type>
{
public:
    using PointFilter     = pointcloud::PointFilterT<PointT>;
    using VoxelFilter     = pointcloud::VoxelGridFilterT<PointNT>;
    using Wrapper         = PointCloudWrapper<PointT>;
    using Base            = DataContainerBaseT<Wrapper, Pose3Type>;
    using PointCheckerPtr = typename pointcloud::PointCheckerT<PointT>::Ptr;
    using PoseSplinePtr   = std::shared_ptr<localization::PoseSpline>;

    struct Parameters
    {
        uint32_t knn_num    = 8u;   ///< number of knn points for computing point normal
        Scalar   voxel_size = 0.5;  ///< voxel filter size
    };

    /**
     * @brief Construct a new Lidar Data Container object
     *
     * @param params
     */
    LidarDataContainerT(Parameters const& params = Parameters());

    /**
     * @brief Destroy the Lidar Data Container object
     *
     */
    virtual ~LidarDataContainerT();

    /**
     * @brief Set the Data Container data
     *
     * @param[in] clouds input point clouds
     * @param[in] pose_spline target sensor pose spline
     */
    void SetData(std::vector<PointCloudPtr> const& clouds, PoseSplinePtr const& pose_spline);

    /**
     * @brief Get container data size
     *
     * @return uint8_t
     */
    uint16_t GetDataSize() const override;

    /**
     * @brief Get the source point cloud wrapper at input index
     *
     * @param[in] index point cloud index
     * @return Wrapper const&  point cloud wrapper
     * @throws std::out_of_range if index > size()
     */
    Wrapper const& GetSource(uint16_t const index) const override;

    /**
     * @brief Get the source point cloud wrapper at input index
     *
     * @param[in] index point cloud index
     * @return Wrapper& point cloud wrapper
     * @throws std::out_of_range if index > size()
     */
    Wrapper& GetSource(uint16_t const index) override;

    /**
     * @brief Get the target pose at input index
     *
     * @param[in] index pose index
     * @return Pose3Type const& pose at input index
     * @throws std::out_of_range if index > size()
     */
    Pose3Type const& GetTarget(uint16_t const index) const override;

    /**
     * @brief Get the target pose at input index
     *
     * @param[in] index pose index
     * @return Pose3Type& pose at input index
     * @throws std::out_of_range if index > size()
     */
    Pose3Type& GetTarget(uint16_t const index) override;

    /**
     * @brief Update container status, compenstate point cloud and compute feature cloud
     *
     */
    void UpdateStatus() override;

protected:
    /**
     * @brief Set the source point cloud data
     *
     * @param[in] clouds input source point clouds
     */
    void setSourceData(std::vector<PointCloudPtr> const& clouds);

    /**
     * @brief Set the target odometry data
     *
     * @param[in] pose_spline input target pose spline ptr
     */
    void setTargetData(PoseSplinePtr const& pose_spline);

    /**
     * @brief Compenstate point cloud
     *
     * @param[in] cloud point cloud wrapper
     * @throws std::out_of_range if point's timestamp is not in timestamp range
     */
    void compensatePointCloud(Wrapper& cloud);

    /**
     * @brief Update point cloud wrapper info , compute feature cloud with normal
     *
     */
    void updatePointCloudWrapperInfo();

private:
    Parameters             params_;          ///< container parameters
    std::vector<Wrapper>   cloud_wrappers_;  ///< source cloud wrapper data
    std::vector<Pose3Type> poses_;           ///< target sensor poses at each point cloud time
    PoseSplinePtr          pose_spline_;     ///< pose spline of target sensor pose trajectory
};

}  // namespace lidar
}  // namespace calibration
}  // namespace holo

#endif
