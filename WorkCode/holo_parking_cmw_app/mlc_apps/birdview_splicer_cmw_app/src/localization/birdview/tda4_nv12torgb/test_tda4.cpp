
/*
 *
 * Copyright (c) 2020 Texas Instruments Incorporated
 *
 * All rights reserved not granted herein.
 *
 * Limited License.
 *
 * Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 * license under copyrights and patents it now or hereafter owns or controls to make,
 * have made, use, import, offer to sell and sell ("Utilize") this software subject to the
 * terms herein.  With respect to the foregoing patent license, such license is granted
 * solely to the extent that any such patent is necessary to Utilize the software alone.
 * The patent license shall not apply to any combinations which include this software,
 * other than combinations with devices manufactured by or for TI ("TI Devices").
 * No hardware patent is licensed hereunder.
 *
 * Redistributions must preserve existing copyright notices and reproduce this license
 * (including the above copyright notice and the disclaimer and (if applicable) source
 * code license limitations below) in the documentation and/or other materials provided
 * with the distribution
 *
 * Redistribution and use in binary form, without modification, are permitted provided
 * that the following conditions are met:
 *
 * *       No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 *
 * *       any redistribution and use are licensed by TI for use only with TI Devices.
 *
 * *       Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 *
 * *       any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 *
 * *       any redistribution and use of any object code compiled from the source code
 * and any resulting derivative works, are licensed by TI for use only with TI Devices.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of its suppliers
 *
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * DISCLAIMER.
 *
 * THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

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

#include <localization/vision/birdview/tda4_nv12torgb/app_common.h>
#include <localization/vision/birdview/tda4_nv12torgb/app_pre_proc_module.h>
#include <localization/vision/birdview/tda4_nv12torgb/app_scaler_module.h>

#include <localization/vision/birdview/tda4_nv12torgb/tadl.h>
/* #define WRITE_INTERMEDIATE_OUTPUTS */
#include <time.h>

#define x86_64
#ifndef x86_64
#define APP_ENABLE_PIPELINE_FLOW
#endif

#define APP_PIPELINE_DEPTH (6)
#define APP_FOUR_CAMERA_TOGETHER
// self example
#include <iostream>
#ifdef USE_OPECV_CPP
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#endif
#include <localization/vision/birdview/tda4_nv12torgb/TadlInference.h>
#include <fstream>
class FeatureMap
{
public:
    float* data;
    int    channel_;
    int    height_;
    int    width_;
    int    data_len_;
    FeatureMap();
    FeatureMap(int channel, int height, int width);
    virtual ~FeatureMap();
    void  SetDataPtr(int channel, int height, int width);
    float GetDataElement(int index_c, int index_h, int index_w);
    void  StoreFeauremapData(std::string file_tmp);
};

void StoreFeaturemapDataFunc(float* data, int data_len, const char* file_tmp)
{
    std::fstream fs;
    fs.open(file_tmp);
    for (int i = 0; i < data_len; i++)
    {
        fs << data[i] << std::endl;
    }
    fs.close();
}

void FeatureMap::StoreFeauremapData(std::string file_tmp)
{
    auto file1    = file_tmp.c_str();
    int  data_len = channel_ * height_ * width_;
    StoreFeaturemapDataFunc(data, data_len, file1);
}

float FeatureMap::GetDataElement(int index_c, int index_h, int index_w)
{
    int index = index_c * height_ * width_ + index_h * width_ + index_w;
    return data[index];
}
FeatureMap::FeatureMap()
{
    data = nullptr;
}
void FeatureMap::SetDataPtr(int channel, int height, int width)
{
    channel_      = channel;
    height_       = height;
    width_        = width;
    int data_size = channel * height * width;
    data_len_     = data_size;
    data          = new float[data_size];
}

FeatureMap::FeatureMap(int channel, int height, int width)
{
    channel_      = channel;
    height_       = height;
    width_        = width;
    int data_size = channel * height * width;
    data          = new float[data_size];
}

