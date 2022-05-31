/*!
 * \brief visual based slam common types header file
 * \author Feng. Li, lifeng@holomatic.com
 * \date Feb-11-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_COMMON_TYPES_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_COMMON_TYPES_H_

#include <gtsam/geometry/EssentialMatrix.h>
#include <gtsam/geometry/OrientedPlane3.h>
#include <gtsam/geometry/Point2.h>
#include <gtsam/geometry/Point3.h>
#include <gtsam/geometry/Pose2.h>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/inference/Symbol.h>
#include <gtsam/navigation/AHRSFactor.h>
#include <gtsam/navigation/GPSFactor.h>
#include <gtsam/navigation/ImuFactor.h>
#include <gtsam/nonlinear/NonlinearEquality.h>
#include <gtsam/nonlinear/Values.h>
#include <gtsam/slam/BetweenFactor.h>
#include <gtsam/slam/PriorFactor.h>
#include <gtsam/slam/ProjectionFactor.h>
#include <gtsam_unstable/slam/InvDepthFactor3.h>
#include <gtsam_unstable/slam/InvDepthFactorVariant3.h>
#include <holo/3d/common/point_cloud.h>
#include <holo/common/chassis_state.h>
#include <holo/common/coordinate.h>
#include <holo/common/details/intrinsic.h>
#include <holo/common/extrinsic.h>
#include <holo/common/gnss_position.h>
#include <holo/common/image.h>
#include <holo/common/imu.h>
#include <holo/common/imu_bias.h>
#include <holo/common/odometry.h>
#include <holo/common/parking_slot.h>
#include <holo/core/epsilon.h>
#include <holo/core/exception.h>
#include <holo/core/types.h>
#include <holo/geometry/box2.h>
#include <holo/geometry/point2.h>
#include <holo/geometry/point3.h>
#include <holo/geometry/pose3.h>
#include <holo/geometry/quaternion.h>
#include <holo/geometry/rot2.h>
#include <holo/geometry/rot3.h>
#include <holo/io/common/intrinsic.h>
#include <holo/io/io.h>
#include <holo/localization/common/navstate.h>
#include <holo/localization/sam/vision/line/orthonormal_line.h>
#include <holo/localization/sam/vision/line/plucker_line.h>
#include <holo/localization/tools/source_checker.h>
#include <holo/localization/vision/common/holo_gtsam.h>
#include <holo/localization/vision/common/image_undistorter.h>
#include <holo/localization/vision/feature/fast.h>
#include <holo/localization/vision/feature/gridding_feature_extractor.h>
#include <holo/localization/vision/geometry/ransac_fundamental_matrix_problem.h>
#include <holo/localization/vision/vslam/intrinsic.h>
#include <holo/localization/vision/vslam/intrinsic_yaml_node_convert.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>
#include <holo/obstacle/obstacle_list.h>
#include <holo/os/tictoc_timer.h>
#include <holo/os/timer.h>
#include <holo/parking/vision/point_feature_list.h>
#include <holo/parking/vision/point_feature_list_common_types.h>
#include <holo/point_cloud/point_type.h>
#include <holo/probability/ransac/ransac.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>

#include <boost/filesystem.hpp>
#include <boost/optional.hpp>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
/**
 * @addtogroup vslam
 * @{
 *
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define common basic types
 */
using Scalar                       = holo::float64_t;
using Box2                         = holo::Box2T<Scalar>;
using Epsilon                      = holo::EpsilonT<Scalar>;
using Matrix2                      = holo::Matrix2T<Scalar>;
using Matrix3                      = holo::Matrix3T<Scalar>;
using Matrix4                      = holo::Matrix4T<Scalar>;
using Matrix6                      = holo::Matrix6T<Scalar>;
using MatrixX                      = holo::MatrixXT<Scalar>;
using Point2                       = holo::Point2T<Scalar>;
using Point3                       = holo::Point3T<Scalar>;
using Pose3                        = holo::Pose3T<Scalar>;
using Quaternion                   = holo::QuaternionT<Scalar>;
using Rot2                         = holo::Rot2T<Scalar>;
using Rot3                         = holo::Rot3T<Scalar>;
using Vector2                      = holo::Vector2T<Scalar>;
using Vector3                      = holo::Vector3T<Scalar>;
using Vector4                      = holo::Vector4T<Scalar>;
using Vector5                      = holo::Vector5T<Scalar>;
using Vector6                      = holo::Vector6T<Scalar>;
using VectorX                      = holo::VectorXT<Scalar>;
using IntrinsicBaseType            = CameraIntrinsicBaseT<Scalar>;
using IntrinsicBaseTypeFromBase    = holo::common::details::CameraIntrinsicBaseT<Scalar>;
using IntrinsicBaseTypePtr         = std::shared_ptr<IntrinsicBaseType>;
using FisheyeIntrinsicType         = FisheyeIntrinsicT<Scalar>;
using PinholeIntrinsicType         = PinholeIntrinsicT<Scalar>;
using OmnidirectionalIntrinsicType = OmnidirectionalIntrinsicT<Scalar>;
using Extrinsic                    = holo::common::Extrinsicf;
using PointFeature                 = holo::parking::vision::PointFeatureT<holo::float32_t>;
using PointFeaturePtrList          = holo::parking::vision::PointFeaturePtrListT<PointFeature>;
using PointFeaturefList_ST         = holo::parking::vision::PointFeaturefList_ST;
using ParkingSlotType              = holo::common::ParkingSlotT<Scalar>;
using ParkingSlotFrameType         = holo::common::ParkingSlotFrameT<Scalar>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define types for ransac funcdamental matrix problem
 */
