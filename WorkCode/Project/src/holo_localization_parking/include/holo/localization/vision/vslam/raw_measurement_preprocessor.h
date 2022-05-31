/*!
 * \brief raw measurement preprocessor class header file in vslam
 * \author Feng. Li, lifeng@holomatic.com
 * \date May-21-2020
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_RAW_MEASUREMENT_PREPROCESSOR_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_RAW_MEASUREMENT_PREPROCESSOR_H_

#include <holo/localization/vision/vslam/feature_associator.h>
#include <holo/localization/vision/vslam/graph_builder.h>
#include <holo/localization/vision/vslam/semantic/data_association.h>
#include <holo/localization/vision/vslam/sliding_window_state.h>
#include <holo/localization/vision/vslam/wheel_integration.h>

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
 * @brief raw measurement preprocessor class
 *
 * @details this class is mainly responsible for preprocessing raw sensor measurement. specifically, it will convert the
 * input RawMeasurements to PreprocessedMeasurements according to the following steps:
 *          1. image undistortion and feature extraction.
 *          2. estimated state(p v q) prediction by imu integration.
 *          3. imu preintegration.
 *          4. velocity scale correction.
 *          5. visual feature association.
 *          6. vehicle speed checking.(zero speed checking, motion conflict detction with imu / camera, etc)
 *          7. outlier rejection for global observed source if given(gps position, integrated navigation state, etc).
 *          8. convert gps position to UTM coordinate
 */

class RawMeasurementPreprocessor
{
public:
    /**
     * @brief define parameters
     */
    struct Parameters
    {
        /// @brief define imu preintegration parameters
        const PreintegrationParamsPtr pim_params;

        /// @brief wheel integration parameters
        const WheelIntegrationBase::Parameters wim_params;

        /// @brief semantic data association parameters
        semantic::DataAssociation::Parameters sda_params;

        /// @brief vehicle speed correction coefficients
        const Vector2 speed_correction_coeff;

        /// @brief slope threshold to enable slipping checking.[degree]
        const Scalar slope_threshold;

        /// @brief global matching inliers threshold to extend global match window size
        const uint32_t inliers_threshold;

        /// @brief body to imu extrinsic
        const Pose3 T_bi;

        /**
         * @brief Construct a new Parameters object
         * @param _builder_params graph builder parameters
         * @param _pim_params imu preintegration parameters
         * @param _wim_params wheel integration parameters
         * @param _lag_size number of frame in the fixed lag
         * @param _isam2_params isam2 parameters
         * @param _gdm global descriptor matching parameters
         */
        Parameters(const PreintegrationParamsPtr& _pim_params, const WheelIntegrationBase::Parameters _wim_params,
                   const semantic::DataAssociation::Parameters& _sda_params, const Vector2& _speed_correction_coeff,
                   Scalar _slope_threshold = 10.0, uint32_t _inliers_threshold = 100,
                   const Pose3& _T_bi = Pose3::Identity())
          : pim_params(_pim_params)
          , wim_params(_wim_params)
          , sda_params(_sda_params)
          , speed_correction_coeff(_speed_correction_coeff)
          , slope_threshold(_slope_threshold)
          , inliers_threshold(_inliers_threshold)
          , T_bi(_T_bi)
        {
        }

        /**
         * @brief output stream parameters
         *
         * @param os std::ostream&
         * @param parameters
         * @return std::ostream&
         */
        friend std::ostream& operator<<(std::ostream& os, const Parameters& parameters)
        {
            os << "RawMeasurementPreprocessorParams: \n"
               << "\n sda_parameters " << parameters.sda_params
               << "\n speed_correction_coeff = " << parameters.speed_correction_coeff.Transpose() << "\n"
               << "\n slope_threshold = " << parameters.slope_threshold << "\n inliers_threshold"
               << parameters.inliers_threshold << "\n body imu extrinsic: " << parameters.T_bi << std::endl;

            // @note gtsam only provides print() function
            parameters.pim_params->print("pim parameters");

            return os;
        }

        /**
         * @brief load from yaml
         *
         * @param node
         * @return Parameters
         */
        static Parameters LoadFromYaml(const holo::yaml::Node& node);

        /// @brief load speed correction coefficients from yaml
        static Vector2 LoadSpeedCorrectionCoeff(const holo::yaml::Node& node);

