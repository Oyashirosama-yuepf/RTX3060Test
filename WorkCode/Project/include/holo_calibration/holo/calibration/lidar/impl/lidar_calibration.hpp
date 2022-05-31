/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lidar_calibration.hpp
 * @brief Implementation of lidar calibration
 * @author luopei(luopei@holomatic.com)
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2020-12-11
 */

#ifndef HOLO_CALIBRATION_LIDAR_LIDAR_CALIBRATION_HPP_
#define HOLO_CALIBRATION_LIDAR_LIDAR_CALIBRATION_HPP_

#include <gtsam/geometry/Pose3.h>
#include <gtsam/inference/Symbol.h>
#include <gtsam/linear/NoiseModel.h>
#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/nonlinear/Values.h>
#include <holo/3d/common/io.h>
#include <holo/calibration/lidar/lidar_calibration.h>

namespace holo
{
namespace calibration
{
namespace lidar
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
LidarCalibrationT<PointT>::LidarCalibrationT(Parameters const& params) : params_(params)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
LidarCalibrationT<PointT>::LidarCalibrationT(std::vector<Container> const& containers, Parameters const& params)
  : params_(params), lidar_containers_(containers)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
LidarCalibrationT<PointT>::~LidarCalibrationT()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
void LidarCalibrationT<PointT>::SetContainers(std::vector<Container> const& containers)
{
    lidar_containers_ = containers;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
uint8_t LidarCalibrationT<PointT>::GetContainerNum() const
{
    return lidar_containers_.size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
LidarDataContainerT<PointT> const& LidarCalibrationT<PointT>::GetContainer() const
{
    if (lidar_containers_.empty())
    {
        std::string msg = "LidarCalibrationT: query container out of bounds!";
        LOG(ERROR) << msg;
        throw holo::exception::OutOfRangeException(msg);
    }

    return lidar_containers_[0];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
LidarDataContainerT<PointT>& LidarCalibrationT<PointT>::GetContainer()
{
    if (lidar_containers_.empty())
    {
        std::string msg = "LidarCalibrationT: query container out of bounds!";
        LOG(ERROR) << msg;
        throw holo::exception::OutOfRangeException(msg);
    }

    return lidar_containers_[0];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
LidarDataContainerT<PointT> const& LidarCalibrationT<PointT>::GetContainer(uint8_t const index) const
{
    if (index >= lidar_containers_.size())
    {
        std::string msg = "LidarCalibrationT: query container out of bounds!";
        LOG(ERROR) << msg;
        throw holo::exception::OutOfRangeException(msg);
    }
    return lidar_containers_[index];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
LidarDataContainerT<PointT>& LidarCalibrationT<PointT>::GetContainer(uint8_t const index)
{
    if (index >= lidar_containers_.size())
    {
        std::string msg = "LidarCalibrationT: query container out of bounds!";
        LOG(ERROR) << msg;
        throw holo::exception::OutOfRangeException(msg);
    }
    return lidar_containers_[index];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
bool_t LidarCalibrationT<PointT>::Compute()
{
    uint32_t max_iterations = params_.max_iterations;
    Scalar   plane_noise    = params_.plane_noise;
    Scalar   mean_plane_factors =
        static_cast<Scalar>(2 * params_.max_point_pairs_container) / static_cast<Scalar>(lidar_containers_.size());
    Scalar z_noise = params_.z_noise / std::sqrt(mean_plane_factors);

    // store initial poses
    std::vector<Pose3Type> init_poses;

    for (uint32_t k = 0; k < lidar_containers_.size(); ++k)
    {
        init_poses.push_back(GetContainer(k).GetExtrinsic());
    }

    for (uint32_t i = 0U; i < max_iterations; ++i)
    {
        gtsam::Values               initial_values;
        gtsam::NonlinearFactorGraph graph;
        bool_t is_primary_lidar     = true;

        for (uint32_t k = 0; k < lidar_containers_.size(); ++k)
        {
            Container& container = GetContainer(k);
            container.UpdateStatus();  ///< compenstate point cloud and compute normal feature cloud

            Pose3Type const& pose = container.GetExtrinsic();

            // add initial values
            gtsam::Matrix4 mat_gtsam;
            memcpy(mat_gtsam.data(), pose.ToMatrix().GetData(), sizeof(Scalar) * 16U);
            initial_values.insert(k, gtsam::Pose3(mat_gtsam));

            /**
             * @details Due to the plane motion, the LiDAR-Sensor calibration process lacks the z-direction constraint.
             * when calibrating multiple sensor simultaneously, since the primary lidar will serve as an intermediate
             * term for subsequent calibration(such as camera-lidar), so we provide an prior on it
             * 
             * @note if adding a strong prior to the external parameter Z of all sensors, due to the error of initial
             *  measurements, the result of point cloud registration will be stratified in the Z direction
             */
            if (is_primary_lidar)
            {
                is_primary_lidar           = false;                     // update primary lidar's status
                Pose3Type const& init_pose = init_poses[k];
                ZFactor          factor(z_noise, k, init_pose.GetZ());

                gtsam::NoiseModelFactor::shared_ptr gtsam_factor;
                gtsam_factor.reset(static_cast<gtsam::NoiseModelFactor*>(factor.GetZFactor()));
                graph.push_back(gtsam_factor);
            }
        }

        // compute correspondences
        computePointPairs();

        LOG(INFO) << "point pairs in one container: " << point_pairs_one_container_.size();
        LOG(INFO) << "point pairs in two containers: " << point_pairs_two_containers_.size();

        // add plane factors in one container
        for (auto const& point_pair : point_pairs_one_container_)
        {
            PointIndex const& l = point_pair.first;
            PointIndex const& r = point_pair.second;

            Container const& lc = GetContainer(l.lidar_index);
            Container const& rc = GetContainer(r.lidar_index);

            PointNT const& lp = lc.GetSource(l.cloud_index).feature_cloud->at(l.point_index);
            PointNT const& rp = rc.GetSource(r.cloud_index).feature_cloud->at(r.point_index);

            Pose3Type const& lg   = lc.GetTarget(l.cloud_index);
            Pose3Type const& rg   = rc.GetTarget(r.cloud_index);
            Pose3Type        pose = rg.Inverse() * lg;

            uint64_t    extrinsic_key = static_cast<uint64_t>(l.lidar_index);
            Point3Type  src_pt(lp[0], lp[1], lp[2]);
            Point3Type  tgt_pt(rp[0], rp[1], rp[2]);
            Vector3Type tgt_normal = rp.template GetNormal<Vector3Type>();

            PlaneFactor1 factor(plane_noise, extrinsic_key, src_pt, tgt_pt, tgt_normal, pose);

            gtsam::NoiseModelFactor::shared_ptr gtsam_factor;
            gtsam_factor.reset(static_cast<gtsam::NoiseModelFactor*>(factor.GetPlaneFactor1()));
            graph.push_back(gtsam_factor);
        }

        // add plane factors between two containers
        for (auto const& point_pair : point_pairs_two_containers_)
        {
            PointIndex const& l = point_pair.first;
            PointIndex const& r = point_pair.second;

            Container const& lc = GetContainer(l.lidar_index);
            Container const& rc = GetContainer(r.lidar_index);

            PointNT const& lp = lc.GetSource(l.cloud_index).feature_cloud->at(l.point_index);
            PointNT const& rp = rc.GetSource(r.cloud_index).feature_cloud->at(r.point_index);

            Pose3Type const& lg   = lc.GetTarget(l.cloud_index);
            Pose3Type const& rg   = rc.GetTarget(r.cloud_index);
            Pose3Type        pose = rg.Inverse() * lg;

            uint64_t    src_key = static_cast<uint64_t>(l.lidar_index);
            uint64_t    tgt_key = static_cast<uint64_t>(r.lidar_index);
            Point3Type  src_pt(lp[0], lp[1], lp[2]);
            Point3Type  tgt_pt(rp[0], rp[1], rp[2]);
            Vector3Type tgt_normal = rp.template GetNormal<Vector3Type>();

            PlaneFactor2 factor(plane_noise, src_key, tgt_key, src_pt, tgt_pt, tgt_normal, pose);

            gtsam::NoiseModelFactor::shared_ptr gtsam_factor;
            gtsam_factor.reset(static_cast<gtsam::NoiseModelFactor*>(factor.GetPlaneFactor2()));
            graph.push_back(gtsam_factor);
        }

        gtsam::LevenbergMarquardtParams    params;
        gtsam::LevenbergMarquardtOptimizer lm(graph, initial_values, params);

        gtsam::Values optimized_values = lm.optimize();

        // update container extrinsic
        for (uint8_t k = 0U; k < GetContainerNum(); ++k)
        {
            Container& container = GetContainer(k);

            gtsam::Pose3 pose = optimized_values.at<gtsam::Pose3>(k);

            Matrix4Type mat_holo;
            memcpy(mat_holo.GetData(), pose.matrix().data(), sizeof(Scalar) * 16U);

            container.SetExtrinsic(Pose3Type(mat_holo));
        }

        /// evaluate error
        Scalar error = evaluate();

        LOG(INFO) << "iterations: " << i << " lm error: " << lm.error() << " plane error: " << error;
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
Scalar LidarCalibrationT<PointT>::Evaluate()
{
    // update container status
    for (uint32_t k = 0; k < lidar_containers_.size(); ++k)
    {
        Container& container = GetContainer(k);
        container.UpdateStatus();  ///< compenstate point cloud and compute normal feature cloud
    }

    // compute correspondences
    computePointPairs();

    // compute mean point2plane error using point pairs
    Scalar mean_error = evaluate();

    return mean_error;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
void LidarCalibrationT<PointT>::computePointPairs()
{
    uint32_t max_point_pairs_container = params_.max_point_pairs_container;

    point_pairs_one_container_.clear();
    point_pairs_two_containers_.clear();
    point_pairs_one_container_.reserve(max_point_pairs_container);
    point_pairs_two_containers_.reserve(max_point_pairs_container);

    uint32_t num_containers = lidar_containers_.size();

    for (uint32_t i = 0U; i < num_containers; ++i)
    {
        computePointPairsInOneContainer(i);
    }

    for (uint32_t i = 0U; i < num_containers; ++i)
    {
        for (uint32_t j = i + 1; j < num_containers; ++j)
        {
            computePointPairsBetweenContainer(i, j);
        }
    }

    if (point_pairs_one_container_.size() > max_point_pairs_container)
    {
        std::random_shuffle(point_pairs_one_container_.begin(), point_pairs_one_container_.end());
        point_pairs_one_container_.resize(max_point_pairs_container);
    }

    if (point_pairs_two_containers_.size() > max_point_pairs_container)
    {
        std::random_shuffle(point_pairs_two_containers_.begin(), point_pairs_two_containers_.end());
        point_pairs_two_containers_.resize(max_point_pairs_container);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
void LidarCalibrationT<PointT>::computePointPairsInOneContainer(uint8_t container_index)
{
    Container const& container  = GetContainer(container_index);
    uint8_t          num_clouds = container.GetDataSize();

    for (uint8_t i = 0U; i < num_clouds; ++i)
    {
        for (uint8_t j = i + 1; j < num_clouds; ++j)
        {
            Wrapper const& src_wrapper = container.GetSource(i);
            Wrapper const& tgt_wrapper = container.GetSource(j);
            computePointPairsBase(src_wrapper, container_index, i, tgt_wrapper, container_index, j);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
void LidarCalibrationT<PointT>::computePointPairsBetweenContainer(uint8_t src_container_index,
                                                                  uint8_t tgt_container_index)
{
    Container const& src_container = GetContainer(src_container_index);
    Container const& tgt_container = GetContainer(tgt_container_index);
    uint8_t          src_cloud_num = src_container.GetDataSize();
    uint8_t          tgt_cloud_num = tgt_container.GetDataSize();

    for (uint8_t i = 0U; i < src_cloud_num; ++i)
    {
        for (uint8_t j = 0U; j < tgt_cloud_num; ++j)
        {
            Wrapper const& src_wrapper = src_container.GetSource(i);
            Wrapper const& tgt_wrapper = tgt_container.GetSource(j);
            computePointPairsBase(src_wrapper, src_container_index, i, tgt_wrapper, tgt_container_index, j);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
void LidarCalibrationT<PointT>::computePointPairsBase(Wrapper const& source, uint8_t src_container_index,
                                                      uint8_t src_index, Wrapper const& target,
                                                      uint8_t tgt_container_index, uint8_t tgt_index)
{
    PointPairs point_pairs;
    point_pairs.reserve(params_.max_point_pairs_container);

    Pose3Type src_extrinsic = GetContainer(src_container_index).GetExtrinsic();
    Pose3Type src_pose      = GetContainer(src_container_index).GetTarget(src_index) * src_extrinsic;

    Pose3Type tgt_extrinsic = GetContainer(tgt_container_index).GetExtrinsic();
    Pose3Type tgt_pose      = GetContainer(tgt_container_index).GetTarget(tgt_index) * tgt_extrinsic;

    PointNCloudPtr src  = source.feature_cloud;
    PointNCloudPtr tgt  = target.feature_cloud;
    KdTreePtr      tree = target.tree;

    if (src->empty() || tgt->empty())
    {
        LOG(INFO) << "point cloud is empty!";
        return;
    }

    using PoseType  = geometry::Pose3T<PointScalar>;
    using PointType = geometry::Point3T<PointScalar>;

    Pose3Type pose = tgt_pose.Inverse() * src_pose;
    PoseType  tTs  = (PoseType)pose;

    Scalar max_dist_sqr = params_.max_corr_dist * params_.max_corr_dist;
    Scalar dot_min      = std::cos(geometry::Radian(params_.max_angle));

    std::vector<size_t> nn_indices(1U);
    std::vector<Scalar> nn_dists(1U);
    PointNT             pt_d;

    for (uint32_t i = 0U; i < src->size(); ++i)
    {
        PointNT const& src_pt = src->at(i);
        pt_d.Set(tTs.TransformFrom(PointType(src_pt[0], src_pt[1], src_pt[2])));
        pt_d.SetNormal(tTs.TransformFrom(src_pt.GetNormal()));

        if (tree->KnnSearch(pt_d, 1, nn_indices, nn_dists) <= 0)
        {
            continue;
        }

        if (nn_dists[0] < max_dist_sqr)
        {
            auto const& pt_m = tgt->at(nn_indices[0]);

            if (pt_m.GetNormal().Dot(pt_d.GetNormal()) > dot_min)
            {
                PointIndex pi_src, pi_tgt;
                pi_src.lidar_index = src_container_index;
                pi_src.cloud_index = src_index;
                pi_src.point_index = i;
                pi_tgt.lidar_index = tgt_container_index;
                pi_tgt.cloud_index = tgt_index;
                pi_tgt.point_index = nn_indices[0];

                point_pairs.push_back(std::make_pair(pi_src, pi_tgt));
            }
        }
    }

    if (point_pairs.size() > params_.max_point_pairs_pcd)
    {
        std::random_shuffle(point_pairs.begin(), point_pairs.end());
        point_pairs.resize(params_.max_point_pairs_pcd);
    }

    if (src_container_index == tgt_container_index)
    {
        std::copy(point_pairs.begin(), point_pairs.end(), std::back_inserter(point_pairs_one_container_));
    }
    else
    {
        std::copy(point_pairs.begin(), point_pairs.end(), std::back_inserter(point_pairs_two_containers_));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
Scalar LidarCalibrationT<PointT>::evaluate()
{
    Scalar total_error = 0.0;

    PointPairs total_pairs = point_pairs_one_container_;
    total_pairs.insert(total_pairs.end(), point_pairs_two_containers_.begin(), point_pairs_two_containers_.end());

    for (auto const& point_pair : total_pairs)
    {
        PointIndex const& l = point_pair.first;
        PointIndex const& r = point_pair.second;

        Container const& lc = GetContainer(l.lidar_index);
        Container const& rc = GetContainer(r.lidar_index);

        PointNT const& lp = lc.GetSource(l.cloud_index).feature_cloud->at(l.point_index);
        PointNT const& rp = rc.GetSource(r.cloud_index).feature_cloud->at(r.point_index);

        Pose3Type const& lg = lc.GetTarget(l.cloud_index);
        Pose3Type const& rg = rc.GetTarget(r.cloud_index);

        Pose3Type const& le = lc.GetExtrinsic();
        Pose3Type const& re = rc.GetExtrinsic();

        Pose3Type tTs = re.Inverse() * rg.Inverse() * lg * le;

        Point3Type  src_pt(lp[0], lp[1], lp[2]);
        Point3Type  tgt_pt(rp[0], rp[1], rp[2]);
        Vector3Type tgt_normal = rp.template GetNormal<Vector3Type>();

        Point3Type diff = tTs.TransformFrom(src_pt) - tgt_pt;

        total_error += std::abs(tgt_normal.Dot(diff.As<Vector3Type>()));
    }

    Scalar mean_error = total_error / static_cast<Scalar>(total_pairs.size());

    return mean_error;
}

}  // namespace lidar
}  // namespace calibration
}  // namespace holo

#endif
