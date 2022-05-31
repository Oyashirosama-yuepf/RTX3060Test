/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_resize_encode_tda4.cpp
 * @brief Image Resize And Encode on TDA4
 * @author zhangruiqiang(zhangruiqiang@holomatic.com).
 * @date 2021-11-11
 */

#include <holo/log/hololog.h>
#include <holo/sensors/camera/encoder/image_resize_encode_tda4.h>
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
vx_status resize_encode_app_init(struct AppResizeEncodeObject* object, vx_context context)
{
    vx_status                   status = VX_SUCCESS;
    tivx_video_encoder_params_t params;
    uint32_t                    node_max_bitstream_size;

    object->context = context;

    if (vx_true_e != tivxIsTargetEnabled(TIVX_TARGET_VENC1))
    {
        status = VX_FAILURE;
        LOG(ERROR) << "tivxIsTargetDisabled !";
        return status;
    }
    if (vx_true_e != tivxIsTargetEnabled(TIVX_TARGET_VPAC_MSC1))
    {
        status = VX_FAILURE;
        LOG(ERROR) << "tivxIsTargetDisabled !";
        return status;
    }

    object->encodeObject.node_src_image = vxCreateImage(object->context, object->encodeObject.node_src_width,
                                                        object->encodeObject.node_src_height, VX_DF_IMAGE_NV12);
    object->encodeObject.node_dst_image = vxCreateImage(object->context, object->encodeObject.node_dst_width,
                                                         object->encodeObject.node_dst_height, VX_DF_IMAGE_NV12);

    tivx_video_encoder_params_init(&params);
    params.bitstream_format = TIVX_BITSTREAM_FORMAT_H264;
    params.bitrate          = object->encodeObject.bitrate;
    params.framerate        = object->encodeObject.fps;
    params.idr_period       = 1;
    params.i_period         = 1;

    object->encodeObject.node_configuration_object = vxCreateUserDataObject(
        object->context, "tivx_video_encoder_params_t", sizeof(tivx_video_encoder_params_t), NULL);
    if (vxGetStatus((vx_reference)object->encodeObject.node_configuration_object) != VX_SUCCESS)
    {
        status = VX_FAILURE;
        return status;
    }
    node_max_bitstream_size = ((uint32_t)(object->encodeObject.node_dst_width / 16) *
                                (uint32_t)(object->encodeObject.node_dst_height / 16) * WORST_QP_SIZE) +
                               ((object->encodeObject.node_dst_height >> 4) * CODED_BUFFER_INFO_SECTION_SIZE);
    object->encodeObject.node_bitstream_object = vxCreateUserDataObject(
        object->context, "tivx_video_bitstream_t", sizeof(uint8_t) * node_max_bitstream_size, NULL);
    if (vxGetStatus((vx_reference)object->encodeObject.node_bitstream_object) != VX_SUCCESS)
    {
        status = VX_FAILURE;
        return status;
    }
    vxCopyUserDataObject(object->encodeObject.node_configuration_object, 0, sizeof(tivx_video_encoder_params_t),
                         &params, VX_WRITE_ONLY, VX_MEMORY_TYPE_HOST);
    object->graph = vxCreateGraph(object->context);
    if (vxGetStatus((vx_reference)object->graph) != VX_SUCCESS)
    {
        status = VX_FAILURE;
        LOG(ERROR) << "vxGetStatus failed !";
        return status;
    }

    object->encodeObject.resize_node =
        tivxVpacMscScaleNode(object->graph, object->encodeObject.node_src_image, object->encodeObject.node_dst_image, 
                             NULL, NULL, NULL, NULL);
    object->encodeObject.encode_node =
        tivxVideoEncoderNode(object->graph, object->encodeObject.node_configuration_object,
                             object->encodeObject.node_dst_image, object->encodeObject.node_bitstream_object);

    vxSetNodeTarget(object->encodeObject.encode_node, VX_TARGET_STRING, TIVX_TARGET_VENC1);
    vxSetNodeTarget(object->encodeObject.resize_node, VX_TARGET_STRING, TIVX_TARGET_VPAC_MSC1);

    status = vxVerifyGraph(object->graph);

    vx_reference                 refs[1] = {0};
    tivx_vpac_msc_coefficients_t msc_coeff;
    tivx_vpac_msc_coefficients_params_init(&msc_coeff, VX_INTERPOLATION_BILINEAR);
    object->encodeObject.node_src_msc_coeff_object = vxCreateUserDataObject(
        object->context, "tivx_vpac_msc_coefficients_t", sizeof(tivx_vpac_msc_coefficients_t), NULL);
    if (status == VX_SUCCESS)
    {
        status =
            vxCopyUserDataObject(object->encodeObject.node_src_msc_coeff_object, 0,
                                 sizeof(tivx_vpac_msc_coefficients_t), &msc_coeff, VX_WRITE_ONLY, VX_MEMORY_TYPE_HOST);
    }
    refs[0] = (vx_reference)object->encodeObject.node_src_msc_coeff_object;
    if (status == VX_SUCCESS)
    {
        status = tivxNodeSendCommand(object->encodeObject.resize_node, 0, TIVX_VPAC_MSC_CMD_SET_COEFF, refs, 1u);
    }

    return status;
}

vx_status resize_encode_app_run(struct AppResizeEncodeObject* object)
{
    object->encodeObject.node_src_data_ptr_uv =
        object->encodeObject.node_src_data_ptr +
        object->encodeObject.node_src_width * object->encodeObject.node_src_height;

    vx_map_id map_id;
    vx_status status = VX_SUCCESS;

    vx_rectangle_t node_src_rect_y;
    vx_rectangle_t node_src_rect_uv;

    vx_map_id                  node_src_map_id_image_y;
    vx_imagepatch_addressing_t node_src_image_addr_y;
    vx_map_id                  node_src_map_id_image_uv;
    vx_imagepatch_addressing_t node_src_image_addr_uv;

    uint8_t* node_src_data_ptr_y;
    uint8_t* node_src_data_ptr_uv;

    if (vx_true_e != tivxIsTargetEnabled(TIVX_TARGET_VENC1))
    {
        status = VX_FAILURE;
        return status;
    }
    if (vx_true_e != tivxIsTargetEnabled(TIVX_TARGET_VPAC_MSC1))
    {
        status = VX_FAILURE;
        return status;
    }

    node_src_rect_y.start_x   = 0;
    node_src_rect_y.start_y   = 0;
    node_src_rect_y.end_x     = object->encodeObject.node_src_width;
    node_src_rect_y.end_y     = object->encodeObject.node_src_height;
    node_src_rect_uv.start_x  = 0;
    node_src_rect_uv.start_y  = 0;
    node_src_rect_uv.end_x    = object->encodeObject.node_src_width;
    node_src_rect_uv.end_y    = (object->encodeObject.node_src_height * 1) / 2;

    vxMapImagePatch(object->encodeObject.node_src_image, &node_src_rect_y, 0,
        &node_src_map_id_image_y, &node_src_image_addr_y,
        (void**)&node_src_data_ptr_y, VX_WRITE_ONLY, VX_MEMORY_TYPE_HOST, VX_NOGAP_X);
    vxMapImagePatch(object->encodeObject.node_src_image, &node_src_rect_uv, 1,
        &node_src_map_id_image_uv, &node_src_image_addr_uv,
        (void**)&node_src_data_ptr_uv, VX_WRITE_ONLY, VX_MEMORY_TYPE_HOST, VX_NOGAP_X);
    if (object->encodeObject.node_src_data_ptr != nullptr)
    {
        memcpy(node_src_data_ptr_y, object->encodeObject.node_src_data_ptr,
               object->encodeObject.node_src_width * object->encodeObject.node_src_height);
        memcpy(node_src_data_ptr_uv, object->encodeObject.node_src_data_ptr_uv,
               object->encodeObject.node_src_width * object->encodeObject.node_src_height / 2);
    }
    else
    {
        vxUnmapImagePatch(object->encodeObject.node_src_image, node_src_map_id_image_y);
        vxUnmapImagePatch(object->encodeObject.node_src_image, node_src_map_id_image_uv);
        return -1;
    }
    vxUnmapImagePatch(object->encodeObject.node_src_image, node_src_map_id_image_y);
    vxUnmapImagePatch(object->encodeObject.node_src_image, node_src_map_id_image_uv);

    vxProcessGraph(object->graph);

    vxQueryUserDataObject(object->encodeObject.node_bitstream_object, TIVX_USER_DATA_OBJECT_VALID_SIZE,
                          &object->encodeObject.node_bitstream_size, sizeof(vx_size));
    vxMapUserDataObject(object->encodeObject.node_bitstream_object, 0, object->encodeObject.node_bitstream_size,
                        &map_id, (void**)&object->encodeObject.node_bitstream, VX_READ_ONLY, VX_MEMORY_TYPE_HOST, 0);
    vxUnmapUserDataObject(object->encodeObject.node_bitstream_object, map_id);

    return status;
}

void resize_encode_app_deinit(struct AppResizeEncodeObject* object)
{
    vxReleaseImage(&object->encodeObject.node_src_image);
    vxReleaseImage(&object->encodeObject.node_dst_image);

    if (object->encodeObject.resize_node != nullptr)
    {
        vxReleaseNode(&object->encodeObject.resize_node);
    }
    if (object->encodeObject.encode_node != nullptr)
    {
        vxReleaseNode(&object->encodeObject.encode_node);
    }

    if (object->graph != nullptr)
    {
        vxReleaseGraph(&object->graph);
    }
}

}  // namespace camera
}  // namespace sensors
}  // namespace holo