using ProblemType      = RansacFundamentalMatrixProblemT<Scalar>;
using MethodType       = typename ProblemType::MethodType;
using AdapterType      = typename ProblemType::AdapterType;
using RansacType       = holo::Ransac<ProblemType>;
using RansacParameters = typename RansacType::Parameters;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define types used in vslam
 */
using Imu                  = holo::ImuT<Scalar>;
using ImuBias              = holo::ImuBiasT<Scalar>;
using Odometry             = holo::common::OdometryT<Scalar>;
using ChassisState         = holo::ChassisState;
using Image                = holo::Image;
using Navstate             = holo::localization::NavstateT<Scalar>;
using Vehiclestate         = holo::localization::AdvancedNavstateT<Scalar>;
using StampedVehiclestate  = StampedT<Vehiclestate>;
using Mat                  = holo::localization::Mat;
using Mask                 = holo::localization::Mask;
using Model                = IntrinsicBaseType::Model;
using Rect2i               = holo::localization::Rect2i;
using Size2i               = holo::localization::Size2i;
using KeyPoint2f           = holo::localization::KeyPoint2f;
using ImageUndistortion    = holo::localization::ImageUndistorterT<IntrinsicBaseTypeFromBase>;
using ImageUndistortionPtr = std::shared_ptr<ImageUndistortion>;
using GnssPosition         = holo::GnssPosition;
using PointCloudXYZIRRgbSt =
    holo::pointcloud::PointCloudT<holo::point_cloud::details::PointXYZIRRgbSt<holo::float32_t>, -1>;
using ObstacleGeneral = holo::ObstacleGeneralT<holo::float32_t>;
using ObstaclePtrList = holo::ObstaclePtrListT<ObstacleGeneral, holo::OBSTACLE_MAX_NUM_CONTOUR_POINTS>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define source checker
 */
using SourceCheckerPointFeatureList = SourceCheckerT<PointFeaturePtrList>;
using SourceCheckerObstaclePtrList  = SourceCheckerT<ObstaclePtrList>;
using SourceCheckerParkingSlotFrame = SourceCheckerT<ParkingSlotFrameType>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define mappoint state
 */
enum class MapPointState : uint16_t
{
    CANDIDATE = 0,  ///< the initial state of prebuilt mappoint
    VISIBLE   = 1,  ///< the mappoint is visible but not matched with new features
    MATCHED   = 2,  ///< the mappoint is matched with new features

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define semantic label
 */
enum class SemanticLabel : uint16_t
{
    STATIC       = 0,  ///< the semantic label is static
    VEHICLE      = 1,  ///< the semantic label is car
    BYCICLE      = 2,  ///< the semantic label is bycicle
    PEDESTRIAN   = 3,  ///< the semantic label is people
    TRAFFIC_SIGN = 4,  ///< the semantic label is traffic sign
    ANIMAL       = 5,  ///< the semantic label is animal
    UNKNOWN      = 6,  ///< the semantic label is unknow

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief the struct represent app error status
 */
struct AppErrorStatus
{
    /**
     * @brief define smart pointer
     */
    using Ptr      = std::shared_ptr<AppErrorStatus>;
    using ConstPtr = std::shared_ptr<const AppErrorStatus>;

    /// @brief the number of feature point is few
    bool feature_point_num_few;

    ///@brief the front camera frequency is low
    bool front_camera_frequency_low;

    ///@brief the imu frequency is low
    bool imu_frequency_low;

    /// @brief the chassis state frequency is low
    bool chassis_state_frequency_low;

    /// @brief the point feauture frequency is low
    bool feature_point_frequency_low;

    /// @brief the obstacle list frequency is low
    bool obstacle_frequency_low;

    ///@brief the parking slot frequency is low
    bool parking_slot_frequency_low;

    ///@brief the gnss postion frequency is low
    bool gnss_position_frequency_low;

    /// @brief the vehicle is not standstill when online mapping
    bool vehicle_is_not_standstill;

    /// @brief parking overtime when online mapping
    bool online_mapping_parking_overtime;

    /// @brief travel distance beyond limits when online mapping
    bool online_mapping_over_length;

    /// @brief mapping distance over length warning level 1
    bool online_mapping_over_length_warning_L1;

    /// @brief travel speed beyond limits 15km/h when online mapping
    bool online_mapping_over_speed_15;

    ///@brief travel speed beyond limits 20km/h when online mapping
    bool online_mapping_over_speed_20;

    /// @brief travel timeout when online mapping
    bool online_mapping_overtime;

    /// @brief mapping timeout warning
    bool online_mapping_overtime_warning;

    /// @brief init failed when localization
    bool localization_init_failed;

    /// @brief offline mapping overtime
    bool offline_mapping_overtime;

    /// @brief offline mapping failed
    bool offline_mapping_failed;

    /// @brief mapping distance over length warning level 1
    bool online_mapping_over_length_warning_L2;

    /// @brief online mapping turning limit
    bool onine_mapping_turning_radius_small;

    /// @brief slope limit
    bool online_mapping_slope_large;

