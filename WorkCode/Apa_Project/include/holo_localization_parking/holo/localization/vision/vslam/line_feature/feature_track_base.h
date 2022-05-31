/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file feature_track_base.h
 * @brief This header file defines feature track base class.
 * @author MaYufei(mayufei@holomatic.com)
 * @date "2022-03-07"
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_LINE_FEATURE_FEATURE_TRACK_BASE_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_LINE_FEATURE_FEATURE_TRACK_BASE_H_

#include <holo/localization/vision/vslam/common_types.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
/**
 * @brief feature track base
 * @details It contains many feature measurements that belong to one track
 * @tparam T1 tracked feature type
 * @tparam T2 tracked feature landmark
 */
template <typename T1, typename T2>
class FeatureTrackBase
{
public:
    /**
     * @brief smart pointer
     */
    typedef std::shared_ptr<T1>                     Ptr;
    typedef std::shared_ptr<const FeatureTrackBase> ConstPtr;

    /**
     * @brief typedef camera index to feature map
     * @details key: camera index, value: Feature
     */
    typedef std::unordered_map<uint16_t, T1> CameraIndexedFeature;

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
            os << "FeatureTrackBaseParameters: "
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
    FeatureTrackBase(const Parameters::ConstPtr& parameters, const CameraParameters::Ptr& camera_parameters,
                     const uint64_t id, const Measurement& first_measurement)
      : FeatureTrackBase(parameters, camera_parameters, id, {first_measurement}, State::CANDIDATE)
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
    FeatureTrackBase(const Parameters::ConstPtr& parameters, const CameraParameters::Ptr& camera_parameters,
                     const uint64_t id, const std::vector<Measurement>& measurements, const State state,
                     const boost::optional<T2>& landmark = boost::none)
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
    const boost::optional<T2>& GetLandmark() const;

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
    FeatureTrackBase CreateNewTrackByAddingNewestMeasurement(const uint64_t frame_id, const T1& feature) const;

    /**
     * @brief add newest measurement to this track
     *
     * @param frame_id observed frame
     * @param feature observed feature
     */
    void AddNewestMeasurement(const uint64_t frame_id, const T1& feature);

    /**
     * @brief create new track by updating its state
     * @throws std::runtime_error Thrown if update state to FRESH, but do not give landmark point
     *
     * @param[in] state track_state
     * @param[in] optional_point it must evaluate to true if and only if
     *            new_state is "FRESH"
     */
    FeatureTrackBase CreateNewTrackByUpdatingState(
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
    static FeatureTrackBase CreateNewTrack(const Parameters::ConstPtr&  parameters,
                                           const CameraParameters::Ptr& camera_parameters,
                                           const Measurement&           measurement);

protected:
    Parameters::ConstPtr     parameters_;           ///< parameters
    CameraParameters::Ptr    camera_parameters_;    ///< shared_ptr of camera parameters
    uint64_t                 id_;                   ///< track id
    std::vector<Measurement> measurements_;         ///< multiple measurements
    State                    state_;                ///< track state
    static uint64_t          next_id_;              ///< id for next track
    static std::mutex        feature_track_mutex_;  ///< feature track mutex
};
}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif