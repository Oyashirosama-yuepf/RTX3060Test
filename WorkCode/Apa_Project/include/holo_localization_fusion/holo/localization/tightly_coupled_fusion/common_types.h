/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file common_types.h
 * @brief this file aims to define the common types which will be used in the whole tightly coupled fusion project
 * @author Shuaijie Li(lishuaijie@holomatic.com)
 * @date "2021-02-04"
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_COMMON_TYPES_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_COMMON_TYPES_H_

#include <holo/common/optional.h>
#include <holo/localization/common/imu_preintegration.h>
#include <holo/localization/common/types.h>
#include <holo/localization/common/wheel_preintegration.h>
#include <holo/localization/sam/sam.h>
#include <holo/localization/tightly_coupled_fusion/map/map_service_client_base.h>
#include <holo/localization/tightly_coupled_fusion/sign/types.h>
#include <holo/obstacle/obstacle_list.h>
#include <holo/obstacle/obstacle_radar.h>

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

using MapServiceClientBase     = holo::localization::tightly_coupled_fusion::map::MapServiceClientBase;
using MapLinkId                = MapServiceClientBase::LinkId;
using MapLaneId                = MapServiceClientBase::LaneId;
using MapObjectType            = MapServiceClientBase::MapObject;
using ObstacleRadarPtrListType = holo::obstacle::ObstacleRadarPtrList;
using ObstacleRadarType        = holo::obstacle::ObstacleRadarT<holo::float32_t>;
using ImageObjectsType         = holo::localization::tightly_coupled_fusion::sign::ImageObjectsType;
/// rename WheelPreintegrationMeasurement and its parameters to use same naming style as PreintegratedImuMeasurement
using PreintegratedWheelMeasurements = holo::localization::WheelPreintegrationMeasurement;
using PreintegrationWheelParams      = holo::localization::WheelPreintegrationMeasurement::WheelPreintegrationParams;
using StampedAdvancedNavstateType    = StampedT<AdvancedNavstateType>;
using Timestamp                      = holo::common::details::Timestamp;
using Duration                       = holo::common::details::Duration;
using VisualSemanticRawMeasurement   = holo::localization::tightly_coupled_fusion::sign::VisualSemanticRawMeasurement;
/**
 * @brief define struct to store the corrected vehicle velocity including four wheel speed and vehicle speed
 *
 */
struct CorrectedVehicleVelocity
{
    Scalar      rear_left_wheel_speed;   ///< corrected rear left wheel speed (unit: m/s)
    Scalar      rear_right_wheel_speed;  ///< corrected rear right wheel speed (unit: m/s)
    Vector3Type vehicle_velocity;        ///< corrected vehicle velocity (unit: m/s)

    /**
     * @brief constructor
     *
     * @param _rear_left_wheel_speed corrected rear left wheel speed
     * @param _rear_right_wheel_speed corrected rear right wheel speed
     * @param _vehicle_velocity corrected vehicle velocity
     */
    CorrectedVehicleVelocity(Scalar const       _rear_left_wheel_speed  = Scalar(0.0),
                             Scalar const       _rear_right_wheel_speed = Scalar(0.0),
                             Vector3Type const& _vehicle_velocity       = Vector3Type::Zero())
      : rear_left_wheel_speed(_rear_left_wheel_speed)
      , rear_right_wheel_speed(_rear_right_wheel_speed)
      , vehicle_velocity(_vehicle_velocity)
    {
    }
};  // CorrectedVehicleVelocity

using StampedCorrectedVehicleVelocity = StampedT<CorrectedVehicleVelocity>;

/**
 * @brief define struct to store velocity measurements: pwm, velocity factor measurement
 */
struct CombinedVelocityMeasurement
{
    /**
     * @brief velocity factor measurement
     */
    struct VelocityFactorMeasurement
    {
        GTVector3 velocity;  ///< velocity in body frame
        GTVector3 sigmas;    ///< velocity's standard deviation

        /**
         * @brief constructor
         *
         * @param[in] _velocity velocity in body frame
         * @param[in] _sigmas standard deviation of velocity
         */
        VelocityFactorMeasurement(GTVector3 const& _velocity = GTVector3::Constant(0.0),
                                  GTVector3 const& _sigmas   = GTVector3::Constant(1e3))
          : velocity(_velocity), sigmas(_sigmas)
        {
        }
    };  // VelocityFactorMeasurement

