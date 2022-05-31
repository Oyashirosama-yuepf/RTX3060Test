/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_resize_decode_tda4.h
 * @brief Image Resize And Decode on TDA4
 * @author zhangruiqiang(zhangruiqiang@holomatic.com).
 * @date 2021-11-15
 */

#ifndef _HOLO_SENSORS_CAMERA_IMAGE_RESIZE_DECODE_TDA4_H
#define _HOLO_SENSORS_CAMERA_IMAGE_RESIZE_DECODE_TDA4_H

#include <iostream>
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

extern "C" 
{
#include <app_init.h>
}

#include <holo/log/hololog.h>
#include <libyuv.h>

namespace holo
{
namespace sensors
{
namespace camera
{
struct ResizeDecodeObject
{
    vx_node             decode_node;

    vx_image            node_src_image;

    vx_uint32           node_src_width;
    vx_uint32           node_src_height;
    vx_uint32           node_dst_width;
    vx_uint32           node_dst_height;

    vx_kernel           kernel;
    vx_user_data_object configuration_object;
    vx_user_data_object bitstream_object;

    vx_uint8*           node_bitstream;
    vx_size             node_bitstream_size;
    
    vx_uint8*           node_src_data_ptr;
    vx_uint8*           node_src_data_ptr_uv;
    vx_uint8*           node_dst_data_ptr;
    vx_uint8*           node_dst_data_ptr_uv;
};

struct AppResizeDecodeObject
{
    vx_context          context;
    vx_graph            graph;
    struct ResizeDecodeObject decodeObject;
};

vx_status resize_decode_app_init(struct AppResizeDecodeObject* object, vx_context context);
vx_status resize_decode_app_run(struct AppResizeDecodeObject* object);
void      resize_decode_app_deinit(struct AppResizeDecodeObject* object);
}  // namespace camera
}  // namespace sensors
}  // namespace holo

#endif  //_HOLO_SENSORS_CAMERA_IMAGE_RESIZE_DECODE_TDA4_H