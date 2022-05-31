#include <holo/log/hololog.h>
#include <holo/sensors/camera/encoder/image_encoder_tda4.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

static const uint32_t MB_ALIGN = 16;

vx_status app_encode_init(App_encode_obj* obj, vx_context context, uint16_t cols, uint16_t rows, uint32_t fps, uint32_t i_period, uint32_t bitrate)
{
    vx_status                   status = VX_SUCCESS;
    tivx_video_encoder_params_t params;
    uint32_t                    max_bitstream_size;

    obj->context         = context;
    EncodeObj* encodeObj = &obj->encodeObj;
    encodeObj->width     = ((cols + MB_ALIGN - 1) / MB_ALIGN) * MB_ALIGN;
    encodeObj->height    = ((rows + MB_ALIGN - 1) / MB_ALIGN) * MB_ALIGN;
    if (vx_true_e == tivxIsTargetEnabled(TIVX_TARGET_VENC1))
    {
        encodeObj->data_ptr =
            (uint8_t*)malloc(encodeObj->width * encodeObj->height + (encodeObj->height * encodeObj->width) / 2);
        if (encodeObj->data_ptr == NULL)
        {
            status = VX_FAILURE;
            return status;
        }
        encodeObj->data_ptr_y  = encodeObj->data_ptr;
        encodeObj->data_ptr_uv = encodeObj->data_ptr + encodeObj->width * encodeObj->height;
        tivx_video_encoder_params_init(&params);
        params.bitstream_format      = TIVX_BITSTREAM_FORMAT_H264;
        params.idr_period = i_period; /* for I-only encode, set to 1 */
        params.i_period = i_period; /* for I-only encode, set to 1 */
        params.bitrate = bitrate;
        params.framerate = fps;
        params.crop_left = 0;
        params.crop_right = encodeObj->width - cols;
        params.crop_top = 0;
        params.crop_bottom = encodeObj->height - rows;
        encodeObj->configuration_obj = vxCreateUserDataObject(obj->context, "tivx_video_encoder_params_t",
                                                              sizeof(tivx_video_encoder_params_t), NULL);
        if (vxGetStatus((vx_reference)encodeObj->configuration_obj) != VX_SUCCESS)
        {
            status = VX_FAILURE;
            return status;
        }
        encodeObj->input_image = vxCreateImage(obj->context, encodeObj->width, encodeObj->height, VX_DF_IMAGE_NV12);
        max_bitstream_size = ((uint32_t)(encodeObj->width / 16) * (uint32_t)(encodeObj->height / 16) * WORST_QP_SIZE) +
                             ((encodeObj->height >> 4) * CODED_BUFFER_INFO_SECTION_SIZE);
        encodeObj->bitstream_obj =
            vxCreateUserDataObject(obj->context, "tivx_video_bitstream_t", sizeof(uint8_t) * max_bitstream_size, NULL);
        if (vxGetStatus((vx_reference)encodeObj->bitstream_obj) != VX_SUCCESS)
        {
            status = VX_FAILURE;
            return status;
        }
        vxCopyUserDataObject(encodeObj->configuration_obj, 0, sizeof(tivx_video_encoder_params_t), &params,
                             VX_WRITE_ONLY, VX_MEMORY_TYPE_HOST);
        obj->graph = vxCreateGraph(obj->context);
        if (vxGetStatus((vx_reference)obj->graph) != VX_SUCCESS)
        {
            status = VX_FAILURE;
            return status;
        }
        encodeObj->node = tivxVideoEncoderNode(obj->graph, encodeObj->configuration_obj, encodeObj->input_image,
                                               encodeObj->bitstream_obj);
        vxSetNodeTarget(encodeObj->node, VX_TARGET_STRING, TIVX_TARGET_VENC1);
        status = vxVerifyGraph(obj->graph);
    }
    return status;
}

vx_status app_encode_run(App_encode_obj* obj)
{
    vx_map_id                  map_id;
    vx_status                  status = VX_SUCCESS;
    vx_rectangle_t             rect_y;
    vx_rectangle_t             rect_uv;
    vx_map_id                  map_id_image_y;
    vx_imagepatch_addressing_t image_addr_y;
    vx_map_id                  map_id_image_uv;
    vx_imagepatch_addressing_t image_addr_uv;
    uint8_t*                   data_ptr_y;
    uint8_t*                   data_ptr_uv;
    EncodeObj*                 encodeObj = &obj->encodeObj;

    if (vx_true_e == tivxIsTargetEnabled(TIVX_TARGET_VENC1))
    {
        rect_y.start_x = 0;
        rect_y.start_y = 0;
        rect_y.end_x   = encodeObj->width;
        rect_y.end_y   = encodeObj->height;

        rect_uv.start_x = 0;
        rect_uv.start_y = 0;
        rect_uv.end_x   = encodeObj->width;
        rect_uv.end_y   = (encodeObj->height * 1) / 2;

        vxMapImagePatch(encodeObj->input_image, &rect_y, 0, &map_id_image_y, &image_addr_y, (void**)&data_ptr_y,
                        VX_WRITE_ONLY, VX_MEMORY_TYPE_HOST, VX_NOGAP_X);
        vxMapImagePatch(encodeObj->input_image, &rect_uv, 1, &map_id_image_uv, &image_addr_uv, (void**)&data_ptr_uv,
                        VX_WRITE_ONLY, VX_MEMORY_TYPE_HOST, VX_NOGAP_X);
        if (encodeObj->data_ptr != NULL)
        {
            (void)memcpy(data_ptr_y, encodeObj->data_ptr_y, encodeObj->width * encodeObj->height);
            (void)memcpy(data_ptr_uv, encodeObj->data_ptr_uv, encodeObj->width * encodeObj->height / 2);
        }
        else
        {
            vxUnmapImagePatch(encodeObj->input_image, map_id_image_y);
            vxUnmapImagePatch(encodeObj->input_image, map_id_image_uv);
            return -1;
        }
        vxUnmapImagePatch(encodeObj->input_image, map_id_image_y);
        vxUnmapImagePatch(encodeObj->input_image, map_id_image_uv);
        vxProcessGraph(obj->graph);
        vxQueryUserDataObject(encodeObj->bitstream_obj, TIVX_USER_DATA_OBJECT_VALID_SIZE, &encodeObj->bitstream_size,
                              sizeof(vx_size));
        status = vxMapUserDataObject(encodeObj->bitstream_obj, 0, encodeObj->bitstream_size, &map_id,
                                     (void**)&encodeObj->bitstream, VX_READ_ONLY, VX_MEMORY_TYPE_HOST, 0);
        vxUnmapUserDataObject(encodeObj->bitstream_obj, map_id);
    }
    return status;
}

void app_encode_deinit(App_encode_obj* obj)
{
    EncodeObj* encodeObj = &obj->encodeObj;
    vxReleaseImage(&encodeObj->input_image);
    if (encodeObj->configuration_obj != NULL)
    {
        vxReleaseUserDataObject(&encodeObj->configuration_obj);
        encodeObj->configuration_obj = NULL;
    }
    if (encodeObj->bitstream_obj != NULL)
    {
        vxReleaseUserDataObject(&encodeObj->bitstream_obj);
        encodeObj->bitstream_obj = NULL;
    }
    if (encodeObj->data_ptr != NULL)
    {
        free(encodeObj->data_ptr);
        encodeObj->data_ptr = NULL;
    }
    if (encodeObj->node != NULL)
    {
        vxReleaseNode(&encodeObj->node);
    }
    if (obj->graph != NULL)
    {
        vxReleaseGraph(&obj->graph);
    }
}
