/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file common_functions.h
 * @brief this file defins the common functions used in tightly coupled fusion
 * @author Shuaijie Li(lishuaijie@holomatic.com)
 * @date "2021-02-23"
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_UTILS_COMMON_FUNCTIONS_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_UTILS_COMMON_FUNCTIONS_H_

#include <holo/localization/common/measurements_manager_base.h>
#include <holo/localization/sam/type_converter.h>
#include <holo/localization/tightly_coupled_fusion/common_types.h>
#include <holo/localization/tightly_coupled_fusion/imu_stationary_calibrator.h>
#include <holo/localization/tightly_coupled_fusion/measurements_manager_fusion.h>
#include <holo/localization/tightly_coupled_fusion/utils/yaml_helper.h>

/**
 * @brief specialization MeasurementsManagerBase::interpolateT for StampedCorrectedVehicleVelocity
 *
 */
namespace holo
{
namespace localization
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <>
tightly_coupled_fusion::StampedCorrectedVehicleVelocity
MeasurementsManagerBase::interpolateT<tightly_coupled_fusion::StampedCorrectedVehicleVelocity>(
    tightly_coupled_fusion::StampedCorrectedVehicleVelocity const& left,
    tightly_coupled_fusion::StampedCorrectedVehicleVelocity const& right, common::Timestamp const& stamp);
}  // namespace localization
}  // namespace holo

namespace holo
{
namespace localization
{
namespace tightly_coupled_fusion
{
/**
 * @addtogroup utils
 * @{
 *
 */

/**
 * @brief this class defines some static functions which might be used in serveral modules of tightly coupled fusion
 */

class Utility
{
public:
    using MeasurementsManagerFusionPtr = MeasurementsManagerFusion::Ptr;
    using StampedImuStationaryResult   = ImuStationaryCalibrator::StampedImuStationaryResult;

    /**
     * @brief create GTPreIntegratedImuMeasurements with mid-value integration
     *
     * @param[in] multi_imu the input imu data during the integration interval
     * @param[in] pim_params parameters for GTPreIntegratedImuMeasurements object
     * @param[in] imu_bias the estimated imu bias
     * @return GTPreIntegratedImuMeasurements
     */
    static GTPreintegratedImuMeasurements CreatePIM(std::vector<ImuType> const&                      multi_imu,
                                                    boost::shared_ptr<GTPreintegrationParams> const& pim_params,
                                                    GTConstantBias const&                            imu_bias);

    /**
     * @brief create preintegrated wheel measurements
     *
     * @param[in] multi_corrected_vehicle_velocity the input corrected vehicle velocity data
     * @param[in] pim preintegrated imu measurement whose time interval is aligned with multi_corrected_vehicle_velocity
     * @param[in] pwm_params parameters for preintegrated wheel measurements
     * @param[in] iTb extrinsic between body and imu
     * @return PreintegratedWheelMeasurements
     */
    static PreintegratedWheelMeasurements
    CreatePWM(std::vector<StampedCorrectedVehicleVelocity> const& multi_corrected_vehicle_velocity,
              GTPreintegratedImuMeasurements const& pim, PreintegrationWheelParams const& pwm_params,
              Pose3Type const& iTb = Pose3Type());

