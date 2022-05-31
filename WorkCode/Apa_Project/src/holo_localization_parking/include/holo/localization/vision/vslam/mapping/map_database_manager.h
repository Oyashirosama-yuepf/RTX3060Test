/*!
 * \brief map database manager class head file in vslam
 * \author Feng. Li, lifeng@holomatic.com
 * \date Mar-13-2020
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_MAPPING_MAP_DATABASE_MANAGER_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_MAPPING_MAP_DATABASE_MANAGER_H_

#include <holo/localization/vision/vslam/common_types.h>
#include <holo/localization/vision/vslam/feature_track.h>
#include <holo/localization/vision/vslam/localization/relocalization.h>
#include <holo/localization/vision/vslam/mapping/common_types.h>
#include <holo/localization/vision/vslam/semantic/parking_slot_track.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @ingroup localization
 * @brief map database manager class
 *
 * @details this class is mainly responsible for manage all mapping data.
 * it can save the intermediate results and the raw sensor data of an online mapping process for further offline global
 * loop detection and optimization.
 */

class MapDatabaseManager
{
public:
    // define smart pointer
    using Ptr      = std::shared_ptr<MapDatabaseManager>;
    using ConstPtr = std::shared_ptr<const MapDatabaseManager>;

    /**
     * @brief define voxel gridding frame ids
     *
     * @details some application may need assign frames to voxel grid with certain distance resolution and angle
     * resolution according to each frame's vehicle pose. for convenience, we hashing the index of a frame in voxel
     * grids to an unique key.
     * key: hashing value of index(x, y, z, and angle) in voxel grid, value: all frame id belongs to this grid
     */
    typedef std::unordered_map<std::string, std::set<uint64_t>> GriddingFrameIds;

    ///@brief statistics data related to reprojection error
    struct ReprojectionErrorData
    {
        ///@brief the mean reprojection error of mappoints
        std::vector<Scalar> reprojection_error_sequence;

        ///@brief mean of the sequence
        Scalar mean;

        /// median of the sequence
        Scalar median;

        /// maxmum of the sequence
        Scalar maxmum;

        /// minimum of the sequence
        Scalar minimum;
    };

    /// @brief define map quality indicators
    struct MapQualityIndicators
    {
        /// @brief max speed during build this map
        Scalar max_speed;

        /// @brief total travel distance
        Scalar travel_distance;

        /// @brief total landmarks number
        uint64_t landmarks_number;

        /// @brief landmarks density. equals to landmarks_number / travel_distance
        Scalar landmarks_density;

        /// @brief voxel grid number.
        uint64_t voxel_grid_number;

        /// @brief keyframe_number
        uint64_t keyframe_number;

        /// @brief keyframe_density.  equals to keyframe_number / voxel_grid_number
        Scalar keyframe_density;

        /// @brief max travel distance without keyframes
        Scalar max_travel_distance_without_keyframes;

        /// @brief is there keyframes around start point
        bool is_there_keyframe_around_start_point;

        ///@brief data related to reprojection error
        ReprojectionErrorData reprojection_error_data;

        ///@brief mean average accuracy of the map
        Scalar mean_average_accuracy;

        /// @brief default constructor
        MapQualityIndicators()
          : max_speed(0.0)
          , travel_distance(0.0)
          , landmarks_number(0)
          , landmarks_density(0.0)
          , voxel_grid_number(0)
          , keyframe_number(0)
          , keyframe_density(0.0)
          , max_travel_distance_without_keyframes(0.0)
          , is_there_keyframe_around_start_point(false)
          , mean_average_accuracy(0.0)
        {
        }

