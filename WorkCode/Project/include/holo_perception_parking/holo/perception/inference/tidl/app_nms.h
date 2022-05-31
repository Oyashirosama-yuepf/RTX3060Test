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

#define APP_PRE_PROC_MAX_TENSORS (8)        

// #include "tiadalg_interface.h"  
// #include "itidl_ti.h"
// #include <TI/tivx.h>
// #include <TI/tivx_task.h>
// #include <TI/tivx_target_kernel.h>
// #include "tivx_kernels_host_utils.h"
// #include <TI/tivx_img_proc.h>
// #include <TI/tivx_self_img_proc.h>

// #include <TI/j7.h>
// #include <TI/j7_tidl.h>
// #include <tivx_utils_file_rd_wr.h>
// #include <tivx_utils_graph_perf.h>

#include <assert.h>
#include <vector>
#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif

#define APP_PRE_PROC_MAX_TENSORS 4
// #define APP_BUFFER_Q_DEPTH 4
#define GRAPH_PARAMETER_MAX 16
#define APP_ASSERT_VALID_REF(ref)   (APP_ASSERT(vxGetStatus((vx_reference)(ref))==VX_SUCCESS));
#ifdef APP_DEBUG
#define APP_PRINTF(f_, ...) printf((f_), ##__VA_ARGS__)
#else
#define APP_PRINTF(f_, ...)
#endif

#define APP_ASSERT(x)               assert((x))
#define APP_ASSERT_VALID_REF(ref)   (APP_ASSERT(vxGetStatus((vx_reference)(ref))==VX_SUCCESS));
#define APP_MAX_FILE_PATH           (256u)
#define APP_MAX_TENSORS             (8u)
#define APP_MAX_TENSOR_DIMS         (8u)
#define APP_TIDL_MAX_PARAMS         (16u)
#define NUM_CH    (1)
// #define APP_BUFFER_Q_DEPTH   (4)  // pipeline 

// typedef struct {
//   vx_node  node;

//   vx_array config;
//   tivxImgPreProcParams params;

//   sTIDL_IOBufDesc_t ioBufDesc;
//   // test
//   vx_tensor input1[APP_PRE_PROC_MAX_TENSORS], input2[APP_PRE_PROC_MAX_TENSORS];
//   vx_tensor scores, indexs;
//   vx_int32 graph_parameter_index[16];
//   std::vector<int> data_len;
//   std::vector<int> data_type; 
// } test_obj;

// int32_t appInit();
// int32_t appDeInit();
struct test_obj;

// vx_status app_update_pre_proc_test(vx_context context, test_obj *preProcObj, vx_user_data_object config);
// vx_status app_init_pre_proc_test(vx_context context, test_obj *preProcObj, char *objName);
// vx_status app_update_pre_proc_data_convert_test(vx_context context, test_obj *preProcObj);
// void app_deinit_pre_proc_test(test_obj *obj);
// void app_delete_pre_proc_test(test_obj *obj);
// vx_status app_create_graph_pre_proc_test(vx_graph graph, test_obj *preProcObj);
// vx_status writePreProcOutput_test(char* file_name, test_obj *preProcObj);

// class AppTest
// {
//    public:
//     //ScalerObj  scalerObj;
//     test_obj preProcObj;
//     /* OpenVX references */
//     vx_context context;
//     vx_graph   graph;

//     vx_int32 en_out_img_write;

//     vx_int32 start_frame;
//     vx_int32 num_frames;

//     vx_uint32 delay_in_msecs;
//     vx_uint32 num_iterations;
//     vx_uint32 is_interactive;

//     int32_t pipeline;	
    
//     int32_t enqueueCnt;
//     int32_t dequeueCnt;
//     public:
//        AppTest();
//        AppTest(std::vector<int> data_len, std::vector<int> data_type);
// };

class AppTest;
class AppSelfKernel
{
    public:
        AppSelfKernel();
        AppSelfKernel(std::vector<int> data_len, std::vector<int> data_type);
        ~AppSelfKernel();
        // bool map_tensor_data(vx_tensor& data, void*& data_buf, bool read=false);
        // void unmap_tensor_data(const vx_tensor& data);

        int setdata(int8_t* data, int data_len, int index=0);
        int setdata(int8_t* data, std::vector<int> data_shape, std::vector<int> data_crop);

        int getdata(int8_t* data);
        bool getdata(int8_t* data, const int data_len, int index=0);
    public:
        AppTest* obj;
        // vx_map_id map_id;
};
// class GetTimeDiffApp
// {
//     public:
//       struct timeval t1,t2;
//     public:
//       void SetStartTime()
//       {
//          gettimeofday(&t1,NULL);
//       }
//       float GetTimeDiff()
//       {
//          gettimeofday(&t2,NULL);
//          auto timeuse = (t2.tv_sec - t1.tv_sec)*1000.0 + (double)(t2.tv_usec - t1.tv_usec)/1000.0;
//          return timeuse;
//       }
// };

#ifdef __cplusplus
}
#endif