        /// @brief load wheel integration from yaml
        static WheelIntegrationBase::Parameters LoadWheelIntegrationParams(const holo::yaml::Node& node);

        /**
         * @brief static example parameters for unit test
         *
         * @return Parameters
         */
        static Parameters Example();
    };

    /**
     * @brief constructor with parameters
     */
    RawMeasurementPreprocessor(const Parameters& parameters, const CameraParameters::Ptr& camera_parameters,
                               const FeatureAssociator::Parameters& fa_params);

    /**
     * @brief destructor
     */
    ~RawMeasurementPreprocessor()
    {
    }

    /**
     * @brief create the initial factor measurements
     *
     * @param initial_vehicle_state the initial vehicle state
     * @param initial_frame_id initial frame id
     * @param initial_measurement initial raw measurement
     * @return pair of initial factor measurements and the CorrectedMeasurement of initial raw measurement
     */
    std::pair<CorrectedMeasurement, FactorMeasurements> Initialize(const VehicleState&   initial_vehicle_state,
                                                                   const uint64_t        initial_frame_id,
                                                                   const RawMeasurement& initial_measurement) const;

    /**
     * @brief main computing function
     *
     * @param old_state old_state old sliding window state
     * @param new_raw_measurement new_raw_measurement
     * @param new_frame_id the new frame id
     * @return pair of new factor measurements and corrected measurements
     */
    std::pair<CorrectedMeasurement, FactorMeasurements> Run(const SlidingWindowState& old_state,
                                                            const uint64_t            new_frame_id,
                                                            const RawMeasurement&     new_raw_measurement) const;

    /**
     * @brief return parameters
     *
     * @return const Parameters&
     */
    const Parameters& Params() const;

    /**
     * @brief create new pre-integrated measurements with imus and bias
     *
     * @param imus imus
     * @param bias bias
     * @return new pre-integrated measurements with imus
     */
    PreintegratedImuMeasurements CreateNewPim(const std::vector<Imu>&             imus,
                                              const gtsam::imuBias::ConstantBias& bias) const;

    /**
     * @brief check if the vehicle is stationary
     * @details if the wheel pulse do not update through all the vehicle infos, we think the vehicle is stationary
     *
     * @param chassis_states chassis states measurements
     * @return true if the vehicle is stationary, else return false.
     */
    bool IsZeroSpeedState(const std::vector<ChassisState>& chassis_states) const;

    /**
     * @brief convert point features to features defined in vslam system.
     * @details the 2d position of each point feature will be unproject as a bearing vector with intrinsic
     *
     * @param multi_point_feature_list the raw point features measaurement recieved from cmw
     * @param multi_obstacle_list newest multi obstacle list
     * @param images images correspond to the detection results
     * @return features
     */
    std::vector<Features> ConvertPointFeatures(const std::vector<PointFeaturefList_ST*>& multi_point_feature_list,
                                               const std::vector<ObstaclePtrList>&       multi_obstacle_list,
                                               const std::vector<Image>&                 images) const;

    /**
     * @brief convert multi obstacle ptr list to cv mats
     *
     * @param multi_obstacle_list detection results of multi images which have the same timestamp
     * @param images images correspond to the detection results
     * @return multi semantic mat
     */
    std::vector<cv::Mat> ConvertMulitObstaclePtrListToCvMats(const std::vector<ObstaclePtrList>& multi_obstacle_list,
                                                             const std::vector<Image>&           images) const;

    /**
     * @brief convert raw imu measurements to  another frame
     *
     * @param input_imus the input imus to be converted
     * @param extrinsic transformation from target frame to imu frame
     * @return imu measurements in target frame
     */
    std::vector<Imu> ConvertImuMeasurements(const std::vector<Imu>& input_imus, const Pose3& extrinsic) const;

    /**
     * @brief provide a interface to do parking slot association
     *
     * @param semantic_state parking slot track state
     * @param parking_slot_frame new parking slot frame measurement
     * @param wTb transformation from body frame to world frame
     * @param frame_id frame id
     */
    void GetParkingSlotTrackResult(semantic::DataAssociation::State& semantic_state,
                                   const ParkingSlotFrameType& parking_slot_frame, const Pose3& wTb, uint64_t frame_id);

private:
    /**
     * @brief image preprocess
     * @details undistort image.
     *
     * @param new_raw_measurement raw measurements
     * @return undistorted image
     */
    std::vector<Image> ImagePreprocess(const RawMeasurement& new_raw_measurement) const;

