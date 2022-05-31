#include "TI/tivx.h"
#include "holo/localization/vision/tidl/tivx_self_img_proc.h"
#include "TI/tivx_target_kernel.h"
#include "tivx_kernels_host_utils.h"
#include "holo/localization/vision/tidl/tivx_hirain_threshold_host.h"
#include <stdio.h>

static vx_kernel hirain_threshold_self_user_kernel = NULL;

static vx_status VX_CALLBACK hirain_threshold_self_user_kernel_validate(vx_node node, const vx_reference parameters[],
                                                                        vx_uint32 num, vx_meta_format metas[])
{
    vx_status status = VX_SUCCESS;
    return status;
    (void)node;
    (void)parameters;
    (void)num;
    (void)metas;
}

static vx_status VX_CALLBACK hirain_threshold_self_user_kernel_Initialize(vx_node node, const vx_reference parameters[],
                                                                          vx_uint32 num_params)
{
    vx_status status = VX_SUCCESS;
    return status;
    (void)num_params;
    (void)parameters;
    (void)node;
}

vx_status tivxAddKernelSelfHirainThreshold(vx_context context)
{
    vx_kernel kernel = NULL;
    vx_status status;
    uint32_t  index;
    // kernel = hirain_threshold_self_user_kernel_add_as_target_kernel(context);
    vx_enum hirain_threshold_self_user_kernel_id;
    printf("TIDL: hirain_threshold_self_user_kernel_add_as_target_kernel is runing\n");
    status = vxAllocateUserKernelId(context, &hirain_threshold_self_user_kernel_id);
    if (status != VX_SUCCESS)
    {
        printf(
            " hirain_threshold_self_user_kernel_add_as_target_kernel: ERROR: vxAllocateUserKernelId failed (%d)!!!\n",
            status);
    }

    if (status == VX_SUCCESS)
    {
        kernel = vxAddUserKernel(context,
                                 TIVX_KERNEL_SELF_HIRAIN_THRESHOLD_NAME,  // TIVX_TUTORIAL_KERNEL_hirain_threshold_NAME
                                 hirain_threshold_self_user_kernel_id, NULL,
                                 HIRAIN_THRESHOLD_MAX_PARAMS, /* number of parameters objects for this user function */
                                 hirain_threshold_self_user_kernel_validate,
                                 hirain_threshold_self_user_kernel_Initialize,  // kernel param
                                 NULL);
        status = vxGetStatus((vx_reference)kernel);
    }

    /** \endcode */
    if (status == VX_SUCCESS)
    {
        index = 0;
        if (status == VX_SUCCESS)
        {
            status = vxAddParameterToKernel(
                kernel, index, VX_INPUT, VX_TYPE_TENSOR,
                VX_PARAMETER_STATE_REQUIRED  // vx_parameter_state_required or VX_PARAMETER_STATE_OPTIONAL
            );
            index++;
        }
        if (status == VX_SUCCESS)
        {
            status = vxAddParameterToKernel(
                kernel, index, VX_INPUT, VX_TYPE_TENSOR,
                VX_PARAMETER_STATE_REQUIRED  // vx_parameter_state_required or VX_PARAMETER_STATE_OPTIONAL
            );
            index++;
        }
        if (status == VX_SUCCESS)
        {
            status = vxAddParameterToKernel(kernel, index, VX_OUTPUT, VX_TYPE_TENSOR, VX_PARAMETER_STATE_REQUIRED);
            index++;
        }
        if (status == VX_SUCCESS)
        {
            status = vxAddParameterToKernel(kernel, index, VX_OUTPUT, VX_TYPE_TENSOR, VX_PARAMETER_STATE_REQUIRED);
            index++;
        }

        if (status == VX_SUCCESS)
        {
            tivxAddKernelTarget(kernel, TIVX_TARGET_DSP1);
            tivxAddKernelTarget(kernel, TIVX_TARGET_DSP2);
        }

        if (status == VX_SUCCESS)
        {
            status = vxFinalizeKernel(kernel);
        }
        /** \endcode */
        if (status != VX_SUCCESS)
        {
            printf(" hirain_threshold_self_user_kernel_add: ERROR: vxAddParameterToKernel, vxFinalizeKernel failed "
                   "(%d)!!!\n",
                   status);
            vxReleaseKernel(&kernel);
            kernel = NULL;
        }
    }
    else
    {
        kernel = NULL;
        printf(" hirain_threshold_self_user_kernel_add: ERROR: vxAddUserKernel failed (%d)!!!\n", status);
    }

    if (status == VX_SUCCESS)
    {
        hirain_threshold_self_user_kernel = kernel;
        printf(" hirain_threshold_self_user_kernel_add: SUCCESS !!!\n");
        return status;
    }
    return status;
}

vx_status hirain_threshold_self_user_kernel_remove(vx_context context)
{
    vx_status status;
    status                            = vxRemoveKernel(hirain_threshold_self_user_kernel);
    hirain_threshold_self_user_kernel = NULL;
    /** \endcode */

    if (status != VX_SUCCESS)
    {
        printf(" hirain_threshold_self_user_kernel_remove: Unable to remove kernel (%d)!!!\n", status);
    }

    if (status == VX_SUCCESS)
    {
        printf(" hirain_threshold_self_user_kernel_remove: SUCCESS !!!\n");
    }

    return status;
    (void)context;
}