        // output stream
        friend std::ostream& operator<<(std::ostream& os, const MapQualityIndicators& map_quality_indicators)
        {
            os << "the map quality indicators:\n";
            os << "                                    max_speed: " << map_quality_indicators.max_speed << " km/h\n"
               << "                              travel_distance: " << map_quality_indicators.travel_distance
               << " meter\n"
               << "                             landmarks_number: " << map_quality_indicators.landmarks_number << "\n"
               << "                            landmarks_density: " << map_quality_indicators.landmarks_density << "\n"
               << "                            voxel_grid_number: " << map_quality_indicators.voxel_grid_number << "\n"
               << "                              keyframe_number: " << map_quality_indicators.keyframe_number << "\n"
               << "                             keyframe_density: " << map_quality_indicators.keyframe_density << "\n"
               << "        max_travel_distance_without_keyframes: "
               << map_quality_indicators.max_travel_distance_without_keyframes << " meter\n"
               << "         is_there_keyframe_around_start_point: "
               << map_quality_indicators.is_there_keyframe_around_start_point << "\n"
               << "                                          mAA: " << map_quality_indicators.mean_average_accuracy
               << "\n"
               << "     reprojection_error(max/mini/mean/median): "
               << map_quality_indicators.reprojection_error_data.maxmum << " "
               << map_quality_indicators.reprojection_error_data.minimum << " "
               << map_quality_indicators.reprojection_error_data.mean << " "
               << map_quality_indicators.reprojection_error_data.median << "\n";

            return os;
        }
    };

    /// @brief define keyframe selection parameters
    struct KeyFrameSelectionParameters
    {
        /// @brief minimum distance interval. meter
        const Scalar minimum_distance_interval;

        /// @brief minimum_angle interval. degree
        const Scalar minimum_angle_interval;

        /// @brief minimum observed landmark number
        const uint16_t minimum_observed_landmark_num;

        /// @brief constructor
        KeyFrameSelectionParameters(const Scalar   _minimum_distance_interval     = 5.0,
                                    const Scalar   _minimum_angle_interval        = 5.0,
                                    const uint16_t _minimum_observed_landmark_num = 50)
          : minimum_distance_interval(_minimum_distance_interval)
          , minimum_angle_interval(_minimum_angle_interval)
          , minimum_observed_landmark_num(_minimum_observed_landmark_num)
        {
        }
    };

    /// @brief define parameters
    struct Parameters
    {
        /// @brief directory used to store all mapping data
        const std::string map_data_dir;

        /// @brief map name. support multi map merging
        /// @details each map name is also a sub directory in ${map_data_dir}
        const std::vector<std::string> map_names;

        /// @brief define working mode: online data association or offline optimization
        const std::string mode;

        /// @brief save raw images
        const bool save_image;

        /// @brief keyframe selection parameters
        const KeyFrameSelectionParameters kf_selection_params;

        ///@brief max distance without keyframe
        const Scalar max_dis_without_kf;

        /// @brief constructor
        Parameters(const std::string& _map_data_dir, const std::vector<std::string>& _map_names,
                   const std::string& _mode, const bool _save_image = false,
                   const KeyFrameSelectionParameters& _kf_selection_params = KeyFrameSelectionParameters(),
                   const Scalar                       _max_dis_without_kf  = 15.0)
          : map_data_dir(_map_data_dir)
          , map_names(_map_names)
          , mode(_mode)
          , save_image(_save_image)
          , kf_selection_params(_kf_selection_params)
          , max_dis_without_kf(_max_dis_without_kf)
        {
        }

        // output stream
        friend std::ostream& operator<<(std::ostream& os, const Parameters& parameters)
        {
            os << "MapDatabaseManagerParameters: "
               << "\n  map_data_dir = " << parameters.map_data_dir;

            if (!parameters.map_names.empty())
            {
                os << "\n map_names:";

                for (const auto& map_name : parameters.map_names)
                {
                    os << "\n  " << map_name;
                }
            }

            os << "\n  save_image = " << parameters.save_image << "\n  kf_selection_params.minimum_distance_interval = "
               << parameters.kf_selection_params.minimum_distance_interval
               << "\n  kf_selection_params.minimum_angle_interval = "
               << parameters.kf_selection_params.minimum_angle_interval
               << "\n  kf_selection_params.minimum_observed_landmark_num = "
               << parameters.kf_selection_params.minimum_observed_landmark_num
               << "\n max distance without kf: " << parameters.max_dis_without_kf << std::endl;
            return os;
        }

