/*!
 * \brief global optimizer class header file in vslam
 * \author Feng. Li, lifeng@holomatic.com
 * \date Mar-02-2020
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_MAPPING_GLOBAL_OPTIMIZER_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_MAPPING_GLOBAL_OPTIMIZER_H_

#include <gtsam_unstable/nonlinear/BatchFixedLagSmoother.h>
#include <holo/localization/tools/pose_spline.h>
#include <holo/localization/vision/vslam/descriptor_matcher.h>
#include <holo/localization/vision/vslam/factor_graph.h>
#include <holo/localization/vision/vslam/feature_track.h>
#include <holo/localization/vision/vslam/mapping/loop_detector.h>
#include <holo/localization/vision/vslam/mapping/map_database_manager.h>
#include <holo/localization/vision/vslam/mapping/visualizer.h>
#include <holo/localization/vision/vslam/pose_only_unit3_factor.h>
#include <holo/localization/vision/vslam/semantic/parking_slot_parallel_factor.h>
#include <holo/localization/vision/vslam/semantic/parking_slot_vertex_factor.h>
#include <holo/localization/vision/vslam/triangulator.h>
#include <holo/localization/vision/vslam/velocity_factor.h>

#include <thread>

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
 * @brief global optimizer class
 *
 * @details this class is mainly responsible for re-estimates the whole trajectory and landmarks.
 */

class GlobalOptimizer
{
public:
    /// @brief handy typedefine
    typedef LoopDetector::CandidatesLoop CandidatesLoop;

    /**
     * @brief define parameters
     */
    struct Parameters
    {
        struct Sigmas
        {
            /// @brief sigmas for imu bias between fator. [acc gyro]
            const Vector6 bias_between_sigma;

            /// @brief velocity factor sigma. [vx vy vz]
            const Vector3 velocity_factor_sigma;

            /// @brief velocity factor sigma when vehicle make turns
            const Vector3 velocity_factor_sigma_when_turns;

            /// @brief wheel pulse integration sigma
            const Vector6 wheel_integration_factor_sigma;

            /// @brief between pose3 factor sigma when zero velocity detected
            const Vector6 zero_velocity_between_pose_sigma;

            /// @brief between pose3 factor sigma for loop closing constraint
            const Vector6 loop_closing_between_pose_sigma;

            /// @brief prior pose sigma. for first frame only
            const Vector6 prior_pose_sigma;

            /// @brief prior velocity sigma. for first frame only
            const Vector3 prior_velocity_sigma;

            /// @brief prior bias sigma. for first frame only
            const Vector6 prior_bias_sigma;

            /// @brief prior ground truth sigma. for all frames
            const Vector6 gt_pose_sigma;

            /// @brief sigma for parking slot vertex factor
            const Vector3 vertex_factor_sigma;

            /// @brief sigma for parking slot plane factor
            const Vector3 plane_factor_sigma;

            /// @brief sigma for parking slot point plane factor
            const Vector1 point_plane_factor_sigma;

            /// @brief sigma for parking slot parallel factor
            const Vector3 parallel_factor_sigma;

            /// @brief constructor
            Sigmas(const Vector6& _bias_between_sigma, const Vector3& _velocity_factor_sigma,
                   const Vector3& _velocity_factor_sigma_when_turns, const Vector6& _wheel_integration_factor_sigma,
                   const Vector6& _zero_velocity_between_pose_sigma, const Vector6& _loop_closing_between_pose_sigma,
                   const Vector6& _prior_pose_sigma, const Vector3& _prior_velocity_sigma,
                   const Vector6& _prior_bias_sigma, const Vector6& _gt_pose_sigma, const Vector3& _vertex_factor_sigma,
                   const Vector3& _plane_factor_sigma, const Vector1& _point_plane_factor_sigma,
                   const Vector3& _parallel_factor_sigma)
              : bias_between_sigma(_bias_between_sigma)
              , velocity_factor_sigma(_velocity_factor_sigma)
              , velocity_factor_sigma_when_turns(_velocity_factor_sigma_when_turns)
              , wheel_integration_factor_sigma(_wheel_integration_factor_sigma)
              , zero_velocity_between_pose_sigma(_zero_velocity_between_pose_sigma)
              , loop_closing_between_pose_sigma(_loop_closing_between_pose_sigma)
              , prior_pose_sigma(_prior_pose_sigma)
              , prior_velocity_sigma(_prior_velocity_sigma)
              , prior_bias_sigma(_prior_bias_sigma)
              , gt_pose_sigma(_gt_pose_sigma)
              , vertex_factor_sigma(_vertex_factor_sigma)
              , plane_factor_sigma(_plane_factor_sigma)
              , point_plane_factor_sigma(_point_plane_factor_sigma)
              , parallel_factor_sigma(_parallel_factor_sigma)
            {
            }
        };

        /// @brief define parameters for frame to frame checking
        struct FrameToFrameCheckingParameters
        {
            /// @brief the frame id interval threshold
            /// @details if the interval between train frame's id and query frame's id is less than this threshold, we
            /// think the information shared by these two frames is redundant. so we don't trying to assoiate features
            /// between them.
            const uint64_t minimum_frame_interval;

