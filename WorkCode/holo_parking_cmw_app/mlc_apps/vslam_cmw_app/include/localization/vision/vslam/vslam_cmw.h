/*!
 * \brief holo cmw wrapper of visual based slam
 * \author Yanwei Du, duyanwei@holomatic.com
 * \date April-01-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_CMW_APPS_LOCALIZATION_VISION_VSLAM_VSLAM_CMW_H_
#define HOLO_CMW_APPS_LOCALIZATION_VISION_VSLAM_VSLAM_CMW_H_

#include <cmw_wrapper/cmw_bus.h>
#include <holo/localization/vision/vslam/localization/localization.h>
#include <holo/localization/vision/vslam/mapping/mapping.h>
#include <holo/localization/vision/vslam/visualizer.h>
#include <holo/parking/localization/vehicle_pose_2d.h>
#include <holo/sensors/camera/image_ipc.h>
#include <holo_base_msg/traits.h>
#include <holo_parking_msg/traits.h>

namespace vslam = holo::localization::vision::vslam;

namespace holo_cmw
{
/**
 * @brief VSLAM CMW class
 */
class VSLAMCmw
{
public:
    /**
     * @brief handy type define
     */
    using BusType              = cmw_wrapper::BusType;
    using VSLAMBase            = vslam::VSLAMBase;
    using VSLAMParameters      = VSLAMBase::Parameters;
    using Visualizer           = vslam::Visualizer;
    using VisParameters        = Visualizer::Parameters;
    using Scalar               = vslam::Scalar;
    using Matrix2              = vslam::Matrix2;
    using Matrix3              = vslam::Matrix3;
    using Matrix4              = vslam::Matrix4;
    using Matrix6              = vslam::Matrix6;
    using Point2               = vslam::Point2;
    using Point3               = vslam::Point3;
    using Pose3                = vslam::Pose3;
    using Quaternion           = vslam::Quaternion;
    using Rot2                 = vslam::Rot2;
    using Rot3                 = vslam::Rot3;
    using Vector2              = vslam::Vector2;
    using Vector3              = vslam::Vector3;
    using Vector4              = vslam::Vector4;
    using Vector5              = vslam::Vector5;
    using Vector6              = vslam::Vector6;
    using PointCloudXYZIRRgbSt = vslam::PointCloudXYZIRRgbSt;
    using ChassisState         = vslam::ChassisState;
    using PointFeaturePtrList  = vslam::PointFeaturePtrList;
    using VehiclePose          = holo::parking::localization::VehiclePose2Df;

    /**
     * @brief constructor
     */
    VSLAMCmw(const std::string& config_file, const uint32_t domain_id, const std::string& ns);

    /**
     * @brief destructor
     */
    ~VSLAMCmw();

    /**
     * @brief spin the node
     * @param[in] num_threads Number of threads
     */
    void Spin(holo::uint16_t const num_threads = 1u);

    /**
     * @brief stop the node
     */
    void Stop();

private:
    /************** @brief methods **************/
    /**
     * @brief set up
     */
    void SetUp(const std::string& config_file);

    /**
     * @brief input image callback
     */
    void InputImageCallback(holo::uint32_t msg, uint16_t camera_index);

    /**
     * @brief input imu callback
     */
    void InputImuCallback(const vslam::Imu& msg);

    /**
     * @brief input point feature list callback
     */
    void InputPointFeatureListCallback(const PointFeaturePtrList& msg);

    /**
     * @brief input chassis state callback
     */
    void InputChassisStateCallback(const vslam::ChassisState& msg);

    /**
     * @brief input gravity-aligned odometry callback
     */
    void InputGravityAlignedOdometryCallback(const vslam::Odometry& msg);

    /**
     * @brief input ground truth odometry callback
     */
    void InputGroundTruthOdometryCallback(const vslam::Odometry& msg);

    /**
     * @brief input gps position callback
     */
    void InputGpsPositionCallback(const vslam::GnssPosition& msg);

    /**
     * @brief input obstacle general list callback
     */
    void InputObstacleGeneralListCallback(const vslam::ObstaclePtrList& msg);

    /**
     * @brief output vslam callback
     */
    holo::int32_t OutputVSLAMResultCallback(const vslam::Odometry& odo_m, const vslam::ImuBias& bias);

    /**
     * @brief publish local feature map
     */
    holo::int32_t OutputLocalFeatureMap(const PointCloudXYZIRRgbSt& m);

    /**
     * @brief publish global feature map
     */
    holo::int32_t OutputGlobalFeatureMap(const PointCloudXYZIRRgbSt& m);

    /**
     * @brief publish global correspondence points
     *
     * @param m
     * @return holo::int32_t
     */
    holo::int32_t OutputGlobalCorrespondence(const PointCloudXYZIRRgbSt& m);