    /**
     * @brief get Imu / StampedCorrectedVehicleVelocity which is aligned to the given timestmap
     * @note multi_measurement.front().GetTimestamp() <= *(multi_timestamp.begin())
     *       multi_measurement.back().GetTimestamp() >= *(multi_timestamp.end() -1u)
     *
     * @tparam ContainerType ordered STL container type of timestamp(std::vector<Timestamp>, std::set<Timestamp>)
     * @param[in] multi_measurement the given measurements
     * @param[in] multi_timestamp the given timestamp
     * @return std::vector<std::vector<DataType>> aligned measurements data which is aligned each timestamp pair
     * @throw if the condition in {@note} is not satisfied
     */
    template <typename DataType, typename TimestampContainerType>
    static std::vector<std::vector<DataType>> GetMultiAlignedMeasurement(std::vector<DataType> const& multi_measurement,
                                                                         TimestampContainerType const& multi_timestamp)
    {
        if (multi_measurement.front().GetTimestamp() > *(multi_timestamp.begin()) ||
            multi_measurement.back().GetTimestamp() < *(multi_timestamp.rbegin()))
        {
            std::stringstream ss;
            ss << "Utility --- data timestamp and the given timestamp is not matched!!!"
               << "measurement: left timestamp: " << multi_measurement.front().GetTimestamp().ToNsec()
               << ", right timestmap: " << multi_measurement.back().GetTimestamp().ToNsec()
               << "\n given timestamp: left timestamp: " << multi_timestamp.begin()->ToNsec()
               << ", right timestamp: " << multi_timestamp.rbegin()->ToNsec();
            LOG(ERROR) << ss.str();
            throw std::runtime_error(ss.str());
        }

        std::vector<std::vector<DataType>> result;
        result.reserve(multi_timestamp.size() - 1u);

        typename TimestampContainerType::const_iterator left  = multi_timestamp.begin();
        typename TimestampContainerType::const_iterator right = multi_timestamp.begin();
        right++;
        typename std::vector<DataType>::const_iterator anchor_iter = multi_measurement.begin();
        // move anchor to the first place whose timestamp is not larger than *(multi_timestap.begin())
        while ((anchor_iter + 1u)->GetTimestamp() <= *left)
        {
            anchor_iter++;
        }

        for (; right != multi_timestamp.end(); left++, right++)
        {
            std::vector<DataType> aligned_measurements;

            if (anchor_iter->GetTimestamp() == *left)
            {
                aligned_measurements.push_back(*anchor_iter);
            }
            else
            {
                aligned_measurements.push_back(
                    MeasurementsManagerBase::interpolateT(*anchor_iter, *(anchor_iter + 1u), *left));
            }

            while ((anchor_iter + 1u)->GetTimestamp() < *right)
            {
                aligned_measurements.push_back(*(anchor_iter + 1u));
                anchor_iter++;
            }

            if ((anchor_iter + 1u)->GetTimestamp() == *right)
            {
                aligned_measurements.push_back(*(anchor_iter + 1u));
                anchor_iter++;
            }
            else
            {
                aligned_measurements.push_back(
                    MeasurementsManagerBase::interpolateT(*anchor_iter, *(anchor_iter + 1u), *right));
            }

            result.push_back(aligned_measurements);
        }

        return result;
    }

    /**
     * @brief convert wgs84 coordinate to Utm coordinate
     *
     * @param[in] gnss_pvt gnss pvt measurement
     * @param[in] parent_coordinate parent coordinate of gnss pvt
     * @param[in][out] gnss_position position in UTM coordinate [unit: m]
     * @param[in][out] gnss_velocity velocity in ENU coordinate [unit: m/s]
     * @param[in][out] gnss_sigmas sigmas for position, velocity [unit: m^2, m^2, m^2, m^2/s^2, m^2/s^2, m^2/s^2]
     */
    static void ConvertWgs84ToUtm(GnssPvtType const& gnss_pvt, CoordinateType const& parent_coordinate,
                                  GTPoint3& gnss_position, GTVector3& gnss_velocity, GTVector6& gnss_sigmas);

    /**
     * @brief convert Utm coordinate to wgs84 coordinate
     *
     * @param[in] timestamp timestamp of the created gnss pvt
     * @param[in] gnss_position position in UTM coordinate [unit: m]
     * @param[in] gnss_velocity velocity in ENU coordinate [unit: m/s]
     * @param[in] gnss_position_cov covariance for position [unit: m^2]
     * @param[in] gnss_velocity_cov covariance for velocity [unit: m^2/s^2]
     * @param[in] parent_coordinate UTM coordinate of the position
     * @param[in][out] gnss_pvt gnss pvt measurement
     */
    static void ConvertUtmToWgs84(Timestamp const& timestamp, GTPoint3 const& gnss_position,
                                  GTVector3 const& gnss_velocity, GTVector3 const& gnss_position_cov,
                                  GTVector3 const& gnss_velocity_cov, CoordinateType const& parent_coordinate,
                                  GnssPvtType& gnss_pvt);

