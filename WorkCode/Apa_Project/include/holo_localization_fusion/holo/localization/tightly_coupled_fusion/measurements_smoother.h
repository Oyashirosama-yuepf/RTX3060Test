/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file measurements smoother.h
 * @brief This header file defines the class to check measurements lost or find and update measurements to keep smooth
 * @author Liao MingJian(liaomingjian@holomatic.com)
 * @date Sept, 17, 2021
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_MEASUREMENTS_SMOOTHER_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_MEASUREMENTS_SMOOTHER_H_

#include <holo/localization/common/types.h>
#include <holo/localization/tightly_coupled_fusion/graph_builder.h>

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
 * @brief The class is defined to solve the problem when tightly coupled fusion measurements lost or find in unstable
 * environment, which leads to fusion result becoming unsmooth, especially between high precision measurements such as
 * lane correspondence and semantic correspondence and low precision measurements such as gnss and so on.
 * @todo add semantic correspondence check and smooth(wait until semantic localization can run in stable environment)
 */
class MeasurementsSmoother
{
public:
    /**
     * @brief handy type define
     *
     */
    using GnssFactorMeasurement =
        holo::localization::tightly_coupled_fusion::GraphBuilder::GnssPositionVelocityFactorMeasurement;

    /**
     * @brief Define method used in smooth measurements.
     *
     * @details
     * EXPAND_SIGMA_CONSTANT method: update measurement longitude and latitude sigma directly by multiply a constant
     * coefficient, usually used in case measurements lost or find in short duration. When duration of smoothing
     * measurements ends, this method may still lead to unsmooth in fusion odometry.
     *
     * EXPAND_SIGMA_GRADIENT method: update measurement longtitude and latitude sigma by providing a gradient variable
     * coefficient to ensure fusion keep smooth during precision change and some measurements lost in long time.
     *
     * REMOVE_MEASUREMENTS method: update by directly remove measurement so entirely remove their affects in unstable
     * environment.
     */
    enum Method : uint8_t
    {
        EXPAND_SIGMA_CONSTANT = 0u,
        EXPAND_SIGMA_GRADIENT = 1u,
        REMOVE_MEASUREMENTS   = 2u,
    };

    /**
     * @brief Define smooth status to save whether each measurements should be smoothed or not and each measurements'
     * duration after their status is changed. In measurements smoother pipeline, a SmoothStatus structure will be
     * generated in function DetermineSmoothStatus() , and function Smooth() would use SmoothStatus to smooth
     * measurements
     *
     * @details
     * is_gnss_ready_to_smooth: determine whether gnss in current measurements should be smoothed
     *
     * is_lane_correspondence_ready_to_smooth: determine whether lane correspondence in current measurements should be
     * smoothed
     *
     * duration_smooth_gnss: save the duration after high precision measurements lose.Only used when
     * is_gnss_ready_to_smooth == true
     *
     * duration_smooth_lane_correspondence: save the duration after high precision measurements get.Only used when
     * is_lane_correspondence_ready_to_smooth == true
     */
    struct SmoothStatus
    {
        bool_t is_gnss_ready_to_smooth                = false;
        bool_t is_lane_correspondence_ready_to_smooth = false;
        Scalar duration_smooth_gnss                   = 0.0;
        Scalar duration_smooth_lane_correspondence    = 0.0;
    };

    /**
     * @brief Define the parameters of this class.
     */
    struct Parameters
    {
        Method method;
        bool_t enable_lane_correspondence_smooth;  ///< enable smoothing lane correspondence measurements
        Scalar duration_update_gnss;  ///< process time threshold after lane correspondence lost so update gnss
                                      ///< measurements, unit(second)
        Scalar duration_update_lane_correspondence;  ///< process time threshold after lane correspondence find and
                                                     ///< update lane correspondence , unit(second)
        Scalar coefficient_expand_sigma;             ///< coefficient about expanding sigma
        Scalar duration_smooth_delay;  ///< duration about delay in smooth method , which ensure the gnss sigma
                                       ///< expanding can work in lost-get-lost-get situation, unit(second)

        /**
         * @brief create a new parameter
         */
        Parameters(Method const _method                            = Method::EXPAND_SIGMA_GRADIENT,
                   bool_t const _enable_lane_correspondence_smooth = false, Scalar const _duration_update_gnss = 8.0,
                   Scalar const _duration_update_lane_correspondence = 2.0,
                   Scalar const _coefficient_expand_sigma = 10.0, Scalar const _duration_smooth_delay = 5.0)
          : method(_method)
          , enable_lane_correspondence_smooth(_enable_lane_correspondence_smooth)
          , duration_update_gnss(_duration_update_gnss)
          , duration_update_lane_correspondence(_duration_update_lane_correspondence)
          , coefficient_expand_sigma(_coefficient_expand_sigma)
          , duration_smooth_delay(_duration_smooth_delay)
        {
        }

        /**
         * @brief Static method to generate example parameters for unit test.
         *
         * @return Parameters
         */
        static Parameters GenerateExample()
        {
            return Parameters();
        }

        /**
         * @brief load parameters from yaml
         *
         * @details loading order: [method, enable_lane_correspondence_smooth, duration_update_gnss,
         * duration_update_lane_correspondence,coefficient_expand_sigma,duration_smooth_delay]
         * @param[in] node node of yaml
         * @return Parameters
         */
        static Parameters LoadFromYaml(yaml::Node const& node);

