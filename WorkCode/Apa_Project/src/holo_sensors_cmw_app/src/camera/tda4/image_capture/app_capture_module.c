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

#include <app_capture_module.h>
#include <iss_sensors.h>
#include <iss_sensor_if.h>

vx_status app_init_capture(vx_context context, CaptureObj *captureObj, SensorObj *sensorObj, char *objName, int32_t bufq_depth)
{
    vx_status status = VX_SUCCESS;
    //tivx_raw_image raw_image;
    vx_image sample_image;
    vx_uint32 num_capt_instances;
    vx_int32 id, lane, q, ch;

    IssSensor_CreateParams *sensorParams = &sensorObj->sensorParams;

    if(sensorObj->num_cameras_enabled > 4)
    {
        num_capt_instances= 2;
    }
    else
    {
        num_capt_instances= 1;
    }

    tivx_capture_params_init(&captureObj->params);

    if (captureObj->enable_error_detection)
    {
        captureObj->params.timeout        = 90;
        captureObj->params.timeoutInitial = 500;
    }
    captureObj->params.numInst  = num_capt_instances;
    captureObj->params.numCh    = sensorObj->num_cameras_enabled;

        
APP_PRINTF("capture inst is %d, channle is  = %d \n", captureObj->params.numInst,captureObj->params.numCh);
    ch = 0;
    for(id = 0; id < num_capt_instances; id++)
    {
        captureObj->params.instId[id]                       = 1;
        captureObj->params.instCfg[id].enableCsiv2p0Support = (uint32_t)vx_true_e;
        captureObj->params.instCfg[id].numDataLanes         = 4U;
        APP_PRINTF("captureObj->params.numDataLanes = %d \n", captureObj->params.instCfg[id].numDataLanes);

        for (lane = 0; lane < captureObj->params.instCfg[id].numDataLanes; lane++)
        {
            captureObj->params.instCfg[id].dataLanesMap[lane] = lane + 1;
            APP_PRINTF("captureObj->params.dataLanesMap[%d] = %d \n",
                        lane,
                        captureObj->params.instCfg[id].dataLanesMap[lane]);
        }
        for (q = 0; q < NUM_CAPT_CHANNELS; q++)
        {
            captureObj->params.chVcNum[ch]   = q;
            captureObj->params.chInstMap[ch] = id;
            ch++;
        }
    }

    captureObj->config = vxCreateUserDataObject(context, "tivx_capture_params_t", sizeof(tivx_capture_params_t), &captureObj->params);

    //raw_image = tivxCreateRawImage(context, &sensorParams->sensorInfo.raw_params);
      //sample_image = vxCreateImage(context, sensorObj->image_width,sensorObj->image_height,VX_DF_IMAGE_UYVY);
      sample_image = vxCreateImage(context, sensorObj->image_width,sensorObj->image_height,VX_DF_IMAGE_YUYV);

    for(q = 0; q < bufq_depth; q++)
    {
        //captureObj->raw_image_arr[q] = vxCreateObjectArray(context, (vx_reference)raw_image, sensorObj->num_cameras_enabled);
        captureObj->raw_image_arr[q] = vxCreateObjectArray(context, (vx_reference)sample_image, sensorObj->num_cameras_enabled);
    }
    //tivxReleaseRawImage(&raw_image);
    vxReleaseImage(&sample_image);

    if(captureObj->en_out_capture_write == 1)
    {
        char file_path[TIVX_FILEIO_FILE_PATH_LENGTH];
        char file_prefix[TIVX_FILEIO_FILE_PREFIX_LENGTH];

        strcpy(file_path, captureObj->output_file_path);
        captureObj->file_path   = vxCreateArray(context, VX_TYPE_UINT8, TIVX_FILEIO_FILE_PATH_LENGTH);
        vxAddArrayItems(captureObj->file_path, TIVX_FILEIO_FILE_PATH_LENGTH, &file_path[0], 1);

        strcpy(file_prefix, "csix_raw_output");
        captureObj->file_prefix = vxCreateArray(context, VX_TYPE_UINT8, TIVX_FILEIO_FILE_PREFIX_LENGTH);
        vxAddArrayItems(captureObj->file_prefix, TIVX_FILEIO_FILE_PREFIX_LENGTH, &file_prefix[0], 1);

        captureObj->write_cmd = vxCreateUserDataObject(context, "tivxFileIOWriteCmd", sizeof(tivxFileIOWriteCmd), NULL);
    }
    else
    {
        captureObj->file_path   = NULL;
        captureObj->file_prefix = NULL;
        captureObj->write_node  = NULL;
        captureObj->write_cmd   = NULL;
    }

    return (status);
}

void app_deinit_capture(CaptureObj *captureObj, vx_int32 bufq_depth)
{
    vx_int32 i;

    vxReleaseUserDataObject(&captureObj->config);
    for(i = 0; i < bufq_depth; i++)
    {
        vxReleaseObjectArray(&captureObj->raw_image_arr[i]);
    }

//    tivxReleaseRawImage(&captureObj->black_raw_image);

    if(captureObj->en_out_capture_write == 1)
    {
        vxReleaseArray(&captureObj->file_path);
        vxReleaseArray(&captureObj->file_prefix);
        vxReleaseUserDataObject(&captureObj->write_cmd);
    }
}

void app_delete_capture(CaptureObj *captureObj)
{
    if(captureObj->node != NULL)
    {
        vxReleaseNode(&captureObj->node);
    }
    if(captureObj->write_node != NULL)
    {
        vxReleaseNode(&captureObj->write_node);
    }
}

vx_status app_create_graph_capture(vx_graph graph, CaptureObj *captureObj)
{
    vx_status status = VX_SUCCESS;

    captureObj->node = tivxCaptureNode(graph, captureObj->config, captureObj->raw_image_arr[0]);
    status = vxGetStatus((vx_reference)captureObj->node);
    vxSetNodeTarget(captureObj->node, VX_TARGET_STRING, TIVX_TARGET_CAPTURE1);
    vxSetReferenceName((vx_reference)captureObj->node, "capture_node");

    if(captureObj->en_out_capture_write == 1)
    {
        APP_PRINTF("Adding Capture write node on graph .. \n");
        status = app_create_graph_capture_write_output(graph, captureObj);
        APP_PRINTF("Capture write node added! \n");
    }

    return status;
}

vx_status app_create_graph_capture_write_output(vx_graph graph, CaptureObj *captureObj)
{
    vx_status status = VX_SUCCESS;

    tivx_raw_image raw_img = (tivx_raw_image)vxGetObjectArrayItem(captureObj->raw_image_arr[0], 0);

    captureObj->write_node = tivxWriteRawImageNode(graph, raw_img, captureObj->file_path, captureObj->file_prefix);
    status = vxGetStatus((vx_reference)captureObj->write_node);
    vxSetNodeTarget(captureObj->write_node, VX_TARGET_STRING, TIVX_TARGET_A72_0);
    vxSetReferenceName((vx_reference)captureObj->write_node, "capture_write_node");

    vx_bool replicate[] = { vx_true_e, vx_false_e, vx_false_e};
    vxReplicateNode(graph, captureObj->write_node, replicate, 3);

    tivxReleaseRawImage(&raw_img);

    return (status);
}

vx_status app_send_cmd_capture_node(CaptureObj *captureObj, vx_uint32 start_frame, vx_uint32 num_frames, vx_uint32 num_skip)
{
    vx_status status = VX_SUCCESS;

    tivxFileIOWriteCmd write_cmd;

    write_cmd.start_frame = start_frame;
    write_cmd.num_frames = num_frames;
    write_cmd.num_skip = num_skip;

    status = vxCopyUserDataObject(captureObj->write_cmd, 0, sizeof(tivxFileIOWriteCmd),\
                  &write_cmd, VX_WRITE_ONLY, VX_MEMORY_TYPE_HOST);

    if(status == VX_SUCCESS)
    {
        vx_reference refs[2];

        refs[0] = (vx_reference)captureObj->write_cmd;

        status = tivxNodeSendCommand(captureObj->write_node, TIVX_CONTROL_CMD_SEND_TO_ALL_REPLICATED_NODES,
                                 TIVX_FILEIO_CMD_SET_FILE_WRITE,
                                 refs, 1u);

        if(VX_SUCCESS != status)
        {
            printf("Capture node send command failed!\n");
        }

        APP_PRINTF("Capture node send command success!\n");
    }

    return (status);
}

vx_status app_send_error_frame(vx_context context, CaptureObj *captureObj, SensorObj *sensorObj)
{
    vx_status status = VX_SUCCESS;
    IssSensor_CreateParams *sensorParams = &sensorObj->sensorParams;

    captureObj->black_raw_image = tivxCreateRawImage(context, &(sensorParams->sensorInfo.raw_params));;

    status = tivxCaptureRegisterErrorFrame(captureObj->node, (vx_reference)captureObj->black_raw_image);

    return status;
}
