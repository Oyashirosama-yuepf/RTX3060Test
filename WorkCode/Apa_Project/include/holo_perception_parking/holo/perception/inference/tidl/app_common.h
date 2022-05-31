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
#ifndef _APP_COMMON
#define _APP_COMMON

#ifdef __cplusplus
extern "C" {
#endif

#include <TI/tivx.h>
#include <TI/tivx_img_proc.h>
#include <TI/tivx_target_kernel.h>
#include <TI/tivx_task.h>
#include "tivx_kernels_host_utils.h"

#include <TI/j7.h>
#include <TI/j7_tidl.h>
#include <tivx_utils_file_rd_wr.h>
#include <tivx_utils_graph_perf.h>
#include <utils/iss/include/app_iss.h>

#ifdef __cplusplus
}
#endif

#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include <sys/time.h>

//#define APP_DEBUG
#define APP_USE_FILEIO

#define APP_MAX_FILE_PATH (256u)
#define APP_ASSERT(x) assert((x))
#define APP_ASSERT_VALID_REF(ref) (APP_ASSERT(vxGetStatus((vx_reference)(ref)) == VX_SUCCESS));

#define APP_MAX_TENSORS (8u)
#define APP_MAX_TENSOR_DIMS (8u)
#define APP_TIDL_MAX_PARAMS (16u)
#define GRAPH_PARAMETER_MAX (20)  // random value > APP_TIDL_MAX_TENSORS+1

#define ABS_FLT(a) ((a) > 0) ? (a) : (-(a))

#define MAX_IMG_WIDTH (2048)
#define MAX_IMG_HEIGHT (2048)
#define DISPLAY_WIDTH (1920)
#define DISPLAY_HEIGHT (1080)
#define NUM_CH (1)
#define NUM_ALGOS (5)

#define APP_BUFFER_Q_DEPTH (4)  // pipeline
#define APP_TIDL_NODE_NUM  (2)  // od fd node
#define APP_TIDL_MAX_TENSORS (8)

#define DET_SCORE -0.8473        // 0.7
#define FREESPACE_SCORE -0.8473  // test
#define SRC_IMAGE_WIDTH 1920
#define SRC_IMAGE_HEIGHT 1020
#define DET_OUTPUT_WIDTH 256
#define DET_OUTPUT_HEIGHT 128
#define DET_OUTPUT_CHANNEL 6

// get tda4 tensor id
// #define DET_SIGMOID_ID 4
// #define DET_WH_ID 4
// #define DET_REG_ID 4

// #define FREESPACE_ID 0

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

#define APP_MAX_BUFQ_DEPTH (8)

#ifdef APP_DEBUG
#define APP_PRINTF(f_, ...) printf((f_), ##__VA_ARGS__)
#else
#define APP_PRINTF(f_, ...)
#endif

#endif