    /**
     * @brief output imu prediction callback
     */
    holo::int32_t OutputImuPredictionResultCallback(const vslam::Odometry& odo_m);

    /**
     * @brief save ground truth trajectory and front wheel angle if enable using ground truth odometry as estimated
     * result
     */
    void SaveGroundTruthTrajectoryAndFrontWheelAngle();

    /// @brief subscribed and published topics
    struct Topics
    {
        /// @brief subscribed image topic
        const std::vector<std::string> input_images;

        /// @brief subscribed obstacle list topic
        const std::string input_obstacle_list;

        /// @brief subscribed point feature list topic.
        const std::string input_point_feature_list;

        /// @brief subscribed imu topic
        const std::string input_imu;

        /// @brief subscribed chassis_state topic
        const std::string input_chassis_state;

        /// @brief subscribed gps position topic
        const std::string input_gps_position;

        /// @brief subscribed gravity_aligned_odometry topic
        const std::string input_gravity_aligned_odometry;

        /// @brief subscribed ground_truth_odometry topic.
        const std::string input_ground_truth_odometry;

        /// @brief published vslam_odometry topic. in vslam frame, ~10Hz
        const std::string output_vslam_odometry;

        /// @brief published imu_prediction_odometry topic. in vslam frame, 100Hz
        const std::string output_imu_prediction_odometry;

        /// @brief published 2d vehicle pose topic.
        const std::string output_hpa_local;

        /// @brief published local_feature_map topic.
        /// @details local_feature_map is all landmarks retained in curernt sliding window state
        const std::string output_local_feature_map;

        /// @brief published global_feature_map topic.
        /// @details in mapping mode, global_feature_map means all landmarks accumulated in the whole history sliding
        /// window state. in localization mode, global_feature_map means the prebuilt map.
        const std::string output_global_feature_map;

        /// @brief published global_correspondence topic.
        /// @details global_correspondence is the associated global mappoint with prebuilt map
        const std::string output_global_correspondence;

        /// @brief constructor
        Topics(const std::vector<std::string>& _input_images = {}, const std::string& _input_obstacle_list = {},
               const std::string& _input_point_feature_list = {}, const std::string& _input_imu = {},
               const std::string& _input_chassis_state = {}, const std::string& _input_gps_position = {},
               const std::string& _input_gravity_aligned_odometry = {},
               const std::string& _input_ground_truth_odometry = {}, const std::string& _output_vslam_odometry = {},
               const std::string& _output_imu_prediction_odometry = {}, const std::string& _output_hpa_local = {},
               const std::string& _output_local_feature_map = {}, const std::string& _output_global_feature_map = {},
               const std::string& _output_global_correspondence = {})
          : input_images(_input_images)
          , input_obstacle_list(_input_obstacle_list)
          , input_point_feature_list(_input_point_feature_list)
          , input_imu(_input_imu)
          , input_chassis_state(_input_chassis_state)
          , input_gps_position(_input_gps_position)
          , input_gravity_aligned_odometry(_input_gravity_aligned_odometry)
          , input_ground_truth_odometry(_input_ground_truth_odometry)
          , output_vslam_odometry(_output_vslam_odometry)
          , output_imu_prediction_odometry(_output_imu_prediction_odometry)
          , output_hpa_local(_output_hpa_local)
          , output_local_feature_map(_output_local_feature_map)
          , output_global_feature_map(_output_global_feature_map)
          , output_global_correspondence(_output_global_correspondence)
        {
        }

        /// @brief output stream
        friend std::ostream& operator<<(std::ostream& os, const Topics& topics)
        {
            os << "Topics:";

            if (!topics.input_images.empty())
            {
                os << "\n input_images:";

                for (const auto& image_topic : topics.input_images)
                {
                    os << "\n  " << image_topic;
                }
            }

            os << "\n input_point_feature_list = " << topics.input_point_feature_list
               << "\n input_imu = " << topics.input_imu << "\n input_chassis_state = " << topics.input_chassis_state
               << "\n input_gps_position = " << topics.input_gps_position
               << "\n input_gravity_aligned_odometry = " << topics.input_gravity_aligned_odometry
               << "\n input_ground_truth_odometry = " << topics.input_ground_truth_odometry
               << "\n output_vslam_odometry = " << topics.output_vslam_odometry
               << "\n output_imu_prediction_odometry = " << topics.output_imu_prediction_odometry
               << "\n output_hpa_local = " << topics.output_hpa_local
               << "\n output_local_feature_map = " << topics.output_local_feature_map
               << "\n output_global_feature_map = " << topics.output_global_feature_map
               << "\n output_global_correspondence = " << topics.output_global_correspondence << std::endl;
            return os;
        }

