/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file measurements_manager_fusion.h
 * @brief This header file is used to define the manage all measurements
 * @author Wenzhi Liu (liuwenzhi@holomatic.com)
 * @date Feb 02, 2021
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_MEASUREMENTS_MANAGER_FUSION_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_MEASUREMENTS_MANAGER_FUSION_H_

#include <holo/localization/common/measurements_manager_base.h>
#include <holo/localization/tightly_coupled_fusion/common_types.h>
#include <holo/localization/tightly_coupled_fusion/imu_stationary_calibrator.h>
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
 * @brief Manage measurement queues of fusion
 *
 */
class MeasurementsManagerFusion : public MeasurementsManagerBase
{
public:
    /**
     * @brief define measurements buffer size
     *
     */
    const static std::size_t kRadarBufferSize                                 = 200u;
    const static std::size_t kImageObjectsBufferSize                          = 100u;
    const static std::size_t kStampedGTPreintegratedImuMeasurementsBufferSize = 100u;
    const static std::size_t kStampedCombinedVelocityMeasurementBufferSize    = 100u;
    const static std::size_t kStampedAdvancedNavstateBufferSize               = 100u;
    const static std::size_t kStampedPredictionAdvancedNavstateBufferSize     = 500u;
    const static std::size_t kIntegratedNavigationMeasurementsBufferSize      = 100u;
    const static std::size_t kStampedImuStationaryResultBufferSize            = 100u;

    using Base                                  = MeasurementsManagerBase;
    using Ptr                                   = std::shared_ptr<MeasurementsManagerFusion>;
    using ConstPtr                              = std::shared_ptr<const MeasurementsManagerFusion>;
    using StampedGTPreintegratedImuMeasurements = StampedT<GTPreintegratedImuMeasurements>;
    using StampedImuStationaryResult            = ImuStationaryCalibrator::StampedImuStationaryResult;

    using RadarBufferType =
        OrderedBuffer<ObstacleRadarPtrListType, kRadarBufferSize, StampedTimeCompareT<ObstacleRadarPtrListType>>;
    using ImageObjectsBufferType =
        OrderedBuffer<ImageObjectsType, kImageObjectsBufferSize, StampedTimeCompareT<ImageObjectsType>>;
    using StampedGTPreintegratedImuMeasurementsBufferType =
        OrderedBuffer<StampedGTPreintegratedImuMeasurements, kStampedGTPreintegratedImuMeasurementsBufferSize,
                      StampedTimeCompareT<StampedGTPreintegratedImuMeasurements>>;
    using StampedCombinedVelocityMeasurementBufferType =
        OrderedBuffer<StampedCombinedVelocityMeasurement, kStampedCombinedVelocityMeasurementBufferSize,
                      StampedTimeCompareT<StampedCombinedVelocityMeasurement>>;
    using StampedAdvancedNavstateBufferType =
        OrderedBuffer<StampedAdvancedNavstateType, kStampedAdvancedNavstateBufferSize,
                      StampedTimeCompareT<StampedAdvancedNavstateType>>;
    using StampedPredictionAdvancedNavstateBufferType =
        OrderedBuffer<StampedAdvancedNavstateType, kStampedPredictionAdvancedNavstateBufferSize,
                      StampedTimeCompareT<StampedAdvancedNavstateType>>;
    using IntegratedNavigationMeasurementsBufferType =
        OrderedBuffer<OdometryType, kIntegratedNavigationMeasurementsBufferSize, StampedTimeCompareT<OdometryType>>;
    using StampedImuStationaryResultBufferType =
        OrderedBuffer<StampedImuStationaryResult, kStampedImuStationaryResultBufferSize,
                      StampedTimeCompareT<StampedImuStationaryResult>>;

    using VehicleVelocityCorrectorPtr = VehicleVelocityCorrector::Ptr;

    using Base::GetCurrentMeasurement;
    using Base::GetLatestMeasurement;

