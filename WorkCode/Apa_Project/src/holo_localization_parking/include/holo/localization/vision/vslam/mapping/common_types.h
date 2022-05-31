/*!
 * \brief common types in visual mapping
 * \author Feng. Li, lifeng@holomatic.com
 * \date Mar-13-2020
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_MAPPING_COMMON_TYPES_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_MAPPING_COMMON_TYPES_H_

#include <holo/localization/vision/3rdparty/BowVector.h>
#include <holo/localization/vision/vslam/common_types.h>
#include <holo/localization/vision/vslam/feature_track.h>
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
 * @brief map database class
 *
 * @details this file defines some basic data structure for visual based offline mapping task
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief support pair as key of unordered_map
 */
struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const
    {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

typedef std::pair<uint64_t, uint64_t> PairHashedKey;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief support comparation between two pose pair
 */
struct ComparePose3Pair
{
    bool operator()(const std::pair<Pose3, Pose3>& p1, const std::pair<Pose3, Pose3>& p2) const
    {
        return (p1.first.GetX() < p2.first.GetX()) ||
               (p1.first.GetX() == p2.first.GetX() && p1.first.GetY() < p2.first.GetY()) ||
               (p1.first.GetX() == p2.first.GetX() && p1.first.GetY() == p2.first.GetY() &&
                p1.first.GetZ() < p2.first.GetZ());
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief handy type define
typedef std::unordered_map<uint64_t, FeatureTrack> IndexedTracks;

/**
 * @brief typedef camera index to image map
 * @details key: camera index, value: image name in disk.
 */
typedef std::unordered_map<uint16_t, std::string> CameraIndexedImage;

/**
 * @brief typedef frame id to images map
 * @details key: frame_id, value: camera index to image map
 */
typedef std::unordered_map<uint64_t, CameraIndexedImage> FrameIndexedImages;

/**
 * @brief typedef camera index to features map
 * @details key: camera index, value: features.
 */
typedef std::unordered_map<uint16_t, Features> CameraIndexedFeatures;

/**
 * @brief typedef frame id to features map
 * @details key: frame_id, value: camera index to features map
 */
typedef std::unordered_map<uint64_t, CameraIndexedFeatures> FrameIndexedFeatures;

/**
 * @brief typedef pair<query map id, train map id> or pair<query frame id, train frame id> to transform map
 * @details key: pair<query map id, train map id> or pair<query frame id, train frame id>, query frame and train frame
 *          exist in query map and train map correspondingly
 *          value: transform between two maps or two frames
 */
typedef std::unordered_map<PairHashedKey, Pose3, pair_hash> QueryMapToTrainMapTransformPairs;

/**
 * @brief typedef about camera's Bow (bag-of-words) vector
 * 
 * @details Key -> camera_id (one keyframe may have multi camera)
 *          Value -> bag_of_word about one image (bow vector about current camera's image)
 */
using CameraIndexedBow = std::unordered_map<uint16_t, DBoW3::BowVector>;

/**
 * @brief typedef about KeyFrames's Bow (bag-of-words) vector
 * 
 * @details Key -> keyframe_id (one keyframe may have multi camera)
 *          Value -> bag_of_words about one keyframe(bow vector about current keyframe's multi images)
 */
using FrameIndexedBows = std::unordered_map<uint64_t, CameraIndexedBow>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define frame struct
 *
 */
struct Frame
{
    /// @brief define single camera data of a frame
    struct SingleCameraData
    {
        /// @brief image. which is gray scale and has been well undistorted.
        cv::Mat image;

        /// @brief image name, use to load images from disk.
        std::string image_name;

        /// @brief features extracted on this frame
        Features features;

        /// @brief camera pose of this frame
        Pose3 pose;

        /// @brief associated landmark ids, this vector is one-to-one cooresponding to features.
        /// @note. value less than zero mean this feature does not associated to any landmark.
        std::vector<int64_t> associated_landmarks;
    };

    /// @brief frame id
    uint64_t frame_id;

    /// @brief multi camera data
    std::vector<SingleCameraData> multi_camera_data;

    /// @brief camera parameters
    CameraParameters::Ptr camera_parameters;

    /// @brief constructor
    Frame(const uint64_t _frame_id = 0, const CameraParameters::Ptr _camera_parameters = nullptr)
      : frame_id(_frame_id), camera_parameters(_camera_parameters)
    {
        multi_camera_data.resize(camera_parameters->camera_number);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define key frame struct
 * @details A frame is the selected keyframe in prebuilt map
 */
struct KeyFrame
{
    /// @brief define single camera data of a frame
    struct SingleCameraData
    {
        /// @brief features extracted on this frame
        Features features;

        /// @brief camera pose of this frame
        Pose3 pose;

        /// @brief associated landmark ids, this vector is one-to-one cooresponding to features.
        /// @note. value less than zero mean this feature does not associated to any landmark.
        std::vector<int64_t> associated_landmarks;

        ///@brief associated 3d points, this vector is one-to-one cooresponding with features.
        std::vector<Point3> mappoints;
    };

    /// @brief frame id
    uint64_t frame_id;

    /// @brief vehicle pose
    Pose3 pose;

    /// @brief multi camera data
    std::vector<SingleCameraData> multi_camera_data;

    /// @brief constructor
    KeyFrame(const uint64_t _frame_id = 0, const Pose3& _pose = Pose3(), const uint64_t camera_num = 1)
      : frame_id(_frame_id), pose(_pose)
    {
        multi_camera_data.resize(camera_num);
    }
};
using KeyFramesDatabase = std::map<uint64_t, KeyFrame>;
using SubMappingResults = std::vector<std::pair<Map, KeyFramesDatabase>>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define framedatabase
 *
 */
class FramesDatabase
{
public:
    /// @brief default construction
    FramesDatabase();

    ///@brief constuct from multi databases
    FramesDatabase(const std::vector<FramesDatabase>& frames_databases);

    /// @brief add new frame to this database
    void AddFrame(const Frame& frame);

    /// @brief check if exist this frame
    bool Exists(const uint64_t frame_id) const;

    /// @brief query frame from this database
    const Frame& GetFrame(const uint64_t frame_id) const;

    /// @brief get number of feature tracks of this database
    uint64_t Size() const;

    /// @brief get descriptor dimension
    /// @return -1 means database is empty or feature has no descriptor.
    int16_t GetDescriptorDimension() const;

    /// @brief check if this database is empty
    bool IsEmpty() const;

    /// @brief get all frames
    const std::map<uint64_t, Frame>& GetAllFrames() const;

    /// @brief get all frames
    std::map<uint64_t, Frame>& GetAllFrames();

    /// @brief the flag to judge if the database is from multi map merging
    bool IsFromMultiDatabaseMerging() const;

private:
    /// @brief database:  frame id to frame data map
    std::map<uint64_t, Frame> frames_database_;

    /// @brief the mode of database
    bool is_from_multi_database_merging_;

};  // FramesDatabase

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define feature tracks database
 *
 */
class TracksDatabase
{
public:
    /// @brief default construction
    TracksDatabase();

    ///@brief constuct from multi databases
    TracksDatabase(const std::vector<TracksDatabase>& tracks_databases);

    /// @brief add new track to this database
    void AddFeatureTrack(const FeatureTrack& track);

    /// @brief add a set of tracks to this database
    void AddFeatureTracks(const std::vector<FeatureTrack>& tracks);

    /// @brief update track with frame id and feature
    void UpdateFeatureTrack(const uint64_t landmark_id, uint64_t frame_id, const Feature& feature);

    /// @brief update track
    void UpdateFeatureTrack(const uint64_t landmark_id, const FeatureTrack& track);

    /// @brief erase track from this database
    void Erase(const uint64_t landmark_id);

    /// @brief check if exist this track
    bool Exists(const uint64_t landmark_id) const;

    /// @brief query feature track from this database
    const FeatureTrack& GetTrack(const uint64_t landmark_id) const;

    /// @brief get descriptor dimension
    /// @return -1 means database is empty or feature has no descriptor.
    int16_t GetDescriptorDimension() const;

    /// @brief get number of feature tracks of this database
    uint64_t Size() const;

    /// @brief get all tracks
    const std::unordered_map<uint64_t, FeatureTrack>& GetAllTracks() const;

    /// @brief check if this database is empty
    bool IsEmpty() const;

private:
    /// @brief database:  landmark id to track data map
    std::unordered_map<uint64_t, FeatureTrack> tracks_database_;

};  // TracksDatabase

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define feature tracks database
 *
 */
class ParkingSlotTracksDatabase
{
public:
    /// @brief default construction
    ParkingSlotTracksDatabase();

    ///@brief constuct from database
    ParkingSlotTracksDatabase(const ParkingSlotTracksDatabase& parking_slot_tracks_database);

    /// @brief add new track to this database
    void AddParkingSlotTrack(const semantic::ParkingSlotTrack& parking_slot_track);

    /// @brief add a set of tracks to this database
    void AddParkingSlotTracks(const std::vector<semantic::ParkingSlotTrack>& parking_slot_tracks);

    /// @brief update track with frame id and feature
    // void UpdateParkingSlotTrack(const uint64_t landmark_id, uint64_t frame_id, const Feature& feature);

    /// @brief update track
    // void UpdateParkingSlotTrack(const uint64_t landmark_id, const FeatureTrack& track);

    /// @brief erase track from this database
    // void Erase(const uint64_t landmark_id);

    /// @brief check if exist this track
    // bool Exists(const uint64_t landmark_id) const;

    /// @brief query feature track from this database
    // const FeatureTrack& GetTrack(const uint64_t landmark_id) const;

    /// @brief get descriptor dimension
    /// @return -1 means database is empty or feature has no descriptor.
    // int16_t GetDescriptorDimension() const;

    /// @brief get number of feature tracks of this database
    uint64_t Size() const;

    /// @brief get all tracks
    const std::vector<semantic::ParkingSlotTrack>& GetAllParkingSlotTracks() const;

    /// @brief check if this database is empty
    bool IsEmpty() const;

private:
    /// @brief database: parking slot tracks
    std::vector<semantic::ParkingSlotTrack> parking_slot_tracks_database_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define database for a offline mapping process
 *
 */
struct MappingDatabase
{
    /// @brief map id
    holo::uint64_t map_id;

    /// @brief images
    FrameIndexedImages images;

    /// @brief features
    FrameIndexedFeatures frame_indexed_features;

    /// @brief imu measumrements.
    /// @note each element of this variable represent a set of imu measurement between two frames
    std::vector<std::vector<Imu>> imus;

    /// @brief velocity measurements
    std::vector<VelocityMeasurement> velocities;

    /// @brief wheel integration measurements
    std::vector<WheelIntegrationMeasurement> wheel_integrations;

    /// @brief UTM position measurements
    std::vector<UtmPosition> positions;

    /// @brief associated feature tracks
    TracksDatabase tracks_database;

    /// @brief associated parking slot tracks
    ParkingSlotTracksDatabase parking_slot_tracks_database;

    /// @brief values(X V B only) optimized by an online estimator
    Values xvb_values;

    /// @brief timestamp to frame id map
    std::map<Timestamp, uint64_t> timestamp_to_frame_id;

    /// @brief frame id to timestamp map
    std::map<uint64_t, Timestamp> frame_id_to_timestamp;

    /// @brief camera parameters
    CameraParameters::Ptr camera_parameters;

    /// @brief ground truth that loaded from file
    std::vector<Odometry> ground_truth_odometry;

    bool enable_estimation_with_acc;

    /// @brief imu factors
    std::unordered_map<uint64_t, FactorGraph::Base::sharedFactor> imu_factors;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define map's quality
 * @details Localization in an EXCELLENT map can obtain high accuracy result, while the accuracy when localization in a
 * BAD map can not be guaranteed.
 */
enum class MapQuality : uint16_t
{
    EXCELLENT = 0,  ///< the quality of the map is excellent
    GOOD      = 1,  ///< the quality of the map is good
    MEDIUM    = 2,  ///< the quality of the map is just so so
    BAD       = 3,  ///< the quality of the map is bad
};

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_MAPPING_COMMON_TYPES_H_