        /// @brief load parameters from yaml
        static Parameters LoadFromYaml(const holo::yaml::Node& node);

        /// @brief an example parameters
        static Parameters Example();
    };

    /**
     * @brief define the input data for offline mapping
     * @details the input data for offline mapping is the output of the online sliding window estimator. it contains the
     * preliminary estimated values(X V B L), associated features, and the corrected sensor data. when the online
     * sliding window estimator will marginalize a frame. we collect all necessary data associated to the marginalized
     * frame and save to disk for offline mapping.
     */
    struct OfflineMappingData
    {
        /// @brief map name
        std::string map_name;

        /// @brief associated frame id of these data.
        /// @brief generally, this frame will be marginalized by the online sliding window estimator.
        uint64_t frame_id;

        /// @brief features extracted on multi-image
        CameraIndexedFeatures indexed_features;

        /// @brief estimated values by online sliding window estimator. only x v b are available
        Values estimated_xvb_values;

        /// @brief feature tracks
        /// @details generally, it contain tracks which will be marginalized by the online sliding window estimator.
        /// it also contain the newest landmark position which has been optimized several times by gtsam.
        std::vector<FeatureTrack> tracks;

        /// @brief parking slot tracks
        std::vector<semantic::ParkingSlotTrack> parking_slot_tracks;

        /// @brief corrected sensor measurements associated with *this frame id
        CorrectedMeasurement corrected_measurements;

        /// @brief camera parameters
        CameraParameters::Ptr camera_parameters;

        /// @brief imu factors
        FactorGraph::Base::sharedFactor imu_factor;
    };

    /**
     * @brief contain parking slot database and target parking slot id
     */
    struct ParkingSlotData
    {
        /// @brief all optimized parking slot
        std::vector<holo::common::ParkingSlot> parking_slot_database;

        /// @brief target parking slot id
        uint64_t target_parking_slot_id = 0;
    };

    /// @brief constructor
    MapDatabaseManager(const Parameters& parameters);

    /// @brief destructor
    ~MapDatabaseManager();

    /**
     * @brief save the data association results and the corrected sensor measurement of an online mapping process
     *
     * @param mapping_data all mapping data
     */
    void SaveMappingDataForOfflineOptimization(const OfflineMappingData& mapping_data);

    /**
     * @brief query mapping database for offline tasks.
     *
     * @return mapping database.
     */
    const std::unordered_map<std::string, MappingDatabase>& GetMappingDatabases() const
    {
        return mapping_databases_;
    }

    /**
     * @brief get parameters
     */
    const Parameters& GetParameters() const
    {
        return parameters_;
    }

    /**
     * @brief get prebuilt map
     */
    const MapPtr& GetPrebuiltMap() const
    {
        return prebuilt_map_;
    }

    /**
     * @brief get prebuilt map
     */
    const SlotMapPtr& GetPrebuiltSlotMap() const
    {
        return prebuilt_slot_map_;
    }

    /**
     * @brief get key frames
     */
    const KeyFramesDatabase& GetKeyframes() const
    {
        return key_frames_database_;
    }

    /**
     * @brief get keyframe's bow vector
     */
    const FrameIndexedBows& GetKeyframesBowVector() const
    {
        return keyframes_bow_vectors_;
    }

    /**
     * @brief get learned path
     */
    const std::vector<Odometry>& GetLearnedPath() const
    {
        return learned_path_;
    }

