/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lidar_calibration.h
 * @brief This header file defines lidar calibration class
 * @author luopei(luopei@holomatic.com)
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2020-12-10
 */

#ifndef HOLO_CALIBRATION_LIDAR_LIDAR_CALIBRATION_H_
#define HOLO_CALIBRATION_LIDAR_LIDAR_CALIBRATION_H_

#include <holo/calibration/common/calibration_base.h>
#include <holo/calibration/lidar/lidar_data_container.h>
#include <holo/calibration/lidar/plane_factor.h>
#include <holo/calibration/lidar/types.h>

namespace holo
{
namespace calibration
{
namespace lidar
{
/**
 * @brief Lidar calibration class, calibrate the extrinsics between lidar and the target sensor with pose
 * trajectory
 *
 * @tparam PointT Point type
 */
template <typename PointT>
class LidarCalibrationT : public CalibrationBaseT<LidarDataContainerT<PointT>>
{
public:
    using Container = LidarDataContainerT<PointT>;
    using Base      = CalibrationBaseT<Container>;
    using Wrapper   = PointCloudWrapper<PointT>;

    /**
     * @brief structure to hold the point pair info
     *
     */
    struct PointIndex
    {
        uint8_t  lidar_index;  ///< lidar container index
        uint8_t  cloud_index;  ///< point cloud index in container
        uint32_t point_index;  ///< point index in point cloud
    };

    using PointPair  = std::pair<PointIndex, PointIndex>;
    using PointPairs = std::vector<PointPair>;

    /**
     * @brief lidar calibration parameters
     *
     */
    struct Parameters
    {
        uint32_t max_iterations            = 5u;      ///< max iterations of lidar calibration
        uint32_t max_point_pairs_pcd       = 1000u;   ///< max point pairs between two pcds
        uint32_t max_point_pairs_container = 10000u;  ///< max point pairs in/between containers
        uint32_t knn_num                   = 8u;      ///< number of knn points for computing point normal
        Scalar   voxel_size                = 0.5;     ///< voxel size of voxel filtering
        Scalar   max_corr_dist             = 1.0;     ///< max correspondence distance, unit(m)
        Scalar   max_angle                 = 45.0;    ///< max angle between two point's normal, unit(degree)
        Scalar   plane_noise               = 0.1;     ///< plane factor noise, unit(m)
        Scalar   z_noise                   = 0.05;    ///< prior z value noise, unit(m)
    };

    /**
     * @brief Construct a new Lidar Calibration object with parameters
     *
     * @param[in] params
     */
    LidarCalibrationT(Parameters const& params = Parameters());

    /**
     * @brief Construct a new Lidar Calibration object with containers and parameters
     *
     * @param[in] containers lidar data containers
     * @param[in] params calibration parameters
     */
    LidarCalibrationT(std::vector<Container> const& containers, Parameters const& params = Parameters());

    /**
     * @brief Destructor
     *
     */
    virtual ~LidarCalibrationT();

    /**
     * @brief Set the containers
     *
     * @param[in] containers
     */
    void SetContainers(std::vector<Container> const& containers);

    /**
     * @brief Get the container size
     *
     * @return uint8_t
     */
    uint8_t GetContainerNum() const override;

    /**
     * @brief Get the container in case we just have one container
     *
     * @return Container const&
     */
    Container const& GetContainer() const override;

    /**
     * @brief Get the container in case we just have one container
     *
     * @return Container&
     */
    Container& GetContainer() override;

    /**
     * @brief Get the container by index
     *
     * @param[in] index container index
     * @return Container const&
     */
    Container const& GetContainer(uint8_t const index) const override;

    /**
     * @brief Get the Container object
     *
     * @param[in] index
     * @return Container&
     */
    Container& GetContainer(uint8_t const index) override;

    /**
     * @brief Calls the calibration method
     *
     * @return bool_t
     */
    bool_t Compute() override;

    /**
     * @brief Evaluate extrinsic of lidar sensors in container
     *
     * @return Scalar mean point2plane error
     */
    Scalar Evaluate();

protected:
    /**
     * @brief compute point pairs
     *
     */
    void computePointPairs();

    /**
     * @brief compute point correspondences in one container
     *
     * @param[in] container_index
     */
    void computePointPairsInOneContainer(uint8_t container_index);

    /**
     * @brief compute point correspondences between two containers
     *
     * @param[in] src_container_index
     * @param[in] tgt_container_index
     */
    void computePointPairsBetweenContainer(uint8_t src_container_index, uint8_t tgt_container_index);

    /**
     * @brief base function to compute point pairs
     *
     * @param[in] source source cloud wrapper
     * @param[in] src_container_index source container index
     * @param[in] src_index source cloud wrapper index
     * @param[in] target target cloud wrapper
     * @param[in] tgt_container_index target container index
     * @param[in] tgt_index target cloud wrapper index
     */
    void computePointPairsBase(Wrapper const& source, uint8_t src_container_index, uint8_t src_index,
                               Wrapper const& target, uint8_t tgt_container_index, uint8_t tgt_index);

    /**
     * @brief evaluate lidar calibration results
     *
     * @return Scalar mean point2plane distance
     */
    Scalar evaluate();

private:
    Parameters             params_;                      ///< calibration parameters
    std::vector<Container> lidar_containers_;            ///< lidar data containers
    PointPairs             point_pairs_one_container_;   ///< point pairs in one container
    PointPairs             point_pairs_two_containers_;  ///< point pairs between two containers
};
}  // namespace lidar
}  // namespace calibration
}  // namespace holo

#endif