    /**
     * @brief create new pre-integrated measurements with new imus
     *
     * @param old_values old_values
     * @param new_frame_index old_frame_index
     * @param new_imus new_imus
     * @return new pre-integrated measurements with new imus
     */
    PreintegratedImuMeasurements CreateNewPim(const Values& old_values, const uint64_t new_frame_index,
                                              const std::vector<Imu>& new_imus) const;

    /**
     * @brief create new pre-integrated ahrs measurements with new imus
     *
     * @param old_values old_values
     * @param new_frame_index old_frame_index
     * @param new_imus new_imus
     * @return new pre-integrated ahrs measurements with new imus
     */
    PreintegratedAhrsMeasurements CreateNewPam(const Values& old_values, const uint64_t new_frame_index,
                                               const std::vector<Imu>& new_imus) const;

    /**
     * @brief predict new vehicle state values
     * @details predicted by PIM
     *
     * @param old_values old_values
     * @param new_frame_index new_frame_index
     * @param new_pim new_pim
     * @return Values new_values
     */
    Values PredictVehicleStateValues(const Values& old_values, const uint64_t new_frame_index,
                                     const PreintegratedImuMeasurements& new_pim) const;

    /**
     * @brief predict new vehicle state values
     * @details predicted by WIM
     *
     * @param old_values old_values
     * @param new_frame_index new_frame_index
     * @param new_wim new_wim
     * @return Values new_values
     */
    Values PredictVehicleStateValues(const Values& old_values, const uint64_t new_frame_index,
                                     const WheelIntegrationMeasurement& new_wim) const;

    /**
     * @brief convert gps position from LL to UTM coordinate
     *
     * @param position ll position
     * @return gps position in utm coordinate
     */
    UtmPosition LL2UTM(const GnssPosition& position) const;

    /**
     * @brief checking reliability of the vehicle speed measurement
     * @details vehicle speed is NOT completely reliable when:
     *          1. the vehicle is NOT stationary while the vehicle speed is almost zero.
     *          2. the vehicle is moving through an uneven ground.
     *          3. the sign of vehicle speed and predicted speed by imu integration are diametrically opposed
     *
     * @param chassis_states chassis state  measurements
     * @param imus imu measurements
     * @param is_zero_speed_state indicate if the vehicle is stationary
     * @param predicted_values the predicted values by imu integration
     * @param frame_id the frame id
     * @return status of the vehicle speed measurement.
     */
    VelocityMeasurementReliability VehicleSpeedReliabilityChecking(const std::vector<ChassisState>& chassis_states,
                                                                   const std::vector<Imu>&          imus,
                                                                   const bool                       is_zero_speed_state,
                                                                   const Values&                    predicted_values,
                                                                   const uint64_t                   frame_id) const;

    /**
     * @brief correct chassis state
     *
     * @param chassis_states chassis states
     * @param is_zero_speed_state flat which indicate if the vehicle is stationary
     * @return corrected chassis state
     */
    std::vector<ChassisState> CorrectChassisState(const std::vector<ChassisState>& chassis_states,
                                                  const bool                       is_zero_speed_state) const;

    /**
     * @brief calcu essential matrixt from tracks
     *
     */
    EssentialMatrixMeasurements GetEssentialMatrixMeasurements(const std::vector<FeatureTrack>& tracks,
                                                               const Values& values, uint64_t frame_id,
                                                               Scalar min_baseline_distance, Scalar largest_angle,
                                                               uint64_t min_train_feaures_num) const;

    /// @brief parameteres
    const Parameters parameters_;

    /// @brief shared_ptr of camera parameters
    CameraParameters::Ptr camera_parameters_;

    /// @brief image undistorters for multi camera vslam system
    std::vector<ImageUndistortionPtr> undistorters_;

    /// @brief feature associator
    FeatureAssociator feature_associator_;

    /// @brief semantic data association
    semantic::DataAssociation::Ptr semantic_associator_;

    /// @brief camera id to camera intrinsic
    std::unordered_map<uint16_t, cv::Mat> camera_id_to_cv_K_;

};  // class RawMeasurementPreprocessor

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_RAW_MEASUREMENT_PREPROCESSOR_H_
