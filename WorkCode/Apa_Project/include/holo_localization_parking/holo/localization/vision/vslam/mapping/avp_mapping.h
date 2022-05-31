/*!
 * \brief avp mapping class header file in vslam
 * \author Peikai. Guo guopeikai@holomatic.com
 * \date Jun-02-2021
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_MAPPING_AVP_MAPPING_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_MAPPING_AVP_MAPPING_H_

#include <boost/circular_buffer.hpp>
#include <thread>

#include <gtsam/geometry/triangulation.h>
#include <gtsam_unstable/nonlinear/BatchFixedLagSmoother.h>

#include <holo/localization/common/localization_base.h>
#include <holo/localization/deep/common_types.h>
#include <holo/localization/deep/raw_measurement_preprocessor.h>
#include <holo/localization/vision/vslam/graph_builder.h>
#include <holo/localization/vision/vslam/mapping/common_types.h>
#include <holo/localization/vision/vslam/mapping/map_database_manager.h>
#include <holo/localization/vision/vslam/triangulator.h>
#include <holo/3d/common/io.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
///////////////////////////////////////////////////////////////////////////////
/**
 * @ingroup localization
 * @brief avp mapping class
 *
 * @details build new avp map in this class
 */

class AvpMapping
{
public:
    /**
     * @brief typedef feature with its own index in the whole track vector
     *
     * @details track_id + Feature
     */
    using IndexedFeatures = std::unordered_map<uint64_t, vslam::Feature>;

    /**
     * @brief typedef camera index with its detected features
     *
     */
    using CameraIndexedFeatures = std::unordered_map<uint64_t, vslam::Features>;
    /**
     * @brief define optimization data
     */
    struct BundleAdjustmentProblem
    {
        std::vector<FeatureTrack> tracks;
        Values                    values;
        FactorGraph               pose_graph;

        /// @brief default constructor
        BundleAdjustmentProblem()
        {
        }
    };

    /**
     * @brief define avp mapping parameters
     */
    struct Parameters
    {
        /// @brief avp map file
        std::string map_file;

        ///@brief avp raw images file path
        std::string images_path;

        /// @brief shared_ptr of camera parameters
        CameraParameters::Ptr camera_params;

        /// @brief shared_ptr of deep camera parameters
        deep::CameraParameters::Ptr deep_camera_params;

        /// @brief raw measurement preprocessor parameters
        deep::RawMeasurementPreprocessor::Parameters rmpp_params;

        /// @brief map database manager parameters
        MapDatabaseManager::Parameters mdm_params;

        /// @brief epipolar line matching max tracking lost frame
        uint64_t elm_max_tracking_lost_frame;

        /// @brief epipolar line matching epipolar dist threshold
        Scalar elm_epipolar_dist_th;

        /// @brief epipolar line matching descriptor dist threshold
        Scalar elm_descriptor_dist_th;

        /// @brief epipolar line matching ratio test threshold
        Scalar elm_ratio_test_th;

        /// @brief triangulator params
        Triangulator::Parameters triangulator_params;

        /// @brief feature track's parameters
        FeatureTrack::Parameters::ConstPtr track_params;

        /// @brief visualizer flag
        bool enable_visualizer;

        ///@brief start frame id
        uint64_t start_frame_id;

        ///@brief end frame id
        uint64_t end_frame_id;

        /// @brief constructor
        Parameters(const std::string& _map_file, const std::string& _images_path,
                   const CameraParameters::Ptr& _camera_params, const deep::CameraParameters::Ptr& _deep_camera_params,
                   const deep::RawMeasurementPreprocessor::Parameters& _rmpp_params,
                   const MapDatabaseManager::Parameters& _mdm_params, const uint64_t _elm_max_tracking_lost_frame,
                   const Scalar _elm_epipolar_dist_th, const Scalar _elm_descriptor_dist_th,
                   const Scalar _elm_ratio_test_th, const Triangulator::Parameters& _triangulator_params,
                   const bool& _enable_visualizer = false, const uint64_t _start_frame_id = 0,
                   const uint64_t _end_frame_id = 0)
          : map_file(_map_file)
          , images_path(_images_path)
          , camera_params(_camera_params)
          , deep_camera_params(_deep_camera_params)
          , rmpp_params(_rmpp_params)
          , mdm_params(_mdm_params)
          , elm_max_tracking_lost_frame(_elm_max_tracking_lost_frame)
          , elm_epipolar_dist_th(_elm_epipolar_dist_th)
          , elm_descriptor_dist_th(_elm_descriptor_dist_th)
          , elm_ratio_test_th(_elm_ratio_test_th)
          , triangulator_params(_triangulator_params)
          , track_params(new FeatureTrack::Parameters(false, false))
          , enable_visualizer(_enable_visualizer)
          , start_frame_id(_start_frame_id)
          , end_frame_id(_end_frame_id)
        {
        }

