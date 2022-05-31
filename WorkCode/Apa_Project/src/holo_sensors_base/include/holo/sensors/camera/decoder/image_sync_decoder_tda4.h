/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_sync_decode_tda4.h
 * @brief Image Sync Decode on TDA4
 * @author zhangruiqiang(zhangruiqiang@holomatic.com).
 * @date 2021-11-17
 */

#ifndef __HOLO_SENSORS_CAMERA_IMAGE_SYNC_DECODER_TDA4_H
#define __HOLO_SENSORS_CAMERA_IMAGE_SYNC_DECODER_TDA4_H

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

namespace holo
{
namespace sensors
{
namespace camera
{
struct SyncDecodeObject
{
    vx_node             decode_node0; 
    vx_node             decode_node1; 

    vx_image            node0_dst_image;
    vx_image            node1_dst_image;

    vx_uint32           node0_dst_width;
    vx_uint32           node0_dst_height;
    vx_uint32           node1_dst_width;
    vx_uint32           node1_dst_height;

    vx_uint8*           node00_dst_data_ptr;
    vx_uint8*           node00_dst_data_ptr_uv;
    vx_uint8*           node01_dst_data_ptr;
    vx_uint8*           node01_dst_data_ptr_uv;
    vx_uint8*           node10_dst_data_ptr;
    vx_uint8*           node10_dst_data_ptr_uv;
    vx_uint8*           node11_dst_data_ptr;
    vx_uint8*           node11_dst_data_ptr_uv;

    vx_kernel           kernel;

    vx_user_data_object node0_configuration_object;
    vx_user_data_object node0_bitstream_object;
    vx_user_data_object node1_configuration_object;
    vx_user_data_object node1_bitstream_object;

    uint8_t*            node0_bitstream;
    uint8_t*            node1_bitstream;

    vx_size             node0_bitstream_size;
    vx_size             node1_bitstream_size;
};

struct AppSyncDecodeObject
{
    vx_context          context;
    vx_graph            graph;
    struct SyncDecodeObject decodeObject;
};

vx_status sync_decode_app_init(struct AppSyncDecodeObject* object, vx_context context);
vx_status sync_decode_app_run(struct AppSyncDecodeObject* object);
void sync_decode_app_deinit(struct AppSyncDecodeObject* object);
}  // namespace camera
}  // namespace sensors
}  // namespace holo

#endif  //__HOLO_SENSORS_CAMERA_IMAGE_SYNC_DECODER_TDA4_H