    OptionalT<PreintegratedWheelMeasurements> optional_pwm;
    OptionalT<VelocityFactorMeasurement>      optional_velocity_factor_measurement;

    /**
     * @brief constructor
     *
     * @param[in] _optional_pwm optional pwm
     * @param[in] _optional_velocity_factor_measurement optional velocity factor measurement
     */
    CombinedVelocityMeasurement(
        OptionalT<PreintegratedWheelMeasurements> const& _optional_pwm                         = optional::none,
        OptionalT<VelocityFactorMeasurement> const&      _optional_velocity_factor_measurement = optional::none)
      : optional_pwm(_optional_pwm), optional_velocity_factor_measurement(_optional_velocity_factor_measurement)
    {
    }
};  // VelocityMeasurement

using StampedCombinedVelocityMeasurement = StampedT<CombinedVelocityMeasurement>;

/**
 * @brief define struct to store raw measurements for ego lane estimator
 *
 */
struct EgoLaneRawMeasurements
{
    ///< The CameraLaneBoundaries which stores the detected lines and road edges
    std::vector<CameraLaneBoundariesType> camera_lane_boundaries_measurements;
    /// The predicted fusion NavState based on the last smoothing result and Imu preintegration
    std::vector<StampedAdvancedNavstateType> predicted_fusion_navstates;
    /**
     * @brief The dead-reckoning(DR) NavState based on the DR prediction process
     * @attention The timestamp of the DR NavStates must be aligned to the timestamp of 
     * CameraLaneBoundaries measurements.
     */
    std::vector<StampedAdvancedNavstateType> predicted_dr_navstates;
    std::vector<ObstacleRadarPtrListType>    radar_obstacle_measurements;  ///< The detected radar obstacle measurements
};

/**
 * @brief Define struct to store raw measurements for localization fusion
 *
 */
struct FusionRawMeasurements
{
    std::vector<ImuType>                         imu_measurements;
    std::vector<StampedCorrectedVehicleVelocity> corrected_vehicle_velocity_measurements;
    std::vector<GnssPvtType>                     gnss_pvt_measurements;
    std::vector<OdometryType>                    integrated_navigation_measurements;
    EgoLaneRawMeasurements                       ego_lane_raw_measurements;
    std::vector<VisualSemanticRawMeasurement>    visual_semantic_raw_measurements;
};  // FusionRawMeasurements

/**
 * @brief The enum types of the defintaion of vehicle motion state.
 *
 */
enum class VehicleMotionState : uint8_t
{
    STATIONRAY                   = 0x00,  ///< Stationray state with the zero velocity
    VARIABLE_SPEED_LINEAR_MOTION = 0x01,  ///< Linear motion with the variable vehicle speed
    UNIFORM_SPEED_LINEAR_MOTION  = 0x02,  ///< Linear motion with the uniform vehicle speed
    UNDEFINED_MOTION             = 0xFF,  ///< The undefined motion which don't belong to the above
};

/**
 * @brief define navstate and imu bias structor
 *
 */
struct GTNavStateAndImuBias
{
    GTNavState     navstate;  ///< prediction navstate measurement
    GTConstantBias imu_bias;  ///< prediction imu bias measurement

    /**
     * @brief constructor
     *
     * @param _navstate prediction navstate measurement
     * @param _imu_bias prediction imu bias measurement
     */
    GTNavStateAndImuBias(GTNavState const& _navstate = GTNavState(), GTConstantBias const& _imu_bias = GTConstantBias())
      : navstate(_navstate), imu_bias(_imu_bias)
    {
    }
};  // GTNavStateAndImuBias
using StampedGTNavStateAndImuBias = StampedT<GTNavStateAndImuBias>;

/**
 * @brief This struct defines the basic earth parameters for the WGS-84 reference system
 *
 */
struct Wgs84ReferenceSystemParameters
{
    static Scalar const EQUATORIAL_RADIUS;   ///< Earth equatorial radius. Unit: meter
    static Scalar const EQUATORIAL_GRAVITY;  ///< Earth equatorial gravity. Unit: m/s^2
    static Scalar const STANDARD_GRAVITY;  ///< Standard gravity, International agreement: gravitational acceleration at
                                           ///< sea level at latitude 45 degrees. Unit: m/s^2
};

/**
 * @brief FusionState which includes new optimized navstate, imu bias and smoother
 */
