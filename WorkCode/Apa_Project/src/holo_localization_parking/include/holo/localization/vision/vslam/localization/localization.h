/*!
 * \brief visual localization class header file in vslam
 * \author Yanwei. Du duyanwei@holomatic.com
 * \author Feng. Li lifeng@holomatic.com
 * \date Mar-18-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_LOCALIZATION_LOCALIZATION_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_LOCALIZATION_LOCALIZATION_H_

#include <holo/localization/vision/vslam/mapping/map_database_manager.h>
#include <holo/localization/vision/vslam/mapping/sub_mapping.h>
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
 * @brief visual localization main estimator class
 *
 * @details all the threads will be created in this class
 */
class Localization : public VSLAMBase
{
public:
    /**
     * @brief handy typedefs
     */
    using Base                  = VSLAMBase;
    using SubMappingMeasurement = SubMapping::Measurement;

    /**
     * @brief vslam parameters
     */
    struct Parameters : public Base::Parameters
    {
        /// @brief frequency is defined in Base class

        /// @brief the minimum update frequency of vslam thread required by imu prediction thread.
        /// @details if vslam thread's update frequency is lower than this threshold, imu prediction thread will not
        /// predict untill vslam update again.
        Scalar minimum_acceptable_frequency;

        /// @brief imu prediction frequency
        Scalar imu_prediction_frequency;

        /// @brief initializer parameters
        Initializer::Parameters initializer_params;

        /// @brief feature association parameters
        FeatureAssociator::Parameters fa_params;

        /// @brief visual relocalization parameters
        Relocalization::Parameters reloc_params;

        /// @brief online sub mapping parameters
        SubMapping::Parameters sub_mapping_params;

        /// @brief map database manager params
        MapDatabaseManager::Parameters mdm_params;

        /// @brief flag which indicate if enable sub mapping thread
        bool enable_sub_mapping;

        /// @brief flag which indicate if predicte nav state by pure imu integration
        bool predict_navstate_by_pure_imu_integration;

        /// @brief constructor
        Parameters(const Base::Parameters& base_params, const Scalar _minimum_acceptable_frequency,
                   const Scalar _imu_prediction_frequency, const Initializer::Parameters& _initializer_params,
                   const FeatureAssociator::Parameters& _fa_params, const Relocalization::Parameters& _reloc_params,
                   const SubMapping::Parameters& _sub_mapping_params, const MapDatabaseManager::Parameters& _mdm_params,
                   const bool _enable_sub_mapping = false, const bool _predict_navstate_by_pure_imu_integration = true)
          : Base::Parameters(base_params)
          , minimum_acceptable_frequency(_minimum_acceptable_frequency)
          , imu_prediction_frequency(_imu_prediction_frequency)
          , initializer_params(_initializer_params)
          , fa_params(_fa_params)
          , reloc_params(_reloc_params)
          , sub_mapping_params(_sub_mapping_params)
          , mdm_params(_mdm_params)
          , enable_sub_mapping(_enable_sub_mapping)
          , predict_navstate_by_pure_imu_integration(_predict_navstate_by_pure_imu_integration)
        {
        }

        // output stream
        friend std::ostream& operator<<(std::ostream& os, const Parameters& parameters)
        {
            os << static_cast<Base::Parameters>(parameters)
               << "\nLocalizationParameters:\n  minimum_acceptable_frequency = "
               << parameters.minimum_acceptable_frequency
               << "\n  imu_prediction_frequency = " << parameters.imu_prediction_frequency << "\n "
               << parameters.initializer_params << parameters.fa_params << parameters.reloc_params
               << parameters.sub_mapping_params << parameters.mdm_params
               << "enable_sub_mapping = " << parameters.enable_sub_mapping
               << "\n  predict_navstate_by_pure_imu_integration = "
               << parameters.predict_navstate_by_pure_imu_integration << "\n";
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
    Localization(const Parameters& parameters);

    /**
     * @brief destructor
     */
    virtual ~Localization();

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

    /**
     * @brief Set the Visualizer object
     *
     * @param visualizer
     */
    virtual void SetVisualizer(std::shared_ptr<vslam::Visualizer> visualizer) override;

protected:
    /**
     * @brief post processing
     *
     * @details it will be called after EstimationCore()
     */
    virtual bool postProcess() override;

    /**
     * @brief reset LocalizationVSLAM when there is serious error
     * @note!!! 1. only reset LocalizationVSLAM because other modules are FP
     *          2. imu prediction thread will be reset when new SlidingWindowState is updated
     *          because there is no memeber variable for this thread and the internal variable
     *          in the thead function will be reset when new SlidingWindowState comes
     *          3. visualizer thread will be reset when new SlidingWindowState is updated
     *          it will check whether LocalizationVSLAM is reset by frame_id == 0 in the SlidingWindowState
     */
    void Reset();

    /**
     * @brief process and publish point clouds
     * @details localization module will publish two kinds of point clouds insides this function.
     *          1. all landmarks retained in curernt sliding window state
     *          2. associated global mappoint with prebuilt map
     *
     * @param state
     * @return inlier number of associated global mappoint
     */
    uint32_t PublishPointClouds(const SlidingWindowState& state) const;

    /**
     * @brief publish prebuild map to ROS
     */
    void PublishPrebuiltMap() const;

    /**
     * @brief prediction thread function
     * @detials the frequency of VSLAM is around 10Hz. however, a higher frequency DR odometry
     *          is requried by other modules. this thread aims to do prediction with imu based on the vslam Odometry
     *  VSLAM odo: V|          |
     *  Imu: |||||||||||||||||
     *  DR odo:   |||||||||||(V+Imu)
     * @param[in] frequency the frequency of the prediction thread
     */
    void PredictionThreadFunc(const Scalar frequency);

    /**
     * @brief do prediction with imu
     * @param[in] newest_vehicle_state the newest estimated vehicle state from VSLAM
     * @param[in] imus the imus from the timestamp of the newest_vehicle_state to current time
     * @return the predicted VehicleState
     */
    VehicleState ImuPrediction(const VehicleState& newest_vehicle_state, const std::vector<Imu>& imus) const;

    /**
     * @brief do navigation state prediction with imu and vehicle info
     * @param newest_vehicle_state the newest estimated vehicle state from VSLAM
     * @param imus all imus between the timestamp of the ${newest_vehicle_state} and current time.
     * @param chassis_states all chassis states between the timestamp of the ${newest_vehicle_state} and current time
     * @return the predicted VehicleState
     */
    VehicleState NavigationStatePrediction(gtsam::ISAM2& isam, uint64_t& new_frame_id,
                                           const VehicleState&                  newest_vehicle_state,
                                           const std::vector<std::vector<Imu>>& imu_blocks,
                                           const std::vector<ChassisState>&     chassis_states) const;

    /**
     * @brief do navigation state prediction with imu and vehicle info
     * @return the predicted VehicleState
     */
    VehicleState NavigationStatePrediction(gtsam::ISAM2& isam, uint64_t& new_frame_id,
                                           const VehicleState&                           newest_vehicle_state,
                                           const std::vector<std::vector<Imu>>&          imu_blocks,
                                           const std::vector<std::vector<ChassisState>>& chassis_state_blocks) const;

    /**
     * @brief publish imu prediction result
     * @param[in] vehicle_state estimated vehicle state
     * @param[in] current_time timestamp corresponding to vehicle_state
     * @param[in] sequence_counter counter of the published VehicleState
     * @param[in] vslam_is_good flag which indicate if the vslam thread is work well or not
     */
    void PublishImuPredictionResult(const VehicleState& vehicle_state, const Timestamp& current_time,
                                    const uint64_t sequence_counter, bool vslam_is_good) const;

    /**
     * @brief update prebuilt map with new maps
     * @param[in] old_point_cloud_map old point cloud map
     * @param[in] new_map the new map
     * @return updated point cloud map
     */
    PointCloudXYZIRRgbSt UpdatePrebuiltCloudMap(const PointCloudXYZIRRgbSt& old_point_cloud_map,
                                                const Map&                  new_map) const;

    /**
     * @brief add new measurement to sub mapping thread
     * @param[in] corrected_measurement the newest corrected measurement
     * @param[in] factor_measurements the newest factor measurements
     * @param[in] mpm_inlier_indexes the mpm index set which pass the reprojection error check
     */
    void AddNewMeasurementToSubMapping(const CorrectedMeasurement& corrected_measurement,
                                       const FactorMeasurements&   factor_measurements,
                                       const std::set<uint64_t>&   mpm_inlier_indexes);

    /**
     * @brief update matched map reprojection errors
     * @param[in] mpms the map projection measurements of the current frame
     * @param[in] xvb_values the xvb_values
     *
     * @return the mpm index set which pass the reprojection error check
     */
    std::set<uint64_t> ComputeReprojectionError(const std::vector<MapProjectionMeasurement>& mpms,
                                                const Values&                                xvb_values) const;

    /**
     * @brief update prebuilt mappoints with new remember rate
     * @param[in] prebuilt_map the prebuild map
     */
    void RemoveMappointsWithRememberRate(const MapPtr& prebuilt_map) const;

    /**
     * @brief variables
     */
    const Parameters             parameters_;        ///< vslam parameters
    std::shared_ptr<std::thread> estimator_thread_;  ///< vslam estimator thread

    /**
     * @brief imu prediction thread
     */
    std::shared_ptr<std::thread> imu_prediction_thread_;
    std::atomic<bool>            is_imu_prediction_running_;

    /// @brief visualization map
    /// @details visualization_map_ is the PointCloud type of the prebuilt map
    PointCloudXYZIRRgbSt visualization_map_;

    // prebuilt map
    MapPtr prebuilt_map_;

    // prebuilt slot map
    SlotMapPtr prebuilt_slot_map_;

    // the new maps and frames databases are built by sub mapping thread
    SubMappingResults new_maps_framesdatabases_;

    /// @brief variable for communication with imu prediction thread
    std::mutex   update_mutex_;
    VehicleState newest_updated_vehicle_state_;
    Timestamp    newest_updated_timestamp_;
    bool         is_vslam_updated_;
    bool         is_vslam_initialized_;

    // sub map id
    uint64_t sub_map_id_;

    /// @brief relocalization module
    Relocalization::Ptr relocalization_;

    /// sub mapping smart pointer
    SubMapping::Ptr sub_mapping_;

    /// map database manager smart pointer
    MapDatabaseManager::Ptr map_database_manager_;

    /// distance lacking matched feature points
    holo::float32_t lacking_feature_points_distance;

};  // LocalizationVSLAM

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_LOCALIZATION_LOCALIZATION_H_
