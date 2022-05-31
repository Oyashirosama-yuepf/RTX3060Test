/*!
 * @file convex_polygon2_float32.c
 * @brief implementation of convex polygon in 2d.
 * @author duyanwei@holomatic.com
 * @date 2019-08-22
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <assert.h>
#include <math.h>

#include <holo_c/core/epsilon.h>
#include <holo_c/geometry/convex_polygon2_float32.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static int8_t convex_polygon2f_convexity(const struct Point2f* pt1, const struct Point2f* pt2,
                                         const struct Point2f* pt3, const struct Point2f* pt4)
{
    assert(point2f_is_valid(pt1));
    assert(point2f_is_valid(pt2));
    assert(point2f_is_valid(pt3));
    assert(point2f_is_valid(pt4));

    const float32_t x1 = pt2->x - pt1->x;
    const float32_t y1 = pt2->y - pt1->y;
    const float32_t x2 = pt4->x - pt3->x;
    const float32_t y2 = pt4->y - pt3->y;

    const float32_t value = x1 * y2 - x2 * y1;

    return (value >= 0.0f) ? 1 : -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t convex_polygon2f_init(struct ConvexPolygon2f* self)
{
    assert(self != NULL);

    self->size = 0u;
    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t convex_polygon2f_init_from_point2f_array(struct ConvexPolygon2f* self, const struct Point2f* buffer,
                                                   const uint8_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;

    if (buffer_size > convex_polygon2f_get_vertex_maximum_size())
    {
        rc = RC_FAIL;
    }
    else
    {
        for (uint8_t i = 0u; i < buffer_size; i++)
        {
            point2f_init_from_point2f(&(self->vertices[i]), &buffer[i]);
        }
        self->size = buffer_size;

        if (!convex_polygon2f_is_valid(self))
        {
            rc = RC_FAIL;
        }
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t convex_polygon2f_init_from_convex_polygon2f(struct ConvexPolygon2f* self, const struct ConvexPolygon2f* other)
{
    assert(self != NULL);
    assert(true == convex_polygon2f_is_valid(other));

    self->size = other->size;
    for (uint8_t i = 0u; i < self->size; i++)
    {
        point2f_init_from_point2f(&(self->vertices[i]), &(other->vertices[i]));
    }

    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t convex_polygon2f_is_valid(const struct ConvexPolygon2f* self)
{
    assert(self != NULL);

    bool_t flag = true;

    if (self->size > convex_polygon2f_get_vertex_maximum_size() ||
        self->size < convex_polygon2f_get_vertex_minimum_size())
    {
        flag = false;
    }
    else
    {
        // check point valid
        {
            for (uint8_t i = 0u; i < self->size; i++)
            {
                flag = point2f_is_valid(&(self->vertices[i]));

                if (flag == false)
                {
                    break;
                }
            }
        }

        // check polygon convexity
        if (self->size > convex_polygon2f_get_vertex_minimum_size())
        {
            int8_t sign = 1;
            for (uint8_t i = 0u; i < self->size; i++)
            {
                const uint8_t idx0 = (i == 0u) ? (self->size - 1u) : (i - 1u);
                const uint8_t idx1 = i;
                const uint8_t idx2 = (i == self->size - 1u) ? 0u : (i + 1u);

                const int8_t result = convex_polygon2f_convexity(&(self->vertices[idx0]), &(self->vertices[idx1]),
                                                                 &(self->vertices[idx1]), &(self->vertices[idx2]));
                if (i == 0u)
                {
                    sign = result;
                }
                else
                {
                    if (sign != result)
                    {
                        flag = false;
                        break;
                    }
                }
            }
        }
    }

    return flag;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t convex_polygon2f_is_equal(const struct ConvexPolygon2f* lhs, const struct ConvexPolygon2f* rhs)
{
    assert(true == convex_polygon2f_is_valid(lhs));
    assert(true == convex_polygon2f_is_valid(rhs));

    bool_t flag = (lhs->size == rhs->size);

    if (flag)
    {
        for (uint8_t i = 0; i < lhs->size; i++)
        {
            flag = point2f_is_equal(&(lhs->vertices[i]), &(rhs->vertices[i]));

            if (flag == false)
            {
                break;
            }
        }
    }

    return flag;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t convex_polygon2f_if_contains_point2f(const struct ConvexPolygon2f* self, const struct Point2f* point)
{
    assert(true == convex_polygon2f_is_valid(self));
    assert(true == point2f_is_valid(point));

    bool_t flag = true;

    {
        int8_t sign = true;
        for (uint8_t i = 0u; i < self->size; i++)
        {
            const uint8_t idx0 = i;
            const uint8_t idx1 = (i == self->size - 1u) ? 0u : (i + 1u);

            const int8_t result =
                convex_polygon2f_convexity(&(self->vertices[idx0]), point, point, &(self->vertices[idx1]));

            if (i == 0u)
            {
                sign = result;
            }
            else
            {
                if (sign != result)
                {
                    flag = false;
                    break;
                }
            }
        }
    }

    return flag;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t convex_polygon2f_add_vertex(struct ConvexPolygon2f* self, const struct Point2f* point)
{
    assert(self != NULL);
    assert(true == point2f_is_valid(point));

    retcode_t rc = RC_SUCCESS;

    if (self->size >= convex_polygon2f_get_vertex_maximum_size())
    {
        // reached the maximum size of polygon
        rc = RC_FAIL;
    }
    else
    {
        point2f_init_from_point2f(&(self->vertices[self->size]), point);
        self->size += 1u;

        if (self->size >= convex_polygon2f_get_vertex_minimum_size())
        {
            if (!convex_polygon2f_is_valid(self))
            {
                self->size -= 1u;
                rc = RC_FAIL;
            }
        }
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t convex_polygon2f_set_vertex(struct ConvexPolygon2f* self, const uint8_t index, const struct Point2f* point)
{
    assert(true == convex_polygon2f_is_valid(self));
    assert(true == point2f_is_valid(point));

    retcode_t rc = RC_SUCCESS;
    if (index >= self->size)
    {
        rc = RC_FAIL;
    }
    else
    {
        struct Point2f temp;
        point2f_init_from_point2f(&temp, &(self->vertices[index]));
        point2f_init_from_point2f(&(self->vertices[index]), point);

        if (!convex_polygon2f_is_valid(self))
        {
            point2f_init_from_point2f(&(self->vertices[index]), &temp);
            rc = RC_FAIL;
        }
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t convex_polygon2f_get_vertex(const struct ConvexPolygon2f* self, const uint8_t index, struct Point2f* point)
{
    assert(true == convex_polygon2f_is_valid(self));
    assert(point != NULL);

    retcode_t rc = RC_SUCCESS;
    if (index >= self->size)
    {
        rc = RC_FAIL;
    }
    else
    {
        point2f_init_from_point2f(point, &(self->vertices[index]));
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint8_t convex_polygon2f_get_vertex_size(const struct ConvexPolygon2f* self)
{
    assert(self != NULL);

    return self->size;
}
