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

#include <app_img_mosaic_module.h>


vx_status app_init_img_mosaic(vx_context context, ImgMosaicObj *imgMosaicObj, char *objName, vx_int32 bufq_depth)
{
  vx_status status = VX_SUCCESS;
  vx_int32 i, q;

  imgMosaicObj->config = vxCreateUserDataObject(context, "ImgMosaicConfig", sizeof(tivxImgMosaicParams), NULL);
  status = vxGetStatus((vx_reference)imgMosaicObj->config);

  if(status == VX_SUCCESS)
  {
      status = vxCopyUserDataObject(imgMosaicObj->config, 0, sizeof(tivxImgMosaicParams),\
                &imgMosaicObj->params, VX_WRITE_ONLY, VX_MEMORY_TYPE_HOST);
  }

  for(q = 0; q < bufq_depth; q++)
  {
    if(status == VX_SUCCESS)
    {
      imgMosaicObj->output_image[q] = vxCreateImage(context, imgMosaicObj->out_width, imgMosaicObj->out_height, VX_DF_IMAGE_NV12);
      status = vxGetStatus((vx_reference)imgMosaicObj->output_image[q]);
    }
  }

  if(status == VX_SUCCESS)
  {
      imgMosaicObj->kernel = tivxAddKernelImgMosaic(context, imgMosaicObj->num_inputs);
      status = vxGetStatus((vx_reference)imgMosaicObj->kernel);
      //ywg add for debug
      if(status == VX_SUCCESS)
      {
	printf("imgmosaic kernel creat ok\n");
      }
  }

  for(i = 0; i < TIVX_IMG_MOSAIC_MAX_INPUTS; i++)
  {
    imgMosaicObj->input_arr[i] = NULL;
  }

  return status;
}

void app_deinit_img_mosaic(ImgMosaicObj *imgMosaicObj, vx_int32 bufq_depth)
{
  vx_int32 q;

  vxReleaseUserDataObject(&imgMosaicObj->config);
  for(q = 0; q < bufq_depth; q++)
  {
    vxReleaseImage(&imgMosaicObj->output_image[q]);
  }

  return;
}

void app_delete_img_mosaic(ImgMosaicObj *imgMosaicObj)
{
  if(imgMosaicObj->node != NULL)
  {
    vxReleaseNode(&imgMosaicObj->node);
  }
  if(imgMosaicObj->kernel != NULL)
  {
    vxRemoveKernel(imgMosaicObj->kernel);
  }
  return;
}

vx_status app_create_graph_img_mosaic(vx_graph graph, ImgMosaicObj *imgMosaicObj)
{

  vx_status status = VX_SUCCESS;

  imgMosaicObj->node = tivxImgMosaicNode(graph,
                                         imgMosaicObj->kernel,
                                         imgMosaicObj->config,
                                         imgMosaicObj->output_image[0],
                                         imgMosaicObj->input_arr,
                                         imgMosaicObj->num_inputs);

  APP_ASSERT_VALID_REF(imgMosaicObj->node);
  #ifdef x86_64
  vxSetNodeTarget(imgMosaicObj->node, VX_TARGET_STRING, TIVX_TARGET_DSP1);
  #else
  vxSetNodeTarget(imgMosaicObj->node, VX_TARGET_STRING, TIVX_TARGET_VPAC_MSC1);
  #endif
  vxSetReferenceName((vx_reference)imgMosaicObj->node, "mosaic_node");
  status = vxGetStatus((vx_reference)imgMosaicObj->node);

  return (status);

}

vx_status writeMosaicOutput(char* file_name, vx_image out_img)
{
  vx_status status;

  status = vxGetStatus((vx_reference)out_img);

  if(status == VX_SUCCESS)
  {
	FILE * fp = fopen(file_name,"wb");
    if(fp == NULL)
    {
      printf("File could not be opened \n");
      return (VX_FAILURE);
    }

    {
      vx_rectangle_t rect;
      vx_imagepatch_addressing_t image_addr;
      vx_map_id map_id;
      void * data_ptr;
      vx_uint32  img_width;
      vx_uint32  img_height;
      vx_uint32  num_bytes;

      vxQueryImage(out_img, VX_IMAGE_WIDTH, &img_width, sizeof(vx_uint32));
      vxQueryImage(out_img, VX_IMAGE_HEIGHT, &img_height, sizeof(vx_uint32));

      rect.start_x = 0;
      rect.start_y = 0;
      rect.end_x = img_width;
      rect.end_y = img_height;
      status = vxMapImagePatch(out_img,
                               &rect,
                               0,
                               &map_id,
                               &image_addr,
                               &data_ptr,
                               VX_READ_ONLY,
                               VX_MEMORY_TYPE_HOST,
                               VX_NOGAP_X);

      //Copy Luma
      num_bytes = fwrite(data_ptr,1,img_width*img_height, fp);

      if(num_bytes != (img_width*img_height))
        printf("Luma bytes written = %d, expected = %d", num_bytes, img_width*img_height);

      vxUnmapImagePatch(out_img, map_id);

      status = vxMapImagePatch(out_img,
                               &rect,
                               1,
                               &map_id,
                               &image_addr,
                               &data_ptr,
                               VX_READ_ONLY,
                               VX_MEMORY_TYPE_HOST,
                               VX_NOGAP_X);


      //Copy CbCr
      num_bytes = fwrite(data_ptr,1,img_width*img_height/2, fp);

      if(num_bytes != (img_width*img_height/2))
        printf("CbCr bytes written = %d, expected = %d", num_bytes, img_width*img_height/2);

      vxUnmapImagePatch(out_img, map_id);

    }

    fclose(fp);
  }

  return(status);
}