FeatureMap::~FeatureMap()
{
    if (data != nullptr)
    {
        delete[] data;
    }
}

/*
 * Utility API used to add a graph parameter from a node, node parameter index
 */
void AppObj::add_graph_parameter_by_node_index(vx_graph graph, vx_node node, vx_uint32 node_parameter_index)
{
    vx_parameter parameter = vxGetParameterByIndex(node, node_parameter_index);

    vxAddParameterToGraph(graph, parameter);
    vxReleaseParameter(&parameter);
}

int TidlLibrary::app_preproc_init(AppObj* obj)
{
    int                  status = VX_SUCCESS;
    app_grpx_init_prms_t grpx_prms;

    /* Create OpenVx Context */
    obj->context = vxCreateContext();
    APP_ASSERT_VALID_REF(obj->context);
    tivxHwaLoadKernels(obj->context);
    tivxImgProcLoadKernels(obj->context);
    // tivxTIDLLoadKernels(obj->context);

    std::cout << "test end" << std::endl;
    /* Initialize modules */
    app_init_scaler(obj->context, &obj->scalerObj, "scaler_obj", APP_BUFFER_Q_DEPTH);
    APP_PRINTF("Scaler Init Done! \n");
    std::cout << "test" << std::endl;
    /* Update ioBufDesc in pre proc object */
    app_update_pre_proc_data_convert(obj->context, &obj->preProcObj);
    APP_PRINTF("Pre Proc Update Done! \n");
    std::cout << "test" << std::endl;
    app_init_pre_proc(obj->context, &obj->preProcObj, "pre_proc_obj");
    APP_PRINTF("Pre Proc Init Done! \n");
    std::cout << "test" << std::endl;
#ifndef x86_64
    if (obj->displayObj.display_option == 1)
    {
        appGrpxInitParamsInit(&grpx_prms, obj->context);
        grpx_prms.draw_callback = app_draw_graphics;
        appGrpxInit(&grpx_prms);
    }
#endif

    return status;
}

void TidlLibrary::app_default_param_set(AppObj* obj)
{
    set_pre_proc_defaults(&obj->preProcObj);

    app_pipeline_params_defaults(obj);

    obj->delay_in_msecs = 0;
    obj->num_iterations = 1;
    obj->is_interactive = 0;
}
void TidlLibrary::app_delete_graph(AppObj* obj)
{
    app_delete_scaler(&obj->scalerObj);

    app_delete_pre_proc(&obj->preProcObj);

    vxReleaseGraph(&obj->graph);
}

void TidlLibrary::app_deinit(AppObj* obj)
{
    app_deinit_scaler(&obj->scalerObj, APP_BUFFER_Q_DEPTH);

    app_deinit_pre_proc(&obj->preProcObj);

    // app_deinit_draw_detections(&obj->drawDetectionsObj);

    // app_deinit_img_mosaic(&obj->imgMosaicObj, APP_BUFFER_Q_DEPTH);

    // app_deinit_display(&obj->displayObj);

#ifndef x86_64
    if (obj->displayObj.display_option == 1)
    {
        appGrpxDeInit();
    }
#endif

    tivxTIDLUnLoadKernels(obj->context);
    tivxImgProcUnLoadKernels(obj->context);
    tivxHwaUnLoadKernels(obj->context);

    vxReleaseContext(&obj->context);
}

