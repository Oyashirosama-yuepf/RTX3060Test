
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

#ifdef __cplusplus
}
#endif

#include <string>
#include <vector>

#include "app_common.h"
#include "app_cvt_color_module.h"
#include "app_display_module.h"
#include "app_draw_detections_module.h"
#include "app_img_mosaic_module.h"
#include "app_ldc_module.h"
#include "app_pre_proc_module.h"
#include "app_scaler_module.h"
#include "app_tidl_module.h"
#include "utils.h"

class AppObj
{
public:
    LDCObj     ldcObj;
    CvtObj     cvtObj;
    ScalerObj  scalerObj;
    PreProcObj preProcObj;

    TIDLObj tidlObj;

    DrawDetectionsObj drawDetectionsObj;
    ImgMosaicObj      imgMosaicObj;

    DisplayObj displayObj;

    sTIDL_IOBufDesc_t* ioBufDesc;

    vx_char input_file_path[APP_MAX_FILE_PATH];
    vx_char output_file_path[APP_MAX_FILE_PATH];

    /* OpenVX references */
    vx_context context;
    vx_graph   graph;
    vx_graph   sub_graph;

    vx_int32 en_out_img_write;

    vx_int32 start_frame;
    vx_int32 num_frames;

    vx_uint32 delay_in_msecs;
    vx_uint32 num_iterations;
    vx_uint32 is_interactive;

    tivx_task        task;
    vx_uint32        stop_task;
    vx_uint32        stop_task_done;
    app_perf_point_t total_perf;
    app_perf_point_t fileio_perf;
    app_perf_point_t draw_perf;
    uint32_t         pipeline_depth;
    int32_t          pipeline;
    int32_t          enqueueCnt;
    int32_t          dequeueCnt;
    TIDL_outArgs*    quantscale;
    TIDL_outArgs*    quantscale_arr[APP_TIDL_NODE_NUM];

    std::string yuv_type;
    std::string data_format;
    int         feature_map_size;
    //
    std::vector<FeatureMapRawData> fp_data_vec;

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
                            float* featuremap_data, bool decode_flag = false);
    void add_graph_parameter_by_node_index(vx_graph graph, vx_node node, vx_uint32 node_parameter_index);
    void app_find_object_array_index(vx_object_array object_array[], vx_reference ref, vx_int32 array_size,
                                     vx_int32* array_idx);
    void display_convert_data(vx_tensor output_tensors, uint8_t* img_data);
    vx_size getTensorDataType(vx_int32 tidl_type);
};

#endif
