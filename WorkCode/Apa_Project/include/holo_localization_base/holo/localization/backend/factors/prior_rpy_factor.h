/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file prior_rpy_factor.h
 * @brief this file defines a prior factor for rotation with rpy measurements
 * @author Shuaijie Li(lishuaijie@holomatic.com)
 * @date "2021-02-07"
 */

#ifndef HOLO_LOCALIZATION_BACKEND_FACTORS_PRIOR_RPY_FACTOR_H_
#define HOLO_LOCALIZATION_BACKEND_FACTORS_PRIOR_RPY_FACTOR_H_

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

class PriorRPYFactor
{
public:
    /**
     * @brief construct a new prior RPY factor object
     *
     * @param[in] sigmas sigmas of roll, pitch, yaw measurement[rad]
     * @param[in] pose_index index of the pose variable
     * @param[in] measurement roll, pitch , yaw measurement[rad]
     * @param[in] fix_roll whether fix roll
     * @param[in] fix_pitch whether fix pitch
     * @param[in] fix_yaw whehter fix yaw
     * @param[in] delta small perturbution used to compute numerical derivation
     */
    PriorRPYFactor(Vector3Type const& sigmas, uint32_t const pose_index, Vector3Type const& measurement,
                   bool_t const fix_roll, bool_t const fix_pitch, bool_t const fix_yaw,
                   Scalar const delta = 1e-8) noexcept;

    /**
     * @brief destroy the prior RPY factor object
     */
    ~PriorRPYFactor() noexcept;

    /**
     * @brief get a void pointer of prior rpy factor
     * @details it can be cast to a pointer of base class of holo::localization::internal::PriorRPYFactor
     * @note whoever calls this method must take care of the allocated memory and release it !!!
     *
     * @return void* void pointer to the created prior rpy factor
     * @throw std::bad_alloc if memory allocation fails
     */
    void* GetFactor();

protected:
    Vector3Type const sigmas_;       ///< stdandard deviation for rpy measurement
    uint32_t const    pose_index_;   ///< index of the pose variable
    Vector3Type const measurement_;  ///< roll, pitch, yaw measurement
    bool_t            fix_roll_;     ///< whether fix roll during optimization
    bool_t            fix_pitch_;    ///< whether fix pitch during optimization
    bool_t            fix_yaw_;      ///< whether fix yaw during optimization
    Scalar            delta_;        ///< perturbution used to compute numerical derivation
};

/**
 * @}
 *
 */
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_BACKEND_FACTORS_PRIOR_RPY_FACTOR_H_