    /**
     * @brief save map(which include mappoints, trajectory, keyframes) to file. meanwhile evaluate quality of the map.
     *
     * @param optimized_values optimized values
     * @param frame_database the frame database
     * @param tracks_database triangulated tracks_database
     * @return the quality of this map
     */
    MapQuality SaveAndEvaluateQualityOfTheOptimizedMap(const Values&         optimized_values,
                                                       const FramesDatabase& frame_database,
                                                       const std::string&    map_name,
                                                       const TracksDatabase& tracks_database) const;

    /**
     * @brief save merged map after optimizing(which include mappoints, trajectory, keyframes) to file.
     *
     * @param optimized_values optimized values
     * @param frame_database the frame database
     * @param map_database the map database
     * @param tracks_database the tracks database
     * @return the quality of this map
     */
    void SaveTheMergedMapAfterOptimizing(const Values& optimized_values, const FramesDatabase& frame_database,
                                         const MappingDatabase& map_database, const TracksDatabase& tracks_database,
                                         const std::string& map_name) const;

    /**
     * @brief save avp map after optimizing(which include mappoints, keyframes) to file.
     *
     * @param optimized_values optimized values
     * @param frame_database the frame database
     * @param map_name the map name
     * @param pose_compensation pose compensation
     * @return the quality of this map
     */
    void SaveTheAvpMapAfterOptimizing(const Values& optimized_values, const FramesDatabase& frame_database,
                                      const Map& map, const std::string& map_name,
                                      const Pose3& pose_compensation) const;

    /**
     * @brief Assign all frames to vovel grid
     *
     * @param values the optimized values
     * @param frame_database the frame database to be processed
     * @return gridding frame ids
     */
    GriddingFrameIds AssignFramesToVoxelGrid(const Values& values, const FramesDatabase& frame_database) const;

    /**
     * @brief select keyframes
     * @details each grid will generated one or zero keyframe, two conditions to determine keyframe:
     * a. associated landmarks' quality is most excellent in this grid.
     * b. associated landmarks' quality is more excellent than threshold define in config file.
     *
     * @param values optimized values
     * @param frame_database the frame database
     * @param gridding_frame_ids the gridding frame ids
     * @return keyframe ids
     */
    std::vector<uint64_t> SelectKeyFrames(const Values& values, const FramesDatabase& frame_database,
                                          const GriddingFrameIds& gridding_frame_ids) const;

    /**
     * @brief update prebilt map and keyframes database by new maps and keyframes databases
     *
     * @param sub_maps_keyframes_databases the new maps and keyframes databases
     */
    void UpdatePrebiltMapAndKeyFramesDatabase(const SubMappingResults& sub_maps_keyframes_databases);

    /**
     * @brief save map and key frames in files
     */
    void SaveMapAndKeyFrames() const;

    /**
     * @brief save updated map for further localization
     *
     * @param map updated map
     * @param map_name map name
     * @return void
     */
    void SaveMap(const Map& map, const std::string& map_name) const;

    /**
     * @brief save updated parking slot map
     *
     * @param parking_slot_map updated map
     * @param map_name map name
     * @return target parking slot id
     */
    int64_t SaveParkingSlotMapAndTargetID(const std::vector<ParkingSlotType>& parking_slot_map, const Point3& end_point,
                                          const std::string& map_name) const;

    /**
     * @brief save updated map state for debug
     *
     * @param map updated map
     * @param map_name map name
     * @return void
     */
    void SaveUpdatedMapStates(const Map& map, const std::string& map_name) const;

    /**
     * @brief save  key frames for further localization
     *
     * @param keyframes_database keyframes database
     * @return void
     */
    void SaveKeyFrames(const KeyFramesDatabase& keyframes_database, const std::string& map_name) const;

    /**
     * @brief save keyframe's bag-of-words for further localization initialize
     *
     * @param keyframes_database frames database
     * @param keyframe_ids all keyframe ids
     * @param map_name storge map name
     *
     * @return void
     */
    void SaveKeyFramesBowVector(FramesDatabase const& frames_database, std::vector<uint64_t> const& keyframe_ids,
                                const std::string& map_name) const;

