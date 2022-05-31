/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file failure_recovery.h
 * @brief do failure recovery for fusion
 * @author Shuaijie Li(lishuaijie@holomatic.com)
 * @date "2021-03-29"
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_FAILURE_RECOVERY_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_FAILURE_RECOVERY_H_

#include <holo/localization/tightly_coupled_fusion/common_types.h>
#include <holo/localization/tightly_coupled_fusion/fusion_estimator.h>
#include <holo/localization/tightly_coupled_fusion/measurements_manager_fusion.h>

namespace holo
{
namespace localization
{
namespace tightly_coupled_fusion
{
/**
 * @addtogroup tightly_coupled_fusion
 * {
 *
 */
class FailureRecovery
{
public:
    /**
     * @brief recovery mode
     */
    enum class Mode : uint8_t
    {
        EXCEPTION       = 0u,    ///< recovery from exception
        SWITCH_UTM_ZONE = 1u,    ///< recovery from new utm zone
        FATAL           = 2u,    ///< recovery from fatal ,it will force exit high precision
        UNKNOWM         = 255u,  ///< unknown type
    };

    /**
     * @brief constructor
     */
    FailureRecovery();

    /**
     * @brief destructor
     */
    ~FailureRecovery();

    /**
     * @brief recovery from different mode
     *
     * @param[in] mode failure mode
     * @param[in] state fusion state before failure
     * @param[in] measurements_manager_fusion_ptr pointer of measurements manager fusion
     * @param[in] fusion_estimator_ptr pointer of fusion estimator
     * @return bool_t true -> sucesses, false -> otherwise
     */
    bool_t Run(Mode const mode, FusionState& state, MeasurementsManagerFusion::Ptr& measurements_manager_fusion_ptr,
               FusionEstimator::Ptr& fusion_estimator_ptr) const;

protected:
    /**
     * @brief compute navstate in new coordinate
     *
     * @param[in] lhs navstate whose timestamp is smaller than rhs
     * @param[in] rhs newest fusion navstate
     * @param[in] new_coordinate new utm coordinate
     * @return StampedGTNavStateAndImuBias navstate of of rhs in new coordinate
     */
    StampedGTNavStateAndImuBias computeNavstateInNewUtmCoordinate(StampedAdvancedNavstate const& lhs,
                                                                  StampedAdvancedNavstate const& rhs,
                                                                  CoordinateType const&          new_coordinate) const;

    /**
     * @brief initialize fusion state by add prior factor and optimize it
     *
     * @param[in] state fusion state
     * @param[in] parent_coordinate parent coordinate of fusion navstate
     * @param[in] stamped_gt_navstate_and_imu_bias prior navstate and imu bias
     * @param[in] fusion_estimator_ptr pointer of fusion estimator
     * @return FusionEstimator::Status fusion estimator status
     */
    FusionEstimator::Status initializeFusionState(FusionState& state, CoordinateType const parent_coordinate,
                                                  StampedGTNavStateAndImuBias const& stamped_gt_navstate_and_imu_bias,
                                                  FusionEstimator::Ptr&              fusion_estimator_ptr) const;
};  // FailureRecovery
/**
 * @}
 *
 */
}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_FAILURE_RECOVERY_H_
