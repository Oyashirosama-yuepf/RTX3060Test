/**
 * @file cubic_spline.c
 * @brief the implementation of the cubic spline
 * @author zhengshaoqian&lijiawen(zhengshaoqian@holomatic.com&lijiawen@holomatic.com)
 * @date 2019-09-26
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <assert.h>
#include <string.h>

#include <holo_c/numerics/cubic_spline.h>

static void cubic_spline_calc_coef(struct CubicSpline* spline, const struct Point2f* point_list, uint32_t size)
{
    assert(spline != NULL);
    assert(point_list != NULL);
    assert(size != 0U);

    float32_t pp_breaks_data[10], pp_coefs_data[36];
    int32_t   pp_coefs_size[3], pp_breaks_size[2], x_size[2], y_size[2];
    float32_t x_data[size], y_data[size];
    uint32_t  i;
    float32_t c0, c1, c2, c3;

    x_size[0] = 1U;
    x_size[1] = size;
    y_size[0] = 1U;
    y_size[1] = size;

    for (i = 0; i < size; ++i)
    {
        x_data[i] = point2f_get_x(&(point_list[i]));
        y_data[i] = point2f_get_y(&(point_list[i]));
    }

    splinepp(x_data, x_size, y_data, y_size, pp_breaks_data, pp_breaks_size, pp_coefs_data, pp_coefs_size);

    for (i = 0; i < size - 1; ++i)
    {
        c0 = pp_coefs_data[i + (size - 1) * 3];
        c1 = pp_coefs_data[i + (size - 1) * 2];
        c2 = pp_coefs_data[i + (size - 1) * 1];
        c3 = pp_coefs_data[i];

        cubic_polynomial_init(&(spline->spline_func[i]), c0, c1, c2, c3);
    }
}

retcode_t cubic_spline_init(struct CubicSpline* spline, const struct Point2f* point_list, uint32_t size)
{
    assert(spline != NULL);
    assert(point_list != NULL);

    float32_t now_x, former_x;

    /* check size */
    if (size < CUBIC_SPLINE_MIN_POINTS_NUM)
    {
        return RC_NUMERICS_CUBIC_SPLINE_LACK_POINTS;
    }
    else if (size > CUBIC_SPLINE_MAX_POINTS_NUM)
    {
        return RC_NUMERICS_CUBIC_SPLINE_OVERFLOW_POINTS;
    }
    else
    {
    }

    /* check point_list */
    former_x = point2f_get_x(&(point_list[0]));
    for (uint32_t i = 1; i < size; ++i)
    {
        now_x = point2f_get_x(&(point_list[i]));
        if (now_x <= former_x)
        {
            return RC_NUMERICS_CUBIC_SPLINE_INVALID_POINTLIST;
        }
        else
        {
            former_x = now_x;
        }
    }

    cubic_spline_calc_coef(spline, point_list, size);
    spline->size = size;
    for (uint32_t i = 0; i < size; ++i)
    {
        spline->x_value[i] = point2f_get_x(&(point_list[i]));
    }

    return RC_SUCCESS;
}

float32_t cubic_spline_interpolate(struct CubicSpline* spline, float32_t x)
{
    assert(spline != NULL);

    uint32_t  low_i, mid_i, high_i, temp_i;
    float32_t xloc;

    if (x < spline->x_value[0])
    {
        return cubic_polynomial_get_result(&(spline->spline_func[0]), 0.0f);
    }
    else if (x > spline->x_value[spline->size - 1])
    {
        return cubic_polynomial_get_result(&(spline->spline_func[spline->size - 2]),
                                           spline->x_value[spline->size - 1] - spline->x_value[spline->size - 2]);
    }
    else
    {
        low_i  = 0;
        temp_i = 2;
        high_i = spline->size;
        while (high_i > temp_i)
        {
            mid_i = ((low_i + high_i) + 1) >> 1;
            if (x >= spline->x_value[mid_i - 1])
            {
                low_i  = mid_i - 1;
                temp_i = mid_i + 1;
            }
            else
            {
                high_i = mid_i;
            }
        }

        xloc = x - spline->x_value[low_i];

        return cubic_polynomial_get_result(&(spline->spline_func[low_i]), xloc);
    }
}