    /**
     * @brief update mapping database
     *
     * @param mapping_data offline mapping data
     * @return void
     */
    void UpdateMappingDatabase(const OfflineMappingData& mapping_data);

    /**
     * @brief clear up mapping database
     */
    void CleanMappingDatabase();

private:
    /**
     * @brief load mapping database from disk.
     * @note this funtion will be call automatically in constructor when and only when this map_dababase_manager is
     * use by an offline optimization application.
     *
     * @param parameters parameters which contain all neccessary files,
     * @return mapping database.
     */
    void LoadMappingDatabase(const Parameters& parameters);

    /**
     * @brief save value(X B V) to file
     *
     * @details the format of a single value file will be:
     * frame_id tx ty tz qw qx qy qz vx vy vz bias_acc_x bias_acc_y bias_acc_z bias_gyro_x bias_gyro_y bias_gyro_z
     *
     * @param frame_id current frame id
     * @param values values
     * @param map_name which map does this data comes from
     */
    void SaveXVBValue(const uint64_t frame_id, const Values& values, const std::string& map_name) const;

    /**
     * @brief save online trajectory to file
     *
     * @param frame_id current frame id
     * @param timestamp current timestamp
     * @param values values
     * @param map_name which map does this data comes from
     */
    void SaveOnlineTrajectory(const uint64_t frame_id, const holo::Timestamp& timestamp, const Values& values,
                              const std::string& map_name) const;

    /**
     * @brief save online ground truth trajectory to file
     *
     * @param gt_odo current ground truth
     * @param map_name which map does this data comes from
     */
    void SaveGroundTruthOdometry(const Odometry& gt_odo, const std::string& map_name) const;

    /**
     * @brief save imu measurements to file
     *
     * @param frame_id current frame id
     * @param values values
     * @param map_name which map does this data comes from
     */
    void SaveImus(const std::vector<Imu>& imus, const std::string& map_name) const;

    /**
     * @brief save velocity measurements to file
     *
     * @param timestamp timestamp of this measurement
     * @param velocity velocity in body frame
     * @param map_name which map does this data comes from
     */
    void SaveVelocity(const Timestamp& timestamp, const Vector3& velocity, const std::string& map_name) const;

    /**
     * @brief save wheel integration measurements to file
     *
     * @param timestamp timestamp of this measurement
     * @param velocity velocity in body frame
     * @param map_name which map does this data comes from
     */
    void SaveWheelIntegrationMeasurement(const WheelIntegrationMeasurement& wim, const std::string& map_name) const;

    /**
     * @brief save vehicle info to file
     *
     * @param chassis_state
     * @param map_name which map does this data comes from
     */
    void SaveChassisState(const ChassisState& chassis_state, const std::string& map_name) const;

    /**
     * @brief save position to file
     *
     * @param position UTM position
     * @param map_name which map does this data comes from
     */
    void SaveUTMPosition(const UtmPosition& position, const std::string& map_name) const;

    /**
     * @brief save images to file
     *
     * @param frame_id associated frame id of these images
     * @param images images come from multi camera which were triggered at the same time.
     * @param map_name which map does this data comes from
     */
    void SaveImages(const uint64_t frame_id, const std::vector<Image>& images, const std::string& map_name) const;

    /**
     * @brief save features to file
     *
     * @param frame_id associated frame id of these features
     * @param multi_camera_features features come from multi camera system.
     * @param map_name which map does this data comes from
     */
    void SaveFeatures(const uint64_t frame_id, const CameraIndexedFeatures& multi_camera_features,
                      const std::string& map_name) const;

    /**
     * @brief save timestamp and frame id pair to file
     *
     * @param timestamp the timestamp
     * @param frame_id the frame id
     * @param map_name which map does this data comes from
     */
    void SaveTimestampAndFrameId(const Timestamp& timestamp, const uint64_t frame_id,
                                 const std::string& map_name) const;

