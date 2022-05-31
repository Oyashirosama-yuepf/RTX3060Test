/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ego_lane_predictor.h
 * @brief This class is used to get the lane level localization by the predicted position.
 * @author Lei Gehang (leigehang@holomatic.com)
 * @date Mar 16, 2021
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_EGO_LANE_PREDICTOR_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_EGO_LANE_PREDICTOR_H_

#include <holo/localization/tightly_coupled_fusion/common_types.h>
#include <holo/localization/tightly_coupled_fusion/lane/types.h>
#include <holo/localization/tightly_coupled_fusion/map/map_service_client_base.h>
#include <holo/localization/tightly_coupled_fusion/utils/common_functions.h>
#include <limits>

namespace holo
{
namespace localization
{
namespace tightly_coupled_fusion
{
/**
 * @addtogroup tightly_coupled_fusion
 * @{
 *
 */

/**
 * @brief This class is used to get the ego lane results by the predicted vehicle navstate.
 *
 */
class EgoLanePredictor
{
public:
    /// The handy typedef
    using MapServiceClientBase    = holo::localization::tightly_coupled_fusion::map::MapServiceClientBase;
    using MapServiceClientBasePtr = MapServiceClientBase::Ptr;
    using MapMatchingAttribute    = MapServiceClientBase::MatchingAttribute;

    using Ptr = std::shared_ptr<EgoLanePredictor>;

    /**
     * @brief This struct defines the result of the EgoLanePredictor.
     *
     */
    struct Result
    {
        /** The vehicle navstate. It may represent high precision result or low precision result. It mainly depends on
         * whether there is Enum Lane in the source member*/
        StampedAdvancedNavstate       predicted_navstate;
        OptionalT<EgoLaneInformation> ego_lane_information;  ///< The ego lane information. none means invalid.

        /**
         * @brief Construct a new Ego Lane Predictor Result object
         *
         * @param[in] _predicted_navstate The vehicle navstate
         * @param[in] _ego_lane_information The ego lane information
         */
        Result(StampedAdvancedNavstate const&       _predicted_navstate   = StampedAdvancedNavstate(),
               OptionalT<EgoLaneInformation> const& _ego_lane_information = optional::none)
          : predicted_navstate(_predicted_navstate), ego_lane_information(_ego_lane_information)
        {
        }
    };

    using Results = std::vector<Result>;

    /**
     * @brief The parameters of this ego lane predictor class.
     *
     */
    struct Parameters
    {
        /** The max accumulative distance since last high precision navstate. If the distance is less than this
         * threshold, we think we can use current navstate as the effective and believable results to request the map
         * and get the lane inforamtion. */
        Scalar max_distance_from_last_high_precision_navstate = Scalar(145.0);  ///< Unit: meter

        /**
         * @brief Static method to load parameters from yaml
         *
         * @param[in] node Yaml node
         * @return the loaded parameters
         */
        static Parameters LoadFromYaml(holo::yaml::Node const& node);

        /**
         * @brief Output stream overloading for EgoLanePredictor's parameter
         *
         * @param[in] os std::ostream&
         * @param[in] parameters Parameters
         * @return std::ostream& contains content of the given parameters
         */
        friend std::ostream& operator<<(std::ostream& os, Parameters const parameters)
        {
            os << "EgoLanePredictorParameters: \n"
               << "max_distance_from_last_high_precision_navstate = "
               << parameters.max_distance_from_last_high_precision_navstate << std::endl;
            return os;
        }
    };

    /**
     * @brief Construct a new Ego Lane Predictor object.
     *
     * @param[in] params_ The parameters.
     */
    EgoLanePredictor(Parameters const params_)
      : parameters_(params_)
      , is_initialized_(false)
      , last_predicted_navstate_()
      , accumulated_distance_from_last_high_precision_navstate_(std::numeric_limits<Scalar>::max())
    {
    }

    /**
     * @brief Run the ego lane predictor to get the ego lane results.
     *
     * @param[in] raw_measurements The ego lane raw measurements.
     * @param[in] map_service_client_ptr The map service client smart pointer to request the map.
     * @return Results including the predicted navstate and ego lane information.
     */
    Results Run(EgoLaneRawMeasurements const& raw_measurements, MapServiceClientBasePtr const& map_service_client_ptr);

