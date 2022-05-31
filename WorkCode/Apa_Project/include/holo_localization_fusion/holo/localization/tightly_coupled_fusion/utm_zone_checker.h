/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file  utm_zone_checker.h
 * @brief check utm zone to determine parent coordinate
 * @author Bai Pengfei (baipengfei@holomatic.com)
 * @author Shuaijie Li(lishuaijie@holomatic.com)
 * @date "2021-03-24"
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_UTM_ZONE_CHECKER_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_UTM_ZONE_CHECKER_H_

#include <holo/localization/tightly_coupled_fusion/common_types.h>

namespace holo
{
namespace localization
{
namespace tightly_coupled_fusion
{
/**
 * @addtogroup tightly_coupled_fusion
 * {
 *
 */

/**
 * @brief this class aims to determine parent coordinate in utm and check whether the coordinate is changed
 *
 */

class UtmZoneChecker
{
public:
    using Ptr = std::shared_ptr<UtmZoneChecker>;

    /**
     * @brief parameters for utm zone checker
     *
     */
    struct Parameters
    {
        Scalar distance_threshold;  ///< distance threshold to checker whether the coordinate is changed(unit: m)

        /**
         * @brief constructor
         *
         * @param[in] _distance_threshold distance threshold to checker whether the coordinate is changed(unit: m)
         */
        Parameters(Scalar const _distance_threshold = 50.0) : distance_threshold(_distance_threshold)
        {
        }

        /**
         * @brief output stream for fusion parameters
         *
         * @param[in] os std::ostream&
         * @param[in] parameters parameters
         * @return std::ostream& contains content of the given parameters
         */
        friend std::ostream& operator<<(std::ostream& os, Parameters const& parameters)
        {
            os << "UtmZoneChecker::Parameters :"
               << "\n distance_threshold = " << parameters.distance_threshold << std::endl;
            return os;
        }

        /**
         * @brief static method to load parameters from yaml
         *
         * @param[in] node yaml node
         * @return the loaded parameters
         */
        static Parameters LoadFromYaml(holo::yaml::Node const& node);

        /**
         * @brief static method to generate example parameters for unit test
         *
         * @return Parameters
         */
        static Parameters GenerateExample();
    };

    /**
     * @brief constructor
     */
    UtmZoneChecker(Parameters const& parameters);

    /**
     * @brief destructor
     */
    ~UtmZoneChecker();

    /**
     * @brief determine parent coordinate and check whether the coordinate is changed
     *
     * @param[in] gnss_pvt gnss pvt measurement
     * @return bool_t true -> parent coordinate is changed, false -> otherwise
     */
    bool_t Run(GnssPvtType const& gnss_pvt);

    /**
     * @brief get parent coordinate
     *
     * @return parent coordinate
     */
    CoordinateType const& GetParentCoordinate() const;

protected:
    Parameters     parameters_;         ///< parameters for utm zone checker
    CoordinateType parent_coordinate_;  ///< parent coordinate
};

/**
 * @}
 *
 */
}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_UTM_ZONE_CHECKER_H_