    /**
     * @brief Construct a new Measurements Manager Fusion object
     * @param[in] _vehicle_velocity_corrector_ptr pointer of vehicle velocity corrector
     * @param[in] _local_gravity The initialized local gravity. Unit: m/s^2
     */
    MeasurementsManagerFusion(VehicleVelocityCorrectorPtr _vehicle_velocity_corrector_ptr =
                                  std::make_shared<VehicleVelocityCorrector>(VehicleVelocityCorrector::Parameters()),
                              Scalar const _local_gravity = Wgs84ReferenceSystemParameters::STANDARD_GRAVITY)
      : vehicle_velocity_corrector_ptr_(_vehicle_velocity_corrector_ptr)
      , local_gravity_(_local_gravity)
      , is_need_force_exit_high_precision_(false)
    {
    }

    /**
     * @brief Destroy the Measurements Manager Fusion object
     *
     */
    virtual ~MeasurementsManagerFusion() noexcept
    {
    }

    /**
     * @brief Push the imu into queue, pop out outdated measurements, then sort them in temporal order
     *
     * @param m imu which to be joined into queue
     * @return true for add imu successfully
     * @return false otherwise
     * @note the reptition Timestamp case isn't taken into account
     */
    bool_t AddImu(ImuType const& m);

    /**
     * @brief Push the CameraLaneBoundaries into queue, pop out outdated measurements, then sort them in
     * temporal order
     *
     * @param m CameraLaneBoundaries which to be joined into queue
     * @return true for add CameraLaneBoundariess successfully
     * @return false otherwise
     * @note the reptition Timestamp case isn't taken into account
     */
    bool_t AddCameraLaneBoundaries(CameraLaneBoundariesType const& m);

    /**
     * @brief Push the chassis state into queue, pop out outdated measurements, then sort them in temporal order
     *
     * @param m chassis state which to be joined into queue
     * @return true for add chassis state successfully
     * @return false otherwise
     * @note the reptition Timestamp case isn't taken into account
     * @note
     */
    bool_t AddChassisState(ChassisState const& m);

    /**
     * @brief Push the gnss into queue, pop out outdated measurements, then sort them in temporal order
     *
     * @param m gnss pvt which to be joined into queue
     * @return true for add gnss pvt successfully
     * @return false otherwise
     * @note the reptition Timestamp case isn't taken into account
     */
    bool_t AddGnssPvt(GnssPvtType const& m);

    /**
     * @brief Push the radar into queue, pop out outdated measurements, then sort them in temporal order
     *
     * @param m radar which to be joined into queue
     * @return true for add radar successfully
     * @return false otherwise
     * @note the reptition Timestamp case isn't taken into account
     */
    bool_t AddRadar(ObstacleRadarPtrListType const& m);

    /**
     * @brief Push the image objects into queue, pop out outdated measurements, then sort them in temporal order
     *
     * @param m image objects which to be joined into queue
     * @return true for add image objects successfully
     * @return false otherwise
     * @note the reptition Timestamp case isn't taken into account
     */
    bool_t AddImageObjects(ImageObjectsType const& m);

    /**
     * @brief Push the preintegrated imu measurements into queue, pop out outdated measurements, then sort them in
     * temporal order
     *
     * @param m stamped preintegrated imu measurements which to be joined into queue
     * @return true for add preintegrated imu measurements successfully
     * @return false otherwise
     * @note the reptition Timestamp case isn't taken into account
     */
    bool_t AddPreintegratedImuMeasurements(StampedGTPreintegratedImuMeasurements const& m);

    /**
     * @brief Push the imu stationary result into queue, pop out outdated result, then sort them in
     * temporal order
     *
     * @param m stamped imu stationary result which to be joined into queue
     * @return true for add imu stationary result successfully
     * @return false otherwise
     * @note the reptition Timestamp case isn't taken into account
     */
    bool_t AddImuStationaryResult(StampedImuStationaryResult const& m);

    /**
     * @brief Push the stamped combined velocity measurement into queue, pop out outdated measurements, then sort them
     * in temporal order
     *
     * @param m stamped combined velocity measurement which to be joined into queue
     * @return true for add stamped combined velocity measurement successfully
     * @return false otherwise
     * @note the reptition Timestamp case isn't taken into account
     */
    bool_t AddCombinedVelocityMeasurement(StampedCombinedVelocityMeasurement const& m);

    /**
     * @brief Push the dr navstate into queue, pop out outdated measurements, then sort them in temporal order
     *
     * @param m dr navstate which to be joined into queue
     * @return true for add dr navstate successfully
     * @return false otherwise
     * @note the reptition Timestamp case isn't taken into account
     */
    bool_t AddDrNavstate(StampedAdvancedNavstate const& m);

