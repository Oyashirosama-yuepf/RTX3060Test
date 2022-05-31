/*!
 * @file box2_float32.c
 * @brief box2 implementation
 * @author duyanwei@holomatic.com
 * @date 2019-08-12
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <assert.h>
#include <math.h>

#include <holo_c/core/epsilon.h>
#include <holo_c/geometry/box2_float32.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t box2f_init(struct Box2f* self)
{
    assert(self != NULL);

    self->width  = 1.0f;
    self->height = 1.0f;
    return pose2f_init(&self->pose);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t box2f_init_from_two_point2f(struct Box2f* self, const struct Point2f* pt1, const struct Point2f* pt2)
{
    assert(self != NULL);
    assert(true == point2f_is_valid(pt1));
    assert(true == point2f_is_valid(pt2));

    retcode_t rc = RC_SUCCESS;

    // width and height
    const float32_t x_min = pt1->x < pt2->x ? pt1->x : pt2->x;
    const float32_t x_max = pt1->x > pt2->x ? pt1->x : pt2->x;
    const float32_t y_min = pt1->y < pt2->y ? pt1->y : pt2->y;
    const float32_t y_max = pt1->y > pt2->y ? pt1->y : pt2->y;

    self->width  = x_max - x_min;
    self->height = y_max - y_min;

    // pose
    rc = pose2f_init(&self->pose);
    rc = point2f_init_from_scalars(&(self->pose.translation), x_min, y_min);

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t box2f_init_from_width_and_height(struct Box2f* self, const float32_t width, const float32_t height)
{
    assert(self != NULL);

    retcode_t rc = RC_SUCCESS;

    if (width <= holo_float32_epsilon || height <= holo_float32_epsilon)
    {
        rc = RC_FAIL;
    }
    else
    {
        self->width  = width;
        self->height = height;

        rc = pose2f_init(&self->pose);
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t box2f_init_from_width_height_and_pose2f(struct Box2f* self, const float32_t width, const float32_t height,
                                                  const struct Pose2f* pose)
{
    assert(self != NULL);
    assert(true == pose2f_is_valid(pose));

    retcode_t rc = RC_SUCCESS;

    if (width <= holo_float32_epsilon || height <= holo_float32_epsilon)
    {
        rc = RC_FAIL;
    }
    else
    {
        self->width  = width;
        self->height = height;

        rc = pose2f_init(&self->pose);
        rc = pose2f_init_from_pose2f(&self->pose, pose);
    }
    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t box2f_init_from_vector2f_and_pose2f(struct Box2f* self, const struct Vectorf* dimension,
                                              const struct Pose2f* pose)
{
    assert(self != NULL);
    assert(true == vectorf_is_valid(dimension));

    retcode_t rc = RC_SUCCESS;

    if (dimension->size != 2u)
    {
        rc = RC_FAIL;
    }
    else
    {
        float32_t width, height;
        rc = vectorf_get(dimension, 0u, &width);
        rc = vectorf_get(dimension, 1u, &height);

        rc = box2f_init_from_width_height_and_pose2f(self, width, height, pose);
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t box2f_init_from_box2f(struct Box2f* self, const struct Box2f* other)
{
    assert(self != NULL);
    assert(true == box2f_is_valid(other));

    self->width  = other->width;
    self->height = other->height;
    pose2f_init(&self->pose);

    return pose2f_init_from_pose2f(&self->pose, &other->pose);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t box2f_is_valid(const struct Box2f* self)
{
    assert(self != NULL);

    bool_t flag = true;

    if (self->width <= holo_float32_epsilon || self->height <= holo_float32_epsilon)
    {
        flag = false;
    }
    else
    {
        flag = pose2f_is_valid(&self->pose);
    }

    return flag;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t box2f_is_equal(const struct Box2f* self, const struct Box2f* other)
{
    assert(true == box2f_is_valid(self));
    assert(true == box2f_is_valid(other));

    bool_t flag = true;

    const float32_t diff_w = fabsf(self->width - other->width);
    const float32_t diff_h = fabsf(self->height - other->height);

    if (diff_w > holo_float32_epsilon || diff_h > holo_float32_epsilon)
    {
        flag = false;
    }
    else
    {
        flag = pose2f_is_equal(&self->pose, &other->pose);
    }

    return flag;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t box2f_contains_point2f(const struct Box2f* self, const struct Point2f* point)
{
    assert(true == box2f_is_valid(self));
    assert(true == point2f_is_valid(point));

    struct Point2f transformed_point;
    point2f_init(&transformed_point);

    bool_t flag = true;

    if (RC_SUCCESS != pose2f_transform_to_point2f(&self->pose, point, &transformed_point))
    {
        flag = false;
    }
    else
    {
        flag = (transformed_point.x >= holo_float32_epsilon) &&
               (transformed_point.x <= self->width - holo_float32_epsilon);
        flag &= (transformed_point.y >= holo_float32_epsilon) &&
                (transformed_point.y <= self->height - holo_float32_epsilon);
    }
    return flag;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t box2f_get_corner_points(const struct Box2f* self, struct Point2f* bl, struct Point2f* br, struct Point2f* tr,
                                  struct Point2f* tl)
{
    assert(true == box2f_is_valid(self));
    assert(bl != NULL);
    assert(br != NULL);
    assert(tr != NULL);
    assert(tl != NULL);

    retcode_t rc = RC_SUCCESS;

    struct Point2f pt;

    // bottom left
    {
        rc = point2f_init_from_scalars(&pt, 0.0f, 0.0f);
        rc = pose2f_transform_from_point2f(&self->pose, &pt, bl);
    }

    // bottom right
    {
        rc = point2f_init_from_scalars(&pt, self->width, 0.0f);
        rc = pose2f_transform_from_point2f(&self->pose, &pt, br);
    }

    // top right
    {
        rc = point2f_init_from_scalars(&pt, self->width, self->height);
        rc = pose2f_transform_from_point2f(&self->pose, &pt, tr);
    }

    // top left
    {
        rc = point2f_init_from_scalars(&pt, 0.0f, self->height);
        rc = pose2f_transform_from_point2f(&self->pose, &pt, tl);
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t box2f_get_axis_aligned_external_box(const struct Box2f* self, struct Point2f* min_pt, struct Point2f* max_pt)
{
    assert(true == box2f_is_valid(self));
    assert(min_pt != NULL);
    assert(max_pt != NULL);

    // create 8-corner points in box body frame
    float32_t data[4][2] = {{0.0f, 0.0f}, {self->width, 0.0f}, {self->width, self->height}, {0.0f, self->height}};

    // create initial value for them
    point2f_init_from_scalars(min_pt, INT16_MAX, INT16_MAX);
    point2f_init_from_scalars(max_pt, INT16_MIN, INT16_MIN);

    // loop to find min and max point
    struct Point2f pt1;
    point2f_init(&pt1);
    struct Point2f pt2;
    point2f_init(&pt2);
    for (uint8_t i = 0u; i < 4u; i++)
    {
        point2f_init_from_array(&pt1, &data[i][0], 2u);
        pose2f_transform_from_point2f(&self->pose, &pt1, &pt2);

        if (min_pt->x > pt2.x)
        {
            min_pt->x = pt2.x;
        }
        if (min_pt->y > pt2.y)
        {
            min_pt->y = pt2.y;
        }
        if (max_pt->x < pt2.x)
        {
            max_pt->x = pt2.x;
        }
        if (max_pt->y < pt2.y)
        {
            max_pt->y = pt2.y;
        }
    }

    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float32_t box2f_get_area(const struct Box2f* self)
{
    assert(true == box2f_is_valid(self));

    return self->width * self->height;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t box2f_get_center(const struct Box2f* self, struct Point2f* center)
{
    assert(true == box2f_is_valid(self));
    assert(center != NULL);

    struct Point2f center_in_body;
    retcode_t      rc = point2f_init_from_scalars(&center_in_body, self->width / 2.0f, self->height / 2.0f);

    if (rc == RC_SUCCESS)
    {
        rc = pose2f_transform_from_point2f(&self->pose, &center_in_body, center);
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t box2f_compute_intersection_over_union(const struct Box2f* self, const struct Box2f* other, float32_t* value)
{
    assert(true == box2f_is_valid(self));
    assert(true == box2f_is_valid(other));
    assert(value != NULL);

    retcode_t rc = RC_SUCCESS;

    float32_t self_theta  = -1.0f;
    float32_t other_theta = -1.0f;
    rot2f_get_angle(&(self->pose.rotation), &self_theta);
    rot2f_get_angle(&(other->pose.rotation), &other_theta);

    if ((fabsf(self_theta) > holo_float32_epsilon) || (fabsf(other_theta) > holo_float32_epsilon))
    {
        rc = RC_FAIL;
    }
    else
    {
        struct Point2f self_min_pt;
        point2f_init(&self_min_pt);
        struct Point2f self_max_pt;
        point2f_init(&self_max_pt);
        box2f_get_axis_aligned_external_box(self, &self_min_pt, &self_max_pt);

        struct Point2f other_min_pt;
        point2f_init(&other_min_pt);
        struct Point2f other_max_pt;
        point2f_init(&other_max_pt);
        box2f_get_axis_aligned_external_box(other, &other_min_pt, &other_max_pt);

        // compute intersection area of two boxes
        const float32_t bl_x = self_min_pt.x > other_min_pt.x ? self_min_pt.x : other_min_pt.x;
        const float32_t bl_y = self_min_pt.y > other_min_pt.y ? self_min_pt.y : other_min_pt.y;
        const float32_t tr_x = self_max_pt.x < other_max_pt.x ? self_max_pt.x : other_max_pt.x;
        const float32_t tr_y = self_max_pt.y < other_max_pt.y ? self_max_pt.y : other_max_pt.y;

        const float32_t width  = tr_x - bl_x;
        const float32_t height = tr_y - bl_y;

        const float32_t area = width * height;

        // bug !!!
        const float32_t self_area  = box2f_get_area(self);
        const float32_t other_area = box2f_get_area(other);

        *value = area / (self_area + other_area - area);
    }

    return rc;
}