    /// @brief constructor
    AppErrorStatus(const bool& _feature_point_num_few = 0, const bool& _front_camera_frequency_low = 0,
                   const bool& _imu_frequency_low = 0, const bool& _chassis_state_frequency_low = 0,
                   const bool& _feature_point_frequency_low = 0, const bool& _obstacle_frequency_low = 0,
                   const bool& _parking_slot_frequency_low = 0, const bool& _gnss_position_frequency_low = 0,
                   const bool& _vehicle_is_not_standstill = 0, const bool& _online_mapping_parking_overtime = 0,
                   const bool& _online_mapping_over_length = 0, const bool& _online_mapping_over_length_warning_L1 = 0,
                   const bool& _online_mapping_over_speed_15 = 0, const bool& _online_mapping_over_speed_20 = 0,
                   const bool& _online_mapping_overtime = 0, const bool& _online_mapping_overtime_warning = 0,
                   const bool& _localization_init_failed = 1, const bool& _offline_mapping_overtime = 0,
                   const bool& _offline_mapping_failed = 0, const bool& _online_mapping_over_length_warning_L2 = 0,
                   const bool& _onine_mapping_turning_radius_small = 0, const bool& _online_mapping_slope_large = 0)
      : feature_point_num_few(_feature_point_num_few)
      , front_camera_frequency_low(_front_camera_frequency_low)
      , imu_frequency_low(_imu_frequency_low)
      , chassis_state_frequency_low(_chassis_state_frequency_low)
      , feature_point_frequency_low(_feature_point_frequency_low)
      , obstacle_frequency_low(_obstacle_frequency_low)
      , parking_slot_frequency_low(_parking_slot_frequency_low)
      , gnss_position_frequency_low(_gnss_position_frequency_low)
      , vehicle_is_not_standstill(_vehicle_is_not_standstill)
      , online_mapping_parking_overtime(_online_mapping_parking_overtime)
      , online_mapping_over_length(_online_mapping_over_length)
      , online_mapping_over_length_warning_L1(_online_mapping_over_length_warning_L1)
      , online_mapping_over_speed_15(_online_mapping_over_speed_15)
      , online_mapping_over_speed_20(_online_mapping_over_speed_20)
      , online_mapping_overtime(_online_mapping_overtime)
      , online_mapping_overtime_warning(_online_mapping_overtime_warning)
      , localization_init_failed(_localization_init_failed)
      , offline_mapping_overtime(_offline_mapping_overtime)
      , offline_mapping_failed(_offline_mapping_failed)
      , online_mapping_over_length_warning_L2(_online_mapping_over_length_warning_L2)
      , onine_mapping_turning_radius_small(_onine_mapping_turning_radius_small)
      , online_mapping_slope_large(_online_mapping_slope_large)
    {
    }

