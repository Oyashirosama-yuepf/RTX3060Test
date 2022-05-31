/*
 *
 * Copyright (c) 2019 Texas Instruments Incorporated
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

#ifndef TIVX_SELF_PROC_KERNELS_H_
#define TIVX_SELF_PROC_KERNELS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <VX/vx.h>
#include <VX/vx_kernels.h>

#include "itidl_ti.h"

/**
 * \defgroup group_vision_apps_kernels_img_proc TIVX Kernels for Image Pre/Post Processing
 *
 * \brief This section documents the kernels defined for Image Pre/Post Processing
 *
 * \ingroup group_vision_apps_kernels
 */
/*!
 * \file
 * \brief The list of supported kernels in this kernel extension.
 */

/*! \brief OpenVX module name
 * \ingroup group_vision_apps_kernels_img_proc
 */
#define TIVX_MODULE_NAME_SELF_PROC "private_proc"

// /*! \brief Kernel Name: Image Pre Processing
//  *  \see group_vision_apps_kernels_img_proc
//  */
// #define TIVX_KERNEL_IMG_PREPROCESS_NAME     "com.ti.img_proc.img.preprocess"

// /*! \brief Kernel Name: OC Pre Processing
//  *  \see group_vision_apps_kernels_img_proc
//  */
// #define TIVX_KERNEL_OC_PRE_PROC_NAME     "com.ti.img_proc.oc.pre.proc"

// /*! \brief Kernel Name: OC Post Processing
//  *  \see group_vision_apps_kernels_img_proc
//  */
// #define TIVX_KERNEL_OC_POST_PROC_NAME     "com.ti.img_proc.oc.post.proc"

// /*! \brief Kernel Name: Parking Spot detection Post Processing
//  *  \see group_vision_apps_kernels_img_proc
//  */
// #define TIVX_KERNEL_OD_POSTPROCESS_NAME     "com.ti.img_proc.od.postprocess"

// /*! \brief Kernel Name: Parking Spot detection Post Processing
//  *  \see group_vision_apps_kernels_img_proc
//  */
// #define TIVX_KERNEL_TEST_POSTPROCESS_NAME     "com.ti.img_proc.test.postprocess"

// /*! \brief Kernel Name: Parking Spot detection Post Processing
//  *  \see group_vision_apps_kernels_img_proc
//  */
// #define TIVX_KERNEL_SP_POSTPROCESS_NAME     "com.ti.img_proc.sp.postprocess"

// /*! \brief Kernel Name: Dense Optical Flow plane seperation
//  *  \see group_vision_apps_kernels_img_proc
//  */
// #define TIVX_KERNEL_DOF_PLANE_SEPERATION_NAME     "com.ti.img_proc.dof.plane.seperation"

// /*! \brief Kernel Name: Pixel visualization
//  *  \see group_vision_apps_kernels_img_proc
//  */
// #define TIVX_KERNEL_PIXEL_VISUALIZATION_NAME     "com.ti.img_proc.pixel.visualization"

// /*! \brief Kernel Name: Ego Localization
//  *  \see group_vision_apps_kernels_img_proc
//  */
// #define TIVX_KERNEL_VISUAL_LOCALIZATION_NAME     "com.ti.img_proc.visual.localization"

// /*! \brief Kernel Name: Pose Visualization
//  *  \see group_vision_apps_kernels_img_proc
//  */
// #define TIVX_KERNEL_POSE_VISUALIZATION_NAME     "com.ti.img_proc.pose.visualization"

// /*! \brief Kernel Name: Image Mosaic
//  *  \see group_vision_apps_kernels_img_proc
//  */
// #define TIVX_KERNEL_IMG_MOSAIC_NAME             "com.ti.img_proc.img.mosaic"

// /*! \brief Kernel Name: Draw Keypoint Detections
//  *  \see group_vision_apps_kernels_img_proc
//  */
// #define TIVX_KERNEL_DRAW_KEYPOINT_DETECTIONS_NAME     "com.ti.img_proc.od.draw.keypoint.detections"

// /*! \brief Kernel Name: Draw Box Detections
//  *  \see group_vision_apps_kernels_img_proc
//  */
// #define TIVX_KERNEL_DRAW_BOX_DETECTIONS_NAME     "com.ti.img_proc.od.draw.box.detections"

// my node name
#define TIVX_KERNEL_SELF_HIRAIN_THRESHOLD_NAME "com.ti.self.hirain.threshold"

/*!
 * \brief
 * \ingroup group_vision_apps_kernels_img_proc
 */
/* Number of maximum output tensor for visualization purpose. motion/semantic/depth*/
// #define TIVX_PIXEL_VIZ_MAX_TENSOR  (3U)

// /*For semantic segmentation supported maximum class is 5 including background*/
// /*For depth tensor output is U08, which makes for each value one different color has to be assigned, so each value is
// treated as different class*/ #define TIVX_PIXEL_VIZ_MAX_CLASS  (256U)

// #define TIVX_IMG_MOSAIC_MAX_INPUTS    (8U)
// #define TIVX_IMG_MOSAIC_MAX_CHANNELS  (4U)
// #define TIVX_IMG_MOSAIC_MAX_WINDOWS   (TIVX_IMG_MOSAIC_MAX_INPUTS * TIVX_IMG_MOSAIC_MAX_CHANNELS)

// /* Maximum number of classes drawn on the image */
// #define TIVX_DRAW_KEYPOINT_DETECTIONS_MAX_CLASSES  (16)
// #define TIVX_DRAW_BOX_DETECTIONS_MAX_CLASSES       (128)

// #define TIVX_OC_MAX_CLASSES  (10)
// /*!
//  * \brief
//  * \ingroup group_vision_apps_kernels_img_proc
//  */

// typedef struct{
//   /**Mean pixel for each output plane which needs to be subtracted*/
//   vx_float32 mean_pixel[3];

//   /**Scale value for each output plane which needs to be multiplied*/
//   vx_float32 scale_val[3];

//   /**Pad value for output planes for each side of image*/
//   vx_int32 pad_pixel[4];

//   /** To enable 8 bit or 16 bit input/output tensor for tidl. 0 means 8 bit, 1 means 16 bit*/
//   vx_int32 tidl_8bit_16bit_flag;

//   /** Falg to indicate input is RGB or YUV. 0 means RGB otherwise YUV*/
//   vx_int32 ip_rgb_or_yuv;

//   /** color conversion flag for seperating the plane as peer the model requirement*/
//   vx_int32 color_conv_flag;

//   /** Number of times to clear the output buffer*/
//   vx_uint32 clear_count;

//   /** Skip processing */
//   vx_int32 skip_flag;

// }tivxImgPreProcParams;

// /*!
//  * \brief
//  * \ingroup group_vision_apps_kernels_img_proc
//  */

// typedef struct{

//   /** Detection tensor I/O params */
//   sTIDL_IOBufDesc_t ioBufDesc;

// }tivxOCPreProcParams;

// /*!
//  * \brief
//  * \ingroup group_vision_apps_kernels_img_proc
//  */

// typedef struct{

//   /** Detection tensor I/O params */
//   sTIDL_IOBufDesc_t ioBufDesc;
//   /** Number of top results to consider */
//   vx_int32 num_top_results;

// }tivxOCPostProcParams;

// /*!
//  * \brief
//  * \ingroup group_vision_apps_kernels_img_proc
//  */

// typedef struct{

//   /** List of class ID's in descending order */
//   vx_uint32 class_id[TIVX_OC_MAX_CLASSES];
//   /** Number of top results to consider */
//   vx_int32 num_top_results;

// }tivxOCPostProcOutput;

// /*!
//  * \brief
//  * \ingroup group_vision_apps_kernels_img_proc
//  */
// typedef struct {
//   /** focal length of camera*/
//   vx_float32 focal_length;

//   /** Optical center x of the input image*/
//   vx_int32 center_x;

//   /** Optical center y of the input image*/
//   vx_int32 center_y;

//   /** Optical center x multiplication factor of the output image. output image optical center x =
//   inter_center_x_fact*center_x */ vx_int32 inter_center_x_fact;

//   /** Optical center y multiplication factor of the output image. output image optical center y =
//   inter_center_y_fact*center_y */ vx_int32 inter_center_y_fact;

//   /** Number of table entries provided for each angular value for transformation */
//   vx_int32 num_table_rows;

//   /** Maximum nuber of detection */
//   vx_int32 num_max_det;

//   /** Width of the image */
//   vx_int32 width;

//   /** Height of the image */
//   vx_int32 height;

//   /** Width of the image given to deep learning algorithm*/
//   vx_int32 dl_width;

//   /** Height of the image given to deep learning algorithm*/
//   vx_int32 dl_height;

//   /** Points per line to be interpolated for visualization purpose*/
//   vx_int32 points_per_line;

//   /** Number of keypoints to be detected by algorithm for each parking spot*/
//   vx_int32 num_keypoints;

//   /** Offset of the object information by the deep learning algorithm in output buffer*/
//   vx_int32 output_buffer_offset;

//   /** Skip processing */
//   vx_int32 skip_flag;

// }tivxODPostProcParams;

// /*!
//  * \brief
//  * \ingroup group_vision_apps_kernels_img_proc
//  */
// typedef struct {
//   /** focal length of camera*/
//   vx_float32 focal_length;

//   /** Optical center x of the input image*/
//   vx_int32 center_x;

//   /** Optical center y of the input image*/
//   vx_int32 center_y;

//   /** Optical center x multiplication factor of the output image. output image optical center x =
//   inter_center_x_fact*center_x */ vx_int32 inter_center_x_fact;

//   /** Optical center y multiplication factor of the output image. output image optical center y =
//   inter_center_y_fact*center_y */ vx_int32 inter_center_y_fact;

//   /** Number of table entries provided for each angular value for transformation */
//   vx_int32 num_table_rows;

//   /** Maximum nuber of detection */
//   vx_int32 num_max_det;

//   /** Width of the image */
//   vx_int32 width;

//   /** Height of the image */
//   vx_int32 height;

//   /** Width of the image given to deep learning algorithm*/
//   vx_int32 dl_width;

//   /** Height of the image given to deep learning algorithm*/
//   vx_int32 dl_height;

//   /** Points per line to be interpolated for visualization purpose*/
//   vx_int32 points_per_line;

//   /** Number of keypoints to be detected by algorithm for each parking spot*/
//   vx_int32 num_keypoints;

//   /** Offset of the object information by the deep learning algorithm in output buffer*/
//   vx_int32 output_buffer_offset;

//   /** Skip processing */
//   vx_int32 skip_flag;

// }tivxTESTPostProcParams;

// /*!
//  * \brief
//  * \ingroup group_vision_apps_kernels_img_proc
//  */

// typedef struct{
//   /** width of the input dof plane */
//   vx_int32 width;

//   /** height of the input dof plane */
//   vx_int32 height;

//   /**Pad value for output planes for each side of dof plane*/
//   vx_int32 pad_pixel[4];

//   /** To enable 8 bit or 16 bit input/output tensor for tidl. 0 means 8 bit, 1 means 16 bit*/
//   vx_int32 tidl_8bit_16bit_flag;

//   /** Skip processing */
//   vx_int32 skip_flag;

// }tivxDofPlaneSepParams;

// /*!
//  * \brief
//  * \ingroup group_vision_apps_kernels_img_proc
//  */

// typedef struct{
//   /*voxel size in meters for x,y,z directionin meters*/
//   vx_int32 voxel_size[3];
//   /*map range minimum and maximum for x,y,z direction in meters[x/y/z][min/max]*/
//   vx_int32 map_range[3][2];
//   /*total number of voxels in image*/
//   vx_int32 num_voxels;
//   /*total number of features in map*/
//   vx_int32 num_map_feat;
//   /*Maximum number of match between current frame and map descriptors*/
//   vx_int32 max_feat_match;
//   /*Maximum number of features accounted in given frame of estimation*/
//   vx_int32 max_cur_map_feat;
//   /*Is feature points calculated inside the algorithm or provided from outside. 0->inside,1-outside*/
//   vx_int32 is_feat_comp_ext;
//   /*max number of features possible in a frame*/
//   vx_int32 max_frame_feat;
//   /*initial estimate for location*/
//   vx_float32 init_est[3];
//   /*Input image width for feature point detection */
//   vx_int32 img_width;
//   /*Input image height for feature point detection */
//   vx_int32 img_height;
//   /*Input image width for feature point descriptor detection */
//   vx_int32 desc_plane_width;
//   /*Input image height for feature descriptor detection */
//   vx_int32 desc_plane_height;
//   /*Input size for feature descriptor plane produced by TIDL including padding */
//   vx_int32 desc_plane_size;
//   /*Input descriptor scale in power of 2 */
//   vx_int32 in_desc_scale_pw2;
//   /*upsampling filter scale in power of 2 */
//   vx_int32 in_filter_scale_pw2;
//   /*upsampling filter bias scale in power of 2 */
//   vx_int32 in_bias_scale_pw2;
//   /*Output descriptor scale */
//   vx_int32 out_desc_scale;
//   /* NMS score threshold for feature point filtering */
//   vx_int32 score_th;
//   /* Start location for tidl tensor */
//   vx_int32 tidl_tensor_startx[2];
//   /* pitch for tidl tensor */
//   vx_int32 tidl_tensor_pitch[2];
//   /* Lens fish eye distortion correction table size*/
//   vx_int32 lens_dist_table_size;
//   /** Skip processing */
//   vx_int32 skip_flag;

// }tivxVisualLocalizationParams;

// typedef struct{
//   /*Image width for visualization*/
//   vx_int32 img_width;
//   /*Image height for visualization*/
//   vx_int32 img_height;
//   /*Image planes*/
//   vx_int32 img_num_planes;
//   /*spatial resolution in x direction for visualization*/
//   vx_float32 pixel_per_meter_w;
//   /*spatial resolution in y direction for visualization*/
//   vx_float32 pixel_per_meter_h;
//   /*minimum location (X) of the world co-ordinte mapped to x=0 in imge*/
//   vx_float32 min_loc_x;
//   /*minimum location (Y)of the world co-ordinte mapped to y=0 in imge*/
//   vx_float32 min_loc_y;
//   /*Inveerse of the projection matrix to be displayed or not*/
//   vx_int32 use_inv_proj_mat;
//   /*running frame counter*/
//   vx_int32 cur_frame_num;
//   /** Skip processing */
//   vx_int32 skip_flag;

// }tivxPoseVizParams;

// /*!
//  * \brief
//  * \ingroup group_vision_apps_kernels_img_proc
//  */
// typedef struct {

//   /** Number of input tensor*/
//   vx_int32 num_input_tensors;

//   /** Number of output tensor. Most likely this will be equal to number of input tensors*/
//   vx_int32 num_output_tensors;

//   /** Number of classes for each input tensor for visualization*/
//   vx_int32 num_classes[TIVX_PIXEL_VIZ_MAX_TENSOR];

//   /** Valid ROI for each class for visualiization. [TL_x, TL_y, BR_x, BR_y] */
//   vx_int32 valid_region[TIVX_PIXEL_VIZ_MAX_CLASS][4];

//   /** max value for each input tensor*/
//   vx_int32 max_value[TIVX_PIXEL_VIZ_MAX_TENSOR];

//   /** Number of classes for each output tensor*/
//   vx_uint8 color_map[TIVX_PIXEL_VIZ_MAX_TENSOR][TIVX_PIXEL_VIZ_MAX_CLASS][3];

//   /** output image width for each output*/
//   vx_int32 output_width[TIVX_PIXEL_VIZ_MAX_TENSOR];

//   /** output image height for each output*/
//   vx_int32 output_height[TIVX_PIXEL_VIZ_MAX_TENSOR];

//   /** offset for first pixel in each input tensor given out by TIDL*/
//   vx_int32 output_buffer_offset[TIVX_PIXEL_VIZ_MAX_TENSOR];

//   /** Pitch for one output row for each input tensor given out by TIDL*/
//   vx_int32 output_buffer_pitch[TIVX_PIXEL_VIZ_MAX_TENSOR];

//   /** offset for first pixel in input image tensor*/
//   vx_int32 input_img_offset;

//   /** Pitch for input image tensor*/
//   vx_int32 input_img_pitch;

//   /** Pitch for input image each plane pitch*/
//   vx_int32 input_img_plane_pitch;

//   /** Flag to generate raw tidl output*/
//   vx_int32 raw_tidl_op;

//   /** To enable 8 bit or 16 bit input/output tensor for tidl. 0 means 8 bit, 1 means 16 bit*/
//   vx_int32 tidl_8bit_16bit_flag;

//   /** To enable RGB output or yuv output. 0 - RGB, non-zero - YUV*/
//   vx_int32 op_rgb_or_yuv;

//   /** Falg to indicate input is RGB or YUV. 0 means RGB otherwise YUV*/
//   vx_int32 ip_rgb_or_yuv;

//   /** Skip processing */
//   vx_int32 skip_flag;

// }tivxPixelVizParams;

