/*!
 * \brief sub mapping class header file in vslam
 * \author Peikai. Guo guopeikai@holomatic.com
 * \date Jan-11-2021
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_MAPPING_SUB_MAPPING_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_MAPPING_SUB_MAPPING_H_

#include <boost/circular_buffer.hpp>
#include <thread>

#include <gtsam/geometry/triangulation.h>
#include <gtsam_unstable/nonlinear/BatchFixedLagSmoother.h>

#include <holo/localization/common/localization_base.h>
#include <holo/localization/vision/vslam/graph_builder.h>
#include <holo/localization/vision/vslam/mapping/common_types.h>
#include <holo/localization/vision/vslam/mapping/map_database_manager.h>
#include <holo/localization/vision/vslam/triangulator.h>

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
 * @brief sub mapping class
 *
 * @details build new sub map in this class
 */

class SubMapping : public LocalizationBase
{
public:
    /**
     * @brief handy typedefs
     */
    using Base     = LocalizationBase;
    using Ptr      = std::shared_ptr<SubMapping>;
    using ConstPtr = std::shared_ptr<const SubMapping>;

    /**
     * @brief typedef feature with its own index in the whole track vector
     *
     * @details track_id + Feature
     */
    using IndexedFeatures = std::unordered_map<uint16_t, Feature>;

    /**
     * @brief define measurement status
     */
    enum class MeasurementStatus : uint16_t
    {
        START_FRAME = 0,
        OTHER_FRAME = 1,
        END_FRAME   = 2,
    };

    /**
     * @brief define optimization data
     */
    struct BundleAdjustmentProblem
    {
        std::vector<FeatureTrack> tracks;
        Values                    xvb_values;
        FactorGraph               pose_graph;

        /// @brief default constructor
        BundleAdjustmentProblem()
        {
        }
    };

    /**
     * @brief define sub mapping parameters
     */
    struct Parameters
    {
        /// @brief frequency is defined in Base class
        Scalar frequency;

        /// @brief epipolar line matching max tracking lost frame
        uint16_t elm_max_tracking_lost_frame;

        /// @brief epipolar line matching epipolar dist threshold
        Scalar elm_epipolar_dist_th;

        /// @brief epipolar line matching descriptor dist threshold
        Scalar elm_descriptor_dist_th;

        /// @brief epipolar line matching ratio test threshold
        Scalar elm_ratio_test_th;

        Triangulator::Parameters triangulator_params;

        /// @brief feature track's parameters
        FeatureTrack::Parameters::ConstPtr track_params;

        /// @brief visualizer flag
        bool enable_visualizer;

        /// @brief constructor
        Parameters(const Scalar _frequency, const uint16_t _elm_max_tracking_lost_frame,
                   const Scalar _elm_epipolar_dist_th, const Scalar _elm_descriptor_dist_th,
                   const Scalar _elm_ratio_test_th, const Triangulator::Parameters& _triangulator_params,
                   const bool& _enable_visualizer = false)
          : frequency(_frequency)
          , elm_max_tracking_lost_frame(_elm_max_tracking_lost_frame)
          , elm_epipolar_dist_th(_elm_epipolar_dist_th)
          , elm_descriptor_dist_th(_elm_descriptor_dist_th)
          , elm_ratio_test_th(_elm_ratio_test_th)
          , triangulator_params(_triangulator_params)
          , track_params(new FeatureTrack::Parameters(false, false))
          , enable_visualizer(_enable_visualizer)

        {
        }

        // output stream
        friend std::ostream& operator<<(std::ostream& os, const Parameters& parameters)
        {
            os << "SubMappingParameters:\n"
               << "\n elm_max_tracking_lost_frame = " << parameters.elm_max_tracking_lost_frame
               << "\n elm_epipolar_dist_th = " << parameters.elm_epipolar_dist_th
               << "\n elm_descriptor_dist_th = " << parameters.elm_descriptor_dist_th
               << "\n elm_ratio_test_th = " << parameters.elm_ratio_test_th << "\nfrequency = " << parameters.frequency
               << "\n triangulator: " << parameters.triangulator_params << "\n";
            return os;
        }

        // @brief load parameters from yaml
        static Parameters LoadFromYaml(const holo::yaml::Node& node);

        // @brief an example parameters
        static Parameters Example();
    };  // Parameters

    /**
     * @brief define the input data for sub mapping
     * @details  it contains the frame id, sub map id, images, associated features, the factor measurement, detection
     * result (added later).
     */
    struct Measurement
    {
        /// @brief associated frame id of these data.
        uint64_t frame_id;

        /// @brief associated sub map id of these data.
        uint64_t sub_map_id;

        /// @brief the measurement status
        MeasurementStatus status;

        /// @brief images sampled by multi camera system.
        /// @details all images are grayscale and already been well undistorted.
        std::vector<Image> images;

        /// @brief tracks in sliding window
        std::vector<FeatureTrack> tracks;

        /// @brief factor measurements
        FactorMeasurements factor_measurements;

        /// @brief default constructor
        Measurement()
        {
        }

        /// @brief constructor
        Measurement(const uint64_t _frame_id, const uint64_t _sub_map_id, const MeasurementStatus& _status,
                    const std::vector<Image>& _images, const std::vector<FeatureTrack>& _tracks,
                    const FactorMeasurements& _factor_measurements)
          : frame_id(_frame_id)
          , sub_map_id(_sub_map_id)
          , status(_status)
          , images(_images)
          , tracks(_tracks)
          , factor_measurements(_factor_measurements)
        {
        }
    };
    using MeasurementCircularBuffer = boost::circular_buffer<Measurement>;

