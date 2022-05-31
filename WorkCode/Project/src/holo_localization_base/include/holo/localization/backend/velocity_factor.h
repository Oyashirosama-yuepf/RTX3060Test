/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file velocity_factor.h
 * @brief this file deines velocity factor class
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "2019-12-15"
 */

#ifndef HOLO_LOCALIZATION_BACKEND_VELOCITY_FACTOR_H_
#define HOLO_LOCALIZATION_BACKEND_VELOCITY_FACTOR_H_

#include <holo/localization/common/types.h>

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
class VelocityFactor
{
public:
    /**
     * @brief disable default contructor
     */
    VelocityFactor() = delete;

    /**
     * @brief constructor
     * @param[in] pose_index index of the pose
     * @param[in] velocity_index index of the velocity
     * @param[in] velocity velocity measurement in body frame
     * @param[in] sigmas sigma for velocity
     */
    VelocityFactor(const uint64_t pose_index, const uint64_t velocity_index, const Vector3Type& velocity,
                   const Vector3Type& sigmas);

    /**
     * @brief destructor
     */
    ~VelocityFactor()
    {
    }

    /**
     * @brief get a void pointer of velocity factor
     * @details it can be cast to a pointer of base class of holo::localization::internal::VelocityFactor
     * @note whoever calls this method must take care of the allocated memory and release it after using !!!
     *
     * @return void* void pointer to the created velocity factor
     * @throw std::bad_alloc if memory allocation fails
     */
    void* GetFactor();

    /**
     * @brief test default constructor of internal velocity factor
     * @note this function only for unit test, do not use it
     */
    static void TestDefaultConstructorOfInternalFactor();

private:
    const uint64_t    pose_index_;
    const uint64_t    velocity_index_;
    const Vector3Type velocity_;
    const Vector3Type sigmas_;
};  // VelocityFactor

/**
 * @}
 *
 */
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_BACKEND_VELOCITY_FACTOR_H_
