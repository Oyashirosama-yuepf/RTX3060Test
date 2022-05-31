/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_decoder_tda4.h
 * @brief Image decoder lib on tda4
 * @author guoguangchao(guoguangchao@holomatic.com).
 * @date 2021-03-12
 */

#ifndef _HOLO_SENSORS_CAMERA_IMAGE_DECODER_TDA4_H
#define _HOLO_SENSORS_CAMERA_IMAGE_DECODER_TDA4_H

#include <TI/j7.h>
#include <TI/j7_video_decoder.h>
#include <TI/tivx.h>
#include <TI/tivx_task.h>
#include <VX/vx.h>
#include <VX/vxu.h>
#include <stdio.h>
#include <string.h>
#include <tivx_utils_checksum.h>
#include <tivx_utils_file_rd_wr.h>

extern "C" {
#include <app_init.h>
}

typedef struct
{
    uint8_t* streambuf;
    vx_size  bitstream_sizes;
    uint8_t* ptr_output;
    uint8_t* ptr_y;
    uint8_t* ptr_uv;
} stream_info;

typedef struct
{
    vx_node                     node;
    vx_kernel                   kernel;
    tivx_video_decoder_params_t params;
    vx_user_data_object         configuration_obj;
    vx_user_data_object         bitstream_obj;
    vx_image                    output_image;
    vx_uint32                   width;
    vx_uint32                   height;
    stream_info                 info;
} DecodeObj;

typedef struct
{
    vx_context context;
    vx_graph   graph;
    DecodeObj  decodeObj;
} App_decode_Obj;

vx_status app_init_resource(App_decode_Obj* obj, uint16_t cols, uint16_t rows);
vx_status app_run_decode(App_decode_Obj* obj);
vx_status app_decode_deinit(App_decode_Obj* obj);

#endif
