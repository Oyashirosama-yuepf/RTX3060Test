/*!
 * @file box3_float32.c
 * @brief box3 implementation
 * @author duyanwei@holomatic.com
 * @date 2019-08-12
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <assert.h>
#include <math.h>

#include <holo_c/geometry/box3_float32.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t box3f_init(struct Box3f* self)
{
    assert(self != NULL);

    self->width  = 1.0f;
    self->height = 1.0f;
    self->depth  = 1.0f;
    return pose3f_init(&self->pose);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t box3f_init_from_two_point3f(struct Box3f* self, const struct Point3f* pt1, const struct Point3f* pt2)
{
    assert(self != NULL);
    assert(true == point3f_is_valid(pt1));
    assert(true == point3f_is_valid(pt2));

    retcode_t rc = RC_SUCCESS;

    // dimension
    const float32_t x_min = pt1->x < pt2->x ? pt1->x : pt2->x;
    const float32_t x_max = pt1->x > pt2->x ? pt1->x : pt2->x;
    const float32_t y_min = pt1->y < pt2->y ? pt1->y : pt2->y;
    const float32_t y_max = pt1->y > pt2->y ? pt1->y : pt2->y;
    const float32_t z_min = pt1->z < pt2->z ? pt1->z : pt2->z;
    const float32_t z_max = pt1->z > pt2->z ? pt1->z : pt2->z;

    self->width  = x_max - x_min;
    self->height = y_max - y_min;
    self->depth  = z_max - z_min;

    // pose
    rc = pose3f_init(&self->pose);
    rc = point3f_init_from_scalars(&(self->pose.translation), x_min, y_min, z_min);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t box3f_init_from_width_height_and_depth(struct Box3f* self, const float32_t width, const float32_t height,
                                                 const float32_t depth)
{
    assert(self != NULL);

    retcode_t rc = RC_SUCCESS;

    if (width <= holo_float32_epsilon || height <= holo_float32_epsilon || depth <= holo_float32_epsilon)
    {
        rc = RC_FAIL;
    }
    else
    {
        self->width  = width;
        self->height = height;
        self->depth  = depth;

        rc = pose3f_init(&self->pose);
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t box3f_init_from_width_height_depth_and_pose3f(struct Box3f* self, const float32_t width,
                                                        const float32_t height, const float32_t depth,
                                                        const struct Pose3f* pose)
{
    assert(self != NULL);
    assert(true == pose3f_is_valid(pose));

    retcode_t rc = RC_SUCCESS;

    if (width <= holo_float32_epsilon || height <= holo_float32_epsilon || depth <= holo_float32_epsilon)
    {
        rc = RC_FAIL;
    }
    else
    {
        self->width  = width;
        self->height = height;
        self->depth  = depth;

        rc = pose3f_init_from_pose3f(&self->pose, pose);
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t box3f_init_from_vector3f_and_pose3f(struct Box3f* self, const struct Vectorf* dimension,
                                              const struct Pose3f* pose)
{
    assert(self != NULL);
    assert(true == vectorf_is_valid(dimension));

    retcode_t rc = RC_SUCCESS;

    if (dimension->size != 3u)
    {
        rc = RC_FAIL;
    }
    else
    {
        float32_t width, height, depth;
        rc = vectorf_get(dimension, 0u, &width);
        rc = vectorf_get(dimension, 1u, &height);
        rc = vectorf_get(dimension, 2u, &depth);

        rc = box3f_init_from_width_height_depth_and_pose3f(self, width, height, depth, pose);
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t box3f_init_from_box3f(struct Box3f* self, const struct Box3f* other)
{
    assert(self != NULL);
    assert(true == box3f_is_valid(other));

    self->width  = other->width;
    self->height = other->height;
    self->depth  = other->depth;

    return pose3f_init_from_pose3f(&self->pose, &other->pose);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t box3f_is_valid(const struct Box3f* self)
{
    assert(self != NULL);

    bool_t flag = true;

    if (self->width <= holo_float32_epsilon || self->height <= holo_float32_epsilon ||
        self->depth <= holo_float32_epsilon)
    {
        flag = false;
    }
    else
    {
        flag = pose3f_is_valid(&self->pose);
    }

    return flag;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t box3f_is_equal(const struct Box3f* self, const struct Box3f* other)
{
    assert(true == box3f_is_valid(self));
    assert(true == box3f_is_valid(other));

    bool_t flag = true;

    const float32_t diff_w = fabsf(self->width - other->width);
    const float32_t diff_h = fabsf(self->height - other->height);
    const float32_t diff_d = fabsf(self->depth - other->depth);

    if (diff_w > holo_float32_epsilon || diff_h > holo_float32_epsilon || diff_d > holo_float32_epsilon)
    {
        flag = false;
    }
    else
    {
        flag = pose3f_is_equal(&self->pose, &other->pose);
    }

    return flag;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t box3f_contains_point3f(const struct Box3f* self, const struct Point3f* point)
{
    assert(true == box3f_is_valid(self));
    assert(true == point3f_is_valid(point));

    struct Point3f transformed_point;
    point3f_init(&transformed_point);

    bool_t flag = true;

    if (RC_SUCCESS != pose3f_transform_to_point3f(&self->pose, point, &transformed_point))
    {
        flag = false;
    }
    else
    {
        flag = (transformed_point.x >= holo_float32_epsilon) &&
               (transformed_point.x <= self->width - holo_float32_epsilon);
        flag &= (transformed_point.y >= holo_float32_epsilon) &&
                (transformed_point.y <= self->height - holo_float32_epsilon);
        flag &= (transformed_point.z >= holo_float32_epsilon) &&
                (transformed_point.z <= self->depth - holo_float32_epsilon);
    }
    return flag;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t box3f_get_axis_aligned_external_box(const struct Box3f* self, struct Point3f* min_pt, struct Point3f* max_pt)
{
    assert(true == box3f_is_valid(self));
    assert(min_pt != NULL);
    assert(max_pt != NULL);

    // create 8-corner points in box body frame
    float32_t data[8][3] = {{0.0f, 0.0f, 0.0f},
                            {self->width, 0.0f, 0.0f},
                            {self->width, self->height, 0.0f},
                            {0.0f, self->height, 0.0f},
                            {0.0f, 0.0f, self->depth},
                            {self->width, 0.0f, self->depth},
                            {self->width, self->height, self->depth},
                            {0.0f, self->height, self->depth}};

    // create initial value for them
    point3f_init_from_scalars(min_pt, INT16_MAX, INT16_MAX, INT16_MAX);
    point3f_init_from_scalars(max_pt, INT16_MIN, INT16_MIN, INT16_MIN);

    // loop to find min and max point
    struct Point3f pt1;
    point3f_init(&pt1);
    struct Point3f pt2;
    point3f_init(&pt2);
    for (uint8_t i = 0u; i < 8u; i++)
    {
        point3f_init_from_array(&pt1, &data[i][0], 3u);
        pose3f_transform_from_point3f(&self->pose, &pt1, &pt2);

        if (min_pt->x > pt2.x)
        {
            min_pt->x = pt2.x;
        }
        if (min_pt->y > pt2.y)
        {
            min_pt->y = pt2.y;
        }
        if (min_pt->z > pt2.z)
        {
            min_pt->z = pt2.z;
        }
        if (max_pt->x < pt2.x)
        {
            max_pt->x = pt2.x;
        }
        if (max_pt->y < pt2.y)
        {
            max_pt->y = pt2.y;
        }
        if (max_pt->z < pt2.z)
        {
            max_pt->z = pt2.z;
        }
    }

    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float32_t box3f_get_volume(const struct Box3f* self)
{
    assert(true == box3f_is_valid(self));

    return self->width * self->height * self->depth;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t box3f_get_center(const struct Box3f* self, struct Point3f* center)
{
    assert(true == box3f_is_valid(self));
    assert(center != NULL);

    struct Point3f center_in_body;
    retcode_t      rc =
        point3f_init_from_scalars(&center_in_body, self->width / 2.0f, self->height / 2.0f, self->depth / 2.0f);

    if (rc == RC_SUCCESS)
    {
        rc = pose3f_transform_from_point3f(&self->pose, &center_in_body, center);
    }

    return rc;
}
