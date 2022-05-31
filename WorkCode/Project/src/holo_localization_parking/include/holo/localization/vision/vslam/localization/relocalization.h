/*!
 * \brief visual slam relocalization class header file
 * \author Feng.Li lifeng@holomatic.com
 * \date Aug-26-2020
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_LOCALIZATION_RELOCALIZATION_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_LOCALIZATION_RELOCALIZATION_H_

#include <boost/circular_buffer.hpp>
#include <thread>

#include <gtsam_unstable/nonlinear/BatchFixedLagSmoother.h>
#include <opencv2/core/eigen.hpp>

#include <holo/localization/vision/3rdparty/Vocabulary.h>
#include <holo/localization/common/localization_base.h>
#include <holo/localization/vision/vslam/mapping/common_types.h>
#include <holo/localization/vision/vslam/descriptor_matcher.h>
#include <holo/localization/vision/vslam/factor_graph.h>
#include <holo/localization/vision/vslam/pose_only_unit3_factor.h>

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
 * @brief relocalization class
 *
 * @details this class implements visual based relocalization in vslam system
 */
class Relocalization : public LocalizationBase
{
public:
    /**
     * @brief define smart pointer
     */
    typedef LocalizationBase                      Base;
    typedef std::shared_ptr<Relocalization>       Ptr;
    typedef std::shared_ptr<const Relocalization> ConstPtr;
    typedef DescriptorMatcher::MatchPairs         MatchedPairs;

    /**
     * @brief method type to find candidate keyframes
     */
    enum class QueryType : uint16_t
    {
        PRIOR_POSE    = 0u,    ///< query candidate keyframes by prior pose
        BOW           = 1u,    ///< query candidate keyframes by BOW (bag-of-words)
        VLAD          = 2u,    ///< query candidate keyframes by VLAD (vector of locally aggregated descriptors)
        NETVLAD       = 3u,    ///< query candidate keyframes by NetVLAD (deep learning model)
        UNKNOWN       = 255u,   ///< unknown query type.

    };  // enum ValueType

    /**
     * @brief measurements for relocalization in prebuilt map
     */
    struct Measurement
    {
        /// @brief query frame id
        uint64_t query_frame_id;

        /// @brief features extracted on given image
        std::vector<Features> multi_camera_features;

        /// @brief gray image
        std::vector<cv::Mat> multi_camera_grayscale;

        /// @brief prior vehicle pose in world frame
        Pose3 prior_Twb;

        /// @brief constructor
        Measurement(const uint64_t _query_frame_id = 0, const std::vector<Features>& _features = {},
                    const std::vector<cv::Mat>& _grayscale = {}, const Pose3& _prior_Twb = Pose3())
          : query_frame_id(_query_frame_id)
          , multi_camera_features(_features)
          , multi_camera_grayscale(_grayscale)
          , prior_Twb(_prior_Twb)
        {
        }
    };
    typedef boost::circular_buffer<Measurement> MeasurementCircularBuffer;

    /**
     * @brief define relocalization message
     * @details this message will be used to communication which other module
     */
    struct RelocalizationMsg
    {
        /// @brief queried frame id
        uint64_t query_frame_id;

        /// @brief solved pose of query frame in global map frame
        Pose3 query_T_wb;

        /// @brief 3d to 2d correspondences, used to build pose only projection factor
        MapProjectionMeasurements mpm;

        /// @brief constructor
        RelocalizationMsg(const uint64_t _query_frame_id = 0, const Pose3& _query_T_wb = Pose3(),
                          const MapProjectionMeasurements& _mpm = {})
          : query_frame_id(_query_frame_id), query_T_wb(_query_T_wb), mpm(_mpm)
        {
        }
    };

    /**
     * @brief define ransac pnp solver parameters
     */
    struct RansacPnPParameters
    {
        /// @brief iteration number
        const uint16_t iteration;

        /// @brief projection threshold to determine inliers
        const Scalar projection_threshold;

        /// @brief ransanc confidence
        const Scalar confidence;

        /// @brief minimum matched correspondence number
        const uint16_t minimum_correspondence;

        /// @brief minimum inliers number
        const uint16_t minimum_inliers;

        /**
         * @brief Constructor
         */
        RansacPnPParameters(const uint16_t& _iterator = 100, const Scalar& _projection_threshold = 0.005,
                            const Scalar& _confidence = 0.99, const uint16_t& _minimum_correspondence = 10,
                            const uint16_t& _minimum_inliers = 8)
          : iteration(_iterator)
          , projection_threshold(_projection_threshold)
          , confidence(_confidence)
          , minimum_correspondence(_minimum_correspondence)
          , minimum_inliers(_minimum_inliers)
        {
        }
    };  // PnPParameters