struct FusionState
{
    std::vector<StampedGTNavStateAndImuBias> multi_stamped_gt_navstate_and_imu_bias;  ///< new optimized navstate and
                                                                                      ///< imu bias
    std::shared_ptr<GTIncrementalFixedLagSmoother> smoother_ptr;                      ///< smoother for optimziation
    CoordinateType                                 parent_coordinate;  ///< parent coordinate of fusion navstate
    Timestamp old_gnss_pvt_timestamp;  ///< timestamp of last gnss pvt which has been used in optimziation

    /// measurements for other modules
    std::vector<StampedAdvancedNavstateType> multi_stamped_advanced_navstate;  ///< optimzied navstate and bias with
                                                                               ///< covariance in holo type
    std::vector<StampedT<GTPreintegratedImuMeasurements>> multi_stamped_pim;   ///< new pim measurements
    std::vector<StampedCombinedVelocityMeasurement>       multi_stamped_cvm;   ///< multi combined velocity
                                                                               ///< measurement
    StampedT<Scalar> stampted_local_gravity =
        StampedT<Scalar>(Timestamp(),
                         Wgs84ReferenceSystemParameters::STANDARD_GRAVITY);  ///< The stamped local gravity based on the
                                                                             ///< position, Unit: m/s^2

    /**
     * @brief constructor
     */
    FusionState() : smoother_ptr(nullptr)
    {
    }

    /**
     * @brief check whether the state is initialized
     *
     * @return bool_t true -> initialized, false -> not initialized
     */
    bool_t IsInitialized() const
    {
        return smoother_ptr && multi_stamped_gt_navstate_and_imu_bias.size() > 0u &&
               multi_stamped_advanced_navstate.size() > 0u;
    }

    /**
     * @brief clear internal state
     */
    void Reset()
    {
        smoother_ptr = nullptr;
        multi_stamped_gt_navstate_and_imu_bias.clear();
        multi_stamped_advanced_navstate.clear();
    }
};

/**
 * @brief this enum used to list error code which might be check in fusion and dr
 */
enum class ErrorCode : uint8_t
{
    ALLGOOD                                        = 0u,   ///< all good
    NO_GNSS                                        = 1u,   ///< no gnss message comming
    GNSS_SLIGHTLY_DELAY                            = 2u,   ///< gnss message is slightly delayed
    GNSS_SERIOUSLY_DELAY                           = 3u,   ///< gnss message is seriously delayed
    GNSS_SERIOUSLY_FRAME_DROPPING                  = 4u,   ///< gnss message is seriously lost
    NO_IMU                                         = 5u,   ///< no imu message comming
    IMU_SLIGHTLY_DELAY                             = 6u,   ///< imu message is slightly delayed
    IMU_SERIOUSLY_DELAY                            = 7u,   ///< imu message is seriously delayed
    IMU_SERIOUSLY_FRAME_DROPPING                   = 8u,   ///< imu message is seriously lost
    NO_CHASSIS_STATE                               = 9u,   ///< no chassis state message comming
    CHASSIS_STATE_SLIGHTLY_DELAY                   = 10u,  ///< chassis state message is slightly delayed
    CHASSIS_STATE_SERIOUSLY_DELAY                  = 11u,  ///< chassis state message is seriously delayed
    CHASSIS_STATE_SERIOUSLY_FRAME_DROPPING         = 12u,  ///< chassis state message is seriously lost
    NO_CAMERA_LANE_BOUNDARIES                      = 13u,  ///< no CameraLaneBoundaries message comming
    CAMERA_LANE_BOUNDARIES_SLIGHTLY_DELAY          = 14u,  ///< CameraLaneBoundaries message is slightly delayed
    CAMERA_LANE_BOUNDARIES_SERIOUSLY_DELAY         = 15u,  ///< CameraLaneBoundaries message is seriously delayed
    CAMERA_LANE_BOUNDARIES_SERIOUSLY_FRAME_DROPPING= 16u,  ///< CameraLaneBoundaries message is seriously lost
    NO_INTEGRATED_NAVIGATION                       = 17u,  ///< no integrated navigation message comming
    INTEGRATED_NAVIGATION_SLIGHTLY_DELAY           = 18u,  ///< integrated navigation message is slightly delayed
    INTEGRATED_NAVIGATION_SERIOUSLY_DELAY          = 19u,  ///< integrated navigation message is seriously delayed
    INTEGRATED_NAVIGATION_SERIOUSLY_FRAME_DROPPING = 20u,  ///< integrated navigation message is seriously lost

