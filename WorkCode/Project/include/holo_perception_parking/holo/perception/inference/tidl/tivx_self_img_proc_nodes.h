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

#ifndef TIVX_SELF_PROC_NODES_H_
#define TIVX_SELF_PROC_NODES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <VX/vx.h>

/*! \brief Creates a Image Pre Processing Node.
 *
 * Node does pre processing needed for conventional deep learning algorithm. Preprocessing steps
 * such as mean subtraction, scaling and plane deinterleaving is supported by this Node.
 *
 *
 * \param [in] graph             The reference to the graph.
 * \param [in] config            Array element type tivxImgPreProcParams, max number of elements = 1
 * \param [in] in_img            input image
 * \param [in] out_tensor        output tensor
 *
 * \ingroup group_vision_apps_kernels_img_proc
 *
 * \retval vx_node A node reference. Any possible errors preventing a successful creation should be checked using
 * <tt>vxGetStatus</tt>
 */
// VX_API_ENTRY vx_node VX_API_CALL tivxImgPreProcNode(vx_graph   graph,
//                                                     vx_array   config,
//                                                     vx_image   in_img,
//                                                     vx_tensor  out_tensor);

/*! \brief Creates a OC Pre Processing Node.
 *
 * Node does pre processing needed for image classification operation
 * Performs only NV12 to BGR conversion
 *
 * \param [in] graph        The reference to the graph.
 * \param [in] config       User data object element type tivxOCPreProcParams
 * \param [in] in_img       input image
 * \param [out] out_tensor  output tensor
 *
 * \ingroup group_vision_apps_kernels_img_proc
 *
 * \retval vx_node A node reference. Any possible errors preventing a successful creation should be checked using
<tt>vxGetStatus</tt>
//  */
// VX_API_ENTRY vx_node VX_API_CALL tivxOCPreProcNode(vx_graph graph,
//                                                    vx_user_data_object  config,
//                                                    vx_image             in_img,
//                                                    vx_tensor            out_tensor);

/*! \brief Creates a OC Post Processing Node.
 *
 * Node does post processing needed for conventional image classification algorithm.
 * Returns top N classes from a list of probabilities
 *
 * \param [in] graph        The reference to the graph.
 * \param [in] config       User data object element type tivxOCPostProcParams
 * \param [in] in_args      input user data object
 * \param [in] in_tensor    input tensor
 * \param [out] results     output user data object
 *
 * \ingroup group_vision_apps_kernels_img_proc
 *
 * \retval vx_node A node reference. Any possible errors preventing a successful creation should be checked using
 * <tt>vxGetStatus</tt>
 */
// VX_API_ENTRY vx_node VX_API_CALL tivxOCPostProcNode(vx_graph graph,
//                                                     vx_user_data_object  config,
//                                                     vx_user_data_object  in_args,
//                                                     vx_tensor            in_tensor,
//                                                     vx_user_data_object  results);

/*! \brief Creates a Post processing Node for Parking Spot Detection Algorithm.
 *
 * Node does generates interpolated points on parking spot periphery from four corners points
 * detected from deep learning based algorithm
 *
 *
 * \param [in] graph                The reference to the graph.
 * \param [in] configuration        Array element type tivxODPostProcParams, max number of elements = 1
 * \param [in] input_key_points     Interleaved 4 corner points of multiple parking spots.
 * \param [in] fwd_table_tensor     Angular map table for rectilinear angle to fish eye angle
 * \param [in] rev_table_tensor     Angular map table for fish eye angle to rectilinear angle
 * \param [in] kp_tensor            output interpolated points on periphery of parking spot
 * \param [in] kp_valid             output flag of validity for each parking spot
 *
 * \ingroup group_vision_apps_kernels_img_proc
 *
 * \retval vx_node A node reference. Any possible errors preventing a successful creation should be checked using
 * <tt>vxGetStatus</tt>
 */

// VX_API_ENTRY vx_node VX_API_CALL tivxODPostProcNode(vx_graph graph,
//                                       vx_array             configuration,
//                                       vx_tensor            input_key_points,
//                                       vx_tensor            fwd_table_tensor,
//                                       vx_tensor            rev_table_tensor,
//                                       vx_tensor            kp_tensor,
//                                       vx_tensor            kp_valid);

/*! \brief Creates a Post processing Node for Parking Spot Detection Algorithm.
 *
 * Node does generates interpolated points on parking spot periphery from four corners points
 * detected from deep learning based algorithm
 *
 *
 * \param [in] graph                The reference to the graph.
 * \param [in] configuration        Array element type tivxODPostProcParams, max number of elements = 1
 * \param [in] input_key_points     Interleaved 4 corner points of multiple parking spots.
 * \param [in] fwd_table_tensor     Angular map table for rectilinear angle to fish eye angle
 * \param [in] rev_table_tensor     Angular map table for fish eye angle to rectilinear angle
 * \param [in] kp_tensor            output interpolated points on periphery of parking spot
 * \param [in] kp_valid             output flag of validity for each parking spot
 *
 * \ingroup group_vision_apps_kernels_img_proc
 *
 * \retval vx_node A node reference. Any possible errors preventing a successful creation should be checked using
 * <tt>vxGetStatus</tt>
 */