    /**
     * @brief constructor
     */
    SubMapping(const Parameters& parameters, const CameraParameters::Ptr& camera_parameters);

    /**
     * @brief destructor
     */
    virtual ~SubMapping();

    /**
     * @brief get parameters
     */
    virtual const Parameters& Params() const
    {
        return parameters_;
    }

    /**
     * @brief stop sub mapping thread
     */
    virtual void Stop() override;

    /**
     * @brief after get optimized results, we will clear them
     */
    SubMappingResults GetOptimizedResultsAndClearOldResults();

    /**
     * @brief add sub mapping data
     *
     * @param new_measurement the new measurement
     */
    void AddNewMeasurement(const Measurement& new_measurement);

    /**
     * @brief set graph builder pointer to this module.
     * @param graph_builder the smart pointer to a graph builder module
     */
    void SetGraphBuilderPtr(GraphBuilder::Ptr graph_builder)
    {
        graph_builder_ = graph_builder;
    }

    /**
     * @brief set map database manager pointer to this module.
     * @param map_database_manager the smart pointer to a map database manager module
     */
    void SetMapDatabaseManagerPtr(MapDatabaseManager::Ptr map_database_manager)
    {
        map_database_manager_ = map_database_manager;
    }

protected:
    /**
     * @brief check pre condition
     */
    virtual bool checkPreCondition() override
    {
        std::unique_lock<std::mutex> lock(sub_mapping_mutex_);
        return (!measurement_queue_.empty() || !sub_map_id_to_ba_problem_.empty());
    }

    /**
     * @brief estimator core function
     *
     * @details all the algorithms will be called in this function
     */
    virtual void run() override;

    /**
     * @brief get features in roi (now is static) area
     *
     * @param tracks feature tracks are prepared to extract interested features
     * @param frame_id the frame id
     *
     * @return Camera Indexed Features
     */
    CameraIndexedFeatures GetInterestedFeatures(const std::vector<FeatureTrack>& tracks,
                                                const MapProjectionMeasurements& mpms, const uint64_t frame_id) const;

    /**
     * @brief update old values with new values
     *
     * @param old_values the old values
     * @param new_values the new values from the newest measurement
     * @param new_frame_id the newest frame id
     *
     * @return upadted values
     */
    Values AddNewXVBValues(const Values& old_values, const Values& new_values, const uint64_t new_frame_id) const;

    /**
     * @brief it will be called to initialize sub mapping matching window
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
                                              const uint64_t old_frame_id, const Features& new_features,
                                              const uint64_t new_frame_id, const uint16_t camera_index,
                                              const Pose3& prior_Twc) const;

    /**
     * @brief retrieve all features extracted at given frame from all feature tracks
     *
     * @param tracks feature tracks
     * @param frame_id frame id
     * @return camera id and the corresponding feaures.
     */
    CameraIndexedFeatures ExtractFeaturesFromTracks(const std::vector<FeatureTrack>& tracks,
                                                    const uint64_t                   frame_id) const;

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
                                     const std::vector<uint16_t>& old_tracks_index, const Features& new_features,
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
    Values AddLandmarksToValues(const Values& old_values, const std::vector<FeatureTrack>& feature_tracks) const;

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
     * @return optimized values
     */
    FramesDatabase CreateFramesDatabase(const std::vector<FeatureTrack>& feature_tracks,
                                        const Values&                    xvb_values) const;

    /**
     * @brief optimization thread
     *
     * @param[in] optimization_data the data (tracks, values, factor graph) to be optimized
     */
    void Optimization(const BundleAdjustmentProblem& optimization_data);

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
     * @brief variables
     */
    const Parameters      parameters_;         ///< vslam parameters
    CameraParameters::Ptr camera_parameters_;  ///< camera parameters

    /// last processed frame id
    uint64_t last_processed_frame_id_;

    /// the flag indicates the state of gba. (true: is running)
    bool is_running_gba_;

    ///  mutex and thread
    std::mutex                   sub_mapping_mutex_;
    std::mutex                   optimization_mutex_;
    std::mutex                   matching_results_mutex_;
    std::shared_ptr<std::thread> sub_mapping_thread_;
    std::shared_ptr<std::thread> optimization_thread_;

    // accumulated sub mapping measurements in sliding window.
    // key: frame id, value: sub mapping measurement
    MeasurementCircularBuffer measurement_queue_;

    ///  current processed measurement
    Measurement current_measurement_;

    // the optimization data of the current sub map
    BundleAdjustmentProblem current_ba_problem_;

    /// sub map id to tracks
    std::unordered_map<uint64_t, BundleAdjustmentProblem> sub_map_id_to_ba_problem_;

    /// sub mapping results
    SubMappingResults sub_mapping_results_;

    /// triangulator
    Triangulator triangulator_;

    ///  graph builder smart pointer
    GraphBuilder::Ptr graph_builder_;

    /// map database manager smart pointer
    MapDatabaseManager::Ptr map_database_manager_;

    /// num of sub maps to be optimized
    uint64_t num_of_sub_maps_to_be_optimized_;

};  // sub mapping

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_MAPPING_SUB_MAPPING_H_
