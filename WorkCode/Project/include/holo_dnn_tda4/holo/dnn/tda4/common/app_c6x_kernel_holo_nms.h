#ifndef APP_C6X_KERNEL_NMS_H
#define APP_C6X_KERNEL_NMS_H

#define APP_DEBUG
#ifdef APP_DEBUG
#define APP_PRINTF(f_, ...)
#else
#define APP_PRINTF(f_, ...)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <VX/vx.h>

#include "tiadalg_interface.h"

/**
 * @func tiadalg_image_recursive_nms_c66
 *
 * @brief It does scores buffer thresholding, and then NMS is performed. This is helpful
 *        in the scenario where score are sturated in clusters.
 *
 * @param score_buf          [in]  : Input 8b score buffer
 * @param img_width          [in]  : Input image width corresponding to \c score_buf
 * @param img_pitch          [in]  : Input image width pitch corresponding to \c score_buf
 * @param img_height         [in]  : Input image height corresponding to \c score_buf
 * @param cur_score_th       [in]  : score threshold value
 * @param max_frame_feat     [in]  : maximum feature points
 * @param guard_pixels       [in]  : guard pixels to be avoided in each direction of x and y.
 * @param scratch            [in]  : scratch buffer
 * @param data_type          [in]  : score_buf data type
 * @param out_buf            [out] : interleaved x and y of each feature points
 *
 * @note
 * - Step 1 if score_buf[i] < cur_score_th, then score_buf[i] = 0
 * - Step 2 Then 3x3 NMS is performed on filtered out scores
 * - Size of the buffer \c scratch is \c img_width * 2
 * - \c out_buf will have feature points x and y co-ordinated interleaved. x0,y0,x1,y1,x2,y2,x3,y3,... so on
 * - return value is total number of generated feature points
 */
// int32_t tiadalg_image_recursive_nms_c66(int8_t* score_buf, int32_t img_width, int32_t img_pitch, int32_t img_height,
//                                         int32_t cur_score_th, int32_t max_frame_feat,
//                                         int32_t guard_pixels, int8_t* scratch, int32_t data_type,
//                                         int32_t* out_buf);

typedef struct
{
    // nms parameter
    vx_int32            img_width;
    vx_int32            img_height;
    vx_int32            img_pitch;
    vx_int32            cur_score_th;
    vx_int32            max_frame_feat;
    vx_int32            guard_pixels;
    e_tiadalg_data_type data_type;

} tivxHoloNmsParams;

typedef struct
{
    // nms output cfg
    vx_int32 num_key_points;
} tivxHoloNmsOutParams;

// ######################################## kernel holo_nms
/*参数序号，参数总数，kennel名字*/
#define HOLO_NMS_CONFIG (0u)
#define HOLO_NMS_INPUT_TENSOR (1u)
#define HOLO_NMS_OUTPUT_TENSOR (2u)
#define HOLO_NMS_OUTPUT_CONFIG (3u)
#define HOLO_NMS_MAX_PARAMS (4u)

#define HOLO_NMS_NAME "c6x_kernel.holo_nms"

/* target 上注册使用的函数 */
void      app_c6x_target_kernel_holo_nms_register(void);
vx_status app_c6x_target_kernel_holo_nms_unregister(void);

/* host 上注册使用的函数 */
vx_status app_c6x_kernel_holo_nms_register(vx_context);
vx_status app_c6x_kernel_holo_nms_unregister(vx_context);

/* 获取node的函数 */
vx_node app_c6x_kernel_holo_nms_node(vx_graph graph, vx_user_data_object config, vx_tensor in, vx_tensor out,
                                     vx_user_data_object out_config);

#ifdef __cplusplus
}
#endif

#endif