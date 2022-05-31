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
#ifndef _APP_TIDL_MODULE
#define _APP_TIDL_MODULE

#ifdef __cplusplus
extern "C" {
#endif

#include "app_common.h"
#include "itidl_ti.h"

#define APP_TIDL_MAX_TENSORS (8)

/* #define APP_TIDL_TRACE_DUMP */

typedef struct
{
    vx_node             node;
    vx_kernel           kernel;
    vx_user_data_object config;
    vx_user_data_object network;
    vx_user_data_object createParams;
    vx_object_array     in_args_arr;
    vx_object_array     out_args_arr;
    vx_object_array     trace_data_arr;
    vx_object_array     output_tensor_arr[APP_TIDL_MAX_TENSORS][APP_MAX_BUFQ_DEPTH];

    vx_uint32 num_input_tensors;
    vx_uint32 num_output_tensors;
    vx_int32  graph_parameter_index[APP_MAX_BUFQ_DEPTH];

    vx_char  label_names[3][APP_MAX_FILE_PATH];
    vx_char  config_file_path[APP_MAX_FILE_PATH];
    vx_char  network_file_path[APP_MAX_FILE_PATH];
    vx_char  objName[APP_MAX_FILE_PATH];
    vx_uint8 config_checksum[TIVX_TIDL_J7_CHECKSUM_SIZE];
    vx_uint8 network_checksum[TIVX_TIDL_J7_CHECKSUM_SIZE];

} TIDLObj;

vx_status app_init_tidl(vx_context context, TIDLObj* obj, char* objName);
void      app_deinit_tidl(TIDLObj* obj);
void      app_delete_tidl(TIDLObj* obj);
vx_status app_create_graph_tidl(vx_context context, vx_graph graph, TIDLObj* tidlObj,
                                vx_object_array input_tensor_arr[]);

vx_status writeTIDLOutput(char* file_name, TIDLObj* tidlObj);

#ifdef __cplusplus
}
#endif

#endif
