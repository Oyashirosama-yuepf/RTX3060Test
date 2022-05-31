/*!
 * @file measurement_appendix.h
 * @brief This header file define appendix of several measurements.
 * @author lichao@holomatic.com
 * @date Aug 24, 2019
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *  notice.
 */

#ifndef HOLO_C_COMMON_MEASUREMENT_APPENDIX_H_
#define HOLO_C_COMMON_MEASUREMENT_APPENDIX_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief define odometry status types
 *
 */
enum OdometryStatus
{
    ODOMETRY_STATUS_ALLGOOD                    = 0x0000, /* solution is good */
    ODOMETRY_STATUS_SOLUTIONNOGOOD             = 0x0001, /* solution is bad */
    ODOMETRY_STATUS_POSITIONINACTIVE           = 0x0002, /* position field of solution is inactive */
    ODOMETRY_STATUS_ORIENTATIONINACTIVE        = 0x0004, /* orientation field of solution is inactive */
    ODOMETRY_STATUS_LINEARVELOCITYINACTIVE     = 0x0008, /* linear velocity field of solution is inactive */
    ODOMETRY_STATUS_ANGULARVELOCITYINACTIVE    = 0x0010, /* angular velocity field of solution is inactive */
    ODOMETRY_STATUS_LINEARACCELERATIONINACTIVE = 0x0020, /* linear acceleration field of solution is inactive */
};

/**
 * @brief define odometry source types
 *
 */
enum OdometrySource
{
    ODOMETRY_SOURCE_GNSS          = 0x0001, /* from Global Navigation Staellite System (GNSS) */
    ODOMETRY_SOURCE_IMU           = 0x0002, /* from Inertial Measurement Unit (IMU) */
    ODOMETRY_SOURCE_VISION        = 0x0004, /* from camera */
    ODOMETRY_SOURCE_WHEEL         = 0x0008, /* from vehicle wheel speed sensor */
    ODOMETRY_SOURCE_RADAR         = 0x0010, /* from Radar */
    ODOMETRY_SOURCE_LIDAR         = 0x0020, /* from LiDAR */
    ODOMETRY_SOURCE_SEMANTIC      = 0x0040, /* from semantic measurement which provided by Machine Learning*/
    ODOMETRY_SOURCE_HD_MAP        = 0x0080, /* from High Definition Map (HD Map) */
    ODOMETRY_SOURCE_RTK           = 0x0080, /* from RTK Base Station */
    ODOMETRY_SOURCE_DETECTED_LANE = 0x0100, /* from detected lanes which provided by Smart Camera */
    ODOMETRY_SOURCE_UNKNOWN       = 0xFFFF, /* from undefined source */
};

/**
 * @brief define position status types
 *
 */
enum GnssPositionStatus
{
    GNSS_POSITION_STATUS_ALLGOOD          = 0x0000, /* solution is good */
    GNSS_POSITION_STATUS_INSUFFICIENT_OBS = 0x0001, /* insufficient number of observations of the satellite */
    GNSS_POSITION_STATUS_UNSTABLE         = 0x0002, /* including high variance, singular solution, no convergence */
    GNSS_POSITION_STATUS_BAD              = 0x0004, /* solution is bad */
    GNSS_POSITION_STATUS_UNDEFINEDERROR   = 0xFFFF, /* undefined error */
};

/**
 * @brief define imu status types
 *
 */
enum ImuStatus
{
    IMU_STATUS_ALLGOOD        = 0x0000, /* status is good */
    IMU_STATUS_GYROXERROR     = 0x0001, /* x axis of gyroscope is bad */
    IMU_STATUS_GYROYERROR     = 0x0002, /* y axis of gyroscope is bad */
    IMU_STATUS_GYROZERROR     = 0x0004, /* z axis of gyroscope is bad */
    IMU_STATUS_ACCLXERROR     = 0x0008, /* x axis of accelerometer is bad */
    IMU_STATUS_ACCLYERROR     = 0x0010, /* y axis of accelerometer is bad */
    IMU_STATUS_ACCLZERROR     = 0x0020, /* z axis of accelerometer is bad */
    IMU_STATUS_UNDEFINEDERROR = 0xFFFF, /* undefined error */
};

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_MEASUREMENT_APPENDIX_H_