// VX_API_ENTRY vx_node VX_API_CALL tivxTESTPostProcNode(vx_graph graph,
//                                       vx_array             configuration,
//                                       vx_tensor            input_key_points,
//                                       vx_tensor            fwd_table_tensor,
//                                       vx_tensor            rev_table_tensor,
//                                       vx_tensor            kp_tensor,
//                                       vx_tensor            kp_valid);

/*! \brief Creates a Post processing Node for Parking Spot Detection Algorithm.
 *
 * Node does generates interpolated points on parking spot periphery from four corners points
 * detected from deep learning based algorithm
 *
 *
 * \param [in] graph                The reference to the graph.
 * \param [in] configuration        Array element type tivxODPostProcParams, max number of elements = 1
 * \param [in] input_key_points     Interleaved 4 corner points of multiple parking spots.
 * \param [in] fwd_table_tensor     Angular map table for rectilinear angle to fish eye angle
 * \param [in] rev_table_tensor     Angular map table for fish eye angle to rectilinear angle
 * \param [in] kp_tensor            output interpolated points on periphery of parking spot
 * \param [in] kp_valid             output flag of validity for each parking spot
 *
 * \ingroup group_vision_apps_kernels_img_proc
 *
 * \retval vx_node A node reference. Any possible errors preventing a successful creation should be checked using
 * <tt>vxGetStatus</tt>
 */

// VX_API_ENTRY vx_node VX_API_CALL tivxSPPostProcNode(vx_graph graph,
//                                       vx_int16             input,
//                                       vx_int16             output);

/*! \brief Creates a Dense Optical Flow (Dof) 3 plane creation Node.
 *
 * Node does creation of three planes (each of 8 bit) from the raw 32 bit output from Dof hardware accelerator
 * 3 planes corresponds to horizontal, vertical flow vectors and confidence
 *
 * \param [in] graph         The reference to the graph.
 * \param [in] config        Array element type tivxDofPlaneSepParams, max number of elements = 1
 * \param [in] dof_flow      input dof flow vectors
 * \param [out] out_planes    output planes.
 *
 * \ingroup group_vision_apps_kernels_img_proc
 *
 * \retval vx_node A node reference. Any possible errors preventing a successful creation should be checked using
 * <tt>vxGetStatus</tt>
 */
// VX_API_ENTRY vx_node VX_API_CALL tivxDofPlaneSepNode(vx_graph             graph,
//                                                      vx_user_data_object  config,
//                                                      vx_image             dof_flow,
//                                                      vx_tensor            out_planes);

/*! \brief Creates an image with pixel level detection/label overlayed.
 *
 * Node does blending of input image with pixel level detection/classification data for visualization purpose.
 *
 * \param [in] graph                The reference to the graph.
 * \param [in] kernel               The reference to openvx kernel
 * \param [in] configuration        Array element type tivxODPostProcParams, max number of elements = 1
 * \param [in] tidl_out_args        out args of tidl to receive the scale values of each output tensor
 * \param [in] in_img               Input image.
 * \param [in] num_output_tensors   Number of output tensors/images.
 * \param [in] detection            Detection planes
 * \param [out] out_img             ovelayed output image
 *
 * \ingroup group_vision_apps_kernels_img_proc
 *
 * \retval vx_node A node reference. Any possible errors preventing a successful creation should be checked using
 * <tt>vxGetStatus</tt>
 */

//  VX_API_ENTRY vx_node VX_API_CALL tivxPixelVizNode(vx_graph             graph,
//                                                    vx_kernel            kernel,
//                                                    vx_user_data_object  configuration,
//                                                    vx_user_data_object  tidl_out_args,
//                                                    vx_image             in_img,
//                                                    vx_int32             num_output_tensors,
//                                                    vx_tensor            detection[],
//                                                    vx_image             out_img[]);

/*! \brief Estimating the camera location from captured image and map information
 *
 * Node estimates the location in 3d world co-ordinate
 *
 * \param [in] graph                The reference to the graph.
 * \param [in] configuration        Array element type tivxODPostProcParams, max number of elements = 1
 * \param [in] voxel_info           Voxel info. voxels are cuboid in real world
 * \param [in] map_3d_points        Map 3D points
 * \param [in] map_desc             Map descriptors
 * \param [in] ext_feat_pt          Externally computed feature points(x,y)
 * \param [in] ext_feat_desc        Feature descriptor for each feature point
 * \param [in] up_samp_wt           Filter weights for upsampling
 * \param [in] lens_dist_table      Fish eye lens distortion table
 * \param [out] pose_tensor         Output pose matrix of size 3x4
 *
 * \ingroup group_vision_apps_kernels_img_proc
 *
 * \retval vx_node A node reference. Any possible errors preventing a successful creation should be checked using
 * <tt>vxGetStatus</tt>
 */