        /// @brief load from yaml
        static Topics LoadFromYaml(const holo::yaml::Node& node)
        {
            const std::vector<std::string> input_images =
                node["input_images"].as<std::vector<std::string>>(std::vector<std::string>{});
            const std::string input_obstacle_list            = node["input_obstacle_list"].as<std::string>();
            const std::string input_point_feature_list       = node["input_point_feature_list"].as<std::string>();
            const std::string input_imu                      = node["input_imu"].as<std::string>();
            const std::string input_chassis_state            = node["input_chassis_state"].as<std::string>();
            const std::string input_gps_position             = node["input_gps_position"].as<std::string>();
            const std::string input_gravity_aligned_odometry = node["input_gravity_aligned_odometry"].as<std::string>();
            const std::string input_ground_truth_odometry    = node["input_ground_truth_odometry"].as<std::string>();
            const std::string output_vslam_odometry          = node["output_vslam_odometry"].as<std::string>();
            const std::string output_imu_prediction_odometry = node["output_imu_prediction_odometry"].as<std::string>();
            const std::string output_hpa_local               = node["output_hpa_local"].as<std::string>();
            const std::string output_local_feature_map       = node["output_local_feature_map"].as<std::string>();
            const std::string output_global_feature_map      = node["output_global_feature_map"].as<std::string>();
            const std::string output_global_correspondence   = node["output_global_correspondence"].as<std::string>();

            return Topics(input_images, input_obstacle_list, input_point_feature_list, input_imu, input_chassis_state,
                          input_gps_position, input_gravity_aligned_odometry, input_ground_truth_odometry,
                          output_vslam_odometry, output_imu_prediction_odometry, output_hpa_local,
                          output_local_feature_map, output_global_feature_map, output_global_correspondence);
        }
    };

    /// @brief cmw reader and writer wrapper
    struct CmwReadersWriters
    {
        /// @brief cmw reader
        std::vector<BusType::ReaderType<holo::uint32_t>> images_reader;
        BusType::ReaderType<vslam::ObstaclePtrList>      obstacle_list_reader;
        BusType::ReaderType<PointFeaturePtrList, BusType::DefaultConversionTraitsType<PointFeaturePtrList>>
                                                     point_feature_list_reader;
        BusType::ReaderType<holo::common::Imud>      imu_reader;
        BusType::ReaderType<vslam::ChassisState>     chassis_state_reader;
        BusType::ReaderType<vslam::GnssPosition>     gps_position_reader;
        BusType::ReaderType<holo::common::Odometryd> gravity_aligned_odometry_reader;
        BusType::ReaderType<holo::common::Odometryd> ground_truth_odometry_reader;

        /// @brief cmw writer
        BusType::WriterType<holo::common::Odometryd> vslam_odometry_writer;
        BusType::WriterType<holo::common::Odometryd> imu_prediction_odometry_writer;
        BusType::WriterType<PointCloudXYZIRRgbSt>    local_feature_map_writer;
        BusType::WriterType<PointCloudXYZIRRgbSt>    global_feature_map_writer;
        BusType::WriterType<PointCloudXYZIRRgbSt>    global_correspondence_writer;

        BusType::WriterType<VehiclePose, BusType::DefaultConversionTraitsType<VehiclePose>> vehicle_pose_2d_writer;
    };

    /// @brief log files
    struct LoggingFiles
    {
        std::string gts;         ///< ground truth odometry output file
        std::string ess;         ///< estimated vslam odometry output file
        std::string bias;        ///< estimated vslam bias output file
        std::string imu_ess;     ///< imu prediction odometry output file
        std::string output_dir;  ///< log file output directory

        LoggingFiles(const std::string& dir = ".")
          : gts(dir + "/gts.txt")
          , ess(dir + "/ess.txt")
          , bias(dir + "/bias.txt")
          , imu_ess(dir + "/imu_ess.txt")
          , output_dir(dir)
        {
            InitializeFile(gts);
            InitializeFile(ess);
            InitializeFile(bias);
            InitializeFile(imu_ess);
        }

        /// @brief output stream
        friend std::ostream& operator<<(std::ostream& os, const LoggingFiles& lfs)
        {
            os << "LoggingFiles:"
               << "\n gts = " << lfs.gts << "\n ess = " << lfs.ess << "\n bias = " << lfs.bias
               << "\n imu_ess = " << lfs.imu_ess << "\n output_dir" << lfs.output_dir << std::endl;
            return os;
        }

        /// @brief update log file name when vslam is reset
        void ReInitializeVSLAMFile(const std::string& file_name, const uint16_t count)
        {
            if (file_name == "ess")
            {
                ess = ReInitializeFile(file_name, count);
            }
            else if (file_name == "bias")
            {
                bias = ReInitializeFile(file_name, count);
            }
            else if (file_name == "imu_ess")
            {
                imu_ess = ReInitializeFile(file_name, count);
            }
            else
            {
                LOG(WARNING) << "LoggingFiles --- wrong file name!!! file name: " << file_name;
            }
        }