    /**
     * @brief Push the fusion navstate into queue, pop out outdated measurements, then sort them in temporal order
     *
     * @param m fusion navstate which to be joined into queue
     * @return true for add fusion navstate successfully
     * @return false otherwise
     * @note the reptition Timestamp case isn't taken into account
     */
    bool_t AddFusionNavstate(StampedAdvancedNavstate const& m);

    /**
     * @brief Push the dr prediction navstate into queue, pop out outdated measurements, then sort them in temporal
     * order
     * @param m stamped dr prediction navstate which to be joined into queue
     * @return true for add dr prediction navstate successfully
     * @return false otherwise
     * @note the reptition Timestamp case isn't taken into account
     */
    bool_t AddDrPredictionNavstate(StampedAdvancedNavstate const& m);

    /**
     * @brief Push the fusion prediction navstate into queue, pop out outdated measurements, then sort them in temporal
     * order
     * @param m stamped fusion prediction navstate which to be joined into queue
     * @return true for add fusion prediction navstate successfully
     * @return false otherwise
     * @note the reptition Timestamp case isn't taken into account
     */
    bool_t AddFusionPredictionNavstate(StampedAdvancedNavstate const& m);

    /**
     * @brief Push the Integrated navigation measurement into queue, pop out outdated measurements, then sort them in
     * temporal order
     *
     * @param m Integrated navigation measurement which to be joined into queue
     * @return true for add Integrated navigation measurement successfully
     * @return false otherwise
     * @note the reptition Timestamp case isn't taken into account
     */
    bool_t AddIntegratedNavigation(OdometryType const& m);

    /**
     * @brief return radar number
     */
    inline uint16_t GetRadarNum() const
    {
        return static_cast<uint16_t>(radar_buffer_.size());
    }

    /**
     * @brief return preintegrated imu measurements number
     */
    inline uint16_t GetPreintegratedImuMeasurementsNum() const
    {
        return static_cast<uint16_t>(stamped_gt_preintegrated_imu_measurements_buffer_.size());
    }

    /**
     * @brief return stamped combined velocity measurement number
     */
    inline uint16_t GetCombinedVelocityMeasurementsNum() const
    {
        return static_cast<uint16_t>(stamped_combined_velocity_measurements_buffer_.size());
    }

    /**
     * @brief return dr navstate number
     */
    inline uint16_t GetDrNavstateNum() const
    {
        return static_cast<uint16_t>(stamped_dr_navstate_buffer_.size());
    }

    /**
     * @brief return fusion navstate number
     */
    inline uint16_t GetFusionNavstateNum() const
    {
        return static_cast<uint16_t>(stamped_fusion_navstate_buffer_.size());
    }

    /**
     * @brief return dr prediction navstate number
     */
    inline uint16_t GetDrPredictionNavstateNum() const
    {
        return static_cast<uint16_t>(stamped_dr_prediction_navstate_buffer_.size());
    }

    /**
     * @brief return fusion prediction navstate number
     */
    inline uint16_t GetFusionPredictionNavstateNum() const
    {
        return static_cast<uint16_t>(stamped_fusion_prediction_navstate_buffer_.size());
    }

    /**
     * @brief return Integrated navigation number
     */
    uint16_t GetIntegratedNavigationNum() const
    {
        return static_cast<uint16_t>(integrated_navigation_measurements_buffer_.size());
    }

    /**
     * @brief Clear imu buffer
     *
     */
    void ClearImu();

    /**
     * @brief Clear CameraLaneBoundaries buffer
     *
     */
    void ClearCameraLaneBoundaries();

    /**
     * @brief Clear chassis state buffer
     *
     */
    void ClearChassisState();

    /**
     * @brief Clear gnss pvt buffer
     *
     */
    void ClearGnssPvt();

    /**
     * @brief Clear radar buffer
     *
     */
    void ClearRadar();

    /**
     * @brief Clear image object buffer
     *
     */
    void ClearImageObjects();

    /**
     * @brief Clear preintegrated imu measurements buffer
     *
     */
    void ClearPreintegratedImuMeasurements();

    /**
     * @brief Clear imu stationary results buffer
     *
     */
    void ClearImuStationaryResult();

    /**
     * @brief Clear combined velocity measurement buffer
     *
     */
    void ClearCombinedVelocityMeasurement();

