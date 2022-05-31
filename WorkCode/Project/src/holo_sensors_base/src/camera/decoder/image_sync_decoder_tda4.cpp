/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_sync_decode_tda4.cpp
 * @brief Image Sync Decode on TDA4
 * @author zhangruiqiang(zhangruiqiang@holomatic.com).
 * @date 2021-11-17
 */

#include <holo/sensors/camera/decoder/image_sync_decoder_tda4.h>

namespace holo
{
namespace sensors
{
namespace camera
{
vx_status sync_decode_app_init(struct AppSyncDecodeObject* object, vx_context context)
{
    vx_status status = VX_SUCCESS;
    object->context  = context;
    tivx_video_decoder_params_t params;

    if (vx_true_e != tivxIsTargetEnabled(TIVX_TARGET_VDEC1))
    {
        status = VX_FAILURE;
        LOG(ERROR) << "tivxIsTargetDisabled !";
        return status;
    }

    tivx_video_decoder_params_init(&params);

    object->decodeObject.node0_configuration_object =
        vxCreateUserDataObject(object->context, "tivx_video_decoder_params_t", sizeof(tivx_video_decoder_params_t), NULL);
    if (vxGetStatus((vx_reference)object->decodeObject.node0_configuration_object) != VX_SUCCESS)
    {
        printf("configuration create failed!\n");
        return VX_FAILURE;
    }
    object->decodeObject.node0_bitstream_object = vxCreateUserDataObject(
        object->context, "video_bitstream", 
        sizeof(uint8_t) * object->decodeObject.node0_dst_width * object->decodeObject.node0_dst_height * 3 / 2, NULL);
    
    object->decodeObject.node1_configuration_object =
        vxCreateUserDataObject(object->context, "tivx_video_decoder_params_t", sizeof(tivx_video_decoder_params_t), NULL);
    if (vxGetStatus((vx_reference)object->decodeObject.node1_configuration_object) != VX_SUCCESS)
    {
        printf("configuration create failed!\n");
        return VX_FAILURE;
    }
    object->decodeObject.node1_bitstream_object = vxCreateUserDataObject(
        object->context, "video_bitstream", 
        sizeof(uint8_t) * object->decodeObject.node1_dst_width * object->decodeObject.node1_dst_height * 3 / 2, NULL);

    params.bitstream_format = TIVX_BITSTREAM_FORMAT_H264;

    vxCopyUserDataObject(object->decodeObject.node0_configuration_object, 0, sizeof(tivx_video_decoder_params_t),
                         &params, VX_WRITE_ONLY, VX_MEMORY_TYPE_HOST);
    vxCopyUserDataObject(object->decodeObject.node1_configuration_object, 0, sizeof(tivx_video_decoder_params_t),
                         &params, VX_WRITE_ONLY, VX_MEMORY_TYPE_HOST);

    object->decodeObject.node0_dst_image = vxCreateImage(object->context, object->decodeObject.node0_dst_width,
                                                        object->decodeObject.node0_dst_height, VX_DF_IMAGE_NV12);
    object->decodeObject.node1_dst_image = vxCreateImage(object->context, object->decodeObject.node1_dst_width,
                                                         object->decodeObject.node1_dst_height, VX_DF_IMAGE_NV12);

    object->graph = vxCreateGraph(object->context);
    if (vxGetStatus((vx_reference)object->graph) != VX_SUCCESS)
    {
        status = VX_FAILURE;
        LOG(ERROR) << "vxGetStatus failed !";
        return status;
    }

    object->decodeObject.decode_node0 = tivxVideoDecoderNode(object->graph, object->decodeObject.node0_configuration_object,
                                               object->decodeObject.node0_bitstream_object, object->decodeObject.node0_dst_image);
    object->decodeObject.decode_node1 = tivxVideoDecoderNode(object->graph, object->decodeObject.node1_configuration_object,
                                               object->decodeObject.node1_bitstream_object, object->decodeObject.node1_dst_image);

    vxSetNodeTarget(object->decodeObject.decode_node0, VX_TARGET_STRING, TIVX_TARGET_VDEC1);
    vxSetNodeTarget(object->decodeObject.decode_node1, VX_TARGET_STRING, TIVX_TARGET_VDEC1);

    status = vxVerifyGraph(object->graph);
    tivxTaskWaitMsecs(200);

    return status;
}

vx_status sync_decode_app_run(struct AppSyncDecodeObject* object)
{
    object->decodeObject.node00_dst_data_ptr_uv = 
        object->decodeObject.node00_dst_data_ptr + 
        object->decodeObject.node0_dst_width * object->decodeObject.node0_dst_height / 2;
    object->decodeObject.node01_dst_data_ptr_uv = 
        object->decodeObject.node01_dst_data_ptr + 
        object->decodeObject.node0_dst_width * object->decodeObject.node0_dst_height / 2;
    object->decodeObject.node10_dst_data_ptr_uv = 
        object->decodeObject.node10_dst_data_ptr + 
        object->decodeObject.node1_dst_width * object->decodeObject.node1_dst_height / 2;
    object->decodeObject.node11_dst_data_ptr_uv = 
        object->decodeObject.node11_dst_data_ptr + 
        object->decodeObject.node1_dst_width * object->decodeObject.node1_dst_height / 2;

    vx_map_id map_id;
    vx_status status = VX_SUCCESS;

    vx_rectangle_t             node0_dst_rect_y;
    vx_rectangle_t             node0_dst_rect_uv;
    vx_rectangle_t             node1_dst_rect_y;
    vx_rectangle_t             node1_dst_rect_uv;

    vx_map_id                  node0_dst_map_id_image_y;
    vx_imagepatch_addressing_t node0_dst_image_addr_y;
    vx_map_id                  node0_dst_map_id_image_uv;
    vx_imagepatch_addressing_t node0_dst_image_addr_uv;
    vx_map_id                  node1_dst_map_id_image_y;
    vx_imagepatch_addressing_t node1_dst_image_addr_y;
    vx_map_id                  node1_dst_map_id_image_uv;
    vx_imagepatch_addressing_t node1_dst_image_addr_uv;

    uint8_t*                   node0_dst_data_ptr_y;
    uint8_t*                   node0_dst_data_ptr_uv;
    uint8_t*                   node1_dst_data_ptr_y;
    uint8_t*                   node1_dst_data_ptr_uv;

    vx_uint8*                  node0_bitstream;
    vx_uint8*                  node1_bitstream;

    if (vx_true_e != tivxIsTargetEnabled(TIVX_TARGET_VDEC1))
    {
        status = VX_FAILURE;
        return status;
    }

    vxMapUserDataObject(object->decodeObject.node0_bitstream_object, 0, object->decodeObject.node0_bitstream_size, &map_id,
                        (void**)&node0_bitstream, VX_WRITE_ONLY, VX_MEMORY_TYPE_HOST, 0);
    memcpy(node0_bitstream, object->decodeObject.node0_bitstream, object->decodeObject.node0_bitstream_size);
    vxUnmapUserDataObject(object->decodeObject.node0_bitstream_object, map_id);
    tivxSetUserDataObjectAttribute(object->decodeObject.node0_bitstream_object, TIVX_USER_DATA_OBJECT_VALID_SIZE,
                                   (void*)&(object->decodeObject.node0_bitstream_size), sizeof(vx_size));                        
    vxMapUserDataObject(object->decodeObject.node1_bitstream_object, 0, object->decodeObject.node1_bitstream_size, &map_id,
                        (void**)&node1_bitstream, VX_WRITE_ONLY, VX_MEMORY_TYPE_HOST, 0);
    memcpy(node1_bitstream, object->decodeObject.node1_bitstream, object->decodeObject.node1_bitstream_size);
    vxUnmapUserDataObject(object->decodeObject.node1_bitstream_object, map_id);
    tivxSetUserDataObjectAttribute(object->decodeObject.node1_bitstream_object, TIVX_USER_DATA_OBJECT_VALID_SIZE,
                                   (void*)&(object->decodeObject.node1_bitstream_size), sizeof(vx_size));
    vxProcessGraph(object->graph);

    node0_dst_rect_y.start_x   = 0;
    node0_dst_rect_y.start_y   = 0;
    node0_dst_rect_y.end_x     = object->decodeObject.node0_dst_width;
    node0_dst_rect_y.end_y     = object->decodeObject.node0_dst_height;
    node0_dst_rect_uv.start_x  = 0;
    node0_dst_rect_uv.start_y  = 0;
    node0_dst_rect_uv.end_x    = object->decodeObject.node0_dst_width;
    node0_dst_rect_uv.end_y    = (object->decodeObject.node0_dst_height * 1) / 2;

    node1_dst_rect_y.start_x   = 0;
    node1_dst_rect_y.start_y   = 0;
    node1_dst_rect_y.end_x     = object->decodeObject.node1_dst_width;
    node1_dst_rect_y.end_y     = object->decodeObject.node1_dst_height;
    node1_dst_rect_uv.start_x  = 0;
    node1_dst_rect_uv.start_y  = 0;
    node1_dst_rect_uv.end_x    = object->decodeObject.node1_dst_width;
    node1_dst_rect_uv.end_y    = (object->decodeObject.node1_dst_height * 1) / 2;

    vxMapImagePatch(object->decodeObject.node0_dst_image, &node0_dst_rect_y, 0,
        &node0_dst_map_id_image_y, &node0_dst_image_addr_y,
        (void**)&node0_dst_data_ptr_y, VX_READ_ONLY, VX_MEMORY_TYPE_HOST, VX_NOGAP_X);
    vxMapImagePatch(object->decodeObject.node0_dst_image, &node0_dst_rect_uv, 1,
        &node0_dst_map_id_image_uv, &node0_dst_image_addr_uv,
        (void**)&node0_dst_data_ptr_uv, VX_READ_ONLY, VX_MEMORY_TYPE_HOST, VX_NOGAP_X);

    if ((nullptr == node0_dst_data_ptr_y) || (nullptr == node0_dst_data_ptr_uv))
    {
        vxUnmapImagePatch(object->decodeObject.node0_dst_image, node0_dst_map_id_image_y);
        vxUnmapImagePatch(object->decodeObject.node0_dst_image, node0_dst_map_id_image_uv);
        throw std::runtime_error("TDA4 image decoder node0 decode failed");
    }

    memcpy(object->decodeObject.node00_dst_data_ptr, node0_dst_data_ptr_y,
           object->decodeObject.node0_dst_width * object->decodeObject.node0_dst_height / 2);
    memcpy(object->decodeObject.node01_dst_data_ptr, node0_dst_data_ptr_y + 
           object->decodeObject.node0_dst_width * object->decodeObject.node0_dst_height / 2,
           object->decodeObject.node0_dst_width * object->decodeObject.node0_dst_height / 2);
    memcpy(object->decodeObject.node00_dst_data_ptr_uv, node0_dst_data_ptr_uv,
           object->decodeObject.node0_dst_width * object->decodeObject.node0_dst_height / 2 / 2);
    memcpy(object->decodeObject.node01_dst_data_ptr_uv, node0_dst_data_ptr_uv +
           object->decodeObject.node0_dst_width * object->decodeObject.node0_dst_height / 2 / 2,
           object->decodeObject.node0_dst_width * object->decodeObject.node0_dst_height / 2 / 2);

    vxUnmapImagePatch(object->decodeObject.node0_dst_image, node0_dst_map_id_image_y);
    vxUnmapImagePatch(object->decodeObject.node0_dst_image, node0_dst_map_id_image_uv);

    vxMapImagePatch(object->decodeObject.node1_dst_image, &node1_dst_rect_y, 0,
        &node1_dst_map_id_image_y, &node1_dst_image_addr_y,
        (void**)&node1_dst_data_ptr_y, VX_READ_ONLY, VX_MEMORY_TYPE_HOST, VX_NOGAP_X);
    vxMapImagePatch(object->decodeObject.node1_dst_image, &node1_dst_rect_uv, 1,
        &node1_dst_map_id_image_uv, &node1_dst_image_addr_uv,
        (void**)&node1_dst_data_ptr_uv, VX_READ_ONLY, VX_MEMORY_TYPE_HOST, VX_NOGAP_X);
    
    if ((nullptr == node1_dst_data_ptr_y) || (nullptr == node1_dst_data_ptr_uv))
    {
        vxUnmapImagePatch(object->decodeObject.node1_dst_image, node1_dst_map_id_image_y);
        vxUnmapImagePatch(object->decodeObject.node1_dst_image, node1_dst_map_id_image_uv);
        throw std::runtime_error("TDA4 image decoder node1 decode failed");
    }

    memcpy(object->decodeObject.node10_dst_data_ptr, node1_dst_data_ptr_y,
           object->decodeObject.node1_dst_width * object->decodeObject.node1_dst_height / 2);
    memcpy(object->decodeObject.node11_dst_data_ptr, node1_dst_data_ptr_y + 
           object->decodeObject.node1_dst_width * object->decodeObject.node1_dst_height / 2,
           object->decodeObject.node1_dst_width * object->decodeObject.node1_dst_height / 2);
    memcpy(object->decodeObject.node10_dst_data_ptr_uv, node1_dst_data_ptr_uv,
           object->decodeObject.node1_dst_width * object->decodeObject.node1_dst_height / 2 / 2);
    memcpy(object->decodeObject.node11_dst_data_ptr_uv, node1_dst_data_ptr_uv +
           object->decodeObject.node1_dst_width * object->decodeObject.node1_dst_height / 2 / 2,
           object->decodeObject.node1_dst_width * object->decodeObject.node1_dst_height / 2 / 2);

    vxUnmapImagePatch(object->decodeObject.node1_dst_image, node1_dst_map_id_image_y);
    vxUnmapImagePatch(object->decodeObject.node1_dst_image, node1_dst_map_id_image_uv);

    return status;
}

void sync_decode_app_deinit(struct AppSyncDecodeObject* object)
{
    vxReleaseImage(&object->decodeObject.node0_dst_image);
    vxReleaseImage(&object->decodeObject.node1_dst_image);

    if (object->decodeObject.decode_node0 != nullptr)
    {
        vxReleaseNode(&object->decodeObject.decode_node0);
    }
    if (object->decodeObject.decode_node1 != nullptr)
    {
        vxReleaseNode(&object->decodeObject.decode_node1);
    }

    if (object->graph != nullptr)
    {
        vxReleaseGraph(&object->graph);
    }
}
}  // namespace camera
}  // namespace sensors
}  // namespace holo