    /**
     * @brief define parameters
     */
    struct Parameters
    {
        /// @brief vio estimation frequency
        Scalar frequency;

        /// @brief measurement circular buffer size.
        const uint64_t measurements_queue_size;

        /// @brief distance threshold to query candidate keyframe. in meter
        const Scalar distance_threshold;

        /// @brief angle threshold to query candidate keyframe. in degree
        const Scalar angle_threshold;

        /// @brief maximum processed keyframe
        const uint16_t maximum_keyframe_num;

        /// @brief flag which indicate whether enable pose only BA after frame to frames checking
        const bool enable_pose_only_ba;

        /// @brief flag which indicate whether enable visualize matched result
        const bool visualize_matches;

        /// @brief ransac pnp solver parameters
        const RansacPnPParameters ransac_pnp_params;

        /// @brief bag-of-words vocabulary
        std::string const vocabulary_path;

        /// @brief query candidate key-frames method
        uint16_t const query_type_uint16;

        /**
         * @brief Constructor
         */
        Parameters(const Scalar _frequency = 1.0, const uint64_t _measurements_queue_size = 5,
                   const Scalar _distance_threshold = 10.0, const Scalar _angle_threshold = 15.0,
                   const uint16_t _maximum_keyframe_num = 6, const bool _enable_pose_only_ba = true,
                   const bool                 _visualize_matches = false,
                   const RansacPnPParameters& _ransac_pnp_params = RansacPnPParameters(),
                   std::string const& _vocabulary_path = "",
                   uint16_t const _query_type_uint16 = 0u)
          : measurements_queue_size(_measurements_queue_size)
          , distance_threshold(_distance_threshold)
          , angle_threshold(_angle_threshold)
          , maximum_keyframe_num(_maximum_keyframe_num)
          , enable_pose_only_ba(_enable_pose_only_ba)
          , visualize_matches(_visualize_matches)
          , ransac_pnp_params(_ransac_pnp_params)
          , vocabulary_path(_vocabulary_path)
          , query_type_uint16(_query_type_uint16)
        {
            frequency = _frequency;
        }

