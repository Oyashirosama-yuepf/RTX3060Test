/*!
 * \brief map database manager class implementation file in vslam
 * \author Feng. Li, lifeng@holomatic.com
 * \date Mar-13-2020
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo/3d/common/io.h>
#include <holo/localization/vision/vslam/feature_track.h>
#include <holo/localization/vision/vslam/mapping/map_database_manager.h>
#include <holo/localization/vision/vslam/sliding_window_state.h>
#include <malloc.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
std::unordered_map<std::string, MappingDatabase> MapDatabaseManager::mapping_databases_ = {};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MapDatabaseManager::Parameters MapDatabaseManager::Parameters::LoadFromYaml(const holo::yaml::Node& node)
{
    // load map data directory
    auto map_data_dir = node["map_data_dir"].as<std::string>("");

    if (!IsAbsolutePath(map_data_dir))
    {
        map_data_dir = holo::GetHoloConfigRootDirectory() + "/" + map_data_dir;
    }

    // load map name
    const auto map_names = node["map_names"].as<std::vector<std::string>>(std::vector<std::string>{});

    // load working mode
    const auto mode = node["mode"].as<std::string>("offline_optimization");

    // save images
    const auto save_image = node["save_image"].as<bool>(false);

    // keyframe selection parameters
    const holo::yaml::Node kf_selection_node =
        node["keyframe_selection_params"].as<holo::yaml::Node>(holo::yaml::Node());

    if (kf_selection_node.IsNull())
    {
        return Parameters(map_data_dir, map_names, mode, save_image);
    }

    const auto   minimum_distance_interval     = kf_selection_node["minimum_distance_interval"].as<Scalar>(5.0);
    const auto   minimum_angle_interval        = kf_selection_node["minimum_angle_interval"].as<Scalar>(5.0);
    const auto   minimum_observed_landmark_num = kf_selection_node["minimum_observed_landmark_num"].as<uint16_t>(50);
    const Scalar max_distance_without_keyframe = node["max_distance_without_keyframe"].as<Scalar>(15.0);
    KeyFrameSelectionParameters keyframe_selection_params(minimum_distance_interval, minimum_angle_interval,
                                                          minimum_observed_landmark_num);

    return Parameters(map_data_dir, map_names, mode, save_image, keyframe_selection_params,
                      max_distance_without_keyframe);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MapDatabaseManager::Parameters MapDatabaseManager::Parameters::Example()
{
    const std::string              map_data_dir = "/tmp";
    const std::vector<std::string> map_names    = {"route_1"};
    const std::string              mode         = "";
    const bool                     save_image   = false;

    return Parameters(map_data_dir, map_names, mode, save_image);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MapDatabaseManager::MapDatabaseManager(const Parameters& parameters) : parameters_(parameters)
{
    if (parameters_.mode == "offline_optimization")
    {
        LoadMappingDatabase(parameters_);
        CleanUpDirectory(true);
    }
    else if (parameters_.mode == "online_data_association")
    {
        // clean up directory to ensure the result is valid.
        CleanUpDirectory();
    }
    else if (parameters_.mode == "localization")
    {
        prebuilt_map_ = LoadMap(parameters_.map_data_dir + parameters_.map_names.front() + "/mappoints.bin");
        prebuilt_slot_map_ =
            LoadParkingSlotMap(parameters_.map_data_dir + parameters_.map_names.front() + "/slot_map.bin");
        key_frames_database_ =
            LoadKeyFramesDatabase(parameters_.map_data_dir + parameters_.map_names.front() + "/frames.bin");

        // just load bow vocabulary when it exist
        if (Relocalization::bow_vocabulary_)
        {
            keyframes_bow_vectors_ =
                LoadKeyFramesBowVector(parameters_.map_data_dir + parameters_.map_names.front() + "/keyframes_bow.bin");
        }

        learned_path_ =
            holo_io::Load<Odometry>(parameters_.map_data_dir + parameters_.map_names.front() + "/vehicle_odometry.txt");
    }
    else if (parameters_.mode == "avp_mapping")
    {
        LOG(INFO) << "MapDatabaseManager --- The mode is avp mapping.\n";
    }
    else
    {
        LOG(ERROR) << "MapDatabaseManager --- unknown mode: " << parameters_.mode << "\n";
        throw std::runtime_error("MapDatabaseManager --- unknown mode.\n");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MapDatabaseManager::~MapDatabaseManager()
{
    if (parameters_.mode == "online_data_association")
    {
        // save tracks
        SaveTracks(tracks_database_, parameters_.map_names.front());
        SaveParkingSlotTracks(parking_slot_tracks_database_, parameters_.map_names.front());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapDatabaseManager::SaveMappingDataForOfflineOptimization(const OfflineMappingData& mapping_data)
{
    const auto& timestamp = mapping_data.corrected_measurements.imus.back().GetTimestamp();
    SaveImus(mapping_data.corrected_measurements.imus, mapping_data.map_name);

    // save only velocity measurement which is aligned with new image's timestamp
    /// @todo(Feng.Li lifeng@holomatic.com) we should save all vehicle info when we want to pre-integrate all wheel
    /// speed in future.
    const auto& chassis_state = mapping_data.corrected_measurements.chassis_states.back();

    if (mapping_data.corrected_measurements.velocity_measurement.reliability != VelocityMeasurementReliability::NOGOOD)
    {
        SaveVelocity(timestamp, Vector3(chassis_state.GetVehicleSpeed(), 0.0, 0.0), mapping_data.map_name);
    }

    SaveChassisState(chassis_state, mapping_data.map_name);

    SaveWheelIntegrationMeasurement(mapping_data.corrected_measurements.wheel_integration_measurement,
                                    mapping_data.map_name);

    // save position in UTM coordinate
    if (mapping_data.corrected_measurements.optional_position)
    {
        SaveUTMPosition(*(mapping_data.corrected_measurements.optional_position), mapping_data.map_name);
    }

    // save images if requested
    if (parameters_.save_image && !mapping_data.corrected_measurements.images.empty())
    {
        SaveImages(mapping_data.frame_id, mapping_data.corrected_measurements.images, mapping_data.map_name);
    }

    if (!mapping_data.indexed_features.empty())
    {
        SaveFeatures(mapping_data.frame_id, mapping_data.indexed_features, mapping_data.map_name);
    }

    SaveXVBValue(mapping_data.frame_id, mapping_data.estimated_xvb_values, mapping_data.map_name);
    SaveOnlineTrajectory(mapping_data.frame_id, timestamp, mapping_data.estimated_xvb_values, mapping_data.map_name);

    // save ground truth to txt
    if (mapping_data.corrected_measurements.optional_ground_truth_odom)
    {
        SaveGroundTruthOdometry(*mapping_data.corrected_measurements.optional_ground_truth_odom, mapping_data.map_name);
    }

    SaveTimestampAndFrameId(timestamp, mapping_data.frame_id, mapping_data.map_name);
    SaveCameraParameters(mapping_data.camera_parameters, mapping_data.map_name);

    // record tracks
    tracks_database_.AddFeatureTracks(mapping_data.tracks);

    parking_slot_tracks_database_.AddParkingSlotTracks(mapping_data.parking_slot_tracks);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapDatabaseManager::UpdateMappingDatabase(const OfflineMappingData& mapping_data)
{
    const auto& timestamp                          = mapping_data.corrected_measurements.imus.back().GetTimestamp();
    const auto  map_name                           = mapping_data.map_name;
    const auto  frame_id                           = mapping_data.frame_id;
    mapping_databases_[map_name].camera_parameters = mapping_data.camera_parameters;
    mapping_databases_[map_name].imus.push_back(mapping_data.corrected_measurements.imus);
    mapping_databases_[map_name].velocities.push_back(mapping_data.corrected_measurements.velocity_measurement);
    mapping_databases_[map_name].xvb_values.insert(X(frame_id), mapping_data.estimated_xvb_values.at(X(frame_id)));
    mapping_databases_[map_name].xvb_values.insert(B(frame_id), mapping_data.estimated_xvb_values.at(B(frame_id)));
    mapping_databases_[map_name].tracks_database.AddFeatureTracks(mapping_data.tracks);
    mapping_databases_[map_name].parking_slot_tracks_database.AddParkingSlotTracks(mapping_data.parking_slot_tracks);
    mapping_databases_[map_name].timestamp_to_frame_id.emplace(timestamp, frame_id);
    mapping_databases_[map_name].frame_id_to_timestamp.emplace(frame_id, timestamp);

    if (!mapping_data.indexed_features.empty())
    {
        mapping_databases_[map_name].frame_indexed_features.emplace(frame_id, mapping_data.indexed_features);
    }

    mapping_databases_[map_name].wheel_integrations.push_back(
        mapping_data.corrected_measurements.wheel_integration_measurement);
    const auto& chassis_state = mapping_data.corrected_measurements.chassis_states.back();
    SaveChassisState(chassis_state, mapping_data.map_name);

    if (SlidingWindowState::enable_estimation_with_acc)
    {
        mapping_databases_[map_name].xvb_values.insert(V(frame_id), mapping_data.estimated_xvb_values.at(V(frame_id)));
    }
    mapping_databases_[map_name].enable_estimation_with_acc = SlidingWindowState::enable_estimation_with_acc;
    mapping_databases_[map_name].imu_factors.emplace(frame_id, mapping_data.imu_factor);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapDatabaseManager::LoadMappingDatabase(const Parameters& parameters)
{
    if (!mapping_databases_.empty())
    {
        LOG(INFO) << "MapDatabaseManager --- mapping database is not empty.\n";
        return;
    }

    holo::uint64_t map_id = 0;

    for (const auto& map_name : parameters.map_names)
    {
        const std::string data_dir = parameters.map_data_dir + "/" + map_name;
        MappingDatabase   mapping_database;
        mapping_database.xvb_values             = LoadXVBValues(data_dir + "/values_xvb.txt");
        mapping_database.map_id                 = map_id;
        mapping_database.camera_parameters      = vslam::CameraParameters::LoadFromBin(data_dir + "/camera_params.bin");
        mapping_database.images                 = LoadImages(data_dir + "/image.txt");
        mapping_database.frame_indexed_features = LoadFeatures(data_dir + "/features.txt");
        mapping_database.imus                   = LoadImus(data_dir + "/imu.txt");
        mapping_database.velocities             = LoadVelocities(data_dir + "/velocity.txt");
        mapping_database.wheel_integrations     = LoadWheelIntegrationMeasurements(data_dir + "/wheel_integration.txt");
        mapping_database.positions              = LoadUTMPositions(data_dir + "/utm_position.txt");
        mapping_database.tracks_database = LoadTracks(data_dir + "/tracks.bin", mapping_database.camera_parameters);
        mapping_database.parking_slot_tracks_database = LoadParkingSlotTracks(data_dir + "/parking_slot_tracks.bin");
        const auto timestamp_and_frame_id = LoadTimeStampAndFrameId(data_dir + "/timestamp_and_frame_id.txt");
        std::vector<ParkingSlotType> parking_slot_database;

        // load ground truth
        mapping_database.ground_truth_odometry = holo_io::Load<Odometry>(data_dir + "/gts.txt");

        // create timestamp to frame id map and frame id to timestamp map
        std::map<Timestamp, uint64_t> timestamp_to_frame_id;
        std::map<uint64_t, Timestamp> frame_id_to_timestamp;
        for (const auto& time_frame_id : timestamp_and_frame_id)
        {
            const auto& timestamp = time_frame_id.first;
            const auto& frame_id  = time_frame_id.second;
            timestamp_to_frame_id.emplace(timestamp, frame_id);
            frame_id_to_timestamp.emplace(frame_id, timestamp);
        }

        mapping_database.frame_id_to_timestamp      = frame_id_to_timestamp;
        mapping_database.timestamp_to_frame_id      = timestamp_to_frame_id;
        mapping_database.enable_estimation_with_acc = SlidingWindowState::enable_estimation_with_acc;
        mapping_databases_.emplace(map_name, mapping_database);

        LOG(INFO) << "MapDatabaseManager --- enable_estimation_with_acc = "
                  << mapping_database.enable_estimation_with_acc;

        map_id++;
    }

    LOG(INFO) << "MapDatabaseManager --- load mapping database done.\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapDatabaseManager::SaveXVBValue(const uint64_t frame_id, const Values& values, const std::string& map_name) const
{
    // retrieve pose
    const auto pose = HoloGtsam::Convert(values.at(X(frame_id)).cast<gtsam::Pose3>());
    const auto t    = pose.GetTranslation();
    const auto q    = pose.GetRotation().ToQuaternion();

    // save data to file, file format:
    // frame_id tx ty tz qw qx qy qz vx vy vz bias_acc_x bias_acc_y bias_acc_z bias_gyro_x bias_gyro_y bias_gyro_z
    std::string file_name(parameters_.map_data_dir + "/" + map_name + "/values_xvb.txt");

    // check if it is first line of this file
    if (!boost::filesystem::exists(file_name))
    {
        std::fstream file(file_name, std::fstream::app);
        file << SlidingWindowState::enable_estimation_with_acc << "\n";
        file.close();
    }

    std::fstream file(file_name, std::fstream::app);

    file << frame_id << " ";
    file << t.GetX() << " " << t.GetY() << " " << t.GetZ() << " ";
    file << q.GetW() << " " << q.GetX() << " " << q.GetY() << " " << q.GetZ() << " ";

    if (SlidingWindowState::enable_estimation_with_acc)
    {
        // retrieve velocity
        const auto velocity(values.at(V(frame_id)).cast<gtsam::Vector3>());

        // retrieve imu bias
        const auto bias(values.at(B(frame_id)).cast<gtsam::imuBias::ConstantBias>());
        file << velocity.x() << " " << velocity.y() << " " << velocity.z() << " ";
        file << bias.accelerometer().x() << " " << bias.accelerometer().y() << " " << bias.accelerometer().z() << " "
             << bias.gyroscope().x() << " " << bias.gyroscope().y() << " " << bias.gyroscope().z() << "\n";
    }
    else
    {
        const auto gyro_bias(values.at(B(frame_id)).cast<gtsam::Vector3>());
        file << gyro_bias(0) << " " << gyro_bias(1) << " " << gyro_bias(2) << "\n";
    }

    file.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapDatabaseManager::SaveOnlineTrajectory(const uint64_t frame_id, const holo::Timestamp& timestamp,
                                              const Values& values, const std::string& map_name) const
{
    // retrieve pose
    const auto            pose = HoloGtsam::Convert(values.at(X(frame_id)).cast<gtsam::Pose3>());
    std::vector<Odometry> trajectory;
    trajectory.reserve(1);

    Odometry odo;
    odo.SetTimestamp(timestamp);
    odo.SetPose(pose);
    trajectory.emplace_back(odo);

    // save trajectory
    const std::string trajectory_file = parameters_.map_data_dir + "/" + map_name + "/vehicle_odometry.txt";
    holo_io::Save(trajectory, trajectory_file);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapDatabaseManager::SaveGroundTruthOdometry(const Odometry& gt_odo, const std::string& map_name) const
{
    // save trajectory
    const std::string gts_file = parameters_.map_data_dir + "/" + map_name + "/gts.txt";
    holo_io::Save<Odometry>({gt_odo}, gts_file);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapDatabaseManager::SaveImus(const std::vector<Imu>& imus, const std::string& map_name) const
{
    if (imus.empty())
    {
        return;
    }

    std::fstream file(parameters_.map_data_dir + "/" + map_name + "/imu.txt", std::fstream::app);
    file << imus.size() << "\n";

    // save imu measurement one by one
    for (size_t i = 0; i < imus.size(); i++)
    {
        const auto& imu = imus.at(i);
        // timestamp acc_x acc_y acc_z gyro_x gyro_y gyro_z
        file << imu.GetTimestamp().ToNsec() << " ";
        file << imu.GetLinearAcceleration()[0] << " " << imu.GetLinearAcceleration()[1] << " "
             << imu.GetLinearAcceleration()[2] << " ";
        file << imu.GetAngularVelocity()[0] << " " << imu.GetAngularVelocity()[1] << " " << imu.GetAngularVelocity()[2]
             << "\n";
    }
    file.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapDatabaseManager::SaveVelocity(const Timestamp& timestamp, const Vector3& velocity,
                                      const std::string& map_name) const
{
    std::fstream file(parameters_.map_data_dir + "/" + map_name + "/velocity.txt", std::fstream::app);
    file << timestamp.ToNsec() << " " << velocity[0] << " " << velocity[1] << " " << velocity[2] << "\n";
    file.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapDatabaseManager::SaveWheelIntegrationMeasurement(const WheelIntegrationMeasurement& wim,
                                                         const std::string&                 map_name) const
{
    std::fstream file(parameters_.map_data_dir + "/" + map_name + "/wheel_integration.txt", std::fstream::app);
    file << wim.start.ToNsec() << " " << wim.end.ToNsec() << " "
         << " " << wim.delta_x << " " << wim.delta_y << " " << wim.delta_yaw << "\n";
    file.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapDatabaseManager::SaveUTMPosition(const UtmPosition& position, const std::string& map_name) const
{
    // const auto& header  = position.header;
    const auto& pos     = position.position;
    const auto& pos_std = position.position_std;

    std::fstream file(parameters_.map_data_dir + "/" + map_name + "/utm_position.txt", std::fstream::app);
    file << pos.GetX() << " " << pos.GetY() << " " << pos.GetZ() << " " << pos_std[0] << " " << pos_std[1] << " "
         << pos_std[2] << "\n";
    file.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapDatabaseManager::SaveImages(const uint64_t frame_id, const std::vector<Image>& images,
                                    const std::string& map_name) const
{
    if (images.empty())
    {
        return;
    }

    // get image directory
    const std::string image_file = parameters_.map_data_dir + "/" + map_name + "/image.txt";
    const auto        image_dir  = holo::GetParentDirectory(image_file) + "/images/";

    std::fstream file(image_file, std::fstream::app);
    for (size_t camera_index = 0; camera_index < images.size(); camera_index++)
    {
        std::stringstream image_name;
        image_name << image_dir << frame_id << "-" << camera_index << ".png";

        // save image name to file
        // frame_id camera_index image_name
        file << frame_id << " " << camera_index << " " << image_name.str() << "\n";

        // save image to disk
        const auto& image = images.at(camera_index).GetCvType();
        cv::imwrite(image_name.str(), image);
    }
    file.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapDatabaseManager::SaveFeatures(const uint64_t frame_id, const CameraIndexedFeatures& multi_camera_features,
                                      const std::string& map_name) const
{
    if (multi_camera_features.empty())
    {
        return;
    }

    // get features directory
    const std::string features_file_name = parameters_.map_data_dir + "/" + map_name + "/features.txt";
    const auto        features_dir       = holo::GetParentDirectory(features_file_name) + "/features/";

    std::fstream features_file(features_file_name, std::fstream::app);

    for (const auto& indexed_features : multi_camera_features)
    {
        const auto& camera_index     = indexed_features.first;
        const auto& current_features = indexed_features.second;

        if (current_features.empty())
        {
            continue;
        }

        std::stringstream file_name;
        file_name << features_dir << frame_id << "-" << camera_index << ".bin";

        // save file name
        // frame_id camera_index feature_file
        features_file << frame_id << " " << camera_index << " " << file_name.str() << "\n";

        // save features to bin
        std::ofstream fout(file_name.str());

        if (!fout)
        {
            LOG(ERROR) << "MapDatabaseManager --- SaveFeatures, could not open " << file_name.str();
            throw std::runtime_error("MapDatabaseManager --- failed to save features.");
        }

        // save feature number
        uint16_t features_num = current_features.size();
        fout.write((const char*)&(features_num), sizeof(uint16_t));

        // save descriptor col number
        uint16_t dim = (uint16_t)current_features.at(0).optional_descriptor->cols;
        fout.write((const char*)&(dim), sizeof(uint16_t));

        for (uint16_t i = 0; i < features_num; i++)
        {
            const auto& feature = current_features.at(i);

            // save image point
            const auto&  img_pt   = feature.image_point;
            const Scalar img_pt_x = img_pt.x;
            const Scalar img_pt_y = img_pt.y;
            fout.write((const char*)&(img_pt_x), sizeof(Scalar));
            fout.write((const char*)&(img_pt_y), sizeof(Scalar));

            // save normalized point
            const Point3& ptn   = feature.normalized_point;
            const Scalar  ptn_x = ptn.GetX();
            const Scalar  ptn_y = ptn.GetY();
            const Scalar  ptn_z = ptn.GetZ();
            fout.write((const char*)&(ptn_x), sizeof(Scalar));
            fout.write((const char*)&(ptn_y), sizeof(Scalar));
            fout.write((const char*)&(ptn_z), sizeof(Scalar));

            // save semantic label
            const auto& semantic_label = feature.semantic_label;
            fout.write((const char*)&(semantic_label), sizeof(SemanticLabel));

            // save descriptor
            const auto& desc = feature.optional_descriptor;
            for (uint16_t j = 0; j < dim; j++)
            {
                fout.write((const char*)&desc->at<float32_t>(0, j), sizeof(float32_t));
            }

            // save camera id
            fout.write((const char*)&(feature.camera_id), sizeof(uint16_t));

            // save score
            fout.write((const char*)&(feature.score), sizeof(Scalar));
        }
        fout.close();
    }

    features_file.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapDatabaseManager::SaveTimestampAndFrameId(const Timestamp& timestamp, const uint64_t frame_id,
                                                 const std::string& map_name) const
{
    std::fstream file(parameters_.map_data_dir + "/" + map_name + "/timestamp_and_frame_id.txt", std::fstream::app);
    file << timestamp.ToNsec() << " " << frame_id << "\n";
    file.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapDatabaseManager::SaveTracks(const TracksDatabase& tracks_database, const std::string& map_name) const
{
    const auto    tracks_file = parameters_.map_data_dir + "/" + map_name + "/tracks.bin";
    std::ofstream file(tracks_file);

    if (!file)
    {
        LOG(ERROR) << "MapDatabaseManager --- SaveTracks, could not open " << tracks_file;
        return;
    }

    if (tracks_database.IsEmpty())
    {
        LOG(ERROR) << "MapDatabaseManager --- SaveTracks, track database is empty";
        return;
    }

    // check valid of descriptor_dimension
    auto descriptor_dimension = tracks_database.GetDescriptorDimension();
    if (descriptor_dimension < 0)
    {
        LOG(ERROR) << "MapDatabaseManager --- SaveTracks, feature in this track database has no descriptor.";
        return;
    }

    // save total mappoints number
    uint64_t tracks_num = tracks_database.Size();
    file.write((const char*)&(tracks_num), sizeof(uint64_t));

    // save descriptor col number
    uint16_t dim = (uint16_t)descriptor_dimension;
    file.write((const char*)&(dim), sizeof(uint16_t));

    const auto& indexed_tracks = tracks_database.GetAllTracks();

    // save mappoints' information
    for (const auto& indexed_track : indexed_tracks)
    {
        const auto& track    = indexed_track.second;
        const auto& landmark = track.GetLandmark();

        // check if this track
        if (!landmark)
        {
            throw std::runtime_error("MapDatabaseManager --- SaveTracks. we can only save a tracks with landmark.\n");
        }

        // save landmrak id
        const uint64_t landmark_id = landmark->Id();
        file.write((const char*)&landmark_id, sizeof(uint64_t));

        // save position
        const Point3 position   = HoloGtsam::Convert(landmark->Point());
        Scalar       position_x = position.GetX();
        Scalar       position_y = position.GetY();
        Scalar       position_z = position.GetZ();
        file.write((const char*)&position_x, sizeof(Scalar));
        file.write((const char*)&position_y, sizeof(Scalar));
        file.write((const char*)&position_z, sizeof(Scalar));

        // save track state
        if (track.GetState() != FeatureTrack::State::FINISHED && track.GetState() != FeatureTrack::State::CANDIDATE)
        {
            throw std::runtime_error(
                "MapDatabaseManager --- SaveTracks. we can only save FINISHED or CANDIDATE tracks.\n");
        }
        uint16_t state = static_cast<uint16_t>(track.GetState());
        file.write((const char*)&state, sizeof(uint16_t));

        // save measurement_number
        const uint16_t length = track.Length();
        file.write((const char*)&length, sizeof(uint16_t));

        // save measurement
        for (uint16_t i = 0; i < length; i++)
        {
            const auto& m = track.Measurements(i);

            // get frame id
            const uint64_t frame_id = m.first;
            file.write((const char*)&frame_id, sizeof(uint64_t));

            // loop all associated camera
            for (const auto& camera_indexed_feature : m.second)
            {
                const auto& camera_index = camera_indexed_feature.first;
                const auto& feature      = camera_indexed_feature.second;

                // check valid of descriptor
                if (!feature.optional_descriptor)
                {
                    throw std::runtime_error(
                        "MapDatabaseManager --- SaveTracks. we can only save the feature with valid descriptor.\n");
                }

                // save camera id
                file.write((const char*)&camera_index, sizeof(uint16_t));

                // save image point
                const Scalar img_pt_x = feature.image_point.x;
                const Scalar img_pt_y = feature.image_point.y;
                file.write((const char*)&img_pt_x, sizeof(Scalar));
                file.write((const char*)&img_pt_y, sizeof(Scalar));

                // save normalized point
                const Scalar normalized_point_x = feature.normalized_point.GetX();
                const Scalar normalized_point_y = feature.normalized_point.GetY();
                const Scalar normalized_point_z = feature.normalized_point.GetZ();
                file.write((const char*)&normalized_point_x, sizeof(Scalar));
                file.write((const char*)&normalized_point_y, sizeof(Scalar));
                file.write((const char*)&normalized_point_z, sizeof(Scalar));

                const auto semantic_label = feature.semantic_label;
                file.write((const char*)&semantic_label, sizeof(SemanticLabel));

                // save descriptor
                const cv::Mat descriptor = *feature.optional_descriptor;
                for (uint16_t j = 0; j < descriptor_dimension; j++)
                {
                    file.write((const char*)&descriptor.at<float32_t>(0, j), sizeof(float32_t));
                }

                // save score
                file.write((const char*)&(feature.score), sizeof(Scalar));
            }
        }
    }
    LOG(ERROR) << "MapDatabaseManager --- SaveTracks done, total tracks: " << tracks_num;
    file.close();
}

void MapDatabaseManager::SaveParkingSlotTracks(const ParkingSlotTracksDatabase& parking_slot_tracks_database,
                                               const std::string&               map_name) const
{
    const auto    parking_slot_tracks_file = parameters_.map_data_dir + "/" + map_name + "/parking_slot_tracks.bin";
    std::ofstream file(parking_slot_tracks_file);

    if (!file)
    {
        LOG(ERROR) << "MapDatabaseManager --- SaveParkingSlotTracks, could not open " << parking_slot_tracks_file;
        return;
    }

    if (parking_slot_tracks_database.IsEmpty())
    {
        LOG(ERROR) << "MapDatabaseManager --- SaveParkingSlotTracks, track database is empty";
        return;
    }

    // save total parking slot tracks number
    uint64_t parking_slot_track_num = parking_slot_tracks_database.Size();
    file.write((const char*)&(parking_slot_track_num), sizeof(uint64_t));

    const auto& all_parking_slot_tracks = parking_slot_tracks_database.GetAllParkingSlotTracks();

    // save parking slot's information
    for (const auto& parking_slot_track : all_parking_slot_tracks)
    {
        if (parking_slot_track.state == semantic::ParkingSlotTrack::State::LIVE)
        {
            std::cout << "parking slot track state : " << static_cast<int>(parking_slot_track.state) << std::endl;
            throw std::runtime_error("MapDatabaseManager --- SaveParkingSlotTracks. we can only save CANDIDATE and "
                                     "FRESH parking slot tracks.\n");
        }

        // save track id
        const uint64_t track_id = parking_slot_track.id;
        file.write((const char*)&(track_id), sizeof(uint64_t));

        const uint64_t track_timestamp = parking_slot_track.timestamp.ToNsec();
        file.write((const char*)&(track_timestamp), sizeof(int64_t));

        const uint64_t plane_id = parking_slot_track.plane_id;
        file.write((const char*)&(plane_id), sizeof(plane_id));

        const uint16_t state = static_cast<uint16_t>(parking_slot_track.state);
        file.write((const char*)&(state), sizeof(uint16_t));

        const uint64_t measurement_num = parking_slot_track.measurements.size();
        file.write((const char*)&(measurement_num), sizeof(uint64_t));

        for (const auto& m : parking_slot_track.measurements)
        {
            const uint64_t frame_id = m.first;
            file.write((const char*)&frame_id, sizeof(uint64_t));

            const uint64_t parking_slot_timestamp = m.second.first.ToNsec();
            file.write((const char*)&parking_slot_timestamp, sizeof(int64_t));

            const auto parking_slot_in_body_frame = m.second.second;

            const Scalar p0_x = parking_slot_in_body_frame.vertices[0].GetX();
            const Scalar p0_y = parking_slot_in_body_frame.vertices[0].GetY();
            const Scalar p0_z = parking_slot_in_body_frame.vertices[0].GetZ();
            file.write((const char*)&(p0_x), sizeof(Scalar));
            file.write((const char*)&(p0_y), sizeof(Scalar));
            file.write((const char*)&(p0_z), sizeof(Scalar));

            const Scalar p1_x = parking_slot_in_body_frame.vertices[1].GetX();
            const Scalar p1_y = parking_slot_in_body_frame.vertices[1].GetY();
            const Scalar p1_z = parking_slot_in_body_frame.vertices[1].GetZ();
            file.write((const char*)&(p1_x), sizeof(Scalar));
            file.write((const char*)&(p1_y), sizeof(Scalar));
            file.write((const char*)&(p1_z), sizeof(Scalar));

            bool_t is_rear_vertex_available = parking_slot_in_body_frame.is_rear_vertex_available;
            file.write((const char*)&(is_rear_vertex_available), sizeof(bool_t));

            // rear vertices, index starts with [2]
            if (parking_slot_in_body_frame.is_rear_vertex_available)
            {
                const Scalar p2_x = parking_slot_in_body_frame.vertices[2].GetX();
                const Scalar p2_y = parking_slot_in_body_frame.vertices[2].GetY();
                const Scalar p2_z = parking_slot_in_body_frame.vertices[2].GetZ();
                file.write((const char*)&(p2_x), sizeof(Scalar));
                file.write((const char*)&(p2_y), sizeof(Scalar));
                file.write((const char*)&(p2_z), sizeof(Scalar));

                const Scalar p3_x = parking_slot_in_body_frame.vertices[3].GetX();
                const Scalar p3_y = parking_slot_in_body_frame.vertices[3].GetY();
                const Scalar p3_z = parking_slot_in_body_frame.vertices[3].GetZ();
                file.write((const char*)&(p3_x), sizeof(Scalar));
                file.write((const char*)&(p3_y), sizeof(Scalar));
                file.write((const char*)&(p3_z), sizeof(Scalar));
            }

            bool_t is_center_vertex_available = parking_slot_in_body_frame.is_center_vertex_available;
            file.write((const char*)&(is_center_vertex_available), sizeof(bool_t));

            // center vertex, index starts with [4]
            if (parking_slot_in_body_frame.is_center_vertex_available)
            {
                const Scalar center_vertex_x = parking_slot_in_body_frame.center_vertex.GetX();
                const Scalar center_vertex_y = parking_slot_in_body_frame.center_vertex.GetY();
                const Scalar center_vertex_z = parking_slot_in_body_frame.center_vertex.GetZ();
                file.write((const char*)&(center_vertex_x), sizeof(Scalar));
                file.write((const char*)&(center_vertex_y), sizeof(Scalar));
                file.write((const char*)&(center_vertex_z), sizeof(Scalar));
            }
        }
    }
    LOG(ERROR) << "MapDatabaseManager --- SaveParkingSlotTrack done, total tracks: " << parking_slot_track_num;
    file.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapDatabaseManager::SaveCameraParameters(const CameraParameters::Ptr& camera_parameters,
                                              const std::string&           map_name) const
{
    const std::string file_name = parameters_.map_data_dir + "/" + map_name + "/camera_params.bin";

    // check if camera parameters already be saved.
    if (boost::filesystem::exists(file_name))
    {
        return;
    }

    // save camera parameters
    camera_parameters->SaveParametersToBin(file_name);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapDatabaseManager::SaveMapAndTrajectory(const Map& map, const std::vector<Odometry>& trajectory,
                                              const std::string& map_name) const
{
    SaveMap(map, map_name);

    const std::string trajectory_file = parameters_.map_data_dir + "/" + map_name + "/vehicle_odometry.txt";
    if (boost::filesystem::exists(trajectory_file))
    {
        boost::filesystem::remove(trajectory_file);
    }
    LOG(INFO) << "MapDatabaseManager --- trying to save trajectory to " << trajectory_file << " ...\n";

    // save trajectory
    holo_io::Save(trajectory, trajectory_file);

    // save x y z only
    const std::string xyz_file = parameters_.map_data_dir + "/" + map_name + "/path.txt";
    std::fstream      file(xyz_file, std::fstream::out);

    for (const auto& odo : trajectory)
    {
        const auto& t   = odo.GetPose().GetTranslation();
        const auto& yaw = odo.GetPose().GetRotation().RPY().At(2);
        // timestamp, X, Y, Z, yaw
        file << odo.GetTimestamp().ToSec() << " " << t.GetX() << " " << t.GetY() << " " << t.GetZ() << " " << yaw
             << "\n";
    }

    file.close();

    LOG(INFO) << "MapDatabaseManager --- save trajectory to file done. total odometry num: " << trajectory.size()
              << "\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MapQuality MapDatabaseManager::SaveAndEvaluateQualityOfTheOptimizedMap(const Values&         optimized_values,
                                                                       const FramesDatabase& frame_database,
                                                                       const std::string&    map_name,
                                                                       const TracksDatabase& tracks_database) const
{
    // 1. create mappoints and trajectory
    const auto map_and_trajectory =
        CreateMapAndTrajectory(optimized_values, tracks_database, mapping_databases_.at(map_name));

    const auto parking_slot_map = CreateParkingSlotMap(optimized_values, mapping_databases_.at(map_name));

    // 2. select keyframes
    const auto gridding_frame_ids = AssignFramesToVoxelGrid(optimized_values, frame_database);
    const auto keyframe_ids       = SelectKeyFrames(optimized_values, frame_database, gridding_frame_ids);
    const auto keyframes_database = RetrieveKeyFramesDatabase(optimized_values, frame_database, keyframe_ids);

    // 3. map quality evaluation
    const auto quality = EvaluateMapQuality(map_name, optimized_values, map_and_trajectory.first,
                                            map_and_trajectory.second, gridding_frame_ids, keyframe_ids);

    // if map quality is bad, save nothing
    if (quality == MapQuality::BAD)
    {
        std::string ply_file_name = parameters_.map_data_dir + "/" + map_name + "/pcd.ply";

        if (boost::filesystem::exists(ply_file_name))
        {
            boost::filesystem::remove(ply_file_name);
        }

        const auto mapoints_pcd   = ConvertToPointCloud(map_and_trajectory.first);
        const auto trajectory_pcd = ConvertToPointCloud(map_and_trajectory.second);
        const auto keyframe_pcd   = ConvertToPointCloud(optimized_values, frame_database, keyframe_ids);

        // save point clouds to ply file for debugging
        PointCloudXYZIRRgbSt pcd_msg;
        pcd_msg.insert(pcd_msg.end(), mapoints_pcd.begin(), mapoints_pcd.end());
        pcd_msg.insert(pcd_msg.end(), trajectory_pcd.begin(), trajectory_pcd.end());
        pcd_msg.insert(pcd_msg.end(), keyframe_pcd.begin(), keyframe_pcd.end());

        holo::pointcloud::SavePly(ply_file_name, pcd_msg);
        LOG(ERROR) << "MapDatabaseManager --- map quality is BAD, nothing will be saved, see log for more details.\n";
        return quality;
    }

    // 4. save mappoints, trajectory, and keyframes, keyframe's bow vector
    SaveMapAndTrajectory(map_and_trajectory.first, map_and_trajectory.second, map_name);
    SaveKeyFrames(keyframes_database, map_name);
    SaveKeyFramesBowVector(frame_database, keyframe_ids, map_name);

    // save parking slot map and get target parking slot id
    const auto end_point              = map_and_trajectory.second.back().GetPose().GetTranslation();
    const auto target_parking_slot_id = SaveParkingSlotMapAndTargetID(parking_slot_map, end_point, map_name);

    // 5. save mapoints + trajectory + keyframe_poses to ply for debugging
    std::string ply_file_name = parameters_.map_data_dir + "/" + map_name + "/pcd.ply";

    if (boost::filesystem::exists(ply_file_name))
    {
        boost::filesystem::remove(ply_file_name);
    }

    const auto mapoints_pcd      = ConvertToPointCloud(map_and_trajectory.first);
    const auto trajectory_pcd    = ConvertToPointCloud(map_and_trajectory.second);
    const auto keyframe_pcd      = ConvertToPointCloud(optimized_values, frame_database, keyframe_ids);
    const auto parking_slots_pcd = ConvertToPointCloud(parking_slot_map, target_parking_slot_id);

    // save point clouds to ply file for debugging
    PointCloudXYZIRRgbSt pcd_msg;
    pcd_msg.insert(pcd_msg.end(), mapoints_pcd.begin(), mapoints_pcd.end());
    pcd_msg.insert(pcd_msg.end(), trajectory_pcd.begin(), trajectory_pcd.end());
    pcd_msg.insert(pcd_msg.end(), keyframe_pcd.begin(), keyframe_pcd.end());
    pcd_msg.insert(pcd_msg.end(), parking_slots_pcd.begin(), parking_slots_pcd.end());

    holo::pointcloud::SavePly(ply_file_name, pcd_msg);

    // copy result to /opt/holo/hpp/route_*
    {
        // remove old map and create new directory
        boost::filesystem::path map_path("/opt/holo/hpp/" + map_name);
        if (boost::filesystem::exists(map_path))
        {
            boost::filesystem::path map_path_files("/opt/holo/hpp/" + map_name + "/");
            boost::filesystem::remove_all(map_path_files);

            if (!boost::filesystem::create_directories(map_path))
            {
                std::stringstream ss;
                ss << "MapDatabaseManager --- Failed to create dir: " << map_path << "\n";
                throw std::runtime_error(ss.str());
            }
        }
        else
        {
            if (!boost::filesystem::create_directories(map_path))
            {
                std::stringstream ss;
                ss << "MapDatabaseManager --- Failed to create dir: " << map_path << "\n";
                throw std::runtime_error(ss.str());
            }
        }

        try
        {
            // copy files from config_path to /opt/holo/hpp/route_*
            const std::string source_path      = parameters_.map_data_dir + "/" + map_name + "/";
            const std::string destination_path = "/opt/holo/hpp/" + map_name + "/";
            boost::filesystem::copy_file(source_path + "vehicle_odometry.txt",
                                         destination_path + "vehicle_odometry.txt");
            boost::filesystem::copy_file(source_path + "mappoints.bin", destination_path + "mappoints.bin");
            boost::filesystem::copy_file(source_path + "frames.bin", destination_path + "frames.bin");
            boost::filesystem::copy_file(source_path + "keyframes_bow.bin", destination_path + "keyframes_bow.bin");
            boost::filesystem::copy_file(source_path + "pcd.ply", destination_path + "pcd.ply");
            boost::filesystem::copy_file(source_path + "path.txt", destination_path + "path.txt");
            boost::filesystem::copy_file(source_path + "front_wheel_angle.txt",
                                         destination_path + "front_wheel_angle.txt");
            boost::filesystem::copy_file(source_path + "map_quality.txt", destination_path + "map_quality.txt");
            boost::filesystem::copy_file(source_path + "start_point.jpg", destination_path + "start_point.jpg");
            boost::filesystem::copy_file(source_path + "slot_map.bin", destination_path + "slot_map.bin");

            LOG(INFO) << "MapDatabaseManager --- success copy mapfiles to /opt/holo/."
                      << "\n";
        }
        catch (boost::filesystem::filesystem_error)
        {
            LOG(ERROR) << "MapDatabaseManager --- fail copy mapfiles to /opt/holo/.";
        }
    }
    return quality;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapDatabaseManager::SaveTheMergedMapAfterOptimizing(const Values&          optimized_values,
                                                         const FramesDatabase&  frame_database,
                                                         const MappingDatabase& map_database,
                                                         const TracksDatabase&  tracks_database,
                                                         const std::string&     map_name) const
{
    // 1. create mappoints and trajectory
    const auto map_and_trajectory = CreateMapAndTrajectory(optimized_values, tracks_database, map_database);

    // 2. select keyframes
    const auto gridding_frame_ids = AssignFramesToVoxelGrid(optimized_values, frame_database);
    const auto keyframe_ids       = SelectKeyFrames(optimized_values, frame_database, gridding_frame_ids);
    const auto keyframes_database = RetrieveKeyFramesDatabase(optimized_values, frame_database, keyframe_ids);

    // 3. save mappoints, trajectory, and keyframes
    SaveMapAndTrajectory(map_and_trajectory.first, map_and_trajectory.second, map_name);
    SaveKeyFrames(keyframes_database, map_name);

    // 4. save mapoints + trajectory + keyframe_poses to ply for debugging
    std::string ply_file_name = parameters_.map_data_dir + "/" + map_name + "/pcd.ply";

    if (boost::filesystem::exists(ply_file_name))
    {
        boost::filesystem::remove(ply_file_name);
    }

    const auto mapoints_pcd   = ConvertToPointCloud(map_and_trajectory.first);
    const auto trajectory_pcd = ConvertToPointCloud(map_and_trajectory.second);
    const auto keyframe_pcd   = ConvertToPointCloud(optimized_values, frame_database, keyframe_ids);

    // save point clouds to ply file for debugging
    PointCloudXYZIRRgbSt pcd_msg;
    pcd_msg.insert(pcd_msg.end(), mapoints_pcd.begin(), mapoints_pcd.end());
    pcd_msg.insert(pcd_msg.end(), trajectory_pcd.begin(), trajectory_pcd.end());
    pcd_msg.insert(pcd_msg.end(), keyframe_pcd.begin(), keyframe_pcd.end());

    holo::pointcloud::SavePly(ply_file_name, pcd_msg);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapDatabaseManager::SaveTheAvpMapAfterOptimizing(const Values&         optimized_values,
                                                      const FramesDatabase& frame_database, const Map& map,
                                                      const std::string& map_name, const Pose3& pose_compensation) const
{
    /// create map and key frames directory
    const auto directory = parameters_.map_data_dir + "/" + parameters_.map_names.front();

    // remove all old file if exist
    if (boost::filesystem::is_directory(directory))
    {
        boost::filesystem::remove_all(directory);
    }

    if (!boost::filesystem::create_directories(directory))
    {
        std::stringstream ss;
        ss << "MapDatabaseManager --- Failed to create dir: " << directory << "\n";
        throw std::runtime_error(ss.str());
    }

    // 1. select keyframes
    const auto gridding_frame_ids = AssignFramesToVoxelGrid(optimized_values, frame_database);
    const auto keyframe_ids       = SelectKeyFrames(optimized_values, frame_database, gridding_frame_ids);
    const auto keyframes_database = RetrieveKeyFramesDatabase(optimized_values, frame_database, keyframe_ids);

    // create trajectory
    std::vector<Odometry> trajectory;

    for (const auto& frame_id_to_frame : frame_database.GetAllFrames())
    {
        const auto& frame_id  = frame_id_to_frame.first;
        const auto& timestamp = holo::Timestamp();

        // retrieve pose and velocity from values.
        if (!optimized_values.exists(X(frame_id)))
        {
            continue;
        }

        const auto pose = HoloGtsam::Convert(optimized_values.at(X(frame_id)).cast<gtsam::Pose3>());

        // create odometry.
        Odometry odom;
        odom.SetTimestamp(timestamp);
        odom.SetChildCoordinate(holo::Coordinate());
        odom.SetStatus(Odometry::Status::ALLGOOD);
        odom.SetSource(Odometry::Source::VISION);
        odom.SetPose(pose);
        odom.SetVelocity(Vector6(0.0, 0.0, 0.0, 0.0, 0.0, 0.0));

        trajectory.push_back(odom);
    }

    // save mapoints + trajectory + keyframe_poses to ply for debugging
    std::string ply_file_name = parameters_.map_data_dir + "/" + map_name + "/pcd.ply";

    if (boost::filesystem::exists(ply_file_name))
    {
        boost::filesystem::remove(ply_file_name);
    }

    const auto mapoints_pcd = ConvertToPointCloud(map, pose_compensation);
    const auto keyframe_pcd = ConvertToPointCloud(optimized_values, frame_database, keyframe_ids, pose_compensation);

    // save point clouds to ply file for debugging
    PointCloudXYZIRRgbSt pcd_msg;
    pcd_msg.insert(pcd_msg.end(), mapoints_pcd.begin(), mapoints_pcd.end());
    pcd_msg.insert(pcd_msg.end(), keyframe_pcd.begin(), keyframe_pcd.end());

    holo::pointcloud::SavePly(ply_file_name, pcd_msg);

    // map quality evaluation
    const auto quality =
        EvaluateMapQuality(map_name, optimized_values, map, trajectory, gridding_frame_ids, keyframe_ids, true);

    // if map quality is bad, save nothing
    if (quality == MapQuality::BAD)
    {
        LOG(ERROR) << "MapDatabaseManager --- map quality is BAD, nothing will be saved, see log for more details.\n";
        return;
    }

    // 2. save mappoints, and keyframes
    SaveMap(map, map_name);
    SaveKeyFrames(keyframes_database, map_name);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapDatabaseManager::SaveChassisState(const ChassisState& chassis_state, const std::string& map_name) const
{
    const std::string file_name = parameters_.map_data_dir + "/" + map_name + "/front_wheel_angle.txt";

    // save front_wheel_angle to file, which is required by PC module.
    std::fstream file(file_name, std::fstream::app);
    file << chassis_state.GetTimestamp().ToNsec() << " " << chassis_state.GetFrontWheelAngle() << "\n";
    file.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string MapDatabaseManager::HashingGridIndex(const int64_t index_x, const int64_t index_y, const int64_t index_z,
                                                 const int64_t index_angle) const
{
    return std::to_string(index_x) + "-" + std::to_string(index_y) + "-" + std::to_string(index_z) + "-" +
           std::to_string(index_angle);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string MapDatabaseManager::AssignPoseToVoxelGrid(const Pose3& pose) const
{
    // get distance resolution and angle resolution for voxel grid construction.
    int64_t dist_res  = parameters_.kf_selection_params.minimum_distance_interval;  // meter
    int64_t angle_res = parameters_.kf_selection_params.minimum_angle_interval;     // degree

    int64_t index_x     = (int64_t)pose.GetTranslation().GetX() / dist_res;
    int64_t index_y     = (int64_t)pose.GetTranslation().GetY() / dist_res;
    int64_t index_z     = (int64_t)pose.GetTranslation().GetZ() / dist_res;
    int64_t index_angle = (int64_t)pose.GetRotation().ComputeAngle() / angle_res;

    // hash mapping
    return HashingGridIndex(index_x, index_y, index_z, index_angle);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MapDatabaseManager::GriddingFrameIds
MapDatabaseManager::AssignFramesToVoxelGrid(const Values& values, const FramesDatabase& frame_database) const
{
    // construct the voxel grid.
    GriddingFrameIds gridding_frame_ids;

    for (const auto& indexed_frame : frame_database.GetAllFrames())
    {
        const auto& frame_id = indexed_frame.first;

        if (!values.exists(X(frame_id)))
        {
            continue;
        }

        // compute index in voxel grid
        const auto& current_pose = HoloGtsam::Convert(values.at(X(frame_id)).cast<gtsam::Pose3>());

        // hash mapping
        std::string key = AssignPoseToVoxelGrid(current_pose);
        gridding_frame_ids[key].emplace(frame_id);
    }

    return gridding_frame_ids;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<uint64_t> MapDatabaseManager::SelectKeyFrames(const Values& values, const FramesDatabase& frame_database,
                                                          const GriddingFrameIds& gridding_frame_ids) const
{
    // select frame with most excellent quality in each grid as keyframe
    /// @todo(Feng.Li 2020-10-21) for the quality metioned above, we only checking the associated landmark's number by
    /// now. we may also consider each landmark's confidence, covariance, physical attribute, etc. in future.
    std::vector<uint64_t> keyframe_ids;

    for (uint64_t first_frame_id = 0; first_frame_id < frame_database.Size(); ++first_frame_id)
    {
        if (frame_database.Exists(first_frame_id))
        {
            keyframe_ids.emplace_back(first_frame_id);
            break;
        }
    }

    // traversal the voxel grid
    for (const auto& item : gridding_frame_ids)
    {
        const auto&                   frame_ids                  = item.second;
        std::pair<uint64_t, uint16_t> best_kf_with_landmarks_num = std::make_pair(0, 0);  // frame id and score pair

        for (const auto& frame_id : frame_ids)
        {
            // retrieve frame data
            const auto& frame             = frame_database.GetFrame(frame_id);
            const auto& multi_camera_data = frame.multi_camera_data;
            uint16_t    max_lm_num        = 0;

            for (uint16_t camera_index = 0; camera_index < multi_camera_data.size(); camera_index++)
            {
                uint16_t lm_num = 0;

                for (const auto& lm_id : multi_camera_data.at(camera_index).associated_landmarks)
                {
                    if (lm_id >= 0 && values.exists(L(lm_id)))
                    {
                        lm_num++;
                    }
                }

                // recorde the maximum number of observed landmarks
                if (lm_num > max_lm_num)
                {
                    max_lm_num = lm_num;
                }
            }

            // checking if this frame associated to more landmarks
            if (max_lm_num < best_kf_with_landmarks_num.second)
            {
                continue;
            }

            // update the best keyframe
            best_kf_with_landmarks_num = std::make_pair(frame_id, max_lm_num);
        }

        // check keyframe condition
        if (best_kf_with_landmarks_num.second < parameters_.kf_selection_params.minimum_observed_landmark_num)
        {
            continue;
        }

        keyframe_ids.push_back(best_kf_with_landmarks_num.first);
    }

    return keyframe_ids;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Scalar MapDatabaseManager::ComputeMaxTravelDistanceWithoutKeyframes(const std::vector<Odometry>& trajectory,
                                                                    const GriddingFrameIds&      gridding_frame_ids,
                                                                    const std::vector<uint64_t>& keyframe_ids) const
{
    Scalar                max_distance_interval_no_keyframes = 0.0;
    std::set<std::string> checked_voxel_grid;

    for (size_t i = 0; i < trajectory.size(); i++)
    {
        // get voxel grid key for this pose
        const auto  current_pose = trajectory.at(i).GetPose();
        std::string key          = AssignPoseToVoxelGrid(current_pose);

        // check if this grid already be checked, and if this key exist in gridding_frame_ids
        if (checked_voxel_grid.count(key) || !gridding_frame_ids.count(key))
        {
            continue;
        }

        checked_voxel_grid.insert(key);

        static size_t last_index = i;

        // get all frame belongs to this grid
        const auto& current_gridding_frames_ids = gridding_frame_ids.at(key);

        // check if any keyframe id exist in frames of this grid
        bool has_keyframe_in_this_grid = false;

        for (const auto& key_frame_id : keyframe_ids)
        {
            if (current_gridding_frames_ids.count(key_frame_id))
            {
                has_keyframe_in_this_grid = true;
                break;
            }
        }

        if (!has_keyframe_in_this_grid)
        {
            continue;
        }

        // compute travel distance from last grid without keyframe
        Scalar dist = 0.0;

        for (size_t index = last_index + 1; index <= i; index++)
        {
            dist += trajectory.at(index - 1).GetPose().Dist(trajectory.at(index).GetPose());
        }

        if (dist > max_distance_interval_no_keyframes)
        {
            max_distance_interval_no_keyframes = dist;
        }

        last_index = i;
    }

    return max_distance_interval_no_keyframes;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MapDatabaseManager::IsThereKeyframeAroundStartPoint(const std::vector<Odometry>& trajectory,
                                                         const GriddingFrameIds&      gridding_frame_ids,
                                                         const std::vector<uint64_t>& keyframe_ids) const
{
    bool         has_keyframe_around_start_point = false;
    const Pose3  start_pose                      = trajectory.front().GetPose();
    const Scalar distance_range_of_start_point   = 6.0;   // meter
    const Scalar angle_range_of_start_point      = 30.0;  // degree

    for (const auto& odo : trajectory)
    {
        // compute relative pose with start_pose
        const auto delta_pose = odo.GetPose().Inverse() * start_pose;

        if (odo.GetPose().Dist(start_pose) > distance_range_of_start_point ||
            delta_pose.GetRotation().ComputeAngle() > angle_range_of_start_point)
        {
            break;
        }

        // get voxel grid key for this pose
        std::string key = AssignPoseToVoxelGrid(odo.GetPose());

        // check if this key exist in gridding_frame_ids
        if (!gridding_frame_ids.count(key))
        {
            continue;
        }

        // get all frame belongs to this grid
        const auto& current_gridding_frames_ids = gridding_frame_ids.at(key);

        // check if any keyframe id exist in frames of this grid
        for (const auto& key_frame_id : keyframe_ids)
        {
            if (current_gridding_frames_ids.count(key_frame_id))
            {
                has_keyframe_around_start_point = true;
                break;
            }
        }

        if (has_keyframe_around_start_point)
        {
            break;
        }
    }

    return has_keyframe_around_start_point;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapDatabaseManager::ComputeReprojectionErrorData(const Map& mappoints, MapQualityIndicators& indicator) const
{
    Scalar mean    = 0.0;
    Scalar median  = 0.0;
    Scalar maxmum  = 0.0;
    Scalar minimum = 0.0;

    Scalar sum_sequence = 0.0;

    // save the mean reprojection error of mappoint to sequence
    for (auto& mp : mappoints)
    {
        indicator.reprojection_error_data.reprojection_error_sequence.emplace_back(mp->mean_reprojection_error);
        sum_sequence += mp->mean_reprojection_error;
    }

    // compute the mean, median, maxmum, minimum of mean projection error
    mean = sum_sequence / mappoints.size();
    std::sort(indicator.reprojection_error_data.reprojection_error_sequence.begin(),
              indicator.reprojection_error_data.reprojection_error_sequence.end());
    median  = indicator.reprojection_error_data.reprojection_error_sequence[mappoints.size() / 2];
    maxmum  = indicator.reprojection_error_data.reprojection_error_sequence[mappoints.size() - 1];
    minimum = indicator.reprojection_error_data.reprojection_error_sequence[0];

    // save the data
    indicator.reprojection_error_data.mean    = mean;
    indicator.reprojection_error_data.median  = median;
    indicator.reprojection_error_data.maxmum  = maxmum;
    indicator.reprojection_error_data.minimum = minimum;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint64_t MapDatabaseManager::AssignReprojectionErrorToInterval(const Scalar& error, const Scalar& resolution) const
{
    Scalar temp = error / resolution;
    return uint64_t(temp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Scalar MapDatabaseManager::ComputeMeanAverageAccuracy(const Map& mappoints) const
{
    Scalar              resolution    = 0.1;
    uint64_t            intervals_num = 4.0 / resolution;
    std::vector<Scalar> frequency_distribution(intervals_num, 0.0);
    std::vector<Scalar> accumulate_frequency_distribution(intervals_num, 0.0);

    // compute the frequency distribution of reprojection error
    for (auto& mp : mappoints)
    {
        uint64_t key = AssignReprojectionErrorToInterval(mp->mean_reprojection_error, resolution);
        frequency_distribution[key]++;
    }

    // compute the accumulate frequency distribution
    for (auto& fd : frequency_distribution)
    {
        fd /= mappoints.size();
    }
    accumulate_frequency_distribution[0] = frequency_distribution[0];
    Scalar sum_frequency                 = accumulate_frequency_distribution[0];
    for (size_t i = 1; i < frequency_distribution.size(); i++)
    {
        accumulate_frequency_distribution[i] = frequency_distribution[i] + accumulate_frequency_distribution[i - 1];
        sum_frequency += accumulate_frequency_distribution[i];
    }

    // compute the MAA
    sum_frequency /= accumulate_frequency_distribution.size();

    LOG(INFO) << "MapDatabaseManager --- mAA: " << sum_frequency << "\n";
    LOG(INFO) << " MapDatabaseManager --- num of mappoints: " << mappoints.size() << "\n";

    // get  some frequency distribution data
    resolution    = 1;
    intervals_num = 4.0 / resolution;
    std::vector<Scalar> frequency_distribution_data(intervals_num, 0.0);
    for (auto& mp : mappoints)
    {
        uint64_t key = AssignReprojectionErrorToInterval(mp->mean_reprojection_error, resolution);
        frequency_distribution_data[key]++;
    }

    // compute frequency
    for (auto& fd : frequency_distribution_data)
    {
        fd /= mappoints.size();
    }

    // print frequency distribution data
    LOG(INFO) << "MapDatabaseManager --- error frequency distribution: " << frequency_distribution_data[0] << "|"
              << frequency_distribution_data[1] << "|" << frequency_distribution_data[2] << "|"
              << frequency_distribution_data[3] << "\n";

    return sum_frequency;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MapQuality MapDatabaseManager::EvaluateMapQuality(const std::string& map_name, const Values& optimized_value,
                                                  const Map& mappoints, const std::vector<Odometry>& trajectory,
                                                  const GriddingFrameIds&      gridding_frame_ids,
                                                  const std::vector<uint64_t>& keyframe_ids,
                                                  const bool                   is_avp_map) const
{
    const std::string quality_file = parameters_.map_data_dir + "/" + map_name + "/map_quality.txt";
    LOG(INFO) << "MapDatabaseManager --- start evaluate map quality of " << map_name << ":\n";

    // remove old file
    if (boost::filesystem::exists(quality_file))
    {
        boost::filesystem::remove(quality_file);
    }

    std::fstream file(quality_file, std::fstream::app);

    // create map quality indicators
    MapQualityIndicators map_quality_indicators;

    if (!is_avp_map)
    {
        // compute max vehicle speed
        for (const auto& vel : mapping_databases_.at(map_name).velocities)
        {
            const auto speed = vel.velocity.GetNorm() * 3.6;  // km/h

            if (speed > map_quality_indicators.max_speed)
            {
                map_quality_indicators.max_speed = speed;
            }
        }
    }

    // compute travel distance
    for (size_t i = 1; i < trajectory.size(); i++)
    {
        map_quality_indicators.travel_distance += trajectory.at(i - 1).GetPose().Dist(trajectory.at(i).GetPose());
    }

    // landmarks number
    map_quality_indicators.landmarks_number = mappoints.size();

    // landmark density
    map_quality_indicators.landmarks_density = 1.0 * mappoints.size() / map_quality_indicators.travel_distance;

    // voxel grid number
    map_quality_indicators.voxel_grid_number = gridding_frame_ids.size();

    // keyframe number
    map_quality_indicators.keyframe_number = keyframe_ids.size();

    // keyframe density
    map_quality_indicators.keyframe_density = 1.0 * keyframe_ids.size() / gridding_frame_ids.size();

    // check max travel distance without keyframes
    map_quality_indicators.max_travel_distance_without_keyframes =
        ComputeMaxTravelDistanceWithoutKeyframes(trajectory, gridding_frame_ids, keyframe_ids);

    if (!is_avp_map)
    {
        // check if exist keyframe around start point
        map_quality_indicators.is_there_keyframe_around_start_point =
            IsThereKeyframeAroundStartPoint(trajectory, gridding_frame_ids, keyframe_ids);
    }

    // compute statitisc data related to reprojection error
    ComputeReprojectionErrorData(mappoints, map_quality_indicators);

    // compute the mean average accuracy
    map_quality_indicators.mean_average_accuracy = ComputeMeanAverageAccuracy(mappoints);

    file << map_quality_indicators;
    LOG(INFO) << map_quality_indicators;

    (void)optimized_value;

    LOG(INFO) << "MapDatabaseManager --- evaluate map quality of " << map_name << " done.\n";
    LOG(INFO) << "MapDatabaseManager --- we have saved map quality to " << quality_file;
    file.close();

    if (!is_avp_map)
    {
        if (!map_quality_indicators.is_there_keyframe_around_start_point)
        {
            LOG(ERROR)
                << "MapDatabaseManager --- Do not have keyframe around start point. please check scenarios around "
                   "start point.\n";
            return MapQuality::BAD;
        }
    }
    if (map_quality_indicators.max_travel_distance_without_keyframes > parameters_.max_dis_without_kf)
    {
        LOG(ERROR) << "MapDatabaseManager --- The max distance between two keyframe: "
                   << map_quality_indicators.max_travel_distance_without_keyframes
                   << " is larger than threshold: " << parameters_.max_dis_without_kf;
        return MapQuality::BAD;
    }

    return MapQuality::MEDIUM;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapDatabaseManager::CleanMappingDatabase()
{
    mapping_databases_ = std::unordered_map<std::string, MappingDatabase>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapDatabaseManager::CleanUpDirectory(const bool& clear_merge_dir) const
{
    if (clear_merge_dir)
    {
        const auto        config_root_dir = holo::GetHoloConfigRootDirectory() + "/";
        const std::string merge_root_dir  = "holo_localization_parking/vslam/";

        // remove old merge result and create new directory
        boost::filesystem::path merge_path(config_root_dir + merge_root_dir + "multi_map_merging");
        if (boost::filesystem::exists(merge_path))
        {
            boost::filesystem::path merge_result_files(config_root_dir + merge_root_dir + "multi_map_merging" + "/");
            boost::filesystem::remove_all(merge_result_files);

            if (!boost::filesystem::create_directory(merge_path))
            {
                std::stringstream ss;
                ss << "MapDatabaseManager --- Failed to create dir: " << merge_path << "\n";
                throw std::runtime_error(ss.str());
            }
        }
        else if (!boost::filesystem::create_directory(merge_path))
        {
            std::stringstream ss;
            ss << "MapDatabaseManager --- Failed to create dir: " << merge_path << "\n";
            throw std::runtime_error(ss.str());
        }

        // remove old loop images and create new directory
        boost::filesystem::path loop_image_pair_path(config_root_dir + merge_root_dir + "loop_images");
        if (boost::filesystem::exists(loop_image_pair_path))
        {
            boost::filesystem::path loop_image_pair_files(config_root_dir + merge_root_dir + "loop_images" + "/");
            boost::filesystem::remove_all(loop_image_pair_files);

            if (!boost::filesystem::create_directory(loop_image_pair_path))
            {
                std::stringstream ss;
                ss << "MapDatabaseManager --- Failed to create dir: " << loop_image_pair_path << "\n";
                throw std::runtime_error(ss.str());
            }
        }
        else if (!boost::filesystem::create_directory(loop_image_pair_path))
        {
            std::stringstream ss;
            ss << "MapDatabaseManager --- Failed to create dir: " << loop_image_pair_path << "\n";
            throw std::runtime_error(ss.str());
        }
    }
    else
    {
        /// get parent directory
        const auto directory = parameters_.map_data_dir + "/" + parameters_.map_names.front() + "/";

        // remove all old file if exist
        if (boost::filesystem::is_directory(directory))
        {
            boost::filesystem::remove_all(directory);
        }

        // create directory to save mapping data
        if (!boost::filesystem::create_directories(directory))
        {
            std::stringstream ss;
            ss << "MapDatabaseManager --- Failed to create dir: " << directory << "\n";
            throw std::runtime_error(ss.str());
        }

        // create directory to save image
        if (parameters_.save_image && !boost::filesystem::create_directory(directory + "images/"))
        {
            std::stringstream ss;
            ss << "MapDatabaseManager --- Failed to create dir: " << directory << "images/\n";
            throw std::runtime_error(ss.str());
        }

        // create directory to save features
        if (!boost::filesystem::create_directory(directory + "features/"))
        {
            std::stringstream ss;
            ss << "MapDatabaseManager --- Failed to create dir: " << directory << "features/\n";
            throw std::runtime_error(ss.str());
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Values MapDatabaseManager::LoadXVBValues(const std::string& file_name) const
{
    if (!boost::filesystem::exists(file_name))
    {
        LOG(ERROR) << "MapDatabaseManager --- values file: " << file_name << " does not exist ";
        throw std::runtime_error("No such file or directory!\n");
    }

    LOG(INFO) << "MapDatabaseManager --- trying to load values from " << file_name << "\n";
    std::ifstream ifs(file_name, std::fstream::in);
    Values        values;

    bool first_line = true;
    // read values
    while (ifs.good())
    {
        if (first_line)
        {
            bool enable_estimation_with_acc = false;
            ifs >> enable_estimation_with_acc;
            SlidingWindowState::enable_estimation_with_acc = enable_estimation_with_acc;
            first_line                                     = false;
            LOG(INFO) << "MapDatabaseManager --- enable_estimation_with_acc = " << enable_estimation_with_acc;
            continue;
        }

        // frame_id tx ty tz qw qx qy qz vx vy vz bias_acc_x bias_acc_y bias_acc_z bias_gyro_x bias_gyro_y bias_gyro_z
        uint64_t frame_id = 0;
        Scalar   tx = 0.0, ty = 0.0, tz = 0.0;
        Scalar   qw = 0.0, qx = 0.0, qy = 0.0, qz = 0.0;
        Scalar   vx = 0.0, vy = 0.0, vz = 0.0;
        Scalar   bias_acc_x = 0.0, bias_acc_y = 0.0, bias_acc_z = 0.0;
        Scalar   bias_gyro_x = 0.0, bias_gyro_y = 0.0, bias_gyro_z = 0.0;

        if (SlidingWindowState::enable_estimation_with_acc)
        {
            ifs >> frame_id >> tx >> ty >> tz >> qw >> qx >> qy >> qz >> vx >> vy >> vz >> bias_acc_x >> bias_acc_y >>
                bias_acc_z >> bias_gyro_x >> bias_gyro_y >> bias_gyro_z;
        }
        else
        {
            ifs >> frame_id >> tx >> ty >> tz >> qw >> qx >> qy >> qz >> bias_gyro_x >> bias_gyro_y >> bias_gyro_z;
        }

        if (ifs.fail())
        {
            break;
        }

        // construct pose
        Point3     t(tx, ty, tz);
        Rot3       r(Quaternion(qw, qx, qy, qz).ToRotationMatrix());
        const auto pose = holo::localization::HoloGtsam::Convert(Pose3(r, t));

        // construct bias
        gtsam::imuBias::ConstantBias bias(HoloGtsam::Convert(Vector3(bias_acc_x, bias_acc_y, bias_acc_z)),
                                          HoloGtsam::Convert(Vector3(bias_gyro_x, bias_gyro_y, bias_gyro_z)));

        // insert to values
        if (values.exists(X(frame_id)))
        {
            LOG(ERROR) << "MapDatabaseManager --- LoadXVBValues. frame id: " << frame_id
                       << " already exist in values.\n";
            throw std::runtime_error("MapDatabaseManager --- LoadXVBValues. frame id already exist in values.");
        }

        values.insert(X(frame_id), pose);

        if (SlidingWindowState::enable_estimation_with_acc)
        {
            values.insert(V(frame_id), HoloGtsam::Convert(Vector3(vx, vy, vz)));
            values.insert(B(frame_id), bias);
        }
        else
        {
            values.insert(B(frame_id), gtsam::Vector3(bias_gyro_x, bias_gyro_y, bias_gyro_z));
        }
    }

    LOG(INFO) << "MapDatabaseManager --- load values done. total values: " << values.size() << "\n";
    return values;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TracksDatabase MapDatabaseManager::LoadTracks(const std::string&           file_name,
                                              const CameraParameters::Ptr& camera_parameters) const
{
    std::ifstream fin(file_name);

    if (!fin)
    {
        LOG(ERROR) << "MapDatabaseManager --- LoadTracks, could not open " << file_name;
        return {};
    }

    // total landmarks number
    uint64_t landmark_num;
    fin.read((char*)&landmark_num, sizeof(uint64_t));

    // descriptor dimension
    uint16_t descriptor_dimension;
    fin.read((char*)&descriptor_dimension, sizeof(uint16_t));

    TracksDatabase tracks_database;

    // read data one by one
    for (uint64_t i = 0; i < landmark_num; i++)
    {
        // read landmark id
        uint64_t landmark_id;
        fin.read((char*)&landmark_id, sizeof(uint64_t));

        // read position
        Scalar x, y, z;
        fin.read((char*)&x, sizeof(Scalar));
        fin.read((char*)&y, sizeof(Scalar));
        fin.read((char*)&z, sizeof(Scalar));

        // create landmark
        Landmark landmark(landmark_id, gtsam::Point3(x, y, z));

        // create track parameters
        FeatureTrack::Parameters::ConstPtr track_params = std::make_shared<FeatureTrack::Parameters>(true, true);

        // create new track
        FeatureTrack track(track_params, camera_parameters, landmark_id, {}, FeatureTrack::State::FRESH, landmark);

        // load track state
        uint16_t state;
        fin.read((char*)&state, sizeof(uint16_t));

        // if state is CANDIDATE, we will triangulate is again
        if (state == static_cast<uint16_t>(FeatureTrack::State::CANDIDATE))
        {
            track = track.CreateNewTrackByUpdatingState(FeatureTrack::State::CANDIDATE, gtsam::Point3(x, y, z));
        }

        // read measurement length
        uint16_t length = 0;
        fin.read((char*)&length, sizeof(uint16_t));

        // read measurement
        for (uint16_t i = 0; i < length; i++)
        {
            // read frame id
            uint64_t frame_id = 0;
            fin.read((char*)&frame_id, sizeof(uint64_t));

            // read camera id
            uint16_t camera_id = 0;
            fin.read((char*)&camera_id, sizeof(uint16_t));

            // read image point
            Scalar img_pt_x = 0.0;
            Scalar img_pt_y = 0.0;
            fin.read((char*)&img_pt_x, sizeof(Scalar));
            fin.read((char*)&img_pt_y, sizeof(Scalar));

            // read normalized point
            Scalar normalized_point_x = 0.0;
            Scalar normalized_point_y = 0.0;
            Scalar normalized_point_z = 0.0;
            fin.read((char*)&normalized_point_x, sizeof(Scalar));
            fin.read((char*)&normalized_point_y, sizeof(Scalar));
            fin.read((char*)&normalized_point_z, sizeof(Scalar));

            // read semantic label
            SemanticLabel semantic_label;
            fin.read((char*)&semantic_label, sizeof(SemanticLabel));

            // read descriptor
            cv::Mat descriptor;
            descriptor.create(1, descriptor_dimension, CV_32FC1);

            for (uint16_t j = 0; j < descriptor_dimension; j++)
            {
                fin.read((char*)&descriptor.at<float32_t>(0, j), sizeof(float32_t));
            }

            // read score
            Scalar score = -1.0;
            fin.read((char*)&score, sizeof(Scalar));

            // create new feature and update track measurement
            Feature feature(cv::Point2f(img_pt_x, img_pt_y), descriptor,
                            Point3(normalized_point_x, normalized_point_y, normalized_point_z), camera_id, score,
                            semantic_label);

            // check if this frame id exists in values
            // if (!mapping_database_.xvb_values.exists(X(frame_id)))
            // {
            //     continue;
            // }

            if (track.Measurements().empty())
            {
                FeatureTrack::Measurement measurement =
                    std::make_pair(frame_id, FeatureTrack::CameraIndexedFeature{{camera_id, feature}});
                track = FeatureTrack(track_params, camera_parameters, landmark_id, {measurement}, track.GetState(),
                                     landmark);
            }
            else
            {
                track = track.CreateNewTrackByAddingNewestMeasurement(frame_id, feature);
            }
        }

        if (track.Length() < 2)
        {
            continue;
        }

        tracks_database.AddFeatureTrack(track);
    }

    LOG(INFO) << "MapDatabaseManager --- load tracks done. total tracks: " << tracks_database.Size() << "\n";

    return tracks_database;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ParkingSlotTracksDatabase MapDatabaseManager::LoadParkingSlotTracks(const std::string& file_name) const
{
    std::ifstream fin(file_name);
    if (!fin)
    {
        LOG(ERROR) << "MapDatabaseManager --- LoadTracks, could not open " << file_name;
        return {};
    }

    ParkingSlotTracksDatabase parking_slot_track_database;

    // total parking slot tracks number
    uint64_t parking_slot_track_num;
    fin.read((char*)&parking_slot_track_num, sizeof(uint64_t));

    // read data one by one
    for (uint16_t i = 0; i < parking_slot_track_num; ++i)
    {
        semantic::ParkingSlotTrack parking_slot_track;

        // read track id
        uint64_t track_id;
        fin.read((char*)&track_id, sizeof(uint64_t));
        parking_slot_track.id = track_id;

        uint64_t track_timestamp = 0;
        fin.read((char*)&track_timestamp, sizeof(uint64_t));
        parking_slot_track.timestamp = Timestamp(track_timestamp);

        uint64_t plane_id;
        fin.read((char*)&plane_id, sizeof(uint64_t));
        parking_slot_track.plane_id = plane_id;

        uint16_t state;
        fin.read((char*)&(state), sizeof(uint16_t));
        parking_slot_track.state = semantic::ParkingSlotTrack::State(state);

        // read measurement num
        uint64_t measurement_num;
        fin.read((char*)&measurement_num, sizeof(uint64_t));

        ParkingSlotType parking_slot;
        parking_slot.is_valid = true;

        for (uint64_t j = 0; j < measurement_num; ++j)
        {
            // read frame id
            uint64_t frame_id = 0;
            fin.read((char*)&frame_id, sizeof(uint64_t));

            uint64_t parking_slot_timestamp = 0;
            fin.read((char*)&parking_slot_timestamp, sizeof(uint64_t));

            Scalar p_x, p_y, p_z;

            fin.read((char*)&p_x, sizeof(Scalar));
            fin.read((char*)&p_y, sizeof(Scalar));
            fin.read((char*)&p_z, sizeof(Scalar));
            Point3 vertex_0(p_x, p_y, p_z);
            parking_slot.vertices[0] = vertex_0;

            fin.read((char*)&p_x, sizeof(Scalar));
            fin.read((char*)&p_y, sizeof(Scalar));
            fin.read((char*)&p_z, sizeof(Scalar));
            Point3 vertex_1(p_x, p_y, p_z);
            parking_slot.vertices[1] = vertex_1;

            bool_t is_rear_vertex_available;
            fin.read((char*)&is_rear_vertex_available, sizeof(bool_t));
            parking_slot.is_rear_vertex_available = is_rear_vertex_available;

            if (is_rear_vertex_available)
            {
                fin.read((char*)&p_x, sizeof(Scalar));
                fin.read((char*)&p_y, sizeof(Scalar));
                fin.read((char*)&p_z, sizeof(Scalar));
                Point3 vertex_2(p_x, p_y, p_z);
                parking_slot.vertices[2] = vertex_2;

                fin.read((char*)&p_x, sizeof(Scalar));
                fin.read((char*)&p_y, sizeof(Scalar));
                fin.read((char*)&p_z, sizeof(Scalar));
                Point3 vertex_3(p_x, p_y, p_z);
                parking_slot.vertices[3] = vertex_3;
            }

            bool_t is_center_vertex_available;
            fin.read((char*)&is_center_vertex_available, sizeof(bool_t));
            parking_slot.is_center_vertex_available = is_center_vertex_available;

            if (is_center_vertex_available)
            {
                fin.read((char*)&p_x, sizeof(Scalar));
                fin.read((char*)&p_y, sizeof(Scalar));
                fin.read((char*)&p_z, sizeof(Scalar));
                Point3 center_vertex(p_x, p_y, p_z);
                parking_slot.center_vertex = center_vertex;
            }
            parking_slot_track.measurements.push_back(
                std::make_pair(frame_id, std::make_pair(Timestamp(parking_slot_timestamp), parking_slot)));
        }
        parking_slot_track_database.AddParkingSlotTrack(parking_slot_track);
    }
    fin.close();

    LOG(INFO) << " LoadParkingSlotTrack --- successfully load parking slot track, total parking slot track num: "
              << parking_slot_track_database.Size() << "\n";

    return parking_slot_track_database;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FrameIndexedImages MapDatabaseManager::LoadImages(const std::string& file_name) const
{
    if (!boost::filesystem::exists(file_name))
    {
        LOG(WARNING) << "MapDatabaseManager --- image file: " << file_name << " does not exist ";
        return {};
    }

    LOG(INFO) << "MapDatabaseManager --- trying to load images from " << file_name << "\n";
    std::ifstream      ifs(file_name, std::fstream::in);
    FrameIndexedImages frame_indexed_images;

    // read image
    while (ifs.good())
    {
        // frame_id camera_index image_name
        uint64_t    frame_id     = 0;
        uint16_t    camera_index = 0;
        std::string image_name   = "";

        ifs >> frame_id >> camera_index >> image_name;

        if (ifs.fail())
        {
            break;
        }

        frame_indexed_images[frame_id].emplace(camera_index, image_name);
    }

    LOG(INFO) << "MapDatabaseManager --- load images done. total images: " << frame_indexed_images.size() << "\n";

    return frame_indexed_images;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FrameIndexedFeatures MapDatabaseManager::LoadFeatures(const std::string& file_name) const
{
    if (!boost::filesystem::exists(file_name))
    {
        LOG(ERROR) << "MapDatabaseManager --- features file: " << file_name << " does not exist ";
        throw std::runtime_error("No such file or directory!\n");
    }

    LOG(INFO) << "MapDatabaseManager --- trying to load features from " << file_name << "\n";
    std::ifstream        ifs(file_name, std::fstream::in);
    FrameIndexedFeatures frame_indexed_features;

    // read image
    while (ifs.good())
    {
        // frame_id camera_index image_name
        uint64_t    frame_id          = 0;
        uint16_t    camera_index      = 0;
        std::string feature_file_name = "";

        ifs >> frame_id >> camera_index >> feature_file_name;

        if (ifs.fail())
        {
            break;
        }

        // load features
        std::ifstream fin(feature_file_name);

        if (!fin)
        {
            LOG(ERROR) << "MapDatabaseManager --- LoadFeatures, could not open " << feature_file_name;
            throw std::runtime_error("MapDatabaseManager --- LoadFeatures, no such file or directory.\n");
        }

        // total feature number
        uint16_t features_num;
        fin.read((char*)&features_num, sizeof(uint16_t));

        // descriptor dimension
        uint16_t descriptor_dimension;
        fin.read((char*)&descriptor_dimension, sizeof(uint16_t));

        Features features;
        features.reserve(features_num);

        // read features
        for (uint16_t i = 0; i < features_num; i++)
        {
            // read image point
            Scalar img_pt_x = 0.0;
            Scalar img_pt_y = 0.0;
            fin.read((char*)&img_pt_x, sizeof(Scalar));
            fin.read((char*)&img_pt_y, sizeof(Scalar));

            // read normalized point
            Scalar normalized_point_x = 0.0;
            Scalar normalized_point_y = 0.0;
            Scalar normalized_point_z = 0.0;
            fin.read((char*)&normalized_point_x, sizeof(Scalar));
            fin.read((char*)&normalized_point_y, sizeof(Scalar));
            fin.read((char*)&normalized_point_z, sizeof(Scalar));

            // read category
            SemanticLabel semantic_label;
            fin.read((char*)&semantic_label, sizeof(SemanticLabel));

            // read descriptor
            cv::Mat descriptor;
            descriptor.create(1, descriptor_dimension, CV_32FC1);

            for (uint16_t j = 0; j < descriptor_dimension; j++)
            {
                fin.read((char*)&descriptor.at<float32_t>(0, j), sizeof(float32_t));
            }

            // load camera id
            uint16_t camera_id;
            fin.read((char*)&camera_id, sizeof(uint16_t));

            // load score
            Scalar score = -1.0;
            fin.read((char*)&score, sizeof(Scalar));
            // stores this feature
            features.emplace_back(cv::Point2f(img_pt_x, img_pt_y), descriptor,
                                  Point3(normalized_point_x, normalized_point_y, normalized_point_z), camera_id, score,
                                  semantic_label);
        }
        frame_indexed_features[frame_id].emplace(camera_index, features);
    }

    LOG(INFO) << "MapDatabaseManager --- load features done. total frames: " << frame_indexed_features.size() << "\n";

    return frame_indexed_features;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<std::vector<Imu>> MapDatabaseManager::LoadImus(const std::string& file_name) const
{
    if (!boost::filesystem::exists(file_name))
    {
        LOG(ERROR) << "MapDatabaseManager --- imus file: " << file_name << " does not exist ";
        throw std::runtime_error("No such file or directory!\n");
    }

    LOG(INFO) << "MapDatabaseManager --- trying to load imus from " << file_name << "\n";
    std::ifstream                 ifs(file_name, std::fstream::in);
    std::vector<std::vector<Imu>> result;

    // read imus
    while (ifs.good())
    {
        uint16_t imu_data_number = 0;
        ifs >> imu_data_number;

        if (imu_data_number == 0)
        {
            continue;
        }

        std::vector<Imu> imus;
        imus.reserve(imu_data_number);

        for (size_t i = 0; i < imu_data_number; i++)
        {
            uint64_t timestamp = 0;
            Scalar   acc_x = 0.0, acc_y = 0.0, acc_z = 0.0;
            Scalar   gyro_x = 0.0, gyro_y = 0.0, gyro_z = 0.0;
            ifs >> timestamp >> acc_x >> acc_y >> acc_z >> gyro_x >> gyro_y >> gyro_z;

            if (ifs.fail())
            {
                break;
            }

            // construct imu measurement
            Imu imu;
            imu.SetTimestamp(Timestamp(timestamp));
            imu.SetAngularVelocity(Vector3(gyro_x, gyro_y, gyro_z));
            imu.SetLinearAcceleration(Vector3(acc_x, acc_y, acc_z));
            imus.emplace_back(imu);
        }

        result.push_back(imus);
    }

    LOG(INFO) << "MapDatabaseManager --- load imus done. total imu blocks: " << result.size() << "\n";

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<VelocityMeasurement> MapDatabaseManager::LoadVelocities(const std::string& file_name) const
{
    if (!boost::filesystem::exists(file_name))
    {
        LOG(ERROR) << "MapDatabaseManager --- velocity file: " << file_name << " does not exist ";
        throw std::runtime_error("No such file or directory!\n");
    }

    LOG(INFO) << "MapDatabaseManager --- trying to load velocities from " << file_name << "\n";
    std::ifstream                    ifs(file_name, std::fstream::in);
    std::vector<VelocityMeasurement> result;

    // read imus
    while (ifs.good())
    {
        uint64_t timestamp = 0;
        Scalar   vx = 0.0, vy = 0.0, vz = 0.0;
        ifs >> timestamp >> vx >> vy >> vz;

        if (ifs.fail())
        {
            break;
        }

        // construct velocit measurement
        VelocityMeasurement vel_m;
        vel_m.timestamp = Timestamp(timestamp);
        vel_m.velocity  = Vector3(vx, vy, vz);
        result.push_back(vel_m);
    }

    LOG(INFO) << "MapDatabaseManager --- load velocities done. total velocity measurement num: " << result.size()
              << "\n";
    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<WheelIntegrationMeasurement>
MapDatabaseManager::LoadWheelIntegrationMeasurements(const std::string& file_name) const
{
    if (!boost::filesystem::exists(file_name))
    {
        LOG(ERROR) << "MapDatabaseManager --- wheel integration file: " << file_name << " does not exist ";
        throw std::runtime_error("No such file or directory!\n");
    }

    LOG(INFO) << "MapDatabaseManager --- trying to load wheel integration from " << file_name << "\n";
    std::ifstream                            ifs(file_name, std::fstream::in);
    std::vector<WheelIntegrationMeasurement> result;

    // read wheel integration
    while (ifs.good())
    {
        uint64_t start_t = 0;
        uint64_t end_t   = 0;
        Scalar   dx = 0.0, dy = 0.0, d_yaw = 0.0;
        ifs >> start_t >> end_t >> dx >> dy >> d_yaw;

        if (ifs.fail())
        {
            break;
        }

        result.emplace_back(Timestamp(start_t), Timestamp(end_t), dx, dy, d_yaw);
    }

    LOG(INFO) << "MapDatabaseManager --- load wheel integration done. total velocity measurement num: " << result.size()
              << "\n";
    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<UtmPosition> MapDatabaseManager::LoadUTMPositions(const std::string& file_name) const
{
    if (!boost::filesystem::exists(file_name))
    {
        LOG(ERROR) << "MapDatabaseManager --- position file: " << file_name << " does not exist ";
        return {};
    }

    LOG(INFO) << "MapDatabaseManager --- trying to load utm positions from " << file_name << "\n";
    std::ifstream            ifs(file_name, std::fstream::in);
    std::vector<UtmPosition> result;

    // read imus
    while (ifs.good())
    {
        uint64_t timestamp = 0;
        Scalar   p_x = 0.0, p_y = 0.0, p_z = 0.0;
        Scalar   std_x = 0.0, std_y = 0.0, std_z = 0.0;
        ifs >> timestamp >> p_x >> p_y >> p_z >> std_x >> std_y >> std_z;

        if (ifs.fail())
        {
            break;
        }

        // construct velocit measurement
        UtmPosition position(Timestamp(timestamp), Point3(p_x, p_y, p_z), Vector3(std_x, std_y, std_z));
        result.push_back(position);
    }

    LOG(INFO) << "MapDatabaseManager --- load positions done. total position measurement num: " << result.size()
              << "\n";

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<std::pair<Timestamp, uint64_t>>
MapDatabaseManager::LoadTimeStampAndFrameId(const std::string& file_name) const
{
    if (!boost::filesystem::exists(file_name))
    {
        LOG(ERROR) << "MapDatabaseManager --- timestamp file: " << file_name << " does not exist ";
        throw std::runtime_error("No such file or directory!\n");
    }

    LOG(INFO) << "MapDatabaseManager --- trying to load timestamp and frame id from " << file_name << "\n";
    std::ifstream                               ifs(file_name, std::fstream::in);
    std::vector<std::pair<Timestamp, uint64_t>> result;

    // read imus
    while (ifs.good())
    {
        uint64_t timestamp = 0, frame_id = 0;
        ifs >> timestamp >> frame_id;

        if (ifs.fail())
        {
            break;
        }

        result.push_back(std::make_pair(holo::Timestamp(timestamp), frame_id));
    }

    LOG(INFO) << "MapDatabaseManager --- load timestamp and frame id done. total frame num: " << result.size() << "\n";

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::pair<Map, std::vector<Odometry>> MapDatabaseManager::CreateMapAndTrajectory(
    const Values& values, const TracksDatabase& tracks_database, const MappingDatabase& mapping_database) const
{
    uint64_t used_tracks = 0;

    // create map
    Map         map;
    const auto& indexed_tracks = tracks_database.GetAllTracks();

    for (const auto& indexed_track : indexed_tracks)
    {
        const auto& track    = indexed_track.second;
        const auto  landmark = track.GetLandmark();

        if (!landmark)
        {
            continue;
        }
        const auto& lm_id = landmark->Id();

        if (!values.exists(L(lm_id)))
        {
            continue;
        }
        used_tracks++;

        // get position
        const Point3 position = HoloGtsam::Convert(values.at(L(lm_id)).cast<gtsam::Point3>());

        // get reference measurement
        // set the oldest measurement which still exist in sliding window as this mappoint's reference measurement
        FeatureTrack::Measurement reference_measurement;

        for (size_t i = 0; i < track.Length(); i++)
        {
            reference_measurement = track.Measurements(i);

            if (values.exists(X(reference_measurement.first)))
            {
                break;
            }
        }

        // check validity of reference_measurement
        if (reference_measurement.second.empty())
        {
            throw std::runtime_error("MapDatabaseManager --- CreateMapAndPath, reference_measurement is "
                                     "invalid. something must be wrong.\n");
        }

        const auto& reference_frame_id                  = reference_measurement.first;
        const auto& reference_feature_with_camera_index = reference_measurement.second;

        // create a new mappoint
        MapPoint mp;

        /// @todo(Feng. Li 2020-02-13) in multi-camera vslam system, if a feature track can be tracked by different
        /// camera. then how can we select the direction for the mappoint? since by now we just track features at
        /// the same camera, here we just select the first one, there shouldn't be much problem. if we enbale
        /// tracking feature at different camera, we should come back to fix this issue.
        const auto& camera_index      = reference_feature_with_camera_index.begin()->first;
        const auto& reference_feature = reference_feature_with_camera_index.begin()->second;
        const Pose3 T_wc              = HoloGtsam::Convert(values.at(X(reference_frame_id)).cast<gtsam::Pose3>()) *
                           mapping_database.camera_parameters->extrinsics.at(camera_index);
        const auto direction = T_wc.GetRotation().Rotate(reference_feature.normalized_point.ToVector());

        // select the best category of this track
        const auto semantic_label = track.GetLabel();

        // assign the category to mappoint which satisfies the conditions
        // we only add the static and vehicle mappoint to map for localization
        if ((semantic_label == SemanticLabel::STATIC || semantic_label == SemanticLabel::VEHICLE))
        {
            mp.semantic_label = semantic_label;
        }
        else
        {
            continue;
        }

        // compute reprojection errors in whole track of the mappoint
        // and the mean reprojection error of this mappoint
        std::vector<Scalar> measurement_errors;
        for (uint64_t measurement_index = 0; measurement_index < track.Length(); measurement_index++)
        {
            // check if the measurement has data
            if (track.Measurements(measurement_index).second.empty())
            {
                continue;
            }
            boost::optional<Scalar> reprojection_error = track.ComputePiexlReprojectionError(values, measurement_index);
            if (!reprojection_error)
            {
                continue;
            }
            mp.reprojection_errors.emplace_back(*reprojection_error);
            measurement_errors.emplace_back(*reprojection_error);
        }

        mp.mean_reprojection_error =
            std::accumulate(measurement_errors.begin(), measurement_errors.end(), 0.0) / measurement_errors.size();

        mp.reference_pose     = T_wc;
        mp.reference_frame_id = reference_frame_id;
        mp.direction          = direction / direction.GetNorm();
        mp.score              = reference_feature.score;

        mp.position = position;
        /// @todo(Feng. Li) select best descriptor of this track
        mp.descriptor = *(reference_feature.optional_descriptor);
        mp.life_long_states.push_back(MapPointState::MATCHED);
        mp.remember_rate = std::exp(-(1.0 / 19));

        /// @todo compute covariance of this mappoint

        map.push_back(std::make_shared<MapPoint>(mp));
    }

    LOG(INFO) << "MapDatabaseManager --- create map success , total tracks num: " << indexed_tracks.size()
              << "  used tracks num: " << used_tracks << "  map size: " << map.size() << "\n";

    // create trajectory
    std::vector<Odometry> trajectory;

    for (const auto& frame_id_to_timestamp : mapping_database.frame_id_to_timestamp)
    {
        const auto& frame_id  = frame_id_to_timestamp.first;
        const auto& timestamp = frame_id_to_timestamp.second;

        // retrieve pose and velocity from values.
        if (!values.exists(X(frame_id)))
        {
            continue;
        }

        const auto     pose = HoloGtsam::Convert(values.at(X(frame_id)).cast<gtsam::Pose3>());
        gtsam::Vector3 velocity;
        if (mapping_database.enable_estimation_with_acc)
        {
            velocity = values.at(V(frame_id)).cast<gtsam::Vector3>();
        }

        // create odometry.
        Odometry odom;
        odom.SetTimestamp(timestamp);
        odom.SetChildCoordinate(holo::Coordinate());
        odom.SetStatus(Odometry::Status::ALLGOOD);
        odom.SetSource(Odometry::Source::VISION);
        odom.SetPose(pose);
        odom.SetVelocity(Vector6(velocity[0], velocity[1], velocity[2], 0.0, 0.0, 0.0));

        trajectory.push_back(odom);
    }

    return std::make_pair(map, trajectory);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<ParkingSlotType> MapDatabaseManager::CreateParkingSlotMap(const Values&          values,
                                                                      const MappingDatabase& mapping_database) const
{
    std::vector<ParkingSlotType> result;

    const auto& all_parking_slot_tracks = mapping_database.parking_slot_tracks_database.GetAllParkingSlotTracks();

    ParkingSlotType out;
    for (const auto& parking_slot_track : all_parking_slot_tracks)
    {
        out.id                       = parking_slot_track.id;
        out.is_rear_vertex_available = true;
        const auto& vertices         = parking_slot_track.GetIndexedVertices(0);
        for (const auto& vertex : vertices)
        {
            if (values.exists(S(vertex.id)))
            {
                const Point3   point        = HoloGtsam::Convert(values.at<gtsam::Point3>(S(vertex.id)));
                const uint64_t vertex_index = Utility::UnHashId(vertex.id).second;
                if (vertex_index < 4u)
                {
                    out.vertices[vertex_index] = point;
                }
                else if (vertex_index == 4u)
                {
                    out.center_vertex = point;
                }
                else
                {
                    throw std::out_of_range("set vertex out of range");
                }
            }
        }
        result.push_back(out);
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PointCloudXYZIRRgbSt MapDatabaseManager::ConvertToPointCloud(const Map& map, const Pose3& pose_compensation) const
{
    PointCloudXYZIRRgbSt pcd_msg(map.size());
    pcd_msg.SetTimestamp(holo::Timestamp());
    pcd_msg.SetCoordinate(holo::Coordinate());
    pcd_msg.SetPose(Pose3::Identity().Cast<::holo::float32_t>());

    for (uint64_t i = 0; i < map.size(); i++)
    {
        Point3  p  = pose_compensation * map.at(i)->position;
        Point3f pt = p.Cast<::holo::float32_t>();
        pcd_msg[i].Set(pt.GetX(), pt.GetY(), pt.GetZ());

        Scalar intensity = map.at(i)->mean_reprojection_error;
        pcd_msg[i].SetIntensity(2 * intensity);
    }
    return pcd_msg;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PointCloudXYZIRRgbSt MapDatabaseManager::ConvertToPointCloud(const std::vector<Odometry>& trajectory,
                                                             const Pose3&                 pose_compensation) const
{
    PointCloudXYZIRRgbSt pcd_msg(trajectory.size());
    pcd_msg.SetTimestamp(holo::Timestamp());
    pcd_msg.SetCoordinate(holo::Coordinate());
    pcd_msg.SetPose(Pose3::Identity().Cast<::holo::float32_t>());

    for (uint64_t i = 0; i < trajectory.size(); i++)
    {
        Point3  p  = pose_compensation * trajectory.at(i).GetPose().GetTranslation();
        Point3f pt = p.Cast<::holo::float32_t>();
        pcd_msg[i].Set(pt.GetX(), pt.GetY(), pt.GetZ());
        pcd_msg[i].SetIntensity(0.0);
    }
    return pcd_msg;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PointCloudXYZIRRgbSt MapDatabaseManager::ConvertToPointCloud(const Values&                optimized_values,
                                                             const FramesDatabase&        frame_database,
                                                             const std::vector<uint64_t>& keyframe_ids,
                                                             const Pose3&                 pose_compensation) const
{
    PointCloudXYZIRRgbSt pcd_msg;

    // traversal all frame
    for (const auto& frame_id : keyframe_ids)
    {
        if (!optimized_values.exists(X(frame_id)) || !frame_database.Exists(frame_id))
        {
            throw std::runtime_error(
                "ConvertToPointCloud --- given keyframe id does not exist in values or frame database, "
                "this should not happened!");
        }

        // get vehicle pose of this keyframe
        const auto& T_wb = HoloGtsam::Convert(optimized_values.at(X(frame_id)).cast<gtsam::Pose3>());

        // get frame
        const auto& frame = frame_database.GetFrame(frame_id);

        // traversal all camera data
        for (uint16_t camera_index = 0; camera_index < frame.multi_camera_data.size(); camera_index++)
        {
            // compute camera pose in world
            const auto& T_bc = frame.camera_parameters->extrinsics.at(camera_index);
            const auto  T_wc = pose_compensation * T_wb * T_bc;
            // create points which can represent camera view
            // create vertex
            Point3 inner_vertex0 = T_wc * Point3(0.2, 0.2, 0);
            Point3 inner_vertex1 = T_wc * Point3(-0.2, 0.2, 0);
            Point3 inner_vertex2 = T_wc * Point3(0.2, -0.2, 0);
            Point3 inner_vertex3 = T_wc * Point3(-0.2, -0.2, 0);

            Point3 outer_vertex0 = T_wc * Point3(0.4, 0.4, 0.2);
            Point3 outer_vertex1 = T_wc * Point3(-0.4, 0.4, 0.2);
            Point3 outer_vertex2 = T_wc * Point3(0.4, -0.4, 0.2);
            Point3 outer_vertex3 = T_wc * Point3(-0.4, -0.4, 0.2);

            // create point between vertex
            auto inner_vertex01 = GeneratePointCloudBetween(inner_vertex0, inner_vertex1);
            auto inner_vertex02 = GeneratePointCloudBetween(inner_vertex0, inner_vertex2);
            auto inner_vertex13 = GeneratePointCloudBetween(inner_vertex1, inner_vertex3);
            auto inner_vertex23 = GeneratePointCloudBetween(inner_vertex2, inner_vertex3);

            auto outer_vertex01 = GeneratePointCloudBetween(outer_vertex0, outer_vertex1);
            auto outer_vertex02 = GeneratePointCloudBetween(outer_vertex0, outer_vertex2);
            auto outer_vertex13 = GeneratePointCloudBetween(outer_vertex1, outer_vertex3);
            auto outer_vertex23 = GeneratePointCloudBetween(outer_vertex2, outer_vertex3);

            auto inner_vertex0_outer_vertex0 = GeneratePointCloudBetween(inner_vertex0, outer_vertex0);
            auto inner_vertex1_outer_vertex1 = GeneratePointCloudBetween(inner_vertex1, outer_vertex1);
            auto inner_vertex2_outer_vertex2 = GeneratePointCloudBetween(inner_vertex2, outer_vertex2);
            auto inner_vertex3_outer_vertex3 = GeneratePointCloudBetween(inner_vertex3, outer_vertex3);

            pcd_msg.insert(pcd_msg.end(), inner_vertex01.begin(), inner_vertex01.end());
            pcd_msg.insert(pcd_msg.end(), inner_vertex02.begin(), inner_vertex02.end());
            pcd_msg.insert(pcd_msg.end(), inner_vertex13.begin(), inner_vertex13.end());
            pcd_msg.insert(pcd_msg.end(), inner_vertex23.begin(), inner_vertex23.end());

            pcd_msg.insert(pcd_msg.end(), outer_vertex01.begin(), outer_vertex01.end());
            pcd_msg.insert(pcd_msg.end(), outer_vertex02.begin(), outer_vertex02.end());
            pcd_msg.insert(pcd_msg.end(), outer_vertex13.begin(), outer_vertex13.end());
            pcd_msg.insert(pcd_msg.end(), outer_vertex23.begin(), outer_vertex23.end());

            pcd_msg.insert(pcd_msg.end(), inner_vertex0_outer_vertex0.begin(), inner_vertex0_outer_vertex0.end());
            pcd_msg.insert(pcd_msg.end(), inner_vertex1_outer_vertex1.begin(), inner_vertex1_outer_vertex1.end());
            pcd_msg.insert(pcd_msg.end(), inner_vertex2_outer_vertex2.begin(), inner_vertex2_outer_vertex2.end());
            pcd_msg.insert(pcd_msg.end(), inner_vertex3_outer_vertex3.begin(), inner_vertex3_outer_vertex3.end());
        }
    }

    return pcd_msg;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PointCloudXYZIRRgbSt MapDatabaseManager::ConvertToPointCloud(const std::vector<ParkingSlotType>& slot_map,
                                                             uint64_t target_parking_slot_id) const
{
    PointCloudXYZIRRgbSt pcd_msg(slot_map.size() * 250 + 300);
    pcd_msg.SetTimestamp(holo::Timestamp());
    pcd_msg.SetCoordinate(holo::Coordinate());
    pcd_msg.SetPose(Pose3::Identity().Cast<holo::float32_t>());
    uint64_t i = 0;

    for (const auto& slot : slot_map)
    {
        for (size_t j = 0; j < 4; j++)
        {
            Point3f pt = slot.vertices[j].Cast<::holo::float32_t>();
            pcd_msg[i].SetX(pt.GetX());
            pcd_msg[i].SetY(pt.GetY());
            pcd_msg[i].SetZ(pt.GetZ());
            pcd_msg[i].SetIntensity(0.0);
            i++;
        }

        std::vector<Point3> pts;

        // draw edge 1-2, 2-3, 3-0
        GeneratePointOnLine(slot.vertices[1], slot.vertices[2], pts);
        GeneratePointOnLine(slot.vertices[2], slot.vertices[3], pts);
        GeneratePointOnLine(slot.vertices[3], slot.vertices[0], pts);

        if (slot.id == target_parking_slot_id)
        {
            GeneratePointOnLine(slot.vertices[0], slot.vertices[2], pts);
            GeneratePointOnLine(slot.vertices[1], slot.vertices[3], pts);
        }

        // draw entrance 0-1
        // GeneratePointOnLine(slot.vertices[0], slot.vertices[1], pts);

        for (const auto& edge : pts)
        {
            Point3f pt = edge.Cast<::holo::float32_t>();
            pcd_msg[i].SetX(pt.GetX());
            pcd_msg[i].SetY(pt.GetY());
            pcd_msg[i].SetZ(pt.GetZ());
            pcd_msg[i].SetIntensity(0);
            i++;
        }
    }

    return pcd_msg;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapDatabaseManager::GeneratePointOnLine(const Point3& start, const Point3& end, std::vector<Point3>& pts) const
{
    uint16_t pt_num = 50;

    float64_t start_x = start.GetX();
    float64_t start_y = start.GetY();
    float64_t start_z = start.GetZ();

    float64_t end_x = end.GetX();
    float64_t end_y = end.GetY();
    float64_t end_z = end.GetZ();

    float64_t inc_x = (end_x - start_x) / pt_num;
    float64_t inc_y = (end_y - start_y) / pt_num;
    float64_t inc_z = (end_z - start_z) / pt_num;

    for (float64_t i = 0; i < pt_num; i += 1)
    {
        float64_t x = start_x + i * inc_x;
        float64_t y = start_y + i * inc_y;
        float64_t z = start_z + i * inc_z;
        pts.emplace_back(Point3(x, y, z));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PointCloudXYZIRRgbSt MapDatabaseManager::GeneratePointCloudBetween(const Point3& start, const Point3& end,
                                                                   const uint16_t points_num) const
{
    // get x y z respectively of start point and end point
    const auto start_x = start.GetX();
    const auto start_y = start.GetY();
    const auto start_z = start.GetZ();
    const auto end_x   = end.GetX();
    const auto end_y   = end.GetY();
    const auto end_z   = end.GetZ();

    // get the constant increment
    const auto inc_x = (end_x - start_x) / points_num;
    const auto inc_y = (end_y - start_y) / points_num;
    const auto inc_z = (end_z - start_z) / points_num;

    // construct pointcloud
    PointCloudXYZIRRgbSt pcd_msg(points_num);
    pcd_msg.SetTimestamp(holo::Timestamp());
    pcd_msg.SetCoordinate(holo::Coordinate());
    pcd_msg.SetPose(Pose3::Identity().Cast<::holo::float32_t>());

    // create points
    for (uint16_t i = 0; i < points_num; i += 1)
    {
        pcd_msg[i].SetX(static_cast<holo::float32_t>(start_x + i * inc_x));
        pcd_msg[i].SetY(static_cast<holo::float32_t>(start_y + i * inc_y));
        pcd_msg[i].SetZ(static_cast<holo::float32_t>(start_z + i * inc_z));
        pcd_msg[i].SetIntensity(0.0);
    }

    return pcd_msg;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MapPtr MapDatabaseManager::LoadMap(const std::string& file_name) const
{
    std::ifstream fin(file_name);

    if (!fin)
    {
        LOG(ERROR) << "LocalizationVSLAM --- LoadMap, could not open " << file_name;
        return nullptr;
    }

    // total landmarks number
    uint64_t landmark_num;
    fin.read((char*)&landmark_num, sizeof(uint64_t));

    // descriptor dimension
    uint16_t descriptor_dimension;
    fin.read((char*)&descriptor_dimension, sizeof(uint16_t));

    // read data one by one
    Map map;
    map.reserve(landmark_num);

    for (uint64_t i = 0; i < landmark_num; i++)
    {
        // load descriptor
        cv::Mat descriptor;
        descriptor.create(1, descriptor_dimension, CV_32FC1);

        for (uint16_t j = 0; j < descriptor_dimension; j++)
        {
            fin.read((char*)&descriptor.at<float32_t>(0, j), sizeof(float32_t));
        }

        // load position
        Scalar x, y, z;
        fin.read((char*)&x, sizeof(Scalar));
        fin.read((char*)&y, sizeof(Scalar));
        fin.read((char*)&z, sizeof(Scalar));
        Point3 position(x, y, z);

        // load direction
        Scalar direction_x, direction_y, direction_z;
        fin.read((char*)&direction_x, sizeof(Scalar));
        fin.read((char*)&direction_y, sizeof(Scalar));
        fin.read((char*)&direction_z, sizeof(Scalar));
        Vector3 direction(direction_x, direction_y, direction_z);

        // load reference camera pose
        Scalar t_x, t_y, t_z, q_w, q_x, q_y, q_z;
        fin.read((char*)&t_x, sizeof(Scalar));
        fin.read((char*)&t_y, sizeof(Scalar));
        fin.read((char*)&t_z, sizeof(Scalar));
        fin.read((char*)&q_w, sizeof(Scalar));
        fin.read((char*)&q_x, sizeof(Scalar));
        fin.read((char*)&q_y, sizeof(Scalar));
        fin.read((char*)&q_z, sizeof(Scalar));
        Pose3 pose(Rot3(Quaternion(q_w, q_x, q_y, q_z).ToRotationMatrix()), Point3(t_x, t_y, t_z));

        // load reference frame id
        uint64_t reference_frame_id;
        fin.read((char*)&reference_frame_id, sizeof(uint64_t));

        // load score
        Scalar score;
        fin.read((char*)&score, sizeof(Scalar));

        // load covariance
        Matrix3 covariance;
        fin.read((char*)&(covariance(0, 0)), sizeof(Scalar));
        fin.read((char*)&(covariance(0, 1)), sizeof(Scalar));
        fin.read((char*)&(covariance(0, 2)), sizeof(Scalar));

        fin.read((char*)&(covariance(1, 0)), sizeof(Scalar));
        fin.read((char*)&(covariance(1, 1)), sizeof(Scalar));
        fin.read((char*)&(covariance(1, 2)), sizeof(Scalar));

        fin.read((char*)&(covariance(2, 0)), sizeof(Scalar));
        fin.read((char*)&(covariance(2, 1)), sizeof(Scalar));
        fin.read((char*)&(covariance(2, 2)), sizeof(Scalar));

        // load semantic label
        SemanticLabel semantic_label;
        fin.read((char*)&semantic_label, sizeof(SemanticLabel));

        // load life long states
        uint64_t states_num;
        fin.read((char*)&states_num, sizeof(uint64_t));
        std::vector<MapPointState> states;
        states.reserve(states_num);

        for (uint64_t i = 0; i < states_num; i++)
        {
            MapPointState state;
            fin.read((char*)&state, sizeof(MapPointState));
            states.push_back(state);
        }
        states.push_back(MapPointState::CANDIDATE);

        // load remember rate
        Scalar remember_rate;
        fin.read((char*)&remember_rate, sizeof(Scalar));

        // create new map point
        MapPoint mp;
        mp.descriptor         = descriptor;
        mp.position           = position;
        mp.direction          = direction;
        mp.covariance         = covariance;
        mp.reference_pose     = pose;
        mp.reference_frame_id = reference_frame_id;
        mp.score              = score;
        mp.life_long_states   = states;
        mp.remember_rate      = remember_rate;
        mp.semantic_label     = semantic_label;

        map.emplace_back(std::make_shared<MapPoint>(mp));
    }
    fin.close();

    LOG(INFO) << " LoadMap --- successfully load prebuilt map, total landmarks num: " << map.size() << "\n";

    return std::make_shared<Map>(map);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SlotMapPtr MapDatabaseManager::LoadParkingSlotMap(const std::string& file_name)
{
    std::cout << "start Load parking slot map " << std::endl;
    SlotMapPtr    result = std::make_shared<SlotMap>();
    std::ifstream fin(file_name);

    if (!fin)
    {
        LOG(ERROR) << "MapDatabaseManager --- LoadParkingSlotDatabase, could not open " << file_name;
        return {};
    }

    // total parking slot number
    uint64_t slot_num;
    fin.read((char*)&slot_num, sizeof(uint64_t));

    for (uint64_t i = 0; i < slot_num; ++i)
    {
        // holo::common::ParkingSlot         parking_slot;
        std::shared_ptr<ParkingSlotType> parking_slot = std::make_shared<ParkingSlotType>();

        uint64_t slot_id;
        fin.read((char*)&slot_id, sizeof(uint64_t));
        parking_slot->id = slot_id;

        bool_t is_valid;
        fin.read((char*)&is_valid, sizeof(bool_t));
        parking_slot->is_valid = is_valid;

        Scalar vertex0_x, vertex0_y, vertex0_z;
        fin.read((char*)&vertex0_x, sizeof(Scalar));
        fin.read((char*)&vertex0_y, sizeof(Scalar));
        fin.read((char*)&vertex0_z, sizeof(Scalar));
        parking_slot->vertices[0] = Point3(vertex0_x, vertex0_y, vertex0_z);

        Scalar vertex1_x, vertex1_y, vertex1_z;
        fin.read((char*)&vertex1_x, sizeof(Scalar));
        fin.read((char*)&vertex1_y, sizeof(Scalar));
        fin.read((char*)&vertex1_z, sizeof(Scalar));
        parking_slot->vertices[1] = Point3(vertex1_x, vertex1_y, vertex1_z);

        bool_t is_rear_vertex_available;
        fin.read((char*)&is_rear_vertex_available, sizeof(bool_t));
        parking_slot->is_center_vertex_available = is_rear_vertex_available;
        if (is_rear_vertex_available)
        {
            Scalar vertex2_x, vertex2_y, vertex2_z;
            fin.read((char*)&vertex2_x, sizeof(Scalar));
            fin.read((char*)&vertex2_y, sizeof(Scalar));
            fin.read((char*)&vertex2_z, sizeof(Scalar));
            parking_slot->vertices[2] = Point3(vertex2_x, vertex2_y, vertex2_z);

            Scalar vertex3_x, vertex3_y, vertex3_z;
            fin.read((char*)&vertex3_x, sizeof(Scalar));
            fin.read((char*)&vertex3_y, sizeof(Scalar));
            fin.read((char*)&vertex3_z, sizeof(Scalar));
            parking_slot->vertices[3] = Point3(vertex3_x, vertex3_y, vertex3_z);
        }
        result->emplace_back(parking_slot);
    }

    fin.close();
    LOG(INFO) << " LoadParkingSlotMap --- successfully load parking slot map, total parking slots num: " << slot_num
              << "\n";
    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MapDatabaseManager::LoadParkingSlotDatabase(const std::string& parking_slot_file_name,
                                                 ParkingSlotData&   parking_slot_data)
{
    std::vector<holo::common::ParkingSlot> parking_slot_database;
    std::ifstream                          fin(parking_slot_file_name);

    if (!fin)
    {
        LOG(ERROR) << "MapDatabaseManager --- LoadParkingSlotDatabase, could not open " << parking_slot_file_name;
        return false;
    }

    // total parking slot number
    uint64_t slot_num;
    fin.read((char*)&slot_num, sizeof(uint64_t));

    for (uint64_t i = 0; i < slot_num; ++i)
    {
        holo::common::ParkingSlot parking_slot;

        uint64_t slot_id;
        fin.read((char*)&slot_id, sizeof(uint64_t));
        parking_slot.id = slot_id;

        bool_t is_valid;
        fin.read((char*)&is_valid, sizeof(bool_t));
        parking_slot.is_valid = is_valid;

        Scalar vertex0_x, vertex0_y, vertex0_z;
        fin.read((char*)&vertex0_x, sizeof(Scalar));
        fin.read((char*)&vertex0_y, sizeof(Scalar));
        fin.read((char*)&vertex0_z, sizeof(Scalar));
        parking_slot.vertices[0] = Point3(vertex0_x, vertex0_y, vertex0_z);

        Scalar vertex1_x, vertex1_y, vertex1_z;
        fin.read((char*)&vertex1_x, sizeof(Scalar));
        fin.read((char*)&vertex1_y, sizeof(Scalar));
        fin.read((char*)&vertex1_z, sizeof(Scalar));
        parking_slot.vertices[1] = Point3(vertex1_x, vertex1_y, vertex1_z);

        bool_t is_rear_vertex_available;
        fin.read((char*)&is_rear_vertex_available, sizeof(bool_t));
        parking_slot.is_center_vertex_available = is_rear_vertex_available;
        if (is_rear_vertex_available)
        {
            Scalar vertex2_x, vertex2_y, vertex2_z;
            fin.read((char*)&vertex2_x, sizeof(Scalar));
            fin.read((char*)&vertex2_y, sizeof(Scalar));
            fin.read((char*)&vertex2_z, sizeof(Scalar));
            parking_slot.vertices[2] = Point3(vertex2_x, vertex2_y, vertex2_z);

            Scalar vertex3_x, vertex3_y, vertex3_z;
            fin.read((char*)&vertex3_x, sizeof(Scalar));
            fin.read((char*)&vertex3_y, sizeof(Scalar));
            fin.read((char*)&vertex3_z, sizeof(Scalar));
            parking_slot.vertices[3] = Point3(vertex3_x, vertex3_y, vertex3_z);
        }

        parking_slot_database.push_back(parking_slot);
    }
    parking_slot_data.parking_slot_database = parking_slot_database;

    bool_t is_geted_target_parking_slot;
    fin.read((char*)&is_geted_target_parking_slot, sizeof(bool_t));

    if (is_geted_target_parking_slot)
    {
        uint64_t target_parking_slot_id;
        fin.read((char*)&target_parking_slot_id, sizeof(uint64_t));
        parking_slot_data.target_parking_slot_id = target_parking_slot_id;
    }
    else
    {
        fin.close();
        LOG(ERROR) << "MapDatabaseManager --- LoadParkingSlotDatabase,  can't get target parking slot id";
        return false;
    }

    fin.close();
    LOG(INFO) << " LoadParkingSlotMap --- successfully load parking slot map, total parking slots num: " << slot_num
              << "\n";
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
KeyFramesDatabase MapDatabaseManager::LoadKeyFramesDatabase(const std::string& file_name) const
{
    LOG(INFO) << "MapDatabaseManager --- trying to load frames from: " << file_name << "\n";
    std::ifstream fin(file_name);

    if (!fin)
    {
        LOG(ERROR) << "MapDatabaseManager --- LoadKeyFramesDatabase: could not open " << file_name;
        return {};
    }

    KeyFramesDatabase database;

    uint16_t frame_num;
    fin.read((char*)&frame_num, sizeof(uint16_t));

    uint16_t descriptor_dimension;
    fin.read((char*)&descriptor_dimension, sizeof(uint16_t));

    for (uint16_t i = 0; i < frame_num; i++)
    {
        uint64_t frame_id;
        fin.read((char*)&frame_id, sizeof(uint64_t));

        uint16_t camera_number;
        fin.read((char*)&camera_number, sizeof(uint16_t));

        // read pose
        Pose3 vehicle_pose;
        {
            float64_t x, y, z, q_w, q_x, q_y, q_z;
            fin.read((char*)&x, sizeof(Scalar));
            fin.read((char*)&y, sizeof(Scalar));
            fin.read((char*)&z, sizeof(Scalar));
            fin.read((char*)&q_w, sizeof(Scalar));
            fin.read((char*)&q_x, sizeof(Scalar));
            fin.read((char*)&q_y, sizeof(Scalar));
            fin.read((char*)&q_z, sizeof(Scalar));
            Vector3    translation(x, y, z);
            Quaternion rotation(q_w, q_x, q_y, q_z);
            vehicle_pose = Pose3(Rot3(rotation.ToRotationMatrix()), Point3(translation));
        }
        KeyFrame keyframe(frame_id, vehicle_pose, camera_number);

        for (uint16_t camera_index = 0; camera_index < camera_number; camera_index++)
        {
            uint16_t camera_id;
            fin.read((char*)&camera_id, sizeof(uint16_t));

            float64_t x, y, z, q_w, q_x, q_y, q_z;
            fin.read((char*)&x, sizeof(Scalar));
            fin.read((char*)&y, sizeof(Scalar));
            fin.read((char*)&z, sizeof(Scalar));
            fin.read((char*)&q_w, sizeof(Scalar));
            fin.read((char*)&q_x, sizeof(Scalar));
            fin.read((char*)&q_y, sizeof(Scalar));
            fin.read((char*)&q_z, sizeof(Scalar));
            Vector3    translation(x, y, z);
            Quaternion rotation(q_w, q_x, q_y, q_z);
            Pose3      pose(Rot3(rotation.ToRotationMatrix()), Point3(translation));

            uint16_t feature_num;
            fin.read((char*)&feature_num, sizeof(uint16_t));

            Features             features;
            std::vector<int64_t> associated_landmarks;
            std::vector<Point3>  mappoints;
            features.reserve(feature_num);
            associated_landmarks.reserve(feature_num);
            mappoints.reserve(feature_num);

            for (uint16_t j = 0; j < feature_num; j++)
            {
                Scalar pt_x, pt_y;
                fin.read((char*)&pt_x, sizeof(Scalar));
                fin.read((char*)&pt_y, sizeof(Scalar));

                Scalar ptn_x, ptn_y, ptn_z;
                fin.read((char*)&ptn_x, sizeof(Scalar));
                fin.read((char*)&ptn_y, sizeof(Scalar));
                fin.read((char*)&ptn_z, sizeof(Scalar));

                // read semantic label
                SemanticLabel semantic_label;
                fin.read((char*)&semantic_label, sizeof(SemanticLabel));

                cv::Mat descriptors;
                descriptors.create(1, descriptor_dimension, CV_32FC1);

                for (uint16_t k = 0; k < descriptor_dimension; k++)
                {
                    fin.read((char*)&descriptors.at<float32_t>(0, k), sizeof(float32_t));
                }

                Scalar score;
                fin.read((char*)&score, sizeof(Scalar));

                int64_t lm_id;
                fin.read((char*)&lm_id, sizeof(int64_t));

                features.emplace_back(cv::Point2f(pt_x, pt_y), descriptors, Point3(ptn_x, ptn_y, ptn_z), camera_id,
                                      score, semantic_label);
                associated_landmarks.emplace_back(lm_id);

                Scalar ptw_x, ptw_y, ptw_z;
                fin.read((char*)&ptw_x, sizeof(Scalar));
                fin.read((char*)&ptw_y, sizeof(Scalar));
                fin.read((char*)&ptw_z, sizeof(Scalar));
                mappoints.emplace_back(ptw_x, ptw_y, ptw_z);
            }

            keyframe.multi_camera_data[camera_id].pose                 = pose;
            keyframe.multi_camera_data[camera_id].features             = features;
            keyframe.multi_camera_data[camera_id].associated_landmarks = associated_landmarks;
            keyframe.multi_camera_data[camera_id].mappoints            = mappoints;
        }

        database.emplace(keyframe.frame_id, keyframe);
    }

    LOG(INFO) << "MapDatabaseManager --- LoadKeyFramesDatabase: load key frame done. total frames: " << database.size();
    return database;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FrameIndexedBows MapDatabaseManager::LoadKeyFramesBowVector(std::string const& file_name) const
{
    /// Step-0: source data checker
    LOG(INFO) << "MapDatabaseManager --- trying to load keyframe's bow vectors from: " << file_name << "\n";
    std::ifstream fin(file_name);

    if (!fin)
    {
        LOG(ERROR) << "MapDatabaseManager --- LoadKeyFramesBowVector: could not open " << file_name;
        return {};
    }

    FrameIndexedBows keyframe_index_bow;

    // load keyframe numbers
    uint16_t keyframe_num;
    fin.read((char*)&keyframe_num, sizeof(uint16_t));

    for (uint16_t index = 0u; index < keyframe_num; index++)
    {
        // load keyframe's id
        uint64_t keyframe_id;
        fin.read((char*)&keyframe_id, sizeof(uint64_t));

        // load keyframe's camera number
        uint16_t camera_number;
        fin.read((char*)&camera_number, sizeof(uint16_t));

        // load each camera image's bow vector
        CameraIndexedBow camera_index_bow;

        for (uint16_t camera_index = 0u; camera_index < camera_number; camera_index++)
        {
            // load camera ID
            uint16_t camera_id;
            fin.read((char*)&camera_id, sizeof(uint16_t));

            // load bag of words
            DBoW3::BowVector camera_keyframe_bow;
            camera_keyframe_bow.fromStream(fin);
            camera_index_bow.emplace(camera_id, camera_keyframe_bow);
        }

        keyframe_index_bow.emplace(keyframe_id, camera_index_bow);
    }

    LOG(INFO) << "MapDatabaseManager --- LoadKeyFramesBowVector: load keyframe's bow vector done. "
              << "Total keyframe's size: " << keyframe_index_bow.size();
    return keyframe_index_bow;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapDatabaseManager::UpdatePrebiltMapAndKeyFramesDatabase(const SubMappingResults& sub_maps_keyframes_databases)
{
    uint64_t new_mappoints_num = 0, new_key_frames_num = 0;
    for (const auto& map_keyframes_database : sub_maps_keyframes_databases)
    {
        new_mappoints_num += map_keyframes_database.first.size();
        new_key_frames_num += map_keyframes_database.second.size();

        // update map
        prebuilt_map_->insert(prebuilt_map_->end(), map_keyframes_database.first.begin(),
                              map_keyframes_database.first.end());

        // update key frames
        for (const auto& key_frame : map_keyframes_database.second)
        {
            uint64_t new_key_frame_id = key_frames_database_.rbegin()->first + 1;
            key_frames_database_.emplace(new_key_frame_id, key_frame.second);
        }
    }
    LOG(INFO) << "MapDatabaseManager --- Update Prebilt Map And Key Frames Database done.\n Add new mappoints: "
              << new_mappoints_num << ", add new key frames: " << new_key_frames_num;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapDatabaseManager::SaveMapAndKeyFrames() const
{
    if (parameters_.mode == "localization")
    {
        /// create updated map and key frames directory
        const auto directory = parameters_.map_data_dir + "/" + parameters_.map_names.front() + "/updated/";

        // remove all old file if exist
        if (boost::filesystem::is_directory(directory))
        {
            boost::filesystem::remove_all(directory);
        }

        if (!boost::filesystem::create_directories(directory))
        {
            std::stringstream ss;
            ss << "MapDatabaseManager --- Failed to create dir: " << directory << "\n";
            throw std::runtime_error(ss.str());
        }
    }

    SaveMap(*prebuilt_map_, parameters_.map_names.front());
    SaveUpdatedMapStates(*prebuilt_map_, parameters_.map_names.front());
    SaveKeyFrames(key_frames_database_, parameters_.map_names.front());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapDatabaseManager::SaveMap(const Map& map, const std::string& map_name) const
{
    std::string mappoints_file;
    mappoints_file = parameters_.map_data_dir + map_name + "/mappoints.bin";
    LOG(INFO) << "MapDatabaseManager --- trying to save map to " << mappoints_file << " ...\n";

    // remove old map and trjectory file
    if (boost::filesystem::exists(mappoints_file))
    {
        boost::filesystem::remove(mappoints_file);
    }

    // save map
    if (map.empty())
    {
        LOG(ERROR) << "MapDatabaseManager --- SaveMap. empty map data.\n";
        return;
    }

    std::ofstream file_map(mappoints_file);

    if (!file_map)
    {
        LOG(ERROR) << "MapDatabaseManager --- SaveMapAndTrajectory, could not open " << mappoints_file;
        return;
    }

    // map file format: bin
    // {
    //   mappoints_num:
    //   descriptor_dimension:
    //   mappoints:
    //   [
    //     {
    //          descriptor:
    //          position_x:
    //          position_y:
    //          position_z:
    //          direction_x:
    //          direction_y:
    //          direction_z:
    //          translation_x:
    //          translation_y:
    //          translation_z:
    //          quaternion_w:
    //          quaternion_x:
    //          quaternion_y:
    //          quaternion_z:
    //          reference_frame_id:
    //          covariance_matrix[00]:
    //          covariance_matrix[01]:
    //          covariance_matrix[02]:
    //          covariance_matrix[10]:
    //          covariance_matrix[11]:
    //          covariance_matrix[12]:
    //          covariance_matrix[20]:
    //          covariance_matrix[21]:
    //          covariance_matrix[22]:
    //          matching_results:
    //          remember_rate:
    //     }
    //   ]
    // }

    LOG(INFO) << "MapDatabaseManager --- begin to save map to " << mappoints_file << " ...\n";
    // save total mappoints number
    uint64_t mappoints_num = 0;
    for (const auto& mp : map)
    {
        if (mp)
        {
            mappoints_num++;
        }
    }
    file_map.write((const char*)&(mappoints_num), sizeof(uint64_t));

    // save descriptor col number
    uint16_t descriptor_dimension = (uint16_t)map[0]->descriptor.cols;
    file_map.write((const char*)&(descriptor_dimension), sizeof(uint16_t));

    // save mappoints' information
    for (uint64_t i = 0; i < map.size(); i++)
    {
        if (!map.at(i))
        {
            continue;
        }

        const auto mappoint = map.at(i);

        for (uint16_t j = 0; j < descriptor_dimension; j++)
        {
            file_map.write((const char*)&mappoint->descriptor.at<float32_t>(0, j), sizeof(float32_t));
        }

        const Point3 position   = mappoint->position;
        Scalar       position_x = position.GetX();
        Scalar       position_y = position.GetY();
        Scalar       position_z = position.GetZ();
        file_map.write((const char*)&position_x, sizeof(Scalar));
        file_map.write((const char*)&position_y, sizeof(Scalar));
        file_map.write((const char*)&position_z, sizeof(Scalar));

        const Vector3 direction = mappoint->direction;
        Scalar        dir_x     = direction[0];
        Scalar        dir_y     = direction[1];
        Scalar        dir_z     = direction[2];
        file_map.write((const char*)&dir_x, sizeof(Scalar));
        file_map.write((const char*)&dir_y, sizeof(Scalar));
        file_map.write((const char*)&dir_z, sizeof(Scalar));

        Vector3    translation = mappoint->reference_pose.GetTranslation().ToVector();
        Quaternion quaternion  = mappoint->reference_pose.GetRotation().ToQuaternion();
        Scalar     x           = translation[0];
        Scalar     y           = translation[1];
        Scalar     z           = translation[2];
        Scalar     q_w         = quaternion.GetW();
        Scalar     q_x         = quaternion.GetX();
        Scalar     q_y         = quaternion.GetY();
        Scalar     q_z         = quaternion.GetZ();
        file_map.write((const char*)&(x), sizeof(Scalar));
        file_map.write((const char*)&(y), sizeof(Scalar));
        file_map.write((const char*)&(z), sizeof(Scalar));
        file_map.write((const char*)&(q_w), sizeof(Scalar));
        file_map.write((const char*)&(q_x), sizeof(Scalar));
        file_map.write((const char*)&(q_y), sizeof(Scalar));
        file_map.write((const char*)&(q_z), sizeof(Scalar));

        const uint64_t reference_frame_id = mappoint->reference_frame_id;
        file_map.write((const char*)&(reference_frame_id), sizeof(uint64_t));

        const Scalar score = mappoint->score;
        file_map.write((const char*)&(score), sizeof(Scalar));

        const auto covariance = mappoint->covariance;

        Scalar c00 = covariance(0, 0);
        Scalar c01 = covariance(0, 1);
        Scalar c02 = covariance(0, 2);

        Scalar c10 = covariance(1, 0);
        Scalar c11 = covariance(1, 1);
        Scalar c12 = covariance(1, 2);

        Scalar c20 = covariance(2, 0);
        Scalar c21 = covariance(2, 1);
        Scalar c22 = covariance(2, 2);

        file_map.write((const char*)&(c00), sizeof(Scalar));
        file_map.write((const char*)&(c01), sizeof(Scalar));
        file_map.write((const char*)&(c02), sizeof(Scalar));

        file_map.write((const char*)&(c10), sizeof(Scalar));
        file_map.write((const char*)&(c11), sizeof(Scalar));
        file_map.write((const char*)&(c12), sizeof(Scalar));

        file_map.write((const char*)&(c20), sizeof(Scalar));
        file_map.write((const char*)&(c21), sizeof(Scalar));
        file_map.write((const char*)&(c22), sizeof(Scalar));

        // save semantic label
        file_map.write((const char*)&(mappoint->semantic_label), sizeof(SemanticLabel));

        // save matching results
        const uint64_t matching_results_size = mappoint->life_long_states.size();
        file_map.write((const char*)&(matching_results_size), sizeof(uint64_t));
        for (uint64_t i = 0; i < matching_results_size; i++)
        {
            MapPointState result = mappoint->life_long_states[i];
            file_map.write((const char*)&(result), sizeof(MapPointState));
        }

        Scalar remember_rate = mappoint->remember_rate;
        file_map.write((const char*)&(remember_rate), sizeof(Scalar));
    }

    file_map.close();
    LOG(INFO) << "MapDatabaseManager --- save map to file done. total map points num: " << map.size() << "\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int64_t MapDatabaseManager::SaveParkingSlotMapAndTargetID(const std::vector<ParkingSlotType>& parking_slot_map,
                                                          const Point3& end_point, const std::string& map_name) const
{
    const std::string slot_map_file = parameters_.map_data_dir + map_name + "/slot_map.bin";

    LOG(INFO) << "MapDatabaseManager --- trying to save parking slot map to " << slot_map_file << " ...\n";
    // remove old map and trjectory file
    if (boost::filesystem::exists(slot_map_file))
    {
        boost::filesystem::remove(slot_map_file);
    }

    // save map
    if (parking_slot_map.empty())
    {
        LOG(ERROR) << "MapDatabaseManager --- SaveSlotMap. empty map data.\n";
        return -1;
    }

    std::ofstream file_slot_map(slot_map_file);

    // the following variable used to determine target parking slot id
    uint64_t  target_parking_slot_id = 0;
    Point3    parking_slot_center_point;
    float64_t minimum_distance_to_end_point = 10.0;

    if (!file_slot_map)
    {
        LOG(ERROR) << "MapDatabaseManager --- SaveParkingSlotMap, could not open " << slot_map_file;
        return -1;
    }
    LOG(INFO) << "MapDatabaseManager --- SaveParkingSlotMap, begin to save map to " << slot_map_file << " ...\n";

    // save total mappoints number
    uint64_t slot_num = parking_slot_map.size();
    file_slot_map.write((const char*)&(slot_num), sizeof(uint64_t));

    // save slot map information
    for (const auto& parking_slot : parking_slot_map)
    {
        uint64_t id = parking_slot.id;
        file_slot_map.write((const char*)&(id), sizeof(uint64_t));

        bool_t is_valid = parking_slot.is_valid;
        file_slot_map.write((const char*)&(is_valid), sizeof(bool_t));

        const Point3 vertex0   = parking_slot.vertices[0];
        Scalar       vertex0_x = vertex0.GetX();
        Scalar       vertex0_y = vertex0.GetY();
        Scalar       vertex0_z = vertex0.GetZ();
        file_slot_map.write((const char*)&(vertex0_x), sizeof(Scalar));
        file_slot_map.write((const char*)&(vertex0_y), sizeof(Scalar));
        file_slot_map.write((const char*)&(vertex0_z), sizeof(Scalar));

        const Point3 vertex1   = parking_slot.vertices[1];
        Scalar       vertex1_x = vertex1.GetX();
        Scalar       vertex1_y = vertex1.GetY();
        Scalar       vertex1_z = vertex1.GetZ();
        file_slot_map.write((const char*)&(vertex1_x), sizeof(Scalar));
        file_slot_map.write((const char*)&(vertex1_y), sizeof(Scalar));
        file_slot_map.write((const char*)&(vertex1_z), sizeof(Scalar));

        bool_t is_rear_vertex_available = parking_slot.is_rear_vertex_available;
        file_slot_map.write((const char*)&(is_rear_vertex_available), sizeof(bool_t));

        if (is_rear_vertex_available)
        {
            const Point3 vertex2   = parking_slot.vertices[2];
            Scalar       vertex2_x = vertex2.GetX();
            Scalar       vertex2_y = vertex2.GetY();
            Scalar       vertex2_z = vertex2.GetZ();
            file_slot_map.write((const char*)&(vertex2_x), sizeof(Scalar));
            file_slot_map.write((const char*)&(vertex2_y), sizeof(Scalar));
            file_slot_map.write((const char*)&(vertex2_z), sizeof(Scalar));

            const Point3 vertex3   = parking_slot.vertices[3];
            Scalar       vertex3_x = vertex3.GetX();
            Scalar       vertex3_y = vertex3.GetY();
            Scalar       vertex3_z = vertex3.GetZ();
            file_slot_map.write((const char*)&(vertex3_x), sizeof(Scalar));
            file_slot_map.write((const char*)&(vertex3_y), sizeof(Scalar));
            file_slot_map.write((const char*)&(vertex3_z), sizeof(Scalar));

            parking_slot_center_point = (vertex0 + vertex1 + vertex2 + vertex3) / 4;
        }

        const auto distance_to_end_point = parking_slot_center_point.Dist(end_point);

        if (distance_to_end_point < minimum_distance_to_end_point)
        {
            minimum_distance_to_end_point = distance_to_end_point;
            target_parking_slot_id        = parking_slot.id;
        }
    }

    if (minimum_distance_to_end_point > 10.0)
    {
        bool_t is_geted_target_parking_slot = false;
        file_slot_map.write((const char*)&(is_geted_target_parking_slot), sizeof(bool_t));
        LOG(ERROR) << "MapDatabaseManager --- SaveParkingSlotMap no target parking slot";
    }
    else
    {
        bool_t is_geted_target_parking_slot = true;
        file_slot_map.write((const char*)&(is_geted_target_parking_slot), sizeof(bool_t));
        file_slot_map.write((const char*)&(target_parking_slot_id), sizeof(uint64_t));
    }

    file_slot_map.close();
    LOG(INFO) << "MapPing --- save slot map to file done. total slot map num: " << parking_slot_map.size() << "\n";
    return target_parking_slot_id;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapDatabaseManager::SaveUpdatedMapStates(const Map& map, const std::string& map_name) const
{
    // remove old mappoint states file
    std::string mappoints_states_file = parameters_.map_data_dir + map_name + "/new_mappoints.txt";

    if (boost::filesystem::exists(mappoints_states_file))
    {
        boost::filesystem::remove(mappoints_states_file);
    }
    std::fstream file_mappoints_state(mappoints_states_file, std::ios::out);
    for (uint64_t i = 0; i < map.size(); i++)
    {
        if (!map.at(i))
        {
            continue;
        }
        const auto mappoint = map.at(i);

        switch (mappoint->semantic_label)
        {
            case SemanticLabel::STATIC:
                file_mappoints_state << "semantic label: STATIC\n";
                break;
            case SemanticLabel::VEHICLE:
                file_mappoints_state << "semantic label: VEHICLE\n";
                break;

            default:
                file_mappoints_state << "semantic label: UNKNOWN\n";
                break;
        }

        file_mappoints_state << "position: " << mappoint->position.GetX() << " " << mappoint->position.GetY() << " "
                             << mappoint->position.GetZ() << "\nremember rate: " << mappoint->remember_rate
                             << "\nlife long states: ";
        for (size_t i = 0; i < mappoint->life_long_states.size(); i++)
        {
            if (mappoint->life_long_states.at(i) == MapPointState::CANDIDATE)
            {
                file_mappoints_state << "CANDIDATE ";
            }
            else if (mappoint->life_long_states.at(i) == MapPointState::VISIBLE)
            {
                file_mappoints_state << "VISIBLE ";
            }
            else
            {
                file_mappoints_state << "MATCHED ";
            }
        }
        file_mappoints_state << "\n";
        file_mappoints_state << "=============================================================\n";
    }
    file_mappoints_state.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapDatabaseManager::SaveKeyFrames(const KeyFramesDatabase& keyframes_database, const std::string& map_name) const
{
    std::string frame_file;
    frame_file = parameters_.map_data_dir + map_name + "/frames.bin";
    LOG(INFO) << "MapDatabaseManager --- trying to save keyframes to " << frame_file;

    // remove old frames file
    if (boost::filesystem::exists(frame_file))
    {
        boost::filesystem::remove(frame_file);
    }

    std::ofstream fout(frame_file);
    if (!fout)
    {
        LOG(ERROR) << "MapDatabaseManager --- SaveKeyFrames, could not open " << frame_file;
        return;
    }

    // get descriptor col number
    const auto& desc = keyframes_database.begin()->second.multi_camera_data.at(0).features.at(0).optional_descriptor;
    if (!desc)
    {
        LOG(ERROR) << "MapDatabaseManager --- SaveKeyFrames, features of this frame database without decriptor.";
        return;
    }

    auto descriptor_dimension = desc->cols;
    if (descriptor_dimension < 0)
    {
        LOG(ERROR) << "MapDatabaseManager --- SaveKeyFrames, features of this frame database without decriptor.";
        return;
    }

    // save frames number
    uint16_t saved_frame_num = keyframes_database.size();
    fout.write((const char*)&(saved_frame_num), sizeof(uint16_t));

    // save descriptor col number
    uint16_t dim = (uint16_t)descriptor_dimension;
    fout.write((const char*)&(dim), sizeof(uint16_t));

    for (const auto& id_to_frame : keyframes_database)
    {
        uint64_t frame_id = id_to_frame.first;
        fout.write((const char*)&(frame_id), sizeof(uint64_t));

        auto& frame             = id_to_frame.second;
        auto& multi_camera_data = frame.multi_camera_data;

        uint16_t camera_number = multi_camera_data.size();
        fout.write((const char*)&(camera_number), sizeof(uint16_t));

        // save pose
        const auto current_pose = frame.pose;
        {
            Vector3    translation = current_pose.GetTranslation().ToVector();
            Quaternion quaternion  = current_pose.GetRotation().ToQuaternion();
            Scalar     x           = translation[0];
            Scalar     y           = translation[1];
            Scalar     z           = translation[2];
            Scalar     q_w         = quaternion.GetW();
            Scalar     q_x         = quaternion.GetX();
            Scalar     q_y         = quaternion.GetY();
            Scalar     q_z         = quaternion.GetZ();
            fout.write((const char*)&(x), sizeof(Scalar));
            fout.write((const char*)&(y), sizeof(Scalar));
            fout.write((const char*)&(z), sizeof(Scalar));
            fout.write((const char*)&(q_w), sizeof(Scalar));
            fout.write((const char*)&(q_x), sizeof(Scalar));
            fout.write((const char*)&(q_y), sizeof(Scalar));
            fout.write((const char*)&(q_z), sizeof(Scalar));
        }

        // process all camera data
        for (uint16_t camera_index = 0; camera_index < multi_camera_data.size(); camera_index++)
        {
            fout.write((const char*)&(camera_index), sizeof(uint16_t));

            // save camera pose
            const auto T_wc        = frame.multi_camera_data[camera_index].pose;
            Vector3    translation = T_wc.GetTranslation().ToVector();
            Quaternion quaternion  = T_wc.GetRotation().ToQuaternion();
            Scalar     x           = translation[0];
            Scalar     y           = translation[1];
            Scalar     z           = translation[2];
            Scalar     q_w         = quaternion.GetW();
            Scalar     q_x         = quaternion.GetX();
            Scalar     q_y         = quaternion.GetY();
            Scalar     q_z         = quaternion.GetZ();
            fout.write((const char*)&(x), sizeof(Scalar));
            fout.write((const char*)&(y), sizeof(Scalar));
            fout.write((const char*)&(z), sizeof(Scalar));
            fout.write((const char*)&(q_w), sizeof(Scalar));
            fout.write((const char*)&(q_x), sizeof(Scalar));
            fout.write((const char*)&(q_y), sizeof(Scalar));
            fout.write((const char*)&(q_z), sizeof(Scalar));

            // save features and associated landmark ids
            const auto& features             = multi_camera_data.at(camera_index).features;
            const auto& associated_landmarks = multi_camera_data.at(camera_index).associated_landmarks;
            const auto& mappoints            = multi_camera_data.at(camera_index).mappoints;

            uint16_t features_num = features.size();
            fout.write((const char*)&(features_num), sizeof(uint16_t));

            for (uint16_t i = 0; i < features_num; i++)
            {
                const cv::Point2f& pt       = features.at(i).image_point;
                const Scalar       img_pt_x = pt.x;
                const Scalar       img_pt_y = pt.y;
                fout.write((const char*)&(img_pt_x), sizeof(Scalar));
                fout.write((const char*)&(img_pt_y), sizeof(Scalar));

                const Point3 ptn   = features.at(i).normalized_point;
                Scalar       ptn_x = ptn.GetX();
                Scalar       ptn_y = ptn.GetY();
                Scalar       ptn_z = ptn.GetZ();
                fout.write((const char*)&(ptn_x), sizeof(Scalar));
                fout.write((const char*)&(ptn_y), sizeof(Scalar));
                fout.write((const char*)&(ptn_z), sizeof(Scalar));

                const auto semantic_label = features.at(i).semantic_label;
                fout.write((const char*)&semantic_label, sizeof(SemanticLabel));

                const cv::Mat desc = *(features.at(i).optional_descriptor);
                for (uint16_t j = 0; j < dim; j++)
                {
                    fout.write((const char*)&desc.at<float32_t>(0, j), sizeof(float32_t));
                }

                const Scalar score = features.at(i).score;
                fout.write((const char*)&(score), sizeof(Scalar));

                const int64_t lm_id = associated_landmarks.at(i);
                fout.write((const char*)&(lm_id), sizeof(int64_t));

                // save point
                const auto&  ptw   = mappoints.at(i);
                const Scalar ptw_x = ptw.GetX();
                const Scalar ptw_y = ptw.GetY();
                const Scalar ptw_z = ptw.GetZ();
                fout.write((const char*)&(ptw_x), sizeof(Scalar));
                fout.write((const char*)&(ptw_y), sizeof(Scalar));
                fout.write((const char*)&(ptw_z), sizeof(Scalar));
            }
        }
    }

    fout.close();
    LOG(INFO) << "MapDatabaseManager ---  save keyframes done. total keyframes num: " << keyframes_database.size()
              << "\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapDatabaseManager::SaveKeyFramesBowVector(FramesDatabase const&        frames_database,
                                                std::vector<uint64_t> const& keyframe_ids,
                                                std::string const&           map_name) const
{
    /// Step-0: Create filenames using input map name
    std::string frame_file;
    frame_file = parameters_.map_data_dir + map_name + "/keyframes_bow.bin";
    LOG(INFO) << "MapDatabaseManager --- trying to save keyframe's bow vector to " << frame_file;

    if (boost::filesystem::exists(frame_file))
    {
        boost::filesystem::remove(frame_file);
    }

    std::ofstream fout(frame_file);
    if (!fout)
    {
        LOG(ERROR) << "MapDatabaseManager --- SaveKeyFramesBowVector, could not open " << frame_file;
        return;
    }

    /// Step-1: Get all keyframe's feature
    // save key-frames number
    uint16_t saved_keyframe_num = keyframe_ids.size();
    fout.write((const char*)&(saved_keyframe_num), sizeof(uint16_t));

    for (uint64_t const& keyframe_id : keyframe_ids)
    {
        auto const     keyframe      = frames_database.GetFrame(keyframe_id);
        uint16_t const camera_number = keyframe.multi_camera_data.size();

        // save keyframe's id
        fout.write((const char*)&(keyframe_id), sizeof(uint64_t));
        // save keyframe's camera number
        fout.write((const char*)&(camera_number), sizeof(uint16_t));

        /// Step-2: compute the keyframe's bow-descriptors and save to disk
        for (uint16_t camera_index = 0u; camera_index < camera_number; camera_index++)
        {
            // save camera's ID
            fout.write((const char*)&(camera_index), sizeof(uint16_t));

            // Step-2.1: get all feature descriptors about current camera image
            std::vector<cv::Mat> keyframe_descriptors;
            keyframe_descriptors.reserve(keyframe.multi_camera_data.at(camera_index).features.size());

            for (auto const& feature : keyframe.multi_camera_data.at(camera_index).features)
            {
                if (feature.optional_descriptor == boost::none)
                {
                    LOG(WARNING) << "SaveKeyFramesBowVector --- want to save feature's descriptors,"
                                 << "but keyframe have keypoints which descriptors is none!";
                    continue;
                }

                keyframe_descriptors.push_back(*feature.optional_descriptor);
            }

            // Step-2.2: compute the bow vector about current camera image using all descriptors
            DBoW3::BowVector keyframe_bow;

            if (Relocalization::bow_vocabulary_)
            {
                Relocalization::bow_vocabulary_->transform(keyframe_descriptors, keyframe_bow);
            }
            else
            {
                LOG(ERROR) << "MapDatabaseManager --- Save keyframes bow vector failed, "
                           << "there don't have bow vocabulary in class Relocalization!";
                return;
            }

            // Step-2.3: save keyframe's bow vector
            keyframe_bow.toStream(fout);
        }
    }

    fout.close();
    LOG(INFO) << "MapDatabaseManager ---  save keyframes bow vector done. total keyframes num: " << keyframe_ids.size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
KeyFramesDatabase MapDatabaseManager::RetrieveKeyFramesDatabase(const Values&                values,
                                                                const FramesDatabase&        frames_database,
                                                                const std::vector<uint64_t>& keyframe_ids) const
{
    KeyFramesDatabase new_keyframes_database;

    for (auto& keyframe_id : keyframe_ids)
    {
        auto           frame             = frames_database.GetFrame(keyframe_id);
        const uint64_t camera_number     = frame.multi_camera_data.size();
        auto&          multi_camera_data = frame.multi_camera_data;
        KeyFrame       keyframe(frame.frame_id, HoloGtsam::Convert(values.at(X(keyframe_id)).cast<gtsam::Pose3>()),
                                camera_number);

        // process all camera data
        for (uint16_t camera_index = 0; camera_index < camera_number; camera_index++)
        {
            // save camera pose
            const auto T_wc = HoloGtsam::Convert(values.at(X(keyframe_id)).cast<gtsam::Pose3>()) *
                              frame.camera_parameters->extrinsics.at(camera_index);

            // save features and associated landmark ids
            const auto& features             = multi_camera_data.at(camera_index).features;
            const auto& associated_landmarks = multi_camera_data.at(camera_index).associated_landmarks;

            // select features observed landmark
            Features             selected_features;
            std::vector<Point3>  landmarks;
            std::vector<int64_t> ids;

            for (uint16_t i = 0; i < features.size(); i++)
            {
                const auto& lm_id = associated_landmarks.at(i);
                if (lm_id < 0 || !values.exists(L(lm_id)))
                {
                    continue;
                }

                selected_features.push_back(features.at(i));
                ids.push_back(lm_id);
                const auto point = HoloGtsam::Convert(values.at(L(lm_id)).cast<gtsam::Point3>());
                landmarks.push_back(point);
            }

            keyframe.multi_camera_data[camera_index].pose                 = T_wc;
            keyframe.multi_camera_data[camera_index].features             = selected_features;
            keyframe.multi_camera_data[camera_index].associated_landmarks = ids;
            keyframe.multi_camera_data[camera_index].mappoints            = landmarks;
        }
        new_keyframes_database.emplace(keyframe.frame_id, keyframe);
    }
    LOG(INFO) << "MapDatabaseManager --- Retrive key frames: " << new_keyframes_database.size();
    return new_keyframes_database;
}

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo
