/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file likelihood_computer.h
 * @brief a class which do sign data association
 * @author Li Chao (lichao@holomatic.com)
 * @author Bai Pengfei (baipengfei@holomatic.com)
 * @date Dec 04, 2019
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_SIGN_LIKELIHOOD_COMPUTER_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_SIGN_LIKELIHOOD_COMPUTER_H_

#include <holo/localization/tightly_coupled_fusion/sign/types.h>

namespace holo
{
namespace localization
{
namespace tightly_coupled_fusion
{
namespace sign
{
/**
 * @addtogroup sign
 * @{
 *
 */

/**
 * @brief This class define likelihood computer to generate a lookup table of squared reprojection error.
 *
 */
class LikelihoodComputer
{
public:
    /**
     * @brief Construct a new LikelihoodComputer object.
     *
     * @param [in] measurements vector of measurement.
     * @param [in] predictions vector of prediction.
     * @param [in] spurious_likelihood likelihood of spurious.
     * @param [in] measurement_sigma the standard deviation of measurement.
     * @param [in] verbose verbosity, disable by default.
     */
    LikelihoodComputer(std::vector<Point2Type> const& measurements, std::vector<Point2Type> const& predictions,
                       Scalar const spurious_likelihood, Scalar const measurement_sigma,
                       MapObjectType::Classification const& classification, bool_t const verbose = false)
      : measurements_(measurements)
      , predictions_(predictions)
      , spurious_likelihood_(spurious_likelihood)
      , measurement_sigma_(measurement_sigma)
      , lookup_table_(measurements.size(), predictions.size())
      , classification_(classification)
      , verbose_(verbose)
    {
        lookup_table_ = 1.0 / std::pow(measurement_sigma_, 2.0) * CreateSquaredErrorLookupTable();
        LOG_IF(INFO, verbose) << "Squared error lookup table: \n" << lookup_table_;
    }

    /**
     * @brief Destroy the LikelihoodComputer object.
     *
     */
    ~LikelihoodComputer() noexcept
    {
    }

    /**
     * @brief A functor which calculate likelihood of a correspondence vector.
     *
     * @param correspondences the correspondence vector.
     * @return the likehood of correspondence.
     */
    Scalar operator()(std::vector<uint32_t> const& correspondences) const;

    /**
     * @brief Create a squared error lookup table.
     *
     * @return the lookup table of squared reprojection error.
     */
    MatrixXType CreateSquaredErrorLookupTable();

private:
    std::vector<Point2Type>       measurements_;         ///< vector of measurement.
    std::vector<Point2Type>       predictions_;          ///< vector of prediction.
    Scalar                        spurious_likelihood_;  ///< likelihood of spurious.
    Scalar                        measurement_sigma_;    ///< the standard deviation of measurement.
    MatrixXType                   lookup_table_;         ///< the lookup table of squared reprojection error.
    MapObjectType::Classification classification_;       ///< measurement's type
    bool_t                        verbose_;              ///< verbosity.
};

/**
 * @}
 *
 */

}  // namespace sign
}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_SIGN_LIKELIHOOD_COMPUTER_H_