/*
 *
 * Copyright (c) 2017 Texas Instruments Incorporated
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

#include <localization/vision/birdview/tda4_nv12torgb/app_pre_proc_module.h>

static void    createOutputTensors(vx_context context, vx_user_data_object config, vx_tensor output_tensors[]);
static vx_enum get_vx_tensor_datatype(int32_t tidl_datatype);

vx_status app_init_pre_proc(vx_context context, PreProcObj* preProcObj, char* objName)
{
    vx_status status = VX_SUCCESS;

    vx_enum config_type = VX_TYPE_INVALID;
    config_type         = vxRegisterUserStruct(context, sizeof(tivxImgPreProcParams));
    APP_ASSERT(config_type >= VX_TYPE_USER_STRUCT_START && config_type <= VX_TYPE_USER_STRUCT_END);

    preProcObj->config = vxCreateArray(context, config_type, 1);
    APP_ASSERT_VALID_REF(preProcObj->config);

    vx_char ref_name[APP_MAX_FILE_PATH];
    vxAddArrayItems(preProcObj->config, 1, &preProcObj->params, sizeof(tivxImgPreProcParams));
    snprintf(ref_name, APP_MAX_FILE_PATH, "%s_config", objName);
    vxSetReferenceName((vx_reference)preProcObj->config, ref_name);

    return status;
}

vx_status app_update_pre_proc_data_convert(vx_context context, PreProcObj* preProcObj)
{
    vx_status status = VX_SUCCESS;

    vx_map_id map_id_config;
    vx_int32  i;

    preProcObj->params.pad_pixel[0] = 0;  // Left
    preProcObj->params.pad_pixel[1] = 0;  // Top
    preProcObj->params.pad_pixel[2] = 0;  // Right
    preProcObj->params.pad_pixel[3] = 0;  // Bottom

    int data_format = preProcObj->data_format_;
    if (data_format == 1) /*RGB*/
    {
        preProcObj->params.color_conv_flag = TIADALG_COLOR_CONV_YUV420_RGB;
    }
    else if (data_format == 0) /*BGR*/
    {
        preProcObj->params.color_conv_flag = TIADALG_COLOR_CONV_YUV420_BGR;
    }
    else
    {
        preProcObj->params.color_conv_flag = TIADALG_COLOR_CONV_YUV420_BGR;
    }

    preProcObj->params.tidl_8bit_16bit_flag = 0;
    preProcObj->num_input_tensors           = 1;
    preProcObj->num_output_tensors          = 1;

    vx_size input_sizes[APP_MAX_TENSOR_DIMS];
    input_sizes[0] = preProcObj->width_;
    input_sizes[1] = preProcObj->height_;
    input_sizes[2] = 3;

    vx_enum   data_type = VX_TYPE_UINT8;
    vx_tensor output_tensors[APP_MAX_TENSORS];
    output_tensors[0] = vxCreateTensor(context, 3, input_sizes, data_type, 0);

    for (i = 0; i < preProcObj->num_input_tensors; i++)
    {
        preProcObj->output_tensor_arr[i] = vxCreateObjectArray(context, (vx_reference)output_tensors[i], NUM_CH);
        vxReleaseTensor(&output_tensors[i]);
    }
}

