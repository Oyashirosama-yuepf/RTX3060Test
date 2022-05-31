/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file body_in_ground_roll_pitch_estimator.h
 * @brief this file defines a class to estimate the roll and pitch of the body in ground coordinate
 * @author Shuaijie Li @ lishuaijie@holomatic.com
 * @date 2021-09-09
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_APP_BODY_IN_GROUND_ROLL_PITCH_ESTIMATOR_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_APP_BODY_IN_GROUND_ROLL_PITCH_ESTIMATOR_H_

#include <holo/localization/tightly_coupled_fusion/common_types.h>
#include <holo/localization/tightly_coupled_fusion/utils/common_functions.h>

namespace holo
{
namespace localization
{
namespace tightly_coupled_fusion
{
/**
 * @addtogroup apps
 * @{
 *
 */

/**
 * @brief estimate roll and pitch of body in ground coordinate
 * @details Input: of this class is a series of odometry which is the pose of body in reference coordinate
 *          Output: Rot3Type whose yaw is set to zero
 *          Method: 1. estimate the normal vector of ground plane {ground_normal_vector} in reference coordinate with
 *                     the input odometry
 *                  2. get z axis of body {body_z_axis} in reference coordinate with the newest input odometry
 *                  3. estimate roll and pitch of body in ground coordinate with {ground_normal_vector} and
 *                     {body_z_axis}
 *                  4. set yaw to zero
 */

class BodyInGroundRollPitchEstimator
{
public:
    template <typename T>
    using QueueType = std::queue<T>;
    using Ptr       = std::shared_ptr<BodyInGroundRollPitchEstimator>;

    /**
     * @brief parameters to litmit the data used to estimate ground plane
     */
    struct Parameters
    {
        Scalar max_accumulated_distance;  ///< max distance of the trajectory used to estimate ground palne [Unit: m]
        Scalar min_accumulated_distance;  ///< min distance of the trejectory used to estimate ground plane [Unit: m]
        Scalar min_distance_between_consecutive_odometry;  ///< min distance of the consecutive odometry in the
                                                           ///< trajectory which is used to estimate ground plane
                                                           ///< [Unit:m]
        /**
         * @brief constructor
         *
         * @param[in] _max_accumulated_distance max distance of the trajectory used to estimate ground palne [Unit: m]
         * @param[in] _min_accumulated_distance min distance of the trejectory used to estimate ground plane [Unit: m]
         * @param[in] _min_distance_between_consecutive_odometry min distance of the consecutive odometry [Unit: m]
         */
        Parameters(Scalar const _max_accumulated_distance, Scalar const _min_accumulated_distance,
                   Scalar const _min_distance_between_consecutive_odometry);

        /**
         * @brief output stream for BodyInGroundRollPitchEstimator parameters
         *
         * @param[in] os std::ostream&
         * @param[in] parameters BodyInGroundRollPitchEstimator parameters
         *
         * @return std::ostream& constains content of the given  parameters
         */
        friend std::ostream& operator<<(std::ostream& os, Parameters const& parameters)
        {
            os << "BodyInGroundRollPitchEstimator::Parameters "
               << "\n max_accumulated_distance = " << parameters.max_accumulated_distance
               << "\n min_accumulated_distance = " << parameters.min_accumulated_distance
               << "\n min_distance_between_consecutive_odometry = "
               << parameters.min_distance_between_consecutive_odometry << std::endl;
            return os;
        }

        /**
         * @brief static method to load parameters from yaml node
         *
         * @param[in] node yaml node
         *
         * @return   the loaded parameters
         */
        static Parameters LoadFromYaml(yaml::Node const& node);

        /**
         * @brief static method to generate example parameters for unit test
         *
         * @return Parameters
         */
        static Parameters GenerateExample();
    };  // Parameters

    /**
     * @brief constructor
     *
     * @param[in] parameters parameters for plane fitting
     */
    BodyInGroundRollPitchEstimator(Parameters const& parameters);

    /**
     * @brief destructor
     */
    ~BodyInGroundRollPitchEstimator(){};

    /**
     * @brief estimate roll and pitch with the given odometry
     * @note it will modify {history_odometry_}, {history_relative_distance_}, {accumulated_ground_normal_vector_},
     * {accumulated_distance_}
     *
     * @param[in] current_odometry odometry of body in reference coordinate
     *
     * @return std::pair<bool_t, Rot3Type> the first one is true means the second one valid, false -> invalid
     */
    std::pair<bool_t, Rot3Type> Run(OdometryType const& current_odometry);

    /**
     * @brief clear internal variable
     * @note it will modify {history_odometry_}, {history_relative_distance_}, {accumulated_ground_normal_vector_},
     * {accumulated_distance_}
     */
    void Reset();

protected:
    /**
     * @brief initialize internal variables with the given odometry
     * @note it will modify {history_odometry_}, {history_relative_distance_}, {accumulated_ground_normal_vector_},
     * ${accumulated_distance_}
     *
     * @param[in] current_odometry odometry of body in reference coordinate
     */
    void initialize(OdometryType const& current_odometry);

    /**
     * @brief update internal variable with the given odometry
     * @details update history information
     *          1. do nothing if the translation between current odometry and last history odometry is smaller than
     *             parameters_.min_distance_between_consecutive_odometry
     *          2. append current odometry to history information, if the accumulated_distance_ is smaller than
     *             parameters_.max_accumulated_distance
     *          3. clear history_odometry_.front() and append current odometry to history information if the
     *             accumulated_distance_ is larger than parameters_.max_accumulated_distance
     * @note it will modify {history_odometry_}, {history_relative_distance_}, {accumulated_ground_normal_vector_},
     * ${accumulated_distance_}
     *
     * @param[in] current_odometry odometry of body in reference coordinate
     */
    void update(OdometryType const& current_odometry);

    /**
     * @brief fit ground plane and estimate roll and pitch of current body in ground plane
     *
     * @param[in] current_odometry odometry of body in reference coordinate
     *
     * @return std::pair<bool_t, Rot3Type> the first one is true means the second one valid, false -> invalid
     */
    std::pair<bool_t, Rot3Type> estimateRollAndPitch(OdometryType const& current_odometry);

protected:
    Parameters              parameters_;        ///< parameters for BodyInGroundRollPitchEstimator
    QueueType<OdometryType> history_odometry_;  ///< history odometry which is used to estimate ground plane
    /**
     * @brief distance of consective odometry
     * @details history_relative_distance_[i] = history_odometry_[i].GetPose().Inverse() *
     * history_odometry_[i+1u].GetPose()).GetTranslation().As<Vector3Type>().GetNorm()
     * @note history_relative_distance_.size() = history_odometry_.size() - 1u when history_odometry_ is not empty
     */
    QueueType<Scalar> history_relative_distance_;
    Vector3Type accumulated_ground_normal_vector_;  ///< accumulated ground normal vector of each {history_odometry_}
    Scalar      accumulated_distance_;              ///< accumulated distance of {history_relative_distance_}

};  // BodyInGroundRollPitchEstimator

/**
 * @}
 */
}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo
#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_APP_BODY_IN_GROUND_ROLL_PITCH_ESTIMATOR_H_
