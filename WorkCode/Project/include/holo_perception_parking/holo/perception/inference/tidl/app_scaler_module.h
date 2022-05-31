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
#ifndef _APP_SCALER_MODULE
#define _APP_SCALER_MODULE

#ifdef __cplusplus
extern "C" {
#endif

#include "app_common.h"

typedef struct
{
    vx_object_array arr[APP_MAX_BUFQ_DEPTH];

    vx_int32 width;
    vx_int32 height;

    vx_char objName[APP_MAX_FILE_PATH];

} ImgObj;

typedef struct
{
    vx_node node;

    ImgObj input;

    ImgObj output1;
    ImgObj output2;
    ImgObj output[APP_TIDL_NODE_NUM];

    vx_user_data_object coeff_obj;

    vx_int32 graph_parameter_index;

    /* Arrray of 0th index reference of input.arr */
    vx_image input_images[APP_MAX_BUFQ_DEPTH];

    vx_char objName[APP_MAX_FILE_PATH];

    bool     crop_use = false;
    vx_int32 crop_start_x;
    vx_int32 crop_start_y;
    vx_int32 crop_width;
    vx_int32 crop_height;

} ScalerObj;

void scale_set_coeff(tivx_vpac_msc_coefficients_t* coeff, uint32_t interpolation);

vx_status app_init_scaler(vx_context context, ScalerObj* scalerObj, char* objName, vx_int32 bufq_depth);

void app_deinit_scaler(ScalerObj* obj, vx_int32 bufq_depth);

void app_delete_scaler(ScalerObj* obj);

vx_status app_create_graph_scaler(vx_context context, vx_graph graph, ScalerObj* scalerObj);
vx_status app_create_graph_ldc_scaler(vx_context context, vx_graph graph, ScalerObj *scalerObj, vx_object_array input_arr);

vx_status readScalerInput(char* file_name, vx_object_array img_arr, int32_t ch_num);

vx_status writeScalerOutput(char* file_name, vx_object_array img_arr);

#ifdef __cplusplus
}
#endif

#endif
