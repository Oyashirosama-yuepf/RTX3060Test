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
#include <localization/vision/birdview/tda4_nv12torgb/app_scaler_module.h>

vx_status app_init_scaler(vx_context context, ScalerObj* scalerObj, char* objName, vx_int32 bufq_depth)
{
    printf("test end\n");
    vx_status status = VX_SUCCESS;
    vx_int32  q;

    tivx_vpac_msc_coefficients_t coeffs;
    printf("width: %d", scalerObj->input.width);
    vx_image input   = vxCreateImage(context, scalerObj->input.width, scalerObj->input.height, VX_DF_IMAGE_NV12);
    vx_image output1 = vxCreateImage(context, scalerObj->output1.width, scalerObj->output1.height, VX_DF_IMAGE_NV12);
    // vx_image output2  = vxCreateImage(context, scalerObj->output2.width, scalerObj->output2.height,
    // VX_DF_IMAGE_NV12);
    printf("max batch size: %d", bufq_depth);
    for (q = 0; q < bufq_depth; q++)
    {
        scalerObj->input.arr[q]    = vxCreateObjectArray(context, (vx_reference)input, NUM_CH);
        scalerObj->input_images[q] = (vx_image)vxGetObjectArrayItem((vx_object_array)scalerObj->input.arr[q], 0);
    }
    scalerObj->output1.arr[0] = vxCreateObjectArray(context, (vx_reference)output1, NUM_CH);
    // scalerObj->output2.arr[0]  = vxCreateObjectArray(context, (vx_reference)output2, NUM_CH);

    scale_set_coeff(&coeffs, VX_INTERPOLATION_BILINEAR);
    // scale_set_coeff(&coeffs, VX_INTERPOLATION_NEAREST_NEIGHBOR);

    /* Set Coefficients */
    scalerObj->coeff_obj =
        vxCreateUserDataObject(context, "tivx_vpac_msc_coefficients_t", sizeof(tivx_vpac_msc_coefficients_t), NULL);

    vxCopyUserDataObject(scalerObj->coeff_obj, 0, sizeof(tivx_vpac_msc_coefficients_t), &coeffs, VX_WRITE_ONLY,
                         VX_MEMORY_TYPE_HOST);

    vxReleaseImage(&input);
    vxReleaseImage(&output1);
    // vxReleaseImage(&output2);

    return status;
}

void app_deinit_scaler(ScalerObj* scalerObj, vx_int32 bufq_depth)
{
    vx_int32 q;

    for (q = 0; q < bufq_depth; q++)
    {
        vxReleaseObjectArray(&scalerObj->input.arr[q]);
        vxReleaseImage(&scalerObj->input_images[q]);
    }

    vxReleaseObjectArray(&scalerObj->output1.arr[0]);
    vxReleaseObjectArray(&scalerObj->output2.arr[0]);

    vxReleaseUserDataObject(&scalerObj->coeff_obj);
}

void app_delete_scaler(ScalerObj* scalerObj)
{
    if (scalerObj->node != NULL)
    {
        vxReleaseNode(&scalerObj->node);
    }
}

vx_status app_create_graph_scaler(vx_context context, vx_graph graph, ScalerObj* scalerObj)
{
    vx_status status = VX_SUCCESS;

    vx_image input   = (vx_image)vxGetObjectArrayItem((vx_object_array)scalerObj->input.arr[0], 0);
    vx_image output1 = (vx_image)vxGetObjectArrayItem((vx_object_array)scalerObj->output1.arr[0], 0);
    // vx_image output2 = (vx_image)vxGetObjectArrayItem((vx_object_array)scalerObj->output2.arr[0], 0);

    // scalerObj->node = tivxVpacMscScaleNode(graph, input, output1, output2, NULL, NULL, NULL);
    scalerObj->node = tivxVpacMscScaleNode(graph, input, output1, NULL, NULL, NULL, NULL);
    vxSetNodeTarget(scalerObj->node, VX_TARGET_STRING, TIVX_TARGET_VPAC_MSC1);
    vxSetReferenceName((vx_reference)scalerObj->node, "ScalerNode");

    vx_bool replicate[] = {vx_true_e, vx_true_e, vx_true_e, vx_false_e, vx_false_e, vx_false_e};
    vxReplicateNode(graph, scalerObj->node, replicate, 6);

    vxReleaseImage(&input);
    vxReleaseImage(&output1);
    // vxReleaseImage(&output2);

    return status;
}