    /**
     * @brief Clear dr navstate buffer
     *
     */
    void ClearDrNavstate();

    /**
     * @brief Clear fusion navstate buffer
     *
     */
    void ClearFusionNavstate();

    /**
     * @brief Clear dr prediction navstate buffer
     *
     */
    void ClearDrPredictionNavstate();

    /**
     * @brief Clear fusion prediction navstate buffer
     *
     */
    void ClearFusionPredictionNavstate();

    /**
     * @brief Clear integrated navigation measurements buffer
     *
     */
    void ClearIntegratedNavigationMeasurements();

    /**
     * @brief get latest radar of the queue
     *
     * @param m radar measurement
     * @return bool_t it returns false when fails to find such a measurement
     */
    bool_t GetLatestMeasurement(ObstacleRadarPtrListType& m);

    /**
     * @brief get latest image object of the queue
     *
     * @param m image object measurement
     * @return bool_t it returns false when fails to find such a measurement
     */
    bool_t GetLatestMeasurement(ImageObjectsType& m);

    /**
     * @brief get latest preintegrated imu measurements of the queue
     *
     * @param m stamped preintegrated imu measurements
     * @return bool_t it returns false when fails to find such a measurement
     */
    bool_t GetLatestMeasurement(StampedGTPreintegratedImuMeasurements& m);

    /**
     * @brief get latest imu stationary result of the queue
     *
     * @param m stamped imu stationary result
     * @return bool_t it returns false when fails to find such a result
     */
    bool_t GetLatestMeasurement(StampedImuStationaryResult& m);

    /**
     * @brief get latest combined velocity measurement of the queue
     *
     * @param m stamped combined velocity measurement
     * @return bool_t it returns false when fails to find such a measurement
     */
    bool_t GetLatestMeasurement(StampedCombinedVelocityMeasurement& m);

    /**
     * @brief get latest dr navstate of the queue
     *
     * @param m stamped dr navstate
     * @return bool_t it returns false when fails to find such a measurement
     */
    bool_t GetLatestDrNavstate(StampedAdvancedNavstateType& m);

    /**
     * @brief get latest fusion navstate of the queue
     *
     * @param m stamped fusion navstate
     * @return bool_t it returns false when fails to find such a measurement
     */
    bool_t GetLatestFusionNavstate(StampedAdvancedNavstateType& m);

    /**
     * @brief get latest dr prediction navstate of the queue
     *
     * @param m dr prediction navstate
     * @return bool_t it returns false when fails to find such a measurement
     */
    bool_t GetLatestDrPredictionNavstate(StampedAdvancedNavstateType& m);

    /**
     * @brief get latest fusion prediction navstate of the queue
     *
     * @param m fusion prediction navstate
     * @return bool_t it returns false when fails to find such a measurement
     */
    bool_t GetLatestFusionPredictionNavstate(StampedAdvancedNavstateType& m);

    /**
     * @brief get latest integrated navigation measurement of the queue
     *
     * @param m integrated navigation measurements
     * @return bool_t it returns false when fails to find such a measurement
     */
    bool_t GetLatestIntegratedNavigationMeasurement(OdometryType& m);

    /**
     * @brief get nearest radar of the queue with a timestamp
     *
     * @param t timestamp
     * @param m radar measurement
     * @return bool_t it returns false when fails to find such a measurement
     */
    bool_t GetNearestMeasurement(Timestamp const& t, ObstacleRadarPtrListType& m);

    /**
     * @brief get nearest image object of the queue with a timestamp
     *
     * @param t timestamp
     * @param m image object measurement
     * @return bool_t it returns false when fails to find such a measurement
     */
    bool_t GetNearestMeasurement(Timestamp const& t, ImageObjectsType& m);

    /**
     * @brief get nearest dr navstate of the queue with a timestamp
     *
     * @param t timestamp
     * @param m stamped dr navstate
     * @return bool_t it returns false when fails to find such a measurement
     */
    bool_t GetNearestDrNavstate(Timestamp const& t, StampedAdvancedNavstateType& m);

    /**
     * @brief get nearest fusion navstate of the queue with a timestamp
     *
     * @param t timestamp
     * @param m stamped fusion navstate
     * @return bool_t it returns false when fails to find such a measurement
     */
    bool_t GetNearestFusionNavstate(Timestamp const& t, StampedAdvancedNavstateType& m);