        // output stream
        friend std::ostream& operator<<(std::ostream& os, const Parameters& parameters)
        {
            os << "AvpMappingParameters:\n"
               << "\n map file = " << parameters.map_file << "\n images path = " << parameters.images_path << "\n"
               << parameters.camera_params << parameters.rmpp_params << parameters.mdm_params
               << "\n elm_max_tracking_lost_frame = " << parameters.elm_max_tracking_lost_frame
               << "\n elm_epipolar_dist_th = " << parameters.elm_epipolar_dist_th
               << "\n elm_descriptor_dist_th = " << parameters.elm_descriptor_dist_th
               << "\n elm_ratio_test_th = " << parameters.elm_ratio_test_th
               << "\n triangulator: " << parameters.triangulator_params
               << "\n enable vis: " << parameters.enable_visualizer
               << "\n start frame id: " << parameters.start_frame_id << "\n end frame id: " << parameters.end_frame_id
               << "\n";
            return os;
        }

        // @brief load parameters from yaml
        static Parameters LoadFromYaml(const holo::yaml::Node& node);

        // @brief an example parameters
        static Parameters Example();
    };  // Parameters

    /**
     * @brief constructor
     */
    AvpMapping(const Parameters& parameters);

    /**
     * @brief destructor
     */
    ~AvpMapping();

    /**
     * @brief get parameters
     */
    const Parameters& Params() const
    {
        return parameters_;
    }

    /**
     * @brief avp map databse
     *
     */
    struct AvpMapDatabase
    {
        std::map<uint64_t, CameraIndexedImage> frame_id_to_images;
        Values                                 values;
    };

    /**
     * @brief load avp map database from files
     *
     * @param file_name the files which includes raw avp data
     * @return AvpMapDatabase
     */
    AvpMapDatabase LoadAvpMapDatabase(const std::string& file_name);

    /**
     * @brief estimator core function
     *
     * @details all the algorithms will be called in this function
     */
    void run();

protected:
    /**
     * @brief it will be called to initialize avp mapping matching window
     * @details create feature tracks by new features
     *
     * @param[in] features the features
     * @param[in] frame_id the frame id
     * @return new feature tracks
     */
    std::vector<FeatureTrack> CreateNewTracks(const CameraIndexedFeatures& features, const uint64_t frame_id) const;

    /**
     * @brief if there are no tracks in matching window, new feature tracks will be created by new features.
     *        otherwise use descriptor to do feature matching.
     *
     * @param[in] tracks the tracks in matching window
     * @param[in] features new features
     * @param[in] values the values
     * @param[in] new_frame_id the new frame id
     */
    void FeatureMatching(std::vector<FeatureTrack>& tracks, const CameraIndexedFeatures& features, const Values& values,
                         const uint64_t new_frame_id) const;

    /**
     * @brief epipolar line matching
     * @details match old tracks by epipolar line matching method, meanwhile update old feature tracks as below:
     *          1. the old tracks will be updated with matched new features
     *          2. the new features which do not match old tracks will be created as new feature tracks
     *          3. the old tracks which do not match new feature will not update
     * @throws std::runtime_error thrown if a frame associated to any input track's newest measurement dose not exist in
     * old_values
     *
     * @param[in, out] old_tracks old feature tracks input (updated feature tracks output)
     * @param old_values old optimized value, it will be used to retrieve optimized poses
     * @param old_frame_id old frame id, will be used to select old tracks to be matched
     * @param new_features new features extracted on new image
     * @param new_frame_id new frame id, use to extend track's measurement
     * @param camera_index camera index, will be used to specify camera parameters
     * @param prior_Twc prior camera pose in wolrd frame
     */
    void MatchOldTracksByEpipolarLineMatching(std::vector<FeatureTrack>& old_tracks, const Values& old_values,
                                              const uint64_t old_frame_id, const vslam::Features& new_features,
                                              const uint64_t new_frame_id, const uint64_t camera_index,
                                              const Pose3& prior_Twc) const;