vx_status app_update_pre_proc(vx_context context, PreProcObj* preProcObj, vx_user_data_object config)
{
    vx_status status = VX_SUCCESS;

    vx_map_id          map_id_config;
    sTIDL_IOBufDesc_t* ioBufDesc;
    tivxTIDLJ7Params*  tidlParams;
    vx_tensor          output_tensors[APP_MAX_TENSORS];
    vx_int32           i;

    vxMapUserDataObject(config, 0, sizeof(tivxTIDLJ7Params), &map_id_config, (void**)&tidlParams, VX_READ_ONLY,
                        VX_MEMORY_TYPE_HOST, 0);

    ioBufDesc = (sTIDL_IOBufDesc_t*)&tidlParams->ioBufDesc;
    memcpy(&preProcObj->ioBufDesc, ioBufDesc, sizeof(sTIDL_IOBufDesc_t));

    vxUnmapUserDataObject(config, map_id_config);

    preProcObj->params.pad_pixel[0] = ioBufDesc->inPadL[0];  // Left
    preProcObj->params.pad_pixel[1] = ioBufDesc->inPadT[0];  // Top
    preProcObj->params.pad_pixel[2] = ioBufDesc->inPadR[0];  // Right
    preProcObj->params.pad_pixel[3] = ioBufDesc->inPadB[0];  // Bottom

    if ((ioBufDesc->inElementType[0] == TIDL_UnsignedChar) || (ioBufDesc->inElementType[0] == TIDL_SignedChar))
    {
        preProcObj->params.tidl_8bit_16bit_flag = 0;
    }
    else if ((ioBufDesc->inElementType[0] == TIDL_UnsignedShort) || (ioBufDesc->inElementType[0] == TIDL_SignedShort))
    {
        preProcObj->params.tidl_8bit_16bit_flag = 1;
    }

    if (ioBufDesc->inDataFormat[0] == 1) /*RGB*/
    {
        preProcObj->params.color_conv_flag = TIADALG_COLOR_CONV_YUV420_RGB;
    }
    else if (ioBufDesc->inDataFormat[0] == 0) /*BGR*/
    {
        preProcObj->params.color_conv_flag = TIADALG_COLOR_CONV_YUV420_BGR;
    }

    preProcObj->num_input_tensors  = ioBufDesc->numInputBuf;
    preProcObj->num_output_tensors = ioBufDesc->numOutputBuf;

    createOutputTensors(context, config, output_tensors);

    for (i = 0; i < preProcObj->num_input_tensors; i++)
    {
        preProcObj->output_tensor_arr[i] = vxCreateObjectArray(context, (vx_reference)output_tensors[i], NUM_CH);
        vxReleaseTensor(&output_tensors[i]);
    }

    return status;
}

vx_status app_update_tidl_pre_proc(vx_context context, PreProcObj* preProcObj, vx_user_data_object config)
{
    vx_status status = VX_SUCCESS;

    vx_map_id          map_id_config;
    sTIDL_IOBufDesc_t* ioBufDesc;
    tivxTIDLJ7Params*  tidlParams;
    vx_tensor          output_tensors[APP_MAX_TENSORS];
    vx_int32           i;

    vxMapUserDataObject(config, 0, sizeof(tivxTIDLJ7Params), &map_id_config, (void**)&tidlParams, VX_READ_ONLY,
                        VX_MEMORY_TYPE_HOST, 0);

    ioBufDesc = (sTIDL_IOBufDesc_t*)&tidlParams->ioBufDesc;
    memcpy(&preProcObj->ioBufDesc, ioBufDesc, sizeof(sTIDL_IOBufDesc_t));

    vxUnmapUserDataObject(config, map_id_config);

    preProcObj->params.pad_pixel[0] = ioBufDesc->inPadL[0];  // Left
    preProcObj->params.pad_pixel[1] = ioBufDesc->inPadT[0];  // Top
    preProcObj->params.pad_pixel[2] = ioBufDesc->inPadR[0];  // Right
    preProcObj->params.pad_pixel[3] = ioBufDesc->inPadB[0];  // Bottom

    if ((ioBufDesc->inElementType[0] == TIDL_UnsignedChar) || (ioBufDesc->inElementType[0] == TIDL_SignedChar))
    {
        preProcObj->params.tidl_8bit_16bit_flag = 0;
    }
    else if ((ioBufDesc->inElementType[0] == TIDL_UnsignedShort) || (ioBufDesc->inElementType[0] == TIDL_SignedShort))
    {
        preProcObj->params.tidl_8bit_16bit_flag = 1;
    }

    if (ioBufDesc->inDataFormat[0] == 1) /*RGB*/
    {
        preProcObj->params.color_conv_flag = TIADALG_COLOR_CONV_YUV420_RGB;
    }
    else if (ioBufDesc->inDataFormat[0] == 0) /*BGR*/
    {
        preProcObj->params.color_conv_flag = TIADALG_COLOR_CONV_YUV420_BGR;
    }

    preProcObj->num_input_tensors  = ioBufDesc->numInputBuf;
    preProcObj->num_output_tensors = ioBufDesc->numOutputBuf;

    for (int i = 0; i < preProcObj->num_input_tensors; i++)  // num_input_tensors=1
    {
        for (int j = 0; j < APP_BUFFER_Q_DEPTH; j++)
        {
            preProcObj->output_tidl_data[i][j] = NULL;
        }
    }

    createOutputTensors(context, config, output_tensors);

    for (int i = 0; i < preProcObj->num_input_tensors; i++)
    {
        // preProcObj->output_tensor_arr[i] = vxCreateObjectArray(context, (vx_reference)output_tensors[i], NUM_CH);
        for (int j = 0; j < APP_BUFFER_Q_DEPTH; j++)
        {
            preProcObj->output_tidl_data[i][j] = vxCreateObjectArray(context, (vx_reference)output_tensors[i], NUM_CH);
        }
        vxReleaseTensor(&output_tensors[i]);
    }

    return status;
}

