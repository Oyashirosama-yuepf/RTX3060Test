
#include <holo/sensors/camera/decoder/image_decoder_tda4.h>
#include <holo/log/hololog.h>

vx_status app_init_resource(App_decode_Obj* obj, uint16_t cols, uint16_t rows)
{
    vx_status status = VX_SUCCESS;
    obj->context     = vxCreateContext();
    tivxHwaLoadKernels(obj->context);
    obj->graph                     = vxCreateGraph(obj->context);
    obj->decodeObj.width           = cols;
    obj->decodeObj.height          = rows;
    obj->decodeObj.info.ptr_output = (uint8_t*)malloc(4 * 1024 * 1024);
    obj->decodeObj.info.ptr_y      = obj->decodeObj.info.ptr_output;
    obj->decodeObj.info.ptr_uv     = obj->decodeObj.info.ptr_output + (obj->decodeObj.width * obj->decodeObj.height);
    obj->decodeObj.info.streambuf  = (uint8_t*)malloc(4 * 1024 * 1024);
    tivx_video_decoder_params_init(&obj->decodeObj.params);
    obj->decodeObj.configuration_obj =
        vxCreateUserDataObject(obj->context, "tivx_video_decoder_params_t", sizeof(tivx_video_decoder_params_t), NULL);
    if (vxGetStatus((vx_reference)obj->decodeObj.configuration_obj) != VX_SUCCESS)
    {
        printf("configuration create failed!\n");
        return VX_FAILURE;
    }
    obj->decodeObj.bitstream_obj = vxCreateUserDataObject(
        obj->context, "video_bitstream", sizeof(uint8_t) * obj->decodeObj.width * obj->decodeObj.height * 3 / 2, NULL);
    obj->decodeObj.params.bitstream_format = TIVX_BITSTREAM_FORMAT_H264;
    vxCopyUserDataObject(obj->decodeObj.configuration_obj, 0, sizeof(tivx_video_decoder_params_t),
                         &obj->decodeObj.params, VX_WRITE_ONLY, VX_MEMORY_TYPE_HOST);
    obj->decodeObj.output_image =
        vxCreateImage(obj->context, obj->decodeObj.width, obj->decodeObj.height, VX_DF_IMAGE_NV12);
    obj->decodeObj.node = tivxVideoDecoderNode(obj->graph, obj->decodeObj.configuration_obj,
                                               obj->decodeObj.bitstream_obj, obj->decodeObj.output_image);
    vxSetNodeTarget(obj->decodeObj.node, VX_TARGET_STRING, TIVX_TARGET_VDEC1);
    status = vxVerifyGraph(obj->graph);
    tivxTaskWaitMsecs(200);
    return status;
}

vx_status app_run_decode(App_decode_Obj* obj)
{
    vx_status                  status = VX_SUCCESS;
    vx_uint8*                  bitstream;
    vx_map_id                  map_id;
    vx_rectangle_t             rect_y;
    vx_rectangle_t             rect_uv;
    vx_map_id                  map_id_image_y;
    vx_imagepatch_addressing_t image_addr_y;
    vx_map_id                  map_id_image_uv;
    vx_imagepatch_addressing_t image_addr_uv;

    vxMapUserDataObject(obj->decodeObj.bitstream_obj, 0, obj->decodeObj.info.bitstream_sizes, &map_id,
                        (void**)&bitstream, VX_WRITE_ONLY, VX_MEMORY_TYPE_HOST, 0);
    memcpy(bitstream, obj->decodeObj.info.streambuf, obj->decodeObj.info.bitstream_sizes);
    vxUnmapUserDataObject(obj->decodeObj.bitstream_obj, map_id);
    tivxSetUserDataObjectAttribute(obj->decodeObj.bitstream_obj, TIVX_USER_DATA_OBJECT_VALID_SIZE,
                                   (void*)&(obj->decodeObj.info.bitstream_sizes), sizeof(vx_size));
    vxProcessGraph(obj->graph);

    rect_y.start_x = 0;
    rect_y.start_y = 0;
    rect_y.end_x   = obj->decodeObj.width;
    rect_y.end_y   = obj->decodeObj.height;

    rect_uv.start_x = 0;
    rect_uv.start_y = 0;
    rect_uv.end_x   = obj->decodeObj.width;
    rect_uv.end_y   = obj->decodeObj.height / 2;

    vxMapImagePatch(obj->decodeObj.output_image, &rect_y, 0, &map_id_image_y, &image_addr_y,
                    (void**)&obj->decodeObj.info.ptr_y, VX_READ_ONLY, VX_MEMORY_TYPE_HOST, VX_NOGAP_X);

    vxMapImagePatch(obj->decodeObj.output_image, &rect_uv, 1, &map_id_image_uv, &image_addr_uv,
                    (void**)&obj->decodeObj.info.ptr_uv, VX_READ_ONLY, VX_MEMORY_TYPE_HOST, VX_NOGAP_X);
    vxUnmapImagePatch(obj->decodeObj.output_image, map_id_image_y);
    vxUnmapImagePatch(obj->decodeObj.output_image, map_id_image_uv);
    return status;
}

vx_status app_decode_deinit(App_decode_Obj* obj)
{
    vx_status status = VX_SUCCESS;

    vxReleaseNode(&obj->decodeObj.node);
    vxReleaseGraph(&obj->graph);

    vxReleaseImage(&obj->decodeObj.output_image);
    vxReleaseUserDataObject(&obj->decodeObj.bitstream_obj);
    vxReleaseUserDataObject(&obj->decodeObj.configuration_obj);
    if (obj->decodeObj.info.ptr_output)
    {
        free(obj->decodeObj.info.ptr_output);
        obj->decodeObj.info.ptr_output = NULL;
    }
    if (obj->decodeObj.info.streambuf)
    {
        free(obj->decodeObj.info.streambuf);
        obj->decodeObj.info.streambuf = NULL;
    }
    tivxHwaUnLoadKernels(obj->context);

    return status;
}
