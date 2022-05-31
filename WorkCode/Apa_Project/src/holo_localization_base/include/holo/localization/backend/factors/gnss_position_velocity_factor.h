/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file gnss_position_velocity_factor.h
 * @brief This file define GNSS position and velocity factor class
 * @author Lei Gehang (leigehang@holomaitc.com)
 * @date Aug 24, 2020
 */

#ifndef HOLO_LOCALIZATION_BACKEND_GNSS_POSITION_VELOCITY_FACTOR_H_
#define HOLO_LOCALIZATION_BACKEND_GNSS_POSITION_VELOCITY_FACTOR_H_

#include <holo/common/optional.h>
#include <holo/localization/common/imu_preintegration.h>
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

class GnssPositionVelocityFactor
{
public:
    static_assert(std::is_same<Scalar, float64_t>::value, "GnssFactor needs float64_t precision.");

    using OptionalPimType = holo::OptionalT<ImuPreintegrationMeasurement>;

    /**
     * @brief Construct a new Gnss Position and Velocity Factor object
     *
     * @param[in] pose_index The index of the pose variable
     * @param[in] velocity_index The index of the velocity variable
     * @param[in] gnss_measurement The measured gnss output (pos_x, pos_y, pos_z, vel_x, vel_y, vel_z)
     * @param[in] sigmas The noise sigma values (standard deviation)
     *            (std_pos_x, std_pos_y, std_pos_z, std_vel_x, std_vel_y, std_vel_z)
     * @param[in] pim preintegrated imu measurements between state_timestamp and gnss_timestamp
     * @param[in] wRb rotation in world frame
     */
    GnssPositionVelocityFactor(uint64_t const pose_index, uint64_t const velocity_index,
                               Vector6Type const& gnss_measurement, Vector6Type const& sigmas,
                               OptionalPimType const& pim = holo::optional::none,
                               Rot3Type const&        wRb = Rot3Type::Identity());

    /**
     * @brief Destroy the Gnss Position Factor object
     *
     */
    ~GnssPositionVelocityFactor()
    {
    }

    /**
     * @brief Get a void pointer of GNSS position and velocity factor
     * @details It can be cast to a pointer of base class of holo::localization::internal::GnssPositionVelocityFactor
     * @note Whoever calls this method must take care of the allocated memory and release it after using !!!
     *
     * @return void* void pointer to the created GNSS position and velocity factor
     * @throw std::bad_alloc if memory allocation fails
     */
    void* GetFactor();

private:
    uint64_t const        pose_index_;        ///< The index of pose variable
    uint64_t const        velocity_index_;    ///< The index of velocity variable
    Vector6Type const     gnss_measurement_;  ///< It's (3D position, 3D velocity)
    Vector6Type const     sigmas_;            ///< The noise sigma(3D position, 3D velocity)
    OptionalPimType const pim_;               ///< The preintegrated imu measurements between
                                              ///< state_timestamp and gnss_timestamp
    Rot3Type const wRb_;                      ///< rotation in world coordinate
};

}  // namespace localization
}  // namespace holo

#endif  ///< HOLO_LOCALIZATION_BACKEND_GNSS_POSITION_VELOCITY_FACTOR_H_