void app_deinit_pre_proc(PreProcObj* preProcObj)
{
    vx_int32 i;
    vxReleaseArray(&preProcObj->config);
    printf("preProcObj->num_output_tensors: %d\n", preProcObj->num_output_tensors);
    for (i = 0; i < preProcObj->num_output_tensors; i++)
    {
        vxReleaseObjectArray(&preProcObj->output_tensor_arr[i]);
    }
}

void app_delete_pre_proc(PreProcObj* preProcObj)
{
    if (preProcObj->node != NULL)
    {
        vxReleaseNode(&preProcObj->node);
    }
}

vx_status app_create_graph_pre_proc(vx_graph graph, PreProcObj* preProcObj, vx_object_array input_arr)
{
    vx_status status = VX_SUCCESS;

    vx_image  input  = (vx_image)vxGetObjectArrayItem((vx_object_array)input_arr, 0);
    vx_tensor output = (vx_tensor)vxGetObjectArrayItem((vx_object_array)preProcObj->output_tensor_arr[0], 0);

    preProcObj->node = tivxImgPreProcNode(graph, preProcObj->config, input, output);

    APP_ASSERT_VALID_REF(preProcObj->node);

    status = vxSetNodeTarget(preProcObj->node, VX_TARGET_STRING, TIVX_TARGET_DSP1);
    vxSetReferenceName((vx_reference)preProcObj->node, "PreProcNode");

    vx_bool replicate[] = {vx_false_e, vx_true_e, vx_true_e};
    vxReplicateNode(graph, preProcObj->node, replicate, 3);

    vxReleaseImage(&input);
    vxReleaseTensor(&output);

    return (status);
}

vx_status app_create_graph_pre_convert(vx_graph graph, PreProcObj* preProcObj, vx_object_array input_arr)
{
    vx_status status = VX_SUCCESS;

    vx_image  input  = (vx_image)vxGetObjectArrayItem((vx_object_array)input_arr, 0);
    vx_tensor output = (vx_tensor)vxGetObjectArrayItem((vx_object_array)preProcObj->output_tensor_arr[0], 0);

    preProcObj->node = tivxImgPreProcNode(graph, preProcObj->config, input, output);

    APP_ASSERT_VALID_REF(preProcObj->node);

    status = vxSetNodeTarget(preProcObj->node, VX_TARGET_STRING, TIVX_TARGET_DSP1);
    vxSetReferenceName((vx_reference)preProcObj->node, "PreProcNode");

    vx_bool replicate[] = {vx_false_e, vx_true_e, vx_true_e};
    vxReplicateNode(graph, preProcObj->node, replicate, 3);

    vxReleaseImage(&input);
    vxReleaseTensor(&output);

    return (status);
}