    FUSION_NOT_INITIALIZED         = 50u,  ///< fusion is not initialized
    MAP_SERVICE_CONNECTION_FAILURE = 51u,  ///< map service connection failed
    MAP_DATA_UNAVALIABLE           = 52u,  ///< map data is unavaliable
    INVALID_INITIAL_LANE           = 53u,  ///< initial lane is not successfully determined
    NO_LANE_CORRESPONDENCES        = 54u,  ///< no lane correspondences is created
    FUSION_TRAJECTORY_JUMPING      = 55u,  ///< fusion trajectory jumping occurs
    FUSION_EXCEPTION               = 56u,  ///< exception occurs in fusion
    FUSION_ZONE_CHANGING           = 57u,  ///< utm zone changing occrus
    EGO_LANE_DETERMINER_ERROR      = 58u,  ///< ego lane determiner error

    DR_NOT_INITIALIZED      = 100u,  ///< DR is not initialized
    DR_CHANGE_TO_INTEGRATOR = 101u,  ///< DR changes to integrator mode
    DR_CHANGE_TO_ESTIMATOR  = 102u,  ///< DR changes to estimator mode
    DR_EXCEPTION            = 103u,  ///< exception occurs in DR
    DR_TRAJECTORY_JUMPING   = 104u,  ///< DR trajectory jumping occurs

    KEYPOINT_DATA_UNAVALIABLE          = 150u,  ///< vision keypoint data is unavaliable
    NO_VISUAL_SEMANTIC_CORRESPONDENCES = 151u,  ///< no visual semantic correspondences is created

};  // ErrorCode

/**
 * @brief The coefficients for the vehicle velocity correction.
 * @details It includes a scale coefficient and a bias coefficient. The correction formula is:
 *          corrected_value = scalar * raw_value + bias
 */
struct VehicleVelocityCorrectionCoefficients
{
    Scalar scale = 1.0;
    Scalar bias  = 0.0;  ///< Unit: m/s

    /**
     * @brief Constructor
     *
     * @param[in] _scale The scale value
     * @param[in] _bias The bias value
     */
    VehicleVelocityCorrectionCoefficients(Scalar const _scale = 1.0, Scalar const _bias = 0.0)
      : scale(_scale), bias(_bias)
    {
    }

    /**
     * @brief Static method to load coefficient from the yaml node.
     *
     * @param[in] node The yaml node.
     * @return The loaded coefficient
     */
    static VehicleVelocityCorrectionCoefficients LoadFromYaml(holo::yaml::Node const& node);

    /**
     * @brief Static method to save coefficient to the yaml node.
     *
     * @param[in] coefficient The saved coefficient.
     * @param[in] node The yaml node
     * @return It returns true if saving successfully. Otherwise, it returns false.
     */
    static bool_t SaveToYaml(VehicleVelocityCorrectionCoefficients const& coefficient, holo::yaml::Node& node);

    /**
     * @brief Static method to load from file.
     * @note The file must be a yaml file.
     *
     * @param[in] file_directory The file directory to be loaded.
     * @param[out] coefficients The loaded correction coefficients.
     * @return It returns true if we load successfully. Otherwise, it returns false.
     */
    static bool_t LoadFromFile(std::string const& file_directory, VehicleVelocityCorrectionCoefficients& coefficients);

    /**
     * @brief Static method to save correction coefficients to the target yaml file.
     *
     * @param[in] file_directory The target file directory.
     * @param[in] coefficients
     * @return bool_t
     */
    static bool_t SaveToFile(std::string const&                           file_directory,
                             VehicleVelocityCorrectionCoefficients const& coefficients);

    /**
     * @brief The operator overloading for <<.
     *
     * @param[in] os The ostream
     * @param[in] coefficients The vehicle velocity coefficients.
     * @return std::ostream&
     */
    friend std::ostream& operator<<(std::ostream& os, VehicleVelocityCorrectionCoefficients const& coefficients)
    {
        os << "Scale: " << coefficients.scale << ", Bias: " << coefficients.bias << "\n"
           << "It means: corrected_vel = raw_vel * " << coefficients.scale << " + " << coefficients.bias << std::endl;
        return os;
    }
};  /// VehicleVelocityCorrectionCoefficients

/**
 * @}
 *
 */
}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_COMMON_TYPES_H_
