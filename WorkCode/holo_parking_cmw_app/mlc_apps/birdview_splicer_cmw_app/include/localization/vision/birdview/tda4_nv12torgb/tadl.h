
#ifndef _TADL_H
#define _TADL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <VX/vx_khr_pipelining.h>
#include <utils/console_io/include/app_get.h>
#include <utils/draw2d/include/draw2d.h>
#include <utils/grpx/include/app_grpx.h>
#include <utils/perf_stats/include/app_perf_stats.h>

#ifdef APP_TIDL_TRACE_DUMP
#include <tivx_utils_tidl_trace.h>
#endif

#include "app_common.h"
#include "app_pre_proc_module.h"
#include "app_scaler_module.h"

#ifdef __cplusplus
}
#endif

#include <vector>

class combine_channel_test
{
public:
    combine_channel_test(int width, int height)
    {
        width_     = width;
        height_    = height;
        context    = vxCreateContext();
        graph      = vxCreateGraph(context);
        src1_image = vxCreateImage(context, width, height, VX_DF_IMAGE_U8);
        src2_image = vxCreateImage(context, width, height, VX_DF_IMAGE_U8);
        src3_image = vxCreateImage(context, width, height, VX_DF_IMAGE_U8);
        dst_image  = vxCreateImage(context, width, height, VX_DF_IMAGE_RGB);
        node       = vxChannelCombineNode(graph, src1_image, src2_image, src3_image, NULL, dst_image);
        vxVerifyGraph(graph);
    }
    void set_src_data(uint8_t* data, int data_len, int channel = 0)
    {
        vx_status                  status;
        vx_rectangle_t             rect;
        vx_imagepatch_addressing_t image_addr;
        vx_map_id                  map_id;
        void*                      data_ptr;
        vx_uint32                  img_width;
        vx_uint32                  img_height;
        vx_image                   in_img;
        vx_uint32                  num_bytes;

        if (channel == 0)
            in_img = src1_image;
        else if (channel == 1)
            in_img = src2_image;
        else
            in_img = src3_image;

        vxQueryImage(in_img, VX_IMAGE_WIDTH, &img_width, sizeof(vx_uint32));
        vxQueryImage(in_img, VX_IMAGE_HEIGHT, &img_height, sizeof(vx_uint32));

        rect.start_x = 0;
        rect.start_y = 0;
        rect.end_x   = img_width;
        rect.end_y   = img_height;
        status = vxMapImagePatch(in_img, &rect, 0, &map_id, &image_addr, &data_ptr, VX_WRITE_ONLY, VX_MEMORY_TYPE_HOST,
                                 VX_NOGAP_X);
        memcpy(data_ptr, data, data_len);
        vxUnmapImagePatch(in_img, map_id);
    }

    void set_src_data(uint8_t* data)
    {
        int channel_size = width_ * height_;
        set_src_data(data, channel_size, 0);
        set_src_data(data + channel_size, channel_size, 1);
        set_src_data(data + 2 * channel_size, channel_size, 2);
    }

    void get_dst_data(uint8_t* data)
    {
        vx_status                  status;
        vx_rectangle_t             rect;
        vx_imagepatch_addressing_t image_addr;
        vx_map_id                  map_id;
        void*                      data_ptr;
        vx_uint32                  img_width;
        vx_uint32                  img_height;
        vx_image                   dst_img;
        vx_uint32                  num_bytes;
        dst_img = dst_image;

        vxQueryImage(dst_img, VX_IMAGE_WIDTH, &img_width, sizeof(vx_uint32));
        vxQueryImage(dst_img, VX_IMAGE_HEIGHT, &img_height, sizeof(vx_uint32));

        rect.start_x = 0;
        rect.start_y = 0;
        rect.end_x   = img_width;
        rect.end_y   = img_height;
        status = vxMapImagePatch(dst_img, &rect, 0, &map_id, &image_addr, &data_ptr, VX_READ_ONLY, VX_MEMORY_TYPE_HOST,
                                 VX_NOGAP_X);
        memcpy(data, (uint8_t*)data_ptr, img_height * img_width * 3);
        vxUnmapImagePatch(dst_img, map_id);
    }

public:
    vx_context context;
    vx_graph   graph;
    vx_node    node;
    vx_image   src1_image;
    vx_image   src2_image;
    vx_image   src3_image;
    vx_image   dst_image;
    int        width_;
    int        height_;
};

class AppObj
{
public:
    ScalerObj  scalerObj;
    PreProcObj preProcObj;

    vx_char input_file_path[APP_MAX_FILE_PATH];
    vx_char output_file_path[APP_MAX_FILE_PATH];

    /* OpenVX references */
    vx_context context;
    vx_graph   graph;

    vx_int32 en_out_img_write;

    vx_int32 start_frame;
    vx_int32 num_frames;

    vx_uint32 delay_in_msecs;
    vx_uint32 num_iterations;
    vx_uint32 is_interactive;

    tivx_task task;
    vx_uint32 stop_task;
    vx_uint32 stop_task_done;

    app_perf_point_t total_perf;
    app_perf_point_t fileio_perf;
    app_perf_point_t draw_perf;

    uint32_t pipeline_depth;
    int32_t  pipeline;

    int32_t enqueueCnt;
    int32_t dequeueCnt;

    TIDL_outArgs*         quantscale;
    bool                  use_resize = true;
    bool                  use_channel_convert;
    uint8_t*              rgb_chw_data;
    combine_channel_test* channel_convert;

public:
    void get_data_map_8(vx_int8* pOut, int outPadT, int outPadB, int outPadL, int outPadR, int outHeight, int outWidth,
                        int outNumChannels, vx_size output_sizes[APP_MAX_TENSOR_DIMS], int id, float* data,
                        TIDL_outArgs* quantscale);
    void get_data_map_8(vx_uint8* pOut, int outPadT, int outPadB, int outPadL, int outPadR, int outHeight, int outWidth,
                        int outNumChannels, vx_size output_sizes[APP_MAX_TENSOR_DIMS], int id, float* data,
                        TIDL_outArgs* quantscale);
    void get_data_map_16(vx_int16* pOut, int outPadT, int outPadB, int outPadL, int outPadR, int outHeight,
                         int outWidth, int outNumChannels, vx_size output_sizes[APP_MAX_TENSOR_DIMS], int id,
                         float* data, TIDL_outArgs* quantscale);
    void get_data_map_16(vx_uint16* pOut, int outPadT, int outPadB, int outPadL, int outPadR, int outHeight,
                         int outWidth, int outNumChannels, vx_size output_sizes[APP_MAX_TENSOR_DIMS], int id,
                         float* data, TIDL_outArgs* quantscale);
    int  get_inference_data(sTIDL_IOBufDesc_t* ioBufDesc, vx_tensor* output_tensors, TIDL_outArgs* quantscale,
                            float* featuremap_data);
    void add_graph_parameter_by_node_index(vx_graph graph, vx_node node, vx_uint32 node_parameter_index);
    void app_find_object_array_index(vx_object_array object_array[], vx_reference ref, vx_int32 array_size,
                                     vx_int32* array_idx);
    void display_convert_data(vx_tensor output_tensors, uint8_t* img_data);
    vx_size getTensorDataType(vx_int32 tidl_type);
};

#endif
