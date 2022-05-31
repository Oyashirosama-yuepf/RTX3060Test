/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_sync_encode_tda4.cpp
 * @brief Image Sync Encode on TDA4
 * @author zhangruiqiang(zhangruiqiang@holomatic.com).
 * @date 2021-11-11
 */

#include <holo/log/hololog.h>
#include <holo/sensors/camera/encoder/image_sync_encoder_tda4.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

namespace holo
{
namespace sensors
{
namespace camera
{
vx_status sync_encode_app_init(struct AppSyncEncodeObject* object, vx_context context)
{
    vx_status                   status = VX_SUCCESS;
    tivx_video_encoder_params_t params;
    uint32_t                    node0_max_bitstream_size;
    uint32_t                    node1_max_bitstream_size;

    object->context = context;

    if (vx_true_e != tivxIsTargetEnabled(TIVX_TARGET_VENC1))
    {
        status = VX_FAILURE;
        LOG(ERROR) << "tivxIsTargetDisabled !";
        return status;
    }

    object->encodeObject.node0_src_image = vxCreateImage(object->context, object->encodeObject.node0_src_width,
                                                         object->encodeObject.node0_src_height, VX_DF_IMAGE_NV12);
    object->encodeObject.node1_src_image = vxCreateImage(object->context, object->encodeObject.node1_src_width,
                                                         object->encodeObject.node1_src_height, VX_DF_IMAGE_NV12);
    tivx_video_encoder_params_init(&params);
    params.bitstream_format = TIVX_BITSTREAM_FORMAT_H264;
    params.bitrate          = object->encodeObject.bitrate;
    params.framerate        = object->encodeObject.fps;
    params.idr_period       = 1;
    params.i_period         = 1;

    object->encodeObject.node0_configuration_object = vxCreateUserDataObject(
        object->context, "tivx_video_encoder_params_t", sizeof(tivx_video_encoder_params_t), NULL);
    if (vxGetStatus((vx_reference)object->encodeObject.node0_configuration_object) != VX_SUCCESS)
    {
        status = VX_FAILURE;
        return status;
    }
    node0_max_bitstream_size = ((uint32_t)(object->encodeObject.node0_src_width / 16) *
                                (uint32_t)(object->encodeObject.node0_src_height / 16) * WORST_QP_SIZE) +
                               ((object->encodeObject.node0_src_height >> 4) * CODED_BUFFER_INFO_SECTION_SIZE);
    object->encodeObject.node0_bitstream_object = vxCreateUserDataObject(
        object->context, "tivx_video_bitstream_t", sizeof(uint8_t) * node0_max_bitstream_size, NULL);
    if (vxGetStatus((vx_reference)object->encodeObject.node0_bitstream_object) != VX_SUCCESS)
    {
        status = VX_FAILURE;
        return status;
    }
    vxCopyUserDataObject(object->encodeObject.node0_configuration_object, 0, sizeof(tivx_video_encoder_params_t),
                         &params, VX_WRITE_ONLY, VX_MEMORY_TYPE_HOST);
    object->encodeObject.node1_configuration_object = vxCreateUserDataObject(
        object->context, "tivx_video_encoder_params_t", sizeof(tivx_video_encoder_params_t), NULL);
    if (vxGetStatus((vx_reference)object->encodeObject.node1_configuration_object) != VX_SUCCESS)
    {
        status = VX_FAILURE;
        return status;
    }
    node1_max_bitstream_size = ((uint32_t)(object->encodeObject.node1_src_width / 16) *
                                (uint32_t)(object->encodeObject.node1_src_height / 16) * WORST_QP_SIZE) +
                               ((object->encodeObject.node1_src_height >> 4) * CODED_BUFFER_INFO_SECTION_SIZE);
    object->encodeObject.node1_bitstream_object = vxCreateUserDataObject(
        object->context, "tivx_video_bitstream_t", sizeof(uint8_t) * node1_max_bitstream_size, NULL);
    if (vxGetStatus((vx_reference)object->encodeObject.node1_bitstream_object) != VX_SUCCESS)
    {
        status = VX_FAILURE;
        return status;
    }
    vxCopyUserDataObject(object->encodeObject.node1_configuration_object, 0, sizeof(tivx_video_encoder_params_t),
                         &params, VX_WRITE_ONLY, VX_MEMORY_TYPE_HOST);
    object->graph = vxCreateGraph(object->context);
    if (vxGetStatus((vx_reference)object->graph) != VX_SUCCESS)
    {
        status = VX_FAILURE;
        LOG(ERROR) << "vxGetStatus failed !";
        return status;
    }

    object->encodeObject.encode_node0 =
        tivxVideoEncoderNode(object->graph, object->encodeObject.node0_configuration_object,
                             object->encodeObject.node0_src_image, object->encodeObject.node0_bitstream_object);
    object->encodeObject.encode_node1 =
        tivxVideoEncoderNode(object->graph, object->encodeObject.node1_configuration_object,
                             object->encodeObject.node1_src_image, object->encodeObject.node1_bitstream_object);

    vxSetNodeTarget(object->encodeObject.encode_node0, VX_TARGET_STRING, TIVX_TARGET_VENC1);
    vxSetNodeTarget(object->encodeObject.encode_node1, VX_TARGET_STRING, TIVX_TARGET_VENC1);

    status = vxVerifyGraph(object->graph);

    return status;
}

vx_status sync_encode_app_run(struct AppSyncEncodeObject* object)
{  
    object->encodeObject.node00_src_data_ptr_uv = 
        object->encodeObject.node00_src_data_ptr + 
        object->encodeObject.node0_src_width * object->encodeObject.node0_src_height / 2;
    object->encodeObject.node01_src_data_ptr_uv = 
        object->encodeObject.node01_src_data_ptr + 
        object->encodeObject.node0_src_width * object->encodeObject.node0_src_height / 2;
    object->encodeObject.node10_src_data_ptr_uv = 
        object->encodeObject.node10_src_data_ptr + 
        object->encodeObject.node1_src_width * object->encodeObject.node1_src_height / 2;
    object->encodeObject.node11_src_data_ptr_uv = 
        object->encodeObject.node11_src_data_ptr + 
        object->encodeObject.node1_src_width * object->encodeObject.node1_src_height / 2;

    vx_map_id map_id;
    vx_status status = VX_SUCCESS;

    vx_rectangle_t node0_src_rect_y;
    vx_rectangle_t node0_src_rect_uv;
    vx_rectangle_t node1_src_rect_y;
    vx_rectangle_t node1_src_rect_uv;

    vx_map_id                  node0_src_map_id_image_y;
    vx_imagepatch_addressing_t node0_src_image_addr_y;
    vx_map_id                  node0_src_map_id_image_uv;
    vx_imagepatch_addressing_t node0_src_image_addr_uv;
    vx_map_id                  node1_src_map_id_image_y;
    vx_imagepatch_addressing_t node1_src_image_addr_y;
    vx_map_id                  node1_src_map_id_image_uv;
    vx_imagepatch_addressing_t node1_src_image_addr_uv;

    uint8_t* node0_src_data_ptr_y;
    uint8_t* node0_src_data_ptr_uv;
    uint8_t* node1_src_data_ptr_y;
    uint8_t* node1_src_data_ptr_uv;

    if (vx_true_e != tivxIsTargetEnabled(TIVX_TARGET_VENC1))
    {
        status = VX_FAILURE;
        return status;
    }

    node0_src_rect_y.start_x  = 0;
    node0_src_rect_y.start_y  = 0;
    node0_src_rect_y.end_x    = object->encodeObject.node0_src_width;
    node0_src_rect_y.end_y    = object->encodeObject.node0_src_height;
    node0_src_rect_uv.start_x = 0;
    node0_src_rect_uv.start_y = 0;
    node0_src_rect_uv.end_x   = object->encodeObject.node0_src_width;
    node0_src_rect_uv.end_y   = (object->encodeObject.node0_src_height * 1) / 2;
    node1_src_rect_y.start_x  = 0;
    node1_src_rect_y.start_y  = 0;
    node1_src_rect_y.end_x    = object->encodeObject.node1_src_width;
    node1_src_rect_y.end_y    = object->encodeObject.node1_src_height;
    node1_src_rect_uv.start_x = 0;
    node1_src_rect_uv.start_y = 0;
    node1_src_rect_uv.end_x   = object->encodeObject.node1_src_width;
    node1_src_rect_uv.end_y   = (object->encodeObject.node1_src_height * 1) / 2;

    vxMapImagePatch(object->encodeObject.node0_src_image, &node0_src_rect_y, 0, &node0_src_map_id_image_y,
                    &node0_src_image_addr_y, (void**)&node0_src_data_ptr_y, VX_WRITE_ONLY, VX_MEMORY_TYPE_HOST,
                    VX_NOGAP_X);
    vxMapImagePatch(object->encodeObject.node0_src_image, &node0_src_rect_uv, 1, &node0_src_map_id_image_uv,
                    &node0_src_image_addr_uv, (void**)&node0_src_data_ptr_uv, VX_WRITE_ONLY, VX_MEMORY_TYPE_HOST,
                    VX_NOGAP_X);

    memcpy(node0_src_data_ptr_y, object->encodeObject.node00_src_data_ptr, 
           object->encodeObject.node0_src_width * object->encodeObject.node0_src_height / 2);
    memcpy(node0_src_data_ptr_y +
           object->encodeObject.node0_src_width * object->encodeObject.node0_src_height / 2
           , object->encodeObject.node01_src_data_ptr, 
           object->encodeObject.node0_src_width * object->encodeObject.node0_src_height / 2);
    memcpy(node0_src_data_ptr_uv, object->encodeObject.node00_src_data_ptr_uv, 
           object->encodeObject.node0_src_width * object->encodeObject.node0_src_height / 2 / 2);
    memcpy(node0_src_data_ptr_uv +
           object->encodeObject.node0_src_width * object->encodeObject.node0_src_height / 2 / 2
           , object->encodeObject.node01_src_data_ptr_uv, 
           object->encodeObject.node0_src_width * object->encodeObject.node0_src_height / 2 / 2);

    vxUnmapImagePatch(object->encodeObject.node0_src_image, node0_src_map_id_image_y);
    vxUnmapImagePatch(object->encodeObject.node0_src_image, node0_src_map_id_image_uv);
    vxMapImagePatch(object->encodeObject.node1_src_image, &node1_src_rect_y, 0, &node1_src_map_id_image_y,
                    &node1_src_image_addr_y, (void**)&node1_src_data_ptr_y, VX_WRITE_ONLY, VX_MEMORY_TYPE_HOST,
                    VX_NOGAP_X);
    vxMapImagePatch(object->encodeObject.node1_src_image, &node1_src_rect_uv, 1, &node1_src_map_id_image_uv,
                    &node1_src_image_addr_uv, (void**)&node1_src_data_ptr_uv, VX_WRITE_ONLY, VX_MEMORY_TYPE_HOST,
                    VX_NOGAP_X);

    memcpy(node1_src_data_ptr_y, object->encodeObject.node10_src_data_ptr, 
           object->encodeObject.node1_src_width * object->encodeObject.node1_src_height / 2);
    memcpy(node1_src_data_ptr_y +
           object->encodeObject.node1_src_width * object->encodeObject.node1_src_height / 2
           , object->encodeObject.node11_src_data_ptr, 
           object->encodeObject.node1_src_width * object->encodeObject.node1_src_height / 2);
           
    memcpy(node1_src_data_ptr_uv, object->encodeObject.node10_src_data_ptr_uv, 
           object->encodeObject.node1_src_width * object->encodeObject.node1_src_height / 2 / 2);
    memcpy(node1_src_data_ptr_uv +
           object->encodeObject.node1_src_width * object->encodeObject.node1_src_height / 2 / 2
           , object->encodeObject.node11_src_data_ptr_uv, 
           object->encodeObject.node1_src_width * object->encodeObject.node1_src_height / 2 / 2);

    vxUnmapImagePatch(object->encodeObject.node1_src_image, node1_src_map_id_image_y);
    vxUnmapImagePatch(object->encodeObject.node1_src_image, node1_src_map_id_image_uv);

    vxProcessGraph(object->graph);
    vxQueryUserDataObject(object->encodeObject.node0_bitstream_object, TIVX_USER_DATA_OBJECT_VALID_SIZE,
                          &object->encodeObject.node0_bitstream_size, sizeof(vx_size));
    vxMapUserDataObject(object->encodeObject.node0_bitstream_object, 0, object->encodeObject.node0_bitstream_size,
                        &map_id, (void**)&object->encodeObject.node0_bitstream, VX_READ_ONLY, VX_MEMORY_TYPE_HOST, 0);
    vxUnmapUserDataObject(object->encodeObject.node0_bitstream_object, map_id);
    vxQueryUserDataObject(object->encodeObject.node1_bitstream_object, TIVX_USER_DATA_OBJECT_VALID_SIZE,
                          &object->encodeObject.node1_bitstream_size, sizeof(vx_size));
    vxMapUserDataObject(object->encodeObject.node1_bitstream_object, 0, object->encodeObject.node1_bitstream_size,
                        &map_id, (void**)&object->encodeObject.node1_bitstream, VX_READ_ONLY, VX_MEMORY_TYPE_HOST, 0);
    vxUnmapUserDataObject(object->encodeObject.node1_bitstream_object, map_id);

    LOG(INFO) << "query data success";

    return status;
}

void sync_encode_app_deinit(struct AppSyncEncodeObject* object)
{
    vxReleaseImage(&object->encodeObject.node0_src_image);
    vxReleaseImage(&object->encodeObject.node1_src_image);

    if (object->encodeObject.encode_node0 != nullptr)
    {
        vxReleaseNode(&object->encodeObject.encode_node0);
    }
    if (object->encodeObject.encode_node1 != nullptr)
    {
        vxReleaseNode(&object->encodeObject.encode_node1);
    }

    if (object->graph != nullptr)
    {
        vxReleaseGraph(&object->graph);
    }
}
}  // namespace camera
}  // namespace sensors
}  // namespace holo