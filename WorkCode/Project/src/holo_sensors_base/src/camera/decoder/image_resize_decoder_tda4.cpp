/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_resize_decode_tda4.cpp
 * @brief Image Resize And Decode on TDA4
 * @author zhangruiqiang(zhangruiqiang@holomatic.com).
 * @date 2021-11-15
 */

#include <holo/sensors/camera/decoder/image_resize_decoder_tda4.h>

namespace holo
{
namespace sensors
{
namespace camera
{
vx_status resize_decode_app_init(struct AppResizeDecodeObject* object, vx_context context)
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
    object->decodeObject.configuration_object =
        vxCreateUserDataObject(object->context, "tivx_video_decoder_params_t", sizeof(tivx_video_decoder_params_t), NULL);
    if (vxGetStatus((vx_reference)object->decodeObject.configuration_object) != VX_SUCCESS)
    {
        printf("configuration create failed!\n");
        return VX_FAILURE;
    }
    object->decodeObject.bitstream_object = vxCreateUserDataObject(
        object->context, "video_bitstream", 
        sizeof(uint8_t) * object->decodeObject.node_src_width * object->decodeObject.node_src_height * 3 / 2, NULL);
    params.bitstream_format = TIVX_BITSTREAM_FORMAT_H264;
    vxCopyUserDataObject(object->decodeObject.configuration_object, 0, sizeof(tivx_video_decoder_params_t),
                         &params, VX_WRITE_ONLY, VX_MEMORY_TYPE_HOST);

    object->decodeObject.node_src_image = vxCreateImage(object->context, object->decodeObject.node_src_width,
                                                        object->decodeObject.node_src_height, VX_DF_IMAGE_NV12);

    object->graph = vxCreateGraph(object->context);
    if (vxGetStatus((vx_reference)object->graph) != VX_SUCCESS)
    {
        status = VX_FAILURE;
        LOG(ERROR) << "vxGetStatus failed !";
        return status;
    }

    object->decodeObject.decode_node = tivxVideoDecoderNode(object->graph, object->decodeObject.configuration_object,
                                               object->decodeObject.bitstream_object, object->decodeObject.node_src_image);
    vxSetNodeTarget(object->decodeObject.decode_node, VX_TARGET_STRING, TIVX_TARGET_VDEC1);

    status = vxVerifyGraph(object->graph);
    tivxTaskWaitMsecs(200);

    return status;
}

vx_status resize_decode_app_run(struct AppResizeDecodeObject* object)
{
    object->decodeObject.node_dst_data_ptr_uv =
        object->decodeObject.node_dst_data_ptr +
        object->decodeObject.node_dst_width * object->decodeObject.node_dst_height;
    
    vx_map_id map_id;
    vx_status status = VX_SUCCESS;

    vx_rectangle_t             node_src_rect_y;
    vx_rectangle_t             node_src_rect_uv;

    vx_map_id                  node_src_map_id_image_y;
    vx_imagepatch_addressing_t node_src_image_addr_y;
    vx_map_id                  node_src_map_id_image_uv;
    vx_imagepatch_addressing_t node_src_image_addr_uv;

    uint8_t*                   node_src_data_ptr_y;
    uint8_t*                   node_src_data_ptr_uv;

    vx_uint8* bitstream;

    if (vx_true_e != tivxIsTargetEnabled(TIVX_TARGET_VDEC1))
    {
        status = VX_FAILURE;
        return status;
    }

    node_src_rect_y.start_x   = 0;
    node_src_rect_y.start_y   = 0;
    node_src_rect_y.end_x     = object->decodeObject.node_src_width;
    node_src_rect_y.end_y     = object->decodeObject.node_src_height;
    node_src_rect_uv.start_x  = 0;
    node_src_rect_uv.start_y  = 0;
    node_src_rect_uv.end_x    = object->decodeObject.node_src_width;
    node_src_rect_uv.end_y    = (object->decodeObject.node_src_height * 1) / 2;

    vxMapUserDataObject(object->decodeObject.bitstream_object, 0, object->decodeObject.node_bitstream_size, &map_id,
                        (void**)&bitstream, VX_WRITE_ONLY, VX_MEMORY_TYPE_HOST, 0);
    memcpy(bitstream, object->decodeObject.node_bitstream, object->decodeObject.node_bitstream_size);
    vxUnmapUserDataObject(object->decodeObject.bitstream_object, map_id);
    tivxSetUserDataObjectAttribute(object->decodeObject.bitstream_object, TIVX_USER_DATA_OBJECT_VALID_SIZE,
                                   (void*)&(object->decodeObject.node_bitstream_size), sizeof(vx_size));

    vxProcessGraph(object->graph);

    vxMapImagePatch(object->decodeObject.node_src_image, &node_src_rect_y, 0,
        &node_src_map_id_image_y, &node_src_image_addr_y,
        (void**)&node_src_data_ptr_y, VX_READ_ONLY, VX_MEMORY_TYPE_HOST, VX_NOGAP_X);
    vxMapImagePatch(object->decodeObject.node_src_image, &node_src_rect_uv, 1,
        &node_src_map_id_image_uv, &node_src_image_addr_uv,
        (void**)&node_src_data_ptr_uv, VX_READ_ONLY, VX_MEMORY_TYPE_HOST, VX_NOGAP_X);
    if (node_src_data_ptr_y != nullptr)
    {
        libyuv::NV12Scale(node_src_data_ptr_y, object->decodeObject.node_src_width, 
                          node_src_data_ptr_uv, object->decodeObject.node_src_width, 
                          object->decodeObject.node_src_width, object->decodeObject.node_src_height, 
                          object->decodeObject.node_dst_data_ptr, object->decodeObject.node_dst_width, 
                          object->decodeObject.node_dst_data_ptr_uv, object->decodeObject.node_dst_width, 
                          object->decodeObject.node_dst_width, object->decodeObject.node_dst_height, 
                          libyuv::FilterMode::kFilterBox);
    }
    else
    {
        vxUnmapImagePatch(object->decodeObject.node_src_image, node_src_map_id_image_y);
        vxUnmapImagePatch(object->decodeObject.node_src_image, node_src_map_id_image_uv);
        return -1;
    }
    vxUnmapImagePatch(object->decodeObject.node_src_image, node_src_map_id_image_y);
    vxUnmapImagePatch(object->decodeObject.node_src_image, node_src_map_id_image_uv);

    return status;
}

void resize_decode_app_deinit(struct AppResizeDecodeObject* object)
{
    vxReleaseImage(&object->decodeObject.node_src_image);

    if (object->decodeObject.decode_node != nullptr)
    {
        vxReleaseNode(&object->decodeObject.decode_node);
    }

    if (object->graph != nullptr)
    {
        vxReleaseGraph(&object->graph);
    }
}

}  // namespace camera
}  // namespace sensors
}  // namespace holo