// VX_API_ENTRY vx_node VX_API_CALL tivxVisualLocalizationNode(vx_graph graph,
//                                       vx_array             configuration,
//                                       vx_tensor            voxel_info,
//                                       vx_tensor            map_3d_points,
//                                       vx_tensor            map_desc,
//                                       vx_tensor            ext_feat_pt,
//                                       vx_tensor            ext_feat_desc,
//                                       vx_tensor            up_samp_wt,
//                                       vx_tensor            lens_dist_table,
//                                       vx_matrix            pose_tensor);
/*! \brief Visualization of the estimated location
 *
 * Node generated an image with visualization of X, Y location of 3D world on image plane
 *
 * \param [in] graph                The reference to the graph.
 * \param [in] configuration        Array element type tivxODPostProcParams, max number of elements = 1
 * \param [in] pose_tensor          Input pose matrix created by tivxVisualLocalizationNode Node
 * \param [out] output_image        Output image
 *
 * \ingroup group_vision_apps_kernels_img_proc
 *
 * \retval vx_node A node reference. Any possible errors preventing a successful creation should be checked using
 * <tt>vxGetStatus</tt>
 */
// VX_API_ENTRY vx_node VX_API_CALL tivxPoseVizNode(vx_graph graph,
//                                       vx_array             configuration,
//                                       vx_matrix            pose_tensor,
//                                       vx_image             output_image);

/*! \brief Image Mosiac Node
 *
 * Used to mosiac a list of images onto to a sigle image
 *
 * \param [in] graph             The reference to the graph.
 * \param [in] kernel            The reference to the openvx kernel
 * \param [in] config            Mosaic configuration of type tivxImgMosaicParams
 * \param [out] output_image     Output image of type vx_image
 * \param [in]  input_arr        Array of inputs
 * \param [in]  num_inputs       Number of inputs, i.e number of elements in input_arr[]
 *
 * \ingroup group_vision_apps_kernels_img_proc
 *
 * \retval vx_node A node reference. Any possible errors preventing a successful creation should be checked using
 * <tt>vxGetStatus</tt>
 */
// VX_API_ENTRY vx_node VX_API_CALL tivxImgMosaicNode(vx_graph             graph,
//                                                    vx_kernel            kernel,
//                                                    vx_user_data_object  config,
//                                                    vx_image             output_image,
//                                                    vx_object_array      input_arr[],
//                                                    vx_uint32            num_inputs);

/*! \brief Draw Keypoint Detections Node
 *
 * Used to draw keypoint detections on an image
 *
 * \param [in] graph            reference to the graph.
 * \param [in] configuration    configuration of type tivxDrawKeyPointDetectionParams
 * \param [in] kp_tensor        keypoint tensor from OD postprocessing node
 * \param [in] kp_valid         valid keypoints tensor from OD postprocessing node
 * \param [in] input_tensor     TIDL output tensor of detected key points
 * \param [in] input_image      Input image to draw detections
 * \param [out] output_image    Output image with detections drawn
 *
 * \ingroup group_vision_apps_kernels_img_proc
 *
 * \retval vx_node A node reference. Any possible errors preventing a successful creation should be checked using
 * <tt>vxGetStatus</tt>
 */
// VX_API_ENTRY vx_node VX_API_CALL tivxDrawKeypointDetectionsNode(vx_graph             graph,
//                                                                 vx_user_data_object  configuration,
//                                                                 vx_tensor            kp_tensor,
//                                                                 vx_tensor            kp_valid,
//                                                                 vx_tensor            input_tensor,
//                                                                 vx_image             input_image,
//                                                                 vx_image             output_image);

/*! \brief Draw Box Detections Node
 *
 * Used to draw box detections on an image
 *
 * \param [in] graph            reference to the graph.
 * \param [in] configuration    configuration of type tivxDrawBoxDetectionParams
 * \param [in] input_tensor     TIDL output tensor of detected key points
 * \param [in] input_image      Input image to draw detections
 * \param [out] output_image    Output image with detections drawn
 *
 * \ingroup group_vision_apps_kernels_img_proc
 *
 * \retval vx_node A node reference. Any possible errors preventing a successful creation should be checked using
 * <tt>vxGetStatus</tt>
 */
// VX_API_ENTRY vx_node VX_API_CALL tivxDrawBoxDetectionsNode(vx_graph             graph,
//                                                            vx_user_data_object  configuration,
//                                                            vx_tensor            input_tensor,
//                                                            vx_image             input_image,
//                                                            vx_image             output_image);

VX_API_ENTRY vx_node VX_API_CALL tivxSelfHirainThresholdNode(vx_graph graph, vx_tensor input1, vx_tensor input2,
                                                             vx_tensor scores, vx_tensor indexs);

// VX_API_ENTRY vx_node VX_API_CALL tivxHWC2CHWNode(vx_graph graph, vx_tensor input, vx_tensor output);

#ifdef __cplusplus
}
#endif

#endif /* TIVX_IMG_PROC_NODES_H_ */
