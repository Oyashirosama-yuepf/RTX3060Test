/*!
 * @file point3_float64.c
 * @brief This header file defines 3f point.
 * @author liuya(liuya@holomaitc.com)
 * @date 2018-12-27
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <assert.h>
#include <math.h>

#include <holo_c/core/epsilon.h>
#include <holo_c/geometry/point3_float64.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3d_init_from_scalars(struct Point3d* self, const float64_t x, const float64_t y, const float64_t z)
{
    assert(self != NULL);

    self->x = x;
    self->y = y;
    self->z = z;

    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3d_init(struct Point3d* self)
{
    return point3d_init_from_scalars(self, 0.0f, 0.0f, 0.0f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3d_init_from_array(struct Point3d* self, const float64_t* array, const uint8_t array_size)
{
    assert(self != NULL);
    assert(array != NULL);

    retcode_t rc = RC_SUCCESS;

    if (array_size < point3d_dim())
    {
        rc = RC_FAIL;
    }
    else
    {
        self->x = array[0];
        self->y = array[1];
        self->z = array[2];

        rc = RC_SUCCESS;
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t point3d_is_valid(const struct Point3d* self)
{
    assert(self != NULL);

    bool_t flag = true;

    if (isnan(self->x) || isnan(self->y) || isnan(self->z))
    {
        flag = false;
    }

    return flag;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t point3d_is_equal(const struct Point3d* self, const struct Point3d* other)
{
    assert(true == point3d_is_valid(self));
    assert(true == point3d_is_valid(other));

    bool_t flag = true;

    const float64_t diff_x = self->x - other->x;
    const float64_t diff_y = self->y - other->y;
    const float64_t diff_z = self->z - other->z;

    if ((fabsf(diff_x) > holo_float64_epsilon) || (fabsf(diff_y) > holo_float64_epsilon) ||
        (fabsf(diff_z) > holo_float64_epsilon))
    {
        flag = false;
    }

    return flag;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3d_init_from_point3d(struct Point3d* self, const struct Point3d* other)
{
    assert(self != NULL);
    assert(true == point3d_is_valid(other));

    self->x = other->x;
    self->y = other->y;
    self->z = other->z;

    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3d_add(const struct Point3d* self, const struct Point3d* other, struct Point3d* out)
{
    assert(true == point3d_is_valid(self));
    assert(true == point3d_is_valid(other));
    assert(out != NULL);

    out->x = self->x + other->x;
    out->y = self->y + other->y;
    out->z = self->z + other->z;

    retcode_t rc = RC_SUCCESS;

    if (!point3d_is_valid(out))
    {
        rc = RC_FAIL;
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3d_negate(struct Point3d* self)
{
    return point3d_multiply_float64(self, -1.0f, self);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3d_multiply_float64(const struct Point3d* self, const float64_t scalar, struct Point3d* out)
{
    assert(true == point3d_is_valid(self));
    assert(out != NULL);

    out->x = self->x * scalar;
    out->y = self->y * scalar;
    out->z = self->z * scalar;

    retcode_t rc = RC_SUCCESS;

    if (!point3d_is_valid(out))
    {
        rc = RC_FAIL;
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3d_divide_float64(const struct Point3d* self, const float64_t scalar, struct Point3d* out)
{
    assert(true == point3d_is_valid(self));
    assert(out != NULL);

    retcode_t rc = RC_SUCCESS;

    if (fabsf(scalar) <= holo_float64_epsilon)
    {
        rc = RC_FAIL;
    }
    else
    {
        out->x = self->x / scalar;
        out->y = self->y / scalar;
        out->z = self->z / scalar;

        if (!point3d_is_valid(out))
        {
            rc = RC_FAIL;
        }
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3d_dist_sqr(const struct Point3d* self, const struct Point3d* other, float64_t* dist_sqr)
{
    assert(true == point3d_is_valid(self));
    assert(true == point3d_is_valid(other));
    assert(dist_sqr != NULL);

    const float64_t diff_x = self->x - other->x;
    const float64_t diff_y = self->y - other->y;
    const float64_t diff_z = self->z - other->z;

    *dist_sqr = diff_x * diff_x + diff_y * diff_y + diff_z * diff_z;

    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3d_dist(const struct Point3d* self, const struct Point3d* other, float64_t* dist)
{
    const retcode_t rc = point3d_dist_sqr(self, other, dist);
    if (rc == RC_SUCCESS)
    {
        *dist = sqrtf(*dist);
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t point3d_is_finite(const struct Point3d* self)
{
    assert(true == point3d_is_valid(self));

    return (!isnan(self->x)) && (!isnan(self->y)) && (!isnan(self->z));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t point3d_is_zero(const struct Point3d* self)
{
    assert(true == point3d_is_valid(self));

    return (fabsf(self->x) <= holo_float64_epsilon) && (fabsf(self->y) <= holo_float64_epsilon) &&
           (fabsf(self->z) <= holo_float64_epsilon);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3d_set_constant(struct Point3d* self, const float64_t value)
{
    assert(self != NULL);

    self->x = value;
    self->y = value;
    self->z = value;

    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3d_set_zero(struct Point3d* self)
{
    return point3d_set_constant(self, 0.0f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3d_set_unit_x(struct Point3d* self)
{
    return point3d_init_from_scalars(self, 1.0f, 0.0f, 0.0f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3d_set_unit_y(struct Point3d* self)
{
    return point3d_init_from_scalars(self, 0.0f, 1.0f, 0.0f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3d_set_unit_z(struct Point3d* self)
{
    return point3d_init_from_scalars(self, 0.0f, 0.0f, 1.0f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float64_t point3d_get_x(const struct Point3d* self)
{
    assert(true == point3d_is_valid(self));

    return self->x;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float64_t point3d_get_y(const struct Point3d* self)
{
    assert(true == point3d_is_valid(self));

    return self->y;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float64_t point3d_get_z(const struct Point3d* self)
{
    assert(true == point3d_is_valid(self));

    return self->z;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3d_set_x(struct Point3d* self, const float64_t value)
{
    assert(true == point3d_is_valid(self));

    self->x = value;

    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3d_set_y(struct Point3d* self, const float64_t value)
{
    assert(true == point3d_is_valid(self));

    self->y = value;

    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t point3d_set_z(struct Point3d* self, const float64_t value)
{
    assert(true == point3d_is_valid(self));

    self->z = value;

    return RC_SUCCESS;
}
