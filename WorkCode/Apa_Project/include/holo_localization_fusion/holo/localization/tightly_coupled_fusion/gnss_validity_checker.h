/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file gnss_validity_checker.h
 * @brief This header file defines the class to check the GNSS validity
 * @author Lei Gehang(leigehang@holomatic.com)
 * @date Dec 02, 2019
 */
#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_GNSS_VALIDITY_CHECKER_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_GNSS_VALIDITY_CHECKER_H_

#include <holo/localization/common/types.h>

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
 * @brief This class is used to judge the validity of GNSS measurement
 */
class GnssValidityChecker
{
public:
    using Vector3 = Vector3Type;
    using Matrix6 = Matrix6Type;
    using GnssPvt = GnssPvtType;

    /**
     * @brief Gnss covariance validity parameters for position and velocity based on the adaptive covariance method
     *
     */
    struct AdaptiveCovarianceThreshold
    {
        Scalar covariance_threshold_max = Scalar(-1.0);  ///< Upper limit of Gnss cov threshold
        Scalar covariance_threshold_min = Scalar(-1.0);  ///< Lower limit of Gnss cov threshold
        Scalar threshold_reduction_rate = Scalar(-1.0);  ///< Reduction rate for adaptive threshold
        Scalar threshold_expansion_rate = Scalar(-1.0);  ///< Expansion rate for adaptive threshold
        Scalar lowest_multiple          = Scalar(-1.0);  ///< The multiple = current_cov_threshold / actual_threshold

        /**
         * @brief static method to load parameters from yaml.
         *
         * @param[in] node yaml node
         * @return AdaptiveCovarianceThreshold
         */
        static AdaptiveCovarianceThreshold LoadFromYaml(holo::yaml::Node const& node);

        /**
         * @brief Output the AdaptiveCovarianceThreshold in standard format.
         *
         * @param[in] os std::ostream&
         * @param[in] covariance_threshold The adaptive covariance threshold
         * @return std::ostream& contains content of the given parameters
         */
        friend std::ostream& operator<<(std::ostream& os, AdaptiveCovarianceThreshold const& covariance_threshold);
    };

    /**
     * @brief The parameter struct of the Gnss validity checker class
     */
    struct Parameters
    {
        /// The threshold for the velocity validity judgement
        AdaptiveCovarianceThreshold gnss_velocity_parameter;
        /// The threshold for the position validity judgement
        AdaptiveCovarianceThreshold gnss_position_parameter;
        /// The minimum number of observated satellites that a valid GNSS data has
        uint16_t min_satellites_number_for_valid_gnss    = 14u;
        bool_t   enable_gnss_satellites_number_judgement = false;  ///< The switch of GNSS satellites number judgement

        /**
         * @brief static method to load parameters from yaml.
         *
         * @param[in] node yaml node
         * @return Parameters
         */
        static Parameters LoadFromYaml(holo::yaml::Node const& node);

        /**
         * @brief Output the Parameters in standard format.
         *
         * @param[in] os std::ostream&
         * @param[in] parameters The Parameters
         * @return std::ostream& contains content of the given parameters
         */
        friend std::ostream& operator<<(std::ostream& os, Parameters const& parameters);
    };

    /**
     * @brief Gnss covariance scaling parameters for position and velocity based on the adaptive method
     */
    struct AdaptiveCovarianceScalingParameters
    {
        Scalar velocity_cov_scaling_parameter = Scalar(1.0);  ///< The adaptive coefficient for velocity
        Scalar position_cov_scaling_parameter = Scalar(1.0);  ///< The adaptive coefficient for position
    };

    /**
     * @brief Deprecated default constructor
     *
     */
    GnssValidityChecker() = delete;

    /**
     * @brief Construct a new Gnss Validity Checker object
     *
     * @param param The initial parameters
     * @throws std::valid_argument When the input parameters is invalid, for example using the default parameters.
     */
    explicit GnssValidityChecker(const Parameters& param);

    /**
     * @brief Destroy the Gnss Validity Checker object
     */
    ~GnssValidityChecker() noexcept
    {
    }

    /**
     * @brief Judge whether it is valid Gnss measurements based on its validity flag.
     * @details Both the data(position and velocity) and its covariance (position cov and velocity) are valid, this
     * measurements will be considered valid.
     *
     * @param[in] gnss_measurement GNSS measurement
     * @return It returns true if it is considered valid, otherwise, it returns false.
     */
    bool_t RunValidityCheckBasedOnValidFlags(GnssPvt const& gnss_measurement) const
    {
        return gnss_measurement.IsValid() && gnss_measurement.IsCovValid();
    }

    /**
     * @brief Judge the gnss validity based on the GNSS covaraicne
     * @details Judge the validity with the adaptive scaling parameter. The scaling parameter will be changed according
     * to the judgement result. If the measurement covariance is lower than the threshold, the parameter will reduce.
     * Otherwize, It will increase.
     *
     * @param[in] gnss_measurement The Gnss measurement
     * @return The GNSS validity: True -- valid, False -- invalid
     */
    bool_t RunAdaptiveValidityCheckBasedOnCovariance(const GnssPvt& gnss_measurement) noexcept;

    /**
     * @brief Judge the GNSS validity based on the observed satellites number
     * @attention In the current version, the number of satellites is assigned to the up velocity covariance of GNSS
     *
     * @param gnss_measurement The Gnss measurement
     * @return It returns true if it is valid. Otherwise, it returns false
     */
    bool_t RunValidityCheckBasedOnSatellitesNumber(const GnssPvt& gnss_measurement) const noexcept;

    /**
     * @brief check whether the gnss pvt is wrong due to bais plug-in
     * @details the longitude and latitude is zero if the position is outside the region of bias plug-in, so it is
     * invalid if appears
     *
     * @param gnss_measurement The Gnss measurement
     *
     * @return It returns true if it is valid. Otherwise, it returns false
     */
    bool_t RunBiasPlugInCheck(GnssPvt const& gnss_measurement) const noexcept
    {
        return std::abs(gnss_measurement.GetLongitude()) + std::abs(gnss_measurement.GetLatitude()) >
               holo::EpsilonT<Scalar>::value;
    }

private:
    /**
     * @brief Judge the gnss validity with the adaptive scaling parameter.
     * @details The scaling parameter will be changed according to the judgement result. If the measurement covariance
     * is lower than the threshold, the parameter will reduce. Otherwize, It will increase.
     *
     * @param covariance The velocity covariance or position covariance
     * @param threshold The corresponding adaptive covariance threshold struct
     * @param scaling_parameter The last corresponding scaling parameter
     * @return std::pair<the gnss validity, the updated scaling parameter>
     */
    std::pair<bool_t, Scalar> checkGnssCovarianceAdaptively(const Vector3&                     covariance,
                                                            const AdaptiveCovarianceThreshold& threshold,
                                                            const Scalar scaling_parameter) const noexcept;

    /**
     * @brief Check the input adaptive covariance threshold validity
     *
     * @param threshold The input threshold parameters
     * @return The validity: True -- valid, False -- invalid
     */
    bool_t checkAdaptiveThresholdValidity(const AdaptiveCovarianceThreshold& threshold) const noexcept;

    const Parameters                    parameters_;  ///< The class parameters
    AdaptiveCovarianceScalingParameters adaptive_cov_scaling_parameters_;
};

/**
 * @}
 *
 */
}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo
#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_GNSS_VALIDITY_CHECKER_H_