    /**
     * @brief get nearest dr prediction navstate of the queue with a timestamp
     *
     * @param t timestamp
     * @param m dr prediction navstate
     * @return bool_t it returns false when fails to find such a measurement
     */
    bool_t GetNearestDrPredictionNavstate(Timestamp const& t, StampedAdvancedNavstate& m);

    /**
     * @brief get nearest fusion prediction navstate of the queue with a timestamp
     *
     * @param t timestamp
     * @param m fusion prediction navstate
     * @return bool_t it returns false when fails to find such a measurement
     */
    bool_t GetNearestFusionPredictionNavstate(Timestamp const& t, StampedAdvancedNavstate& m);

    /**
     * @brief get nearest integrated navigation measurement of the queue with a timestamp
     *
     * @param t timestamp
     * @param m integrated navigation measurement
     * @return bool_t it returns false when fails to find such a measurement
     */
    bool_t GetNearestIntegratedNavigationMeasurement(Timestamp const& t, OdometryType& m);

    /**
     * @brief get imu at current timestamp
     *
     * @param t timestamp
     * @param m imu measurement
     * @return bool_t it returns false when fails to find such a measurement
     */
    bool_t GetCurrentMeasurement(Timestamp const& t, ImuType& m);

    /**
     * @brief get dr prediction navstate at current timestamp
     *
     * @param t timestamp
     * @param m stamped dr prediction navstate
     * @return bool_t it return false when fails to find such a measurement
     */
    bool_t GetCurrentDrPredictionNavstate(Timestamp const& t, StampedAdvancedNavstate& m);

    /**
     * @brief get fusion prediction navstate at current timestamp
     *
     * @param t timestamp
     * @param m stamped fusion prediction navstate
     * @return bool_t it return false when fails to find such a measurement
     */
    bool_t GetCurrentFusionPredictionNavstate(Timestamp const& t, StampedAdvancedNavstate& m);

    /**
     * @brief Get the Current Fusion Navstate object
     *
     * @param[in] t timestamp
     * @param[in] m stamped fusion navstate
     * @return bool_t it return false when fails to find such a measurement
     */
    bool_t GetCurrentFusionNavstate(Timestamp const& t, StampedAdvancedNavstate& m);

    /**
     * @brief get integrated navigation measurement at current timestamp
     *
     * @param t timestamp
     * @param m integrated navigation measurement
     * @return bool_t it return false when fails to find such a measurement
     */
    bool_t GetCurrentIntegratedNavigationMeasurement(Timestamp const& t, OdometryType& m);

    /**
     * @brief Get radars between two timestamp
     *
     * @param left left timestamp
     * @param right right timestamp
     * @param multi_radar radar's muasurements
     * @return bool_t it returns false when fails to find such measurements
     */
    bool_t GetMeasurementsBetween(Timestamp const& left, Timestamp const& right,
                                  std::vector<ObstacleRadarPtrListType>& multi_radar);

    /**
     * @brief Get image object between two timestamp
     *
     * @param left left timestamp
     * @param right right timestamp
     * @param multi_image_object image object's muasurements
     * @return bool_t it returns false when fails to find such measurements
     */
    bool_t GetMeasurementsBetween(Timestamp const& left, Timestamp const& right,
                                  std::vector<ImageObjectsType>& multi_image_objects);

    /**
     * @brief Get multi preintegrated imu measurements between two timestamp
     *
     * @param left left timestamp
     * @param right right timestamp
     * @param multi_stamped_gt_preintegrated_imu_measurements stamped preintegrated imu measurements vector
     * @return bool_t it returns false when fails to find such measurements
     */
    bool_t GetMeasurementsBetween(
        Timestamp const& left, Timestamp const& right,
        std::vector<StampedGTPreintegratedImuMeasurements>& multi_stamped_gt_preintegrated_imu_measurements);

    /**
     * @brief Get multi combined velocity measurements between two timestamp
     *
     * @param left left timestamp
     * @param right right timestamp
     * @param multi_stamped_combined_velocity_measurements stamped combined velocity measurements vector
     * @return bool_t it returns false when fails to find such measurements
     */
    bool_t GetMeasurementsBetween(
        Timestamp const& left, Timestamp const& right,
        std::vector<StampedCombinedVelocityMeasurement>& multi_stamped_combined_velocity_measurements);