    /**
     * @brief Rese this predictor.
     *
     */
    void Reset()
    {
        is_initialized_                                         = false;
        accumulated_distance_from_last_high_precision_navstate_ = std::numeric_limits<Scalar>::max();
    }

protected:
    /**
     * @brief To check whether all the timestamps of the source measurements exist in the timestamp sets.
     *
     * @tparam T The type of the source measurements.
     * @param[in] timestamp_sets The timestamp sets waiting for being checked.
     * @param[in] source_measurements The source measurements with the timestamps.
     *
     * @return It returns true if all the timestamps of the source measurements exist in the timestamp sets.
     * Otherwise, it returns false.
     */
    template <typename T>
    bool_t checkAllTimestampExist(std::set<Timestamp> const& timestamp_sets,
                                  std::vector<T> const&      source_measurements) const;

    /**
     * @brief Judge whether the raw measurement meets the requirements to estimate ego lane
     *
     * @param[in] raw_measurement The raw measurement
     * @return It returns true if it is valid and meets the requirements
     */
    bool_t isRawMeasurementValid(EgoLaneRawMeasurements const& raw_measurement) const;

    /**
     * @brief Get the aligned fusion navstates with CameraLaneBoundaries timestamps.
     *
     * @param[in] raw_measurements The ego lane raw measurments.
     * @return StampedAdvancedNavstates. They has beed aligned to the CameraLaneBoundaries timestamps.
     */
    std::vector<StampedAdvancedNavstate>
    getAlignedFusionNavstatesWithCameraLaneBoundariesTimestamp(EgoLaneRawMeasurements const& raw_measurements) const;

    /**
     * @brief Get the Ego Lane Information from the map client with the Fusion navstate.
     *
     * @param[in] fusion_navstate The fusion navstate.
     * @param[in] map_service_client_ptr The map service client ptr.
     * @return OptionalT<EgoLaneInformation>. If the fusion navsate is not in high precision, we can't get the link Id
     * and lane Id from the map client, so we set it to optional::none.
     */
    OptionalT<EgoLaneInformation> getEgoLaneInformation(StampedAdvancedNavstate const& fusion_navstate,
                                                        MapServiceClientBasePtr const& map_service_client_ptr) const;

    /**
     * @brief Judge whether the navstate is high precision based on the source.
     *
     * @param[in] navstate The Advanced navstate
     * @return It returns true if it is high precision. Otherwise, it returns false.
     */
    inline bool_t isHighPrecisionNavstate(StampedAdvancedNavstate const& navstate) const
    {
        return (static_cast<uint32_t>(navstate.GetData().GetSource()) &
                static_cast<uint32_t>(AdvancedNavstate::Source::LANE)) &&
               (static_cast<uint32_t>(navstate.GetData().GetSource()) &
                static_cast<uint32_t>(AdvancedNavstate::Source::HD_MAP));
    }

    /**
     * @brief Set the Navstate High Precision.
     *
     * @param navstate
     */
    inline void setNavstateHighPrecision(StampedAdvancedNavstate& navstate) const
    {
        navstate.GetData().SetSource(
            static_cast<AdvancedNavstate::Source>(static_cast<uint32_t>(navstate.GetData().GetSource()) |
                                                  static_cast<uint32_t>(AdvancedNavstate::Source::LANE) |
                                                  static_cast<uint32_t>(AdvancedNavstate::Source::HD_MAP)));
    }

    /**
     * @brief Accumulate the distance which means how far away from last high precision navstate. Based on the distance,
     * we set the predicted_navstate member of each of the Results.
     *
     * @param[in] aligned_fusion_navstate The aligned fusion navstates with CameraLaneBoundaries timestamps.
     * @param[out] ego_lane_predictor_results The Results which's predicted_navstate member has been
     * set.
     */
    void accumulateDistanceAndSetNavstates(std::vector<StampedAdvancedNavstate> const& aligned_fusion_navstate,
                                           Results&                                    ego_lane_predictor_results);

private:
    Parameters const        parameters_;
    bool_t                  is_initialized_;           ///< The flag of this class is initialized.
    StampedAdvancedNavstate last_predicted_navstate_;  ///< To record last adavanced navstate of the vehicle.

    /// The salar value to record how far away from the last high precision navstate.
    Scalar accumulated_distance_from_last_high_precision_navstate_;
};

/**
 * @}
 *
 */

}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_EGO_LANE_PREDICTOR_H_
