#ifndef TIVX_SELF_PROC_KERNELS_H_
#define TIVX_SELF_PROC_KERNELS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <VX/vx.h>
#include <VX/vx_kernels.h>

#include "itidl_ti.h"

#define TIVX_MODULE_NAME_SELF_PROC "private_proc"

// my node name
#define TIVX_KERNEL_SELF_HIRAIN_THRESHOLD_NAME "com.ti.self.hirain.threshold"

// /*********************************
//  *      Functions
//  *********************************/

// /*!
//  * \brief Used for the Application to load the img_proc kernels into the context.
//  * \ingroup group_vision_apps_kernels_img_proc
//  */
void tivxSelfProcLoadKernels(vx_context context);

// /*!
//  * \brief Used for the Application to unload the img_proc kernels from the context.
//  * \ingroup group_vision_apps_kernels_img_proc
//  */
void tivxSelfProcUnLoadKernels(vx_context context);

// /*!
//  * \brief Function to register IMG_PROC Kernels on the C66x Target
//  * \ingroup group_tivx_ext
//  */
void tivxRegisterSelfProcTargetC66Kernels(void);

// /*!
//  * \brief Function to un-register IMG_PROC Kernels on the C66x Target
//  * \ingroup group_tivx_ext
//  */
void tivxUnRegisterSelfProcTargetC66Kernels(void);

#ifdef __cplusplus
}
#endif

#endif /* TIVX_IMG_PROC_KERNELS_H_ */
