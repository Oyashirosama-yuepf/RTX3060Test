/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_encoder_tda4.h
 * @brief Image encoder on tda4
 * @author guoguangchao(guoguangchao@holomatic.com).
 * @date 2021-03-12
 */

#ifndef _HOLO_SENSORS_CAMERA_IMAGE_ENCODER_TDA4_H
#define _HOLO_SENSORS_CAMERA_IMAGE_ENCODER_TDA4_H

#include <TI/j7.h>
#include <VX/vx.h>
#include <VX/vxu.h>

extern "C" {
#include <TI/tivx.h>
#include <app_init.h>
}

typedef struct
{
    vx_node             node;
    vx_user_data_object configuration_obj;
    vx_user_data_object bitstream_obj;
    vx_image            input_image;
    vx_uint32           width;
    vx_uint32           height;
    vx_uint8*           bitstream;
    vx_uint32           bitstream_size;
    vx_uint8*           data_ptr;
    vx_uint8*           data_ptr_y;
    vx_uint8*           data_ptr_uv;
} EncodeObj;

typedef struct
{
    vx_context context;
    vx_graph   graph;
    EncodeObj  encodeObj;
} App_encode_obj;

vx_status app_encode_init(App_encode_obj* obj, vx_context context, uint16_t cols, uint16_t rows, uint32_t fps, uint32_t i_period, uint32_t bitrate);
vx_status app_encode_run(App_encode_obj* obj);
void      app_encode_deinit(App_encode_obj* obj);

#endif