    /**
     * @brief Get dr navstate between two timestamp
     *
     * @param left left timestamp
     * @param right right timestamp
     * @param multi_stamped_dr_navstate stamped dr navstate vector
     * @return bool_t it returns false when fails to find such measurements
     */
    bool_t GetDrNavstateBetween(Timestamp const& left, Timestamp const& right,
                                std::vector<StampedAdvancedNavstateType>& multi_stamped_dr_navstate);

    /**
     * @brief Get fusion navstate between two timestamp
     *
     * @param left left timestamp
     * @param right right timestamp
     * @param multi_stamped_fusion_navstate stamped fusion navstate vector
     * @return bool_t it returns false when fails to find such measurement
     */
    bool_t GetFusionNavstateBetween(Timestamp const& left, Timestamp const& right,
                                    std::vector<StampedAdvancedNavstateType>& multi_stamped_fusion_navstate);

    /**
     * @brief Get dr prediction navstate between two timestamp
     *
     * @param left left timestamp
     * @param right right timestamp
     * @param multi_stamped_dr_prediction_navstate stamped dr prediction navstate vector
     * @return bool_t it returns false when fails to find such measurement
     */
    bool_t GetDrPredictionNavstateBetween(Timestamp const& left, Timestamp const& right,
                                          std::vector<StampedAdvancedNavstate>& multi_stamped_dr_prediction_navstate);

    /**
     * @brief Get fusion prediction navstate between two timestamp
     *
     * @param left left timestamp
     * @param right right timestamp
     * @param multi_stamped_fusion_prediction_navstate stamped fusion prediction navstate vector
     * @return bool_t it returns false when fails to find such measurement
     */
    bool_t
    GetFusionPredictionNavstateBetween(Timestamp const& left, Timestamp const& right,
                                       std::vector<StampedAdvancedNavstate>& multi_stamped_fusion_prediction_navstate);

    /**
     * @brief Get dr integrated navigation measurements between two timestamp
     *
     * @param left left timestamp
     * @param right right timestamp
     * @param multi_integrated_navigation_measurements integrated navigation measurement vector
     * @return bool_t it returns false when fails to find such measurements
     */
    bool_t
    GetIntegratedNavigationMeasurementsBetween(Timestamp const& left, Timestamp const& right,
                                               std::vector<OdometryType>& multi_integrated_navigation_measurements);

    /**
     * @brief get the aligned dr prediction navstate between two timestamp
     *
     * @param left left timestamp
     * @param right right timestamp
     * @param multi_stamped_dr_prediction_navstate stamped dr prediction navstate vector
     * @return bool_t it return false when fails to find such measurement
     */
    bool_t
    GetAlignedDrPredictionNavstateBetween(Timestamp const& left, Timestamp const& right,
                                          std::vector<StampedAdvancedNavstate>& multi_stamped_dr_prediction_navstate);

    /**
     * @brief get the aligned fusion prediction navstate between two timestamp
     *
     * @param left left timestamp
     * @param right right timestamp
     * @param multi_stamped_fusion_prediction_navstate stamped fusion prediction navstate vector
     * @return bool_t it return false when fails to find such measurement
     */
    bool_t GetAlignedFusionPredictionNavstateBetween(
        Timestamp const& left, Timestamp const& right,
        std::vector<StampedAdvancedNavstate>& multi_stamped_fusion_prediction_navstate);

    /**
     * @brief get ego lane raw measurements between two timestamp
     *
     * @param old_timestamp old timestamp
     * @param new_timestamp new timestamp
     * @param ego_lane_raw_measurements ego lane raw measurements
     * @return bool_t it returns false when fails to find such measurements
     */
    bool_t GetEgoLaneRawMeasurements(Timestamp const& old_timestamp, Timestamp const& new_timestamp,
                                     EgoLaneRawMeasurements& ego_lane_raw_measurements);

    /**
     * @brief get visual semantic raw measurements between two timestamp
     *
     * @param old_timestamp old timestamp
     * @param new_timestamp new timestamp
     * @param visual_semantic_raw_measurements visual semantic raw measurements
     * @return bool_t it returns false when fails to find such measurements
     */
    bool_t
    GetVisualSemanticRawMeasurements(Timestamp const& old_timestamp, Timestamp const& new_timestamp,
                                     std::vector<VisualSemanticRawMeasurement>& visual_semantic_raw_measurements);