vx_status readScalerInput(char* file_name, vx_object_array img_arr, int32_t ch_num)
{
    vx_status status;

    status = vxGetStatus((vx_reference)img_arr);

    if (status == VX_SUCCESS)
    {
        FILE*    fp = fopen(file_name, "rb");
        vx_size  arr_len;
        vx_int32 i;

        if (fp == NULL)
        {
            printf("Unable to open file %s \n", file_name);
            return (VX_FAILURE);
        }

        vxQueryObjectArray(img_arr, VX_OBJECT_ARRAY_NUMITEMS, &arr_len, sizeof(vx_size));

        printf("arr_len: %d\n", arr_len);
        for (i = 0; i < arr_len; i++)
        {
            vx_rectangle_t             rect;
            vx_imagepatch_addressing_t image_addr;
            vx_map_id                  map_id;
            void*                      data_ptr;
            vx_uint32                  img_width;
            vx_uint32                  img_height;
            vx_image                   in_img;
            vx_uint32                  num_bytes;

            in_img = (vx_image)vxGetObjectArrayItem(img_arr, i);

            vxQueryImage(in_img, VX_IMAGE_WIDTH, &img_width, sizeof(vx_uint32));
            vxQueryImage(in_img, VX_IMAGE_HEIGHT, &img_height, sizeof(vx_uint32));

            rect.start_x = 0;
            rect.start_y = 0;
            rect.end_x   = img_width;
            rect.end_y   = img_height;
            status       = vxMapImagePatch(in_img, &rect, 0, &map_id, &image_addr, &data_ptr, VX_WRITE_ONLY,
                                     VX_MEMORY_TYPE_HOST, VX_NOGAP_X);

            vx_int32 one_frame = img_width * img_height * 1.5;

            if (ch_num == NUM_CH)
            {
                fseek(fp, one_frame * i, SEEK_SET);
            }
            else
            {
                fseek(fp, one_frame * ch_num, SEEK_SET);
            }

            // Copy Luma
            num_bytes = fread(data_ptr, 1, img_width * img_height, fp);

            if (num_bytes != (img_width * img_height))
                printf("Luma bytes read = %d, expected = %d", num_bytes, img_width * img_height);

            vxUnmapImagePatch(in_img, map_id);

            rect.start_x = 0;
            rect.start_y = 0;
            rect.end_x   = img_width;
            rect.end_y   = img_height / 2;
            status       = vxMapImagePatch(in_img, &rect, 1, &map_id, &image_addr, &data_ptr, VX_WRITE_ONLY,
                                     VX_MEMORY_TYPE_HOST, VX_NOGAP_X);

            // Copy CbCr
            num_bytes = fread(data_ptr, 1, img_width * img_height / 2, fp);

            if (num_bytes != (img_width * img_height / 2))
                printf("CbCr bytes read = %d, expected = %d", num_bytes, img_width * img_height / 2);

            vxUnmapImagePatch(in_img, map_id);

            vxReleaseImage(&in_img);
        }

        fclose(fp);
    }

    return (status);
}

vx_status writeScalerOutput(char* file_name, vx_object_array img_arr)
{
    vx_status status;

    status = vxGetStatus((vx_reference)img_arr);

    if (status == VX_SUCCESS)
    {
        FILE*    fp = fopen(file_name, "wb");
        vx_size  arr_len;
        vx_int32 i;

        if (fp == NULL)
        {
            printf("Unable to open file %s \n", file_name);
            return (VX_FAILURE);
        }

        vxQueryObjectArray(img_arr, VX_OBJECT_ARRAY_NUMITEMS, &arr_len, sizeof(vx_size));

        printf("arr_len: %d\n", arr_len);
        for (i = 0; i < arr_len; i++)
        {
            vx_rectangle_t             rect;
            vx_imagepatch_addressing_t image_addr;
            vx_map_id                  map_id;
            void*                      data_ptr;
            vx_uint32                  img_width;
            vx_uint32                  img_height;
            vx_image                   out_img;
            vx_uint32                  num_bytes;

            out_img = (vx_image)vxGetObjectArrayItem(img_arr, i);

            vxQueryImage(out_img, VX_IMAGE_WIDTH, &img_width, sizeof(vx_uint32));
            vxQueryImage(out_img, VX_IMAGE_HEIGHT, &img_height, sizeof(vx_uint32));

            rect.start_x = 0;
            rect.start_y = 0;
            rect.end_x   = img_width;
            rect.end_y   = img_height;
            status       = vxMapImagePatch(out_img, &rect, 0, &map_id, &image_addr, &data_ptr, VX_READ_ONLY,
                                     VX_MEMORY_TYPE_HOST, VX_NOGAP_X);

            // Copy Luma
            num_bytes = fwrite(data_ptr, 1, img_width * img_height, fp);

            if (num_bytes != (img_width * img_height))
                printf("Luma bytes written = %d, expected = %d", num_bytes, img_width * img_height);

            vxUnmapImagePatch(out_img, map_id);

            rect.start_x = 0;
            rect.start_y = 0;
            rect.end_x   = img_width;
            rect.end_y   = img_height / 2;
            status       = vxMapImagePatch(out_img, &rect, 1, &map_id, &image_addr, &data_ptr, VX_READ_ONLY,
                                     VX_MEMORY_TYPE_HOST, VX_NOGAP_X);

            // Copy CbCr
            num_bytes = fwrite(data_ptr, 1, img_width * img_height / 2, fp);

            if (num_bytes != (img_width * img_height / 2))
                printf("CbCr bytes written = %d, expected = %d", num_bytes, img_width * img_height / 2);

            vxUnmapImagePatch(out_img, map_id);

            vxReleaseImage(&out_img);
        }

        fclose(fp);
    }

    return (status);
}