    /**
     * @brief save feature tracks to file.
     * @note we assume that all tracks to be processed has been well triangulated.
     *
     * @param tracks_database the tracks_database to be saved
     * @param map_name which map does this data comes from
     */
    void SaveTracks(const TracksDatabase& tracks_database, const std::string& map_name) const;

    /**
     * @brief save feature tracks to file.
     * @note we assume that all tracks to be processed has been well triangulated.
     *
     * @param parking_slot_tracks_database the tracks_database to be saved
     * @param map_name which map does this data comes from
     */
    void SaveParkingSlotTracks(const ParkingSlotTracksDatabase& parking_slot_tracks_database,
                               const std::string&               map_name) const;

    /**
     * @brief save camera parameters to file.
     *
     * @param camera_parameters the camera_parameters to be saved
     * @param map_name which map does this data comes from
     */
    void SaveCameraParameters(const CameraParameters::Ptr& camera_parameters, const std::string& map_name) const;

    /**
     * @brief save map and trajectory to file.
     * @param map processed map
     * @param trajectory vehicle trajectory
     *  @param map_name which map does this data comes from
     */
    void SaveMapAndTrajectory(const Map& map, const std::vector<Odometry>& trajectory,
                              const std::string& map_name) const;

    /**
     * @brief load x.v.b values from file.
     */
    Values LoadXVBValues(const std::string& file_name) const;

    /**
     * @brief load tracks from file.
     */
    TracksDatabase LoadTracks(const std::string& file_name, const CameraParameters::Ptr& camera_parameters) const;

    /**
     * @brief load parking slot tracks from file.
     */
    ParkingSlotTracksDatabase LoadParkingSlotTracks(const std::string& file_name) const;

    /**
     * @brief load images from file.
     */
    FrameIndexedImages LoadImages(const std::string& file_name) const;

    /**
     * @brief load features from file.
     */
    FrameIndexedFeatures LoadFeatures(const std::string& file_name) const;

    /**
     * @brief load imu measurements from file.
     */
    std::vector<std::vector<Imu>> LoadImus(const std::string& file_name) const;

    /**
     * @brief load velocities measurements from file.
     */
    std::vector<VelocityMeasurement> LoadVelocities(const std::string& file_name) const;

    /**
     * @brief load wheel integration measurements from file.
     */
    std::vector<WheelIntegrationMeasurement> LoadWheelIntegrationMeasurements(const std::string& file_name) const;

    /**
     * @brief load utm position from file.
     */
    std::vector<UtmPosition> LoadUTMPositions(const std::string& file_name) const;

    /**
     * @brief load timestamp and frame id from file.
     */
    std::vector<std::pair<Timestamp, uint64_t>> LoadTimeStampAndFrameId(const std::string& file_name) const;

    /**
     * @brief create map and vehicle trajectory from optimized value
     *
     * @param values optimized values
     *
     * @param tracks_database triangulated tracks_database
     *
     * @return pair of map and trajectory
     */
    std::pair<Map, std::vector<Odometry>> CreateMapAndTrajectory(const Values&          values,
                                                                 const TracksDatabase&  tracks_database,
                                                                 const MappingDatabase& mapping_database) const;

    /**
     * @brief create parking slot map from optimized value
     *
     * @param values optimized values
     *
     * @return vector of parking slots
     */
    std::vector<ParkingSlotType> CreateParkingSlotMap(const Values&          values,
                                                      const MappingDatabase& mapping_database) const;

    /**
     * @brief convert map to point clouds type
     */
    PointCloudXYZIRRgbSt ConvertToPointCloud(const Map& map, const Pose3& pose_compensation = Pose3()) const;

