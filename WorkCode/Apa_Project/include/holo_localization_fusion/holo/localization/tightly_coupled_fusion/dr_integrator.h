/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file dr_integrator.h
 * @brief this file defines DrIntegrator
 * @author Yanwei Du (duyanwei@holomatic.com)
 * @date 2021-02-08
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_DR_INTEGRATOR_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_DR_INTEGRATOR_H_

#include <thread>

#include <holo/localization/common/localization_base.h>
#include <holo/localization/tightly_coupled_fusion/common_types.h>
#include <holo/localization/tightly_coupled_fusion/imu_stationary_calibrator.h>
#include <holo/localization/tightly_coupled_fusion/measurements_manager_fusion.h>
#include <holo/localization/tightly_coupled_fusion/utils/common_functions.h>
#include <holo/localization/tightly_coupled_fusion/vehicle_velocity_corrector.h>

namespace holo
{
namespace localization
{
namespace tightly_coupled_fusion
{
/**
 * @addtogroup tightly_coupled_fusion
 * @{
 *
 */

/**
 * @brief DrIntegrator
 *
 * @details It serves as a functor to integrate wheel speeds and gyroscope measurements and output a 2D dr odometry
 *
 */
class DrIntegrator : public LocalizationBase
{
public:
    using Base                             = LocalizationBase;
    using MeasurementsManagerFusionPtr     = MeasurementsManagerFusion::Ptr;
    using VehicleVelocityCorrectorConstPtr = VehicleVelocityCorrector::ConstPtr;
    using StampedImuStationaryResult       = ImuStationaryCalibrator::StampedImuStationaryResult;

    /**
     * @brief parameters
     *
     */
    struct Parameters
    {
        Scalar      frequency        = 100.0;
        ImuBiasType default_imu_bias = ImuBiasType();

        /**
         * @brief
         *
         * @param os
         * @param params
         * @return std::ostream&
         */
        friend std::ostream& operator<<(std::ostream& os, Parameters const& params)
        {
            os << "DrIntegrator::Parameters : \n"
               << "frequency = " << params.frequency << "\n"
               << "initial_bias = acc: " << params.default_imu_bias.GetLinearAccelerationBias<Vector3Type>().Transpose()
               << ", gyro: " << params.default_imu_bias.GetAngularVelocityBias<Vector3Type>().Transpose() << std::endl;
            return os;
        }

        /**
         * @brief load parameters from yaml
         *
         * @details bias loading order: [acc, gyro]
         * @param node
         * @return Parameters
         */
        static Parameters LoadFromYaml(yaml::Node const& node);

        /**
         * @brief generate parameters
         *
         * @return Parameters
         */
        static Parameters GenerateExample()
        {
            return Parameters();
        }
    };

    /**
     * @brief Construct a new Dr Integration object
     *
     * @param parameters dr integrator parameters
     * @param mmf measurements manager
     * @param vvc vehicle velocity corrector
     */
    DrIntegrator(Parameters const& parameters, MeasurementsManagerFusionPtr mmf, VehicleVelocityCorrectorConstPtr vvc);

    /**
     * @brief Destroy the Dr Integrator object
     *
     */
    virtual ~DrIntegrator();

    /**
     * @brief get parameters
     *
     * @return parameters
     */
    Parameters const& GetParameters() const
    {
        return parameters_;
    }

    /**
     * @brief set status to pause
     */
    virtual void Pause();

protected:
    /**
     * @brief initialize state
     *
     * @details single thread calling
     */
    void initializeState();

    /**
     * @brief core algorithm happens here
     *
     */
    virtual void run() override;

    /**
     * @brief check if system is initialized
     *
     * @return bool_t
     */
    bool_t isInitialized() const;

    /**
     * @brief initialize
     *
     * @param state dr state
     * @return bool_t
     */
    bool_t initialize(StampedAdvancedNavstateType* state) const;

    /**
     * @brief integrate
     *
     * @param state dr state
     * @return bool_t
     */
    bool_t integrate(StampedAdvancedNavstateType* state) const;

    Parameters const                 parameters_;        ///< parameters
    MeasurementsManagerFusionPtr     mmf_;               ///< measurements manager
    VehicleVelocityCorrectorConstPtr vvc_;               ///< vehicle velocity corrector
    StampedAdvancedNavstateType      state_;             ///< latest dr state
    std::shared_ptr<std::thread>     estimator_thread_;  ///< estimation thread
};

/**
 * @}
 *
 */

}  // namespace tightly_coupled_fusion

}  // namespace localization

}  // namespace holo

#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_DR_INTEGRATOR_H_
