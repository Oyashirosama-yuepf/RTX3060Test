/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_gpu.h.
 * @brief Image Encoder.
 * @author lanpade(yangpeiwen@holomatic.com).
 * @date 2020-07-31.
 */
#ifndef _HOLO_SENSORS_CAMERA_CAPTURE_IMAGE_GPU_H
#define _HOLO_SENSORS_CAMERA_CAPTURE_IMAGE_GPU_H

#include <cuda.h>
#include <cuda_runtime.h>

#include <iostream>

void CudaYUYVToRGB(const int32_t cols, const int32_t rows, uint8_t* cuda_yuyv, uint8_t* cuda_rgb, uint8_t* yuyv,
                   uint8_t* rgbb_image);

void CudaYUYVToYUV(const int32_t cols, const int32_t rows, uint8_t* cuda_yuyv, uint8_t* cuda_yuv, uint8_t* yuyv,
                   uint8_t* yuv);

void CudaRGBToYUV(const int32_t cols, const int32_t rows, uint8_t* cuda_rgb, uint8_t* cuda_yuv, const uint8_t* rgb,
                  uint8_t* yuv);
void CudaRGBToYUV(const int32_t cols, const int32_t rows, uint8_t* cuda_rgb, uint8_t* cuda_yuv, const uint8_t* rgb,
                  uint8_t* y, uint8_t* u, uint8_t* v);
void CudaYUVToRGB(const int32_t cols, const int32_t rows, uint8_t* cuda_yuv, uint8_t* cuda_rgb, uint8_t* yuv,
                  uint8_t* rgb);

#endif  // _HOLO_SENSORS_CAMERA_CAPTURE_IMAGE_GPU_H
