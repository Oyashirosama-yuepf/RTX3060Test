/**
 * @file angle_float32.c
 * @brief angle implementation
 * @author duyanwei@holomatic.com
 * @date 2019-08-26
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <holo_c/geometry/angle_float32.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float32_t radianf(float32_t degree)
{
    return degree / 180.f * M_PI;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float32_t radian2f(float32_t degree)
{
    float32_t new_angle = degree_normalize(degree);

    return radianf(new_angle);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float32_t degreef(float32_t radian)
{
    return radian / M_PI * 180.f;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float32_t degree2f(float32_t radian)
{
    float32_t new_angle = radian_normalize(radian);

    return degreef(new_angle);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float32_t radian_normalize(float32_t radian)
{
    float32_t scale     = (radian + M_PI) / (M_PI * 2.0f);
    float32_t new_angle = (scale - floorf(scale)) * M_PI * 2.0f;

    return new_angle - M_PI;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float32_t degree_normalize(float32_t degree)
{
    float32_t scale     = (degree + 180.0f) / 360.0f;
    float32_t new_angle = (scale - floorf(scale)) * 360.0f;

    return new_angle - 180.0f;
}