void scale_set_coeff(tivx_vpac_msc_coefficients_t* coeff, uint32_t interpolation)
{
    uint32_t i;
    uint32_t idx;
    uint32_t weight;

    idx                           = 0;
    coeff->single_phase[0][idx++] = 0;
    coeff->single_phase[0][idx++] = 0;
    coeff->single_phase[0][idx++] = 256;
    coeff->single_phase[0][idx++] = 0;
    coeff->single_phase[0][idx++] = 0;
    idx                           = 0;
    coeff->single_phase[1][idx++] = 0;
    coeff->single_phase[1][idx++] = 0;
    coeff->single_phase[1][idx++] = 256;
    coeff->single_phase[1][idx++] = 0;
    coeff->single_phase[1][idx++] = 0;

    if (VX_INTERPOLATION_BILINEAR == interpolation)
    {
        idx = 0;
        for (i = 0; i < 32; i++)
        {
            weight                       = i << 2;
            coeff->multi_phase[0][idx++] = 0;
            coeff->multi_phase[0][idx++] = 0;
            coeff->multi_phase[0][idx++] = 256 - weight;
            coeff->multi_phase[0][idx++] = weight;
            coeff->multi_phase[0][idx++] = 0;
        }
        idx = 0;
        for (i = 0; i < 32; i++)
        {
            weight                       = (i + 32) << 2;
            coeff->multi_phase[1][idx++] = 0;
            coeff->multi_phase[1][idx++] = 0;
            coeff->multi_phase[1][idx++] = 256 - weight;
            coeff->multi_phase[1][idx++] = weight;
            coeff->multi_phase[1][idx++] = 0;
        }
        idx = 0;
        for (i = 0; i < 32; i++)
        {
            weight                       = i << 2;
            coeff->multi_phase[2][idx++] = 0;
            coeff->multi_phase[2][idx++] = 0;
            coeff->multi_phase[2][idx++] = 256 - weight;
            coeff->multi_phase[2][idx++] = weight;
            coeff->multi_phase[2][idx++] = 0;
        }
        idx = 0;
        for (i = 0; i < 32; i++)
        {
            weight                       = (i + 32) << 2;
            coeff->multi_phase[3][idx++] = 0;
            coeff->multi_phase[3][idx++] = 0;
            coeff->multi_phase[3][idx++] = 256 - weight;
            coeff->multi_phase[3][idx++] = weight;
            coeff->multi_phase[3][idx++] = 0;
        }
    }
    else /* STR_VX_INTERPOLATION_NEAREST_NEIGHBOR */
    {
        idx = 0;
        for (i = 0; i < 32; i++)
        {
            coeff->multi_phase[0][idx++] = 0;
            coeff->multi_phase[0][idx++] = 0;
            coeff->multi_phase[0][idx++] = 256;
            coeff->multi_phase[0][idx++] = 0;
            coeff->multi_phase[0][idx++] = 0;
        }
        idx = 0;
        for (i = 0; i < 32; i++)
        {
            coeff->multi_phase[1][idx++] = 0;
            coeff->multi_phase[1][idx++] = 0;
            coeff->multi_phase[1][idx++] = 0;
            coeff->multi_phase[1][idx++] = 256;
            coeff->multi_phase[1][idx++] = 0;
        }
        idx = 0;
        for (i = 0; i < 32; i++)
        {
            coeff->multi_phase[2][idx++] = 0;
            coeff->multi_phase[2][idx++] = 0;
            coeff->multi_phase[2][idx++] = 256;
            coeff->multi_phase[2][idx++] = 0;
            coeff->multi_phase[2][idx++] = 0;
        }
        idx = 0;
        for (i = 0; i < 32; i++)
        {
            coeff->multi_phase[3][idx++] = 0;
            coeff->multi_phase[3][idx++] = 0;
            coeff->multi_phase[3][idx++] = 0;
            coeff->multi_phase[3][idx++] = 256;
            coeff->multi_phase[3][idx++] = 0;
        }
    }
}