    /**
     * @brief update tracks with new features
     * @details Classify features into two parts according to the matched pairs:
     *        1. belongs to an old track; theses features will be added to the newest measurement of its matched tracks;
     *        2. belongs to a new feature track, theses feature will used to create a new tracks
     *
     * @param[in,out] old_tracks old feature tracks input (updated feature tracks output)
     * @param[in] old_tracks_index it contains the candidate matching track's index in vector old tracks
     * @param[in] new_features processed features
     * @param[in] new_frame_id the new frame id
     * @param[in] camera_index the new camera index
     * @param[in] match_pairs matched result
     */
    void UpdateTracksWithNewFeatures(std::vector<FeatureTrack>&   old_tracks,
                                     const std::vector<uint64_t>& old_tracks_index, const vslam::Features& new_features,
                                     const uint64_t new_frame_id, const uint64_t camera_index,
                                     const DescriptorMatcher::MatchPairs& match_pairs) const;

    /**
     * @brief triangulate all new tracks
     * @details if the track is triangulated sucessfully, track will be updated with triangulation result.
     *
     * @param[in] tracks the feature tracks
     * @param[in] values the values
     */
    void TriangulateNewTracks(std::vector<FeatureTrack>& tracks, const Values& values) const;

    /**
     * @brief select out tracks which are triangulated sucessfully
     *
     * @param[in] feature_tracks feature tracks in matching window
     *
     * @return feature tracks with landmark
     */
    std::vector<FeatureTrack>
    SelectTracksWithTriangulationResult(const std::vector<FeatureTrack>& feature_tracks) const;

    /**
     * @brief add visual factor to factor graph
     * @details this function will build Unit3Factor by each feature track.
     *
     * @param old_graph old factor graph to be processed
     * @param feature_tracks feature tracks with landmark
     *
     * @return a new factor graph witch contain ImuFactor, ImuBiasFactor, VelocityFactor, GpsFactor(optional),
     * Pose3BetweenFactor, and visual factor
     */
    FactorGraph AddVisualFactorGraph(const Values& values, const FactorGraph& old_graph,
                                     const std::vector<FeatureTrack>& feature_tracks) const;

    /**
     * @brief add landmarks' position to values
     *
     * @param old_values old value to be processed
     * @param feature_tracks feature tracks with landmark
     *
     * @return new values contain all landmarks' position
     */
    Values AddLandmarksToValues(const Values& old_values, const std::vector<FeatureTrack>& feature_tracks);

    /**
     * @brief convert well optimized tracks database to map
     *
     * @param feature_tracks feature tracks with landmark
     * @param values the values after optimization
     * @return the corresponding map
     */
    Map ConvertTracksToMap(const std::vector<FeatureTrack>& feature_tracks, const Values& values) const;

    /**
     * @brief create frames database depending on tracks database
     *
     * @param[in] feature_tracks feature tracks with landmark
     * @param[in] xvb_values xvb values
     *
     * @return frames database
     */
    FramesDatabase CreateFramesDatabase(const std::vector<FeatureTrack>& feature_tracks,
                                        const Values&                    xvb_values) const;

    /**
     * @brief optimization thread
     *
     * @param[in] optimization_data the data (tracks, values, factor graph) to be optimized
     */
    std::pair<std::vector<FeatureTrack>, Values> Optimization(const BundleAdjustmentProblem& optimization_data);

    /**
     * @brief do global bundle adjuestment
     *
     * @param[in] new_factor_graph factor graph
     * @param[in] new_values xvb values
     *
     * @return optimized values
     */
    Values GlobalBundleAdjustment(const FactorGraph& new_factor_graph, const Values& new_values) const;

    /**
     * @brief remove outlier landmarks from values after optimizing
     *
     * @param[in] values old values
     * @param[in] feature_tracks feature tracks with landmark
     *
     * @return new values
     */
    Values RemoveOutlierLandmarksFromValue(const Values& values, const std::vector<FeatureTrack>& feature_tracks) const;

