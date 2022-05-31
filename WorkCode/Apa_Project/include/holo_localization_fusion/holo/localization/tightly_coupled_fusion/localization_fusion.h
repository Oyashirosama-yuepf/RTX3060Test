/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file localization_fusion.h
 * @brief main pipline of tightly coupled fusion localization
 * @author Shuaijie Li(lishuaijie@holomatic.com)
 * @date "2021-02-04"
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_LOCALIZATION_FUSION_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_LOCALIZATION_FUSION_H_

#include <set>
#include <thread>

#include <holo/localization/common/localization_base.h>
#include <holo/localization/tightly_coupled_fusion/calibrator.h>
#include <holo/localization/tightly_coupled_fusion/common_types.h>
#include <holo/localization/tightly_coupled_fusion/dr_estimator.h>
#include <holo/localization/tightly_coupled_fusion/failure_recovery.h>
#include <holo/localization/tightly_coupled_fusion/fusion_estimator.h>
#include <holo/localization/tightly_coupled_fusion/imu_predictor.h>
#include <holo/localization/tightly_coupled_fusion/utm_zone_checker.h>

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

class LocalizationFusion : public LocalizationBase
{
public:
    /**
     * @brief handy typedefs
     */
    using Base = LocalizationBase;
    using Ptr  = std::shared_ptr<LocalizationFusion>;

    /**
     * @brief define callback function
     */
    using OdometryCallback  = ImuPredictor::OdometryCallback;
    using ImuBiasCallback   = ImuPredictor::ImuBiasCallback;
    using ErrorCodeCallback = std::function<void(uint8_t const, bool_t const)>;

    /**
     * @brief define masurement manager fusion ptr
     *
     */
    using MeasurementsManagerFusionPtr = holo::localization::tightly_coupled_fusion::MeasurementsManagerFusion::Ptr;
    using MeasurementsManagerFusionConstPtr =
        holo::localization::tightly_coupled_fusion::MeasurementsManagerFusion::ConstPtr;
    using MapServiceClientBasePtr = FusionEstimator::MapServiceClientBasePtr;

    /**
     * @brief parameters for localization fusion
     *
     */
    struct Parameters
    {
        Scalar                   fusion_frequency;              ///< frequency of fusion pipline        
        ImuPredictor::Parameters imu_prediction_fusion_params;  ///< parameters of imu prediction from fusion
        ImuPredictor::Parameters imu_prediction_dr_params;      ///< parameters of imu prediction from dr
        VehicleVelocityCorrector::Parameters vehicle_velocity_corrector_params;  ///< parameters of vehicle velocity
                                                                                 ///< corrector
        DrEstimator::Parameters     dr_estimator_params;                         ///< parameters of dr estimator
        FusionEstimator::Parameters fusion_estimator_params;                     ///< parameters of fusion estimator
        UtmZoneChecker::Parameters  utm_zone_checker_params;                     ///< parameters of utm zone checker
        bool_t                      enable_lateral_velocity_correction;  ///< whether enable lateral velocity correction
        Scalar time_threshold_for_fake_gnss_pvt;  ///< fake gnss pvt measurement will be created if gnss lost time is
                                                  ///< larger than this threshold, unit: [s]

        Calibrator::Parameters calibrator_params;  ///< parameters of calibrator

        Scalar   max_camera_lane_boundaries_delay; ///< max time of camera lane boundaries delay, unit: [s]

        /**
         * @brief constructor
         *
         * @param[in] _fusion_frequency frequency of fusion pipline         
         * @param[in] _imu_prediction_fusion_params parameters of imu prediction from fusion
         * @param[in] _imu_prediction_dr_params parameters of imu prediction from dr
         * correction coefficients from the calibrator.
         * @param[in] _vehicle_velocity_corrector_params parameters of vehicle velocity corrector
         * @param[in] _dr_estimator_params parameters of dr estimator
         * @param[in] _fusion_estimator_params parameters of fusion estimator
         * @param[in] _utm_zone_checker_params parameters of utm zone checker
         * @param[in] _enable_lateral_velocity_correction whether enable lateral velocity correction
         * @param[in] _time_threshold_for_fake_gnss_pvt fake gnss pvt will be created if gnss lost time is larger than
         * this threshold
         * @param[in] _calibrator_params parameters of the calibrator
         * @param[in] _max_camera_lane_boundaries_delay max time of CameraLaneBoundaries delay. uint: [s]
         */

