/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file io.h
 * @brief This header file defines point cloud io functions
 * @author luopei(luopei@holomaitc.com)
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2020-10-15
 */

#ifndef HOLO_3D_COMMON_IO_H_
#define HOLO_3D_COMMON_IO_H_

#include <holo/3d/common/point_cloud.h>
#include <holo/3d/common/point_types.h>

namespace holo
{
namespace pointcloud
{
/**
 * @brief Save ply file
 *
 * @tparam PointT
 * @param[in] fn filename
 * @param[in] cloud point cloud
 * @param[in] binary mode flag
 * @return true if save ply success
 * @return false if save ply failed
 */
template <typename PointT>
bool_t SavePly(std::string const& fn, PointCloudT<PointT> const& cloud, bool_t binary = true);

/**
 * @brief Load ply file
 *
 * @tparam PointT
 * @param[in] fn input ply filename
 * @param[out] cloud point cloud
 * @return true if load ply success
 * @return false if load ply failed
 */
template <typename PointT>
bool_t LoadPly(std::string const& fn, PointCloudT<PointT>& cloud);

}  // namespace pointcloud
}  // namespace holo
#endif  // HOLO_3D_COMMON_IO_H_
