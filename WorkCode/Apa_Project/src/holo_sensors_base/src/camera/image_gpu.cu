/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_gpu.cu.
 * @brief Image Encoder.
 * @author lanpade(yangpeiwen@holomatic.com).
 * @date 2020-07-31.
 */
#include <holo/sensors/camera/image_gpu.h>

inline __device__ __host__ float clamp(float f, float a, float b)
{
    return fmaxf(a, fminf(f, b));
}

/* From RGB to YUV

   Y = 0.299R + 0.587G + 0.114B
   U = 0.492 (B-Y)
   V = 0.877 (R-Y)

   It can also be represented as:

   Y =  0.299R + 0.587G + 0.114B
   U = -0.147R - 0.289G + 0.436B
   V =  0.615R - 0.515G - 0.100B

   From YUV to RGB

   R = Y + 1.140V
   G = Y - 0.395U - 0.581V
   B = Y + 2.032U
 */

struct __align__(2) uchar6
{
    uchar3 a0, a1;
};
static __host__ __device__ __forceinline__ uchar6 make_uchar6(uchar3 a0, uchar3 a1)
{
    uchar6 val = {a0, a1};
    return val;
}

__global__ void yuyvToRgb(uint8_t* yuyv, uint8_t* rgb, int srcAlignedWidth, int dstAlignedWidth, int width, int height)
{
    const int x = blockIdx.x * blockDim.x + threadIdx.x;
    const int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x >= srcAlignedWidth || y >= height)
        return;

    const uchar4 macroPx = ((uchar4*)yuyv)[y * width / 2 + x];  // = src[y * srcAlignedWidth + x];

    // Y0 is the brightness of pixel 0, Y1 the brightness of pixel 1.
    // U0 and V0 is the color of both pixels.
    // UYVY [ U0 | Y0 | V0 | Y1 ]
    // YUYV [ Y0 | U0 | Y1 | V0 ]
    const float y0 = macroPx.x;
    const float y1 = macroPx.z;
    const float u  = (macroPx.y) - 128.0f;
    const float v  = (macroPx.w) - 128.0f;

    const float3 px0 = make_float3(y0 + 1.4065f * v, y0 - 0.3455f * u - 0.7169f * v, y0 + 1.7790f * u);

    const float3 px1 = make_float3(y1 + 1.4065f * v, y1 - 0.3455f * u - 0.7169f * v, y1 + 1.7790f * u);

    ((uchar6*)rgb)[y * width / 2 + x] =
        make_uchar6(make_uchar3(clamp(px0.x, 0.0f, 255.0f), clamp(px0.y, 0.0f, 255.0f), clamp(px0.z, 0.0f, 255.0f)),
                    make_uchar3(clamp(px1.x, 0.0f, 255.0f), clamp(px1.y, 0.0f, 255.0f), clamp(px1.z, 0.0f, 255.0f)));
}

__global__ void yuyvToYuv(uint8_t* yuyv, uint8_t* yuv, int srcAlignedWidth, int width, int height)
{
    const int x = blockIdx.x * blockDim.x + threadIdx.x;
    const int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x >= srcAlignedWidth || y >= height)
        return;

    const uchar4 macroPx = ((uchar4*)yuyv)[y * width / 2 + x];  // = src[y * srcAlignedWidth + x];

    // Y0 is the brightness of pixel 0, Y1 the brightness of pixel 1.
    // U0 and V0 is the color of both pixels.
    // UYVY [ U0 | Y0 | V0 | Y1 ]
    // YUYV [ Y0 | U0 | Y1 | V0 ]
    const float y0 = macroPx.x;
    const float y1 = macroPx.z;
    const float u  = (macroPx.y);
    const float v  = (macroPx.w);

    ((uchar2*)yuv)[y * width / 2 + x] = make_uchar2(y0, y1);

    if (y % 2 == 0)
    {
        ((uchar1*)yuv)[width * height + y * width / 4 + x]                        = make_uchar1(u);
        ((uchar1*)yuv)[width * height + (width * height) / 4 + y * width / 4 + x] = make_uchar1(v);
    }
}

