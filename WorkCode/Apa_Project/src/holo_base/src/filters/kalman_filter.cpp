/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file kalman_filter.cpp
 * @brief The instantiation of template class Kalman filter
 * @author Yuchao Hu (huyuchao@holomatic.com), lichao@holomatic.com
 * @date Sep 20, 2019
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo/filters/kalman_filter.h>
#include <holo/filters/impl/kalman_filter.hpp>

#define INSTANTIATE(Scalar, Dimension) template class KalmanFilterT<Scalar, Dimension>;

#define INSTANTIATE_PREDICTION(Scalar, Dimension, ControlDim)                                                          \
    template void KalmanFilterT<Scalar, Dimension>::Predict<ControlDim>(                                               \
        const numerics::MatrixT<Scalar, Dimension, Dimension>&  state_transition_model,                                          \
        const numerics::MatrixT<Scalar, Dimension, ControlDim>& control_input_model, const numerics::VectorT<Scalar, ControlDim>& control, \
        const numerics::MatrixT<Scalar, Dimension, Dimension>& process_noise_covariance);

#define INSTANTIATE_CORRECTION(Scalar, Dimension, ObservationDim)                                                      \
    template void KalmanFilterT<Scalar, Dimension>::Correct<ObservationDim>(                                           \
        const numerics::VectorT<Scalar, ObservationDim>&                 observation,                                            \
        const numerics::MatrixT<Scalar, ObservationDim, Dimension>&      observation_model,                                      \
        const numerics::MatrixT<Scalar, ObservationDim, ObservationDim>& observation_noise_covariance);

namespace holo
{
/**
 * @brief instantiate kalman filter
 */
INSTANTIATE(float32_t, 4);
INSTANTIATE(float64_t, 13);
INSTANTIATE(float64_t, 15);

/**
 * @brief instantiate prediction
 */
INSTANTIATE_PREDICTION(float32_t, 4, 2);
INSTANTIATE_PREDICTION(float64_t, 13, 3);
INSTANTIATE_PREDICTION(float64_t, 13, 6);
INSTANTIATE_PREDICTION(float64_t, 15, 3);
INSTANTIATE_PREDICTION(float64_t, 15, 6);

/**
 * @brief instantiate correction
 */
INSTANTIATE_CORRECTION(float32_t, 4, 2);
INSTANTIATE_CORRECTION(float64_t, 13, 3);
INSTANTIATE_CORRECTION(float64_t, 13, 6);
INSTANTIATE_CORRECTION(float64_t, 15, 3);
INSTANTIATE_CORRECTION(float64_t, 15, 6);

}  // namespace holo

//#undef INSTANTIATE