vx_status writePreProcOutput(char* file_name, PreProcObj* preProcObj)
{
    vx_status status = VX_SUCCESS;

    vx_tensor output;
    vx_size   numCh;
    vx_int32  ch;

    vxQueryObjectArray((vx_object_array)preProcObj->output_tensor_arr[0], VX_OBJECT_ARRAY_NUMITEMS, &numCh,
                       sizeof(vx_size));

    for (ch = 0; ch < numCh; ch++)
    {
        vx_size   num_dims;
        void*     data_ptr;
        vx_map_id map_id;

        vx_size start[APP_MAX_TENSOR_DIMS];
        vx_size tensor_strides[APP_MAX_TENSOR_DIMS];
        vx_size tensor_sizes[APP_MAX_TENSOR_DIMS];
        vx_char new_name[APP_MAX_FILE_PATH];

        /* Write Y plane */
        output = (vx_tensor)vxGetObjectArrayItem((vx_object_array)preProcObj->output_tensor_arr[0], ch);

        vxQueryTensor(output, VX_TENSOR_NUMBER_OF_DIMS, &num_dims, sizeof(vx_size));

        if (num_dims != 3)
        {
            printf("Number of dims are != 3! exiting.. \n");
            break;
        }

        vxQueryTensor(output, VX_TENSOR_DIMS, tensor_sizes, 3 * sizeof(vx_size));

        start[0] = start[1] = start[2] = 0;

        tensor_strides[0] = 1;
        tensor_strides[1] = tensor_strides[0];
        tensor_strides[2] = tensor_strides[1] * tensor_strides[1];

        status = tivxMapTensorPatch(output, num_dims, start, tensor_sizes, &map_id, tensor_strides, &data_ptr,
                                    VX_READ_ONLY, VX_MEMORY_TYPE_HOST);

        snprintf(new_name, APP_MAX_FILE_PATH, "%s_%dx%d_ch%d.yuv", file_name, (uint32_t)tensor_sizes[0],
                 (uint32_t)tensor_sizes[1], ch);

        FILE* fp = fopen(new_name, "wb");
        if (NULL == fp)
        {
            printf("Unable to open file %s \n", new_name);
            break;
        }

        if (VX_SUCCESS == status)
        {
            fwrite(data_ptr, 1, tensor_sizes[0] * tensor_sizes[1] * tensor_sizes[2], fp);

            tivxUnmapTensorPatch(output, map_id);
        }
        vxReleaseTensor(&output);

        fclose(fp);
    }

    return (status);
}

static void createOutputTensors(vx_context context, vx_user_data_object config, vx_tensor output_tensors[])
{
    vx_size   input_sizes[APP_MAX_TENSOR_DIMS];
    vx_map_id map_id_config;

    vx_uint32 id;

    tivxTIDLJ7Params*  tidlParams;
    sTIDL_IOBufDesc_t* ioBufDesc;

    vxMapUserDataObject(config, 0, sizeof(tivxTIDLJ7Params), &map_id_config, (void**)&tidlParams, VX_READ_ONLY,
                        VX_MEMORY_TYPE_HOST, 0);

    ioBufDesc = (sTIDL_IOBufDesc_t*)&tidlParams->ioBufDesc;
    for (id = 0; id < ioBufDesc->numInputBuf; id++)
    {
        input_sizes[0] = ioBufDesc->inWidth[id] + ioBufDesc->inPadL[id] + ioBufDesc->inPadR[id];
        input_sizes[1] = ioBufDesc->inHeight[id] + ioBufDesc->inPadT[id] + ioBufDesc->inPadB[id];
        input_sizes[2] = ioBufDesc->inNumChannels[id];

        vx_enum data_type  = get_vx_tensor_datatype(ioBufDesc->inElementType[id]);
        output_tensors[id] = vxCreateTensor(context, 3, input_sizes, data_type, 0);
    }

    vxUnmapUserDataObject(config, map_id_config);

    return;
}

static vx_enum get_vx_tensor_datatype(int32_t tidl_datatype)
{
    vx_enum tiovx_datatype = VX_TYPE_INVALID;

    if (tidl_datatype == TIDL_UnsignedChar)
    {
        tiovx_datatype = VX_TYPE_UINT8;
    }
    else if (tidl_datatype == TIDL_SignedChar)
    {
        tiovx_datatype = VX_TYPE_INT8;
    }
    else if (tidl_datatype == TIDL_UnsignedShort)
    {
        tiovx_datatype = VX_TYPE_UINT16;
    }
    else if (tidl_datatype == TIDL_SignedShort)
    {
        tiovx_datatype = VX_TYPE_INT16;
    }
    else if (tidl_datatype == TIDL_UnsignedWord)
    {
        tiovx_datatype = VX_TYPE_UINT32;
    }
    else if (tidl_datatype == TIDL_SignedWord)
    {
        tiovx_datatype = VX_TYPE_INT32;
    }
    else if (tidl_datatype == TIDL_SinglePrecFloat)
    {
        tiovx_datatype = VX_TYPE_FLOAT32;
    }

    return (tiovx_datatype);
}