        Parameters(Scalar const _fusion_frequency, ImuPredictor::Parameters const& _imu_prediction_fusion_params,
                   ImuPredictor::Parameters const&             _imu_prediction_dr_params,
                   VehicleVelocityCorrector::Parameters const& _vehicle_velocity_corrector_params,
                   DrEstimator::Parameters const&              _dr_estimator_params,
                   FusionEstimator::Parameters const&          _fusion_estimator_params,
                   UtmZoneChecker::Parameters const&           _utm_zone_checker_params,
                   bool_t const _enable_lateral_velocity_correction, Scalar const _time_threshold_for_fake_gnss_pvt,
                   Calibrator::Parameters const& _calibrator_params,
                   Scalar const _max_camera_lane_boundaries_delay = 0.5)
          : fusion_frequency(_fusion_frequency)          
          , imu_prediction_fusion_params(_imu_prediction_fusion_params)
          , imu_prediction_dr_params(_imu_prediction_dr_params)
          , vehicle_velocity_corrector_params(_vehicle_velocity_corrector_params)
          , dr_estimator_params(_dr_estimator_params)
          , fusion_estimator_params(_fusion_estimator_params)
          , utm_zone_checker_params(_utm_zone_checker_params)
          , enable_lateral_velocity_correction(_enable_lateral_velocity_correction)
          , time_threshold_for_fake_gnss_pvt(_time_threshold_for_fake_gnss_pvt)
          , calibrator_params(_calibrator_params)
          , max_camera_lane_boundaries_delay(_max_camera_lane_boundaries_delay)
        {
        }

        /**
         * @brief output stream for fusion parameters
         *
         * @param[in] os std::ostream&
         * @param[in] parameters parameters
         * @return std::ostream& contains content of the given parameters
         */
        friend std::ostream& operator<<(std::ostream& os, Parameters const& parameters)
        {
            os << "LocalizationFusionParameters: "
               << "\n fusion_frequency = " << parameters.fusion_frequency               
               << "\n imu prediction fusion parameters: " << parameters.imu_prediction_fusion_params
               << "\n imu prediction dr parameters: " << parameters.imu_prediction_dr_params
               << "\n vehicle velocity corrector parameters: " << parameters.vehicle_velocity_corrector_params
               << "\n dr estimator parameters: " << parameters.dr_estimator_params
               << "\n fusion estimator parameters: " << parameters.fusion_estimator_params
               << "\n utm zone checker parameters: " << parameters.utm_zone_checker_params
               << "\n enable_lateral_velocity_correction = " << parameters.enable_lateral_velocity_correction
               << "\n time_threshold_for_fake_gnss_pvt = " << parameters.time_threshold_for_fake_gnss_pvt
               << "\n calibrator parameters: " << parameters.calibrator_params 
               << "\n max_camera_lane_boundaries_delay = " << parameters.max_camera_lane_boundaries_delay << std::endl;
            return os;
        }

        /**
         * @brief static method to load parameters from yaml
         *
         * @param[in] node yaml node
         * @return the loaded parameters
         */
        static Parameters LoadFromYaml(holo::yaml::Node const& node);

        /**
         * @brief static method to generate example parameters for unit test
         *
         * @return the generated parameters for unit test
         */
        static Parameters GenerateExample();
    };  // Parameters

    /**
     * @brief constructor
     *
     * @param[in] parameters parameters for localization fusion
     */
    LocalizationFusion(Parameters const& parameters);

    /**
     * @brief destructor
     */
    virtual ~LocalizationFusion();

    /**
     * @brief set status to stop
     */
    virtual void Stop() override;

    /**
     * @brief  set status to spin
     */
    virtual void Spin() override;

    /**
     * @brief get parameters
     *
     * @return Parameters const&
     */
    Parameters const& GetParameters() const noexcept;

    /**
     * @brief process gnss pvt
     *
     * @param[in] measurement latest gnss pvt measurement
     * @return 1->process the measurement successfully
     *         0->do not process the measurement
     */
    int32_t ProcessGnssPvt(GnssPvtType const& measurement);

    /**
     * @brief process imu
     * @param[in] measurement latest imu measurement
     * @return 1->process the measurement successfully
     *         0->do not process the measurement
     */
    int32_t ProcessImu(ImuType const& measurement);

    /**
     * @brief process chassis state
     * @param[in] measurement latest chassis state measurement
     * @return 1->process the measurement successfully
     *         0->do not process the measurement
     */
    int32_t ProcessChassisState(ChassisState const& measurement);

