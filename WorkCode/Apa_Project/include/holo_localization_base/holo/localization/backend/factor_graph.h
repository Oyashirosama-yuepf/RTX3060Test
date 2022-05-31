/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file FactorGraph.h
 * @author lichao (lichao@holomatic.com)
 * @brief define factor graph for nonlinear optimization
 * @date 2019-12-04
 */

#ifndef HOLO_LOCALIZATION_BACKEND_FACTOR_GRAPH_H_
#define HOLO_LOCALIZATION_BACKEND_FACTOR_GRAPH_H_

#include <holo/common/optional.h>
#include <holo/localization/common/imu_preintegration.h>
#include <holo/localization/common/types.h>
#include <holo/localization/common/wheel_preintegration.h>

namespace holo
{
namespace localization
{
/**
 * @addtogroup backend
 * @{
 *
 */

/**
 * @brief Enumerate factor type
 *
 */
enum class FactorType
{
    PRIOR_POSE = 0,  ///< Prior Pose Factor which use prior informantion to constraint on Pose3.
                     ///< Symbol order: (pose_key)
    PRIOR_VEL = 1,   ///< Prior Velocity Factor which use prior informantion to constraint on Velocity3. Symbol
                     ///< order: (velocity_key)
    PRIOR_IMUBIAS =
        2,  ///< Prior ImuBias Factor which use prior informantion to constraint on ImuBias. Symbol order: (imubias_key)
    GNSS =
        3,  ///< Gnss Factor which use gnss measurement to constraint on Position3, Velocity3. Symbol order: (pose_key)
    IMU = 4,  ///< Imu Factor which use imu preintegrated measurement to constraint on two Navstates and first imu bias.
              ///< Symbol order: (pose_key1, velocity_key1, pose_key2, velocity_key2, imubias_key1)
    IMUBIAS = 5,      ///< Imu bias factor which use imu bias difference to constaint on two ImuBiases. Symbol order:
                      ///< (imubias_key1, imubias_key2)
    REL_POSE = 6,     ///< Relative pose factor which use pose difference to constraint on two Pose3. Symbol order:
                      ///< (pose_key1, pose_key2)
    REL_VEL = 7,      ///< Relative velocity factor which use velocity difference to constraint on two Velocity3. Symbol
                      ///< order: (velocity_key1, velocity_key2)
    LANE       = 8,   ///< Lane factor which use lane correspondence to constraint on Pose3. Symbol order: (pose_key)
    SIGN       = 9,   ///< Sign factor which use sign correspondence to constraint on Pose3. Symbol order: (pose_key)
    PROJECTION = 10,  ///< Projection factor which use feature correspondence to constraint on Pose3 and Landmark
                      ///< Position3. Symbol order: (pose_key, landmark_key)
    VELOCITY = 11,    ///< Velocity factor which use vehicle speed to constraint on Pose3 and Velocity3. Symbol order:
                      ///< (pose_key, velocity_key)
    RADAR = 12,  ///< Radar factor which use radar-map correspondence to constraint on Pose3. Symbol order: (pose_key)
    PRIOR_VECTOR3 =
        13,  ///< Prior Vector3 Factor which use prior information to constraint on a variable represented
             ///< by Vector3. e.g. using Vector3(roll, pitch, yaw) to represent euler angle in the
             ///< optimization, PRIOR_VECTOR3 can provide prior knowledge for this variable. Symbol order: (vector3_key)
    CAMERA_IMU_EXTRINSIC = 14,  ///< Camera imu extrinsic calibration factor which use 3d-2d correspondence to
                                ///< constraint on Pose3, Velocity3, roll, pitch, yaw and translation of extrinsic
                                ///< camera in imu frame. Symbol order: (wTi_key, ptw_key, rpy_key, itc_key)
    WHEEL_SPEED = 15,           ///< Wheel Speed factor which use wheel speed to constraint on two Pose3. Symbol order:
                                ///< (pose_key1, pose_key2)
    IMU_BODY_EXTRINSIC = 16,    ///< imu body extrinsic calibration factor
    PRIOR_ROT3         = 17,
    PROJECTION_LINE    = 18,      ///< projection line factor which use 3d-2d correspondence of lane
                                  ///< feature to constraint on Pose3, Symbol order: (pose_key)
    GNSS_POSITION_VELOCITY = 19,  ///< gnss position and velocity factor, Symbol order: (pose_key, velocity_key)
    PRIOR_RPY = 20,  ///< Prior rpy factor which add constraint for rotaion with measurement is parameterized in
                     ///< roll,pitch,yaw, Symbol order: (pose_key)
    UNKNOWN = 256,   ///< Unknown factor type.

};  // enum FactorType

/**
 * @brief Enumerate value type
 *
 */
enum class ValueType : uint16_t
{
    POSITION3 = 0,    ///< Position3 of landmark or vehicle.
    POSE3     = 1,    ///< Pose3 of vehicle or camera.
    VELOCITY3 = 2,    ///< Velocity3 of vehicle or camera.
    IMUBIAS   = 3,    ///< ImuBias
    VECTOR3   = 4,    ///< Vector3 value
    ROT3      = 5,    ///< Rotation
    UNKNOWN   = 256,  ///< Unknown value type.

};  // enum ValueType

struct Symbol
{
    ValueType value_type = ValueType::UNKNOWN;  ///< the value type which can be Position3, Pose3, ImuBias, etc
    uint64_t  index      = 0u;  ///< the index of value which factor constraints on, it also can be a nano second.

};  // struct Symbol

/**
 * @brief This struct defines prior pose factor structure based on factor graph inference.
 *
 */
struct PriorPoseFactor
{
    uint8_t     arity = 1u;                      ///< the arity of factor.
    FactorType  type  = FactorType::PRIOR_POSE;  ///< the type of factor.
    Symbol      symbol;                          ///< the symbol of value.
    Pose3Type   measurement;                     ///< the measurement of factor.
    Matrix6Type covariance_matrix;               ///< the covariance matrix of measurement. the order is [T_cov, R_cov].
    uint64_t    factor_index;                    ///< the index of factor in factor graph
    Scalar      error = Scalar(0.0);             ///< the residual error

};  // struct PriorPoseFactor

/**
 * @brief This struct defines prior velocity factor structure based on factor graph inference.
 *
 */
struct PriorVelocityFactor
{
    uint8_t     arity = 1u;                     ///< the arity of factor.
    FactorType  type  = FactorType::PRIOR_VEL;  ///< the type of factor.
    Symbol      symbol;                         ///< the symbol of value.
    Vector3Type measurement;                    ///< the measurement of factor.
    Matrix3Type covariance_matrix;              ///< the covariance matrix of measurement
    uint64_t    factor_index;                   ///< the index of factor in factor graph.
    Scalar      error = Scalar(0.0);            ///< the residual error

};  // struct PriorVelocityFactor

/**
 * @brief This struct defines prior imu bias factor structure based on factor graph inference.
 *
 */
struct PriorImuBiasFactor
{
    uint8_t     arity = 1u;                         ///< the arity of factor.
    FactorType  type  = FactorType::PRIOR_IMUBIAS;  ///< the type of factor.
    Symbol      symbol;                             ///< the symbol of value.
    ImuBiasType measurement;                        ///< the measurement of factor.
    Matrix6Type covariance_matrix;                  ///< the covariance matrix of measurement.
                                                    ///< the order is [LinearAccelerationCov, AngularVelocityCov]
    uint64_t factor_index;                          ///< the index of factor in factor graph.
    Scalar   error = Scalar(0.0);                   ///< the residual error

};  // struct PriorImuBiasFactor

/**
 * @brief prior vector3 factor.
 *
 */
struct PriorVector3Factor
{
    uint8_t     arity = 1u;                         ///< the arity of factor.
    FactorType  type  = FactorType::PRIOR_VECTOR3;  ///< the type of factor.
    Symbol      symbol;                             ///< the symbol of value.
    Vector3Type measurement;                        ///< the measurement of factor.
    Matrix3Type covariance_matrix;                  ///< the covariance matrix of measurement.
    uint64_t    factor_index;                       ///< the index of factor in factor graph.
    Scalar      error = Scalar(0.0);                ///< the residual error

};  // struct PriorVector3Factor

/**
 * @brief prior rot3 factor.
 *
 */
struct PriorRot3Factor
{
    uint8_t     arity = 1u;                      ///< the arity of factor.
    FactorType  type  = FactorType::PRIOR_ROT3;  ///< the type of factor.
    Symbol      symbol;                          ///< the symbol of value.
    Rot3Type    measurement;                     ///< the measurement of factor.
    Matrix3Type covariance_matrix;               ///< the covariance matrix of measurement.
    uint64_t    factor_index;                    ///< the index of factor in factor graph.
    Scalar      error = Scalar(0.0);             ///< the residual error

};  // struct PriorRot3Factor

/**
 * @brief This struct defines GNSS factor structure based on factor graph inference.
 *
 */
struct GnssFactor
{
    uint8_t    arity = 1u;                ///< the arity of factor.
    FactorType type  = FactorType::GNSS;  ///< the type of factor.
    Symbol     symbol;                    ///< the symbol of value.
    Point3Type measurement;               ///< the measurement of factor.
                                          ///< The measurement are gnss position in UTM coordinate
    Matrix3Type covariance_matrix;        ///< the covariance matrix of measurement
    uint64_t    factor_index;             ///< the index of factor in factor graph.
    Scalar      error = Scalar(0.0);      ///< the residual error

};  // struct GnssFactor

/**
 * @brief This struct defines prior velocity factor structure based on factor graph inference.
 *
 */
struct ImuFactor
{
    uint8_t                      arity = 2u;               ///< the arity of factor.
    FactorType                   type  = FactorType::IMU;  ///< the type of factor.
    std::vector<Symbol>          symbols;                  ///< the symbol of value.
    ImuPreintegrationMeasurement measurement;              ///< the measurement of factor.
    Matrix99Type                 covariance_matrix;        ///< the covariance matrix of measurement
    uint64_t                     factor_index;             ///< the index of factor in factor graph.
    Scalar                       error = Scalar(0.0);      ///< the residual error

};  // struct ImuFactor

/**
 * @brief This struct defines imu bias factor structure based on factor graph inference.
 *
 */
struct ImuBiasFactor
{
    uint8_t             arity = 2u;                   ///< the arity of factor.
    FactorType          type  = FactorType::IMUBIAS;  ///< the type of factor.
    std::vector<Symbol> symbols;                      ///< the symbol of value.
    ImuBiasType         measurement;                  ///< the measurement of factor.
    Matrix6Type         covariance_matrix;            ///< the covariance matrix of measurement.
                                                      ///< the order is [LinearAccelerationCov, AngularVelocityCov]
    uint64_t factor_index;                            ///< the index of factor in factor graph.
    Scalar   error = Scalar(0.0);                     ///< the residual error

};  // struct ImuBiasFactor

/**
 * @brief This struct defines relative pose factor structure based on factor graph inference.
 *
 */
struct RelativePoseFactor
{
    uint8_t             arity = 2u;                    ///< the arity of factor.
    FactorType          type  = FactorType::REL_POSE;  ///< the type of factor.
    std::vector<Symbol> symbols;                       ///< the symbol of value.
    Pose3Type           measurement;                   ///< the measurement of factor.
    Matrix6Type         covariance_matrix;             ///< the covariance matrix of measurement.
                                                       ///< the order is [T_cov, R_cov].
    uint64_t factor_index;                             ///< the index of factor in factor graph.
    Scalar   error = Scalar(0.0);                      ///< the residual error

};  // struct RelativePoseFactor

/**
 * @brief This struct defines relative velocity factor structure based on factor graph inference.
 *
 */
struct RelativeVelocityFactor
{
    uint8_t             arity = 2u;                   ///< the arity of factor.
    FactorType          type  = FactorType::REL_VEL;  ///< the type of factor.
    std::vector<Symbol> symbols;                      ///< the symbol of value.
    Vector3Type         measurement;                  ///< the measurement of factor.
    Matrix3Type         covariance_matrix;            ///< the covariance matrix of measurement
    uint64_t            factor_index;                 ///< the index of factor in factor graph.
    Scalar              error = Scalar(0.0);          ///< the residual error

};  // struct RelativeVelocityFactor

/**
 * @brief This struct defines lane factor structure based on factor graph inference.
 *
 */
struct LaneFactor
{
    uint8_t             arity = 1u;                ///< the arity of factor.
    FactorType          type  = FactorType::LANE;  ///< the type of factor.
    Symbol              symbol;                    ///< the symbol of value.
    LaneCorrespondences measurement;               ///< the measurement of factor.
    std::vector<Scalar> covariance_matrix;         ///< the covariance matrix of measurement
    uint64_t            factor_index;              ///< the index of factor in factor graph.
    Scalar              error = Scalar(0.0);       ///< the residual error

};  // struct LaneFactor

/**
 * @brief This struct defines sign factor structure based on factor graph inference.
 *
 */
struct SignFactor
{
    /**
     * @brief This struct defines sign measurement.
     *
     */
    struct SignMeasurement
    {
        Pose3Type                                      bTc;       ///< extrinsic pose body_T_camera
        Matrix3Type                                    K;         ///< intrinsic matrix
        std::vector<std::pair<Point2Type, Point3Type>> measured;  ///< measured correspondences
    };