vx_status TidlLibrary::app_create_pre_graph(AppObj* obj)
{
    vx_status                         status = VX_SUCCESS;
    vx_graph_parameter_queue_params_t graph_parameters_queue_params_list[4];
    vx_int32                          graph_parameter_index;
    obj->graph = vxCreateGraph(obj->context);
    status     = vxGetStatus((vx_reference)obj->graph);
    vxSetReferenceName((vx_reference)obj->graph, "OpenVxGraph");

    if (obj->use_resize)
    {
        app_create_graph_scaler(obj->context, obj->graph, &obj->scalerObj);
        app_create_graph_pre_proc(obj->graph, &obj->preProcObj, obj->scalerObj.output1.arr[0]);

        /* Scalar Node - input is in Index 0 */
        graph_parameter_index = 0;
        obj->add_graph_parameter_by_node_index(obj->graph, obj->scalerObj.node, 0);
        obj->scalerObj.graph_parameter_index                                            = graph_parameter_index;
        graph_parameters_queue_params_list[graph_parameter_index].graph_parameter_index = graph_parameter_index;
        graph_parameters_queue_params_list[graph_parameter_index].refs_list_size        = APP_BUFFER_Q_DEPTH;
        graph_parameters_queue_params_list[graph_parameter_index].refs_list =
            (vx_reference*)&obj->scalerObj.input_images[0];
        graph_parameter_index++;

        obj->add_graph_parameter_by_node_index(obj->graph, obj->preProcObj.node, 2);  //?
        obj->preProcObj.graph_parameter_index                                           = graph_parameter_index;
        graph_parameters_queue_params_list[graph_parameter_index].graph_parameter_index = graph_parameter_index;
        graph_parameters_queue_params_list[graph_parameter_index].refs_list_size        = 1;
        graph_parameters_queue_params_list[graph_parameter_index].refs_list =
            (vx_reference*)&obj->preProcObj.output_tensor_arr[0];
        graph_parameter_index++;
        vxSetGraphScheduleConfig(obj->graph, VX_GRAPH_SCHEDULE_MODE_QUEUE_AUTO, graph_parameter_index,
                                 graph_parameters_queue_params_list);
        tivxSetGraphPipelineDepth(obj->graph, APP_PIPELINE_DEPTH);

        tivxSetNodeParameterNumBufByIndex(obj->scalerObj.node, 1, APP_BUFFER_Q_DEPTH);
        tivxSetNodeParameterNumBufByIndex(obj->scalerObj.node, 2, APP_BUFFER_Q_DEPTH);
    }
    else
    {
        app_create_graph_pre_convert(obj->graph, &obj->preProcObj, obj->scalerObj.input.arr[0]);

        /* Scalar Node - input is in Index 0 */
        graph_parameter_index = 0;
        obj->add_graph_parameter_by_node_index(obj->graph, obj->preProcObj.node, 1);
        obj->scalerObj.graph_parameter_index                                            = graph_parameter_index;
        graph_parameters_queue_params_list[graph_parameter_index].graph_parameter_index = graph_parameter_index;
        graph_parameters_queue_params_list[graph_parameter_index].refs_list_size        = APP_BUFFER_Q_DEPTH;
        graph_parameters_queue_params_list[graph_parameter_index].refs_list =
            (vx_reference*)&obj->scalerObj.input_images[0];
        graph_parameter_index++;

        obj->add_graph_parameter_by_node_index(obj->graph, obj->preProcObj.node, 2);  //?
        obj->preProcObj.graph_parameter_index                                           = graph_parameter_index;
        graph_parameters_queue_params_list[graph_parameter_index].graph_parameter_index = graph_parameter_index;
        graph_parameters_queue_params_list[graph_parameter_index].refs_list_size        = 1;
        graph_parameters_queue_params_list[graph_parameter_index].refs_list =
            (vx_reference*)&obj->preProcObj.output_tensor_arr[0];
        graph_parameter_index++;
        vxSetGraphScheduleConfig(obj->graph, VX_GRAPH_SCHEDULE_MODE_QUEUE_AUTO, graph_parameter_index,
                                 graph_parameters_queue_params_list);
        tivxSetGraphPipelineDepth(obj->graph, APP_PIPELINE_DEPTH);

        std::cout << "config end" << std::endl;
    }
    return status;
}

vx_status TidlLibrary::app_verify_graph(AppObj* obj)
{
    vx_status status = VX_SUCCESS;

    ScalerObj*   scalerObj;
    vx_reference refs[5] = {0};

    std::cout << "test graph" << std::endl;
    status = vxVerifyGraph(obj->graph);
    std::cout << "test end" << std::endl;

    APP_PRINTF("App Verify Graph Done!\n");

#if 1
    if (VX_SUCCESS == status)
    {
        status = tivxExportGraphToDot(obj->graph, ".", "vx_app_tidl_od");
    }
#endif

    if (obj->use_resize)
    {
        scalerObj = &obj->scalerObj;

        refs[0] = (vx_reference)scalerObj->coeff_obj;

        status = tivxNodeSendCommand(scalerObj->node, 0u, TIVX_VPAC_MSC_CMD_SET_COEFF, refs, 1u);
    }

    APP_PRINTF("App Send MSC Command Done!\n");

    // crop
    std::cout << "use crop" << std::endl;
    if (obj->scalerObj.crop_use)
    {
        vx_user_data_object         crop_obj;
        tivx_vpac_msc_crop_params_t crop;

        crop.crop_start_x = obj->scalerObj.crop_start_x;
        crop.crop_start_y = obj->scalerObj.crop_start_y;
        crop.crop_width   = obj->scalerObj.crop_width;
        crop.crop_height  = obj->scalerObj.crop_height;
        std::cout << crop.crop_start_x << " " << crop.crop_start_y << " " << crop.crop_width << " " << crop.crop_height
                  << std::endl;

        crop_obj = vxCreateUserDataObject(obj->context, "tivx_vpac_msc_crop_params_t",
                                          sizeof(tivx_vpac_msc_crop_params_t), NULL);
        vxCopyUserDataObject(crop_obj, 0, sizeof(tivx_vpac_msc_crop_params_t), &crop, VX_WRITE_ONLY,
                             VX_MEMORY_TYPE_HOST);
        refs[0] = (vx_reference)crop_obj;

        status = status && tivxNodeSendCommand(scalerObj->node, 0u, TIVX_VPAC_MSC_CMD_SET_CROP_PARAMS, refs, 5u);

        vxReleaseUserDataObject(&crop_obj);
    }

    if (VX_SUCCESS != status)
    {
        printf("MSC: Node send command failed!\n");
    }

    /* wait a while for prints to flush */
    tivxTaskWaitMsecs(400);

    return status;
}

vx_status TidlLibrary::app_verify_tidl_graph(AppObj* obj)
{
    vx_status status = VX_SUCCESS;

    ScalerObj*   scalerObj;
    vx_reference refs[1];

    status = vxVerifyGraph(obj->graph);

    APP_PRINTF("App Verify Graph Done!\n");

#if 1
    if (VX_SUCCESS == status)
    {
        status = tivxExportGraphToDot(obj->graph, ".", "vx_app_tidl_od");
    }
#endif

    /* wait a while for prints to flush */
    tivxTaskWaitMsecs(100);

    return status;
}

vx_size AppObj::getTensorDataType(vx_int32 tidl_type)
{
    vx_size openvx_type = VX_TYPE_INVALID;

    if (tidl_type == TIDL_UnsignedChar)
    {
        openvx_type = VX_TYPE_UINT8;
    }
    else if (tidl_type == TIDL_SignedChar)
    {
        openvx_type = VX_TYPE_INT8;
    }
    else if (tidl_type == TIDL_UnsignedShort)
    {
        openvx_type = VX_TYPE_UINT16;
    }
    else if (tidl_type == TIDL_SignedShort)
    {
        openvx_type = VX_TYPE_INT16;
    }
    else if (tidl_type == TIDL_UnsignedWord)
    {
        openvx_type = VX_TYPE_UINT32;
    }
    else if (tidl_type == TIDL_SignedWord)
    {
        openvx_type = VX_TYPE_INT32;
    }
    else if (tidl_type == TIDL_SinglePrecFloat)
    {
        openvx_type = VX_TYPE_FLOAT32;
    }

    return openvx_type;
}

class GetTimeDiffApp
{
public:
    struct timeval start, end;
    void           StartTiming()
    {
        gettimeofday(&start, NULL);
    }
    float GetTimeDiff()  // ms
    {
        gettimeofday(&end, NULL);
        return (end.tv_sec - start.tv_sec) * 1e3 + (end.tv_usec - start.tv_usec) / 1e3;
    }
};

void AppObj::display_convert_data(vx_tensor output_tensors, uint8_t* img_data)
{
    vx_status status = VX_SUCCESS;

    vx_tensor output = output_tensors;
    vx_size   numCh;

    vx_size   num_dims;
    void*     data_ptr;
    vx_map_id map_id;
    vx_size   start[APP_MAX_TENSOR_DIMS];
    vx_size   tensor_strides[APP_MAX_TENSOR_DIMS];
    vx_size   tensor_sizes[APP_MAX_TENSOR_DIMS];

    std::cout << "---------------get rgb img----------------" << std::endl;
    vxQueryTensor(output, VX_TENSOR_NUMBER_OF_DIMS, &num_dims, sizeof(vx_size));
    if (num_dims != 3)
    {
        printf("Number of dims are != 3! exiting.. \n");
    }
    vxQueryTensor(output, VX_TENSOR_DIMS, tensor_sizes, 3 * sizeof(vx_size));
    for (int i = 0; i < 3; i++)
        std::cout << tensor_sizes[i] << std::endl;

    start[0] = start[1] = start[2] = 0;
    tensor_strides[0]              = 1;
    tensor_strides[1]              = tensor_strides[0];
    tensor_strides[2]              = tensor_strides[1] * tensor_strides[1];
    status = tivxMapTensorPatch(output, num_dims, start, tensor_sizes, &map_id, tensor_strides, &data_ptr, VX_READ_ONLY,
                                VX_MEMORY_TYPE_HOST);

    if (VX_SUCCESS == status)
    {
        std::cout << "get img data" << std::endl;
        vx_enum data_type;
        vxQueryTensor(output, (vx_enum)VX_TENSOR_DATA_TYPE, &data_type, sizeof(data_type));
        if (data_type == VX_TYPE_UINT8)
        {
            if (!use_channel_convert)
            {
                std::cout << "int8" << std::endl;
                int data_len = tensor_sizes[0] * tensor_sizes[1] * tensor_sizes[2];
                std::cout << "data len " << data_len << std::endl;
                int8_t* data_ptr_tmp = (int8_t*)data_ptr;
                memcpy(img_data, data_ptr, data_len);
                std::cout << use_channel_convert << std::endl;
            }
            else
            {
                /*
                int            data_len     = tensor_sizes[0] * tensor_sizes[1] * tensor_sizes[2];
                uint8_t*       data_ptr_tmp = (uint8_t*)data_ptr;
                int            width        = preProcObj.width_;
                int            height       = preProcObj.height_;
                GetTimeDiffApp t1;
                t1.StartTiming();
                channel_convert->set_src_data(data_ptr_tmp);
                vxProcessGraph(channel_convert->graph);
                channel_convert->get_dst_data(img_data);
                std::cout << (int)img_data[0] << " " << (int)img_data[1] << " " << (int)img_data[2] << std::endl;
                std::cout << "kernel convert channel time use " << t1.GetTimeDiff() << std::endl;
                */
            }
        }
        else if (data_type == VX_TYPE_UINT16)
        {
            int      data_len     = tensor_sizes[0] * tensor_sizes[1] * tensor_sizes[2];
            int16_t* data_ptr_tmp = (int16_t*)data_ptr;
            //  while(data_len--)
            //  {
            //     *img_data++ = *data_ptr_tmp++;
            //  }
            //  img_data = img_data - data_len;
            memcpy(img_data, data_ptr, data_len);
        }

        tivxUnmapTensorPatch(output, map_id);
    }
    vxReleaseTensor(&output);
}

vx_status TidlLibrary::app_read_image(AppObj* obj, vx_int32 frame_id)
{
    vx_char    input_file_name[APP_MAX_FILE_PATH];
    ScalerObj* scalerObj = &obj->scalerObj;
    snprintf(input_file_name, APP_MAX_FILE_PATH, "%s/%010d.yuv", obj->input_file_path, frame_id);
    readScalerInput(input_file_name, scalerObj->input.arr[obj->enqueueCnt], NUM_CH);
}