            /// @brief brute force feature matching parameters
            const Scalar descriptor_distance_th;  ///< descriptor distance threshold
            const Scalar ratio_test_th;           ///< ratio test threshold

            /// @brief the minimum matched feature need by pnp solver
            const uint16_t matches_threshold;

            /// @brief pnp solver parameters
            const uint16_t ransanc_iterations_number;   ///< number of iterations.
            const Scalar   projection_error_threshold;  ///< inlier threshold value
            const Scalar   confidence;  ///< the probability that the algorithm produces a useful result.

            /// @brief the minimum inlier number after pnp solver
            const uint16_t minimum_inliers_number;

            /// @brief constructor
            FrameToFrameCheckingParameters(const uint64_t _minimum_frame_interval = 100,
                                           const Scalar   _descriptor_distance_th = 1.2,
                                           const Scalar _ratio_test_th = 0.85, const uint16_t _matches_threshold = 10,
                                           const uint16_t _ransanc_iterations_number  = 100,
                                           const Scalar   _projection_error_threshold = 8e-3,
                                           const Scalar _confidence = 0.99, const uint16_t _minimum_inliers_number = 8)
              : minimum_frame_interval(_minimum_frame_interval)
              , descriptor_distance_th(_descriptor_distance_th)
              , ratio_test_th(_ratio_test_th)
              , matches_threshold(_matches_threshold)
              , ransanc_iterations_number(_ransanc_iterations_number)
              , projection_error_threshold(_projection_error_threshold)
              , confidence(_confidence)
              , minimum_inliers_number(_minimum_inliers_number)
            {
            }
        };

        /**
         * @brief define parameters for frame to covisibility map checking
         * @details these parameters will be used to verify the loop closing relationship between a train frame and
         * query frame by matching the covisibility map and features extracted on query frame.
         */
        struct FrameToCovisibilityMapCheckingParameters
        {
            /**
             * @brief this parameters is used to determine whether the train frame and query frame have shared enough
             * information with each other.
             * @details the ${covisibility_intensity} is the number of the shared landmarks by two frames. if the query
             * frame is a covisibility frame of train frame and their covisibility intensity has beyond this threshold,
             * we think the information shared by these two frames is redundant.
             */
            const uint16_t max_covisibility_intensity;

            /**
             * @brief this parameters is used to filter the covisibility map.
             * @details As we know, the covisibility map is constructed by all covisibility frames. only the frames
             * whose covisibility intensity is larger than this parameters will be used to construct the covisibility
             * map.
             */
            const uint16_t min_covisibility_intensity;

            /// @brief parameters used by function MappointsToFeaturesMatching()
            const Scalar window_size;         ///< searched window size
            const Scalar descriptor_dist_th;  ///< descriptor distance threshold
            const Scalar ratio_test_th;       ///< ratio test threshold
            const Scalar view_distance_th;    ///<  threshold of distance between mappoint's reference pose and query
                                              ///<  camera pose. in meter
            const Scalar view_direction_th;   ///< threshold of view direction between mappoints and features. in degree

            /// @brief the minimum matched feature need by pnp solver
            const uint16_t matches_threshold;

            /// @brief sigma for pose only unit3 factor.
            const Vector2 pose_only_unit3_factor_sigma;

            /// @brief huber loss
            const Scalar pose_only_unit3_factor_huber_loss;

            /// @brief projection error threshold to check inliers after optimization
            const Scalar projection_error_threshold;

            /// @brief the minimum inlier number after pnp solver
            const uint16_t minimum_inliers_number;

            /// @brief constructor
            FrameToCovisibilityMapCheckingParameters(
                const uint16_t _max_covisibility_intensity = 60, const uint16_t _min_covisibility_intensity = 5,
                const Scalar _window_size = 80.0, const Scalar _descriptor_dist_th = 1.0,
                const Scalar _ratio_test_th = 0.95, const Scalar _view_distance_th = 100.0,
                const Scalar _view_direction_th = 45.0, const uint16_t _matches_threshold = 60,
                const Vector2 _pose_only_unit3_factor_sigma     = Vector2(0.05, 0.05),
                const Scalar _pose_only_unit3_factor_huber_loss = 0.5, const Scalar _projection_error_threshold = 5e-3,
                const uint16_t _minimum_inliers_number = 50)
              : max_covisibility_intensity(_max_covisibility_intensity)
              , min_covisibility_intensity(_min_covisibility_intensity)
              , window_size(_window_size)
              , descriptor_dist_th(_descriptor_dist_th)
              , ratio_test_th(_ratio_test_th)
              , view_distance_th(_view_distance_th)
              , view_direction_th(_view_direction_th)
              , matches_threshold(_matches_threshold)
              , pose_only_unit3_factor_sigma(_pose_only_unit3_factor_sigma)
              , pose_only_unit3_factor_huber_loss(_pose_only_unit3_factor_huber_loss)
              , projection_error_threshold(_projection_error_threshold)
              , minimum_inliers_number(_minimum_inliers_number)
            {
            }
        };

        /// @brief loop detector parameters
        const LoopDetector::Parameters loop_detector_parames;