    uint8_t         arity = 1u;                           ///< the arity of factor.
    FactorType      type  = FactorType::SIGN;             ///< the type of factor.
    Symbol          symbol;                               ///< the symbol of value.
    SignMeasurement measurement;                          ///< the measurement of factor.
    Matrix2Type     covariance_matrix;                    ///< the covariance matrix of measurement
    uint64_t        factor_index;                         ///< the index of factor in factor graph.
    Scalar          error                = Scalar(0.0);   ///< the residual error
    bool_t          use_huber_loss       = false;         ///< the switch of use huber loss
    Scalar          huber_loss_threshold = Scalar(10.0);  ///< the threshold of huber loss

};  // struct SignFactor

/**
 * @brief This struct defines projection factor structure based on factor graph inference.
 *
 */
struct ProjectionFactor
{
    /**
     * @brief This struct defines projection measurement based on pinhole model.
     *
     */
    struct ProjectionMeasurement
    {
        Pose3Type   bTc;       ///< extrinsic pose body_T_camera
        Matrix3Type K;         ///< intrinsic matrix
        Point2Type  measured;  ///< measured 2D point

    };  // struct ProjectionMeasurement

    uint8_t               arity = 2u;                      ///< the arity of factor.
    FactorType            type  = FactorType::PROJECTION;  ///< the type of factor.
    std::vector<Symbol>   symbols;                         ///< the symbol of value.
    ProjectionMeasurement measurement;                     ///< the measurement of factor.
    Matrix2Type           covariance_matrix;               ///< the covariance matrix of measurement
    uint64_t              factor_index;                    ///< the index of factor in factor graph.
    Scalar                error = Scalar(0.0);             ///< the residual error

};  // struct ProjectionFactor

/**
 * @brief This struct defines velocity factor structure based on factor graph inference.
 *
 */
struct VelocityFactor
{
    uint8_t             arity = 2u;                    ///< the arity of factor.
    FactorType          type  = FactorType::VELOCITY;  ///< the type of factor.
    std::vector<Symbol> symbols;                       ///< the symbol of value.
    Vector3Type         measurement;                   ///< the measurement of factor.
    Matrix3Type         covariance_matrix;             ///< the covariance matrix of measurement
    uint64_t            factor_index;                  ///< the index of factor in factor graph.
    Scalar              error = Scalar(0.0);           ///< the residual error

};  // struct VelocityFactor

/**
 * @brief This struct defines wheel speed factor structure based on factor graph inference.
 *
 */
struct WheelSpeedFactor
{
    uint8_t                        arity = 2u;                       ///< the arity of factor.
    FactorType                     type  = FactorType::WHEEL_SPEED;  ///< the type of factor.
    std::vector<Symbol>            symbols;                          ///< the symbol of value.
    WheelPreintegrationMeasurement measurement;                      ///< the measurement of factor.
    Matrix3Type                    covariance_matrix;                ///< the covariance matrix of measurement
    uint64_t                       factor_index;                     ///< the index of factor in factor graph.
    Scalar                         error = Scalar(0.0);              ///< the residual error

};  // struct WheelSpeedFactor

/**
 * @brief This struct defines camera imu extrinsic calibration factor based on factor graph inference.
 *
 */
struct CameraImuExtrinsicCalibFactor
{
    /**
     * @brief This struct defines measurement for camera imu extrinsic calibration factor
     *
     */
    struct Measurement
    {
        Matrix3Type K;         ///< intrinsic matrix
        Point2Type  measured;  ///< measured 2D point

    };  // struct Measurement