    /**
     * @brief convert keyframe's camera view to point clouds
     * @details this function will create some points which can represent each keyframe's camera view. then user can
     * visualize these camera view for debugging.
     *
     * @param optimized_values the optimized value, include optimized pose of all frames
     * @param frame_database the frame database
     * @param keyframe_ids all keyframe ids
     * @param pose_compensation pose compensation
     * @return point clouds of all keyframe's all camera view
     */
    PointCloudXYZIRRgbSt ConvertToPointCloud(const Values& optimized_values, const FramesDatabase& frame_database,
                                             const std::vector<uint64_t>& keyframe_ids,
                                             const Pose3&                 pose_compensation = Pose3()) const;

    /**
     * @brief convert trajectory to point clouds type
     */
    PointCloudXYZIRRgbSt ConvertToPointCloud(const std::vector<Odometry>& trajectory,
                                             const Pose3&                 pose_compensation = Pose3()) const;

    /**
     * @brief convert parking slot map to point clouds type
     */
    PointCloudXYZIRRgbSt ConvertToPointCloud(const std::vector<ParkingSlotType>& slot_map,
                                             uint64_t                            target_parking_slot_id) const;

    /**
     * @brief Generate sample point on line between start and end
     *
     * @param start start point
     * @param end end point
     * @return the generated sample point in line
     */
    void GeneratePointOnLine(const Point3& start, const Point3& end, std::vector<Point3>& pts) const;

    /**
     * @brief generate pointcloud between two points
     * @details this function will generate some points between start and end with constant increment. the return
     * pointcloud can represent a line between these two points.
     *
     * @param start the start point
     * @param end the end point
     * @param points_num the number of points to be generated
     * @return point clouds between start and end
     */
    PointCloudXYZIRRgbSt GeneratePointCloudBetween(const Point3& start, const Point3& end,
                                                   const uint16_t points_num = 10) const;

    /**
     * @brief clear up directory
     * @param clear_merge_dir the flag whether clean old merge result or not
     */
    void CleanUpDirectory(const bool& clear_merge_dir = false) const;

    /**
     * @brief hashing the index of a frame in voxel grids to an unique key.
     *
     * @param index_x x index in a voxel grid
     * @param index_y y index in a voxel grid
     * @param index_z z index in a voxel grid
     * @param index_angle angle index in a voxel grid
     *
     * @return hashed key of the indexes
     */
    std::string HashingGridIndex(const int64_t index_x, const int64_t index_y, const int64_t index_z,
                                 const int64_t index_angle) const;

    /**
     * @brief Assign a pose to vovel grid
     *
     * @param pose the pose
     * @return hashed key in voxel grid
     */
    std::string AssignPoseToVoxelGrid(const Pose3& pose) const;

    /**
     * @brief compute max travel distance without keyframes
     * @details calling this function when evaluate map quality
     *
     * @param trajectory the vehicle's travel trajectory when build this map
     * @param gridding_frame_ids all frame ids have been assigned to voxel grid
     * @param keyframe_ids key frame ids
     * @return max distance interval no keyframes
     */
    Scalar ComputeMaxTravelDistanceWithoutKeyframes(const std::vector<Odometry>& trajectory,
                                                    const GriddingFrameIds&      gridding_frame_ids,
                                                    const std::vector<uint64_t>& keyframe_ids) const;

    /**
     * @brief checking if there exist keyframe around start point
     * @details calling this function when evaluate map quality
     *
     * @param trajectory the vehicle's travel trajectory when build this map
     * @param gridding_frame_ids all frame ids have been assigned to voxel grid
     * @param keyframe_ids key frame ids
     * @return true if has keyframe around start point
     */
    bool IsThereKeyframeAroundStartPoint(const std::vector<Odometry>& trajectory,
                                         const GriddingFrameIds&      gridding_frame_ids,
                                         const std::vector<uint64_t>& keyframe_ids) const;

