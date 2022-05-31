/*!
 * \brief vslam base class header file in vslam
 * \author Yanwei. Du duyanwei@holomatic.com
 * \author Feng. Li lifeng@holomatic.com
 * \date Mar-18-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_VSLAM_BASE_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_VSLAM_BASE_H_

#include <holo/localization/common/localization_base.h>
#include <holo/localization/tools/source_checker.h>
#include <holo/localization/vision/vslam/failure_detection.h>
#include <holo/localization/vision/vslam/initializer.h>
#include <holo/localization/vision/vslam/localization/relocalization.h>
#include <holo/localization/vision/vslam/measurements_manager_vslam.h>
#include <holo/localization/vision/vslam/raw_measurement_preprocessor.h>
#include <holo/localization/vision/vslam/sliding_window_estimator.h>
#include <holo/localization/vision/vslam/visualizer.h>

#include <holo/localization/tools/impl/source_checker.hpp>
#include <mutex>
#include <thread>

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
 * @brief vslam main estimator class
 *
 * @details all the threads will be created in this class
 */
class VSLAMBase : public LocalizationBase
{
public:
    /**
     * @brief handy typedefs
     */
    typedef LocalizationBase Base;

    /**
     * @brief define callback functions
     */
    typedef std::function<int32_t(const Odometry&, const ImuBias&)>     VslamResultCallback;
    typedef std::function<int32_t(const Odometry&)>                     ImuPredictionResultCallback;
    typedef std::function<int32_t(const Visualizer::VisualizerStates&)> VisualizationCallback;
    typedef std::function<holo::int32_t(const PointCloudXYZIRRgbSt&)>   OutputPointCloudCallback;
    typedef std::function<holo::int32_t(const ParkingSlotFrameType&)>   OutputParkingSlotFrameCallback;

    /**
     * @brief vslam parameters
     */
    struct SourceCheckerResult
    {
        bool      is_frequency_low         = false;
        bool      is_error                 = false;
        Timestamp low_frequency_start_time = Timestamp(0, 0);
    };

    /**
     * @brief vslam parameters
     */
    struct SourceCheckerParameters
    {
        SourceCheckerImu::Parameters imu_sc_params;

        SourceCheckerChassisState::Parameters chassis_state_sc_params;

        SourceCheckerPointFeatureList::Parameters point_feature_list_sc_params;

        SourceCheckerObstaclePtrList::Parameters obstacle_list_sc_params;

        SourceCheckerParkingSlotFrame::Parameters parking_slot_frame_sc_params;

        SourceCheckerParameters(const SourceCheckerImu::Parameters&              _imu_sc_params,
                                const SourceCheckerChassisState::Parameters&     _chassis_state_sc_params,
                                const SourceCheckerPointFeatureList::Parameters& _point_feature_list_sc_params,
                                const SourceCheckerObstaclePtrList::Parameters&  _obstacle_list_sc_params,
                                const SourceCheckerParkingSlotFrame::Parameters& _parking_slot_frame_sc_params)
          : imu_sc_params(_imu_sc_params)
          , chassis_state_sc_params(_chassis_state_sc_params)
          , point_feature_list_sc_params(_point_feature_list_sc_params)
          , obstacle_list_sc_params(_obstacle_list_sc_params)
          , parking_slot_frame_sc_params(_parking_slot_frame_sc_params)
        {
        }

        // @brief load parameters from yaml
        static SourceCheckerParameters LoadFromYaml(const holo::yaml::Node& node);
    };

    /**
     * @brief error code paramters
     */
    struct ErrorCodeParameters
    {
        /// @brief inliers few error params
        uint32_t  feature_point_num_few_threshold;
        float32_t feature_few_tolerance;

        /// @brief camera frequency low error params
        float32_t front_camera_frequency_low_threshold;
        float32_t front_camera_frequency_low_tolerance;

        /// @brief imu frequency low error params
        float32_t imu_frequency_low_threshold;
        float32_t imu_frequency_low_tolerance;

        /// @brief chassis state frequency low error params
        float32_t chassis_state_frequency_low_threshold;
        float32_t chassis_state_frequency_low_tolerance;

        /// @brief point feauture frequency low error params
        float32_t feature_point_frequency_low_threshold;
        float32_t feature_point_frequency_low_tolerance;

        /// @brief obstacle frequency low error params
        float32_t obstacle_frequency_low_threshold;
        float32_t obstacle_frequency_low_tolerance;

        ///@brief parking slot frequency low error params
        float32_t parking_slot_frequency_low_threshold;
        float32_t parking_slot_frequency_low_tolerance;

        ///@brief gnss frequency low error params
        float32_t gnss_position_frequency_low_threshold;
        float32_t gnss_position_frequency_low_tolerance;

        /// @brief parking overtime when online mapping threshold
        float32_t online_mapping_parking_overtime_threshold;

        /// @brief travel distance beyond limits when online mapping
        float32_t online_mapping_over_length_threshold;

        /// @brief mapping distance over length warning level 1
        float32_t online_mapping_over_length_warning_L1_threshold;

        /// @brief travel timeout when online mapping
        float32_t online_mapping_overtime_threshold;

        /// @brief mapping timeout threshold
        float32_t online_mapping_overtime_warning_threshold;

        /// @brief mapping distance over length warning level 1
        float32_t online_mapping_over_length_warning_L2_threshold;

        /// @brief online mapping turning limit threshold
        float32_t onine_mapping_turning_radius_small_threshold;

        /// @brief slope limit threshold
        float32_t online_mapping_slope_large_threshold;

        /// @brief constructor
        ErrorCodeParameters(const uint32_t _feature_point_num_few_threshold, const float32_t _feature_few_tolerance,
                            const float32_t _front_camera_frequency_low_threshold,
                            const float32_t _front_camera_frequency_low_tolerance,
                            const float32_t _imu_frequency_low_threshold, const float32_t _imu_frequency_low_tolerance,
                            const float32_t _chassis_state_frequency_low_threshold,
                            const float32_t _chassis_state_frequency_low_tolerance,
                            const float32_t _feature_point_frequency_low_threshold,
                            const float32_t _feature_point_frequency_low_tolerance,
                            const float32_t _obstacle_frequency_low_threshold,
                            const float32_t _obstacle_frequency_low_tolerance,
                            const float32_t _parking_slot_frequency_low_threshold,
                            const float32_t _parking_slot_frequency_low_tolerance,
                            const float32_t _gnss_position_frequency_low_threshold,
                            const float32_t _gnss_position_frequency_low_tolerance,
                            const float32_t _online_mapping_parking_overtime_threshold,
                            const float32_t _online_mapping_over_length_threshold,
                            const float32_t _online_mapping_over_length_warning_L1_threshold,
                            const float32_t _online_mapping_overtime_threshold,
                            const float32_t _online_mapping_overtime_warning_threshold,
                            const float32_t _online_mapping_over_length_warning_L2_threshold,
                            const float32_t _onine_mapping_turning_radius_small_threshold,
                            const float32_t _online_mapping_slope_large_threshold)
          : feature_point_num_few_threshold(_feature_point_num_few_threshold)
          , feature_few_tolerance(_feature_few_tolerance)
          , front_camera_frequency_low_threshold(_front_camera_frequency_low_threshold)
          , front_camera_frequency_low_tolerance(_front_camera_frequency_low_tolerance)
          , imu_frequency_low_threshold(_imu_frequency_low_threshold)
          , imu_frequency_low_tolerance(_imu_frequency_low_tolerance)
          , chassis_state_frequency_low_threshold(_chassis_state_frequency_low_threshold)
          , chassis_state_frequency_low_tolerance(_chassis_state_frequency_low_tolerance)
          , feature_point_frequency_low_threshold(_feature_point_frequency_low_threshold)
          , feature_point_frequency_low_tolerance(_feature_point_frequency_low_tolerance)
          , obstacle_frequency_low_threshold(_obstacle_frequency_low_threshold)
          , obstacle_frequency_low_tolerance(_obstacle_frequency_low_tolerance)
          , parking_slot_frequency_low_threshold(_parking_slot_frequency_low_threshold)
          , parking_slot_frequency_low_tolerance(_parking_slot_frequency_low_tolerance)
          , gnss_position_frequency_low_threshold(_gnss_position_frequency_low_threshold)
          , gnss_position_frequency_low_tolerance(_gnss_position_frequency_low_tolerance)
          , online_mapping_parking_overtime_threshold(_online_mapping_parking_overtime_threshold)
          , online_mapping_over_length_threshold(_online_mapping_over_length_threshold)
          , online_mapping_over_length_warning_L1_threshold(_online_mapping_over_length_warning_L1_threshold)
          , online_mapping_overtime_threshold(_online_mapping_overtime_threshold)
          , online_mapping_overtime_warning_threshold(_online_mapping_overtime_warning_threshold)
          , online_mapping_over_length_warning_L2_threshold(_online_mapping_over_length_warning_L2_threshold)
          , onine_mapping_turning_radius_small_threshold(_onine_mapping_turning_radius_small_threshold)
          , online_mapping_slope_large_threshold(_online_mapping_slope_large_threshold)
        {
        }

        // output stream
        friend std::ostream& operator<<(std::ostream& os, const ErrorCodeParameters& parameters)
        {
            os << " feature_point_num_few_threshold = " << parameters.feature_point_num_few_threshold
               << "\n feature_few_tolerance = " << parameters.feature_few_tolerance
               << "\n front_camera_frequency_low_threshold = " << parameters.front_camera_frequency_low_threshold
               << "\n front_camera_frequency_low_tolerance = " << parameters.front_camera_frequency_low_tolerance
               << "\n imu_frequency_low_threshold = " << parameters.imu_frequency_low_threshold
               << "\n imu_frequency_low_tolerance = " << parameters.imu_frequency_low_tolerance
               << "\n chassis_state_frequency_low_threshold = " << parameters.chassis_state_frequency_low_threshold
               << "\n chassis_state_frequency_low_tolerance = " << parameters.chassis_state_frequency_low_tolerance
               << "\n feature_point_frequency_low_threshold = " << parameters.feature_point_frequency_low_threshold
               << "\n feature_point_frequency_low_tolerance = " << parameters.feature_point_frequency_low_tolerance
               << "\n obstacle_frequency_low_threshold = " << parameters.obstacle_frequency_low_threshold
               << "\n obstacle_frequency_low_tolerance = " << parameters.obstacle_frequency_low_tolerance
               << "\n parking_slot_frequency_low_threshold = " << parameters.parking_slot_frequency_low_threshold
               << "\n parking_slot_frequency_low_tolerance = " << parameters.parking_slot_frequency_low_tolerance
               << "\n gnss_position_frequency_low_threshold = " << parameters.gnss_position_frequency_low_threshold
               << "\n gnss_position_frequency_low_threshold = " << parameters.gnss_position_frequency_low_threshold
               << "\n online_mapping_parking_overtime_threshold = "
               << parameters.online_mapping_parking_overtime_threshold
               << "\n online_mapping_over_length_threshold = " << parameters.online_mapping_over_length_threshold
               << "\n online_mapping_over_length_warning_L1_threshold = "
               << parameters.online_mapping_over_length_warning_L1_threshold
               << "\n online_mapping_overtime_threshold = " << parameters.online_mapping_overtime_threshold
               << "\n online_mapping_overtime_warning_threshold = "
               << parameters.online_mapping_overtime_warning_threshold
               << "\n online_mapping_over_length_warning_L2_threshold = "
               << parameters.online_mapping_over_length_warning_L2_threshold
               << "\n onine_mapping_turning_radius_small_threshold = "
               << parameters.onine_mapping_turning_radius_small_threshold
               << "\n online_mapping_slope_large_threshold = " << parameters.online_mapping_slope_large_threshold
               << "\n";
            return os;
        }

        // @brief load parameters from yaml
        static ErrorCodeParameters LoadFromYaml(const holo::yaml::Node& node);

        /// @brief example
        static ErrorCodeParameters Example();
    };

    /**
     * @brief vslam parameters
     */
    struct Parameters
    {
        /// @brief the flag indicates if do imu prediction with fixed frequency
        bool do_imu_preintegration_with_fixed_frequency;

        /// @brief frequency to do imu preintegration
        Scalar preintegration_frequency;

        /// @brief enable semantic model
        bool enable_semantic_mode;

        /// @brief frequency is defined in Base class
        Scalar frequency;

        /// @brief the time interval between two parking slot frames
        Scalar psd_fusion_time_interval;

        /// @brief shared_ptr of camera parameters
        CameraParameters::Ptr camera_params;

        /// @brief raw measurement preprocessor parameters
        RawMeasurementPreprocessor::Parameters rmpp_params;

        /// @brief define graph builder parameters
        GraphBuilder::Parameters builder_params;

        /// @brief define sliding window estimator parameters
        SlidingWindowEstimator::Parameters se_params;

        /// @brief define failure detection parameters
        FailureDetection::Parameters fd_params;

        /// @brief define measurement manager vslam parameters
        MeasurementsManagerVSLAM::Parameters mmv_params;

        /// @brief define source checker parameters
        SourceCheckerParameters sc_params;

        /// @brief define error code params
        ErrorCodeParameters ec_params;

        /// @brief enable estimation with acc
        bool enable_estimation_with_acc;

        /// @brief max inliers in sliding window
        /// @details if the inlier global correspondence number larger than this threshold, for efficiency reason, we
        /// don't add new global association to factor graph any more.
        uint32_t max_inlier_global_correspondence_num;

        /// @brief minimum inliers in current frame
        /// @details if the inlier correspondence number in current frame less than this threshold,  we will do global
        /// association in next iteration.
        uint32_t minimum_inlier_correspondence_num;

        /// @brief constructor
        Parameters(const bool _is_imu_prediction_frequency_fixed, const Scalar _frequency,
                   const Scalar _preintegration_frequency, const bool& _enable_semantic_mode,
                   const Scalar _psd_fusion_time_interval, const CameraParameters::Ptr& _camera_params,
                   const RawMeasurementPreprocessor::Parameters& _rmpp_params,
                   const GraphBuilder::Parameters&               _builder_params,
                   const SlidingWindowEstimator::Parameters& _se_params, const FailureDetection::Parameters& _fd_params,
                   const MeasurementsManagerVSLAM::Parameters& _mmv_params, const SourceCheckerParameters& _sc_params,
                   const ErrorCodeParameters& _ec_params, bool _enable_estimation_with_acc = false,
                   uint32_t       _max_inlier_global_correspondence_num = 300,
                   const uint32_t _minimum_inlier_correspondence_num    = 20)
          : do_imu_preintegration_with_fixed_frequency(_is_imu_prediction_frequency_fixed)
          , preintegration_frequency(_preintegration_frequency)
          , enable_semantic_mode(_enable_semantic_mode)
          , psd_fusion_time_interval(_psd_fusion_time_interval)
          , camera_params(_camera_params)
          , rmpp_params(_rmpp_params)
          , builder_params(_builder_params)
          , se_params(_se_params)
          , fd_params(_fd_params)
          , mmv_params(_mmv_params)
          , sc_params(_sc_params)
          , ec_params(_ec_params)
          , enable_estimation_with_acc(_enable_estimation_with_acc)
          , max_inlier_global_correspondence_num(_max_inlier_global_correspondence_num)
          , minimum_inlier_correspondence_num(_minimum_inlier_correspondence_num)
        {
            frequency = _frequency;
        }

        // output stream
        friend std::ostream& operator<<(std::ostream& os, const Parameters& parameters)
        {
            os << "VSLAMBaseParameters: " << parameters.camera_params << parameters.rmpp_params
               << parameters.builder_params << parameters.se_params << parameters.fd_params << parameters.mmv_params
               << "\n do_imu_preintegration_with_fixed_frequency = "
               << parameters.do_imu_preintegration_with_fixed_frequency
               << "\n preintegration_frequency = " << parameters.preintegration_frequency
               << "\n enable_estimation_with_acc = " << parameters.enable_estimation_with_acc
               << "\n max_inlier_global_correspondence_num = " << parameters.max_inlier_global_correspondence_num
               << "\n minimum_inlier_correspondence_num = " << parameters.minimum_inlier_correspondence_num << "\n";
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
    VSLAMBase(const Parameters& parameters, const FeatureAssociator::Parameters& fa_params,
              const Initializer::Parameters& initializer_params);

    /**
     * @brief destructor
     */
    virtual ~VSLAMBase();

    /**
     * @brief get vslam parameters
     */
    virtual const Parameters& Params() const
    {
        return parameters_;
    }

    /**
     * @brief set visualizer
     */
    virtual void SetVisualizer(std::shared_ptr<vslam::Visualizer> visualizer)
    {
        visualizer_ = visualizer;
    };

    /**
     * @brief stop vslam and imu prediction thread
     */
    virtual void Stop() override;

    /**
     * @brief process image
     * @param[in] measurement latest image measurement
     */
    int32_t ProcessImage(const Image& measurement, const uint16_t camera_index);

    /**
     * @brief process point feature list
     * @param[in] measurement latest point feature list measurement
     */
    int32_t ProcessPointFeaturePtrList(PointFeaturefList_ST* const measurement);

    /**
     * @brief process imu
     * @param[in] measurement latest imu measurement
     */
    int32_t ProcessImu(const Imu& measurement);

    /**
     * @brief process vehicle info
     * @param[in] measurement latest vehicle info measurement
     */
    int32_t ProcessChassisState(const ChassisState& measurement);

    /**
     * @brief process gps position
     * @param[in] latest gps position measurement
     */
    int32_t ProcessGnssPosition(const GnssPosition& measurement);

    /**
     * @brief process gravity-aligned odometry
     * @details use gravity-aligned odometry to initialize vslam system
     */
    int32_t ProcessGravityAlignedOdometry(const Odometry& measurement);

    /**
     * @brief process ground truth odometry
     */
    int32_t ProcessGroundTruthOdometry(const Odometry& measurement);

    /**
     * @brief process obstacle ptr list
     */
    int32_t ProcessObstaclePtrList(const ObstaclePtrList& measurement);

    /**
     * @brief process parking slot frame
     * @param[in] measurement latest parking slot frame measurement
     */
    int32_t ProcessParkingSlotFrame(const ParkingSlotFrameType& measurement);

    /**
     * @brief set vslam result callback for publishing and saving
     */
    int32_t SetVslamResultCallback(const VslamResultCallback& cb);

    /**
     * @brief set imu prediction result callback for publishing and saving
     */
    int32_t SetImuPredictionResultCallback(const ImuPredictionResultCallback& cb);

    /**
     * @brief set visualization callback
     */
    int32_t SetVisualizationCallback(const VisualizationCallback& cb);

    /**
     * @brief Set the Output Local Feature Map Callback
     */
    int32_t SetOutputLocalFeatureMapCallback(const OutputPointCloudCallback& cb);

    /**
     * @brief Set the Output Global Feature Map Callback
     */
    int32_t SetOutputGlobalFeatureMapCallback(const OutputPointCloudCallback& cb);

    /**
     * @brief Get the App Error Status Ptr
     */
    AppErrorStatus::Ptr GetAppErrorStatus()
    {
        std::unique_lock<std::mutex> app_error_status_mutex_;
        return app_error_status_;
    }

    /**
     * @brief Set the Output Global Correspondence Callback
     *
     * @param cb
     * @return int32_t
     */
    int32_t SetOutputGlobalCorrespondenceCallback(const OutputPointCloudCallback& cb);

    /**
     * @brief Set the Output Parking Slot frame Callback
     */
    int32_t SetOutputGlobalParkingSlotFrameCallback(const OutputParkingSlotFrameCallback& cb);

    /**
     * @brief set vslam base in dr mode
     */
    void SetDrMode();

protected:
    /**
     * @brief pre-condition checking
     *
     * @details it will be called before EstimationCore() to check
     *          pre-condition
     */
    virtual bool checkPreCondition() override;

    /**
     * @brief post-condition checking
     *
     * @details it will be called after EstimationCore()
     */
    virtual bool postProcess() override;

    /**
     * @brief check raw measurements consistency
     * @details if the timestamp difference between measurements in new_raw_measurement and old_timestamp is smaller
     * than certain threshold, we think this measurement is consistent. threshold is hard code inside the function.
     *
     * @param old_timestamp timestamp of latest processed raw measurement
     * @param new_raw_measurement new raw measurement will be processed by vslam
     * @return true if new_raw_measurement is consistent. else return false.
     */
    bool IsMeasurementConsistent(const Timestamp& old_timestamp, const RawMeasurement& new_raw_measurement) const;

    /**
     * @brief process and publish vslam result
     * @param[in] state
     * @param[in] sequence_counter counter of the published SlidingWindowState
     */
    void PublishVslamResult(const SlidingWindowState& state, const uint64_t sequence_counter) const;

    /**
     * @brief visualize vslam result
     */
    void VisualizeVslamResult(const Visualizer::VisualizerStates& visualizer_states) const;

    /**
     * @brief predict prior vehicle pose in world frame
     * @details this function will be called at beginning of EstimationCore(), it will be used to query a local map from
     * the prebuilt map which is stored in measurement manager.
     * @note NOT FP!!! since MeasurementsManagerVSLAM was NOT FP, so we can NOT pass its const reference argument to
     * this function
     *
     * @param measurements_manager measurements manager.
     * @return an optional vehicle pose
     */
    boost::optional<Pose3> PredictVehiclePoseAtBeginning(MeasurementsManagerVSLAM& measurements_manager) const;

    /**
     * @brief estimator core function
     *
     * @details all the algorithms will be called in this function
     */
    virtual void run() override;

    /**
     * @brief convert VehicleState to Odometry
     * @param[in] vehicle_state current VehicleState
     * @param[in] current_time timestamp corresponding to vehicle_state
     * @param[in] sequence_counter the counter of the Odometry sequence
     * @return odometry
     */
    Odometry VehicleStateToOdometry(const VehicleState& vehicle_state, const Timestamp& current_time,
                                    const uint64_t sequence_counter) const;

    /**
     * @brief convert map to point clouds for visualization
     */
    PointCloudXYZIRRgbSt ConvertToPointCloud(const ConstMapPtr& map,
                                             const Pose3&       anchor_pose = Pose3::Identity()) const;

    /**
     * @brief check if a track is activated
     */
    static bool IsActivedTrack(const FeatureTrack& track)
    {
        return track.GetState() != FeatureTrack::State::DEAD;
    }

    /**
     * @brief set tracks's state to DEAD if the track is useless.
     * @details DEAD track will be removed from sliding window in next tracking progress. defferent business logic may
     * have different strategy to determine which tracks will be treated as DEAD.
     *
     * @param[in,out] state tracker state
     */
    virtual void DetermineDeadTracks(Tracker::State& state) const;

    /**
     * @brief update sliding window state by filter rejected tracks
     * @details it will remove bad tracks in given sliding window by calling function FilterRejectedTracks()
     *
     * @param[in,out] state the processed sliding window state
     */
    void UpdateStateByFilterRejectedTracks(SlidingWindowState& state) const;

    template <typename T1, typename T2>
    SourceCheckerResult SourceChecker(const T1& soucer_checker, const T2& measurement,
                                      const Scalar& low_frequency_limit, const Scalar& tolerate_duration,
                                      const std::string& source_name, const SourceCheckerResult& last_checker_result);

    /**
     * @brief variables
     */
    const Parameters           parameters_;                         ///< vslam parameters
    MeasurementsManagerVSLAM   measurements_manager_;               ///< measurements_manager
    RawMeasurementPreprocessor preprocessor_;                       ///< raw measurement preprocessor
    Initializer                initializer_;                        ///< initializer
    SlidingWindowEstimator     estimator_;                          ///< estimator
    FailureDetection           failure_detection_;                  ///< failure_detection
    SlidingWindowState         sliding_window_state_;               ///< sliding window state
    uint64_t                   estimation_core_iteration_counter_;  ///< counter for EstimationCore

    /**
     * define callback functions
     */
    VslamResultCallback            vslam_result_callback_;
    ImuPredictionResultCallback    imu_prediction_result_callback_;
    VisualizationCallback          visualization_callback_;
    OutputPointCloudCallback       output_local_feature_map_callback_;
    OutputPointCloudCallback       output_global_feature_map_callback_;
    OutputPointCloudCallback       output_global_correspondence_callback_;
    OutputParkingSlotFrameCallback output_global_parking_slot_frame_callback_;

    /**
     * @brief variables for reset
     */
    ResetFlags      reset_flags_;       ///< reset flags
    SequenceCounter sequence_counter_;  ///< sequence counter

    /// @brief learned path for HPP
    /// @details this variable is just used by hpp, it's the vehicle trajectory when build the pre-built map in mapping
    /// mode
    std::vector<Odometry> learned_path_;

    /// @brief time monitor for
    TicTocTimer timer_;

    /// @brief the newest raw measurements
    RawMeasurement new_raw_measurements_;

    /// @brief the newest corrected measurement
    CorrectedMeasurement new_corrected_measurements_;

    /// @brief the newest factor measurement
    FactorMeasurements new_factor_measurements_;

    /// @brief flat to indicate if the EstimationCore work well.
    /// @details for example. if some exception thrown by gtsam during optimization, or failed to get raw measurements,
    /// this variable will be false.
    bool is_estimation_core_work_well_;

    /// @brief relocalization message
    Relocalization::RelocalizationMsg reloc_msg_;

    // graph builder smart pointer
    GraphBuilder::Ptr graph_builder_;

    uint64_t new_frame_id_;

    /// @brief timestamp to control raw measurement cycle time
    Timestamp last_raw_measurement_timestamp_;
    Timestamp last_parking_slot_timestamp_;

    ///@brief app error status
    AppErrorStatus::Ptr app_error_status_;
    std::mutex          app_error_status_mutex_;

    /// @brief chassis state source checker
    SourceCheckerChassisState::Ptr chassis_state_source_checker_;

    ///@brief imu source checker
    SourceCheckerImu::Ptr imu_source_checker_;

    ///@brief point feature list source checker
    SourceCheckerPointFeatureList::Ptr point_feature_list_source_checker_;

    ///@brief obstacle list source checker
    SourceCheckerObstaclePtrList::Ptr obstacle_list_source_checker_;

    ///@brief parking slot frame source checker
    SourceCheckerParkingSlotFrame::Ptr parking_slot_frame_source_checker_;

    ///@brief gnss position source checker
    SourceCheckerGnssPosition::Ptr gnss_position_source_checker_;

    /// choose if use dr mode according to state machine cmw app
    std::atomic<bool> enable_dr_mode_;

    ///@brief the visualizer
    std::shared_ptr<vslam::Visualizer> visualizer_;

};  // VSLAMBase

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_VSLAM_BASE_H_