    /**
     * @brief select key frames from the new frames database
     *
     * @param[in] new_frames_database new frames database
     * @param[in] xvb_values xvb values
     * @return new key frames
     */
    KeyFramesDatabase SelectKeyFrames(const FramesDatabase& new_frames_database, const Values& xvb_values) const;

    /**
     * @brief convert deep feature to vslam feature
     *
     * @param[in] feature the deep feature
     * @return the vslam featue
     */
    vslam::Features ConvertDeepToVslamFeatures(const deep::Features& feature);

    /**
     * @brief draw tracks on the current image for visualization
     *
     * @param[in] img the raw image
     * @param[in] frame_id the current frame id
     * @param[in] tracks the filtered tracks
     * @return the image is drawn with tracks
     */
    cv::Mat VisualizeTracks(const cv::Mat& img, const uint64_t frame_id, const std::vector<FeatureTrack>& tracks) const;

    /**
     * @brief draw camera pose in point cloud
     *
     * @param pose the current camera pose
     */
    void DrawCamera(const Pose3& pose);

    /**
     * @brief draw vihecle pose in point cloud
     *
     * @param pose the current vehicle pose
     */
    void DrawTrajectory(const Pose3& pose);

    /**
     * @brief draw line between to 3d point in point cloud
     *
     * @param start the 3d start point
     * @param end the 3d end point
     */
    void DrawLine(const Point3& start, const Point3& end);

    /**
     * @brief load holo avp map database
     *
     * @param img_file_name timestamp_and_frame_id.txt
     * @param values_file_name the init values
     * @return Avp Map Database
     */
    AvpMapDatabase LoadAvpMapDatabase(const std::string& img_file_name, const std::string& values_file_name);

    /**
     * @brief draw matching result between query image and train image
     *
     * @param associated_results the association between tracks on train image and features on query image
     * @param query_image the query image
     * @param train_image the train image
     * @param camera_index the camera index
     */
    void DrawMacthedInfo(const std::vector<std::pair<FeatureTrack, vslam::Feature>>& associated_results,
                         const cv::Mat& query_image, const cv::Mat& train_image, const uint64_t camera_index) const;

    /**
     * @brief draw epipolar line between query and train images
     *
     * @param first_data query features detected on query image with observed poses
     * @param second_data train features detected on train image with observed poses
     * @param query_image the query iamge
     * @param train_image the train image
     * @param epipolar_dist_th the epipolar distance threshold
     * @param descriptor_dist_th the descriptor distance threshold
     * @param ratio_test_th the ratio thresold of best and better descriptor
     */
    void DrawEpipolarLineMatching(const DescriptorMatcher::FeaturesWithObservedPoses& first_data,
                                  const DescriptorMatcher::FeaturesWithObservedPoses& second_data,
                                  const cv::Mat& query_image, const cv::Mat& train_image, Scalar epipolar_dist_th,
                                  Scalar descriptor_dist_th, Scalar ratio_test_th) const;

    /**
     * @brief get undistorted image
     *
     * @param cv_img the image is to be undistorted
     * @return the undistorted image
     */
    holo::localization::Mat UndistortedImage(const cv::Mat& cv_img) const;

    /**
     * @brief variables
     */
    const Parameters                 parameters_;              ///< vslam parameters
    CameraParameters::Ptr            camera_parameters_;       ///< camera parameters
    deep::CameraParameters::Ptr      deep_camera_parameters_;  ///< deep camera parameters
    deep::RawMeasurementPreprocessor preprocessor_;            ///< raw measurement preprocessor

    // the optimization data of the current avp map
    BundleAdjustmentProblem current_ba_problem_;

    /// triangulator
    Triangulator triangulator_;

    /// map database manager smart pointer
    MapDatabaseManager map_database_manager_;

    AvpMapDatabase avp_map_database_;

    /// image undistorters for multi camera vslam system
    std::vector<ImageUndistortionPtr> undistorters_;

    /// pose and trajectory point cloud for visualization
    PointCloudXYZIRRgbSt pose_and_trajectory_msg_;

    // pose compensation when save ply
    Pose3 pose_compensation_;
};  // avp mapping

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_MAPPING_AVP_MAPPING_H_
