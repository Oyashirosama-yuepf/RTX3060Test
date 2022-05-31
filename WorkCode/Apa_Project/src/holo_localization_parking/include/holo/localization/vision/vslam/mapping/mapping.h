/*!
 * \brief mapping class header file in vslam
 * \author Yanwei. Du duyanwei@holomatic.com
 * \author Feng. Li lifeng@holomatic.com
 * \date Mar-18-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_MAPPING_MAPPING_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_MAPPING_MAPPING_H_

#include <holo/localization/vision/vslam/mapping/map_database_manager.h>
#include <holo/localization/vision/vslam/vslam_base.h>

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
 * @brief visual mapping main estimator class
 *
 * @details all the threads will be created in this class
 */
class Mapping : public VSLAMBase
{
public:
    /**
     * @brief handy typedefs
     */
    typedef VSLAMBase                                     Base;
    typedef std::unordered_map<uint64_t, MapPoint>        IndexedMappoints;
    typedef std::unordered_map<uint64_t, ParkingSlotType> IndexedParkingSlots;
    typedef MapDatabaseManager::OfflineMappingData        OfflineMappingData;

    /**
     * @brief vslam parameters
     */
    struct Parameters : public Base::Parameters
    {
        /// @brief frequency is defined in Base class

        /// @brief initializer parameters
        Initializer::Parameters initializer_params;

        /// @brief visual feature association parameters
        FeatureAssociator::Parameters fa_params;

        /// @brief map database maneger parameters
        MapDatabaseManager::Parameters mdm_params;

        /// @brief enable map database save thread
        bool_t enable_data_save_thread;

        /// @brief minimum travel distance for keyfram selection
        Scalar minimum_keyframe_travel_distance;

        /// @brief minimum angle for keyfram selection
        Scalar minimum_keyframe_angle;

        /// @brief constructor
        Parameters(const Base::Parameters& _base_params, const Initializer::Parameters& _initializer_params,
                   const FeatureAssociator::Parameters& _fa_params, const MapDatabaseManager::Parameters& _mdm_params,
                   const bool_t _enable_data_save_thread, const Scalar _minimum_keyframe_travel_distance = 1.0,
                   const Scalar _minimum_keyframe_angle = 5.0)
          : Base::Parameters(_base_params)
          , initializer_params(_initializer_params)
          , fa_params(_fa_params)
          , mdm_params(_mdm_params)
          , enable_data_save_thread(_enable_data_save_thread)
          , minimum_keyframe_travel_distance(_minimum_keyframe_travel_distance)
          , minimum_keyframe_angle(_minimum_keyframe_angle)
        {
        }

        // output stream
        friend std::ostream& operator<<(std::ostream& os, const Parameters& parameters)
        {
            os << static_cast<Base::Parameters>(parameters) << "\nMappingParameters:\n "
               << parameters.initializer_params << parameters.fa_params << parameters.mdm_params
               << parameters.mmv_params << "\n, enable_data_save_thread : " << parameters.enable_data_save_thread
               << "\n, minimum_keyframe_travel_distance : " << parameters.minimum_keyframe_travel_distance
               << "\n, minimum_keyframe_angle : " << parameters.minimum_keyframe_angle << "\n";
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
    Mapping(const Parameters& parameters);

    /**
     * @brief destructor
     */
    virtual ~Mapping();

    /**
     * @brief get vslam parameters
     */
    virtual const Parameters& Params() const override
    {
        return parameters_;
    }

    /**
     * @brief stop vslam and imu prediction thread
     */
    virtual void Stop() override;

protected:
    /**
     * @brief post processing
     *
     * @details it will be called after EstimationCore()
     */
    virtual bool postProcess() override;

    /**
     * @brief process and publish point clouds
     * @details all landmarks retained in current sliding window and accumulated in the whole history sliding window
     * state will be published.
     *
     * @param state sliding window state
     *
     */
    void PublishPointClouds(const SlidingWindowState& state) const;

    /**
     * @brief publish global parking slot map
     *
     * @param state sliding window state
     *
     */
    void PublishGlobalSlotMap(const SlidingWindowState& state) const;

    /**
     * @brief convert parking slot from global to body
     *
     * @param T_bw from world to body
     * @param in parking slot in world frame
     */
    ParkingSlotType ConvertFromGlobalToBody(const Pose3& bTw, const ParkingSlotType& in) const;

    /**
     * @brief update the accumulated mappoints in sliding window
     *
     * @param[in,out] indexed_map the processed map
     */
    void UpdateMappoints(IndexedMappoints& indexed_map, const SlidingWindowState& new_state) const;

    /**
     * @brief update the accumulated parking slots in sliding window
     *
     * @param[in,out] indexed_parking_slots the processed parking slots
     * @param[in] semantic_state new parking slot semantic state
     * @param[in] new_sliding_window_state new sliding window state
     */
    void UpdateParkingSlots(IndexedParkingSlots&                    indexed_parking_slots,
                            const semantic::DataAssociation::State& semantic_state) const;

    /**
     * @brief get and remove marginalized parking slot tracks
     * @details for a track whoes newest measurement is out of sliding window, it will be marginalized from sliding
     * window. we also record optimized parking slot for visiual.
     *
     * @param[in,out] new_state new sliding window state
     * @param[out] marginalized_parking_slot_tracks the marginalized parking slot tracks
     *
     */
    void UpdateParkingSlotTracks(semantic::DataAssociation::State& semantic_state);

    /**
     * @brief wait here until the image queue get empty.
     * @note this function will be called in Stop() function when work in mapping mode.
     */
    void ProcessRemainingImages() const;

    /**
     * @brief construct map by indexed mappoints
     */
    MapPtr ConvertToMap(const IndexedMappoints& indexed_mappoints) const;

    /**
     * @brief retrieve all features extracted at given frame from all feature tracks
     *
     * @param tracks feature tracks
     * @param frame_id frame id
     * @return camera id and the corresponding feaures extracted on this camera.
     */
    CameraIndexedFeatures RetrieveFeatures(const std::vector<FeatureTrack>& tracks, const uint64_t frame_id) const;

    /**
     * @brief retrieve marginalized and `GOOD` tracks
     * @details for a track whoes newest measurement is out of sliding window, it will be marginalized from sliding
     * window. if it has been triangulated and well optimized, we record it for offline global optimization later.
     *
     * @param state tracker state
     * @param optimized_values optimized values in sliding window
     * @param compensated_values compensated values in sliding window
     * @return tracks
     */
    void GetMarginalizedGoodTracks(Tracker::State& state, const Values& optimized_values,
                                   const Values& compensated_value, std::vector<FeatureTrack>& tracks) const;

    /**
     * @brief retrieve marginalized and `GOOD` parking slot tracks
     * @details for a track whoes newest measurement is out of sliding window, it will be marginalized from sliding
     * window. if it has been triangulated and well optimized, we record it for offline global optimization later.
     *
     * @param state parking slot tracker state
     * @param optimized_values optimized values in sliding window
     * @param compensated_values compensated values in sliding window
     * @return parking slot tracks
     */
    std::vector<semantic::ParkingSlotTrack>
    GetMarginalizedGoodParkingSlotTracks(const semantic::DataAssociation::State& state, const Values& optimized_values,
                                         const Values& compensated_value) const;

    /**
     * @brief save mapping data(values, tracks, raw measurement in sliding window)
     */
    void SaveMappingDataInSlidingWindow(const SlidingWindowState& sliding_window_state);

    /**
     * @brief check if stop overtime during online mapping
     */
    bool CheckIfStoppingOvertime(const std::vector<ChassisState>& chassis_states);

    /**
     * @brief main thread function for offline mapping data saving
     * @param[in] frequency the frequency of the offline map data saving thread
     */
    void OfflineMappingDataSavingThreadFunc(const Scalar frequency);

    /**
     * @brief mainly do parking slot association
     */
    void ParkingSlotAssociation();

    /**
     * @brief variables
     */
    const Parameters             parameters_;            ///< vslam parameters
    std::shared_ptr<std::thread> estimator_thread_;      ///< vslam estimator thread
    MapDatabaseManager           map_database_manager_;  ///< map database manager

    // accumulated mappoints in sliding window
    // key: landmark id, value: mappoint
    IndexedMappoints indexed_mappoints_;

    // accumulated parking slots in sliding window
    // key: track id, value: parking slot
    IndexedParkingSlots indexed_parking_slots_;

    // accumulated features in sliding window.
    // key: frame id, value: camera id to features map
    std::unordered_map<uint64_t, CameraIndexedFeatures> indexed_features_;

    // accumulated corrected measurements in sliding window.
    // key: frame id, value: corrected measurement
    std::unordered_map<uint64_t, CorrectedMeasurement> indexed_corrected_measurement_;

    /// vehicle standing time when online mapping
    holo::float32_t vehicle_standing_time_;

    /// path length of online mapping
    holo::float32_t online_mapping_length_;

    /// online mapping time
    holo::float32_t online_mapping_time_;

    /// @brief thread to save mapping data
    std::shared_ptr<std::thread> map_data_saving_thread_;

    /// @brief offline mapping database buffer
    std::mutex                                 offline_mapping_data_buffer_mutex_;
    boost::circular_buffer<OfflineMappingData> offline_mapping_data_buffer_;

    /// @brief last keyframe pose
    boost::optional<Pose3> optional_last_keyfram_pose_;

    /// @brief parking slot tracks state
    semantic::DataAssociation::State semantic_state_;

};  // Mapping

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_MAPPING_MAPPING_H_
