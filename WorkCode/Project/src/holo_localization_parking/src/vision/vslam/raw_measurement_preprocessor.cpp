/*!
 * \brief raw measurement preprocessor class implementation file in vslam
 * \author Feng. Li, lifeng@holomatic.com
 * \date May-21-2020
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */
#include <eigen3/Eigen/Dense>
#include <opencv2/core/eigen.hpp>

#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
#include <gtsam/slam/EssentialMatrixFactor.h>

#include <holo/localization/vision/vslam/raw_measurement_preprocessor.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RawMeasurementPreprocessor::Parameters
RawMeasurementPreprocessor::Parameters::LoadFromYaml(const holo::yaml::Node& node)
{
    // imu pre-integration parameters
    PreintegrationParamsPtr pim_params;
    const holo::yaml::Node  pim_node = node["pim_params"];
    {
        const Scalar   gravity = node["gravity"].as<Scalar>(9.81);
        gtsam::Vector3 gyro_noise_sigma;
        {
            gyro_noise_sigma(0) = pim_node["gyro_noise_sigma"][0].as<Scalar>(1e-3);
            gyro_noise_sigma(1) = pim_node["gyro_noise_sigma"][1].as<Scalar>(1e-3);
            gyro_noise_sigma(2) = pim_node["gyro_noise_sigma"][2].as<Scalar>(1e-3);
        }

        gtsam::Vector3 acc_noise_sigma;
        {
            acc_noise_sigma(0) = pim_node["acc_noise_sigma"][0].as<Scalar>(1e-3);
            acc_noise_sigma(1) = pim_node["acc_noise_sigma"][1].as<Scalar>(1e-3);
            acc_noise_sigma(2) = pim_node["acc_noise_sigma"][2].as<Scalar>(1e-3);
        }

        gtsam::Vector3 gyro_noise_sigma_square;
        gtsam::Vector3 acc_noise_sigma_square;

        for (auto i = 0; i < 3; i++)
        {
            gyro_noise_sigma_square(i) = std::pow(gyro_noise_sigma(i), 2);
            acc_noise_sigma_square(i)  = std::pow(acc_noise_sigma(i), 2);
        }

        // create pim params
        pim_params = gtsam::PreintegrationParams::MakeSharedU(gravity);

        // construct pim covariance
        const gtsam::Matrix3 gyro_cov = gyro_noise_sigma_square.asDiagonal();
        const gtsam::Matrix3 acc_cov  = acc_noise_sigma_square.asDiagonal();
        const gtsam::Matrix3 int_cov  = gtsam::Matrix3::Identity() * 1e-8;

        // set pim covariance
        pim_params->setGyroscopeCovariance(gyro_cov);
        pim_params->setAccelerometerCovariance(acc_cov);
        pim_params->setIntegrationCovariance(int_cov);
    }

    WheelIntegrationBase::Parameters wim_params = LoadWheelIntegrationParams(node);

    // semantic data association parameters
    const semantic::DataAssociation::Parameters sda_params =
        semantic::DataAssociation::Parameters::LoadFromYaml(node["sda_params"]);

    // vehicle speed correction coefficients
    // @TODO use correction coefficients from initial alignment now,
    //       try to correct vehicle speed in sensor code in the future
    //       lishuaijie@holomatic.com Oct-8-2019
    const Vector2 speed_correction_coeff = LoadSpeedCorrectionCoeff(node);

    // slope threshold
    const auto slope_threshold = node["slope_threshold"].as<Scalar>(10.0);

    // slope threshold
    const auto inliers_threshold = node["inliers_threshold"].as<uint32_t>(100);

    // load body imu extrinsic
    const std::string body_imu_extrinsic_file = node["body_imu_extrinsic_file"].as<std::string>("");
    Pose3             T_bi                    = Pose3::Identity();

    if (!body_imu_extrinsic_file.empty())
    {
        T_bi = Extrinsic::LoadYaml(holo::GetConfigFileAbsolutePath(body_imu_extrinsic_file)).GetPose().Cast<Scalar>();
    }

    // combine all into parameters
    return Parameters(pim_params, wim_params, sda_params, speed_correction_coeff, slope_threshold, inliers_threshold,
                      T_bi);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Vector2 RawMeasurementPreprocessor::Parameters::LoadSpeedCorrectionCoeff(const holo::yaml::Node& node)
{
    std::string speed_correction_coeff_file = node["speed_correction_coeff_file"].as<std::string>();

    // if the given path is relative path, add ${HOLO_ROOT} before it
    speed_correction_coeff_file =
        holo::GetFileAbsolutePath(speed_correction_coeff_file, holo::GetHoloConfigRootDirectory());

    // default speed correction coefficients
    Vector2 speed_correction_coeff(1.0104, 0.0);

    try
    {
        holo::yaml::Node        correction_node = holo::yaml::LoadFile(speed_correction_coeff_file);
        const holo::yaml::Node& coeff_node      = correction_node["wheel_speed_correction_coefficient"];
        speed_correction_coeff(0)               = coeff_node["a"].as<Scalar>(1.0104);
        speed_correction_coeff(1)               = coeff_node["b"].as<Scalar>(0.0);
    }
    catch (const std::exception& e)
    {
        LOG(WARNING) << "VSLAMBase --- Can not load "
                     << "speed correction coefficients from file: " << speed_correction_coeff_file
                     << ", use default parameters! exception information: " << e.what() << std::endl;
    }

    return speed_correction_coeff;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WheelIntegrationBase::Parameters
RawMeasurementPreprocessor::Parameters::LoadWheelIntegrationParams(const holo::yaml::Node& node)
{
    std::string wheel_integration_params_file = node["wheel_integration_params_file"].as<std::string>();

    // if the given path is relative path, add ${HOLO_ROOT} before it
    wheel_integration_params_file =
        holo::GetFileAbsolutePath(wheel_integration_params_file, holo::GetHoloConfigRootDirectory());

    holo::yaml::Node wheel_integration_params_node = holo::yaml::LoadFile(wheel_integration_params_file);
    return WheelIntegrationBase::Parameters::LoadFromYaml(wheel_integration_params_node);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RawMeasurementPreprocessor::Parameters RawMeasurementPreprocessor::Parameters::Example()
{
    // create imu preintegration parameters
    const Scalar gravity(9.81);
    auto         pim_params_example = gtsam::PreintegrationParams::MakeSharedU(gravity);
    {
        const gtsam::Matrix3 cov = 1e-8 * gtsam::Matrix3::Identity();
        pim_params_example->setGyroscopeCovariance(cov);
        pim_params_example->setAccelerometerCovariance(cov);
        pim_params_example->setIntegrationCovariance(cov);
    }

    Vector2 speed_correction_coeff(1.0, 0.0);

    // return parameters
    return Parameters(pim_params_example, WheelIntegrationBase::Parameters::Example(),
                      semantic::DataAssociation::Parameters::GenerateExample(), speed_correction_coeff);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RawMeasurementPreprocessor::RawMeasurementPreprocessor(const Parameters&                    parameters,
                                                       const CameraParameters::Ptr&         camera_parameters,
                                                       const FeatureAssociator::Parameters& fa_params)
  : parameters_(parameters)
  , camera_parameters_(camera_parameters)
  , undistorters_(Utility::CreateImageUndistorters(camera_parameters_->intrinsics))
  , feature_associator_(fa_params, camera_parameters_)
  , semantic_associator_(new semantic::DataAssociation(parameters.sda_params))
{
    // construct camera_id_to_cv_K_
    for (size_t camera_id = 0; camera_id < camera_parameters_->camera_number; ++camera_id)
    {
        FisheyeIntrinsicType const* fisheye =
            dynamic_cast<FisheyeIntrinsicType const*>(camera_parameters_->intrinsics.at(camera_id).get());
        cv::Mat cv_K;
        cv::eigen2cv(HoloGtsam::Convert(fisheye->GetK()), cv_K);
        camera_id_to_cv_K_.emplace(camera_id, cv_K);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RawMeasurementPreprocessor::GetParkingSlotTrackResult(semantic::DataAssociation::State& semantic_state,
                                                           const ParkingSlotFrameType&       parking_slot_frame,
                                                           const Pose3& wTb, uint64_t frame_id)
{
    semantic_associator_->Run(semantic_state, parking_slot_frame, wTb, frame_id);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::pair<CorrectedMeasurement, FactorMeasurements>
RawMeasurementPreprocessor::Initialize(const VehicleState& initial_vehicle_state, const uint64_t initial_frame_id,
                                       const RawMeasurement& initial_measurements) const
{
    // create corrected measurements
    CorrectedMeasurement cm;
    cm.imus                       = ConvertImuMeasurements(initial_measurements.imus, parameters_.T_bi);
    cm.optional_ground_truth_odom = initial_measurements.optional_odometry;

    // initilize tracker_state in SlidingWindowState;
    SlidingWindowState::static_tracker_state = Tracker::State();

    // image undistortion and feature extraction
    cm.images = ImagePreprocess(initial_measurements);

    // visual features association
    MapProjectionMeasurements mpm;
    std::vector<Features>     new_features = ConvertPointFeatures(initial_measurements.multi_point_feature_list,
                                                                  initial_measurements.multi_obstacle_list, cm.images);

    const auto& new_timestamp = initial_measurements.newest_timestamp;

    Scalar window_size = 2.0 * feature_associator_.Params().gdm.window_size;
    feature_associator_.Run(Pose3::Identity(), new_timestamp, initial_frame_id, new_features,
                            initial_measurements.visible_map, window_size, SlidingWindowState::static_tracker_state,
                            mpm);

    // create factor measurements
    FactorMeasurements fm;

    // correct velocity in raw vslam measurement
    cm.chassis_states = CorrectChassisState(initial_measurements.chassis_states, false);
    cm.velocity_measurement =
        VelocityMeasurement(new_timestamp, Vector3(cm.chassis_states.back().GetVehicleSpeed(), 0.0, 0.0),
                            VelocityMeasurementReliability::HIGH);
    fm.vm = cm.velocity_measurement;

    // wheel integration measurement
    AckermannWheelIntegration   wheel_integration(parameters_.wim_params);
    WheelIntegrationMeasurement wim  = wheel_integration.integrateMeasurement(cm.chassis_states);
    cm.wheel_integration_measurement = wim;
    fm.wim                           = wim;

    // get ground truth to build prior factor
    if (initial_measurements.optional_odometry)
    {
        fm.gt_pose = initial_measurements.optional_odometry->GetPose();
    }

    // convert gps position to UTM coordinate
    if (initial_measurements.optional_position)
    {
        cm.optional_position = LL2UTM(*initial_measurements.optional_position);
        fm.position          = cm.optional_position;
    }

    // run semantic associator
    LOG(INFO) << "Initializer --- run semantic associator. \n";
    if (initial_measurements.optional_parking_slot_frame)
    {
        semantic_associator_->Run(SlidingWindowState::static_semantic_state,
                                  *(initial_measurements.optional_parking_slot_frame), initial_vehicle_state.Pose(),
                                  initial_frame_id);
    }
    LOG(INFO) << "Initializer --- end semantic associator. \n";

    // @Step 2: create initial values
    const uint64_t     initial_frame_index = SlidingWindowState::static_tracker_state.frame_id;
    const gtsam::Pose3 prior_pose          = HoloGtsam::Convert(initial_vehicle_state.Pose());
    fm.predicted_values.insert(X(initial_frame_index), prior_pose);

    if (SlidingWindowState::enable_estimation_with_acc)
    {
        const gtsam::imuBias::ConstantBias prior_bias(HoloGtsam::Convert(initial_vehicle_state.AccBias()),
                                                      HoloGtsam::Convert(initial_vehicle_state.GyroBias()));

        const gtsam::Vector3 prior_velocity = HoloGtsam::Convert(initial_vehicle_state.Velocity());
        fm.predicted_values.insert(V(initial_frame_index), prior_velocity);
        fm.predicted_values.insert(B(initial_frame_index), prior_bias);
    }
    else
    {
        fm.predicted_values.insert(B(initial_frame_index), HoloGtsam::Convert(initial_vehicle_state.GyroBias()));
    }

    return std::make_pair(cm, fm);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::pair<CorrectedMeasurement, FactorMeasurements> RawMeasurementPreprocessor::Run(
    const SlidingWindowState& old_state, const uint64_t new_frame_id, const RawMeasurement& new_raw_measurement) const
{
    if (!old_state.IsInitialized())
    {
        throw std::runtime_error(
            "RawMeasurementPreprocessor --- you should initialize the old_state before calling Run()");
    }

    holo::TicTocTimer timer;
    timer.Tic();

    // create corrected measurements
    CorrectedMeasurement cm;
    cm.imus                       = ConvertImuMeasurements(new_raw_measurement.imus, parameters_.T_bi);
    cm.optional_ground_truth_odom = new_raw_measurement.optional_odometry;

    // correct velocity in raw measurement
    timer.Tic();
    const bool is_zero_speed = IsZeroSpeedState(new_raw_measurement.chassis_states);
    cm.chassis_states        = CorrectChassisState(new_raw_measurement.chassis_states, is_zero_speed);

    // wheel integration measurement
    AckermannWheelIntegration   wheel_integration(parameters_.wim_params);
    WheelIntegrationMeasurement wim  = wheel_integration.integrateMeasurement(cm.chassis_states);
    cm.wheel_integration_measurement = wim;

    // CreateNewPim and PredictVehicleStateValues
    PreintegratedImuMeasurements  pim;
    PreintegratedAhrsMeasurements pam;
    Values                        predicted_values;

    if (SlidingWindowState::enable_estimation_with_acc)
    {
        pim                                 = CreateNewPim(old_state.values, new_frame_id, cm.imus);
        predicted_values                    = PredictVehicleStateValues(old_state.values, new_frame_id, pim);
        cm.velocity_measurement.timestamp   = new_raw_measurement.newest_timestamp;
        cm.velocity_measurement.velocity    = Vector3(cm.chassis_states.back().GetVehicleSpeed(), 0.0, 0.0);
        cm.velocity_measurement.reliability = VehicleSpeedReliabilityChecking(
            new_raw_measurement.chassis_states, cm.imus, is_zero_speed, predicted_values, new_frame_id);
    }
    else
    {
        pam              = CreateNewPam(old_state.values, new_frame_id, cm.imus);
        predicted_values = PredictVehicleStateValues(old_state.values, new_frame_id, wim);

        // set velocity measuremrnt, it will be used to check max vehicle speed during online mapping
        cm.velocity_measurement = VelocityMeasurement(new_raw_measurement.newest_timestamp,
                                                      Vector3(cm.chassis_states.back().GetVehicleSpeed(), 0.0, 0.0),
                                                      VelocityMeasurementReliability::HIGH);
    }

    Pose3 prior_T_wb = HoloGtsam::Convert(predicted_values.at(X(new_frame_id)).cast<gtsam::Pose3>());

    LOG(INFO) << "CreateNewPim and PredictVehicleStateValues takes " << 1000 * timer.Elapsed() << " ms.\n";
    timer.Tic();

    // image undistortion and feature extraction
    cm.images = ImagePreprocess(new_raw_measurement);
    LOG(INFO) << "ImagePreprocess takes " << 1000 * timer.Elapsed() << " ms.\n";

    timer.Tic();
    // visual features association
    MapProjectionMeasurements mpm;

    std::vector<Features> new_features = ConvertPointFeatures(new_raw_measurement.multi_point_feature_list,
                                                              new_raw_measurement.multi_obstacle_list, cm.images);

    Scalar window_size = feature_associator_.Params().gdm.window_size;

    if (old_state.inlier_global_correspondence_num < parameters_.inliers_threshold)
    {
        window_size = 2.0 * window_size;
    }
    const auto& new_timestamp = new_raw_measurement.newest_timestamp;
    LOG(INFO) << "ConvertPointFeatures takes " << 1000 * timer.Elapsed() << " ms.\n";

    feature_associator_.Run(prior_T_wb, new_timestamp, new_frame_id, new_features, new_raw_measurement.visible_map,
                            window_size, SlidingWindowState::static_tracker_state, mpm);

    // convert gps position to UTM coordinate
    if (new_raw_measurement.optional_position)
    {
        cm.optional_position = LL2UTM(*new_raw_measurement.optional_position);

        /// @todo(Feng. Li. 2020-05-21) outliers rejection for gps measurement
    }

    LOG(INFO) << "CorrectChassisState takes " << 1000 * timer.Elapsed() << " ms.\n";

    // get ground truth to build prior factor
    boost::optional<Pose3> optioanl_gt_pose = boost::none;
    if (new_raw_measurement.optional_odometry)
    {
        optioanl_gt_pose = new_raw_measurement.optional_odometry->GetPose();
    }

    timer.Tic();
    // const auto emms = GetEssentialMatrixMeasurements(SlidingWindowState::static_tracker_state.tracks,
    // predicted_values,
    //                                                  new_frame_id, 0.5, 100, 35);
    LOG(INFO) << "GetEssentialMatrixMeasurements takes " << 1000 * timer.Elapsed() << " ms.\n";

    // run global semantic associator in localization mode
    SlotMapFactorMeasurement sfm;
    if (new_raw_measurement.optional_parking_slot_frame)
    {
        if (new_raw_measurement.visible_slot_map != nullptr)
        {
            timer.Tic();
            sfm = semantic_associator_->RunParkingSlotGlobalMatching(new_raw_measurement.visible_slot_map,
                                                                     *(new_raw_measurement.optional_parking_slot_frame),
                                                                     prior_T_wb, new_frame_id);
            LOG(INFO) << "RunParkingSlotGlobalMatching takes " << 1000 * timer.Elapsed() << " ms.\n";
        }
    }

    // create factor measurements
    FactorMeasurements fm(pim, pam, mpm, cm.velocity_measurement, wim, predicted_values, optioanl_gt_pose,
                          cm.optional_position, sfm);

    return std::make_pair(cm, fm);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<Image> RawMeasurementPreprocessor::ImagePreprocess(const RawMeasurement& new_raw_measurement) const
{
    std::vector<Image> result;
    result.reserve(camera_parameters_->camera_number);

    for (uint16_t camera_index = 0; camera_index < new_raw_measurement.images.size(); camera_index++)
    {
        // retrieve intrinsic
        const auto& undistorter = undistorters_.at(camera_index);
        const auto& old_image   = new_raw_measurement.images.at(camera_index);

        if (!undistorter)
        {
            result.emplace_back(old_image);
            continue;
        }

        const holo::localization::Mat old_holo_mat(old_image);

        // undistort
        holo::localization::Mat undistorted_holo_mat;
        undistorter->Undistort(old_holo_mat, undistorted_holo_mat);

        Image          undistorted_image = old_image;
        const uint16_t width             = old_image.GetWidth();
        const uint16_t height            = old_image.GetHeight();
        const uint32_t buffer_size       = width * height;
        undistorted_image.SetData(static_cast<uint8_t*>(undistorted_holo_mat.GetCvType().data), buffer_size, width,
                                  height, Image::Encoding::GRAYSCALE);
        result.emplace_back(undistorted_image);
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PreintegratedImuMeasurements RawMeasurementPreprocessor::CreateNewPim(const Values&           old_values,
                                                                      const uint64_t          new_frame_index,
                                                                      const std::vector<Imu>& new_imus) const
{
    // get old bias values
    const uint64_t                     old_frame_index = new_frame_index - 1;
    const gtsam::imuBias::ConstantBias old_bias =
        old_values.at(B(old_frame_index)).cast<gtsam::imuBias::ConstantBias>();

    return CreateNewPim(new_imus, old_bias);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PreintegratedAhrsMeasurements RawMeasurementPreprocessor::CreateNewPam(const Values&           old_values,
                                                                       const uint64_t          new_frame_index,
                                                                       const std::vector<Imu>& new_imus) const
{
    static boost::shared_ptr<PreintegratedAhrsMeasurements::Params> ahrs_params =
        boost::make_shared<PreintegratedAhrsMeasurements::Params>(parameters_.pim_params->getGyroscopeCovariance(),
                                                                  parameters_.pim_params->getOmegaCoriolis());

    const uint64_t old_frame_index = new_frame_index - 1;
    const auto     old_bias        = old_values.at(B(old_frame_index)).cast<gtsam::Vector3>();

    // create rotation only
    PreintegratedAhrsMeasurements pam(ahrs_params, old_bias);

    for (uint16_t i = 0; i < (uint16_t)(new_imus.size() - 1); i++)
    {
        const Scalar dt = (new_imus.at(i + 1).GetTimestamp() - new_imus.at(i).GetTimestamp()).ToSec();

        const auto angular_velocity =
            0.5 * new_imus.at(i).GetAngularVelocity() + 0.5 * new_imus.at(i + 1).GetAngularVelocity();

        pam.integrateMeasurement(HoloGtsam::Convert(angular_velocity), dt);
    }

    return pam;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PreintegratedImuMeasurements RawMeasurementPreprocessor::CreateNewPim(const std::vector<Imu>&             imus,
                                                                      const gtsam::imuBias::ConstantBias& bias) const
{
    PreintegratedImuMeasurements new_pim(parameters_.pim_params, bias);

    // @note!!! the condition can be true only if this function[CreateNewPim]
    //          is called by the first frame to initialize system.
    //          in other case, something must be wrong!!!
    if (imus.size() == 0)
    {
        LOG(WARNING) << "DataAssociater --- empty imu vector!!!";
        return new_pim;
    }

    for (uint16_t i = 0; i < (uint16_t)(imus.size() - 1); i++)
    {
        const Scalar dt = (imus.at(i + 1).GetTimestamp() - imus.at(i).GetTimestamp()).ToSec();

        // calculate average linear_acceleration and angular_velocity
        // @todo(Feng. Li 2020-01-10) should we rotate imus.at(i + 1) with Quatation(angular_velocity * dt) ?
        const auto linear_acceleration =
            0.5 * imus.at(i).GetLinearAcceleration() + 0.5 * imus.at(i + 1).GetLinearAcceleration();

        const auto angular_velocity = 0.5 * imus.at(i).GetAngularVelocity() + 0.5 * imus.at(i + 1).GetAngularVelocity();

        new_pim.integrateMeasurement(HoloGtsam::Convert(linear_acceleration), HoloGtsam::Convert(angular_velocity), dt);
    }

    return new_pim;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const RawMeasurementPreprocessor::Parameters& RawMeasurementPreprocessor::Params() const
{
    return parameters_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Values RawMeasurementPreprocessor::PredictVehicleStateValues(const Values& old_values, const uint64_t new_frame_index,
                                                             const PreintegratedImuMeasurements& new_pim) const
{
    Values new_values = old_values;

    // retrieve newest vehicle state from old values
    const uint64_t old_frame_index = new_frame_index - 1;

    // newest navstate
    const gtsam::NavState old_navstate(old_values.at(X(old_frame_index)).cast<gtsam::Pose3>(),
                                       old_values.at(V(old_frame_index)).cast<gtsam::Vector3>());

    // newest bias
    const gtsam::imuBias::ConstantBias old_bias(old_values.at(B(old_frame_index)).cast<gtsam::imuBias::ConstantBias>());

    // predict new vehicle state with pim(IMU)
    const auto new_navstate = new_pim.predict(old_navstate, old_bias);

    // insert to new values
    new_values.insert(X(new_frame_index), new_navstate.pose());
    new_values.insert(V(new_frame_index), new_navstate.velocity());
    new_values.insert(B(new_frame_index), old_bias);

    // return
    return new_values;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Values RawMeasurementPreprocessor::PredictVehicleStateValues(const Values& old_values, const uint64_t new_frame_index,
                                                             const WheelIntegrationMeasurement& new_wim) const
{
    Values new_values = old_values;

    // retrieve newest vehicle state from old values
    const uint64_t old_frame_index = new_frame_index - 1;
    const auto     old_bias        = old_values.at(B(old_frame_index)).cast<gtsam::Vector3>();
    const auto     old_pose        = old_values.at(X(old_frame_index)).cast<gtsam::Pose3>();

    // predict new vehicle state with pim(IMU)
    gtsam::Pose3 delta_pose(gtsam::Pose2(new_wim.delta_x, new_wim.delta_y, new_wim.delta_yaw));
    gtsam::Pose3 new_pose = old_pose * delta_pose;

    // insert to new values
    new_values.insert(X(new_frame_index), new_pose);
    new_values.insert(B(new_frame_index), old_bias);

    // return
    return new_values;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UtmPosition RawMeasurementPreprocessor::LL2UTM(const GnssPosition& position) const
{
    /*
    // ll to utm convertion
    Point2 xy_in_utm;
    GeographicalTransformation::LL2UTM(position.longitude(), position.latitude(), xy_in_utm);
    const Point3  xyz_in_utm(xy_in_utm.x(), xy_in_utm.y(), position.altitude());
    const Vector3 position_std(position.longitude_std(), position.latitude_std(), position.altitude_std());

    // extrinsic compensation
    const Vector3 antenna_bias(0.0, 0.0, 0.0);
    const Point3  xyz_compensated = xyz_in_utm - antenna_bias;
    */
    (void)position;
    /// @todo(Feng. Li) convert position from LL to UTM coordinate
    return UtmPosition();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool RawMeasurementPreprocessor::IsZeroSpeedState(const std::vector<ChassisState>& chassis_states) const
{
    if (chassis_states.empty())
    {
        throw std::runtime_error("RawMeasurementPreprocessor --- IsZeroSpeedState, Input chassis_states is empty.\n");
    }

    const auto ref_chassis_state = chassis_states.back();

    if (std::fabs(ref_chassis_state.GetVehicleSpeed()) > 1e-3)
    {
        return false;
    }

    // zero speed detection by wheel pulse
    for (const auto& chassis_state : chassis_states)
    {
        const bool rr_wheel_speed_pulse_updated =
            (chassis_state.GetRearRightWheelPulse() != ref_chassis_state.GetRearRightWheelPulse());
        const bool rl_wheel_speed_pulse_updated =
            (chassis_state.GetRearLeftWheelPulse() != ref_chassis_state.GetRearLeftWheelPulse());

        if (std::fabs(chassis_state.GetVehicleSpeed()) > 1e-3 || rr_wheel_speed_pulse_updated ||
            rl_wheel_speed_pulse_updated)
        {
            return false;
        }
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VelocityMeasurementReliability RawMeasurementPreprocessor::VehicleSpeedReliabilityChecking(
    const std::vector<ChassisState>& chassis_states, const std::vector<Imu>& imus, const bool is_zero_speed_state,
    const Values& predicted_values, const uint64_t frame_id) const
{
    // 1. if it's not zero speed state while vehicle speed is almost zero, the vehicle speed should be unreliable
    /// @note this is common for lots of vehicles which can not output vehicle speed less than 1kph.
    if (!is_zero_speed_state)
    {
        for (const auto& chassis_state : chassis_states)
        {
            if (std::fabs(chassis_state.GetVehicleSpeed()) < 1e-3)
            {
                LOG(ERROR) << "RawMeasurementPreprocessor --- it's not zero speed state while vehicle speed is "
                              "almost zero.";
                return VelocityMeasurementReliability::LOW;
            }
        }
    }

    // 2. if the vehicle is moving through an uneven ground. the vehicle speed should be unreliable
    const Scalar kMaxXYAngularVelocityOnFlatGround = 0.05;  // rad/s

    for (const auto& imu : imus)
    {
        if (imu.GetAngularVelocity().GetHead(2).GetNorm() > kMaxXYAngularVelocityOnFlatGround)
        {
            LOG(WARNING) << "RawMeasurementPreprocessor --- the vehicle is moving through an uneven ground.";
            // Actually, as PC guys need the vehicle pose of BODY instead of IMU, so we completely discarded the
            // velocity constraint in this case may not so much reasonbale too.
            /// @todo(Feng. Li.2020-12-01) enable this condition when adding a status to vslam output odometry.
            // return VelocityMeasurementReliability::LOW;
        }
    }

    // 3. if the vehicle speed and predicted speed by imu integration are diametrically opposed. the vehicle speed
    // should be unreliable
    /// @note this case always happened when vehicle is backwards while gear is not in R
    const auto measured_speed     = chassis_states.back().GetVehicleSpeed();
    const auto predicted_pose     = predicted_values.at(X(frame_id)).cast<gtsam::Pose3>();
    const auto predicted_velocity = predicted_values.at(V(frame_id)).cast<gtsam::Vector3>();
    const auto predicted_speed    = (predicted_pose.inverse().rotation().rotate(predicted_velocity)).x();

    if (std::fabs(holo::Degree(predicted_pose.rotation().pitch())) > parameters_.slope_threshold &&
        measured_speed * predicted_speed < 0)
    {
        LOG(WARNING) << "RawMeasurementPreprocessor --- measured speed and predicted speed are diametrically opposed. "
                        "vehicle may be slipping now.\n";
        return VelocityMeasurementReliability::NOGOOD;
    }

    return VelocityMeasurementReliability::HIGH;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<ChassisState> RawMeasurementPreprocessor::CorrectChassisState(
    const std::vector<ChassisState>& chassis_states, const bool is_zero_speed_state) const
{
    std::vector<ChassisState> new_chassis_states = chassis_states;

    for (auto& new_chassis_state : new_chassis_states)
    {
        Scalar sign = 1.0;

        if (new_chassis_state.GetGearPosition() == ChassisState::GearPosition::R)
        {
            sign = -1.0;
        }

        Scalar speed = new_chassis_state.GetVehicleSpeed();

        if (is_zero_speed_state)
        {
            speed = 0.0;
        }
        else if (std::fabs(speed) < 1e-3)
        {
            speed = sign * 0.15;
        }

        new_chassis_state.SetVehicleSpeed(parameters_.speed_correction_coeff[0] * speed +
                                          parameters_.speed_correction_coeff[1]);
    }

    return new_chassis_states;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<Features> RawMeasurementPreprocessor::ConvertPointFeatures(
    const std::vector<PointFeaturefList_ST*>& multi_point_feature_list,
    const std::vector<ObstaclePtrList>& multi_obstacle_list, const std::vector<Image>& images) const
{
    std::vector<Features> ret;
    ret.reserve(multi_point_feature_list.size());
    std::vector<cv::Mat> multi_obstacle_mats;
    if (!multi_obstacle_list.empty())
    {
        multi_obstacle_mats = ConvertMulitObstaclePtrListToCvMats(multi_obstacle_list, images);
    }

    for (uint64_t index = 0; index < multi_point_feature_list.size(); index++)
    {
        const auto& all_point_features  = multi_point_feature_list.at(index)->point_features;
        const auto  point_features_size = multi_point_feature_list.at(index)->size;
        const auto  camera_id           = camera_parameters_->sensor_id_to_camera_index_map_.at(
                       static_cast<uint32_t>(multi_point_feature_list.at(index)->sensor_id));
        Features features;
        features.reserve(point_features_size);

        for (size_t i = 0; i < point_features_size; i++)
        {
            const auto& point_feature = all_point_features[i];
            Feature     ft;
            ft.camera_id = camera_id;

            Point2 undistorted_point;
            camera_parameters_->intrinsics.at(camera_id)->UndistortPoint(
                Point2(point_feature.position.x, point_feature.position.y), undistorted_point,
                camera_id_to_cv_K_.at(camera_id));

            ft.image_point = cv::Point2f(undistorted_point.GetX(), undistorted_point.GetY());
            Point3 normalized_point;
            camera_parameters_->intrinsics.at(camera_id)->Unproject(undistorted_point, normalized_point);
            ft.normalized_point = normalized_point / normalized_point.GetZ();
            ft.score            = point_feature.confidence;

            // convert descriptor
            cv::Mat desc_mat(cv::Size(point_feature.dimension, 1), CV_32FC1);

            for (size_t i = 0; i < point_feature.dimension; i++)
            {
                desc_mat.at<float_t>(0, i) = point_feature.descriptor[i];
            }

            ft.optional_descriptor = desc_mat;

            int16_t feature_x = std::floor(ft.image_point.x);
            int16_t feature_y = std::floor(ft.image_point.y);

            if (!multi_obstacle_list.empty() && multi_obstacle_list.at(index).GetSize())
            {
                if (feature_x < 0 || feature_x > multi_obstacle_mats.at(index).cols || feature_y < 0 ||
                    feature_y > multi_obstacle_mats.at(index).rows)
                {
                    continue;
                }
                else
                {
                    ft.semantic_label = SemanticLabel(multi_obstacle_mats.at(index).at<uint16_t>(feature_y, feature_x));
                }
            }
            features.emplace_back(ft);
        }
        ret.emplace_back(features);
    }
    return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<cv::Mat> RawMeasurementPreprocessor::ConvertMulitObstaclePtrListToCvMats(
    const std::vector<ObstaclePtrList>& multi_obstacle_list, const std::vector<Image>& images) const
{
    //(void)images;
    std::vector<cv::Mat> obstacles_mat;
    obstacles_mat.reserve(multi_obstacle_list.size());

    for (uint32_t i = 0; i < multi_obstacle_list.size(); i++)
    {
        const auto&                                     undistorter = undistorters_.at(i);
        const auto                                      obstacle    = multi_obstacle_list.at(i);
        std::map<Scalar, int16_t, std::greater<Scalar>> point_y_to_index_map;
        std::vector<Classification::MainType>           classifications;
        classifications.reserve(obstacle.GetSize());

        cv::Mat obstacle_mat = cv::Mat::zeros(camera_parameters_->intrinsics.at(i)->GetHeight(),
                                              camera_parameters_->intrinsics.at(i)->GetWidth(), CV_16UC1);
        cv::Mat obstacle_image;

        for (uint32_t i = 0; i < obstacle.GetSize(); i++)
        {
            const auto contour_points_and_score = obstacle.GetObstacleList()[i]->GetContourPoints();
            point_y_to_index_map.emplace(contour_points_and_score[0].GetY(), i);
            classifications.emplace_back(obstacle.GetObstacleList()[i]->GetClassification().GetMainType());
        }

        for (const auto y_to_index : point_y_to_index_map)
        {
            const auto index          = y_to_index.second;
            const auto left_top_x     = obstacle.GetObstacleList()[index]->GetContourPoints()[0].GetX();
            const auto left_top_y     = obstacle.GetObstacleList()[index]->GetContourPoints()[0].GetY();
            const auto right_bottom_x = obstacle.GetObstacleList()[index]->GetContourPoints()[1].GetX();
            const auto right_bottom_y = obstacle.GetObstacleList()[index]->GetContourPoints()[1].GetY();

            // undistort obstacle point
            std::vector<Point2d> undistorted_points_left_top, undistorted_points_right_bottom,
                undistorted_points_top_mid, undistorted_points_bottom_mid;

            undistorted_points_left_top.reserve(1);
            undistorted_points_right_bottom.reserve(1);
            undistorted_points_top_mid.reserve(1);
            undistorted_points_bottom_mid.reserve(1);

            Point2d distorded_left_top_point(left_top_x, left_top_y);
            Point2d distorded_right_bottom_point(right_bottom_x, right_bottom_y);
            Point2d distorted_top_mid((left_top_x + right_bottom_x) / 2, left_top_y);
            Point2d distorted_bottom_mid((left_top_x + right_bottom_x) / 2, right_bottom_y);

            undistorter->UndistortPoints(std::vector<Point2d>{distorded_left_top_point}, undistorted_points_left_top);
            undistorter->UndistortPoints(std::vector<Point2d>{distorded_right_bottom_point},
                                         undistorted_points_right_bottom);
            undistorter->UndistortPoints(std::vector<Point2d>{distorted_top_mid}, undistorted_points_top_mid);
            undistorter->UndistortPoints(std::vector<Point2d>{distorted_bottom_mid}, undistorted_points_bottom_mid);

            const auto classification           = classifications[index];
            uint16_t   classification_order_num = 0;

            if (classification == Classification::MainType::VEHICLE)
            {
                LOG(INFO) << "the feature is vehicle";
                classification_order_num = 1;
            }
            else if (classification == Classification::MainType::BIKE)
            {
                LOG(INFO) << "the feature is bike";
                classification_order_num = 2;
            }
            else if (classification == Classification::MainType::PEDESTRIAN)
            {
                LOG(INFO) << "the feature is pedestrian";
                classification_order_num = 3;
            }
            else if (classification == Classification::MainType::TRAFFIC_SIGN)
            {
                LOG(INFO) << "the feature is traffic sign";
                classification_order_num = 4;
            }
            else if (classification == Classification::MainType::ANIMAL)
            {
                LOG(INFO) << "the feature is animal";
                classification_order_num = 5;
            }
            else if (classification == Classification::MainType::UNKNOWN)
            {
                LOG(INFO) << "the feature is unknown";
                classification_order_num = 6;
            }

            int x_upper_boundary = std::min((int)camera_parameters_->intrinsics.at(i)->GetHeight(),
                                            std::max(0, (int)std::floor(undistorted_points_top_mid.front().GetY())));
            int x_lower_boundary = std::max(0, std::min((int)camera_parameters_->intrinsics.at(i)->GetHeight(),
                                                        (int)std::floor(undistorted_points_bottom_mid.front().GetY())));
            int y_left_boundary  = std::min((int)camera_parameters_->intrinsics.at(i)->GetWidth(),
                                            std::max(0, (int)std::floor(undistorted_points_left_top.front().GetX())));
            int y_right_boundary =
                std::max(0, std::min((int)camera_parameters_->intrinsics.at(i)->GetWidth(),
                                     (int)std::floor(undistorted_points_right_bottom.front().GetX())));

            for (uint16_t mat_x = x_upper_boundary; mat_x < x_lower_boundary; mat_x++)
            {
                for (uint16_t mat_y = y_left_boundary; mat_y < y_right_boundary; mat_y++)
                {
                    obstacle_mat.at<uint16_t>(mat_x, mat_y) = classification_order_num;
                }
            }
            if (!images.empty())
            {
                obstacle_image = images.at(i).GetCvType().clone();
                // top line
                cv::line(obstacle_image, cv::Point(y_left_boundary, x_upper_boundary),
                         cv::Point(y_right_boundary, x_upper_boundary), cv::Scalar(0, 0, 255));
                // left line
                cv::line(obstacle_image, cv::Point(y_left_boundary, x_upper_boundary),
                         cv::Point(y_left_boundary, x_lower_boundary), cv::Scalar(0, 0, 255));
                // right line
                cv::line(obstacle_image, cv::Point(y_right_boundary, x_upper_boundary),
                         cv::Point(y_right_boundary, x_lower_boundary), cv::Scalar(0, 0, 255));
                // bottom line
                cv::line(obstacle_image, cv::Point(y_left_boundary, x_lower_boundary),
                         cv::Point(y_right_boundary, x_lower_boundary), cv::Scalar(0, 0, 255));
            }
        }
        obstacles_mat.emplace_back(obstacle_mat);
    }

    return obstacles_mat;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<Imu> RawMeasurementPreprocessor::ConvertImuMeasurements(const std::vector<Imu>& input_imus,
                                                                    const Pose3&            extrinsic) const
{
    std::vector<Imu> output_imus;
    output_imus.reserve(input_imus.size());
    const auto& r = extrinsic.GetRotation();
    const auto& t = extrinsic.GetTranslation();

    for (auto imu : input_imus)
    {
        // convert angular velocity
        Vector3 angular_velocity = r * imu.GetAngularVelocity();
        imu.SetAngularVelocity(angular_velocity);

        // convert acceleration
        Vector3 acceleration = r * imu.GetLinearAcceleration();

        // Centrifugal acceleration
        if (!t.IsZero())
        {
            // Subtract out the the centripetal acceleration from the unbiased one
            // to get linear acceleration vector in the body frame:
            const auto body_Omega_body = angular_velocity.ToSkewSymmetric();
            const auto b_velocity_bs   = body_Omega_body * t.ToVector();  // magnitude: omega * arm
            auto       centripetal_acc = HoloGtsam::Convert(body_Omega_body * b_velocity_bs);
            acceleration -= Vector3(centripetal_acc[0], centripetal_acc[1], centripetal_acc[2]);
        }

        imu.SetLinearAcceleration(acceleration);

        output_imus.emplace_back(imu);
    }

    return output_imus;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EssentialMatrixMeasurements RawMeasurementPreprocessor::GetEssentialMatrixMeasurements(
    const std::vector<FeatureTrack>& tracks, const Values& values, uint64_t frame_id, Scalar min_baseline_distance,
    Scalar largest_rotation_angle, uint64_t min_train_feaures_num) const
{
    EssentialMatrixMeasurements ret;
    // map Key: train frame id; map value: sub map<camera index, keypoints>
    std::unordered_map<uint64_t,
                       std::unordered_map<uint64_t, std::pair<std::vector<gtsam::Point2>, std::vector<gtsam::Point2>>>>
        train_frame_index_train_keypoints;

    if (tracks.empty())
    {
        LOG(ERROR) << "RawMeasurementPreprocessor --- GetEssentialMatrixMeasurements, the input tracks is empty !!!";
        return ret;
    }

    // traveral all cameras to prepare feature correspondence
    for (uint16_t camera_index = 0; camera_index < camera_parameters_->camera_number; camera_index++)
    {
        for (const auto& track : tracks)
        {
            // select the feature tracks which observe the current frame
            if (track.NewestMeasurement().first != frame_id || !track.NewestMeasurement().second.count(camera_index))
            {
                continue;
            }
            if (!values.exists(X(frame_id)))
            {
                LOG(ERROR) << "RawMeasurementPreprocessor --- the current frame id: " << frame_id
                           << " is not exist in values!!!";
                std::runtime_error("The query frame id is not exist in values.");
            }
            const auto& query_frame_pose  = HoloGtsam::Convert(values.at(X(frame_id)).cast<gtsam::Pose3>());
            const auto& query_measurement = track.NewestMeasurement();

            for (size_t i = 0; i < track.Length() - 1; i++)
            {
                auto        train_measurement = track.Measurements(i);
                const auto& train_frame_id    = train_measurement.first;

                if (!values.exists(X(train_frame_id)))
                {
                    continue;
                }

                if (!train_measurement.second.count(camera_index))
                {
                    // the camera index is not exist in train measurement
                    continue;
                }

                const auto& train_frame_pose = HoloGtsam::Convert(values.at(X(train_frame_id)).cast<gtsam::Pose3>());
                if (train_frame_pose.Dist(query_frame_pose) < min_baseline_distance ||
                    train_frame_pose.GetRotation().ComputeAngle(query_frame_pose.GetRotation()) >
                        largest_rotation_angle)
                {
                    continue;
                }

                const auto& train_key_point = train_measurement.second.at(camera_index).normalized_point;
                const auto& query_key_point = query_measurement.second.at(camera_index).normalized_point;
                train_frame_index_train_keypoints[train_frame_id][camera_index].first.push_back(
                    gtsam::Point2(train_key_point.GetX(), train_key_point.GetY()));
                train_frame_index_train_keypoints[train_frame_id][camera_index].second.push_back(
                    gtsam::Point2(query_key_point.GetX(), query_key_point.GetY()));
            }
        }
    }

    // select the candidate train frames which include enough features
    for (const auto& item : train_frame_index_train_keypoints)
    {
        const auto& train_frame_id = item.first;
        for (const auto& camera_index_kpts_pair : item.second)
        {
            const auto& train_kps = camera_index_kpts_pair.second.first;
            const auto& query_kps = camera_index_kpts_pair.second.second;

            if (train_kps.size() < min_train_feaures_num)
            {
                continue;
            }
            const auto& camera_index = camera_index_kpts_pair.first;

            /// @todo(Feng.Li 2022-01-19) we should check if this camera model is Fisheye or not, and handle it!!!
            if (camera_parameters_->intrinsics.at(camera_index)->GetModel() != Model::FISHEYE)
            {
                LOG(ERROR) << "RawMeasurementPreprocessor --- CalcuRotationFromFeatureTracks only support Fisheye "
                              "camera now.\n";
                continue;
            }

            FisheyeIntrinsicType const* fisheye =
                dynamic_cast<FisheyeIntrinsicType const*>(camera_parameters_->intrinsics.at(camera_index).get());
            const auto& camera_intrinsic_K = fisheye->GetK();

            const auto& camera_extrinsic = camera_parameters_->extrinsics.at(camera_index);
            const auto& train_frame_pose =
                values.at(X(train_frame_id)).cast<gtsam::Pose3>() * HoloGtsam::Convert(camera_extrinsic);
            const auto& query_frame_pose =
                values.at(X(frame_id)).cast<gtsam::Pose3>() * HoloGtsam::Convert(camera_extrinsic);
            const auto             _1P2_     = train_frame_pose.between(query_frame_pose);
            gtsam::EssentialMatrix essential = gtsam::EssentialMatrix::FromPose3(_1P2_);
            Values                 values;
            FactorGraph            factor_graph;

            values.insert(E(0), essential);

            Scalar fx = camera_intrinsic_K(0, 0);
            Scalar fy = camera_intrinsic_K(1, 1);
            Scalar f  = 0.5 * (fx + fy);
            // convert sigma uv
            static const Scalar sigma_uv = 3.0 / f;

            // create noise model
            static const gtsam::SharedNoiseModel noise_model(gtsam::noiseModel::Isotropic::Sigma(1, sigma_uv));

            // create huber loss
            static const Scalar huber_loss = 3.5 / (f * sigma_uv);
            // create hub
            const auto huber = gtsam::noiseModel::Robust::Create(
                gtsam::noiseModel::mEstimator::Huber::Create(0.5 * huber_loss * huber_loss), noise_model);
            // Noise model for first type of factor is evaluating algebraic error

            for (size_t i = 0; i < train_kps.size(); ++i)
            {
                const auto& p1 = train_kps.at(i);
                const auto& p2 = query_kps.at(i);
                factor_graph.add(boost::make_shared<gtsam::EssentialMatrixFactor>(E(0), p1, p2, huber));
            }

            // optimize by gtsam
            gtsam::LevenbergMarquardtParams params;
            params.setVerbosity(gtsam::LevenbergMarquardtParams::verbosityLMTranslator(
                gtsam::LevenbergMarquardtParams::VerbosityLM::LAMBDA));
            gtsam::LevenbergMarquardtOptimizer optimizer(factor_graph, values, params);
            const Values                       optimized_value = optimizer.optimize();

            Scalar   sum_square_error = 0.0;
            uint64_t num_error        = 0;
            for (size_t i = 0; i < factor_graph.size(); i++)
            {
                const FactorGraph::Base::sharedFactor& factor = factor_graph.at(i);

                if (const gtsam::EssentialMatrixFactor* f =
                        dynamic_cast<const gtsam::EssentialMatrixFactor*>(&(*factor)))
                {
                    const Scalar error = (f->unwhitenedError(optimized_value)).norm();
                    sum_square_error += (error * error);
                    num_error++;
                }
            }

            if (sum_square_error / num_error > 3.0 / f)
            {
                continue;
            }

            essential            = optimized_value.at(E(0)).cast<gtsam::EssentialMatrix>();
            const auto& rotation = HoloGtsam::Convert(essential.rotation());

            EssentialMatrixMeasurement emm;
            emm.train_frame_id           = train_frame_id;
            emm.query_frame_id           = frame_id;
            emm.r                        = HoloGtsam::Convert(camera_extrinsic.GetRotation() * rotation *
                                                              camera_extrinsic.GetRotation().Inverse());
            emm.measured_E[camera_index] = essential;

            if (emm.r.ypr()[1] * 57.3 > 1.0)
            {
                continue;
            }

            if (emm.r.ypr()[2] * 57.3 > 1.0)
            {
                continue;
            }

            ret.push_back(emm);
            break;
        }
    }

    return ret;
}

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo
