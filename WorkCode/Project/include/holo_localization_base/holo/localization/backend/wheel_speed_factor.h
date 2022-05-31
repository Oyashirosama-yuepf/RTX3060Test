/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file wheel_speed_factor.h
 * @brief this file deines wheel speed factor class
 * @author Binbin.Wang wangbinbin@holomatic.com
 * @date 2020-08-04
 */

#ifndef HOLO_LOCALIZATION_BACKEND_WHEEL_SPEED_FACTOR_H_
#define HOLO_LOCALIZATION_BACKEND_WHEEL_SPEED_FACTOR_H_

#include <holo/localization/common/types.h>
#include <holo/localization/common/wheel_preintegration.h>

namespace holo
{
namespace localization
{
/**
 * @addtogroup backend
 * @{
 *
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief factor for wheel speed factor
 */
class WheelSpeedFactor
{
public:
    /**
     * @brief disable default contructor
     */
    WheelSpeedFactor() = delete;

    /**
     * @brief construct a new wheel speed factor object
     *
     * @param[in] pose1_index index of pose1
     * @param[in] pose2_index index of pose2
     * @param[in] iEb body pose in imu frame
     * @param[in] pwm wheel preintegration measurement
     */
    WheelSpeedFactor(uint64_t const pose1_index, uint64_t const pose2_index, Pose3Type const& iEb,
                     WheelPreintegrationMeasurement const& pwm);

    /**
     * @brief destructor
     */
    ~WheelSpeedFactor()
    {
    }

    /**
     * @brief get a void pointer of wheel speed factor
     * @details it can be cast to a pointer of base class of holo::localization::internal::WheelSpeedFactor
     * @note whoever calls this method must take care of the allocated memory and release it after using !!!
     *
     * @return void* void pointer to the created wheel speed factor
     * @throw std::bad_alloc if memory allocation fails
     */
    void* GetFactor() const;

    /**
     * @brief test default constructor of internal wheel speed factor
     * @note this function only for unit test, do not use it
     */
    static void TestDefaultConstructorOfInternalFactor();

private:
    /// @brief index of pose1
    uint64_t const pose1_index_;

    /// @brief index of pose2
    uint64_t const pose2_index_;

    /// @brief body frame in imu frame
    Pose3Type const iEb_;

    /// @brief displacement measurement of wheel odometry frame
    WheelPreintegrationMeasurement const pwm_;

};  // WheelSpeedFactor

/**
 * @}
 *
 */
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_BACKEND_WHEEL_SPEED_FACTOR_H_