__global__ void rgbToYuv(uint8_t* rgb, uint8_t* yuv, int srcAlignedWidth, int width, int height)
{
    const int x = blockIdx.x * blockDim.x + threadIdx.x;
    const int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x >= srcAlignedWidth || y >= height)
        return;

    const uchar6 macroPx = ((uchar6*)rgb)[y * width / 2 + x];

    const float r0 = macroPx.a0.x;
    const float g0 = macroPx.a0.y;
    const float b0 = macroPx.a0.z;
    const float r1 = macroPx.a1.x;
    const float g1 = macroPx.a1.y;
    const float b1 = macroPx.a1.z;

    float y0 = 0.257 * r0 + 0.504 * g0 + 0.098 * b0 + 16;
    float y1 = 0.257 * r1 + 0.504 * g1 + 0.098 * b1 + 16;

    ((uchar2*)yuv)[y * width / 2 + x] = make_uchar2(y0, y1);

    if (y % 2 == 0)
    {
        float u                                            = -0.148 * r0 - 0.291 * g0 + 0.439 * b0 + 128;
        float v                                            = 0.439 * r0 - 0.368 * g0 - 0.071 * b0 + 128;
        ((uchar1*)yuv)[width * height + y * width / 4 + x] = make_uchar1(u);
        ((uchar1*)yuv)[width * height + (width * height) / 4 + y * width / 4 + x] = make_uchar1(v);
    }
}

__global__ void yuvToRgb(uint8_t* yuv, uint8_t* rgb, int srcAlignedWidth, int width, int height)
{
    const int x = blockIdx.x * blockDim.x + threadIdx.x;
    const int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x >= srcAlignedWidth || y >= height)
        return;

    const uchar2 macroPx = ((uchar2*)yuv)[y * width / 2 + x];

    float y0 = macroPx.x;
    float y1 = macroPx.y;
    int   y_id;

    if (y % 2 == 0)
    {
        y_id = y;
    }
    else
    {
        y_id = y - 1;
    }

    const uchar2 tt = make_uchar2(((uchar1*)yuv)[width * height + y_id * width / 4 + x].x,
                                  ((uchar1*)yuv)[width * height + (width * height) / 4 + y_id * width / 4 + x].x);
    // float u = ((uchar1*)yuv)[width * height + y_id * width/4 + x];// -128.0f;
    // uchar1 v = ((uchar1*)yuv)[width * height + (width*height)/4 + y_id * width/4 + x];

    // float u = tt.x - 128.0f;
    float u = clamp(((uchar1*)yuv)[width * height + y_id * width / 4 + x].x - 128.0f, 0.0f, 255.0f);
    float v =
        clamp(((uchar1*)yuv)[width * height + (width * height) / 4 + y_id * width / 4 + x].x - 128.0f, 0.0f, 255.0f);
    // float uu = (float) - 128.0f;
    // const float v =  tt.y - 128.0f;

    const float3 px0 = make_float3(y0 + 1.4065f * v, y0 - 0.3455f * u - 0.7169f * v, y0 + 1.7790f * u);

    const float3 px1 = make_float3(y1 + 1.4065f * v, y1 - 0.3455f * u - 0.7169f * v, y1 + 1.7790f * u);

    ((uchar6*)rgb)[y * width / 2 + x] =
        make_uchar6(make_uchar3(clamp(px0.x, 0.0f, 255.0f), clamp(px0.y, 0.0f, 255.0f), clamp(px0.z, 0.0f, 255.0f)),
                    make_uchar3(clamp(px1.x, 0.0f, 255.0f), clamp(px1.y, 0.0f, 255.0f), clamp(px1.z, 0.0f, 255.0f)));
}