        /**
         * @brief Operator overloading for "<<" to output the parameters to stream.
         *
         * @param[in] os std::ostream&
         * @param[in] parameters The Parameters to be outputed.
         * @return std::ostream& contains content of the given parameters
         */
        friend std::ostream& operator<<(std::ostream& os, Parameters const& parameters);
    };

    /**
     * @brief Define measurements smoother states.
     */
    struct State
    {
        bool_t is_init                                       = false;  ///< smoother is initialize or not
        bool_t is_last_measurements_with_lane_correspondence = false;  ///< last frame is with lane factor or not
        // timestamp of last time when graph builder lose lane correspondence
        Timestamp timestamp_lane_correspondence_lose = Timestamp(0, 0);
        // timestamp of last time when graph builder get lane correspondence
        Timestamp timestamp_lane_correspondence_get = Timestamp(0, 0);

        /**
         * @brief init a new state
         */
        State(bool_t const& _is_init = false, bool_t const& _is_last_measurements_with_lane_correspondence = false,
              Timestamp const& _timestamp_lane_correspondence_lose = Timestamp(0, 0),
              Timestamp const& _timestamp_lane_correspondence_get  = Timestamp(0, 0))
          : is_init(_is_init)
          , is_last_measurements_with_lane_correspondence(_is_last_measurements_with_lane_correspondence)
          , timestamp_lane_correspondence_lose(_timestamp_lane_correspondence_lose)
          , timestamp_lane_correspondence_get(_timestamp_lane_correspondence_get)
        {
        }
    };

    /**
     * @brief constructor.
     *
     * @param[in] parameters smoother parameter to construct smoother
     */
    MeasurementsSmoother(Parameters const& parameters);

    /**
     * @brief destructor.
     */
    ~MeasurementsSmoother();

    /**
     * @brief run measurements smoother
     * @details totally 3 steps
     * step1: check whether the smoother is initialized. If not, initialize the smoother
     * step2: check current lane correspondence , judge whether precision is changed , calculate duration use current
     * measurements and past states
     * step3: update measurements by state
     * @param[out] measurements input graphbuilder measurements and update the measurements in smoother
     * @return if initialize success and output success return true , else return false
     */
    bool_t Run(GraphBuilder::Measurements& measurements);

    /**
     * @brief reset smoother
     */
    void Reset()
    {
        state_ = State();
    }

protected:
    /**
     * @brief Define coefficients structure to save coefficients value in expanding sigma step
     *
     * @details
     * coefficient_expand_gnss_sigma: when gnss is ready to smooth and using expand sigma method. this coefficient will
     * be used in updateMeasurements()
     *
     * coefficient_expand_lane_correspondence_sigma: when lane correpondence is ready to smooth and using expand sigma
     * method. this coefficient will be used in updateMeasurements()
     */
    struct Coefficients
    {
        Scalar coefficient_expand_gnss_sigma                = 1.0;
        Scalar coefficient_expand_lane_correspondence_sigma = 1.0;

        /**
         * @brief init a new Coefficient
         */
        Coefficients(Scalar const& _coefficient_expand_gnss_sigma               = 1.0,
                     Scalar const& _coefficient_expand_lane_correpondence_sigma = 1.0)
          : coefficient_expand_gnss_sigma(_coefficient_expand_gnss_sigma)
          , coefficient_expand_lane_correspondence_sigma(_coefficient_expand_lane_correpondence_sigma)
        {
        }
    };

    /**
     * @brief initialize measurements smoother
     * @details only initialize when lane correspondence is detected
     *
     * @param[in] measurements graphbuilder measurements
     * @return if initialize success return true , else return false
     */
    bool_t initialize(GraphBuilder::Measurements const& measurements);

    /**
     * @brief determine the smooth status of measurements
     *
     * @param[in] measurements graphbuilder measurements
     * @return smooth status to determine each measurements status and their current duration
     */
    SmoothStatus determineSmoothStatus(GraphBuilder::Measurements const& measurements);

    /**
     * @brief smooth measurements
     *
     * @param[in] smooth_status smooth status
     * @param[out] measurements graphbuilder measurements
     */
    void smooth(SmoothStatus const& smooth_status, GraphBuilder::Measurements& measurements);

    /**
     * @brief smooth measurements using expanding sigma with constant value
     *
     * @param[in] smooth_status smooth status
     * @param[out] measurements graphbuilder measurements
     */
    void smoothUsingExpandSigmaConstant(SmoothStatus const& smooth_status, GraphBuilder::Measurements& measurements);

    /**
     * @brief smooth measurements using expanding sigma with gradient value
     *
     * @param[in] smooth_status smooth status
     * @param[out] measurements graphbuilder measurements
     */
    void smoothUsingExpandSigmaGradient(SmoothStatus const& smooth_status, GraphBuilder::Measurements& measurements);

    /**
     * @brief smooth measurements using removing measurements
     *
     * @param[in] smooth_status smooth status
     * @param[out] measurements graphbuilder measurements
     */
    void smoothUsingRemoveMeasurements(SmoothStatus const& smooth_status, GraphBuilder::Measurements& measurements);

    /**
     * @brief update the measurements using cofficients to expand sigma
     *
     * @param[in] smooth_status smooth status
     * @param[in] coefficients cofficient to expand sigma
     * @param[out] measurements graphbuilder measurements
     */
    void updateMeasurements(SmoothStatus const& smooth_status, Coefficients const& coefficients,
                            GraphBuilder::Measurements& measurements);

private:
    Parameters parameters_;  ///< parameters
    State      state_;       ///< smoother state
};

}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo

#endif  /// HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_MEASUREMENTS_SMOOTHER_H_