    uint8_t             arity = 4u;                                ///< the arity of factor.
    FactorType          type  = FactorType::CAMERA_IMU_EXTRINSIC;  ///< the type of factor.
    std::vector<Symbol> symbols;                                   ///< the symbol of value.
    Measurement         measurement;                               ///< the measurement of factor.
    Matrix2Type         covariance_matrix;                         ///< the covariance matrix of measurement.
    uint64_t            factor_index;                              ///< the index of factor in factor graph.
    Scalar              error = Scalar(0.0);                       ///< the residual error

    /**
     * @brief flags to control which parameters will be fixed in this factor
     *
     */
    bool_t fix_wTi;    ///< whether fix pose wTi
    bool_t fix_ptw;    ///< whether fix landmark ptw
    bool_t fix_roll;   ///< whether fix roll of extrinsic camera in imu frame
    bool_t fix_pitch;  ///< whether fix pitch of extrinsic camera in imu frame
    bool_t fix_yaw;    ///< whether fix yaw of extrinsic camera in imu frame
    bool_t fix_itc;    ///< whether fix translation of extrinsic camera in imu frame

};  // struct CameraImuExtrinsicCalibFactor

/**
 * @brief This struct defines projection line factor based on factor graph inference.
 *
 */
struct ProjectedLineFactor
{
    /**
     * @brief This struct defines measurement for smart camera extrinsic calibration factor
     *
     */
    struct Measurement
    {
        Pose3Type               bTc;          ///< extrinsic pose body_T_camera
        Matrix3Type             K;            ///< intrinsic matrix
        std::vector<Point3Type> source_pts;   ///< smart camera interpolated 3D points
        Line2Type               target_line;  ///< holo camera detected lane in image

    };  // struct Measurement

    uint8_t     arity = 1u;                           ///< the arity of factor.
    FactorType  type  = FactorType::PROJECTION_LINE;  ///< the type of factor.
    Symbol      symbol;                               ///< the symbol of value.
    Measurement measurement;                          ///< the measurement of factor.
    Scalar      covariance_matrix;                    ///< the covariance matrix of measurement.
    uint64_t    factor_index;                         ///< the index of factor in factor graph.
    Scalar      error                = Scalar(0.0);   ///< the residual error
    Scalar      huber_loss_threshold = Scalar(-1.0);  ///< the threshold of huber loss

};  // struct ProjectedLineFactor

/**
 * @brief This struct defines imu body extrinsic calibration factor based on factor graph inference.
 *
 */
struct ImuBodyExtrinsicCalibFactor
{
    uint8_t                        arity = 3u;                              ///< the arity of factor.
    FactorType                     type  = FactorType::IMU_BODY_EXTRINSIC;  ///< the type of factor.
    std::vector<Symbol>            symbols;                                 ///< the symbol of value.
    WheelPreintegrationMeasurement measurement;                             ///< the measurement of factor.
    Matrix3Type                    covariance_matrix;                       ///< the covariance matrix of measurement.
    uint64_t                       factor_index;                            ///< the index of factor in factor graph.
    Scalar                         error = Scalar(0.0);                     ///< the residual error

};  // struct CameraImuExtrinsicCalibFactor

/**
 * @brief This struct defines gnss position velocity factor based on factor graph inference.
 *
 */
struct GnssPositionVelocityFactor
{
    uint8_t                                 arity = 2u;                                  ///< the arity of factor.
    FactorType                              type  = FactorType::GNSS_POSITION_VELOCITY;  ///< the type of factor.
    std::vector<Symbol>                     symbols;       ///< the symbol of value in an order of [pose, velocity]
    Point3Type                              position;      ///< the position measurement of factor.
    Vector3Type                             velocity;      ///< the velocity measurement of factor.
    Vector6Type                             sigmas;        ///< the measurement noise
    OptionalT<ImuPreintegrationMeasurement> pim;           ///< pim
    Rot3Type                                wRb;           ///< prior rotation of the optimized pose
    uint64_t                                factor_index;  ///< the index of factor in factor graph.
    Scalar                                  error = Scalar(0.0);  ///< the residual error

};  // struct GnssPositionVelocityFactor

/**
 * @brief This struct defines prior rpy factor base on factor graph inference
 *
 */
struct PriorRPYFactor
{
    uint8_t     arity = 1u;                     ///< the arity of factor.
    FactorType  type  = FactorType::PRIOR_RPY;  ///< the type of factor.
    Symbol      symbol;                         ///< the symbol of the optimized value.
    Vector3Type measurement;                    ///< the measurement of roll, pitch and yaw
    Matrix3Type covariance_matrix;              ///< the covariance matrix of roll, pitch, yaw measurement
    uint64_t    factor_index;                   ///< the index of the factor in factor graph
    Scalar      error = Scalar(0.0);            ///< the residual error of this factor
    bool_t      fix_roll;                       ///< whether fix roll in optimization
    bool_t      fix_pitch;                      ///< whether fix pitch in optimization
    bool_t      fix_yaw;                        ///< whether fix yaw in optimization
};

/**
 * @brief This struct defines pose3 value structure based on factor graph inference. It is a state to be estimated.
 * @todo we should consider to use Index-Timestamp map instead of define timestamp in the value.
 *
 */
struct Pose3Value
{
    Symbol      symbol;             ///< the symbol of value
    Timestamp   timestamp;          ///< the timestamp of value
    Pose3Type   state;              ///< the state value which to be optimized.
    Matrix6Type covariance_matrix;  ///< covariance matrix of pose. the order is [T_cov, R_cov].

};  // struct Pose3Value

/**
 * @brief This struct defines velocity3 value structure based on factor graph inference. It is a state to be estimated.
 * @todo we should consider to use Index-Timestamp map instead of define timestamp in the value.
 *
 */
struct Velocity3Value
{
    Symbol      symbol;             ///< the symbol of value
    Timestamp   timestamp;          ///< the timestamp of value
    Vector3Type state;              ///< the state value which to be optimized.
    Matrix3Type covariance_matrix;  ///< covariance matrix of velocity.

};  // struct Velocity3Value

/**
 * @brief This struct defines imu bias value structure based on factor graph inference. It is a state to be estimated.
 * @todo we should consider to use Index-Timestamp map instead of define timestamp in the value.
 *
 */
struct ImuBiasValue
{
    Symbol      symbol;             ///< the symbol of value
    Timestamp   timestamp;          ///< the timestamp of value
    ImuBiasType state;              ///< the state value which to be optimized.
    Matrix6Type covariance_matrix;  ///< covariance matrix of imu bias. the order is [LinearAcceleeerationCov,
                                    ///< AngularVelocityCov].

};  // struct ImuBiasValue

/**
 * @brief This struct defines position3 value structure based on factor graph inference. It is a state to be estimated.
 * @todo we should consider to use Index-Timestamp map instead of define timestamp in the value.
 *
 */
struct Position3Value
{
    Symbol      symbol;             ///< the symbol of value
    Timestamp   timestamp;          ///< the timestamp of value
    Point3Type  state;              ///< the state value which to be optimized.
    Matrix3Type covariance_matrix;  ///< covariance matrix of position.

};  // struct ImuBiasValue

/**
 * @brief This struct defines vector3 values structure based on factor graph inference. It is a state to be estimated.
 *
 */
struct Vector3Value
{
    Symbol      symbol;             ///< the symbol of value
    Timestamp   timestamp;          ///< the timestamp of value
    Vector3Type state;              ///< the state value which to be optimized
    Matrix3Type covariance_matrix;  ///< the covariance matrix of vector3

};  // struct Vector3Value

/**
 * @brief This struct defines rotation values structure based on factor graph inference. It is a state to be estimated.
 *
 */
struct Rot3Value
{
    Symbol      symbol;             ///< the symbol of value
    Timestamp   timestamp;          ///< the timestamp of value
    Rot3Type    state;              ///< the state value which to be optimized
    Matrix3Type covariance_matrix;  ///< the covariance matrix of Rot3

};  // struct Rot3Value

using PriorPoseFactors               = std::vector<PriorPoseFactor>;
using PriorVelocityFactors           = std::vector<PriorVelocityFactor>;
using PriorImuBiasFactors            = std::vector<PriorImuBiasFactor>;
using PriorVector3Factors            = std::vector<PriorVector3Factor>;
using PriorRot3Factors               = std::vector<PriorRot3Factor>;
using GnssFactors                    = std::vector<GnssFactor>;
using ImuFactors                     = std::vector<ImuFactor>;
using ImuBiasFactors                 = std::vector<ImuBiasFactor>;
using RelativePoseFactors            = std::vector<RelativePoseFactor>;
using RelativeVelocityFactors        = std::vector<RelativeVelocityFactor>;
using LaneFactors                    = std::vector<LaneFactor>;
using SignFactors                    = std::vector<SignFactor>;
using ProjectionFactors              = std::vector<ProjectionFactor>;
using VelocityFactors                = std::vector<VelocityFactor>;
using WheelSpeedFactors              = std::vector<WheelSpeedFactor>;
using CameraImuExtrinsicCalibFactors = std::vector<CameraImuExtrinsicCalibFactor>;
using ProjectedLineFactors           = std::vector<ProjectedLineFactor>;
using ImuBodyExtrinsicCalibFactors   = std::vector<ImuBodyExtrinsicCalibFactor>;
using GnssPositionVelocityFactors    = std::vector<GnssPositionVelocityFactor>;
using PriorRPYFactors                = std::vector<PriorRPYFactor>;

using Pose3Values     = std::vector<Pose3Value>;
using Velocity3Values = std::vector<Velocity3Value>;
using ImuBiasValues   = std::vector<ImuBiasValue>;
using Position3Values = std::vector<Position3Value>;
using Vector3Values   = std::vector<Vector3Value>;
using Rot3Values      = std::vector<Rot3Value>;

/**
 * @brief This struct defines factor graph model which contains factors, values and other properties.
 *
 */
struct FactorGraph
{
    OptionalT<PriorPoseFactors>        prior_pose_factors;      ///< the optional object of prior pose factor array
    OptionalT<PriorVelocityFactors>    prior_velocity_factors;  ///< the optional object of prior velocity factor array
    OptionalT<PriorImuBiasFactors>     prior_imu_bias_factors;  ///< the optional object of prior imubias factor array
    OptionalT<PriorVector3Factors>     prior_vector3_factors;   ///< the optional object of vector3 factor array
    OptionalT<PriorRot3Factors>        prior_rot3_factors;      ///< the optional object of rot3 factor array
    OptionalT<GnssFactors>             gnss_factors;            ///< the optional object of gnss factor array
    OptionalT<ImuFactors>              imu_factors;             ///< the optional object of imu factor array
    OptionalT<ImuBiasFactors>          imu_bias_factors;        ///< the optional object of imubias factor array
    OptionalT<RelativePoseFactors>     relative_pose_factors;   ///< the optional object of relative pose factor array
    OptionalT<RelativeVelocityFactors> relative_velocity_factors;   ///< the optional object of relative velocity factor
                                                                    ///< array
    OptionalT<LaneFactors>                    lane_factors;         ///< the optional object of lane factor array
    OptionalT<SignFactors>                    sign_factors;         ///< the optional object of sign factor array
    OptionalT<ProjectionFactors>              projection_factors;   ///< the optional object of projection factor array
    OptionalT<VelocityFactors>                velocity_factors;     ///< the optional object of velocity factor array
    OptionalT<WheelSpeedFactors>              wheel_speed_factors;  ///< the optional object of wheel speed factor array
    OptionalT<CameraImuExtrinsicCalibFactors> camera_imu_extrinsic_calib_factors;  ///< the optional object of camera
                                                                                   ///< imu extrinsic calib factor array
    OptionalT<ProjectedLineFactors> projection_line_factors;  ///< the optional object of projection line factor array
    OptionalT<ImuBodyExtrinsicCalibFactors> imu_body_extrinsic_calib_factors;  ///< the optional object of body
                                                                               ///< imu extrinsic calib factor array
    OptionalT<GnssPositionVelocityFactors> gnss_position_velocity_factors;     ///< the optional object of gnss position
                                                                               ///< velocity factor array
    OptionalT<PriorRPYFactors> prior_rpy_factors;  ///< the optional object of prior rpy factor array

    OptionalT<Pose3Values>     pose_values;      ///< the optional object of pose value array
    OptionalT<Velocity3Values> velocity_values;  ///< the optional object of velocity value array
    OptionalT<ImuBiasValues>   imu_bias_values;  ///< the optional object of imubias value array
    OptionalT<Position3Values> position_values;  ///< the optional object of position value array
    OptionalT<Vector3Values>   vector3_values;   ///< the optional object of vector3 value array
    OptionalT<Rot3Values>      rot3_values;      ///< the optional object of rot3 value array

};  // struct FactorGraph

/**
 * @}
 *
 */

}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_BACKEND_FACTOR_GRAPH_H_