void TidlLibrary::write_pre_data(AppObj* obj, char* input_file_name)
{
    ScalerObj*  scalerObj  = &obj->scalerObj;
    PreProcObj* preProcObj = &obj->preProcObj;
    /* Enqueue outpus */
    vxGraphParameterEnqueueReadyRef(obj->graph, preProcObj->graph_parameter_index,
                                    (vx_reference*)&preProcObj->output_tensor_arr[obj->enqueueCnt], 1);

    /* Read input */
    readScalerInput(input_file_name, scalerObj->input.arr[obj->enqueueCnt], NUM_CH);
    //////////image arr -> dsp(gpu)////////////////
    /* Enqueue input - start execution */
    vxGraphParameterEnqueueReadyRef(obj->graph, scalerObj->graph_parameter_index,
                                    (vx_reference*)&obj->scalerObj.input_images[obj->enqueueCnt], 1);

    // obj->enqueueCnt++;
    // obj->enqueueCnt   = (obj->enqueueCnt  >= APP_BUFFER_Q_DEPTH)? 0 : obj->enqueueCnt;
}

void TidlLibrary::read_convert_data(AppObj* obj, uint8_t* img_data)
{
    vx_int32        frame_id;
    ScalerObj*      scalerObj  = &obj->scalerObj;
    PreProcObj*     preProcObj = &obj->preProcObj;
    vx_object_array output_tensor_arr[1];
    uint32_t        num_refs;
    vxGraphParameterDequeueDoneRef(obj->graph, preProcObj->graph_parameter_index, (vx_reference*)&output_tensor_arr[0],
                                   1, &num_refs);

    vx_tensor output;
    output = (vx_tensor)vxGetObjectArrayItem((vx_object_array)output_tensor_arr[0], 0);

    // char* output_file_name = (char*)malloc(100 * sizeof(char));
    // snprintf(output_file_name, APP_MAX_FILE_PATH, "%s/%010d.txt", obj->output_file_path, frame_id -
    // APP_BUFFER_Q_DEPTH + 1 + obj->dequeueCnt);  //?

    // printf("%s\n", output_file_name);
    uint64_t cur_time = tivxPlatformGetTimeInUsecs();
    obj->display_convert_data(output, img_data);
    cur_time = tivxPlatformGetTimeInUsecs() - cur_time;
    printf("pre time: %d ms\n", cur_time / 1000);
    obj->dequeueCnt++;
}

void TidlLibrary::set_pre_proc_defaults(PreProcObj* preProcObj)
{
    vx_int32 i;
    for (i = 0; i < 4; i++)
    {
        preProcObj->params.pad_pixel[i] = 0;
    }
    for (i = 0; i < 3; i++)
    {
        preProcObj->params.scale_val[i]  = 1.0;
        preProcObj->params.mean_pixel[i] = 0.0;
    }
    preProcObj->params.ip_rgb_or_yuv   = 1; /* YUV-NV12 default */
    preProcObj->params.color_conv_flag = TIADALG_COLOR_CONV_YUV420_BGR;
}

void TidlLibrary::app_pipeline_params_defaults(AppObj* obj)
{
    obj->pipeline   = -APP_BUFFER_Q_DEPTH;
    obj->enqueueCnt = 0;
    obj->dequeueCnt = 0;
}

void AppObj::app_find_object_array_index(vx_object_array object_array[], vx_reference ref, vx_int32 array_size,
                                         vx_int32* array_idx)
{
    vx_int32 i;

    *array_idx = -1;
    for (i = 0; i < array_size; i++)
    {
        vx_image img_ref = (vx_image)vxGetObjectArrayItem((vx_object_array)object_array[i], 0);
        if (ref == (vx_reference)img_ref)
        {
            *array_idx = i;
            vxReleaseImage(&img_ref);
            break;
        }
        vxReleaseImage(&img_ref);
    }
}