    /**
     * @brief Get the Nearest Measurement from the vector sequence
     *
     * @tparam T The vector type
     * @param[in] timestamp The target timestamp
     * @param[in] measurements The measurements vector sequence
     * @param[out] target The iterator of the return value
     * @return It returns true if it can get successfully. Otherwise, it returns false.
     */
    template <typename T>
    static bool_t GetNearestMeasurement(Timestamp const& timestamp, std::vector<T> const& measurements,
                                        typename std::vector<T>::const_iterator& target)
    {
        if (measurements.empty())
        {
            return false;
        }

        /// If the time is not latter than all of elements, get the front of buffer
        if (timestamp <= measurements.front().GetTimestamp())
        {
            target = measurements.begin();
            return true;
        }

        /// If the time is not earlier than all of elements, get the back of buffer
        if (timestamp >= measurements.back().GetTimestamp())
        {
            target = measurements.end() - 1;
            return true;
        }

        /// Get the element which is the first greater than t
        auto r = std::upper_bound(measurements.begin(), measurements.end(), timestamp, StampedTimeCompareT<T>());

        /// Get the element from the nearest one from left and right
        target = std::fabs((timestamp - (r - 1)->GetTimestamp()).ToSec()) <
                         std::fabs((r->GetTimestamp() - timestamp).ToSec()) ?
                     r - 1 :
                     r;

        return true;
    }

    /**
     * @brief load isam2 parameters
     *
     * @param node
     * @return GTISAM2Params
     */
    static GTISAM2Params LoadGTISAM2Parameters(yaml::Node const& node);

    /**
     * @brief load GTPreintegrationParams
     *
     * @param node
     */
    static boost::shared_ptr<GTPreintegrationParams> LoadPIMParameters(yaml::Node const& node);

    /**
     * @brief load imu bias
     *
     * @param node imu bias node
     * @param default_imu_bias default imu bias value
     * @return ImuBiasType It returns imu bias loaded from the node when the node is normal
     *                        returns default imu bias when the node is abnormal
     */
    static ImuBiasType LoadImuBias(yaml::Node const& node, ImuBiasType const& default_imu_bias = ImuBiasType());

    /**
     * @brief check yaml file
     *
     * @param[in] yaml_file yaml file
     * @return bool_t It returns false when:
     *          1. file directory is null
     *          2. the loaded node is empty
     *          Otherwise it returns true
     */
    static bool_t CheckYamlFile(std::string const& yaml_file);

    /**
     * @brief Static method to save imu bias to the yaml node.
     *
     * @param[in] imu_bias The recorded imu bias
     * @param[in] node The yaml node
     * @return bool_t It returns true if saving successfully. Otherwise, it returns false.
     */
    static bool_t SaveImuBias(ImuBiasType const& imu_bias, holo::yaml::Node& node);

    /**
     * @brief format timestmap to make timestamp == Timestamp(timestamp.ToSec())
     *
     * @param[in] timestamp the input timstamp which should be formatted
     * @return Timestamp the formatted timestamp
     */
    static Timestamp FormatTimestmap(Timestamp const& timestamp)
    {
        return Timestamp(timestamp.ToSec());
    }

    /**
     * @brief or operator for enum type
     *
     * @tparam EnumType enum type
     * @tparam UnderlyingType underlying type of EnumType
     * @param[in] lhs left hand side enum variable
     * @param[in] rhs right hand side enum variable
     *
     * @return lhs | rhs
     */
    template <typename EnumType, typename UnderlyingType = typename std::underlying_type<EnumType>::type>
    static EnumType EnumOr(EnumType const lhs, EnumType const rhs)
    {
        return static_cast<EnumType>(static_cast<UnderlyingType>(lhs) | static_cast<UnderlyingType>(rhs));
    }

    /**
     * @brief and operator for enum type
     *
     * @tparam EnumType enum type
     * @tparam UnderlyingType underlying type of EnumType
     * @param[in] lhs left hand side enum variable
     * @param[in] rhs right hand side enum variable
     *
     * @return lhs & rhs
     */
    template <typename EnumType, typename UnderlyingType = typename std::underlying_type<EnumType>::type>
    static EnumType EnumAnd(EnumType const lhs, EnumType const rhs)
    {
        return static_cast<EnumType>(static_cast<UnderlyingType>(lhs) & static_cast<UnderlyingType>(rhs));
    }

