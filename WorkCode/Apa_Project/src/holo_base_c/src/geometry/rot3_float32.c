/*!
 * @file rot3_float32.c
 * @brief rot3 implementation
 * @author liuya(liuya@holomaitc.com), duyanwei@holomatic.com
 * @date 2019-08-11
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <holo_c/geometry/rot3_float32.h>
#include <holo_c/utils/serialization.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot3f_init(struct Rot3f* self)
{
    assert(self != NULL);
    matrixf_init(&(self->m), 3, 3, self->matrix_data, MATRIXF_MIN_BUF_SIZE(3u, 3u));
    retcode_t rc = matrixf_set_identity(&self->m);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot3f_init_from_scalars(struct Rot3f* self, const float32_t m00, const float32_t m01, const float32_t m02,
                                  const float32_t m10, const float32_t m11, const float32_t m12, const float32_t m20,
                                  const float32_t m21, const float32_t m22)
{
    assert(self != NULL);

    retcode_t rc = RC_SUCCESS;
    matrixf_init(&(self->m), 3, 3, self->matrix_data, MATRIXF_MIN_BUF_SIZE(3u, 3u));
    rc = matrixf_set(&self->m, 0u, 0u, m00);
    rc = matrixf_set(&self->m, 0u, 1u, m01);
    rc = matrixf_set(&self->m, 0u, 2u, m02);
    rc = matrixf_set(&self->m, 1u, 0u, m10);
    rc = matrixf_set(&self->m, 1u, 1u, m11);
    rc = matrixf_set(&self->m, 1u, 2u, m12);
    rc = matrixf_set(&self->m, 2u, 0u, m20);
    rc = matrixf_set(&self->m, 2u, 1u, m21);
    rc = matrixf_set(&self->m, 2u, 2u, m22);

    if (!rot3f_is_valid(self))
    {
        rc = RC_FAIL;
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot3f_init_from_rot3f(struct Rot3f* self, const struct Rot3f* other)
{
    assert(self != NULL);
    assert(true == rot3f_is_valid(other));

    self->m.rows     = 3u ;
    self->m.cols     = 3u ;
    self->m.size     = 9 ;
    self->m.pitchx   = MATRIXF_ELE_ALIGN_CNT(3u);
    self->m.pitchy   = MATRIXF_ELE_ALIGN_CNT(3u);
    self->m.capacity = MATRIXF_MIN_BUF_SIZE(3u, 3u) ;
    self->m.base     = self->matrix_data ;
    uint16_t data_idx = 0;
    for (data_idx = 0; data_idx < self->m.capacity; data_idx++)
        self->m.base[data_idx] = 0.0f;

    retcode_t rc = matrixf_set_from_matrixf(&self->m, &other->m) ;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t rot3f_is_valid(const struct Rot3f* self)
{
    assert(self != NULL);

    bool_t flag = matrixf_is_valid(&self->m);

    if (flag)
    {
        struct Matrixf m_inv;
        float32_t      m_inv_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
        matrixf_init(&m_inv, 3, 3, m_inv_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));
        matrixf_inverse(&self->m, &m_inv);

        struct Matrixf m_transpose;
        float32_t      m_transpose_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
        matrixf_init(&m_transpose, 3, 3, m_transpose_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));
        matrixf_transpose(&self->m, &m_transpose);

        float32_t det = 0.0f;
        matrixf_determinant(&self->m, &det);
        flag = matrixf_is_equal(&m_inv, &m_transpose) && (fabsf(det - 1.0f) <= holo_float32_epsilon);
    }

    return flag;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t rot3f_is_equal(const struct Rot3f* self, const struct Rot3f* other)
{
    assert(true == rot3f_is_valid(self));
    assert(true == rot3f_is_valid(other));

    return matrixf_is_equal(&self->m, &other->m);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot3f_to_matrix33f(const struct Rot3f* self, struct Matrixf* matrix)
{
    assert(true == rot3f_is_valid(self));
    assert(true == matrixf_is_valid(matrix));

    return matrixf_set_from_matrixf(matrix, &self->m);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot3f_transpose(const struct Rot3f* self, struct Rot3f* out)
{
    assert(true == rot3f_is_valid(self));
    assert(true == rot3f_is_valid(out));

    return matrixf_transpose(&self->m, &out->m);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot3f_inverse(const struct Rot3f* self, struct Rot3f* out)
{
    return rot3f_transpose(self, out);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot3f_rotate_vector3f(const struct Rot3f* self, const struct Vectorf* vector, struct Vectorf* out)
{
    assert(true == rot3f_is_valid(self));
    assert(true == vectorf_is_valid(vector));
    assert(true == vectorf_is_valid(out));

    return vectorf_multiply_by_matrixf(vector, &self->m, out);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot3f_unrotate_vector3f(const struct Rot3f* self, const struct Vectorf* vector, struct Vectorf* out)
{
    assert(true == rot3f_is_valid(self));
    assert(true == vectorf_is_valid(vector));
    assert(true == vectorf_is_valid(out));

    retcode_t rc = RC_SUCCESS;

    struct Rot3f self_inv;
    rc = rot3f_init(&self_inv);
    rc = rot3f_inverse(self, &self_inv);
    rc = rot3f_rotate_vector3f(&self_inv, vector, out);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot3f_multiply_vector3f(const struct Rot3f* self, const struct Vectorf* vector, struct Vectorf* out)
{
    return rot3f_rotate_vector3f(self, vector, out);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot3f_rotate_point3f(const struct Rot3f* self, const struct Point3f* point, struct Point3f* out)
{
    assert(true == rot3f_is_valid(self));
    assert(true == point3f_is_valid(point));
    assert(out != NULL);

    retcode_t rc = RC_SUCCESS;

    struct Vectorf vec_in;
    float32_t      vec_in_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec_in, 3, vec_in_buf, VECTORF_MIN_BUF_SIZE(3u));
    rc = point3f_to_vector3f(point, &vec_in);

    struct Vectorf vec_out;
    float32_t      vec_out_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec_out, 3, vec_out_buf, VECTORF_MIN_BUF_SIZE(3u));
    rc = rot3f_rotate_vector3f(self, &vec_in, &vec_out);
    rc = point3f_init_from_vector3f(out, &vec_out);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot3f_unrotate_point3f(const struct Rot3f* self, const struct Point3f* point, struct Point3f* out)
{
    assert(true == rot3f_is_valid(self));
    assert(true == point3f_is_valid(point));
    assert(out != NULL);

    retcode_t rc = RC_SUCCESS;

    struct Rot3f self_inv;
    rc = rot3f_init(&self_inv);
    rc = rot3f_inverse(self, &self_inv);
    rc = rot3f_rotate_point3f(&self_inv, point, out);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot3f_multiply_point3f(const struct Rot3f* self, const struct Point3f* point, struct Point3f* out)
{
    return rot3f_rotate_point3f(self, point, out);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot3f_compose(const struct Rot3f* self, const struct Rot3f* other, struct Rot3f* out)
{
    assert(true == rot3f_is_valid(self));
    assert(true == rot3f_is_valid(other));
    assert(true == rot3f_is_valid(out));

    return matrixf_multiply(&self->m, &other->m, &out->m);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot3f_multiply(const struct Rot3f* self, const struct Rot3f* other, struct Rot3f* out)
{
    return rot3f_compose(self, other, out);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot3f_expmap(struct Rot3f* self, const struct Vectorf* vector)
{
    assert(true == rot3f_is_valid(self));
    assert(true == vectorf_is_valid(vector));

    retcode_t rc = RC_SUCCESS;

    const float32_t theta = vectorf_get_norm(vector);

    if (theta <= holo_float32_epsilon)
    {
        rot3f_set_identity(self);
    }
    else
    {
        // r = cos(theta) * I3x3 + (1-cos(theta) * a * a^T) + sin(theta) * a^;
        struct Vectorf axis;
        float32_t      axis_buf[VECTORF_MIN_BUF_SIZE(3u)];
        vectorf_init(&axis, 3, axis_buf, VECTORF_MIN_BUF_SIZE(3u));
        vectorf_set_from_vectorf(&axis, vector);
        vectorf_normalize(&axis);

        float32_t wx, wy, wz;
        vectorf_get(&axis, 0u, &wx);
        vectorf_get(&axis, 1u, &wy);
        vectorf_get(&axis, 2u, &wz);

        const float32_t cn = cosf(theta);
        const float32_t sn = sinf(theta);

        const float32_t value = 1.0f - cn;
        const float32_t c00   = value * wx * wx;
        const float32_t c10   = value * wy * wx;
        const float32_t c11   = value * wy * wy;
        const float32_t c20   = value * wz * wx;
        const float32_t c21   = value * wz * wy;
        const float32_t c22   = value * wz * wz;

        struct Matrixf skew;
        float32_t      skew_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
        matrixf_init(&skew, 3, 3, skew_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));
        vectorf_to_skew_symmetric(&axis, &skew);
        matrixf_multiply_float32(&skew, sn, &skew);

        float32_t s01, s02, s10, s12, s20, s21;
        matrixf_get(&skew, 0u, 1u, &s01);
        matrixf_get(&skew, 0u, 2u, &s02);
        matrixf_get(&skew, 1u, 0u, &s10);
        matrixf_get(&skew, 1u, 2u, &s12);
        matrixf_get(&skew, 2u, 0u, &s20);
        matrixf_get(&skew, 2u, 1u, &s21);

        rc = rot3f_init_from_scalars(self, cn + c00, c10 + s01, c20 + s02, c10 + s10, cn + c11, c21 + s12, c20 + s20,
                                     c21 + s21, cn + c22);
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot3f_logmap(const struct Rot3f* self, struct Vectorf* vector)
{
    assert(true == rot3f_is_valid(self));
    assert(true == vectorf_is_valid(vector));

    retcode_t rc = RC_SUCCESS;

    // returned value in vector
    float32_t array[3] = {0.0f};

    // get each single element of the matrix
    const float32_t r11 = rot3f_get_r00(self);
    const float32_t r12 = rot3f_get_r01(self);
    const float32_t r13 = rot3f_get_r02(self);
    const float32_t r21 = rot3f_get_r10(self);
    const float32_t r22 = rot3f_get_r11(self);
    const float32_t r23 = rot3f_get_r12(self);
    const float32_t r31 = rot3f_get_r20(self);
    const float32_t r32 = rot3f_get_r21(self);
    const float32_t r33 = rot3f_get_r22(self);

    // get trace of the matrix
    float32_t trace;
    rc = matrixf_trace(&(self->m), &trace);

    // check if theta is close to +-pi, +-3pi, ...(trace = -1)
    if (fabsf(trace + 1.0f) < holo_float32_epsilon)
    {
        const float32_t theta = M_PI;
        if (fabs(r33 + 1.0f) > holo_float32_epsilon)
        {
            const float32_t factor = theta / sqrtf(2.0f + 2.0f * r33);

            array[0] = factor * r13;
            array[1] = factor * r23;
            array[2] = factor * (1.0f + r33);
        }
        else if (fabs(r22 + 1.0f) > holo_float32_epsilon)
        {
            const float32_t factor = theta / sqrtf(2.0f + 2.0f * r22);

            array[0] = factor * r12;
            array[1] = factor * (1.0f + r22);
            array[2] = factor * r22;
        }
        else
        {
            const float32_t factor = theta / sqrtf(2.0f + 2.0f * r11);

            array[0] = factor * (1.0 + r11);
            array[1] = factor * r21;
            array[2] = factor * r31;
        }
    }
    else
    {
        float32_t factor;
        // check if theta is close to 0,  +-2pi, +-4pi, ...(trace = 3)
        if (fabs(trace - 3.0f) < holo_float32_epsilon)
        {
            const float32_t value = trace - 3.0f;
            factor                = 0.5f - value * value / 12.0f;
        }
        else
        {
            const float32_t theta = acosf((trace - 1.0f) / 2.0f);
            factor                = theta / (2.0f * sinf(theta));
        }

        array[0] = factor * (r32 - r23);
        array[1] = factor * (r13 - r31);
        array[2] = factor * (r21 - r12);
    }

    vectorf_set_from_array(vector, array, 3);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot3f_from_angle_axis(struct Rot3f* self, const struct Vectorf* vector)
{
    return rot3f_expmap(self, vector);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot3f_to_angle_axis(const struct Rot3f* self, struct Vectorf* vector)
{
    return rot3f_logmap(self, vector);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float32_t rot3f_compute_angle_diff(const struct Rot3f* self, const struct Rot3f* other)
{
    assert(true == rot3f_is_valid(self));
    assert(true == rot3f_is_valid(other));

    struct Rot3f rot_inv;
    rot3f_init(&rot_inv);
    rot3f_inverse(self, &rot_inv);

    struct Rot3f rot_diff;
    rot3f_init(&rot_diff);
    rot3f_compose(&rot_inv, other, &rot_diff);

    struct Vectorf vec_diff;
    float32_t      vec_diff_buf[VECTORF_MIN_BUF_SIZE(3u)];
    vectorf_init(&vec_diff, 3, vec_diff_buf, VECTORF_MIN_BUF_SIZE(3u));
    rot3f_logmap(&rot_diff, &vec_diff);
    return vectorf_get_norm(&vec_diff);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot3f_from_rpy(struct Rot3f* self, const float32_t roll, const float32_t pitch, const float32_t yaw)
{
    assert(true == rot3f_is_valid(self));

    const float32_t cnx = cosf(roll);
    const float32_t snx = sinf(roll);
    const float32_t cny = cosf(pitch);
    const float32_t sny = sinf(pitch);
    const float32_t cnz = cosf(yaw);
    const float32_t snz = sinf(yaw);
    const float32_t c00 = cnz * cny;
    const float32_t c01 = cnz * sny * snx - snz * cnx;
    const float32_t c02 = cnz * sny * cnx + snz * snx;
    const float32_t c10 = snz * cny;
    const float32_t c11 = snz * sny * snx + cnz * cnx;
    const float32_t c12 = snz * sny * cnx - cnz * snx;
    const float32_t c20 = -sny;
    const float32_t c21 = cny * snx;
    const float32_t c22 = cny * cnx;

    return rot3f_init_from_scalars(self, c00, c01, c02, c10, c11, c12, c20, c21, c22);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot3f_from_ypr(struct Rot3f* self, const float32_t yaw, const float32_t pitch, const float32_t roll)
{
    return rot3f_from_rpy(self, roll, pitch, yaw);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot3f_from_roll(struct Rot3f* self, const float32_t roll)
{
    return rot3f_from_rpy(self, roll, 0.0f, 0.0f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot3f_from_pitch(struct Rot3f* self, const float32_t pitch)
{
    return rot3f_from_rpy(self, 0.0f, pitch, 0.0f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot3f_from_yaw(struct Rot3f* self, const float32_t yaw)
{
    return rot3f_from_rpy(self, 0.0f, 0.0f, yaw);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot3f_to_ypr(const struct Rot3f* self, float32_t* yaw, float32_t* pitch, float32_t* roll)
{
    assert(true == rot3f_is_valid(self));
    assert(yaw != NULL);
    assert(pitch != NULL);
    assert(roll != NULL);

    float32_t a21, a22;

    matrixf_get(&(self->m), 2u, 1u, &a21);
    matrixf_get(&(self->m), 2u, 2u, &a22);

    const float32_t x = atan2f(a21, a22);
    struct Rot3f    Qx;
    rot3f_init(&Qx);
    rot3f_from_roll(&Qx, -x);

    struct Matrixf B;
    float32_t      B_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&B, 3, 3, B_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));
    matrixf_multiply(&(self->m), &(Qx.m), &B);

    float32_t b20, b22;
    matrixf_get(&B, 2u, 0u, &b20);
    matrixf_get(&B, 2u, 2u, &b22);

    const float32_t y = atan2f(-b20, b22);

    struct Rot3f Qy;
    rot3f_init(&Qy);
    rot3f_from_pitch(&Qy, -y);

    struct Matrixf C;
    float32_t      C_buf[MATRIXF_MIN_BUF_SIZE(3u, 3u)];
    matrixf_init(&C, 3, 3, C_buf, MATRIXF_MIN_BUF_SIZE(3u, 3u));

    matrixf_multiply(&B, &(Qy.m), &C);

    float32_t c10, c11;
    matrixf_get(&C, 1u, 0u, &c10);
    matrixf_get(&C, 1u, 1u, &c11);

    const float32_t z = atan2f(c10, c11);

    *roll  = x;
    *pitch = y;
    *yaw   = z;

    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot3f_to_rpy(const struct Rot3f* self, float32_t* roll, float32_t* pitch, float32_t* yaw)
{
    return rot3f_to_ypr(self, yaw, pitch, roll);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot3f_set_identity(struct Rot3f* self)
{
    assert(true == rot3f_is_valid(self));
    return matrixf_set_identity(&self->m);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float32_t rot3f_get_r00(const struct Rot3f* self)
{
    assert(true == rot3f_is_valid(self));
    float32_t value;
    matrixf_get(&self->m, 0u, 0u, &value);
    return value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float32_t rot3f_get_r01(const struct Rot3f* self)
{
    assert(true == rot3f_is_valid(self));
    float32_t value;
    matrixf_get(&self->m, 0u, 1u, &value);
    return value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float32_t rot3f_get_r02(const struct Rot3f* self)
{
    assert(true == rot3f_is_valid(self));
    float32_t value;
    matrixf_get(&self->m, 0u, 2u, &value);
    return value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float32_t rot3f_get_r10(const struct Rot3f* self)
{
    assert(true == rot3f_is_valid(self));
    float32_t value;
    matrixf_get(&self->m, 1u, 0u, &value);
    return value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float32_t rot3f_get_r11(const struct Rot3f* self)
{
    assert(true == rot3f_is_valid(self));
    float32_t value;
    matrixf_get(&self->m, 1u, 1u, &value);
    return value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float32_t rot3f_get_r12(const struct Rot3f* self)
{
    assert(true == rot3f_is_valid(self));
    float32_t value;
    matrixf_get(&self->m, 1u, 2u, &value);
    return value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float32_t rot3f_get_r20(const struct Rot3f* self)
{
    assert(true == rot3f_is_valid(self));
    float32_t value;
    matrixf_get(&self->m, 2u, 0u, &value);
    return value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float32_t rot3f_get_r21(const struct Rot3f* self)
{
    assert(true == rot3f_is_valid(self));
    float32_t value;
    matrixf_get(&self->m, 2u, 1u, &value);
    return value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float32_t rot3f_get_r22(const struct Rot3f* self)
{
    assert(true == rot3f_is_valid(self));
    float32_t value;
    matrixf_get(&self->m, 2u, 2u, &value);
    return value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot3f_to_quaternionf(const struct Rot3f* self, struct Quaternionf* quaternion)
{
    assert(true == rot3f_is_valid(self));
    assert(quaternion != NULL);

    float32_t w, x, y, z;
    {
        struct Vectorf vector;
        float32_t      vector_buf[VECTORF_MIN_BUF_SIZE(3u)];
        vectorf_init(&vector, 3, vector_buf, VECTORF_MIN_BUF_SIZE(3u));

        rot3f_logmap(self, &vector);
        float32_t theta = vectorf_get_norm(&vector);
        vectorf_normalize(&vector);
        theta /= 2.0f;

        const float32_t costheta = cosf(theta);
        const float32_t sintheta = sinf(theta);
        vectorf_multiply_float32(&vector, sintheta, &vector);

        w = costheta;
        vectorf_get(&vector, 0u, &x);
        vectorf_get(&vector, 1u, &y);
        vectorf_get(&vector, 2u, &z);
    }

    quaternionf_init_from_scalars(quaternion, w, x, y, z);

    return RC_SUCCESS;
}

uint32_t rot3f_get_serialized_size(const struct Rot3f* self)
{
    uint32_t size = matrixf_get_serialized_size(&self->m);

    return serialization_aligned_size(size);
}

retcode_t rot3f_serialize(const struct Rot3f* self, uint8_t* buffer, uint32_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    uint32_t serialized_size = 0;
    uint32_t expected_size = rot3f_get_serialized_size(self);

    if (expected_size > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += matrixf_serialize(&self->m, 
                buffer, 
                buffer_size);

        serialized_size += serialize_padding(serialized_size,
                buffer + serialized_size,
                buffer_size - serialized_size);

        assert(expected_size == serialized_size);
        rc = (retcode_t)serialized_size;
    }

    return rc;
}

retcode_t rot3f_deserialize(struct Rot3f* self, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    uint32_t deserialized_size = 0;
    uint32_t expected_size = rot3f_get_serialized_size(self);

    if (expected_size > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size += matrixf_deserialize(&self->m, buffer, buffer_size);

        deserialized_size += deserialize_padding(deserialized_size,
                buffer + deserialized_size, 
                buffer_size - deserialized_size);


        assert(expected_size == deserialized_size);
        rc = (retcode_t)deserialized_size;
    }

    return rc;
}

