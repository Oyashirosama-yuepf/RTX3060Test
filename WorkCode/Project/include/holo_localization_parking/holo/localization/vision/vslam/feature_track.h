/*!
 * \brief feature track class header file in vslam
 * \author Yanwei. Du, duyanwei@holomatic.com
 * \date Feb-11-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_FEATURE_TRACK_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_FEATURE_TRACK_H_

#include <holo/localization/vision/vslam/common_types.h>
#include <holo/localization/vision/vslam/essential_matrix_factor.h>
#include <holo/localization/vision/vslam/factor_graph.h>
#include <holo/localization/vision/vslam/landmark.h>
#include <holo/localization/vision/vslam/unit3_factor.h>

#include <memory>
#include <vector>

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
 * @brief feature track class
 *
 * @details It contains many feature measurements that belong to one track
 */
class FeatureTrack
{
public:
    /**
     * @brief smart pointer
     */
    typedef std::shared_ptr<FeatureTrack>       Ptr;
    typedef std::shared_ptr<const FeatureTrack> ConstPtr;

    /**
     * @brief typedef camera index to feature map
     * @details key: camera index, value: Feature
     */
    typedef std::unordered_map<uint16_t, Feature> CameraIndexedFeature;

    /**
     * @brief typedef single feature measurement
     * @details key: frame_id, value: camera index to feature map
     */
    typedef std::pair<uint64_t, CameraIndexedFeature> Measurement;

    /**
     * @brief parameters
     */
    struct Parameters
    {
        /**
         * @brief smart pointer
         */
        typedef std::shared_ptr<Parameters>       Ptr;
        typedef std::shared_ptr<const Parameters> ConstPtr;

        // If true, rethrows Cheirality exceptions (default: false)
        const bool throw_cheirality;

        // If true, prints text for Cheirality exceptions (default: false)
        const bool verbose_cheirality;

        // constructor
        Parameters(const bool _throw_cheirality = false, const bool _verbose_cheirality = false)
          : throw_cheirality(_throw_cheirality), verbose_cheirality(_verbose_cheirality)
        {
        }

        // output stream
        friend std::ostream& operator<<(std::ostream& os, const Parameters& parameters)
        {
            os << "FeatureTrackParameters: "
               << "\n throw_cheirality = " << parameters.throw_cheirality
               << "\n verbose_cheirality = " << parameters.verbose_cheirality << std::endl;
            return os;
        }

        // static method to generate example for unit test
        static Parameters Example()
        {
            return Parameters();
        }
    };

    /**
     * @brief define state of track
     */
    enum class State
    {
        CANDIDATE               = 0,  ///< newly detected feature
        FRESH                   = 1,  ///< being evaluated for upgrading to live track
        LIVE                    = 2,  ///< can be used for estimation
        FINISHED                = 3,  ///< track that has been finished tracking
        BAD_BEFORE_OPTIMIZATION = 4,  ///< rejected with initial pim
        BAD_AFTER_OPTIMIZATION  = 5,  ///< rejected with optimzied values of pose
        DEAD                    = 6,  ///< track with this state will be removed from sliding window.
    };                                // State

    /**
     * @brief constructor with track id and the first measurement
     * @param[in] parameters
     * @param[in] id track id
     * @param[in] first_measurement the first measurement
     */
    FeatureTrack(const Parameters::ConstPtr& parameters, const CameraParameters::Ptr& camera_parameters,
                 const uint64_t id, const Measurement& first_measurement)
      : FeatureTrack(parameters, camera_parameters, id, {first_measurement}, State::CANDIDATE)
    {
    }

    /**
     * @brief constructor with track id and measurements
     * @param[in] parameters
     * @param[in] camera parameters
     * @param[in] id track id
     * @param[in] measurements multiple measurements in a track
     * @param[in] state track state
     * @param[in] landmark corresponded landmark in vio map frame
     */
    FeatureTrack(const Parameters::ConstPtr& parameters, const CameraParameters::Ptr& camera_parameters,
                 const uint64_t id, const std::vector<Measurement>& measurements, const State state,
                 const boost::optional<Landmark>& landmark = boost::none)
      : parameters_(parameters)
      , camera_parameters_(camera_parameters)
      , id_(id)
      , measurements_(measurements)
      , state_(state)
      , landmark_(landmark)
    {
    }

    /**
     * @brief return parameters
     */
    const Parameters& Params() const;

    /**
     * @brief return camera parameters
     */
    const CameraParameters::Ptr& CameraParams() const;

    /**
     * @brief return the id of this track
     */
    uint64_t Id() const;

    /**
     * @brief return all feature measurements
     */
    const std::vector<Measurement>& Measurements() const;

    /**
     * @brief return the state of track
     */
    State GetState() const;

    /**
     * @brief get Landmark
     */
    const boost::optional<Landmark>& GetLandmark() const;

    /**
     * @brief return the length of a track
     */
    uint64_t Length() const;

    /**
     * @brief return the semantic label of a track
     */
    SemanticLabel GetLabel() const;

    /**
     * @brief return single feature measurement
     * @throws std::out_of_range Thrown if query index is larger than measurements_'s size.
     */
    const Measurement& Measurements(const uint64_t index) const;

    /**
     * @brief return the newest feature measurement in track
     */
    const Measurement& NewestMeasurement() const;

    /**
     * @brief return the oldest feature measurement in track
     */
    const Measurement& OldestMeasurement() const;

    /**
     * @brief create new track when adding newest measurement
     *
     * @param frame_id observed frame
     * @param feature observed feature
     * @return new a feature track
     */
    FeatureTrack CreateNewTrackByAddingNewestMeasurement(const uint64_t frame_id, const Feature& feature) const;

    /**
     * @brief add newest measurement to this track
     *
     * @param frame_id observed frame
     * @param feature observed feature
     */
    void AddNewestMeasurement(const uint64_t frame_id, const Feature& feature);

    /**
     * @brief create new track by updating its state
     * @throws std::runtime_error Thrown if update state to FRESH, but do not give landmark point
     *
     * @param[in] state track_state
     * @param[in] optional_point it must evaluate to true if and only if
     *            new_state is "FRESH"
     */
    FeatureTrack CreateNewTrackByUpdatingState(
        const State new_state, const boost::optional<gtsam::Point3>& optional_point = boost::none) const;

    /**
     * @brief updating this track's state
     * @note(Feng. Li 2020-05-28) NOT FP!!! for efficiency reason!!!!
     * @throws std::runtime_error Thrown if update state to FRESH, but do not give landmark point
     *
     * @param state track_state
     * @param optional_point it must evaluate to true if and only if new_state is "FRESH"
     */
    void UpdatingState(const State new_state, const boost::optional<gtsam::Point3>& optional_point = boost::none);

    /**
     * @brief create new track
     * @param parameters track parameters
     * @param camera_parameters camera parameters
     * @param measurement the first feature measurement
     */
    static FeatureTrack CreateNewTrack(const Parameters::ConstPtr&  parameters,
                                       const CameraParameters::Ptr& camera_parameters, const Measurement& measurement);

    /**
     * @brief predict new point using latest two track measurements
     * @details it predic new point on each camera independently
     *
     * @return key: camera index, value: predicted new point
     */
    std::unordered_map<uint16_t, cv::Point2f> PredictNewPoints() const;

    /**
     * @brief generate unit3 factors
     *
     * @details API for graph builder
     */
    std::vector<Unit3FactorPtr> Unit3Factors(const Values& values                                = {},
                                             const Scalar  minimum_measurement_distance_interval = 0.0,
                                             const Scalar  minimum_measurement_angle_interval    = 0.0) const;

    std::vector<EssentialMatrixFactorPtr> EssentialMatrixFactors(
        uint64_t current_frame_id, const Values& values = {}, const Scalar minimum_measurement_distance_interval = 1.0,
        const Scalar maximum_measurement_angle_interval = 15.0) const;

    /**
     * @brief compute feature track's reprojection error
     * @param[in] values includes optimized landmark position and camera poses
     * @param[in] measurement_index measurement index (default -1, compute mean error of all measurements)
     * @param[in] camera_index camera index (default -1)
     * return the boost optional unit3 reprojection error
     */
    boost::optional<Scalar> ComputeReprojectionError(const Values& values, int64_t measurement_index = -1,
                                                     int16_t camera_index = -1) const;

    /**
     * @brief compute feature track's reprojection error
     * @param[in] values includes optimized landmark position and camera poses
     * @param[in] measurement_index measurement index (default -1, compute mean error of all measurements)
     * @param[in] camera_index camera index (default -1)
     * return the boost optional piexl reprojection error
     */
    boost::optional<Scalar> ComputePiexlReprojectionError(const Values& values, int64_t measurement_index = -1,
                                                          int16_t camera_index = -1) const;

    /**
     * @brief output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const FeatureTrack& ft)
    {
        os << "FeatureTrack:"
           << "\n id = " << ft.id_ << "\n state = " << (uint32_t)ft.state_;

        if (ft.landmark_)
        {
            os << "\n landmark id = " << (ft.landmark_)->Id() << "\n landmark point = " << (ft.landmark_)->Point();
        }
        else
        {
            os << "\n no valid landmark";
        }

        os << "\n measurements = ";
        for (const auto& m : ft.measurements_)
        {
            os << "(" << m.first << ", ";
            for (const auto& indexed_feature : m.second)
            {
                os << indexed_feature.first << ", " << indexed_feature.second.image_point << "), ";
            }
        }
        os << std::endl;
        return os;
    }
    // @brief handy function to create unit3 factor
    void AddUnit3Factor(FactorGraph& graph, const uint64_t index) const;

    // @brief handy function to create unit3 factor
    std::vector<Unit3FactorPtr> CreateUnit3Factor(const uint64_t index) const;

private:
    Parameters::ConstPtr      parameters_;         ///< parameters
    CameraParameters::Ptr     camera_parameters_;  ///< shared_ptr of camera parameters
    uint64_t                  id_;                 ///< track id
    std::vector<Measurement>  measurements_;       ///< multiple measurements
    State                     state_;              ///< track state
    boost::optional<Landmark> landmark_;           ///< landmark

    static uint64_t   next_id_;              ///< id for next track
    static std::mutex feature_track_mutex_;  ///< feature track mutex

};  // FeatureTrack

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_FEATURE_TRACK_H_