        /// @brief triangulation parameters
        const Triangulator::Parameters triangulator_params;

        /// @brief sigmas
        const Sigmas sigmas;

        /// @brief imu preintigration parameters
        const PreintegrationParamsPtr pim_params;

        /// @brief frame to frame checking parameters.
        const FrameToFrameCheckingParameters f2fc_params;

        /// @brief frame to covisibility map checking parameters
        const FrameToCovisibilityMapCheckingParameters f2cmc_params;

        /// @brief inliers projection error after global BA
        const Scalar projection_error_after_gba;

        /// @brief max landmark distance. used to determine outliers after global BA
        const Scalar max_landmark_distance;

        /// @brief flag indicated if enable ground truth factor
        const bool enable_gt_pose_factor;

        /// @brief flag indicated if enable gps position factor
        const bool enable_position_factor;

        /// @brief flag indicated if enale visualizer
        const bool enable_visualizer;

        /// @brief define working mode: single_map_optimization or multi_map_merging
        const std::string mode;

        /// @brief output more log information
        bool verbose;

        // minimum measurement distance interval
        const Scalar minimum_keyframe_travel_distance;

        // minimum measurement angle interval
        const Scalar minimum_keyframe_angle;

        /// @brief flag if enable loop detection
        const bool enable_loop_detection;

        const uint64_t factor_number_in_one_frame;

        const uint64_t minimum_valid_track_length;

        const uint32_t frame_num_selected_for_epipolar_matching;

        /**
         * @brief Construct a new Parameters object
         *
         */
        Parameters(
            const LoopDetector::Parameters& _loop_detector_parames,
            const Triangulator::Parameters& _triangulator_params, const Sigmas _sigmas,
            const PreintegrationParamsPtr&                  _pim_params,
            const FrameToFrameCheckingParameters&           _f2fc_params  = FrameToFrameCheckingParameters(),
            const FrameToCovisibilityMapCheckingParameters& _f2cmc_params = FrameToCovisibilityMapCheckingParameters(),
            const Scalar _projection_error_after_gba = 3.0, const Scalar _max_landmark_distance = 150.0,
            const bool _enable_gt_pose_factor = false, const bool _enable_position_factor = false,
            const bool _enable_visualizer = false, const std::string& _mode = "single_map_optimization",
            const bool _verbose = false, const Scalar _minimum_keyframe_travel_distance = 0.5,
            const Scalar _minimum_keyframe_angle = 3.0, const bool _enable_loop_detection = false,
            const uint64_t _factor_number_in_one_frame = 20, const uint64_t _minimum_valid_track_length = 3,
            const uint32_t _frame_num_selected_for_epipolar_matching = 10)
          : loop_detector_parames(_loop_detector_parames)
          , triangulator_params(_triangulator_params)
          , sigmas(_sigmas)
          , pim_params(_pim_params)
          , f2fc_params(_f2fc_params)
          , f2cmc_params(_f2cmc_params)
          , projection_error_after_gba(_projection_error_after_gba)
          , max_landmark_distance(_max_landmark_distance)
          , enable_gt_pose_factor(_enable_gt_pose_factor)
          , enable_position_factor(_enable_position_factor)
          , enable_visualizer(_enable_visualizer)
          , mode(_mode)
          , verbose(_verbose)
          , minimum_keyframe_travel_distance(_minimum_keyframe_travel_distance)
          , minimum_keyframe_angle(_minimum_keyframe_angle)
          , enable_loop_detection(_enable_loop_detection)
          , factor_number_in_one_frame(_factor_number_in_one_frame)
          , minimum_valid_track_length(_minimum_valid_track_length)
          , frame_num_selected_for_epipolar_matching(_frame_num_selected_for_epipolar_matching)
        {
        }

        /**
         * @brief output stream parameters
         *
         * @param os std::ostream&
         * @param parameters
         * @return std::ostream&
         */
        friend std::ostream& operator<<(std::ostream& os, const Parameters& params)
        {
            os << params.loop_detector_parames << "Sigmas: "
               << "\n bias_between sigma = " << params.sigmas.bias_between_sigma.Transpose()
               << "\n velocity_factor_sigma = " << params.sigmas.velocity_factor_sigma.Transpose()
               << "\n velocity_factor_sigma_when_turns = " << params.sigmas.velocity_factor_sigma_when_turns.Transpose()
               << "\n wheel_integration_factor_sigma = " << params.sigmas.wheel_integration_factor_sigma.Transpose()
               << "\n zero_velocity_between_pose_sigma = " << params.sigmas.zero_velocity_between_pose_sigma.Transpose()
               << "\n loop_closing_between_pose_sigma = " << params.sigmas.loop_closing_between_pose_sigma.Transpose()
               << "\n prior_pose_sigma = " << params.sigmas.prior_pose_sigma.Transpose()
               << "\n prior_velocity_sigma = " << params.sigmas.prior_velocity_sigma.Transpose()
               << "\n prior_bias_sigma = " << params.sigmas.prior_bias_sigma.Transpose() << "\n f2fc_params:"
               << "\n gt_pose_sigma = " << params.sigmas.gt_pose_sigma.Transpose()
               << "\n  minimum_frame_interval = " << params.f2fc_params.minimum_frame_interval
               << "\n  descriptor_distance_th = " << params.f2fc_params.descriptor_distance_th
               << "\n  ratio_test_th = " << params.f2fc_params.ratio_test_th
               << "\n  matches_threshold = " << params.f2fc_params.matches_threshold
               << "\n  ransanc_iterations_number = " << params.f2fc_params.ransanc_iterations_number
               << "\n  projection_error_threshold = " << params.f2fc_params.projection_error_threshold
               << "\n  confidence = " << params.f2fc_params.confidence
               << "\n  minimum_inliers_number = " << params.f2fc_params.minimum_inliers_number << "\n f2cmc_params:"
               << "\n  max_covisibility_intensity = " << params.f2cmc_params.max_covisibility_intensity
               << "\n  min_covisibility_intensity = " << params.f2cmc_params.min_covisibility_intensity
               << "\n  window_size = " << params.f2cmc_params.window_size
               << "\n  descriptor_dist_th = " << params.f2cmc_params.descriptor_dist_th
               << "\n  ratio_test_th = " << params.f2cmc_params.ratio_test_th
               << "\n  view_distance_th = " << params.f2cmc_params.view_distance_th
               << "\n  view_direction_th = " << params.f2cmc_params.view_direction_th
               << "\n  matches_threshold = " << params.f2cmc_params.matches_threshold
               << "\n  pose_only_unit3_factor_sigma = " << params.f2cmc_params.pose_only_unit3_factor_sigma.Transpose()
               << "\n  pose_only_unit3_factor_huber_loss = " << params.f2cmc_params.pose_only_unit3_factor_huber_loss
               << "\n  projection_error_threshold = " << params.f2cmc_params.projection_error_threshold
               << "\n  minimum_inliers_number = " << params.f2cmc_params.minimum_inliers_number
               << "\n triangulator_params: " << params.triangulator_params
               << "\n projection_error_after_gba = " << params.projection_error_after_gba
               << "\n max_landmark_distance = " << params.max_landmark_distance
               << "\n enable_gt_pose_factor = " << params.enable_gt_pose_factor
               << "\n enable_position_factor = " << params.enable_position_factor
               << "\n enable_visualizer = " << params.enable_visualizer << "\n mode = " << params.mode
               << "\n verbose = " << params.verbose
               << "\n minimum_keyframe_travel_distance = " << params.minimum_keyframe_travel_distance
               << "\n minimum_keyframe_angle = " << params.minimum_keyframe_angle
               << "\n enable_loop_detection = " << params.enable_loop_detection
               << "\n factor_number_in_one_frame = " << params.factor_number_in_one_frame
               << "\n minimum_valid_track_length = " << params.minimum_valid_track_length
               << "\n frame_num_selected_for_epipolar_matching = " << params.frame_num_selected_for_epipolar_matching
               << "\n";

            // @note gtsam only provides print() function
            params.pim_params->print("pim parameters");
            return os;
        }

        /**
         * @brief load from yaml
         *
         * @param node
         * @return Parameters
         */
        static Parameters LoadFromYaml(const holo::yaml::Node& node);

        /**
         * @brief static example parameters for unit test
         *
         * @return Parameters
         */
        static Parameters Example();
    };

    /**
     * @brief constructor
     */
    GlobalOptimizer(const Parameters& parameters);

    /**
     * @brief destructor
     */
    ~GlobalOptimizer()
    {
    }

    /**
     * @brief struct of PnpResult
     */
    struct PnpResult
    {
        /// @brief optional camera pose in world frame. if solve pnp faild, this varibale will be evaluated to false
        boost::optional<Pose3> pose;

        /// @brief inliers
        std::vector<uint16_t> inliers;

        /**
         * @brief Construct a new Pnp Result object
         *
         * @param _pose
         * @param _inliers
         */
        PnpResult(const boost::optional<Pose3>& _pose, const std::vector<uint16_t>& _inliers)
          : pose(_pose), inliers(_inliers)
        {
        }
    };

    /**
     * @brief define struct of loop detection result
     */
    typedef std::pair<uint64_t, uint64_t>              LandmarkIdPair;
    typedef std::vector<LandmarkIdPair>                LandmarkIdPairs;
    typedef std::pair<uint64_t, uint16_t>              LandmarkIdAndFeatureIndexPair;
    typedef std::vector<LandmarkIdAndFeatureIndexPair> LandmarkIdAndFeatureIndexPairs;
    struct LoopClosingResult
    {
        /// @brief train frame.<frame id, camera index>
        std::pair<uint64_t, uint16_t> train_frame;

        /// @brief query frame.<frame id, camera index>
        std::pair<uint64_t, uint16_t> query_frame;

        /// @brief pose of query frame in world frame.
        Pose3 T_wq;

        /// @brief associated landmark id pairs. <train lm id, query lm id>
        LandmarkIdPairs associated_landmarks;

        /// @brief associated landmark to query feature index.<train lm id, query feature index>
        LandmarkIdAndFeatureIndexPairs train_lm_id_to_query_feature_index;

        /// @brief constructor
        LoopClosingResult(const std::pair<uint64_t, uint16_t>& _train_frame,
                          const std::pair<uint64_t, uint16_t>& _query_frame, const Pose3& _T_wq,
                          const LandmarkIdPairs&                _associated_landmarks,
                          const LandmarkIdAndFeatureIndexPairs& _train_lm_id_to_query_feature_index)
          : train_frame(_train_frame)
          , query_frame(_query_frame)
          , T_wq(_T_wq)
          , associated_landmarks(_associated_landmarks)
          , train_lm_id_to_query_feature_index(_train_lm_id_to_query_feature_index)
        {
        }
    };
    typedef std::vector<LoopClosingResult> LoopClosingResults;

    /// @brief define optimize result
    struct OptimizedResults
    {
        /// @brief optimized frame database
        const FramesDatabase frames_database;

        /// @brief optimized tracks
        const TracksDatabase tracks_database;

        /// @brief optimized values
        const Values optimized_values;

        /// @brief loop closing results
        const LoopClosingResults loop_closing_results;

        /// @brief construct
        OptimizedResults(const FramesDatabase& _frames_database, const TracksDatabase& _tracks_database,
                         const Values& _optimized_values, const LoopClosingResults& _loop_closing_results)
          : frames_database(_frames_database)
          , tracks_database(_tracks_database)
          , optimized_values(_optimized_values)
          , loop_closing_results(_loop_closing_results)
        {
        }
    };  // struct OptimizeResult

    /**
     * @brief main computing function
     * @details it will choose SingleMapOptimization or MultiMapMerging adaptively according the mode defined in
     * parameters
     */
    void Run(const MapDatabaseManager& map_database_manager);

    /**
     * @brief visualize all optimized landmarks and trajectory and loop edge by pcl.
     */
    void VisualizeOptimizedResults(const OptimizedResults& optimize_result, mapping::Visualizer& visualizer) const;

    /**
     * @brief get offline mapping progress
     */
    holo::uint8_t GetMappingProgress() const;

    /**
     * @brief get quality of maping result
     */
    holo::uint8_t GetMappingResultQuality() const;

private:
    /**
     * @brief main computing function for single map optimization only
     */
    OptimizedResults SingleMapOptimization(const MappingDatabase& mapping_database);

    /**
     * @brief optimize parking slot map
     */
    Values ParkingSlotOptimization(const Values& new_values, const MappingDatabase& mapping_database);

    /**
     * @brief main computing function for multi map merging only
     */
    void MultiMapMerging(const MapDatabaseManager& map_database_manager) const;

    /**
     * @brief create frames database from track database.
     */
    FramesDatabase CreateFramesDatabaseFromTracks(const Values& values, const TracksDatabase& track_database) const;

    /**
     * @brief create frames database from mapping database.
     * @details frames will be used to create a visual database for loop detetion
     */
    FramesDatabase CreateFramesDatabase(const MappingDatabase& mapping_database) const;

    /**
     * @brief constrain value within [min, max]
     */
    int32_t BoundaryClamp(const int32_t value, const int32_t min, const int32_t max) const;

    /**
     * @brief add untracked features to each frame
     * @details online mapping progress will save all features extracted on each image. but some features can not
     * associated to any landmarks for many reasons. these features will be add to the corresponding frame inside this
     * function for futher covisibility map association.
     *
     * @param frames all frames
     * @param frame_indexed_features all features
     */
    FramesDatabase AddUntrackedFeaturesToEachFrame(const std::vector<Frame>&   frames,
                                                   const FrameIndexedFeatures& frame_indexed_features) const;

    /**
     * @brief matching a local map for each frame to search more feature association
     * @details each frame in frames_database will match with its covisibility map.
     *          1. for feature which do not observed by any tracks before, if it was matched with a track after
     *             covisibility map matching, we will add this feature to the matched track's measurement.
     *          2. for feature which was already associated to an old track. we return these landmark id pairs to merge
     *             the same landmakrs later.
     * @param frames_database the frames database
     * @param tracks_database the tracks database
     * @return a std::tuple: 0. new frames database.
     *                       1. new tracks database.
     *                       2. associated landmark id pairs.
     */
    std::tuple<FramesDatabase, TracksDatabase, LandmarkIdPairs> LocalMapMatchingAndTracksExtending(
        const FramesDatabase& frames_database, const TracksDatabase& tracks_database) const;

    /**
     * @brief matching a local map for each frame to search more feature association
     * @details 1. call LocalMapMatchingAndTracksExtending(). for more details please see the doxygen of this function.
     *          2. merge the assoicated landmarks pairs. which is returned by step1.
     *          3. update frame database by repalce the associated landmark ids.
     */
    std::pair<FramesDatabase, TracksDatabase> LocalMapAssociation(const FramesDatabase& frames_database,
                                                                  const TracksDatabase& tracks_database) const;

    /**
     * @brief triangulate candidate tracks
     *
     * @param tracks_database database contain all tracks
     * @param values values with optimized vheicle state
     * @param only_candiate_tracks flag if only triangulate candiate tracks
     *
     * @return new track database inwhich all track has beewn well triangulated
     */
    TracksDatabase TriangulateTracks(const TracksDatabase& tracks_database, const Values& values,
                                     holo::bool_t only_candiate_tracks = true) const;

    /**
     * @brief slove pnp
     * @param point3d map points in world frame
     * @param point2d points on normalized plane.(z == 1)
     * @param K camera intrinsic matrix.
     * @return PnpResult
     */
    PnpResult SolvePNP(const std::vector<cv::Point3d>& point3d, const std::vector<cv::Point2d>& point2d,
                       const cv::Mat& K) const;

    /**
     * @brief geomitric consistency checking for each candidate looped frame.
     * @details 1. frame to frame feature matching with BruteForceMatching method.
     *          2. solve pnp by EPNP method.
     *
     * @param frames_database frame database
     * @param tracks_database tracks database
     * @param candidates candidate looped frame, it include the query frame and all candidate train frame
     * @return optional loop closing result
     */
    boost::optional<LoopClosingResult> FrameToFrameChecking(const FramesDatabase& frames_database,
                                                            const TracksDatabase& tracks_database,
                                                            const CandidatesLoop& candidates) const;

    /**
     * @brief query all covisibility frames from the frame database
     * @details if a frame share one or more than one landmark with query_frame, it will be treat as a covisibility
     * frame of query_frame.
     * @note this function also return the covisibility intensity of each covisibility frame. the covisibility intensity
     * is the number of the shared landmarks by these two frames.
     *
     * @param frames_database frame database
     * @param tracks_database tracks database
     * @param query_frame_id query frame id
     * @param query_camera_index query camera index
     * @return all covisibility frames with their covisibility intensity. <frame id, covisibility intensity>
     */
    std::unordered_map<uint64_t, uint16_t> QueryCovisibilityFrames(const FramesDatabase& frames_database,
                                                                   const TracksDatabase& tracks_database,
                                                                   const uint64_t        query_frame_id,
                                                                   const uint16_t        query_camera_index) const;

    /**
     * @brief construct a covisibility map from covisibility frames
     * @details put all landmarks associated to covisibility_frames together as a covisibility map.
     *
     * @param frames_database the frame database
     * @param tracks_database the tracks database
     * @param covisibility_frames the covisibility frames
     * @param query_camera_index the query camera index
     * @param min_covisibility_intensity the minimum required covisibility intensity.
     *
     * @return a covisibility map. <landmark id, MapPoint>
     */
    std::unordered_map<uint64_t, MapPoint>
    QueryCovisibilityMap(const FramesDatabase& frames_database, const TracksDatabase& tracks_database,
                         const std::unordered_map<uint64_t, uint16_t>& covisibility_frames,
                         const uint16_t query_camera_index, const uint16_t min_covisibility_intensity) const;

    /**
     * @brief geomitric consistency checking by the train frame's covisibility map.
     *
     * @details 1. query the covisibility map of the candiate train frame.
     *          2. matching the covisibility map and features extracted on query frame by MappointsToFeaturesMatching.
     *          3. solve pnp by gtsam, (pose only optimization).
     *
     * @note this function should be called after FrameToFrameChecking()
     *
     * @param frames_database the frame database
     * @param tracks_database the tracks database
     * @param candidate_result the best loop candidate after FrameToFrameChecking
     *
     * @return an optional loop cloding result
     */
    boost::optional<LoopClosingResult> FrameToCovisibilityMapChecking(const FramesDatabase&    frames_database,
                                                                      const TracksDatabase&    tracks_database,
                                                                      const LoopClosingResult& candidate_result) const;

    /**
     * @brief loop detection and checking
     *
     * @param loop_detector loop detector
     * @param frames_database the frames database
     * @param tracks_database the feature tracks database
     * @return LoopClosingResults
     */
    LoopClosingResults LoopDetectionAndGeometricChecking(const LoopDetector&   loop_detector,
                                                         const FramesDatabase& frames_database,
                                                         const TracksDatabase& tracks_database) const;

    /**
     * @brief put landmark ids which belong to a same landmark into a single set
     * @details if the &{associated_lamdmarks} is like this:
     *          1 - 3
     *          3 - 4
     *          5 - 8
     *          7 - 8
     *          4 - 7
     * obviously these id should belongs to one set. this function is mainly responsible for find such a set and return.
     *
     * @param associated_lamdmarks all landmark id pairs to be processed.
     */
    std::vector<std::set<uint64_t>> ClusteringAssociatedLandmarkIds(const LandmarkIdPairs& associated_lamdmarks) const;

    /**
     * @brief merge feature tracks
     * @details if track_i(comes from train frame) and track_j(comes from query frame) had passed the geometric
     * consistency checking after LoopDetectionAndGeometricChecking, we will add all track_j's measurement to track_i
     * and meanwhile remove track_j.
     *
     * @param frames_database the frames database
     * @param tracks_database the track database
     * @param loop_results loop closing result whcih contain the associated feature tracks.
     *
     * @return new tracks database after merging
     */
    TracksDatabase FeatureTracksMerging(const FramesDatabase& frames_database, const TracksDatabase& tracks_database,
                                        const LoopClosingResults& loop_results) const;

    /**
     * @brief build factor graph from mapping database
     * @details the return factor graph does not contain visual factor. all tracks contain in the input mapping_database
     * will be further processed by loop detection module. and will be merged with each other if the loop closing
     * relationship established. visual factor and loop closing constraint will be built and add to this factor graph
     * later. see function FeatureTracksMerging() and AddVisualFactorsAndLoopConstraintsToGraph() for more details.
     *
     * @param mapping_database mapping_database to be processed
     *
     * @return a factor graph which contains ImuFactor, ImuBiasFactor, VelocityFactor, Unit3Factor, GpsFactor(optional)
     * and Pose3BetweenFactor(optional, only build this factor when zero velocity detected)
     */
    void BuildSequentialFactorGraphFromMappingDatabase(const MappingDatabase& mapping_database,
                                                       FactorGraph&           factor_graph) const;

    /**
     * @brief added prior factor graph for first frame from mapping database
     * @details prior pose factor, prior velocity factor and prior bias factor will be built and added to this factor
     * graph.
     *
     * @param mapping_database mapping_database to be processed
     * @param old_graph old factor graph to be processed
     *
     * @return a factor graph which contains ImuFactor, ImuBiasFactor, VelocityFactor, Unit3Factor, GpsFactor(optional),
     * Pose3BetweenFactor(optional, only build this factor when zero velocity detected) and prior factors
     */
    void AddPriorFactor(const MappingDatabase& mapping_database, FactorGraph& factor_graph) const;

    /**
     * @brief add loop constraints and visual factor to factor graph and optimize the graph
     * @details this function will build Pose3BetweenFactor by loop_results, and Unit3Factor by each feature track.
     *
     * @param old_graph old factor graph to be processed
     * @param old_values values of the variable in old graph
     * @param frames_database the frame database
     * @param tracks_database the feature tracks database
     * @param loop_results loop closing result
     *
     * @return a new factor graph witch contain ImuFactor, ImuBiasFactor, VelocityFactor, GpsFactor(optional),
     * Pose3BetweenFactor, and visual factor
     */
    std::set<holo::uint64_t> AddVisualFactorAndLoopConstraintsToGraph(FactorGraph&              factor_graph,
                                                                      const Values&             old_values,
                                                                      const FramesDatabase&     frames_database,
                                                                      const TracksDatabase&     tracks_database,
                                                                      const LoopClosingResults& loop_results) const;
    /**
     * @brief add parking based semantic factors
     * @details parking slot parallel factor, point only slot vertex factor will be built
     *
     * @param pose_spline the pose spline
     * @param parking_slot_track_database the parking slot tracks database
     *
     * @return a pair of factor graph and values which contains parking slot parallel factor, point only slot vertex
     * factor will be built
     */
    std::pair<FactorGraph, Values> AddSemanticFactor(const PoseSpline&                pose_spline,
                                                     const ParkingSlotTracksDatabase& parking_slot_track_database);

    /**
     * @brief add landmarks' position to values
     *
     * @param landmark_ids landmar id to be add to values
     * @param old_values old value to be processed
     * @param tracks_database feature tracks database
     *
     * @return new values contain all landmarks' position
     */
    Values AddLandmarksToValues(const std::set<holo::uint64_t>& landmark_ids, const Values& old_values,
                                const TracksDatabase& tracks_database) const;
    /**
     * @brief update landmarks' position in values
     *
     * @param old_values old value to be processed
     * @param tracks_database feature tracks database
     *
     * @return new values contain all landmarks' position
     */
    Values UpdateLandmarksValues(const Values& old_values, const TracksDatabase& tracks_database) const;

    /**
     * @brief add landmarks' position to values
     *
     * @param old_values old value to be processed
     * @param tracks_database feature tracks database
     *
     * @return new values contain all landmarks' position
     */
    Values AddLandmarksToValues(const Values& old_values, const TracksDatabase& tracks_database) const;

    /**
     * @brief using new values construct pose spline
     *
     * @param new_values old value to be processed
     *
     * @return new pose spline
     */
    PoseSpline ConstructPoseSpline(const MappingDatabase& mapping_database, const Values& new_values) const;

    /**
     * @brief global bundle adjustment by gtsam
     *
     * @param factor_graph the whole factor graph contain everything to be processed
     * @param values the initial value of this BA problem
     *
     * @return new values
     */
    Values GlobalBundleAdjustment(const FactorGraph& factor_graph, const Values& values) const;

    /**
     * @brief find best transform between two maps
     * @param frames_database frame database
     * @param transforms_query_map_frames_to_train_map_frames all transforms which are calculated from loop results
     * @return the best transform between two maps with different map id
     */
    QueryMapToTrainMapTransformPairs FindTheBestTransformBetweenTwoMaps(const FramesDatabase&     frames_database,
                                                                        const LoopClosingResults& loop_results) const;

    /**
     * @brief find out all loop relationship of each map
     * @param transform_between_two_maps the best transform between two maps
     * @return record maps' id which have loop relationship with each map
     */
    std::unordered_map<uint64_t, std::set<uint64_t>>
    FindLoopCandidatesForEachMap(const QueryMapToTrainMapTransformPairs& transform_between_two_maps) const;