    /**
     * @brief Judge whether the navstate is high precision based on the source.
     *
     * @param[in] navstate The navstate
     * @return bool_t It returns true if it is high precision. Otherwise, it returns false.
     */
    static bool_t IsHighPrecisionNavstate(AdvancedNavstate const& navstate);

    /**
     * @brief Set the AdvancedNavstate to low precision
     *
     * @param[in,out] navstate The in-output AdvancedNavstate
     */
    static void SetNavstateLowPrecision(AdvancedNavstate& navstate);

    /**
     * @brief Set the AdvancedNavstate to high precision.
     *
     * @param[in,out] navstate The in-output AdvancedNavstate
     */
    static void SetNavstateHighPrecision(AdvancedNavstate& navstate);

    /**
     * @brief compute the rotation of ${src}'s coordinate in ${tgt}'s coordinate
     * @details ${src} and ${tgt} is the same vector ${v} in different coordinate, and this function will return a
     * rotation tRs, which satisfies tgt = tRs * src
     * @note when ${v} in target coordinate is along z-axis, the yaw of tRs is invalid and the roll and pitch is valid
     *       in other case, there is a invalid freedom along ${v}
     *
     * @param[in] src vector ${v} in source coordinate
     * @param[in] tgt vector ${v} in target coordinate
     *
     * @return rotation of source coordinate in target coordinate
     */
    static Rot3Type ComputeRotationBetweenTwoVector(Vector3Type const& src, Vector3Type const& tgt);

    /**
     * @brief compute angle ([0, PI]) between two vector
     *
     * @param[in] v1 the first vector
     * @param[in] v2 the second vector
     *
     * @return angle between two vector [Unit: rad]
     */
    static Scalar ComputeAngleBetweenTwoVector(Vector3Type const& v1, Vector3Type const& v2);

    /**
     * @brief Convert the yaw angle from the ENU coordinate system to the UTM coordinate system.
     * @details Due to the different definitions of UTM and ENU coordinate systems and the distortion of UTM, the yaw
     * angle is different in the two coordinate systems. We use WGS84 coordinate system as the intermediate conversion
     * to realize the correction of yaw angle
     *
     * @param[in] longitude The longitude of the position (unit: radian)
     * @param[in] latitude The latitude of the position (unit: radian)
     * @param[in] yaw_in_enu The yaw value in the ENU coordiante (unit: radian)
     * @param[in] coordinate The target UTM coordiante. If it is a default value or not a UTM6 type. We will use
     * the current lon/lat to compute the UTM zone as the target coordinate.
     * @param[in] is_simplified_conversion The flag which the conversion is simplified. Default value is true.
     *
     * @return The yaw angle in the UTM coordinate. (unit: radian)
     */
    static Scalar ConvertYawFromEnuToUtm(Scalar const longitude, Scalar const latitude, Scalar const yaw_in_enu,
                                         CoordinateType const coordinate               = CoordinateType(),
                                         bool_t const         is_simplified_conversion = true);

    /**
     * @brief Convert a 2-dimensional vector in the EON plane of the ENU coordinate system to the UTM coordinate system.
     *
     * @param[in] longitude The longitude of the position (unit: radian)
     * @param[in] latitude The latitude of the position (unit: radian)
     * @param[in] vector2_in_enu 2-dimensional vector in the ENU coordinate system (unit: meter)
     * @param[in] coordinate The target UTM coordiante. If it is a default value or not a UTM6 type. We will use
     * the current lon/lat to compute the UTM zone as the target coordinate.
     * @param is_simplified_conversion The flag which the conversion is simplified. Default value is true.
     *
     * @return 2-dimensional vector in the UTM coordinate. (unit: meter)
     */
    static Vector2Type ConvertVector2FromEnuToUtm(Scalar const longitude, Scalar const latitude,
                                                  Vector2Type const    vector2_in_enu,
                                                  CoordinateType const coordinate               = CoordinateType(),
                                                  bool_t const         is_simplified_conversion = true);

