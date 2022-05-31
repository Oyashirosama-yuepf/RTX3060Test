#ifndef APP_C6X_KERNEL_UPSAMPLE_H
#define APP_C6X_KERNEL_UPSAMPLE_H

#include <TI/tivx.h>
#include <VX/vx.h>

#define APP_DEBUG
#ifdef APP_DEBUG
#define APP_PRINTF(f_, ...) printf((f_), ##__VA_ARGS__)
#else
#define APP_PRINTF(f_, ...)
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @func tiadalg_sparse_upsampling_c66
 *
 * @brief Given the keypoint locations list at higher image resolution and descriptors at lower image resolution,
 * higher resolution descriptor is derived by nearest neighbour upsampling scheme and spatial 7x7 filtering centered at
 * keypoint location. Only 4x4 upsampling is supported by this API. And 7x7 intra descriptor plane filtering post
 * upsampling is applied. The process is equivalent of upsampling the descriptor plane by factor 4 in both direction,
 * and selecting the values specific to key point locations.
 *
 * @param desc_plane          [in]  : Input descriptor data buffer at lower resolution e.g. (w/4)x(h/4)
 * @param desc_line_pitch     [in]  : One line pitch in each descriptor plane of resolution (w/4)x(h/4)
 * @param desc_plane_pitch    [in]  : Plane pitch for each descriptor plane
 * @param num_desc_planes     [in]  : Number of descriptor planes
 * @param filter_coeff        [in]  : Filter coefficient (7x7) for each descriptor plane, to be applied after 4x4
 * upsampling the \ref desc_plane
 * @param bias                [in]  : 16 bit bias to be applied after 7x7 up-sampling filter for each descriptor plane
 * @param key_point_list      [in]  : Key point locations in higher image resolution domain e.g. (wxh)
 * @param num_key_points      [in]  : Number of key points
 * @param scratch_buffer      [in]  : Scartch buffer required. Not used in _cn API
 * @param is_scratch_filled   [in]  : If scratch buffer was filled by previous call of the API, then it should be passed
 * as '1' otherwise '0'
 * @param desc_scale          [in]  : Scale of descriptor in power of 2
 * @param filter_scale        [in]  : Filter scale in power of 2
 * @param bias_scale          [in]  : Bias scale in power of 2
 * @param out_scale           [in]  : Output scale required in power of 2
 * @param out_desc            [out] : Output upsampled descriptor at higher resolution
 * @param in_desc_data_type   [in]  : input descriptor data type.
 * @param out_desc_data_type  [in]  : output descriptor data type.
 *
 * @note
 * - Size of the buffer \ref desc_plane is equal to \ref desc_line_pitch * \ref desc_plane_height * \ref num_desc_planes
 * - Size of the \ref filter_coeff is 7 * 7 * \ref num_desc_planes
 * - x and y location for each key point has to be provided in the buffer \ref key_point_list
 * - Size of the buffer \ref key_point_list is 2 * \ref num_key_points.
 * - Size of the \ref out_desc is \ref num_desc_planes * \ref num_key_points
 * - Input descriptor data \ref desc_plane is expected in signed 8 bit
 * - \ref out_desc can be unsgined 8 bit or unsigned 16 bit depending on \ref out_desc_data_type
 */
// int32_t tiadalg_sparse_upsampling_c66(int8_t * desc_plane,
//   uint32_t desc_line_pitch,
//   uint32_t desc_plane_pitch,
//   uint16_t num_desc_planes,
//   int8_t *  filter_coeff,
//   int16_t * bias,
//   int32_t * key_point_list,
//   uint16_t num_key_points,
//   int16_t * scratch_buffer,
//   uint8_t is_scratch_filled,
//   int32_t desc_scale,
//   int32_t filter_scale,
//   int32_t bias_scale,
//   int32_t out_scale,
//   void * out_desc,
//   int32_t in_desc_data_type,
//   int32_t out_desc_data_type
//   );
#define MAX_PLANE 256
typedef struct
{
    // nms parameter

    uint32_t desc_line_pitch;
    uint32_t desc_plane_pitch;
    uint16_t num_desc_planes;

    uint8_t is_scratch_filled;
    int16_t num_key_points;

    int32_t filter_scale;
    int32_t desc_scale;
    int32_t bias_scale;
    int32_t out_scale;
    int32_t in_desc_data_type;
    int32_t out_desc_data_type;

    int32_t in_tensor_width;
    int32_t in_tensor_height;
    int32_t out_tensor_width;
    int32_t out_tensor_height;

    int8_t  filter_coeff[MAX_PLANE * 7 * 7];
    int16_t bias[MAX_PLANE * 7 * 7];
} tivxHoloUpsampleParams;

// ######################################## kernel new
/*参数序号，参数总数，kennel名字*/
#define HOLO_UPSAMPLE_CONFIG (0u)
#define HOLO_UPSAMPLE_INPUT_PLANE_TENSOR (1u)
#define HOLO_UPSAMPLE_INPUT_KEYPOINT_TENSOR (2u)
#define HOLO_UPSAMPLE_OUTPUT_KEYPOINT_TENSOR (3u)
#define HOLO_UPSAMPLE_MAX_PARAMS (4u)

#define HOLO_UPSAMPLE_NAME "c6x_kernel.holo_upsample"

/* target 上注册使用的函数 */
void      app_c6x_target_kernel_holo_upsample_register(void);
vx_status app_c6x_target_kernel_holo_upsample_unregister(void);

/* host 上注册使用的函数 */
vx_status app_c6x_kernel_holo_upsample_register(vx_context);
vx_status app_c6x_kernel_holo_upsample_unregister(vx_context);

/* 获取node的函数 */
vx_node app_c6x_kernel_holo_upsample_node(vx_graph graph, vx_array config, vx_tensor in_plane, vx_tensor keypoint,
                                          vx_tensor out_plane);

#ifdef __cplusplus
}
#endif

#endif