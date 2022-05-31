/*!
 * @brief implementation of point in 2D space.
 * @author lichao(lichao@holomaitc.com)
 * @date 2019-08-10
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *  notice.
 */

#include <assert.h>
#include <holo_c/core/epsilon.h>
#include <holo_c/geometry/point2_float32.h>
#include <holo_c/geometry/rot2_float32.h>
#include <holo_c/utils/serialization.h>
#include <math.h>
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static retcode_t rot2f_normalize(struct Rot2f* self)
{
    assert(self != NULL);
    retcode_t rc = RC_SUCCESS;

    /* compute the norm of sin(theta) and cos(theta) */
    float32_t norm = (self->c * self->c) + (self->s * self->s);

    /* normalize when norm isn't equal to 1 */
    if (fabsf(norm - 1.0) > holo_float32_epsilon)
    {
        norm = powf(norm, -0.5);
        self->c *= norm;
        self->s *= norm;
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot2f_init(struct Rot2f* self)
{
    assert(self != NULL);

    retcode_t rc = RC_SUCCESS;

    rot2f_init_from_angle(self, 0.0);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot2f_init_from_angle(struct Rot2f* self, const float32_t theta)
{
    assert(self != NULL);
    assert(!isnan(theta));

    retcode_t rc = RC_SUCCESS;

    self->c = cosf(theta);
    self->s = sinf(theta);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot2f_init_from_matrix(struct Rot2f* self, const struct Matrixf* in)
{
    assert(self != NULL);
    assert(matrixf_is_valid(in));

    retcode_t rc = RC_SUCCESS;
    /* compute inverse of input matrix */
    struct Matrixf inverse_m;
    float32_t      inverse_m_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&inverse_m, 2, 2, inverse_m_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    matrixf_inverse(in, &inverse_m);

    /* compute transpose of input matrix */
    struct Matrixf transpose_m;
    float32_t      transpose_m_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&transpose_m, 2, 2, transpose_m_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    matrixf_transpose(in, &transpose_m);

    /* check if inverse matrix is equal to transpose matrix */
    if (!matrixf_is_equal(&inverse_m, &transpose_m))
    {
        rc = RC_FAIL;
    }

    /* compute determinate of input matrix */
    float32_t det = 0.0;
    matrixf_determinant(&inverse_m, &det);

    /* check if determinate is equal to 1 */
    if (fabsf(det - 1.0) > holo_float32_epsilon)
    {
        rc = RC_FAIL;
    }

    /* set coefficients */
    matrixf_get(in, 0, 0, &self->c);
    matrixf_get(in, 1, 0, &self->s);

    /* normalize 2D rotation */
    rot2f_normalize(self);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot2f_init_from_rot2f(struct Rot2f* self, const struct Rot2f* in)
{
    assert(self != NULL);
    assert(in != NULL);
    assert(rot2f_is_valid(in));

    retcode_t rc = RC_SUCCESS;

    self->c = in->c;
    self->s = in->s;

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot2f_inverse(const struct Rot2f* self, struct Rot2f* out)
{
    assert(rot2f_is_valid(self));

    retcode_t rc = RC_SUCCESS;

    float32_t theta = 0.0;

    /* get theta from 2D rotation */
    rc = rot2f_get_angle(self, &theta);

    /* negate theta and use it initial a 2D rotation */
    rc = rot2f_init_from_angle(out, -theta);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot2f_rotate_point2f(const struct Rot2f* self, const struct Point2f* in, struct Point2f* out)
{
    assert(rot2f_is_valid(self));
    assert(point2f_is_valid((const struct Point2f*)in));

    retcode_t rc = RC_SUCCESS;

    /* get 2D vector from 2D point */
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&vec, 2, vec_buf, VECTORF_MIN_BUF_SIZE(2u));
    point2f_to_vector2f(in, &vec);

    /* multiply rotation matrix by vector */
    struct Matrixf matrix;
    float32_t      matrix_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&matrix, 2, 2, matrix_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    rot2f_to_matrix22f(self, &matrix);

    struct Vectorf vec_out;
    float32_t      vec_out_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&vec_out, 2, vec_out_buf, VECTORF_MIN_BUF_SIZE(2u));
    matrixf_multiply(&matrix, (const struct Matrixf*)&vec, (struct Matrixf*)&vec_out);

    /* convert result 2D vector to 2D point */
    point2f_init_from_vector2f(out, &vec_out);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot2f_rotate_vector2f(const struct Rot2f* self, const struct Vectorf* in, struct Vectorf* out)
{
    assert(rot2f_is_valid(self));
    assert(vectorf_is_valid(in));

    retcode_t rc = RC_SUCCESS;

    /* multiply rotation matrix by vector */
    struct Matrixf matrix;
    float32_t      matrix_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&matrix, 2, 2, matrix_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    rot2f_to_matrix22f(self, &matrix);
    matrixf_multiply(&matrix, (const struct Matrixf*)in, (struct Matrixf*)out);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot2f_unrotate_point2f(const struct Rot2f* self, const struct Point2f* in, struct Point2f* out)
{
    assert(rot2f_is_valid(self));
    assert(point2f_is_valid(in));

    retcode_t rc = RC_SUCCESS;

    /* get 2D vector from 2D point */
    struct Vectorf vec;
    float32_t      vec_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&vec, 2, vec_buf, VECTORF_MIN_BUF_SIZE(2u));
    point2f_to_vector2f(in, &vec);

    /* multiply inverse rotation matrix by vector */
    struct Matrixf matrix;
    float32_t      matrix_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&matrix, 2, 2, matrix_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    rot2f_to_matrix22f(self, &matrix);
    struct Matrixf matrix_inverse;
    float32_t      matrix_inverse_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&matrix_inverse, 2, 2, matrix_inverse_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    matrixf_inverse(&matrix, &matrix_inverse);

    struct Vectorf vec_out;
    float32_t      vec_out_buf[VECTORF_MIN_BUF_SIZE(2u)];
    vectorf_init(&vec_out, 2, vec_out_buf, VECTORF_MIN_BUF_SIZE(2u));
    matrixf_multiply(&matrix_inverse, (const struct Matrixf*)&vec, (struct Matrixf*)&vec_out);

    /* convert result 2D vector to 2D point */
    point2f_init_from_vector2f(out, &vec_out);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot2f_unrotate_vector2f(const struct Rot2f* self, const struct Vectorf* in, struct Vectorf* out)
{
    assert(rot2f_is_valid(self));
    assert(vectorf_is_valid(in));

    retcode_t rc = RC_SUCCESS;

    /* multiply inverse rotation matrix by vector */
    struct Matrixf matrix;
    float32_t      matrix_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&matrix, 2, 2, matrix_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    rot2f_to_matrix22f(self, &matrix);
    struct Matrixf matrix_inverse;
    float32_t      matrix_inverse_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&matrix_inverse, 2, 2, matrix_inverse_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    matrixf_inverse(&matrix, &matrix_inverse);
    matrixf_multiply(&matrix_inverse, (const struct Matrixf*)in, (struct Matrixf*)out);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot2f_compose(const struct Rot2f* self, const struct Rot2f* other, struct Rot2f* out)
{
    assert(rot2f_is_valid(self));
    assert(rot2f_is_valid(other));

    retcode_t rc = RC_SUCCESS;

    struct Matrixf mat1;
    float32_t      mat1_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&mat1, 2, 2, mat1_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    struct Matrixf mat2;
    float32_t      mat2_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&mat2, 2, 2, mat2_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    struct Matrixf mat3;
    float32_t      mat3_buf[MATRIXF_MIN_BUF_SIZE(2u, 2u)];
    matrixf_init(&mat3, 2, 2, mat3_buf, MATRIXF_MIN_BUF_SIZE(2u, 2u));
    rot2f_to_matrix22f(self, &mat1);
    rot2f_to_matrix22f(other, &mat2);
    matrixf_multiply(&mat1, &mat2, &mat3);

    /* generate 2D rotation with result matrix */
    rot2f_init_from_matrix(out, &mat3);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t rot2f_is_equal(const struct Rot2f* self, const struct Rot2f* other)
{
    assert(self != NULL);
    assert(other != NULL);
    assert(rot2f_is_valid(self));
    assert(rot2f_is_valid(other));

    bool_t flag = false;

    if ((fabs(self->c - other->c) < holo_float32_epsilon) && (fabs(self->s - other->s) < holo_float32_epsilon))
    {
        flag = true;
    }

    return flag;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot2f_to_matrix22f(const struct Rot2f* self, struct Matrixf* out)
{
    assert(self != NULL);
    assert(rot2f_is_valid(self));

    retcode_t rc = RC_SUCCESS;

    /* set rotation matrix
       out = [cos(theta)  -sin(theta)
              sin(theta)   cos(theta)] */
    uint16_t data_idx = 0;
    for (data_idx = 0; data_idx < out->capacity; data_idx++)
        out->base[data_idx] = 0.0f;
    matrixf_set(out, 0, 0, self->c);
    matrixf_set(out, 0, 1, -self->s);
    matrixf_set(out, 1, 0, self->s);
    matrixf_set(out, 1, 1, self->c);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline retcode_t rot2f_get_angle(const struct Rot2f* self, float32_t* out)
{
    assert(self != NULL);
    assert(rot2f_is_valid(self));

    retcode_t rc = RC_SUCCESS;

    *out = atan2f(self->s, self->c);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot2f_set_identity(struct Rot2f* self)
{
    assert(rot2f_is_valid(self));
    retcode_t rc = RC_SUCCESS;

    /* initialize from zero angle */
    rot2f_init(self);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot2f_to_string(const struct Rot2f* self, char_t* string_buf, uint32_t buffer_length)
{
    assert(rot2f_is_valid(self));
    retcode_t rc = RC_SUCCESS;

    /* get theta angle */
    float32_t theta = 0.0f;
    rot2f_get_angle(self, &theta);

    snprintf(string_buf, buffer_length, "rot2: (%f) (%f, %f)", theta, self->c, self->s);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t rot2f_is_valid(const struct Rot2f* self)
{
    assert(self != NULL);
    bool_t flag = true;

    /* check if meet Pythagorean Identities: sin(x)^2 + cos(x)^2 = 1 */
    if (!(fabs((self->c * self->c) + (self->s * self->s) - 1.0) < holo_float32_epsilon))
    {
        flag = false;
    }

    return flag;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t rot2f_get_serialized_size(const struct Rot2f* self)
{
    (void)self;
    HOLO_STATIC_ASSERT(sizeof(struct Rot2f) % 8 == 0);
    return sizeof(struct Rot2f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot2f_serialize(const struct Rot2f* self, uint8_t* buffer, uint32_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    uint32_t serialized_size = 0;
    uint32_t expected_size = rot2f_get_serialized_size(self);

    if (expected_size > buffer_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += serialize_float32(&self->c, buffer, buffer_size);
        serialized_size += serialize_float32(&self->s, 
                                             buffer + serialized_size, 
                                             buffer_size - serialized_size);
        assert(expected_size == serialized_size);
        rc = (retcode_t)serialized_size;
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t rot2f_deserialize(struct Rot2f* self, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    uint32_t deserialized_size = 0;
    uint32_t expected_size = rot2f_get_serialized_size(self); // fixed size object.

    if (expected_size > buffer_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size += deserialize_float32(&self->c, buffer, buffer_size);
        deserialized_size += deserialize_float32(&self->s, 
                                                 buffer + deserialized_size, 
                                                 buffer_size - deserialized_size);
        assert(expected_size == deserialized_size);
        rc = (retcode_t)deserialized_size;
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