        /**
         * @brief output stream for Parameters
         *
         * @param os std::ostream&
         * @param params Parameters
         * @return std::ostream&
         */
        friend std::ostream& operator<<(std::ostream& os, const Parameters& params)
        {
            os << "RelocaizationParameters:\n"
               << " frequency = " << params.frequency
               << "\n measurements_queue_size = " << params.measurements_queue_size
               << "\n distance_threshold = " << params.distance_threshold
               << "\n angle_threshold = " << params.angle_threshold
               << "\n maximum_keyframe_num = " << params.maximum_keyframe_num
               << "\n enable_pose_only_ba = " << params.enable_pose_only_ba
               << "\n visualize_matches = " << params.visualize_matches
               << "\n ransac_pnp_params.iteration = " << params.ransac_pnp_params.iteration
               << "\n ransac_pnp_params.projection_threshold = " << params.ransac_pnp_params.projection_threshold
               << "\n ransac_pnp_params.confidence = " << params.ransac_pnp_params.confidence
               << "\n ransac_pnp_params.minimum_correspondence = " << params.ransac_pnp_params.minimum_correspondence
               << "\n ransac_pnp_params.minimum_inliers = " << params.ransac_pnp_params.minimum_inliers << std::endl;
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
     * @brief struct of FrameToFrameCheckingResult
     */
    struct FrameToFrameCheckingResult
    {
        /// @brief train frame id and camera index
        std::pair<uint64_t, uint16_t> train_frame_id_and_camera_index;

        /// @brief matched index pairs
        MatchedPairs matche_pairs;

        /// @brief inlier index pairs
        /// @details if solving failed, the inliers is empty. so one should checking the inliers first before use the
        /// solved T_wc.
        std::vector<std::pair<uint16_t, uint16_t>> inliers;

        /// @brief solved camera pose in world frame
        Pose3 T_wc;

        /**
         * @brief Constructor
         */
        FrameToFrameCheckingResult(const std::pair<uint64_t, uint16_t> _train_frame_id_and_camera_index = {},
                                   const MatchedPairs&                 _matche_pairs                    = {},
                                   const std::vector<std::pair<uint16_t, uint16_t>>& _inliers           = {},
                                   const Pose3&                                      _T_wc = Pose3::Identity())
          : train_frame_id_and_camera_index(_train_frame_id_and_camera_index)
          , matche_pairs(_matche_pairs)
          , inliers(_inliers)
          , T_wc(_T_wc)
        {
        }
    };

    /**
     * @brief Constructor
     *
     * @param parameters
     */
    Relocalization(const Parameters& parameters, const CameraParameters::Ptr& camera_parameters);

    /**
     * @brief Destructor
     */
    ~Relocalization()
    {
        relocalization_thread_->join();
    }

    /**
     * @brief add new measurement
     */
    void AddNewMeasurement(const Measurement& m)
    {
        {
            std::unique_lock<std::mutex> lock(relocalization_mutex_);
            measurements_queue_.push_back(m);
        }
    }

    /**
     * @brief query lastest relocalization message
     */
    boost::optional<RelocalizationMsg> GetLastestRelocalizationMsg()
    {
        std::unique_lock<std::mutex> lock(relocalization_mutex_);
        const auto                   result = lastest_relocalization_msg_;
        lastest_relocalization_msg_         = boost::none;
        return result;
    }

    /**
     * @brief main function for computing initial vehiclestate
     *
     * @param multi_camera_features features from multi-camera system
     * @param prior_vehicle_pose prior vehicle pose (optional)
     * @return optional solved vehicle pose
     */
    boost::optional<Pose3> RunSynchronously(const std::vector<Features>& multi_camera_features,
                                            const boost::optional<Pose3>& prior_vehicle_pose) const;

    /**
     * @brief load keyframe database from file
     * @param frames_database key frames database
     */
    void SetKeyFramesDatabase(const KeyFramesDatabase& key_frames_database)
    {
        key_frames_database_ = key_frames_database;
    }

    /**
     * @brief load keyframe dbow vector from file
     * 
     * @param keyframes_bow_vector keyframe's bow vector
     */
    void SetKeyFramesDbowVector(const FrameIndexedBows& keyframes_bow_vector)
    {
        keyframes_bow_vectors_ = keyframes_bow_vector;
    }

    /// @brief bag-of-words vocabulary
    static std::shared_ptr<DBoW3::Vocabulary> bow_vocabulary_;

private:
    /**
     * @brief check pre condition
     */
    virtual bool checkPreCondition() override
    {
        std::unique_lock<std::mutex> lock(relocalization_mutex_);
        return (!measurements_queue_.empty());
    }

    /**
     * @brief core algorithm happens here
     */
    virtual void run() override;

    /**
     * @brief slove pnp with ransac method
     * @param point3d points in world frame
     * @param point2d points in normalized frame
     * @param K intrinsic
     * @return solved camera pose and inliers index. if solved pnp failed, the inliers is empty. so one should checking
     * the inliers first before use the pose.
     */
    std::pair<Pose3, std::vector<uint16_t>> RansacPnpRun(const std::vector<cv::Point3d>& point3d,
                                                         const std::vector<cv::Point2d>& point2d,
                                                         const cv::Mat&                  K) const;

    /**
     * @brief solve vehile pose by frame to frame matching
     * @details 1. query candidate frames from given keyframe database
     *          2. feature mathing betwen each candidate frame and query features
     *          3. geometric consistency checking by ransac epnp for each candidate frame
     *
     * @param train_frames the train frame database
     * @param query_features query features
     * @param prior_vehicle_pose prior vehicle pose.
     * @param query_image query image. used to visualization
     * @return a set of FrameToFrameCheckingResult
     */
    std::vector<FrameToFrameCheckingResult>
    SolvePoseByFrameToFrameMatching(const KeyFramesDatabase& train_frames, const Features& query_features,
                                    const boost::optional<Pose3>& prior_vehicle_pose = boost::none,
                                    const cv::Mat& query_image = cv::Mat()) const;

    /**
     * @brief query candidate frames from keyframe database
     * @details use a prior pose to query candidate frame, all keyframes located in a certain range will served as
     * candidate frame.
     *
     * @param train_frames train keyframe database
     * @param prior_camera_pose query prior pose aboue camera
     * @param n_best_candidates top N similar candidate keyframes
     * @param dist_threshold distance threshold in meter
     * @param angle_threshold angle threshold in degree
     *
     * @return a vector which include candidate frames; key: candidate_frame_id, value: candidata_camera_id 
     * @note one frame can have multi camera's image
     */
    std::vector<std::pair<uint64_t, uint16_t> >
    QueryCandidateFramesByPose(KeyFramesDatabase const& train_frames, Pose3 const& prior_camera_pose,
                               uint16_t const n_best_candidates, Scalar const dist_threshold,
                               Scalar const angle_threshold) const;

    /**
     * @brief query candidate frames from keyframe database
     * @details use bag-of-words to query candidate frame, all keyframes with high similarity score will served as
     * candidate frame.
     *
     * @param query_features image features which extracted from query image
     * @param train_keyframes train keyframe database, store all information about keyframes
     * @param n_best_candidates top N similar candidate keyframes
     *
     * @return a vector which include: key: candidate_frame_id, value: candidata_camera_id
     * @note one frame can have multi camera
     */
    std::vector<std::pair<uint64_t, uint16_t>> QueryCandidateFramesByBOW(Features const&          query_features,
                                                                         FrameIndexedBows const& keyframes_bow_vectors,
                                                                         uint16_t const n_best_candidates) const;

    /**
     * @brief frame to frame geometric consistency checking
     * @details 1. feature matching
     *          2. ransac epnp solving
     *
     * @param train_frame candidate frame
     * @param camera_index candidate camera index in train frame
     * @param query_features query features
     * @param optional_prior_Twc prior camera pose (optional)
     *
     * @return A FrameToFrameCheckingResult struct
     */
    FrameToFrameCheckingResult GeometricConsistencyChecking(const KeyFrame& train_frame, const uint16_t camera_index,
                                                            const Features& query_features,
                                                            const boost::optional<Pose3>& optional_prior_Twc = boost::none) const;

    /**
     * @brief constrain value within [min, max]
     */
    int32_t BoundaryClamp(const int32_t value, const int32_t min, const int32_t max) const;

    /**
     * @brief create MapProjectionMeasurements from a set of FrameToFrameCheckingResult
     *
     * @param train_frames keyframe database
     * @param query_features query features
     * @param associated_results associated FrameToFrameCheckingResult
     * @return MapProjectionMeasurements
     */
    MapProjectionMeasurements
    CreatePoseOnlyProjectionFactorMeasurements(const KeyFramesDatabase& train_frames, const Features& query_features,
                                               const std::vector<FrameToFrameCheckingResult>& associated_results) const;

    /**
     * @brief pose only bundle adjustment
     * @details optimize camera pose by given MapProjectionMeasurements
     *
     * @param mpms factor measurements
     * @param prior_Twc initial camera pose
     * @param intrinsic camera intrinsic
     * @return potimized camera pose and inliers MapProjectionMeasurements. if optimization failed, the inliers
     * MapProjectionMeasurements is empty. so one should checking the MapProjectionMeasurements first before use the
     * pose.
     */
    std::pair<Pose3, MapProjectionMeasurements> PoseOnlyBundleAdjustment(const MapProjectionMeasurements& mpms,
                                                                         const Pose3&                     prior_Twc,
                                                                         const IntrinsicBaseTypePtr& intrinsic) const;

    /**
     * @brief merge two images as a single one for futher draw matches information
     *
     * @param image0 first image
     * @param image1 second image
     * @return merged image
     */
    cv::Mat MergeTwoImages(const cv::Mat& image0, const cv::Mat& image1) const;

    /**
     * @brief visualize matches information
     *
     * @param train_frames keyframe database
     * @param query_features the current query features
     * @param query_image the query image
     * @param associated_results associated FrameToFrameCheckingResult
     */
    void DrawMacthedInfo(const KeyFramesDatabase& train_frames, const Features& query_features,
                         const cv::Mat&                                 query_image,
                         const std::vector<FrameToFrameCheckingResult>& associated_results) const;

    /// @brief parameters
    const Parameters parameters_;

    /// @brief shared_ptr of camera parameters
    CameraParameters::Ptr camera_parameters_;

    /// @brief mutex and thread
    std::mutex                   relocalization_mutex_;
    std::shared_ptr<std::thread> relocalization_thread_;

    /// @brief keyframe database
    KeyFramesDatabase key_frames_database_;

    /// @brief keyframe;s bow vector
    FrameIndexedBows keyframes_bow_vectors_;

    /// @brief measurements buffer
    MeasurementCircularBuffer measurements_queue_;

    /// @brief current processed measurement
    Measurement current_measurement_;

    /// @brief lastest relocalization message
    boost::optional<RelocalizationMsg> lastest_relocalization_msg_;

    /// @brief query candidate keyframe's method
    QueryType query_type_;

};  // class Relocalization

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_LOCALIZATION_RELOCALIZATION_H_