    private:
        /// @brief initialize file
        void InitializeFile(const std::string& file) const
        {
            if (boost::filesystem::exists(file))
            {
                boost::filesystem::remove(file);
            }
        }

        /// @brief re-initialize log file
        std::string ReInitializeFile(const std::string& file_name, const uint16_t count)
        {
            const std::string full_name = output_dir + "/" + file_name + std::to_string(count) + ".txt";
            InitializeFile(full_name);
            return full_name;
        }
    };

    /// @brief debugging parameters
    struct DebuggingParameters
    {
        /// @brief flag indicate whether use ground trurh odometry as estimated result
        bool use_ground_trurh_as_estimated;

        /// @brief flag indicate whether use ground trurh odometry as gravity_aligned odometry
        bool use_ground_trurh_as_gravity_aligned;

        /// @brief flag indicate whether logging out vslam estimated result to file
        bool enable_result_logging;

        /// @brief flag indicate whether pubish vslam estimated result to ros
        bool publish_vslam_result;

        /// @brief output more log information
        bool verbose;

        /// @brief constructor
        DebuggingParameters(const bool _use_ground_trurh_as_estimated       = false,
                            const bool _use_ground_trurh_as_gravity_aligned = false,
                            const bool _enable_result_logging = false, const bool _publish_vslam_result = false,
                            const bool _verbose = false)
          : use_ground_trurh_as_estimated(_use_ground_trurh_as_estimated)
          , use_ground_trurh_as_gravity_aligned(_use_ground_trurh_as_gravity_aligned)
          , enable_result_logging(_enable_result_logging)
          , publish_vslam_result(_publish_vslam_result)
          , verbose(_verbose)
        {
        }

        /// @brief output stream
        friend std::ostream& operator<<(std::ostream& os, const DebuggingParameters& dp)
        {
            os << "DebuggingParameters:"
               << "\n use_ground_trurh_as_estimated = " << dp.use_ground_trurh_as_estimated
               << "\n use_ground_trurh_as_gravity_aligned = " << dp.use_ground_trurh_as_gravity_aligned
               << "\n enable_result_logging = " << dp.enable_result_logging
               << "\n publish vslam result = " << dp.publish_vslam_result << "\n verbose = " << dp.verbose << std::endl;
            return os;
        }

        /// @brief load from yaml
        static DebuggingParameters LoadFromYaml(const holo::yaml::Node& node)
        {
            const bool use_ground_trurh_as_estimated = node["use_ground_trurh_as_estimated"].as<bool>(false);
            const bool use_ground_trurh_as_gravity_aligned =
                node["use_ground_trurh_as_gravity_aligned"].as<bool>(false);
            const bool enable_result_logging = node["enable_result_logging"].as<bool>(false);
            const bool publish_vslam_result  = node["publish_vslam_result"].as<bool>(false);
            const bool verbose               = node["verbose"].as<bool>(false);

            return DebuggingParameters(use_ground_trurh_as_estimated, use_ground_trurh_as_gravity_aligned,
                                       enable_result_logging, publish_vslam_result, verbose);
        }
    };

    /// @brief holo cmw
    BusType bus_;

    /// @brief cmw readers and writers
    CmwReadersWriters cmw_readers_writers_;

    /// @brief the image ipc client which helps load image
    ///        from driver or other image source
    std::vector<std::shared_ptr<holo::sensors::camera::ImageIpc>> image_ipcs_;

    /// @brief vslam algorithm
    std::shared_ptr<vslam::VSLAMBase> vslam_;

    /// @brief visualizer
    std::shared_ptr<vslam::Visualizer> visualizer_;

    ///< extrinsic novatel in body frame(default 90 degree)
    Pose3 E_bn_;

    /// @brief outputs files
    LoggingFiles logging_files_;

    /// @brief debugging parameters
    DebuggingParameters debugging_parameters_;

    /// @brief chassis state buffer, which will be saved to file in mapping mode
    std::mutex                           chassis_state_buffer_mutex_;
    boost::circular_buffer<ChassisState> chassis_state_buffer_;

    /// @brief ground truth odometry buffer, which will be saved to file in mapping mode
    boost::circular_buffer<vslam::Odometry> ground_truth_buffer_;

    /// @brief vslam mode
    std::string mode_;

    /// @brief directory to save learned path and front whell angle
    std::string directory_;
};  // VSLAMCmw

}  // namespace holo_cmw

#endif  // HOLO_CMW_APPS_LOCALIZATION_VISION_VSLAM_VSLAM_CMW_H_