    /**
     * @brief Process CameraLaneBoundaries measurement
     *
     * @param measurement CameraLaneBoundaries measurement
     * @return 1->process the measurement successfully
     *         0->do not process the measurement
     */
    int32_t ProcessCameraLaneBoundaries(CameraLaneBoundariesType const& measurement);
    /**
     * @brief Process Radar measurement
     *
     * @param measurement radar measurement
     * @return 1->process the measurement successfully
     *         0->do not process the measurement
     */
    int32_t ProcessRadar(ObstacleRadarPtrListType const& measurement);

    /**
     * @brief Process image objects measurement
     *
     * @param measurement image objects measurement
     * @return 1->process the measurement successfully
     *         0->do not process the measurement
     */
    int32_t ProcessImageObjects(ImageObjectsType const& measurement);

    /**
     * @brief process ground truth odometry
     *
     * @param[in] measurement latest groundtruth odometry measurement
     * @return 1->process the measurement successfully
     *         0->do not process the measurement
     */
    int32_t ProcessGroundTruthOdometry(OdometryType const& measurement);

    /**
     * @brief process integrated navigation
     *
     * @param[in] measurement latest integrated navigation measurement
     * @return 1->process the measurement successfully
     *         0->do not process the measurement
     */
    int32_t ProcessIntegratedNavigation(OdometryType const& measurement);

    /**
     * @brief set fusion odometry callback
     *
     * @param[in] handler fusion odometry callback
     */
    void SetFusionOdometryCallback(OdometryCallback const& handler);

    /**
     * @brief set dr odometry callback
     *
     * @param[in] handler dr odometry callback
     */
    void SetDrOdometryCallback(OdometryCallback const& handler);

    /**
     * @brief set fusion imu bias callback
     *
     * @param[in] handler fusion imu bias callback
     */
    void SetFusionImuBiasCallback(ImuBiasCallback const& handler);

    /**
     * @brief set dr imu bias callback
     *
     * @param[in] handler dr imu bias callback
     */
    void SetDrImuBiasCallback(ImuBiasCallback const& handler);

    /**
     * @brief set map service client
     *
     * @param[in] map_service_client_ptr pointer of map service client
     */
    void SetMapServiceClient(MapServiceClientBasePtr const& map_service_client_ptr);

    /**
     * @brief set error code callback
     *
     * @param[in] handler the pointer of callback function
     */
    void SetErrorCodeCallback(ErrorCodeCallback const& handler);

    /**
     * @brief Set the vehicle velocity correction coefficients callback for the calibrator
     *
     * @param[in] handler The pointer of callback function
     */
    void SetVehicleVelocityCorrectionCoefficientsCallback(
        Calibrator::VehicleVelocityCorrectionCoefficientsCallback const& handler);

    /**
     * @brief get const pointer of measurement manager fusion
     *
     * @return  const pointer of measurement manager fusion
     */
    MeasurementsManagerFusionConstPtr GetMeasurementManagerFusion() const;

protected:
    /**
     * @brief check whehter the conditions to run fusion pipeline are satisfied
     *
     * @return bool_t ture -> the conditions are satisfied, false -> otherwise
     */
    virtual bool_t checkPreCondition() override;

    /**
     * @brief core algorithm happens here
     */
    virtual void run() override;

    /**
     * @brief determine optimization timestamp interval
     * @details new_timestamp is the smaller of the newest imu timestamp and newest chassis state timestamp.
     * old_timestamp is the last one state timestamp of previous optimization state queue. old_gnss_pvt_timestamp
     * is the last one gnss_pvt timestamp of gnss pvt measurement queue used for previous optimization plus 0.01.
     * imu timestamp                   | | | | | | | | | | | | | | | 
     * chassis_state timestamp        | | | | | | | | | | | | | | | 
     * previous state queue              |   |   |   |   |        . 
     * previous gnss_pvt queue             |           | .        .
     * new_timestamp                                   . .        |
     * old_timestamp                                   . |
     * old_gnss_pvt_timestamp                           | 
     * when the system has CameraLaneBoundaries which has a time delay input, new_timestamp is newest CameraLaneBoundaries timestamp 
     * plus 0.01. That guarantees that CameraLaneBoundaries doesn't get lost in optimization.
     * imu timestamp                   | | | | | | | | | | | | | | |
     * CameraLaneBoundaries timestamp |           |           |  
     * chassis_state timestamp        | | | | | | | | | | | | | | | 
     * previous state queue              |   |   |   |   |    . 
     * previous gnss_pvt queue             |           | .    . 
     * new_timestamp                                   . .     |
     * old_timestamp                                   . |
     * old_gnss_pvt_timestamp                           |  
     * 
     * @param[out] new_timestamp right hand side of the optimization timestamp interval
     * @param[out] old_timestamp left hand side of the optimization timestamp interval 
     * @param[out] old_gnss_pvt_timestamp left hand side of gnss pvt timestamp interval, 
     * [old_gnss_pvt_timestamp, new_timestamp] will be used to get gnss pvt measurement
     * @return bool_t ture -> success, false -> false
     */
    bool_t determineTimestampInterval(Timestamp &new_timestamp, Timestamp &old_timestamp, 
                                      Timestamp &old_gnss_pvt_timestamp);

    /**
     * @brief update measurements manager fusion with the optimized fusion state
     *
     * @param[in] fusion_state optimized fusion state
     * @param[in] measurements_manager_fusion_ptr pointer of measurements manager fusion
     */
    void updateMeasurementsManagerFusion(FusionState const&            fusion_state,
                                         MeasurementsManagerFusionPtr& measurements_manager_fusion_ptr) const;

    /**
     * @brief check gnss pvt measurements
     *
     * @param old_timestamp the oldest timestamp of fusion window
     * @param gnss_pvt_measurements gnss pvt measurements
     * @return bool_t return false if the number of measurements that meet the requirements is 0
     */
    bool_t checkGnssPvtMeasurements(Timestamp const&          old_timestamp,
                                    std::vector<GnssPvtType>& gnss_pvt_measurements) const;

    /**
     * @brief create a fake gnss pvt measurement from latest fusion navstate in measurement to avoid losing global
     * constraints
     * @details the constraints will be added if the gnss pvt is not avaliable last
     * ${parameters_.time_threshold_for_fake_gnss_pvt} seconds the timestamp, position, velocity, parent coordinate
     * comes from latest fusion navstate the position covariance, velocity covariance comes from latest gnss pvt
     *
     * @param[in] old_fusion_state fusion state from last iteration
     * @paran[in] measurements_manager_fusion_ptr pointer of measurements manager fusion
     * @param[in] gnss_pvt_measurements the fake gnss pvt measurement
     *
     * @return whether the fake gnss pvt measurement is created
     */
    bool_t createFakeGnssPvtMeasurement(FusionState const&                  old_fusion_state,
                                        MeasurementsManagerFusionPtr const& measurements_manager_fusion_ptr,
                                        std::vector<GnssPvtType>&           gnss_pvt_measurements) const;

    /**
     * @brief parse fusion estimator status and publish corresponding error code
     *
     * @param[in] fusion_estimator_status status from fusion estimator
     */
    void processFusionEstimatorStatus(FusionEstimator::Status const& fusion_estimator_status) const;

    /**
     * @brief output error code
     *
     * @param[in] error_code error code which should be published
     * @param[in] is_error_code_exist whether this error code occurs
     */
    void outputErrorCode(ErrorCode const error_code, bool_t const is_error_code_exist) const;

protected:
    Parameters                   parameters_;                       ///< parameters for localization fusion
    MeasurementsManagerFusionPtr measurements_manager_fusion_ptr_;  ///< measurement manager fusion ptr
    ImuPredictor::Ptr            imu_predictor_fusion_ptr_;         ///< imu predictor from fusion
    ImuPredictor::Ptr            imu_predictor_dr_ptr_;             ///< imu predictor from dr
    std::shared_ptr<DrEstimator> dr_estimator_ptr_;                 ///< dr estimator
    FusionEstimator::Ptr         fusion_estimator_ptr_;             ///< fusion estimator
    UtmZoneChecker::Ptr          utm_zone_checker_ptr_;             ///< check utm zone id
    FailureRecovery              failure_recovery_;                 ///< recovery from different failure cases
    std::shared_ptr<std::thread> fusion_thread_ptr_;                ///< thread pointer for fusion
    FusionState                  fusion_state_;                     ///< fusion state

    MapServiceClientBasePtr map_service_client_ptr_;  ///< map service client
    ErrorCodeCallback       error_code_callback_;     ///< error code callback used to output error code

    Calibrator::Ptr calibrator_ptr_;  ///< calibrator smart pointer

    Timestamp previous_camera_lane_boundaries_timestamp_;  ///< previous CameraLaneBoundaries timestamp
    Scalar optimization_delay_time_;           ///< optimization delay time
};  // LocalizationFusion

/**
 * @}
 *
 */
}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_LOCALIZATION_FUSION_H_