    /**
     * @brief get fusion raw measurements between two timestamp
     *
     * @param old_timestamp old timestamp
     * @param new_timestamp new timestamp
     * @param old_gnss_pvt_timestamp old timestamp for gnss pvt because gnss pvt might delay
     * @param fusion_raw_measurements fusion raw measurements
     * @param enable_lateral_velocity_correction flag of enable lateral velocity correction, default:false
     * @return bool_t it return false when fails to find such measurements
     */
    bool_t GetFusionRawMeasurements(Timestamp const& old_timestamp, Timestamp const& new_timestamp,
                                    Timestamp const&       old_gnss_pvt_timestamp,
                                    FusionRawMeasurements& fusion_raw_measurements,
                                    bool_t const           enable_lateral_velocity_correction = false);

    /**
     * @brief get the corrected vehicle velocity object
     *
     * @param old_timestamp old timestamp
     * @param new_timestamp new timestamp
     * @param multi_stamped_corrected_vehicle_velocity corrected stamped vehicle velocity vector
     * @param enable_lateral_velocity_correction flag of enable lateral velocity correction, default: false
     * @return bool_t it return false when fails to find such measurements
     */
    bool_t GetCorrectedVehicleVelocity(
        Timestamp const& old_timestamp, Timestamp const& new_timestamp,
        std::vector<StampedT<CorrectedVehicleVelocity>>& multi_stamped_corrected_vehicle_velocity,
        bool_t const                                     enable_lateral_velocity_correction = false);

    /**
     * @brief Get the local gravity value. Unit: m/s^2
     *
     * @return The local gravity value.
     */
    Scalar GetLocalGravity()
    {
        std::unique_lock<std::mutex> lock(local_gravity_mutex_);
        return local_gravity_;
    }

    /**
     * @brief Set the local gravity value. Unit: m/s^2
     *
     * @param[in] local_gravity The local gravity value.
     */
    void SetLocalGravity(Scalar const local_gravity)
    {
        std::unique_lock<std::mutex> lock(local_gravity_mutex_);
        local_gravity_ = local_gravity;
    }

    /**
     * @brief check if need force exit high precision right now by return is_need_force_exist_high_precision_ Flag
     *
     * @return if is true, means need force exit high precision.
     */
    bool_t IsNeedForceExitHighPrecision()
    {
        std::unique_lock<std::mutex> lock(is_need_force_exit_high_precision_mutex_);
        return is_need_force_exit_high_precision_;
    }

    /**
     * @brief Force Exit High Precision by setting is_need_force_exit_high_precision_ Flag
     *
     * @param[in] is_need_force_exit_high_precision return
     */
    void SetNeedForceExitHighPrecision(bool_t const is_need_force_exit_high_precision)
    {
        std::unique_lock<std::mutex> lock(is_need_force_exit_high_precision_mutex_);
        is_need_force_exit_high_precision_ = is_need_force_exit_high_precision;
    }

protected:
    /**
     * @brief accumulate timestamp vector
     *
     * @tparam T type of measurement
     * @param multi_measurement measurement vector
     * @param multi_timestamp timestamp vector
     */
    template <typename T>
    void accumulateTimestampVector(std::vector<T> const&   multi_measurement,
                                   std::vector<Timestamp>& multi_timestamp) const
    {
        for (T const& measurement : multi_measurement)
        {
            multi_timestamp.emplace_back(measurement.GetTimestamp());
        }
    }

