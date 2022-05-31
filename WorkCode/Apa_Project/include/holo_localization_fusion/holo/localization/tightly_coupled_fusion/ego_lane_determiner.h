/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ego_lane_determiner.h
 * @brief the definition of EgoLaneDeterminer class which is the public external interfaces for the ego lane estimation.
 * @author Lei Gehang (leigehang@holomatic.com)
 * @date Mar 18, 2021
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_EGO_LANE_DETERMINER_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_EGO_LANE_DETERMINER_H_

#include <holo/localization/tightly_coupled_fusion/ego_lane_estimator.h>
#include <holo/localization/tightly_coupled_fusion/ego_lane_predictor.h>
#include <holo/localization/tightly_coupled_fusion/lane/types.h>

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
 * @brief The estimation of the ego lane. It combines the ego lane estimator and ego lane predictor, and outputs the
 * LaneRawMeasurements type as the input of the subsequent LanePreprocessor.
 *
 */
class EgoLaneDeterminer
{
public:
    /// The handy typedef
    using EgoLaneEstimatorResult  = EgoLaneEstimator::Result;
    using EgoLaneEstimatorResults = EgoLaneEstimator::Results;
    using EgoLanePredictorResult  = EgoLanePredictor::Result;
    using EgoLanePredictorResults = EgoLanePredictor::Results;
    using MapServiceClientBase    = holo::localization::tightly_coupled_fusion::map::MapServiceClientBase;
    using MapServiceClientBasePtr = MapServiceClientBase::Ptr;

    /**
     * @brief The relative parameters of this class.
     *
     */
    struct Parameters
    {
        EgoLaneEstimator::Parameters ego_lane_estimator_params;
        EgoLanePredictor::Parameters ego_lane_predictor_params;
        /**
         * @brief Enable using ego lane estimator. If this parameter be set to true, probabilistic based ego-lane
         * location method will be used otherwise we consider predicted fusion navstates has been in high precision
         * (Usually occurs in scene that high precision GNSS is integrated in fusion navstate) and force predicted
         * fusion navstates to high precision
         */
        bool_t enable_ego_lane_estimator = true;

        /**
         * @brief Static method to load parameters from yaml
         *
         * @param[in] node Yaml node
         * @return the loaded parameters
         */
        static Parameters LoadFromYaml(holo::yaml::Node const& node);

        /**
         * @brief Output stream overloading for EgoLaneDeterminer's parameter
         *
         * @param[in] os std::ostream&
         * @param[in] parameters Parameters
         * @return std::ostream& contains content of the given parameters
         */
        friend std::ostream& operator<<(std::ostream& os, Parameters const parameters);
    };

    /**
     * @brief Construct a new Ego Lane Determiner object
     *
     * @param[in] parameters The parameters of this class.
     */
    EgoLaneDeterminer(Parameters const& parameters)
      : parameters_(parameters)
      , ego_lane_predictor_ptr_(std::make_shared<EgoLanePredictor>(parameters_.ego_lane_predictor_params))
      , ego_lane_estimator_ptr_(std::make_shared<EgoLaneEstimator>(parameters_.ego_lane_estimator_params))
    {
    }

    /**
     * @brief To run the ego lane estimator and predictor to get the relative results and combines them to the
     * LaneRawMeasurements.
     *
     * @param[in] raw_measurements The ego lane raw measurements.
     * @param[in] map_service_client_ptr The map service client smart pointer
     * @return LaneRawMeasurements
     */
    LaneRawMeasurements Run(EgoLaneRawMeasurements const&  raw_measurements,
                            MapServiceClientBasePtr const& map_service_client_ptr);

protected:
    /**
     * @brief Find the corresponding ego lane predictor result with the targer timestamp.
     *
     * @param[in] ego_lane_predictor_results The ego lane predictor results.
     * @param[in] target_timestamp The target timestamp
     * @param[out] current_result_iterator The iterator of the result.
     * @return It returns true if we can find it. Otherwise, we returns false.
     */
    bool_t findCurrentResult(EgoLanePredictorResults const&           ego_lane_predictor_results,
                             Timestamp const&                         target_timestamp,
                             EgoLanePredictorResults::const_iterator& current_result_iterator) const;

    /**
     * @brief Find the corresponding ego lane estimator result with the targer timestamp.
     *
     * @param[in] ego_lane_estimator_results The ego lane estimator results.
     * @param[in] target_timestamp The target timestamp
     * @param[out] current_result_iterator The iterator of the result.
     * @return It returns true if we can find it. Otherwise, we returns false.
     */
    bool_t findCurrentResult(EgoLaneEstimatorResults const&           ego_lane_estimator_results,
                             Timestamp const&                         target_timestamp,
                             EgoLaneEstimatorResults::const_iterator& current_result_iterator) const;

    /**
     * @brief Set predicted fusion navstates of the ego lane raw measurements to high precision state.
     *
     * @param[in] raw_measurements The ego lane raw measurements.
     * @return EgoLaneRawMeasurements.
     */
    EgoLaneRawMeasurements setHighPrecision(EgoLaneRawMeasurements const& raw_measurements) const;

private:
    Parameters const parameters_;

    EgoLanePredictor::Ptr ego_lane_predictor_ptr_;  ///< The HMM algorithm ego lane estimator.
    EgoLaneEstimator::Ptr ego_lane_estimator_ptr_;  ///< The predictor using the last high precision navstate.
};

/**
 * @}
 *
 */

}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_EGO_LANE_DETERMINER_H_