// typedef struct {
//   /** Start postion of image along X direction (horizontal) */
//   vx_uint32 startX;

//   /** Start postion of image along Y direction (vertical) */
//   vx_uint32 startY;

//   /** Width of the image */
//   vx_uint32 width;

//   /** Height of the image */
//   vx_uint32 height;

//   /** Input selector */
//   vx_uint32 input_select;

//   /** Channel selector */
//   vx_uint32 channel_select;

// }tivxImgMosaicWindow;

// /*!
//  * \brief
//  * \ingroup group_vision_apps_kernels_img_proc
//  */
// typedef struct {

//   /** Array of windows */
//   tivxImgMosaicWindow windows[TIVX_IMG_MOSAIC_MAX_WINDOWS];

//   /** Number of windows participating in mosiac operation */
//   vx_uint32 num_windows;

//   /** Number of times to clear the output buffer */
//   vx_uint32 clear_count;

//   /** 0: static overlay on SW mosaic is disabled
//    *  1: AVP2 demo static overlay
//    * */
//   vx_uint32 enable_overlay;

// }tivxImgMosaicParams;

// /*!
//  * \brief
//  * \ingroup group_vision_apps_kernels_img_proc
//  */
// typedef struct {

//   /** Detection tensor I/O params */
//   sTIDL_IOBufDesc_t ioBufDesc;

//   /** User config visualization threshold */
//   vx_float32 viz_th;

//   /** Maximum nuber of detection */
//   vx_int32 num_max_det;

//   /** Original Width of the image */
//   vx_int32 width;

//   /** Original Height of the image */
//   vx_int32 height;

//   /** DL Width of the image */
//   vx_int32 dl_width;

//   /** DL Height of the image */
//   vx_int32 dl_height;

//   /** Points per line to be interpolated for visualization purpose*/
//   vx_int32 points_per_line;

//   /** Number of keypoints to be detected by algorithm for each parking spot*/
//   vx_int32 num_keypoints;

//   /** List of valid class IDs to draw*/
//   vx_int32 class_id[TIVX_DRAW_KEYPOINT_DETECTIONS_MAX_CLASSES];

//   /** Number of valid classes to draw*/
//   vx_int32 num_classes;

//   /** Skip processing */
//   vx_int32 skip_flag;

// }tivxDrawKeypointDetectionsParams;

// /*!
//  * \brief
//  * \ingroup group_vision_apps_kernels_img_proc
//  */
// typedef struct {

//   /** Detection tensor I/O params */
//   sTIDL_IOBufDesc_t ioBufDesc;

//   /** User config visualization threshold */
//   vx_float32 viz_th;

//   /** width of the image */
//   vx_int32 width;

//   /** height of the image */
//   vx_int32 height;

//   /** Number of classes for each output tensor*/
//   vx_uint8 color_map[TIVX_DRAW_BOX_DETECTIONS_MAX_CLASSES][3];

//   /** Number of valid classes to draw*/
//   vx_int32 num_classes;

//   /** Skip processing */
//   vx_int32 skip_flag;

// }tivxDrawBoxDetectionsParams;

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

// /*!
//  * \brief Function to register IMG_PROC Kernels on the arm Target
//  * \ingroup group_tivx_ext
//  */
// void tivxRegisterImgProcTargetArmKernels(void);

// /*!
//  * \brief Function to un-register IMG_PROC Kernels on the arm Target
//  * \ingroup group_tivx_ext
//  */
// void tivxUnRegisterImgProcTargetArmKernels(void);

// /*!
//  * \brief Used for the Application to create the pix viz kernel from the context.
//  * \ingroup group_vision_apps_kernels_img_proc
//  */
// vx_kernel tivxAddKernelPixelViz(vx_context context, vx_int32 num_output_tensors);

// /*!
//  * \brief Used by the application to create the mosaic kernel from the context.
//  * \ingroup group_vision_apps_kernels_img_proc
//  */
// vx_kernel tivxAddKernelImgMosaic(vx_context context, vx_int32 num_inputs);

// /*!
//  * \brief Set default parameters for tivxImgMosaicParams
//  * \ingroup group_vision_apps_kernels_img_proc
//  */
// void tivxImgMosaicParamsSetDefaults(tivxImgMosaicParams *prms);

#ifdef __cplusplus
}
#endif

#endif /* TIVX_IMG_PROC_KERNELS_H_ */
