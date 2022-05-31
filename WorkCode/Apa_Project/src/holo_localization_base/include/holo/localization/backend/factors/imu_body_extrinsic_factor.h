/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file imu_body_extrinsic_factor.h
 * @brief this file defines imu body extrinsic factor class
 * @author Binbin.Wang wangbinbin@holomatic.com
 * @date 2020-08-13
 */
#ifndef HOLO_LOCALIZATION_BACKEND_FACTORS_IMU_BODY_EXTRINSIC_FACTOR_H_
#define HOLO_LOCALIZATION_BACKEND_FACTORS_IMU_BODY_EXTRINSIC_FACTOR_H_

#include <holo/localization/common/types.h>
#include <holo/localization/common/wheel_preintegration.h>

namespace holo
{
namespace localization
{
/**
 * @addtogroup backend
 * @{
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief factor for imu body extrinsic factor
 */
class ImuBodyExtrinsicFactor
{
public:
    /**
     * @brief disable default contructor
     */
    ImuBodyExtrinsicFactor() = delete;

    /**
     * @brief construct a new imu body extrinsic factor object
     *
     * @param[in] pose1_index index of pose1
     * @param[in] pose2_index index of pose2
     * @param[in] iRb_index index of iRb
     * @param[in] itb body translation in imu frame
     * @param[in] pwm wheel preintegration measurement
     */
    ImuBodyExtrinsicFactor(uint64_t const pose1_index, uint64_t const pose2_index, uint64_t const iRb_index,
                           Point3Type const& itb, WheelPreintegrationMeasurement const& pwm);

    /**
     * @brief destructor
     */
    ~ImuBodyExtrinsicFactor()
    {
    }

    /**
     * @brief get a void pointer of imu body extrinsic factor
     * @details it can be cast to a pointer of base class of holo::localization::internal::ImuBodyExtrinsicFactor
     * @note whoever calls this method must take care of the allocated memory and release it after using !!!
     *
     * @return void* void pointer to the created imu bosy extrinsic factor
     * @throw std::bad_alloc if memory allocation fails
     */
    void* GetFactor() const;

    /**
     * @brief test default constructor of internal imu body extrinsic factor
     * @note this function only for unit test, do not use it
     */
    static void TestDefaultConstructorOfInternalFactor();

private:
    ///@brief index of pose1
    uint64_t const pose1_index_;

    ///@brief index of pose2
    uint64_t const pose2_index_;

    ///@brief index of iRb
    uint64_t const iRb_index_;

    ///@brief body translation in imu frame
    Point3Type const itb_;

    ///@brief displacement measurement of wheel odometry frame
    WheelPreintegrationMeasurement const pwm_;

};  // ImuBodyExtrinsicFactor
/**
 * @}
 */
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_BACKEND_FACTORS_IMU_BODY_EXTRINSIC_FACTOR_H_