void CudaYUYVToRGB(const int32_t cols, const int32_t rows, uint8_t* cuda_yuyv, uint8_t* cuda_rgb, uint8_t* yuyv,
                   uint8_t* rgbb_image)
{
    cudaError_t cuda_status;

    cuda_status = cudaSetDevice(0);
    if (cuda_status != cudaSuccess)
    {
        printf("Device does not support cuda\n");
        return;
    }

    cuda_status = cudaMemcpy(cuda_yuyv, yuyv, cols * rows * 2, cudaMemcpyHostToDevice);
    if (cuda_status != cudaSuccess)
    {
        printf("Could not copy data to gpu\n");
        return;  // cuda_status;
    }

    dim3      block(8, 8);
    dim3      grid(cols / 2 / 8, rows / 8);
    const int srcAlignedWidth =
        cols * rows * 2 / sizeof(uchar4);  // normally would be uchar2, but we're doubling up pixels
    const int dstAlignedWidth = cols * rows * 3 / sizeof(uchar6);  // normally would be uchar4 ^^^

    // printf("yuyvToRgba %zu %zu %i %i %i %i %i\n", width, height, (int)formatUYVY, srcAlignedWidth, dstAlignedWidth,
    // grid.x, grid.y);

    yuyvToRgb<<<grid, block>>>(cuda_yuyv, cuda_rgb, srcAlignedWidth, dstAlignedWidth, cols, rows);

    cuda_status = cudaGetLastError();

    if (cuda_status != cudaSuccess)
    {
        printf("Yuyv to rgb error\n");
        return;
    }

    cuda_status = cudaDeviceSynchronize();
    if (cuda_status != cudaSuccess)
    {
        printf("sychronization error\n");
        return;
    }

    cuda_status = cudaMemcpy(rgbb_image, cuda_rgb, cols * rows * 3, cudaMemcpyDeviceToHost);
    if (cuda_status != cudaSuccess)
    {
        printf("Could not copy data from gpu\n");
        return;
    }

    return;
}

void CudaYUYVToYUV(const int32_t cols, const int32_t rows, uint8_t* cuda_yuyv, uint8_t* cuda_yuv, uint8_t* yuyv,
                   uint8_t* yuv)
{
    cudaError_t cuda_status;

    cuda_status = cudaSetDevice(0);
    if (cuda_status != cudaSuccess)
    {
        printf("Device does not support cuda\n");
        return;
    }

    cuda_status = cudaMemcpy(cuda_yuyv, yuyv, cols * rows * 2, cudaMemcpyHostToDevice);
    if (cuda_status != cudaSuccess)
    {
        printf("Could not copy data to gpu\n");
        return;  // cuda_status;
    }

    dim3      block(8, 8);
    dim3      grid(cols / 2 / 8, rows / 8);
    const int srcAlignedWidth = cols * rows * 2 / sizeof(uchar4);

    yuyvToYuv<<<grid, block>>>(cuda_yuyv, cuda_yuv, srcAlignedWidth, cols, rows);

    cuda_status = cudaGetLastError();

    if (cuda_status != cudaSuccess)
    {
        printf("Yuyv to rgb error\n");
        return;
    }

    cuda_status = cudaDeviceSynchronize();
    if (cuda_status != cudaSuccess)
    {
        printf("sychronization error\n");
        return;
    }

    cuda_status = cudaMemcpy(yuv, cuda_yuv, cols * rows * 1.5, cudaMemcpyDeviceToHost);
    if (cuda_status != cudaSuccess)
    {
        printf("Could not copy data from gpu\n");
        return;
    }

    return;
}

void CudaRGBToYUV(const int32_t cols, const int32_t rows, uint8_t* cuda_rgb, uint8_t* cuda_yuv, const uint8_t* rgb,
                  uint8_t* yuv)
{
    cudaError_t cuda_status;

    cuda_status = cudaSetDevice(0);
    if (cuda_status != cudaSuccess)
    {
        printf("Device does not support cuda\n");
        return;
    }

    cuda_status = cudaMemcpy(cuda_rgb, rgb, cols * rows * 3, cudaMemcpyHostToDevice);
    if (cuda_status != cudaSuccess)
    {
        printf("Could not copy data to gpu\n");
        return;  // cuda_status;
    }

    dim3      block(8, 8);
    dim3      grid(cols / 2 / 8, rows / 8);
    const int srcAlignedWidth = cols * rows * 2 / sizeof(uchar4);

    rgbToYuv<<<grid, block>>>(cuda_rgb, cuda_yuv, srcAlignedWidth, cols, rows);

    cuda_status = cudaGetLastError();

    if (cuda_status != cudaSuccess)
    {
        printf("rgb to yuv error\n");
        return;
    }

    cuda_status = cudaDeviceSynchronize();
    if (cuda_status != cudaSuccess)
    {
        printf("sychronization error\n");
        return;
    }

    cuda_status = cudaMemcpy(yuv, cuda_yuv, cols * rows * 1.5, cudaMemcpyDeviceToHost);
    if (cuda_status != cudaSuccess)
    {
        printf("Could not copy data from gpu\n");
        return;
    }

    return;
}

