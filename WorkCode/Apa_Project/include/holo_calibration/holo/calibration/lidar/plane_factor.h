/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file plane_factor.h
 * @brief This header file defines plane factor interfaces
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2020-12-10
 */

#ifndef HOLO_CALIBRATION_LIDAR_PLANE_FACTOR_H_
#define HOLO_CALIBRATION_LIDAR_PLANE_FACTOR_H_

#include <holo/calibration/lidar/types.h>

namespace holo
{
namespace calibration
{
namespace lidar
{
/**
 * @brief Point2Plane factor in one container
 */
class PlaneFactor1
{
public:
    /**
     * @brief Construct a new Plane Factor 1 object
     *
     * @param[in] sigma sigma of point to plane error
     * @param[in] extrinsic_index lidar to target sensor extrinsic key
     * @param[in] src_pt source point
     * @param[in] tgt_pt target point
     * @param[in] tgt_normal target point normal
     * @param[in] btTbs transformation between source and target cloud in target coordinate system
     */
    PlaneFactor1(Scalar sigma, uint64_t const extrinsic_id, Point3Type const& src_pt, Point3Type const& tgt_pt,
                 Vector3Type const& tgt_normal, Pose3Type const& btTbs);

    /**
     * @brief Destroy the Plane Factor 1 object
     *
     */
    ~PlaneFactor1()
    {
    }

    /**
     * @brief Get the Plane Factor 1 object
     *
     * @return void*
     */
    void* GetPlaneFactor1() const;

private:
    Scalar      sigma_;
    uint64_t    extrinsic_id_;
    Point3Type  src_pt_;
    Point3Type  tgt_pt_;
    Vector3Type tgt_normal_;
    Pose3Type   btTbs_;
};

/**
 * @brief Point2Plane factor between two containers
 */
class PlaneFactor2
{
public:
    /**
     * @brief Construct a new Plane Factor 2 object
     *
     * @param[in] sigma sigma of point to plane error
     * @param[in] src_extrinsic_id source lidar to target sensor extrinsic key
     * @param[in] tgt_extrinsic_id target lidar to target sensor extrinsic key
     * @param[in] src_pt source point
     * @param[in] tgt_pt target point
     * @param[in] tgt_normal target normal
     * @param[in] btTbs transformation between source and target cloud in target coordinate system
     * @param[in] inverse_tgt If true, tgt_extrinsic transforms target lidar to target sensor.
     *                        Otherwise, tgt_extrinsic transforms target sensor to target lidar.
     */
    PlaneFactor2(Scalar sigma, uint64_t const src_extrinsic_id, uint64_t const tgt_extrinsic_id,
                 Point3Type const& src_pt, Point3Type const& tgt_pt, Vector3Type const& tgt_normal,
                 Pose3Type const& btTbs, bool_t const inverse_tgt = true);

    /**
     * @brief Destroy the Plane Factor 2 object
     *
     */
    ~PlaneFactor2()
    {
    }

    /**
     * @brief Get the Plane Factor 2 object
     *
     * @return void*
     */
    void* GetPlaneFactor2() const;

private:
    Scalar      sigma_;
    uint64_t    src_extrinsic_id_;
    uint64_t    tgt_extrinsic_id_;
    Point3Type  src_pt_;
    Point3Type  tgt_pt_;
    Vector3Type tgt_normal_;
    Pose3Type   btTbs_;
    bool_t      inverse_tgt_;
};

/**
 * @brief Prior z factor
 * @note the vehicle usually do in-plane movement, the data will cause calibration method lack constaints for z
 * dimension, so we need add prior z factor
 */
class ZFactor
{
public:
    /**
     * @brief Construct a new ZFactor object
     *
     * @param[in] sigma noise sigma of prior z
     * @param[in] pose_key  key of the optimized pose
     * @param[in] prior_z prior z value
     */
    ZFactor(Scalar sigma, uint64_t const pose_key, Scalar const prior_z);

    /**
     * @brief Destroy the Z Factor object
     *
     */
    ~ZFactor()
    {
    }

    /**
     * @brief Get the Z Factor object
     *
     * @return void*
     */
    void* GetZFactor() const;

private:
    Scalar    sigma_;
    uint64_t  pose_key_;
    float64_t prior_z_;
};
}  // namespace lidar
}  // namespace calibration
}  // namespace holo

#endif
