/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file fisheye_factor.h
 * @brief  This file defines fisheye camera projection factor class
 * @author bin.chen @ chenbin@holomatic.com
 * @date   2020-09-10
 */

#ifndef HOLO_CALIBRATION_CAMERA_FIELD_FISHEYE_FACTOR_H_
#define HOLO_CALIBRATION_CAMERA_FIELD_FISHEYE_FACTOR_H_

#include <holo/calibration/camera/field/types.h>

namespace holo
{
namespace calibration
{
namespace camera
{
/**
 *  @addtogroup camera
 *  @{
 *
 */

class FisheyeProjectionFactor
{
public:
    /**
     * @brief Disable default constructor
     */
    FisheyeProjectionFactor() = delete;

    /**
     * @brief Construct a new Fisheye Projection Factor object.
     * @param[in] sigmas sigmas of reprojection error [unit: pixel].
     * @param[in] huber_loss_threshold threshold value of huber robust kernel function.
     * @param[in] pose_index pose index in the world frame.
     * @param[in] intrinsic_index intrinsic index.
     * @param[in] measure_2d 2d measurement in image [unit: pixel].
     * @param[in] point3d_world 3d point in the world [unit: m].
     * @note If you don't use Huber_ Loss, please enter a negative value
     */
    FisheyeProjectionFactor(Vector2 const& sigmas, Scalar const huber_loss_threshold, uint64_t const pose_index,
                            uint64_t const intrinsic_index, Point2 const& measure_2d, Point3 const& point3d_world);

    /**
     * @brief Destroy the Fisheye Projection Factor object.
     */
    ~FisheyeProjectionFactor()
    {
    }

    /**
     * @brief Get a void pointer of fisheye projection factor in factor graph.
     * @note Whoever calls this method must take care of the allocated memory and release it !!!
     *       Smart Pointers are recommended, such as shared_ptr.
     *
     * @return void* void pointer to the created fisheye projection factor.
     * @throw std::bad_alloc if memory allocation fails.
     */
    void* GetFisheyeProjectionFactor() const;

protected:
    Vector2 const  sigmas_;                ///< sigma for error [unit: pixel].
    Scalar const   huber_loss_threshold_;  ///< threshold value of huber robust kernel function
    uint64_t const pose_index_;            ///< index of camera pose in world.
    uint64_t const intrinsic_index_;       ///< index of camera intrinsic.
    Point2 const   measure_2d_;            ///< 2d point in image [unit: pixel].
    Point3 const   point3d_world_;         ///< 3d point in world [unit: m].
};

/**
 * @}
 */

}  // namespace camera

}  // namespace calibration

}  // namespace holo

#endif  /// ----- #ifndef HOLO_CALIBRATION_CAMERA_FIELD_FISHEYE_FACTOR_H_
