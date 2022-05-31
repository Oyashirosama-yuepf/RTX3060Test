/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file kalman_filter_float32.c
 * @brief The implementation of kalman_filter_float32.c
 * @author Lei Gehang (leigehang@holomatic.com)
 * @date Feb 11, 2020
 */

#include <assert.h>

#include <holo_c/filters/kalman_filter_float32.h>
#include <holo_c/utils/serialization.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t kalman_filterf_init(struct KalmanFilterf* self, struct Vectorf const* state,
                              struct Matrixf const* priori_covariance)
{
    /// Step 1: Check the validity of the inputs
    assert(self != NULL);
    assert(vectorf_is_valid(state));
    assert(matrixf_is_valid(priori_covariance));

    /// Step 2: Check the rows and columns of the inputs
    if (priori_covariance->rows != priori_covariance->cols)
    {
        return RC_NUMERICS_MATRIX_NOT_SQUARE;
    }

    if (priori_covariance->cols != state->size)
    {
        return RC_NUMERICS_MATRIX_MIXED_SIZE;
    }

    /// Step 3: Assignment operation
    self->current_state              = *state;
    self->priori_estimate_covariance = *priori_covariance;
    self->stability_gamma            = 1.0f;
    self->stability                  = false;

    return RC_SUCCESS;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t kalman_filterf_set_from_kalman_filterf(struct KalmanFilterf* self, struct KalmanFilterf const* other)
{
    assert(kalman_filterf_is_valid(self));
    assert(kalman_filterf_is_valid(other));

    /// Check the validity of other kalman filter
    if (vectorf_get_size(&self->current_state) == vectorf_get_size(&other->current_state) &&
        matrixf_get_rows(&self->priori_estimate_covariance) == matrixf_get_rows(&other->priori_estimate_covariance) &&
        matrixf_get_cols(&self->priori_estimate_covariance) == matrixf_get_cols(&other->priori_estimate_covariance))
    {
        vectorf_set_from_vectorf(&self->current_state, &other->current_state);
        matrixf_set_from_matrixf(&self->priori_estimate_covariance, &other->priori_estimate_covariance);
        self->stability       = other->stability;
        self->stability_gamma = other->stability_gamma;

        return RC_SUCCESS;
    }
    else
    {
        return RC_NUMERICS_MATRIX_MIXED_SIZE;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t kalman_filterf_is_valid(struct KalmanFilterf const* self)
{
    assert(self != NULL);

    bool_t flag = true;
    if (!matrixf_is_valid(&self->priori_estimate_covariance))
    {
        flag = false;
    }
    else if (!vectorf_is_valid(&self->current_state))
    {
        flag = false;
    }
    else if (self->priori_estimate_covariance.rows != self->priori_estimate_covariance.cols)
    {
        flag = false;
    }
    else if (self->priori_estimate_covariance.cols != self->current_state.size)
    {
        flag = false;
    }
    return flag;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t kalman_filterf_reset(struct KalmanFilterf* self)
{
    assert(self != NULL);
    assert(kalman_filterf_is_valid(self));

    retcode_t rc = RC_SUCCESS;

    vectorf_set_zeros(&self->current_state);
    matrixf_set_zeros(&self->priori_estimate_covariance);
    self->stability_gamma = 1.0f;
    self->stability       = false;

    return rc;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t kalman_filterf_set_state_with_covariance(struct KalmanFilterf* self, struct Vectorf const* state,
                                                   struct Matrixf const* priori_covariance)
{
    /// Check the input pointer
    assert(self != NULL);
    assert(state != NULL);
    assert(priori_covariance != NULL);
    assert(kalman_filterf_is_valid(self));

    if (priori_covariance->cols == self->priori_estimate_covariance.cols &&
        priori_covariance->rows == self->priori_estimate_covariance.rows && state->size == self->current_state.size)
    {
        matrixf_set_from_matrixf(&self->priori_estimate_covariance, priori_covariance);
        vectorf_set_from_vectorf(&self->current_state, state);
        return RC_SUCCESS;
    }
    else
    {
        return RC_NUMERICS_MATRIX_MIXED_SIZE;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t kalman_filterf_set_state(struct KalmanFilterf* self, struct Vectorf const* state)
{
    assert(self != NULL);
    assert(state != NULL);
    assert(kalman_filterf_is_valid(self));

    return vectorf_set_from_vectorf(&self->current_state, state);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t kalman_filterf_set_covariance(struct KalmanFilterf* self, struct Matrixf const* covariance)
{
    assert(self != NULL);
    assert(covariance != NULL);
    assert(kalman_filterf_is_valid(self));

    return matrixf_set_from_matrixf(&self->priori_estimate_covariance, covariance);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t kalman_filterf_get_state(struct KalmanFilterf const* self, struct Vectorf* state)
{
    assert(self != NULL);
    assert(state != NULL);
    assert(kalman_filterf_is_valid(self));

    return vectorf_set_from_vectorf(state, &self->current_state);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t kalman_filterf_get_covariance(struct KalmanFilterf const* self, struct Matrixf* covariance)
{
    assert(self != NULL);
    assert(covariance != NULL);
    assert(kalman_filterf_is_valid(self));

    return matrixf_set_from_matrixf(covariance, &self->priori_estimate_covariance);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t kalman_filterf_get_state_with_covariance(struct KalmanFilterf const* self, struct Vectorf* state,
                                                   struct Matrixf* covariance)
{
    /// Check the input pointer
    assert(self != NULL);
    assert(state != NULL);
    assert(covariance != NULL);
    assert(kalman_filterf_is_valid(self));

    if (covariance->cols == self->priori_estimate_covariance.cols &&
        covariance->rows == self->priori_estimate_covariance.rows && state->size == self->current_state.size)
    {
        matrixf_set_from_matrixf(covariance, &self->priori_estimate_covariance);
        vectorf_set_from_vectorf(state, &self->current_state);
        return RC_SUCCESS;
    }
    else
    {
        return RC_NUMERICS_MATRIX_MIXED_SIZE;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t kalman_filterf_predict(struct KalmanFilterf* self, struct Matrixf const* state_transition_model,
                                 struct Matrixf const* control_input_model, struct Vectorf const* control,
                                 struct Matrixf const* process_noise_covariance)
{
    /// Step 1: Check if the input pointers are null
    assert(self != NULL);
    assert(state_transition_model != NULL);
    assert(control_input_model != NULL);
    assert(control != NULL);
    assert(process_noise_covariance != NULL);
    assert(kalman_filterf_is_valid(self));

    /// Step 2: Check the dimension of the inputs
    if (state_transition_model->rows == state_transition_model->cols &&
        state_transition_model->cols == self->current_state.size &&
        control_input_model->rows == self->current_state.size && control_input_model->cols == control->size &&
        process_noise_covariance->rows == process_noise_covariance->cols &&
        process_noise_covariance->rows == self->priori_estimate_covariance.rows &&
        process_noise_covariance->cols == self->priori_estimate_covariance.cols)
    {
        uint8_t const state_dimension_const = vectorf_get_size(&self->current_state);
        /// Step 3: Predicted (a priori) state estimate, x_j = F * x_i + B * u
        struct Vectorf vec_f_multi_x_i;
        float32_t      vec_f_multi_x_i_buff[VECTORF_MIN_BUF_SIZE(state_dimension_const)];
        vectorf_init(&vec_f_multi_x_i, state_dimension_const, vec_f_multi_x_i_buff,
                     VECTORF_MIN_BUF_SIZE(state_dimension_const));
        vectorf_multiply_by_matrixf(&self->current_state, state_transition_model, &vec_f_multi_x_i);

        struct Vectorf vec_b_multi_u;
        float32_t      vec_b_multi_u_buff[VECTORF_MIN_BUF_SIZE(state_dimension_const)];
        vectorf_init(&vec_b_multi_u, state_dimension_const, vec_b_multi_u_buff,
                     VECTORF_MIN_BUF_SIZE(state_dimension_const));
        vectorf_multiply_by_matrixf(control, control_input_model, &vec_b_multi_u);

        vectorf_add(&vec_f_multi_x_i, &vec_b_multi_u, &self->current_state);

        /// Step 4: Predicted(a priori) estimate covariance, P_j = F * P_i * F^T + Q
        struct Matrixf mat_f_transpose;
        float32_t
            mat_f_transpose_buff[MATRIXF_MIN_BUF_SIZE(state_transition_model->cols, state_transition_model->rows)];
        matrixf_init(&mat_f_transpose, state_transition_model->cols, state_transition_model->rows, mat_f_transpose_buff,
                     MATRIXF_MIN_BUF_SIZE(state_transition_model->cols, state_transition_model->rows));
        matrixf_transpose(state_transition_model, &mat_f_transpose);

        struct Matrixf mat_f_pi_f_t;
        float32_t      mat_f_pi_f_t_buff[MATRIXF_MIN_BUF_SIZE(state_dimension_const, state_dimension_const)];
        matrixf_init(&mat_f_pi_f_t, state_dimension_const, state_dimension_const, mat_f_pi_f_t_buff,
                     MATRIXF_MIN_BUF_SIZE(state_dimension_const, state_dimension_const));
        matrixf_multiply(state_transition_model, &self->priori_estimate_covariance, &mat_f_pi_f_t);
        matrixf_multiply(&mat_f_pi_f_t, &mat_f_transpose, &mat_f_pi_f_t);
        matrixf_add(&mat_f_pi_f_t, process_noise_covariance, &self->priori_estimate_covariance);

        return RC_SUCCESS;
    }
    else
    {
        return RC_NUMERICS_MATRIX_MIXED_SIZE;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t kalman_filterf_correct(struct KalmanFilterf* self, struct Vectorf const* observation,
                                 struct Matrixf const* observation_model,
                                 struct Matrixf const* observation_noise_covariance)
{
    /// Step 1: Check if the input pointers are null
    assert(self != NULL);
    assert(observation != NULL);
    assert(observation_model != NULL);
    assert(observation_noise_covariance != NULL);
    assert(kalman_filterf_is_valid(self));

    /// Step 2: Check the dimensions of the inputs
    if (observation->size == observation_model->rows && observation_model->cols == self->current_state.size &&
        observation_noise_covariance->rows == observation->size &&
        observation_noise_covariance->cols == observation->size)
    {
        uint8_t const obs_dimension_const   = observation->size;  ///< Observation dimension
        uint8_t const state_dimension_const = self->current_state.size;
        /// Step 3: Innovation or measurement pre-fit residual, y = z - H * x_j
        struct Vectorf innovation;
        float32_t      innovation_buff[VECTORF_MIN_BUF_SIZE(obs_dimension_const)];
        vectorf_init(&innovation, obs_dimension_const, innovation_buff, VECTORF_MIN_BUF_SIZE(obs_dimension_const));
        vectorf_multiply_by_matrixf(&self->current_state, observation_model, &innovation);
        vectorf_sub(observation, &innovation, &innovation);

        /// Step 4: Innovation (or pre-fit residual) covariance, S = H * P * H^T + R
        /// Get temporary matrixf: H * P
        struct Matrixf mat_h_multi_p;
        float32_t      mat_h_multi_p_buff[MATRIXF_MIN_BUF_SIZE(obs_dimension_const, state_dimension_const)];
        matrixf_init(&mat_h_multi_p, obs_dimension_const, state_dimension_const, mat_h_multi_p_buff,
                     MATRIXF_MIN_BUF_SIZE(obs_dimension_const, state_dimension_const));
        matrixf_multiply(observation_model, &self->priori_estimate_covariance, &mat_h_multi_p);

        /// Get the transpose matrix of H
        struct Matrixf mat_h_transpose;
        float32_t      mat_h_transpose_buff[MATRIXF_MIN_BUF_SIZE(state_dimension_const, obs_dimension_const)];
        matrixf_init(&mat_h_transpose, state_dimension_const, obs_dimension_const, mat_h_transpose_buff,
                     MATRIXF_MIN_BUF_SIZE(state_dimension_const, obs_dimension_const));
        matrixf_transpose(observation_model, &mat_h_transpose);

        /// Get the temporary matrixf: H * P * H_T
        struct Matrixf innovation_covariance;
        float32_t      innovation_covariance_buff[MATRIXF_MIN_BUF_SIZE(obs_dimension_const, obs_dimension_const)];
        matrixf_init(&innovation_covariance, obs_dimension_const, obs_dimension_const, innovation_covariance_buff,
                     MATRIXF_MIN_BUF_SIZE(obs_dimension_const, obs_dimension_const));
        matrixf_multiply(&mat_h_multi_p, &mat_h_transpose, &innovation_covariance);
        /// Add the observation noise matrix
        matrixf_add(&innovation_covariance, observation_noise_covariance, &innovation_covariance);

        /** check if the filter is stable, innovation^T * innovation > gamma * tr{E(innovation * innovation^T)}
         * @todo (lichao@holomatic.com) check correctness of this formula */
        {
            float32_t innovation_covariance_trace = 0.0f;
            matrixf_trace(&innovation_covariance, &innovation_covariance_trace);
            self->stability = vectorf_get_norm_sqr(&innovation) > self->stability_gamma * innovation_covariance_trace;
        }

        /// Step 5: Optimal kalman gain, K = P_j * H^T * S^(-1)
        /// Get the inverse of the innovation covariance
        struct Matrixf innovation_covariance_inverse;
        float32_t innovation_covariance_inverse_buff[MATRIXF_MIN_BUF_SIZE(obs_dimension_const, obs_dimension_const)];
        matrixf_init(&innovation_covariance_inverse, obs_dimension_const, obs_dimension_const,
                     innovation_covariance_inverse_buff,
                     MATRIXF_MIN_BUF_SIZE(obs_dimension_const, obs_dimension_const));
        matrixf_inverse(&innovation_covariance, &innovation_covariance_inverse);

        /// Get the kalman gain
        struct Matrixf kf_gain;
        float32_t      kf_gain_buff[MATRIXF_MIN_BUF_SIZE(state_dimension_const, obs_dimension_const)];
        matrixf_init(&kf_gain, state_dimension_const, obs_dimension_const, kf_gain_buff,
                     MATRIXF_MIN_BUF_SIZE(state_dimension_const, obs_dimension_const));
        matrixf_multiply(&self->priori_estimate_covariance, &mat_h_transpose, &kf_gain);
        matrixf_multiply(&kf_gain, &innovation_covariance_inverse, &kf_gain);

        /// Step 6: Update posteriori state estimate, x_k = x_j + K * y
        /// Get the temporary result: K * y
        struct Vectorf vec_gain_multi_innovation;
        float32_t      vec_gain_multi_innovation_buff[VECTORF_MIN_BUF_SIZE(state_dimension_const)];
        vectorf_init(&vec_gain_multi_innovation, state_dimension_const, vec_gain_multi_innovation_buff,
                     VECTORF_MIN_BUF_SIZE(state_dimension_const));
        vectorf_multiply_by_matrixf(&innovation, &kf_gain, &vec_gain_multi_innovation);
        vectorf_add(&self->current_state, &vec_gain_multi_innovation, &self->current_state);

        /// Step 7: Update posteriori estimate covariance, P_k = (I - K * H ) * P_j
        /// Creat the identity matrix
        struct Matrixf identity_mat;
        float32_t      identity_mat_buff[MATRIXF_MIN_BUF_SIZE(state_dimension_const, state_dimension_const)];
        matrixf_init(&identity_mat, state_dimension_const, state_dimension_const, identity_mat_buff,
                     MATRIXF_MIN_BUF_SIZE(state_dimension_const, state_dimension_const));
        matrixf_set_identity(&identity_mat);

        struct Matrixf temp_mat;
        float32_t      temp_mat_buff[MATRIXF_MIN_BUF_SIZE(state_dimension_const, state_dimension_const)];
        matrixf_init(&temp_mat, state_dimension_const, state_dimension_const, temp_mat_buff,
                     MATRIXF_MIN_BUF_SIZE(state_dimension_const, state_dimension_const));
        /// Get the result of K * H
        matrixf_multiply(&kf_gain, observation_model, &temp_mat);
        /// Get the result of (I - K * H)
        matrixf_sub(&identity_mat, &temp_mat, &temp_mat);
        /// Get the result of (I - K * H ) * P_j
        matrixf_multiply(&temp_mat, &self->priori_estimate_covariance, &self->priori_estimate_covariance);
        matrixf_add(&self->priori_estimate_covariance, &self->priori_estimate_covariance, &temp_mat);
        matrixf_multiply_float32(&temp_mat, 0.5f, &self->priori_estimate_covariance);

        return RC_SUCCESS;
    }
    else
    {
        return RC_NUMERICS_MATRIX_MIXED_SIZE;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t kalman_filterf_is_stable(struct KalmanFilterf const* self)
{
    assert(self != NULL);
    assert(kalman_filterf_is_valid(self));

    return self->stability;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t kalman_filterf_get_serialized_size(struct KalmanFilterf const* self)
{
    (void)self;

    uint32_t size = 0u;

    size += matrixf_get_serialized_size(&self->priori_estimate_covariance);
    size += vectorf_get_serialized_size(&self->current_state);
    size += sizeof(float32_t);
    size += sizeof(bool_t);

    return serialization_aligned_size(size);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t kalman_filterf_serialize(struct KalmanFilterf const* self, uint8_t* buffer, uint32_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

    retcode_t      rc                  = RC_SUCCESS;
    uint32_t       serialized_size     = 0u;
    uint32_t const expected_size_const = kalman_filterf_get_serialized_size(self);

    if (buffer_size < expected_size_const)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size +=
            vectorf_serialize(&self->current_state, buffer + serialized_size, buffer_size - serialized_size);
        serialized_size += matrixf_serialize(&self->priori_estimate_covariance, buffer + serialized_size,
                                             buffer_size - serialized_size);
        serialized_size +=
            serialize_float32(&self->stability_gamma, buffer + serialized_size, buffer_size - serialized_size);

        *(buffer + serialized_size) = self->stability;
        serialized_size += 1u;

        serialized_size += serialize_padding(serialized_size, buffer + serialized_size, buffer_size - serialized_size);

        assert(expected_size_const == serialized_size);
        rc = (retcode_t)(serialized_size);
    }

    return rc;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t kalman_filterf_deserialize(struct KalmanFilterf* self, uint8_t const* buffer, uint32_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

    retcode_t      rc                  = RC_SUCCESS;
    uint32_t       deserialized_size   = 0u;
    uint32_t const expected_size_const = kalman_filterf_get_serialized_size(self);

    if (expected_size_const > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size +=
            vectorf_deserialize(&self->current_state, buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += matrixf_deserialize(&self->priori_estimate_covariance, buffer + deserialized_size,
                                                 buffer_size - deserialized_size);
        deserialized_size +=
            deserialize_float32(&self->stability_gamma, buffer + deserialized_size, buffer_size - deserialized_size);
        self->stability = *(buffer + deserialized_size);
        deserialized_size += 1u;

        deserialized_size +=
            deserialize_padding(deserialized_size, buffer + deserialized_size, buffer_size - deserialized_size);

        assert(expected_size_const == deserialized_size);
        rc = (retcode_t)deserialized_size;
    }

    return rc;
}
