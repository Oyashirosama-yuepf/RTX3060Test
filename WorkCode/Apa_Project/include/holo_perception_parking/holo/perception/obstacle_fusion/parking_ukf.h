/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parking_ukf.h
 * @brief This header file defines .
 * @author wenxunzhe(wenxunzhe@holomatic.com)
 * @date "2021-12-13"
 */

#ifndef HOLO_PERCEPTION_OBSTACLE_FUSION_PARKING_UKF_H
#define HOLO_PERCEPTION_OBSTACLE_FUSION_PARKING_UKF_H

#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>

#include <Eigen/Dense>
#include <holo/numerics/impl/eigen_solver.hpp>

namespace holo
{
namespace perception
{
/**
 * @brief obstacle tracking pipeline interface for parking
 * @details following common tracking pipeline and define association machanism
 *
 */
class ParkingObstacleUnscentedKalmanFilter
{
public:
    static const uint8_t STATE_DIM = 6U;

public:
    using Scalar      = holo::float32_t;
    using Timestamp   = holo::common::details::Timestamp;
    using StateVector = holo::numerics::VectorT<Scalar, STATE_DIM>;
    using EigenVector = Eigen::VectorXd;
    using EigenMatrix = Eigen::MatrixXd;

    /**
     * ParkingObstacleUnscentedKalmanFilter constructor
     */
    ParkingObstacleUnscentedKalmanFilter(Timestamp const& timestamp, Scalar const x, Scalar const vx, Scalar const ax,
                                         Scalar const y, Scalar const vy, Scalar const ay);

    /**
     * @brief Predicts sigma points, the state, and the state covariance matrix
     *
     * @param timestamp current time stamp
     */
    void Predict(Timestamp const& timestamp);

    /**
     * @brief Updates the state and the state covariance matrix using a measurement
     *
     * @param x position along x in measurement
     * @param vx velocity along x in measurement
     * @param ax acceleration along x in measurement
     * @param y position along y in measurement
     * @param vy velocity along y in measurement
     * @param ay acceleration along y in measurement
     */
    void Update(Scalar const x, Scalar const vx, Scalar const ax, Scalar const y, Scalar const vy, Scalar const ay);

    /**
     * @brief normalize the angle into -M_PI to M_PI
     */
    void NormalizeAngle(EigenVector& state);

    /**
     * @brief get the state vector
     *
     * @return state vector
     */
    StateVector const& GetState()
    {
        return state_vector_;
    }

    /**
     * @brief get the meansurement covariance matrix
     *
     * @return measurement covariance matrix
     */
    EigenMatrix& GetMeasureNoiseCov()
    {
        return R_;
    }

private:
    Timestamp   time_stamp_;
    StateVector state_vector_;

    EigenVector x_;
    EigenMatrix P_;
    EigenMatrix R_;
    EigenVector weights_;
    EigenMatrix pred_sigma_matrix_;

    Scalar std_a_;
    Scalar std_a_dot_;

    Scalar std_px_;
    Scalar std_py_;
    Scalar std_v_;
    Scalar std_phi_;
    Scalar std_phi_dot_;

    Scalar kappa_;

    int dim_x_;
    int dim_z_;
    int dim_aug_;
};
/**
 * @}
 */

}  // namespace perception
}  // namespace holo

#endif