    /// @brief cast struct to uint32
    operator uint32_t() const
    {
        return static_cast<uint32_t>(
            feature_point_num_few * 0x0001 + front_camera_frequency_low * 0x0002 + imu_frequency_low * 0x0004 +
            chassis_state_frequency_low * 0x0008 + feature_point_frequency_low * 0x0010 +
            obstacle_frequency_low * 0x0020 + parking_slot_frequency_low * 0x0040 +
            gnss_position_frequency_low * 0x0080 + vehicle_is_not_standstill * 0x0100 +
            online_mapping_parking_overtime * 0x0200 + online_mapping_over_length * 0x0400 +
            online_mapping_over_length_warning_L1 * 0x0800 + online_mapping_over_speed_15 * 0x1000 +
            online_mapping_over_speed_20 * 0x2000 + online_mapping_overtime * 0x4000 +
            online_mapping_overtime_warning * 0x8000 + localization_init_failed * 0x00010000 +
            offline_mapping_overtime * 0x00020000 + offline_mapping_failed * 0x00040000 +
            online_mapping_over_length_warning_L2 * 0x00080000 + onine_mapping_turning_radius_small * 0x00100000 +
            online_mapping_slope_large * 0x00200000);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief the struct represent feature point in feature map
 */
struct MapPoint
{
    /// @brief update remember rate of mappoint
    void UpdateRememberRate();

    /// @brief update mappoint state
    void UpdateState();

    /// @brief position of the point
    Point3 position;

    /// @brief view direction when triangulate the point
    Vector3 direction;

    /// @brief covariance of the point
    Matrix3 covariance;

    /// @brief associated descriptor
    cv::Mat descriptor;

    /// @brief reference observed camera pose in world frame
    Pose3 reference_pose;

    /// @brief reference frame id
    uint64_t reference_frame_id;

    /// @brief score
    Scalar score;

    /// @brief the remember_rate (the new remember rate can calculate from the old, so retain it to avoid repeated
    /// computation.)
    Scalar remember_rate;

    /// @brief the matching results for all localization times
    std::vector<MapPointState> life_long_states;

    /// @brief the reprojection errors in once localization
    std::vector<Scalar> reprojection_errors;

    ///@brief the mean reprojection error
    Scalar mean_reprojection_error;

    /// @brief the semantic of mappoint
    SemanticLabel semantic_label;
};

using MapPointPtr = std::shared_ptr<MapPoint>;
using Map         = std::vector<MapPointPtr>;
using MapPtr      = std::shared_ptr<Map>;
using ConstMapPtr = std::shared_ptr<const Map>;

using ParkingSlotPtr  = std::shared_ptr<ParkingSlotType>;
using SlotMap         = std::vector<ParkingSlotPtr>;
using SlotMapPtr      = std::shared_ptr<SlotMap>;
using ConstSlotMapPtr = std::shared_ptr<const SlotMap>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief the struct represent feature line in feature map
 *
 */
struct MapLine
{
    /// @brief update mappoint state
    void UpdateState();

    /// @brief position of one of the line endpoint
    Point3 first_endpoint;

    /// @brief position of another line endpoint
    Point3 second_endpoint;

    /// @brief space plucker line consist of line normal vector and direction vector
    GTPluckerLine plucker_line;

    /// @brief covariance of the line
    Matrix3 covariance;

    /// @brief associated descriptor
    cv::Mat descriptor;

    /// @brief reference observed camera pose in world frame
    Pose3 reference_pose;

    /// @brief reference frame id
    uint64_t reference_frame_id;

    /// @brief score
    Scalar score;

    /// @brief the reprojection errors in once localization
    std::vector<Scalar> reprojection_errors;
};

using MapLinePtr       = std::shared_ptr<MapLine>;
using MapLines         = std::vector<MapLinePtr>;
using MapLinesPtr      = std::shared_ptr<MapLines>;
using ConstMapLinesPtr = std::shared_ptr<const MapLines>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef gtsam::Symbol Symbol;      ///< gtsam symbol
using gtsam::symbol_shorthand::B;  ///< gtsam bias key
using gtsam::symbol_shorthand::E;  ///< gtsam essential matrix key
using gtsam::symbol_shorthand::L;  ///< gtsam landmark key
using gtsam::symbol_shorthand::P;  ///< gtsam Plane key
using gtsam::symbol_shorthand::S;  ///< gtsam ParkingSlot key
using gtsam::symbol_shorthand::V;  ///< gtsam Velocity key
using gtsam::symbol_shorthand::X;  ///< gtsam Pose key

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define gtsam factor
 */
using ImuBiasFactor                 = gtsam::BetweenFactor<gtsam::imuBias::ConstantBias>;
using Pose3BetweenFactor            = gtsam::BetweenFactor<gtsam::Pose3>;
using Vector3BetweenFactor          = gtsam::BetweenFactor<gtsam::Vector3>;
using GPSFactor                     = gtsam::GPSFactor;
using ImuFactor                     = gtsam::ImuFactor;
using ProjectionFactor              = gtsam::GenericProjectionFactor<gtsam::Pose3, gtsam::Point3>;
using PosePriorFactor               = gtsam::PriorFactor<gtsam::Pose3>;
using GeneralCamera                 = gtsam::PinholeCamera<gtsam::Cal3_S2>;
using PreintegratedImuMeasurements  = gtsam::PreintegratedImuMeasurements;
using PreintegratedAhrsMeasurements = gtsam::PreintegratedAhrsMeasurements;
using Values                        = gtsam::Values;

class Unit3Factor;
using Unit3Factors = std::vector<Unit3Factor>;

/**
 * @brief define position measurement in UTM coordinate
 */
struct UtmPosition
{
    Timestamp timestamp;     ///< timestamp
    Point3    position;      ///< position in UTM coordinate
    Vector3   position_std;  ///< standard deviation of position

    /// @brief constructor
    UtmPosition(const Timestamp& _timestamp = Timestamp(), const Point3& _position = {},
                const Vector3& _position_std = {})
      : timestamp(_timestamp), position(_position), position_std(_position_std)
    {
    }
};

/**
 * @brief define wheel integration parameters
 */
struct WheelIntegrationMeasurement
{
    Timestamp start;
    Timestamp end;
    Scalar    delta_x;
    Scalar    delta_y;
    Scalar    delta_yaw;

    WheelIntegrationMeasurement(const Timestamp& _start = Timestamp(), const Timestamp& _end = Timestamp(),
                                const Scalar _delta_x = 0.0, const Scalar _delta_y = 0.0,
                                const Scalar _delata_yaw = 0.0)
      : start(_start), end(_end), delta_x(_delta_x), delta_y(_delta_y), delta_yaw(_delata_yaw)
    {
    }
};

/**
 * @brief define reliability of the velocity measurement
 */
enum class VelocityMeasurementReliability : uint16_t
{
    HIGH   = 0,  ///< the velocity measurement is reliable
    LOW    = 1,  ///< the velocity measurement is not completely reliable
    NOGOOD = 2,  ///< the velocity measurement is NOT reliable
};

/**
 * @brief define velocity measurement
 */
struct VelocityMeasurement
{
    /// @brief timestamp of this measurement
    Timestamp timestamp;

    /// @brief velocity measurement in body
    Vector3 velocity;

    /// @brief reliability of the velocity measurement
    VelocityMeasurementReliability reliability;

    /// @brief default comstructor
    VelocityMeasurement(const Timestamp& _timestamp = Timestamp(), const Vector3& _velocity = Vector3(0.0, 0.0, 0.0),
                        const VelocityMeasurementReliability& _reliability = VelocityMeasurementReliability::NOGOOD)
      : timestamp(_timestamp), velocity(_velocity), reliability(_reliability)
    {
    }
};

struct EssentialMatrixMeasurement
{
    uint64_t                                             train_frame_id;
    uint64_t                                             query_frame_id;
    std::unordered_map<uint16_t, gtsam::EssentialMatrix> measured_E;
    gtsam::Rot3                                          r;
};
using EssentialMatrixMeasurements = std::vector<EssentialMatrixMeasurement>;

/**
 * @brief define raw measurement
 */
struct RawMeasurement
{
    /// @brief newest timestamp
    Timestamp newest_timestamp;

    /// @brief new images sampled by multi camera system
    /// @note images is only for visualization, it's normal if multi_point_feature_list is available while images is
    /// empty. so one should check if images is empty before use it.
    std::vector<Image> images;

    /// @brief new features extracted on new image
    std::vector<PointFeaturefList_ST*> multi_point_feature_list;

    /// @brief new imus from last vslam localization timestamp to the new image's timestamp
    std::vector<Imu> imus;

    /// @brief all vehicle info from last image's timestamp to new image's timestamp
    std::vector<ChassisState> chassis_states;

    /// @brief gravity-aligned odometry at new image's timestamp
    boost::optional<Odometry> optional_odometry;

    /// @brief visible map points
    MapPtr visible_map;

    /// @brief gps position at new image's timestamp
    boost::optional<GnssPosition> optional_position;

    /// @brief obstacle lists sampled by multi camera system.
    std::vector<ObstaclePtrList> multi_obstacle_list;

    /// @brief parking_slot_frame
    boost::optional<ParkingSlotFrameType> optional_parking_slot_frame;

    /// @brief visible parking slot map
    SlotMapPtr visible_slot_map;
    /**
     * @brief Construct a new Raw Measurement object
     *
     * @param _image new image
     * @param _imus new imus
     * @param _velocity new vehicle velocity in body frame
     * @param _optional_odometry new gravity-aligned odometry
     * @param _map new map
     * @param _optional_position new gps position
     */
    RawMeasurement(const Timestamp& _newest_timestamp = Timestamp(), const std::vector<Image>& _images = {},
                   const std::vector<PointFeaturefList_ST*>& _multi_point_feature_list = {},
                   const std::vector<Imu>& _imus = {}, const std::vector<ChassisState>& _chassis_states = {},
                   const boost::optional<Odometry>& _optional_odometry = boost::none, const MapPtr& _visible_map = {},
                   const boost::optional<GnssPosition>&         _optional_position           = boost::none,
                   const std::vector<ObstaclePtrList>&          _multi_obstacle_list         = {},
                   const boost::optional<ParkingSlotFrameType>& _optional_parking_slot_frame = boost::none,
                   const SlotMapPtr&                            _visiable_slot_map           = {})
      : newest_timestamp(_newest_timestamp)
      , images(_images)
      , multi_point_feature_list(_multi_point_feature_list)
      , imus(_imus)
      , chassis_states(_chassis_states)
      , optional_odometry(_optional_odometry)
      , visible_map(_visible_map)
      , optional_position(_optional_position)
      , multi_obstacle_list(_multi_obstacle_list)
      , optional_parking_slot_frame(_optional_parking_slot_frame)
      , visible_slot_map(_visiable_slot_map)
    {
    }
};  // RawMeasurement

/**
 * @brief define the corrected sensor measurement
 * @details the CorrectedMeasurement is the "advanced version" of the RawMeasurement. all measurements collected in
 * RawMeasurement will be calibrated by each sensor's own intrinsic parameters.
 */
struct CorrectedMeasurement
{
    /// @brief images sampled by multi camera system.
    /// @details all images are grayscale and already been well undistorted.
    std::vector<Image> images;

    /// @brief new imus from last vslam localization timestamp to the new image's timestamp
    std::vector<Imu> imus;

    /// @brief all vehicle info from last image's timestamp to new image's timestamp
    /// @details the vehicle speed was corrected by the calibrated scale factor.
    std::vector<ChassisState> chassis_states;

    /// @brief optional gps position in utm coordinate, and it has absolutely pass the outlier checking.
    boost::optional<UtmPosition> optional_position;

    /// @brief wheel integration measurement
    WheelIntegrationMeasurement wheel_integration_measurement;

    /// @brief velocity measurement status.
    VelocityMeasurement velocity_measurement;

    /// @brief ground truth odometry, only enable in benchmark.
    boost::optional<Odometry> optional_ground_truth_odom;

};  // CorrectedMeasurement

/**
 * @brief measurement for map projection factor
 */
struct MapProjectionMeasurement
{
    /// @brief associated frame id of this factor
    uint64_t frame_id;

    /// @brief associated camera id of this factor
    uint16_t camera_index;

    /// @brief map point
    MapPointPtr map_point;

    /// @brief projective ray of detected point to the sphere
    Vector3 bearing;

    /**
     * @brief Construct a new Map Projection Measurement object
     *
     * @param _frame_id current frame id
     * @param _map_point map point
     * @param _bearing bearing vector
     */
    MapProjectionMeasurement(const uint64_t _frame_id, const uint16_t _camera_index,
                             const std::shared_ptr<MapPoint>& _map_point, const Vector3& _bearing)
      : frame_id(_frame_id), camera_index(_camera_index), map_point(_map_point), bearing(_bearing)
    {
    }
};

typedef std::vector<MapProjectionMeasurement> MapProjectionMeasurements;

/**
 * @brief association result of parking slots
 */
struct SlotMapAssociationResult
{
    ParkingSlotType train_slot;

    ParkingSlotType query_slot;
};

/**
 * @brief Measurements used to construct parking slot pose only factors in localization mode
 */
struct SlotMapFactorMeasurement
{
    /// @brief associated frame id of this factor
    uint64_t frame_id;

    std::vector<SlotMapAssociationResult> measurements;

    SlotMapFactorMeasurement(const uint64_t                               _frame_id     = 0,
                             const std::vector<SlotMapAssociationResult>& _measurements = {})
      : frame_id(_frame_id), measurements(_measurements)
    {
    }
};

/**
 * @brief smart pointer
 */
typedef boost::shared_ptr<ImuBiasFactor>               ImuBiasFactorPtr;
typedef boost::shared_ptr<Vector3BetweenFactor>        GyroBiasFactorPtr;
typedef boost::shared_ptr<Pose3BetweenFactor>          Pose3BetweenFactorPtr;
typedef boost::shared_ptr<ImuFactor>                   ImuFactorPtr;
typedef boost::shared_ptr<ProjectionFactor>            ProjectionFactorPtr;
typedef boost::shared_ptr<gtsam::NoiseModelFactor>     NoiseModelFactorPtr;
typedef boost::shared_ptr<gtsam::PreintegrationParams> PreintegrationParamsPtr;
typedef boost::shared_ptr<PosePriorFactor>             PosePriorFactorPtr;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define feature information
 */
struct Feature
{
    /// @brief 2d point detected on image
    cv::Point2f image_point;

    /// @brief an optional descriptor of this point
    boost::optional<cv::Mat> optional_descriptor;

    /// @brief normalized point on normalized plane(z == 1)
    Point3 normalized_point;

    /// @brief camera id. indicate which camera does this feature comes from
    uint16_t camera_id;

    /// @brief confidence of this keypoint
    Scalar score;

    ///@brief the semantic label of this feature
    SemanticLabel semantic_label;

    /**
     * @brief Construct a new Feature object
     *
     * @param _image_point 2d point detected on image
     * @param _optional_descriptor an optional descriptor of this point
     * @param _normalized_point normalized point on normalized plane(z == 1)
     * @param _camera_id camera id
     */
    Feature(const cv::Point2f&             _image_point         = cv::Point2f(),
            const boost::optional<cv::Mat> _optional_descriptor = boost::none,
            const Point3& _normalized_point = Point3(), const uint16_t _camera_id = 0, const Scalar _score = -1.0,
            const SemanticLabel& _semantic_label = SemanticLabel::STATIC)
      : image_point(_image_point)
      , optional_descriptor(_optional_descriptor)
      , normalized_point(_normalized_point)
      , camera_id(_camera_id)
      , score(_score)
      , semantic_label(_semantic_label)
    {
    }
};
typedef std::vector<Feature> Features;

/**
 * @brief define line feature information
 *
 */
struct LineFeature
{
    /// @brief 2d line endpoints detected on image
    cv::Point2f line_endpoint_first;
    cv::Point2f line_endpoint_second;

    /// @brief normalized line endpoints in camera frame
    Vector3 normalized_line_endpoint_first;
    Vector3 normalized_line_endpoint_second;

    /// @brief an optional descriptor of this line
    boost::optional<cv::Mat> optional_line_descriptor;

    /// @brief normalized line coefficient
    Vector3 normalized_line_coefficient;

    /// @brief plucker line landmark
    GTPluckerLine plucker_line;

    /// @brief orthonormal line
    GTOrthonormalLine orthonormal_line;

    /// @brief camera id. indicate which camera does this line feature comes from
    uint16_t camera_id;

    /**
     * @brief Construct a new Line Feature object
     *
     * @param[in] _line_endpoint_first 2d line endpoint first detected on image
     * @param[in] _line_endpoint_second 2d line endpoint second  detected on image
     * @param[in] _normalized_line_endpoint_first normalized line endpoint first in camera frame
     * @param[in] _normalized_line_endpoint_second normalized line endpoint second in camera frame
     * @param[in] _optional_line_descriptor an optional descriptor of this line
     * @param[in] _normalized_line_coefficient normalized line coefficient
     * @param[in] _plucker_line plucker line landmark
     * @param[in] _orthonormal_line orthonormal line
     * @param[in] _camera_id camera id. indicate which camera does this line feature comes from
     */
    LineFeature(cv::Point2f const& _line_endpoint_first, cv::Point2f const& _line_endpoint_second,
                Vector3 const& _normalized_line_endpoint_first, Vector3 const& _normalized_line_endpoint_second,
                boost::optional<cv::Mat> const& _optional_line_descriptor, Vector3 const& _normalized_line_coefficient,
                GTPluckerLine const& _plucker_line, GTOrthonormalLine const& _orthonormal_line,
                uint16_t const _camera_id)
      : line_endpoint_first(_line_endpoint_first)
      , line_endpoint_second(_line_endpoint_second)
      , normalized_line_endpoint_first(_normalized_line_endpoint_first)
      , normalized_line_endpoint_second(_normalized_line_endpoint_second)
      , optional_line_descriptor(_optional_line_descriptor)
      , normalized_line_coefficient(_normalized_line_coefficient)
      , plucker_line(_plucker_line)
      , orthonormal_line(_orthonormal_line)
      , camera_id(_camera_id)
    {
    }
};
typedef std::vector<LineFeature> LineFeatures;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief vehicle state
 *
 * @details it defines vehicle state in world/IMU frame
 *          (position, orientation, linear_velocity) and imu bias
 */
struct VehicleState
{
    /// @brief navstate
    Navstate navstate;

    /// @brief imu bias
    ImuBias bias;

    /**
     * @brief Construct a new Vehicle State object
     *
     * @param _navstate
     * @param _bias
     */
    VehicleState(const Navstate& _navstate = Navstate(), const ImuBias& _bias = ImuBias())
      : navstate(_navstate), bias(_bias)
    {
    }

    /**
     * @brief Construct a new Vehicle State object
     *
     * @param _pose
     * @param _velocity
     * @param _bias
     */
    VehicleState(const Pose3& _pose, const Vector3& _velocity, const ImuBias& _bias)
      : navstate(_pose, _velocity), bias(_bias)
    {
    }

    /**
     * @brief Construct a new Vehicle State object
     *
     * @param translation
     * @param rotation
     * @param velocity
     * @param acc_bias
     * @param gyro_bias
     */
    VehicleState(const Point3& translation, const Rot3& rotation, const Vector3& velocity, const Vector3& acc_bias,
                 const Vector3& gyro_bias)
      : navstate(Pose3(rotation, translation), velocity)
    {
        bias.SetLinearAccelerationBias(acc_bias);
        bias.SetAngularVelocityBias(gyro_bias);
    }

    /**
     * @brief API of pose
     */
    const Pose3& Pose() const;

    /**
     * @brief API of velocity
     */
    const Vector3& Velocity() const;

    /**
     * @brief velocity in body
     */
    Vector3 VelocityInBody() const;

    /**
     * @brief API of translation
     */
    const Point3& Translation() const;

    /**
     * @brief API of rotation
     */
    const Rot3& Rotation() const;

    /**
     * @brief API of acc bias
     */
    const Vector3 AccBias() const;

    /**
     * @brief API of gyro bias
     */
    const Vector3 GyroBias() const;

    /**
     * @brief output stream for VehicleState
     *
     * @param os std::ostream&
     * @param vs vehicle state
     * @return std::ostream&
     */
    friend std::ostream& operator<<(std::ostream& os, const VehicleState& vs)
    {
        os << "Vehicle State:"
           << "\n pose = " << vs.navstate.GetPose() << "\n velocity = " << vs.navstate.GetVelocity().Transpose()
           << "\n bias: acc = [" << vs.bias.GetLinearAccelerationBias().Transpose() << "], gyro = ["
           << vs.bias.GetAngularVelocityBias().Transpose() << "]" << std::endl;
        return os;
    }

};  // struct VehicleState

/**
 * @brief prior vehicle state noise
 */
struct PriorVehicleStateNoise
{
    /// @brief sigma of prior pose factor for roll, pitch, yaw, x, y, z
    const Vector6 pose_sigma;

    /// @brief sigma of prior velocity factor for vx, vy, vz
    const Vector3 velocity_sigma;

    /// @brief sigma of prior imu bias factor for acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z
    const Vector6 bias_sigma;

    /**
     * @brief Construct a new Prior Vehicle State Noise object
     *
     * @param _pose_sigma sigma for pose
     * @param _velocity_sigma sigma for velocity
     * @param _bias_sigma sigma for imu bias
     */
    PriorVehicleStateNoise(const Vector6& _pose_sigma, const Vector3& _velocity_sigma, const Vector6& _bias_sigma)
      : pose_sigma(_pose_sigma), velocity_sigma(_velocity_sigma), bias_sigma(_bias_sigma)
    {
    }

    /**
     * @brief output stream for prior vehicle state noise
     *
     * @param os std::ostream&
     * @param prior_noise  prior vehicle state noise
     * @return std::ostream& contains contents of input prior vehicle state noise
     */
    friend std::ostream& operator<<(std::ostream& os, const PriorVehicleStateNoise& prior_noise)
    {
        os << "PriorVehicleStateNoise:"
           << "\n pose_sigma = " << prior_noise.pose_sigma.Transpose()
           << "\n velocity_sigma = " << prior_noise.velocity_sigma.Transpose()
           << "\n bias_sigma = " << prior_noise.bias_sigma.Transpose() << std::endl;
        return os;
    }

    /**
     * @brief static method to generate example for unit test
     *
     * @return PriorVehicleStateNoise
     */
    static PriorVehicleStateNoise Example();

    /**
     * @brief load from yaml
     *
     * @param node node
     * @return PriorVehicleStateNoise
     */
    static PriorVehicleStateNoise LoadFromYaml(const holo::yaml::Node& node);

};  // struct PriorVehicleStateNoise

/**
 * @brief utility class of construct extrinsic T_bc (camera pose in body frame)
 */
class Utility
{
public:
    /**
     * @brief construct extrinsic T_bc from lidar_in_gnss lidar_in_camera and gnss_in_body extrinsic yaml file
     *
     * @param lidar_extrinsic_file extrinsic yaml file for lidar in gnss frame
     * @param camera_extrinsic_file extrinsic yaml file for lidar in camera frame
     * @param body_gnss_extrinsic_file extrinsic yaml file for gnss in body frame
     * @throw throw exception when the yaml file does not exist
     * @return extrinsic of camera in body frame
     */
    static Pose3 ConstructTbc(const std::string lidar_extrinsic_file, const std::string camera_extrinsic_file,
                              const std::string body_gnss_extrinsic_file = "");

    static Pose3 CompensateT(Pose3 const& initial_T, Vector3 const& delta_rpy);

    /**
     * @brief compute the essential matrix ( E = t_x * R) from two poses
     *
     * @todo this function needs to support both float32_t and float64_t type
     *
     * @param pose0 pose of the first view that transforms point from current view
     * to world
     * @param pose1 pose of the second view that transforms point from current view
     * to world
     *
     * @return matrix3 essential matrix E = t_x * R
     */
    static Matrix3 EssentialMatrixFromPoses(const Pose3& pose0, const Pose3& pose1);

    /**
     * @brief input two id to get an unique id.
     */
    static uint64_t HashId(const uint64_t& first_id, const uint64_t& second_id);

    /**
     * @brief get two original id from an unique id.
     */
    static std::pair<uint64_t, uint64_t> UnHashId(const uint64_t& hashed_id);

    /**
     * @brief create image undostorters from intrinsics
     */
    static std::vector<ImageUndistortionPtr>
    CreateImageUndistorters(const std::vector<IntrinsicBaseTypePtr>& intrinsics);

    /**
     * @brief create image undostorter from intrinsic
     */
    static ImageUndistortionPtr CreateImageUndistorter(const IntrinsicBaseTypePtr& intrinsic);

    template <typename T>
    static std::shared_ptr<IntrinsicBaseType> CreateCameraIntrinsic(YAML::Node const& node);

};  // class Utility

/**
 * @brief reset flags
 * @detials flags record the unexpected behavior of the LocalizationVslam algorithm
 */
struct ResetFlags
{
    /// @brief whether exception happens
    std::atomic<bool> is_exception;

    /// @brief whether the trajectory jumping happens
    std::atomic<bool> is_trajectory_jump;

    /**
     * @brief constructor
     */
    ResetFlags() : is_exception(false), is_trajectory_jump(false)
    {
    }

    /**
     * @brief operator bool to return whether should reset
     */
    operator bool() const
    {
        return is_exception || is_trajectory_jump;
    }

    /**
     * @brief overload operator= because operator = is delete in std::atomic<T>
     */
    void operator=(const ResetFlags& in)
    {
        is_exception.exchange(in.is_exception);
        is_trajectory_jump.exchange(in.is_trajectory_jump);
    }
};  // struct ResetFlags

/**
 * @brief sequence counter for PublishVslamResult() and PublishImuPredictionResult()
 *        to recorder the number of the result published from the begining of the algorithm
 */
struct SequenceCounter
{
    /// @brief vslam callback sequence counter
    uint64_t vslam_callback_sequence_counter;

    /// @brief imu prediction callback sequence counter
    uint64_t prediction_callback_sequence_counter;

    /**
     * @brief constructor
     */
    SequenceCounter() : vslam_callback_sequence_counter(0), prediction_callback_sequence_counter(0)
    {
    }
};  // SequenceCounter

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define camera parameters.(intrinsics and extrinsics)
 *
 */
struct CameraParameters
{
    /**
     * @brief smart pointer
     */
    typedef std::shared_ptr<CameraParameters>       Ptr;
    typedef std::shared_ptr<const CameraParameters> ConstPtr;

    /// @brief number of camera
    uint16_t camera_number;

    /// @brief camera coord, images in raw measurement should construct by this order.
    std::vector<std::string> camera_coords;

    /// @brief camera intrinsics
    std::vector<IntrinsicBaseTypePtr> intrinsics;

    /// @brief camera extrinsic
    std::vector<Pose3> extrinsics;

    /// @brief available_fov of each camera for feature extraction
    std::vector<Scalar> available_fov;

    /// @brief roi for feature extraction of each camera
    /// @details this rectangle region will computed by available_fov and intrinsic of each camera
    std::vector<cv::Rect2i> rois;

    /// @brief feature detection noise at image center and loss function threshold for visual projection factor.
    std::vector<std::pair<Scalar, Scalar>> sigma_uv_and_loss;

    /// @brief camera sensor id to camera index map
    /// @details camera sensor id is defined in intrinsics, camera index is the index of these std::vector above.
    std::unordered_map<uint32_t, uint16_t> sensor_id_to_camera_index_map_;

    /// @brief constructor
    CameraParameters(const uint16_t _camera_number, const std::vector<std::string>& _camera_coords,
                     const std::vector<IntrinsicBaseTypePtr>& _intrinsics, const std::vector<Pose3>& _extrinsics,
                     const std::vector<Scalar>&                    _available_fov,
                     const std::vector<std::pair<Scalar, Scalar>>& _sigma_uv_and_loss)
      : camera_number(_camera_number)
      , camera_coords(_camera_coords)
      , intrinsics(_intrinsics)
      , extrinsics(_extrinsics)
      , available_fov(_available_fov)
      , rois(CreateROI(intrinsics, available_fov))
      , sigma_uv_and_loss(_sigma_uv_and_loss)
    {
        // init sensor_id_to_camera_index_map_ for point features measurement alignment
        for (uint16_t camera_index = 0; camera_index < camera_number; camera_index++)
        {
            const auto& sensor_id = intrinsics.at(camera_index)->GetSensorId();
            sensor_id_to_camera_index_map_.emplace(static_cast<uint32_t>(sensor_id), camera_index);
        }
    }

    /**
     * @brief load camera parameters from yaml
     *
     * @param node yaml node
     * @return Parameters
     */
    static CameraParameters::Ptr LoadFromYaml(const holo::yaml::Node& node);

    /**
     * @brief load camera parameters from bin.
     * @details this function will be called by an offline map optimization APP. the camera parameters was saved by some
     * online mapping process.
     *
     * @param file which stored all camera parameters.
     * @return Parameters
     */
    static CameraParameters::Ptr LoadFromBin(const std::string& params_file);

    /**
     * @brief save camera parameters to bin.
     * @details this function will be called by an online mapping APP.
     *
     * @param file file to be saved
     */
    void SaveParametersToBin(const std::string& params_file) const;

    /**
     * @brief static example parameters
     */
    static CameraParameters::Ptr Example();

    /**
     * @brief load intrinsic
     */
    static IntrinsicBaseTypePtr LoadIntrinsic(const holo::yaml::Node& node);
    /**
     * @brief convert pixel error around image center(cx, cy) to unit3 error between the corresponding view direction
     * @details this function will compute the unit3 error(see unit3_factor.h) between such two direction vector
     *          1. the camera optical axis.
     *          2. a direction vector which from optical center to Point2(pixel_error, 0) + Point2(cx, cy);
     *
     * @param intrinsic camera intrinsic
     * @param pixel_error pixel error on image center
     *
     * @return unit3 error of the the two direction vector
     */
    static Scalar ComputeUnit3ErrorFromPixelErrorAtImageCenter(const IntrinsicBaseTypePtr& intrinsic,
                                                               const Scalar                pixel_error);

    /**
     * @brief create roi for feature extraction
     *
     * @param intrinsics camera intrinsics
     * @param available_fov available_fov for feature extraction
     * @return rois
     */
    std::vector<cv::Rect2i> CreateROI(const std::vector<IntrinsicBaseTypePtr>& intrinsics,
                                      const std::vector<Scalar>&               available_fov) const;

    /**
     * @brief output stream parameters
     *
     * @param os std::ostream&
     * @param parameters
     * @return std::ostream&
     */
    friend std::ostream& operator<<(std::ostream& os, const CameraParameters::Ptr params)
    {
        os << "\nMulti Camera Parameters: "
           << "\ncamera_number: " << params->camera_number << "\n";

        for (uint16_t camera_index = 0; camera_index < params->camera_number; camera_index++)
        {
            os << params->camera_coords.at(camera_index) << " camera: \n"
               << "extrinsic:  " << params->extrinsics.at(camera_index)
               << "\navailable_fov: " << params->available_fov.at(camera_index)
               << "\nsigma_uv: " << params->sigma_uv_and_loss.at(camera_index).first
               << "\nloss: " << params->sigma_uv_and_loss.at(camera_index).second << "\n";
        }

        return os;
    }

};  // CameraParameters

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_COMMON_TYPES_H_