    /**
     * @brief Convert the yaw angle from the UTM coordinate system to the ENU coordinate system.
     * @details Due to the different definitions of UTM and ENU coordinate systems and the distortion of UTM, the yaw
     * angle is different in the two coordinate systems. We use WGS84 coordinate system as the intermediate conversion
     * to realize the correction of yaw angle
     *
     * @param[in] longitude The longitude of the position (unit: radian)
     * @param[in] latitude The latitude of the position (unit: radian)
     * @param[in] yaw_in_utm The yaw value in the UTM coordiante (unit: radian)
     * @param[in] coordinate The UTM coordiante. If it is a default value or not a UTM6 type. We will use
     * the current lon/lat to compute the UTM zone as the UTM coordinate.
     * @param[in] is_simplified_conversion The flag which the conversion is simplified. Default value is true.
     *
     * @return The yaw angle in the ENU coordinate. (unit: radian)
     */
    static Scalar ConvertYawFromUtmToEnu(Scalar const longitude, Scalar const latitude, Scalar const yaw_in_utm,
                                         CoordinateType const coordinate               = CoordinateType(),
                                         bool_t const         is_simplified_conversion = true);

    /**
     * @brief Convert a 2-dimensional vector in the UTM coordinate system to the EON plane of the ENU coordinate system.
     *
     * @param[in] longitude The longitude of the position (unit: radian)
     * @param[in] latitude The latitude of the position (unit: radian)
     * @param[in] vector2_in_utm 2-dimensional vector in the ENU coordinate system (unit: meter)
     * @param[in] coordinate The UTM coordiante. If it is a default value or not a UTM6 type. We will use
     * the current lon/lat to compute the UTM zone as the target coordinate.
     * @param is_simplified_conversion The flag which the conversion is simplified. Default value is true.
     *
     * @return 2-dimensional vector in the ENU coordinate. (unit: meter)
     */
    static Vector2Type ConvertVector2FromUtmToEnu(Scalar const longitude, Scalar const latitude,
                                                  Vector2Type const    vector2_in_utm,
                                                  CoordinateType const coordinate               = CoordinateType(),
                                                  bool_t const         is_simplified_conversion = true);

    /**
     * @brief Calculate the Local gravity value based on the input position.
     * @details This function supports UTM position and WGS84 position, depending on the given coordinate. If coordinate
     * is neither UTM nor WGS84, we return the standard gravity.
     * The calculation method refers to this web page: https://www.isobudgets.com/how-to-calculate-local-gravity/
     *
     * @param[in] coordinate The coordinate type. Its type should be WGS84 or UTM.
     * @param[in] position The position for gravity calculation. [x,y,z] in UTM or [longitude, latitude, height] in
     * WGS84. Unit: meter(UTM) or [degree, degree, meter] (WGS84).
     * @return The local gravity. Unit: m/s^2.
     */
    static Scalar CalculateLocalGravity(CoordinateType const& coordinate, Point3Type const& position);

    /**
     * @brief Revise angular velocity bias of navstate.
     *
     * @tparam T The navstate type
     * @param[in] imu_result Imu stationary data used to revise the  angular velocity bias of navstate.
     * @param[in, out] state The navstate  which angular velocity bias will be calibrated.
     *
     * @return It is true if calibrated angular velocity bias. Otherwise, it is false.
     */
    template <typename T>
    static void ReviseNavstateImuBias(StampedImuStationaryResult const& imu_result, T& state);

    /**
     * @brief Correct angular velocity bias of navstate  using imu stationary results.
     *
     * @tparam T The navstate  type
     * @param[in] mmf Measurements manager pointer.
     * @param[in] max_time_gap The max time gap between navstate  and imu stationary data. Unit: second.
     * @param[in, out] state The navstate  which angular velocity bias will be calibrated.
     *
     * @return It is true if calibrated angular velocity bias. Otherwise, it is false.
     */
    template <typename T>
    static bool_t UpdateNavstateAngularVelocityBias(MeasurementsManagerFusionPtr const& mmf, Scalar const max_time_gap,
                                                    T& state)
    {
        /// Try  to get  imu stationary result and check timestamp gap.
        StampedImuStationaryResult latest_imu_result;

        if (mmf->GetLatestMeasurement(latest_imu_result) &&
            (std::fabs((state.GetTimestamp() - latest_imu_result.GetTimestamp()).ToSec()) < max_time_gap))
        {
            ReviseNavstateImuBias<T>(latest_imu_result, state);
            return true;
        }
        return false;
    }

};  // Utility

/**
 * @}
 *
 */

}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_UTILS_COMMON_FUNCTIONS_H_
