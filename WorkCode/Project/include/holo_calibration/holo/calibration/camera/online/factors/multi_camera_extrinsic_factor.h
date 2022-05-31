/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file multi_camera_extrinsic_factor.h
 * @brief this file defines multi camera extrinsic factor class
 * @author zhaojiaxing (zhaojiaxing@holomaitc.com)
 * @date 2020-09-23
 */

#ifndef HOLO_CALIBRATION_CAMERA_ONLINE_FACTORS_MULTI_CAMERA_EXTRINSIC_FACTOR_H_
#define HOLO_CALIBRATION_CAMERA_ONLINE_FACTORS_MULTI_CAMERA_EXTRINSIC_FACTOR_H_

#include <holo/localization/common/types.h>

namespace holo
{
namespace calibration
{
/**
 * @addtogroup camera
 * @{
 */
class MultiCameraExtrinsicFactor
{
public:
    using Scalar      = holo::localization::Scalar;
    using Pose3Type   = holo::localization::Pose3Type;
    using Matrix3Type = holo::localization::Matrix3Type;
    using Matrix4Type = holo::localization::Matrix4Type;
    using Line2Type   = holo::localization::Line2Type;
    /**
     * @brief disable default constructor
     */
    MultiCameraExtrinsicFactor() = delete;

    /**
     * @brief Construct a new multi Camera Extrinsic Factor object
     *
     * @details (u,v) = K_tgt * E_body_tgt.Inverse() * E_body_smartbody`(optimized variable) * pt_smartbody or (u,v) =
     * K_tgt * E_tgt_src(optimized variable) * pt_src(E_body_tgt=Identity)  error = detected_line_2d_tgt.Dist((u,v))
     * @param[in] b_E_tgt pose of camera in body frame only for smart camera calibration
     * @param[in] k intrinsic of target camera
     * @param[in] line fitted line in 2d in target camera image frame
     * @param[in] sigma standard deviation of error[pixel]
     * @param[in] pt_index index of 3d point in camera or body frame
     * @param[in] rpy_index index of euler angle of tgt_E_src
     * @param[in] itc_index index of translation of of tgt_E_src
     * @param[in] fix_pt whether fix pt
     * @param[in] fix_roll whether fix roll
     * @param[in] fix_pitch whether fix pitch
     * @param[in] fix_yaw whether fix yaw
     * @param[in] fix_t whether fix translation
     * @note If you don't use Huber_ Loss, please enter a negative value
     */
    MultiCameraExtrinsicFactor(Pose3Type const& b_E_tgt, Matrix3Type const& K_tgt, Line2Type const& line,
                               Scalar const sigma, uint64_t const pt_index, uint64_t const rpy_index,
                               uint64_t const t_index, Scalar const huber_loss_threshold = -1.0,
                               bool_t const fix_pt = true, bool_t const fix_roll = true, bool_t const fix_pitch = true,
                               bool_t const fix_yaw = true, bool_t const fix_t = true);

    /**
     * @brief Destroy the Multi Camera Extrinsic Factor object
     *
     */
    ~MultiCameraExtrinsicFactor();

    /**
     * @brief get a void pointer of multi camera extrinsic factor
     * @details it can be cast to a pointer of base class of holo::localization::internal::MultiCameraExtrinsicFactor
     * @note whoever calls this method must take care of the allocated memory and release it !!!
     *
     * @return void* void pointer to the created multi camera extrinsic factor
     * @throw std::bad_alloc if memory allocation fails
     */
    void* GetFactor() const;

    /**
     * @brief test default constructor of internal multi camera extrinsic factor
     * @note this function only for unit test, do not use it
     */
    static void TestDefaultConstructorOfInternalFactor();

private:
    Pose3Type const   b_E_tgt_;               ///< pose of camera in body frame
    Matrix3Type const K_;                     ///< intrinsic of camera
    Line2Type const   line_;                  ///< fitted line
    Scalar const      sigma_;                 ///< standard deviation of measurement for error [pixel]
    uint64_t const    pt_index_;              ///< index of 3d point in camera or body frame
    uint64_t const    rpy_index_;             ///< index of euler angle in extrinsic
    uint64_t const    t_index_;               ///< index of translation in extrinsic
    Scalar const      huber_loss_threshold_;  ///< the threshold of huber loss
    bool_t const      fix_pt_;                ///< whether fix pt during optimization
    bool_t const      fix_roll_;              ///< whether fix roll during optimization
    bool_t const      fix_pitch_;             ///< whether fix pitch during optimization
    bool_t const      fix_yaw_;               ///< whether fix yaw during optimization
    bool_t const      fix_t_;                 ///< whether fix t during optimization
};
/**
 * @}
 */
}  // namespace calibration
}  // namespace holo

#endif  // HOLO_CALIBRATION_CAMERA_ONLINE_FACTORS_MULTI_CAMERA_EXTRINSIC_FACTOR_H_