/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_resize_encode_tda4.h
 * @brief Image Resize And Encode on TDA4
 * @author zhangruiqiang(zhangruiqiang@holomatic.com).
 * @date 2021-11-11
 */

#ifndef _HOLO_SENSORS_CAMERA_IMAGE_RESIZE_ENCODE_TDA4_H
#define _HOLO_SENSORS_CAMERA_IMAGE_RESIZE_ENCODE_TDA4_H

#include <TI/j7.h>
#include <VX/vx.h>
#include <VX/vxu.h>

extern "C" 
{
#include <TI/tivx.h>
#include <app_init.h>
}

namespace holo
{
namespace sensors
{
namespace camera
{
struct ResizeEncodeObject
{
    vx_node             encode_node;
    vx_node             resize_node;

    vx_image            node_dst_image;
    vx_image            node_src_image;

    vx_uint32           node_dst_width;
    vx_uint32           node_dst_height;
    vx_uint32           node_src_width;
    vx_uint32           node_src_height;
    
    vx_uint8*           node_src_data_ptr;
    vx_uint8*           node_src_data_ptr_uv;

    vx_user_data_object node_configuration_object;
    vx_user_data_object node_bitstream_object;
    vx_user_data_object node_src_msc_coeff_object;

    vx_uint8*           node_bitstream;
    
    uint32_t            bitrate;
    uint32_t            fps;

    vx_size             node_bitstream_size;
};

struct AppResizeEncodeObject
{
    vx_context context;
    vx_graph   graph;
    struct ResizeEncodeObject encodeObject;
};

vx_status resize_encode_app_init(struct AppResizeEncodeObject* object, vx_context context);
vx_status resize_encode_app_run(struct AppResizeEncodeObject* object);
void      resize_encode_app_deinit(struct AppResizeEncodeObject* object);

}  // namespace camera
}  // namespace sensors
}  // namespace holo

#endif  //_HOLO_SENSORS_CAMERA_IMAGE_RESIZE_ENCODE_TDA4_H