    /**
     * @brief find transform from the current map to the target map0 (now we choose the map with id=0 as the world
     * coordinate, we will design a method to find the best world coordinate when merge multi maps later)
     * @param map_id the current map id
     * @param loop_map_ids_of_each_map all loop maps' id of current map
     * @param map_ids the transform routes from the current map to the target map0
     * @return ture if have transform routes from the current map to map_0
     */
    bool TransformCurrentMapToMap0(uint64_t                                                map_id,
                                   const std::unordered_map<uint64_t, std::set<uint64_t>>& loop_map_ids_of_each_map,
                                   std::vector<uint64_t>&                                  map_ids) const;

    /**
     * @brief transform all landmarks' position to target map coordinate
     * @param tracks_database old tracks database
     * @param transforms the best pose transforms between loop maps
     * @param loop_map_ids_of_each_map all loop map ids of each map
     * @return the new tracks database
     */
    TracksDatabase TransformAllLandmarksToTargetCoordinate(
        const TracksDatabase& tracks_database, const QueryMapToTrainMapTransformPairs& transforms,
        const std::unordered_map<uint64_t, std::set<uint64_t>>& loop_map_ids_of_each_map) const;

    /**
     * @brief transform all frames' pose to target map coordinate
     * @param values old values
     * @param frames_database old frames database
     * @param transforms the best pose transform between loop maps
     * @param loop_map_ids_of_each_map all loop map ids of each map
     * @return the new values and the new frames database
     */
    std::pair<Values, FramesDatabase> TransformAllFramePoseToTargetCoordinate(
        const Values& values, FramesDatabase& frames_database, const QueryMapToTrainMapTransformPairs& transforms,
        const std::unordered_map<uint64_t, std::set<uint64_t>>& loop_map_ids_of_each_map) const;

    /**
     * @brief update all tracks state to Finshed
     * @param tracks_database the old tracks database
     * @param new_values the xvb values
     * @return the new tracks database
     */
    TracksDatabase UpdateTrackState(const TracksDatabase& tracks_database, const Values& new_values) const;

    /**
     * @brief Draw multi mapping merge loop
     * @param loop_results all loop results among all maps
     * @param tracks_database merged tracks database
     * @param unmerged_tracks_database unmerged tracks database
     * @param frames_database merged frames database
     * @param unmerged_frames_database unmerged frames database
     * @param maps_number the number of maps which need to be merged
     */
    void DrawMappingMergeLoop(const LoopClosingResults& loop_results, const TracksDatabase& tracks_database,
                              const TracksDatabase& unmerged_tracks_database, const FramesDatabase& frames_database,
                              const FramesDatabase& unmerged_frames_database, const uint64_t& maps_number) const;

    /**
     * @brief hash mapping database for merge
     * @details hash frame id, landmark id, timestamp of each local map data, and combine all hashed local map data
     *  into global map database
     * @param old_mapping_database the raw mapping database
     * @param multi_mapping_database the global map database in which the frame id, landmark id, timestamp are hashed
     * @return the hashed local mapping database
     */
    MappingDatabase HashMappingDatabaseForMerge(const MappingDatabase& old_mapping_databases,
                                                MappingDatabase&       multi_mapping_database) const;

    /**
     * @brief check if the feature track satisfies the projection constraint
     * @param frames_database the frame database
     * @param track feature track
     * @param values values for check
     * @return true if satisfies the projection constrain
     */
    bool CheckReprojectionError(const FramesDatabase& frames_database, const FeatureTrack& track,
                                const Values& values) const;

    /**
     * @brief check if the feature track satisfies the projection constraint
     * @param frames_database the frame database
     * @param track feature track
     * @param values values for check
     * @return true if satisfies the projection constrain
     */
    bool CheckPiexlReprojectionError(const FeatureTrack& track, const Values& values,
                                     const FramesDatabase& frames_database = FramesDatabase()) const;

    /**
     * @brief remove bad landmarks from value
     * @details if a feature track can not satisfies the re-projection constraint, remove its key from value.
     *
     * @param values values for check
     * @param track_database feature tracks for check
     * @param frames_database the frame database
     * @return new value without any bad landmarks
     */
    Values RemoveOutlierLandmarksFromValue(const Values& values, const TracksDatabase& track_database,
                                           const FramesDatabase& frames_database = FramesDatabase()) const;

    /**
     * @brief do epipolar matching after global BA is done to find more landmark in fisrt frame
     *
     * @param old_frame_database
     * @param new_frame_database
     * @param optimized_values
     * @return new tracksDatabase with renewed landmarks in fisrt frame
     */
    TracksDatabase FindMoreMappointsInFrame(const FramesDatabase& old_frame_database,
                                            const FramesDatabase& new_frame_database, const Values& optimized_values,
                                            const TracksDatabase& track_database) const;

    /// @brief parameteres
    const Parameters parameters_;

    /// @brief mapping progress
    std::atomic<holo::uint8_t> offline_mapping_progress_;

    /// @brief map result quality
    std::atomic<holo::uint8_t> map_quality_;

};  // class GlobalOptimizer

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_MAPPING_GLOBAL_OPTIMIZER_H_