    /**
     * @brief Get the Navstate Aligned With Measurements object
     *
     * @tparam Args parameter pack which is type of measurement
     * @param multi_navstate navstates which are aligned with all measurements
     * @param prediction_funciton pointer of prediction function
     * @param args parameter pack which is vector of measurement
     * @return bool_t it return false when fails to find such measurements
     */
    template <typename... Args>
    bool_t getNavstateAlignedWithMeasurements(
        std::vector<StampedAdvancedNavstate>& multi_navstate,
        bool_t (MeasurementsManagerFusion::*prediction_funciton)(Timestamp const&, StampedAdvancedNavstate&),
        std::vector<Args> const&... args)
    {
        std::vector<Timestamp> multi_timestamp;

        int arr[] = {(accumulateTimestampVector(args, multi_timestamp), 0)...};

        (void)arr;
        std::sort(multi_timestamp.begin(), multi_timestamp.end());

        StampedAdvancedNavstate navstate;
        bool_t                  result = true;

        for (Timestamp const& t : multi_timestamp)
        {
            if ((this->*prediction_funciton)(t, navstate))
            {
                multi_navstate.emplace_back(navstate);
            }
            else
            {
                result = false;
            }
        }

        return result;
    }

private:
    // mutex for radar buffer
    std::mutex radar_buffer_mutex_;

    // mutex for image object buffer
    std::mutex image_objects_buffer_mutex_;

    // mutex for stamped preintegrated imu measurements buffer
    std::mutex stamped_gt_preintegrated_imu_measurements_buffer_mutex_;

    // mutex for stamped imu stationary measurements buffer
    std::mutex stamped_imu_stationary_results_buffer_mutex_;

    // mutex for stamped combined velocity measuremets buffer
    std::mutex stamped_combined_velocity_measurements_buffer_mutex_;

    // mutex for stamped dr navstate buffer
    std::mutex stamped_dr_navstate_buffer_mutex_;

    //  mutex for stamped fusion navstate buffer
    std::mutex stamped_fusion_navstate_buffer_mutex_;

    // mutex for stamped dr prediction navstate buffer
    std::mutex stamped_dr_prediction_navstate_buffer_mutex_;

    // mutex for stamped fusion prediction navstate buffer
    std::mutex stamped_fusion_prediction_navstate_buffer_mutex_;

    // mutex for integrated navigation measurements buffer
    std::mutex integrated_navigation_measurements_buffer_mutex_;

    // mutex for local gravity value
    std::mutex local_gravity_mutex_;

    // mutex for force exit high precision
    std::mutex is_need_force_exit_high_precision_mutex_;

    // radar buffer
    RadarBufferType radar_buffer_;

    // image object buffer
    ImageObjectsBufferType image_objects_buffer_;

    // stamped preintegrated imu measurements buffer
    StampedGTPreintegratedImuMeasurementsBufferType stamped_gt_preintegrated_imu_measurements_buffer_;

    // stamped imu stationary results buffer
    StampedImuStationaryResultBufferType stamped_imu_stationary_results_buffer_;

    // stamped combined vector measurements buffer
    StampedCombinedVelocityMeasurementBufferType stamped_combined_velocity_measurements_buffer_;

    // stamped dr navstate buffer
    StampedAdvancedNavstateBufferType stamped_dr_navstate_buffer_;

    // stamped fusion navstate buffer
    StampedAdvancedNavstateBufferType stamped_fusion_navstate_buffer_;

    // stamped dr prediction navstate buffer
    StampedPredictionAdvancedNavstateBufferType stamped_dr_prediction_navstate_buffer_;

    // stamped fusion  prediction navstate buffer
    StampedPredictionAdvancedNavstateBufferType stamped_fusion_prediction_navstate_buffer_;

    // Integrated navigation measurements buffer
    IntegratedNavigationMeasurementsBufferType integrated_navigation_measurements_buffer_;

    // pointer of vehicle velocity corrector
    VehicleVelocityCorrectorPtr vehicle_velocity_corrector_ptr_;

    // Local gravity value. Unit: m/s^2
    Scalar local_gravity_;

    // its a Communication flag ,use for failure_recovery module call imu_predictor to force exit high precision right now
    bool_t is_need_force_exit_high_precision_;

};  // class MeasurementsManagerFusion

/**
 * @}
 *
 */

}  // namespace tightly_coupled_fusion

template <>
StampedAdvancedNavstate MeasurementsManagerBase::interpolateT<StampedAdvancedNavstate>(
    StampedAdvancedNavstate const& left, StampedAdvancedNavstate const& right, Timestamp const& stamp);

template <>
StampedAdvancedNavstate MeasurementsManagerBase::extrapolateT<StampedAdvancedNavstate>(
    StampedAdvancedNavstate const& left, StampedAdvancedNavstate const& right, Timestamp const& stamp);

}  // namespace localization

}  // namespace holo

#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_MEASUREMENTS_MANAGER_FUSION_H_
