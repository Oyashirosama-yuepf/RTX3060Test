/*!
 * \brief vslam base implementation in vslam
 * \author Yanwei. Du duyanwei@holomatic.com
 * \author Feng. Li lifeng@holomatic.com
 * \date Mar-18-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo/localization/vision/vslam/vslam_base.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VSLAMBase::SourceCheckerParameters VSLAMBase::SourceCheckerParameters::LoadFromYaml(const holo::yaml::Node& node)
{
    const holo::yaml::Node imu_sc_node   = node["imu_sc_params"];
    const auto             imu_sc_params = SourceCheckerImu::Parameters::LoadYaml(imu_sc_node);

    const holo::yaml::Node chassis_state_sc_node = node["chassis_state_sc_params"];
    const auto chassis_state_sc_params = SourceCheckerChassisState::Parameters::LoadYaml(chassis_state_sc_node);

    const holo::yaml::Node point_feature_list_sc_node = node["feature_point_sc_params"];
    const auto             point_feature_list_sc_params =
        SourceCheckerPointFeatureList::Parameters::LoadYaml(point_feature_list_sc_node);

    const holo::yaml::Node obstacle_list_sc_node = node["obstacle_list_sc_params"];
    const auto obstacle_list_sc_params = SourceCheckerObstaclePtrList::Parameters::LoadYaml(obstacle_list_sc_node);

    const holo::yaml::Node parking_slot_frame_sc_node = node["parking_slot_frame_sc_params"];
    const auto             parking_slot_frame_sc_params =
        SourceCheckerParkingSlotFrame::Parameters::LoadYaml(parking_slot_frame_sc_node);

    return SourceCheckerParameters(imu_sc_params, chassis_state_sc_params, point_feature_list_sc_params,
                                   obstacle_list_sc_params, parking_slot_frame_sc_params);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VSLAMBase::ErrorCodeParameters VSLAMBase::ErrorCodeParameters::LoadFromYaml(const holo::yaml::Node& node)
{
    const uint32_t  feature_point_num_few_threshold = node["feature_point_num_few_threshold"].as<uint32_t>(10U);
    const float32_t feature_few_tolerance           = node["feature_few_tolerance"].as<float32_t>(20.0);
    const float32_t front_camera_frequency_low_threshold =
        node["front_camera_frequency_low_threshold"].as<float32_t>(1.0);
    const float32_t front_camera_frequency_low_tolerance =
        node["front_camera_frequency_low_tolerance"].as<float32_t>(10.0);
    const float32_t imu_frequency_low_threshold = node["imu_frequency_low_threshold"].as<float32_t>(90.0);
    const float32_t imu_frequency_low_tolerance = node["imu_frequency_low_tolerance"].as<float32_t>(10.0);
    const float32_t chassis_state_frequency_low_threshold =
        node["chassis_state_frequency_low_threshold"].as<float32_t>(90.0);
    const float32_t chassis_state_frequency_low_tolerance =
        node["chassis_state_frequency_low_tolerance"].as<float32_t>(10.0);
    const float32_t feature_point_frequency_low_threshold =
        node["feature_point_frequency_low_threshold"].as<float32_t>(3.5);
    const float32_t feature_point_frequency_low_tolerance =
        node["feature_point_frequency_low_tolerance"].as<float32_t>(10.0);
    const float32_t obstacle_frequency_low_threshold = node["obstacle_frequency_low_threshold"].as<float32_t>(1.0);
    const float32_t obstacle_frequency_low_tolerance = node["obstacle_frequency_low_tolerance"].as<float32_t>(10.0);
    const float32_t parking_slot_frequency_low_threshold =
        node["parking_slot_frequency_low_threshold"].as<float32_t>(1.0);
    const float32_t parking_slot_frequency_low_tolerance =
        node["parking_slot_frequency_low_tolerance"].as<float32_t>(10.0);
    const float32_t gnss_position_frequency_low_threshold =
        node["gnss_position_frequency_low_threshold"].as<float32_t>(1.0);
    const float32_t gnss_position_frequency_low_tolerance =
        node["gnss_position_frequency_low_tolerance"].as<float32_t>(10.0);
    const float32_t online_mapping_parking_overtime_threshold =
        node["online_mapping_parking_overtime_threshold"].as<float32_t>(180.0);
    const float32_t online_mapping_over_length_threshold =
        node["online_mapping_over_length_threshold"].as<float32_t>(200.0);
    const float32_t online_mapping_over_length_warning_L1_threshold =
        node["online_mapping_over_length_warning_L1_threshold"].as<float32_t>(150.0);
    const float32_t online_mapping_overtime_threshold = node["online_mapping_overtime_threshold"].as<float32_t>(300.0);
    const float32_t online_mapping_overtime_warning_threshold =
        node["online_mapping_overtime_warning_threshold"].as<float32_t>(200.0);
    const float32_t online_mapping_over_length_warning_L2_threshold =
        node["online_mapping_over_length_warning_L2_threshold"].as<float32_t>(180.0);
    const float32_t onine_mapping_turning_radius_small_threshold =
        node["onine_mapping_turning_radius_small_threshold"].as<float32_t>(0.18);
    const float32_t online_mapping_slope_large_threshold =
        node["online_mapping_slope_large_threshold"].as<float32_t>(0.15);

    return ErrorCodeParameters(
        feature_point_num_few_threshold, feature_few_tolerance, front_camera_frequency_low_threshold,
        front_camera_frequency_low_tolerance, imu_frequency_low_threshold, imu_frequency_low_tolerance,
        chassis_state_frequency_low_threshold, chassis_state_frequency_low_tolerance,
        feature_point_frequency_low_threshold, feature_point_frequency_low_tolerance, obstacle_frequency_low_threshold,
        obstacle_frequency_low_tolerance, parking_slot_frequency_low_threshold, parking_slot_frequency_low_tolerance,
        gnss_position_frequency_low_threshold, gnss_position_frequency_low_tolerance,
        online_mapping_parking_overtime_threshold, online_mapping_over_length_threshold,
        online_mapping_over_length_warning_L1_threshold, online_mapping_overtime_threshold,
        online_mapping_overtime_warning_threshold, online_mapping_over_length_warning_L2_threshold,
        onine_mapping_turning_radius_small_threshold, online_mapping_slope_large_threshold);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VSLAMBase::ErrorCodeParameters VSLAMBase::ErrorCodeParameters::Example()
{
    return ErrorCodeParameters(10, 20.0, 1.0, 10.0, 90.0, 10.0, 90.0, 10.0, 3.5, 10, 1.0, 10.0, 1.0, 10.0, 1.0, 10.0,
                               180.0, 200.0, 150.0, 300.0, 200.0, 180.0, 0.18, 0.15);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VSLAMBase::Parameters VSLAMBase::Parameters::LoadFromYaml(const holo::yaml::Node& node)
{
    // frequency
    const Scalar frequency = 10.0;

    /// @brief enable semantic model
    bool enable_semantic_mode = node["enable_semantic_mode"].as<bool>(false);

    /// @brief psd_fusion_time_interval
    Scalar psd_fusion_time_interval =
        node["psd_fusion_time_interval"].IsDefined() ? node["psd_fusion_time_interval"].as<Scalar>(1.0) : 0.1;

    // camera parameters
    const holo::yaml::Node camera_node   = node["camera_params"];
    const auto             camera_params = CameraParameters::LoadFromYaml(camera_node);

    // raw measurement preprocessor parameters
    const holo::yaml::Node                       rmpp_node = node["rmpp_params"];
    const RawMeasurementPreprocessor::Parameters rmpp_params =
        RawMeasurementPreprocessor::Parameters::LoadFromYaml(rmpp_node);

    // builder parameters
    const holo::yaml::Node         builder_node   = node["builder_params"];
    const GraphBuilder::Parameters builder_params = GraphBuilder::Parameters::LoadFromYaml(builder_node);

    // sliding window estimator parameters
    const holo::yaml::Node                   se_node   = node["se_params"];
    const SlidingWindowEstimator::Parameters se_params = SlidingWindowEstimator::Parameters::LoadFromYaml(se_node);

    // failure detection parameters
    const holo::yaml::Node             fd_node   = node["fd_params"];
    const FailureDetection::Parameters fd_params = FailureDetection::Parameters::LoadFromYaml(fd_node);

    // failure measurement manager vslam parameters
    const holo::yaml::Node                     mmv_node = node["mmv_params"];
    const MeasurementsManagerVSLAM::Parameters mmv_params =
        MeasurementsManagerVSLAM::Parameters::LoadFromYaml(mmv_node);

    // load source checker parameters
    std::string vslam_source_checker_file =
        holo::GetHoloConfigRootDirectory() + "/" + node["vslam_source_checker_params_file"].as<std::string>("");
    if (!boost::filesystem::exists(vslam_source_checker_file))
    {
        LOG(ERROR) << "Vslam Base --- failed to load vslam source checker parameters, invalid vslam source checker: \n"
                   << vslam_source_checker_file << "\n";
        throw std::runtime_error("Localization --- failed to load vslam sourece checker file");
    }
    const holo::yaml::Node        sc_node   = holo::yaml::LoadFile(vslam_source_checker_file);
    const SourceCheckerParameters sc_params = SourceCheckerParameters::LoadFromYaml(sc_node);

    // load error code parameters
    std::string vslam_error_code_params_file =
        holo::GetHoloConfigRootDirectory() + "/" + node["vslam_error_code_params_file"].as<std::string>("");
    if (!boost::filesystem::exists(vslam_error_code_params_file))
    {
        LOG(ERROR) << "Vslam Base --- failed to load vslam error code parameters, invalid vslam ec params file: \n"
                   << vslam_error_code_params_file << "\n";
        throw std::runtime_error("Localization --- failed to load vslam error params file");
    }
    const holo::yaml::Node    ec_node   = holo::yaml::LoadFile(vslam_error_code_params_file);
    const ErrorCodeParameters ec_params = ErrorCodeParameters::LoadFromYaml(ec_node);

    const bool enable_estimation_with_acc = node["enable_estimation_with_acc"].as<bool>(true);

    return Parameters(false, 10, frequency, enable_semantic_mode, psd_fusion_time_interval, camera_params, rmpp_params,
                      builder_params, se_params, fd_params, mmv_params, sc_params, ec_params,
                      enable_estimation_with_acc);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VSLAMBase::Parameters VSLAMBase::Parameters::Example()
{
    const Scalar frequency                = 10;
    const bool&  enable_semantic_mode     = false;
    const Scalar psd_fusion_time_interval = 1.0;

    SourceCheckerImu::Parameters imu_sc_params;

    SourceCheckerChassisState::Parameters chassis_state_sc_params;

    SourceCheckerPointFeatureList::Parameters point_feature_list_sc_params;

    SourceCheckerObstaclePtrList::Parameters obstacle_list_sc_params;

    SourceCheckerParkingSlotFrame::Parameters parking_slot_frame_sc_params;

    return Parameters(false, 10, frequency, enable_semantic_mode, psd_fusion_time_interval, CameraParameters::Example(),
                      RawMeasurementPreprocessor::Parameters::Example(), GraphBuilder::Parameters::Example(),
                      SlidingWindowEstimator::Parameters::Example(), FailureDetection::Parameters::Example(),
                      MeasurementsManagerVSLAM::Parameters::Example(),
                      SourceCheckerParameters(imu_sc_params, chassis_state_sc_params, point_feature_list_sc_params,
                                              obstacle_list_sc_params, parking_slot_frame_sc_params),
                      ErrorCodeParameters::Example());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VSLAMBase::VSLAMBase(const Parameters& parameters, const FeatureAssociator::Parameters& fa_params,
                     const Initializer::Parameters& initializer_params)
  : parameters_(parameters)
  , measurements_manager_(parameters_.mmv_params, parameters_.camera_params)
  , preprocessor_(parameters_.rmpp_params, parameters_.camera_params, fa_params)
  , initializer_(initializer_params, parameters_.camera_params)
  , estimator_(parameters_.se_params, parameters_.camera_params)
  , failure_detection_(parameters_.fd_params)
  , sliding_window_state_()
  , estimation_core_iteration_counter_(0)
  , vslam_result_callback_(nullptr)
  , visualization_callback_(nullptr)
  , reset_flags_()
  , sequence_counter_()
  , is_estimation_core_work_well_(false)
  , graph_builder_(std::make_shared<GraphBuilder>(parameters_.builder_params, parameters_.camera_params))
  , new_frame_id_(0)
  , last_raw_measurement_timestamp_(0, 0)
  , last_parking_slot_timestamp_(0, 0)
  , app_error_status_(std::make_shared<AppErrorStatus>())
  , chassis_state_source_checker_(nullptr)
  , imu_source_checker_(nullptr)
  , point_feature_list_source_checker_(nullptr)
  , obstacle_list_source_checker_(nullptr)
  , parking_slot_frame_source_checker_(nullptr)
  , gnss_position_source_checker_(nullptr)
  , enable_dr_mode_(false)
  , visualizer_(nullptr)
{
    estimator_.SetGraphBuilderPtr(graph_builder_);

    if (parameters_.sc_params.chassis_state_sc_params.enable_checker)
    {
        chassis_state_source_checker_ =
            std::make_shared<SourceCheckerChassisState>(parameters_.sc_params.chassis_state_sc_params, "chassis state");
    }
    if (parameters_.sc_params.imu_sc_params.enable_checker)
    {
        imu_source_checker_ = std::make_shared<SourceCheckerImu>(parameters_.sc_params.imu_sc_params, "imu");
    }
    if (parameters_.sc_params.point_feature_list_sc_params.enable_checker)
    {
        point_feature_list_source_checker_ = std::make_shared<SourceCheckerPointFeatureList>(
            parameters_.sc_params.point_feature_list_sc_params, "point feature list");
    }
    if (parameters_.sc_params.obstacle_list_sc_params.enable_checker)
    {
        obstacle_list_source_checker_ = std::make_shared<SourceCheckerObstaclePtrList>(
            parameters_.sc_params.obstacle_list_sc_params, "obstacle list");
    }
    if (parameters_.sc_params.parking_slot_frame_sc_params.enable_checker)
    {
        parking_slot_frame_source_checker_ = std::make_shared<SourceCheckerParkingSlotFrame>(
            parameters_.sc_params.parking_slot_frame_sc_params, "parking slot frame");
    }
    sliding_window_state_.enable_estimation_with_acc = parameters_.enable_estimation_with_acc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VSLAMBase::~VSLAMBase()
{
    app_error_status_ = nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VSLAMBase::Stop()
{
    // stop vslam thread
    Base::Stop();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t VSLAMBase::ProcessImage(const Image& measurement, const uint16_t camera_index)
{
    if (state_ < State::READY)
    {
        return 0;
    }

    measurements_manager_.AddMeasurement(measurement, camera_index);
    return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t VSLAMBase::ProcessPointFeaturePtrList(PointFeaturefList_ST* const measurement)
{
    if (state_ < State::READY)
    {
        return 0;
    }

    if (app_error_status_)
    {
        std::unique_lock<std::mutex>(app_error_status_mutex_);
        if (app_error_status_->feature_point_frequency_low)
        {
            LOG(ERROR) << "Vslam Base --- Point feature list frequency is low, please check data source.";
            return 0;
        }
        // static SourceCheckerResult point_feature_souce_checker_result;
        // point_feature_souce_checker_result = SourceChecker(point_feature_list_source_checker_, measurement,
        //                                                    parameters_.ec_params.feature_point_frequency_low_threshold,
        //                                                    parameters_.ec_params.feature_point_frequency_low_tolerance,
        //                                                    "feature point", point_feature_souce_checker_result);

        // if (point_feature_souce_checker_result.is_error)
        // {
        //     app_error_status_->feature_point_frequency_low = true;
        // }
    }

    measurements_manager_.AddMeasurement(measurement);
    return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t VSLAMBase::ProcessImu(const Imu& measurement)
{
    if (state_ < State::READY)
    {
        return 0;
    }

    if (app_error_status_)
    {
        std::unique_lock<std::mutex>(app_error_status_mutex_);
        if (app_error_status_->imu_frequency_low)
        {
            LOG(ERROR) << "Vslam Base --- Imu frequency is low, please check data source.";
            return 0;
        }
        static SourceCheckerResult imu_souce_checker_result;
        imu_souce_checker_result =
            SourceChecker(imu_source_checker_, measurement, parameters_.ec_params.imu_frequency_low_threshold,
                          parameters_.ec_params.imu_frequency_low_tolerance, "imu", imu_souce_checker_result);

        if (imu_souce_checker_result.is_error)
        {
            app_error_status_->imu_frequency_low = true;
        }
    }

    measurements_manager_.AddMeasurement(measurement);
    return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t VSLAMBase::ProcessChassisState(const ChassisState& measurement)
{
    if (state_ < State::READY)
    {
        return 0;
    }

    if (app_error_status_)
    {
        std::unique_lock<std::mutex>(app_error_status_mutex_);
        if (app_error_status_->chassis_state_frequency_low)
        {
            LOG(ERROR) << "Vslam Base --- chassis state frequency is low, please check data source.";
            return 0;
        }

        static SourceCheckerResult chassis_souce_checker_result;
        chassis_souce_checker_result = SourceChecker(
            chassis_state_source_checker_, measurement, parameters_.ec_params.chassis_state_frequency_low_threshold,
            parameters_.ec_params.chassis_state_frequency_low_tolerance, "chassis state", chassis_souce_checker_result);

        if (chassis_souce_checker_result.is_error)
        {
            app_error_status_->chassis_state_frequency_low = true;
        }

        // over speed checking
        if (measurement.GetVehicleSpeed() > 20)
        {
            app_error_status_->online_mapping_over_speed_20 = true;
            LOG(ERROR) << "Vslam Base --- Vehicle speed is over the limit(20). the current speed is: "
                       << measurement.GetVehicleSpeed() << "! vslam will exit！";
        }
        else if (measurement.GetVehicleSpeed() > 15)
        {
            app_error_status_->online_mapping_over_speed_15 = true;
            LOG(WARNING) << "Vslam Base --- The vehicle speed is about to exceed the limit(20), the current speed is:"
                         << measurement.GetVehicleSpeed() << "! Please slow down to within 15.";
        }
    }

    measurements_manager_.AddMeasurement(measurement);
    return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t VSLAMBase::ProcessGnssPosition(const GnssPosition& measurement)
{
    if (state_ < State::READY)
    {
        return 0;
    }

    if (app_error_status_)
    {
        std::unique_lock<std::mutex>(app_error_status_mutex_);
        if (app_error_status_->gnss_position_frequency_low)
        {
            LOG(ERROR) << "Vslam Base --- Gnss Position frequency is low, please check data source.";
            return 0;
        }

        static SourceCheckerResult gnss_souce_checker_result;
        gnss_souce_checker_result = SourceChecker(
            gnss_position_source_checker_, measurement, parameters_.ec_params.gnss_position_frequency_low_threshold,
            parameters_.ec_params.gnss_position_frequency_low_tolerance, "gnss position", gnss_souce_checker_result);

        if (gnss_souce_checker_result.is_error)
        {
            app_error_status_->gnss_position_frequency_low = true;
        }
    }

    measurements_manager_.AddMeasurement(measurement);
    return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t VSLAMBase::ProcessGravityAlignedOdometry(const Odometry& measurement)
{
    if (state_ < State::READY)
    {
        return 0;
    }

    measurements_manager_.AddGravityAlignedOdometry(measurement);
    return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t VSLAMBase::ProcessGroundTruthOdometry(const Odometry& measurement)
{
    if (state_ < State::READY)
    {
        return 0;
    }

    measurements_manager_.AddGroundTruth(measurement);
    return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t VSLAMBase::ProcessObstaclePtrList(const ObstaclePtrList& measurement)
{
    if (state_ < State::READY)
    {
        return 0;
    }

    if (app_error_status_)
    {
        std::unique_lock<std::mutex>(app_error_status_mutex_);
        if (app_error_status_->obstacle_frequency_low)
        {
            LOG(ERROR) << "Vslam Base --- obstacle list frequency is low, please check data source.";
            return 0;
        }

        static SourceCheckerResult obstacle_souce_checker_result;
        obstacle_souce_checker_result = SourceChecker(
            obstacle_list_source_checker_, measurement, parameters_.ec_params.obstacle_frequency_low_threshold,
            parameters_.ec_params.obstacle_frequency_low_tolerance, "obstacle list", obstacle_souce_checker_result);

        if (obstacle_souce_checker_result.is_error)
        {
            app_error_status_->obstacle_frequency_low = true;
        }
    }

    measurements_manager_.AddMeasurement(measurement);
    return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t VSLAMBase::ProcessParkingSlotFrame(const ParkingSlotFrameType& measurement)
{
    if (state_ < State::READY)
    {
        return 0;
    }

    if (app_error_status_)
    {
        std::unique_lock<std::mutex>(app_error_status_mutex_);
        if (app_error_status_->parking_slot_frequency_low)
        {
            LOG(ERROR) << "Vslam Base --- Parking slot frame frequency is low, please check data source.";
            return 0;
        }

        static SourceCheckerResult parking_slot_souce_checker_result;
        parking_slot_souce_checker_result = SourceChecker(parking_slot_frame_source_checker_, measurement,
                                                          parameters_.ec_params.parking_slot_frequency_low_threshold,
                                                          parameters_.ec_params.parking_slot_frequency_low_tolerance,
                                                          "parking slot", parking_slot_souce_checker_result);

        if (parking_slot_souce_checker_result.is_error)
        {
            app_error_status_->parking_slot_frequency_low = true;
        }
    }

    measurements_manager_.AddMeasurement(measurement);
    return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t VSLAMBase::SetVslamResultCallback(const VslamResultCallback& cb)
{
    vslam_result_callback_ = cb;
    return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t VSLAMBase::SetImuPredictionResultCallback(const ImuPredictionResultCallback& cb)
{
    imu_prediction_result_callback_ = cb;
    return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t VSLAMBase::SetVisualizationCallback(const VisualizationCallback& cb)
{
    visualization_callback_ = cb;
    return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t VSLAMBase::SetOutputLocalFeatureMapCallback(const OutputPointCloudCallback& cb)
{
    output_local_feature_map_callback_ = cb;
    return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t VSLAMBase::SetOutputGlobalFeatureMapCallback(const OutputPointCloudCallback& cb)
{
    output_global_feature_map_callback_ = cb;
    return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t VSLAMBase::SetOutputGlobalCorrespondenceCallback(const OutputPointCloudCallback& cb)
{
    output_global_correspondence_callback_ = cb;
    return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t VSLAMBase::SetOutputGlobalParkingSlotFrameCallback(const OutputParkingSlotFrameCallback& cb)
{
    output_global_parking_slot_frame_callback_ = cb;
    return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VSLAMBase::SetDrMode()
{
    enable_dr_mode_ = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool VSLAMBase::checkPreCondition()
{
    bool is_parking_slot_optional = (parameters_.enable_semantic_mode == false);

    return measurements_manager_.IsRawMeasurementAvailable((bool)visualization_callback_, enable_dr_mode_,
                                                           is_parking_slot_optional);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool VSLAMBase::postProcess()
{
    return Base::postProcess();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool VSLAMBase::IsMeasurementConsistent(const Timestamp& old_timestamp, const RawMeasurement& new_raw_measurement) const
{
    // define camera driver parameters
    const Scalar camera_frequency          = 10.0;  // hz
    const Scalar image_maximum_drop_number = 1.0;
    const Scalar imu_frequency             = 100.0;  // hz

    // get timestamp from new_raw_measurement
    const Timestamp new_timestamp       = new_raw_measurement.newest_timestamp;
    const Timestamp first_imu_timestamp = new_raw_measurement.imus.front().GetTimestamp();
    const Timestamp last_imu_timestamp  = new_raw_measurement.imus.back().GetTimestamp();

    // check image timestamp
    // @todo this part works the same as in MeasurementManagerVslam, please think
    // of a way to unify it. (duyanwei@holomatic.com)
    {
        const Scalar time_diff     = (new_timestamp - old_timestamp).ToSec();
        const Scalar min_tolerance = 1.0 / camera_frequency * 1.5;
        const Scalar max_tolerance = 1.0 / camera_frequency * (image_maximum_drop_number + 1.5);

        if (time_diff <= 0 || time_diff >= min_tolerance)
        {
            LOG(WARNING) << "VSLAMBase --- image measurement NOT "
                            "consistent!\n"
                         << "old image time = " << old_timestamp.ToString()
                         << ", new image time = " << new_timestamp.ToString();

            if (time_diff <= 0 || time_diff >= max_tolerance)  // reset system
            {
                return false;
            }
        }
    }

    // check imu timestamp and number
    {
        const Scalar  td_1 = std::fabs((new_timestamp - last_imu_timestamp).ToSec());
        const Scalar  td_2 = std::fabs((old_timestamp - first_imu_timestamp).ToSec());
        const int32_t expected_imu_num =
            static_cast<int32_t>((last_imu_timestamp - first_imu_timestamp).ToSec() * imu_frequency);

        if (td_1 >= Epsilon::value || td_2 >= Epsilon::value)
        {
            LOG(ERROR) << "VSLAMBase --- imu measurement NOT "
                          "consistent!\n"
                       << "old image time = " << old_timestamp.ToString()
                       << ", new image time = " << new_timestamp.ToString()
                       << ", first imu time = " << first_imu_timestamp.ToString()
                       << ", last imu time = " << last_imu_timestamp.ToString()
                       << ", expected imu number = " << expected_imu_num
                       << ", actual imu number = " << new_raw_measurement.imus.size();
            return false;
        }
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
boost::optional<Pose3> VSLAMBase::PredictVehiclePoseAtBeginning(MeasurementsManagerVSLAM& measurements_manager) const
{
    // trying to get prior vehicle pose
    boost::optional<Pose3> prior_vehicle_pose = boost::none;

    if (!sliding_window_state_.IsInitialized())
    {
        // system was not initialized. try to get prior pose from start point of learned HPP path if exist; otherwise
        // we should trying to get prior vehicle pose from a gravity aligned odometry
        if (!learned_path_.empty())
        {
            prior_vehicle_pose = learned_path_.at(0).GetPose();
        }
        else
        {
            Timestamp timestamp;

            // 1. get oldest image timestamp
            if (!measurements_manager.GetNewestRawMeasurementTimestamp(timestamp))
            {
                return boost::none;
            }

            // 2. get gravity aligned odometry at specific timestamp 't'
            Odometry gravity_aligned_odo;

            if (!measurements_manager.GetNearestGroundTruth(timestamp, gravity_aligned_odo))
            {
                return boost::none;
            }
            prior_vehicle_pose = gravity_aligned_odo.GetPose();
        }
    }
    else
    {
        // system is running, get current prior pose from sliding window state.
        /// here the prior_vehicle_pose will be used to query sub map around current vehicle pose. so the
        /// NewestVehicleState.Pose() is OK.
        prior_vehicle_pose = sliding_window_state_.NewestVehicleState().Pose();
    }

    return prior_vehicle_pose;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VSLAMBase::run()
{
    is_estimation_core_work_well_ = false;

    // if VSLAM should be reset, do nothing in this function and wait Reset() is called by the other thread
    if (reset_flags_)
    {
        LOG(INFO) << "VSLAMBase --- waiting for system resetting.\n";
        return;
    }

    LOG(INFO) << "Start iteration = " << estimation_core_iteration_counter_;

    Timestamp last_sliding_window_state_timestamp = sliding_window_state_.GetTimestamp();
    timer_.Tic();

    // create step timer for time monitor of each step
    TicTocTimer timer_step;
    timer_step.Tic();

    // get raw measurement
    if (enable_dr_mode_)
    {
        if (!measurements_manager_.GetDrRawMeasurement(last_raw_measurement_timestamp_, new_raw_measurements_))
        {
            LOG(INFO) << "VSLAMBase --- could not get raw measurements.\n";
            return;
        }
    }
    else if (parameters_.enable_semantic_mode)
    {
        if (!measurements_manager_.GetSemanticRawMeasurement(last_raw_measurement_timestamp_, new_raw_measurements_))
        {
            LOG(INFO) << "VSLAMBase --- could not get raw measurements.\n";
            return;
        }
    }
    else
    {
        if (!measurements_manager_.GetRawMeasurement(last_raw_measurement_timestamp_, boost::none,
                                                     new_raw_measurements_))
        {
            LOG(INFO) << "VSLAMBase --- could not get raw measurements.\n";
            return;
        }
    }

    // update last timestamp
    last_raw_measurement_timestamp_ = new_raw_measurements_.newest_timestamp;
    LOG(INFO) << "It takes " << 1e3 * timer_step.Elapsed() << "ms to get raw measurement";

    // @todo(Feng. Li. 2019-12-24) there are some bugs for first three image. so we temporary drop it before fix this
    // issue.
    if (new_raw_measurements_.imus.empty())
    {
        LOG(INFO) << "VSLAMBase --- get raw measurements, but imu not included\n";
        return;
    }

    // propagate state with estimator
    bool is_estimator_running_good = false;

    if (!sliding_window_state_.IsInitialized())
    {
        std::vector<Features> new_features =
            preprocessor_.ConvertPointFeatures(new_raw_measurements_.multi_point_feature_list,
                                               new_raw_measurements_.multi_obstacle_list, new_raw_measurements_.images);
        RawMeasurement new_rm = new_raw_measurements_;

        // predicted vehicle pose. it will be used to query local map
        const auto prior_vehicle_pose = PredictVehiclePoseAtBeginning(measurements_manager_);

        if (prior_vehicle_pose)
        {
            new_rm.visible_map = measurements_manager_.QueryMap(*prior_vehicle_pose);
        }

        new_rm.imus = preprocessor_.ConvertImuMeasurements(new_raw_measurements_.imus, parameters_.rmpp_params.T_bi);
        const auto vehicle_state = initializer_.Run(new_rm, new_features, prior_vehicle_pose);

        {
            std::unique_lock<std::mutex>(app_error_status_mutex_);
            app_error_status_->localization_init_failed = (vehicle_state == boost::none);
        }

        if (!vehicle_state)
        {
            LOG(INFO) << "VSLAMBase --- failed to initialize system.\n";
            return;
        }

        // build initial factor measurement
        LOG(INFO) << "VSLAMBase --- start preprocessor initialize. \n";
        const auto result = preprocessor_.Initialize(*vehicle_state, new_frame_id_, new_raw_measurements_);
        LOG(INFO) << "VSLAMBase --- end preprocessor initialize. \n";
        new_corrected_measurements_ = result.first;
        new_factor_measurements_    = result.second;

        // call Initialize() at the beginning
        LOG(INFO) << "VSLAMBase --- start estimator initialize. \n";
        is_estimator_running_good = estimator_.Initialize(sliding_window_state_, result.second,
                                                          new_raw_measurements_.newest_timestamp, new_frame_id_);
        LOG(INFO) << "VSLAMBase --- end estimator initialize. \n";
    }
    else
    {
        Timestamp last_timestamp    = last_sliding_window_state_timestamp;
        Timestamp current_timestamp = new_raw_measurements_.newest_timestamp;
        uint16_t  pim_num           = 1;
        if (parameters_.do_imu_preintegration_with_fixed_frequency)
        {
            pim_num = std::ceil((current_timestamp - last_timestamp).ToSec() * parameters_.preintegration_frequency);
        }

        for (uint16_t i = 0; i < pim_num; i++)
        {
            RawMeasurement            new_rm;
            std::vector<Imu>          imus;
            std::vector<ChassisState> chassis_states;
            Timestamp                 new_timestamp;

            if (i == (pim_num - 1) || (new_raw_measurements_.newest_timestamp.ToSec() - last_timestamp.ToSec()) < 0.15)
            {
                new_timestamp                   = new_raw_measurements_.newest_timestamp;
                new_rm.newest_timestamp         = new_timestamp;
                new_rm.optional_odometry        = new_raw_measurements_.optional_odometry;
                new_rm.images                   = new_raw_measurements_.images;
                new_rm.multi_point_feature_list = new_raw_measurements_.multi_point_feature_list;

                if (new_factor_measurements_.mpm.size() < parameters_.minimum_inlier_correspondence_num)
                {
                    // if so, we need associating the prebuilt map again.
                    const auto prior_vehicle_pose = PredictVehiclePoseAtBeginning(measurements_manager_);

                    if (prior_vehicle_pose)
                    {
                        new_rm.visible_map      = measurements_manager_.QueryMap(*prior_vehicle_pose);
                        new_rm.visible_slot_map = measurements_manager_.QuerySlotMap(*prior_vehicle_pose);
                    }
                }
            }
            else
            {
                static holo::Duration duration(1.0 / parameters_.preintegration_frequency);
                new_timestamp           = last_timestamp + duration;
                new_rm.newest_timestamp = new_timestamp;
            }

#ifdef HOLO_VISUALIZE_WITH_PANGOLIN
            const auto prior_vehicle_pose = PredictVehiclePoseAtBeginning(measurements_manager_);

            if (prior_vehicle_pose)
            {
                new_raw_measurements_.visible_map = measurements_manager_.QueryMap(*prior_vehicle_pose);
            }
#endif

            // add parking_slot_frame to new_rm when the interval between two parking_slot_frames is more than
            // psd_fusion_time_interval
            if ((new_raw_measurements_.newest_timestamp.ToSec() - last_parking_slot_timestamp_.ToSec()) >
                parameters_.psd_fusion_time_interval)
            {
                new_rm.optional_parking_slot_frame = new_raw_measurements_.optional_parking_slot_frame;
                last_parking_slot_timestamp_       = new_raw_measurements_.newest_timestamp;
            }

            if (!measurements_manager_.GetImuMeasurements(last_timestamp, new_timestamp, imus))
            {
                LOG(ERROR) << "VslamBase --- failed to get imus chain !!!"
                           << "\n last timestamp: " << last_timestamp.ToString()
                           << "\n new_timestamp: " << new_timestamp.ToString();
                throw std::runtime_error("VslamBase --- failed to get imus chain");
            }

            if (!measurements_manager_.GetChassisStatesMeasurements(last_timestamp, new_timestamp, chassis_states))
            {
                LOG(ERROR) << "VslamBase --- failed to get chassis states chain"
                           << "\n last timestamp: " << last_timestamp.ToString()
                           << "\n new_timestamp: " << new_timestamp.ToString();
                throw std::runtime_error("VslamBase --- failed to get chassis states chain");
            }
            new_rm.imus           = imus;
            new_rm.chassis_states = chassis_states;

            // update frame id
            /// @todo(lifeng@holomatic.com) new_frame_id_ may not only plus one in
            /// future if we add node to factor graph with fixed frequency.
            new_frame_id_++;

            // logging measurement consistency information
            IsMeasurementConsistent(sliding_window_state_.GetTimestamp(), new_rm);

            // raw measurement preprocessor
            LOG(INFO) << "START raw measurement preprocess ...\n";
            timer_step.Tic();
            const auto result           = preprocessor_.Run(sliding_window_state_, new_frame_id_, new_rm);
            new_corrected_measurements_ = result.first;
            new_factor_measurements_    = result.second;
            LOG(INFO) << "Done raw measurement preprocess, takes " << 1e3 * timer_step.Elapsed() << " ms";

            // check if relocalization msg is available
            if (!reloc_msg_.mpm.empty())
            {
                LOG(INFO) << "VSLAMBase --- Get " << reloc_msg_.mpm.size() << "mpms from relocalization  thread.\n ";
                LOG(INFO) << " VSLAMBase--- lastest frame id in vslam thread : " << new_frame_id_
                          << ", lastest frame id in relocalization thread: " << reloc_msg_.query_frame_id << "\n";
                if (sliding_window_state_.values.exists(X(reloc_msg_.query_frame_id)))
                {
                    new_factor_measurements_.mpm.reserve(reloc_msg_.mpm.size() + new_factor_measurements_.mpm.size());
                    std::copy(reloc_msg_.mpm.begin(), reloc_msg_.mpm.end(),
                              std::back_inserter(new_factor_measurements_.mpm));
                    reloc_msg_.mpm.clear();
                }
                else
                {
                    LOG(ERROR)
                        << "VSLAMBase --- result of relocalization thread can NOT be added to the sliding window "
                           "for time delay reason.\n";
                }
            }

            // call Run(...) after initialization
            LOG(INFO) << "START sliding window estimation ...\n";
            timer_step.Tic();

            is_estimator_running_good =
                estimator_.Run(sliding_window_state_, new_factor_measurements_, new_rm.newest_timestamp, new_frame_id_);

            LOG(INFO) << "Done sliding window estimation, takes " << 1e3 * timer_step.Elapsed() << " ms";

            last_timestamp = sliding_window_state_.GetTimestamp();
            if (last_timestamp == new_raw_measurements_.newest_timestamp)
            {
                break;
            }
        }
    }
    new_factor_measurements_.predicted_values = sliding_window_state_.compensated_values;

    // check exception and trajectory jump to reset VSLAM
    // when exception is catchend in SlidingWindowEstimator the is_estimator_running_good will be false
    if (!is_estimator_running_good)
    {
        reset_flags_.is_exception = true;
        LOG(INFO) << "VSLAMBase --- exception from gtsam catched. reset system!\n";
        return;
    }

    // set reset_flags_.is_trajectory_jump = true when Failure case is detected check relative translation along x
    // and y axis, yaw and velocity with the updated SlidingWindowState
    if (sliding_window_state_.IsInitialized() &&
        failure_detection_.Run(sliding_window_state_, last_sliding_window_state_timestamp, parameters_.frequency))
    {
        reset_flags_.is_trajectory_jump = true;
        LOG(INFO) << "VSLAMBase --- trajectory jump detected. reset system!\n";
        return;
    }

    is_estimation_core_work_well_ = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VSLAMBase::PublishVslamResult(const SlidingWindowState& state, const uint64_t sequence_counter) const
{
    if (!vslam_result_callback_)
    {
        return;
    }

    const VehicleState vehicle_state = state.NewestVehicleState();
    const Timestamp    current_time  = state.GetTimestamp();

    const Odometry vslam_odo = VehicleStateToOdometry(vehicle_state, current_time, sequence_counter);

    // result callback
    vslam_result_callback_(vslam_odo, vehicle_state.bias);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VSLAMBase::VisualizeVslamResult(const Visualizer::VisualizerStates& visualizer_states) const
{
    if (visualization_callback_)
    {
        visualization_callback_(visualizer_states);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Odometry VSLAMBase::VehicleStateToOdometry(const VehicleState& vehicle_state, const Timestamp& current_time,
                                           const uint64_t sequence_counter) const
{
    Odometry est_odo;  // estimated vslam odometry in vslam map frame
    est_odo.SetCoordinate(common::Coordinate(common::Coordinate::UNKNOWN));
    est_odo.SetTimestamp(current_time);
    est_odo.SetChildCoordinate(common::Coordinate(common::Coordinate::BODY));
    est_odo.SetPosePrecision(Odometry::Precision::HIGH);

    /// @note tell other module vio has been reset
    est_odo.SetStatus(sequence_counter == 0u ? Odometry::Status::SOLUTIONNOGOOD : Odometry::Status::ALLGOOD);

    est_odo.SetSource(Odometry::Source::VISION);
    est_odo.SetPose(vehicle_state.Pose());

    Vector6 velocity_m;
    velocity_m.SetHead(vehicle_state.Velocity());
    est_odo.SetVelocity(velocity_m);

    return est_odo;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PointCloudXYZIRRgbSt VSLAMBase::ConvertToPointCloud(const ConstMapPtr& map, const Pose3& anchor_pose) const
{
    if (map == nullptr)
    {
        return PointCloudXYZIRRgbSt();
    }

    PointCloudXYZIRRgbSt pcd_msg(map->size());
    pcd_msg.SetTimestamp(holo::Timestamp());
    pcd_msg.SetCoordinate(holo::Coordinate());
    pcd_msg.SetPose(anchor_pose.Cast<holo::float32_t>());

    const auto inv_anchor = anchor_pose.Inverse();

    for (uint64_t i = 0; i < map->size(); i++)
    {
        Point3  p  = inv_anchor * map->at(i)->position;
        Point3f pt = p.Cast<::holo::float32_t>();
        pcd_msg[i].Set(pt.GetX(), pt.GetY(), pt.GetZ());

        // intensity stands for the confience of the mappoint here
        pcd_msg[i].SetIntensity(map->at(i)->remember_rate);

        switch (map->at(i)->semantic_label)
        {
            case SemanticLabel::STATIC:
                pcd_msg[i].SetRgb({0, 0, 205});
                break;

            case SemanticLabel::VEHICLE:
                pcd_msg[i].SetRgb({0, 255, 255});
                break;

            case SemanticLabel::BYCICLE:
                pcd_msg[i].SetRgb({50, 205, 50});
                break;

            case SemanticLabel::PEDESTRIAN:
                pcd_msg[i].SetRgb({255, 255, 0});
                break;

            case SemanticLabel::TRAFFIC_SIGN:
                pcd_msg[i].SetRgb({255, 165, 0});
                break;

            case SemanticLabel::ANIMAL:
                pcd_msg[i].SetRgb({255, 0, 0});
                break;

            case SemanticLabel::UNKNOWN:
                pcd_msg[i].SetRgb({250, 250, 250});
                break;

            default:
                LOG(INFO) << "invaild semantic type.\n";
                break;
        }

        // ring stands for the category of the mappoint here
        pcd_msg[i].SetRing((uint32_t)map->at(i)->semantic_label);
    }

    return pcd_msg;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VSLAMBase::DetermineDeadTracks(Tracker::State& state) const
{
    // check all tracks then reject tracks which state is BAD_BEFORE_OPTIMIZATION or BAD_AFTER_OPTIMIZATION, or its
    // newest measurement is out of sliding window, or state is CANDIDATE while its oldest measurement is out of lag
    // size. we retain the tracks with state FINISHED because these track still have a chance to be tracked in
    // newest frame if it contain a good landmark.
    const auto oldest_frame_id = estimator_.GetOldestFrameId(new_frame_id_);
    auto&      tracks          = state.tracks;
    LOG(INFO) << "VSLAMBase --- total tracks number: " << tracks.size() << "\n";

    for (size_t i = 0; i < tracks.size();)
    {
        auto& track = tracks.at(i);

        // case 1. reject track whose newest measurement is out of sliding window, it can not be tracked any more.
        if (!parameters_.builder_params.enable_unit3_factor)
        {
            if (track.NewestMeasurement().first != new_frame_id_)
            {
                track.UpdatingState(FeatureTrack::State::DEAD);
            }
        }
        else if (track.GetState() != FeatureTrack::State::DEAD)
        {
            if (track.NewestMeasurement().first <= oldest_frame_id)
            {
                track.UpdatingState(FeatureTrack::State::DEAD);
            }

            // case 2. reject track whose oldest measurement will be marginalized while it still can not be well
            // triangulated.
            if (!track.GetLandmark() && track.OldestMeasurement().first <= oldest_frame_id)
            {
                track.UpdatingState(FeatureTrack::State::DEAD);
            }

            // case 3. reject track which is bad before/after optimization
            if (track.GetState() == FeatureTrack::State::BAD_BEFORE_OPTIMIZATION ||
                track.GetState() == FeatureTrack::State::BAD_AFTER_OPTIMIZATION)
            {
                track.UpdatingState(FeatureTrack::State::DEAD);
            }
        }

        if (track.GetState() == FeatureTrack::State::DEAD)
        {
            std::swap(tracks.at(i), tracks.back());
            tracks.pop_back();
            continue;
        }

        i++;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VSLAMBase::UpdateStateByFilterRejectedTracks(SlidingWindowState& state) const
{
    // if there is only one or less frame in given sliding window. no tracks should be rejected.
    if (state.values.count<gtsam::Pose3>() <= 1)
    {
        return;
    }

    // @TODO : we can not remove bad tracks from iSAM2 smoother, this function just remove the bad tracks from track
    // state
    DetermineDeadTracks(state.static_tracker_state);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T1, typename T2>
VSLAMBase::SourceCheckerResult VSLAMBase::SourceChecker(const T1& soucer_checker, const T2& measurement,
                                                        const Scalar& low_frequency_limit,
                                                        const Scalar& tolerate_duration, const std::string& source_name,
                                                        const VSLAMBase::SourceCheckerResult& last_checker_result)
{
    if (!soucer_checker)
    {
        LOG_EVERY_N(INFO, 50)
            << source_name
            << " source checker is NOT enable, if you want to check it, you can enable it in source checker yaml.";
        return last_checker_result;
    }

    VSLAMBase::SourceCheckerResult new_checker_result;
    soucer_checker->CheckSourceState(measurement);

    // Abnormal frequency detected for the first time
    if (soucer_checker->GetSourceActualFrequency() < low_frequency_limit && !last_checker_result.is_frequency_low)
    {
        new_checker_result.is_frequency_low         = true;
        new_checker_result.is_error                 = false;
        new_checker_result.low_frequency_start_time = measurement.GetTimestamp();
        LOG(WARNING) << "Vslam Base --- " + source_name + " actual frequency is too low: "
                     << soucer_checker->GetSourceActualFrequency() << " HZ.";
    }
    // Abnormal frequency duration
    else if (soucer_checker->GetSourceActualFrequency() < low_frequency_limit && last_checker_result.is_frequency_low)
    {
        if ((measurement.GetTimestamp() - last_checker_result.low_frequency_start_time).ToSec() > tolerate_duration)
        {
            new_checker_result.is_frequency_low         = true;
            new_checker_result.is_error                 = true;
            new_checker_result.low_frequency_start_time = last_checker_result.low_frequency_start_time;
            LOG(ERROR) << "Vslam Base --- " + source_name + " with low frequency lasts over 10 sec.";
        }
        else
        {
            new_checker_result.is_frequency_low         = true;
            new_checker_result.is_error                 = false;
            new_checker_result.low_frequency_start_time = last_checker_result.low_frequency_start_time;
            LOG(WARNING) << "Vslam Base --- " + source_name + " with low frequency lasts: "
                         << (measurement.GetTimestamp() - last_checker_result.low_frequency_start_time).ToSec()
                         << " sec.";
        }
    }
    // the source frequency is normal
    else
    {
        LOG_EVERY_N(INFO, 10) << source_name << "'s frequency is: " << soucer_checker->GetSourceActualFrequency();
        new_checker_result.is_frequency_low = false;
        new_checker_result.is_error         = false;
    }
    return new_checker_result;
}

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo
