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

/*
 * This function is generated from Matlab, so the coding-style maybe strange.
 * It is a original version: there is no changes on it.
 * MATLAB Coder version: 4.0 (R2018a)
 */
void splinepp(const float x_data[], const int x_size[2], const float y_data[], const int y_size[2],
              float pp_breaks_data[], int pp_breaks_size[2], float pp_coefs_data[], int pp_coefs_size[3])
{
    int   nx;
    bool  has_endslopes;
    int   yoffset;
    float d31;
    float c_data[2];
    int   k;
    float dnnm2;
    float b_c_data[3];
    float s_data[10];
    float dx_data[9];
    float r;
    float dvdf_data[9];
    float t0_coefs[4]={};
    float md_data[10];
    int   nxm1;
    float t2_breaks_data[10];
    float t2_coefs_data[36];
    nx            = x_size[1] - 1;
    has_endslopes = (y_size[1] == x_size[1] + 2);
    if (x_size[1] <= 2)
    {
        if (has_endslopes)
        {
            k = x_size[1];
            if (0 <= k - 1)
            {
                memcpy(&s_data[0], &x_data[0], (unsigned int)(k * (int)sizeof(float)));
            }

            if (1 <= x_size[1] - 1)
            {
                r           = x_data[1] - x_data[0];
                d31         = (y_data[2] - y_data[1]) / r;
                dnnm2       = (d31 - y_data[0]) / r;
                d31         = (y_data[y_size[1] - 1] - d31) / r;
                t0_coefs[0] = (d31 - dnnm2) / r;
                t0_coefs[1] = 2.0 * dnnm2 - d31;
                t0_coefs[2] = y_data[0];
                t0_coefs[3] = y_data[1];
            }

            pp_breaks_size[0] = 1;
            pp_breaks_size[1] = x_size[1];
            k                 = x_size[1];
            if (0 <= k - 1)
            {
                memcpy(&pp_breaks_data[0], &s_data[0], (unsigned int)(k * (int)sizeof(float)));
            }

            pp_coefs_size[0] = 1;
            pp_coefs_size[1] = 4;
            pp_coefs_size[2] = 1;
            for (k = 0; k < 4; k++)
            {
                pp_coefs_data[k] = t0_coefs[k];
            }
        }
        else
        {
            c_data[0] = (y_data[1] - y_data[0]) / (x_data[1] - x_data[0]);
            c_data[1] = y_data[0];
            k         = x_size[1];
            if (0 <= k - 1)
            {
                memcpy(&s_data[0], &x_data[0], (unsigned int)(k * (int)sizeof(float)));
            }

            pp_breaks_size[0] = 1;
            pp_breaks_size[1] = x_size[1];
            k                 = x_size[1];
            if (0 <= k - 1)
            {
                memcpy(&pp_breaks_data[0], &s_data[0], (unsigned int)(k * (int)sizeof(float)));
            }

            pp_coefs_size[0] = 1;
            pp_coefs_size[1] = 1;
            pp_coefs_size[2] = 2;
            for (k = 0; k < 2; k++)
            {
                pp_coefs_data[k] = c_data[k];
            }
        }
    }
    else if ((x_size[1] == 3) && (!has_endslopes))
    {
        d31               = x_data[1] - x_data[0];
        dnnm2             = (y_data[1] - y_data[0]) / d31;
        b_c_data[0]       = ((y_data[2] - y_data[1]) / (x_data[2] - x_data[1]) - dnnm2) / (x_data[2] - x_data[0]);
        b_c_data[1]       = dnnm2 - b_c_data[0] * d31;
        b_c_data[2]       = y_data[0];
        c_data[0]         = x_data[0];
        c_data[1]         = x_data[2];
        pp_breaks_size[0] = 1;
        pp_breaks_size[1] = 2;
        for (k = 0; k < 2; k++)
        {
            pp_breaks_data[k] = c_data[k];
        }

        pp_coefs_size[0] = 1;
        pp_coefs_size[1] = 1;
        pp_coefs_size[2] = 3;
        for (k = 0; k < 3; k++)
        {
            pp_coefs_data[k] = b_c_data[k];
        }
    }
    else
    {
        yoffset = has_endslopes;
        for (k = 0; k < nx; k++)
        {
            dx_data[k]   = x_data[k + 1] - x_data[k];
            dvdf_data[k] = (y_data[(yoffset + k) + 1] - y_data[yoffset + k]) / dx_data[k];
        }

        for (k = 1; k < nx; k++)
        {
            s_data[k] = 3.0 * (dx_data[k] * dvdf_data[k - 1] + dx_data[k - 1] * dvdf_data[k]);
        }

        if (has_endslopes)
        {
            d31                   = 0.0;
            dnnm2                 = 0.0;
            s_data[0]             = dx_data[1] * y_data[0];
            s_data[x_size[1] - 1] = dx_data[x_size[1] - 3] * y_data[x_size[1] + 1];
        }
        else
        {
            d31   = x_data[2] - x_data[0];
            dnnm2 = x_data[x_size[1] - 1] - x_data[x_size[1] - 3];
            s_data[0] =
                ((dx_data[0] + 2.0 * d31) * dx_data[1] * dvdf_data[0] + dx_data[0] * dx_data[0] * dvdf_data[1]) / d31;
            s_data[x_size[1] - 1] =
                ((dx_data[x_size[1] - 2] + 2.0 * dnnm2) * dx_data[x_size[1] - 3] * dvdf_data[x_size[1] - 2] +
                 dx_data[x_size[1] - 2] * dx_data[x_size[1] - 2] * dvdf_data[x_size[1] - 3]) /
                dnnm2;
        }

        md_data[0]             = dx_data[1];
        md_data[x_size[1] - 1] = dx_data[x_size[1] - 3];
        for (k = 1; k < nx; k++)
        {
            md_data[k] = 2.0 * (dx_data[k] + dx_data[k - 1]);
        }

        r = dx_data[1] / md_data[0];
        md_data[1] -= r * d31;
        s_data[1] -= r * s_data[0];
        for (k = 2; k < nx; k++)
        {
            r = dx_data[k] / md_data[k - 1];
            md_data[k] -= r * dx_data[k - 2];
            s_data[k] -= r * s_data[k - 1];
        }

        r = dnnm2 / md_data[x_size[1] - 2];
        md_data[x_size[1] - 1] -= r * dx_data[x_size[1] - 3];
        s_data[x_size[1] - 1] -= r * s_data[x_size[1] - 2];
        s_data[x_size[1] - 1] /= md_data[x_size[1] - 1];
        for (k = x_size[1] - 2; k + 1 > 1; k--)
        {
            s_data[k] = (s_data[k] - dx_data[k - 1] * s_data[k + 1]) / md_data[k];
        }

        s_data[0] = (s_data[0] - d31 * s_data[1]) / md_data[0];
        nx        = x_size[1] - 1;
        nxm1      = x_size[1] - 1;
        k         = x_size[1];
        memcpy(&t2_breaks_data[0], &x_data[0], (unsigned int)(k * (int)sizeof(float)));
        for (k = 0; k < nx; k++)
        {
            dnnm2                          = (dvdf_data[k] - s_data[k]) / dx_data[k];
            d31                            = (s_data[k + 1] - dvdf_data[k]) / dx_data[k];
            t2_coefs_data[k]               = (d31 - dnnm2) / dx_data[k];
            t2_coefs_data[nx + k]          = 2.0 * dnnm2 - d31;
            t2_coefs_data[(nxm1 << 1) + k] = s_data[k];
            t2_coefs_data[3 * nxm1 + k]    = y_data[yoffset + k];
        }

        pp_breaks_size[0] = 1;
        pp_breaks_size[1] = x_size[1];
        k                 = x_size[1];
        memcpy(&pp_breaks_data[0], &t2_breaks_data[0], (unsigned int)(k * (int)sizeof(float)));
        pp_coefs_size[0] = 1;
        pp_coefs_size[1] = (signed char)(x_size[1] - 1);
        pp_coefs_size[2] = 4;
        k                = (signed char)(x_size[1] - 1) << 2;
        if (0 <= k - 1)
        {
            memcpy(&pp_coefs_data[0], &t2_coefs_data[0], (unsigned int)(k * (int)sizeof(float)));
        }
    }
}

