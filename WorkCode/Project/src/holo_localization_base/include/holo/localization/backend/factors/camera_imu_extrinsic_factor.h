/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file camera_imu_extrinsic_factor.h
 * @brief this file defines camera imu extrinsic factor class
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "2020-04-20"
 */
#ifndef HOLO_LOCALIZATION_BACKEND_FACTORS_CAMERA_IMU_EXTRINSIC_FACTOR_H_
#define HOLO_LOCALIZATION_BACKEND_FACTORS_CAMERA_IMU_EXTRINSIC_FACTOR_H_

#include <holo/localization/common/types.h>

namespace holo
{
namespace localization
{
/**
 * @addtogroup backend
 * @{
 */
class CameraImuExtrinsicFactor
{
public:
    /**
     * @brief disable default constructor
     */
    CameraImuExtrinsicFactor() = delete;

    /**
     * @brief Construct a new Camera Imu Extrinsic Factor object
     *
     * @param[in] sigmas sigmas of error[pixel]
     * @param[in] wTi_index index of imu in world frame pose
     * @param[in] ptw_index index of 3d point in world frame
     * @param[in] rpy_index index of euler angle
     * @param[in] itc_index index of translation
     * @param[in] K camera matrix
     * @param[in] measurement 2d measurement in image [pixel]
     * @param[in] fix_wTi whether fix wTi
     * @param[in] fix_ptw whether fix ptw
     * @param[in] fix_roll whether fix roll
     * @param[in] fix_pitch whether fix pitch
     * @param[in] fix_yaw whether fix yaw
     * @param[in] fix_itc whether fix itc
     */
    CameraImuExtrinsicFactor(Vector2Type const& sigmas, uint64_t const wTi_index, uint64_t const ptw_index,
                             uint64_t const rpy_index, uint64_t const itc_index, Matrix3Type const& K,
                             Point2Type const& measurement, bool_t const fix_wTi = true, bool_t const fix_ptw = true,
                             bool_t const fix_roll = true, bool_t const fix_pitch = true, bool_t const fix_yaw = true,
                             bool_t const fix_itc = true);

    /**
     * @brief Destroy the Camera Imu Extrinsic Factor object
     *
     */
    ~CameraImuExtrinsicFactor();

    /**
     * @brief get a void pointer of camera imu extrinsic factor
     * @details it can be cast to a pointer of base class of holo::localization::internal::CameraImuExtrinsicFactor
     * @note whoever calls this method must take care of the allocated memory and release it !!!
     *
     * @return void* void pointer to the created camera imu extrinsic factor
     * @throw std::bad_alloc if memory allocation fails
     */
    void* GetFactor() const;

    /**
     * @brief test default constructor of internal camera imu extrinsic factor
     * @note this function only for unit test, do not use it
     */
    static void TestDefaultConstructorOfInternalFactor();

private:
    Vector2Type const sigmas_;       ///< sigma for error [pixel]
    uint64_t const    wTi_index_;    ///< index of imu pose in world frame
    uint64_t const    ptw_index_;    ///< index of 3d point in world frame
    uint64_t const    rpy_index_;    ///< index of euler angle in extrinsic
    uint64_t const    itc_index_;    ///< index of translation in extrinsic
    Matrix3Type const K_;            ///< camera matrix
    Point2Type const  measurement_;  ///< 2d point in image [pixel]
    bool_t const      fix_wTi_;      ///< whether fix wTi during optimization
    bool_t const      fix_ptw_;      ///< whether fix ptw during optimization
    bool_t const      fix_roll_;     ///< whether fix roll during optimization
    bool_t const      fix_pitch_;    ///< whether fix pitch during optimization
    bool_t const      fix_yaw_;      ///< whether fix yaw during optimization
    bool_t const      fix_itc_;      ///< whether fix itc during optimization
};
/**
 * @}
 */
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_BACKEND_FACTORS_CAMERA_IMU_EXTRINSIC_FACTOR_H_
