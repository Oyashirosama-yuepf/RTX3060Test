/*
 * Copyright (C) HoloMatic Technology (Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file imu_extrinsic_calibration.h
 * @brief class for eol(end of line) imu extrinsic calibration
 * @author bin.chen @ chenbin@holomatic.com
 * @date 2021-08-30
 */

#ifndef HOLO_CALIBRATION_IMU_IMU_EXTRINSIC_CALIBRATION_H_
#define HOLO_CALIBRATION_IMU_IMU_EXTRINSIC_CALIBRATION_H_

#include <atomic>
#include <string>

#include <holo/common/extrinsic.h>
#include <holo/common/imu.h>
#include <holo/core/exception.h>
#include <holo/core/types.h>
#include <holo/geometry/pose3.h>

namespace holo
{
namespace calibration
{
namespace imu
{

/**
 * @addtogroup imu
 * @{
 *
 */

/**
 * @brief A class aims at calibrating the extrinsic(rotation and translation) parameters between 
 *  imu(child_coordinate) and body(parent_coordinate) in vehicle production line
 *
 * @details program works in the stationary state of the vehicle, so the extrinsic parameters 
 *  <translation_x, translation_y, translation_z and rotation_yaw> is the \b unobservable dof of this
 *  calibration algorithm, you have to manually specify these parameters
 */

class ImuExtrinsicCalibration
{
public:
    /**
     * @brief typedefs
     */
    using Scalar      = holo::float64_t;
    using Vector3     = holo::numerics::Vector3T<Scalar>;
    using Point3      = holo::geometry::Point3T<Scalar>;
    using Rot3        = holo::geometry::Rot3T<Scalar>;
    using Pose3       = holo::geometry::Pose3T<Scalar>;
    using Quaternion  = holo::geometry::QuaternionT<Scalar>;
    using Extrinsic   = holo::common::ExtrinsicT<holo::float32_t>;
    using Imu         = holo::common::ImuT<Scalar>;
    using bool_t      = holo::bool_t;
    using EpsilonType = holo::EpsilonT<Scalar>;
    using Coordinate  = holo::common::Coordinate;

    /**
     * @brief this enum defines error codes for different calibration result
     */
    enum class Status : uint8_t
    {
        CALIBRATION_SUCCESS           = 0u,   ///< calibration success
        NO_IMU_DATA                   = 1u,   ///< there is no imu data
        ABNORMAL_IMU_FREQUENCY        = 2u,   ///< the frequency of the IMU is abnormal
        LARAGE_ACCELEROMETER_VARIANCE = 4u,   ///< the variance of the accelerometer is too large
        EXTRINSIC_FILE_WRITE_FAILED   = 5u,   ///< failed to write extrinsic file

    };  // Status

    /**
     * @brief This struct save the vehicle's measurement parameters
     */
    struct VehicleParameters
    {
        Scalar front_left_wheel_trim_height;   ///< height of front left wheel trim [unit: m]
        Scalar front_right_wheel_trim_height;  ///< height of front right wheel trim [unit: m]
        Scalar rear_left_wheel_trim_height;    ///< height of rear left wheel trim [unit: m]
        Scalar rear_right_wheel_trim_height;   ///< height of rear right wheel trim [unit: m]
        Scalar wheel_base;                     ///< length of wheel base [unit: m]
        Scalar axle_length;                    ///< length of axle length [unit: m]
        Scalar extrinsic_yaw;                  ///< exrinsic parameters yaw between imu and body [unit: rad]
        Scalar extrinsic_x;                    ///< exrinsic translation x between imu and body [unit: m]
        Scalar extrinsic_y;                    ///< exrinsic translation y between imu and body [unit: m]
        Scalar extrinsic_z;                    ///< exrinsic translation z between imu and body [unit: m]

    }; // VehicleParameters

    /**
    * @brief This struct is used to save the parameters for computing the IMU-Body extrinsic parameters.
    * 
    * @details refer to the calibration manual for detailed coordinate system definitions
    */
    struct Parameters
    {
        /**
         * @brief Vehicle's measurement parameters
         */
        VehicleParameters vehicle_params;

        /**
         * @brief Imu frequency. Unit: Hz
         */
        Scalar expected_imu_frequency = Scalar(100.0);

        /**
         * @brief Maximum difference between the expected frequency and the actual frequency of IMU data
         */
        Scalar max_diff_imu_frequency = Scalar(2.0);

        /**
         * @brief The allowed maximum sample variance of imu data acquisition for calibration.  Unit: m/s^2
         */
        Scalar max_imu_data_variance = Scalar(0.03);

        /**
         * @brief The path where the calibration result will be stored
         */
        std::string output_extrinsic_file_path;

    }; // Parameters
    
    /**
     * @brief Construct a new ImuExtrinsicCalibration object
     * 
     * @param param the ImuExtrinsicCalibration parameters
     * @param is_start_imu_calibration_ flag which used to switch online/offline calibration modes
     */
    ImuExtrinsicCalibration(Parameters const& param) : parameters_(param)
    {
    }

    /**
     * @brief Destroy the ImuExtrinsicCalibration object
     */
    ~ImuExtrinsicCalibration() noexcept
    {
    }

    /**
     * @brief Main process about imu extrinsic calibration 
     *
     * @param[in] imu_datas input imu datas which required by imu extrinsic calibration 
     * @return status of calibration result 
     */
    Status Run(std::vector<Imu> const& imu_datas) const;

protected:
    /**
     * @brief Compute the angle between the two vectors
     *
     * @details implement using vector's dot product
     * @param v1 vector 1
     * @param v2 vector 2
     * 
     * @return angle between these vectors
     */
    Scalar computeAngleBetweenTwoVectors(Vector3 const& v1, Vector3 const& v2) const;

    /**
     * @brief Compute rotation between two frames with the same vector represented in these frames
     *
     * @details v2 = R * v1
     * @param v1 vector in first frame
     * @param v2 vector in second frame
     * 
     * @return Rot3
     */
    Rot3 computeRotationBetweenTwoVectors(Vector3 const& v1, Vector3 const& v2) const;

    /**
     * @brief Compute the normal vector of the plane from three points
     *
     * @details three points in space define a plane
     * @param pt_1 point 1
     * @param pt_2 point 2
     * @param pt_3 point 3
     * 
     * @throw three points are collinear
     * @return normal vector of this plane which determined by these points
     */
    Vector3 computePlaneNormalFromThreePoints(Point3 const& pt_1, Point3 const& pt_2, Point3 const& pt_3) const;

private:
    /**
     * @brief Calibration parameters
     */
    Parameters parameters_;

}; // ImuExtrinsicCalibration

/**
 * @}
 *
 */

} // namespace imu
} // namespace calibration
} // namespace holo


#endif // HOLO_CALIBRATION_EOL_IMU_EXTRINSIC_CALIBRATION_H_