    /**
     * @brief compute statitic data related to reprojection error
     * @param  mappoints the mappoints
     * @return void
     */
    void ComputeReprojectionErrorData(const Map& mappoints, MapQualityIndicators& indicator) const;

    /**
     * @brief assign measurment's error to different intervals
     * @param  error the reprojection error
     * @param resolution the sample resolution
     * @return the interval index this error belongs
     */
    uint64_t AssignReprojectionErrorToInterval(const Scalar& error, const Scalar& resolution) const;

    /**
     * @brief compute mean average accuracy based on reprojection error
     * @param  mappoints the mappoints
     * @return mean average accuracy of the map
     */
    Scalar ComputeMeanAverageAccuracy(const Map& mappoints) const;

    /**
     * @brief evaluate quality of given map data
     *
     * @param map_name the map name to be processed
     * @param optimized_value the optimized values
     * @param mappoints all mappoints
     * @param trajectory the vehicle's travel trajectory when build this map
     * @param gridding_frame_ids all frame ids have been assigned to voxel grid
     * @param keyframe_ids key frame ids
     * @return quality of this map
     */
    MapQuality EvaluateMapQuality(const std::string& map_name, const Values& optimized_value, const Map& mappoints,
                                  const std::vector<Odometry>& trajectory, const GriddingFrameIds& gridding_frame_ids,
                                  const std::vector<uint64_t>& keyframe_ids, const bool is_avp_map = false) const;

    /**
     * @brief load map points from bin file
     * @param[in] file_name
     * @return prebuilt map
     */
    MapPtr LoadMap(const std::string& file_name) const;

    /**
     * @brief load parking slot database
     *
     * @param [in] file_name the parking slot file path name
     * @return parking slot map
     * @return
     */
    SlotMapPtr LoadParkingSlotMap(const std::string& file_name);

    /**
     * @brief load parking slot database
     *
     * @param [in] parking_slots_file_name the parking slot file path name
     * @param [out] parking_slot_database the loaded parking slot database
     * @return true: load successfully
     * @return false: load failed
     */
    bool LoadParkingSlotDatabase(const std::string& parking_slots_file_name, ParkingSlotData& parking_slot_data);

    /**
     * @brief load keyframe database from file
     * @param file_name file name contain keyframe database
     * @return key frames database
     */
    KeyFramesDatabase LoadKeyFramesDatabase(const std::string& file_name) const;

    /**
     * @brief load keyframe database from file
     * @param file_name file name contain keyframe database
     * @return key frames database
     */
    FrameIndexedBows LoadKeyFramesBowVector(const std::string& file_name) const;

    /**
     * @brief retrieve key frames database
     * @param values the optimized values
     * @param frames_database the frames database
     * @param keyframe_ids key frame ids
     * @return key frames database
     */
    KeyFramesDatabase RetrieveKeyFramesDatabase(const Values& values, const FramesDatabase& frames_database,
                                                const std::vector<uint64_t>& keyframe_ids) const;

    /// @brief parameters
    const Parameters parameters_;

    /// @brief mapping databases for offline optimization or merging
    static std::unordered_map<std::string, MappingDatabase> mapping_databases_;

    /// @brief feature tracks database
    TracksDatabase tracks_database_;

    /// @brief parking slot tracks database
    ParkingSlotTracksDatabase parking_slot_tracks_database_;

    /// @brief key frames database
    KeyFramesDatabase key_frames_database_;

    /// @brief key frames bow vectors
    FrameIndexedBows keyframes_bow_vectors_;

    // prebuilt map
    MapPtr prebuilt_map_;

    // prebuild parking slot map
    SlotMapPtr prebuilt_slot_map_;

    /// @brief learned path for HPP
    /// @details this variable is just used by hpp, it's the vehicle trajectory when build the pre-built map in mapping
    /// mode
    std::vector<Odometry> learned_path_;

};  // class MapDatabaseManager

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_MAPPING_MAP_DATABASE_MANAGER_H_