void CudaRGBToYUV(const int32_t cols, const int32_t rows, uint8_t* cuda_rgb, uint8_t* cuda_yuv, const uint8_t* rgb,
                  uint8_t* y, uint8_t* u, uint8_t* v)
{
    cudaError_t cuda_status;

    cuda_status = cudaSetDevice(0);
    if (cuda_status != cudaSuccess)
    {
        printf("Device does not support cuda\n");
        return;
    }

    cuda_status = cudaMemcpy(cuda_rgb, rgb, cols * rows * 3, cudaMemcpyHostToDevice);
    if (cuda_status != cudaSuccess)
    {
        printf("Could not copy data to gpu\n");
        return;  // cuda_status;
    }

    dim3      block(8, 8);
    dim3      grid(cols / 2 / 8, rows / 8);
    const int srcAlignedWidth = cols * rows * 2 / sizeof(uchar4);

    rgbToYuv<<<grid, block>>>(cuda_rgb, cuda_yuv, srcAlignedWidth, cols, rows);

    cuda_status = cudaGetLastError();

    if (cuda_status != cudaSuccess)
    {
        printf("rgb to yuv error\n");
        return;
    }

    cuda_status = cudaDeviceSynchronize();
    if (cuda_status != cudaSuccess)
    {
        printf("sychronization error\n");
        return;
    }

    uint32_t offset = 0u;
    cuda_status     = cudaMemcpy(y, cuda_yuv + offset, cols * rows, cudaMemcpyDeviceToHost);
    if (cuda_status != cudaSuccess)
    {
        printf("Could not copy data from gpu\n");
        return;
    }
    offset += cols * rows;
    cuda_status = cudaMemcpy(u, cuda_yuv + offset, cols * rows / 4, cudaMemcpyDeviceToHost);
    if (cuda_status != cudaSuccess)
    {
        printf("Could not copy data from gpu\n");
        return;
    }
    offset += cols * rows / 4;
    cuda_status = cudaMemcpy(v, cuda_yuv + offset, cols * rows / 4, cudaMemcpyDeviceToHost);
    if (cuda_status != cudaSuccess)
    {
        printf("Could not copy data from gpu\n");
        return;
    }
}

void CudaYUVToRGB(const int32_t cols, const int32_t rows, uint8_t* cuda_yuv, uint8_t* cuda_rgb, uint8_t* yuv,
                  uint8_t* rgb)
{
    cudaError_t cuda_status;

    cuda_status = cudaSetDevice(0);
    if (cuda_status != cudaSuccess)
    {
        printf("Device does not support cuda\n");
        return;
    }

    cuda_status = cudaMemcpy(cuda_yuv, yuv, cols * rows * 1.5, cudaMemcpyHostToDevice);
    if (cuda_status != cudaSuccess)
    {
        printf("Could not copy data to gpu\n");
        return;  // cuda_status;
    }

    dim3      block(8, 8);
    dim3      grid(cols / 2 / 8, rows / 8);
    const int srcAlignedWidth = cols * rows * 2 / sizeof(uchar4);

    yuvToRgb<<<grid, block>>>(cuda_yuv, cuda_rgb, srcAlignedWidth, cols, rows);

    cuda_status = cudaGetLastError();

    if (cuda_status != cudaSuccess)
    {
        printf("Yuv to rgb error\n");
        return;
    }

    cuda_status = cudaDeviceSynchronize();
    if (cuda_status != cudaSuccess)
    {
        printf("sychronization error\n");
        return;
    }

    cuda_status = cudaMemcpy(rgb, cuda_rgb, cols * rows * 3, cudaMemcpyDeviceToHost);
    if (cuda_status != cudaSuccess)
    {
        printf("Could not copy data from gpu\n");
        return;
    }

    return;
}
