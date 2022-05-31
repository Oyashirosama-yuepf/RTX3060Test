/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_sync_encode_tda4.h
 * @brief Image Sync Encode on TDA4
 * @author zhangruiqiang(zhangruiqiang@holomatic.com).
 * @date 2021-11-11
 */

#ifndef _HOLO_SENSORS_CAMERA_IMAGE_SYNC_ENCODER_TDA4_H
#define _HOLO_SENSORS_CAMERA_IMAGE_SYNC_ENCODER_TDA4_H

#include <TI/j7.h>
#include <VX/vx.h>
#include <VX/vxu.h>

#include <chrono>

extern "C" 
{
#include <TI/tivx.h>
#include <tivx_utils_file_rd_wr.h>
#include <app_init.h>
}

namespace holo
{
namespace sensors
{
namespace camera
{
struct SyncEncodeObject
{
    vx_node             encode_node0;
    vx_node             encode_node1;

    vx_image            node0_src_image;
    vx_image            node1_src_image;

    vx_uint32           node0_src_width;
    vx_uint32           node0_src_height;
    vx_uint32           node1_src_width;
    vx_uint32           node1_src_height;

    vx_uint8*           node00_src_data_ptr;
    vx_uint8*           node00_src_data_ptr_uv;
    vx_uint8*           node01_src_data_ptr;
    vx_uint8*           node01_src_data_ptr_uv;
    vx_uint8*           node10_src_data_ptr;
    vx_uint8*           node10_src_data_ptr_uv;
    vx_uint8*           node11_src_data_ptr;
    vx_uint8*           node11_src_data_ptr_uv;

    vx_user_data_object node0_configuration_object;
    vx_user_data_object node0_bitstream_object;
    vx_user_data_object node1_configuration_object;
    vx_user_data_object node1_bitstream_object;

    vx_uint8*           node0_bitstream;
    vx_uint8*           node1_bitstream;

    uint32_t            bitrate;
    uint32_t            fps;

    vx_size             node0_bitstream_size;
    vx_size             node1_bitstream_size;
};

struct AppSyncEncodeObject
{
    vx_context context;
    vx_graph   graph;
    struct SyncEncodeObject encodeObject;
};

vx_status sync_encode_app_init(struct AppSyncEncodeObject* object, vx_context context);
vx_status sync_encode_app_run(struct AppSyncEncodeObject* object);
void      sync_encode_app_deinit(struct AppSyncEncodeObject* object);
}  // namespace camera
}  // namespace sensors
}  // namespace holo

#endif  //_HOLO_SENSORS_CAMERA_IMAGE_SYNC_ENCODER_TDA4_H